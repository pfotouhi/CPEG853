#include "encoder.hh"



Encoder::Encoder(EncoderParams *params) : SimObject(params) {
	/*printf("made enc\n\n");
	printf("instructionQueue-instruction-flag: %i\n", params->instructionQueue_instruction_flag);
    printf("instructionQueue-instruction-faultType: %i\n", params->instructionQueue_instruction_faultType);
    printf("instructionQueue-instruction-faultRate: %f\n", params->instructionQueue_instruction_faultRate);
    printf("reorderBuffer-instruction-flag: %i\n", params->reorderBuffer_instruction_flag);
    printf("reorderBuffer-instruction-faultType: %i\n", params->reorderBuffer_instruction_faultType);
    printf("reorderBuffer-instruction-faultRate: %f\n", params->reorderBuffer_instruction_faultRate);
    printf("register-integer-flag: %i\n", params->register_integer_flag);
    printf("register-integer-faultType: %i\n", params->register_integer_faultType);
    printf("register-integer-faultRate: %f\n", params->register_integer_faultRate);
    printf("register-floatingPoint-flag: %i\n", params->register_floatingPoint_flag);
    printf("register-floatingPoint-faultType: %i\n", params->register_floatingPoint_faultType);
    printf("register-floatingPoint-faultRate: %f\n", params->register_floatingPoint_faultRate);
    printf("tlb-tag-flag: %i\n", params->tlb_tag_flag);
    printf("tlb-tag-faultType: %i\n", params->tlb_tag_faultType);
    printf("tlb-tag-faultRate: %f\n", params->tlb_tag_faultRate);
    printf("tlb-state-flag: %i\n", params->tlb_state_flag);
    printf("tlb-state-faultType: %i\n", params->tlb_state_faultType);
    printf("tlb-state-faultRate: %f\n", params->tlb_state_faultRate);
    printf("tlb-data-flag: %i\n", params->tlb_data_flag);
    printf("tlb-data-faultType: %i\n", params->tlb_data_faultType);
    printf("tlb-data-faultRate: %f\n", params->tlb_data_faultRate);
    printf("cache-tag-flag: %i\n", params->cache_tag_flag);
    printf("cache-tag-faultType: %i\n", params->cache_tag_faultType);
    printf("cache-tag-faultRate: %f\n", params->cache_tag_faultRate);
    printf("cache-state-flag: %i\n", params->cache_state_flag);
    printf("cache-state-faultType: %i\n", params->cache_state_faultType);
    printf("cache-state-faultRate: %f\n", params->cache_state_faultRate);
    printf("cache-data-flag: %i\n", params->cache_data_flag);
    printf("cache-data-faultType: %i\n", params->cache_data_faultType);
    printf("cache-data-faultRate: %f\n", params->cache_data_faultRate);*/
    instructionQueue_instruction_flag= params->instructionQueue_instruction_flag;
	instructionQueue_instruction_faultType= params->instructionQueue_instruction_faultType;
	instructionQueue_instruction_faultRate= params->instructionQueue_instruction_faultRate;
	reorderBuffer_instruction_flag= params->reorderBuffer_instruction_flag;
	reorderBuffer_instruction_faultType= params->reorderBuffer_instruction_faultType;
	reorderBuffer_instruction_faultRate= params->reorderBuffer_instruction_faultRate;
	register_integer_flag= params->register_integer_flag;
	register_integer_faultType= params->register_integer_faultType;
	register_integer_faultRate= params->register_integer_faultRate;
	register_floatingPoint_flag= params->register_floatingPoint_flag;
	register_floatingPoint_faultType= params->register_floatingPoint_faultType;
	register_floatingPoint_faultRate= params->register_floatingPoint_faultRate;
	tlb_tag_flag= params->tlb_tag_flag;
	tlb_tag_faultType= params->tlb_tag_faultType;
	tlb_tag_faultRate= params->tlb_tag_faultRate;
	tlb_state_flag= params->tlb_state_flag;
	tlb_state_faultType= params->tlb_state_faultType;
	tlb_state_faultRate= params->tlb_state_faultRate;
	tlb_data_flag= params->tlb_data_flag;
	tlb_data_faultType= params->tlb_data_faultType;
	tlb_data_faultRate= params->tlb_data_faultRate;
	cache_tag_flag= params->cache_tag_flag;
	cache_tag_faultType= params->cache_tag_faultType;
	cache_tag_faultRate= params->cache_tag_faultRate;
	cache_state_flag= params->cache_state_flag;
	cache_state_faultType= params->cache_state_faultType;
	cache_state_faultRate= params->cache_state_faultRate;
	cache_data_flag= params->cache_data_flag;
	cache_data_faultType= params->cache_data_faultType;
	cache_data_faultRate= params->cache_data_faultRate;
    //params = passedParams;
}

