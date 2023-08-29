#include <iostream>
using namespace std;
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>


int increase = 0;
int PuzzleDigits;
int SudokuPuzzle[][9] =
{
  { 3, 8, 7, 4, 9, 1, 6, 2, 5 },
  { 2, 4, 1, 5, 6, 8, 3, 7, 9 },
  { 5, 6, 9, 3, 2, 7, 4, 1, 8 },
  { 7, 5, 8, 6, 1, 9, 2, 3, 4 },
  { 1, 2, 3, 7, 8, 4, 5, 9, 6 },
  { 4, 9, 6, 2, 5, 3, 1, 8, 7 },
  { 9, 3, 4, 1, 7, 6, 8, 5, 2 },
  { 6, 7, 5, 8, 3, 2, 9, 4, 1 },
  { 8, 1, 2, 9, 4, 5, 7, 6, 3 }
};
vector<int> RowSudoku = {};
void printSudoku();

bool accurate = true;
bool SudokuValidator = true;

string CorrectRow;
string newTarget;
string SelectedRow;





// Void function that does the job of identifying specific errors in the rows such as problems with the digits that are entered. 
void NumCount(string perfect)
{
  int Cause;
  accurate = true;
  
    cout << newTarget << " " << PuzzleDigits << ":" << endl;

    for (int a = 1; a <= 9; a++)
    {
        Cause = 0;
        char aChar = '0' + a;

        for (int i = 0; i < perfect.size(); i++)
        {
            if (perfect[i] == aChar) Cause++;
        }

        if (Cause > 1)
        {
            cout << "Error Occurred: " << newTarget << "Consists of more than one digits of the number \"" << a << "\".\n";
            accurate = false;
        }

        else if (Cause < 1)
        {
            cout << "Error Occurred: " << newTarget << "Consists of fewer than one digits of the number \"" << a << "\".\n";
            accurate = false;
        }
    }
    Cause = 0;
}

void endValidation(bool validity)
{
    if (SudokuValidator)
    {
        cout << "Sudoku Puzzle is VALID! There were no errors to be found." << endl;
    }
    else
    {
        cout << "Sudoku Puzzle is INVALID! Errors were detected in the puzzle." << endl;
    }
}


void changeRow(int digit)
{
    for (int n = 0; n < 9; n++)
    {
        RowSudoku.push_back(SudokuPuzzle[digit][n]);
    }

    stringstream vectorString;
    for (size_t n = 0; n < RowSudoku.size(); ++n)
    {
        if (n != 0)
        vectorString << ",";
        vectorString << RowSudoku[n];
    }
    SelectedRow = vectorString.str();
}

void BoxAdjust(int digit)
{
    for (int v = 0; v < 3; v++)
    {
        for (int i = 0; i < 3; i++)
        {
            RowSudoku.push_back(SudokuPuzzle[(digit + v)][i + increase]);
        }
    }
    stringstream vectorString;
    for (size_t i = 0; i < RowSudoku.size(); ++i)
    {
        if (i != 0)
            vectorString << ",";
        vectorString << RowSudoku[i];
    }
    SelectedRow = vectorString.str();
}

void ColAdjust(int digit)
{
    for (int n = 0; n < 9; n++)
    {
        RowSudoku.push_back(SudokuPuzzle[n][digit]);
    }

    stringstream vectorString;
    for (size_t n = 0; n < RowSudoku.size(); ++n)
    {
        if (n != 0)
        vectorString << ",";
        vectorString << RowSudoku[n];
    }
    SelectedRow = vectorString.str();
}



void deleteChars(string bit)
{
    string::iterator spa_pos = remove(bit.begin(), bit.end(), ' ');
    bit.erase(spa_pos, bit.end());

    string::iterator com_pos = remove(bit.begin(), bit.end(), ',');
    bit.erase(com_pos, bit.end());

    CorrectRow = bit;
}

void printSudoku()
{
    int a;
    int b;

    for (a = 0; a < 9; a++)
    {
        for (b = 0; b < 9; b++)
        {
         printf("%d ", SudokuPuzzle[a][b]);
        }
        printf("\n");
    }

    return;
}

//A void function that checks each row for errors. When an error is found, it informs the user what the error is.
void RowValidation()
{
    deleteChars(SelectedRow);
    if (CorrectRow.length() > 9)
    {
        if (RowSudoku.size() > 9)
        {
         cout << "Error: Row contains too many digits." << endl;
         exit(EXIT_FAILURE);
        }
        else
        {
         cout << "Error: Row contains digit(s) with values less than 1, and or digits greater than 9." << endl;
         
         exit(EXIT_FAILURE);
        }
    }
    else if (CorrectRow.length() < 9)
    {
        cout << "Error: Row contains less digits than required." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        NumCount(CorrectRow);
    }
    //Outputs valid if each row doesn't have any errors.
    if (accurate)
    {
        cout << "Successful! " << newTarget << " " << PuzzleDigits << " [" << SelectedRow << "] is valid!" << endl;
        SelectedRow.clear();
        CorrectRow.clear();
        RowSudoku.clear();
    }
    //Outputs not valid if any row contains errors.
    else
    {
        cout << "Failure! " << newTarget << " " << PuzzleDigits << " [" << SelectedRow << "] is not valid!" << endl;
        SudokuValidator = false;
        SelectedRow.clear();
        CorrectRow.clear();
        RowSudoku.clear();
    }
}

// The main functions includes everything from the title, validating the puzzle such as row,column,box and prints the results.  
int main()
{
  cout << endl;
    cout << "----------------------------------"<<endl;
    cout << "|        SUDOKU PUZZLE           |" <<endl;
    cout << "----------------------------------"<<endl;
    cout << endl;
      printSudoku();
    cout << endl;
 
    cout << "----------------------------------"<<endl;
    cout <<"|   VALIDATING THE SUDOKU PUZZLE |" <<endl;
    cout << "----------------------------------"<<endl;

    // Validates each row in the puzzle and prints the findings. 
    cout <<endl<<endl;
    newTarget = "Row";
    PuzzleDigits = 0;
  
    for (int Row = 0; Row < 9; Row++)
    {
        changeRow(Row);
        PuzzleDigits++;
        RowValidation();
    }

    //Validates each column in the puzzle and prints the findings. 
 cout<<endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    newTarget = "Column";
    PuzzleDigits = 0;
  
    for(int Col = 0; Col < 9; Col++)
    {
        ColAdjust(Col);
        PuzzleDigits++;
        RowValidation();
    }
    //Validates each box in the puzzle and prints the findings.
    cout<<endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    newTarget = "3 x 3 Box";
    PuzzleDigits = 0;
  
    for (int B = 0; B < 3; B++)
    {
        for (int X = 0; X < 3; X++)
        {
            BoxAdjust(3 * X);
            PuzzleDigits++;
            RowValidation();
        }
        increase += 3;
    }
  
    cout<<endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;

    endValidation(SudokuValidator);
  
    string end;
    cout << endl << endl;
    cout << "Press any key to terminate the program." << endl;
    cin >> end;
}
