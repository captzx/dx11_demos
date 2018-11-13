using namespace insight;

template <typename T>
TStateMonitor<T>::TStateMonitor(T initialState):
	_bNeedUpload(false),
	_initialState(initialState),
	_state(initialState),
	_pIntentState(nullptr){

	InitializeState();
	ResetUploadFlag();
}

template<typename T>
TStateMonitor<T>::~TStateMonitor() {

}

template<typename T>
void TStateMonitor<T>::InitializeState() {
	SetState(_initialState);
}

template<typename T>
void TStateMonitor<T>::ResetUploadFlag() {
	_bNeedUpload = false;
}

template<typename T>
void TStateMonitor<T>::SetIntentState(TStateMonitor<T*> pIntentState) {
	_pIntentState = pIntentState;
}

template<typename T>
void TStateMonitor<T>::SetState(T state) {
	_state = state;

	if (!_pIntentState) {
		_bNeedUpload = true;
		return;
	}

	_bNeedUpload = !IsSameWithIntent();
}

template<typename T>
const T& TStateMonitor<T>::GetState() const {
	return _state;
}

template<typename T>
bool TStateMonitor<T>::IsSameWithIntent() {
	return _state == _pIntentState->_state;
}

template<typename T>
bool TStateMonitor<T>::IsNeedUpdate() {
	return _bNeedUpload;
}
