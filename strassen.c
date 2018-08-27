#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*creates matrix*/
float** CreateMatrix(int n){
  int i, j;
  int e = 1;
  float **matrix;
  float random, randomRounded;

  while(e < n || e == 1){
    e = e * 2;
  }

  matrix = (float **)malloc(e*sizeof(float*));

  for (i=0; i<e; ++i)
  {
    matrix[i]= (float *)malloc(e*sizeof(float));
    for(j = 0; j < e; j++){
      random = ((float)rand())/RAND_MAX;
      randomRounded = random * 100 / 100;
      /* randomRounded = roundf(random * 100)/100; */
      if(randomRounded > 5.0){
        randomRounded = randomRounded - 2;
      }
      if(i < n && j < n){
        matrix[i][j] = randomRounded;
      }
      else{
        matrix[i][j] = 0;
      }
    }
  }
  return matrix;
}

/*deallocate the memory*/
void Destroy(float** matrix, int n){
  /* while(n--) { */
  /* free(matrix[n]); */
  /* } */
  /* free(matrix); */
}

/*displays matrix*/
void DisplayMatrix(float** matrix, int n){
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      printf("%.2f\t", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

/*multiplication by standard method*/
void standardMultiplication(float** A, float** B, int n){
  int i, j, k;
  float sum = 0;
  float** result = (float **)malloc(n*sizeof(float*));
  for(i = 0; i < n; i++){
    result[i]= (float *)malloc(n*sizeof(float));
    for(j = 0; j < n; j++){
      sum = 0;
      for(k = 0; k < n; k++){
        sum = sum + (A[i][k] * B[k][j]);
      }
      result[i][j] = sum * 100 / 100;
      sum = 0;
    }
  }
  DisplayMatrix(result, n);
}


/*recursive method*/
float** customRecursiveStrassensMultFunction(int n, float** A, float** B){
  float** C;
  float m1, m2, m3, m4, m5, m6, m7;
  float **a11, **a12, **a21, **a22, **b11, **b12, **b21, **b22;

  /*base case for 2*2 matrix*/
  if(n == 2){
    C = CreateMatrix(2);
    m1= (A[0][0] + A[1][1])*(B[0][0]+B[1][1]);
    m2= (A[1][0]+A[1][1])*B[0][0];
    m3= A[0][0]*(B[0][1]-B[1][1]);
    m4= A[1][1]*(B[1][0]-B[0][0]);
    m5= (A[0][0]+A[0][1])*B[1][1];
    m6= (A[1][0]-A[0][0])*(B[0][0]+B[0][1]);
    m7= (A[0][1]-A[1][1])*(B[1][0]+B[1][1]);

    C[0][0] = (m1+m4-m5+m7)*100/100;
    C[0][1] = (m3+m5)*100/100;
    C[1][0] = (m2+m4)*100/100;
    C[1][1] = (m1-m2+m3+m6)*100/100;

    return C;
  }
  a11 = CreateMatrix(n/2);
  a12 = CreateMatrix(n/2);
  a21 = CreateMatrix(n/2);
  a22 = CreateMatrix(n/2);
  b11 = CreateMatrix(n/2);
  b12 = CreateMatrix(n/2);
  b21 = CreateMatrix(n/2);
  b22 = CreateMatrix(n/2);

  /*matrices for additions*/
  float** a11_22 = CreateMatrix(n/2);
  float** a21_22 = CreateMatrix(n/2);
  float** a11_12 = CreateMatrix(n/2);
  float** a21_11 = CreateMatrix(n/2);
  float** a12_22 = CreateMatrix(n/2);
  float** b11_22 = CreateMatrix(n/2);
  float** b12_22 = CreateMatrix(n/2);
  float** b21_11 = CreateMatrix(n/2);
  float** b11_12 = CreateMatrix(n/2);
  float** b21_22 = CreateMatrix(n/2);

  float** M1 = CreateMatrix(n/2);
  float** M2 = CreateMatrix(n/2);
  float** M3 = CreateMatrix(n/2);
  float** M4 = CreateMatrix(n/2);
  float** M5 = CreateMatrix(n/2);
  float** M6 = CreateMatrix(n/2);
  float** M7 = CreateMatrix(n/2);

  int i, j, k, l;
  /*to get A11*/
  for(i = 0; i < n/2; i++){
    for(j = 0; j < n/2; j++){
      a11[i][j] = A[i][j];
    }
  }
  /*to get A12*/
  for(i = 0; i < n/2; i++){
    for(j = n/2, k = 0; j < n; j++, k++){
      a12[i][k] = A[i][j];
    }
  }
  /*to get A21*/
  for(i = n/2, k = 0; i < n; i++, k++){
    for(j = 0; j < n/2; j++){
      a21[k][j] = A[i][j];
    }
  }
  /*to get A22*/
  for(i = n/2, k = 0; i < n; i++, k++){
    for(j = n/2, l = 0; j < n; j++, l++){
      a22[k][l] = A[i][j];
    }
  }

  /*to get B11*/
  for(i = 0; i < n/2; i++){
    for(j = 0; j < n/2; j++){
      b11[i][j] = B[i][j];
    }
  }
  /*to get B12*/
  for(i = 0; i < n/2; i++){
    for(j = n/2, k = 0; j < n; j++, k++){
      b12[i][k] = B[i][j];
    }
  }
  /*to get B21*/
  for(i = n/2, k = 0; i < n; i++, k++){
    for(j = 0; j < n/2; j++){
      b21[k][j] = B[i][j];
    }
  }
  /*to get B22*/
  for(i = n/2, k = 0; i < n; i++, k++){
    for(j = n/2, l = 0; j < n; j++, l++){
      b22[k][l] = B[i][j];
    }
  }

  /*to get additions*/
  for(i = 0; i < n/2; i++){
    for(j = 0; j < n/2; j++){
      a11_22[i][j] =  a11[i][j] + a22[i][j];
      a21_22[i][j] =  a21[i][j] + a22[i][j];
      a11_12[i][j] =  a11[i][j] + a12[i][j];
      a21_11[i][j] =  a21[i][j] - a11[i][j];
      a12_22[i][j] =  a12[i][j] - a22[i][j];
      b11_22[i][j] =  b11[i][j] + b22[i][j];
      b12_22[i][j] =  b12[i][j] - b22[i][j];
      b21_11[i][j] =  b21[i][j] - b11[i][j];
      b11_12[i][j] =  b11[i][j] + b12[i][j];
      b21_22[i][j] =  b21[i][j] + b22[i][j];
    }
  }
  /*recursive calls*/
  M1 = customRecursiveStrassensMultFunction(n/2, a11_22, b11_22);
  M2 = customRecursiveStrassensMultFunction(n/2, a21_22, b11);
  M3 = customRecursiveStrassensMultFunction(n/2, a11, b12_22);
  M4 = customRecursiveStrassensMultFunction(n/2, a22, b21_11);
  M5 = customRecursiveStrassensMultFunction(n/2, a11_12, b22);
  M6 = customRecursiveStrassensMultFunction(n/2, a21_11, b11_12);
  M7 = customRecursiveStrassensMultFunction(n/2, a12_22, b21_22);

  /*to get additions*/
  C = CreateMatrix(n);
  for(i = 0; i < n/2; i++){
    for(j = 0; j < n/2; j++){
      C[i][j] =  M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
    }
  }
  for(i = 0; i < n/2; i++){
    for(j = n/2, k = 0; j < n; j++, k++){
      C[i][j] =  M3[i][k] + M5[i][k];
    }
  }
  for(i = n/2, k = 0; i < n; i++, k++){
    for(j = 0; j < n/2; j++){
      C[i][j] =  M2[k][j] + M4[k][j];
    }
  }
  for(i = n/2, k = 0; i < n; i++, k++){
    for(j = n/2, l = 0; j < n; j++, l++){
      C[i][j] =  M1[k][l] + M3[k][l] - M2[k][l] + M6[k][l];
    }
  }
  return C;
}
/*multiplication by strassens method*/
void strassensMultiplication(float** A, float** B, int n){
  float** C;
  C = customRecursiveStrassensMultFunction(n, A, B);
  DisplayMatrix(C, n);
}

int main(int argc, char *argv[]){
  if(argc >= 2){
    srand((unsigned int)time(NULL));
    int n = atoi(argv[1]);
    int e = 1;
    float **A, **B;
    while(e < n || e == 1){
      e = e * 2;
    }
    A = CreateMatrix(n);
    B = CreateMatrix(n);
    printf("Matrix A:\n");
    DisplayMatrix(A, e);
    printf("Matrix B\n");
    DisplayMatrix(B, e);
    printf("\n\n\n");
    printf("Strassens Multiplication:\n");
    strassensMultiplication(A, B, e);
    printf("Standard Multiplication:\n");
    standardMultiplication(A, B, n);
    Destroy(A, n);
    Destroy(B, n);
  }
  else{
    printf("One input is required as command line argument.\n");
  }
  return 0;
}
