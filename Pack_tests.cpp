// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
}

TEST(test_pack_istream_ctor) {
    const string filename = "pack.in";
    ifstream ifs(filename);
    assert(ifs.is_open());
    Pack pack(ifs);
    Card first_card = pack.deal_one();
    ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
}

TEST(test_deal_one){
    Pack pack;
    Card first = pack.deal_one();
    Card correct(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(first, correct);
}

TEST(test_deal_one_last){
    Pack pack; 
    for (int i = 0; i < 23; ++i) {
        pack.deal_one();
    }
    Card last = pack.deal_one();
    Card correct(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(last, correct);
}

TEST(test_reset){ 
    Pack pack; 
    for (int i = 0; i < 24; ++i) {
        pack.deal_one();
    }
    pack.reset(); 
    Card first = pack.deal_one();
    Card correct(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(first, correct);
}

TEST(test_empty){
    Pack pack; 
    for (int i = 0; i < 24; ++i) {
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
}

TEST(test_shuffle) {
    std::array<Card, 24> correct = 
    {Card(Card::RANK_KING,Card::SUIT_CLUBS), 
    Card(Card::RANK_JACK,Card::SUIT_HEARTS), 
    Card(Card::RANK_NINE,Card::SUIT_SPADES), 
    Card(Card::RANK_ACE,Card::SUIT_CLUBS), 
    Card(Card::RANK_QUEEN,Card::SUIT_HEARTS), 
    Card(Card::RANK_TEN,Card::SUIT_SPADES),
    Card(Card::RANK_NINE,Card::SUIT_DIAMONDS),
    Card(Card::RANK_KING,Card::SUIT_HEARTS),
    Card(Card::RANK_JACK,Card::SUIT_SPADES),
    Card(Card::RANK_TEN,Card::SUIT_DIAMONDS),
    Card(Card::RANK_ACE,Card::SUIT_HEARTS),
    Card(Card::RANK_QUEEN,Card::SUIT_SPADES),
    Card(Card::RANK_JACK,Card::SUIT_DIAMONDS),
    Card(Card::RANK_NINE,Card::SUIT_CLUBS),
    Card(Card::RANK_KING,Card::SUIT_SPADES),
    Card(Card::RANK_QUEEN,Card::SUIT_DIAMONDS),
    Card(Card::RANK_TEN,Card::SUIT_CLUBS),
    Card(Card::RANK_ACE,Card::SUIT_SPADES),
    Card(Card::RANK_KING,Card::SUIT_DIAMONDS),
    Card(Card::RANK_JACK,Card::SUIT_CLUBS),
    Card(Card::RANK_NINE,Card::SUIT_HEARTS),
    Card(Card::RANK_ACE,Card::SUIT_DIAMONDS),
    Card(Card::RANK_QUEEN,Card::SUIT_CLUBS),
    Card(Card::RANK_TEN,Card::SUIT_HEARTS)};
    Pack pack;
    pack.shuffle();
    for(int i=0; i<24; i++){
       ASSERT_EQUAL(correct[i], pack.deal_one());
    }
}

// Add more tests here

TEST(test_shuffle){
    Pack pack;
    pack.shuffle();
    for(int i=0; i<24; i++){
        cout << pack.deal_one() << endl;
    }
}

TEST_MAIN()
