testmacros
==========

Some macros to test Arduino code, prints result on Serial 

Usage

These macrofunctions must be placed within a void runTests() function

```
testBegin();  
```
Starts the test sets upp the error counter etc




```
test(expression, expression_shouldbe);
```
Does a test _expression_ should evaluate to <i>expression_should_be</i>
example:
```
test(str.length(), 1);
```
If it fails it prints expression and which line that failed




````
testS(expression, "should be this");
````
Is just a wrapper to check a const char array againt a String



````
testWT(expression, obj, MyComplexClass);
````
Test against a defined type, you name the type in the 3d argument



````
testEnd();
````
Ends the test and prints the the testcount and the number of failed tests



This macro function should be placed in void loop()

````
testLoop();
````
Should be placed within loop(), it waits to run the tests until it has recieved something on Serial aka you have send something to show that you are ready to read the test results





Complete example:
````c++
#include <testmacros.h>

void runTests() {
  testBegin();
  int t = 0;
  test(t++, 0);
  test(t, 0); // this will fail and print the line were it ocured
  
  String s = "hej";
  testS(s, "God");
  s += " morgon!";
  testS(s, "God morgon");
  
  // and so on...
  
  testEnd();
}


void setup(){
  Serial.begin(9600);
}

void loop(){
  testLoop(); // waits for you to send something, anything, on serial in
}

````







