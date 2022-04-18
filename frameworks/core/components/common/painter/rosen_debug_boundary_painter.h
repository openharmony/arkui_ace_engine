/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_ROSEN_DEBUG_BOUNDARY_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_ROSEN_DEBUG_BOUNDARY_PAINTER_H

#include <math.h>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/border_edge.h"
#include "core/components/common/properties/border_image_edge.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/edge.h"
#include "core/components/image/render_image.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

class RosenDebugBoundaryPainter : public virtual AceType {
    DECLARE_ACE_TYPE(RosenDebugBoundaryPainter, AceType);
public:
    static void PaintDebugBoundary(SkCanvas* canvas, const Offset& offset, const Size& layoutSize);
    static void PaintDebugMargin(SkCanvas* canvas, const Offset& offset, const Size& layoutSize, const EdgePx margin);
    static void PaintDebugCorner(SkCanvas* canvas, const Offset& offset, const Size& layoutSize);    
};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_ROSEN_DEBUG_BOUNDARY_PAINTER_H