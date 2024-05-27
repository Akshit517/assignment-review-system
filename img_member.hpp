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
        //constructor
        Img_member(std::string name ,int enrollno, std::string role, std::string password);

        //display img_member's details
        void display_details();

        //update details of img_member
        void update_details();

        std::string get_name() const ;
        int get_enrollno() const;
        std::string get_role() const ;
        std::string get_password() const ;
};
#endif
