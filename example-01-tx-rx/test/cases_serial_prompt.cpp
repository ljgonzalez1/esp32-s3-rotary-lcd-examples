#include <Arduino.h>
#include <unity.h>
#include "serial_prompt.h"

void test_make_response_header() {
  String s = make_response("Hello");
  TEST_ASSERT_EQUAL_STRING("[esp32s3]: User said \"Hello\"", s.c_str());
}

void test_parser_crlf_single_line() {
  char buf[64]; SerialPrompt P(buf, sizeof(buf));
  const char *seq = "test\r\n";
  bool done=false; int completes=0;
  for (const char* p=seq; *p; ++p) {
    P.feed(*p, done);
    if (done) { completes++; TEST_ASSERT_EQUAL_STRING("test", P.c_str()); P.reset(); }
  }
  TEST_ASSERT_EQUAL(1, completes);
}

void test_parser_lf_only() {
  char buf[64]; SerialPrompt P(buf, sizeof(buf));
  const char *seq = "abc\n";
  bool done=false; int completes=0;
  for (const char* p=seq; *p; ++p) { P.feed(*p, done); if (done) { completes++; TEST_ASSERT_EQUAL_STRING("abc", P.c_str()); } }
  TEST_ASSERT_EQUAL(1, completes);
}

void test_parser_cr_only() {
  char buf[64]; SerialPrompt P(buf, sizeof(buf));
  const char *seq = "xyz\r";
  bool done=false; int completes=0;
  for (const char* p=seq; *p; ++p) { P.feed(*p, done); if (done) { completes++; TEST_ASSERT_EQUAL_STRING("xyz", P.c_str()); } }
  TEST_ASSERT_EQUAL(1, completes);
}

void test_parser_backspace() {
  char buf[64]; SerialPrompt P(buf, sizeof(buf));
  bool done=false;
  P.feed('a', done);
  P.feed('b', done);
  P.feed('\b', done); // borra 'b'
  P.feed('c', done);
  P.feed('\n', done);
  TEST_ASSERT_TRUE(done);
  TEST_ASSERT_EQUAL_STRING("ac", P.c_str());
}
