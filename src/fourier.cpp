#include "fourier.h"
#include <complex>

Fourier::Fourier()
{
	v_complex_fourier = std::vector<std::complex<double> >();
}

Fourier::Fourier(const Contour& c)
{
	v_complex_fourier = std::vector<std::complex<double> >();
	setFourier(c);
}

const std::complex<double>& Fourier::getValeur(int i)
{
	return v_complex_fourier[i];
}

int Fourier::getTaille() const
{
	return v_complex_fourier.size();
}

void Fourier::setFourier(const Contour& c)
{
	std::vector<std::complex<double> > vec_circle;
	unsigned int N = c.getTaille();
	for(unsigned int i = 0; i < N; i++)
	{
		vec_circle.push_back(std::polar(1., -2*M_PI*i/N));
		//std::cout  << "CIRCLE : " << vec_circle[i] << std::endl;
	}

	v_complex_fourier.resize(N);

	for(unsigned int i = 0; i < N; i++)
	{
		std::complex<double> c_sum = 0;
		for(unsigned int j = 0; j < N; j++)
		{
			c_sum += c.getValeur(j) * vec_circle[((i-N/2)*j + N*N)%N];
			//std::cout << c.getValeur(j) << std::endl;
		}
		v_complex_fourier[i] = c_sum / (double)N;
        std::cout << "FOURIER " << v_complex_fourier[i] << std::endl;
	}
}

void Fourier::invertFourier(Contour& c)
{
	std::vector<std::complex<double> > vec_circle;
	std::vector<std::complex<double> > v_comp;
	unsigned int N = v_complex_fourier.size();
	for(unsigned int i = 0; i < N; i++)
	{
		vec_circle.push_back(std::polar(1., 2*M_PI*i/N));
        //std::cout << vec_circle[i] << std::endl;
	}

	v_comp.resize(N);

	for(unsigned int i = 0; i < N; i++)
	{
		std::complex<double> c_sum = 0;
		for(unsigned int j = 0; j < N; j++)
		{
			c_sum += v_complex_fourier[j] * vec_circle[(i*(j-N/2) + N*N)%N];
		}
		v_comp[i] = c_sum;
	}
	c = Contour(v_comp);
}

void Fourier::to_double (std::vector<double>& v_pixels) const
{
	v_pixels.clear();
	for(std::vector<std::complex<double> >::const_iterator it = v_complex_fourier.begin();
	 	it != v_complex_fourier.end(); 
	 	it++
	 )
	{
		v_pixels.push_back(real(*it) + 200);
		v_pixels.push_back(imag(*it) + 200);
	}

}
