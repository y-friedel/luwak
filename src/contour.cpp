#include "contour.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <complex>


    Contour::Contour()
    {
    	v_complex = std::vector<std::complex<double> >();
    }

    Contour::Contour(const std::vector<double>& v_pts)
    {
    	v_complex = std::vector<std::complex<double> >();
    	for(unsigned int i = 0; i < v_pts.size()/2; i++)
    	{
    		v_complex.push_back(std::complex<double>(v_pts[2*i], v_pts[2*i+1]));
    	}
    }

    Contour::Contour(const std::vector<std::complex<double> >& _v_complex)
    {
        v_complex.resize(_v_complex.size());
        copy(_v_complex.begin(), _v_complex.end(), v_complex.begin());
    }

    Contour::Contour(const std::string filename)
    {
        //load(filename);
    }
    
    void Contour::ajout_point(const std::complex<double>& c)
    {
    	v_complex.push_back(c);
    }

    void Contour::ajout_point(double reel, double imag = 0.0)
    {
    	v_complex.push_back(std::complex<double>(reel, imag));
    }

    
    const std::complex<double>& Contour::getValeur(int i)
    {
    	return v_complex[i];
    }

    int Contour::getTaille() const
    {
    	return v_complex.size();
    }


    void Contour::load(const std::string filename)
    {
        std::cout << "load " << filename << std::endl;

        std::string buffer_string = ""; //Pour récupérer les donnees
        char* cfichier = (char*)filename.c_str();
        std::ifstream fichier(cfichier, std::ios::in);  // on ouvre en lecture

        unsigned int size;
        fichier >> size;


        if(fichier)  // si l'ouverture a fonctionné
        {        
            for(unsigned int i=0; i<size; i++)
            {   
                double x;
                double y;
                std::getline(fichier, buffer_string);
                fichier >> x;
                std::cout<<x;
                fichier >> y;
                std::cout <<" - "<<y<<std::endl;
                ajout_point(x, y);
            }
        }
        
        std::cout << "load OK" << std::endl;
    }

    void Contour::save(const std::string filename)
    {
        std::ofstream file;
        char* cfichier = (char*)filename.c_str();

        file.open(cfichier);

        file << v_complex.size() << std::endl;          

        for(std::vector< std::complex<double> >::iterator it = v_complex.begin(); it != v_complex.end(); it++)
        {
            file << real(*it) << " " << imag(*it) << std::endl;     
        }

        file.close();
    }

    void Contour::save(const std::vector<double>& vec_pts, const std::string filename)
    {
        std::ofstream file;
        char* cfichier = (char*)filename.c_str();

        file.open(cfichier);

        file << vec_pts.size()/2 << std::endl;          

        for(unsigned int i=0; i<vec_pts.size()/2; i++)
        {
            file << vec_pts[2*i] << " " << vec_pts[2*i+1] << std::endl;     
        }

        file.close();
    }

    void Contour::load(const std::string filename, std::vector<double>& v_pts)
    {
        std::cout << "load " << filename << std::endl;

        std::string buffer_string = ""; //Pour récupérer les donnees
        char* cfichier = (char*)filename.c_str();
        std::ifstream fichier(cfichier, std::ios::in);  // on ouvre en lecture

        unsigned int size;
        fichier >> size;

        v_pts.clear();
        if(fichier)  // si l'ouverture a fonctionné
        {        
            for(unsigned int i=0; i<size; i++)
            {   
                double x;
                double y;
                std::getline(fichier, buffer_string);
                fichier >> x;
                std::cout<<x;
                fichier >> y;
                std::cout <<" - "<< y <<std::endl;
                v_pts.push_back(x);
                v_pts.push_back(y);
            }
        }
        
        std::cout << "load OK" << std::endl;
    }