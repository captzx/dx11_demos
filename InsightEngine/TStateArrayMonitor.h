#pragma once

namespace insight {
	template<typename T, unsigned int N>
	class TStateArrayMonitor {
	public:
		TStateArrayMonitor(T initialState);
		~TStateArrayMonitor();

		void InitializeStates();
		void ResetUploadFlags();

		bool IsSameWithDesired();
		bool IsNeedUpload();

		unsigned int GetStartSlot();
		unsigned int GetEndSlot();
		unsigned int GetRange();
		
		T GetState(unsigned int slot) const;
		T* GetFirstSlotLocation();
		T* GetSlotLocation(unsigned int slot);

		void SetState(unsigned int slot, T state);
		void SetDesiredState(TStateArrayMonitor<T, N>* pDesiredState);

	private:
		void _SearchFromBelow();
		void _SearchFromAbove();

		unsigned int _uiStartSlot;
		unsigned int _uiEndSlot;
		bool _bNeedUpload;
		T _initialState;
		T _states[N];

		TStateArrayMonitor<T, N>* _pDesiredState;
	};

	#include "TStateArrayMonitorImpl.h";
}