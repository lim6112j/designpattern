#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;
vector<string> state_names{"off hook"s, "connecting"s, "connected"s, "on hold"s,
                           "destroyed"s};
struct CallDialed{};
struct CallConnected{};
struct LeftMessage{};
struct PlaceOnHold{};
struct PhoneThrownIntoWall{};
struct PhoneStateMachine : state_machine_def<PhoneStateMachine> {
  struct OffHook : state<> {};
  struct Connecting : state<> {
    template <class Event, class FSM>
    void on_entry(const Event &event, FSM &fsm) {
      cout << "we are connecting" << endl;
    }
  };
  struct Connected : state<> {};
  struct OnHold : state<> {};
  struct PhoneDestroyed : state<> {};
  struct trasition_table : mpl::vector<
    Row<OffHook, CallDialed, Connecting>,
    Row<Connecting, CallConnected, Connected>,
    Row<Connected, PlaceOnHold, OnHold>,
    Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed>
    > {};
  typedef OffHook initial_state;
};
int main(int argc, char *argv[]) {
  msm::back::state_machine<PhoneStateMachine> phone;
  auto info = [&](){
    auto i = phone.current_state()[0];
    cout << "The phone is currently " << state_names[i] << endl;
  };
  info();
  phone.process_event(CallDialed{});
  info();
  phone.process_event(CallConnected{});
  info();
  return 0; }
