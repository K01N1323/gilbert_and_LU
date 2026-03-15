#ifndef SECONDFILE_H
#define SECONDFILE_H
class inverse_matrix_gilbert{
public:
    friend class matrixes;
    inverse_matrix_gilbert(double *, int);
    double * GetMatrix()const;
    double GetDet()const;
    void TakeReverse();
    ~inverse_matrix_gilbert();
private:
    int n;
    double *matrix;
    double *conmatrix;
    int det;
    int swaps;
    int neededrow(int skip)const;
    void swaprows( int);
    void divisionrow(int);
    void subtraction(int);
    void triangle();
    void obrat();
    void reverse();
    double GetElement(int, int)const;
};
#endif // secondfile
