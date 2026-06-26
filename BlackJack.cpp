#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Card {
    string rank;
    string suit;
    int value;
};

vector<Card> createDeck() {
    vector<Card> deck;
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    string suits[] = {"♠", "♥", "♦", "♣"};

    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            Card card;
            card.rank = rank;
            card.suit = suit;
            if (rank == "J" || rank == "Q" || rank == "K") {
                card.value = 10;
            } else if (rank == "A") {
                card.value = 11;
            } else {
                card.value = stoi(rank);
            }
            deck.push_back(card);
        }
    }
    return deck;
}

void shuffleDeck(vector<Card>& deck) {
    for (size_t i = 0; i < deck.size(); ++i) {
        size_t j = rand() % deck.size();
        swap(deck[i], deck[j]);
    }
}

Card dealCard(vector<Card>& deck) {
    if (deck.empty()) {
        cout << "\n[Deck ran out of cards. Reshuffling a fresh 52-card deck...]\n";
        deck = createDeck();
        shuffleDeck(deck);
    }
    Card c = deck.back();
    deck.pop_back();
    return c;
}

void printCardsInRows(const vector<Card>& hand) {
    for (int i = 0; i < 5; ++i) {
        for (const auto& card : hand) {
            if (i == 0) cout << "+-----+ ";
            else if (i == 1) cout << "| " << setw(2) << card.rank << "  | ";
            else if (i == 2) cout << "|  " << setw(2) << card.suit << "  | ";
            else if (i == 3) cout << "+-----+ ";
            else if (i == 4) cout << "  ";
        }
        cout << endl;
    }
}

void printDealerCards(const vector<Card>& hand, bool hideSecondCard = false) {
    for (int i = 0; i < 5; ++i) {
        for (size_t j = 0; j < hand.size(); ++j) {
            if (i == 0) {
                if (j == 0)
                    cout << "+-----+ ";
                else
                    cout << "      ";
            } else if (i == 1) {
                if (j == 0)
                    cout << "| " << setw(2) << hand[j].rank << "  | ";
                else
                    cout << "      ";
            } else if (i == 2) {
                if (j == 0)
                    cout << "|  " << setw(2) << hand[j].suit << "  | ";
                else
                    cout << "      ";
            } else if (i == 3) {
                if (j == 0)
                    cout << "+-----+ ";
                else
                    cout << "      ";
            } else if (i == 4) {
                if (j == 1) {
                    if (hideSecondCard) {
                        cout << " ??  ";
                    } else {
                        cout << "| " << setw(2) << hand[j].rank << "  | ";
                        cout << "| " << setw(2) << hand[j].suit << "  | ";
                    }
                }
            }
        }
        cout << endl;
    }
}

int calculateHandValue(const vector<Card>& hand) {
    int total = 0;
    int aces = 0;

    for (const auto& card : hand) {
        total += card.value;
        if (card.rank == "A") {
            aces++;
        }
    }

    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }

    return total;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int chips = 1000;
    char playAgain = 'y';

    vector<Card> deck = createDeck();
    shuffleDeck(deck);

    while (playAgain == 'y' && chips > 0) {
        if (deck.size() < 15) {
            cout << "\n[Deck running low (" << deck.size() << " cards left). Reshuffling a fresh 52-card deck...]\n\n";
            deck = createDeck();
            shuffleDeck(deck);
        }

        cout << "Cards remaining in deck: " << deck.size() << "\n";
        cout << "You have " << chips << " chips.\nPlace your bet: ";
        int bet;
        cin >> bet;

        if (bet <= 0) {
            cout << "Bet must be greater than 0.\n";
            continue;
        }

        if (bet > chips) {
            cout << "Insufficient chips. Bet cannot exceed your available chips.\n";
            continue;
        }

        vector<Card> playerHand;
        vector<Card> dealerHand;

        playerHand.push_back(dealCard(deck));
        dealerHand.push_back(dealCard(deck));
        playerHand.push_back(dealCard(deck));
        dealerHand.push_back(dealCard(deck));

        cout << "\nPlayer's Hand: \n";
        printCardsInRows(playerHand);
        cout << "Total: " << calculateHandValue(playerHand) << " | ";

        cout << "Dealer's Hand: \n";
        printDealerCards(dealerHand, true);
        cout << " ?? \n";

        int playerTotal = calculateHandValue(playerHand);
        while (playerTotal < 21) {
            char choice;
            cout << "\nDo you want to (h)it or (s)tand? ";
            cin >> choice;

            if (choice == 'h') {
                playerHand.push_back(dealCard(deck));
                cout << "Player's Hand: \n";
                printCardsInRows(playerHand);
                playerTotal = calculateHandValue(playerHand);
                cout << "Total: " << playerTotal << "\n";
            } else {
                break;
            }
        }

        if (playerTotal > 21) {
            cout << "\nPlayer busts! Dealer wins.\n";
            chips -= bet;
        } else {
            cout << "\nDealer's Hand: \n";
            printCardsInRows(dealerHand);
            int dealerTotal = calculateHandValue(dealerHand);
            cout << "Total: " << dealerTotal << " | ";

            while (dealerTotal < 17) {
                dealerHand.push_back(dealCard(deck));
                dealerTotal = calculateHandValue(dealerHand);
                cout << "\nDealer's Hand: \n";
                printCardsInRows(dealerHand);
                cout << "Total: " << dealerTotal << " | ";
            }

            if (dealerTotal > 21) {
                cout << "\nDealer busts! Player wins.\n";
                chips += bet;
            } else if (playerTotal > dealerTotal) {
                cout << "\nPlayer wins!\n";
                chips += bet;
            } else if (playerTotal < dealerTotal) {
                cout << "\nDealer wins.\n";
                chips -= bet;
            } else {
                cout << "\nIt's a tie!\n";
            }
        }

        if (chips <= 0) {
            cout << "\nYou ran out of chips! Game Over.\n";
            break;
        }

        cout << "\nDo you want to play again (y/n)? ";
        cin >> playAgain;
    }

    return 0;
}
