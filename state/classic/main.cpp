#include <iostream>

using namespace std;
class LightSwitch;
struct State {
    virtual void on(LightSwitch* ls){
        cout << "light is already on" << endl;
    };
    virtual void off(LightSwitch* ls){
        cout << "light is already off" << endl;
    };
};
struct OnState : State {
    OnState() {
        cout << "Light turned on" << endl;
    }
    void off(LightSwitch *ls) override;
};
struct OffState : State {
    OffState() {
        cout << "Light turned off" << endl;
    }
    void on(LightSwitch *ls) override;
};
class LightSwitch {
    State *state;
    public:
        LightSwitch() {
            state = new OffState();
        }
        void set_state(State* state) {
            this->state = state;
        }
        void on() {
            state->on(this);
        }
        void off() {
            state->off(this);
        }
};

void OnState::off(LightSwitch *ls) {
    cout << "light turn off" << endl;
    ls->set_state(new OffState());
    delete this;
}
void OffState::on(LightSwitch *ls) {
    cout << "light turn on" << endl;
    ls->set_state(new OnState());
    delete this;
}
int main(int argc, char *argv[]) {
    LightSwitch ls ;
    ls.off();
    ls.on();
    ls.on();
    ls.off();

    return 0;
}
