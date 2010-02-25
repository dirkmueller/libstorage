/*
 * Copyright (c) [2004-2010] Novell, Inc.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#include "storage/Device.h"
#include "storage/AsciiFile.h"
#include "storage/AppUtil.h"
#include "storage/StorageTmpl.h"


namespace storage
{
    using namespace std;


    Device::Device(const string& nm, const string& dev)
	: nm(nm), dev(dev), create(false), del(false), silent(false), size_k(0), mjr(0), mnr(0)
    {
    }


    Device::Device(const string& nm, const string& dev, SystemInfo& systeminfo)
	: nm(nm), dev(dev), create(false), del(false), silent(false), size_k(0), mjr(0), mnr(0)
    {
    }


    Device::Device(const AsciiFile& file)
	: nm(), dev(), create(false), del(false), silent(false), size_k(0), mjr(0), mnr(0)
    {
	const vector<string>& lines = file.lines();

	if (lines.size() > 1)
	{
	    // Container

	    for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it)
	    {
		if (boost::starts_with(*it, "Name:"))
		    nm = extractNthWord(1, *it);
		if (boost::starts_with(*it,  "Device:"))
		    dev = extractNthWord(1, *it);

		if (boost::starts_with(*it, "SizeK:"))
		    extractNthWord(1, *it) >> size_k;

		if (boost::starts_with(*it, "Major:"))
		    extractNthWord(1, *it) >> mjr;
		if (boost::starts_with(*it, "Minor:"))
		    extractNthWord(1, *it) >> mnr;
	    }
	}
	else
	{
	    // Volume
	}

	y2deb("constructed Device " << dev << " from file " << file.name());
    }


    Device::Device(const Device& d)
	: nm(d.nm), dev(d.dev), create(d.create), del(d.del), silent(d.silent), size_k(d.size_k),
	  mjr(d.mjr), mnr(d.mnr), uby(d.uby), alt_names(d.alt_names)
    {
	y2deb("copy-constructed Device from " << d.dev);
    }


    Device::~Device()
    {
	y2deb("destructed Device " << dev);
    }


    bool
    Device::getMajorMinor()
    {
	return storage::getMajorMinor(dev, mjr, mnr);
    }


    string
    Device::udevPath() const
    {
	return string();
    }

    list<string>
    Device::udevId() const
    {
	return list<string>();
    }


    void
    Device::setUsedBy(UsedByType type, const string& device)
    {
	uby.clear();
	uby.push_back(UsedBy(type, device));
    }

    void
    Device::addUsedBy(UsedByType type, const string& device)
    {
	uby.push_back(UsedBy(type, device));
    }

    void
    Device::removeUsedBy(UsedByType type, const string& device)
    {
	uby.remove(UsedBy(type, device));
    }

    bool
    Device::isUsedBy(UsedByType type) const
    {
	for (list<UsedBy>::const_iterator it = uby.begin(); it != uby.end(); ++it)
	    if (it->type() == type)
		return true;

	return false;
    }


bool Device::sameDevice( const string& device ) const
    {
    string d = normalizeDevice(device);
    return( d==dev ||
	    find( alt_names.begin(), alt_names.end(), d )!=alt_names.end() );
    }


    std::ostream& operator<<(std::ostream& s, const Device& d)
    {
	s << "Name:" << d.nm << " Device:" << d.dev;
	s << " SizeK:" << d.size_k;
	if (d.mjr != 0 || d.mnr != 0)
	    s << " Node:<" << d.mjr << ":" << d.mnr << ">";
	if (d.create)
	    s << " created";
	if (d.del)
	    s << " deleted";
	if (d.silent)
	    s << " silent";
	return s;
    }

}
