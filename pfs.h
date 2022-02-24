#pragma once
#pragma warning(suppress : 4996)
#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<stdlib.h>
#include <iostream>

using namespace std;

typedef struct tVertex {
	int ix, iy;
	double zG, zRim, hDist;
	int qi;
	struct tVertex* next;
}pVertex;

void readzgrid(char infile[]);

void initHorizOffsets();

void initializeOkPit();

void printpit(int y, int x, FILE* out);

int pointIsPit(int y, int x, double** z);

bool higherPriority(pVertex* v1, pVertex* v2);

void upHeap(int k);

void downHeap(int k);

void PQinsert(pVertex* vOnTree, int x, int y, int d);

pVertex* PQremove();

void pqUpdate(pVertex* vOnTree);

void pqSearch(int y, int x);

void sortDownHeap(double** zi, int k, int high);

void heapSort(double** zi, int ni);//Ð¡¸ù¶Ñ

void fixinvalidpits(double** zi);

void scanGrid();


void getMemory();

void print();


int pfs();