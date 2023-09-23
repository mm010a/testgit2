#pragma once
#include <vector>

typedef double (* func_ptr)(double u, double t);
double f(double u, double t);
using namespace std;


// abstract base class
class ODEBaseSolve {
protected:
	func_ptr f; // function f(u, t)
	double U0; // initial condition
	double T; // time interval(0, T)
	int n; // number of time steps
	vector<double> t; // time steps vector
	vector<double> u; // solution values vector
	double dt; // time step
public:
	ODEBaseSolve();
	ODEBaseSolve(func_ptr f, double U0, double T, int n);
	virtual double advance(int k) const = 0; // Advance sol one time step.
	void solve();
	vector<double> get_t() const;
	vector<double> get_u() const;
};

class EulerSolve : public ODEBaseSolve {
public:
	EulerSolve();
	EulerSolve(func_ptr f, double U0, double T, int n);
	virtual double advance(int k) const;
};


class RungeKuttaSolve : public ODEBaseSolve {
public:
	RungeKuttaSolve();
	RungeKuttaSolve(func_ptr f, double U0, double T, int n);
	virtual double advance(int k) const;
};



