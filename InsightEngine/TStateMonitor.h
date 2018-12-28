#pragma once

namespace insight {
	template <class T>
	class TStateMonitor{
	public:
		TStateMonitor(T val);
		~TStateMonitor();

		void SetDesired(TStateMonitor<T>* pDesired);
		bool SameAsDesired();

		void Set(T val);
		T Get() const;

		bool ShouldUpload();
		void Initialize();
		void Reset();

	private:
		bool _bShouldUpload;

		T _tInitialValue;
		T _tRealValue;
		TStateMonitor<T>* _pDesired;
	};

#include "TStateMonitor.inl"
}