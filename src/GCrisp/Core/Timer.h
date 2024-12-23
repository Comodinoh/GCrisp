#pragma once


namespace GCrisp{

class ProcessedTime
{
friend class Timer;
public:
  ProcessedTime() : ProcessedTime(0) {}
  ProcessedTime(int64_t time) : m_Time(time) {}

  inline const int64_t& GetNSTime() const {return m_Time;}

  inline float GetSecondsF() const {return m_Time/(float)1e9;}
  inline double GetSecondsD() const {return m_Time/(double)1e9;}

  inline float GetMillisF() const {return m_Time/(float)1e6;}
  inline double GetMillisD() const {return m_Time/(double)1e6;}
protected:
  int64_t m_Time;
};

class Timer
{
public:
  Timer(int64_t start) : m_Last(start), m_Elapsed(start) {}
 
  void processTime(int64_t now);

  inline const ProcessedTime& GetElapsedTime() const 
  {
    return m_Elapsed;
  }
private:
  int64_t m_Last;
  ProcessedTime m_Elapsed;
};

class ScopedTimer
{
public:
  ScopedTimer(int64_t start, ProcessedTime& elapsed) : m_Start(start), m_Elapsed(elapsed) {}
  ~ScopedTimer();
private:
  ProcessedTime& m_Elapsed;
  int64_t m_Start;
};

}
