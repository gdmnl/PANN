
/**
 *  Example code for IO, read binary data vectors and write knng to path.
 *
 */

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "assert.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

/// @brief Save knng in binary format (uint32_t) with name "output.bin"
/// @param knng a (N * 100) shape 2-D vector
/// @param path target save path, the output knng should be named as
/// "output.bin" for evaluation
void SaveKNNG(const std::vector<std::vector<uint32_t>> &knng,
              const std::string &path = "output.bin") {
  std::ofstream ofs(path, std::ios::out | std::ios::binary);
  const int K = 100;
  const uint32_t N = knng.size();
  std::cout << "Saving KNN Graph (" << knng.size() << " X 100) to " << path
            << std::endl;
  assert(knng.front().size() == K);
  for (unsigned i = 0; i < knng.size(); ++i) {
    auto const &knn = knng[i];
    ofs.write(reinterpret_cast<char const *>(&knn[0]), K * sizeof(uint32_t));
  }
  ofs.close();
}

/// @brief Reading binary data vectors. Raw data store as a (N x 100)
/// binary file.
/// @param file_path file path of binary data
/// @param data returned 2D data vectors
void ReadBin(const std::string &file_path,
             std::vector<std::vector<float>> &data) {
  std::cout << "Reading Data: " << file_path << std::endl;
  std::ifstream ifs;
  ifs.open(file_path, std::ios::binary);
  assert(ifs.is_open());
  uint32_t N;  // num of points

  ifs.read((char *)&N, sizeof(uint32_t));
  data.resize(N);
  std::cout << "# of points: " << N << std::endl;

  const int num_dimensions = 100;
  std::vector<float> buff(num_dimensions);
  int counter = 0;
  while (ifs.read((char *)buff.data(), num_dimensions * sizeof(float))) {
    std::vector<float> row(num_dimensions);
    for (int d = 0; d < num_dimensions; d++) {
      row[d] = static_cast<float>(buff[d]);
      // std::cout<<row[d]<<" ";
    }
    // std::cout<<endl;
    data[counter++] = std::move(row);
  }

  ifs.close();
  std::cout << "Finish Reading Data" << endl;
}

std::vector<int> tokenize(char* buff){
    std::vector<int> ret;
    int i = 0;
    while(*(buff + i) != '\0'){
        if(*(buff + i) == ':' || *(buff + i) == ' ')
            ret.push_back(i);
        ++i;
    }
    return ret;
}

std::vector<std::pair<int, float>> parse(std::vector<int> tokens,char* buff){
    std::vector<std::pair<int,float>> ret;
    ret.reserve(tokens.size() / 2);
    for(int i = 0; i + 1 < tokens.size(); i += 2){
        int index;
        float val;
        sscanf(buff + tokens[i] + 1,"%d",&index);
        index -= 1;
        double tmp;
        sscanf(buff + tokens[i + 1] + 1,"%lf",&tmp);
        val = tmp;
        ret.push_back(std::make_pair(index,val));
    }
    return ret;
}

void ReadlibSVM(const std::string &file_path,
             std::vector<std::vector<float>> &data) {
  std::cout << "Reading Data: " << file_path << std::endl;
  std::ofstream out("letter_read.txt");
  uint32_t N = 50000;  // num of points

  data.resize(N);
  std::cout << "# of points: " << N << std::endl;

  auto fp = fopen((char*)file_path.data(),"r");
  std::unique_ptr<char[]> buff(new char[100000]);
  std::vector<std::string> buffers;
  const int num_dimensions = 3072;
  int idx = 0;
  int counter=0;
  while(fgets(buff.get(), 100000, fp)){
      // std::cout<<buff.get()<<std::endl;
      auto tokens = tokenize(buff.get());
      auto values = parse(tokens, buff.get());
      std::vector<float> row(num_dimensions);
      for (auto v: values) {
        row[v.first] = v.second;
      }
      data[counter++] = std::move(row);
  }
  fclose(fp);
  for (auto&row: data) {
    for (auto col: row) {
      out<<col<<" ";
    }
    out<<'\n';
  }
  std::cout << "Finish Reading Data" << endl;
}