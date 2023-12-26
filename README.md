# PANN: Parallel Approximate Nearest Neighbour Search Over Graphs

### Prerequisites
We have tested PANN on the following versions of prerequisites.
```
g++ 5.4.0, 9.3.0
CUDA 10.0, 10.1
```

Our referenced paper homepage: [SONG](https://github.com/sunbelbd/song).

### Dataset
- [https://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/multiclass.html](https://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/multiclass.html)
- [http://corpus-texmex.irisa.fr/](http://corpus-texmex.irisa.fr/)

### Several Settings
We have two settings as s1 and s2. You can change the code in ./main.cu to run under different settings.

### Run
You can run ./run.sh to generate the result.
- ./generate_template.sh is to generate a copy of all the files.
- ./fill_parameters.sh q dimension l2
  - For the parameter q, it refers to the length of topk when building the graph. 
  - For the parameter dimension, it means the dimension of the dataset.
- ./build_graph.sh cifar10.txt num dimension l2
  - For the parameter num, it refers to the number of the points of the dataset.
  - For the parameter dimension, it means the dimension of the dataset.
- ./test_query.sh cifar10.txt num l2 s
  - For the parameter num, it refers to the number of the points of the dataset.
  - For the parameter s, it refers to the length of the candidate queue when querying.

### Evaluate
You can run ./evaluate.sh to evalute the recall.

