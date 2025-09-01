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

#include "core/common/ace_engine.h"
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
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_adapter.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/menu_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension PREVIEW_MAX_WIDTH = 360.0_vp;
constexpr Dimension MENU_WIDTH = 224.0_vp;
constexpr Dimension AVATAR_SIZE = 40.0_vp;
constexpr Dimension PREVIEW_MIN_HEIGHT = 64.0_vp;
constexpr Dimension FAILED_TEXT_LINE_SPACING = 8.0_vp;
constexpr float MAX_HEIGHT_PROPORTIONS = 0.65;
constexpr int32_t MAX_LINES = 4;
const std::string CALENDAR_ABILITY_NAME = "AgendaPreviewUIExtensionAbility";
const std::string CONTACTS_ABILITY_NAME = "DataDetectorUIExtensionAbility";
const std::string UIEXTENSION_PARAM = "ability.want.params.uiExtensionType";
const std::string UIEXTENSION_PARAM_VALUE = "sys/commonUI";
constexpr float PERCENT_FULL = 1.0;
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
        textPattern->DragNodeDetachFromParent();
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
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = textPattern->CreateAIEntityMenu();
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

void PreviewMenuController::CreatePreviewMenu(TextDataDetectType type, const std::string& content,
    std::function<void()> disappearCallback, std::map<std::string, std::string> AIparams,
    std::function<void()> aiSpanClickCallabck)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
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
    auto previewNode = CreatePreview(type);
    CHECK_NULL_VOID(previewNode);
    previewNode->MountToParent(frameNode);

    // Other types have not been integrated.
    if (type != TextDataDetectType::DATE_TIME && type != TextDataDetectType::PHONE_NUMBER &&
        type != TextDataDetectType::EMAIL) {
        MountErrorNode(previewNode, type, content, disappearCallback, aiSpanClickCallabck);
        previewNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    CreateWantParams(type, content, AIparams);
    MountUIExtensionNode(previewNode, content, std::move(disappearCallback), type, AIparams);
    return;
}

void PreviewMenuController::CreateWantParams(
    TextDataDetectType type, const std::string& content, std::map<std::string, std::string>& AIparams)
{
    if (type == TextDataDetectType::PHONE_NUMBER) {
        AIparams["phoneNumber"] = content;
    } else if (type == TextDataDetectType::EMAIL) {
        AIparams["email"] = content;
    }
}

void PreviewMenuController::MountUIExtensionNode(const RefPtr<FrameNode>& previewNode, const std::string& content,
    std::function<void()>&& disappearCallback, TextDataDetectType type,
    const std::map<std::string, std::string>& AIparams)
{
#if !defined(ACE_UNITTEST) && !defined(PREVIEW) && defined(OHOS_STANDARD_SYSTEM)
    const auto& extensionAdapter = PreviewUIExtensionAdapter::GetInstance();
    CHECK_NULL_VOID(extensionAdapter);
    UIExtensionConfig config;
    std::string bundleName;
    std::string abilityName;
    std::map<std::string, std::string> params;
    CreateWantConfig(type, bundleName, abilityName, params, AIparams);
    // 第一次使用：创建副本供 PreviewNodeClickCallback 使用
    auto callbackCopy = disappearCallback;
    PreviewNodeClickCallback(type, previewNode, AIparams, std::move(callbackCopy));
    auto wantWrap = WantWrap::CreateWantWrap(bundleName, abilityName);
    CHECK_NULL_VOID(wantWrap);
    wantWrap->SetWantParam(params);
    config.wantWrap = wantWrap;
    auto UIExtensionNode = extensionAdapter->CreatePreviewUIExtensionNode(config);
    auto&& error = GetErrorCallback(previewNode, type, content, std::move(disappearCallback));
    if (UIExtensionNode) {
        auto layoutProperty = UIExtensionNode->GetLayoutProperty();
        std::optional<CalcLength> height = CalcLength(Dimension(PERCENT_FULL, DimensionUnit::PERCENT));
        std::optional<CalcLength> weight = CalcLength(Dimension(PERCENT_FULL, DimensionUnit::PERCENT));
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(weight, height));
        extensionAdapter->UpdatePreviewUIExtensionConfig(UIExtensionNode, config);
        extensionAdapter->SetOnError(UIExtensionNode, std::move(error));
        UIExtensionNode->MarkModifyDone();
        UIExtensionNode->MountToParent(previewNode);
    } else {
        error(-1, "", "");
    }
#endif
}