int
Encoder::countOnes(__uint128_t x, __uint128_t val) {
	int ones = 0;
	int temp = 0;
	__uint128_t z = x;// >> 8;
	z = z & val;
	while (z) {
		temp = z & 1;
		if (temp) {
			ones += 1;
		}
		z = z >> 1;
	}
	return ones;
}

int
Encoder::countOnesB(__uint128_t x) {
	int ones = 0;
	int temp = 0;
	while (x) {
		temp = x & 1;
		if (temp) {
			ones += 1;
		}
		x = x >> 1;
	}
	return ones;
}

int
Encoder::countOnesCheck(__uint128_t x, __uint128_t val) {
	int ones = 0;
	int temp = 0;
	x = x & val;
	//std::cout<<"--x: " << ba<<"\n";
	//printf("--x: %x\n", x);
	while (x) {
		temp = x & 1;
		if (temp) {
			ones += 1;
		}
		x = x >> 1;
	}
	return ones;
}
int 
Encoder::countBits(__uint128_t x) {
	int bits = 0;
	while(x) {
		bits += 1;
		x = x >> 1;
	}
	return bits;
}

__uint128_t
Encoder::fix(__uint128_t val, int syndrome) {
	__uint128_t shifts[72] = { 0x80, 0x1, 0x2, 0x100, 0x4, 0x200, 0x400, 0x800, 0x8, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x40000, 0x10, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000, 0x1000000, 0x2000000, 0x4000000, 0x8000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x100000000, 0x200000000, 0x20, 0x400000000, 0x800000000, 0x1000000000, 0x2000000000, 0x4000000000, 0x8000000000, 0x10000000000, 0x20000000000, 0x40000000000, 0x80000000000, 0x100000000000, 0x200000000000, 0x400000000000, 0x800000000000, 0x1000000000000, 0x2000000000000, 0x4000000000000, 0x8000000000000, 0x10000000000000, 0x20000000000000, 0x40000000000000, 0x80000000000000, 0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000, 0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000, 0x100000000000000, 0x40, 0x200000000000000, 0x400000000000000, 0x800000000000000, 0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000};
	shifts[63] = shifts[63] << 8;
	shifts[65] = shifts[65] << 8;
	shifts[66] = shifts[66] << 8;
	shifts[67] = shifts[67] << 8;
	shifts[68] = shifts[68] << 8;
	shifts[69] = shifts[69] << 8;
	shifts[70] = shifts[70] << 8;
	shifts[71] = shifts[71] << 8;

	val = val ^ shifts[syndrome-128];

	return val;
}

