#include <iostream>
#include <memory>
using namespace std;
class Game {
    public:
        Game(int number_of_players):number_of_players(number_of_players){};
        void run() {
            start();
            while(!have_winner()) {

            }
        }
    protected:
        int number_of_players;
        void start() {};
        bool have_winner() {
            return false;
        }
};
int main(int argc, char *argv[]) {
    cout << "hello" << endl;
    Game game(10);
    return 0;
}
