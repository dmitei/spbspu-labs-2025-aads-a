#include "../common/container.hpp"
#include <stdexcept>

shabalin::Container::Container():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

shabalin::Container::Container(const Container & other):
  data_(nullptr),
  size_(other.size_),
  capacity_(other.capacity_)
{
  if (capacity_ > 0)
  {
    data_ = new std::string[capacity_];
    for (std::size_t i = 0; i < size_; ++i)
    {
      data_[i] = other.data_[i];
    }
  }
}

shabalin::Container & shabalin::Container::operator=(const Container & other)
{
  if (this != std::addressof(other))
  {
    clear();
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (capacity_ > 0)
    {
      data_ = new std::string[capacity_];
      for (std::size_t i = 0; i < size_; ++i)
      {
        data_[i] = other.data_[i];
      }
    }
  }
  return *this;
}

shabalin::Container::~Container()
{
  clear();
}

void shabalin::Container::push_back(const std::string & value)
{
  if (size_ == capacity_)
  {
    std::size_t new_capacity;
    if (capacity_ == 0)
    {
      new_capacity = 2;
    }
    else
    {
      new_capacity = capacity_ * 2;
    }
    reserve(new_capacity);
  }
  data_[size_++] = value;
}

std::string & shabalin::Container::operator[](std::size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Container index out of range\n");
  }
  return data_[index];
}

const std::string & shabalin::Container::operator[](std::size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Container index out of range\n");
  }
  return data_[index];
}

std::size_t shabalin::Container::size() const
{
  return size_;
}

bool shabalin::Container::empty() const
{
  return size_ == 0;
}

void shabalin::Container::reserve(std::size_t new_cap)
{
  if (new_cap <= capacity_)
  {
    return;
  }
  std::string * new_data = new std::string[new_cap];
  for (std::size_t i = 0; i < size_; ++i)
  {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_cap;
}

void shabalin::Container::clear()
{
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}
