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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"

#include "base/utils/utils.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SwiperArrowPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    if (isFirstCreate_) {
        InitNavigationArrow();
        auto swiperNode = GetSwiperNode();
        CHECK_NULL_VOID(swiperNode);
        auto swiperEventHub = swiperNode->GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(swiperEventHub);
        InitSwiperChangeEvent(swiperEventHub);
        index_ = GetSwiperArrowLayoutProperty()->GetIndex().value_or(0);
        isFirstCreate_ = false;
        InitButtonEvent();
    } else {
        UpdateArrowContent();
    }
    UpdateButtonNode(index_);
}

void SwiperArrowPattern::InitSwiperChangeEvent(const RefPtr<SwiperEventHub>& swiperEventHub)
{
    ChangeEvent changeEvent = [weak = WeakClaim(this)](int32_t index) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->UpdateButtonNode(index);
    };
    if (swiperChangeEvent_) {
        (*swiperChangeEvent_).swap(changeEvent);
    } else {
        swiperChangeEvent_ = std::make_shared<ChangeEvent>(std::move(changeEvent));
        swiperEventHub->AddOnChangeEvent(swiperChangeEvent_);
    }
}

void SwiperArrowPattern::UpdateButtonNode(int32_t index)
{
    index_ = index;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);
    auto imageNode = DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    CHECK_NULL_VOID(imageNode);
    SetButtonVisible(isHover_);
    imageNode->MarkModifyDone();
}

void SwiperArrowPattern::InitButtonEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);

    auto arrowGestureHub = buttonNode->GetOrCreateGestureEventHub();

    auto touchCallback = [weak = WeakClaim(this), buttonNode](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->ButtonTouchEvent(buttonNode, info.GetTouches().front().GetTouchType());
    };
    buttonTouchListenr_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    arrowGestureHub->AddTouchEvent(buttonTouchListenr_);

    auto hoverCallback = [weak = WeakClaim(this), buttonNode](bool isHovered) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->ButtonOnHover(buttonNode, isHovered);
    };
    buttonOnHoverListenr_ = MakeRefPtr<InputEvent>(std::move(hoverCallback));
    auto buttonInputHub = buttonNode->GetOrCreateInputEventHub();
    buttonInputHub->AddOnHoverEvent(buttonOnHoverListenr_);

    auto clickCallback = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->ButtonClickEvent();
    };
    if (buttonClickListenr_) {
        arrowGestureHub->RemoveClickEvent(buttonClickListenr_);
    }
    buttonClickListenr_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    arrowGestureHub->AddClickEvent(buttonClickListenr_);
}

void SwiperArrowPattern::ButtonClickEvent()
{
    auto swiperArrowLayoutProperty = GetSwiperArrowLayoutProperty();
    CHECK_NULL_VOID(swiperArrowLayoutProperty);
    if (!hoverOnClickFlag_ && swiperArrowLayoutProperty->GetHoverShowValue(false)) {
        return;
    }
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperController = swiperPattern->GetSwiperController();
    CHECK_NULL_VOID(swiperController);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG) {
        swiperController->ShowPrevious();
    }
    if (host->GetTag() == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        swiperController->ShowNext();
    }
}

void SwiperArrowPattern::InitNavigationArrow()
{
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto swiperArrowLayoutProperty = GetSwiperArrowLayoutProperty();
    CHECK_NULL_VOID(swiperArrowLayoutProperty);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty radius;
    radius.SetRadius(swiperArrowLayoutProperty->GetBackgroundSizeValue());
    renderContext->UpdateBorderRadius(radius);
    host->AddChild(buttonNode);
    buttonNode->AddChild(imageNode);
    UpdateArrowContent();
}

int32_t SwiperArrowPattern::TotalCount() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, 0);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, 0);
    return swiperPattern->TotalCount() - 1;
}

void SwiperArrowPattern::ButtonTouchEvent(RefPtr<FrameNode> buttonNode, TouchType touchType)
{
    auto swiperArrowLayoutProperty = GetSwiperArrowLayoutProperty();
    CHECK_NULL_VOID(swiperArrowLayoutProperty);
    if (!hoverOnClickFlag_ && swiperArrowLayoutProperty->GetHoverShowValue(false)) {
        return;
    }
    const auto& renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID_NOLOG(renderContext);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID_NOLOG(swiperIndicatorTheme);
    Color backgroundColor;
    if (touchType == TouchType::DOWN) {
        isTouch_ = true;
        if (isHover_) {
            backgroundColor = swiperIndicatorTheme->GetHoverArrowBackgroundColor().BlendColor(
                swiperIndicatorTheme->GetClickArrowBackgroundColor());
        } else {
            backgroundColor = swiperIndicatorTheme->GetClickArrowBackgroundColor();
        }
        renderContext->ResetBlendBgColor();
        renderContext->BlendBgColor(backgroundColor);
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        isTouch_ = false;
        if (isHover_) {
            backgroundColor = swiperIndicatorTheme->GetHoverArrowBackgroundColor();
            renderContext->ResetBlendBgColor();
            renderContext->BlendBgColor(backgroundColor);
        } else {
            renderContext->ResetBlendBgColor();
        }
    }
}

