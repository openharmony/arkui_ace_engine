/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/video/render_texture.h"

namespace OHOS::Ace {

RenderTexture::RenderTexture() : RenderNode(true) {}

void RenderTexture::Update(const RefPtr<Component>& component)
{
    const RefPtr<TextureComponent> texture = AceType::DynamicCast<TextureComponent>(component);
    if (!texture) {
        return;
    }

    textureId_ = texture->GetTextureId();
    sourceSize_ = Size(static_cast<double>(texture->GetSrcWidth()), static_cast<double>(texture->GetSrcHeight()));
#ifndef OHOS_STANDARD_SYSTEM
    imageFit_ = texture->GetFit();
#endif
    imagePosition_ = texture->GetImagePosition();

    MarkNeedLayout();
}

void RenderTexture::SetHidden(bool hidden)
{
    RenderNode::SetHidden(hidden);
    if (hiddenChangeEvent_) {
        hiddenChangeEvent_(hidden);
    }
}

void RenderTexture::PerformLayout()
{
    if (!NeedLayout()) {
        return;
    }
    double width = GetLayoutParam().GetMinSize().Width();
    double height = GetLayoutParam().GetMinSize().Height();
    for (const auto& item : GetChildren()) {
        item->Layout(GetLayoutParam());
        width = std::max(width, item->GetLayoutSize().Width());
        height = std::max(height, item->GetLayoutSize().Height());
    }

    if (!GetLayoutParam().GetMaxSize().IsInfinite()) {
        SetLayoutSize(GetLayoutParam().GetMaxSize());
    } else {
        SetLayoutSize(Size(width, height));
    }

    switch (imageFit_) {
        case ImageFit::CONTAIN:
            CalculateFitContain();
            break;
        case ImageFit::FILL:
            CalculateFitFill();
            break;
        case ImageFit::COVER:
            CalculateFitCover();
            break;
        case ImageFit::NONE:
            CalculateFitNone();
            break;
        case ImageFit::SCALEDOWN:
            CalculateFitScaleDown();
            break;
        default:
            CalculateFitContain();
            break;
    }

    ApplyObjectPosition();

    SetNeedLayout(false);
    if (textureSizeChangeEvent_) {
        textureSizeChangeEvent_(textureId_, drawSize_.Width(), drawSize_.Height());
    }
    if (textureOffsetChangeEvent_) {
        textureOffsetChangeEvent_(textureId_,
            (int32_t)(alignmentX_ + GetGlobalOffset().GetX()), (int32_t)(alignmentY_ + GetGlobalOffset().GetY()));
    }
    MarkNeedRender();
}

void RenderTexture::ApplyObjectPosition()
{
    const Size& layoutSize = GetLayoutSize();
    if (imagePosition_.GetSizeTypeX() == BackgroundImagePositionType::PX) {
        alignmentX_ = imagePosition_.GetSizeValueX();
    } else {
        alignmentX_ = imagePosition_.GetSizeValueX() * (layoutSize.Width() - drawSize_.Width()) / PERCENT_TRANSLATE;
    }

    if (imagePosition_.GetSizeTypeY() == BackgroundImagePositionType::PX) {
        alignmentY_ = imagePosition_.GetSizeValueY();
    } else {
        alignmentY_ = imagePosition_.GetSizeValueY() * (layoutSize.Height() - drawSize_.Height()) / PERCENT_TRANSLATE;
    }
}

void RenderTexture::CalculateFitContain()
{
    const Size& layoutSize = GetLayoutSize();
    double sourceRatio = sourceSize_.Width() / sourceSize_.Height();
    double layoutRatio = layoutSize.Width() / layoutSize.Height();

    if (sourceRatio < layoutRatio) {
        drawSize_ = Size(sourceRatio * layoutSize.Height(), layoutSize.Height());
    } else {
        drawSize_ = Size(layoutSize.Width(), layoutSize.Width() / sourceRatio);
    }
}

void RenderTexture::CalculateFitCover()
{
    const Size& LayoutSize = GetLayoutSize();
    double sourceRatio = sourceSize_.Width() / sourceSize_.Height();
    double layoutRatio = LayoutSize.Width() / LayoutSize.Height();

    if (sourceRatio < layoutRatio) {
        drawSize_ = Size(LayoutSize.Width(), LayoutSize.Width() / sourceRatio);
    } else {
        drawSize_ = Size(LayoutSize.Height() * sourceRatio, LayoutSize.Height());
    }
}

void RenderTexture::CalculateFitFill()
{
    drawSize_ = GetLayoutSize();
}

void RenderTexture::CalculateFitNone()
{
    drawSize_ = sourceSize_;
}

void RenderTexture::CalculateFitScaleDown()
{
    const Size& LayoutSize = GetLayoutSize();

    if (LayoutSize.Width() > sourceSize_.Width()) {
        CalculateFitNone();
    } else {
        CalculateFitContain();
    }
}

} // namespace OHOS::Ace
