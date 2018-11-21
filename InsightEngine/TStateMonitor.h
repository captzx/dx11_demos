#pragma once

namespace insight {
	template<typename T>
	class TStateMonitor {
	public:
		TStateMonitor(T initialState);
		~TStateMonitor();

		void InitializeState();
		void ResetTracing();

		void CacheRunningState(TStateMonitor<T>* pState);

		void SetState(T state);
		const T& GetState() const;

		bool IsSameWithCache();
		bool IsNeedUpload();

	private:
		bool _bNeedUpload;
		const static T _csInitialState;
		T _state;

		TStateMonitor<T*> _pCacheState;
	};

	#include "TStateMonitorImpl.h"
}