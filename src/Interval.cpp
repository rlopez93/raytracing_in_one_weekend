#include "Interval.hpp"
#include <algorithm>
#include <limits>

constexpr auto infinity = std::numeric_limits<double>::infinity();

Interval::Interval()
    : min_(+infinity),
      max_(-infinity)
{
}
Interval::Interval(
    double min,
    double max)
    : min_(min),
      max_(max)
{
}
auto Interval::size() const -> double
{
    return max_ - min_;
}
auto Interval::contains(double x) const -> bool
{
    return min_ <= x && x <= max_;
}
auto Interval::surrounds(double x) const -> bool
{
    return min_ < x && x < max_;
}
auto Interval::clamp(double x) const -> double
{
    return std::clamp(x, min_, max_);
}

Interval const Interval::Empty    = Interval(+infinity, -infinity);
Interval const Interval::Universe = Interval(-infinity, +infinity);
