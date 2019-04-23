

void dinoGame() {
  unsigned long currentMillis = millis();
  unsigned long currentMillisOb = millis();
 
  
  if (currentMillisOb - previousMillis >= speedOfScroller) {
    previousMillis = currentMillisOb;
    if (random(chance_of_ob) == 0) {
      runnerArea[15] = 1;
    } else if (random(chance_of_ob) == 1) {
      runnerArea[15] = 2;
    } else {
      runnerArea[15] = 32;
    }
    for (int i = 0; i <= 15; i++) {
      runnerArea[i] = runnerArea[i + 1];
    }
    if (freeze_score == 0) {
      score++;
    }
  }
  drawBarrier();

  if (read_LCD_buttons() == btnSELECT) {
    // runnerArea[1] = 32;
    if (runnerArea[1] != 32 && (runnerArea[1] != 1 || runnerArea[1] != 2)) {
      runnerArea[1] = 32;
    }
    jump = 0;
    freeze_score = 1;
    jumpTime = millis();
  }
  if (millis() - jumpTime >= jumpLength) {
    if (checkSafe) {
      runnerArea[1] = 0;
      jump = 32;
      freeze_score = 0;
    } else {
      showCrashScreen();
    }
  }
  updateLcd();
  printScore();

  if (millis() - previousMillisLED >= 500) {
    previousMillisLED = currentMillis;
    digitalWrite(13, !digitalRead(13));
  }
}
