#include<iostream>
#include<cstdlib>

using namespace std;

enum enWinner { Pleayr1 = 1, Computer = 2, Draw = 3 };
enum enGameChoice { Stone = 1, Paper = 2, Scissore = 3 };
struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};
struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short Computer2WinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};
enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;
	do
	{

		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissore ? " << endl;
		cin >> Choice;

	} while (Choice < 1 || Choice>3);

	return (enGameChoice)Choice;
}
int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}
enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));
}
enWinner WhoWonTheRound(stRoundInfo Round)
{
	if (Round.Player1Choice == Round.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (Round.Player1Choice)
	{
	case enGameChoice::Paper:
		if (Round.ComputerChoice == enGameChoice::Scissore)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissore:
		if (Round.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Stone:
		if (Round.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Pleayr1;
}
string ChoiceName(enGameChoice Choice)
{
	string arrChoiceName[3] = { "Stone", "Paper", "Scissore" };
	return arrChoiceName[Choice - 1];
}
string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}
string Tabs(int Num)
{
	string t = "";
	for (int i = 0;i < Num;i++)
		t += "\t";
	return t;
}
void ShowGameOverScreen()
{
	cout << Tabs(2) << "_________________________________________________________\n\n";
	cout << Tabs(2) << "                +++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "_________________________________________________________\n\n";
}
void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Pleayr1:
		system("color 2F");//turn screen to Green
		break;
	case enWinner::Computer:
		system("color 4F");//turn screen to Red
		cout << "\a";
		break;
	case enWinner::Draw:
		system("color 6F");//turn screen to Yellow
		break;
	}
}
void ResetSecreen()
{
	system("cls");
	system("color 0F");
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n___________________Round[" << RoundInfo.RoundNumber << "]___________________\n\n";
	cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "] \n";
	cout << "______________________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}
void ShowFinalGameResults(stGameResults GameResults)
{

	cout << Tabs(2) << "_______________________[ Game Results ]_______________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player 1 won times : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.Computer2WinTimes << endl;
	cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "______________________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}
short ReadHowManyRound()
{
	short GameRounds = 1;
	do
	{
		cout << "How MAny Rounds 1 to 10 ? \n";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds>10);

	return GameRounds;
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComuterWinTimes)
{
	if (Player1WinTimes > ComuterWinTimes)
		return enWinner::Pleayr1;
	else if (ComuterWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
stGameResults FillGameResults(short HowManyRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = HowManyRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.Computer2WinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}
stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		//Increase Win/Draw counters
		if (RoundInfo.Winner == enWinner::Pleayr1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}
	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetSecreen();
		stGameResults GameResults = PlayGame(ReadHowManyRound());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}