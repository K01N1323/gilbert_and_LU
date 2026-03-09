#ifndef LU_DECOMPOZITION_H
#define LU_DECOMPOZITION_H
class LU_Decomposition {
public:
    LU_Decomposition(int n) : LU_Decomposition(nullptr, n) {}
    LU_Decomposition(double *matrix_data, int n);

    ~LU_Decomposition();

    double* GetL() const;
    double* GetU() const;
    
    int* GetP() const; 
    
    double GetDet() const;
private:
    int n;
    
    double *L; 
    double *U; 
    int *P;    
    int swaps; 

    int neededrow(int skip) const; 
  
    void swaprows(int step);

    void subtraction(int current);
    
    void decompose();
};
#endif // lu decompozition h