/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_IMAGE_FIT_CONVERTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_IMAGE_FIT_CONVERTOR_H

#include "core/components_ng/render/drawing.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
class SvgFitConvertor {
public:
    SvgFitConvertor();
    ~SvgFitConvertor();

    static void ApplyFit(ImageFit imageFit, RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyFill(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyContain(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyCover(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyWidth(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyHeight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyNone(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyScaleDown(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentTopLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentTop(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentTopRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentCenterLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentCenter(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentCenterRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentBottomLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentBottom(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void ApplyAlignmentBottomRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize);
    static void AdjustContentFit(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize,
        float svgScale, Alignment alignMent);
    static void DrawNothing(RSCanvas& canvas);
    static const std::vector<void (*)(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)> FIT_OPERATIONS;
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_IMAGE_FIT_CONVERTOR_H