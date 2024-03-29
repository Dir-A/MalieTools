﻿#include "LIB_Decoder.h"
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
			case 90: MalieEncryption(posOffset, block, g_aKoioto_Se_Piace_Key); break;
			//不運と幸運と恋占いのタロット PKG
			case 91: MalieEncryption(posOffset, block, g_aFuun_to_Kouun_Key); break;
			//その花が咲いたら、また僕は君に出逢う PKG
			case 92: MalieEncryption(posOffset, block, g_aSono_Hana_Key); break;
			//忘却執事と恋するお嬢様の回想録 PKG
			case 93: MalieEncryption(posOffset, block, g_aBoukyaku_Shitsuji_Key); break;
			//初恋＊シンドローム DL
			case 94: MalieEncryption(posOffset, block, g_aHatsukoi_Syndrome_Key); break;
			//二人と始める打算的なラブコメ PKG
			case 95: MalieEncryption(posOffset, block, g_aKimi_To_Hajimeru_Key); break;
			//シルヴァリオ ラグナロク
			case 96: MalieEncryption(posOffset, block, g_aSilverio_Ragnarok_Key); break;
			//シルヴァリオ ヴェンデッタ -Verse of Orpheus-
			case 97: MalieEncryption(posOffset, block, g_aSilverio_Vendetta_Verse_Key); break;
			//シルヴァリオ トリニティ -Beyond the Horizon-
			case 98: MalieEncryption(posOffset, block, g_aSilverio_Trinity_Beyond_Key); break;
			//Dies irae Interview with Kaziklu Bey [ENG]
			case 99: MalieEncryption(posOffset, block, g_aInterview_with_Kaziklu_Bey_ENG_Key); break;

			default: CamelliaDecrypt128(nKeyIndex, block, posOffset);
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
