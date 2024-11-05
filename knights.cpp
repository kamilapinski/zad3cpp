#include "knights.h"

#include <iostream>
#include <queue>
#include <stack>

class Knight {

};

constexpr Knight TRAINEE_KNIGHT; // TODO

class Tournament {
        std::queue<Knight> tournament_list;
        std::stack<Knight> lost_list;

    public:
        Tournament(std::initializer_list<Knight> s) {
            for (auto knight : s) {
                tournament_list.push(knight);
            }

            if (s.size() == 0) tournament_list.push(TRAINEE_KNIGHT);
        }

};