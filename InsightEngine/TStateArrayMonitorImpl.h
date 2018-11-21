using namespace insight;

template <typename T, unsigned int N>
TStateArrayMonitor<T, N>::TStateArrayMonitor(T initialState):
	_uiStartSlot(0),
	_uiEndSlot(0),
	_bNeedUpload(false),
	_csInitialState(initialState),
	_pCacheState(nullptr){

	InitializeStates();
	ResetUploadFlags();
}
template <typename T, unsigned int N>
TStateArrayMonitor<T, N>::~TStateArrayMonitor() {

}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::InitializeState() {

}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::ResetTracing() {

}

template <typename T, unsigned int N>
bool TStateArrayMonitor<T, N>::IsSameWithCache() {

}

template <typename T, unsigned int N>
bool TStateArrayMonitor<T, N>::IsNeedUpload() {

}

template <typename T, unsigned int N>
unsigned int TStateArrayMonitor<T, N>::GetStartSlot() {

}

template <typename T, unsigned int N>
unsigned int TStateArrayMonitor<T, N>::GetEndSlot() {

}

template <typename T, unsigned int N>
unsigned int TStateArrayMonitor<T, N>::GetRange() {

}


template <typename T, unsigned int N>
T TStateArrayMonitor<T, N>::GetState(unsigned int slot) const {

}

template <typename T, unsigned int N>
T* TStateArrayMonitor<T, N>::GetFirstSlotLocation() {

}

template <typename T, unsigned int N>
T* TStateArrayMonitor<T, N>::GetSlotLocation(unsigned int slot) {

}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::SetState(unsigned int slot, T state) {
	assert(slot < N);

	_state[slot] = state;

	if (_pCacheState == nullptr) {
		_bNeedUpload = true;
		_uiStartSlot = 0;
		_uiEndSlot = N - 1;
		
		return;
	}

	bool bSameWithCache = IsSameWithCache();

	if (!_bNeedUpload && !bSameWithCache) {
		_bNeedUpload = true;
		_uiStartSlot = slot;
		_uiEndSlot = slot;
	}

	if (_bNeedUpload) {
		if (slot < _uiStartSlot) {
			if (!bSameWithCache) _uiStartSlot = slot;
		}
		else if (slot == _uiStartSlot) {
			if (bSameWithCache) _SearchFromBlow();
		}
		else if (_uiStartSlot < slot && slot < _uiEndSlot) {

		}
		else if (slot == _uiEndSlot) {
			if (bSameWithCache) _SearchFromAbove();
		}
		else if (_uiEndSlot < slot) {
			if (!bSameWithCache) {
				_uiEndSlot = slot;
			}
		}
	}
}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::CacheRunningState(TStateArrayMonitor<T, N>* pState) {
	_pCacheState = pState;
}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::_SearchFromBelow() {

}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::_SearchFromAbove() {

}