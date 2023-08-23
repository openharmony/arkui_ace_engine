/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/security_component/security_component_layout_algorithm.h"

#include "base/log/ace_scoring_log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {
constexpr float HALF = 2.0f;
}

namespace OHOS::Ace::NG {
RefPtr<LayoutWrapper> SecurityComponentLayoutAlgorithm::GetChildWrapper(LayoutWrapper* layoutWrapper,
    const std::string& tag)
{
    int32_t count = layoutWrapper->GetTotalChildCount();
    for (int32_t i = 0; i < count; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        if (childWrapper == nullptr) {
            continue;
        }
        if (childWrapper->GetHostTag() == tag) {
            return childWrapper;
        }
    }
    return nullptr;
}

void SecurityComponentLayoutAlgorithm::UpdateChildPosition(LayoutWrapper* layoutWrapper, const std::string& tag,
    OffsetT<Dimension>& offset)
{
    auto childWrapper = GetChildWrapper(layoutWrapper, tag);
    CHECK_NULL_VOID(childWrapper);
    auto childNode = childWrapper->GetHostNode();
    CHECK_NULL_VOID(childNode);
    auto childRenderContext = childNode->GetRenderContext();
    CHECK_NULL_VOID(childRenderContext);
    childRenderContext->UpdatePosition(offset);
}

void SecurityComponentLayoutAlgorithm::MeasureIcon(LayoutWrapper* layoutWrapper,
    RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty)
{
    auto iconWrapper = GetChildWrapper(layoutWrapper, V2::IMAGE_ETS_TAG);
    CHECK_NULL_VOID(iconWrapper);

    auto iconConstraint = securityComponentProperty->GetContentLayoutConstraint();
    iconWrapper->Measure(iconConstraint);
    iconSizeF_ = iconWrapper->GetGeometryNode()->GetFrameSize();
}

void SecurityComponentLayoutAlgorithm::MeasureText(LayoutWrapper* layoutWrapper,
    RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty)
{
    auto textWrapper = GetChildWrapper(layoutWrapper, V2::TEXT_ETS_TAG);
    CHECK_NULL_VOID(textWrapper);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto textConstraint = securityComponentProperty->GetContentLayoutConstraint();

    SizeT<float> maxSize { Infinity<float>(), Infinity<float>() };
    textConstraint->maxSize = maxSize;
    textWrapper->Measure(textConstraint);
    textSizeF_ = textWrapper->GetGeometryNode()->GetFrameSize();
}

void SecurityComponentLayoutAlgorithm::MeasureButton(LayoutWrapper* layoutWrapper,
    RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty)
{
    auto buttonWrapper = GetChildWrapper(layoutWrapper, V2::BUTTON_ETS_TAG);
    CHECK_NULL_VOID(buttonWrapper);
    auto buttonLayoutProperty = DynamicCast<ButtonLayoutProperty>(buttonWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(buttonLayoutProperty);
    if (buttonType_ == static_cast<int32_t>(ButtonType::CIRCLE)) {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(NG::CalcLength(std::max(componentWidth_, componentHeight_)),
            NG::CalcLength(std::max(componentWidth_, componentHeight_))));
    } else {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(componentWidth_),
            NG::CalcLength(componentHeight_)));
    }

    auto buttonConstraint = layoutWrapper->GetLayoutProperty()->GetContentLayoutConstraint();
    buttonWrapper->Measure(buttonConstraint);
    buttonSizeF_ = buttonWrapper->GetGeometryNode()->GetFrameSize();
}

void SecurityComponentLayoutAlgorithm::FillPaddingParams(
    RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty, SecurityComponentLayoutPaddingParams& res)
{
    res.top = securityComponentProperty->GetBackgroundTopPadding().value().ConvertToPx();
    res.right = securityComponentProperty->GetBackgroundRightPadding().value().ConvertToPx();
    res.bottom = securityComponentProperty->GetBackgroundBottomPadding().value().ConvertToPx();
    res.left = securityComponentProperty->GetBackgroundLeftPadding().value().ConvertToPx();
    res.textIconSpace = securityComponentProperty->GetTextIconSpace().value().ConvertToPx();
}

void SecurityComponentLayoutAlgorithm::UpdateVertical(OffsetT<Dimension>& offsetIcon,
    OffsetT<Dimension>& offsetText, const SecurityComponentLayoutPaddingParams& params)
{
    componentHeight_ = params.top + iconSizeF_.Height() + params.textIconSpace +
        textSizeF_.Height() + params.bottom;
    componentWidth_ = params.left +
        ((iconSizeF_.Width() > textSizeF_.Width()) ? iconSizeF_.Width() : textSizeF_.Width()) + params.right;
    offsetText = offsetIcon + OffsetT<Dimension>(Dimension(0.0F),
        Dimension(iconSizeF_.Height() + params.textIconSpace));
    if (iconSizeF_.Width() > textSizeF_.Width()) {
        offsetText += OffsetT<Dimension>(Dimension((iconSizeF_.Width() - textSizeF_.Width()) / HALF), Dimension(0.0F));
    } else {
        offsetIcon += OffsetT<Dimension>(Dimension((textSizeF_.Width() - iconSizeF_.Width()) / HALF), Dimension(0.0F));
    }
}

