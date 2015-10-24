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
1. Making a random permuation using a varioation on [Knuth shuffle](https://en.wikipedia.org/wiki/Random_permutation)
2. Running a for loop in parallel using fork function
3. Using pipe to send a result from a child to a parent

=========
**Compiling:**

~~~
git clone https://github.com/nevenaf/parfor_in_c.git
cd parfor_in_c
gcc -std=c99 -o random_perm  random_perm.c
./random_perm
~~~

======

**Output:**
![bla](https://github.com/nevenaf/parfor_in_c/screenshot_output.png)
