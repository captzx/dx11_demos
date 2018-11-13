#pragma once

namespace insight {
	template<typename T>
	class TStateMonitor {
	public:
		TStateMonitor(T initialState);
		~TStateMonitor();

		void InitializeState();
		void ResetUploadFlag();

		void SetIntentState(TStateMonitor<T*> pIntentState);

		void SetState(T state);
		const T& GetState() const;

		bool IsSameWithIntent();
		bool IsNeedUpdate();

	private:
		bool _bNeedUpload;
		T _initialState;
		T _state;
		TStateMonitor<T*> _pIntentState;
	};

	#include "TStateMonitorImpl.h"
}