/* Player.h
 *
 * Euchre player interface
 * Project UID 1d9f47bfc76643019cfbf037641defe1
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2014-12-21
 */
#include "Player.h"
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

class Simple : public Player{
public:
    Simple(std::string n)
    :name(n){

    }

    virtual const std::string & get_name() const override{
        return name;
    }
    virtual void add_card(const Card &c) override{
        hand.push_back(c);
    }
    virtual bool make_trump(const Card &upcard, bool is_dealer,
            int round, std::string &order_up_suit) const override{
        if(round==1){
            int count = 0;
            std::string trump = upcard.get_suit();
            for(int i=0; i < MAX_HAND_SIZE; ++i){
                Card currentCard = hand.at(i);
                if (currentCard.is_trump(trump)==true &&
                    currentCard.is_face()==true)
                    count++;
            }
            if (count >= 2){
                order_up_suit = trump;
                return true;
            }
        }
        if(round==2){
            int count = 0;
            std::string trump = Suit_next(upcard.get_suit());
            if(is_dealer){
                order_up_suit = trump;
                return true;
            }
            for(int i=0; i < MAX_HAND_SIZE; ++i){
                Card currentCard = hand.at(i);
                if (currentCard.is_trump(trump)==true &&
                    currentCard.is_face()==true)
                    count++;
            }
            if (count >= 1){
                order_up_suit = trump;
                return true;
            }
        }
        return false;
    }
    virtual void add_and_discard(const Card &upcard) override{
        Card lowest = upcard;
        int index=-1;
        std::string trump = upcard.get_suit();
        for(int i=0; i < MAX_HAND_SIZE; ++i){
            Card currentCard = hand.at(i);
            if (Card_less(currentCard, lowest, trump)){
                lowest = currentCard;
                index = i;
            }
        }
        if(index == -1){
            return;
        }
        hand.erase(hand.begin()+index);
        hand.push_back(upcard);
    }
    virtual Card lead_card(const std::string &trump) override{
        if(hand.size()==1){
            Card first = hand.at(0);
            hand.erase(hand.begin());
            return first; 
        }
        Card highest;
        int index = -1;
        for(size_t i=0; i<hand.size(); ++i){
            if(!hand.at(i).is_trump(trump)){
                highest = hand.at(i);
                index = i;
                break;
            }
        }
        if(index == -1){
            highest = hand.at(0);
            int index2 = 0;
            for(size_t i=1; i<hand.size(); ++i){
                if(Card_less(highest, hand.at(i), trump)){
                    highest = hand.at(i);
                    index2 = i;
                }
            }
            hand.erase(hand.begin()+index2);
            return highest;
        }
        for(size_t i=index; i<hand.size(); ++i){
            if(!hand.at(i).is_trump(trump) &&
                hand.at(i) > highest){
                highest = hand.at(i);
                index = i;
            }
        }
        hand.erase(hand.begin() + index);
        return highest;
    }
    virtual Card play_card(const Card &led_card,
                    const std::string &trump) override {
        if(hand.size()==1){
            Card first = hand.at(0);
            hand.erase(hand.begin());
            return first; 
        }
        std::string led_suit;
        if (led_card.is_left_bower(trump)) 
            led_suit = Suit_next(led_card.get_suit());
        else 
            led_suit = led_card.get_suit();
        Card highest;
        int index = -1;
        //finding a card with the same suit 
        for(size_t i=0; i<hand.size(); ++i){
            std::string suit; 
            if (hand.at(i).is_left_bower(trump))
                suit = Suit_next(hand.at(i).get_suit()); 
            else 
                suit = hand.at(i).get_suit();
            if(suit == led_suit){
                highest = hand.at(i);
                index = i;
                break;
            }
        }
        if(index == -1){
            return find_lowest(trump);
        }
        return find_highest_suit(trump, led_card, 
                                 highest, index);
    }
private:
    std::string name;
    std::vector<Card> hand;
    Card find_lowest(const std::string &trump) {
        Card lowest = hand.at(0);
        int index = 0;
        for(size_t i=0; i < hand.size(); ++i){
            Card currentCard = hand.at(i);
            if (Card_less(currentCard, lowest, trump)){
                lowest = currentCard;
                index = i;
            }
        }
        hand.erase(hand.begin()+index);
        return lowest;
    }
    Card find_highest_suit(const std::string &trump, 
                           const Card &led_card,
                           Card &highest,
                           int index) {
        std::string led_suit;
        if (led_card.is_left_bower(trump)) 
            led_suit = Suit_next(led_card.get_suit());
        else 
            led_suit = led_card.get_suit();
        for(size_t i=0; i<hand.size(); ++i){
            std::string suit; 
            if (hand.at(i).is_left_bower(trump))
                suit = Suit_next(hand.at(i).get_suit()); 
            else 
                suit = hand.at(i).get_suit();
            if(suit == led_suit){
                if (Card_less(highest, hand.at(i),
                              led_card, trump)) {
                    highest = hand.at(i);
                    index = i;
                }
            }
        }
        hand.erase(hand.begin()+index);
        return highest;
    }
};

class Human : public Player{
public:
    Human(std::string n)
    :name(n){}
    virtual const std::string & get_name() const override{
        return name;
    }
    virtual void add_card(const Card &c) override{
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }
    //REQUIRES hand is sorted
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) 
                            const override{
        for(size_t i=0; i<hand.size(); ++i){
            std::cout << "Human player " << name 
                      << "'s hand: [" << i << "] " 
                      << hand.at(i) << std::endl;
        }
        std::cout << "Human player " << name 
                  << ", please enter a suit, or \"pass\":" 
                  << std::endl;
        std::string in;
        std::cin >> in;
        if(round == 2 && is_dealer && in == "pass"){
            in = Suit_next(upcard.get_suit());
        }
        if(in == "pass"){
            return false;
        }
        else{
            order_up_suit = in;
            return true;
        }
    }
    virtual void add_and_discard(const Card &upcard) override{
        for(size_t i=0; i<hand.size(); ++i){
            std::cout << "Human player " << name 
                      << "'s hand: [" << i << "] " << hand.at(i) 
                      << std::endl;
        }
        std::cout << "Discard upcard: [-1]" << std::endl;
        std::cout << "Human player "<< name 
                  << ", please select a card to discard:" 
                  << std::endl;
        std::string in;
        std::cin >> in;
        int index = stoi(in);
        if(index == -1){
            return;
        }
        hand.erase(hand.begin()+index);
        hand.push_back(upcard);
    }
    virtual Card lead_card(const std::string &trump) override{
        std::sort(hand.begin(), hand.end());
        for(size_t i=0; i<hand.size(); ++i){
            std::cout << "Human player " << name 
                      << "'s hand: [" << i << "] " << hand.at(i) 
                      << std::endl;
        }
        std::cout << "Human player "<< name 
                  << ", please select a card:" << std::endl;
        std::string in;
        std::cin >> in;
        int index = stoi(in);
        Card out = hand.at(index);
        hand.erase(hand.begin() + index);
        return out;
    }
    virtual Card play_card(const Card &led_card,
                    const std::string &trump) override{
        return lead_card(trump);
    }


    
private:
    std::string name;
    std::vector<Card> hand;
};


Player * Player_factory(const std::string &name,
                        const std::string &strategy){
    if(strategy == "Human")
        return new Human(name);
    if(strategy == "Simple")
        return new Simple(name);
    return nullptr;
    
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}


