#ifndef SRC_BOT_H_
#define SRC_BOT_H_
#include "Move2.h"


class Bot
{
	private:
		int ownMap[10][10];
		vector<Move> possibleMoves;
	public:
		Bot();
		int* getNextMove(int map[], int nextMove[]);
		bool isLegalMove(int x1, int y1, int x2, int y2);
		bool isLegalH(int x1, int y1, int x2, int y2);
		bool isLegalV(int x1, int y1, int x2, int y2);
		void fillMap(int map[]);
		int findSets(int map_copy[][10]);
		void printMap();
		void breakTiles(int map_copy[][10]);
		Move find_best_move(int map[][10], int depth, bool improved, int break_depth);
		vector<Move> find_possible_moves(int map[][10], int depth, bool improved, int break_depth);
		int calculate_score(int x1, int y1, int x2, int y2, int map[][10], int depth, bool improved, int break_depth);
};

Bot::Bot() //initialise Bot class - constructor
{

}

void Bot::fillMap(int map[]){
	for(int i=0; i<100; i++){
		ownMap[i/10][i%10] = map[i];
	}
}

void Bot::printMap(){

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(j != 9){
                cout << ownMap[i][j] << " ";
            } else {
                cout << ownMap[i][j];
            }
        }
        cout << endl;
    }
    cout<<endl;
}

int Bot::findSets(int map_copy[][10]){
	int totalScore = 0;
	for(int x=0; x<10; x++){
		int tempScore = 1;
		for(int y=0; y<10; y++){
			if(y>0 && map_copy[x][y] == map_copy[x][y-1] && map_copy[x][y]!=0){
				tempScore++;

			} else if(y>0 && map_copy[x][y] != map_copy[x][y-1] && tempScore>2){
				totalScore += tempScore;
				tempScore = 1;
				// break here
			} else {
				tempScore = 1;
			}
		}
		if(tempScore>2){
			totalScore += tempScore;
			// break here
		}
	}

	for(int y=0; y<10; y++){
			int tempScore = 1;
			for(int x=0; x<10; x++){
				if(x>0 && map_copy[x][y] == map_copy[x-1][y] && map_copy[x][y]!=0){
					tempScore++;
				} else if(y>0 && map_copy[x][y] != map_copy[x-1][y] && tempScore>2){
					totalScore += tempScore;
					tempScore = 1;
				} else {
					tempScore = 1;
				}
			}
			if(tempScore>2){
				totalScore += tempScore;
			}
		}

	return totalScore;
}

void Bot::breakTiles(int map_copy[][10]){
	// Horizontal
	for(int x=0; x<10; x++){
		int count = 1;
		for(int y=0; y<10; y++){
			if(y>0 && map_copy[x][y] == map_copy[x][y-1] && map_copy[x][y]!=0){
				count++;

			} else if(y>0 && map_copy[x][y] != map_copy[x][y-1] && count>2){
				// break here
				int temp_x = x;
				int temp_x2 = x - 1;
				for (int temp_y = y; temp_y > y - count; temp_y--){
					// Make the broken tiles 0
					map_copy[x][temp_y] = 0;
					// Swap the tiles to move zeros upwards
					while(temp_x > 0){
						swap(map_copy[temp_x][temp_y], map_copy[temp_x2][temp_y]);
						temp_x--;
						temp_x2--;
					}
				}
				count = 1;
			} 
			
				else if(y==9 && count>2){
					// break here
					int temp_x = x;
					int temp_x2 = x - 1;
					for (int temp_y = y; temp_y > y - count; temp_y--){
						// Make the broken tiles 0
						map_copy[x][temp_y] = 0;
						// Swap the tiles to move zeros upwards
						while(temp_x > 0){
							swap(map_copy[temp_x][temp_y], map_copy[temp_x2][temp_y]);
							temp_x--;
							temp_x2--;
						}
					}
				}
				else {
					count = 1;
			}
		}
	}

	// Vertical
	for(int y=0; y<10; y++){
		int count = 1;
		for(int x=0; x<10; x++){
			if(x>0 && map_copy[x][y] == map_copy[x-1][y] && map_copy[x][y]!=0){
				count++;

			} else if(x>0 && map_copy[x][y] != map_copy[x-1][y] && count>2){
				// Break here
				int temp_x = x;
				int temp_x2 = x - count;
				map_copy[temp_x][y] = 0;
				while(temp_x2 > -1){
					swap(map_copy[temp_x][y], map_copy[temp_x2][y]);
					temp_x--;
					temp_x2--;
				}
				count = 1;
			
			} else if(x==9 && count>2){
				// Break here
				int temp_x = x;
				int temp_x2 = x - count;
				map_copy[temp_x][y] = 0;
				while(temp_x2 > -1){
					swap(map_copy[temp_x][y], map_copy[temp_x2][y]);
					temp_x--;
					temp_x2--;
				}
				}
				else {
					count = 1;
			}
		}
	}

}

bool Bot::isLegalMove(int x1, int y1, int x2, int y2){
	if((isLegalH(x1,y1,x2,y2) || isLegalV(x1,y1,x2,y2)) && ownMap[x1][y1]!=0 && ownMap[x2][y2]!=0){
		return true;
	}
	return false;
}