void
Encoder::hammingEncode(data_code_t* z) {
	__uint128_t val = 0;
	std::memcpy(&val, (z->data), z->data_size);
	

	__uint128_t parityMatrix[8] = {0xFFFFFFFFFFFFFFFF, 0xFE00000000000000, 0x1FFFFFFFC000000, 0x1FFFE0003FFF800, 0x1FE01FE03FC07F0, 0xF1E1E1E1E3C3C78E, 0xCD9999999B33366D, 0xAB55555556AAAD5B}; //ordered bit 0-7

	int i = 0;
	short parityBits[8] = {0,0,0,0,0,0,0,0};
	short helper = 0;
	while (i < 7) {
		helper = helper << 1;
		parityBits[7-i] = countOnes(parityMatrix[7-i], val)%2;
		helper = helper ^ parityBits[7-i];
		i += 1;
	}
	parityBits[0] = (countOnes(parityMatrix[0], val) + countOnes(helper, 0xff))%2;

	i = 0;
	helper = 0;
	while (i < 8) {
		helper = helper << 1;
		helper = helper ^ parityBits[i];
		i += 1;
	}
	__uint128_t out = val;
	out = (out << 8) ^ helper;


	z->result = out;
	z->result_bits = countBits(out);
	//printf("out: %x%x%x\n", (int)(v>>64), (int)(v>>32), (int)(v));
}

void
Encoder::hammingDecode(data_code_t* z) {
	__uint128_t out = 0;
	std::memcpy(&out, (z->data), z->data_size);
	
	__uint128_t syndromeGenMatrix[8] = {0xFFFFFFFFFFFFFFFF, 0xFE00000000000000, 0x1FFFFFFFC000000, 0x1FFFE0003FFF800, 0x1FE01FE03FC07F0, 0xF1E1E1E1E3C3C78E, 0xCD9999999B33366D, 0xAB55555556AAAD5B}; //ordered bit 7-0
	
	syndromeGenMatrix[0] = syndromeGenMatrix[0] << 8;
	syndromeGenMatrix[0] = syndromeGenMatrix[0] ^ 0xff;

	syndromeGenMatrix[1] = syndromeGenMatrix[1] << 8;
	syndromeGenMatrix[1] = syndromeGenMatrix[1] ^ 0x40;
	
	syndromeGenMatrix[2] = syndromeGenMatrix[2] << 8;
	syndromeGenMatrix[2] = syndromeGenMatrix[2] ^ 0x20;

	syndromeGenMatrix[3] = syndromeGenMatrix[3] << 8;
	syndromeGenMatrix[3] = syndromeGenMatrix[3] ^ 0x10;
	
	syndromeGenMatrix[4] = syndromeGenMatrix[4] << 8;
	syndromeGenMatrix[4] = syndromeGenMatrix[4] ^ 0x08;

	syndromeGenMatrix[5] = syndromeGenMatrix[5] << 8;
	syndromeGenMatrix[5] = syndromeGenMatrix[5] ^ 0x04;
	
	syndromeGenMatrix[6] = syndromeGenMatrix[6] << 8;
	syndromeGenMatrix[6] = syndromeGenMatrix[6] ^ 0x02;
	
	syndromeGenMatrix[7] = syndromeGenMatrix[7] << 8;
	syndromeGenMatrix[7] = syndromeGenMatrix[7] ^ 0x01;

	short syndromeBits[8] = {0,0,0,0,0,0,0,0};
	int j = 0;
	while (j < 8) {
		syndromeBits[7-j] = countOnes(syndromeGenMatrix[j], out) %2;
		j += 1;
	}
	int checker = 0;
	j = 0;
	while (j < 8) {
		checker = checker << 1;
		checker = checker ^ syndromeBits[7-j];
		j += 1;
	}

	if(checker == 0) {
		z->valid = 1;
	}
	else if(checker > 127) {
		out = fix(out, (int)(checker));
		z->valid = 1;
	}
	else {
		z->valid = 0;
	}
	out = out >> 8;
	z->result = out;
	z->result_bits = countBits(out);
	//printf("recoverd: %x%x%x\n", (int)(recovered>>64), (int)(recovered>>32), (int)(recovered));
}

void
Encoder::enc(data_code_t z) {
	long long int j = 0;
	std::memcpy(&j, (z.data), z.data_size);
	printf("here is a: %lli\n", j);
	//printf("here is z: %i\n", z.data[0]);
	z.data_size = 12;
}
void
Encoder::enc2(data_code_t* z) {
	long long int j = 0;
	std::memcpy(&j, (z->data), z->data_size);
	printf("here is a: %lli\n", j);
	//printf("here is z: %i\n", j->data[0]);
	z->data_size = 12;
	z->result = 4350932;
}

