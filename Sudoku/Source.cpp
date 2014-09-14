#include <iostream>
#include <string>
using namespace std;
bool puzzle[9][9][9];
bool origin[9][9][9];
bool easy_mode = true;
// position of field in puzzle
void copyOriginToPuzzle()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			for (int k = 0; k < 9; k++)
				puzzle[i][j][k] = origin[i][j][k];
}
void copyPuzzleToOrigin()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			for (int k = 0; k < 9; k++)
				origin[i][j][k] = puzzle[i][j][k];
}
struct Field
{
	int x;
	int y;
};
Field firstUnsolved = { 0, 0 };
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
				isSolved = false;
				return 0;
			}
		}
	}
	return Value;
}
void setValueFor(Field pos, int value)
{
	if (value != 0)
		puzzle[pos.x][pos.y][value - 1] = true;
}
string parsePuzzle()
{
	string res;
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			res += toChar(getValueFor(Field{ row, column }));
		}
		res += "\n";
	}
	return res;
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
	int column = pos.y;
	for (int i = 0; i < 9; i++)
	{
		Field horizontalField = { row, i };
		int horizontalValue = getValueFor(horizontalField);
		Field verticalField = { i, column };
		int verticalValue = getValueFor(verticalField);
		if (horizontalValue != 0 || verticalValue != 0)
		{
			for (int j = 0; j < 9; j++)
			{
				if (horizontalValue != 0)
					puzzle[row][j][horizontalValue - 1] = false;
				if (verticalValue != 0)
					puzzle[j][column][verticalValue - 1] = false;
			}
			setValueFor(horizontalField, horizontalValue);
			setValueFor(verticalField, verticalValue);
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
			{
				firstUnsolved = pos;
				return true;
			}
		}
	}
	return false;
}
Field getEasiestField(int minimumOfAssumptions)
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			int possibleSolutions = 0;
			for (int value = 0; value < 9; value++)
			{
				if (puzzle[row][column][value] == true)
					possibleSolutions++;
			}
			if (possibleSolutions == minimumOfAssumptions)
				return{ row, column };
		}
	}
	return getEasiestField(minimumOfAssumptions++);
}
bool areWeFucked(string before, string after)
{
	if (before == after)
	{
		if (easy_mode == true)
			copyPuzzleToOrigin();
		easy_mode = false;
		return true;
	}
	else
		return false;

}
void CheckAllFields()
{

	while (KeepSolving())
	{
		string beforeSolving = parsePuzzle();
		for (int row = firstUnsolved.x; row < 9; row++)
		{
			for (int column = firstUnsolved.y; column < 9; column++)
			{
				Field p = { row, column };
				CheckHorizontalLineFor(p);
				CheckSquareFor(p);
			}
		}

		string afterSolving = parsePuzzle();
		if (areWeFucked(beforeSolving, afterSolving))
		{
			Field easiestField = getEasiestField(2);
			cout << afterSolving << endl;
			for (int i = 0; i < 9; i++)
			{
				// mamy coœ do za³o¿enia
				if (puzzle[easiestField.x][easiestField.y][i] == true)
				{
					bool backup[9];
					// wyzeruj pozosta³e
					for (int j = i + 1; j < 9; j++)
					{
						backup[j] = puzzle[easiestField.x][easiestField.y][j];
						puzzle[easiestField.x][easiestField.y][j] = false;
					}
					CheckAllFields();
					if (!KeepSolving())
						return;
					else
					{
						for (int j = i + 1; j < 0; j++)
						{
							puzzle[easiestField.x][easiestField.y][j] = backup[j];
						}
					}

				}
			}
		}

	}

}

void main(int argc, char* argv[])
{

	string testInput =	"9.....4366..7..9..24.8.........8.75....2.3....51.4.........8.75..9..2..1178.....3";
	string testOutput = "485697321;291453678;736128954;917365842;648271593;523849167;859714236;164932785;372586419;";
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
					origin[row][column][k] = false;
				else
				{
					origin[row][column][k] = true;
				}

			}
			if (input != '.')
				origin[row][column][toInt(input) - 1] = true;
		}
	}
	copyOriginToPuzzle();
	drawPuzzle();
	CheckAllFields();
	cout << "OUTPUT:\n";
	drawPuzzle();
	string res = parsePuzzle();

	if (res.compare(testOutput) == 0)
		cout << "===========================\nPRAWIDLOWY WYNIK\n===========================\n";
}