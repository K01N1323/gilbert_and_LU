#ifndef MATRIXES_H
#define MATRIXES_H
class matrixes{
public:
    matrixes(int, int);
    matrixes(double*, int, int);
    double* Get(int)const;
    double* GetMatrix()const;
    double GetDet()const;
    double* GetInverseMatrix()const;
    void MakeGilbert();
    void MakeOnes();
    const matrixes operator+(const matrixes &rv)const;
    const matrixes operator-(const matrixes &rv)const;
    const matrixes operator*(const matrixes &rv)const;
    ~matrixes();
private:
    int rows;
    int cols;
    double *matrix;
    const double SubstrRowCol(const matrixes &rv, int, int)const;
};
#endif // matrixes_h