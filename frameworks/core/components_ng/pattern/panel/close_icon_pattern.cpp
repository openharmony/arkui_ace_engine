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

#include "core/components_ng/pattern/panel/close_icon_pattern.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components/close_icon/close_icon_theme.h"

namespace OHOS::Ace::NG {
void CloseIconPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    if (isFirstLayout_) {
        InitCloseIcon();
        isFirstLayout_ = false;
    }
    InitButtonEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void CloseIconPattern::InitCloseIcon()
{
    auto closeIconLayoutProperty = GetCloseIconLayoutProperty();
    CHECK_NULL_VOID(closeIconLayoutProperty);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto closeIconTheme = pipeline->GetTheme<CloseIconTheme>();
    CHECK_NULL_VOID(closeIconTheme);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(closeIconLayoutProperty->GetCloseIconWidthValue(closeIconTheme->GetCloseIconWidth())),
            CalcLength(closeIconLayoutProperty->GetCloseIconHeightValue(closeIconTheme->GetCloseIconHeight()))));
    buttonNode->MarkModifyDone();
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSkipColorConfigurationUpdate();
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(closeIconLayoutProperty->GetCloseIconWidthValue(closeIconTheme->GetCloseIconWidth())),
            CalcLength(closeIconLayoutProperty->GetCloseIconHeightValue(closeIconTheme->GetCloseIconHeight()))));
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_BOTTOMSHEET_CLOSE_SVG);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageNode->MarkModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty radius;
    radius.SetRadius(closeIconLayoutProperty->GetCloseIconRadiusValue(closeIconTheme->GetCloseIconRadius()));
    renderContext->UpdateBorderRadius(radius);
    host->AddChild(buttonNode);
    buttonNode->AddChild(imageNode);
}

void CloseIconPattern::InitButtonEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);
    auto gestureHub = buttonNode->GetOrCreateGestureEventHub();
    auto clickButtonCallback = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ButtonClickEvent();
    };
    if (buttonClickListenr_) {
        gestureHub->RemoveClickEvent(buttonClickListenr_);
    }
    buttonClickListenr_ = MakeRefPtr<ClickEvent>(std::move(clickButtonCallback));
    gestureHub->AddClickEvent(buttonClickListenr_);
}

void CloseIconPattern::ButtonClickEvent()
{
    if (!clickButtonCallback_) {
        return;
    }
    clickButtonCallback_();
}
} // namespace OHOS::Ace::NG
