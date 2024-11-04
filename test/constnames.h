/* Copyright (c) Elliot Nunn */
/* Licensed under the MIT license */

#pragma once

#include <stdint.h>

const char *PosModeName(char mode);
const char *ErrName(short err);
const char *FieldName(int fieldCode);
const char *TrapName(uint32_t trap);

enum {
	ioNoField,
	ioResult,
	ioFileName,
	ioNamePtr,
	ioVRefNum,
	ioDstVRefNum,
	ioFRefNum,
	ioRefNum,
	ioDenyModes,
	ioFVersNum,
	ioVersNum,
	ioWDIndex,
	ioPermssn,
	ioFCBIndx,
	ioFDirIndex,
	ioNewName,
	ioVolIndex,
	ioWDProcID,
	ioFlAttrib,
	ioVCrDate,
	ioFlVersNum,
	ioBuffer,
	ioCopyName,
	ioDrUsrWds,
	ioFCBFlNm,
	ioFlFndrInfo,
	ioFlags,
	ioWDVRefNum,
	ioSlot,
	ioVLsBkUp,
	ioVLsMod,
	ioFCBFlags,
	ioNewDirID,
	ioReqCount,
	ioFCBStBlk,
	ioVAtrb,
	ioActCount,
	ioFCBEOF,
	ioVNmFls,
	ioVBitMap,
	ioVDirSt,
	ioFCBPLen,
	ioPosMode,
	ioVAllocPtr,
	ioVBlLn,
	ioPosOffset,
	ioVNmAlBlks,
	ioDirID,
	ioDrDirID,
	ioFCBCrPs,
	ioFlNum,
	ioVAlBlkSiz,
	ioWDDirID,
	ioDrNmFls,
	ioFCBVRefNum,
	ioFlStBlk,
	ioVClpSiz,
	ioFCBClpSiz,
	ioFileID,
	ioFlLgLen,
	ioAlBlSt,
	ioFCBParID,
	ioFlPyLen,
	ioVNxtFNum,
	ioFlRStBlk,
	ioVFrBlk,
	ioFlRLgLen,
	ioVSigWord,
	ioVDrvInfo,
	ioFlRPyLen,
	ioVDRefNum,
	ioVFSID,
	ioDrCrDat,
	ioFlCrDat,
	ioVBkUp,
	ioDrMdDat,
	ioFlMdDat,
	ioVSeqNum,
	ioVWrCnt,
	ioDrBkDat,
	ioFlBkDat,
	ioVFilCnt,
	ioDrFndrInfo,
	ioFlXFndrInfo,
	ioVDirCnt,
	ioVFndrInfo,
	ioDrParID,
	ioFlParID,
	ioFlClpSiz,
};

