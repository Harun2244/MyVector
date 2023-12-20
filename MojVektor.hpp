#pragma once
#include <algorithm>
#include <exception>
#include <initializer_list>
#include <iterator>
template <typename T>
class MojVektor {
  public:
  class Iterator;
  MojVektor();
  MojVektor(const std::initializer_list<T>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();
  MojVektor& push_back(const T&);
  MojVektor& push_front(const T&);
  MojVektor& push_back(T&&);
  MojVektor& push_front(T&&);
  size_t size() const;
  T& at(size_t) const;
  T& operator[](size_t) const;
  void clear();
  void resize(size_t newSize, const T& difference_value);
  MojVektor& pop_back();
  MojVektor& pop_front();
  T& back() const;
  T& front() const;
  bool empty() const;
  size_t capacity() const;
  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  bool full() const;
std::string to_string() const;
  MojVektor subvector(Iterator begin, Iterator end);
  Iterator begin() const;
  Iterator end() const;
  Iterator find(const T&) const;
  Iterator erase(Iterator pos);
  Iterator insert(Iterator, const T&);
  Iterator insert(Iterator, T&&);
  Iterator rbegin() const;
  Iterator rend() const;
  Iterator erase(Iterator beginIt, Iterator endIt);
  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);
  T* data();
  

  private:
  void realoc();

  size_t capacity_;
  size_t size_;
  T* arr_;
};

template <typename T>
MojVektor<T>::MojVektor() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}

template <typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& vec)
    : capacity_{10}, size_{vec.size()}, arr_{new T[size_]} {
  std::copy(vec.begin(), vec.end(), arr_);
}

template <typename T>
MojVektor<T>::MojVektor(const MojVektor& other)
    : capacity_{other.capacity_}, size_{other.size_} {
  arr_ = new T[capacity_];
  for (size_t i = 0; i < size_; ++i) {
    arr_[i] = other.arr_[i];
  }
}

template <typename T>
MojVektor<T>::MojVektor(MojVektor&& other)
    : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_} {
  other.capacity_ = 0;
  other.size_ = 0;
  other.arr_ = nullptr;
}

template <typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& other) {
  if (this != &other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = other.arr_[i];
    }
  } else {
    throw std::logic_error{

        "Dodjeljivanje objekta samom sebi nije dozvoljeno!!"};
  }
  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = other.arr_;
  other.capacity_ = 0;
  other.size_ = 0;
  other.arr_ = nullptr;
  return *this;
}

template <typename T>
MojVektor<T>::~MojVektor() {
  delete[] arr_;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
size_t MojVektor<T>::size() const {
  return size_;
}

template <typename T>
T& MojVektor<T>::at(size_t other) const {
  if (other >= size_) {
    throw std::out_of_range{"Indeksiranje van granica!!"};
  } else
    return arr_[other];
}

template <typename T>
T& MojVektor<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range{"Prazan vektor!!"};
  }
  return arr_[size_ - 1];
}

template <typename T>
T& MojVektor<T>::front() const {
  if (size_ == 0) {
    throw std::out_of_range{"Prazan vektor!!"};
  }
  return arr_[0];
}

template <typename T>
bool MojVektor<T>::empty() const {
  return size_ == 0;
}

template <typename T>
bool MojVektor<T>::full() const {
  return size_ == capacity_;
}

template <typename T>
size_t MojVektor<T>::capacity() const {
  return capacity_;
}

template <typename T>
void MojVektor<T>::clear() {
  size_ = 0;
  capacity_ = 0;
  arr_ = nullptr;
}

template <typename T>
T& MojVektor<T>::operator[](size_t i) const {
  return arr_[i];
}

