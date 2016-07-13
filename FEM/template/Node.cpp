#include"Node.h"

Node::Node(MyMath::Physics<double> grid, unsigned int index){
	this->pos = grid;
	this->index = index;
}

Node::~Node(){

}

MyMath::Physics<double> Node::Get_Pos(){
	return pos;
}
void Node::Draw(){
	DrawLine(pos.x, pos.y, pos.x + force.x, pos.y + force.y, RED);
}

void Node::Move(){
//	DrawFormatString(pos.x, pos.y, WHITE, "%f,%f", u_vec.x, u_vec.y);
	pos = pos + u_vec;
	u_vec.Zero();
	//pos = pos + (TIME_STEP*velocity) + (0.5*TIME_STEP*TIME_STEP / mass)*force;
	force.Zero();
}

void Node::Add_Force(MyMath::Physics<double> force){
	this->force = this->force + force;
}

void Node::Set_U_Vec(MyMath::Physics<double> vec){
	u_vec = u_vec + vec;
}

MyMath::Physics<double> Node::Get_Force(){
	return force;
}

const unsigned int Node::Get_Index(){
	return index;
}
