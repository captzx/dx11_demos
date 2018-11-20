using namespace insight;

template <typename T, unsigned int N>
TStateArrayMonitor<T, N>::TStateArrayMonitor(T initialState):
	_uiStartSlot(0),
	_uiEsndSlot(0),
	_bNeedUpload(false),
	_initialState(initialState),
	_pDesiredState(nullptr){

	InitializeStates();
	ResetUploadFlags();
}
template <typename T, unsigned int N>
TStateArrayMonitor<T, N>::~TStateArrayMonitor() {

}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::InitializeStates() {

}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::ResetUploadFlags() {

}

template <typename T, unsigned int N>
bool TStateArrayMonitor<T, N>::IsSameWithDesired() {

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

	if (_pDesiredState == nullptr) {
		_bNeedUpload = true;
		_uiStartSlot = 0;
		_uiEndSlot = N - 1;
		
		return;
	}

	bool bSameWithDesired = IsSameWithDesired();

	if (!_bNeedUpload && !bSameWithDesired) {
		_bNeedUpload = true;
		_uiStartSlot = slot;
		_uiEndSlot = slot;
	}

	if (_bNeedUpload) {
		if (slot < _uiStartSlot) {
			if (!bSameWithDesired) _uiStartSlot = slot;
		}
		else if (slot == _uiStartSlot) {
			if (bSameWithDesired) _SearchFromBlow();
		}
		else if (_uiStartSlot < slot && slot < _uiEndSlot) {

		}
		else if (slot == _uiEndSlot) {
			if (bSameWithDesired) _SearchFromAbove();
		}
		else if (_uiEndSlot < slot) {
			if (!bSameWithDesired) {
				_uiEndSlot = slot;
			}
		}
	}
}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::SetDesiredState(TStateArrayMonitor<T, N>* pState) {
	_pDesiredState = pState;
}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::_SearchFromBelow() {

}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::_SearchFromAbove() {

}