enum {
	tOpen                   = 0xa0000000,
	tHOpen                  = 0xa2000000,
	tClose                  = 0xa0010000,
	tRead                   = 0xa0020000,
	tWrite                  = 0xa0030000,
	tGetVInfo               = 0xa0070000,
	tHGetVInfo              = 0xa2070000,
	tCreate                 = 0xa0080000,
	tHCreate                = 0xa2080000,
	tDelete                 = 0xa0090000,
	tHDelete                = 0xa2090000,
	tOpenRF                 = 0xa00a0000,
	tHOpenRF                = 0xa20a0000,
	tRename                 = 0xa00b0000,
	tHRename                = 0xa20b0000,
	tGetFInfo               = 0xa00c0000,
	tHGetFInfo              = 0xa20c0000,
	tSetFInfo               = 0xa00d0000,
	tHSetFInfo              = 0xa20d0000,
	tUnmountVol             = 0xa00e0000,
	tMountVol               = 0xa00f0000,
	tAllocate               = 0xa0100000,
	tAllocContig            = 0xa2100000,
	tGetEOF                 = 0xa0110000,
	tSetEOF                 = 0xa0120000,
	tFlushVol               = 0xa0130000,
	tHTrashVolumeCaches     = 0xa2130000,
	tGetVol                 = 0xa0140000,
	tHGetVol                = 0xa2140000,
	tSetVol                 = 0xa0150000,
	tHSetVol                = 0xa2150000,
	tEject                  = 0xa0170000,
	tGetFPos                = 0xa0180000,
	tOffLine                = 0xa0350000,
	tSetFLock               = 0xa0410000,
	tHSetFLock              = 0xa2410000,
	tRstFLock               = 0xa0420000,
	tHRstFLock              = 0xa2420000,
	tSetFVers               = 0xa0430000,
	tSetFPos                = 0xa0440000,
	tFlushFile              = 0xa0450000,
	tOpenWD                 = 0xa2600001,
	tCloseWD                = 0xa2600002,
	tCatMove                = 0xa2600005,
	tDirCreate              = 0xa2600006,
	tGetWDInfo              = 0xa2600007,
	tGetFCBInfo             = 0xa2600008,
	tGetCatInfo             = 0xa2600009,
	tSetCatInfo             = 0xa260000a,
	tSetVInfo               = 0xa260000b,
	tLockRange              = 0xa2600010,
	tUnlockRange            = 0xa2600011,
	tXGetVolInfo            = 0xa0600012,
	tCreateFileIDRef        = 0xa2600014,
	tDeleteFileIDRef        = 0xa2600015,
	tResolveFileIDRef       = 0xa2600016,
	tExchangeFiles          = 0xa2600017,
	tCatSearch              = 0xa2600018,
	tOpenDF                 = 0xa060001a,
	tHOpenDF                = 0xa260001a,
	tMakeFSSpec             = 0xa260001b,
	tGetVolumeInfo          = 0xa260001d,
	tSetVolumeInfo          = 0xa260001e,
	tDTGetPath              = 0xa2600020,
	tDTCloseDown            = 0xa2600021,
	tDTAddIcon              = 0xa2600022,
	tDTGetIcon              = 0xa2600023,
	tDTGetIconInfo          = 0xa2600024,
	tDTAddAPPL              = 0xa2600025,
	tDTRemoveAPPL           = 0xa2600026,
	tDTGetAPPL              = 0xa2600027,
	tDTSetComment           = 0xa2600028,
	tDTRemoveComment        = 0xa2600029,
	tDTGetComment           = 0xa260002a,
	tDTFlush                = 0xa260002b,
	tDTReset                = 0xa260002c,
	tDTGetInfo              = 0xa260002d,
	tDTOpenInform           = 0xa060002e,
	tDTDelete               = 0xa060002f,
	tHGetVolParms           = 0xa2600030,
	tHGetLogInInfo          = 0xa2600031,
	tHGetDirAccess          = 0xa2600032,
	tHSetDirAccess          = 0xa2600033,
	tHMapID                 = 0xa2600034,
	tHMapName               = 0xa2600035,
	tHCopyFile              = 0xa2600036,
	tHMoveRename            = 0xa2600037,
	tHOpenDeny              = 0xa2600038,
	tHOpenRFDeny            = 0xa2600039,
	tGetXCatInfo            = 0xa260003a,
	tGetVolMountInfoSize    = 0xa260003f,
	tGetVolMountInfo        = 0xa2600040,
	tVolumeMount            = 0xa2600041,
	tShare                  = 0xa2600042,
	tUnshare                = 0xa2600043,
	tGetUGEntry             = 0xa2600044,
	tGetForkPosition        = 0xa2600053,
	tSetForkPosition        = 0xa2600054,
	tGetForkSize            = 0xa2600055,
	tSetForkSize            = 0xa2600056,
	tAllocateFork           = 0xa2600057,
	tFlushFork              = 0xa2600058,
	tCloseFork              = 0xa2600059,
	tGetForkCBInfo          = 0xa260005a,
	tCloseIterator          = 0xa260005b,
	tGetCatalogInfoBulk     = 0xa260005c,
	tCatalogSearch          = 0xa260005d,
	tGetAltAccess           = 0xa0600060,
	tGetForeignPrivs        = 0xa2600060,
	tSetAltAccess           = 0xa0600061,
	tSetForeignPrivs        = 0xa2600061,
	tMakeFSRef              = 0xa260006e,
	tCreateFileUnicode      = 0xa2600070,
	tCreateDirectoryUnicode = 0xa2600071,
	tDeleteObject           = 0xa2600072,
	tMoveObject             = 0xa2600073,
	tRenameUnicode          = 0xa2600074,
	tExchangeObjects        = 0xa2600075,
	tGetCatalogInfo         = 0xa2600076,
	tSetCatalogInfo         = 0xa2600077,
	tOpenIterator           = 0xa2600078,
	tOpenFork               = 0xa2600079,
	tMakeFSRefUnicode       = 0xa260007a,
	tCompareFSRefs          = 0xa260007c,
	tCreateFork             = 0xa260007d,
	tDeleteFork             = 0xa260007e,
	tIterateForks           = 0xa260007f,
	tReadFork               = 0xa2a80051,
	tWriteFork              = 0xa2a80052,
};