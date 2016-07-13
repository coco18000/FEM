#ifndef _OBJECT
#define _OBJECT

#include"Element.h"

const double YOUNG = 0.005;
const double POISSON = 0.5;

class Object{
public:
	Object(MyMath::Physics<double> left_top, MyMath::Physics<double> right_under);
	~Object();

	void Draw();
	void Move_Node(MyMath::Physics<int> mouse_pos);
	void Calc_U_Vec();
private:
	std::vector<Element*> elements;
	std::vector<Node*> nodes;

	//MEMO::‚Æ‚è‚ ‚¦‚¸‚ÌŽÀ‘•
	std::vector< std::vector<double> > D_Matrix;

	void Create_D_Martix(double young, double poisson);
	void Create_Stiffness_Matrix();

	std::vector< std::vector<double> > stiffness_matrix;
};
#endif