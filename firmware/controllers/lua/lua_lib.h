/**
 * file lua_lib.h
 */

#define ARRAY_EQUALS "function equals(data1, data2) \
 \
  local index = 1 \
  while data1[index] ~= nil do \
	if data1[index] ~= data2[index] then \
       return -1 - index \
    end \
	index = index + 1 \
  end \
	if nil ~= data2[index] then \
       return -1 - index \
    end \
  return 0 \
end \
	"


#define PRINT_ARRAY "hexstr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \"A\", \"B\", \"C\", \"D\", \"E\", \"F\" } \
\
function toHexString(num)  \
	if num == 0 then \
		return '0' \
	end \
 \
	local result = \"\"   \
	while num > 0 do   \
		local n = num % 16  \
		result = hexstr[n + 1] ..result   \
		num = math.floor(num / 16)   \
	end  \
	return result  \
end   \
\
function arrayToString(arr)  \
	local str = \"\"   \
	local index = 1   \
	while arr[index] ~= nil do  \
		str = str..\" \"..toHexString(arr[index])  \
		index = index + 1  \
	end  \
	return str  \
end  \
 \
\
"

// LSB (Least Significant Byte comes first) "Intel"
#define TWO_BYTES_LSB "function getTwoBytesLSB(data, offset, factor)        \
		return (data[offset + 2] * 256 + data[offset + 1]) * factor   \
	end"

// Little-endian System, "Intel"
#define SET_TWO_BYTES "	function setTwoBytes(data, offset, value) \
		value = math.floor(value) \
		data[offset + 2] = value >> 8 \
		data[offset + 1] = value & 0xff \
	end \
	"

// MOTOROLA order, MSB (Most Significant Byte/Big Endian) comes first.
#define TWO_BYTES_MSB "function getTwoBytesMSB(data, offset, factor)        \
		return (data[offset + 1] * 256 + data[offset + 2]) * factor   \
	end"

#define SET_TWO_BYTES_MSB "	function setTwoBytesMsb(data, offset, value) \
		value = math.floor(value) \
		data[offset + 1] = value >> 8 \
		data[offset + 2] = value & 0xff \
	end \
	"

// one day we shall get Preprocessor macros with C++11 raw string literals
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=55971
#define GET_BIT_RANGE_LSB " \
function getBitRange(data, bitIndex, bitWidth) \
	byteIndex = bitIndex >> 3 \
	shift = bitIndex - byteIndex * 8 \
	value = data[1 + byteIndex] \
	if (shift + bitWidth > 8) then \
		value = value + data[2 + byteIndex] * 256 \
	end \
	mask = (1 << bitWidth) - 1 \
	return (value >> shift) & mask \
end \
"


