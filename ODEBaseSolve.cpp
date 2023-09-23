#include "ODEBaseSolve.h"

ODEBaseSolve::ODEBaseSolve() : f(0), U0(0), T(0), n(0) {}

ODEBaseSolve::ODEBaseSolve(func_ptr f, double U0, double T, int n)
{
	this->f = f;
	this->U0 = U0;
	this->T = T;
	this->n = n;

	dt = T / n;
	t = vector<double>(n + 1);
	u = vector<double>(n + 1);

	t[0] = 0.0;
	for (int i = 0; i < n; i++) t[i + 1] = t[i] + dt;
}

void ODEBaseSolve::solve()
{
	u[0] = U0; // initial condition
	for (int k = 1; k <= n; k++) 
	{
		u[k] = advance(k - 1);
	}
}


vector<double> ODEBaseSolve::get_t() const
{
	return t;
}

vector<double> ODEBaseSolve::get_u() const
{
	return u;
}


EulerSolve::EulerSolve() : ODEBaseSolve() {}

EulerSolve::EulerSolve(func_ptr f, double U0, double T, int n) : ODEBaseSolve(f, U0, T, n)
{

}


double EulerSolve::advance(int k) const
{
	return u[k] + dt * f(u[k], t[k]);
}

RungeKuttaSolve::RungeKuttaSolve() : ODEBaseSolve() {}

RungeKuttaSolve::RungeKuttaSolve(func_ptr f, double U0, double T, int n) : ODEBaseSolve(f, U0, T, n)
{

}

double RungeKuttaSolve::advance(int k) const
{
	double K1, K2, K3, K4;

	K1 = dt * f(u[k], t[k]);
	K2 = dt * f(u[k] + 0.5*K1, t[k] + 0.5*dt);
	K3 = dt * f(u[k] + 0.5*K2, t[k] + 0.5*dt);
	K4 = dt * f(u[k] + K3, t[k] + dt);
	return u[k] + (1.0 / 6.0)* (K1 + 2 * K2 + 2 * K3 + K4);
}