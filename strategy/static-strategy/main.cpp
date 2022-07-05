#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
enum class OutputFormat { markdown, html };
struct ListStrategy {
  virtual void start(ostringstream &oss){};
  virtual void add_item_list(ostringstream &oss, const string &item) = 0;
  virtual void end(ostringstream &oss){};
};
struct MarkdownListStrategy : ListStrategy {
  void add_item_list(ostringstream &oss, const string &item) override {
    oss << "* " << item << endl;
  }
};
struct HtmlListStrategy : ListStrategy {
  void start(ostringstream &oss) override { oss << "<ul>" << endl; }
  void add_item_list(ostringstream &oss, const string &item) override {
    oss << "<li> " << item << " </li>" << endl;
  }
  void end(ostringstream &oss) override { oss << "</ul>" << endl; }
};
template <typename LS> struct TextProcessor {
  void clear() {
    oss.str("");
    oss.clear();
  }
  void append_list(const vector<string> &items) {
    list_strategy.start(oss);
    for (auto &item : items)
      list_strategy.add_item_list(oss, item);
    list_strategy.end(oss);
  }

  string str() const { return oss.str(); };

private:
  ostringstream oss;
  LS list_strategy;
};
int main(int argc, char *argv[]) {
  vector<string> items{"foo", "bar", "baz"};
  TextProcessor<MarkdownListStrategy> tp;
  tp.append_list(items);
  cout << tp.str() << endl;
  tp.clear();
  TextProcessor<HtmlListStrategy> tpp;
  tpp.append_list(items);
  cout << tpp.str() << endl;
  tpp.clear();
  return 0;
}
