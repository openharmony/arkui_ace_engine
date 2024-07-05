/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CANVAS_RENDERER_CANVAS_RENDERER_TYPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CANVAS_RENDERER_CANVAS_RENDERER_TYPE_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::NG {
class SvgDomBase;
}
namespace OHOS::Ace {
struct BaseInfo {
    bool isOffscreen;
    bool anti;
    PaintState paintState;
    RefPtr<AceType> canvasPattern;
    RefPtr<AceType> offscreenPattern;
};

struct FillTextInfo {
    std::string text;
    double x;
    double y;
    std::optional<double> maxWidth;
};

struct ImageInfo {
    CanvasImage image;
    double imgWidth;
    double imgHeight;
    RefPtr<PixelMap> pixelMap;
    RefPtr<NG::SvgDomBase> svgDom;
    bool isImage;
    bool isSvg;
    NG::SizeF imageSize;
    ImageFit imageFit;
    int32_t instanceId = 0;
};

struct ImageSize {
    double left;
    double top;
    double width;
    double height;
};

struct BitmapMeshInfo {
    std::vector<double> mesh;
    double column;
    double row;
    RefPtr<AceType> offscreenPattern;
    RefPtr<AceType> pool;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CANVAS_RENDERER_CANVAS_RENDERER_TYPE_H
