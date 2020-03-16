// ----------------- FLIP A COIN ----------------------//
#include<iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <math.h>

using namespace std;

// QUESTO PROGRAMMA SIMULA UN NUMERO N DI LANCI DI UNA MONETA, LEGGE
// I RISULTATI E DETERMINA IL MLE E LA STD SU DI ESSO
int N;
int H;
float bin;
int nbins;   // numero di bin per ottenere il grafico della likelihood
double MLE;    //Maximum Likelihood Estimator

float fattoriale (int a)
{
  if (a > 1)
   return a * fattoriale (a-1);
  else
   return 1;
}

double binomial(int N, int H){
  double NUM = 0;
  double DEN_1 = 0;
  double DEN_2 = 0;
  double bin;

  NUM = fattoriale(N);
  DEN_1 = fattoriale(H);
  DEN_2 = fattoriale(N-H);

  bin = NUM/(DEN_1*DEN_2);
  return bin;
}

double likelihood(int N, int H, int nbins){
  double like [nbins+1];
  double theta [nbins+1];
  double thetaML = 0;
  int i;

  ofstream outdata;
  outdata.open("likelihood.dat");

  if(!outdata){
    cerr << "Errore: impossibile aprire il file 'likelihood.dat'" << endl;
    exit(1);
  }

  theta[0] = 0;
  like[0] = binomial(N,H)*pow(theta[0],H)*pow(1.-theta[0],N-H);
  double delta = 0;
  delta = 1./nbins;
  cout << endl;
//  cout << "DELTA: " << delta;

  for(i=1; i<=nbins;i++){
    theta[i] = theta[i-1]+delta;
    like[i] = binomial(N,H)*pow(theta[i],H)*pow(1.-theta[i],N-H);
  }

  i = 0;
  for(i=0; i<=nbins; i++){
    outdata << theta[i] << " " << like[i] << endl;
  }
  outdata.close();

  // TROVO IL MLE

  i = 1;
  while (i<=nbins){
  if(like[i-1] < like[i] && like[i] > like[i+1]){
    thetaML = theta[i];
  }
  i++;
}
  return thetaML;
}


int main()
{
  cout << "Ciao!" << endl;
  cout << endl;
  cout << "Sono un programma che è in grado di determinare la probabilità di ottenere TESTA dato un numero N di lanci e un numero H di volte in cui è uscita testa." << endl;
  cout << endl;
  cout << "Quanti lanci hai eseguito?  ";
  cin >> N;
  cout << endl;
  cout << "Quante volte è uscito TESTA?  ";
  cin >> H;
// bin = binomial(N,H);
  cout << endl;
  cout << "Prima di eseguire il calcolo voglio calcolare la likelihood.." << endl;
  cout << endl;
  cout << "Quanti bin vuoi nell'asse x?";
  cin >> nbins;
  MLE = likelihood(N,H,nbins);
  cout << endl;
  cout << "Ho calcolato la likelihood, puoi vedere il grafico eseguendo il file python 'plotlike.py'." << endl;
  cout << endl;
  cout << "Ho trovato il Maximum Likelihood Estimator:  " << MLE << endl;
  cout << endl;
  cout << "E' quindi verosimile che la probabilità che uscisse testa fosse del:  " << MLE*100 << "%.";
  return 0;
}
