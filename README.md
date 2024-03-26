# Task 3

- How do you pass command line arguments to a program when using gdb?
  ```shell
  (c)gdb --args ./lab2 arg1 arg2
  ```
- How do you set a breakpoint which only occurs when a set of conditions is true (e.g. when certain variables are a certain value)?
  ```shell
  break <line or func_name>
  break <line or func_name> if expr
  condition <break_num> expr
  ```
- How do you execute the next line of C code in the program after stopping at a breakpoint?
  ```shell
  n
  next
  s
  step
  ```
- If the next line of code is a function call, you'll execute the whole function call at once if you use your answer to #3. (If not, consider a different command for #3!) How do you tell GDB that you want to debug the code inside the function instead? (If you changed your answer to #3, then that answer is most likely now applicable here.)
  ```shell
  step
  s
  ```
- How do you resume the program after stopping at a breakpoint?
  ```shell
  continue
  c
  ```
- How can you see the value of a variable (or even an expression like 1+2) in gdb?
  ```shell
  print expr
  ```
- How do you configure gdb so it prints the value of a variable after every step ?
  ```shell
  disp expr
  ```
- How do you print a list of all variables and their values in the current function?
  ```shell
  info locals
  ```
- How do you exit out of gdb?
  ```shell
  quit
  ```
