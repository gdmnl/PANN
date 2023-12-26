#!/bin/bash

if [ "$#" -lt 4 ]; then
  echo "Usage: $0 <query_data> <built_graph_row> <built_graph_dimension> <l2/ip/cos> [display top k]" >&2
  echo "For example: $0 letter.scale.t 15000 26 cos" >&2
  echo "Use display top 5: $0 letter.scale.t 15000 26 cos 5" >&2
  exit 1
fi

search=101 #only used in CPU mode
display=101

if [ "$#" -ge 5 ]; then
  display=$5
fi

$(dirname $0)/song test 0 $1 ${search} $2 $3 ${display} $4

