// Ohjelmointi 2: Perusteet
// Kevät 2019
// Joona Nousiainen - 267048
// Ohjelma lukee tekstitiedoston (csv) sisällön ja tallentaa sen tiedot map-tietorakenteeseen.
// Funktioiden avulla voidaan tutkia tietorakenteen sisältöä

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

//struct jossa säilytetään jokaista kirjaa koskevat tiedot: tekijä, nimi ja varausten määrä
struct Book {
    std::string title;
    std::string author;
    int reservations;
};

// split funktio, joka ottaa parametrinaan tekstirivin ja erotinmerkin, ja palauttaa vectorin joka sisältää merkeillä erotellut sanat
// lainattu aikaisempien kierrosten tehtävistä
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// print_libraries -funktio tulostaa tietorakenteeseen tallennettujen kirjastojen nimet
// iteroimalla tietorakenteen läpi ja tulostamalla mapin avaimet
// ottaa parametrinaan "libraries" tietorakenteen

void print_libraries(std::map<std::string,std::vector<Book>> libraries){
    for(std::map<std::string, std::vector<Book>>::iterator it = libraries.begin(); it != libraries.end(); ++it){
        std::cout << it->first << std::endl;
    }
}

// print_material tulostaa kirjastosta löytyvät kirjat aakkosjärjestyksessä
// ottaa parametrina libraries tietorakenteen ja syötteenä annetun kirjaston nimen

void print_material(std::map<std::string,std::vector<Book>> libraries, std::string kirjasto){
    std::vector<std::string> titles_and_authors;
    // map -tietorakenteesta tallennetaan kirjojen nimet ja kirjoittajat vectoriin, joka järjestetään aakkosjärjestykseen
    for(unsigned long int i = 0; i < libraries[kirjasto].size();i++){
        titles_and_authors.push_back(libraries[kirjasto].at(i).author + ": " + libraries[kirjasto].at(i).title);
    }
    std::sort (titles_and_authors.begin(),titles_and_authors.end());
    for (unsigned long int i = 0; i < titles_and_authors.size() ; i++){
        std::cout << titles_and_authors.at(i) << std::endl;
    }
}
// author_found tarkistaa onko tietyssä kirjastossa annetun kirjailijan kirjoja, ja palauttaa totuusarvon
// ottaa parametrina libraries tietorakenteen, kirjaston ja kirjan nimet
bool author_found(std::map<std::string, std::vector<Book>> libraries, std::string library, std::string author){
    std::vector<std::string> authors;
    for(unsigned long int i = 0; i < libraries[library].size();i++){
        authors.push_back(libraries[library].at(i).author);
        }
    if ( std::find(authors.begin(), authors.end(), author) != authors.end()){
        return true;
    }
    else
        return false;

}

// print_books tulostaa annetusta kirjastosta löytyvät halutun kirjailijan teokset ja niiden varausjonojen pituudet
// ottaa parametrina libraries tietorakenteen sekä kirjaston ja kirjailijan nimet

void print_books(std::map<std::string, std::vector<Book>> libraries, std::string kirjasto, std::string author){
    std::vector<std::string> books_and_reservations;
    for(unsigned long int i = 0; i < libraries[kirjasto].size();i++){
        if(libraries[kirjasto].at(i).author == author){
            //jos varausjono on 0, tuloste on "on the shelf", muulloin ilmoitetaan jonon pituus
            if(libraries[kirjasto].at(i).reservations != 0 ){
                books_and_reservations.push_back(libraries[kirjasto].at(i).title + " --- " + std::to_string( libraries[kirjasto].at(i).reservations ) + " reservations");
            }
            else{
                books_and_reservations.push_back(libraries[kirjasto].at(i).title + " --- on the shelf");
            }
        }
    }
    // kirjat aakkosjärjestykseen
    std::sort (books_and_reservations.begin(), books_and_reservations.end());
    for (unsigned long int i = 0; i < books_and_reservations.size() ; i++){
        std::cout << books_and_reservations.at(i) << std::endl;
    }
}
//print_reservable tulostaa pienimmän jonon annetulle kirjalle, mistä tahansa kirjastosta
//ottaa parametrina libraries tietorakenteen sekä kirjan nimen

