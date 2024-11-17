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
        static constexpr size_t MAX_GOLD = SIZE_MAX;
        inline constexpr Knight(size_t g, size_t w, size_t a) :
            gold(g), 
            weapon_class(w),
            armour_class(a) 
        { 
        }

        inline constexpr Knight(const Knight&) = default;
        inline constexpr Knight& operator=(const Knight&) = default;
        inline constexpr Knight(Knight&&) = default;
        inline constexpr Knight& operator= (Knight&&) = default;

        inline constexpr size_t get_gold() const {
            return gold;
        }
        inline constexpr size_t get_armour_class() const {
            return armour_class;
        }
        inline constexpr size_t get_weapon_class() const {
            return weapon_class;
        }
        
        inline constexpr size_t give_gold() {
            size_t tmp_gold = gold;
            gold = 0;
            return tmp_gold;
        }

        inline constexpr void take_gold(size_t amount) {
            gold = (gold > MAX_GOLD - amount) ? MAX_GOLD : gold + amount;
        }
 
        inline constexpr void change_weapon(size_t new_weapon_class) {
            weapon_class = new_weapon_class;
        }

        inline constexpr size_t give_up_weapon() {
            size_t temp_weapon = weapon_class;
            weapon_class = 0;
            return temp_weapon;
        }

        inline constexpr void change_armour(size_t new_armour_class) {
            armour_class = new_armour_class;
        }

        inline constexpr size_t take_off_armour() {
            size_t temp_armour = armour_class;
            armour_class = 0;
            return temp_armour;
        }

        inline constexpr Knight& operator+=(Knight& rhs)  {
            take_gold(rhs.give_gold());

            (rhs.weapon_class > this->weapon_class) ? change_weapon(rhs.give_up_weapon()) : change_weapon(this->weapon_class);

            (rhs.armour_class > this->armour_class) ? change_armour(rhs.take_off_armour()) : change_armour(this->armour_class);

            return *this;
        }

        inline constexpr Knight operator+(const Knight& k) const {
            size_t total_gold = (gold > MAX_GOLD - k.gold) ? MAX_GOLD : gold + k.gold;
            size_t best_weapon_class = std::max(weapon_class, k.weapon_class);
            size_t best_armor_class = std::max(armour_class, k.armour_class);

            return Knight(total_gold, best_weapon_class, best_armor_class);
        }

        constexpr std::weak_ordering operator<=>(const Knight& other) const {
            bool this_wins = (this->weapon_class > other.armour_class && this->armour_class >= other.weapon_class);
            bool other_wins = (other.weapon_class > this->armour_class && other.armour_class >= this->weapon_class);

            return (this_wins) ?
                (
                (!other_wins) ? 
                    std::weak_ordering::greater
                :
                    static_cast<std::weak_ordering>((this->armour_class == other.armour_class) ? 
                        this->weapon_class <=> other.weapon_class 
                    : 
                        this->armour_class <=> other.armour_class)
                )
            :
                (other_wins) ?
                    std::weak_ordering::less
                :
                    ((this->armour_class >= other.weapon_class && other.armour_class >= this->weapon_class) ?
                    std::weak_ordering::equivalent
                    :
                    static_cast<std::weak_ordering>(((this->armour_class == other.armour_class) ? 
                    this->weapon_class <=> other.weapon_class : 
                    this->armour_class <=> other.armour_class)))
            ;
        }

        inline constexpr bool operator>(const Knight& other) const {
            return (*this <=> other) == std::weak_ordering::greater;
        }

        inline constexpr bool operator<(const Knight& other) const {
            return (*this <=> other) == std::weak_ordering::less;
        }

        inline constexpr bool operator==(const Knight& other) const {
            return (*this <=> other) == std::weak_ordering::equivalent;
        }

        friend inline std::ostream& operator<<(std::ostream& os, const Knight& knight) {
            os << "(" << knight.gold << " gold, " << knight.weapon_class
               << " weapon class, " << knight.armour_class << " armour class)\n";
            return os;
        }
};

constexpr Knight TRAINEE_KNIGHT(0, 1, 1);

class Tournament {
    private:
        std::list<Knight> fight_list;
        std::list<Knight> lost_list;

        inline void payoff(Knight& winner, Knight& loser) {
            winner += loser;
            fight_list.push_back(winner);
            lost_list.push_front(loser);
        }

        inline void remove_fighting_knights(const Knight& knight) {
            fight_list.remove_if([&knight](const Knight& other) {
                return (knight.get_gold() == other.get_gold() && knight.get_weapon_class() == other.get_weapon_class() && knight.get_armour_class() == other.get_armour_class()) ? true : false;;
            });
        }

    public:
        Tournament(std::initializer_list<Knight> s) {
            fight_list = std::list<Knight>();
            if (s.size() == 0) {
                fight_list.push_back(TRAINEE_KNIGHT);
            } else {
                for (auto knight : s) {
                    fight_list.push_back(knight);
                }
            }
        }

        inline Tournament(const Tournament& that) : 
        fight_list(that.fight_list), 
        lost_list(that.lost_list) {
        }

        inline Tournament(Tournament&& that) : 
        fight_list(std::move(that.fight_list)), 
        lost_list(std::move(that.lost_list)) {
        }

        inline Tournament& operator=(const Tournament& that) {
            if (this != &that) {
                fight_list = that.fight_list;
                lost_list = that.lost_list;
            }
            return *this;
        }

        inline Tournament& operator=(Tournament&& that) {
            if (this != &that) {
                fight_list = std::move(that.fight_list);
                lost_list = std::move(that.lost_list);
            }
            return *this;
        }

        inline Tournament& operator+=(const Knight& knight) {
            lost_list.clear();
            fight_list.push_back(knight);
            return *this;
        }

        inline Tournament& operator-=(const Knight& knight) {
            lost_list.clear();
            this->remove_fighting_knights(knight);
            return *this;
        }

        const std::list<Knight>::const_iterator play() {
            lost_list.clear();

            while (fight_list.size() > 1) {
                Knight first = fight_list.front();
                fight_list.pop_front();
                Knight second = fight_list.front();
                fight_list.pop_front();

                if (first > second)
                    payoff(first, second);
                else if (first < second)
                    payoff(second, first);
                else {
                    lost_list.push_front(second);
                    lost_list.push_front(first);
                }
            }

            return fight_list.begin();
        }

        inline const std::list<Knight>::const_iterator no_winner() const {
            return fight_list.end();
        }

        inline size_t size() const {
            return fight_list.size() + lost_list.size();
        }

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