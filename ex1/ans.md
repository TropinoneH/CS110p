# Senario 1

Associativity: the mapping policy is directly mapping.

Cache Size=Block Size(8) \* Number of Blocks(4)=32

1. 0
2. still 0. because it only depends on inner loop
3. make step size small. e.g. step size $\rightarrow$ 1, then the miss rate will be 0.5

# Senario 2

1. hit rate: 0.75
2. hit rate will increase, until 1
3. use cache block, reuse some block in the outer loop



# Senario 3

1. hit rate is 0.1875, 0.3125, 0.0625, 0.125, 0.25.
2. use direct mapping. then the hit rate is always 0.5
