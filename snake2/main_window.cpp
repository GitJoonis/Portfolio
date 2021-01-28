/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: Joona Nousiainen, 267048, joona.nousiainen@tuni.fi       #
####################################################################
*/

#include "main_window.hh"
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>
#include <list>

//Constructs the mainwindow for the gui
MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {

    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
    connect(&playtime_, SIGNAL(timeout()), this, SLOT(update()));
    //difficulty ranges from 0 to 5
    ui_.DifficultyspinBox->setMinimum(0);
    ui_.DifficultyspinBox->setMaximum(5);
    ui_.lcdScore->setPalette(Qt::red);
    ui_.pauseButton->setDisabled(true);

}

//Change direction according to keyPressEvent, Qstring to QChar
//takes a key press event as a parameter and changes direction according to the pressed wasd key
void MainWindow::keyPressEvent(QKeyEvent* event) {
    if(direction_ != (event->text())[0])
    {
        direction_ = (event->text())[0];
    }
}

//starts the game when play button is pressed
//disables changing settings and enables the pause button
void MainWindow::on_playButton_clicked() {
    //food and head have different appearance
    const QRectF food_rect(0, 0, 1, 1);
    const QRectF head_rect(0, 0, 1, 1);
    const QPen food_pen(Qt::white, 0);
    const QPen head_pen(Qt::red, 0.01);
    const QBrush brush_food(Qt::red);
    QBrush brush_head(QColor(50,0,0));

    //add the initial head and first food to the scene
    food_ = scene_.addEllipse(food_rect, food_pen, brush_food);
    head_ = scene_.addRect(head_rect, head_pen, brush_head);
    body_parts.push_front(head_);

    //get difficulty settings from spinbox
    difficulty_ = ui_.DifficultyspinBox->value();

    //movement interval is changed according to difficulty
    interval_ = 1000-difficulty_*100;
    adjustSceneArea();

    //set head position and move food
    head_->setPos(width_-1,difficulty_+2);
    moveFood();

    //start the clocks
    playtime_.start(1000);
    update();
    timer_.start(interval_);

    //set settings to disabled, as game is about to start
    ui_.pauseButton->setEnabled(true);
    ui_.DifficultyspinBox->setDisabled(true);
    ui_.rngSeed->setDisabled(true);
    ui_.playButton->setDisabled(true);
}

//makes a new head for the snake to the direction given by direction_
//also checks if the snake died
//if snake didnt eat a food, removes the old tail
//also makes sure the snake has gradient colours, head being the darkest.
void MainWindow::moveSnake() {
    //get direction where new head is going to be, compared to old head
    getDirection();

    //get coordinates for new head
    const QRectF head_rect(0, 0, 1, 1);
    const QPointF old_head_pos = body_parts.front()->scenePos();
    QPointF new_head_pos = old_head_pos + QPoint(x_, y_);

    //check if snake went over the border, if difficulty is 5, kill snake. else, move to other side.
    new_head_pos = isOffPlayfield(new_head_pos.x(), new_head_pos.y());

    //new head is added to the scene
    const QPen pen(Qt::red, 0.01);
    QBrush brush_head(QColor(50,0,0));
    QGraphicsRectItem* new_head;
    new_head = scene_.addRect(head_rect, pen, brush_head);
    new_head->setPos(new_head_pos);

    //old head border is changed into white, to make it distinct from the new head
    body_parts.front()->setPen(QPen(Qt::white,0));
    body_parts.push_front(new_head);

    //variable t is used for the gradient colouring
    unsigned int t = 0;
    //iterate through every body part to do gradient colours, and check for collisions with other body parts.
    for(auto it = body_parts.begin(); it != body_parts.end(); ++it)
    {
        (*it)->setBrush(QColor(50+t*200/size_,0,0));
        // new head is on the same spot as some other body part, but its not the head or the tail.
        if(((*it)->scenePos().x() == new_head_pos.x()) && ((*it)->scenePos().y() == new_head_pos.y()) && (t > 0) && (t != body_parts.size()-1))
        {
            dead_ = true;
            break;
        }
        t++;
    }
    //snake is dead, game is over.
    if(dead_ == true){
        gameOver();
    }

    //else if head didn't hit food, move as usual
    else if(new_head->scenePos() != food_->scenePos())
    {
        scene_.removeItem(body_parts.back());
        delete body_parts.back();
        body_parts.pop_back();

    }
    //snake ate a food, add a new head and add 50 score points.
    else
    {
        score_ = score_+50;
        ui_.lcdScore->display(score_);

        if(body_parts.size() == size_)
        {
            //Snake is as big as the playing area, game won.
            gameOver();
        }

        else
        {
            //player didnt win, so move the food to another location.
            moveFood();
        }
    }
}

//Moves the food to a new location
//tries positions using random number generator, until a free spot is found
void MainWindow::moveFood()
{
    //rng tries positions until it isnt occupied by any body part, and moves food there.
    std::uniform_int_distribution<int> height_dist(0,height_-1);
    std::uniform_int_distribution<int> width_dist(0,width_-1);
    while(true){
        int y = height_dist(rng_);
        int x = width_dist(rng_);
        int t = 0;
    for(auto it = body_parts.begin(); it != body_parts.end(); ++it)
    {
        if((*it)->scenePos().x() == x && (*it)->scenePos().y() == y)
        {
            t++;
        }
    }
    //all body parts had different location
    if (t == 0){
        food_->setPos(x,y);
        break;
    }
    }
}

