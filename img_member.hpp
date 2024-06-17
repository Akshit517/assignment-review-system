#ifndef IMGMEMBER_H
#define IMGMEMBER_H

#include <iostream>
#include <string>

class Img_member{
    protected:
        std::string _name;
        int _enrollno;
        std::string _role;
        std::string _password;
    public:
    
        Img_member(std::string name ,int enrollno, std::string role, std::string password);
        
        virtual void display_details() const = 0;

        std::string get_name() const ;
        int get_enrollno() const;
        std::string get_role() const ;
        std::string get_password() const ;
};
#endif