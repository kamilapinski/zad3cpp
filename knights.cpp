#include "knights.h"

constexpr Knight & Knight::operator+=(Knight &rhs) {
    take_gold(rhs.give_gold()); // Chyba tego oczekiwali.

    if (rhs.weapon_class > this->weapon_class) {
        change_weapon(rhs.give_up_weapon());
    
    }
    if (rhs.armour_class > this->armour_class) {
        change_armour(rhs.take_off_armour());
    }

    return *this;
} // DONE

constexpr Knight Knight::operator+(const Knight& k) {
    size_t total_gold = std::min(gold + k.gold, MAX_GOLD);
    size_t best_armor_class = std::max(armour_class, k.armour_class);
    size_t best_weapon_class = std::max(weapon_class, k.weapon_class);

    return Knight(total_gold, best_armor_class, best_weapon_class);
} // DONE

/* być może niepotrzebne ze względu na operator <=>
constexpr bool Knight::operator==(const Knight& other) {

    return (*this <=> other) == std::strong_ordering::equal;
} // DONE
*/

constexpr const std::strong_ordering Knight::operator<=>(const Knight& other) const { // Nie wiem czy da się to zrobić bardziej elegancko.
    bool thisWins = (this->weapon_class > other.armour_class && this->armour_class >= other.weapon_class);
    bool otherWins = (other.weapon_class > this->armour_class && other.armour_class >= this->weapon_class);

    if (thisWins && !otherWins) {
        
        return std::strong_ordering::greater;
    }
    if (otherWins && !thisWins) {

        return std::strong_ordering::less;
    }

    // Obaj rycerze mają broń silniejszą od zbroi przeciwnika.
    if (this->weapon_class > other.armour_class && other.weapon_class > this->armour_class) {
        if (this->armour_class != other.armour_class) {
        
            return this->armour_class <=> other.armour_class;
        }

        return this->weapon_class <=> other.weapon_class;
    }

    return std::strong_ordering::equal;
} // DONE

constexpr bool Knight::operator>(const Knight& other) const {
    return (*this <=> other) == std::strong_ordering::greater;
}
constexpr bool Knight::operator<(const Knight& other) const {
    return (*this <=> other) == std::strong_ordering::less;
}
constexpr bool Knight::operator==(const Knight& other) const {
    return (*this <=> other) == std::strong_ordering::equal;
}


// TOURNAMENT

void Tournament::payoff(Knight& winner, Knight& loser) {
    winner += loser; // Knight musi mieć zdefiniowany ten operator
    fight_list.push_back(winner);
    lost_list.clear(); // to jest dziwne, ale takie jest wymaganie, żeby przy każdej zmianie listy pretendentów czyścić przegranych
    lost_list.push_front(loser);
}

Tournament::Tournament(std::initializer_list<Knight> s) {
    for (auto knight : s) {
        fight_list.push_back(knight);
    }

    if (s.size() == 0) fight_list.push_back(TRAINEE_KNIGHT);
}

Tournament::Tournament(const Tournament& that) : fight_list(that.fight_list), lost_list(that.lost_list) {
    // done
}

Tournament::Tournament(Tournament&& that) :
    fight_list(std::move(that.fight_list)),
    lost_list(std::move(that.lost_list))
{
    // done
}

Tournament& Tournament::operator=(const Tournament& that) {
    if (this != &that) {
        fight_list = that.fight_list;
        lost_list = that.lost_list;
    }
    return *this;
}

Tournament& Tournament::operator=(Tournament&& that) {
    if (this != &that) {
        fight_list = std::move(that.fight_list);
        lost_list = std::move(that.lost_list);
    }
    return *this;
}

Tournament& Tournament::operator+=(const Knight& knight) {
    lost_list.clear();
    fight_list.push_back(knight);
    return *this;
}

Tournament& Tournament::operator-=(const Knight& knight) {
    lost_list.clear();
    fight_list.remove(knight);
    return *this;
}

const std::list<Knight>::iterator Tournament::play() {
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

const std::list<Knight>::iterator Tournament::no_winner() {
    return fight_list.end();
}

size_t Tournament::size() const {
    return fight_list.size() + lost_list.size();
    // chociażby dlatego lost_list nie jest typu forward_list
}

// MAX_DIFF_CLASSES

constexpr std::pair<int, int> max_diff_classes(std::initializer_list<Knight> list) {
    // TODO
    return {0, 0};
}