void PreviewMenuController::PreviewNodeClickCallback(TextDataDetectType type, const RefPtr<FrameNode>& previewNode,
    const std::map<std::string, std::string>& AIparams, std::function<void()>&& disappearCallback)
{
    CHECK_NULL_VOID(previewNode);
    std::function<void()> clickCallback;
    switch (type) {
        case TextDataDetectType::DATE_TIME:
            clickCallback = [AIparams, mainId = Container::CurrentIdSafelyWithCheck()]() {
                ContainerScope scope(mainId);
                auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
                CHECK_NULL_VOID(pipeline);
                auto fontManager = pipeline->GetFontManager();
                CHECK_NULL_VOID(fontManager);
                fontManager->StartAbilityOnCalendar(AIparams);
            };
            break;
        case TextDataDetectType::PHONE_NUMBER:
        case TextDataDetectType::EMAIL:
            clickCallback = disappearCallback;
            break;
        case TextDataDetectType::ADDRESS:
        case TextDataDetectType::URL:
        default:
            break;
    }
    auto eventHub = previewNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetUserOnClick([clickCallback, mainId = Container::CurrentIdSafelyWithCheck()](GestureEvent& info) {
        ContainerScope scope(mainId);
        if (clickCallback) {
            clickCallback();
        }
    });
}

void PreviewMenuController::CreateWantConfig(TextDataDetectType type, std::string& bundleName, std::string& abilityName,
    std::map<std::string, std::string>& params, const std::map<std::string, std::string>& AIparams)
{
    params[UIEXTENSION_PARAM] = UIEXTENSION_PARAM_VALUE;
    switch (type) {
        case TextDataDetectType::DATE_TIME: {
            bundleName = ExpandedMenuPluginLoader::GetInstance().GetAPPName(TextDataDetectType::DATE_TIME);
            abilityName = CALENDAR_ABILITY_NAME;
            break;
        }
        case TextDataDetectType::PHONE_NUMBER:
        case TextDataDetectType::EMAIL: {
            bundleName = ExpandedMenuPluginLoader::GetInstance().GetAPPName(TextDataDetectType::PHONE_NUMBER);
            abilityName = CONTACTS_ABILITY_NAME;
            break;
        }
        case TextDataDetectType::ADDRESS:
        case TextDataDetectType::URL:
        default:
            break;
    }
    params.insert(AIparams.begin(), AIparams.end());
}

AIPreviewMenuErrorCallback PreviewMenuController::GetErrorCallback(const RefPtr<FrameNode>& previewNode,
    TextDataDetectType type, const std::string& content, std::function<void()>&& disappearCallback)
{
    return [node = WeakPtr<FrameNode>(previewNode), disappearCallback, type, content,
               mainId = Container::CurrentIdSafelyWithCheck()](
               int32_t code, const std::string& name, const std::string& message) {
        ContainerScope scope(mainId);
        if (SystemProperties::GetTextTraceEnabled()) {
            TAG_LOGI(AceLogTag::ACE_TEXT, "UIExtensionNode error callbak, mount error node!");
        }
        auto previewNode = node.Upgrade();
        CHECK_NULL_VOID(previewNode);
        previewNode->Clean();
        PreviewMenuController::MountErrorNode(previewNode, type, content, disappearCallback, nullptr);
        previewNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
}

RefPtr<FrameNode> PreviewMenuController::CreatePreview(TextDataDetectType type)
{
    RefPtr<FrameNode> node;
    switch (type) {
        case TextDataDetectType::PHONE_NUMBER:
        case TextDataDetectType::EMAIL:
        case TextDataDetectType::ADDRESS:
        case TextDataDetectType::URL:
            node = CreateContactAndAddressPreviewNode(type);
            break;
        case TextDataDetectType::DATE_TIME:
            node = CreateLinkingPreviewNode();
            break;
        default:
            break;
    }
    return node;
}

RefPtr<FrameNode> PreviewMenuController::CreateContactAndAddressPreviewNode(TextDataDetectType type)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::FLEX_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<FlexLayoutPattern>(false); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto flexLayoutProperty = frameNode->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_RETURN(flexLayoutProperty, nullptr);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto theme = context->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    auto padding = CalcLength(theme->GetPreviewMenuPadding());
    flexLayoutProperty->UpdatePadding({ padding, padding, padding, padding });
    flexLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    flexLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    std::optional<CalcLength> minHeight = CalcLength(Dimension(PREVIEW_MIN_HEIGHT.ConvertToPx()));
    std::optional<CalcLength> maxHeight = CalcLength(GetPreviewMaxHeight(frameNode));
    std::optional<CalcLength> maxWidth = CalcLength(Dimension(PREVIEW_MAX_WIDTH.ConvertToPx()));
    flexLayoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, minHeight));
    flexLayoutProperty->UpdateCalcMaxSize(CalcSize(maxWidth, maxHeight));

    // Adaptive internal content height for URL and address.
    if (type == TextDataDetectType::EMAIL || type == TextDataDetectType::PHONE_NUMBER) {
        std::optional<CalcLength> height = CalcLength(Dimension(PREVIEW_MIN_HEIGHT.ConvertToPx()));
        flexLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));
    }
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return frameNode;
}

