#pragma once
#include "../math.hpp"


namespace rack {
namespace dsp {


/** Hann window function.
p: proportion from [0, 1], usually `i / (len - 1)`
https://en.wikipedia.org/wiki/Window_function#Hann_and_Hamming_windows
*/
template <typename T>
inline T hann(T p) {
	return 0.5f * (1.f - simd::cos(2*M_PI * p));
}

/** Multiplies the Hann window by a signal `x` of length `len` in-place. */
inline void hannWindow(float *x, int len) {
	for (int i = 0; i < len; i++) {
		x[i] *= hann((float) i / (len - 1));
	}
}

/** Blackman window function.
https://en.wikipedia.org/wiki/Window_function#Blackman_window
A typical alpha value is 0.16.
*/
template <typename T>
inline T blackman(T alpha, T p) {
	return
		+ (1 - alpha) / 2.f
		- 1 / 2.f * simd::cos(2*M_PI * p)
		+ alpha / 2.f * simd::cos(4*M_PI * p);
}

inline void blackmanWindow(float alpha, float *x, int len) {
	for (int i = 0; i < len; i++) {
		x[i] *= blackman(alpha, (float) i / (len - 1));
	}
}


/** Blackman-Nuttall window function.
https://en.wikipedia.org/wiki/Window_function#Blackman%E2%80%93Nuttall_window
*/
template <typename T>
inline T blackmanNuttall(T p) {
	return
		+ 0.3635819f
		- 0.4891775f * simd::cos(2*M_PI * p)
		+ 0.1365995f * simd::cos(4*M_PI * p)
		- 0.0106411f * simd::cos(6*M_PI * p);
}

inline void blackmanNuttallWindow(float *x, int len) {
	for (int i = 0; i < len; i++) {
		x[i] *= blackmanNuttall((float) i / (len - 1));
	}
}

/** Blackman-Harris window function.
https://en.wikipedia.org/wiki/Window_function#Blackman%E2%80%93Harris_window
*/
template <typename T>
inline T blackmanHarris(T p) {
	return
		+ 0.35875f
		- 0.48829f * simd::cos(2*M_PI * p)
		+ 0.14128f * simd::cos(4*M_PI * p)
		- 0.01168f * simd::cos(6*M_PI * p);
}

inline void blackmanHarrisWindow(float *x, int len) {
	for (int i = 0; i < len; i++) {
		x[i] *= blackmanHarris((float) i / (len - 1));
	}
}


} // namespace dsp
} // namespace rack
