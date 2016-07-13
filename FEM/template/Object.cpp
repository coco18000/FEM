#include"Object.h"

Object::Object(MyMath::Physics<double> left_top, MyMath::Physics<double> right_under){

	//create nodes
	double div_x_length = (right_under.x - left_top.x) / (double)(DIV_NUM);
	double div_y_length = (right_under.y - left_top.y) / (double)(DIV_NUM);
	int node_index = 0;
	for (int line = 0; line <= DIV_NUM; line++){
		double temp_y = left_top.y + div_y_length*line;
		for (int column = 0; column <= DIV_NUM; column++){
			double temp_x = left_top.y + div_x_length*column;
			MyMath::Physics<double> temp_pos;
			temp_pos.x = temp_x;
			temp_pos.y = temp_y;

			Node* temp_node = new Node(temp_pos, node_index);
			nodes.push_back(temp_node);
			node_index++;
		}
	}

	//create elements;
	for (int line = 0; line < DIV_NUM; line++){
		for (int column = 0; column < DIV_NUM; column++){
			//ã‚©‚çlineŒÂ–ÚA¶‚©‚çcolumnŒÂ–Ú‚ÌBox‚ð\¬‚·‚énode‚Í
			//nodes[(DIV_NUM+1)*line+column],nedes[(DIV_NUM+1)*(line+1)+column]
			//nodes[(DIV_NUM+1)*line+column+1],nedes[(DIV_NUM+1)*(line+1)+column+1]
			Element* temp_ele1 = new Element(	nodes[(DIV_NUM + 1)*line + column], 
												nodes[(DIV_NUM + 1)*line + column + 1],
												nodes[(DIV_NUM + 1)*(line + 1) + column]);
			elements.push_back(temp_ele1);
			Element* temp_ele2 = new Element(	nodes[(DIV_NUM + 1)*line + column + 1],
												nodes[(DIV_NUM + 1)*(line + 1) + column],
												nodes[(DIV_NUM + 1)*(line + 1) + column + 1]);
			elements.push_back(temp_ele2);
		}
	}

	//create D_matrix
	Create_D_Martix(YOUNG, POISSON);

	std::vector<double> temp(2*nodes.size(), 0);
	for (int i = 0; i < 2*nodes.size(); i++){
		stiffness_matrix.push_back(temp);
	}
}

Object::~Object(){
	for (auto _element : elements){
		delete _element;
	}
	elements.clear();

	for (auto _node : nodes){
		delete _node;
	}
	nodes.clear();
}

void Object::Draw(){
	int test = 1;
	for (auto _element : elements){
		_element->Draw();
		//DrawFormatString((int)_element->Get_Center().x, (int)_element->Get_Center().y, WHITE, "%d", test);
		test++;
	}
	for (auto _node : nodes){
		_node->Draw();
		_node->Move();

		MyMath::Physics<double> temp_pos = _node->Get_Pos();
		DrawCircle((int)temp_pos.x, (int)temp_pos.y, 2, RED);
	}
}

//MEMO::‚Æ‚è‚ ‚¦‚¸‚ÌŽÀ‘•
void Object::Move_Node(MyMath::Physics<int> mouse_pos){
	for (auto _node : nodes){
		if (pow(_node->Get_Pos().x - mouse_pos.x, 2) + pow(_node->Get_Pos().y - mouse_pos.y, 2) <= pow(MOUSE_RANGE, 2)){
			DrawCircle((int)_node->Get_Pos().x, (int)_node->Get_Pos().y, 4, GREEN);
			MyMath::Physics<double> force;
			force = (-1.0 * _node->Get_Pos()) + mouse_pos;
			force = force / 10.0;
			_node->Add_Force(force);
		}
	}
}

void Object::Create_D_Martix(double young, double poisson){
	if (!D_Matrix.empty())return;

	double temp = young / (1 - pow(poisson, 2));
	std::vector<double> row1, row2, row3;
	row1.push_back(temp);			row1.push_back(poisson*temp);	row1.push_back(0);
	row2.push_back(poisson*temp);	row2.push_back(temp);			row2.push_back(0);
	row3.push_back(0);				row3.push_back(0);				row3.push_back(temp*(1 - poisson) / 2);

	D_Matrix.push_back(row1);
	D_Matrix.push_back(row2);
	D_Matrix.push_back(row3);
}

void Object::Create_Stiffness_Matrix(){
	for (auto _row : stiffness_matrix){
		for (auto _col : _row){
			_col = 0;
		}
	}
	for (auto _element : elements){
		_element->Create_Stiffness_Matrix(D_Matrix,stiffness_matrix);
	}
}

void Object::Calc_U_Vec(){
	for (auto _node : nodes){
		MyMath::Physics<double> gravity;
		gravity.y = 0.98;
		_node->Add_Force(gravity);
	}

	Create_Stiffness_Matrix();

	std::vector<double> force_vec;
	for (auto _node : nodes){
		force_vec.push_back(_node->Get_Force().x);
		force_vec.push_back(_node->Get_Force().y);
	}

	std::vector<double> u_vec = MyMath::Gauss_Method(force_vec, stiffness_matrix);

	for (int i = 0; i < nodes.size(); i++){
		MyMath::Physics<double> temp;
		temp.x = u_vec[2 * i];
		temp.y = u_vec[2 * i + 1];
		nodes[i]->Set_U_Vec(temp);
	}
}