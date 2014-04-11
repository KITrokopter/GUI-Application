// Copyright (C) 2012 Fabian Beutel (hedgeware)
// www.hedgeware.net
// This code is licenced under the "Irrlicht Engine License" (details:
// http://irrlicht.sourceforge.net/license/)

#include "CQtReadFile.h"
#include <QFile>

CQtReadFile::CQtReadFile(const irr::io::path &fileName)
	: IODevice(NULL), FileName(fileName)
{
	IODevice = new QFile(fileName.c_str());
	IODevice->open(QIODevice::ReadOnly);
}

CQtReadFile::CQtReadFile(QIODevice *qtDevice, const irr::io::path &name)
	: IODevice(qtDevice), FileName(name)
{
	if (IODevice) {
		if (IODevice->parent()) {
			IODevice->setParent(NULL);
		}

		if (!IODevice->isOpen()) {
			IODevice->open(QIODevice::ReadOnly);
		}
	}
}

CQtReadFile::~CQtReadFile()
{
	if (IODevice) {
		delete IODevice;
	}
}

irr::s32 CQtReadFile::read(void *buffer, irr::u32 sizeToRead)
{
	if (IODevice) {
		return (irr::s32)IODevice->read((char*)buffer, (qint64)sizeToRead);
	} else   {
		return -1;
	}
}

bool CQtReadFile::seek(long finalPos, bool relativeMovement)
{
	if (IODevice) {
		return IODevice->seek(relativeMovement ? (qint64)(finalPos + getPos()) : (qint64)finalPos);
	} else   {
		return false;
	}
}

long CQtReadFile::getSize() const
{
	return IODevice ? (long)IODevice->size() : 0;
}

bool CQtReadFile::isOpen() const
{
	return IODevice ? IODevice->isOpen() : false;
}

long CQtReadFile::getPos() const
{
	return IODevice ? (long)IODevice->pos() : 0;
}

const irr::io::path& CQtReadFile::getFileName() const
{
	return FileName;
}

QIODevice* CQtReadFile::getQtDevice() const
{
	return IODevice;
}

