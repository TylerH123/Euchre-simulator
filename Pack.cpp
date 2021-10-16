#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "Pack.h"
#include "Card.h"

Pack::Pack()
:next(0){
    int count = 0;
    for(int i=0; i<4; ++i){
        std::string suit = SUIT_NAMES_BY_WEIGHT[i];
        for(int j=7; j<13; ++j){
            std::string rank = RANK_NAMES_BY_WEIGHT[j];
            Card newcard(rank, suit);
            cards[count] = newcard;
            count++;
        }
    }
}

Pack::Pack(std::istream &packinput)
:next(0){
    std::string word;
    int count = 0;
    while(packinput >> word){
        std::string rank = word;
        packinput >> word;
        packinput >> word;
        std::string suit = word;
        Card newcard(rank, suit);
        cards[count] = newcard;
        count++;
    }
}

Card Pack::deal_one(){
    Card newcard = cards[next];
    next++;
    return newcard;
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    for(int i=0; i<7; ++i){
        std::array<Card, 12> top;
        std::array<Card, 12> bot;
        for(int i=0; i<12; ++i){
            top[i] = cards[i];
        }
        for(int i=12; i<24; ++i){
            bot[i-12] = cards[i];
        }
        int count = 0;
        for(int i=0; i<24; i+=2){
            cards[i] = bot[count];
            cards[i+1] = top[count];
            count++;
        }
    }
    reset();
}

bool Pack::empty() const{
    return next==24;
}