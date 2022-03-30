class ByteStream
{
  public:
	int offset = 7, maxOffset;
	char *buffer;
	// reader
	int readInt();
	int readByte();
	int readVInt();
	std::string readString();
	// memory managers
	bool canRead(int a1);
	bool canWrite(int a1);
	// writer
	void allocate(int chars);
	void writeInt(int a1);
	void writeString(std::string a1);
	void writeUInt(int a1);
	void writeByte(int a1);
	void writeBoolean(bool a1);
	void writeCryptoBytes();
	void writeVInt(int a1);
	void writeDataReference(int a1, int a2);
	// write to client
	void packetize(Player a1, int a2, int a3);
};
void ByteStream::writeCryptoBytes()
{
	buffer[offset] = 255;
	buffer[offset + 1] = 255;
	buffer[offset + 2] = 0;
	buffer[offset + 3] = 0;
	buffer[offset + 4] = 0;
	buffer[offset + 5] = 0;
	buffer[offset + 6] = 0;
	offset += 7;
}
void ByteStream::packetize(Player player, int id, int version)
{
	// packet id
	buffer[0] = (id >> 8 & 0xFF);
	buffer[1] = (id & 0xFF);
	// packet length
	int len = offset - 7;
	buffer[2] = (len >> 16 & 0xFF);
	buffer[3] = (len >> 8 & 0xFF);
	buffer[4] = (len & 0xFF);
	// packet version
	buffer[5] = (version >> 8 & 0xFF);
	buffer[6] = (version & 0xFF);
	writeCryptoBytes();
	send(player.cfd, buffer, offset, 0);
	std::cout << "[S => C] " << int2str(id) << " was sent\n";
}
void ByteStream::writeInt(int a1)
{
	if (canWrite(4))
	{
		buffer[offset] = (a1 >> 24 & 0xFF);
		offset += 1;
		buffer[offset] = (a1 >> 16 & 0xFF);
		offset += 1;
		buffer[offset] = (a1 >> 8 & 0xFF);
		offset += 1;
		buffer[offset] = (a1 & 0xFF);
		offset += 1;
	}
	else
	{
		log("can't write Int: offset out of index!");
	}
}
void ByteStream::writeString(std::string a1 = "none")
{
	if (a1 == "none")
	{
		writeInt(-1);
	}
	else
	{
		int len = a1.length();
		writeInt(len);
		if (canWrite(len))
		{
			for (int index = 0; index < len; index++)
			{
				buffer[offset] = a1[index];
				offset += 1;
			}
		}
		else
		{
			log("can't write string: offset out of index!");
		}
	}
}
void ByteStream::writeUInt(int a1)
{
	if (canWrite(1))
	{
		buffer[offset] = (a1 & 0xFF);
		offset += 1;
	}
	else
	{
		log("can't write UInt: offset out of index!");
	}
}
void ByteStream::writeByte(int a1)
{
	writeUInt(a1);
}
void ByteStream::writeBoolean(bool a1)
{
	if (a1)
	{
		writeUInt(1);
	}
	else
	{
		writeUInt(0);
	}
}
void ByteStream::writeVInt(int a1)
{
	int v1, v2, v3;
	v1 = (((a1 >> 25) & 0x40) | (a1 & 0x3F));
	v2 = ((a1 ^ (a1 >> 31)) >> 6);
	a1 >>= 6;
	if (v2 == 0)
	{
		writeByte(v1);
	}
	else
	{
		writeByte(v1 | 0x80);
		v2 >>= 7;
		v3 = 0;
		if (v2)
		{
			v3 = 0x80;
		}
		writeByte((a1 & 0x7F) | v3);
		a1 >>= 7;
		while (v2 != 0)
		{
			v2 >>= 7;
			v3 = 0;
			if (v2)
			{
				v3 = 0x80;
			}
			writeByte((a1 & 0x7F) | v3);
			a1 >>= 7;
		}
	}
}
void ByteStream::writeDataReference(int a1, int a2)
{
	if (a1 == 0)
	{
		writeVInt(0);
	}
	else
	{
		writeVInt(a1);
		writeVInt(a2);
	}
}
int ByteStream::readInt()
{
	int result;
	if (canRead(4))
	{
		result = ((buffer[offset]) << 24 | (buffer[offset + 1]) << 16 | (buffer[offset + 2]) << 8 | (buffer[offset + 3]));
		offset += 4;
	}
	return result;
}
int ByteStream::readByte()
{
	int result;
	if (canRead(1))
	{
		result = buffer[offset];
		offset += 1;
	}
	return result;
}
int ByteStream::readVInt()
{
	int result, shift, byte, seventh, msb, n;
	while (true)
	{
		byte = readByte();
		if (shift == 0)
		{
			seventh = (byte & 0x40) >> 6;
			msb = (byte & 0x80) >> 7;
			n = byte << 1;
			n = n & ~0x181;
			byte = n | (msb << 7) | seventh;
		}
		result |= (byte & 0x7f) << shift;
		shift += 7;
		if (!(byte & 0x80))
		{
			break;
		}
	}
	return (result >> 1) ^ (-(result & 1));
}
std::string ByteStream::readString()
{
	int length = readInt();
	std::string result;
	if (canRead(length) && length > 0)
	{
		for (int index = 0; index < length; index++)
		{
			result += buffer[offset + index];
		}
		offset += length;
	}
	return result;
}
void ByteStream::allocate(int chars)
{
	buffer = new char[chars + 14]; // 7 for header and 7 for crypto bytes
	offset = 7;
	maxOffset = chars;
};
bool ByteStream::canWrite(int a1)
{
	if ((offset + a1) - maxOffset > 0)
	{
		return false;
	}
	return true;
}
bool ByteStream::canRead(int a1)
{
	if (sizeof(buffer) - (offset + a1) >= 0)
	{
		return true;
	}
	return false;
}
