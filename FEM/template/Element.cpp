#include"Element.h"

Element::Element(Node* node1, Node* node2, Node* node3){
	this->nodes[0] = node1;
	this->nodes[1] = node2;
	this->nodes[2] = node3;

	//MEMO::‚Æ‚è‚ ‚¦‚¸‚ÌŽÀ‘•
	std::vector<double> temp(6, 0);
	B_Matrix.push_back(temp);
	B_Matrix.push_back(temp);
	B_Matrix.push_back(temp);

	Stiffness_Matrix.push_back(temp);
	Stiffness_Matrix.push_back(temp);
	Stiffness_Matrix.push_back(temp);
	Stiffness_Matrix.push_back(temp);
	Stiffness_Matrix.push_back(temp);
	Stiffness_Matrix.push_back(temp);
}
Element::~Element(){}

void Element::Draw(){
	DrawTriangle((int)nodes[0]->Get_Pos().x, (int)nodes[0]->Get_Pos().y,
		(int)nodes[1]->Get_Pos().x, (int)nodes[1]->Get_Pos().y,
		(int)nodes[2]->Get_Pos().x, (int)nodes[2]->Get_Pos().y, WHITE, FALSE);
}

MyMath::Physics<double> Element::Get_Center(){
	MyMath::Physics<double> center_pos;
	for (int i = 0; i < 3; i++){
		center_pos.x += nodes[i]->Get_Pos().x;
		center_pos.y += nodes[i]->Get_Pos().y;
	}

	center_pos.x /= 3.0;
	center_pos.y /= 3.0;

	return center_pos;
}

void Element::Create_B_Matrix(){
	B_Matrix[0][0] = nodes[1]->Get_Pos().y - nodes[2]->Get_Pos().y;
	B_Matrix[0][1] = 0;
	B_Matrix[0][2] = nodes[2]->Get_Pos().y - nodes[0]->Get_Pos().y;
	B_Matrix[0][3] = 0;
	B_Matrix[0][4] = nodes[0]->Get_Pos().y - nodes[1]->Get_Pos().y;
	B_Matrix[0][5] = 0;

	B_Matrix[1][0] = 0;
	B_Matrix[1][1] = nodes[2]->Get_Pos().x - nodes[1]->Get_Pos().x;
	B_Matrix[1][2] = 0;
	B_Matrix[1][3] = nodes[0]->Get_Pos().x - nodes[2]->Get_Pos().x;
	B_Matrix[1][4] = 0;
	B_Matrix[1][5] = nodes[1]->Get_Pos().x - nodes[0]->Get_Pos().x;

	B_Matrix[2][0] = nodes[2]->Get_Pos().x - nodes[1]->Get_Pos().x;
	B_Matrix[2][1] = nodes[1]->Get_Pos().y - nodes[2]->Get_Pos().y;
	B_Matrix[2][2] = nodes[0]->Get_Pos().x - nodes[2]->Get_Pos().x;
	B_Matrix[2][3] = nodes[2]->Get_Pos().y - nodes[0]->Get_Pos().y;
	B_Matrix[2][4] = nodes[1]->Get_Pos().x - nodes[0]->Get_Pos().x;
	B_Matrix[2][5] = nodes[0]->Get_Pos().y - nodes[1]->Get_Pos().y;
}

void Element::Create_Stiffness_Matrix(std::vector< std::vector<double> > D_Matrix, std::vector< std::vector<double> > &stiffness_matrix){
	std::vector< std::vector<double> > temp_mat;
	Create_B_Matrix();

	for (unsigned int i = 0; i < B_Matrix[0].size(); i++){
		std::vector<double> temp_vec;
		for (unsigned int j = 0; j < B_Matrix.size(); j++){
			double temp_sum = 0;
			for (unsigned int k = 0; k < B_Matrix.size(); k++){
				temp_sum += B_Matrix[k][i] * D_Matrix[k][j];
			}
			temp_vec.push_back(temp_sum);
		}
		temp_mat.push_back(temp_vec);
	}

	double S = 0;

	S = 1 * (nodes[1]->Get_Pos().x*nodes[2]->Get_Pos().y -
		nodes[1]->Get_Pos().y*nodes[2]->Get_Pos().x) -
		nodes[0]->Get_Pos().x * (nodes[2]->Get_Pos().y - nodes[1]->Get_Pos().y) +
		nodes[0]->Get_Pos().y*(nodes[2]->Get_Pos().x - nodes[1]->Get_Pos().x);

	S /= 2.0;
	if (S < 0)S *= -1;

	//DrawFormatString(0, 300, WHITE,"%f", S);
	for (unsigned int i = 0; i < B_Matrix[0].size(); i++){
		for (unsigned int j = 0; j < B_Matrix[0].size(); j++){
			double temp_sum = 0;
			for (unsigned int k = 0; k < B_Matrix.size(); k++){
				temp_sum += temp_mat[i][k] * B_Matrix[k][j];
			}
			Stiffness_Matrix[i][j] = S*temp_sum;
		}
	}


	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			stiffness_matrix[2 * nodes[row]->Get_Index()][2 * nodes[col]->Get_Index()] += Stiffness_Matrix[2 * row][2 * col];
			stiffness_matrix[2 * nodes[row]->Get_Index()][2 * nodes[col]->Get_Index() + 1] += Stiffness_Matrix[2 * row][2 * col + 1];
			stiffness_matrix[2 * nodes[row]->Get_Index() + 1][2 * nodes[col]->Get_Index()] += Stiffness_Matrix[2 * row + 1][2 * col];
			stiffness_matrix[2 * nodes[row]->Get_Index() + 1][2 * nodes[col]->Get_Index() + 1] += Stiffness_Matrix[2 * row + 1][2 * col + 1];
		}
	}
}


/*
void Element::calc_u_vec(){
	std::vector<double> force_vec;
	for (int i = 0; i < 3; i++){
		force_vec.push_back(nodes[i]->Get_Force().x);
		force_vec.push_back(nodes[i]->Get_Force().y);
	}
	std::vector<double> u_vec = MyMath::Gauss_Method(force_vec, Stiffness_Matrix);

	for (int i = 0; i < 3; i++){
		MyMath::Physics<double> temp;
		temp.x = u_vec[2*i];
		temp.y = u_vec[2*i+1];
		nodes[i]->Set_U_Vec(temp);
	}
	
	int col = 0, row = 0;
	for (auto _col : B_Matrix){
		for (auto _row : _col){
			DrawFormatString(row * 110, col * 20, WHITE, "%f", _row);
			row++;
		}
		row = 0;
		col++;
	}

}*/