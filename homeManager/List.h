#ifndef List_h
#define List_h

/******************************************
List: data structure to dynamically store different types of objects
*/

template<typename T> class List {
public:
	typedef T* iterator;
	List() {
		_internalArray = NULL;
		_endPosition = 0;
		_allocBlocks = 0;
	}
	~List() {
		delete[] _internalArray;
		_internalArray = NULL;
		_endPosition = 0;
		_allocBlocks = 0;
	}
	void push(T item) {
		if (_endPosition == _allocBlocks) _AllocOneBlock(false);
		_internalArray[_endPosition] = item;
		++_endPosition;
	}
	void pop() {
		if (_endPosition == 0) return;
		--_endPosition;
		_DeAllocOneBlock(false);
	}
	T get(int position = 1) {
		position = position -1;
		if (position > _endPosition) position = _endPosition;
		return _internalArray[position];
	}
	void clear() {
		T* newArray = NULL;
		if (_allocBlocks > 0) newArray = new T[_allocBlocks];
		delete[] _internalArray;
		_internalArray = newArray;
		_endPosition = 0;
	}
	inline iterator begin() { return _internalArray; }
	inline iterator end() { return _internalArray + _endPosition; }
	inline bool empty() { return (_endPosition == 0); }
	inline int size() { return _endPosition; }
	void allocateBlocks(int alloc) {
		_allocBlocks = alloc;
		T* newArray = new T[_allocBlocks];
		for (int i = 0; i < _endPosition; ++i) newArray[i] = _internalArray[i];
		delete[] _internalArray;
		_internalArray = newArray;
	}

private:
	T* _internalArray;
	int _endPosition;
	int _allocBlocks;
	void _AllocOneBlock(bool shiftItems) {
		++_allocBlocks;
		T* newArray = new T[_allocBlocks];
		for (int i = 0; i < _endPosition; ++i) newArray[shiftItems ? (i + 1) : i] = _internalArray[i];
		delete[] _internalArray;
		_internalArray = newArray;
	}
	void _DeAllocOneBlock(bool shiftItems) {
		--_allocBlocks;
		if (_allocBlocks == 0) {
			delete[] _internalArray;
			_internalArray = NULL;
			return;
		}
		T* newArray = new T[_allocBlocks];
		for (int i = 0; i < _endPosition; ++i) newArray[i] = _internalArray[shiftItems ? (i + 1) : i];
		delete[] _internalArray;
		_internalArray = newArray;
	}
};

#endif