void
Encoder::cyclicEncode(data_code_t* z) {
	__uint128_t val = 0;
	__uint128_t gen = z->generator;
	std::memcpy(&val, (z->data), z->data_size);
	//std::memcpy(&gen, (z->generator), z->gen_size);
	__uint128_t t = 0;
	//int loop = 0;
	while (gen) {
		if((gen & 1) == 1) {
			t = t ^ val;
		}
		val = val << 1;
		gen = gen >> 1;
		//loop += 1;
	}
	//printf("the new word is: %i\n", t);
	z->result = t;
	z->result_bits = countBits(t);
}

void
Encoder::cyclicDecode(data_code_t* z) {
	//unsigned long long int val = atoll(argv[1]); //21835;
	//unsigned int gen = atoi(argv[2]);// 25;
	__uint128_t val = 0;
	__uint128_t gen = z->generator;
	std::memcpy(&val, (z->data), z->data_size);
	//std::memcpy(&gen, (z->generator), z->gen_size);

	unsigned int numBitsGen = 0;
	unsigned int temp = gen;
	while (temp) {
		numBitsGen += 1;
		temp = temp >> 1;
	}
	
	unsigned int numBitsVal = 0;
	temp = val;
	while (temp) {
		numBitsVal += 1;
		temp = temp >> 1;
	}

	
	unsigned int out = 0;
	//unsigned int preLength = numBitsVal;
	unsigned int mask = 1;
	unsigned int prevLen = numBitsVal;
	int i = 0;
	//int j = 0;
	int rem = val;
	//int last = 0;
	//int prevVal;// = val;
	while (val > gen) {
		mask = 0;
		//int prevVal = val;
		prevLen = numBitsVal;
		i = numBitsVal-numBitsGen-1;
		if (i >= 0) {
			mask = 1;
		}
		while (i > 0) {
			mask = mask << 1;
			mask += 1;
			i -=1;
		}
		
		if (val >= gen || numBitsGen == numBitsVal) {
			out = out << 1;
			out += 1;
		}
		else {
			out += 1;
		}

		temp = val >> (numBitsVal-numBitsGen);
		//printf("temp: %i val: %i\n", temp, val);
		temp = temp ^ gen;
		
		val = val & mask;
		temp = temp << (numBitsVal-numBitsGen);
		val = temp ^ val;
		rem = val;
		numBitsVal = 0;
		temp = val;
		while (temp) {
			numBitsVal += 1;
			temp = temp >> 1;
		}
		if((prevLen - numBitsVal) > 1 && val > gen) {
			out = out << (prevLen - numBitsVal - 1);
		}
		
	}
	//printf("numBitsVal %i\n", numBitsVal);
	if(numBitsVal == numBitsGen) {
		if((prevLen - numBitsVal) > 1 && val <= gen) {
			out = out << (prevLen - numBitsGen-1);
		}
		//printf("out: %i\n", out);
		out = out << 1;
		out = out + 1;
		rem = val ^ gen;
	}
	else if((prevLen - numBitsVal) > 1 && val < gen) {
		out = out << (prevLen - numBitsGen);
	}
	//printf("out: %i rem: %i\n", out, rem);
	z->result = out;
	if(rem == 0) {
		z->valid = 1;
	}
	else {
		z->valid = 0;
	}
	z->result_bits = countBits(out);
}

void
Encoder::bergerEncode(data_code_t* z) {
	__uint128_t val = 0;
	std::memcpy(&val, (z->data), z->data_size);
	__uint128_t out = 0;
	int x = floor(log2(floor(log2(val)) + 1.0));
	int ones = countOnesB(val);
	//printf("%i %i %llx\n", x, ones, val);
	__uint128_t mask = 0;
	int i = 0;
	while (i <= x) {
		mask = mask << 1;
		mask += 1;
		i += 1;
	}
	out = (val << (x+1)) ^ (~ones & mask);
	//printf("%x\n", out);
	//printf("%x\n", out >> 8);
	z->result = out;
	z->result_bits = countBits(out);
}

