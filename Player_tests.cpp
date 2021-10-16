// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_add_card) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c(Card::RANK_NINE, Card::SUIT_CLUBS);
    alice->add_card(c); 
    ASSERT_TRUE(true);
    delete alice;
}

TEST(test_simple_make_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(two_spades);
  }
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_make_trump_2) {
  Player * bob = Player_factory("Bob", "Simple");
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(jack_spades);
  }
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete bob;
}

TEST(test_simple_make_trump_3) {
  Player * bob = Player_factory("Bob", "Simple");
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(two_spades);
  }
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete bob;
}

TEST(test_simple_make_trump_4) {
  Player * bob = Player_factory("Bob", "Simple");
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(jack_spades);
  }
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_make_trump_5) {
  Player * bob = Player_factory("Bob", "Simple");
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(two_spades);
  }
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_make_trump_pass) {
  Player * bob = Player_factory("Bob", "Simple");
  Card two_hearts = Card(Card::RANK_TWO, Card::SUIT_HEARTS);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(two_hearts);
  }
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_make_trump_pass_2) {
  Player * bob = Player_factory("Bob", "Simple");
  Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(nine_hearts);
  }
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_add_discard) {
  Player * bob = Player_factory("Bob", "Simple");
  Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(nine_hearts);
  }
  Card up(Card::RANK_QUEEN, Card::SUIT_DIAMONDS); 
  bob->add_and_discard(up); 
  ASSERT_TRUE(true);
  delete bob; 
}

TEST(test_simple_lead_card) {
  Player * bob = Player_factory("Bob", "Simple");
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(two_spades);
  }
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, nine_spades); //check led card
  delete bob;
}

TEST(test_simple_lead_card_2) {
  Player * bob = Player_factory("Bob", "Simple");
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(jack_spades);
  }
  Card card_led = bob->lead_card(Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, jack_spades); //check led card
  delete bob;
} 

TEST(test_simple_lead_card_3) {
  Player * bob = Player_factory("Bob", "Simple");
  Card two_clubs = Card(Card::RANK_TWO, Card::SUIT_CLUBS);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(two_clubs);
  }
  Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
  bob->add_and_discard(jack_spades);
  Card card_led = bob->lead_card(Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, two_clubs); //check led card
  delete bob;
} 

TEST(test_simple_lead_card_4) {
  Player * bob = Player_factory("Bob", "Simple");
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  bob->add_card(two_spades);
  Card card_led = bob->lead_card(Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, two_spades); //check led card
  delete bob;
}

TEST(test_simple_play_card) {
  Player * bob = Player_factory("Bob", "Simple");
  Card two_clubs = Card(Card::RANK_TWO, Card::SUIT_CLUBS);
  for (int i = 0; i < 5; ++i) {
    bob->add_card(two_clubs);
  }
  Card card_led = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card card_played = bob->play_card(card_led, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_played, two_clubs); //check led card
  delete bob;
} 

TEST(test_simple_play_card_2) {
  Player * bob = Player_factory("Bob", "Simple");
  Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  for (int i = 0; i < 4; ++i) {
    bob->add_card(ten_clubs);
  }
  Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
  bob->add_card(nine_clubs); 
  Card card_led = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(card_led, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_played, nine_clubs); //check led card
  delete bob;
} 

TEST(test_simple_play_card_3) {
  Player * bob = Player_factory("Bob", "Simple");
  Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  bob->add_card(ten_clubs);
  Card card_led = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(card_led, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_played, ten_clubs); //check led card
  delete bob;
} 

TEST(test_simple_play_card_4) {
  Player * bob = Player_factory("Bob", "Simple");
  Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
  Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  bob->add_card(nine_hearts);
  bob->add_card(jack_hearts);
  Card card_led = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(card_led, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_played, nine_hearts); //check led card
  delete bob;
} 

TEST(test_simple_play_card_5) {
  Player * bob = Player_factory("Bob", "Simple");
  Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  bob->add_card(nine_diamonds);
  bob->add_card(jack_diamonds);
  Card card_led = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(card_led, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, jack_diamonds); //check led card
  delete bob;
} 


// Add more tests here

TEST_MAIN()