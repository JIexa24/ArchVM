#include "./../include/hardDrive.h"

int g_lba2chs(tLBA LBA, tCHS* CHS)
{
  int temp1, temp2, divider, i;
  temp1 = LBA.lba / 63; 
  temp2 = temp1 / 1023;
  for (i = 2; i <= 256; i *= 2) {
    if (i / 2 < temp2 && i > temp2) {
      if (i == 256) {
        --i;
      }
      divider = i;
      break;
    }
  }
  CHS->countSector = 63;
  CHS->countHead = divider;
  CHS->countCylinder = temp1 / divider;
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_lba2large(tLBA LBA, tLARGE* LARGE)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_lba2idechs(tLBA LBA, tIDECHS* IDECHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_chs2large(tCHS CHS, tLARGE* LARGE)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_chs2lba(tCHS CHS, tLBA* LBA)
{
  LBA->lba = (CHS.countCylinder * 255 + CHS.countHead) * 63 + CHS.countSector - 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_chs2idechs(tIDECHS IDECHS, tLBA* LBA)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_large2chs(tLARGE LARGE, tCHS* CHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_large2idechs(tLARGE LARGE, tIDECHS* IDECHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_large2lba(tLARGE LARGE, tLBA* LBA)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_idechs2chs(tIDECHS IDECHS, tCHS* CHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_idechs2lagre(tIDECHS IDECHS, tLARGE* LARGE)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_idechs2lba(tIDECHS IDECHS, tLBA* LBA)
{
  return 0;
}
/*---------------------------------------------------------------------------*/;
int a_lba2chs(tCHS geometry, tLBA LBA, tCHS* CHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_lba2large(tLARGE geometry, tLBA LBA, tLARGE* LARGE)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_lba2idechs(tIDECHS geometry, tLBA LBA,tIDECHS* IDECHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_chs2lba(tCHS geometry, tCHS CHS, tLBA* LBA)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_large2lba(tLARGE geometry, tLARGE LARGE, tLBA* LBA)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_idechs2lba(tIDECHS geometry, tIDECHS IDECHS, tLBA* LBA)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_large2chs(tLARGE geometry1,tCHS geometry2,tLARGE LARGE, tCHS* CHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_large2idechs(tLARGE geometry1, tIDECHS geometry2, tLARGE LARGE,tIDECHS* IDECHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_chs2large(tCHS geometry1, tLARGE geometry2, tCHS CHS, tLARGE* LARGE)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_idechs2large(tIDECHS geometry1, tLARGE geometry2, tIDECHS IDECHS, tLARGE* LARGE)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_chs2idechs(tCHS geometry1, tIDECHS geometry2, tCHS CHS, tIDECHS* IDECHS)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_idechs2chs(tIDECHS geometry1, tCHS geometry2, tIDECHS IDECHS,tCHS* CHS)
{
  return 0;
}



