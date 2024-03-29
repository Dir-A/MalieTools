#include "LIBP.h"
#include "Tools.h"
#include "LIB_Decoder.h"


LIBP::LIBP(FILE* fpPack, size_t nKeyIndex, bool bFlatten)
	: m_fpPack(fpPack), m_nKeyIndex(nKeyIndex), m_bFlatten(bFlatten)
{
	LIBPHDR m_Header = { 0 };
	m_posBaseOffset = 0;

	LIB_Decoder(m_fpPack, nKeyIndex, &m_Header, sizeof(m_Header), m_posBaseOffset);
	m_posBaseOffset += sizeof(m_Header);

	m_pEntries1 = new LIBPENTRY1[m_Header.entry1_count];
	LIB_Decoder(m_fpPack, nKeyIndex, m_pEntries1, sizeof(LIBPENTRY1) * m_Header.entry1_count, m_posBaseOffset);
	m_posBaseOffset += sizeof(LIBPENTRY1) * m_Header.entry1_count;

	m_pEntries2 = new LIBPENTRY2[m_Header.entry2_count];
	LIB_Decoder(m_fpPack, nKeyIndex, m_pEntries2, sizeof(LIBPENTRY2) * m_Header.entry2_count, m_posBaseOffset);
	m_posBaseOffset += sizeof(LIBPENTRY2) * m_Header.entry2_count;

	// Was it really 4k-aligned before?  Maybe this was always a bug...
#if LIBP_VERSION >= 2
	m_posBaseOffset = (m_posBaseOffset + 1023) & ~1023;
#else
	m_posBaseOffset = (m_posBaseOffset + 4095) & ~4095;
#endif

	Extract(".", 0, 1);
}

LIBP::~LIBP()
{
	delete[] m_pEntries1;
	delete[] m_pEntries2;
}

void LIBP::Extract(const std::string& strPreFix, size_t posEntry1Offset, size_t nEntryCount)
{
	char dir_delim = m_bFlatten && strPreFix != "." ? '+' : '/';

	if (!m_bFlatten) { MakeDir(strPreFix.c_str()); }

	LIBPENTRY1* pEntry1 = m_pEntries1 + posEntry1Offset;

	static const size_t LIBPENTRY_FLAG_FILE1 = 0x10000;
	static const size_t LIBPENTRY_FLAG_FILE2 = 0x20000;
	for (size_t iteEntry = 0; iteEntry < nEntryCount; iteEntry++)
	{
		std::string filename = strPreFix + dir_delim + pEntry1[iteEntry].filename;

		if ((pEntry1[iteEntry].flags == LIBPENTRY_FLAG_FILE1) || (pEntry1[iteEntry].flags == LIBPENTRY_FLAG_FILE2))
		{
			unsigned char* pBuffer = new unsigned char[pEntry1[iteEntry].length];
			LIB_Decoder(m_fpPack, m_nKeyIndex, pBuffer, pEntry1[iteEntry].length, m_posBaseOffset + m_pEntries2[pEntry1[iteEntry].offset_index].offset * 1024);

			WriteToFile(filename.c_str(), pBuffer, pEntry1[iteEntry].length);

			delete[] pBuffer;
		}
		else
		{
			Extract(filename, pEntry1[iteEntry].offset_index, pEntry1[iteEntry].length);
		}
	}
}