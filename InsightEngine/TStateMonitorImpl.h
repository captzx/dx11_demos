using namespace insight;

template <typename T>
TStateMonitor<T>::TStateMonitor(T initialState):
	_bNeedUpload(false),
	_initialState(initialState),
	_state(initialState),
	_pDesiredState(nullptr){

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
void TStateMonitor<T>::SetDesiredState(TStateMonitor<T>* pState) {
	_pDesiredState = pState;
}

template<typename T>
void TStateMonitor<T>::SetState(T state) {
	_state = state;

	if (!_pDesiredState) {
		_bNeedUpload = true;
		return;
	}

	_bNeedUpload = !IsSameWithDesired();
}

template<typename T>
const T& TStateMonitor<T>::GetState() const {
	return _state;
}

template<typename T>
bool TStateMonitor<T>::IsSameWithDesired() {
	return _state == _pDesiredState->_state;
}

template<typename T>
bool TStateMonitor<T>::IsNeedUpdate() {
	return _bNeedUpload;
}
