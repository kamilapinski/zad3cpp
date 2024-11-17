#ifndef KNIGHTS_H
#define KNIGHTS_H

#include <initializer_list>
#include <cstdint>
#include <compare>
#include <list>
#include <iostream>
#include <limits>

using std::size_t;


class Knight {
    private:        
        size_t gold;
        size_t weapon_class;
        size_t armour_class;
        
    public:
        //Knight() = delete;
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
            gold = (gold > MAX_GOLD - amount) ? MAX_GOLD : gold + amount;
        }
 
        constexpr void change_weapon(size_t new_weapon_class) {
            weapon_class = new_weapon_class;
        }

        constexpr size_t give_up_weapon() {
            size_t temp_weapon = weapon_class;
            weapon_class = 0;
            return temp_weapon;
        }

        constexpr void change_armour(size_t new_armour_class) {
            armour_class = new_armour_class;
        }

        constexpr size_t take_off_armour() {
            size_t temp_armour = armour_class;
            armour_class = 0;
            return temp_armour;
        }

        constexpr Knight& operator+=(Knight& rhs)  {
            take_gold(rhs.give_gold()); // Chyba tego oczekiwali.

            (rhs.weapon_class > this->weapon_class) ? change_weapon(rhs.give_up_weapon()) : change_weapon(this->weapon_class);

            (rhs.armour_class > this->armour_class) ? change_armour(rhs.take_off_armour()) : change_armour(this->armour_class);

            return *this;
        } // DONE

        constexpr Knight operator+(const Knight& k) const {
            size_t total_gold = (gold > MAX_GOLD - k.gold) ? MAX_GOLD : gold + k.gold;
            size_t best_weapon_class = std::max(weapon_class, k.weapon_class);
            size_t best_armor_class = std::max(armour_class, k.armour_class);

            return Knight(total_gold, best_weapon_class, best_armor_class);
        } // DONE

        constexpr const std::strong_ordering operator<=>(const Knight& other) const {
            bool this_wins = (this->weapon_class > other.armour_class && this->armour_class >= other.weapon_class);
            bool other_wins = (other.weapon_class > this->armour_class && other.armour_class >= this->weapon_class);

            return (this_wins) ?
                (
                (!other_wins) ? 
                    std::strong_ordering::greater
                :
                    ((this->armour_class == other.armour_class) ? this->weapon_class <=> other.weapon_class : this->armour_class <=> other.armour_class)
                )
            :
                (other_wins) ?
                    std::strong_ordering::less
                :
                    ((this->armour_class >= other.weapon_class && other.armour_class >= this->weapon_class) ?
                    std::strong_ordering::equal
                    :
                    ((this->armour_class == other.armour_class) ? this->weapon_class <=> other.weapon_class : this->armour_class <=> other.armour_class))
            ;
        }

        constexpr bool operator>(const Knight& other) const {
            return (*this <=> other) == std::strong_ordering::greater;
        }

        constexpr bool operator<(const Knight& other) const {
            return (*this <=> other) == std::strong_ordering::less;
        }

        constexpr bool operator==(const Knight& other) const {
            return (*this <=> other) == std::strong_ordering::equal;
        }

        friend std::ostream& operator<<(std::ostream& os, const Knight& knight) {
            os << "(" << knight.gold << " gold, " << knight.weapon_class
               << " weapon class, " << knight.armour_class << " armour class)\n";
            return os;
        }

        constexpr bool is_equal(const Knight& other) const {
            return (this->gold == other.gold && this->weapon_class == other.weapon_class && this->armour_class == other.armour_class) ? true : false;
        }
};

constexpr Knight TRAINEE_KNIGHT(0, 1, 1);

class Tournament {
    private:
        std::list<Knight> fight_list;
        std::list<Knight> lost_list;

        void payoff(Knight& winner, Knight& loser);
        void remove_fighting_knights(const Knight& knight);

    public:
        Tournament() = delete;
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
                os << "+ " << knight;
            }
            for (const Knight knight : tournament.lost_list) {
                os << "- " << knight;
            }
            os << "=\n";
            return os;
        }
};

constexpr std::pair<size_t, size_t> max_diff_classes(std::initializer_list<Knight> list) {
    std::pair<size_t, size_t> ans_pair = {0, 0};
    
    for (auto knight : list) {
        std::pair<size_t, size_t> curr_pair = {knight.get_weapon_class(), knight.get_armour_class()};

        if ((curr_pair.first - curr_pair.second) > (ans_pair.first - ans_pair.second)) {
            ans_pair = curr_pair;
        }
    }

    return ans_pair;
}

#endif // KNIGHTS_H