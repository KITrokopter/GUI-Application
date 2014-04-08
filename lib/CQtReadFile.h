// Copyright (C) 2012 Fabian Beutel (hedgeware)
// www.hedgeware.net
// This code is licenced under the "Irrlicht Engine License" (details: http://irrlicht.sourceforge.net/license/)

#ifndef __C_QT_READ_FILE_H_INCLUDED__
#define __C_QT_READ_FILE_H_INCLUDED__

#include <irrlicht/IReadFile.h>
class QIODevice;


/*!
	Wrapper class for providing access to Qt IO devices to Irrlicht
*/
class CQtReadFile : public irr::io::IReadFile
{
public:
	//! Constructs and opens a new file using the fileName.
	//! \param fileName The path to open. Can also be a Qt resource (e.g. ":/my_resources/resource1.png")
	CQtReadFile(const irr::io::path& fileName);

	//! Constructs and opens a new file using a preconstructed QIODevice.
	//! \param qtDevice The device to use. Note that CQtReadFile will take ownership of QIODevice and will delete it when being destructed)
	//! \param name An optional name that will be returned when calling getFileName().
	CQtReadFile(QIODevice* qtDevice, const irr::io::path& name = irr::io::path());

	//! Destructor
	virtual ~CQtReadFile();

	//! returns how much was read
	virtual irr::s32 read(void* buffer, irr::u32 sizeToRead);

	//! changes position in file, returns true if successful
	virtual bool seek(long finalPos, bool relativeMovement = false);

	//! returns size of file
	virtual long getSize() const;

	//! returns if file is open
	virtual bool isOpen() const;

	//! returns where in the file we are.
	virtual long getPos() const;

	//! returns name of file
	virtual const irr::io::path& getFileName() const;

	//! Returns a pointer to the Qt IO device this file is using.
	//! Note: Ownership still belongs to CQtReadFile, so don't delete the QIODevice
	virtual QIODevice* getQtDevice() const;

private:

	//! The Qt file device to access
	QIODevice* IODevice;

	//! Stores the filename
	irr::io::path FileName;
};


#endif

