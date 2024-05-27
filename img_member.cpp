#include "img_member.hpp"

Img_member::Img_member(std::string name ,int enrollno, std::string role, std::string password){
    this->_name=name;
    this->_enrollno=enrollno;
    this->_role=role;
    this->_password=password;
}

//display img_member's details
void Img_member::display_details(){
    std::cout<<"NAME : "<<this->_name<<std::endl;
    std::cout<<"ENROLLMENT NO. : "<<this->_enrollno<<std::endl;
    std::cout<<"ROLE : "<<this->_role<<std::endl;
}

//update details of img_member
void Img_member::update_details(){
    std::cout<<"SELECT A DETAIL TO UPDATE:\n";
    std::cout<<"1. NAME \n2. ROLE .\n3. PASSWORD\n";
    int i;
    std::string new_detail;
    std::cin>>i;
    std::cout<<"Enter the new detail :"<<std::endl;
    std::cin>>new_detail;
    if (i==1){
        this->_name= new_detail;
    }else if (i==2) {
        this->_role=new_detail;   
    }else if (i==3) {
        this->_password=new_detail;   
    }else{
       std::cout<<"ENTER A VALID OPTION!\n"; 
    }
}
std::string Img_member::get_name() const {
    return this->_name;
}
int Img_member::get_enrollno() const {
    return this->_enrollno;
}
std::string Img_member::get_role() const {
    return this->_role;
}
std::string Img_member::get_password() const {
    return this->_password;
}
