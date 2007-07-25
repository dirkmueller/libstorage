#ifndef NFS_H
#define NFS_H

#include "y2storage/Volume.h"

namespace storage
{
class NfsCo;

class Nfs : public Volume
    {
    public:
	Nfs( const NfsCo& d, const string& NfsDev );
	Nfs( const NfsCo& d, const Nfs& d );
	virtual ~Nfs();
	friend std::ostream& operator<< (std::ostream& s, const Nfs& l );

	static string canonicalName( const string& dev );

	virtual void print( std::ostream& s ) const { s << *this; }

	void getInfo( storage::NfsInfo& info ) const;
	bool equalContent( const Nfs& rhs ) const;
	void logDifference( const Nfs& d ) const;

    protected:
	void init();
	Nfs& operator=( const Nfs& );

	mutable storage::NfsInfo info;
    };

}

#endif