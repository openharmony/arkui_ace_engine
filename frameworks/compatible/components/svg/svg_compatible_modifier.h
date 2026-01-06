/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_SVG_COMPATIBLE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_SVG_COMPATIBLE_MODIFIER_H

#include <memory>
#include <optional>

#include "core/components_ng/render/drawing_forward.h"

class SkStream;

namespace OHOS::Ace {
class Offset;
class PipelineContext;
class Rect;
class RenderContext;
class RenderSvgBase;
class RosenRenderSvgPattern;
class Size;
class SvgDom;
class Color;
struct SvgRenderTree;
struct SvgRadius;
enum class ImageFit;
template<class T>
class RefPtr;
} // namespace OHOS::Ace

struct ArkUISvgCompatibleModifier {
    void (*setSvgRenderTreeAndUpdateLayout)(OHOS::Ace::PipelineContext* context,
        OHOS::Ace::SvgRenderTree* svgRenderTree, OHOS::Ace::ImageFit imageFit, OHOS::Ace::SvgRadius* svgRadius,
        bool directPaint);
    OHOS::Ace::RefPtr<OHOS::Ace::SvgDom> (*createSvgDom)(
        SkStream* svgStream, OHOS::Ace::PipelineContext* context, const OHOS::Ace::Color* svgThemeColor);
    OHOS::Ace::SvgRenderTree* (*createRenderTree)(OHOS::Ace::RefPtr<OHOS::Ace::SvgDom> svg,
        OHOS::Ace::ImageFit imageFit, OHOS::Ace::SvgRadius* svgRadius, bool useBox);
    void (*paintDirectly)(OHOS::Ace::RefPtr<OHOS::Ace::SvgDom> svg, OHOS::Ace::RenderContext* context,
        const OHOS::Ace::Offset* offset, OHOS::Ace::ImageFit imageFit, OHOS::Ace::Size* layout);
    OHOS::Ace::RefPtr<OHOS::Ace::RosenRenderSvgPattern> (*getPatternFromRoot)(
        OHOS::Ace::RefPtr<OHOS::Ace::RenderSvgBase> node, const char* id);
    bool (*onAsPaint)(OHOS::Ace::RefPtr<OHOS::Ace::RosenRenderSvgPattern> pattern, const OHOS::Ace::Offset* offset,
        const OHOS::Ace::Rect* paintRect, OHOS::Ace::RSPen* rsPen, OHOS::Ace::RSBrush* rsBrush);
};
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_SVG_COMPATIBLE_MODIFIER_H
