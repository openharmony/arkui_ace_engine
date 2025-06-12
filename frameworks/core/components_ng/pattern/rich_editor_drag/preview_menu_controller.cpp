/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor_drag/preview_menu_controller.h"

#include <cstddef>
#include <optional>

#include "ui/base/geometry/dimension.h"
#include "ui/base/referenced.h"
#include "ui/base/utils/utils.h"
#include "ui/properties/color.h"
#include "ui/properties/dirty_flag.h"
#include "ui/properties/flex.h"

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/expanded_menu_plugin_loader.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/menu_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension PREVIEW_MAX_WIDTH = 360.0_vp;
constexpr Dimension MENU_WIDTH = 224.0_vp;
constexpr Dimension AVATAR_SIZE = 40.0_vp;
constexpr Dimension PADDING_SIZE = 12.0_vp;
constexpr Dimension MARGIN_SIZE = 16.0_vp;
constexpr Dimension PREVIEW_MIN_HEIGHT = 64.0_vp;
constexpr Dimension FAILED_TEXT_LINE_SPACING = 8.0_vp;
constexpr float MAX_HEIGHT_PROPORTIONS = 0.65;
} // namespace
PreviewMenuController::PreviewMenuController(const WeakPtr<TextPattern>& pattern)
{
    pattern_ = pattern;
    menuParam_.type = MenuType::CONTEXT_MENU;
    menuParam_.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam_.previewMode = MenuPreviewMode::CUSTOM;

    menuParam_.isShowHoverImage = true;
    menuParam_.hoverImageAnimationOptions = { 1.0f, 1.0f };
    menuParam_.previewAnimationOptions = { 1.0f, 1.0f };

    auto textPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(textPattern);
    auto textNode = textPattern->GetHost();
    CHECK_NULL_VOID(textNode);
    auto context = textNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto margin = theme->GetMenuLargeMargin();

    MarginProperty marginproperty;
    marginproperty.start = CalcLength(margin);
    marginproperty.end = CalcLength(margin);
    menuParam_.layoutRegionMargin = marginproperty;
    menuParam_.onDisappear = [weak = WeakClaim(this), weakPattern = pattern,
                                 mainId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(mainId);
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->ClosePreviewMenu();
        auto textPattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(textPattern);
        textPattern->ResetAISelected(AIResetSelectionReason::CLOSE_CONTEXT_MENU);
        if (SystemProperties::GetTextTraceEnabled()) {
            auto host = textPattern->GetHost();
            CHECK_NULL_VOID(host);
            TAG_LOGI(AceLogTag::ACE_TEXT, "PreviewMenuController menu onDisappear[id:%{public}d]", host->GetId());
        }
    };
}

void PreviewMenuController::CreateAIEntityMenu()
{
    auto textPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(textPattern);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto onMenuDisappear = [weakPattern = pattern_, mainId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(mainId);
        if (SystemProperties::GetTextTraceEnabled()) {
            auto textPattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(textPattern);
            auto host = textPattern->GetHost();
            CHECK_NULL_VOID(host);
            TAG_LOGI(AceLogTag::ACE_TEXT, "AIEntityMenu on click[id:%{public}d]", host->GetId());
        }
    };
    auto menuNode = textPattern->CreateAIEntityMenu(onMenuDisappear);
    if (!menuNode) {
        menuNode = FrameNode::GetOrCreateFrameNode(
            V2::FLEX_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(); });
        auto flexLayoutProperty = menuNode->GetLayoutProperty<FlexLayoutProperty>();
        CHECK_NULL_VOID(flexLayoutProperty);
        flexLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
        flexLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
        flexLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    }
    auto layoutProperty = menuNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    std::optional<CalcLength> width = CalcLength(MENU_WIDTH);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, std::nullopt));
    stack->Push(menuNode);
}

std::function<void()> PreviewMenuController::GetDisappearCallback()
{
    return [weak = WeakClaim(this), pattern = pattern_, mainId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(mainId);
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        auto textPattern = pattern.Upgrade();
        CHECK_NULL_VOID(textPattern);
        if (SystemProperties::GetTextTraceEnabled()) {
            auto host = textPattern->GetHost();
            CHECK_NULL_VOID(host);
            TAG_LOGI(AceLogTag::ACE_TEXT, "CreateAIEntityMenu onMenuDisappear id:%{public}d", host->GetId());
        }
        auto targetNode = textPattern->MoveDragNode();
        CHECK_NULL_VOID(targetNode);
        controller->BindContextMenu(targetNode, false);
    };
}

