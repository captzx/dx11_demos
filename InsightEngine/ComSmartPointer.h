#pragma once

namespace insight {

	template <typename T>
	class ComUniquePtr {
	public:
		ComUniquePtr():_cup(nullptr, com_safe_release) {

		}
		ComUniquePtr(T* to) {
			_cup = to;
		}
		void operator=(T* cup) {
			_cup.reset(cup);
		}
		std::unique_ptr<T, decltype(com_safe_release)*>& operator->() {
			return _cup;
		}
		~ComUniquePtr() {
			_cup = nullptr;
		}
	private:
		std::unique_ptr<T, decltype(com_safe_release)*> _cup;
	};
}