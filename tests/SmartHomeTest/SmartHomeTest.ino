#include <AUnit.h>
using namespace aunit;

test(dummy) {
    assertEqual(1, 0);
}

void setup() {
  Serial.begin(115200);
  while (! Serial);

  TestRunner::include("*");
}

void loop() {
    TestRunner::run();
}
