#ifndef CRTP_SHAPE_HPP
#define CRTP_SHAPE_HPP

template<typename Impl>
class Shape {
  Impl& impl() { return static_cast<Impl&>(*this); }
public:
  void draw() const { impl().draw(); }
};

#endif