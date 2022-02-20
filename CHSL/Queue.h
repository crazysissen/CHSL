#pragma once

namespace cs
{

	template<typename T>
	class Queue
	{
	public:
		Queue();
		~Queue();
		Queue(const Queue&);
		Queue(Queue&&);

		Queue<T>& operator=(const Queue<T>&);
		Queue<T>& operator=(Queue<T>&&);

		int Size() const;
		int Capacity() const;
		bool Empty() const;
		T& At() const;
		T& Next() const;

		void Clear();
		void Enqueue(const T& value);
		T Dequeue();

	private:
		void Expand();

	private:
		static constexpr int c_dCapacity = 16;

		T* m_elements;
		int m_size;
		int m_capacity;
		int m_first;
		int m_last;
	};





	// Implementation
	
	// Construction

	template<typename T>
	inline Queue<T>::Queue()
		:
		m_elements(new T[c_dCapacity]),
		m_size(0),
		m_capacity(c_dCapacity),
		m_first(0),
		m_last(0)
	{
	}

	template<typename T>
	inline Queue<T>::~Queue()
	{
		delete[] m_elements;
	}

	template<typename T>
	inline Queue<T>::Queue(const Queue<T>& lVal)
		:
		m_elements(nullptr)
	{
		*this = lVal;
	}

	template<typename T>
	inline Queue<T>::Queue(Queue<T>&& rVal)
		:
		m_elements(nullptr)
	{
		*this = static_cast<Queue<T>&&>(rVal);
	}

	template<typename T>
	inline Queue<T>& Queue<T>::operator=(const Queue<T>& lVal)
	{
		if (this == &lVal)
		{
			return *this;
		}

		m_size = lVal.m_size;
		m_capacity = lVal.m_capacity;
		m_first = lVal.m_first;
		m_last = lVal.m_last;

		delete[] m_elements;
		m_elements = new T[m_capacity];
		for (int i = 0; i < m_size; ++i)
		{
			int index = (m_first + i) % m_size;
			m_elements[index] = lVal.m_elements[index];
		}

		return *this;
	}

	template<typename T>
	inline Queue<T>& Queue<T>::operator=(Queue<T>&& rVal)
	{
		if (this == &rVal)
		{
			return *this;
		}

		m_size = rVal.m_size;
		m_capacity = rVal.m_capacity;
		m_first = rVal.m_first;
		m_last = rVal.m_last;

		delete[] m_elements;
		m_elements = rVal.m_elements;

		rVal.m_elements = nullptr;
		rVal.Clear();

		return *this;
	}

	template<typename T>
	inline int Queue<T>::Size() const
	{
		return 0;
	}

	template<typename T>
	inline int Queue<T>::Capacity() const
	{
		return 0;
	}

	template<typename T>
	inline bool Queue<T>::Empty() const
	{
		return false;
	}

	template<typename T>
	inline T& Queue<T>::At() const
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline T& Queue<T>::Next() const
	{
		// TODO: insert return statement here
	}

	template<typename T>
	inline void Queue<T>::Clear()
	{
	}

	template<typename T>
	inline void Queue<T>::Enqueue(const T& value)
	{
	}

	template<typename T>
	inline T Queue<T>::Dequeue()
	{
		return T();
	}

	template<typename T>
	inline Queue<T>::Expand()
	{
	}

}