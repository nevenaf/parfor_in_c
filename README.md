# Template for random permutation and parfor in C
=======

**Objective:** Example C code to replace the following Matlab code:
~~~
parfor i = 1:8
  randperm(10)
end
~~~

========

**Methodology:**

- Making a random permutation using a [Knuth shuffle argorithm](https://en.wikipedia.org/wiki/Random_permutation)
- Running a for loop in parallel using fork function
- Using pipe to send a result from a child to a parent


=========
**Compiling:**

~~~
git clone https://github.com/nevenaf/parfor_in_c.git
cd parfor_in_c
gcc -std=c99 -o random_perm  random_perm.c
./random_perm
~~~

======

![**Output:**](https://github.com/nevenaf/parfor_in_c/blob/master/screenshot_output.png)
