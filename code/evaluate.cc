#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int main(int argc,char** argv){
    string file1 = string(argv[1]);
    string file2 = string(argv[2]);
    ifstream rf1(file1);
    ifstream rf2(file2);
    unordered_map<string, vector<int>> a;
    unordered_map<string, vector<int>> b;
    std::istringstream iss;
    string line_a, line_b;
    int c = 0;
    while(getline(rf1,line_a)) {
        c = 0;
        vector<int> nums;
        string num_a;
        getline(rf1, num_a);
        int num;
        iss.clear();
        iss.str(num_a);
        while(iss>>num) 
        {
            c++;
            if (c>60) break; 
            nums.push_back(num);
        }
        a[line_a] = nums;
    }
    while(getline(rf2,line_b)) {
        c = 0;
        vector<int> nums;
        string num_b;
        getline(rf2, num_b);
        int num;
        iss.clear();
		iss.str(num_b);
        int cnt = 0;
        while(iss>>num) 
        {   
            cnt++;
            if (cnt>60) break;
            nums.push_back(num);
            c++;
        }
        b[line_b] = nums;
    }
    double res = 0;
    int base = 0;
    // double min_res = 1;
    // double max_res = 0;
    for (auto& v: b) {
        double cnt = 0;
        unordered_set<int> tmp;
        for (int j = 0; j < v.second.size(); j++) {
            tmp.insert(v.second[j]);
        }
        for (int n: a[v.first]) {
            if (tmp.find(n)!=tmp.end()) cnt++;
        }
        // min_res = min(min_res, cnt/100);
        // max_res = max(max_res, cnt/100);
        res+=cnt/60;
    }
    cout<<res/50000<<endl;
    // cout<<res/15000<<endl;

}