RefPtr<FrameNode> PreviewMenuController::CreateLinkingPreviewNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::FLEX_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<FlexLayoutPattern>(false); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto flexLayoutProperty = frameNode->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_RETURN(flexLayoutProperty, nullptr);
    flexLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    flexLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    flexLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    std::optional<CalcLength> maxHeight = CalcLength(GetPreviewMaxHeight(frameNode));
    std::optional<CalcLength> maxWidth = CalcLength(Dimension(PREVIEW_MAX_WIDTH.ConvertToPx()));
    std::optional<CalcLength> minHeight = CalcLength(Dimension(PREVIEW_MIN_HEIGHT.ConvertToPx()));
    flexLayoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, minHeight));
    flexLayoutProperty->UpdateCalcMaxSize(CalcSize(maxWidth, maxHeight));
    std::optional<CalcLength> height = CalcLength(Dimension(PERCENT_FULL, DimensionUnit::PERCENT));
    flexLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return frameNode;
}

Dimension PreviewMenuController::GetPreviewMaxHeight(const RefPtr<FrameNode>& frameNode)
{
    auto maxWidth = Dimension(PREVIEW_MAX_WIDTH.ConvertToPx());
    CHECK_NULL_RETURN(frameNode, maxWidth);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, maxWidth);
    auto safeAreaManager = context->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, maxWidth);
    auto bottom = safeAreaManager->GetSafeAreaWithoutProcess().bottom_.Length();
    auto top = safeAreaManager->GetSafeAreaWithoutProcess().top_.Length();
    auto containerId = Container::CurrentId();
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_RETURN(container, maxWidth);
    // Get FreeMultiWindow status of main window or host window
    auto isFreeMultiWindow = container->IsFreeMultiWindow();
    float height;
    if (!isFreeMultiWindow) {
        height = context->GetDisplayWindowRectInfo().Height();
    } else {
        height = context->GetDisplayAvailableRect().Height();
    }
    auto maxHeightValue = (height - static_cast<float>(bottom + top)) * MAX_HEIGHT_PROPORTIONS;

    if (SystemProperties::GetTextTraceEnabled()) {
        TAG_LOGI(AceLogTag::ACE_TEXT,
            "GetPreviewMaxHeight availableRect:%{public}s GetSafeAreaWithoutProcess:%{public}s "
            "displayWindowRect:%{public}s "
            "isFreeMultiWindow:%{public}d maxHeightValue:%{public}f",
            context->GetDisplayAvailableRect().ToString().c_str(),
            safeAreaManager->GetSafeAreaWithoutProcess().ToString().c_str(),
            context->GetDisplayWindowRectInfo().ToString().c_str(), isFreeMultiWindow, maxHeightValue);
    }
    return Dimension(maxHeightValue);
}

void PreviewMenuController::MountErrorNode(const RefPtr<FrameNode>& previewNode, TextDataDetectType type,
    const std::string& content, std::function<void()> disappearCallback, std::function<void()> aiSpanClickCallabck)
{
    switch (type) {
        case TextDataDetectType::PHONE_NUMBER:
        case TextDataDetectType::EMAIL:
            CreateContactErrorNode(previewNode, content, std::move(disappearCallback));
            break;
        case TextDataDetectType::ADDRESS:
        case TextDataDetectType::URL:
            CreateURLAndAddressNode(previewNode, content, type, std::move(aiSpanClickCallabck));
            break;
        case TextDataDetectType::DATE_TIME:
            CreateLinkingErrorNode(previewNode, type, std::move(disappearCallback));
            break;
        default:
            break;
    }
}

