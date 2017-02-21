
/*
  Date    :   2017-02-21
  Maker   :   SeungHyun Lee (Blog address : blog.naver.com/dkwltmdgus)
  MCU     :   Arduino Series
  Purpose :   Serial Gain Adjust
  Please don't change this section
*/

double PITCH_INNER_PGAIN = 1, PITCH_OUTER_PGAIN = 1, PITCH_IGAIN = 0, PITCH_DGAIN = 0;
double PITCH_IN_P = 0, PITCH_IN_I = 0, PITCH_IN_D = 0;
double ROLL_INNER_PGAIN = 1, ROLL_OUTER_PGAIN = 1, ROLL_IGAIN = 0, ROLL_DGAIN = 0;
double ROLL_IN_P = 0, ROLL_IN_I = 0, ROLL_IN_D = 0;

void setup() {
}

void loop() {
}

void updatePIDgain() {
A:
  if (Serial.available()) {
    int readValue = Serial.read();
    int readArr[4] = {0, };
    if (readValue == 80) {
      Serial.println("PITCH PID SET");
      while (1) {
        if (Serial.available()) {
          readValue = Serial.read();
          if (readValue == 80) {
            Serial.println("P gain");
            while (1) {
              if (Serial. available()) {
                readValue = Serial.read();
                if (readValue == 79) {
                  Serial.println("OUTER P gain");
                  int num = 0;
                  while (1) {
                    if (Serial.available()) {
                      readArr[num] = Serial.read() - 48;
                      num++;
                      if (num == 4) {
                        Serial.print(" PITCH_OUTER_P: ");
                        PITCH_OUTER_PGAIN = (readArr[0] * 10 + readArr[1] * 1 + readArr[2] * 0.1 + readArr[3] * 0.01 );
                        Serial.println(PITCH_OUTER_PGAIN);
                        break;
                      }
                    }
                  }
                  break;

                }
                else if (readValue == 73) {
                  Serial.println("INNER P gain");
                  int num = 0;
                  while (1) {
                    if (Serial.available()) {
                      readArr[num] = Serial.read() - 48;
                      num++;
                      if (num == 4) {
                        Serial.print(" PITCH_INNER_P: ");
                        PITCH_INNER_PGAIN = (readArr[0] * 10 + readArr[1] * 1 + readArr[2] * 0.1 + readArr[3] * 0.01 );
                        Serial.println(PITCH_INNER_PGAIN);
                        break;
                      }
                    }
                  }
                  break;
                }
              }
            }
          }
          else if (readValue == 73) {
            Serial.println("I gain");
            int num = 0;
            while (1) {
              if (Serial.available()) {
                readArr[num] = Serial.read() - 48;
                num++;
                if (num == 4) {
                  Serial.print(" PITCH_I: ");
                  PITCH_IN_I = (readArr[0] + readArr[1] * 0.1 + readArr[2] * 0.01 + readArr[3] * 0.001);
                  Serial.println(PITCH_IN_I, 3);
                  break;
                }
              }
            }
          }
          else if (readValue == 68) {
            Serial.println("D gain");
            int num = 0;
            while (1) {
              if (Serial.available()) {
                readArr[num] = Serial.read() - 48;
                num++;
                if (num == 4) {
                  Serial.print(" PITCH_D: ");
                  PITCH_IN_D = (readArr[0] * 10 + readArr[1] * 1 + readArr[2] * 0.1 + readArr[3] * 0.01);
                  Serial.println(PITCH_IN_D);
                  break;
                }
              }
            }
          }
          else if (readValue == 60) {
            Serial.println("back to main loop");
            goto A;
          }
        }
      }
    }
    if (readValue == 82) {
      Serial.println("ROLL PID SET");
      while (1) {
        if (Serial.available()) {
          readValue = Serial.read();
          if (readValue == 80) {
            Serial.println("P gain");
            while (1) {
              if (Serial. available()) {
                readValue = Serial.read();
                if (readValue == 79) {
                  Serial.println("OUTER P gain");
                  int num = 0;
                  while (1) {
                    if (Serial.available()) {
                      readArr[num] = Serial.read() - 48;
                      num++;
                      if (num == 4) {
                        Serial.print(" ROLL_OUTER_P: ");
                        ROLL_OUTER_PGAIN = (readArr[0] * 10 + readArr[1] * 1 + readArr[2] * 0.1 + readArr[3] * 0.01);
                        Serial.println(ROLL_OUTER_PGAIN);
                        break;
                      }
                    }
                  }
                  break;
                }
                else if (readValue == 73) {
                  Serial.println("INNER P gain");
                  int num = 0;
                  while (1) {
                    if (Serial.available()) {
                      readArr[num] = Serial.read() - 48;
                      num++;
                      if (num == 4) {
                        Serial.print(" ROLL_INNER_P: ");
                        ROLL_INNER_PGAIN = (readArr[0] * 10 + readArr[1] * 1 + readArr[2] * 0.1 + readArr[3] * 0.01 );
                        Serial.println(ROLL_INNER_PGAIN);
                        break;
                      }
                    }
                  }
                  break;
                }
              }
            }
          }
          else if (readValue == 73) {
            Serial.println("I gain");
            int num = 0;
            while (1) {
              if (Serial.available()) {
                readArr[num] = Serial.read() - 48;
                num++;
                if (num == 4) {
                  Serial.print(" ROLL_I: ");
                  ROLL_IGAIN = (readArr[0] + readArr[1] * 0.1 + readArr[2] * 0.01 + readArr[3] * 0.001);
                  Serial.println(ROLL_IGAIN, 3);
                  break;
                }
              }
            }
          }
          else if (readValue == 68) {
            Serial.println("D gain");
            int num = 0;
            while (1) {
              if (Serial.available()) {
                readArr[num] = Serial.read() - 48;
                num++;
                if (num == 4) {
                  Serial.print(" ROLL_D: ");
                  ROLL_DGAIN = (readArr[0] * 10 + readArr[1] * 1 + readArr[2] * 0.1 + readArr[3] * 0.01);
                  Serial.println(ROLL_DGAIN);
                  break;
                }
              }
            }
          }
          else if (readValue == 60) {
            Serial.println("back to main loop");
            goto A;
          }
        }
      }

    }
    if (readValue == 83) {
      Serial.print("PITCH_OUTER_P: "); Serial.println(PITCH_OUTER_PGAIN);
      Serial.print("PITCH_INNER_P: "); Serial.println(PITCH_INNER_PGAIN);
      Serial.print("PITCH_I: "); Serial.println(PITCH_IN_I, 3);
      Serial.print("PITCH_D: "); Serial.println(PITCH_IN_D);
      Serial.print("ROLL_OUTER_P: "); Serial.println(ROLL_OUTER_PGAIN);
      Serial.print("ROLL_INNER_P: "); Serial.println(ROLL_INNER_PGAIN);
      Serial.print("ROLL_I: "); Serial.println(ROLL_IN_I, 3);
      Serial.print("ROLL_D: "); Serial.println(ROLL_IN_D, 3);
    }
  }
}

