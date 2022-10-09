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

#include "core/components_ng/image_provider/adapter/skia_svg_dom.h"

#include "draw/canvas.h"
#include "skia_adapter/skia_canvas.h"

namespace OHOS::Ace::NG {

union SkColorEx {
    struct {
        SkColor color : 32;
        bool valid : 1;
        uint32_t reserved : 31; // reserved
    };
    uint64_t value = 0;
};

RefPtr<SkiaSvgDom> SkiaSvgDom::CreateSkiaSvgDom(SkStream& svgStream, const std::optional<Color>& svgFillColor)
{
    SkColorEx skColor;
    if (svgFillColor.has_value()) {
        skColor.color = svgFillColor.value().GetValue();
        skColor.valid = 1;
    }
#ifdef NG_BUILD
        // NG not support svg yet
        sk_sp<SkSVGDOM> skiaDom = nullptr;
#else
        auto skiaDom = SkSVGDOM::MakeFromStream(svgStream, skColor.value);
#endif
        return AceType::MakeRefPtr<SkiaSvgDom>(skiaDom);
}

void SkiaSvgDom::DrawImage(
    RSCanvas& canvas, const ImageFit&  /*imageFit*/, const Size& layout, const std::optional<Color>&  /*color*/)
{
#ifndef NG_BUILD
    CHECK_NULL_VOID(skiaDom_);
    auto rsCanvas = canvas.GetImpl<Rosen::Drawing::SkiaCanvas>();
    CHECK_NULL_VOID(rsCanvas);
    auto *skCanvas = rsCanvas->ExportSkCanvas();
    //TODO:use graphics_2d to paint SVG
    auto svgContainerSize = SizeF(layout.Width(), layout.Height());
    if (svgContainerSize.IsNegative()) {
        // when layout size is invalid, try the container size of svg
        if (GetContainerSize().IsNegative()) {
            return;
        }
        svgContainerSize = GetContainerSize();
    }
    //TODO:svg ObjectFit
    double width = svgContainerSize.Width();
    double height = svgContainerSize.Height();
    SetContainerSize(svgContainerSize);
    skCanvas->clipRect({ 0, 0, width, height }, SkClipOp::kIntersect, true);
    Render(skCanvas);
#endif
}

const sk_sp<SkSVGDOM>& SkiaSvgDom::GetSkiaSvgDom() const
{
    return skiaDom_;
}

void SkiaSvgDom::Render(SkCanvas* skCanvas)
{
#ifndef NG_BUILD
    skiaDom_->render(skCanvas);
#endif
}

SizeF SkiaSvgDom::GetContainerSize() const
{
#ifdef NG_BUILD
    return {};
#else
    return SizeF(skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
#endif
}

void SkiaSvgDom::SetContainerSize(const SizeF& containerSize)
{
#ifndef NG_BUILD
    skiaDom_->setContainerSize({containerSize.Width(), containerSize.Height()});
#endif
}

} // namespace OHOS::Ace::NG
