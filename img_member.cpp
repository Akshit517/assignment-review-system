#include "img_member.hpp"

Img_member::Img_member(std::string name ,int enrollno, std::string role, std::string password){
    this->_name=name;
    this->_enrollno=enrollno;
    this->_role=role;
    this->_password=password;
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