void
Encoder::bergerDecode(data_code_t *z) {
	__uint128_t out = 0;
	std::memcpy(&out, (z->data), z->data_size);
	int mm = 0xf;
	int shifter = 4;
	//int check = 0;
	while(countBits(out>>shifter) > pow(2.0, (double)shifter)) {
		shifter += 1;
		mm = mm<< 1;
		mm += 1;
	}
	//printf("mm: %x\n", mm);
	//printf("check bits: %x\n", (~(out&mm)&mm));
	if((~(out&mm)&mm) == countOnesB(out>>shifter)) {
		//printf("success\n");
		z->valid = 1;
	}
	else {
		z->valid = 0;
	}
	z->result = out>>shifter;
	z->result_bits = countBits(out);
	//printf("extra bits: %i\n", shifter);
}

void
Encoder::single_checksumEncode(data_code_t *z) {
	__uint128_t val = 0;
	std::memcpy(&val, (z->data), z->data_size);
	int shift = 16;
	__uint128_t out = 0;
	__uint128_t tval = val;
	__uint128_t mask = 0xffff;
	__uint128_t sum = 0;
	
	while(tval) {
		__uint128_t t = tval & mask;
		sum = sum + t;
		sum = sum & mask;
		tval = tval >> shift;
	}
	out = (val << shift) ^ sum;
	//printf("sum: %x\n", sum);
	//printf("newVal: %x\n", out);
	z->result = out;
	z->result_bits = countBits(out);
}

void
Encoder::single_checksumDecode(data_code_t *z) {
	__uint128_t out = 0;
	__uint128_t out2 = 0;
	int shift = 16;
	std::memcpy(&out, (z->data), z->data_size);
	__uint128_t cmask = 0xffff;
	__uint128_t check = out & cmask;
	out2 = out;
	out = out >> shift;
	__uint128_t csum = 0;
	while(out) {
		__uint128_t t = out & cmask;
		csum = csum + t;
		csum = csum & cmask;
		out = out >> shift;
	}
	if (check == csum) {
		z->valid = 1;
	}
	else {
		z->valid = 0;
	}
	z->result = out2 >> shift;
	z->result_bits = countBits(out2>>shift);
}

void
Encoder::double_checksumEncode(data_code_t *z) {
	__uint128_t val = 0;
	std::memcpy(&val, (z->data), z->data_size);
	int shift = 16;
	__uint128_t out = 0;
	__uint128_t tval = val;
	__uint128_t mask = 0xffff;
	__uint128_t addMask = 0x1ffff;
	__uint128_t sum = 0;
	
	while(tval) {
		__uint128_t t = tval & mask;
		sum = sum + t;
		sum = sum & addMask;
		tval = tval >> shift;
	}
	out = (val << (shift+1)) ^ sum;
	z->result = out;
	z->result_bits = countBits(out);
	//printf("out: %x sum: %x\n", (int)out, (int)sum);
}

void
Encoder::double_checksumDecode(data_code_t *z) {
	__uint128_t out = 0;
	__uint128_t out2 = 0;
	std::memcpy(&out, (z->data), z->data_size);
	int shift = 16;
	__uint128_t cmask = 0xffff;
	__uint128_t caddMask = 0x1ffff;
	__uint128_t check = out & caddMask;
	out2 = out;
	out = out >> (shift+1);
	__uint128_t csum = 0;
	while(out) {
		__uint128_t t = out & cmask;
		csum = csum + t;
		csum = csum & caddMask;
		out = out >> shift;
	}
	if (check == csum) {
		z->valid = 1;
	}
	else {
		z->valid = 0;
	}
	z->result = out2 >> (shift+1);
	z->result_bits = countBits(out2>>(shift+1));
	//printf("check: %x csum: %x\n", (int)check, (int)csum);
}

Encoder*
EncoderParams::create() {
	return new Encoder(this);
}
