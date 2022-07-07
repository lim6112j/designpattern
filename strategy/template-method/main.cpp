#include <iostream>
#include <memory>
using namespace std;
class Game {
    public:
        Game(int number_of_players):number_of_players(number_of_players){};
        //template method run
        void run() {
            start();
            while(!have_winner())
                take_turn();
            cout << "player " << get_winner() << " wins \n";
        }
    protected:
        int number_of_players;
        int current_player{0};
        virtual void start()=0;
        virtual void take_turn()=0;
        virtual bool have_winner()=0;
        virtual int get_winner()=0;
};
class Chess : public Game {
    public:
        Chess(): Game(2){};
    protected:
        int current_player{0};
        void start(){
        cout << "starting a chess game with " << number_of_players << " players" << endl;
        };
        void take_turn(){
            cout << "Turn " << turn << " taken by player " << current_player << "\n";
            ++turn;
            current_player = (current_player + 1) % number_of_players;
        };
        bool have_winner(){return turn==max_turns;};
        int get_winner(){return current_player;};
    private:
        int turn{0}, max_turns{10};
};
int main(int argc, char *argv[]) {
    Chess chess;
    chess.run();
    return 0;
}
