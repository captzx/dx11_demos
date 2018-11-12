#pragma once


namespace insight {
	template<typename T, unsigned int N>
	class TStateArrayMonitor {
	public:
		TStateArrayMonitor(T initialState);
		~TStateArrayMonitor();

		bool IsNeedUpdate();
		int GetState();
		unsigned int GetStartSlot();
		unsigned int GetEndSlot();

	private:
		T _states[N];
		TStateArrayMonitor<T, N>* _pDesiredState;
	};
}