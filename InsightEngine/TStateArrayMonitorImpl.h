using namespace insight;

template <typename T, unsigned int N>
TStateArrayMonitor<T, N>::TStateArrayMonitor(T initialState):
	_startSlot(0),
	_endSlot(0),
	_bNeedUpload(false),
	_initialState(initialState),
	_pIntentState(nullptr){

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
bool TStateArrayMonitor<T, N>::IsSameWithIntent() {

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

}

template <typename T, unsigned int N>
void TStateArrayMonitor<T, N>::SetIntentState(TStateArrayMonitor<T, N>* pIntentState) {

}