template <typename T>
void MojVektor<T>::realoc() {
  auto temp = new T[capacity_ * 2];
  for (size_t i = 0; i < size_; ++i) {
    temp[i] = arr_[i];
  }
  delete[] arr_;
  arr_ = temp;
  capacity_ = capacity_ * 2;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& element) {
  if (size_ < capacity_) {
    arr_[size_] = element;
    size_ = size_ + 1;
    return *this;
  } else {
    realoc();
    arr_[size_] = element;
    ++size_;
    return *this;
  }
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& element) {
  if (size_ == 0) {
    arr_[0] = element;
    ++size_;
    return *this;
  }

  else if(size_ == capacity_){
    auto temp = new T[capacity_ * 2]; 
    for (size_t i = 0; i < size_; ++i) {
      temp[i + 1] = arr_[i];
    }
    delete[] arr_;
    capacity_ *= 2;
    arr_ = temp;
    arr_[0] = element;
    ++size_;
    return *this;}

  else{ auto temp = new T[capacity_]; 
    for (size_t i = 0; i < size_; ++i) {
      temp[i + 1] = arr_[i];
    }
    delete[] arr_;
    arr_ = temp;
    arr_[0] = element;
    ++size_;
    return *this;}
  }


template <typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& element) {
  if (size_ == capacity_) {
    realoc();
  }
  arr_[size_] = element;
  ++size_;
  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& element) {
  if (size_ == 0) {
    arr_[0] = element;
    ++size_;
    return *this;
  } else if (size_ == capacity_) {
    auto temp = new T[capacity_ * 2];
    for (size_t i = 0; i < size_; ++i) {
      temp[i + 1] = arr_[i];
    }
    delete[] arr_;
    capacity_ = capacity_ *2;
    arr_ = temp;
    arr_[0] = element;
    ++size_;
    return *this;
}
else{ auto temp = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      temp[i + 1] = arr_[i];
    }
    delete[] arr_;
    arr_ = temp;
    arr_[0] = element;
    ++size_;
    return *this;}
}

template <typename T>
std::ostream& operator<<(std::ostream &out, const MojVektor<T> &vektor) {
  out<<"{";
  for (int i = 0; i < vektor.size(); i++) {
    if( i == vektor.size() - 1){
     out << vektor.at(i) <<"";}
    else{ out << vektor.at(i) <<", ";}
  }
  out<< "}";
return out;
}



template <typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value) {
  if (newSize < size_) {
    for (size_t i = 0; i < newSize - size_; ++i) {
      size_ -= 1;
    }
  }

  else if (newSize > size_) {
    auto tmep = size_;
    if (capacity_ - size_ < newSize - size_) {
      capacity_ = capacity_ + newSize;
    }  // ne znamo koliko je size blizu kapaciteta
    for (size_t i = 0; i < newSize - tmep; ++i) {
      arr_[size_] = difference_value;
      ++size_;
    }
  }
}

template <typename T>
MojVektor<T>& MojVektor<T>::pop_back() {
  if (size_ == 0 || size_ == 0) {
    throw std::out_of_range{"Nevalidna operacija!!"};
  }
  size_ -= 1;
}

template <typename T>
MojVektor<T>& MojVektor<T>::pop_front() {

if(size_ == 0){
throw std::out_of_range{"Nedovoljno elemenata u vektoru"};
}

else if (size_ == 1){
  --size_;
}

else{
  auto temp = new T[capacity_];
  for (size_t i = 1; i < size_; ++i) {
    temp[i-1] = arr_[(i-1) + 1];
  }
  delete[] arr_;
  size_ -= 1;
  arr_ = temp;}
}

template <typename T>
bool MojVektor<T>::operator==(const MojVektor& other) const {
  int brojac = 0;
  if (size_ == other.size_) {
    for (size_t i = 0; i < size_; ++i) {
      bool provjera = arr_[i] == other.arr_[i];
      if (provjera == false) ++brojac;
    }

    if (brojac == 0) {
      return true;
    } else
      return false;

  } else
    return false;
}

template <typename T>
bool MojVektor<T>::operator!=(const MojVektor& other) const {
  int brojac = 0;
  if (size_ == other.size_) {
    for (size_t i = 0; i < size_; ++i) {
      bool provjera = arr_[i] == other.arr_[i];
      if (provjera == false) ++brojac;
    }

    if (brojac == 0) {
      return true;
    } else
      return false;

  } else
    return false;
}

