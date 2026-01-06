/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "compatible/components/component_loader.h"

#include <functional>
#include <string>
#include <unordered_map>

#include "compatible/components/badge/badge_loader.h"
#include "compatible/components/canvas/canvas_loader.h"
#include "compatible/components/grid_column/grid_col_loader.h"
#include "compatible/components/grid_container/grid_container_loader.h"
#include "compatible/components/grid_row/grid_row_loader.h"
#include "compatible/components/image-animator/image_animator_loader.h"
#include "compatible/components/marquee/marquee_loader.h"
#include "compatible/components/label/label_loader.h"
#include "compatible/components/svg/svg_loader.h"
#include "compatible/components/qrcode/qrcode_loader.h"
#include "compatible/components/rating/rating_loader.h"
#include "frameworks/base/log/log_wrapper.h"

#include "compatible/components/video/video_loader.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_Compatible_GetLoader(const char* name)
{
    return OHOS::Ace::ComponentLoader::GetLoaderByName(name);
}

namespace OHOS::Ace {

ComponentLoader* ComponentLoader::GetLoaderByName(const char* name)
{
    std::string nameStr(name);
    static std::unordered_map<std::string, std::function<ComponentLoader*()>> sLoaderMap = {
        { "badge", []() -> ComponentLoader* { return new BadgeLoader(); } },
        { "grid-col", []() -> ComponentLoader* { return new GridColLoader(); } },
        { "grid-container", []() -> ComponentLoader* { return new GridContainerLoader(); } },
        { "grid-row", []() -> ComponentLoader* { return new GridRowLoader(); } },
        { "marquee", []() -> ComponentLoader* { return new MarqueeLoader(); } },
        { "label", []() -> ComponentLoader* { return new LabelLoader(); } },
        { "image-animator", []() -> ComponentLoader* { return new ImageAnimatorLoader(); } },
        { "svg", []() -> ComponentLoader* { return new SvgLoader(); } },
        { "animate", []() -> ComponentLoader* { return new SvgAnimateLoader(); } },
        { "animatemotion", []() -> ComponentLoader* { return new SvgAnimateMotionLoader(); } },
        { "animatetransform", []() -> ComponentLoader* { return new SvgAnimateTransformLoader(); } },
        { "circle", []() -> ComponentLoader* { return new SvgCircleLoader(); } },
        { "defs", []() -> ComponentLoader* { return new SvgDefsLoader(); } },
        { "ellipse", []() -> ComponentLoader* { return new SvgEllipseLoader(); } },
        { "fecolormatrix", []() -> ComponentLoader* { return new SvgFeColorMatrixLoader(); } },
        { "fecomposite", []() -> ComponentLoader* { return new SvgFeCompositeLoader(); } },
        { "fegaussianblur", []() -> ComponentLoader* { return new SvgFeGaussianBlurLoader(); } },
        { "feoffset", []() -> ComponentLoader* { return new SvgFeOffsetLoader(); } },
        { "filter", []() -> ComponentLoader* { return new SvgFilterLoader(); } },
        { "g", []() -> ComponentLoader* { return new SvgGLoader(); } },
        { "line", []() -> ComponentLoader* { return new SvgLineLoader(); } },
        { "mask", []() -> ComponentLoader* { return new SvgMaskLoader(); } },
        { "path", []() -> ComponentLoader* { return new SvgPathLoader(); } },
        { "polygon", []() -> ComponentLoader* { return new SvgPolygonLoader(); } },
        { "polyline", []() -> ComponentLoader* { return new SvgPolylineLoader(); } },
        { "rect", []() -> ComponentLoader* { return new SvgRectLoader(); } },
        { "svg-text", []() -> ComponentLoader* { return new SvgTextLoader(); } },
        { "textpath", []() -> ComponentLoader* { return new SvgTextPathLoader(); } },
        { "tspan", []() -> ComponentLoader* { return new SvgTspanLoader(); } },
        { "use", []() -> ComponentLoader* { return new SvgUseLoader(); } },
        { "linearGradient", []() -> ComponentLoader* { return new SvgGradientLoader(); } },
        { "radialGradient", []() -> ComponentLoader* { return new SvgGradientLoader(); } },
        { "stop", []() -> ComponentLoader* { return new SvgStopLoader(); } },
        { "video", []() -> ComponentLoader* { return new VideoLoader(); } },
        { "qrcode", []() -> ComponentLoader* { return new QRCodeLoader(); } },
        { "rating", []() -> ComponentLoader* { return new RatingLoader(); } }
    };
    auto loaderIter = sLoaderMap.find(nameStr);
    if (loaderIter != sLoaderMap.end()) {
        return loaderIter->second();
    }

    return nullptr;
}

} // namespace OHOS::Ace