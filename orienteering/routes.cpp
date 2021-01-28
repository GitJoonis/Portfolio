/*  TIE-02201 Ohjelmointi 2, K2019 / TIE-02207 Programming 2, S2019
 *  Project 3: Orienteering
 *  Joona Nousiainen
 *  File: routes.cpp
 *  Description: Contains the methods and functions used to handle the information of points and routes of an orienteering map
 * */
#include "routes.hh"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>

using namespace std;

//Distance calculator for use in route_length function
//takes four ints as a parameter, two x coordinates and two y coordinates
//returns the distance of these coordinates as a float, using pythagorean theorem

float point_distance(int first_x, int second_x, int first_y, int second_y){
    return sqrt(pow(second_x-first_x,2)+pow(second_y-first_y,2));
}


Routes::Routes()
{

}

Routes::~Routes()
{
    //Created points have to be deleted, when EXIT command is executed.
    for (auto it = points_.begin(); it != points_.end();it++){
        delete it->second;
    }
}

//sets the width and height of the map, used for print_map function
//takes two ints as a parameter
void Routes::set_map_size(int width, int height)
{
    width_ = width;
    height_ = height;
}

//creates a new Point struct and adds it to the points_ map, using points name as a key
//parameters: reference to the point name (string), x,y and height coordinates as an integer and marker character to be used in print_map
void Routes::add_point(std::string &name, int x, int y, int height, char marker)
{
    if (points_.find(name) == points_.end() && (x > 0 && x <= width_) && (y > 0 && y <= height_) ){
        //create new point
        Point* apu = new Point{name,x,y,height,marker,{}};
        points_[name] = apu;

    }
}

//connects two points as following points in a given route
//parameters: the two points to be connected as string references, route name as string reference
//return true if successful, false if failed
bool Routes::connect_route(std::string &from, std::string &to, std::string &route_name)
{

    //only connect if the given point name is found in points_
    if (points_.find(from) == points_.end() || points_.find(to) == points_.end() ){
        return false;
    }

    else{
        // add the connected pair to routes_ and add the route as a route from which point "from" can be found
        routes_[route_name].push_back(std::make_pair(from,to));
        points_[from]->on_routes.push_back(route_name);
        return true;
    }
}

//prints the map with coordinate rows and columns, and each point represented by its marker
void Routes::print_map() const
{
    std::cout << " ";
    //print first horizontal line of numbers
    for(int i = 1; i < width_+1; i++){

        std::string space = ((i < 10) ? "  " : " ");
        std::cout << space << i;
    }

    std::cout << std::endl;
    //print rest of rows according to set map height
    for(int height = 1; height < height_+1; height++){

        std::string space = ((height < 10) ? " " : "");
        std::cout << space << height;

        for(int width = 1; width < width_+1; width++){

            for (std::map<std::string,Point*>::const_iterator it = points_.begin(); it != points_.end();++it){
                //if height and width match a point, print its marker. else, print '.'
                if (it->second->y == height && it->second->x == width){

                    std::cout << "  " << it->second->marker;
                    break;
                }

                else if (it == --points_.end()){
                    std::cout << "  .";
                }
            }
        }
        std::cout << std::endl;
    }
}

//prints every route given in the text file, found stored in routes_
void Routes::print_route_names() const
{

    std::cout << "Routes:" << std::endl;

    for (auto it = routes_.begin(); it != routes_.end();it++){
        std::cout << " - " << it->first << std::endl;
    }
}

//prints every point and its marker that can be found in the map, by iterating through the points_ map
void Routes::print_points() const
{
    std::cout << "Points:" << std::endl;

    for (std::map<std::string,Point*>::const_iterator it = points_.begin(); it != points_.end();++it){
        std::cout << " - " << it->second->name << " : " << it->second->marker << std::endl;
    }
}

