#include <vector>

template<class T>
class FixedQueue
{
public:
    FixedQueue(): m_data(), m_iSize(0), m_iHead(0) {}
    explicit FixedQueue(int iSize): m_data(iSize), m_iSize(0), m_iHead(0) {}
    void push_back(const T& val)
    {
        if(m_iSize == m_data.size())
        {
            return;
        }

        m_data[m_iHead] = val;
        ++m_iHead;
        ++m_iSize;
    }
    T pop_front()
    {
        int tail = _getTail();
        if(m_iSize> 0)
        {
            --m_iSize;
        }

        return m_data[tail];
    }
    void reset(int iSize)
    {
        m_data.clear();
        m_data.resize(iSize);
        m_iSize = 0;
        m_iHead = 0;
    }
    bool empty() const
    {
        return (m_iSize == 0 ? true : false);
    }
    T front() const
    {
        return m_data[_getTail()];
    }

private:
    std::vector<T> m_data;
    int m_iSize;
    int m_iHead;

    int _getTail() const
    {
        int ret = m_iHead - m_iSize;
        if(ret < 0)
        {
            ret += m_data.size();
        }
        return ret;
    }
};
