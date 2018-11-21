// https://github.com/dropbox/json11
// https://github.com/dropbox/json11.git

#include "json11.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

string json_fname{"sample2.json"};

void parse_json11_object(const json11::Json &obj,
                         vector<pair<const string, string>> &v) {
  for (const pair<const string, json11::Json> &o : obj.object_items()) {
    if (o.second.is_number()) {
      stringstream s;
      s << o.second.number_value();
      v.push_back(pair<const string, string>(o.first, s.str()));
    } else if (o.second.is_string()) {
      v.push_back(pair<const string, string>(o.first, o.second.string_value()));
    } else if (o.second.is_object()) {
      parse_json11_object(o.second, v);
    }
  }
}

void type(json11::Json obj) {
  if (obj.is_number()) {
    cout << ":: number" << endl;
  } else if (obj.is_bool()) {
    cout << ":: bool" << endl;
  } else if (obj.is_string()) {
    cout << ":: string" << endl;
  } else if (obj.is_array()) {
    cout << ":: array" << endl;
  } else if (obj.is_object()) {
    cout << ":: object" << endl;
  }
}

int main(int argc, char *argv[]) {
  std::ifstream ifs{json_fname};

  string data;
  string chunk;
  while (getline(ifs, data)) {
    chunk += data;
  }

  string err;
  json11::Json json = json11::Json::parse(chunk, err);

  vector<pair<const string, string>> v;
  parse_json11_object(json, v);

#if 0 // for sample.json
  std::string json_str = json.dump();
  cout << json_str << endl;

  string str = json["k1"].string_value();
  cout << str;
  type(json["k1"]);

  int n = json["k2"].number_value();
  cout << n;
  type(json["k2"]);

  type(json["k3"]);
  for (auto &k : json["k3"].array_items()) {
    cout << k.dump();
    type(k);
  }
  //   Json json = Json::array { Json::object { { "k", "v" } } };
  // std::string str = json[0]["k"].string_value();

#endif
  for (pair<const string, string> &s : v) {
    cout << s.first << ":: -> " << s.second << endl;
  }

  ifs.close();

  return 0;
}
