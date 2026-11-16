/* PROGRAM BackSubstitution text Chap 4 with data */
#define N 10
ARCHITECTURE LINE(N+1);
#include <stdlib.h>
#define TRC 0
float stream pipechan[N+1];
void PipeProcess(value float A[N+1], value float B, float *rtn)
{
  /*Solves Equation i to compute x[i]*/
  int j;
  float sum = 0.0, xvalue = 0.0, cx = 0.0;
  int i = self;
  /*
  */
  if (i == TRC)
    cout << i << " receives ";
  sum = 0;
  for (j = 1; j <= i-1; j++) {
    recv(pipechan[i], xvalue); /*Read x[j] from left*/
    if (i < N)
      send(pipechan[i+1], xvalue); /*Send x[j] to right*/
    sum = sum + A[j] * xvalue;
    /*
    */
    if (i == TRC)
      cout << xvalue;
  }
  /*
  */
  if (i == TRC)
    cout << endl;
  cx = (B - sum) / A[i]; /*Compute x[i]*/
  if (i < N)
    send(pipechan[i+1], cx); /*Send x[i] to right*/
  /*
  */
  if (i == TRC)
    cout << i << " returns " << cx << endl;
  *rtn = cx; /* return the value of this process's unknown */
}
int updown(int ix, int kn)
{
  return kn - abs((ix - 1) % (2 * kn - 2) - (kn - 1));
}
#define NN 5
void genArrays(float *aa, float *bb, int d1, int d2) {
  int i, j, r;
  float *unk;
  float b, s;
  unk = fmalloc(d2);
  *unk = 0.0;
  b = -2.5;
  /* ascending descending sequence, 1 to NN to 1 to NN etc */
  for (i = 1; i < d2; ++i)
  {
    *(unk + i) = b + updown(i, NN);
    /*
    cout << *(unk + i);
    */
  }
  /*
  cout << endl;
  Initialize array values */
  for (j = 0; j < d2; ++j)
  {
    *(aa + j) = 0.0;
  }
  b = -3.5;
  for (i = 1; i < d1; ++i)
  {
    r = i * d2;
    *(aa + r) = *bb = s = 0.0;
    for (j = 1; j <= i; ++j)
    {
      *(aa + r + j) = b + updown(r + j, NN + 6);
      s = s + *(unk + j) * *(aa + r + j);
    }
    *(bb + i) = s;
    for (j = i + 1; j < d2; ++j)
      *(aa + r + j) = 0.0;
  }
  cout.precision(4);
  /*
  cout << "Equations" << endl;
  for (i = 0; i < d1; ++i)
  {
    r = i * d2;
    for (j = 0; j < d2; ++j)
    {
      cout << " " << *(aa + r + j);
    }
    cout << " = " << *(bb + i);
    cout << endl;
  }
  */
  cout << "Unknowns" << endl;
  for (i = 0; i < d2; ++i)
  {
    cout << " " << *(unk + i);
  }
  cout << endl;
  /*
  */
  free(unk);
}
int main( )
{
  float A[N+1][N+1];
  float B[N+1];
  float x[N+1];
  int i, j;
  float s;
  /*Initialize arrays A and B*/
  cout.precision(2);
  cout << "main start" << endl;
  genArrays(A, B, N+1, N+1);
  /*Create pipeline processes*/
  /*
  forall i = 1 to N @i do
    PipeProcess(A[i], B[i], &x[i]);
  */
  for (i =1; i<= N; i++) {
   j = i;
   fork [i] (@j)
    PipeProcess(A[j], B[j], &x[j]);
    /*PipeProcess(A[i], B[i], &x[i]);*/
  }
 for (i =1; i<= N; i++)
   join;

  cout << "solve" << endl;
  for (j = 1; j <= N; ++j) {
    if (j < 10)
      cout << ' ';
    cout.width(1);
    cout << "x" << j << " = ";
    cout << x[j] << endl;
  }
  cout << endl;
  cout << "verify" << endl;
  for (i = 1; i <= N; ++i)
  {
    s = 0.0;
    for (j = 1; j <= N; ++j)
    {
      s += x[j] * A[i][j];
    }
    cout << s;
    cout << " = " << B[i] << endl;
  }
  cout << "main end" << endl;
  /*
  */
}