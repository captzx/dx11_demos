#pragma once

namespace insight {
	template<typename T>
	class TStateMonitor {
	public:
		TStateMonitor(T initialState);
		~TStateMonitor();

		void InitializeState();
		void ResetUploadFlag();

		void SetDesiredState(TStateMonitor<T>* pState);

		void SetState(T state);
		const T& GetState() const;

		bool IsSameWithDesired();
		bool IsNeedUpdate();

	private:
		bool _bNeedUpload;
		T _initialState;
		T _state;
		TStateMonitor<T*> _pDesiredState;
	};

	#include "TStateMonitorImpl.h"
}