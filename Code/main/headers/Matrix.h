#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <math.h>

//Functions made exclusively for 3x3 matrices and 3x1 vectors, to be expanded for nxn and later nxm
void Matrix_zeromat(float A[][3]); //Creates a matrix of zeroes
void Matrix_zerovec(float x[3]); //Creates a vector of zeroes
void Matrix_eye(float A[][3]); //Creates the identity matrix
void Matrix_matvecmul(float A[][3], float x[3], float b[3]); //A*x=b
void Matrix_matmatmul(float A[][3], float B[][3], float C[][3]); //A*B=C
void Matrix_matmatadd(float A[][3], float B[][3], float C[][3]); //A+B=C
void Matrix_matmatsub(float A[][3], float B[][3], float C[][3]); //A-B=C
void Matrix_matscalmult(float A[][3], float k, float C[][3]); //k*A=C 
void Matrix_vecscalmult(float x[3], float y[3], float k); // y = k*x
float Matrix_vecdot(float a[3], float b[3]); //aTb
void Matrix_mat2colvecs(float R[][3], float r1[3], float r2[3], float r3[3]); //R => [r1 r2 r3]
void Matrix_colvecs2mat(float R[][3], float r1[3], float r2[3], float r3[3]); //[r1 r2 r3] => R
void Matrix_matnormalize(float R[][3]); //Re-orthogonalizes and normalizes R
void Matrix_vecvecadd(float a[3], float b[3], float c[3]); //c = a+b
void Matrix_vecvecsub(float a[3], float b[3], float c[3]); //c = a-b
void Matrix_vec2skew(float x[3], float S[][3]); //Skew(x) = S
void Matrix_matcopy(float A[][3], float B[][3]); //B = A
void Matrix_veccopy(float a[3], float b[3]); // b = a
void Matrix_transpose(float A[][3], float AT[][3]); //AT = A^T
float Matrix_vecnorm(float x[3]); //|x|
void Matrix_normalize(float x[3], float x_norm[3]); //x_norm = x/|x|
int Matrix_factorial(int k); //k!
void Matrix_expm(float A[][3], float eA[][3], int k); // exp(A) = I + A + A^2/2 +...+ A^k/k!
float Matrix_det(float A[][3]); //Determinant 
void Matrix_rotX(float t, float R[][3]);
void Matrix_rotY(float t, float R[][3]);
void Matrix_rotZ(float t, float R[][3]);
void Matrix_printscal(float a);
void Matrix_printvec(float v[3]);
void Matrix_printmat(float A[][3]);
void Matrix_printvec_comma_separated(float v[3]);

#endif
