#include <iostream>      
#include <vector>        
#include <string>        
#include <algorithm>     
#include <climits>       

using namespace std;     

int findOverlap(const string& a, const string& b) {

    int maxLen = min(a.length(), b.length()) - 1;

    for (int l = maxLen; l > 0; l--) {
        
        if (a.substr(a.size() - l) == b.substr(0, l)) {
            return l;  
        }
    }
    return 0;  
}

void findBestOrder(const vector<string>& words,  
    vector<bool>& used,           
    vector<int>& currentOrder,    
    int currentLength,            
    int& minLength,               
    vector<int>& bestOrder) {     
  
    if (currentOrder.size() == words.size()) {
        
        if (currentLength < minLength) {
            minLength = currentLength;  
            bestOrder = currentOrder;   
        }
        return;
    }

    for (int i = 0; i < words.size(); i++) {
        
        if (!used[i]) {
            int overlap = 0;  

            if (!currentOrder.empty()) {
                overlap = findOverlap(words[currentOrder.back()], words[i]);
            }

            int newLength = currentLength + words[i].length() - overlap;

            if (newLength < minLength) {
                used[i] = true;              
                currentOrder.push_back(i);   

                findBestOrder(words, used, currentOrder, newLength, minLength, bestOrder);

                currentOrder.pop_back();
                used[i] = false;
            }
        }
    }
}

string buildCrossword(const vector<string>& words) {
    if (words.empty()) return "";

    vector<bool> used(words.size(), false);  
    vector<int> currentOrder, bestOrder;     
    int minLength = INT_MAX;                 

    
    findBestOrder(words, used, currentOrder, 0, minLength, bestOrder);

    
    if (bestOrder.empty()) return "";

    string result = words[bestOrder[0]];  

    for (int i = 1; i < bestOrder.size(); i++) {
        int overlap = findOverlap(words[bestOrder[i - 1]], words[bestOrder[i]]);
        result += words[bestOrder[i]].substr(overlap);
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<string> words = { "матан", "прога", "амбассадор", "новосиб" };

    string crossword = buildCrossword(words);

    cout << "Линейный кроссворд: " << crossword << endl;
    cout << "Длина: " << crossword.length() << " букв" << endl;

    return 0;  
}
