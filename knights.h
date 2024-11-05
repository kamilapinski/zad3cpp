#ifndef KNIGHTS_H
#define KNIGHTS_H

class Knight {

};

class Tournament {
    public:
        Tournament(std::initializer_list<Knight> s);
        Tournament(const Tournament& that);
        Tournament(Tournament&& that);
        Tournament& operator=(const Tournament& that);
        Tournament& operator=(Tournament&& that);
};

#endif KNIGHT_H