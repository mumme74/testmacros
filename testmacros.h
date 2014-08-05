#ifndef TESTMACROS_H
#define TESTMACROS_H

// auto detect types to compare with
#define test(expr, expect) { typedef decltype(expect) _type; testWT(expr, expect, _type) }
// compare with Strings
#define testS(expr, expect) testWT(expr, expect, String)
// compare using supplied type
#define testWT(expr, expect, type) { type e =(expr); type ex = (expect); ++_testsCnt; if (!((e) == (ex))) { \
		 Serial.print("**Error: (" #expr " == " #expect ") -> (");Serial.print((e)); \
		 Serial.print(" == ");Serial.print(ex); Serial.print(") at line ");Serial.println( __LINE__  );Serial.flush(); \
		 _errCnt++;	\
	} else { \
		 Serial.print("passed " #expr " == " #expect " at line: "); Serial.println( __LINE__ );Serial.flush();\
	}}
// begin and end test
#define testBegin() Serial.println("starting tests..."); unsigned int _errCnt = 0, _testsCnt = 0;
#define testEnd() Serial.print("finished running ");Serial.print(_testsCnt);Serial.print(" tests, there was "); \
									Serial.print(_errCnt);Serial.println(" errors");
									
// insert i loop() listens to input in Serial.in and runs tests when it has any input
#define testLoop() 	if (Serial.available() > 0) { \
    Serial.read(); runTests(); \
  } 

#endif // TESTMACROS_H
