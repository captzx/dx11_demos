#pragma once

namespace insight {
	template<typename T>
	class TStateMonitor {
	public:
		TStateMonitor(T initialState);
		~TStateMonitor();

		void SetDesiredState(TStateMonitor<T*> pDesiredState);

		void SetState(T state);
		const T& GetState() const;

		bool isSameWithDesiredState();
		bool isNeedUpload();

		void InitializeState();
		void ResetState();


	private:
		T _state;
		TStateMonitor<T*> _pDesiredState;
	};

	#include "TStateMonitorImpl.h"
}