#ifndef VECTOR_H
#define VECTOR_H
#include <cstring>
#include <iostream>
template <typename Type> class Vector
{
private:
    unsigned int len;
    unsigned int capacity;
    Type * data;
public:
    class VectorException
    {
    public:
        const char * reason;
        VectorException():
            reason("default reason")
        {}
        VectorException(const char * reason_):
            reason(reason_)
        {}
        std :: ostream & operator << (std :: ostream & os) const
        {
            os << reason << std :: endl;
            return os;
        }
    };
public:
    class iterator
    {
    private :
        unsigned int position;
    public:
        iterator():
            position(0)
        {}
        iterator(unsigned int position_):
            position(position_)
        {}
        iterator(const iterator & copy):
            position(copy.position)
        {}
        iterator operator ++()
        {
            iterator tmp(*this);
            position++;
            return tmp;
        }
        iterator & operator ++(int m)
        {
            position ++;
            return *this;
        }
        bool operator <(const iterator & compare) const
        {
            return (position < compare.position);
        }
        bool operator >(const iterator & compare) const
        {
            return (position > compare.position);
        }
        bool operator <=(const iterator & compare) const
        {
            return (position <= compare.position);
        }
        bool operator >=(const iterator & compare) const
        {
            return (position >= compare.position);
        }
        bool operator ==(const iterator & compare) const
        {
            return (position == compare.position);
        }
        bool operator != (const iterator & compare) const
        {
            return (position != compare.position);
        }
        Type & operator *() throw(VectorException)
        {
            if(position >= len)
                throw VectorException("array index out of bounds");
            return data[position];
        }
    };
public:
    class const_iterator
    {
    private:
        unsigned int position;
    public:
        const_iterator():
            position(0)
        {}
        const_iterator(unsigned int position_):
            position(position_)
        {}
        const_iterator(const const_iterator & copy):
            position(copy.position)
        {}
        const_iterator operator ++()
        {
            const_iterator tmp(*this);
            position ++;
            return tmp;
        }
        const_iterator & operator ++(int n)
        {
            position++;
            return *this;
        }
        bool operator < (const const_iterator & compare) const
        {
            return (position < compare.position);
        }
        bool operator > (const const_iterator & compare) const
        {
            return (position > compare.position);
        }
        bool operator <=(const const_iterator & compare) const
        {
            return (position <= compare.position);
        }
        bool operator >=(const const_iterator & compare) const
        {
            return (position >= compare.position);
        }
        bool operator ==(const const_iterator & compare) const
        {
            return (position == compare.position);
        }
        bool operator !=(const const_iterator & compare) const
        {
            return (position != compare.position);
        }
        const Type & operator *() throw (VectorException)
        {
            if(position >= len)
                throw VectorException("index out of bounds");
            return data[position];
        }
    };
public:
    Vector():
        len(0),
        capacity(10),
        data(new Type[len])
    {
        memset(data,0,len*sizeof(Type));
    }
    Vector(int len_):
        len(len_),
        capacity(0),
        data(new Type[len])
    {
        memset(data,0,sizeof(Type)*len);
    }
    Vector(const Vector & copy):
        len(copy.len),
        capacity(copy.capacity),
        data(new Type[len])
    {
        memset(data,0,sizeof(Type));
        memcpy(data,copy.data,len);
    }
    ~Vector()
    {
        delete [] data;
    }
    unsigned int lenth()
    {
        return len;
    }
    unsigned int vectorCapacity()
    {
        return capacity;
    }
    void reallocMem(unsigned int capacity_new)
    {
        Type * tmp = new Type[capacity_new];
        memset(tmp,0,sizeof(Type)*capacity_new);
        memcpy(tmp,data,len*sizeof(Type));
        capacity = capacity_new;
    }
    void push_back(const Type & copy)
    {
        if(len == capacity)
            reallocMem(capacity*1.4);
        data[len] = copy;
        len ++;
    }
    Type & operator [](unsigned int index) throw (VectorException)
    {
        if(index >= len)
            throw VectorException("index out of bounds");
        return data[index];
    }\
    const Type & operator [] (unsigned int index) const throw (VectorException)
    {
        if(index >= len)
            throw VectorException("index out of bounds");
        return data[index];
    }
    void removeData(unsigned int index) throw (VectorException)
    {
        if(index >= len)
            throw VectorException("index out of bounds in removeData");
        if(index == len -1)
            len --;
        else
        {
            memcpy(&(data[index]),&(data[index + 1]),len - index - 1);
            len --;
            if(len < 0.5*capacity && capacity > 29)
                reallocMem(0.5*capacity);
        }
    }
    void freeVector()
    {
        len = 0;
        capacity = 10;
        delete [] data;
        data = new Type[capacity];
        memset(data,0,sizeof(Type)*capacity);
    }
    void cutAfterIndex(unsigned int index) throw(VectorException)
    {
        if (index >= len)
            throw VectorException("index is out of bound in cutAfterIndex");
        if(index == len - 1)
            return ;
        memset(data[index + 1],0,sizeof(Type)*(len - index - 1));
        len = index + 1;
        if(len < capacity*0.6 && capacity > 29)
            reallocMem(capacity*0.6);
    }
};

#endif // VECTOR_H