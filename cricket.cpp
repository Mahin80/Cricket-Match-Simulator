#include<iostream>
#include<fstream>
#include<time.h>
#include<Windows.h>
#include<cstring>
#include<conio.h>
using namespace std;

const int max_players = 7;
int config()
{
	char ch;
	ifstream fin;
	int overs = 0;
	// Reading overs from file
	fin.open("Configuration.txt");
	fin >> ch;
	while (!fin.eof()) {
		if (ch >= 48 && ch <= 57)
		{
			overs = overs * 10 + ch - 48;
		}
		fin >> ch;

	}
	cout << "Total Overs from file: " << overs << endl;
	cout << "\n\n ********************  Match Begins **********************************" << endl;
	return overs;
}
void summary(int ts1, int ts2, int runs1[], int runs2[], int wicket1[], int wicket2[], char team1[][25], char team2[][25])
{   //creating file to save data
	ofstream savefile;
	savefile.open("Savefile.txt");
	//displaying the summary of match
	cout << "\n-----------------------------------------------------\n";
	cout << "        \tMATCH SUMMARY        \n";
	cout << "-----------------------------------------------------\n\n";
	cout << "Pakistan Total Score: " << ts1 << endl;
	cout << "Australia Total Score: " << ts2 << endl;
	if (ts1 > ts2)
	{
		cout << "\n\n *********************** Team 1 Wins!! ***************************** \n";
		cout << "\n\t\t\t***Pakistan won***\n" << endl;
		savefile << "\n\n *********************** Team 1 Wins!! ***************************** \n";
		savefile << "\n\t\t\t***Pakistan won***\n" << endl;
	}
	else if (ts2 > ts1)
	{
		cout << "\n\n *********************** Team 2 Wins!! *****************************\n";
		cout << "\n\t\t\t***Australia won***\n" << endl;
		savefile << "\n\n *********************** Team 2 Wins!! *****************************\n";
		savefile << "\n\t\t\t***Australia won***\n" << endl;
	}
	else
	{
		cout << "Match ended in a tie" << endl;
		savefile << "Match ended in a tie" << endl;
	}
	int  max1 = 0, max2 = 0, max = 0, wic_max1 = 0, wic_max2 = 0, wicmax = 0;  //finding highest wicket & runs scorer
	for (int i = 0; i < max_players; i++)
	{
		if (runs1[i] >= max1)
		{
			max1 = runs1[i];
		}
		if (runs2[i] >= max2)
		{
			max2 = runs2[i];
		}
		if (max2 > max1)  //team2 player scored max runs
		{
			max = max2;
		}
		else if (max1 > max2)  //team1 player scored max runs
		{
			max = max1;
		}
		if (wicket1[i] > wic_max1)
		{
			wic_max1 = wicket1[i];
		}
		if (wicket2[i] > wic_max2)
		{
			wic_max2 = wicket2[i];
		}
		if (wic_max2 > wic_max1)     //team 1 player scored max wickets
		{
			wicmax = wic_max2;
		}
		else if (wic_max1 > wic_max2)  //team 2 player scored max wickets
		{
			wicmax = wic_max1;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (runs1[i] == max)
		{
			savefile << "Batsmen of the match: " << team1[i] << ", scored " << max << " runs" << endl; //reading the data to save
			cout << "Batsmen of the match: " << team1[i] << ", scored " << max << " runs" << endl;
			break;
		}
		else if (runs2[i] == max)
		{
			savefile << "Batsmen of the match: " << team2[i] << ", scored " << max << " runs" << endl; //reading the data to save
			cout << "Batsmen of the match: " << team2[i] << ", scored " << max << " runs" << endl;

			break;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (wicket1[i] == wicmax)
		{
			savefile << "Bowler of the match " << team1[i] << ", scored " << wicmax << " wickets" << endl; //reading the data to save
			cout << "Bowler of the match " << team1[i] << ", scored " << wicmax << " wickets" << endl;
			break;
		}
		else if (wicket2[i] == wicmax)
		{
			savefile << "Bowler of the match " << team2[i] << ", scored " << wicmax << " wickets" << endl; //reading the data to save
			cout << "Bowler of the match " << team2[i] << ", scored " << wicmax << " wickets" << endl;
			break;
		}
	}
	//closing the file
	savefile.close();
}
bool scorecard(int N, int wData[max_players][5], int strike, int ball, int onbat[2], int bowler, int overs, int wickets, int fours[max_players], int sixes[max_players], char teamBat[max_players][25], int runBat[max_players], int ballfaced[max_players], int ballbowled[max_players], char teamBowl[max_players][25], int runBowl[max_players], int wicketsBowl[max_players], int target);
void BatsmanGotOut(string batsmanName, int batsmanScore, int ballsfaced, int fours, int sixes);
void TotalScore(int runBat[max_players], int overs, int wickets, int ball);
void FallOfWickets(int wickets, int wData[max_players][5], char teamBowl[max_players][25]);
void BattingBoard(char teamBat[max_players][25], int wickets, int ballfaced[max_players], int runBat[max_players], int fours[max_players], int sixes[max_players], char teamBowl[max_players][25], int wData[max_players][5]);
void BowlingBoard(char teamBowl[max_players][25], int ballbowled[max_players], int runBowl[max_players], int wicketsBowl[max_players], int ball);
int Innings(int totalNoOfOvers, char teamBat[max_players][25], int runBat[max_players], int ballfaced[max_players], char teamBowl[max_players][25], int ballbowled[max_players], int runBowl[max_players], int wicketsBowl[max_players], int target = 0)
{

	int onbat[2] = { 0,1 };
	int strike = 0;
	int temp = 0;
	int ball = 1;
	int bowler = 6;
	int overs = 0;
	int wickets = 0;
	int fours[max_players];
	int sixes[max_players];
	int wData[max_players][5];

	bool isMatchFinished = false;

	for (int i = 0; i < max_players; i++)
	{
		fours[i] = 0;
		sixes[i] = 0;
	}
	while (overs < totalNoOfOvers)  //Ends when all players have played
	{

		if (isMatchFinished) {
			break;
		}
		while (ball < 7)  //Terminates after every over
		{
			int out = 0;
			int prob = 0;
			if (onbat[strike] <= 3)
			{
				prob = 10; // was 10 
			}
			else
			{
				prob = 2; // was 2 
			}
			if ((rand() % prob) == 0)
			{
				out = 1; // was 1
			}
			else
			{
				out = 0;
			}
			if (!out)
			{
				temp = rand() % 7; //score
				runBat[onbat[strike]] += temp;
				ballfaced[onbat[strike]]++;
				ballbowled[bowler]++;
				runBowl[bowler] += temp;
				if (temp == 4)
				{
					fours[onbat[strike]]++;
				}
				if (temp == 6)
				{
					sixes[onbat[strike]]++;
				}
				if (temp == 1 || temp == 3 || temp == 5)
				{
					strike = (strike + 1) % 2;

				}
			}
			else
			{
				temp = -1; //out

			}
			if (temp == -1)
			{
				ball++;
				ballfaced[onbat[strike]]++;
				ballbowled[bowler]++;

				//cout << teamBat[onbat[strike]] << "\t" << runBat[onbat[strike]] << "\t" << ballfaced[onbat[strike]] << "\t" << (runBat[onbat[strike]] * 1.0) / ballfaced[onbat[strike]] << endl;  
				BatsmanGotOut(teamBat[onbat[strike]], runBat[onbat[strike]], ballfaced[onbat[strike]], fours[onbat[strike]], sixes[onbat[strike]]);
				_getch();
				wData[wickets][0] = onbat[strike]; //Batsman that got out
				int ts = 0;
				for (int i = 0; i < wickets + 2; i++)
				{
					ts += runBat[i];
				}
				wData[wickets][1] = ts; //Total score when wicket fell
				wData[wickets][2] = overs; //Overs when out
				wData[wickets][3] = ball; //Balls when out
				wData[wickets][4] = bowler; //Bowler that took the wicket
				wickets++;
				wicketsBowl[bowler]++;
				onbat[strike] = wickets + 1;

				break;
			}

			if (scorecard(totalNoOfOvers, wData, strike, ball, onbat, bowler, overs, wickets, fours, sixes, teamBat, runBat, ballfaced, ballbowled, teamBowl, runBowl, wicketsBowl, target)) {
				isMatchFinished = true;
				break;
			}

			ball++;
			_getch();

		}
		if (wickets >= 6) {
			break;
		}
		if (ball > 6)
		{
			overs++;
			if (bowler == 2)
			{
				bowler = 6;
			}
			else
			{
				bowler--;
			}
			ball = 1;
		}

	}
	int ts = 0;
	for (int i = 0; i < max_players; i++)
	{
		ts += runBat[i];
	}
	return ts;





}
float Oversbowled(int overs, int ball)
{
	float o = overs;
	if (ball == 6)
	{
		o++;
	}
	else
	{
		o = o * 10 + ball;
		o = o / 10;
	}
	return o;
}
int main() {
	int totalNoOfOvers = 0, ts1, ts2;
	totalNoOfOvers = config();
	char temp[25];
	char playersteam1[max_players][25];
	int runscored1[max_players], ballfaced1[max_players], ballsbowled1[max_players], rungiven1[max_players], wicketstaken1[max_players];

	char playersteam2[max_players][25];

	int runscored2[max_players], ballfaced2[max_players], ballsbowled2[max_players], rungiven2[max_players], wicketstaken2[max_players];
	for (int i = 0; i < max_players; i++)
	{
		runscored1[i] = 0;
		ballfaced1[i] = 0;
		ballsbowled1[i] = 0;
		rungiven1[i] = 0;
		wicketstaken1[i] = 0;
		runscored2[i] = 0;
		ballfaced2[i] = 0;
		ballsbowled2[i] = 0;
		rungiven2[i] = 0;
		wicketstaken2[i] = 0;

	}
	ifstream fin1("team1.txt");
	for (int i = 0; i < 7; i++) {
		fin1 >> playersteam1[i];
		fin1 >> temp;
		int len = strlen(playersteam1[i]);
		int j = 0;
		playersteam1[i][len] = ' ';
		len++;
		while (temp[j] != '\0')
		{
			playersteam1[i][len] = temp[j];
			len++;
			j++;

		}
		playersteam1[i][len] = '\0';
		fin1 >> runscored1[i] >> ballfaced1[i] >> ballsbowled1[i] >> rungiven1[i] >> wicketstaken1[i];

	}

	fin1.close();
	ifstream fin2("team2.txt");
	for (int i = 0; i < 7; i++) {
		fin2 >> playersteam2[i];
		fin2 >> temp;
		int len = strlen(playersteam2[i]);
		int j = 0;
		playersteam2[i][len] = ' ';
		len++;
		while (temp[j] != '\0')
		{
			playersteam2[i][len] = temp[j];
			len++;
			j++;

		}
		playersteam2[i][len] = '\0';
		fin2 >> runscored2[i] >> ballfaced2[i] >> ballsbowled2[i] >> rungiven2[i] >> wicketstaken2[i];

	}
	fin2.close();
	srand(time(NULL));

	int toss = 0 + (rand() % 2);
	if (toss == 1) {
		//team1 will bat
		ts1 = Innings(totalNoOfOvers, playersteam1, runscored1, ballfaced1, playersteam2, ballsbowled2, rungiven2, wicketstaken2);
		ts2 = Innings(totalNoOfOvers, playersteam2, runscored2, ballfaced2, playersteam1, ballsbowled1, rungiven1, wicketstaken1, ts1);
	}
	else {
		//team2 will bat
		ts2 = Innings(totalNoOfOvers, playersteam2, runscored2, ballfaced2, playersteam1, ballsbowled1, rungiven1, wicketstaken1);
		ts1 = Innings(totalNoOfOvers, playersteam1, runscored1, ballfaced1, playersteam2, ballsbowled2, rungiven2, wicketstaken2, ts2);

	}
	char ch;
	while (true) {


		cout << "Do you want a summary and want to save a file of match?" << endl;
		cout << "If yes press 'S' for display " << endl;
		cout << "If No Press 'N' to exit simulator" << endl;
		cout << " Your Choice: ";
		cin >> ch;
		if (ch == 's' || ch == 'S')   // the function for 
		{
			summary(ts1, ts2, runscored1, runscored2, wicketstaken1, wicketstaken2, playersteam1, playersteam2);
			return 0;
		}
		else if (ch == 'n' || ch == 'N') {
			return 0;
		}
		else {
			cout << "\n\t *************** Wrong Input **************" << endl;
			cout << " \t\t\t Try Again !" << endl;
		}

	}

}

bool scorecard(int totalNoOfOvers, int wData[max_players][5], int strike, int ball, int onbat[2], int bowler, int overs, int wickets, int fours[max_players], int sixes[max_players], char teamBat[max_players][25], int runBat[max_players], int ballfaced[max_players], int ballbowled[max_players], char teamBowl[max_players][25], int runBowl[max_players], int wicketsBowl[max_players], int target)
{
	int ts = 0;
	bool isSecondInnings = false;
	cout << "--------------------------------------------------------------------------------------------" << endl << endl;
	if (target == 0)
	{
		cout << "Innings 1" << endl;
	}
	else
	{
		isSecondInnings = true;

		for (int i = 0; i < max_players; i++)
		{
			ts += runBat[i];
		}

		//	if (ts > target) {
			//	cout << "\n\n *********************** Team 2 Wins!! ***************************** \n\n";
			//	return;
			//}
			//cout << "Innings 2" << "\t Target: " << target << "\t Remaining Score= " << target - ts << "\t Remaining Overs= " << totalNoOfOvers - overs << endl;
	}
	BattingBoard(teamBat, wickets, ballfaced, runBat, fours, sixes, teamBowl, wData);
	TotalScore(runBat, overs, wickets, ball);
	FallOfWickets(wickets, wData, teamBowl);
	BowlingBoard(teamBowl, ballbowled, runBowl, wicketsBowl, ball);
	if (isSecondInnings) {
		if ((ts > target) && (Oversbowled(overs, ball) >= totalNoOfOvers)) {
			cout << "\n\n *********************** Match Tied!! ***************************** \n\n";
			return true;
		}
		if (wickets >= 6) {
			cout << "\n\n *********************** Team 2 Wins!! ***************************** \n\n";
			return true;
		}
		if (ts > target) {
			cout << "\n\n *********************** Team 2 Wins!! ***************************** \n\n";
			return true;
		}
		if (Oversbowled(overs, ball) >= totalNoOfOvers) {
			cout << "\n\n *********************** Team 1 Wins!! ***************************** \n\n";
			return true;
		}
		cout << "\nInnings 2" << "\t Target: " << target << "\t Remaining Score= " << target - ts << "\t Remaining Overs= " << totalNoOfOvers - overs << endl;
	}


	return false;

}
void FallOfWickets(int wickets, int wData[max_players][5], char teamBowl[max_players][25])
{
	cout << "Fall of Wickets: " << endl;
	for (int i = 0; i < wickets; i++)
	{
		cout << i + 1 << "-" << wData[i][1] << "( " << teamBowl[wData[i][4]];
		cout << " Overs: " << Oversbowled(wData[i][2], wData[i][3]) << ")  ";
	}
	cout << endl;

}
void TotalScore(int runBat[max_players], int overs, int wickets, int ball)
{
	int ts = 0;
	for (int i = 0; i < wickets + 2; i++)
	{
		ts += runBat[i];
	}

	cout << "\nTOTAL \t OVERS: " << Oversbowled(overs, ball) << "\t RR: " << ((ts * 6) * 1.0) / (overs * 6 + ball) * 1.0 << "\t" << ts << "/" << wickets << endl;
	cout << endl;
}
void BattingBoard(char teamBat[max_players][25], int wickets, int ballfaced[max_players], int runBat[max_players], int fours[max_players], int sixes[max_players], char teamBowl[max_players][25], int wData[max_players][5])
{
	float sRate = 0.0;
	cout << "Batting \t\t Runs \t Balls \t 4s \t 6s \t SR " << endl;
	for (int i = 0; i < wickets + 2; i++)
	{
		if (ballfaced[i] > 0)
		{
			sRate = ((runBat[i] * 1.0) / ballfaced[i]) * 100;
		}
		else
		{
			sRate = 0;
		}
		cout << teamBat[i] << "\t\t   " << runBat[i] << "\t" << ballfaced[i] << "\t" << fours[i] << "\t" << sixes[i] << "\t" << sRate << endl;

	}
}
void BowlingBoard(char teamBowl[max_players][25], int ballbowled[max_players], int runBowl[max_players], int wicketsBowl[max_players], int ball)
{

	cout << endl;
	cout << "Bowling \t\t O \t R \t W \t Eco." << endl;
	float eConomy = 0.0;
	for (int i = 6; i >= 2; i--)
	{
		if (ballbowled[i] > 0)
			eConomy = (runBowl[i] * 6.0) / ballbowled[i];
		else
			eConomy = 0;
		cout << teamBowl[i] << "\t\t" << ballbowled[i] / 6 << "." << ballbowled[i] % 6 << "\t" << runBowl[i] << "\t" << wicketsBowl[i] << "\t" << eConomy << endl;
	}

}
void BatsmanGotOut(string batsmanName, int batsmanScore, int ballsfaced, int fours, int sixes)
{
	cout << "\n \n \t\t ############  BatsMan Got Out ############### \n\n";
	cout << "\n\nBatsman Name \t\t Runs \t Balls \t 4s \t 6s \t SR " << endl;

	cout << batsmanName << "\t\t  " << batsmanScore << "\t  " << ballsfaced << "\t " << fours << "\t " << sixes << "\t" << ((float)batsmanScore / ballsfaced * 100) << "\t" << endl;




}


