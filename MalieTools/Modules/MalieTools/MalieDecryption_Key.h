#pragma once
#include <cstdint>


namespace MalieTools
{
	namespace MalieDecryption
	{
		namespace Key
		{
			//恋音セ・ピアーチェ PKG
			static const uint32_t Koioto_Se_Piace_PKG[4] = { 0x3E362D69, 0x32266378, 0x792A6C70, 0x4C73243C };

			//不運と幸運と恋占いのタロット PKG
			static const uint32_t Fuun_to_Kouun_to_Koi_Uranai_no_Tarot_PKH[4] = { 0x3571312B, 0x662F6D21, 0x24616C42, 0x6E397170 };

			//その花が咲いたら、また僕は君に出逢う PKG
			static const uint32_t Sono_Hana_ga_Saitara_Mata_Boku_wa_Kimi_ni_Deau_PKG[4] = { 0x452B385A, 0x3542327A, 0x37466776, 0x39663C46 };

			//忘却執事と恋するお嬢様の回想録 PKG
			static const uint32_t Boukyaku_Shitsuji_to_Koi_Suru_Ojou_sama_no_Memoir_PKG[4] = { 0x3C46766D, 0x38436736, 0x4269352B, 0x432A3566 };

			//初恋＊シンドローム DL
			static const uint32_t Hatsukoi_Syndrome_DL[4] = { 0x6E4C2431, 0x6A653772, 0x6D46683A, 0x347A6E5C };

			//二人と始める打算的なラブコメ PKG
			static const uint32_t Kimi_to_Hajimeru_Dasanteki_na_Love_Come_PKG[4] = { 0x36736F67, 0x6466416A, 0x7A62722A, 0x76437176 };

			//シルヴァリオ ラグナロク
			static const uint32_t Silverio_Ragnarok[4] = { 0x70752D37, 0x4A526B58, 0x7841457A, 0x67416155 };

			//シルヴァリオ ヴェンデッタ -Verse of Orpheus-
			static const uint32_t Silverio_Vendetta_Verse_of_Orpheus[4] = { 0x62466D43, 0x2B347A65, 0x74456279, 0x6D467A6F };

			//シルヴァリオ トリニティ-Beyond the Horizon-
			static const uint32_t Silverio_Trinity_Beyond_the_Horizon[4] = { 0x372D3668, 0x336B6234, 0x6635662B, 0x78723869 };

			
			static const uint32_t* g_aKey_List[]
			{
				Koioto_Se_Piace_PKG,
				Fuun_to_Kouun_to_Koi_Uranai_no_Tarot_PKH,
				Sono_Hana_ga_Saitara_Mata_Boku_wa_Kimi_ni_Deau_PKG,
				Boukyaku_Shitsuji_to_Koi_Suru_Ojou_sama_no_Memoir_PKG,
				Hatsukoi_Syndrome_DL,
				Kimi_to_Hajimeru_Dasanteki_na_Love_Come_PKG,
				Silverio_Ragnarok,
				Silverio_Vendetta_Verse_of_Orpheus,
				Silverio_Trinity_Beyond_the_Horizon
			};
		}
	}
}
