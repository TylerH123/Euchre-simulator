#include "Pack.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static Pack deck;
static int winning_points;
static Player *players[4];

bool validFile(std::string filename){ 
	std::ifstream f;
	f.open(filename); 
	if (!f.is_open()) 
		return false; 
	return true; 
}

Pack init_pack(string pack_in){
    const string filename = pack_in;
    ifstream ifs(filename);
    Pack pack(ifs);
    return pack;
}

void deal_cards(int dealer_index){
    int shuffle[8] = {3,2,3,2,2,3,2,3}; 
    for (int i = 0; i < 8; ++i) {
        int curr = shuffle[i]; 
        for (int j = 0; j < curr; ++j){
            players[(dealer_index + 1 + i)%4]->
            add_card(deck.deal_one());
        }
    }
}

int trick_winner_index(array<Card, 4> trick,
                       string &trump, Card &led_card){
    Card highest = trick[0];
    int highest_index = 0; 
    for (int i = 1; i<4; ++i) { 
        if (Card_less(highest, trick[i], led_card, trump)) {
            highest = trick[i]; 
            highest_index = i; 
        }
    }
    return highest_index; 
}

int make_trump(string &trump_suit, int &player_index,
                Card &upcard, int &dealer_index){
    bool pick_trump = false;
    int round_counter = 1;
    int round = 1;
    int order_up_index = 0;
    while(!pick_trump){
        if(round_counter > 4)
            round = 2;
        pick_trump = players[player_index]->make_trump
                     (upcard, dealer_index==player_index,
                      round, trump_suit);
        if(pick_trump) {
            std::cout << players[player_index]->get_name() 
                      << " orders up " 
                      << trump_suit 
                      <<  std::endl;
            if (round == 1)
                players[dealer_index]->add_and_discard(upcard);  
            order_up_index = player_index;
        }
        else 
            std::cout << players[player_index]->get_name() 
                      << " passes" << std::endl;
        round_counter++;
        player_index = (player_index + 1)%4;
    }
    cout << "\n";
    return order_up_index; 
}

void play_cards(int points_t1_t2[2], string &trump_suit, 
                int &player_index, array<Card, 4> &played_cards) {
    Card lead_card;
    int player_first = player_index;
    for(int r=0; r<5; ++r){
        //may cause error
        played_cards[player_first] = lead_card 
            = players[player_first]->lead_card(trump_suit);
        std::cout << lead_card << " led by " 
                  << players[player_first]->get_name() 
                  << std::endl;                           
        int player_next = (player_first + 1)%4;
        for(int i=1; i<4; ++i){
            played_cards[player_next] = 
                 players[player_next]->play_card(lead_card, trump_suit);
            std::cout << played_cards[player_next] 
                      << " played by " 
                      << players[player_next]->get_name() 
                      << std::endl;
            player_next = (player_next + 1)%4;
        }
        int trick_winner = trick_winner_index(played_cards,
                                              trump_suit, lead_card);
        player_first = trick_winner;
        cout << players[trick_winner]->get_name() 
             << " takes the trick\n" << endl; 
        if (trick_winner % 2 == 0) 
            points_t1_t2[0]++; 
        else 
            points_t1_t2[1]++;
    }
}

