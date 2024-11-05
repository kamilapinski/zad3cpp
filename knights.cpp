#include "knights.h"

#include <iostream>
#include <list>

class Knight {

};

constexpr Knight TRAINEE_KNIGHT; // TODO

class Tournament {
    private:
        std::list<Knight> fight_list;
        std::list<Knight> lost_list;

        void payoff(Knight& winner, Knight& loser) {
            winner += loser; // Knight musi mieć zdefiniowany ten operator
            fight_list.push_back(winner);
            lost_list.clear(); // to jest dziwne, ale takie jest wymaganie, żeby przy każdej zmianie listy pretendentów czyścić przegranych
            lost_list.push_front(loser);
        }

    public:
        Tournament(std::initializer_list<Knight> s) {
            for (auto knight : s) {
                fight_list.push_back(knight);
            }

            if (s.size() == 0) fight_list.push_back(TRAINEE_KNIGHT);
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

        friend std::ostream& operator<<(std::ostream& os, const Tournament& tournament) {
            for (const Knight knight : tournament.fight_list) {
                os << "+ " << knight << "\n";
            }
            for (const Knight knight : tournament.lost_list) {
                os << "- " << knight << "\n";
            }
            os << "=\n";
            return os;
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

        Tournament& operator+=(const Knight& knight) {
            lost_list.clear();
            fight_list.push_back(knight);
            return *this;
        }

        Tournament& operator-=(const Knight& knight) {
            lost_list.clear();
            fight_list.remove(knight);
            return *this;
        }

        const std::list<Knight>::iterator play() {
            lost_list.clear();

            while (fight_list.size() > 1) {
                Knight first = fight_list.front();
                fight_list.pop_front();
                Knight second = fight_list.front();
                fight_list.pop_front();

                lost_list.clear(); // to jest dziwne, ale takie jest wymaganie, żeby przy każdej zmianie listy pretendentów czyścić przegranych

                if (first > second) // Knight musi mieć zdef. ten operator
                    payoff(first, second);
                else if (first < second)
                    payoff(second, first);
                else {
                    // kolejność taka sama jak na fight_list
                    lost_list.push_front(second);
                    lost_list.push_front(first);
                }
            }

            if (fight_list.empty())
                return fight_list.end();
            return fight_list.begin();
        }

        const std::list<Knight>::iterator no_winner() {
            return fight_list.end();
        }

        size_t size() const {
            return fight_list.size() + lost_list.size();
            // chociażby dlatego lost_list nie jest typu forward_list
        }
};

constexpr std::pair<int, int> max_diff_classes(std::initializer_list<Knight> list) {
    // TODO
}