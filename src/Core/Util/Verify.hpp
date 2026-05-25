#pragma once

#include <exception>

#define SW_CORE_FAIL_COND_MSG(cond, message) if ((cond)) { throw std::runtime_error(message); }
#define SW_CORE_FAIL_COND(cond) SW_CORE_FAIL_COND_MSG((cond), "condition " #cond " failed")
#define SW_CORE_FAIL_NULL(arg) SW_CORE_FAIL_COND((arg) == nullptr)

#define SW_CORE_VERIFY(cond) SW_CORE_FAIL_COND((!(cond)))
#define SW_CORE_VERIFY_MSG(cond, message) SW_CORE_FAIL_COND_MSG((!(cond)), message)