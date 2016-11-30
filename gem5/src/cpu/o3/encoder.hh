#ifndef __ENCODER_HH__
#define __ENCODER_HH__

#include <iostream>
#include "sim/sim_object.hh"
#include "params/Encoder.hh"
#include <math.h>



struct data_code_t {
	void *data;
	int data_size;
	int gen_size;
	__uint128_t generator;
	__uint128_t result;
	int result_bits;
	int valid;
	//int result;
};


class Encoder : public SimObject {
public:
	Encoder(EncoderParams *p);

	void enc(data_code_t z);
	void enc2(data_code_t* z);
	void cyclicEncode(data_code_t* z);
	void cyclicDecode(data_code_t* z);
	void hammingEncode(data_code_t* z);
	void hammingDecode(data_code_t* z);
	void bergerDecode(data_code_t* z);
	void bergerEncode(data_code_t* z);
	void single_checksumDecode(data_code_t* z);
	void single_checksumEncode(data_code_t* z);
	void double_checksumDecode(data_code_t* z);
	void double_checksumEncode(data_code_t* z);
	int countOnes(__uint128_t x, __uint128_t val);
	int countOnesCheck(__uint128_t x, __uint128_t val);
	int countBits(__uint128_t x);
	int countOnesB(__uint128_t x);
	__uint128_t fix(__uint128_t val, int syndrome);
};

#endif