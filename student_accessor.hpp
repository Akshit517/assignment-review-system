#pragma once

#include <iostream>
#include <string>

class Iteration;

class StudentAccessor {
private:
    Iteration& _parent;


    friend class Iteration;
    friend class Student;
    StudentAccessor(Iteration& parent);

    void add_to_iterationRequest(const std::string& assignmentName, int studentEnrollNo);

};
