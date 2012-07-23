// $Id: FriioBlack.cpp 5689 2008-09-18 19:48:59Z clworld $
// 黒凡

#include <glib.h>
#include <string.h>
#include "usbops.hpp"
#include "FriioBlack.hpp"

FriioBlack::FriioBlack()
	: AbstractFriio()
{
	supportBands.push_back(BAND_BS);
	supportBands.push_back(BAND_CS);
	targetType         = TUNER_FRIIO_BLACK;
	asyncBufSize       = BLACK_ASYNCBUFFSIZE;
	requestReserveNum  = BLACK_REQUEST_RESERVE_NUM;
	requestPollingWait = BLACK_REQUEST_POLLING_WAIT;
}

/**
 * 初期化処理 : 処理開始
 * 便宜上Beginにしているが、本来どんなことをしているかは不明
 * @param fd 対象ファイルディスクリプタ
 */
void
FriioBlack::UsbProcBegin(int fd)
{
	UsbSendVendorRequest(fd, 0x0000, 0x0000);
	UsbSendVendorRequest(fd, 0x000f, 0x0006);
	UsbSendVendorRequest(fd, 0x0000, 0x0000);
}

/**
 * 処理終了
 * 便宜上Endにしている。恐らくバッファクリア
 * @param fd 対象ファイルディスクリプタ
 */
void
FriioBlack::UsbProcEnd(int fd)
{
	UsbSendVendorRequest(fd, 0x0000, 0x0000);
}

/**
 * 黒凡 チャンネル設定
 */
