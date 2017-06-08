#include<iostream>
#include<conio.h>
#include<math.h>
#include<time.h>

#include "BackTracking.h"
#include "BackTracking_FC.h"
#include "SimulatedAnnealing.h"
#include "BackTrack_VertexOrder.h"
#include "AC3.h"

using namespace std;

void main()
{
	const char *fname = "C:\\Users\\Varun Rajavelu\\Desktop\\Sudoku\\puzzle-5-easy.txt";
	clock_t startTime = clock();

	CallBackTrackingSolver(fname);
	//CallBackTracking_FCSolver(fname);
	//CallBacktracking_AC3(fname);
	//CallBackTrackingSolver_VertexOrder(fname);
	//CallSimulatedAnnealing_Solver(fname);


	clock_t endTime = clock();
	clock_t clockTicksTaken = endTime - startTime;
    double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
	cout<<"\nTime taken to solve the puzzle in seconds: "<< timeInSeconds<<'\n';
	getch();
}