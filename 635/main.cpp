#include <iostream>
#include <vector>
#include <cassert>
#include <cstdio>

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


using namespace std;

void _getSeq(char* in, char* out)
{
    assert(in);
    assert(out);

    for(int i = 0; i < 52; i++)
    {
        if('J' == in[i * 2])
        {
            out[i] = 1;
        }
        else if(('2' <= in[i * 2]) && ('9' >= in[i * 2]))
        {
            out[i] = in[i * 2] - '0';
        }
        else if('T' == in[i * 2])
        {
            out[i] = 10;
        }
        else if('A' == in[i * 2])
        {
            out[i] = 11;
        }
        else if('Q' == in[i * 2])
        {
            out[i] = 12;
        }
        else if('K' == in[i * 2])
        {
            out[i] = 0;
        }
        else
        {
            printf("Error: intput %c\n", in[i * 2]);
        }
    }
}

void _rotateSeq(char* seq)
{
    char head = seq[0];
    for(int i = 0; i < 51; ++i)
    {
        seq[i] = seq[i + 1];
    }
    seq[51] = head;
}

void _printClock(vector< vector<char> >& c)
{
    for(int i = 0; i < 13; ++i)
    {
        for(int j = 0; j < c[i].size(); ++j)
        {
            printf("%c ", c[i][j] + 'A');
        }
        puts("");
    }
        puts("");
}

bool _solve(char* seq)
{
    // make clock stack
    vector< FixedQueue<char> > clockIn;
    clockIn.resize(13);
    for(int i = 0; i < 13; ++i)
    {
        clockIn[i].reset(4);
    }
    for(int i = 0; i < 48; ++i)
    {
        clockIn[i / 4 + 1].push_back(seq[i]);
    }
    clockIn[0].push_back(seq[48]);
    clockIn[0].push_back(seq[49]);
    clockIn[0].push_back(seq[50]);
    clockIn[0].push_back(seq[51]);
//_printClock(clockIn);
    // solving
    int idx = 0;
    while(clockIn[idx].empty() == false)
    {
        int newIdx = clockIn[idx].pop_front();
        idx = newIdx;
//_printClock(clockIn);
    }
    // checking
    for(int i = 0; i < 13; ++i)
    {
        if(clockIn[i].empty() == false)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    char buf[150];
    cin.getline(buf, 150);
    while(buf[0] != '0')
    {
        char seq[52];
        int nSol = 0;
        _getSeq(buf, seq);
        for(int i = 0; i < 52; i++)
        {
            _rotateSeq(seq);
            if(_solve(seq) == true)
            {
                ++nSol;
            }
        }
        printf("%ld\n", nSol);
        cin.getline(buf, 150);
    }

    return 0;
}