static void SetChannel_Black(int fd, const uint32_t dwSpace, const uint32_t dwChannel)
{
	// 資料不足のため未実装
	struct Black_Channel_Sequence {
		uint8_t byReqNo;
		uint16_t wValue;
		uint16_t wIndex;
		uint8_t bData;		// 3byteのデータ部があるか
		uint8_t byData1;	// データ１
		uint8_t byData2;	// データ２
		uint8_t byData3;	// データ３
	};
	
	struct Black_Channel_Sequence cmd[] = {
														// Index(n回目-1)
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x00, 0x0A },	// 0
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x01, 0x4C },	// 1
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x02, 0x02 },	// 2
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x03, 0x40 },	// 3
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x04, 0x6C },	// 4
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x05, 0x47 },	// 5
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x06, 0x02 },	// 6
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x07, 0x30 },	// 7
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x08, 0x20 },	// 8
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x09, 0xA2 },	// 9
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0A, 0xF1 },	// 10
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0B, 0x38 },	// 11
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0C, 0xD0 },	// 12
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0D, 0x10 },	// 13
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0E, 0xB0 },	// 14
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0F, 0x01 },	// 15
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x00, 0x0A },	// 16
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x01, 0x4C },	// 17
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x02, 0x02 },	// 18
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x03, 0x40 },	// 19
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x04, 0x6C },	// 20
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x05, 0x47 },	// 21
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x06, 0x02 },	// 22
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x07, 0x30 },	// 23
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x08, 0x20 },	// 24
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x09, 0xA2 },	// 25
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0A, 0xF1 },	// 26
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0B, 0x38 },	// 27
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0C, 0xD0 },	// 28
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0D, 0x10 },	// 29
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0E, 0xB0 },	// 30
		{ 0x03, 0x3200, 0x00FE, TRUE, 0xC0, 0x0F, 0x01 },	// 31
		{ 0x01, 0x3210, 0x0001, FALSE, 0x00, 0x00, 0x00 },	// 32
		{ 0x01, 0x3200, 0x0002, FALSE, 0x00, 0x00, 0x00 },	// 33
		{ 0x01, 0x3200, 0x0003, FALSE, 0x00, 0x00, 0x00 },	// 34
		{ 0x01, 0x3200, 0x0008, FALSE, 0x00, 0x00, 0x00 },	// 35
		{ 0x01, 0x3259, 0x000C, FALSE, 0x00, 0x00, 0x00 },	// 36
		{ 0x01, 0x32F2, 0x000D, FALSE, 0x00, 0x00, 0x00 },	// 37
		{ 0x01, 0x3251, 0x000F, FALSE, 0x00, 0x00, 0x00 },	// 38
		{ 0x01, 0x32B2, 0x0010, FALSE, 0x00, 0x00, 0x00 },	// 39
		{ 0x01, 0x3204, 0x001A, FALSE, 0x00, 0x00, 0x00 },	// 40
		{ 0x01, 0x3204, 0x001B, FALSE, 0x00, 0x00, 0x00 },	// 41
		{ 0x01, 0x3240, 0x0038, FALSE, 0x00, 0x00, 0x00 },	// 42
		{ 0x01, 0x3210, 0x0039, FALSE, 0x00, 0x00, 0x00 },	// 43
		{ 0x01, 0x3208, 0x003C, FALSE, 0x00, 0x00, 0x00 },	// 44
		{ 0x01, 0x3296, 0x003D, FALSE, 0x00, 0x00, 0x00 },	// 45
		{ 0x01, 0x32D9, 0x003E, FALSE, 0x00, 0x00, 0x00 },	// 46
		{ 0x01, 0x32B6, 0x003F, FALSE, 0x00, 0x00, 0x00 },	// 47
		{ 0x01, 0x325D, 0x0040, FALSE, 0x00, 0x00, 0x00 },	// 48
		{ 0x01, 0x3299, 0x0041, FALSE, 0x00, 0x00, 0x00 },	// 49
		{ 0x01, 0x3258, 0x0044, FALSE, 0x00, 0x00, 0x00 },	// 50
		{ 0x01, 0x3254, 0x0045, FALSE, 0x00, 0x00, 0x00 },	// 51
		{ 0x01, 0x3230, 0x0046, FALSE, 0x00, 0x00, 0x00 },	// 52
		{ 0x01, 0x3241, 0x0047, FALSE, 0x00, 0x00, 0x00 },	// 53
		{ 0x01, 0x3216, 0x0049, FALSE, 0x00, 0x00, 0x00 },	// 54
		{ 0x01, 0x3241, 0x004A, FALSE, 0x00, 0x00, 0x00 },	// 55
		{ 0x01, 0x3241, 0x004B, FALSE, 0x00, 0x00, 0x00 },	// 56
		{ 0x01, 0x325E, 0x004F, FALSE, 0x00, 0x00, 0x00 },	// 57
		{ 0x01, 0x3204, 0x0050, FALSE, 0x00, 0x00, 0x00 },	// 58
		{ 0x01, 0x32C0, 0x0051, FALSE, 0x00, 0x00, 0x00 },	// 59
		{ 0x01, 0x328A, 0x0052, FALSE, 0x00, 0x00, 0x00 },	// 60
		{ 0x01, 0x3213, 0x0053, FALSE, 0x00, 0x00, 0x00 },	// 61
		{ 0x01, 0x3290, 0x0054, FALSE, 0x00, 0x00, 0x00 },	// 62
		{ 0x01, 0x3292, 0x0055, FALSE, 0x00, 0x00, 0x00 },	// 63
		{ 0x01, 0x326D, 0x0058, FALSE, 0x00, 0x00, 0x00 },	// 64
		{ 0x01, 0x326F, 0x0059, FALSE, 0x00, 0x00, 0x00 },	// 65
		{ 0x01, 0x322E, 0x005A, FALSE, 0x00, 0x00, 0x00 },	// 66
		{ 0x01, 0x3223, 0x005B, FALSE, 0x00, 0x00, 0x00 },	// 67
		{ 0x01, 0x3233, 0x005D, FALSE, 0x00, 0x00, 0x00 },	// 68
		{ 0x01, 0x3204, 0x0087, FALSE, 0x00, 0x00, 0x00 },	// 69
		{ 0x01, 0x3200, 0x008D, FALSE, 0x00, 0x00, 0x00 },	// 70
		{ 0x01, 0x3000, 0x0077, FALSE, 0x00, 0x00, 0x00 },	// 71
		{ 0x01, 0x3000, 0x0071, FALSE, 0x00, 0x00, 0x00 },	// 72
		{ 0x01, 0x3000, 0x0071, FALSE, 0x00, 0x00, 0x00 },	// 73
		{ 0x01, 0x3240, 0x008F, FALSE, 0x00, 0x00, 0x00 },	// 74
		{ 0x01, 0x32F2, 0x0090, FALSE, 0x00, 0x00, 0x00 },	// 75
		{ 0x01, 0x3207, 0x00A5, FALSE, 0x00, 0x00, 0x00 },	// 76
		{ 0x01, 0x3207, 0x00A5, FALSE, 0x00, 0x00, 0x00 },	// 77
		{ 0x01, 0x32FF, 0x00A3, FALSE, 0x00, 0x00, 0x00 },	// 78
		{ 0x01, 0x32F7, 0x00A3, FALSE, 0x00, 0x00, 0x00 },	// 79
		{ 0x01, 0x3040, 0x0001, FALSE, 0x00, 0x00, 0x00 },	// 80
		{ 0x01, 0x3030, 0x0004, FALSE, 0x00, 0x00, 0x00 },	// 81
		{ 0x01, 0x3040, 0x0005, FALSE, 0x00, 0x00, 0x00 },	// 82
		{ 0x01, 0x3040, 0x0007, FALSE, 0x00, 0x00, 0x00 },	// 83
		{ 0x01, 0x30FF, 0x000F, FALSE, 0x00, 0x00, 0x00 },	// 84
		{ 0x01, 0x3027, 0x0011, FALSE, 0x00, 0x00, 0x00 },	// 85
		{ 0x01, 0x302F, 0x0013, FALSE, 0x00, 0x00, 0x00 },	// 86
		{ 0x01, 0x3031, 0x0014, FALSE, 0x00, 0x00, 0x00 },	// 87
		{ 0x01, 0x3002, 0x0016, FALSE, 0x00, 0x00, 0x00 },	// 88
		{ 0x01, 0x3020, 0x0022, FALSE, 0x00, 0x00, 0x00 },	// 89
		{ 0x01, 0x3070, 0x0024, FALSE, 0x00, 0x00, 0x00 },	// 90
		{ 0x01, 0x3079, 0x002C, FALSE, 0x00, 0x00, 0x00 },	// 91
		{ 0x01, 0x3034, 0x002D, FALSE, 0x00, 0x00, 0x00 },	// 92
		{ 0x01, 0x3028, 0x0030, FALSE, 0x00, 0x00, 0x00 },	// 93
		{ 0x01, 0x3031, 0x0031, FALSE, 0x00, 0x00, 0x00 },	// 94
		{ 0x01, 0x3001, 0x0038, FALSE, 0x00, 0x00, 0x00 },	// 95
		{ 0x01, 0x3078, 0x0039, FALSE, 0x00, 0x00, 0x00 },	// 96
		{ 0x01, 0x3090, 0x0048, FALSE, 0x00, 0x00, 0x00 },	// 97
		{ 0x01, 0x3068, 0x0051, FALSE, 0x00, 0x00, 0x00 },	// 98
		{ 0x01, 0x3038, 0x005E, FALSE, 0x00, 0x00, 0x00 },	// 99
		{ 0x01, 0x3021, 0x00C0, FALSE, 0x00, 0x00, 0x00 },	// 100
		{ 0x01, 0x3010, 0x00C1, FALSE, 0x00, 0x00, 0x00 },	// 101
		{ 0x01, 0x301A, 0x00E4, FALSE, 0x00, 0x00, 0x00 },	// 102
		{ 0x01, 0x301F, 0x00EA, FALSE, 0x00, 0x00, 0x00 },	// 103
		{ 0x00, 0x0000, 0x0000, FALSE, 0x00, 0x00, 0x00 },	// End
	};
	
	// チューニングシーケンス可変部分
	static const uint8_t PllConfA[] = {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0C, 0x0C, 0x0D, 0x0D, 0x0D, 0x0E, 0x0E, 0x0E, 0x0F, 0x0F, 0x0F, 0x10};	// 1/17回目 +40
	static const uint8_t PllConfB[] = {0x32, 0x32, 0x80, 0x80, 0xCC, 0xCC, 0x18, 0x18, 0x18, 0x64, 0x64, 0x64, 0xB2, 0xB2, 0xB2, 0x00, 0x00, 0x4C, 0x4C, 0x98, 0x98, 0xE4, 0xE4, 0xE4, 0x32, 0x32, 0x32, 0x7E, 0x7E, 0x7E, 0x9A, 0xEA, 0x3A, 0x8A, 0xDA, 0x2A, 0x7A, 0xCA, 0x1A, 0x6A, 0xBA, 0x0A};	// 2/18回目 +40
	static const uint8_t PllConfC[] = {0x40, 0x40, 0x40, 0x40, 0x44, 0x44, 0x44, 0x46, 0x46, 0x40, 0x40, 0x40, 0x46, 0x46, 0x46, 0x40, 0x40, 0x40, 0x40, 0x43, 0x43, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	// 75回目	+02
	static const uint8_t PllConfD[] = {0x10, 0x11, 0x30, 0x31, 0x50, 0x51, 0x70, 0x71, 0x72, 0x90, 0x91, 0x92, 0xB0, 0xB1, 0xB2, 0xD0, 0xD1, 0xF1, 0xF2, 0x10, 0x11, 0x30, 0x31, 0x32, 0x50, 0x51, 0x52, 0x70, 0x71, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	// 76回目	+02
	
	const uint32_t dwChIndex = dwSpace * 30UL + dwChannel;
	
	// 資料
	// BSAT-2c/3a TsID=4[BSch番号(2byte)][TP番号]
	// BS- 1  周波数=11.727GHz 0832 TsID=4010 BS朝日
	// BS- 1  周波数=11.727GHz 0832 TsID=4011 BS-TBS
	// BS- 3  周波数=11.765GHz 0880 TsID=4030 WOWWOWプライム
	// BS- 3  周波数=11.765GHz 0880 TsID=4031 BSジャパン
	// BS- 5  周波数=11.804GHz 08CC TsID=4450 WOWWOWライブ
	// BS- 5  周波数=11.804GHz 08CC TsID=4451 WOWWOWシネマ
	// BS- 7  周波数=11.842GHz 0918 TsID=4470 スター・チャンネル2/スター・チャンネル3
	// BS- 7  周波数=11.842GHz 0918 TsID=4671 BSアニマックス
	// BS- 7  周波数=11.842GHz 0918 TsID=4672 ディズニー・チャンネル
	// BS- 9  周波数=11.880GHz 0964 TsID=4090 BS11
	// BS- 9  周波数=11.880GHz 0964 TsID=4091 スター・チャンネル1
	// BS- 9  周波数=11.880GHz 0964 TsID=4092 TwellV
	// BS-11  周波数=11.919GHz 09B2 TsID=46b0 FOX bs238
	// BS-11  周波数=11.919GHz 09B2 TsID=46b1 BSスカパー！
	// BS-11  周波数=11.919GHz 09B2 TsID=46b2 放送大学テレビ/放送大学ラジオ
	// BS-13  周波数=11.957GHz 0A00 TsID=40D0 BS日テレ
	// BS-13  周波数=11.957GHz 0A00 TsID=40D1 BSフジ
	// BS-15  周波数=11.996GHz 0A4C TsID=40F1 NHK BS1
	// BS-15  周波数=11.996GHz 0A4C TsID=40F2 NHK BSプレミアム/ウェザーニューズ/エンジニアリングストリーム
	// BS-17  周波数=12.034GHz 0A98 TsID=4310 地上デジタル放送難視聴対策放送1(NHK/NHK E/FUJI)
	// BS-17  周波数=12.034GHz 0A98 TsID=4311 地上デジタル放送難視聴対策放送2(NTV/TBS/ASAHI/TX)
	// BS-19  周波数=12.072GHz 0AE4 TsID=4730 グリーンチャンネル
	// BS-19  周波数=12.072GHz 0AE4 TsID=4731 J SPORTS 1
	// BS-19  周波数=12.072GHz 0AE4 TsID=4732 J SPORTS 2
	// BS-21  周波数=12.111GHz 0B32 TsID=4750 IMAGICA BS
	// BS-21  周波数=12.111GHz 0B32 TsID=4751 J SPORTS 3
	// BS-21  周波数=12.111GHz 0B32 TsID=4752 J SPORTS 4
	// BS-23  周波数=12.149GHz 0B7E TsID=4770 BS釣りビジョン
	// BS-23  周波数=12.149GHz 0B7E TsID=4771 日本映画専門チャンネル
	// BS-23  周波数=12.149GHz 0B7E TsID=4772 D-Life
	//
	// NSAT-110 TsID=0000 固定
	// CSND2  周波数=12.291GHz 0C9A TsID=0000 CS
	// CSND4  周波数=12.331GHz 0CEA TsID=0000 CS
	// CSND6  周波数=12.371GHz 0D3A TsID=0000 CS
	// CSND8  周波数=12.411GHz 0D8A TsID=0000 CS
	// CSND10 周波数=12.451GHz 0DDA TsID=0000 CS
	// CSND12 周波数=12.491GHz 0E2A TsID=0000 CS
	// CSND14 周波数=12.531GHz 0E7A TsID=0000 CS
	// CSND16 周波数=12.571GHz 0ECA TsID=0000 CS
	// CSND18 周波数=12.611GHz 0F1A TsID=0000 CS
	// CSND20 周波数=12.651GHz 0F6A TsID=0000 CS
	// CSND22 周波数=12.691GHz 0FBA TsID=0000 CS
	// CSND24 周波数=12.731GHz 100A TsID=0000 CS
	
	uint32_t dwXmitNum = 0;
	for (;;dwXmitNum++) {
		struct Black_Channel_Sequence tmp = cmd[dwXmitNum];
		if (tmp.byReqNo == 0x00) break; // 終端
		
		// リクエストの作成
		uint8_t  buf[3]  = "";
		uint32_t buf_len = 0;
		
		if (tmp.bData) {
			buf_len = 3;
			buf[0]  = tmp.byData1;
			buf[1]  = tmp.byData2;
			buf[2]  = tmp.byData3;
		}
		
		usbdevfs_ctrltransfer ctrl;
		ctrl.bRequestType = USB_DIR_OUT|USB_TYPE_VENDOR|USB_RECIP_DEVICE;
		ctrl.bRequest     = tmp.byReqNo;
		ctrl.wValue       = tmp.wValue;
		ctrl.wIndex       = tmp.wIndex;
		ctrl.wLength      = buf_len;
		ctrl.timeout      = REQUEST_TIMEOUT;
		ctrl.data         = buf;
		
		// 可変部の変更
		switch(dwXmitNum){
			case 0:		buf[2] = PllConfA[dwChIndex];	break;	// 周波数1 データの最終byteにいれる
			case 1:		buf[2] = PllConfB[dwChIndex];	break;	// 周波数2 データの最終byteにいれる
			case 16:	buf[2] = PllConfA[dwChIndex];	break;	// 周波数1 データの最終byteにいれる
			case 17:	buf[2] = PllConfB[dwChIndex];	break;	// 周波数2 データの最終byteにいれる
			case 74:	ctrl.wValue = (ctrl.wValue & 0xFF00) | ((uint16_t)PllConfC[dwChIndex]);		break;	// TsID1 wValueの下位Byteに入れる
			case 75:	ctrl.wValue = (ctrl.wValue & 0xFF00) | ((uint16_t)PllConfD[dwChIndex]);		break;	// TsID2 wValueの下位Byteに入れる
		}
		
		// 送信
		usb_ctrl(fd, &ctrl);
		
		// 何故かここで遅延をかけないとTimeout errorが起こる。
		usleep(SETCHANNEL_COMMAND_INTERBAL * 1000);
	}
}

/**
 * 周波数帯域/チャンネルを設定する。
 * @param newBand 周波数帯域 UHF/BS/CS
 * @param newChannel チャンネル
 */
void
FriioBlack::setChannel(BandType newBand, int newChannel)
{
	if (BAND_BS == newBand && 1 <= newChannel && newChannel <= 30) {
		SetChannel_Black(tunerFd, 0U, newChannel - 1);
	} else if (BAND_CS == newBand && 1 <= newChannel && newChannel <= 12) {
		SetChannel_Black(tunerFd, 1U, newChannel - 1);
	} else {
		throw traceable_error("unknown channel."); // TODO: 適当なエラークラス
	}
}

/**
 * 信号レベルを取得する。
 * @return float 信号レベル
 */
const float
FriioBlack::getSignalLevel(void)
{
	// 線形補完で近似する
	static const float afLevelTable[] =
	{
		24.07f,	// 00	00	0		24.07dB
		24.07f,	// 10	00	4096	24.07dB
		18.61f,	// 20	00	8192	18.61dB
		15.21f,	// 30	00	12288	15.21dB
		12.50f,	// 40	00	16384	12.50dB
		10.19f,	// 50	00	20480	10.19dB
		8.140f,	// 60	00	24576	8.140dB
		6.270f,	// 70	00	28672	6.270dB
		4.550f,	// 80	00	32768	4.550dB
		3.730f,	// 88	00	34816	3.730dB
		3.630f,	// 88	FF	35071	3.630dB
		2.940f,	// 90	00	36864	2.940dB
		1.420f,	// A0	00	40960	1.420dB
		0.000f	// B0	00	45056	-0.01dB
	};
	
	uint8_t sigbuf[4];
	memset(sigbuf, '\0', sizeof(sigbuf));
	
	// 1
	usbdevfs_ctrltransfer ctrl;
	ctrl.bRequestType = USB_DIR_IN|USB_TYPE_VENDOR|USB_RECIP_DEVICE;
	ctrl.bRequest     = 0x02;
	ctrl.wValue       = 0x3200;
	ctrl.wIndex       = 0x00BA;
	ctrl.wLength      = 4;
	ctrl.timeout      = REQUEST_TIMEOUT;
	ctrl.data         = sigbuf;
	
	// 信号レベル要求
	usb_ctrl(tunerFd, &ctrl);

	// 信号レベル計算
	if(sigbuf[2] <= 0x10U){
		// 最大クリップ
		return 24.07f;
	} else if (sigbuf[2] >= 0xB0U) {
		// 最小クリップ
		return 0.0f;
	} else {
		// 線形補完
		const float fMixRate = (float)(((uint16_t)(sigbuf[2] & 0x0FU) << 8) | (uint16_t)sigbuf[3]) / 4095.0f;
		return afLevelTable[sigbuf[2] >> 4] * (1.0f - fMixRate) + afLevelTable[(sigbuf[2] >> 4) + 0x01U] * fMixRate;
	}
}

/**
 * ＬＥＤ制御
 * @param fd 対象ファイルディスクリプタ
 * @param color 色
 */
void
FriioBlack::UsbProcLED(int fd, BonLedColor color, bool lnb_powered)
{
	unsigned int i, j;
	int lnb = lnb_powered ? FRIIO_PIC_LNB_1 : FRIIO_PIC_LNB_0;
	unsigned char data[4];

	switch(color)
	{
	case BON_LED_RED:
		UsbProcLED_full(fd, 100, 0xFF000A, data);
		break;
	case BON_LED_GREEN:
		UsbProcLED_full(fd, 100, 0x00FF64, data);
		break;
	case BON_LED_PURPLE:
		UsbProcLED_full(fd, 150, 0xFF00FF, data);
		break;
	case BON_LED_WHITE:
		UsbProcLED_full(fd, 100, 0xFFFFFF, data);
		break;
	}

	UsbSendLED_bit(fd, FRIIO_PIC_LED_1 | lnb | FRIIO_PIC_STROBE_1);
	UsbSendLED_bit(fd, FRIIO_PIC_LED_0 | lnb | FRIIO_PIC_STROBE_1);

	for (i = 0; i < sizeof(data); i++) {
		for (j = 0; j < 8; j++) {
			int led_bit = (data[i] & (0x80U >> j)) ? FRIIO_PIC_LED_1 : FRIIO_PIC_LED_0;

			UsbSendLED_bit(fd, led_bit | lnb | FRIIO_PIC_STROBE_1);
		}
	}

	// STROBE: OFF
	UsbSendLED_bit(fd, FRIIO_PIC_LED_0 | lnb | FRIIO_PIC_STROBE_0);
}

/**
 * 初期化処理 : 固定処理B
 * @param fd 対象ファイルディスクリプタ
 */
void
FriioBlack::UsbProcFixInitB(int fd)
{
	UsbSendVendorRequest(fd, 0x3040, 0x0001);
	UsbSendVendorRequest(fd, 0x3030, 0x0004);
	UsbSendVendorRequest(fd, 0x3040, 0x0005);
	UsbSendVendorRequest(fd, 0x3040, 0x0007);
	UsbSendVendorRequest(fd, 0x30ff, 0x000f);
	UsbSendVendorRequest(fd, 0x3027, 0x0011);
	UsbSendVendorRequest(fd, 0x302f, 0x0013);
	UsbSendVendorRequest(fd, 0x3031, 0x0014);
	UsbSendVendorRequest(fd, 0x3002, 0x0016);
	UsbSendVendorRequest(fd, 0x3020, 0x0022);
	UsbSendVendorRequest(fd, 0x3070, 0x0024);
	UsbSendVendorRequest(fd, 0x3079, 0x002c);
	UsbSendVendorRequest(fd, 0x3034, 0x002d);
	UsbSendVendorRequest(fd, 0x3028, 0x0030);
	UsbSendVendorRequest(fd, 0x3031, 0x0031);
	UsbSendVendorRequest(fd, 0x3001, 0x0038);
	UsbSendVendorRequest(fd, 0x3078, 0x0039);
	UsbSendVendorRequest(fd, 0x3090, 0x0048);
	UsbSendVendorRequest(fd, 0x3068, 0x0051);
	UsbSendVendorRequest(fd, 0x3038, 0x005e);
	UsbSendVendorRequest(fd, 0x3021, 0x00c0);
	UsbSendVendorRequest(fd, 0x3010, 0x00c1);
	UsbSendVendorRequest(fd, 0x301a, 0x00e4);
	UsbSendVendorRequest(fd, 0x301f, 0x00ea);
}

void 
FriioBlack::UsbSendLED_bit(int fd, unsigned char data)
{
	UsbSendVendorRequest(fd, data | FRIIO_PIC_CLK_0, 0x0000);
	UsbSendVendorRequest(fd, data | FRIIO_PIC_CLK_1, 0x0000);
}

void
FriioBlack::UsbProcLED_full(int fd, int rgb_saturation, uint32_t color, unsigned char *data)
{
	data[0] = rgb_saturation;
	data[1] = (color >> 16) & 0xff;
	data[2] = (color >> 8) & 0xff;
	data[3] = (color >> 0) & 0xff;
}