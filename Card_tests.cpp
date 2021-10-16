// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(test_constructor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
}

TEST(test_get_rank) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
}

TEST(test_get_suit) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_get_suit_trump) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_CLUBS),
                            Card::SUIT_HEARTS);
}

TEST(test_get_suit_trump_jack) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_DIAMONDS),
                            Card::SUIT_DIAMONDS);
}

TEST(test_is_face) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_face());
    Card c2(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_FALSE(c2.is_face());
}

TEST(test_is_right_bower) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_HEARTS));
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c2.is_right_bower(Card::SUIT_HEARTS));
}

TEST(test_is_left_bower) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_HEARTS));
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c2.is_left_bower(Card::SUIT_DIAMONDS));
}

TEST(test_is_trump) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_trump(Card::SUIT_HEARTS));
}

TEST(test_suit_next) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(c.get_suit()), Card::SUIT_DIAMONDS);
}

TEST(test_less_than) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c4(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c<c2);
    ASSERT_TRUE(c3<c4);
}

TEST(test_greater_than) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c4(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c2>c);
    ASSERT_TRUE(c4>c3);
}

TEST(test_equals) {
    Card c(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c2(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(c2==c);
}

TEST(test_not_equals) {
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c2(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(c2!=c);
}

TEST(test_print) {
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "King of Hearts");
}

TEST(test_card_less) {
    string trump = Card::SUIT_DIAMONDS;
    Card card1(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card card2(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card card3(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card card4(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(card2, card3, trump));
    ASSERT_TRUE(Card_less(card1, card4, trump));
    ASSERT_FALSE(Card_less(card1, card1, trump));
}

TEST(test_card_less_2){
    string trump = Card::SUIT_SPADES;
    Card lead(Card::RANK_SEVEN, Card::SUIT_CLUBS);
    Card card1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card card2(Card::RANK_TEN, Card::SUIT_SPADES);
    Card card3(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(card3, card1, lead, trump));
    ASSERT_TRUE(Card_less(card1, card2, lead, trump));
}

// Add more test cases here

TEST_MAIN()