void SecurityComponentLayoutAlgorithm::UpdateHorizontal(OffsetT<Dimension>& offsetIcon,
    OffsetT<Dimension>& offsetText, const SecurityComponentLayoutPaddingParams& params)
{
    componentHeight_ =
        params.top + ((iconSizeF_.Height() > textSizeF_.Height()) ? iconSizeF_.Height() : textSizeF_.Height()) +
        params.bottom;
    componentWidth_ = params.left + iconSizeF_.Width() + params.textIconSpace + textSizeF_.Width() + params.right;
    offsetText = offsetIcon +
        OffsetT<Dimension>(Dimension(iconSizeF_.Width() + params.textIconSpace), Dimension(0.0F));
    if (iconSizeF_.Height() > textSizeF_.Height()) {
        offsetText +=
            OffsetT<Dimension>(Dimension(0.0F), Dimension((iconSizeF_.Height() - textSizeF_.Height()) / HALF));
    } else {
        offsetIcon +=
            OffsetT<Dimension>(Dimension(0.0F), Dimension((textSizeF_.Height() - iconSizeF_.Height()) / HALF));
    }
}

void SecurityComponentLayoutAlgorithm::UpdateCircleBackground(OffsetT<Dimension>& offsetIcon,
    OffsetT<Dimension>& offsetText)
{
    if (componentHeight_ > componentWidth_) {
        OffsetT<Dimension> rightMove(Dimension((componentHeight_ - componentWidth_) / HALF), Dimension(0.0F));
        offsetIcon += rightMove;
        offsetText += rightMove;
        componentWidth_ = componentHeight_;
    } else {
        OffsetT<Dimension> downMove(Dimension(0.0F), Dimension((componentWidth_ - componentHeight_) / HALF));
        offsetIcon += downMove;
        offsetText += downMove;
        componentHeight_ = componentWidth_;
    }
}

void SecurityComponentLayoutAlgorithm::UpdateFrameMeasure(LayoutWrapper* layoutWrapper,
    RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty)
{
    SecurityComponentLayoutPaddingParams params;
    FillPaddingParams(securityComponentProperty, params);

    OffsetT<Dimension> offsetIcon = OffsetT<Dimension>(Dimension(params.left), Dimension(params.top));
    OffsetT<Dimension> offsetText = OffsetT<Dimension>(Dimension(params.left), Dimension(params.top));
    if (securityComponentProperty->GetTextIconLayoutDirection().value() ==
        SecurityComponentLayoutDirection::VERTICAL) {
        UpdateVertical(offsetIcon, offsetText, params);
    } else {
        UpdateHorizontal(offsetIcon, offsetText, params);
    }

    if (buttonType_ == static_cast<int32_t>(ButtonType::CIRCLE)) {
        UpdateCircleBackground(offsetIcon, offsetText);
    }
    UpdateChildPosition(layoutWrapper, V2::IMAGE_ETS_TAG, offsetIcon);
    UpdateChildPosition(layoutWrapper, V2::TEXT_ETS_TAG, offsetText);
}

void SecurityComponentLayoutAlgorithm::InitLayoutParams(RefPtr<SecurityComponentLayoutProperty>& property)
{
    componentWidth_ = 0.0F;
    componentHeight_ = 0.0F;
    iconSizeF_.Reset();
    textSizeF_.Reset();
    buttonSizeF_.Reset();
    buttonType_ = property->GetBackgroundType().value();
}

void SecurityComponentLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto securityComponentLayoutProperty =
        DynamicCast<SecurityComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(securityComponentLayoutProperty);

    InitLayoutParams(securityComponentLayoutProperty);
    if (securityComponentLayoutProperty->GetIconStyle().value() !=
        static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL)) {
        MeasureIcon(layoutWrapper, securityComponentLayoutProperty);
    }

    if (securityComponentLayoutProperty->GetSecurityComponentDescription().value() !=
        static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL)) {
        MeasureText(layoutWrapper, securityComponentLayoutProperty);
    }

    UpdateFrameMeasure(layoutWrapper, securityComponentLayoutProperty);
    MeasureButton(layoutWrapper, securityComponentLayoutProperty);
    componentWidth_ = buttonSizeF_.Width();
    componentHeight_ = buttonSizeF_.Height();

    LOGD("security components size %{public}f %{public}f icon %{public}f %{public}f text %{public}f %{public}f",
        componentWidth_, componentHeight_, iconSizeF_.Width(),
        iconSizeF_.Height(), textSizeF_.Width(), textSizeF_.Height());
    layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(componentWidth_, componentHeight_));
}
} // namespace OHOS::Ace::NG
