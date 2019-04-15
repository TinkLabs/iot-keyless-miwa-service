//******************************************************************************
//* NAME         : AlV2Edl.h
//* FUNCTION     : ALV2 APIJ DLL
//* PROGRAMED    : 12.07.23 CBE/堂谷内
//* REMARK       : 
//* HISTORY      : 
//* ID -- DATE -------- NOTE ---------------------------------------------------
//*<00>12.07.23 CBE/堂谷内      新規作成
//******************************************************************************
#if !defined(ALV2EDL_H)

	#define ALV2EDL_H

	//==========================================================================
	//  データ構造定義
	//==========================================================================

	// エラーコード
	typedef unsigned long EDLERR;				//	APIJ エラーコードの型

	#define EDLERR_NORMAL		0x00000000		//	正常終了

	// 設定異常系
	#define EDLERR_RD_EDLID		0x00010010		//	EDL-ID 読込みエラー
	#define EDLERR_INV_EDLID	0x00010020		//	EDL-ID 値異常

	// エンコード異常系
	#define EDLERR_HTLCD		0x00020010		//	ホテルコード異常
	#define EDLERR_CRDTYP		0x00020020		//	カード種別異常
	#define EDLERR_CRDNO		0x00020030		//	カード枝番異常
	#define EDLERR_ISSNUM		0x00020040		//	カード発行枚数異常
	#define EDLERR_CITIME		0x00020050		//	チェックイン日時異常
	#define EDLERR_COTIME		0x00020060		//	チェックアウト日時異常
	#define EDLERR_SUMFG		0x00020070		//	サマータイムフラグ異常
	#define EDLERR_SHUTFG		0x00020080		//	シャットアウトフラグ異常
	#define EDLERR_BUZFG		0x00020090		//	ブザー通知フラグ異常
	#define EDLERR_SPZFG		0x000200A0		//	スペシャルドアフラグ異常
	#define EDLERR_MAINROM		0x000200B0		//	メインルームNo.異常
	#define EDLERR_2NDROM		0x000200C0		//	セカンドルームNo.異常
	#define EDLERR_LCKDAT		0x000200D0		//	ロックデータ異常
	#define EDLERR_DEADBOLT		0x000200E0		//	デッドボルトオーバーライドフラグ異常

	// デコード異常系
	#define EDLERR_BLANKCRD		0x00030010		//	ブランクカード(初期化されたカード)
	#define EDLERR_INVHTLCD		0x00030020		//	ホテルコード不一致
	#define EDLERR_INVCRDCD		0x00030030		//	不正カード(GU/MT 以外 or カードコード不明)
	#define EDLERR_DEC			0x00030040		//	復号化失敗

	//==========================================================================
	//  プロトタイプ宣言
	//==========================================================================
	#if defined(__cplusplus)
	extern "C" {
	#endif

		// 1Kカードのロックデータ生成（暗号化）
		EDLERR __stdcall EDL_Inf2Enc(
			unsigned char* pEnc1,	//	セクタ1に書き込むデータバイト列 [OUT]
			unsigned char* pEnc4,	//	セクタ4に書き込むデータバイト列 [OUT]
			unsigned char* pEnc5,	//	セクタ5に書き込むデータバイト列 [OUT]
			unsigned long ulHtl,	//	暗号化済みホテルコード [IN]
			const unsigned char* pInf,	//	カード情報文字列 [IN]
			const unsigned char* pSpFlg	//	スペシャルドアフラグ [IN]
			);

		// 1Kカードのロックデータ生成（暗号化）EDL-ID指定あり
		EDLERR __stdcall EDL_Inf2EncWithEdl(
			unsigned char* pEnc1,	//	セクタ1に書き込むデータバイト列 [OUT]
			unsigned char* pEnc4,	//	セクタ4に書き込むデータバイト列 [OUT]
			unsigned char* pEnc5,	//	セクタ5に書き込むデータバイト列 [OUT]
			unsigned long ulHtl,	//	暗号化済みホテルコード [IN]
			const unsigned char* pEdlId,//	EDL-ID [IN]
			const unsigned char* pInf,	//	カード情報文字列 [IN]
			const unsigned char* pSpFlg	//	スペシャルドアフラグ [IN]
		);

		// 1Kカードのロックデータ翻訳（復号化）
		EDLERR __stdcall EDL_Enc2Inf(
			unsigned char* pInf,	//	翻訳後のカード情報文字列 [OUT]
			unsigned char* pSpFlg,	//	スペシャルドアフラグ [OUT]
			unsigned long ulHtl,	//	暗号化済みホテルコード [IN]
			const unsigned char* pEnc1,	//	セクタ1から読み取ったデータバイト列 [IN]
			const unsigned char* pEnc4,	//	セクタ4から読み取ったデータバイト列 [IN]
			const unsigned char* pEnc5	//	セクタ5から読み取ったデータバイト列 [IN]
			);

		// 1Kカードのロックデータ翻訳（復号化）EDL-ID指定あり
		EDLERR __stdcall EDL_Enc2InfWithEdl(
			unsigned char* pInf,	//	翻訳後のカード情報文字列 [OUT]
			unsigned char* pSpFlg,	//	スペシャルドアフラグ [OUT]
			unsigned long ulHtl,	//	暗号化済みホテルコード [IN]
			const unsigned char* pEdlId,//	EDL-ID [IN]
			const unsigned char* pEnc1,	//	セクタ1から読み取ったデータバイト列 [IN]
			const unsigned char* pEnc4,	//	セクタ4から読み取ったデータバイト列 [IN]
			const unsigned char* pEnc5	//	セクタ5から読み取ったデータバイト列 [IN]
		);

		// ULカードのロックデータ生成（暗号化）
		EDLERR __stdcall EDL_Inf2EncUL(
			unsigned char* pEnc,	//	カードに書き込むデータバイト列 [OUT]
			unsigned long ulHtl,	//	暗号化済みホテルコード [IN]
			const unsigned char* pInf,	//	カード情報文字列 [IN]
			const unsigned char* pSpFlg	//	スペシャルドアフラグ [IN]
			);

		// ULカードのロックデータ生成（暗号化）EDL-ID指定あり
		EDLERR __stdcall EDL_Inf2EncULWithEdl(
			unsigned char* pEnc,	//	カードに書き込むデータバイト列 [OUT]
			unsigned long ulHtl,	//	暗号化済みホテルコード [IN]
			const unsigned char* pEdlId,//	EDL-ID [IN]
			const unsigned char* pInf,	//	カード情報文字列 [IN]
			const unsigned char* pSpFlg	//	スペシャルドアフラグ [IN]
		);

		// ULカードのロックデータ翻訳（復号化）
		EDLERR __stdcall EDL_Enc2InfUL(
			unsigned char* pInf,	//	翻訳後のカード情報文字列 [OUT]
			unsigned char* pSpFlg,	//	スペシャルドアフラグ [OUT]
			unsigned long ulHtl,	//	暗号化済みホテルコード [IN]
			const unsigned char* pEnc	//	カードから読み取ったデータバイト列 [IN]
			);

		// ULカードのロックデータ翻訳（復号化）EDL-ID指定あり
		EDLERR __stdcall EDL_Enc2InfULWithEdl(
			unsigned char* pInf,	//	翻訳後のカード情報文字列 [OUT]
			unsigned char* pSpFlg,	//	スペシャルドアフラグ [OUT]
			unsigned long ulHtl,	//	暗号化済みホテルコード [IN]
			const unsigned char* pEdlId,//	EDL-ID [IN]
			const unsigned char* pEnc	//	カードから読み取ったデータバイト列 [IN]
		);

		// ALV2 APIJのバージョン値の取得
		unsigned short __stdcall EDL_GetVer(void);

	#if defined(__cplusplus)
	}
	#endif

#endif