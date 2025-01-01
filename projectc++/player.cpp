#include "player.h"

Player::Player(const string& name, const string& quizName, int score)
    :name(name), quizName(quizName), score(score)
{
}

Player::~Player()
{
}

string Player::GetName() const
{
    return name;
}

string Player::GetQuizName() const
{
    return quizName;
}

int Player::GetScore() const
{
    return score;
}

void Player::SetName(const string& newName)
{
    this->name = newName;
}

void Player::SetQuizName(const string& newQuizName)
{
    this->quizName = newQuizName;
}

void Player::SetScore(int newScore)
{
    this->score = newScore;
}