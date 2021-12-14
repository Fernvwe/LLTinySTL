#ifndef __LL_HASH_FUN_H__
#define __LL_HASH_FUN_H__
#include <stddef.h>

#include <type_traits>
namespace LL {

// 对于大部分类型，hash function 什么都不做
template <class Key>
struct hash {};

inline size_t hash_string(const char* s) {
    size_t hashcode = 0;
    for (; *s; ++s) {
        hashcode = 5 * hashcode + *s;
    }
    return hashcode;
}

template <>
struct hash<char*> {
    size_t operator()(const char* s) const { return hash_string(s); }
};
template <>
struct hash<const char*> {
    size_t operator()(const char* s) const { return hash_string(s); }
};
// 针对指针的偏特化版本
template <class T>
struct hash<T*> {
    size_t operator()(T* p) const noexcept { return static_cast<size_t>(p); }
};

// 对于整数类型，偏特化版本
template <>
struct hash<char> {
    size_t operator()(char __x) const { return __x; }
};

template <>
struct hash<unsigned char> {
    size_t operator()(unsigned char __x) const { return __x; }
};

template <>
struct hash<signed char> {
    size_t operator()(unsigned char __x) const { return __x; }
};

template <>
struct hash<short> {
    size_t operator()(short __x) const { return __x; }
};

template <>
struct hash<unsigned short> {
    size_t operator()(unsigned short __x) const { return __x; }
};

template <>
struct hash<int> {
    size_t operator()(int __x) const { return __x; }
};

template <>
struct hash<unsigned int> {
    size_t operator()(unsigned int __x) const { return __x; }
};

template <>
struct hash<long> {
    size_t operator()(long __x) const { return __x; }
};

template <>
struct hash<unsigned long> {
    size_t operator()(unsigned long __x) const { return __x; }
};
// 对于浮点数，逐位哈希
inline size_t bitwise_hash(const unsigned char* first, size_t count) {
#if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) && __SIZEOF_POINTER__ == 8)
    const size_t fnv_offset = 14695981039346656037ull;
    const size_t fnv_prime = 1099511628211ull;
#else
    const size_t fnv_offset = 2166136261u;
    const size_t fnv_prime = 16777619u;
#endif
    size_t result = fnv_offset;
    for (size_t i = 0; i < count; ++i) {
        result ^= (size_t)first[i];
        result *= fnv_prime;
    }
    return result;
}

template <>
struct hash<float> {
    size_t operator()(const float& val) {
        return val == 0.0f
                   ? 0
                   : bitwise_hash((const unsigned char*)&val, sizeof(float));
    }
};

template <>
struct hash<double> {
    size_t operator()(const double& val) {
        return val == 0.0f
                   ? 0
                   : bitwise_hash((const unsigned char*)&val, sizeof(double));
    }
};

template <>
struct hash<long double> {
    size_t operator()(const long double& val) {
        return val == 0.0f ? 0
                           : bitwise_hash((const unsigned char*)&val,
                                          sizeof(long double));
    }
};
}  // namespace LL
#endif