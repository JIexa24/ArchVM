/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/hardDrive.h"

unsigned int countCylinder;
unsigned int countHead;
unsigned int countSector;

int g_lba2chs(tLBA LBA, tCHS* CHS)
{
  CHS->countSector = (LBA.lba / 15) / 63;
  CHS->countHead = (LBA.lba / 15) % 63;
  CHS->countCylinder = LBA.lba % 63 + 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_lba2large(tLBA LBA, tLARGE* LARGE)
{
  LARGE->countSector = (LBA.lba / 63) / 255;
  LARGE->countHead = (LBA.lba / 63) % 255;
  LARGE->countCylinder = LBA.lba % 255 + 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_lba2idechs(tLBA LBA, tIDECHS* IDECHS)
{
  IDECHS->countSector = (LBA.lba / 15) / 255;
  IDECHS->countHead = (LBA.lba / 15) % 255;
  IDECHS->countCylinder = LBA.lba % 255 + 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_chs2large(tCHS CHS, tLARGE* LARGE)
{
  tLBA tmpLBA;
  g_chs2lba(CHS, &tmpLBA);
  g_lba2large(tmpLBA, LARGE);
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_chs2lba(tCHS CHS, tLBA* LBA)
{
  LBA->lba = (CHS.countCylinder * 15 + CHS.countHead) * 63 + CHS.countSector - 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_chs2idechs(tIDECHS IDECHS, tLBA* LBA)
{
  tLBA tmpLBA;
  g_chs2lba(IDECHS, &tmpLBA);
  g_lba2idechs(tmpLBA, LBA);
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_large2chs(tLARGE LARGE, tCHS* CHS)
{
  tLBA tmpLBA;
  g_large2lba(LARGE, &tmpLBA);
  g_lba2chs(tmpLBA, CHS);
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_large2idechs(tLARGE LARGE, tIDECHS* IDECHS)
{
  tLBA tmpLBA;
  g_large2lba(LARGE, &tmpLBA);
  g_lba2idechs(tmpLBA, IDECHS);
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_large2lba(tLARGE LARGE, tLBA* LBA)
{
  LBA->lba = (LARGE.head + 255 * LARGE.cyl) * 63 + LARGE.sec - 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_idechs2chs(tIDECHS IDECHS, tCHS* CHS)
{
  tLBA tmpLBA;
  g_idechs2lba(IDECHS, &tmpLBA);
  g_lba2chs(tmpLBA, CHS);
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_idechs2lagre(tIDECHS IDECHS, tLARGE* LARGE)
{
  tLBA tmpLBA;
  g_idechs2lba(IDECHS, &tmpLBA);
  g_lba2large(tmpLBA, LARGE);
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_idechs2lba(tIDECHS IDECHS, tLBA* LBA)
{
  LBA->lba = (IDECHS.head + 15 * IDECHS.cyl) * 255 + IDECHS.sec - 1;
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

