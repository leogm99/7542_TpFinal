#include "Tally.h"

Tally::Tally(){
    time = 130;
    ticks = 59;
    boom = false;
    notBoom = false;
}

void Tally::placeInTeam(int id, bool team){
    if (team){
        ctSide[id] = {0, 0};
    } else {
        ttSide[id] = {0, 0};
    }
}

void Tally::swapTeams(){
    ctSide.swap(ttSide);
}

void Tally::playerKilledOther(int id, int other){
    deaths.insert(other);
    // si el player esta en ctSide, el ct mato a un tt
    if (ctSide.find(id) != ctSide.end()){
        // el ct gana 1 kill
        ctSide[id].first++;
        // el tt gana 1 muerte
        ttSide[other].second++;
    } else {
        // si id no esta en ctSide, esta en el ttSide, entonces el tt mato al ct
        ttSide[id].first++;
        // le sumo muerte al ct y kill al tt
        ctSide[other].second++;
    }
}

bool Tally::tickTime(){
    ticks++;
    if ((ticks % 60) == 0){
        time--;
        return true;
    }
    return false;
}

int Tally::getTime(){
    return time;
}

void Tally::resetTime(){
    time = 130;
    boom = false;
    notBoom = false;
}

int Tally::getTerrorist(){
    auto it = ttSide.begin();
    std::advance(it, rand() % ttSide.size());
    return it->first;
}

// checkea si termino la ronda
// x casos:
// 1 - murieron todos los cts -> ganan tts
// 2 - murieron todos los tts (y no plantaron) -> ganan cts
// 3 - se termino el tiempo (ganan los cts pq es de plantar la bomba)
// 4 - exploto la bomba -> ganan tts
// 5 - defusearon la bomba -> ganan cts

void Tally::bombExploded(){
    boom = true;
}

void Tally::bombDefused(){
    notBoom = true;
}

bool Tally::isRoundOver(){
    if (boom) return true;
    if (notBoom) return true;
    if (ctWon()){
        deaths.clear();
        return true;
    } 
    if (ttWon()){
        deaths.clear();
        return true;   
    }
    return false;
}

bool Tally::ctWon(){
    bool isOver = true;
    for (auto it = ttSide.begin(); it != ttSide.end() && isOver; it++){
        isOver = (deaths.find(it->first) != deaths.end());
    }
    // if (bomb.isPlanted() && bomb.) return false;
    return isOver;
}

bool Tally::ttWon(){
    bool isOver = true;
    for (auto it = ctSide.begin(); it != ctSide.end() && isOver; it++){
        isOver = (deaths.find(it->first) != deaths.end());
    }
    // if (bomb.isPlanted() && bomb.) return false;
    return isOver;
}
