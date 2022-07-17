#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <sstream>
using namespace std;




class Game
{
public:
	Game()
	{
		NumberOfPlayers = 0;
		winner = 0;
	}

	void HowManyPlayers()
	{
		cout << "Сколько игроков участвует" << endl;
		cin >> NumberOfPlayers;
		for (int i = 0; i < NumberOfPlayers; i++)
		{
			Player newPlayer;
			Gamers.push_back(newPlayer);
		}
	}

	void SeeState()
	{
		for (int i = 0; i < NumberOfPlayers; i++)
		{
			cout << '\t' << '\t' << '\t' << '\t' << Gamers[i].GetName() << '\t' << Gamers[i].GetPoints() << endl;
		}
		cout << endl;
	}

	void WhoIsFirstAndNext()
	{
		/*Игроки бросают кости*/
		cout << "Игроки бросают кости, для определения кто первый" << endl;
		for (int i = 0; i < NumberOfPlayers; i++)
		{
			Gamers[i].ThrowDice();
			cout << Gamers[i].GetName() << '\t' << Gamers[i].GetDice() << endl;
		}
		cout << endl;
		/* Отсортируем массив по возрастанию значений брошенных костей*/
		for (int i = 1; i < NumberOfPlayers; i++)
		{
			for (int j = 0; j < NumberOfPlayers - 1; j++)
			{
				if (Gamers[j].GetDice() > Gamers[j + 1].GetDice())
				{
					Player temp = Gamers[j];
					Gamers[j] = Gamers[j + 1];
					Gamers[j + 1] = temp;
				}
			}
		}
	};
	void GamersTurn()
	{
		for (int i = 0; i < NumberOfPlayers; i++)
		{
			Gamers[i].Turn();
			if (Gamers[i].GetPoints() > 99) { winner = i; flag = true;  break; } //проверка на выигрыш
			cout << endl << endl;
		}
	}
	bool AnyBodyWin()
	{
		return flag;
	}
	void WhoWon()
	{
		cout << endl << endl << endl << endl << endl << endl;
		cout << "=====================================================";
		cout << endl;
		cout << "Игрок\t" << Gamers[winner].GetName() << "\tПобедил!!!";
		cout << endl;;
		cout << "=====================================================";
	}

private:

	class Player
	{
	public:
		Player()
		{
			dice = 0;
			temporaryPoints = 0;
			points = 0;
			counter++;
			stringstream ss;
			ss << counter;
			name = "Player " + ss.str();
		}

		void ThrowDice()
		{
			dice = 1 + rand() % 6;
		}
		int GetDice()
		{
			return dice;
		};
		string GetName()
		{
			return name;
		}
		int GetPoints()
		{
			return points;
		}
		void Turn()
		{

			cout << "Ход игрока " << name << "\tКоличество несгораемых очков " << points << "\tСгораемые очкм " << temporaryPoints << endl;
			cout << "Кинуть кубик?(y/n)" << endl;
			char choice;
			cin >> choice;
			while (choice == 'y')
			{
				ThrowDice();
				cout << "Выпала\t" << dice << endl;
				if (dice == 1)
				{
					temporaryPoints = 0;
					break;
				};
				temporaryPoints += dice;
				if (temporaryPoints + points > 99)
				{
					break;
				}
				cout << "\tСгораемые очки " << temporaryPoints << endl << "\tСчет при отказе " << temporaryPoints + points << endl << "Бросить еще?" << endl;

				cin >> choice;
			}
			points += temporaryPoints;
			temporaryPoints = 0;
		}
		static int counter;
	private:
		int points;
		int temporaryPoints;
		string name;
		int dice;

	};

	vector<Player> Gamers;
	int NumberOfPlayers;
	int winner;
	bool flag = false;
};


int Game::Player::counter = 0;







int main()
{
	srand(time(0));
	setlocale(LC_ALL, "RU");

	Game game;

	game.HowManyPlayers();
	game.WhoIsFirstAndNext();
	game.SeeState();


	while (true)
	{
		game.GamersTurn();
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		game.SeeState();
		if (game.AnyBodyWin() == true)
		{
			break;
		}
	}

	game.WhoWon();
	return 0;


}