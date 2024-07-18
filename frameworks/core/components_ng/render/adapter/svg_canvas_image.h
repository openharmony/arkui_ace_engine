/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SVG_CANVAS_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SVG_CANVAS_IMAGE_H

#include "core/components_ng/image_provider/svg_dom_base.h"

namespace OHOS::Ace::NG {

class SvgCanvasImage : public CanvasImage {
    DECLARE_ACE_TYPE(SvgCanvasImage, CanvasImage)
public:
    explicit SvgCanvasImage(const RefPtr<SvgDomBase>& svgDom) : svgDom_(svgDom) {}
    ~SvgCanvasImage() override = default;

    void SetFillColor(const std::optional<Color>& color)
    {
        svgDom_->SetFillColor(color);
    }

    void SetSmoothEdge(float value)
    {
        svgDom_->SetSmoothEdge(value);
    }

    void SetColorFilter(const std::optional<ImageColorFilter>& colorFilter)
    {
        svgDom_->SetColorFilter(colorFilter);
    }

    const RefPtr<SvgDomBase>& GetSVGDom() const;

    int32_t GetWidth() const override
    {
        return svgDom_->GetContainerSize().Width();
    }

    int32_t GetHeight() const override
    {
        return svgDom_->GetContainerSize().Height();
    }

    void DrawToRSCanvas(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) override;
    void DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) override;
    bool IsStatic() override;
    void SetRedrawCallback(std::function<void()>&& callback) override;
    void SetOnFinishCallback(std::function<void()>&& callback) override;

    void ControlAnimation(bool play) override;

private:
    const RefPtr<SvgDomBase> svgDom_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SVG_CANVAS_IMAGE_H
