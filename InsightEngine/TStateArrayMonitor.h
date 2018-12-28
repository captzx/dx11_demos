#pragma once

namespace insight {
	template <class T, unsigned int N>
	class TStateArrayMonitor
	{
	public:
		TStateArrayMonitor(T val);
		~TStateArrayMonitor();

		void SetDesired(TStateArrayMonitor<T, N>* pDesired);
		bool SameAsDesired(unsigned int slot);

		void Set(unsigned int slot, T state);

		bool ShouldUpload();
		unsigned int GetStartSlot();
		unsigned int GetEndSlot();
		unsigned int GetRange();

		T Get(unsigned int slot) const;
		T* GetFirstSlotLocation();
		T* GetSlotLocation(unsigned int slot);

		void Initialize();
		void Reset();

	private:
		void _SearchFromBelow();
		void _SearchFromAbove();

		unsigned int _uStartSlot;
		unsigned int _uEndSlot;
		bool _bShouldUpload;

		T _tInitialValue;
		T _tRealValues[N];

		TStateArrayMonitor<T, N>* _pDesired;
	};

#include "TStateArrayMonitor.inl"
}