bool Bot::isLegalH(int x1, int y1, int x2, int y2){
	if(((ownMap[x2][y2]==ownMap[x1-2][y1]) && (ownMap[x2][y2]==ownMap[x1-1][y1]) && x1>1 && x2>=x1)
			|| ((ownMap[x1][y1]==ownMap[x2-2][y2]) && (ownMap[x1][y1]==ownMap[x2-1][y2]) && x2>1 && x1>=x2)){
		return true;
	}

	else if(((ownMap[x2][y2]==ownMap[x1+2][y1]) && (ownMap[x2][y2]==ownMap[x1+1][y1]) && x1<8 && x1>=x2)
			|| ((ownMap[x1][y1]==ownMap[x2+2][y2]) && (ownMap[x1][y1]==ownMap[x2+1][y2]) && x2<8 && x2>=x1)){
		return true;
	}

	else if(y1!=y2 &&  (((ownMap[x2][y2]==ownMap[x1-1][y1]) && (ownMap[x2][y2]==ownMap[x1+1][y1]) && (x1>0 && x1<9))
			|| ((ownMap[x1][y1]==ownMap[x2-1][y2]) && (ownMap[x1][y1]==ownMap[x2+1][y2]) && (x2>0 && x2<9)))){
		return true;
	}
	return false;
}

bool Bot::isLegalV(int x1, int y1, int x2, int y2){
	if(((ownMap[x2][y2]==ownMap[x1][y1-2]) && (ownMap[x2][y2]==ownMap[x1][y1-1]) && y1>1 && y2>=y1)
			|| ((ownMap[x1][y1]==ownMap[x2][y2-2]) && (ownMap[x1][y1]==ownMap[x2][y2-1]) && y2>1 && y1>=y2)){
		return true;
	}
	else if(((ownMap[x2][y2]==ownMap[x1][y1+2]) && (ownMap[x2][y2]==ownMap[x1][y1+1]) && y1<8 && y1>=y2)
			|| ((ownMap[x1][y1]==ownMap[x2][y2+2]) && (ownMap[x1][y1]==ownMap[x2][y2+1]) && y2<8 && y2>=y1)){
		return true;
	}
	else if(x1!=x2 && (((ownMap[x2][y2]==ownMap[x1][y1-1]) && (ownMap[x2][y2]==ownMap[x1][y1+1]) && (y1>0 && y1<9))
			|| ((ownMap[x1][y1]==ownMap[x2][y2-1]) && (ownMap[x1][y1]==ownMap[x2][y2+1]) && (y2>0 && y2<9)))){
		return true;
	}
	return false;
}

int* Bot::getNextMove(int map[], int nextMove[]) //decide and return next move, given the current state of the map.
{
	fillMap(map);
	Move bestMove = find_best_move(ownMap, 2, true, 2);

	int tempx1 = bestMove.x1;
	int tempy1 = bestMove.y1;
	int tempx2 = bestMove.x2;
	int tempy2 = bestMove.y2;
	nextMove[0] = tempx1;
	nextMove[1] = tempy1;
	nextMove[2] = tempx2;
	nextMove[3] = tempy2;

	// cout << "Best move: " << tempx1 << " " << tempy1 << " " << tempx2 << " " << tempy2 << endl;

	return nextMove;
	
}


Move Bot::find_best_move(int map[][10], int depth, bool improved, int break_depth){

	// Find all possible moves
	vector<Move> possible_moves = find_possible_moves(map, depth, improved, break_depth);

	Move best_move = Move(0, 0, 0, 0, -1);

	// Find a move with the best score
	for(int i = 0; i < possible_moves.size(); i++){
		if(possible_moves[i].getScore() >= best_move.getScore()){
			best_move = possible_moves[i];
		}
	}
	return best_move;
}

vector<Move> Bot::find_possible_moves(int map[][10], int depth, bool improved, int break_depth){
	vector<Move> possible_moves;
	for(int x =0; x<10; x++){
		for(int y=0; y<10; y++){
			if(x!=9 && isLegalMove(x,y,x+1,y)){
				int score = calculate_score(x,y,x+1,y, map, depth, improved, break_depth);
				Move m(x,y,x+1,y,score);
				possible_moves.push_back(m);
			}
			if(y!=9 && isLegalMove(x,y,x,y+1)){
				int score = calculate_score(x,y,x,y+1, map, depth, improved, break_depth);
				Move m(x,y,x,y+1,score);
				possible_moves.push_back(m);
			}
		}
	}
	return possible_moves;
}


int Bot::calculate_score(int x1, int y1, int x2, int y2, int map[][10], int depth, bool improved, int break_depth){
	
	// Copy the map
	int map_copy[10][10];
	for(int x=0; x<10; x++){
		for(int y=0; y<10; y++){
			map_copy[x][y] = map[x][y];
		}
	}

	// Make the move
	swap(map_copy[x1][y1], map_copy[x2][y2]);

	// Calculate score
	int score = 0;
	if(improved == false){
		score += findSets(map_copy);
	}
	else{
		// Compute the score of a move with a specified depth
		for(int d=1; d <= break_depth; d++){
			score += findSets(map_copy)*d;
			breakTiles(map_copy);
		}
	}

	if(depth == 0){
		return score;
	}
	else{
		Move best = find_best_move(map_copy, depth-1, improved, break_depth);
		return score + best.getScore();
	}
}

#endif /* SRC_BOT_H_ */
