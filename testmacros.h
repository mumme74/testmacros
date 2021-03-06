#ifndef TESTMACROS_H
#define TESTMACROS_H

// shuld be placed in top of file outside of a function
#define initTests() \
	unsigned int _errCnt = 0, _testsCnt = 0; \
	bool _delayed = false; \
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
	void testDelay(unsigned long ms) { \
		_delayed = true; \
		unsigned long endAt = millis() + ms; \
		do { \
			yield(); \
			loop(); \
		} while (endAt >= millis()); \
		_delayed = false; \
	}
	

// auto detect types to compare with
#define test(expr, expect) testLine(expr, expect, __LINE__)
#define testLine(expr, expect, line) { typedef decltype(expect) _type; testWT<_type>(#expr, #expect, expr, expect, line); }
// compare with Strings
#define testS(expr, expect) testSLine(expr, expect,  __LINE__)
#define testSLine(expr, expect, line) testWT<String>(#expr, #expect, expr, expect, line)
// compare using type as Type
#define testTypeHint(expr, expect, type) testTypeHintLine(expr, expect, type, __LINE__)
#define testTypeHintLine(expr, expect, type, line) testWT<type>(#expr, #expect, expr, expect, line)
// begin and end test
#define testBegin() Serial.println("starting tests..."); _errCnt = 0; _testsCnt = 0;
#define testEnd() Serial.print("finished running ");Serial.print(_testsCnt);Serial.print(" tests, there was "); \
									Serial.print(_errCnt);Serial.println(" errors");
									
// insert i loop() listens to input in Serial.in and runs tests when it has any input
#define testLoop() 	if (Serial.available() > 0 && !_delayed) { \
    Serial.read(); \
    runTests(); \
  } 

#endif // TESTMACROS_H