std::function<void()> PreviewMenuController::GetLinkingCallback(const std::string& appName)
{
    return [appName, mainId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(mainId);
        auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(context);
        auto fontManager = context->GetFontManager();
        CHECK_NULL_VOID(fontManager);
        fontManager->StartAbilityOnInstallAppInStore(appName);
        if (SystemProperties::GetTextTraceEnabled()) {
            TAG_LOGI(AceLogTag::ACE_TEXT, "preview failed onLinkingCallback");
        }
    };
}

void PreviewMenuController::CreatePreviewMenu(
    TextDataDetectType type, const std::string& content, std::function<void()> disappearCallback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto childFrameNode = FrameNode::GetFrameNode(V2::FLEX_ETS_TAG, nodeId);
    if (!childFrameNode) {
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        stack->Push(frameNode);
        auto flexLayoutProperty = frameNode->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(flexLayoutProperty);
        flexLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
        auto flexRenderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(flexRenderContext);
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        auto bgColor = theme->GetBackgroundColor();
        flexRenderContext->UpdateBackgroundColor(bgColor);
        auto node = CreateErrorNode(type, content, std::move(disappearCallback));
        if (node) {
            node->MountToParent(frameNode);
        }
        return;
    }
    stack->Push(childFrameNode);
}

RefPtr<FrameNode> PreviewMenuController::CreateErrorNode(
    TextDataDetectType type, const std::string& content, std::function<void()>&& disappearCallback)
{
    RefPtr<FrameNode> node;
    switch (type) {
        case TextDataDetectType::PHONE_NUMBER:
        case TextDataDetectType::EMAIL:
            node = CreateContactNode(content, std::move(disappearCallback));
            break;
        case TextDataDetectType::DATE_TIME:
        case TextDataDetectType::ADDRESS:
        case TextDataDetectType::URL:
            node = CreateLinkingNode(type, std::move(disappearCallback));
            break;
        default:
            break;
    }
    return node;
}

RefPtr<FrameNode> PreviewMenuController::CreateContactNode(
    const std::string& content, std::function<void()>&& disappearCallback)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::FLEX_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<FlexLayoutPattern>(false); });
    auto avatarNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto flexLayoutProperty = frameNode->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_RETURN(flexLayoutProperty, nullptr);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto padding = CalcLength(PADDING_SIZE);
    flexLayoutProperty->UpdatePadding({ padding, padding, std::nullopt, std::nullopt });
    flexLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    flexLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    auto windowRect = context->GetDisplayWindowRectInfo();
    std::optional<CalcLength> minHeight = CalcLength(PREVIEW_MIN_HEIGHT);
    auto maxHeightValue = windowRect.Height() * MAX_HEIGHT_PROPORTIONS;
    std::optional<CalcLength> maxHeight = CalcLength(Dimension(maxHeightValue));
    std::optional<CalcLength> maxWidth = CalcLength(PREVIEW_MAX_WIDTH);
    flexLayoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, minHeight));
    flexLayoutProperty->UpdateCalcMaxSize(CalcSize(maxWidth, maxHeight));
    std::optional<CalcLength> height = CalcLength(PREVIEW_MIN_HEIGHT);
    flexLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));

    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventHub, nullptr);
    eventHub->SetUserOnClick([disappearCallback, mainId = Container::CurrentIdSafelyWithCheck()](GestureEvent& info) {
        ContainerScope scope(mainId);
        if (disappearCallback) {
            disappearCallback();
        }
    });

    auto imageLayoutProperty = avatarNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    UpdateNonLinkNodeProperty(imageLayoutProperty, textLayoutProperty, content);

    avatarNode->MarkModifyDone();
    avatarNode->MountToParent(frameNode);
    textNode->MountToParent(frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return frameNode;
}

void PreviewMenuController::UpdateNonLinkNodeProperty(const RefPtr<ImageLayoutProperty>& imageLayoutProperty,
    const RefPtr<TextLayoutProperty>& textLayoutProperty, const std::string& content)
{
    auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    std::optional<CalcLength> imageSize = CalcLength(AVATAR_SIZE);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(imageSize, imageSize));
    auto iconTheme = context->GetTheme<IconTheme>();
    std::string iconPath = "";
    if (iconTheme) {
        iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::IC_PERSON_FILL_SVG);
    }
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetSrc(iconPath);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto endMargin = CalcLength(MARGIN_SIZE);
    imageLayoutProperty->UpdateFlexShrink(0);
    imageLayoutProperty->UpdateMargin(
        { std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, endMargin });

    textLayoutProperty->UpdateContent(content);
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    textLayoutProperty->UpdateTextColor(theme->GetMenuFontColor());
}

