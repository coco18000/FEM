#ifndef _MYMATH
#define _MYMATH

#include"Base.h"

namespace MyMath{
	template<typename T> struct Physics{
		T x = 0;
		T y = 0;

		void Zero(){ x = 0, y = 0; }
	};

	template<typename T1, typename T2>
	const Physics<T1> operator +(const Physics<T1> phys1, const Physics<T2> phys2){
		Physics<T1> temp;
		temp.x = phys1.x + phys2.x;
		temp.y = phys1.y + phys2.y;
		return temp;
	}

	template<typename T>
	const Physics<T> operator *(const T scalar, const Physics<T> phys){
		Physics<T> temp;
		temp.x = scalar*phys.x;
		temp.y = scalar*phys.y;
		return temp;
	}

	template<typename T>
	const Physics<T> operator /(const Physics<T> phys, const T scalar){
		Physics<T> temp;
		if (scalar==0)return temp;
		temp.x = phys.x/scalar;
		temp.y = phys.y/scalar;
		return temp;
	}

	//template<class T>
	std::vector<double> Gauss_Method(std::vector<double> vec, std::vector< std::vector<double> > mat);
}



#endif