//prints all points included in a given route
//parameters: route name as string reference
void Routes::print_route(const std::string &name) const
{
    //only if route name exists in routes_
    if (routes_.find(name) != routes_.end()){
        std::cout << routes_.at(name).at(0).first << std::endl;

        //while route has points, print the name of the point following the current one
        for(unsigned int i = 0; i < routes_.at(name).size(); i++){
             std::cout << " -> " << routes_.at(name).at(i).second << std::endl;
        }
    }

    else{

        std::cout << "Error: Route named " << name << " can't be found" << std::endl;
    }
}

//prints the total distance of all points found in a given route
//parameters: route name as a string reference
void Routes::route_length(const std::string &name) const
{
    if (routes_.find(name) != routes_.end()){

        float length = 0;

        for(unsigned int i = 0; i < routes_.at(name).size(); i++){
             //declaring the current x and y coordinates and following points x and y coordinates
             int first_x = points_.at(routes_.at(name).at(i).first)->x;
             int second_x = points_.at(routes_.at(name).at(i).second)->x;
             int first_y = points_.at(routes_.at(name).at(i).first)->y;
             int second_y = points_.at(routes_.at(name).at(i).second)->y;
             //length between two points calculated using point_distance function, added to a sum
             length += point_distance(first_x,second_x,first_y,second_y);

        }
        if (length < 10){
            //float precision: 1 decimal digit
            std::cout << "Route " << name << " length was " << std::fixed << std::setprecision(1) << length << std::endl;
        }
        else{
            std::cout << "Route " << name << " length was " << std::fixed << std::setprecision(0) << length << std::endl;
        }
    }

    else{
        std::cout << "Error: Route named " << name << " can't be found" << std::endl;
    }
}

void Routes::greatest_rise(const std::string &point_name) const
{
    std::vector<std::string> highest_routes;
    int highest_rise = 0;
    if (points_.find(point_name) != points_.end()){
        //iterate through all the routes the point is found in
        for(unsigned int i = 0; i < points_.at(point_name)->on_routes.size();i++){
            int rise = 0;
            std::string route = points_.at(point_name)->on_routes.at(i);
            unsigned int location_number = 0;
            //find the position where the point can be found in the given route
            while(routes_.at(route).at(location_number).first != point_name){
                location_number++;
            }

            //check all indexes following the index where we found the point, whether they are higher
            for(unsigned int a = location_number; a < routes_.at(route).size(); a++){
                std::string current_location = routes_.at(route).at(a).first;
                std::string next_location = routes_.at(route).at(a).second;
                int height_difference = points_.at(next_location)->height - points_.at(current_location)->height;

                // new location is higher than the current one.
                if(height_difference >= 0){
                    rise += height_difference;
                }
                // height goes down -> no longer rising
                else if(height_difference < 0){
                    if(rise > highest_rise){
                        highest_rise = rise;
                        highest_routes = {route};
                    }
                    else if(rise == highest_rise){
                        highest_routes.push_back(route);
                    }
                    rise = 0;
                    a = routes_.at(route).size();
                }
            }

            //if last rise was the highest, update highest_rise
            if (rise > highest_rise){
                highest_rise = rise;
                highest_routes = {route};
            }
            //last rise was as high as previous ones, check if it was added already
            else if (rise == highest_rise){
                std::vector<std::string>::iterator it;
                it = std::find(highest_routes.begin(),highest_routes.end(),route);
                if (it == highest_routes.end()){
                    highest_routes.push_back(route);
                }
            }

            //if the last route is the first one to be added
            if (highest_routes.size() == 0){
                highest_routes.push_back(route);
            }
        }

        if (highest_routes.size() != 0){
            if (highest_rise != 0){
                std::cout << "Greatest rise after point " << point_name << ", " << highest_rise << " meters, is on route(s):" << std::endl;
                //alphabetical order
                sort(highest_routes.begin(),highest_routes.end());
                for(unsigned int b = 0; b < highest_routes.size(); b++){
                    std::cout << " - " << highest_routes.at(b) << std::endl;
                }
            }

            else{
                std::cout << "No route rises after point " << point_name << std::endl;
            }
        }
     }

    else{
        std::cout << "Error: Point named " << point_name << " can't be found" << std::endl;
    }
}

