#ifndef DEFAULT_GAUSS_H
#define DEFAULT_GAUSS_H
class default_gauss {
  public:
    friend class matrixes;
    default_gauss(double *, int);
    double *GetMatrix() const;
    double GetDet() const;
    void TakeReverse();
    ~default_gauss();
    double *Solve(double *b);
    void SolveForTests(double *b);

  private:
    int n;
    double *matrix;
    double *conmatrix;
    int det;
    int swaps;
    int neededrow(int skip) const;
    void swaprows(int);
    void divisionrow(int);
    void subtraction(int);
    void triangle();
    void obrat();
    void reverse();
    double GetElement(int, int) const;
};
#endif // default gauss h