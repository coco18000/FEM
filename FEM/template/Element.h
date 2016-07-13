#ifndef _ELEMENT
#define _ELEMENT

#include "Node.h"

class Element{
public:
	Element(Node* node1, Node* node2, Node* node3);
	~Element();

	void Draw();
	MyMath::Physics<double> Get_Center();

	void Create_Stiffness_Matrix(std::vector< std::vector<double> > D_Matrix, std::vector< std::vector<double> > &stiffness_matrix);
	//void calc_u_vec();
private:
	Node* nodes[3];
	std::vector< std::vector<double> > B_Matrix;
	std::vector< std::vector<double> > Stiffness_Matrix;
	void Create_B_Matrix();
};

#endif