//changes wasd commands into direction vectors
void MainWindow::getDirection()
{
    if (direction_ == 'a')
    {
        if(x_ != 1)
        {
            x_ = -1;
            y_ = 0;
        }
    }

    else if(direction_ == 'w')
    {
        if(y_ != 1)
        {
            x_ = 0;
            y_ = -1;
        }
    }

    else if(direction_ == 'd')
    {
        if(x_ != -1)
        {
            x_ = 1;
            y_ = 0;
        }
    }

    else if(direction_ == 's')
    {
        if(y_ != -1)
        {
            x_ = 0;
            y_ = 1;
        }
    }
}

//checks if the snake went over the playfield
//parameters: x and y coordinates (int) of the new head
//if difficulty is 5, crossing border kills the snake, else, snake head gets sent to the other side.
//returns the new coordinates as a QPoint
QPoint MainWindow::isOffPlayfield(int x, int y)
{
    if(x > (width_-1))
    {
        if(difficulty_ == 5)
        {
            dead_ = true;
        }
        else
        {
            x = 0;
        }
    }

    else if(x < 0)
    {
        if(difficulty_ == 5)
        {
            dead_ = true;
        }
        else
        {
        x = width_-1;
        }
    }

    else if (y > (height_-1))
    {
        if(difficulty_ == 5)
        {
            dead_ = true;
        }
        else
        {
        y = 0;
        }
    }

    else if(y < 0)
    {
        if(difficulty_ == 5)
        {
            dead_ = true;
        }
        else
        {
        y = height_-1;
        }
    }
    //returns the coordinate point of new head, unchanged if none of the if statements were valid.
    return QPoint(x,y);
}

//adjusts the scere area according to current settings
void MainWindow::adjustSceneArea() {
    //width and height according to difficulty, game field size is height times width
    width_ = 3+difficulty_;
    height_ = 3+difficulty_;
    size_ = width_*height_;
    //adjust playfield rectangle and fit it into view
    const QRectF area(0, 0, width_, height_);
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}

//updates the timer and moves the snake, called by timer_ once every interval.
void MainWindow::update()
{
    //update timer
    if (time_s < 10)
    {
        QString time = QString::fromStdString(std::to_string(time_m) + ":0" + std::to_string(time_s));
        ui_.lcdTimer->display(time);
    }

    else
    {
        QString time = QString::fromStdString(std::to_string(time_m) + ":" + std::to_string(time_s));
        ui_.lcdTimer->display(time);
    }
    ++time_s;

    //60 seconds to a minute
    if(time_s == 60)
    {
        ++time_m;
        time_s = 0;
    }

    //time is up
    if (time_m == 5)
    {
        dead_ = true;
        gameOver();
    }

}

//sets the seed according to rng seed option box
void MainWindow::on_rngSeed_editingFinished()
{
    int seed = ui_.rngSeed->text().toInt();
    rng_.seed(seed);
}

//Pauses the game, or resumes playing if game was already paused
void MainWindow::on_pauseButton_clicked()
{
    //if game is paused, change text to resume and stop timers
    if (ui_.pauseButton->text() == "Pause")
    {
        ui_.pauseButton->setText("Resume");
        timer_.stop();
        playtime_.stop();
    }

    else
    {
        //game is resumed, text changes to pause and timers start again
        ui_.pauseButton->setText("Pause");
        timer_.start(interval_);
        playtime_.start(1000);
    }

}

//Pauses the game and asks the player if he would like to play another game.
void MainWindow::gameOver()
{
    //game is over, stop the clock and disable pause button.
    timer_.stop();
    playtime_.stop();
    ui_.pauseButton->setDisabled(true);

    QMessageBox::StandardButton information;
    //info text according to end result
    std::string result;
    std::string time;
    if(dead_ == true)
    {
        result = "Snek is ded. Game over.";
    }
    else
    {
        result = "Well done! You won.";
    }
    if(time_s < 10)
    {
        time = std::to_string(time_m) + ":0" + std::to_string(time_s);
    }
    else
    {
        time = std::to_string(time_m) + ":" + std::to_string(time_s);
    }
    //ask to start a new game or close gui
    std::string info = result + " Time spent alive: 0" + time + " Score: "+ std::to_string(score_) + ". \nNew game?";
    information = QMessageBox::question(this, "Game over!",QString::fromStdString(info), QMessageBox::No|QMessageBox::Yes);
    if (information == QMessageBox::Yes)
    {
        clear();
    }
    else{
        clear();
        this->close();
    }
}


//new game, clears the playfield and body_parts list, and sets all settings to what they were at the start
void MainWindow::clear()
{
    //empty scene and list of all body parts
    for(auto it = body_parts.begin(); it != body_parts.end(); it++){
        delete *it;
    }
    scene_.clear();
    body_parts.clear();
    //set direction to left
    direction_ = 'a';
    x_ = -1;
    y_ = 0;
    //set timers and score to zero
    time_m = 0;
    time_s = 0;
    score_ = 0;
    //snake is no longer dead
    dead_ = false;
    //settings are no longer disabled, and can be modified for new game
    ui_.DifficultyspinBox->setDisabled(false);
    ui_.rngSeed->setDisabled(false);
    ui_.playButton->setDisabled(false);
    //update score and timers to 0
    ui_.lcdScore->display(score_);
    update();
}
