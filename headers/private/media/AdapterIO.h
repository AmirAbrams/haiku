/*
 * Copyright 2016 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _ADAPTER_IO_H
#define _ADAPTER_IO_H


#include <MediaIO.h>
#include <OS.h>
#include <RWLocker.h>
#include <SupportDefs.h>


class BAdapterIO;
class RelativePositionIO;


class BInputAdapter {
public:
	virtual	ssize_t					Write(const void* buffer, size_t size);

private:
	friend class BAdapterIO;

									BInputAdapter(BAdapterIO* io);
	virtual							~BInputAdapter();

			BAdapterIO*				fIO;

	virtual	void					_ReservedInputAdapter1();
	virtual void					_ReservedInputAdapter2();

			uint32					_reserved[2];
};


class BAdapterIO : public BMediaIO {
public:
									BAdapterIO(int32 flags,
										bigtime_t timeout = B_INFINITE_TIMEOUT);
	virtual							~BAdapterIO();

	virtual void					GetFlags(int32* flags) const;

	virtual	ssize_t					ReadAt(off_t position, void* buffer,
										size_t size);
	virtual	ssize_t					WriteAt(off_t position,
										const void* buffer, size_t size);

	virtual	off_t					Seek(off_t position, uint32 seekMode);
	virtual off_t					Position() const;

	virtual	status_t				SetSize(off_t size);
	virtual	status_t				GetSize(off_t* size) const;

			BInputAdapter*			BuildInputAdapter();

protected:
	friend class BInputAdapter;

			void					SetBuffer(BPositionIO* io);

			ssize_t					BackWrite(const void* buffer, size_t size);

			status_t				SeekRequested(off_t position);
			status_t				SeekCompleted(off_t position);

private:
			status_t				_EvaluateWait(off_t position);

			int32					fFlags;
			bigtime_t				fTimeout;

			RelativePositionIO*		fBuffer;
			off_t					fTotalSize;

			BInputAdapter*			fInputAdapter;

									BAdapterIO(const BAdapterIO&);
			BAdapterIO&				operator=(const BAdapterIO&);

	virtual	void					_ReservedAdapterIO1();
	virtual void					_ReservedAdapterIO2();
	virtual void					_ReservedAdapterIO3();
	virtual void					_ReservedAdapterIO4();
	virtual void					_ReservedAdapterIO5();

			uint32					_reserved[5];
};

#endif	// _ADAPTER_IO_H
