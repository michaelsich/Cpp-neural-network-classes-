// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#define DEFAULT_CTOR_SIZE 1
#define ACTIVE_THRESHOLD  0.1
#define DISABLED_PXL      "  "
#define ENABLED_PXL       "**"
#define ERR_INVALID_SIZE            "Error: matrix size invalid"
#define ERR_INVALID_ADDITION        "Error: cannot add matrices of diff sizes"
#define ERR_INVALID_MULTIPLICATION  "Error: cannot X matrices "
#define ERR_INVALID_INDEX           "Error: invalid index"
#define ERR_INVALID_FILE            "Error: file is invalid"


#include <iostream>
#include <fstream>
using std::string;

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

class Matrix
{
    public:
        Matrix();
        Matrix(int rows, int cols);
        Matrix(const Matrix& m);
        ~Matrix() { delete [] matrix; }

        inline int getRows() const {return this->matrixData.rows;}
        inline int getCols() const {return this->matrixData.cols;}

        Matrix& vectorize();
        void    plainPrint() const;

        Matrix& operator=   (const Matrix& rhs);
        Matrix& operator+=  (const Matrix& rhs);
        Matrix  operator+   (const Matrix& rhs)  const;
        Matrix  operator*   (const Matrix& rhs)  const;
        Matrix  operator*   (float scalar)       const;
        float   operator()  (int i, int j)       const;

        inline float   operator[] (int i) const {return matrix[i];}
        //TODO: probably can delete
        inline float&  operator[] (int i)       {return this->matrix[i];}

        friend Matrix           operator* (float scalar, const Matrix& mtx);
        friend std::ostream&    operator<< (std::ostream& oStream, const Matrix& mtx);
        friend std::ifstream&   operator>> (std::ifstream& iStream, Matrix& mtx);

private:
        MatrixDims matrixData{};
        float* matrix;
};






#endif //MATRIX_H
