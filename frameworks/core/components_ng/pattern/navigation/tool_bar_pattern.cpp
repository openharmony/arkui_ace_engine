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

#include "base/utils/utf_helper.h"
#include "base/i18n/localization.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"

namespace OHOS::Ace::NG {
namespace {
void SetBackgroundBlurStyle(RefPtr<FrameNode>& host, const BlurStyleOption& bgBlurStyle)
{
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (bgBlurStyle.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        pipeline->AddWindowFocusChangedCallback(host->GetId());
    } else {
        pipeline->RemoveWindowFocusChangedCallback(host->GetId());
    }
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        if (renderContext->GetBackgroundEffect().has_value()) {
            renderContext->UpdateBackgroundEffect(std::nullopt);
        }
        renderContext->UpdateBackBlurStyle(bgBlurStyle);
        if (renderContext->GetBackBlurRadius().has_value()) {
            renderContext->UpdateBackBlurRadius(Dimension());
        }
    }
}

void SetBackgroundEffect(RefPtr<FrameNode>& host, const EffectOption &effectOption)
{
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (effectOption.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        pipeline->AddWindowFocusChangedCallback(host->GetId());
    } else {
        pipeline->RemoveWindowFocusChangedCallback(host->GetId());
    }
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        if (renderContext->GetBackBlurRadius().has_value()) {
            renderContext->UpdateBackBlurRadius(Dimension());
        }
        if (renderContext->GetBackBlurStyle().has_value()) {
            renderContext->UpdateBackBlurStyle(std::nullopt);
        }
        renderContext->UpdateBackgroundEffect(effectOption);
    }
}
}
void NavToolbarPattern::SetToolbarOptions(NavigationToolbarOptions&& opt)
{
    bool needUpdateBgOptions = options_ != opt;
    if (options_.bgOptions.blurStyleOption->blurOption != opt.bgOptions.blurStyleOption->blurOption) {
        needUpdateBgOptions = true;
    }
    if (!needUpdateBgOptions) {
        return;
    }

    options_ = std::move(opt);
    UpdateBackgroundStyle();
}

void NavToolbarPattern::SetToolbarMoreButtonOptions(MoreButtonOptions&& opt)
{
    moreButtonOptions_ = std::move(opt);
}

void NavToolbarPattern::UpdateBackgroundStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (options_.bgOptions.color.has_value()) {
        renderContext->UpdateBackgroundColor(options_.bgOptions.color.value());
    } else {
        SetDefaultBackgroundColorIfNeeded(host);
    }
    if (options_.bgOptions.blurStyleOption.has_value()) {
        BlurStyleOption styleOption = options_.bgOptions.blurStyleOption.value();
        SetBackgroundBlurStyle(host, styleOption);
    } else {
        renderContext->ResetBackBlurStyle();
    }
    if (options_.bgOptions.effectOption.has_value()) {
        EffectOption effectOption = options_.bgOptions.effectOption.value();
        SetBackgroundEffect(host, effectOption);
    }
}

void NavToolbarPattern::OnModifyDone()
{
    auto hostNode = AceType::DynamicCast<NavToolbarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto containerNode = AceType::DynamicCast<FrameNode>(hostNode->GetToolbarContainerNode());
    CHECK_NULL_VOID(containerNode);
    auto gestureHub = containerNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    float scale = context->GetFontScale();
    if (LessNotEqual(scale, AgingAdapationDialogUtil::GetDialogBigFontSizeScale())) {
        return;
    }
    InitLongPressEvent(gestureHub);
    InitDragEvent(gestureHub);
    auto accessibilityProperty = containerNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
}

void NavToolbarPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto longPressTask = [weak = WeakClaim(this)](GestureEvent& info) {
        auto toolBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(toolBarPattern);
        toolBarPattern->HandleLongPressEvent(info);
    };
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(std::move(longPressTask));
    gestureHub->SetLongPressEvent(longPressEvent);

    auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
    CHECK_NULL_VOID(longPressRecognizer);
    auto longPressActionEnd = [weak = WeakClaim(this)](GestureEvent& info) {
        auto toolBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(toolBarPattern);
        toolBarPattern->HandleLongPressActionEnd();
    };
    longPressRecognizer->SetOnActionEnd(longPressActionEnd);
}