void print_reservable(std::map<std::string,std::vector<Book>> libraries,std::string title){
std::map<std::string,int> found_books;
for(std::map<std::string, std::vector<Book>>::iterator it = libraries.begin(); it != libraries.end(); ++it){
    auto key = it->first;
    for (unsigned long int i = 0; i < libraries[key].size(); i++){
        //jos löydetty kirja vastaa pyydettyä kirjaa, tarkistetaan löytyykö se jo. jos löytyy, verrataan varausten määrää, ja jätetään lyhyimmällä varauksella oleva kirja
        if (libraries[key].at(i).title == title){
            if (found_books.size() != 0){
                for(std::map<std::string,int>::iterator iter = found_books.begin(); iter != found_books.end();iter++){
                    if (found_books[iter->first] > libraries[key].at(i).reservations){
                        //jos löydetyssä kirjassa on lyhyempi jono, poistetaan edellinen kirja
                        iter = found_books.erase(iter);
                        found_books[key] = libraries[key].at(i).reservations;
                    }
                    else if( found_books[iter->first] == libraries[key].at(i).reservations){
                        found_books[key] = libraries[key].at(i).reservations;
                    }
                }
            }
            else{
                found_books[key] = libraries[key].at(i).reservations;
            }
        }
    }
}
//neljä eri tulostetta riippuen tilanteesta
if (found_books.size() == 0){
    std::cout << "Book is not a library book." << std::endl;
}
else if( found_books.begin()->second > 99){
    std::cout << "The book is not reservable from any library." << std::endl;
}
else if(found_books.begin()->second == 0){
    std::cout << "on the shelf" << std::endl;
    for(std::map<std::string,int>::iterator iter = found_books.begin(); iter != found_books.end(); ++iter){
        std::cout << "--- " << iter->first << std::endl;
    }
}
else{
    std::cout << found_books.begin()->second << " reservations" << std::endl;
    for(std::map<std::string,int>::iterator iter = found_books.begin(); iter != found_books.end(); ++iter){
        std::cout << "--- " << iter->first << std::endl;
    }
}
}
//print_loanable tulostaa kaikki kirjat jotka ovat tällä hetkellä lainattavissa, mistä tahansa kirjastosta.
//ottaa parametrina libraries tietorakenteen
void print_loanable(std::map<std::string, std::vector<Book>> libraries){
    std::vector<std::string> loanable_books;
    for(std::map<std::string, std::vector<Book>>::iterator it = libraries.begin(); it != libraries.end(); ++it){
        auto key = it->first;
        for(unsigned long int i = 0; i < libraries[key].size();i++){
                //jos varausjono on 0, lisätään vectoriin
                if(libraries[key].at(i).reservations == 0 ){
                    if (find(loanable_books.begin(),loanable_books.end(),libraries[key].at(i).title) == loanable_books.end()){
                        loanable_books.push_back(libraries[key].at(i).author + ": " + libraries[key].at(i).title);
                    }
                }
        }
    }
    //aakkosjärjestys
    std::sort(loanable_books.begin(), loanable_books.end());
    for ( long unsigned int a = 0; a < loanable_books.size(); a++){
        std::cout << loanable_books.at(a) << std::endl;
    }
}

int main()
{
    //tiedoston avaaminen, lukeminen ja tarvittaessa avaamisvirheestä ilmoittaminen
    std::map<std::string, std::vector<Book>> libraries;
    std::string input;
    std::cout << "Input file: ";
    std::getline(std::cin,input);
    std::ifstream tiedosto_olio(input);
    if (not tiedosto_olio) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    }
    std::string rivi;
    std::vector <std::string> rivin_kentat;
    //tiedoston sisältämät tiedot erotellaan split-funktion avulla ja tallennetaan rivi kerrallaan vectoriin "rivin_kentat"
    while ( getline(tiedosto_olio, rivi) ){
        rivin_kentat = split(rivi,';', true);
    // jos rivi on väärän pituinen, ohjelman suoritus lopetetaan
        if (rivin_kentat.size() != 4){
            std::cout << "Error: empty field" << std::endl;
            return EXIT_FAILURE;
        }
    //varausten määrää kuvataan structissa kokonaislukuna, siksi on-the-shelf kuvataan nollana
        int reservations = 0;
        if (rivin_kentat.at(3) == "on-the-shelf"){
            reservations = 0;
        }
        else{
            reservations = std::stoi(rivin_kentat.at(3));
        }
    //kirjastoa vastaavaan vectoriin lisätään jokaista kirjaa koskevat tiedot
        libraries[rivin_kentat.at(0)].push_back({rivin_kentat.at(2),rivin_kentat.at(1),reservations});
    }
    //tiedostoa ei enää tarvita
    tiedosto_olio.close();

    //komentojen kysyminen, komennolla quit ohjelman suoritus lopetetaan
    while(true){
        std::cout << "> ";
        std::string input;
        std::string command;
        std::vector<std::string> parts;
        getline(std::cin, input);
        parts = split(input,' ',true);
        command = parts.at(0);

    if ( command == "quit"){
        return EXIT_SUCCESS;
    }
    else if (command == "libraries"){
        print_libraries(libraries);
    }
    else if (command == "material"){
        if (parts.size() != 2){
            std::cout << "Error: error in command " << command << std::endl;
            continue;
        }
        if (libraries.find(parts.at(1)) == libraries.end()){
            std::cout << "Error: unknown library name" << std::endl;
            continue;
        }
        print_material(libraries,parts.at(1));
    }

    else if (command == "books"){
        if (parts.size() != 3){
            std::cout << "Error: error in command " << command << std::endl;
            continue;
        }
        if (libraries.find(parts.at(1)) == libraries.end()){
            std::cout << "Error: unknown library name" << std::endl;
            continue;
        }

       if (author_found(libraries,parts.at(1), parts.at(2)) == 0){
           std::cout << "Error: unknown author" << std::endl;
           continue;
       }

      print_books(libraries, parts.at(1), parts.at(2));
    }
    else if (command == "reservable"){
        if (parts.size() == 1){
            std::cout << "Error: error in command " << command << std::endl;
            continue;
        }
        //parametriksi annetaan koko input lukuunottamatta komentoa, poistetaan ensimmäiset 11 merkkiä
        std::string book_name = input.substr(11);
        //lainausmerkkien poisto tarvittaessa
        book_name.erase(std::remove(book_name.begin(), book_name.end(), '\"'),book_name.end());
        print_reservable(libraries,book_name);
    }
    else if (command == "loanable"){
        if (parts.size() != 1){
            std::cout << "Error: error in command " << command << std::endl;
            continue;
        }
        print_loanable(libraries);
    }
    else {
        std::cout << "Error: Unknown command: " << command << std::endl;
    }
    }
}
