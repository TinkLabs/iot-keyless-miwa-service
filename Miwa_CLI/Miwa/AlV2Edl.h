//******************************************************************************
//* NAME         : AlV2Edl.h
//* FUNCTION     : ALV2 APIJ DLL
//* PROGRAMED    : 12.07.23 CBE/���J��
//* REMARK       : 
//* HISTORY      : 
//* ID -- DATE -------- NOTE ---------------------------------------------------
//*<00>12.07.23 CBE/���J��      �V�K�쐬
//******************************************************************************
#if !defined(ALV2EDL_H)

	#define ALV2EDL_H

	//==========================================================================
	//  �f�[�^�\����`
	//==========================================================================

	// �G���[�R�[�h
	typedef unsigned long EDLERR;				//	APIJ �G���[�R�[�h�̌^

	#define EDLERR_NORMAL		0x00000000		//	����I��

	// �ݒ�ُ�n
	#define EDLERR_RD_EDLID		0x00010010		//	EDL-ID �Ǎ��݃G���[
	#define EDLERR_INV_EDLID	0x00010020		//	EDL-ID �l�ُ�

	// �G���R�[�h�ُ�n
	#define EDLERR_HTLCD		0x00020010		//	�z�e���R�[�h�ُ�
	#define EDLERR_CRDTYP		0x00020020		//	�J�[�h��ʈُ�
	#define EDLERR_CRDNO		0x00020030		//	�J�[�h�}�Ԉُ�
	#define EDLERR_ISSNUM		0x00020040		//	�J�[�h���s�����ُ�
	#define EDLERR_CITIME		0x00020050		//	�`�F�b�N�C�������ُ�
	#define EDLERR_COTIME		0x00020060		//	�`�F�b�N�A�E�g�����ُ�
	#define EDLERR_SUMFG		0x00020070		//	�T�}�[�^�C���t���O�ُ�
	#define EDLERR_SHUTFG		0x00020080		//	�V���b�g�A�E�g�t���O�ُ�
	#define EDLERR_BUZFG		0x00020090		//	�u�U�[�ʒm�t���O�ُ�
	#define EDLERR_SPZFG		0x000200A0		//	�X�y�V�����h�A�t���O�ُ�
	#define EDLERR_MAINROM		0x000200B0		//	���C�����[��No.�ُ�
	#define EDLERR_2NDROM		0x000200C0		//	�Z�J���h���[��No.�ُ�
	#define EDLERR_LCKDAT		0x000200D0		//	���b�N�f�[�^�ُ�
	#define EDLERR_DEADBOLT		0x000200E0		//	�f�b�h�{���g�I�[�o�[���C�h�t���O�ُ�

	// �f�R�[�h�ُ�n
	#define EDLERR_BLANKCRD		0x00030010		//	�u�����N�J�[�h(���������ꂽ�J�[�h)
	#define EDLERR_INVHTLCD		0x00030020		//	�z�e���R�[�h�s��v
	#define EDLERR_INVCRDCD		0x00030030		//	�s���J�[�h(GU/MT �ȊO or �J�[�h�R�[�h�s��)
	#define EDLERR_DEC			0x00030040		//	���������s

	//==========================================================================
	//  �v���g�^�C�v�錾
	//==========================================================================
	#if defined(__cplusplus)
	extern "C" {
	#endif

		// 1K�J�[�h�̃��b�N�f�[�^�����i�Í����j
		EDLERR __stdcall EDL_Inf2Enc(
			unsigned char* pEnc1,	//	�Z�N�^1�ɏ������ރf�[�^�o�C�g�� [OUT]
			unsigned char* pEnc4,	//	�Z�N�^4�ɏ������ރf�[�^�o�C�g�� [OUT]
			unsigned char* pEnc5,	//	�Z�N�^5�ɏ������ރf�[�^�o�C�g�� [OUT]
			unsigned long ulHtl,	//	�Í����ς݃z�e���R�[�h [IN]
			const unsigned char* pInf,	//	�J�[�h��񕶎��� [IN]
			const unsigned char* pSpFlg	//	�X�y�V�����h�A�t���O [IN]
			);

		// 1K�J�[�h�̃��b�N�f�[�^�����i�Í����jEDL-ID�w�肠��
		EDLERR __stdcall EDL_Inf2EncWithEdl(
			unsigned char* pEnc1,	//	�Z�N�^1�ɏ������ރf�[�^�o�C�g�� [OUT]
			unsigned char* pEnc4,	//	�Z�N�^4�ɏ������ރf�[�^�o�C�g�� [OUT]
			unsigned char* pEnc5,	//	�Z�N�^5�ɏ������ރf�[�^�o�C�g�� [OUT]
			unsigned long ulHtl,	//	�Í����ς݃z�e���R�[�h [IN]
			const unsigned char* pEdlId,//	EDL-ID [IN]
			const unsigned char* pInf,	//	�J�[�h��񕶎��� [IN]
			const unsigned char* pSpFlg	//	�X�y�V�����h�A�t���O [IN]
		);

		// 1K�J�[�h�̃��b�N�f�[�^�|��i�������j
		EDLERR __stdcall EDL_Enc2Inf(
			unsigned char* pInf,	//	�|���̃J�[�h��񕶎��� [OUT]
			unsigned char* pSpFlg,	//	�X�y�V�����h�A�t���O [OUT]
			unsigned long ulHtl,	//	�Í����ς݃z�e���R�[�h [IN]
			const unsigned char* pEnc1,	//	�Z�N�^1����ǂݎ�����f�[�^�o�C�g�� [IN]
			const unsigned char* pEnc4,	//	�Z�N�^4����ǂݎ�����f�[�^�o�C�g�� [IN]
			const unsigned char* pEnc5	//	�Z�N�^5����ǂݎ�����f�[�^�o�C�g�� [IN]
			);

		// 1K�J�[�h�̃��b�N�f�[�^�|��i�������jEDL-ID�w�肠��
		EDLERR __stdcall EDL_Enc2InfWithEdl(
			unsigned char* pInf,	//	�|���̃J�[�h��񕶎��� [OUT]
			unsigned char* pSpFlg,	//	�X�y�V�����h�A�t���O [OUT]
			unsigned long ulHtl,	//	�Í����ς݃z�e���R�[�h [IN]
			const unsigned char* pEdlId,//	EDL-ID [IN]
			const unsigned char* pEnc1,	//	�Z�N�^1����ǂݎ�����f�[�^�o�C�g�� [IN]
			const unsigned char* pEnc4,	//	�Z�N�^4����ǂݎ�����f�[�^�o�C�g�� [IN]
			const unsigned char* pEnc5	//	�Z�N�^5����ǂݎ�����f�[�^�o�C�g�� [IN]
		);

		// UL�J�[�h�̃��b�N�f�[�^�����i�Í����j
		EDLERR __stdcall EDL_Inf2EncUL(
			unsigned char* pEnc,	//	�J�[�h�ɏ������ރf�[�^�o�C�g�� [OUT]
			unsigned long ulHtl,	//	�Í����ς݃z�e���R�[�h [IN]
			const unsigned char* pInf,	//	�J�[�h��񕶎��� [IN]
			const unsigned char* pSpFlg	//	�X�y�V�����h�A�t���O [IN]
			);

		// UL�J�[�h�̃��b�N�f�[�^�����i�Í����jEDL-ID�w�肠��
		EDLERR __stdcall EDL_Inf2EncULWithEdl(
			unsigned char* pEnc,	//	�J�[�h�ɏ������ރf�[�^�o�C�g�� [OUT]
			unsigned long ulHtl,	//	�Í����ς݃z�e���R�[�h [IN]
			const unsigned char* pEdlId,//	EDL-ID [IN]
			const unsigned char* pInf,	//	�J�[�h��񕶎��� [IN]
			const unsigned char* pSpFlg	//	�X�y�V�����h�A�t���O [IN]
		);

		// UL�J�[�h�̃��b�N�f�[�^�|��i�������j
		EDLERR __stdcall EDL_Enc2InfUL(
			unsigned char* pInf,	//	�|���̃J�[�h��񕶎��� [OUT]
			unsigned char* pSpFlg,	//	�X�y�V�����h�A�t���O [OUT]
			unsigned long ulHtl,	//	�Í����ς݃z�e���R�[�h [IN]
			const unsigned char* pEnc	//	�J�[�h����ǂݎ�����f�[�^�o�C�g�� [IN]
			);

		// UL�J�[�h�̃��b�N�f�[�^�|��i�������jEDL-ID�w�肠��
		EDLERR __stdcall EDL_Enc2InfULWithEdl(
			unsigned char* pInf,	//	�|���̃J�[�h��񕶎��� [OUT]
			unsigned char* pSpFlg,	//	�X�y�V�����h�A�t���O [OUT]
			unsigned long ulHtl,	//	�Í����ς݃z�e���R�[�h [IN]
			const unsigned char* pEdlId,//	EDL-ID [IN]
			const unsigned char* pEnc	//	�J�[�h����ǂݎ�����f�[�^�o�C�g�� [IN]
		);

		// ALV2 APIJ�̃o�[�W�����l�̎擾
		unsigned short __stdcall EDL_GetVer(void);

	#if defined(__cplusplus)
	}
	#endif

#endif