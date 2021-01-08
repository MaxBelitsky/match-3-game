#ifndef MOVE2_H_
#define MOVE2_H_


class Move{

private:
	int score;
public:
	int x1, y1, x2, y2;
	Move();
	Move(int x1, int y1, int x2, int y2, int score);
	int getScore();
	int getCoordinates();
};


Move::Move(int x1, int y1, int x2, int y2, int score=0){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->score = score;
}

int Move::getScore(){
	return this->score;
}

#endif /* MOVE_H2_ */
