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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_SVG_DOM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_SVG_DOM_H

#include "include/core/SkColor.h"
#include "include/core/SkStream.h"
#include "modules/svg/include/SkSVGDOM.h"

#include "core/components_ng/image_provider/svg_dom_base.h"

namespace OHOS::Ace::NG {

class SkiaSvgDom : public SvgDomBase {
    DECLARE_ACE_TYPE(SkiaSvgDom, SvgDomBase);

public:
    SkiaSvgDom() = default;
    explicit SkiaSvgDom(const sk_sp<SkSVGDOM>& skiaDom) : skiaDom_(skiaDom)
    {
        const SkSize& size = skiaDom_->containerSize();
        svgSize_.SetWidth(size.width());
        svgSize_.SetHeight(size.height());
    }

    static RefPtr<SkiaSvgDom> CreateSkiaSvgDom(SkStream& svgStream, const std::optional<Color>& svgFillColor);

    void OffScreenDraw(RSCanvas& canvas, const ImageFit& imageFit, const Size& layout);
    void DrawImage(RSCanvas& canvas, const ImageFit& imageFit, const Size& layout) override;

    const sk_sp<SkSVGDOM>& GetSkiaSvgDom() const;

    void Render(SkCanvas* skCanvas);

    SizeF GetContainerSize() const override;
    void SetContainerSize(const SizeF& containerSize) override;

    // skia SVG doesn't support <animate> element

private:
    void FitImage(SkCanvas* canvas, const ImageFit& imageFit, const Size& layout);
    void FitViewPort(const Size& layout);

    sk_sp<SkSVGDOM> skiaDom_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_SVG_DOM_H