void calculate_points(int points_t1_t2[2], int points[2],
                      int order_up_index) {
    if (points_t1_t2[0] > points_t1_t2[1]) {
        if (order_up_index % 2 == 0) {
            if (points_t1_t2[0] == 3 || points_t1_t2[0] == 4) {
                points[0] += 1;
                cout << players[0]->get_name() << " and " 
                     << players[2]->get_name() << " win the hand" 
                     << endl; 
            }
            else if (points_t1_t2[0] == 5) {
                points[0] += 2;
                cout << players[0]->get_name() << " and " 
                     << players[2]->get_name() << " win the hand" 
                     << "\nmarch!" << endl;
            }
        }
        else {
            if (points_t1_t2[0] > 2) {
                points[0] += 2;
                cout << players[0]->get_name() << " and " 
                     << players[2]->get_name() << " win the hand" 
                     << "\neuchred!" << endl;
            }
        }
    }
    else {
        if (order_up_index % 2 == 1) {
            if (points_t1_t2[1] == 3 || points_t1_t2[1] == 4) {
                points[1] += 1;
                cout << players[1]->get_name() << " and " 
                     << players[3]->get_name() << " win the hand" 
                     << endl; 
            }
            else if (points_t1_t2[1] == 5) {
                points[1] += 2;
                cout << players[1]->get_name() << " and " 
                     << players[3]->get_name() << " win the hand" 
                     << "\nmarch!" << endl;
            }
        }
        else {
            if (points_t1_t2[1] > 2) {
                points[1] += 2;
                cout << players[1]->get_name() << " and " 
                     << players[3]->get_name() << " win the hand" 
                     << "\neuchred!" << endl;
            }
        }
    }
}

void play_hand(string shuffle, int handnumber, int points[2]){
    deck.reset();
    if(shuffle == "shuffle")
        deck.shuffle();
    int dealer_index = handnumber%4;
    cout << "Hand " << handnumber << endl; 
    cout << players[dealer_index]->get_name() << " deals" << endl; 
    deal_cards(dealer_index);
    Card upcard = deck.deal_one();
    cout << upcard << " turned up" << endl; 
    int player_index = (dealer_index+1)%4;
    string trump_suit;
    int order_up_index = make_trump(trump_suit, player_index, 
                                    upcard, dealer_index);
    int points_t1_t2[2] = {};
    player_index = (dealer_index+1)%4;
    array<Card, 4> played_cards;
    play_cards(points_t1_t2, trump_suit, player_index, played_cards); 
    calculate_points(points_t1_t2, points, order_up_index);
}

void print_winner(int points[2]) {
    if (points[0] >= winning_points) 
        cout << players[0]->get_name() << " and "
             << players[2]->get_name() << " win!\n"; 
    if (points[1] >= winning_points) 
        cout << players[1]->get_name() << " and "
             << players[3]->get_name() << " win!\n"; 
}

void print_points(int points[2]) {
    cout << players[0]->get_name() << " and " 
         << players[2]->get_name() << " have " 
         << points[0] << " points" << "\n"
         << players[1]->get_name() << " and " 
         << players[3]->get_name() << " have " 
         << points[1] << " points\n" << endl; 
}

void print_error_message() {
    std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
              << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
              << "NAME4 TYPE4" << std::endl;
}

bool check_param(char *argv[]) {
    bool param1 = (std::stoi(argv[3]) > 100 || 
                   std::stoi(argv[3]) < 0);
    bool param2 = (std::string(argv[2]) != "shuffle" && 
                   std::string(argv[2]) != "noshuffle");
    return param1 || param2; 
}

int main(int argc, char *argv[]) {
    if(argc != 12){
        print_error_message();
        return 1;
    }
    if (!validFile(argv[1])){
		std::cout <<  "Error opening " << argv[1] << std::endl;
		return 1;
	}
    if (check_param(argv)) {
        print_error_message(); 
        return 1;
    } 
    for(int i=5; i<12; i+=2){
        if(string(argv[i]) != "Human" && string(argv[i]) != "Simple"){
            print_error_message();
            return 1;
        }
    }
    for (int i = 0; i<argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << "\n";
    deck = init_pack(argv[1]);
    winning_points = stoi(argv[3]);
    for (int i = 0; i < 4; ++i) {
        players[i] = Player_factory(argv[2*i+4], argv[2*i+5]);
    }
    int hand = 0;
    int points[2] = {};
    while(points[0] < winning_points && points[1] < winning_points){
        play_hand(argv[2], hand, points);
        hand++;
        print_points(points);
    }
    print_winner(points);
    for (int i = 0; i < 4; ++i) {
        delete players[i];
    }
    return 0; 
}