/*
 * Copyright (C) 2017 Robin Gareus <robin@gareus.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#include <malloc.h>
#endif

#include <cstring>

#include "pbd/spinlock.h"

using namespace PBD;

spinlock_t::spinlock_t ()
{
	boost::detail::spinlock init = BOOST_DETAIL_SPINLOCK_INIT;
	std::memcpy (&l, &init, sizeof (init));
}

SpinLock::SpinLock (spinlock_t& lock)
	: _lock (lock)
{
	_lock.lock ();
}

SpinLock::~SpinLock ()
{
	_lock.unlock ();
}