template <typename T>
class MojVektor<T>::Iterator
    : std::iterator<std::bidirectional_iterator_tag, T> {
  public:

 

Iterator() : ptr_{nullptr} {}

  Iterator(T* p) : ptr_{p} {}

  Iterator(const Iterator& other) : ptr_{other.ptr_} {}

  Iterator(Iterator&& other) : ptr_{other.ptr_} {
  other.ptr_ =nullptr;
  }

Iterator operator[](size_t num){

return Iterator(ptr_ + num);
}

  Iterator operator=(const Iterator& other){
  ptr_ = other.ptr_;
  return Iterator{ptr_};
  }

  Iterator operator=(Iterator&& other){
  ptr_ = other.ptr_;
    other.ptr_= nullptr;
  return Iterator{ptr_};
  }

  Iterator operator++() { return Iterator{++ptr_}; }

  Iterator operator--() { return Iterator{--ptr_}; }

  Iterator operator++(int) { return Iterator{ptr_++}; }

  Iterator operator--(int) { return Iterator{ptr_--}; }

  T& operator*() { return *ptr_; }

  T*& operator->(){
  return ptr_;
  }

  bool operator==(const Iterator& other) { return ptr_ == other.ptr_; }

  bool operator!=(const Iterator& other) { return ptr_ != other.ptr_; }
  
  Iterator operator+(int num) {
  return Iterator{ptr_ + num};
  }

Iterator operator-(int num) {
  return Iterator{ptr_ - num};
  }

size_t operator-(const Iterator& other){
return ptr_ - other.ptr_;
}

size_t operator+(const Iterator& other){
return ptr_ + other.ptr_;
}

bool operator>(const Iterator& other) {
return ptr_ > other.ptr_;
}

bool operator<(const Iterator& other) {
return ptr_ < other.ptr_;
}

bool operator>=(const Iterator& other) {
return ptr_ >= other.ptr_;
}

bool operator<=(const Iterator& other) {
return ptr_ <= other.ptr_;
}




  private:
  T* ptr_;
};

template <typename T>
T* MojVektor<T>::data() {
  return arr_;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::begin() const {
  return Iterator{arr_};
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::end() const {
  return Iterator{arr_ + size_};
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& num) const {
  T* ptr = arr_;
  T* ptr2 = arr_ + size_;
  while (ptr != ptr2) {
    if (*ptr == num) {
      return Iterator{ptr};
    }
    ++ptr;
  }
  return ptr;
}

template <typename T>
 MojVektor<T>  MojVektor<T>::subvector(Iterator begin, Iterator end){
 MojVektor vektor;
 while(begin != end){
 vektor.push_back(*begin);
 ++begin;
 }
 return vektor;}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt) {
auto temp = endIt;
for(size_t i = 0; i< temp-beginIt  ;++i ){
for(Iterator it = beginIt; it != end(); ++it){
*it = *(it + 1);
}
--size_;
--endIt;
}
return Iterator{endIt};
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos){
if(pos == end()){
return Iterator{end()};
}
for(auto it = pos; it!=end(); ++it){
*it = *(it + 1);
}
--size_;
return Iterator{pos};
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rbegin() const {
return Iterator{end() - 1};
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rend() const {
return Iterator{begin() - 1};
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator it, const T& num) {
  if(it < begin() || it > end()){throw std::out_of_range{"Nevalidan iterator!!"};}
Iterator last = end() - 1;
while(last != it -1){
*(last + 1) = *last;
--last;
}
*it = num;
++size_;
return it;
}


template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator it, T&& num) {
 if(it < begin() || it >= end()){throw std::out_of_range{"Nevalidan iterator!!"};}
Iterator last = end() - 1;
while(last != it -1){
*(last + 1) = *last;
--last;
}
*it = num;
++size_;
return it;
}

template <typename T>
void MojVektor<T>::rotate() {
  if(size_ == 0 || size_ ==1){throw std::out_of_range{"Nedovoljno elemenara za rotiranje!!"};}
  for(size_t i = 0; i<size_; ++i)
  std::rotate(arr_ + i, arr_ + size_ -1, arr_ + size_);
}


template <typename T>
void MojVektor<T>::rotate(Iterator beginIt, Iterator endIt) {
 if(size_ == 0 || size_ ==1){throw std::out_of_range{"Nedovoljno elemenara za rotiranje!!"};}
for (Iterator left = beginIt, right = endIt - 1; left < right; ++left, --right) {
        std::swap(*left, *right);
    }
}


