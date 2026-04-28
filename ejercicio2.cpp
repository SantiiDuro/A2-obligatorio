#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "tads/Hash.h"
#include "tads/ClosedHashImp.cpp"

using namespace std;

int hash3(string key)
{
    int h = 0;
    for (int i = 0; i < key.length(); i++)
        h = 31 * h + int(key[i]);
    return h;
}

int hash2(string key)
{
    int h = 0;
    for (int i = 0; i < key.length(); i++)
        h = h + key[i] * (i + 1);
    return h;
}

struct Player
{
    int score;
    int maxScore;
    int roundReachedMax;
    Player() : score(0), maxScore(0), roundReachedMax(0) {}
    Player(int s, int max, int round) : score(s), maxScore(max), roundReachedMax(round) {}
};

void processRound(ClosedHashImp<string, Player>* hash, string name, int score, int round)
{
    if (!hash->contains(name))
    {
        Player p(score, score, round);
        hash->insert(name, p);
    }
    else
    {
        Player p = hash->get(name);
        p.score += score;
        if (p.score > p.maxScore)
        {
            p.maxScore = p.score;
            p.roundReachedMax = round;
        }
        hash->update(name, p);
    }
}

string maxScoreCompetition(ClosedHashImp<string, Player>* hash, int hashSize)
{
    string winner;
    int maxScore = INT_MIN;
    int minRound = INT_MAX;

    for (int i = 0; i < hashSize; i++)
    {
        if (hash->isOccupiedAt(i))
        {
            Player p = hash->getValueAt(i);
            string name = hash->getKeyAt(i);
            
            if (p.score > maxScore || (p.score == maxScore && p.roundReachedMax < minRound))
            {
                maxScore = p.score;
                minRound = p.roundReachedMax;
                winner = name;
            }
        }
    }

    return winner;
}


int main()
{
    int roundCount, score, hashSize;
    string name, winner;

    cin >> roundCount;

    ClosedHashImp<string, Player>* hash = new ClosedHashImp<string, Player>(roundCount, hash3, hash2);

    for (int i = 0; i < roundCount; i++)
    {
        cin >> name >> score;
        processRound(hash, name, score, i);
    }

    hashSize = hash->getSize();
    winner = maxScoreCompetition(hash, hashSize);

    cout << winner << endl;

    delete hash;
    return 0;
}