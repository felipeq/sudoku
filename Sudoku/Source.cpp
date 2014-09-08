#include <iostream>
#include <string>
using namespace std;
bool puzzle[9][9][9];
// position of field in puzzle
struct Field
{
	int x;
	int y;
};
int toInt(char arg)
{
	return arg - 48;
}
char toChar(int arg)
{
	return arg + 48;
}
// return value of Field, 0 if not solved
int getValueFor(Field pos)
{
	bool isSolved = true;
	int Value = 0;
	for (int i = 0; i < 9; i++)
	{
		if (puzzle[pos.x][pos.y][i] == true)
		{
			if (Value == 0)
				Value = i + 1;
			else
			{
				isSolved == false;
				return 0;
			}
		}
	}
	return Value;
}
void drawPuzzle()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Field pos = { i, j };
			int val = getValueFor(pos);
			if (val != 0)
				cout << getValueFor(pos) << " ";
			else
				cout << ". ";
		}
		cout << endl;
	}
	cout << "===========================\n";
}
void CheckSquareFor(Field pos)
{
	int StartRow = 3 * (pos.x / 3);
	int StartColumn = 3 * (pos.y / 3);
	for (int row = StartRow; row < StartRow + 3; row++)
	{
		for (int column = StartColumn; column < StartColumn + 3; column++)
		{
			Field pos = { row, column };
			int FieldValue = getValueFor(pos);
			if (FieldValue != 0)
			{
				for (int i = StartRow; i < StartRow + 3; i++)
					for (int j = StartColumn; j < StartColumn + 3; j++)
					{
					puzzle[i][j][FieldValue - 1] = false;
					}
				puzzle[row][column][FieldValue - 1] = true;
			}
		}
	}
}
void CheckHorizontalLineFor(Field pos)
{
	int row = pos.x;
	for (int column = 0; column < 9; column++)
	{
		Field pos = { row, column };
		int FieldValue = getValueFor(pos);
		if (FieldValue != 0)
		{
			for (int i = 0; i < 9; i++)
			{
				puzzle[row][i][FieldValue - 1] = false;
			}
			puzzle[row][column][FieldValue - 1] = true;
		}
	}

}
void CheckVerticalLineFor(Field pos)
{
	int column = pos.y;
	for (int row = 0; row < 9; row++)
	{
		Field pos = { row, column };
		int FieldValue = getValueFor(pos);
		if (FieldValue != 0)
		{
			for (int i = 0; i < 9; i++)
			{
				puzzle[i][column][FieldValue - 1] = false;
			}
			puzzle[row][column][FieldValue - 1] = true;
		}
	}
}
bool KeepSolving()
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			Field pos = { row, column };
			if (getValueFor(pos) == 0)
				return true;
		}
	}
	return false;
}
void CheckAllFields()
{
	while (KeepSolving())
		for (int row = 0; row < 9; row++)
		{
		for (int column = 0; column < 9; column++)
		{
			Field pos = { row, column };
			CheckHorizontalLineFor(pos);
			CheckVerticalLineFor(pos);
			CheckSquareFor(pos);
		}
		}

}
void main(int argc, char* argv[])
{

	string testInput = "...629.489...71..36...859.1724....6....85217...876............98.12475.6..6.384.7";
	string testOutput = "135629748;982471653;647385921;724193865;369852174;518764392;473516289;891247536;256938417;";
	cout << "===========================\n";
	cout << "INPUT:\n";
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			char input;
			input = testInput[row * 9 + column];

			for (int k = 0; k < 9; k++)
			{
				if (input != '.')
					puzzle[row][column][k] = false;
				else
				{
					puzzle[row][column][k] = true;
				}

			}
			if (input != '.')
				puzzle[row][column][toInt(input) - 1] = true;
		}
	}

	drawPuzzle();
	CheckAllFields();
	cout << "OUTPUT:\n";
	drawPuzzle();
	string res = "";
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			res += toChar(getValueFor(Field{ row, column }));
		}
		res += ";";
	}
	if (res.compare(testOutput) == 0)
		cout << "===========================\nPRAWIDLOWY WYNIK\n===========================\n";
}