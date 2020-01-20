#ifndef UTILITY_C_QUEUE_H_
#define UTILITY_C_QUEUE_H_

#include <deque>
#include <vector>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

template <class T> class CQueue
{
public:
  CQueue(){}
  virtual ~CQueue(){}

  void SetName(const char * p_Name){m_Name = p_Name;}
  const char * GetName(void){return m_Name.c_str();}

  bool Pop(T & p_T, long p_WaitTime = 0L) {
	 std::unique_lock<std::mutex> Locker(m_PopLocker);
	 if(m_Deque.empty() == true) {
		if(p_WaitTime) {
		   std::chrono::duration<long, std::ratio<1,1000>> Time2Sleep(p_WaitTime);
		   //FIXME: Implementar lambda como predicado para wakeups espureos en variable condicional
		   if(m_PushSignal.wait_for(Locker, std::chrono::duration<long, std::ratio<1,1000>>(p_WaitTime)) == std::cv_status::timeout) {
			  return false;
		   } else {
			  //FIXME: Solucionar problema de desbloqueo espureo.
		   }
		} else {
		   m_PushSignal.wait(Locker, [this](){return !m_Deque.empty();});
		}
	 }

	 auto T_Iter = m_Deque.begin();
	 if(T_Iter == m_Deque.end()) {
		return false;
	 } else {
		p_T = std::move(*T_Iter);
		m_Deque.pop_front();
		return true;
	 }
	 return true;
  };

  //***************************************************************************************
  bool Push(T p_T, bool p_Lock = true) {
	 std::lock_guard<std::mutex> Locker(m_PopLocker);
	 m_Deque.emplace_back(std::move(p_T));
	 m_PushSignal.notify_one();
	 return true;
  };

  size_t Size(void){return m_Deque.size();}

private:
  std::deque<T>           m_Deque;        //Container deque para almacenar los elementos a�adidos a la cola.
  std::condition_variable m_PushSignal;   //Variable Condicional de Ilog para bloquear al proceso que llame
										  //a la funcion Pop en caso de que el deque este vacio.
  std::mutex              m_PopLocker;    //Mutex para serializar el acceso a la cola
  std::mutex              m_PushLocker;   //Mutex para serializar el acceso a la cola
  std::string             m_Name;         ///Nombre identificativo de la cola (Utilizado para trazar).
};
#endif //Fin define UTILITY_C_QUEUE_H_

