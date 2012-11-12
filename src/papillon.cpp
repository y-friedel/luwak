#include "papillon.h"
#include <complex>

    FPapillon::FPapillon()
    {
    	v_fpapillon = std::vector< std::complex<double> >();
    	_width = 0;
    	_height = 0;
    }

    FPapillon::FPapillon(const std::vector< std::complex<double> >& image, 
    						unsigned int width, 
    						unsigned int height)
    {
    	_width = width;
    	_height = height;

    	setFPapillon(image, width, height);
    }

    void FPapillon::setFPapillon(const std::vector< std::complex<double> >& image, 
    						unsigned int width, 
    						unsigned int height)
    {
    	unsigned int size_temp = std::max(width, height);
    	unsigned int pn_size = 0;

    	while(size_temp > std::pow(2,pn_size))
    	{
    		pn_size++;
    	}
    	v_fpapillon = std::vector< std::complex<double> >(std::pow(2, pn_size+1), std::complex<double>(0,0));
    	_n_size = sqrt(v_fpapillon.size());
    	for(unsigned int i=0; i<width; i++)
    	{
    		for(unsigned int j=0; j<height; j++)
    		{
    			setPixel(image[i + width*j], i, j);
    		}
    	}

    	for(unsigned int i=0; i<_n_size; i++)
    		setFPapillon1D(i);

    	for(unsigned int i=0; i<_n_size; i++)
    		setFPapillon1D(i, 1);
    }

    void FPapillon::setPixel(const std::complex<double>& value, int x, int y)
    {
    	v_fpapillon[x + _n_size*y] = value;
    }

    // unsigned int ret_int(unsigned int my_integer, int size)
    // {
    // 	unsigned int output;
    // 	bool temp;
    // 	for(int i=0; i< size; i++)
    // 	{
    // 		my_integer >> temp; 
    // 		temp >> output;
    // 	}
    // }

    void FPapillon::setFPapillon1D(unsigned int num, bool colonne)
    {
    	//Descente
    	std::vector<std::complex<double> > v_temp = std::vector<std::complex<double> >(_n_size);
    	unsigned int i_modif;
    	for(unsigned int i=0; i<_n_size; i++)
    	{

    		//On place le contraire booleen de la valeur
    		if(!colonne)
    			v_temp[i] = getPixel(num, i);
    		else
    			v_temp[i] = getPixel(i, num);
    	}
    }

    const std::complex<double>& FPapillon::getPixel(int x, int y)
    {
    	return v_fpapillon[x + y*_n_size];
    }

    unsigned int FPapillon::width() const
    {
    	return _width;
    }

    unsigned int FPapillon::height() const
    {
    	return _height;
    }

    unsigned int FPapillon::getNormalizedSize() const
    {
    	return _n_size;
    }

    void FPapillon::to_double_amplitude (std::vector<double>& v_pixels) const
    {

    }

    void FPapillon::to_double_phase (std::vector<double>& v_pixels) const
    {

    }