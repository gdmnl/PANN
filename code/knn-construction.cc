
/**
 *  Naive baseline for construction a KNN Graph.
 *  Randomly select 100 neighbors from a 10k subset.
 */
// faiss 算出答案

#include <sys/time.h>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <string>
#include <vector>

#include "assert.h"
#include "io.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

#define _INT_MAX 2147483640

float EuclideanDistance(const vector<float> &lhs, const vector<float> &rhs, int crt_dis, int crt_size) {
  float ans = 0.0;
  unsigned lensDim = 3072;
  for (unsigned i = 0; i < lensDim; ++i) {
    ans += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    // if (crt_size>=5&&ans>crt_dis) return -1;
  }
  return ans;
}

vector<int> CalculateOneKnn(const vector<vector<float>> &data,
                                 const int id) {
  std::priority_queue<std::pair<float, int>> top_candidates;
  float lower_bound = _INT_MAX;
  for (int i = 0; i < data.size(); i++) {
    int sample_id = i;
    if (id == sample_id) continue;  // skip itself.
    float dist = EuclideanDistance(data[id], data[sample_id], lower_bound, top_candidates.size());
    // if (dist==-1) continue;
    // only keep the top 100
    if (top_candidates.size() < 100 || dist < lower_bound) {
      top_candidates.push(std::make_pair(dist, i));
      if (top_candidates.size() > 100) {
        top_candidates.pop();
      }

      lower_bound = top_candidates.top().first;
    }
  }

  vector<int> knn;
  while (!top_candidates.empty()) {
    knn.emplace_back(top_candidates.top().second);
    top_candidates.pop();
  }
  std::reverse(knn.begin(), knn.end());
  return knn;
}

void ConstructKnng(const vector<vector<float>> &data,
                   vector<vector<int>> &knng, int size) {
  knng.resize(size);
#pragma omp parallel for
  for (int n = 0; n < size; n++) {
    knng[n] = CalculateOneKnn(data, n);
  }
  // for (int i = 0; i < 5; i++) {
  //   for (int j = 0; j < 5; j++) {
  //     cout<<knng[i][j]<<endl;
  //   }
  // }
  cout << "Construction Done!" << endl;
}

int main(int argc, char **argv) {
  // string source_path = "dummy-data.bin";
  string source_path = "letter.scale.txt";

  // Also accept other path for source data
  if (argc > 1) {
    source_path = string(argv[1]);
  }

  // Read data points
  vector<vector<float>> nodes;

  // ReadBin(source_path, nodes);
  ReadlibSVM(source_path, nodes);

  // Sample 10,000 points for greedy search
  // std::default_random_engine rd;
  // std::mt19937 gen(rd());  // Mersenne twister MT19937
  // vector<int> sample_indexes(nodes.size());
  // iota(sample_indexes.begin(), sample_indexes.end(), 0);
  // shuffle(sample_indexes.begin(), sample_indexes.end(), gen);
  // sample_indexes.resize(15000);
  // Knng constuction
  vector<vector<int>> knng;
  int s = std::atoi(argv[2]);
  ConstructKnng(nodes, knng, s);
  std::ofstream out("match_res_cifar.txt");
  for (int i = 0; i < knng.size(); i++) {
    for (int j = 0; j < nodes[0].size(); j++) {
      out<< nodes[i][j] <<"_";
    }
    out<<'\n';
    for (int j = 0; j < knng[0].size(); j++) {
      out<< knng[i][j] <<" ";
    }
    out<<'\n';
  }
  // Save to ouput.bin
  // SaveKNNG(knng);

  return 0;
}
