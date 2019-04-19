#ifndef TESTMACROS_H
#define TESTMACROS_H

// shuld be placed in top of file outside of a function
#define initTests() \
	unsigned int _errCnt = 0, _testsCnt = 0; \
	template <typename T> \
	void testWT(const char *exprStr, const char *expectStr, T expr, T expect, int line) { \
		T e =(expr); T ex = (expect); ++_testsCnt;  \
		if (!((e) == (ex))) { \
			Serial.print("**Error: (");Serial.print(exprStr);Serial.print(" == "); Serial.print(expectStr);Serial.print(") -> (");Serial.print((expr)); \
			Serial.print(" == ");Serial.print(expect); Serial.print(") at line ");Serial.println(line);Serial.flush(); \
			_errCnt++;	\
		} else { \
			Serial.print("passed ");Serial.print(exprStr);Serial.print(" == ");Serial.print(expectStr);Serial.print(" at line: "); Serial.println(line);Serial.flush();\
		} \
	} \

// auto detect types to compare with
#define test(expr, expect) { typedef decltype(expect) _type; testWT<_type>(#expr, #expect, expr, expect, __LINE__); }
// compare with Strings
#define testS(expr, expect) testWT<String>(#expr, #expect, expr, expect, __LINE__)
// begin and end test
#define testBegin() Serial.println("starting tests..."); _errCnt = 0; _testsCnt = 0;
#define testEnd() Serial.print("finished running ");Serial.print(_testsCnt);Serial.print(" tests, there was "); \
									Serial.print(_errCnt);Serial.println(" errors");
									
// insert i loop() listens to input in Serial.in and runs tests when it has any input
#define testLoop() 	if (Serial.available() > 0) { \
    Serial.read(); runTests(); \
  } 

#endif // TESTMACROS_H
