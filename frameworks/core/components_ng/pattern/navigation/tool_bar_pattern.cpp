/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"

#include "base/i18n/localization.h"
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
void NavToolbarPattern::SetToolbarOptions(NavigationToolbarOptions&& opt)
{
    if (opt == options_) {
        return;
    }

    options_ = std::move(opt);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateBackgroundStyle(host);
}

void NavToolbarPattern::UpdateBackgroundStyle(RefPtr<FrameNode>& host)
{
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (options_.bgOptions.color.has_value()) {
        renderContext->UpdateBackgroundColor(options_.bgOptions.color.value());
    } else {
        SetDefaultBackgroundColorIfNeeded(host);
    }
    if (options_.bgOptions.blurStyle.has_value()) {
        BlurStyleOption blur;
        blur.blurStyle = options_.bgOptions.blurStyle.value();
        renderContext->UpdateBackBlurStyle(blur);
    } else {
        renderContext->ResetBackBlurStyle();
    }
}

void NavToolbarPattern::OnModifyDone()
{
    auto hostNode = AceType::DynamicCast<NavToolbarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto containerNode = hostNode->GetToolbarContainerNode();
    CHECK_NULL_VOID(containerNode);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    float scale = context->GetFontScale();
    if (LessNotEqual(scale, AgingAdapationDialogUtil::GetDialogBigFontSizeScale())) {
        return;
    }
    for (auto toolBarItemNode : containerNode->GetChildren()) {
        auto toolBarItem = AceType::DynamicCast<FrameNode>(toolBarItemNode);
        CHECK_NULL_VOID(toolBarItem);
        auto gestureHub = toolBarItem->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        RefPtr<BarItemNode> barItemNode = AceType::DynamicCast<BarItemNode>(toolBarItem->GetChildren().front());
        if (!barItemNode) {
            TAG_LOGD(AceLogTag::ACE_NAVIGATION, "current bar item node is empty, continue");
            continue;
        }
        InitLongPressEvent(gestureHub, barItemNode);
    }
}

void NavToolbarPattern::InitLongPressEvent(
    const RefPtr<GestureEventHub>& gestureHub, const RefPtr<BarItemNode>& barItemNode)
{
    auto longPressTask = [weak = WeakClaim(this), weakBarItemNode = WeakPtr<BarItemNode>(barItemNode)](
                             GestureEvent& info) {
        auto toolBar = weak.Upgrade();
        CHECK_NULL_VOID(toolBar);
        auto barItemNode = weakBarItemNode.Upgrade();
        toolBar->HandleLongPressEvent(barItemNode);
    };
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(std::move(longPressTask));
    gestureHub->SetLongPressEvent(longPressEvent);

    auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
    CHECK_NULL_VOID(longPressRecognizer);
    auto longPressActionEnd = [weak = WeakClaim(this)](GestureEvent& info) {
        auto toolBar = weak.Upgrade();
        CHECK_NULL_VOID(toolBar);
        toolBar->HandleLongPressActionEnd();
    };
    longPressRecognizer->SetOnActionEnd(longPressActionEnd);
}

void NavToolbarPattern::HandleLongPressEvent(const RefPtr<BarItemNode>& barItemNode)
{
    HandleLongPressActionEnd();
    CHECK_NULL_VOID(barItemNode);
    std::string message;
    auto accessibilityProperty = barItemNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    message = accessibilityProperty->GetAccessibilityText();
    if (barItemNode->IsMoreItemNode()) {
        auto theme = NavigationGetTheme();
        CHECK_NULL_VOID(theme);
        message = Localization::GetInstance()->GetEntryLetters("common.more");
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            dialogNode_ =
                AgingAdapationDialogUtil::ShowLongPressDialog(message, SymbolSourceInfo(theme->GetMoreSymbolId()));
            return;
        }
        auto info = ImageSourceInfo("");
        info.SetResourceId(theme->GetMoreResourceId());
        dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, info);
        return;
    }
    RefPtr<FrameNode> textNode = AceType::DynamicCast<FrameNode>(barItemNode->GetTextNode());
    RefPtr<FrameNode> imageNode = AceType::DynamicCast<FrameNode>(barItemNode->GetIconNode());
    if (textNode != nullptr) {
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto textValue = textLayoutProperty->GetContent();
        if (!textValue.value().empty()) {
            message = textValue.value();
        }
    }
    if (imageNode != nullptr) {
        if (imageNode->GetTag() == V2::SYMBOL_ETS_TAG) {
            auto symbolProperty = imageNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(symbolProperty);
            dialogNode_ =
                AgingAdapationDialogUtil::ShowLongPressDialog(message, symbolProperty->GetSymbolSourceInfoValue());
            return;
        }
        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo());
        dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, imageSourceInfo);
        return;
    }
    auto imageSourceInfo = ImageSourceInfo("");
    dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, imageSourceInfo);
}

void NavToolbarPattern::HandleLongPressActionEnd()
{
    CHECK_NULL_VOID(dialogNode_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode_);
    dialogNode_ = nullptr;
}

void NavToolbarPattern::SetDefaultBackgroundColorIfNeeded(RefPtr<FrameNode>& host)
{
    if (options_.bgOptions.color.has_value()) {
        return;
    }

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    renderContext->UpdateBackgroundColor(theme->GetToolBarBgColor());
}

void NavToolbarPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateBackgroundStyle(host);
}
} // namespace OHOS::Ace::NG
