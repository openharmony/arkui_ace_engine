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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_SVG_CANVAS_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_SVG_CANVAS_IMAGE_H

#include "core/components_ng/image_provider/svg_dom.h"
#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class SkiaSvgCanvasImage : public CanvasImage {
    DECLARE_ACE_TYPE(SkiaSvgCanvasImage, CanvasImage)
public:
    SkiaSvgCanvasImage() = default;
    explicit SkiaSvgCanvasImage(const RefPtr<SvgDom>& svgDom) : svgDom_(svgDom) {}
    ~SkiaSvgCanvasImage() override = default;

    void SetSVGDom(const RefPtr<SvgDom>& svgDom);
    const RefPtr<SvgDom>& GetSVGDom() const;

    int32_t GetWidth() const override
    {
        return svgDom_->GetContainerSize().Width();
    }

    int32_t GetHeight() const override
    {
        return svgDom_->GetContainerSize().Height();
    }

    void DrawToRSCanvas(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) override;

private:
    RefPtr<SvgDom> svgDom_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_SVG_CANVAS_IMAGE_H
