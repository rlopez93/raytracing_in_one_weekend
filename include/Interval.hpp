#pragma once

class Interval
{
  public:
    double min_;
    double max_;

    Interval();

    Interval(
        double min,
        double max);

    auto size() const -> double;

    auto contains(double x) const -> bool;

    auto surrounds(double x) const -> bool;

    static Interval const Empty;
    static Interval const Universe;
};
