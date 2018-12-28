template <class T>
TStateMonitor<T>::TStateMonitor(T val) :
	_bShouldUpload(true),
	_tInitialValue(val),
	_pDesired(nullptr){

	Initialize();
	Reset();
}

template <class T>
TStateMonitor<T>::~TStateMonitor(){

}

template <class T>
void TStateMonitor<T>::SetDesired(TStateMonitor<T>* pDesired){
	_pDesired = pDesired;
}

template <class T>
void TStateMonitor<T>::Set(T val){
	_tRealValue = val;

	if (_pDesired == nullptr){
		_bShouldUpload = true;

		return;
	}

	_bShouldUpload = !SameAsDesired();

}

template <class T>
bool TStateMonitor<T>::SameAsDesired(){
	return _tRealValue == _pDesired->_tRealValue;
}

template <class T>
bool TStateMonitor<T>::ShouldUpload(){
	return _bShouldUpload;
}

template <class T>
void TStateMonitor<T>::Initialize(){
	Set(_tInitialValue);
}

template <class T>
void TStateMonitor<T>::Reset(){
	_bShouldUpload = false;
}

template <class T>
T TStateMonitor<T>::Get() const{
	return _tRealValue;
}