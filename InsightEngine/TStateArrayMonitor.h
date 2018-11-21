#pragma once

namespace insight {
	template<typename T, unsigned int N>
	class TStateArrayMonitor {
	public:
		TStateArrayMonitor(T initialState);
		~TStateArrayMonitor();

		void InitializeState();
		void ResetTracing();

		bool IsSameWithCache();
		bool IsNeedUpload();

		unsigned int GetStartSlot();
		unsigned int GetEndSlot();
		unsigned int GetRange();
		
		T GetState(unsigned int slot) const;
		T* GetFirstSlotLocation();
		T* GetSlotLocation(unsigned int slot);

		void SetState(unsigned int slot, T state);
		void CacheRunningState(TStateArrayMonitor<T, N>* pState);

	private:
		void _SearchFromBelow();
		void _SearchFromAbove();

		unsigned int _uiStartSlot;
		unsigned int _uiEndSlot;
		bool _bNeedUpload;
		const static T _csInitialState;
		T _states[N];

		TStateArrayMonitor<T, N>* _pCacheState;
	};

	#include "TStateArrayMonitorImpl.h";
}