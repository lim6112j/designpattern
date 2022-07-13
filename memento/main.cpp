#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Memento {
  int balance;

public:
  Memento(int balance) : balance(balance) {}
  friend class BankAccount;
  friend class BankAccount2;
};
class BankAccount {
  int balance{0};

public:
  BankAccount(int balance) : balance(balance) {}
  Memento deposit(int amount) {
    balance += amount;
    return {balance};
  }
  void restore(const Memento &m) { balance = m.balance; }
  friend ostream &operator<<(ostream &os, const BankAccount &account) {
    os << "balance: " << account.balance;
    return os;
  }
};
class BankAccount2 {
  int balance{0};
  vector<shared_ptr<Memento>> changes;
  int current; //
public:
  BankAccount2(int balance) : balance(balance) {
    changes.emplace_back(make_shared<Memento>(balance));
  }
  shared_ptr<Memento> deposit(int amount) {
    balance += amount;
    auto m = make_shared<Memento>(balance);
    changes.push_back(m);
    ++current;
    return m;
  }
  void restore(const shared_ptr<Memento> &m) {
    if (m) {
      balance = m->balance;
    }
  }
};
int main() {
  BankAccount ba{100};
  auto m1 = ba.deposit(50);
  auto m2 = ba.deposit(25);
  cout << ba << "\n";
  ba.restore(m1);
  cout << "back to m1: " << ba << "\n";
  ba.restore(m2);
  cout << "back to m2: " << ba << "\n";
  return 0;
}
