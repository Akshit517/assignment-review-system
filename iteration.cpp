#include "iteration.hpp"
#include "student_accessor.hpp"
#include "reviewer_accessor.hpp"

Iteration::Iteration()
    : _studentAccessor(*this), _reviewerAccessor(*this) {
}

