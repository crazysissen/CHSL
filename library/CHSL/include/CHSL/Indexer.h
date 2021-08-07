#pragma once

#include "CHSLTypedef.h"
#include "Math.h"

namespace cs
{
	/// <summary>
	/// Fixed-size cyclic list of members with fixed indices
	/// </summary>
	template <typename T, size_t C, byte CBits = 16>
	class Indexer
	{
	public:
		Indexer()
		{
			//m_array = Member[C];

			for (int i = 0; i < C; ++i)
			{
				m_array[i].used = false;
				m_array[i].f = (i + 1) % C;
				m_array[i].b = (i - 1 + C) % C;
			}

			m_count = 0;
			m_head = 0;
			m_max = 0;

			//m_first = 0;
			//m_last = 0;
		}

		///// <summary>
		///// Init with default constructor values for each member before usage. 
		///// </summary>
		//template <typename... P>
		//Indexer(P&&... args)
		//{
		//	m_array = (Member*)malloc(sizeof(Member) * C);

		//	for (size_t i = 0; i < C; ++i)
		//	{
		//		m_array[i] = { T(std::forward(args)), false, (i + 1) % C, (i - 1 + C) % C };
		//	}

		//	m_count = 0;
		//	m_head = 0;
		//	m_first = 0;
		//	m_last = 0;
		//}

		Indexer(const Indexer& lVal)
		{
			delete[] m_array;
			m_array = new Member[C];

			for (int i = 0; i < C; ++i)
			{
				m_array[i] = lVal.m_array[i];
			}

			m_count = lVal.m_count;
			m_head = lVal.m_head;
			m_max = lVal.m_max;

			//m_first = lVal.m_first;
			//m_last = lVal.m_last;
		}

		Indexer(Indexer&& rVal)
		{
			delete[] m_array;
			m_array = rVal.m_array;
			rVal.m_array = nullptr;

			m_count = rVal.m_count;
			m_head = rVal.m_head;
			m_max = rVal.m_max;

			//m_first = rVal.m_first;
			//m_last = rVal.m_last;
		}

		~Indexer()
		{
			/*delete[] m_array;*/
		}



		// Add member and return index

		int Add(const T& value)
		{
			if (m_count >= C)
			{
				throw std::length_error("Tried to exceed Indexer capacity.");
			}

			m_count++;

			Member& current = m_array[m_head];

			// Maximizing array special case
			if (m_count == C)
			{
				// Will create an unstable state, which is resolved in Remove
				current.value = value;
				current.used = true;
				m_max = C;

				return m_head;
			}

			// Regular procedure

			//if (m_head < m_first)
			//{
			//	m_first = m_head;
			//}
			//if (m_head > m_last)
			//{
			//	m_last = m_head;
			//}

			current.value = value;
			current.used = true;
			m_array[current.f].b = current.b;
			m_array[current.b].f = current.f;

			size_t usedIndex = m_head;
			m_head = current.f;

			if (m_head > m_max)
			{
				m_max = m_head;
			}

			return usedIndex;
		}



		// Remove member by index
		void Remove(int index)
		{
			if (m_count == 0 || index < 0 || index >= C || !m_array[index].used)
			{
				return;
			}

			m_count--;

			Member& current = m_array[index];

			// Special case if array full
			if (m_count == C - 1)
			{
				m_head = index;

				current.used = false;
				Optimize();

				return;
			}

			// Normal procedure

			//if (index == m_first)
			//{
			//	m_first = current.f;
			//}
			//if (index == m_last)
			//{
			//	int current;

			//	do
			//	{
			//	}
			//	while(i)
			//}

			if (m_array[current.b].used)
			{
				size_t pUnused;
				for (int i = (current.b - 1 + C) % C; m_array[(i + 1) % C].used; i = (i - 1 + C) % C)
				{
					pUnused = i;
				}

				if (pUnused < current.b)
				{
					for (int i = index; i > pUnused; --i)
					{
						m_array[i].b = pUnused;
					}
				}
				else
				{
					for (int i = index; i != pUnused; i = (i - 1 + C) % C)
					{
						m_array[i].b = pUnused;
					}
				}
			}
			else
			{
				m_array[current.b].f = index;
			}

			for (int i = (index + 1) % C; m_array[(i - 1 + C) % C].used; i = (i + 1) % C)
			{
				current.f = i;
				m_array[i].b = index;
			}

			if (index < m_head)
			{
				m_head = index;
			}

			current.used = false;
		}



		// Get member by index

		const T& Get(int index) const
		{
			if (index >= C || index < 0)
			{
				throw std::out_of_range("Tried to get Indexer member out of range.");
			}

			return m_array[index];
		}

		const T& operator[](int index) const
		{ 
			return Get(index);
		}



		// Misc

		void Clear()
		{
			for (int i = 0; i < C; ++i)
			{
				m_array[i].used = false;
				m_array[i].f = mod(i + 1, C);
				m_array[i].b = mod(i - 1 + C, C);
			}

			m_count = 0; 
			m_head = 0;
			m_max = 0;
		}

		void Optimize()
		{
			if (m_count == C)
			{
				return;
			}
			else if (m_count == 0)
			{
				Clear();
				return;
			}

			size_t firstEmpty = 0;

			while (m_array[firstEmpty].used)
			{
				firstEmpty++;
			}

			size_t latestEmpty = firstEmpty;

			for (size_t i = firstEmpty + 1; i < C; ++i)
			{
				Member& current = m_array[i];

				if (current.used)
				{
					current.b = latestEmpty;
					current.f = mod(i + 1, C);
				}
				else
				{
					m_array[latestEmpty].f = i;

					current.b = latestEmpty;

					latestEmpty = i;
				}
			}

			for (size_t i = 0; i < firstEmpty; ++i)
			{
				Member& current = m_array[i];

				if (current.used)
				{
					current.b = latestEmpty;
					current.f = i + 1;
				}
				else
				{
					m_array[latestEmpty].f = i;

					current.b = latestEmpty;

					latestEmpty = i;
				}
			}

			m_array[firstEmpty].b = latestEmpty;
		}


	public:
		// For iterating
		struct Iterator
		{
			Indexer* indexer;
			size_t current;

			Iterator& operator++() 
			{ 
				for (++current; current < indexer->m_max; ++current)
				{
					if (indexer->m_array[current].used)
					{
						return *this;
					}
				}

				return *this;
			}
			T& operator*() { return indexer->m_array[current].value; }
			bool operator!=(const Iterator& lVal) { return current != lVal.current; }
		};

		Iterator begin() 
		{
			if (m_count == 0 || m_count == C)
			{
				return { this, 0 };
			}

			size_t first = 0;
			while (!m_array[first].used)
			{
				++first;
			}

			return { this, first };
		}

		Iterator end() 
		{ 
			return { this, m_max };
		}



	private:
		struct Member
		{
			T value;
			bool used		: 1;
			size_t f	: CBits;
			size_t b	: CBits;
		};



		Member m_array[C];
		size_t m_count;
		size_t m_head;
		size_t m_max;
		//size_t m_first;
		//size_t m_last;
	};
}