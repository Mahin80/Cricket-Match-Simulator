# Cricket Match Simulator

A simple C++ console application to simulate a limited-overs cricket match between two teams. The simulator reads team and configuration data from files, simulates the match ball-by-ball, and displays a detailed scorecard, including batting and bowling highlights.

---

## Features

- **Team Management:** Reads team lineups and initial stats from `team1.txt` and `team2.txt`.
- **Configurable Overs:** Reads the number of overs from `Configuration.txt`.
- **Ball-by-Ball Simulation:** Randomized scoring and wicket events for each ball.
- **Scorecard:** Displays live batting and bowling boards, with asterisks highlighting current batsmen and bowler.
- **Match Summary:** Declares the winner and highlights top performers.
- **Save Match Summary:** Option to save the match summary to a file.

---

## File Structure

```
Cricket-Match-Simulator/
│
├── cricket.cpp           # Main source code
├── team1.txt             # Team 1 players and stats
├── team2.txt             # Team 2 players and stats
├── Configuration.txt     # Number of overs
├── Savefile.txt          # (Generated) Match summary
└── README.md             # Project documentation
```

---

## How to Use

1. **Prepare Teams:**
   - Edit `team1.txt` and `team2.txt` with your player names and initial stats.
   - Example format for each line:
     ```
     Player Name  0 0 0 0 0
     ```
     (Name followed by runs, balls faced, balls bowled, runs given, wickets taken)

2. **Set Overs:**
   - Edit `Configuration.txt` and enter the number of overs (e.g., `5`).

3. **Build and Run:**
   - Open the project in Visual Studio or any C++ IDE.
   - Compile and run `cricket.cpp`.

4. **Follow Prompts:**
   - The simulator will toss, play both innings, and display live scorecards.
   - After the match, choose to display and save the summary.

---

## Example Output

```
***************** Batting *****************
Batting               Runs    Balls   4s      6s      SR
Baber Azam *          4       1       1       0       400
Mohammad Nawaz *      0       0       0       0       0
...

***************** Bowling *****************
Bowling               O       R       W       Eco.
Naseem Shah           2.0     12      1       6.00
Mohammad Wasim Jr *   1.0     8       0       8.00
...
```

---

## Notes

- The simulator uses randomization for runs and wickets, so results will vary each run.
- The asterisk `*` marks the current batsmen and bowler.
- Only the last 5 players in each team are considered bowlers in the bowling board.

---

## License

This project is for educational purposes and is open for modification and improvement.

---
