using namespace insight;

template <typename T>
TStateMonitor<T>::TStateMonitor(T initialState):
	_bNeedUpload(false),
	_csInitialState(initialState),
	_state(initialState),
	_pCacheState(nullptr){

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
void TStateMonitor<T>::ResetTracing() {
	_bNeedUpload = false;
}

template<typename T>
void TStateMonitor<T>::CacheRunningState(TStateMonitor<T>* pRunningState) {
	_pCacheState = pRunningState;
}

template<typename T>
void TStateMonitor<T>::SetState(T state) {
	_state = state;

	if (!_pCacheState) {
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
bool TStateMonitor<T>::IsSameWithCache() {
	return _state == _pCacheState->_state;
}

template<typename T>
bool TStateMonitor<T>::IsNeedUpload() {
	return _bNeedUpload;
}
