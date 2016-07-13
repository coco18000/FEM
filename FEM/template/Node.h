#ifndef _NODE
#define _NODE

#include "MyMath.h"
#include "Base.h"

class Node{
public:
	Node(MyMath::Physics<double> grid,unsigned int index);
	~Node();

	void Draw();
	void Move();

	void Add_Force(MyMath::Physics<double> force);
	void Set_U_Vec(MyMath::Physics<double> vec);
	MyMath::Physics<double> Get_Pos();
	MyMath::Physics<double> Get_Force();

	const unsigned int Get_Index();

private:
	MyMath::Physics<double> pos;
	MyMath::Physics<double> force;
	MyMath::Physics<double> velocity;
	MyMath::Physics<double> u_vec;

	double mass = 1.0;
	unsigned int index;
};

#endif