//USED LIBLARIES & Definitions:	
	#include <iostream>
	#include <vector>
	#include <limits> //int inf = numeric_limits<int>::max();
	#define Row 0
	#define Column 1
	using namespace std;
//SIGNITURE OF FUNCTIONS:
	vector<vector<char> > read_board(char& maximizer);
	void print_board(const vector<vector<char> >& board);
	int ValOfBoard(const vector<vector<char> >& board,char maximizer);
	int minimax( vector<vector<char> >& board ,bool MaximizerTurn,char maximizer);
	vector<int> next_move(vector<vector<char> >& board,char maximizer);


int main()
{
	char maximizer;
	vector<vector<char> > board=read_board(maximizer);
	vector<int> best_move=next_move(board,maximizer);
	cout<<best_move[Row]<<' '<<best_move[Column]<<endl;
	//print_board(board);
}

vector<int> next_move(vector<vector<char> >& board,char maximizer)
{
	int BestVal = -1*(numeric_limits<int>::max());
	vector<int> result(2,-1);
		for(int i=0;i<9;i++)
		{
			if(board[i/3][i%3]!='E') continue;
			board[i/3][i%3]=maximizer;
			int CurrentVal=minimax(board,false,maximizer);
			board[i/3][i%3]='E';
			    if (CurrentVal > BestVal)
                {
                    result[Row] = i/3;
                    result[Column] = i%3;
                    BestVal = CurrentVal;
                }
		}
		return result;
}

int minimax(vector<vector<char> >& board ,bool MaximizerTurn,char maximizer)
{
	bool FreeSpace=false;
	for(int i=0;i<9;i++)
		if(board[i/3][i%3]=='E')
			FreeSpace=true;
    int CurrentVal = ValOfBoard(board,maximizer);
    if(!FreeSpace || CurrentVal!=0)
    	return CurrentVal;

	if(MaximizerTurn)
	{
		int BestVal = -1*(numeric_limits<int>::max());
		for(int i=0;i<9;i++)
		{
			if(board[i/3][i%3]!='E') continue;
			board[i/3][i%3]=maximizer;
			//Now it's minimizer's turn:
			BestVal=max(BestVal,minimax(board,false,maximizer));
			board[i/3][i%3]='E';
		}
		return BestVal;
	}

	if(!MaximizerTurn)
	{
		char minimizer= (maximizer=='X') ? 'O' : 'X';
		int BestVal = numeric_limits<int>::max();
		for(int i=0;i<9;i++)
		{
			if(board[i/3][i%3]!='E') continue;
			board[i/3][i%3]=minimizer;
			//Now it's maximizer's turn:
			BestVal=min(BestVal,minimax(board,true,maximizer));
			board[i/3][i%3]='E';
		}
		return BestVal;
	}
}

int ValOfBoard(const vector<vector<char> >& board,char maximizer)
{
	//Horizentals:
	for (int i = 0; i < 3; i++)
	{
		if(board[i][1]==board[i][0] && board[i][1]==board[i][2] && board[i][1]!='E')
			return (board[i][1]==maximizer) ? 10 : -10;
	}

	//Verticals:
	for (int i = 0; i < 3; i++)
	{
		if(board[1][i]==board[0][i] && board[1][i]==board[2][i] && board[1][i]!='E')
			return (board[1][i]==maximizer) ? 10 : -10;
	}

	//Diagonals:
	if(((board[1][1]==board[0][0] && board[1][1]==board[2][2])||
		(board[1][1]==board[0][2] && board[1][1]==board[2][0]))&&
		 board[1][1]!='E')
			return (board[1][1]==maximizer) ? 10 : -10;

	//Draw or Incomplete game: 
	return 0;
}

vector<vector<char> > read_board(char& maximizer)
{
	vector<vector<char> > result;
	for(int i=0;i<3;i++)
	{
		vector<char> row;
		for (int j = 0; j < 3; j++)
		{
			char cell;cin>>cell;
			row.push_back(cell);
		}
		result.push_back(row);
	}
	cin>>maximizer;
	return result;
}

void print_board(const vector<vector<char> >& board)
{
	for(int i=0;i<3;i++)
	{
		for (int j = 0; j < 3; j++)
			cout<<board[i][j];
		cout<<endl;
	}
}