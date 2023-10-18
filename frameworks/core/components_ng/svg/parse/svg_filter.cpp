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

#include "frameworks/core/components_ng/svg/parse/svg_filter.h"

#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_filter_declaration.h"
#include "frameworks/core/components_ng/svg/parse/svg_fe.h"

namespace OHOS::Ace::NG {

SvgFilter::SvgFilter() : SvgQuote()
{
    declaration_ = AceType::MakeRefPtr<SvgFilterDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgFilter::Create()
{
    return AceType::MakeRefPtr<SvgFilter>();
}

void SvgFilter::OnInitStyle()
{
    auto declaration = Ace::AceType::DynamicCast<SvgFilterDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    x_ = declaration->GetX();
    y_ = declaration->GetY();
    height_ = declaration->GetHeight();
    width_ = declaration->GetWidth();
    OnAsPaint();
}

void SvgFilter::OnDrawTraversed(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
}

void SvgFilter::OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
}

void SvgFilter::OnDrawTraversedAfter(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->saveLayer(nullptr, &filterPaint_);
#else
    RSSaveLayerOps slo(nullptr, &filterBrush_);
    rsCanvas_->SaveLayer(slo);
#endif
}

void SvgFilter::OnAsPaint()
{
#ifndef USE_ROSEN_DRAWING
    filterPaint_.setAntiAlias(true);
    sk_sp<SkImageFilter> imageFilter = nullptr;
#else
    filterBrush_.SetAntiAlias(true);
    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
#endif
    ColorInterpolationType currentColor = ColorInterpolationType::SRGB;

    for (const auto& item : children_) {
        auto nodeFe = AceType::DynamicCast<SvgFe>(item);
        if (!nodeFe) {
            continue;
        }
        nodeFe->GetImageFilter(imageFilter, currentColor);
    }

    SvgFe::ConverImageFilterColor(imageFilter, currentColor, ColorInterpolationType::SRGB);
#ifndef USE_ROSEN_DRAWING
    filterPaint_.setImageFilter(imageFilter);
#else
    auto filter = filterBrush_.GetFilter();
    filter.SetImageFilter(imageFilter);
    filterBrush_.SetFilter(filter);
#endif
}

} // namespace OHOS::Ace::NG
