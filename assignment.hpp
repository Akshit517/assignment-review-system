#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Assignment{
    private:
        std::string title;
        std::map<int,std::string> tasks;
        std::string deadline;
    public : 
        //Assignment constructor/add a new assignment
        Assignment(std::string title, std::string deadline);
        Assignment(std::string , std::string , std::map<int,std::string> );
        //display assigment details 
        void display_assignment_details();
        //add a new task to assignment
        void add_task(std::string);
        //delete a task
        void delete_task();
        //change deadline
        void change_deadline();

        std::string get_title() const;
        
        std::string get_deadline() const;

        std::string get_task(int index) const;

        std::map<int,std::string> get_all_tasks() const;
};
#endif
