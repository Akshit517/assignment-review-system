#include "student_accessor.hpp"
#include "iteration.hpp"

StudentAccessor::StudentAccessor(Iteration& parent)
    : _parent(parent) {
}

void StudentAccessor::add_to_iterationRequest(const std::string& assignmentName, int studentEnrollNo) {
    _parent._iterationRequest[assignmentName].push_back(studentEnrollNo);
    std::cout << "Added request to iteration " << std::endl;
}