RefPtr<FrameNode> PreviewMenuController::CreateLinkingNode(
    TextDataDetectType type, std::function<void()>&& disappearCallback)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::FLEX_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<FlexLayoutPattern>(false); });
    auto flexLayoutProperty = frameNode->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_RETURN(flexLayoutProperty, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventHub, nullptr);
    std::function<void()> callback;
    if (type == TextDataDetectType::URL) {
        callback = disappearCallback;
    } else if (type == TextDataDetectType::DATE_TIME) {
        auto name = ExpandedMenuPluginLoader::GetInstance().GetAPPName(type);
        callback = GetLinkingCallback(name);
    } else if (type == TextDataDetectType::ADDRESS) {
        auto name = ExpandedMenuPluginLoader::GetInstance().GetAPPName(type);
        callback = GetLinkingCallback(name);
    }
    eventHub->SetUserOnClick([callback, mainId = Container::CurrentIdSafelyWithCheck()](GestureEvent& info) {
        ContainerScope scope(mainId);
        if (callback) {
            callback();
        }
    });
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    UpdateLinkNodeProperty(textLayoutProperty, flexLayoutProperty, type);
    textNode->MountToParent(frameNode);
    return frameNode;
}

void PreviewMenuController::UpdateLinkNodeProperty(const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<FlexLayoutProperty>& flexLayoutProperty, TextDataDetectType type)
{
    auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    flexLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    flexLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    flexLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    auto windowRect = context->GetDisplayWindowRectInfo();
    std::optional<CalcLength> minHeight = CalcLength(PREVIEW_MIN_HEIGHT);
    auto maxHeightValue = windowRect.Height() * MAX_HEIGHT_PROPORTIONS;
    std::optional<CalcLength> maxHeight = CalcLength(Dimension(maxHeightValue));
    std::optional<CalcLength> maxWidth = CalcLength(PREVIEW_MAX_WIDTH);
    flexLayoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, minHeight));
    flexLayoutProperty->UpdateCalcMaxSize(CalcSize(maxWidth, maxHeight));
    auto heightValue = std::clamp(PREVIEW_MAX_WIDTH.ConvertToPx(), PREVIEW_MIN_HEIGHT.ConvertToPx(), maxHeightValue);
    std::optional<CalcLength> height = CalcLength(Dimension(heightValue));
    flexLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));

    auto theme = context->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    auto content = theme->GetPreviewDisplayFailedContent(type);
    textLayoutProperty->UpdateContent(content);
    textLayoutProperty->UpdateFontWeight(FontWeight::REGULAR);
    textLayoutProperty->UpdateFontSize(theme->GetPreviewFailedFontSize());
    textLayoutProperty->UpdateTextColor(theme->GetPreviewFailedFontColor());
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateLineSpacing(FAILED_TEXT_LINE_SPACING);
    textLayoutProperty->UpdateIsOnlyBetweenLines(true);
}

void PreviewMenuController::BindContextMenu(const RefPtr<FrameNode>& targetNode, bool isShow)
{
#ifndef ACE_UNITTEST
    CHECK_NULL_VOID(targetNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    menuBuilder_ = [weak = WeakClaim(this), mainId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(mainId);
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->CreateAIEntityMenu();
    };
    previewBuilder_ = [weak = WeakClaim(this), pattern = pattern_, mainId = Container::CurrentIdSafelyWithCheck(),
                          func = GetDisappearCallback()]() {
        ContainerScope scope(mainId);
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        auto textPattern = pattern.Upgrade();
        CHECK_NULL_VOID(textPattern);
        auto data = textPattern->GetSelectedAIData();
        controller->CreatePreviewMenu(data.type, data.content, func);
    };
    menuParam_.isShow = isShow;
    isShow_ = isShow;
    ViewAbstractModel::GetInstance()->BindContextMenu(
        ResponseType::LONG_PRESS, menuBuilder_, menuParam_, previewBuilder_);
    ViewAbstractModel::GetInstance()->BindDragWithContextMenuParams(menuParam_);
    ViewStackProcessor::GetInstance()->Finish();
#endif
}
} // namespace OHOS::Ace::NG