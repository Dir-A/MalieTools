#include "LIB_Decoder.h"
#include "Tools.h"
#include "CamelliaDecrypt128.h"
#include "MalieEncryption.h"


void LIB_Decoder(FILE* fpPack, size_t nKeyIndex, void* pBuffer, size_t szDec, size_t posOffset)
{
	static const size_t DECRYPT_BLOCK_LENGTH = 16;

	if (nKeyIndex != -1)
	{
		unsigned long  block_pad = posOffset % DECRYPT_BLOCK_LENGTH;
		unsigned long  aligned_len = (szDec + block_pad + 15) & ~15;
		unsigned char* aligned_buff = new unsigned char[aligned_len];

		unsigned char* block = (unsigned char*)aligned_buff;
		unsigned long  block_count = aligned_len / DECRYPT_BLOCK_LENGTH;

		fseek(fpPack, posOffset - block_pad, SEEK_SET);
		fread(aligned_buff, 0x1, aligned_len, fpPack);

		for (unsigned long iteBlock = 0; iteBlock < block_count; iteBlock++)
		{
			switch (nKeyIndex)
			{
				//恋音セ・ピアーチェ PKG
			case 90:
			{
				MalieEncryption(posOffset, block, koisepi_Key);
			}
			break;

			//不運と幸運と恋占いのタロット PKG
			case 91:
			{
				MalieEncryption(posOffset, block, fuun_Key);
			}
			break;

			//その花が咲いたら、また僕は君に出逢う PKG
			case 92:
			{
				MalieEncryption(posOffset, block, kmh_Key);
			}
			break;

			//忘却執事と恋するお嬢様の回想録 PKG
			case 93:
			{
				MalieEncryption(posOffset, block, koi_Key);
			}
			break;

			//初恋＊シンドローム DL
			case 94:
			{
				MalieEncryption(posOffset, block, hat_Key);
			}
			break;

			//二人と始める打算的なラブコメ PKG
			case 95:
			{
				MalieEncryption(posOffset, block, kim_Key);
			}
			break;

			default:
				CamelliaDecrypt128(nKeyIndex, block, posOffset);
			}

			block += DECRYPT_BLOCK_LENGTH;
			posOffset += DECRYPT_BLOCK_LENGTH;
		}

		memcpy(pBuffer, aligned_buff + block_pad, szDec);

		delete[] aligned_buff;
	}
	else
	{
		fseek(fpPack, posOffset, SEEK_SET);
		fread(pBuffer, 0x1, szDec, fpPack);
	}
}