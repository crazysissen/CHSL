#pragma once

namespace cs
{

    template<typename T>
    class ListIterator
    {
    public:
        ListIterator(T* target);

        T& operator*();
        ListIterator& operator++();
        bool operator==(const ListIterator&);
        bool operator!=(const ListIterator&);

    private:
        T* m_target;
    };

    template<typename T>
    class List
    {
    public:
        List();
        ~List();
        List(const List<T>& l_val);
        List(List<T>&& r_val);

        List<T>& operator=(const List<T>& l_val);
        List<T>& operator=(List<T>&& r_val);

        T& operator[](int index) const;

        int size() const;
        int capacity() const;
        bool empty() const;
        T& at(int index) const;
        T& front() const;
        T& back() const;

        void insert(int index, const T& value);
        void erase(int index);
        void push_back(const T& value);
        void pop_back();
        void clear();

        const T* data() const;

        ListIterator<T> begin() const;
        ListIterator<T> end() const;

        void boundArray();
        void shrinkArray();
        void growArray();

    private:
        static constexpr int c_dCapacity = 8;

        T* m_elements;
        int m_size;
        int m_capacity;
    };





    // Implementation

    // Constructors

    template<typename T>
    inline List<T>::List()
        :
        m_elements(new T[c_dCapacity]),
        m_size(0),
        m_capacity(c_dCapacity)
    {

    }

    template<typename T>
    inline List<T>::~List()
    {
        delete[] m_elements;
    }

    template<typename T>
    inline List<T>::List(const List<T>& l_val)
        :
        m_elements(nullptr)
    {
        *this = l_val;
    }

    template<typename T>
    inline List<T>::List(List<T>&& r_val)
        :
        m_elements(nullptr)
    {
        *this = std::move(r_val);
    }





    // Operators

    template<typename T>
    List<T>& List<T>::operator=(const List<T>& l_val)
    {
        if (this == &l_val)
        {
            return *this;
        }

        m_size = l_val.m_size;
        m_capacity = l_val.m_capacity;

        if (m_elements != nullptr)
        {
            delete[] m_elements;
        }

        m_elements = new T[m_capacity];
        for (int i = 0; i < m_size; ++i)
        {
            m_elements[i] = l_val.m_elements[i];
        }

        // memcpy(m_elements, l_val.m_elements, sizeof(T) * m_size);

        return *this;
    }
    template<typename T>
    List<T>& List<T>::operator=(List<T>&& r_val)
    {
        if (this == &r_val)
        {
            return *this;
        }

        m_size = r_val.m_size;
        m_capacity = r_val.m_capacity;

        if (m_elements != nullptr)
        {
            delete[] m_elements;
        }

        m_elements = r_val.m_elements;

        r_val.m_elements = nullptr;
        r_val.clear();

        return *this;
    }

    template<typename T>
    T& List<T>::operator[](int index) const
    {
        if (index < 0 || index >= m_size)
        {
            throw std::out_of_range("Vector.operator[]()");
        }

        return m_elements[index];
    }





    // Information and accessors

    template<typename T>
    inline int List<T>::size() const
    {
        return m_size;
    }

    template<typename T>
    inline int List<T>::capacity() const
    {
        return m_capacity;
    }

    template<typename T>
    inline bool List<T>::empty() const
    {
        return m_size == 0;
    }

    template<typename T>
    inline T& List<T>::at(int index) const
    {
        if (index < 0 || index >= m_size)
        {
            throw std::out_of_range("Vector.at()");
        }

        return m_elements[index];
    }

    template<typename T>
    inline T& List<T>::front() const
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Vector.front()");
        }

        return m_elements[0];
    }

    template<typename T>
    inline T& List<T>::back() const
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Vector.back()");
        }

        return m_elements[m_size - 1];
    }

    template<typename T>
    inline const T* List<T>::data() const
    {
        return m_elements;
    }

    template<typename T>
    inline ListIterator<T> List<T>::begin() const
    {
        return ListIterator<T>(m_elements);
    }

    template<typename T>
    inline ListIterator<T> List<T>::end() const
    {
        return ListIterator<T>(m_elements + m_size);
    }





    // Operations

    template<typename T>
    inline void List<T>::insert(int index, const T& value)
    {
        boundArray();
        if (index < 0 || index > m_size)
        {
            return;
        }

        for (int i = m_size; i > index; --i)
        {
            m_elements[i] = m_elements[i - 1];
        }

        m_elements[index] = value;
        m_size++;

    }

    template<typename T>
    inline void List<T>::erase(int index)
    {
        if (index < 0 || index >= m_size)
        {
            return;
        }

        for (int i = index; i < m_size - 1; ++i)
        {
            m_elements[i] = m_elements[i + 1];
        }

        m_size--;

        //boundArray();
    }

    template<typename T>
    inline void List<T>::push_back(const T& value)
    {
        boundArray();
        m_elements[m_size] = value;

        m_size++;

    }

    template<typename T>
    inline void List<T>::pop_back()
    {
        if (m_size == 0)
        {
            return;
        }

        m_size--;

        //boundArray();
    }

    template<typename T>
    inline void List<T>::clear()
    {
        m_size = 0;
        m_capacity = c_dCapacity;

        if (m_elements != nullptr)
        {
            delete[] m_elements;
        }

        m_elements = new T[c_dCapacity];
    }





    // Privates

    template<typename T>
    inline void List<T>::boundArray()
    {
        if (m_size == m_capacity)
        {
            growArray();
            return;
        }

        if (m_size < m_capacity / 2 && m_capacity > c_dCapacity)
        {
            shrinkArray();
        }
    }

    template<typename T>
    inline void List<T>::shrinkArray()
    {
        T* newElements = new T[m_capacity / 2];
        for (int i = 0; i < m_size; ++i)
        {
            newElements[i] = m_elements[i];
        }

        delete[] m_elements;
        m_elements = newElements;
        m_capacity /= 2;
    }

    template<typename T>
    inline void List<T>::growArray()
    {
        T* newElements = new T[m_capacity * 2];
        for (int i = 0; i < m_size; ++i)
        {
            newElements[i] = m_elements[i];
        }

        delete[] m_elements;
        m_elements = newElements;
        m_capacity *= 2;
    }

    template<typename T>
    inline ListIterator<T>::ListIterator(T* target)
    {
        m_target = target;
    }

    template<typename T>
    inline T& ListIterator<T>::operator*()
    {
        return *m_target;
    }

    template<typename T>
    inline ListIterator<T>& ListIterator<T>::operator++()
    {
        m_target++;
        return *this;
    }

    template<typename T>
    inline bool ListIterator<T>::operator==(const ListIterator& rhs)
    {
        return m_target == rhs.m_target;
    }

    template<typename T>
    inline bool ListIterator<T>::operator!=(const ListIterator& rhs)
    {
        return m_target != rhs.m_target;
    }

}