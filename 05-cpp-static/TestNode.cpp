#include "TestNode.hpp"

TestNode::TestNode(){
std::cout <<"Const TestNode"<<std::endl;
}

TestNode::~TestNode(){
std::cout <<"Dest TestNode"<<std::endl;
}

std::string TestNode::getName(){
return "OLLI";
}




