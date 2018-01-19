/*
* @file plain_render_manager.h
* @Basic class PlainRenderManager
* @author Wei Chen
*
* This file is part of Physika, a versatile physics simulation library.
* Copyright (C) 2013- Physika Group.
*
* This Source Code Form is subject to the terms of the GNU General Public License v2.0.
* If a copy of the GPL was not distributed with this file, you can obtain one at:
* http://www.gnu.org/licenses/gpl-2.0.html
*
*/

#pragma once

#include "Physika_Render/Render_Manager_Base/render_manager_base.h"

namespace Physika{

class PalinRenderManager: public RenderManagerBase
{
public:
    void render() override;
};
   
}