// Fib2.cpp : Defines the entry point for the console application.
//
// Author: Hal O'Connell
// Feb. 2017
// Sample application for PROG 2400
// Bad use of recursion


#include <ctime>
#include <iostream>
#include <conio.h>

using namespace std;
// #define DEBUG
unsigned long num_calls; // "global" to count the recursive calls, bad practice, but this is a demo

unsigned long fibonacciI(int n)
/*    fibonacci: iterative version
Pre:  The parameter n is a nonnegative integer.
Post: The function returns the nth Fibonacci number.
*/
{
	unsigned long last_but_one;   //  second previous Fibonacci number, F_i-2
	unsigned long last_value;     //  previous Fibonacci number, F_i-1
	unsigned long current;        //  current Fibonacci number F_i
	if (n <= 0) return 0;
	else if (n == 1) return 1;
	else {
		last_but_one = 0;
		last_value = 1;
		for (int i = 2; i <= n; i++) {
			current = last_but_one + last_value;
			last_but_one = last_value;
			last_value = current;
		}
#ifdef DEBUG
		cout << n << " iterations made." << endl;
#endif

		return current;
	}
}


unsigned long fibonacciR(int n)
/*    fibonacci: recursive version
Pre:  The parameter n is a nonnegative integer.
Post: The function returns the nth Fibonacci number.
*/
{
#ifdef DEBUG
	cout << "Recursive call made. Value: " << n << endl;
#endif
	num_calls++;
	if (n <= 0)  return 0;
	else if (n == 1)  return 1;
	else              return fibonacciR(n - 1) + fibonacciR(n - 2);
}

int main(int argc, char** argv) {
	unsigned long result;
	int target;
	cout << "Enter the ordinal value of the Fibonacci number desired: ";
	cin >> target;
	cout << "Performing iterative calculation" << endl;

	clock_t begin_nonrecursive = clock();

	result = fibonacciI(target);

	clock_t end_nonrecursive = clock();
	double elapsed_secs_non = double(end_nonrecursive - begin_nonrecursive) / CLOCKS_PER_SEC;
	cout << endl;
	cout << "Elapsed time to calculate " << result << ", iterative: " << elapsed_secs_non << endl;

	num_calls = 0;
	// now recursive version
	cout << "Performing recursive calculation" << endl;


	clock_t begin_recursive = clock();

	result = fibonacciR(target);

	clock_t end_recursive = clock();
	double elapsed_secs_rec = double(end_recursive - begin_recursive) / CLOCKS_PER_SEC;
	cout << endl;
	cout << "Elapsed time to calculate " << result << ", recursive: " << elapsed_secs_rec << endl;
	cout << "Total recursive calls: " << num_calls << endl;
	_getch();
	return 0;

}

