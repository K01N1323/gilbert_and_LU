#ifndef SECONDFILE_H
#define SECONDFILE_H
class gauss_method {
public:
  friend class matrixes;
  gauss_method(double *, int);
  double *GetMatrix() const;
  double GetDet() const;
  void TakeReverse();
  ~gauss_method();
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
#endif // secondfile
