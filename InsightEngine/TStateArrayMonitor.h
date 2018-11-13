#pragma once

namespace insight {
	template<typename T, unsigned int N>
	class TStateArrayMonitor {
	public:
		TStateArrayMonitor(T initialState);
		~TStateArrayMonitor();

		void InitializeStates();
		void ResetUploadFlags();

		bool IsSameWithIntent();
		bool IsNeedUpload();

		unsigned int GetStartSlot();
		unsigned int GetEndSlot();
		unsigned int GetRange();
		
		T GetState(unsigned int slot) const;
		T* GetFirstSlotLocation();
		T* GetSlotLocation(unsigned int slot);

		void SetState(unsigned int slot, T state);
		void SetIntentState(TStateArrayMonitor<T, N>* pIntentState);

	private:
		unsigned int _startSlot;
		unsigned int _endSlot;
		bool _bNeedUpload;
		T _initialState;
		T _states[N];

		TStateArrayMonitor<T, N>* _pIntentState;
	};

	#include "TStateArrayMonitorImpl.h";
}