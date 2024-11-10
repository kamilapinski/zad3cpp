#ifndef KNIGHTS_H
#define KNIGHTS_H

#include <initializer_list>
#include <stdint.h>
#include <compare>
#include <list>
#include <ostream>

using std::size_t;


class Knight {
    private:        
        size_t gold;
        size_t weapon_class;
        size_t armour_class;
        
    public:
        Knight() = delete;
        static constexpr size_t MAX_GOLD = SIZE_MAX;
        constexpr Knight(size_t g, size_t w, size_t a) :
            gold(g), 
            weapon_class(w),
            armour_class(a) 
        { 
        }

        constexpr Knight(const Knight&) = default;
        constexpr Knight& operator=(const Knight&) = default;
        constexpr Knight(Knight&&) = default;
        constexpr Knight& operator= (Knight&&) = default;

        constexpr size_t get_gold() const {
            return gold;
        }
        constexpr size_t get_armour_class() const {
            return armour_class;
        }
        constexpr size_t get_weapon_class() const {
            return weapon_class;
        }
        
        constexpr size_t give_gold() {
            size_t tmp_gold = gold;
            gold = 0;
            return tmp_gold;
        }

        constexpr void take_gold(size_t amount) {
            gold += amount;
        }
 
        constexpr void change_weapon(size_t new_weapon_class) {
            weapon_class = new_weapon_class;
        }

        constexpr size_t give_up_weapon() {
            //size_t temp_weapon = weapon_class;
            weapon_class = 0;
            return weapon_class;
        }

        constexpr void change_armour(size_t new_armour_class) {
            armour_class = new_armour_class;
        }

        constexpr size_t take_off_armour() {
            size_t temp_armour = armour_class;
            armour_class = 0;
            return temp_armour;
        }

        constexpr Knight& operator+=(Knight& rhs);
        constexpr Knight operator+(const Knight& k);
        //constexpr bool operator==(const Knight& other); 
        constexpr const std::strong_ordering operator<=>(const Knight& other) const;

        constexpr bool operator>(const Knight& other) const;
        constexpr bool operator<(const Knight& other) const;
        constexpr bool operator==(const Knight& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Knight& knight) {
            os << "(" << knight.gold << ", " << knight.weapon_class
               << ", " << knight.armour_class << ")";
            return os;
        }
};

constexpr Knight TRAINEE_KNIGHT(0, 1, 1);

class Tournament {
    private:
        std::list<Knight> fight_list;
        std::list<Knight> lost_list;

        void payoff(Knight& winner, Knight& loser);

    public:
        Tournament(std::initializer_list<Knight> s);
        Tournament(const Tournament& that);
        Tournament(Tournament&& that);
        Tournament& operator=(const Tournament& that);
        Tournament& operator=(Tournament&& that);
        Tournament& operator+=(const Knight& knight);
        Tournament& operator-=(const Knight& knight);
        const std::list<Knight>::iterator play();
        const std::list<Knight>::iterator no_winner();
        size_t size() const;

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
};

constexpr std::pair<int, int> max_diff_classes(std::initializer_list<Knight> list);

#endif // KNIGHTS_H