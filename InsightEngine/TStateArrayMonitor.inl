template <class T, unsigned int N>
TStateArrayMonitor<T, N>::TStateArrayMonitor(T val) :
	_uStartSlot(0),
	_uEndSlot(0),
	_bShouldUpload(false),
	_tInitialValue(val),
	_pDesired(nullptr){

	Initialize();
}

template <class T, unsigned int N>
TStateArrayMonitor<T, N>::~TStateArrayMonitor(){

}
template <class T, unsigned int N>
void TStateArrayMonitor<T, N>::SetDesired(TStateArrayMonitor<T, N>* pDesired){
	_pDesired = pDesired;
}

template <class T, unsigned int N>
void TStateArrayMonitor<T, N>::Set(unsigned int slot, T state){
	assert(slot < N);

	_tRealValues[slot] = state;

	// Ensure that a sister state has been set, and if so then use it to manage
	// which slots need to be set in the next update to the pipeline.

	// If there is no sister state, then we default to always requiring an upload
	// of the entire array.

	if (_pDesired == nullptr){
		_bShouldUpload = true;
		_uStartSlot = 0;
		_uEndSlot = N - 1;

		return;
	}

	// Our actions will depend on if this new state matches the sister state or not.

	bool bSameAsDesired = SameAsDesired(slot);


	// Begin by checking if any states changes are already pending.  If not, then if
	// the current state change differs from the sister state, then we have a new 
	// start and end slot.

	if (!_bShouldUpload && !bSameAsDesired){
		_bShouldUpload = true;
		_uStartSlot = slot;
		_uEndSlot = slot;
	}


	// If there is already an upload needed, then we need to update the status of
	// our list.

	if (_bShouldUpload){
		// Updating slot below the current range
		if (slot < _uStartSlot){
			// If the slot is lower than our current start slot, then if the state is
			// different we should consider this the new start state.
			if (!bSameAsDesired) {
				_uStartSlot = slot;
			}
		}
		// Updating slot at the lower end point
		else if (slot == _uStartSlot){
			// If the states don't match, then we retain the same starting slot.
			// Otherwise, we search toward the end state and see if we can reduce
			// the range of the states that need to be set.
			if (bSameAsDesired) {
				_SearchFromBelow();
			}
		}
		// Updating slot inside the current range
		else if (_uStartSlot < slot && slot < _uEndSlot){
			// If the change is between our two endpoints, it doesn't matter.  
			// Regardless of if they are the same or not, we still have to bind
			// the same number of states anyways.
		}
		// Updating slot at the upper end point
		else if (slot == _uEndSlot){
			// If the states don't match, then we retain the same ending slot.
			// Otherwise, we search toward the start slot and see if we can reduce
			// the range of the states that need to be set.
			if (bSameAsDesired) {
				_SearchFromAbove();
			}
		}
		// Updating slot above the current range
		else if (_uEndSlot < slot){
			// If the slot is lower than our current start slot, then if the state is
			// different we should consider this the new start state.
			if (!bSameAsDesired) {
				_uEndSlot = slot;
			}
		}
	}
}
//--------------------------------------------------------------------------------
template <class T, unsigned int N>
void TStateArrayMonitor<T, N>::_SearchFromBelow(){
	// Here we start from the current start slot location, and iterate upward
	// until we encounter the end slot.  As soon as we find a difference, we
	// terminate the iteration, which will automatically make the start slot update
	// to the appropriate location.
	//
	// Note that the iteration will not allow the StartSlot and EndSlot to go past
	// eachother.  Instead, they can end at the same location, and then the final
	// check is made after the loop to see if that last slot is the same or not.

	for (; _uStartSlot < _uEndSlot; _uStartSlot++)
	{
		if (!SameAsDesired(_uStartSlot))
			break;
	}

	// If no differences have been found, we compare the last available slot.  If
	// they are the same, we update the status to reflect that.  This means 
	// resetting the update flag and the slot markers.

	if (_uStartSlot == _uEndSlot && SameAsDesired(_uStartSlot)) {
		Reset();
	}
}
//--------------------------------------------------------------------------------
template <class T, unsigned int N>
void TStateArrayMonitor<T, N>::_SearchFromAbove(){
	// Here we start from the current end slot location, and iterate downward
	// until we encounter the start slot.  As soon as we find a difference, we
	// terminate the iteration, which will automatically make the end slot update
	// to the appropriate location.
	//
	// Note that the iteration will not allow the StartSlot and EndSlot to go past
	// eachother.  Instead, they can end at the same location, and then the final
	// check is made after the loop to see if that last slot is the same or not.

	for (; _uEndSlot > _uStartSlot; _uEndSlot--)
	{
		if (!SameAsDesired(_uEndSlot))
			break;
	}

	// If no differences have been found, we compare the last available slot.  If
	// they are the same, we update the status to reflect that.  This means 
	// resetting the update flag and the slot markers.

	if (_uStartSlot == _uEndSlot && SameAsDesired(_uEndSlot)) {
		Reset();
	}
}
template <class T, unsigned int N>
bool TStateArrayMonitor<T, N>::SameAsDesired(unsigned int slot){
	assert(slot < N);

	return(_tRealValues[slot] == _pDesired->_tRealValues[slot]);
}

template <class T, unsigned int N>
bool TStateArrayMonitor<T, N>::ShouldUpload(){
	return(_bShouldUpload);
}

template <class T, unsigned int N>
unsigned int TStateArrayMonitor<T, N>::GetStartSlot(){
	return(_uStartSlot);
}

template <class T, unsigned int N>
unsigned int TStateArrayMonitor<T, N>::GetEndSlot(){
	return(_uEndSlot);
}

template <class T, unsigned int N>
unsigned int TStateArrayMonitor<T, N>::GetRange(){
	return(_uEndSlot - _uStartSlot + 1);
}

template <class T, unsigned int N>
void TStateArrayMonitor<T, N>::Initialize(){
	for (unsigned int i = 0; i < N; i++)
		Set(i, _tInitialValue);
}

template <class T, unsigned int N>
void TStateArrayMonitor<T, N>::Reset(){
	_uStartSlot = 0;
	_uEndSlot = 0;
	_bShouldUpload = false;
}

template <class T, unsigned int N>
T TStateArrayMonitor<T, N>::Get(unsigned int slot) const{
	assert(slot < N);

	return(_tRealValues[slot]);
}

template <class T, unsigned int N>
T* TStateArrayMonitor<T, N>::GetFirstSlotLocation(){
	return(&_tRealValues[_uStartSlot]);
}

template <class T, unsigned int N>
T* TStateArrayMonitor<T, N>::GetSlotLocation(unsigned int slot){
	assert(slot < N);

	return(&_tRealValues[slot]);
}