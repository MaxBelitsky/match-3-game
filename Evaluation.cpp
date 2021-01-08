#include "std_lib_facilities.h"
#include <fstream>
#include "GameEngine.h"
#include "Bot.h"


int play(string map, string future_map){
    GameEngine engine(map, future_map); 
	Bot myBot; 



	while(engine.hasLegalMoves()){ 
		int x1, y1, x2, y2, nextMoveInt; 
		int *nextMove = &nextMoveInt; 

		nextMove = myBot.getNextMove(engine.getMap(), nextMove); //get next move from bot.

		//assign coordinates of next move
		int tempx1 = nextMove[0];
		int tempy1 = nextMove[1];
		int tempx2 = nextMove[2];
		int tempy2 = nextMove[3];
		x1 = tempx1;
		y1 = tempy1;
		x2 = tempx2;
		y2 = tempy2;

		//check if the move is legal
		if(engine.isLegalMove(x1, y1, x2, y2)){

			int points=1; //first move always gets 1 point per tile
			engine.makeMove(nextMove); //make the move
			while(engine.needsUpdate()){ //while there is still tiles to break
				engine.updateMap(points); //update the map
				engine.restoreMap(); //copy map clone to original map

				points+=1; //next cycle of tile breaking gets +1 point
			}
		}
		else{ //move is invalid
			cout<<"Invalid move, try again"<<endl;
		}
	}
    return engine.getScore();
}

int main()
{
	
    string current, future;
	int score = 0, times = 0;
	for(int i = 1; i < 100; i++){
		current = "maps/GMap" + to_string(i) + ".txt";
		future = "maps/GMap" + to_string(i+1) + ".txt";
		score += play(current, future);
		times ++;
	}

	current = "maps/GMap100.txt";
	future = "maps/GMap1.txt";
	score += play(current, future);
	times ++;

	cout << "The number of tests is " << times << "\nThe average score is " << double(score)/double(times) << endl;

	return 0;
}