from m5.params import *
from m5.SimObject import SimObject

class Encoder(SimObject):
	type = 'Encoder'
	cxx_header = "cpu/o3/encoder.hh"

	instructionQueue_instruction_flag = Param.Int(0, "instructionQueue instruction flag")
	instructionQueue_instruction_faultType = Param.Int(0, "instructionQueue instruction faultType")
	instructionQueue_instruction_faultRate = Param.Float(0.0, "instructionQueue instruction faultRate")
	reorderBuffer_instruction_flag = Param.Int(0, "reorderBuffer instruction flag")
	reorderBuffer_instruction_faultType = Param.Int(0, "reorderBuffer instruction faultType")
	reorderBuffer_instruction_faultRate = Param.Float(0.0, "reorderBuffer instruction faultRate")
	register_integer_flag = Param.Int(0, "register integer flag")
	register_integer_faultType = Param.Int(0, "register integer faultType")
	register_integer_faultRate = Param.Float(0.0, "register integer faultRate")
	register_floatingPoint_flag = Param.Int(0, "register floatingPoint flag")
	register_floatingPoint_faultType = Param.Int(0, "register floatingPoint faultType")
	register_floatingPoint_faultRate = Param.Float(0.0, "register floatingPoint faultRate")

	encodingType = Param.Int(0, "Encoding Type")

	tlb_tag_flag = Param.Int(0, "tlb tag flag")
	tlb_tag_faultType = Param.Int(0, "tlb tag faultType")
	tlb_tag_faultRate = Param.Float(0.0, "tlb tag faultRate")
	tlb_state_flag = Param.Int(0, "tlb state flag")
	tlb_state_faultType = Param.Int(0, "tlb state faultType")
	tlb_state_faultRate = Param.Float(0.0, "tlb state faultRate")
	tlb_data_flag = Param.Int(0, "tlb data flag")
	tlb_data_faultType = Param.Int(0, "tlb data faultType")
	tlb_data_faultRate = Param.Float(0.0, "tlb data faultRate")

	cache_tag_flag = Param.Int(0, "cache tag flag")
	cache_tag_faultType = Param.Int(0, "cache tag faultType")
	cache_tag_faultRate = Param.Float(0.0, "cache tag faultRate")
	cache_state_flag = Param.Int(0, "cache state flag")
	cache_state_faultType = Param.Int(0, "cache state faultType")
	cache_state_faultRate = Param.Float(0.0, "cache state faultRate")
	cache_data_flag = Param.Int(0, "cache data flag")
	cache_data_faultType = Param.Int(0, "cache data faultType")
	cache_data_faultRate = Param.Float(0.0, "cache data faultRate")

	#params = Param.EncoderParams(NULL, "parameters")

class DefaultEncoder(Encoder):
	pass