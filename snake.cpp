#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "snake.h"


SnakeBody::SnakeBody()
{
}


SnakeBody::SnakeBody(int x, int y): mX(x), mY(y)
{
}

int SnakeBody::getX() const
{
    return mX;
}

int SnakeBody::getY() const
{
    return mY;
}

void SnakeBody::setX(int x)
{
    mX = x;
}

void SnakeBody::setY(int y)
{
    mY = y;
}
bool SnakeBody::operator == (const SnakeBody& snakeBody)
{
		// TODO overload the == operator for SnakeBody comparision.
    if (snakeBody.getY() == this->getY() && snakeBody.getX() == this->getX())
        return true;
    return false;
}

Snake::Snake(int gameBoardWidth, int gameBoardHeight, int initialSnakeLength): mGameBoardWidth(gameBoardWidth), mGameBoardHeight(gameBoardHeight), mInitialSnakeLength(initialSnakeLength)
{
    this->initializeSnake();
    this->setRandomSeed();
}

void Snake::setRandomSeed()
{
    // use current time as seed for random generator
    std::srand(std::time(nullptr));
}

/*void Snake::setfood(int x, int y)
{
    Snake::mFood.setX(x);
    Snake::mFood.setY(y);
}*/

void Snake::initializeSnake()
{
    // Instead of using a random initialization algorithm
    // We always put the snake at the center of the game mWindows
    int centerX = this->mGameBoardWidth / 2;
    int centerY = this->mGameBoardHeight / 2;

    for (int i = 0; i < this->mInitialSnakeLength; i ++)
    {
        this->mSnake.push_back(SnakeBody(centerX, centerY + i));
    }
    this->mDirection = Direction::Up;
}

bool Snake::isPartOfSnake(int x, int y)
{
		// TODO check if a given point with axis x, y is on the body of the snake.
    for (int i = 0; i < mSnake.size();i++){
        if (x == mSnake[i].getX() && y == mSnake[i].getY())
            return true;
    }
    return false;
}

/*
 * Assumption:
 * Only the head would hit wall.
 */
bool Snake::hitWall()
{
		// TODO check if the snake has hit the wall
    SnakeBody head = mSnake[0];
    if (head.getX() == 0 || head.getX() == mGameBoardWidth-1
     || head.getY() == 0 || head.getY() == mGameBoardHeight-1)
        return true;
    return false;
}

/*
 * The snake head is overlapping with its body
 */
bool Snake::hitSelf()
{
		// TODO check if the snake has hit itself.
    SnakeBody head = mSnake[0];
    for (int i = 1; i < mSnake.size();i++ ){
        if (head == mSnake[i])
            return true;
    }
    return false;
}


bool Snake::touchFood()
{
    SnakeBody newHead = this->createNewHead();
    if (this->mFood == newHead)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Snake::senseFood(SnakeBody food)
{
    this->mFood = food;
}

std::vector<SnakeBody>& Snake::getSnake()
{
    return this->mSnake;
}

bool Snake::changeDirection(Direction newDirection)
{
    SnakeBody* head = &mSnake[0];
    switch (this->mDirection)
    {
        case Direction::Up:
        {
        // what you need to do when the current direction of the snake is Up
        // and the user inputs a new direction?  TODO
            switch(newDirection)
            {
                case Direction::Up: break;
                case Direction::Down: break;
                case Direction::Left:
                    this->mDirection = Direction::Left;
                    break;
                case Direction::Right:
                    this->mDirection = Direction::Right;
                    break;
            }
            return true;
        }
        case Direction::Down:
        {
        // what you need to do when the current direction of the snake is Down
        // and the user inputs a new direction? TODO
            switch(newDirection)
            {
                case Direction::Up:break;
                case Direction::Down:break;
                case Direction::Left:
                    this->mDirection = Direction::Left;
                    break;
                case Direction::Right:
                    this->mDirection = Direction::Right;
                    break;
            }
            return true;
        }
        case Direction::Left:
        {
        // what you need to do when the current direction of the snake is Left
        // and the user inputs a new direction? TODO
            switch(newDirection)
            {
                case Direction::Left:break;
                case Direction::Right:break;
                case Direction::Up:
                    this->mDirection = Direction::Up;
                    break;
                case Direction::Down:
                    this->mDirection = Direction::Down;
                    break;
            }
            return true;
        }
        case Direction::Right:
        {
        // what you need to do when the current direction of the snake is Right
        // and the user inputs a new direction? TODO
            switch(newDirection)
            {
                case Direction::Left:break;
                case Direction::Right:break;
                case Direction::Up:
                    this->mDirection = Direction::Up;
                    break;
                case Direction::Down:
                    this->mDirection = Direction::Down;
                    break;
            }
            return true;
        }
    }
}


SnakeBody Snake::createNewHead()
{
    /* TODO
    * read the position of the current head
    * read the current heading direction
    * add the new head according to the direction
    * return the new snake
    */
    SnakeBody newHead = mSnake[0];
    Direction direc = this->mDirection;
    int X = newHead.getX();
    int Y = newHead.getY();
    switch(direc)
    {
    case Direction::Up:
        newHead.setY(Y-1);
        break;
    case Direction::Down:
        newHead.setY(Y+1);
        break;
    case Direction::Left:
        newHead.setX(X-1);
        break;
    case Direction::Right:
        newHead.setX(X+1);
        break;
    }
    return newHead;
}

/*
 * If eat food, return true, otherwise return false
 */
bool Snake::moveFoward()
{
    /*
		 * TODO
		 * move the snake forward.
     * If eat food, return true, otherwise return false
     */
    if (touchFood()){
        mSnake.insert(mSnake.begin(), createNewHead());

        return true;
    }
    else{
        for (int i = mSnake.size()-1;i > 0;i--){
            mSnake[i].setX(mSnake[i-1].getX());
            mSnake[i].setY(mSnake[i-1].getY());
        }
        mSnake[0] = createNewHead();
        return false;
    }
}

bool Snake::checkCollision()
{
    if (this->hitWall() || this->hitSelf())
    {
        return true;
    }
    else
    {
        return false;
    }
}


int Snake::getLength()
{
    return this->mSnake.size();
}

