#ifndef XOR_SHIFT_128_H

#define XOR_SHIFT_128_H

#include <stdint.h>
#include <string>
#include <vector>
#include <ctime>

namespace XorShifts {
	class XorShift128 {
	private:
		struct dictionary { uint32_t x; uint32_t y; uint32_t z; uint32_t w; };
		uint32_t x;
		uint32_t y;
		uint32_t z;
		uint32_t w;
		uint32_t t;

	public:
		//static const struct dictionary defaults;
		uint32_t randCount = 0;
		struct dictionary seeds;

		void SetSeed(uint32_t w = time(nullptr), uint32_t x = NULL, uint32_t y = NULL, uint32_t z = NULL);

		uint32_t Rand();

		int RandInt(int min, int max);

		float RandFloat(float min, float max);

		template<typename T>
		T* Shuffle(const T* _arr, T* arr, int arrLength) {
			for (int i = 0; i < arrLength; i++) arr[i] = _arr[i];
			for (int i = 0; i <= arrLength - 2; i++) {
				int r = RandInt(i, arrLength - 1);
				T tmp = arr[i];
				arr[i] = arr[r];
				arr[r] = tmp;
			}
			return arr;
		}

		template<typename T>
		std::vector<T> Shuffle(std::vector<T> arr) {
			for (int i = 0; i <= arr.size() - 2; i++) {
				int r = RandInt(i, arr.size() - 1);
				T tmp = arr[i];
				arr[i] = arr[r];
				arr[r] = tmp;
			}
			return arr;
		}
	};
}

//const struct XorShifts::XorShift::dictionary XorShifts::XorShift::defaults = {
//		123456789,
//		362436069,
//		521288629,
//		88675123
//};


#endif // !XOR_SHIFT_128_H