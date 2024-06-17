#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "student_accessor.hpp"
#include "reviewer_accessor.hpp"

class Iteration {
private:
    std::map<std::string, std::vector<int>> _iterationRequest;

    StudentAccessor _studentAccessor;
    ReviewerAccessor _reviewerAccessor; 
    friend class ReviewerAccessor;
    friend class Reviewer;
    friend class Student;
    friend class StudentAccessor;

public:
    Iteration(); 
};
