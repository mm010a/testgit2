#include <iostream> // for cin, cout
#include <iomanip> // for the formatting functions setw, setprecision
#include <cmath> // for the exp function
#include "ODEBaseSolve.h"

int main()
{
	double U0;
	double T;
	int n;

	try {
		cout << "input initial condition\n";
		cin >> U0;
		cout << "input the range for T (0,T)\n";
		cin >> T;
		cout << "input the number of steps\n";
		cin >> n;
		// allocate the t and u arrays
		vector<double> t, u;
		
		vector<ODEBaseSolve*> vec(2);

		vec[0] = new EulerSolve(f, U0, T, n);
		vec[1] = new RungeKuttaSolve(f, U0, T, n);

		vec[0]->solve();
		vec[1]->solve();

		t = vec[1]->get_t();
		u = vec[1]->get_u();
		
		// output the results
		std::cout << "Solution to u’ = u, " << 0 << " <= t <= " << T << ", step size " <<
			T / n << "\n";
		std::cout << "*********************************************************\n";
		std::cout << "t " << std::setw(30) << "u(t)" << std::setw(20) << "exact_soln" <<
			std::setw(25) << "| u(t) - exact_soln |\n";
		std::cout << std::fixed << std::setprecision(7);
		for (int i = 0; i <= n; i++) {
			std::cout << t[i] << std::setw(25) << u[i] << std::setw(20) << exp(t[i]) <<
				std::setw(20) << fabs(u[i] - exp(t[i])) << "\n";
		}
		delete vec[0];
		delete vec[1];
	}
	catch (std::exception& e) {
		// Catching other errors
		std::cerr << "std::exception caught" << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
		std::cerr << "What: " << e.what() << std::endl;
	}
	
	return 0;
}

double f(double u, double t) // function f that is the right hand side of the ODE
{
	return u; // //
}
