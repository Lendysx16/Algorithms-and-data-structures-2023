
#ifndef TASK3_MY_PAIR_H
#define TASK3_MY_PAIR_H
namespace my {
    template<class X, class Y>
    class pair {
        X el1;
        Y el2;
    public:
        pair(X el1_, Y el2_) : el1(el1_), el2(el2_) {};

        pair() = default;

        ~pair() = default;
        X const &fst_el() {return el1;}
        Y const &snd_el() {return el2;}
        friend bool operator<(const pair &fst, const pair &scnd) {
            return fst.el2 < scnd.el2;
        };
    };
}
#endif //TASK3_MY_PAIR_H
