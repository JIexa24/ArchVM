/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/hardDrive.h"

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
  LBA->lba = (CHS.countCylinder * 15 + CHS.countHead) * 63 + 
              CHS.countSector - 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int g_chs2idechs(tCHS CHS, tIDECHS* IDECHS)
{
  tLBA tmpLBA;
  g_chs2lba(CHS, &tmpLBA);
  g_lba2idechs(tmpLBA, IDECHS);
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
  LBA->lba = (LARGE.countHead + 255 * LARGE.countCylinder) * 63 + 
              LARGE.countSector - 1;
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
  LBA->lba = (IDECHS.countHead + 15 * IDECHS.countCylinder) * 255 + 
              IDECHS.countSector - 1;
  return 0;
}
/*---------------------------------------------------------------------------*/;
int a_lba2chs(tCHS geometry, tLBA LBA, tCHS* CHS)
{
  CHS->countCylinder = LBA.lba / geometry.countCylinder / geometry.countHead;
  CHS->countHead = (LBA.lba / geometry.countSector) % geometry.countHead;
  CHS->countSector = LBA.lba % geometry.countHead + 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_lba2large(tLARGE geometry, tLBA LBA, tLARGE* LARGE)
{
  LARGE->countSector = (LBA.lba / geometry.countCylinder) / geometry.countHead;
  LARGE->countHead = (LBA.lba / geometry.countSector) % geometry.countHead;
  LARGE->countCylinder = LBA.lba % geometry.countHead + 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_lba2idechs(tIDECHS geometry, tLBA LBA, tIDECHS* IDECHS)
{
  IDECHS->countSector = (LBA.lba / geometry.countCylinder) / geometry.countHead;
  IDECHS->countHead = (LBA.lba / geometry.countSector) % geometry.countHead;
  IDECHS->countCylinder = LBA.lba % geometry.countHead + 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_chs2lba(tCHS geometry, tCHS CHS, tLBA* LBA)
{
  LBA->lba = (CHS.countCylinder * geometry.countHead + CHS.countHead) * 
             geometry.countSector + CHS.countSector - 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_large2lba(tLARGE geometry, tLARGE LARGE, tLBA* LBA)
{
  LBA->lba = (LARGE.countCylinder * geometry.countHead + LARGE.countHead) *
               geometry.countSector + LARGE.countSector - 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_idechs2lba(tIDECHS geometry, tIDECHS IDECHS, tLBA* LBA)
{
  LBA->lba = (IDECHS.countCylinder * geometry.countHead + IDECHS.countHead) * 
             geometry.countSector + IDECHS.countSector - 1;
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_large2chs(tLARGE geometry1,tCHS geometry2,tLARGE LARGE, tCHS* CHS)
{
  tLBA tmpLBA;
  a_large2lba(geometry1, LARGE, &tmpLBA);
  a_lba2chs(geometry2, tmpLBA, CHS);
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_large2idechs(tLARGE geometry1, tIDECHS geometry2, tLARGE LARGE,
                   tIDECHS* IDECHS)
{
  tLBA tmpLBA;
  a_large2lba(geometry1, LARGE, &tmpLBA);
  a_lba2idechs(geometry2, tmpLBA, IDECHS);
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_chs2large(tCHS geometry1, tLARGE geometry2, tCHS CHS, tLARGE* LARGE)
{
  tLBA tmpLBA;
  a_chs2lba(geometry1, CHS, &tmpLBA);
  a_lba2large(geometry2, tmpLBA, LARGE);
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_idechs2large(tIDECHS geometry1, tLARGE geometry2, tIDECHS IDECHS, tLARGE* LARGE)
{
  tLBA tmpLBA;
  a_idechs2lba(geometry1, IDECHS, &tmpLBA);
  a_lba2large(geometry2, tmpLBA, LARGE);
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_chs2idechs(tCHS geometry1, tIDECHS geometry2, tCHS CHS, tIDECHS* IDECHS)
{
  tLBA tmpLBA;
  a_chs2lba(geometry1, CHS, &tmpLBA);
  a_lba2idechs(geometry2, tmpLBA, IDECHS);
  return 0;
}
/*---------------------------------------------------------------------------*/
int a_idechs2chs(tIDECHS geometry1, tCHS geometry2, tIDECHS IDECHS,tCHS* CHS)
{
  tLBA tmpLBA;
  a_idechs2lba(geometry1, IDECHS, &tmpLBA);
  a_lba2chs(geometry2, tmpLBA, CHS);
  return 0;
}