void PreviewMenuController::CreateContactErrorNode(
    const RefPtr<FrameNode>& previewNode, const std::string& content, std::function<void()>&& disappearCallback)
{
    CHECK_NULL_VOID(previewNode);
    auto avatarNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });

    auto eventHub = previewNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetUserOnClick([disappearCallback, mainId = Container::CurrentIdSafelyWithCheck()](GestureEvent& info) {
        ContainerScope scope(mainId);
        if (disappearCallback) {
            disappearCallback();
        }
    });

    auto imageLayoutProperty = avatarNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    UpdateImageAndTitleNodeProperty(imageLayoutProperty, textLayoutProperty, TextDataDetectType::PHONE_NUMBER, content);
    avatarNode->MarkModifyDone();
    avatarNode->MountToParent(previewNode);
    textNode->MountToParent(previewNode);
    previewNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void PreviewMenuController::CreateURLAndAddressNode(const RefPtr<FrameNode>& previewNode, const std::string& content,
    TextDataDetectType type, std::function<void()>&& aiSpanClickCallabck)
{
    CHECK_NULL_VOID(previewNode);
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto flexLayoutProperty = contentNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(flexLayoutProperty);
    flexLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);

    auto eventHub = previewNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventHub);
    std::function<void()> callback;
    if (type == TextDataDetectType::URL) {
        callback = [content, type, mainId = Container::CurrentIdSafelyWithCheck()]() {
            ContainerScope scope(mainId);
            auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
            CHECK_NULL_VOID(context);
            auto fontManager = context->GetFontManager();
            CHECK_NULL_VOID(fontManager);
            fontManager->OnPreviewMenuOptionClick(type, content);
        };
    } else if (type == TextDataDetectType::ADDRESS) {
        callback = std::move(aiSpanClickCallabck);
    }
    eventHub->SetUserOnClick([callback, mainId = Container::CurrentIdSafelyWithCheck()](GestureEvent& info) {
        ContainerScope scope(mainId);
        if (callback) {
            callback();
        }
    });
    CreateURLAndAddressContentNode(previewNode, contentNode, content, type);
    previewNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void PreviewMenuController::CreateURLAndAddressContentNode(const RefPtr<FrameNode>& previewNode,
    const RefPtr<FrameNode>& contentNode, const std::string& content, TextDataDetectType type)
{
    auto avatarNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto titleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto imageLayoutProperty = avatarNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto titleProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(titleProperty);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto context = contentNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    auto title = type == TextDataDetectType::ADDRESS ? theme->GetLocationTitle() : theme->GetLinkTitle();
    UpdateImageAndTitleNodeProperty(imageLayoutProperty, titleProperty, type, title);
    textLayoutProperty->UpdateContent(content);
    textLayoutProperty->UpdateMaxLines(MAX_LINES);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateTextColor(theme->GetPreviewFailedFontColor());
    textLayoutProperty->UpdateFontSize(theme->GetPreviewFailedFontSize());
    auto topMargin = CalcLength(theme->GetPreviewContentSpace());
    textLayoutProperty->UpdateMargin(
        { std::nullopt, std::nullopt, topMargin, std::nullopt, std::nullopt, std::nullopt });
    titleNode->MountToParent(contentNode);
    textNode->MountToParent(contentNode);
    avatarNode->MarkModifyDone();
    avatarNode->MountToParent(previewNode);
    contentNode->MountToParent(previewNode);
}

void PreviewMenuController::UpdateImageAndTitleNodeProperty(const RefPtr<ImageLayoutProperty>& imageLayoutProperty,
    const RefPtr<TextLayoutProperty>& textLayoutProperty, TextDataDetectType type, const std::string& content)
{
    auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    std::optional<CalcLength> imageSize = CalcLength(AVATAR_SIZE);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(imageSize, imageSize));
    auto iconTheme = context->GetTheme<IconTheme>();
    std::string iconPath = "";
    if (iconTheme) {
        switch (type) {
            case TextDataDetectType::PHONE_NUMBER:
            case TextDataDetectType::EMAIL:
                iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::IC_PERSON_FILL_SVG);
                break;
            case TextDataDetectType::ADDRESS:
                iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::IC_LOACTION_SVG);
                break;
            case TextDataDetectType::URL:
                iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::IC_LINK_SVG);
                break;
            default:
                break;
        }
    }
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetSrc(iconPath);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto overlayTheme = context->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(overlayTheme);
    auto endMargin = CalcLength(overlayTheme->GetMenuSafeSpacing());
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

void PreviewMenuController::CreateLinkingErrorNode(
    const RefPtr<FrameNode>& previewNode, TextDataDetectType type, std::function<void()>&& disappearCallback)
{
    auto eventHub = previewNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventHub);
    std::function<void()> callback;
    if (type == TextDataDetectType::URL) {
        callback = disappearCallback;
    } else if (type == TextDataDetectType::DATE_TIME) {
        if (SystemProperties::GetPreviewStatus() == 0) {
            auto name = ExpandedMenuPluginLoader::GetInstance().GetAPPName(type);
            callback = GetLinkingCallback(name);
        } else {
            callback = disappearCallback;
        }
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
    CHECK_NULL_VOID(textLayoutProperty);
    UpdateLinkNodeProperty(textLayoutProperty, type);
    textNode->MountToParent(previewNode);
}

void PreviewMenuController::UpdateLinkNodeProperty(
    const RefPtr<TextLayoutProperty>& textLayoutProperty, TextDataDetectType type)
{
    auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
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
        auto spanClickFunc = textPattern->GetPreviewMenuAISpanClickrCallback(data);
        controller->CreatePreviewMenu(data.type, data.content, func, data.params, spanClickFunc);
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