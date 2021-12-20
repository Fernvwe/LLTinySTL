#ifndef __LL_NUMERIC_H__
#define __LL_NUMERIC_H__

namespace LL {

template <class InputIt, class T>
T accumulate(InputIt fir, InputIt last, T init) {
    for (; fir != last; ++fir) init = *fir + init;
    return init;
}

template <class InputIt, class T, class BinaryOperation>
T accumulate(InputIt fir, InputIt last, T init, BinaryOperation binary_op) {
    for (; fir != last; ++fir) init = binary_op(*fir, init);
    return init;
}
// 累计所有区间内前一个元素和后一个元素的差值,赋值给一个迭代器
template <class InputIt, class OutputIt>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt result) {
    if (first == last) return result;
    *result = *first;
    auto value = *first;
    while (++first != last) {
        auto tmp = *first;
        *(++result) = tmp - value;
        value = tmp;
    }
    return ++result;
}
template <class InputIt, class OutputIt, class BinaryOperation>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt result,
                             BinaryOperation binary_op) {
    if (first == last) return result;
    *result = *first;
    auto value = *first;
    while (++first != last) {
        auto tmp = *first;
        *(++result) = banary_op(tmp, value);
        value = tmp;
    }
    return ++result;
}
/*****************************************************************************************/
// inner_product
// 版本1：以 init 为初值，计算两个区间的内积   
// 版本2：自定义 operator+ 和 operator*
/*****************************************************************************************/
// 版本1
template <class InputIter1, class InputIter2, class T>
T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init)
{
  for (; first1 != last1; ++first1, ++first2)
  {
    init = init + (*first1 * *first2);
  }
  return init;
}

// 版本2
template <class InputIter1, class InputIter2, class T, class BinaryOp1, class BinaryOp2>
T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init,
                BinaryOp1 binary_op1, BinaryOp2 binary_op2)
{
  for (; first1 != last1; ++first1, ++first2)
  {
    init = binary_op1(init, binary_op2(*first1, *first2));
  }
  return init;
}

/*****************************************************************************************/
// iota
// 填充[first, last)，以 value 为初值开始递增
/*****************************************************************************************/
template <class ForwardIter, class T>
void iota(ForwardIter first, ForwardIter last, T value)
{
  while (first != last)
  {
    *first++ = value;
    ++value;
  }
}

/*****************************************************************************************/
// partial_sum
// 版本1：计算局部累计求和，结果保存到以 result 为起始的区间上
// 版本2：进行局部进行自定义二元操作
/*****************************************************************************************/
template <class InputIter, class OutputIter>
OutputIter partial_sum(InputIter first, InputIter last, OutputIter result)
{
  if (first == last)  return result;
  *result = *first;  // 记录第一个元素
  auto value = *first;
  while (++first != last)
  {
    value = value + *first;
    *++result = value;
  }
  return ++result;
}

// 版本2
template <class InputIter, class OutputIter, class BinaryOp>
OutputIter partial_sum(InputIter first, InputIter last, OutputIter result,
                       BinaryOp binary_op)
{
  if (first == last)  return result;
  *result = *first;  //记录第一个元素
  auto value = *first;
  while (++first != last)
  {
    value = binary_op(value, *first);
    *++result = value;
  }
  return ++result;
}

}  // namespace LL
#endif