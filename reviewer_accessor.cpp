#include "reviewer_accessor.hpp"
#include "iteration.hpp"

ReviewerAccessor::ReviewerAccessor(Iteration& parent)
    : _parent(parent) {
}

void ReviewerAccessor::view_iteration_requests() const {
    std::cout << "Iteration requests by students:" << std::endl;
    for (const auto& it : _parent._iterationRequest) {
        std::cout << "Assignment: " << it.first << " Requests: ";
        for (const auto& requestId : it.second) {
            std::cout << requestId << " ";
        }
        std::cout << std::endl;
    }
}
