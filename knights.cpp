#include "knights.h"

#include <iostream>
#include <queue>
#include <stack>

class Knight {

};

constexpr Knight TRAINEE_KNIGHT; // TODO

class Tournament {
    private:
        std::queue<Knight> fight_list;
        std::stack<Knight> lost_list;

    public:
        Tournament(std::initializer_list<Knight> s) {
            for (auto knight : s) {
                fight_list.push(knight);
            }

            if (s.size() == 0) fight_list.push(TRAINEE_KNIGHT);
        }

        Tournament(const Tournament& that) : fight_list(that.fight_list), lost_list(that.lost_list) {
            // done
        }

        Tournament(Tournament&& that) :
            fight_list(std::move(that.fight_list)),
            lost_list(std::move(that.lost_list))
        {
            // done
        }

        Tournament& operator=(const Tournament& that) {
            if (this != &that) {
                fight_list = that.fight_list;
                lost_list = that.lost_list;
            }
            return *this;
        }

        Tournament& operator=(Tournament&& that) {
            if (this != &that) {
                fight_list = std::move(that.fight_list);
                lost_list = std::move(that.lost_list);
            }
            return *this;
        }



};