﻿// exdieslib.cpp, v1.81 2014/03/02
// coded by asmodean

// contact: 
//   web:   http://asmodean.reverse.net
//   email: asmodean [at] hush.com
//   irc:   asmodean on efnet (irc.efnet.net)

// This tool extracts encrypted *.lib archives used by various light games.

// 2023.3.1 Modified By Dir-A

#include "LIBP.h"
#include "LIBU.h"
#include "Tools.h"
#include "LIB_Decoder.h"


void PrintfInfo(char* argv[])
{
	PutConsole(L"exdieslib v1.81 by asmodean\n\n");
	PutConsole(L"Add new encryption support by Dir-A 2023.2.27\n\n");
	printf("usage: %s <input.lib|input.dat> <key_index> [-flatten]\n\n", argv[0]);
	PutConsole(L"\tkey_index = -1 -> no encryption\n");
	PutConsole(L"\tkey_index =  0 -> Dies irae\n");
	PutConsole(L"\tkey_index =  1 -> さかしき人にみるこころ\n");
	PutConsole(L"\tkey_index =  2 -> あるす☆まぐな！−ARS：MAGNA−\n");
	PutConsole(L"\tkey_index =  3 -> タペストリー tapestry -you will meet yourself-\n");
	PutConsole(L"\tkey_index =  4 -> どんちゃんがきゅ〜\n");
	PutConsole(L"\tkey_index =  5 -> Dies irae Also sprach Zarathustra -die Wiederkunft-\n");
	PutConsole(L"\t                  Dies irae 〜Acta est Fabula〜\n");
	PutConsole(L"\t                  Dies irae 〜Acta est Fabula〜 −Scharlachrot Grun−\n");
	PutConsole(L"\t                  Dies irae 〜Amantes amentes〜\n");
	PutConsole(L"\tkey_index =  6 -> Soranica Ele−ソラニカ エレ−\n");
	PutConsole(L"\tkey_index =  7 -> まじのコンプレックス DL版\n");
	PutConsole(L"\tkey_index =  8 -> PARADISE LOST 新装版\n");
	PutConsole(L"\tkey_index =  9 -> 神咒神威神楽 超先行 体験版\n");
	PutConsole(L"\tkey_index = 10 -> Vermilion -Bind of Blood-\n");
	PutConsole(L"\tkey_index = 11 -> オメルタ〜沈黙の掟〜\n");
	PutConsole(L"\tkey_index = 12 -> 神咒神威神楽\n");
	PutConsole(L"\tkey_index = 13 -> かみのゆ\n");
	PutConsole(L"\tkey_index = 14 -> Zero Infinity -Devil of Maxwell-\n");
	PutConsole(L"\tkey_index = 15 -> しろのぴかぴかお星さま (v2)\n");
	PutConsole(L"\tkey_index = 16 -> 神咒神威神楽 曙之光\n");
	PutConsole(L"\tkey_index = 17 -> BRAVA!! (v2)\n");
	PutConsole(L"\tkey_index = 18 -> Electro Arms -Realize Digital Dimension- (v2)\n");
	PutConsole(L"\tkey_index = 19 -> 相州戦神館學園 八命陣 (v2)\n");

	//Add By Dir-A
	PutConsole(L"\tkey_index = 20 -> Triangle Love -アプリコットフィズ- PKG / DL\n");
	PutConsole(L"\tkey_index = 90 -> 恋音セ・ピアーチェ PKG [New]\n");
	PutConsole(L"\tkey_index = 91 -> 不運と幸運と恋占いのタロット PKG [New]\n");
	PutConsole(L"\tkey_index = 92 -> その花が咲いたら、また僕は君に出逢う PKG [New]\n");
	PutConsole(L"\tkey_index = 93 -> 忘却執事と恋するお嬢様の回想録 PKG [New]\n");
	PutConsole(L"\tkey_index = 94 -> 初恋＊シンドローム DL [New]\n");
	PutConsole(L"\tkey_index = 95 -> 二人と始める打算的なラブコメ PKG [New]\n");
	PutConsole(L"\tkey_index = 96 -> シルヴァリオ ラグナロク [New]\n");
	PutConsole(L"\tkey_index = 97 -> シルヴァリオ ヴェンデッタ - Verse of Orpheus - [New]\n");
	PutConsole(L"\tkey_index = 98 -> シルヴァリオ トリニティ -Beyond the Horizon- [New]\n");
	PutConsole(L"\tkey_index = 99 -> Dies irae Interview with Kaziklu Bey [ENG] [New]\n");
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		PrintfInfo(argv);
		return 0;
	}

	//Parame Init
	size_t keyIndex = atol(argv[2]);
	std::string fileName(argv[1]);
	bool isFlatten = argc > 3 && !strcmp(argv[3], "-flatten");

	//Open Pack
	FILE* fpPack = nullptr;
	errno_t err = fopen_s(&fpPack, fileName.c_str(), "rb");
	if (!fpPack || err) return 0;

	//Check Signature
	LIBPHDR header = { 0 };
	LIB_Decoder(fpPack, keyIndex, &header, sizeof(header), 0);
	if (!memcmp(header.signature, "LIBP", 4))
	{
		LIBP libp(fpPack, keyIndex, isFlatten);
	}
	else
	{
		LIBU_Extract(fpPack, keyIndex, ".", 0, 0, isFlatten);
	}

	fclose(fpPack);
	return 0;
}

