// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
//card function
//constructors
Card::Card()
:rank(RANK_TWO), suit(SUIT_SPADES){}
Card::Card(const std::string &rank_in, const std::string &suit_in)
:rank(rank_in), suit(suit_in){}
//getters
std::string Card::get_rank()const{
    return rank;
}
std::string Card::get_suit()const{
    return suit;
}
std::string Card::get_suit(const std::string &trump) const{
    if(rank==RANK_JACK && (suit==trump || Suit_next(suit)==trump)){
        return trump;
    }
    return suit;
}

bool Card::is_face() const{
    for(int i=9; i<13; ++i){
        if(rank == RANK_NAMES_BY_WEIGHT[i])
        return true;
    }
    return false;
}
bool Card::is_right_bower(const std::string &trump) const{
    return (rank == RANK_JACK && suit == trump); 
}
bool Card::is_left_bower(const std::string &trump) const{
    return (rank == RANK_JACK && suit == Suit_next(trump));
}
bool Card::is_trump(const std::string &trump) const{
    if(rank == RANK_JACK && suit == Suit_next(trump))
        return true;
    return suit==trump;
}

//helper functions
bool operator<(const Card &lhs, const Card &rhs) {
    int index_lhs = 0,
        index_rhs = 0; 
    for (int i = 0; i < NUM_RANKS; ++i) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank())
            index_lhs = i; 
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank())
            index_rhs = i; 
    }
    if (index_rhs == index_lhs) {
        int index_lhs_suit = 0,
            index_rhs_suit = 0;
        for (int i = 0; i < NUM_SUITS; ++i) {
            if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit())
                index_lhs_suit = i; 
            if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit())
                index_rhs_suit = i; 
        }
        return index_lhs_suit < index_rhs_suit;
    }
    return index_lhs < index_rhs;
}
bool operator>(const Card &lhs, const Card &rhs){
    if(!(lhs.get_rank() == rhs.get_rank() &&
         lhs.get_suit() == rhs.get_suit())){
        return !(lhs < rhs);
    }
    return false;
}
bool operator==(const Card &lhs, const Card &rhs){
    return (lhs.get_rank() == rhs.get_rank() && 
            lhs.get_suit() == rhs.get_suit());
}
bool operator!=(const Card &lhs, const Card &rhs){
    return !(lhs.get_rank() == rhs.get_rank() &&
             lhs.get_suit() == rhs.get_suit());
}
std::string Suit_next(const std::string &suit){
    if(suit==Card::SUIT_CLUBS)
        return Card::SUIT_SPADES;
    if(suit==Card::SUIT_SPADES)
        return Card::SUIT_CLUBS;
    if(suit==Card::SUIT_HEARTS)
        return Card::SUIT_DIAMONDS;
    if(suit==Card::SUIT_DIAMONDS)
        return Card::SUIT_HEARTS;
    throw "invalid suit";
}
std::ostream & operator<<(std::ostream &os, const Card &card){
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}
int Card_less_helper(const Card &a, const Card &b,
                     const std::string &trump){
    if(a==b)
        return -1;
    if(a.is_right_bower(trump))
        return -1; 
    if(b.is_right_bower(trump))
        return 1;
    if(a.is_left_bower(trump))
        return -1;
    if(b.is_left_bower(trump)){
        return 1;
    }
    if(a.is_trump(trump) && !b.is_trump(trump))
        return -1;
    if(!a.is_trump(trump) && b.is_trump(trump))
        return 1;
    return 0;
}
bool Card_less(const Card &a, const Card &b,
               const std::string &trump){
    if(Card_less_helper(a,b,trump)<0){
        return false;
    }
    if(Card_less_helper(a,b,trump)>0){
        return true;
    }
    return a<b;
}
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    if(Card_less_helper(a,b,trump)<0){
        return false;
    }
    if(Card_less_helper(a,b,trump)>0){
        return true;
    }
    if(a.is_trump(led_card.get_suit()) &&
      !b.is_trump(led_card.get_suit()))
        return false;
    if(!a.is_trump(led_card.get_suit()) &&
        b.is_trump(led_card.get_suit()))
        return true;
    return a<b;
}