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

     unsigned int FPapillon::ret_int(unsigned int my_integer, unsigned int size)
     {
        unsigned int output = my_integer%2;
        for(unsigned int i=0; i< size; i++)
        {
            output <<= 1;
            my_integer >>= 1;
            output += my_integer%2;
        }
        return output;
     }

    void FPapillon::setFPapillon1D(unsigned int num, bool colonne)
    {
    	//Descente
    	std::vector<std::complex<double> > v_temp = std::vector<std::complex<double> >(_n_size);

        //On calcule le nb de bits utiles de _n_size
        unsigned int nb_bits_utiles = 0;
        unsigned int temp = _n_size;
        while(temp !=0)
        {
            temp >>=1;
            nb_bits_utiles++;
        }

        //On ordonne les elements du tableau a l'aide de ret_int
    	for(unsigned int i=0; i<_n_size; i++)
    	{

            unsigned int ret = ret_int(i, nb_bits_utiles);
    		//On place le contraire booleen de la valeur
    		if(!colonne)
                v_temp[ret] = getPixel(num, i);
    		else
                v_temp[ret] = getPixel(i, num);
        }

        unsigned int pas = 2;
        while(pas != _n_size)
        {
            unsigned int curseur = 0;
            while(curseur < _n_size)
            {
                for(unsigned int j=curseur; j<curseur + pas/2; j++)
                {
                    std::complex<double> smp = v_temp[j];
                    std::complex<double> smic = v_temp[j+pas/2]*std::polar(1., (double)(j%pas)/pas);

                    v_temp[j] = (double)pas*smp + (double)pas*smic;
                    v_temp[j+pas/2] = (double)pas*smp - (double)pas*smic;
                }
                curseur += pas;
            }


            pas *= pas;
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
