#ifndef SPUC_CIRC_BUFFER
#define SPUC_CIRC_BUFFER

/*
    Copyright (C) 2014 Tony Kirke

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// from directory: spuc_templates
#include <spuc/spuc_types.h>
#include <spuc/smart_array.h>
namespace SPUC {
//! \file
//! \brief Circular Buffer
//
//! \brief Circular Buffer
//
//!  \author Tony Kirke,  Copyright(c) 2001 
//! \author Tony Kirke
//! \ingroup templates misc
template <class T> class circ_buffer {

 protected:
  std::vector<T> buf;
  int	len;
  int	ptr;

 public:
	circ_buffer(void) : len(0), ptr(0) { ; }
	circ_buffer(const circ_buffer<T>& A);
	circ_buffer(int d);
	circ_buffer(int d, T init_value);
	~circ_buffer(void) {
	}
	int size(void) const {return len;}
    void set_size(int l) {
	  len = l+1;
	  buf.resize(len);
	  reset();
    }
	T operator [](int i) const {
	  return buf[(ptr+i)%(len)];
	}
	circ_buffer<T> operator =(circ_buffer<T>& A);
	void put(T data_in) {
	  buf[ptr] = data_in;
	  ptr = (ptr+1)%len;
	}
    void input(T d) {
	  buf[ptr] = d;
	  ptr = (ptr+1)%(len);
    }
    void reset() {
	  for (int i=0;i<len;i++) buf[i] = 0;
	  ptr = 0;
    }
    T last() {return(buf[ptr]);}
    T check(int l) { return(buf[(ptr+len-l-1)%len]); }
};

template <class T> circ_buffer<T>::circ_buffer(const circ_buffer<T>& A) : buf(A.len)
{
	len = A.len;
	ptr = A.ptr;
	for (int i = 0; i < len; i++) buf[i] = A.buf[i];

}	
// copy constructor
template <class T> circ_buffer<T>::circ_buffer(int len1) : buf(len1)
{
	len = len1;
	ptr = len-1;
}

template <class T> circ_buffer<T>::circ_buffer(int len1, T init_value) : buf(len1)
{
  len = len1;
  ptr = len-1;
  for (int i= 0; i < len; i++)	buf[i] = init_value;
}

template <class T> circ_buffer<T> circ_buffer<T>::operator =(circ_buffer<T>& A)
{
  if (this->len != A.size())	{
	// create room for A
	len = A.size();
	buf.resize(len);
  }
  ptr = A.ptr;

  for (int i = 0; i < len; i++)	buf[i] = A.buf[i];
  return *this;
}
} // namespace SPUC
#endif
