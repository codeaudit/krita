/*
 *  Copyright (c) 2006 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <kdebug.h>
#include <klocale.h>

#include <KoIntegerMaths.h>
#include <KoColorSpaceRegistry.h>

#include "kis_gray_u16_colorspace.h"

#include "compositeops/KoCompositeOpOver.h"
#include "compositeops/KoCompositeOpErase.h"
#include "compositeops/KoCompositeOpMultiply.h"
#include "compositeops/KoCompositeOpDivide.h"
#include "compositeops/KoCompositeOpBurn.h"

KisGrayAU16ColorSpace ::KisGrayAU16ColorSpace(KoColorSpaceRegistry * parent, KoColorProfile *p) :
            KoLcmsColorSpace<GrayAU16Traits>("GRAYA16", i18n("Grayscale 16-bit integer/channel)"), parent, TYPE_GRAYA_16, icSigGrayData, p)
{
    addChannel(new KoChannelInfo(i18n("Gray"), 0, KoChannelInfo::COLOR, KoChannelInfo::UINT16));
    addChannel(new KoChannelInfo(i18n("Alpha"), 1, KoChannelInfo::ALPHA, KoChannelInfo::UINT16));

    init();

    addCompositeOp( new KoCompositeOpOver<GrayAU16Traits>( this ) );
    addCompositeOp( new KoCompositeOpErase<GrayAU16Traits>( this ) );
    addCompositeOp( new KoCompositeOpMultiply<GrayAU16Traits>( this ) );
    addCompositeOp( new KoCompositeOpDivide<GrayAU16Traits>( this ) );
    addCompositeOp( new KoCompositeOpBurn<GrayAU16Traits>( this ) );
}