void NavToolbarPattern::InitDragEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto toolBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(toolBarPattern);
        auto hostNode = AceType::DynamicCast<NavToolbarNode>(toolBarPattern->GetHost());
        CHECK_NULL_VOID(hostNode);
        auto containerNode = AceType::DynamicCast<FrameNode>(hostNode->GetToolbarContainerNode());
        CHECK_NULL_VOID(containerNode);
        auto toolBarItemNode =
            containerNode->FindChildByPosition(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
        CHECK_NULL_VOID(toolBarItemNode);
        auto index = containerNode->GetChildIndex(toolBarItemNode);
        auto totalCount = containerNode->TotalChildCount();
        if (toolBarPattern->dialogNode_ && index >= 0 && index < totalCount) {
            auto pipeline = hostNode->GetContextWithCheck();
            CHECK_NULL_VOID(pipeline);
            auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
            CHECK_NULL_VOID(buttonTheme);
            auto buttonPattern = toolBarItemNode->GetPattern<ButtonPattern>();
            CHECK_NULL_VOID(buttonPattern);
            buttonPattern->SetClickedColor(buttonTheme->GetClickedColor());
            if (!toolBarPattern->moveIndex_.has_value()) {
                toolBarPattern->moveIndex_ = index;
            }

            if (toolBarPattern->moveIndex_ != index) {
                auto renderContext = toolBarItemNode->GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateBackgroundColor(buttonTheme->GetClickedColor());
                toolBarPattern->HandleLongPressActionEnd();
                toolBarPattern->moveIndex_ = index;
                auto barItemNode = AceType::DynamicCast<BarItemNode>(toolBarItemNode->GetFirstChild());
                CHECK_NULL_VOID(barItemNode);
                toolBarPattern->ShowDialogWithNode(barItemNode);
            }
        }
    };

    auto dragEvent = MakeRefPtr<DragEvent>(nullptr, std::move(actionUpdateTask), nullptr, nullptr);
    PanDirection panDirection = { .type = PanDirection::ALL };
    gestureHub->SetDragEvent(dragEvent, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void NavToolbarPattern::HandleLongPressEvent(const GestureEvent& info)
{
    auto hostNode = AceType::DynamicCast<NavToolbarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto containerNode = AceType::DynamicCast<FrameNode>(hostNode->GetToolbarContainerNode());
    CHECK_NULL_VOID(containerNode);
    auto toolBarItem =
        containerNode->FindChildByPosition(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    CHECK_NULL_VOID(toolBarItem);
    RefPtr<BarItemNode> barItemNode = AceType::DynamicCast<BarItemNode>(toolBarItem->GetFirstChild());
    CHECK_NULL_VOID(barItemNode);
    ShowDialogWithNode(barItemNode);
}

void NavToolbarPattern::HandleLongPressActionEnd()
{
    CHECK_NULL_VOID(dialogNode_);
    auto host = AceType::DynamicCast<NavToolbarNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto containerNode = AceType::DynamicCast<FrameNode>(host->GetToolbarContainerNode());
    CHECK_NULL_VOID(containerNode);
    if (moveIndex_.has_value()) {
        auto toolBarItemNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildAtIndex(moveIndex_.value()));
        CHECK_NULL_VOID(toolBarItemNode);
        auto renderContext = toolBarItemNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        renderContext->ResetBlendBgColor();
        moveIndex_.reset();
    }
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode_);
    dialogNode_ = nullptr;
}

void NavToolbarPattern::ShowDialogWithNode(const RefPtr<BarItemNode>& barItemNode)
{
    HandleLongPressActionEnd();
    CHECK_NULL_VOID(barItemNode);
    auto accessibilityProperty = barItemNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::string message = accessibilityProperty->GetAccessibilityText();
    if (barItemNode->IsMoreItemNode()) {
        auto theme = NavigationGetTheme();
        CHECK_NULL_VOID(theme);
        message = theme->GetMoreMessage();
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            auto symbolNode = AceType::DynamicCast<FrameNode>(barItemNode->GetFirstChild());
            CHECK_NULL_VOID(symbolNode);
            dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, symbolNode);
            return;
        }
        auto info = ImageSourceInfo("");
        info.SetResourceId(theme->GetMoreResourceId());
        dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, info, host->GetThemeScopeId());
        return;
    }
    RefPtr<FrameNode> textNode = AceType::DynamicCast<FrameNode>(barItemNode->GetTextNode());
    RefPtr<FrameNode> imageNode = AceType::DynamicCast<FrameNode>(barItemNode->GetIconNode());
    if (textNode != nullptr) {
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto textValue = textLayoutProperty->GetContent();
        if (!textValue.value().empty()) {
            message = UtfUtils::Str16ToStr8(textValue.value());
        }
    }
    if (imageNode != nullptr) {
        if (imageNode->GetTag() == V2::SYMBOL_ETS_TAG) {
            dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, imageNode);
            return;
        }
        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo());
        dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, imageSourceInfo, host->GetThemeScopeId());
        return;
    }
    auto imageSourceInfo = ImageSourceInfo("");
    dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, imageSourceInfo, host->GetThemeScopeId());
}

void NavToolbarPattern::SetDefaultBackgroundColorIfNeeded(RefPtr<FrameNode>& host)
{
    if (options_.bgOptions.color.has_value()) {
        return;
    }

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto theme = NavigationGetTheme(host->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    renderContext->UpdateBackgroundColor(theme->GetToolBarBgColor());
}

void NavToolbarPattern::OnColorConfigurationUpdate()
{
    UpdateBackgroundStyle();
}

bool NavToolbarPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    UpdateBackgroundStyle();
    return false;
}

} // namespace OHOS::Ace::NG