void SwiperArrowPattern::ButtonOnHover(RefPtr<FrameNode> buttonNode, bool isHovered)
{
    hoverOnClickFlag_ = isHovered;
    const auto& renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID_NOLOG(renderContext);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID_NOLOG(swiperIndicatorTheme);
    Color backgroundColor;

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    if (swiperLayoutProperty->GetShowIndicatorValue(true)) {
        isHover_ = isHovered;
    }
    if (swiperLayoutProperty->GetHoverShowValue(false)) {
        swiperPattern->ArrowHover(isHover_);
    }
    if (isHovered) {
        if (isTouch_) {
            backgroundColor = swiperIndicatorTheme->GetHoverArrowBackgroundColor().BlendColor(
                swiperIndicatorTheme->GetClickArrowBackgroundColor());
        } else {
            backgroundColor = swiperIndicatorTheme->GetHoverArrowBackgroundColor();
        }
        renderContext->ResetBlendBgColor();
        renderContext->BlendBgColor(backgroundColor);
    } else {
        if (isTouch_) {
            backgroundColor = swiperIndicatorTheme->GetClickArrowBackgroundColor();
            renderContext->ResetBlendBgColor();
            renderContext->BlendBgColor(backgroundColor);
        } else {
            renderContext->ResetBlendBgColor();
        }
    }
}

void SwiperArrowPattern::SetButtonVisible(bool visible)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);
    const auto& renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto swiperArrowLayoutProperty = GetSwiperArrowLayoutProperty();
    CHECK_NULL_VOID(swiperArrowLayoutProperty);
    auto isHoverShow = swiperArrowLayoutProperty->GetHoverShowValue(false);
    auto hostFocusHub = host->GetFocusHub();
    CHECK_NULL_VOID(hostFocusHub);
    if ((host->GetTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG && index_ == 0) ||
        (host->GetTag() == V2::SWIPER_RIGHT_ARROW_ETS_TAG && index_ == TotalCount())) {
        if (!swiperArrowLayoutProperty->GetLoopValue(true)) {
            renderContext->SetVisible(false);
            hostFocusHub->SetParentFocusable(false);
            hostFocusHub->LostSelfFocus();
            return;
        }
    }
    if (isHoverShow) {
        hostFocusHub->SetParentFocusable(false);
        hostFocusHub->LostSelfFocus();
    } else {
        hostFocusHub->SetParentFocusable(true);
        visible = true;
    }
    renderContext->SetVisible(visible);
}

void SwiperArrowPattern::UpdateArrowContent()
{
    auto swiperArrowLayoutProperty = GetSwiperArrowLayoutProperty();
    CHECK_NULL_VOID(swiperArrowLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);
    buttonNode->GetRenderContext()->UpdateBackgroundColor(
        swiperArrowLayoutProperty->GetIsShowBackgroundValue(false)
            ? swiperArrowLayoutProperty->GetBackgroundColorValue(backgroundColor_)
            : Color::TRANSPARENT);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(swiperArrowLayoutProperty->GetBackgroundSizeValue()),
            CalcLength(swiperArrowLayoutProperty->GetBackgroundSizeValue())));
    backgroundColor_ = buttonNode->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT);
    RefPtr<FrameNode> imageNode = DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    CHECK_NULL_VOID(imageNode);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(swiperArrowLayoutProperty->GetArrowSizeValue()),
        CalcLength(swiperArrowLayoutProperty->GetArrowSizeValue())));
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    ImageSourceInfo imageSourceInfo;
    auto swiperLayoutProperty = GetSwiperArrowLayoutProperty();
    CHECK_NULL_VOID(swiperLayoutProperty);
    if (V2::SWIPER_LEFT_ARROW_ETS_TAG == GetHost()->GetTag()) {
        if (swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
            imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG);
        } else {
            imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG);
        }
    } else if (V2::SWIPER_RIGHT_ARROW_ETS_TAG == GetHost()->GetTag()) {
        if (swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
            imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG);
        } else {
            imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG);
        }
    }
    imageSourceInfo.SetFillColor(swiperArrowLayoutProperty->GetArrowColorValue());
    if (!swiperArrowLayoutProperty->GetEnabledValue(true)) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID_NOLOG(pipelineContext);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_VOID_NOLOG(swiperIndicatorTheme);
        buttonNode->GetRenderContext()->UpdateBackgroundColor(
            backgroundColor_.BlendOpacity(swiperIndicatorTheme->GetArrowDisabledAlpha()));
        imageSourceInfo.SetFillColor(swiperArrowLayoutProperty->GetArrowColorValue().BlendOpacity(
            swiperIndicatorTheme->GetArrowDisabledAlpha()));
    }
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageNode->MarkModifyDone();
}

void SwiperArrowPattern::SetArrowHover(bool isHover)
{
    isHover_ = isHover;
}
} // namespace OHOS::Ace::NG
