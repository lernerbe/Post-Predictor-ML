#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <set>
#include <map>
#include <regex>
#include "csvstream.hpp"

using namespace std;

set<string> unique_words(const string &str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
}

class Classifier {
  private:
    int numPosts = 0;
    set<string> unique_word_set;
    set<string> uniqueLabelsInString;
    map<string, int> word_occur;
    map<string, int> label_occur;
    map<string, map<string, int>> label_word_counts;
    map<string, map<string, string>> string_storage;
    
  public:
    Classifier () {}
    
    map<string, map<string, string>> storeString(csvstream& file) {

    // Read all data from file into vector of maps
    vector<map<string, string>> data;
    map<string, string> row;
    while (file >> row) {
        data.push_back(row);
    }
   
   for (auto& row : data) {
        int n;
        stringstream ss(row["n"]);
        ss >> n;
        n = data.size() - n + 1;
        row["n"] = to_string(n);
    } 
    
    // Create map of maps using the reversed vector
    for (const auto& row : data) {
        string_storage[row.at("n")][row.at("tag")] = row.at("content");
    }

    return string_storage;
}

    void clearMap() {
      string_storage.clear();
    }

    int wordCounter(){
      return word_occur.size();
    }

    int countPosts(map<string, map<string, string>> string_storage) {
      string highest_n= "0";
      for (const auto& pair : string_storage) {
        const string& n_value = pair.first;
        if (n_value > highest_n) {
          highest_n = n_value;
        }
      }
      numPosts = stoi(highest_n);
      return stoi(highest_n);
    }

    void wordOccurances(map<string, map<string, string>> string_storage) {
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          istringstream stream(innerPair.second);
          string word;
          set<string> uniqueWordsInString;

          while (stream >> word) {
            uniqueWordsInString.insert(word);
          }

          for (const auto& uniqueWord : uniqueWordsInString) {
            if (uniqueWordsInString.count(uniqueWord)) {
                ++word_occur[uniqueWord];
            }
          }
        }
      }
    }

    void labelOccurances(map<string, map<string, string>> string_storage) {
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          string word = innerPair.first;
          uniqueLabelsInString.insert(word);
        }
      }

      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
            const string& innerFirst = innerPair.first;
            for (const auto& label : uniqueLabelsInString) {
                if (innerFirst == label) {
                    ++label_occur[label];
                }
            }
        }
    }
    }

    void wordAndLabel(map<string, map<string, string>> string_storage) {
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          string label = innerPair.first;
          string content = innerPair.second;
          for (const auto& wordPair : word_occur) {
            const string& word = wordPair.first;
            regex pattern("\\b" + word + "\\b");
            if (regex_search(content, pattern)) {
              label_word_counts[label][word]++;
            }
          }
        }
      }
  }

    double logPC(string label) {
      return log(label_occur[label] / static_cast<double>(numPosts));
    }

    double logPWC(string label, string word) {
      if (label_word_counts.count(label) && 
          label_word_counts[label].count(word)) {
        return log(label_word_counts[label][word] 
                / static_cast<double>(label_occur[label]));
      }
      else if (word_occur.count(word)) {
        return log(word_occur[word] / static_cast<double>(numPosts));
      }
      else {
        return log(1 / static_cast<double>(numPosts));
      }
    }

    pair<string, double> predict(string content) {
      map<string, double> label_prob;
      for (const auto& label : uniqueLabelsInString) {
        double prob = 0;
        for (const auto& word : unique_words(content)) {
          prob += logPWC(label, word);
        }
        prob += logPC(label);
        label_prob[label] = prob;
      }
      string highest_label = "";
      double highest_prob = -10000000;
      for (const auto& pair : label_prob) {
        if (pair.second > highest_prob) {
          highest_label = pair.first;
          highest_prob = pair.second;
        }
      }
      return pair<string, double>(highest_label, highest_prob);
    }

    // for each, prints out labal and content
    void printTrainingData(map<string, map<string, string>> string_storage) {
      cout << "training data:" << endl;
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          cout << "  label = " << innerPair.first;
          cout << ", content = " << innerPair.second << endl;
          }
      }
    }

    // print out each label, number of examples it was trained on,
    // and the value for log-prior
    // print all of these using a for loop to iterate through the labels
    void printClasses() {
      cout << "classes:" << endl;
      for (const auto& pair : label_occur) {
        const std::string& label = pair.first;
        cout << "  " << label;
        cout << ", " << pair.second << " examples";
        cout << ", log-prior = " << logPC(label) << endl;
      }
}

    void printClassifierParamaters() {
      cout << "classifier parameters:" << endl;
      for (const auto& labelPair : label_occur) {
        const string& label = labelPair.first;
        for (const auto& wordPair : word_occur) {
          const string& word = wordPair.first;
          if (label_word_counts[label][word] > 0) {
            cout << "  " << label << ":" << word << ", count = " 
            << label_word_counts[label][word];
            cout << ", log-likelihood = " << logPWC(label, word) << endl;
          }
        }
      }
      cout << endl;
    }

    void printTestData(map<string, map<string, string>> test_string_storage) {
      cout << "test data:" << endl;
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          cout << "  correct = " << innerPair.first;
          cout << ", predicted = " << predict(innerPair.second).first;
          cout << ", log-probability score = " 
               << predict(innerPair.second).second << endl;
          cout << "  content = " << innerPair.second << endl << endl;
          }
      }
    }
    
    // Print the number of correct predictions and total number of test posts.
    // ex:
    // performance: 2 / 3 posts predicted correctly
    void printPerformance(map<string, map<string, string>> 
                          test_string_storage) {
      int correct = 0;
      int total = 0;
      for (const auto& outerPair : string_storage) {
        for (const auto& innerPair : outerPair.second) {
          if (innerPair.first == predict(innerPair.second).first) {
            correct++;
          }
          total++;
          }
      }
      cout << "performance: " << correct << " / " << total 
           << " posts predicted correctly" << endl;
    }
    
};

int main(int argc, char* argv[]) {
  set<string> unique_word_set;
  int total_posts = 0;
  int total_unique_words = 0;
  map<string, map<string, string>> string_storage_main;
  map<string, map<string, string>> string_storage_test;
  cout.precision(3);
  if (((argc != 3) && (argc != 4)) || ((argc == 4) && 
      (strcmp(argv[3], "--debug") != 0))) {
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return 1;
  };
  bool isDebug = false;
  if ((argc == 4) && !(strcmp(argv[3], "--debug"))) {
    isDebug = true;
  }
  csvstream trainFile(argv[1]);
  csvstream testFile(argv[2]);
  Classifier train;

  string_storage_main = train.storeString(trainFile);
  total_posts = train.countPosts(string_storage_main);
  train.wordOccurances(string_storage_main);
  train.labelOccurances(string_storage_main);
  train.wordAndLabel(string_storage_main);
  total_unique_words = train.wordCounter();

  // take the words from the post in the test file
  // iterate through the labels from the training set
  // for each label calculate a log score by 
  // adding the log of all the words together
  // store the first one as the greatest value and
  // subsequently compare all following against the first
  if (isDebug) {
    train.printTrainingData(string_storage_main); // if debug
  }
  train.clearMap();
  cout << "trained on " << total_posts << " examples" << endl << endl;

  if (isDebug) {
    cout << "vocabulary size = " << total_unique_words << endl << endl;
    train.printClasses(); // if debug
    train.printClassifierParamaters(); // if debug
  }
  string_storage_test = train.storeString(testFile);
  train.printTestData(string_storage_test);
  train.printPerformance(string_storage_test);
}