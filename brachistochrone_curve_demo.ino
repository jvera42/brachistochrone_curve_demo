#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5,4,3,2,1,0);

const int raceControl = 12;
const int raceTracks[] = {11, 10, 9};
const int numRaceTracks = 3;

bool raceStarted = false;
int race_counter = 0;
bool allTracksPressed = false;
unsigned long startTime;
unsigned long trackTimes[3] = {0};

// Names for each track
const char* trackNames[] = {"Track 1", "Track 2", "Track 3"};

void setup() 
{
  pinMode(raceControl, INPUT);
  for (int i = 0; i < numRaceTracks; ++i)
  {
    pinMode(raceTracks[i], INPUT);
  }

  lcd.begin(16, 2);

  lcd.print("Race Timer");
  lcd.setCursor(0, 1);
  lcd.print("Press to start");
}

void loop() {
  if (digitalRead(raceControl) == HIGH) 
  {
    if (!raceStarted) {
      // Start the race
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Race Started");
      startTime = millis();
      raceStarted = true;
      delay(500); // Debounce delay
    } 
    else if (raceStarted)
    {
      // Reset the race
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press to start");
      raceStarted = false;
      allTracksPressed = false;
      delay(500);  // Debounce delay
    }
  }

  // Race Ongoing
  if (raceStarted)
  {
    while (race_counter < numRaceTracks) 
    {
      if (digitalRead(raceTracks[0]) == HIGH && trackTimes[0] == 0) 
      {
        // Record the time for the pressed track
        trackTimes[0] = millis() - startTime;
        lcd.setCursor(0, 1);
        lcd.print(trackNames[0]);
        lcd.print(": ");
        lcd.print(trackTimes[0] / 1000.0, 3);  // Convert milliseconds to seconds
        lcd.print(" s");

        race_counter = ++race_counter;
      }
      else if (digitalRead(raceTracks[1]) == HIGH && trackTimes[1] == 0) 
      {
        // Record the time for the pressed track
        trackTimes[1] = millis() - startTime;
        lcd.setCursor(0, 1);
        lcd.print(trackNames[1]);
        lcd.print(": ");
        lcd.print(trackTimes[1] / 1000.0, 3);  // Convert milliseconds to seconds
        lcd.print(" s");

        race_counter = ++race_counter;
      }
      else if (digitalRead(raceTracks[2]) == HIGH && trackTimes[2] == 0) 
      {
        // Record the time for the pressed track
        trackTimes[2] = millis() - startTime;
        lcd.setCursor(0, 1);
        lcd.print(trackNames[2]);
        lcd.print(": ");
        lcd.print(trackTimes[2] / 1000.0, 3);  // Convert milliseconds to seconds
        lcd.print(" s");

        race_counter = ++race_counter;
      }
      else if (digitalRead(raceControl) == HIGH) 
      {
        {
          // Reset the race
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Press to start");
          raceStarted = false;
          allTracksPressed = false;
          for (int i = 0; i < numRaceTracks; ++i)
          {
            trackTimes[i] = 0;
          }
          race_counter = 0;
          delay(500);  // Debounce delay
          break;
        }
      }
    }
    delay(1000); // Race finish delay
  }

  // Check if all tracks are pressed
  if (raceStarted && !allTracksPressed)
  {
    allTracksPressed = true;
  }

  // All tracks pressed
  if (raceStarted && allTracksPressed)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Race Finished");
    delay(2000);

    // Find the fastest time
    int fastestTrack = 0;
    for (int i = 1; i < numRaceTracks; ++i) 
    {
      if (trackTimes[i] < trackTimes[fastestTrack]) 
      {
        fastestTrack = i;
      }
    }

    lcd.setCursor(0, 0);
    lcd.print("Fastest Track:");
    lcd.setCursor(0, 1);
    lcd.print(trackNames[fastestTrack]);
    lcd.print(": ");
    lcd.print(trackTimes[fastestTrack] / 1000.0, 3);  // Convert milliseconds to seconds
    lcd.print(" s");
  
    // Loop indefinitely after the race finishes
    while (true) 
    {
      if (digitalRead(raceControl) == HIGH) 
      {
        // Reset the race
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Press to start");
        raceStarted = false;
        allTracksPressed = false;
        for (int i = 0; i < numRaceTracks; ++i)
        {
          trackTimes[i] = 0;
        }
        race_counter = 0;
        delay(500);  // Debounce delay
        break;
      }
    }
  }
}