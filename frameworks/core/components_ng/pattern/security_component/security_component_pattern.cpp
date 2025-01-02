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

#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#ifdef SECURITY_COMPONENT_ENABLE
#include "core/components_ng/pattern/security_component/security_component_handler.h"
#endif
#include "core/components_ng/pattern/security_component/security_component_log.h"
#include "core/components/common/layout/constants.h"
#ifdef SECURITY_COMPONENT_ENABLE
#include "pointer_event.h"
#endif

namespace OHOS::Ace::NG {
namespace {
#ifdef SECURITY_COMPONENT_ENABLE
const int32_t DELAY_RELEASE_MILLSEC = 10;
static std::unordered_map<uint64_t, RefPtr<FrameNode>> g_scNodeMap;
static std::vector<uint64_t> g_omittedNodeIndex;
static uint64_t g_scIndex = 0;
static std::mutex g_scMutex;
#endif
}
SecurityComponentPattern::SecurityComponentPattern()
{
#ifdef SECURITY_COMPONENT_ENABLE
    uiEventHandler_ = OHOS::AppExecFwk::EventHandler::Current();
#endif
}

SecurityComponentPattern::~SecurityComponentPattern()
{
#ifdef SECURITY_COMPONENT_ENABLE
    UnregisterSecurityComponent();
#endif
}

bool SecurityComponentPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(dirty, false);
    return !(config.skipMeasure || dirty->SkipMeasureContent());
}

void SecurityComponentPattern::SetNodeHitTestMode(RefPtr<FrameNode>& node, HitTestMode mode)
{
    if (node == nullptr) {
        return;
    }
    auto gestureHub = node->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetHitTestMode(mode);
}

void SecurityComponentPattern::OnLanguageConfigurationUpdate()
{
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    auto textNode = GetSecCompChildNode(node, V2::TEXT_ETS_TAG);
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    if (layoutProperty && layoutProperty->GetTextStyle().has_value()) {
        auto textStyle = layoutProperty->GetTextStyle().value();
        if (textStyle != static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL)) {
            auto pipeline = textNode->GetContextRefPtr();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SecurityComponentTheme>();
            CHECK_NULL_VOID(theme);

            std::string text;
            if (node->GetTag() == V2::PASTE_BUTTON_ETS_TAG) {
                text = theme->GetPasteDescriptions(textStyle);
            } else if (node->GetTag() == V2::LOCATION_BUTTON_ETS_TAG) {
                text = theme->GetLocationDescriptions(textStyle);
            } else if (node->GetTag() == V2::SAVE_BUTTON_ETS_TAG) {
                text = theme->GetSaveDescriptions(textStyle);
            }

            textLayoutProperty->UpdateContent(text);
        }
    }
}

bool SecurityComponentPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((event.code == KeyCode::KEY_SPACE) || (event.code == KeyCode::KEY_ENTER) ||
        (event.code == KeyCode::KEY_NUMPAD_ENTER)) {
        auto frameNode = GetHost();
        CHECK_NULL_RETURN(frameNode, false);
        int32_t res = 1;
#ifdef SECURITY_COMPONENT_ENABLE
        res = ReportSecurityComponentClickEvent(event);
        if (res == Security::SecurityComponent::SC_SERVICE_ERROR_WAIT_FOR_DIALOG_CLOSE) {
            res = static_cast<int32_t>(SecurityComponentHandleResult::DROP_CLICK);
        } else if (res != 0) {
            SC_LOG_ERROR("ReportSecurityComponentClickEvent failed, errno %{public}d", res);
            res = 1;
        }
#endif
        auto jsonNode = JsonUtil::Create(true);
        CHECK_NULL_RETURN(jsonNode, false);
        jsonNode->Put("handleRes", res);
        std::shared_ptr<JsonValue> jsonShrd(jsonNode.release());
        auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
        gestureEventHub->ActClick(jsonShrd);
        return true;
    }
    return false;
}

void SecurityComponentPattern::InitOnKeyEvent(RefPtr<FrameNode>& secCompNode)
{
    if (isSetOnKeyEvent) {
        return;
    }
    auto focusHub = secCompNode->GetOrCreateFocusHub();
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (!pattern) {
            return false;
        }
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
    isSetOnKeyEvent = true;
}

bool SecurityComponentPattern::IsParentMenu(RefPtr<FrameNode>& secCompNode)
{
    auto parent = secCompNode->GetParent();
    while (parent != nullptr) {
        if (parent->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            return true;
        }
        parent = parent->GetParent();
    }
    return false;
}

void SecurityComponentPattern::HandleClickEventFromTouch(const TouchEventInfo& info)
{
#ifdef SECURITY_COMPONENT_ENABLE
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (!IsParentMenu(host)) {
        return;
    }

    auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);

    int32_t pointerId = pointerEvent->GetPointerId();
    MMI::PointerEvent::PointerItem item;
    if (!pointerEvent->GetPointerItem(pointerId, item)) {
        SC_LOG_WARN("Get pointer item failed");
        return;
    }

    GestureEvent gestureInfo;
    gestureInfo.SetDisplayX(item.GetDisplayX());
    gestureInfo.SetDisplayY(item.GetDisplayY());
    gestureInfo.SetPointerEvent(info.GetPointerEvent());
    int res = ReportSecurityComponentClickEvent(gestureInfo);
    if (res == Security::SecurityComponent::SC_SERVICE_ERROR_WAIT_FOR_DIALOG_CLOSE) {
        return;
    }
    if (res != 0) {
        SC_LOG_WARN("ReportSecurityComponentClickEvent failed, errno %{public}d", res);
        res = 1;
    }
    auto jsonNode = JsonUtil::Create(true);
    CHECK_NULL_VOID(jsonNode);
    jsonNode->Put("handleRes", res);
    std::shared_ptr<JsonValue> jsonShrd(jsonNode.release());
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    gestureEventHub->ActClick(jsonShrd);
#endif
}

// When security component is a child node of menu wrapper, the menu is immediately hidden
// after being touched, and then the security component will trigger a click event.
// However, it will be considered to have been triggered in a hidden state,
// Therefore, we should report click event on UP touch event.
void SecurityComponentPattern::OnTouch(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        lastTouchOffset_ = std::make_unique<Offset>(info.GetTouches().front().GetLocalLocation());
    } else if (touchType == TouchType::UP) {
        auto touchUpOffset = info.GetTouches().front().GetLocalLocation();
        if (lastTouchOffset_ &&
            (touchUpOffset - *lastTouchOffset_).GetDistance() <= DEFAULT_SECURITY_COMPONENT_CLICK_DISTANCE) {
            HandleClickEventFromTouch(info);
        }
        lastTouchOffset_.reset();
    }
}

void SecurityComponentPattern::InitOnTouch(RefPtr<FrameNode>& secCompNode)
{
    if (onTouchListener_ != nullptr) {
        return;
    }
    auto gestureHub = secCompNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnTouch(info);
    };
    onTouchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(onTouchListener_);
}

void SecurityComponentPattern::InitOnClick(RefPtr<FrameNode>& secCompNode, RefPtr<FrameNode>& icon,
    RefPtr<FrameNode>& text, RefPtr<FrameNode>& button)
{
    if (clickListener_ != nullptr) {
        return;
    }
    auto secCompGesture = secCompNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(secCompGesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
#ifdef SECURITY_COMPONENT_ENABLE
        auto buttonPattern = weak.Upgrade();
        CHECK_NULL_VOID(buttonPattern);
        auto frameNode = buttonPattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        if (info.GetSecCompHandleEvent()) {
            return;
        }
        auto jsonNode = JsonUtil::Create(true);
        CHECK_NULL_VOID(jsonNode);
        std::shared_ptr<JsonValue> jsonShrd(jsonNode.release());
        int32_t res;
        // if info.GetPointerEvent() is null, device may in screen read mode
        // otherwise, this event should be dropped in menu
        if (buttonPattern->IsParentMenu(frameNode) && info.GetPointerEvent() != nullptr) {
            res = static_cast<int32_t>(SecurityComponentHandleResult::DROP_CLICK);
        } else {
            res = buttonPattern->ReportSecurityComponentClickEvent(info);
            if (res == Security::SecurityComponent::SC_SERVICE_ERROR_WAIT_FOR_DIALOG_CLOSE) {
                res = static_cast<int32_t>(SecurityComponentHandleResult::DROP_CLICK);
            } else if (res != 0) {
                SC_LOG_WARN("ReportSecurityComponentClickEvent failed, errno %{public}d", res);
                res = static_cast<int32_t>(SecurityComponentHandleResult::CLICK_GRANT_FAILED);
            }
        }
        jsonShrd->Put("handleRes", res);
        info.SetSecCompHandleEvent(jsonShrd);
#endif
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    secCompGesture->AddClickEvent(clickListener_);
    SetNodeHitTestMode(icon, HitTestMode::HTMTRANSPARENT);
    SetNodeHitTestMode(text, HitTestMode::HTMTRANSPARENT);
}

void SecurityComponentPattern::ToJsonValueIconNode(std::unique_ptr<JsonValue>& json, const RefPtr<FrameNode>& iconNode,
    const InspectorFilter& filter) const
{
    auto iconProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(iconProp);
    CHECK_NULL_VOID(iconProp->GetCalcLayoutConstraint());
    // GetDimension would ret a empty dimension when width is empty
    auto width = iconProp->GetCalcLayoutConstraint()->selfIdealSize->Width();
    CHECK_EQUAL_VOID(width.has_value(), false);
    json->PutExtAttr("iconSize", width->GetDimension().ToString().c_str(), filter);
    json->PutExtAttr("iconColor", iconProp->GetImageSourceInfo()->GetFillColor().
        value_or(Color::WHITE).ColorToString().c_str(), filter);
}

void SecurityComponentPattern::ToJsonValueTextNode(std::unique_ptr<JsonValue>& json, const RefPtr<FrameNode>& textNode,
    const InspectorFilter& filter) const
{
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProp);
    json->PutExtAttr("fontSize", textProp->GetFontSize().value_or(Dimension(0.0)).ToString().c_str(), filter);
    json->PutExtAttr("fontWeight", V2::ConvertWrapFontWeightToStirng(
        textProp->GetFontWeight().value_or(FontWeight::NORMAL)).c_str(), filter);
    json->PutExtAttr("fontFamily", "HarmonyOS Sans", filter);
    json->PutExtAttr("fontStyle",
        static_cast<int64_t>(textProp->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL)), filter);
    json->PutExtAttr("fontColor", textProp->GetTextColor().value_or(Color::WHITE).ColorToString().c_str(), filter);
}

void SecurityComponentPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        ToJsonValueRect(json, filter);
        return;
    }
    auto node = GetHost();
    CHECK_NULL_VOID(node);

    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    json->PutExtAttr("text", layoutProperty->GetSecurityComponentDescription().value_or(0), filter);
    json->PutExtAttr("icon", layoutProperty->GetIconStyle().value_or(0), filter);
    json->PutExtAttr("buttonType", layoutProperty->GetBackgroundType().value_or(0), filter);
    json->PutExtAttr("layoutDirection", static_cast<int64_t>(
        layoutProperty->GetTextIconLayoutDirection().value_or(SecurityComponentLayoutDirection::VERTICAL)), filter);
    json->PutExtAttr("type", node->GetTag().c_str(), filter);

    RefPtr<FrameNode> iconNode = GetSecCompChildNode(node, V2::IMAGE_ETS_TAG);
    if (iconNode != nullptr) {
        ToJsonValueIconNode(json, iconNode, filter);
    }
    RefPtr<FrameNode> textNode = GetSecCompChildNode(node, V2::TEXT_ETS_TAG);
    if (textNode != nullptr) {
        ToJsonValueTextNode(json, textNode, filter);
    }
    auto paddingJson = JsonUtil::Create(true);
    CHECK_NULL_VOID(paddingJson);
    paddingJson->Put("top", layoutProperty->GetBackgroundTopPadding().value_or(Dimension(0.0)).ToString().c_str());
    paddingJson->Put("bottom",
        layoutProperty->GetBackgroundBottomPadding().value_or(Dimension(0.0)).ToString().c_str());
    paddingJson->Put("left", layoutProperty->GetBackgroundLeftPadding().value_or(Dimension(0.0)).ToString().c_str());
    paddingJson->Put("right", layoutProperty->GetBackgroundRightPadding().value_or(Dimension(0.0)).ToString().c_str());
    json->PutExtAttr("padding", paddingJson, filter);
    json->PutExtAttr("textIconSpace",
        layoutProperty->GetTextIconSpace().value_or(Dimension(0.0)).ToString().c_str(), filter);
    ToJsonValueRect(json, filter);
}

void SecurityComponentPattern::ToJsonValueRect(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto node = GetHost();
    CHECK_NULL_VOID(node);

    RefPtr<FrameNode> buttonNode = GetSecCompChildNode(node, V2::BUTTON_ETS_TAG);
    if (buttonNode != nullptr) {
        const auto& renderContext = buttonNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (renderContext->HasBackgroundColor()) {
            json->PutExtAttr("backgroundColor",
                renderContext->GetBackgroundColor().value().ColorToString().c_str(), filter);
        } else {
            json->PutExtAttr("backgroundColor", Color::BLACK.ColorToString().c_str(), filter);
        }
        if (renderContext->HasBorderColor()) {
            json->PutExtAttr("borderColor",
                renderContext->GetBorderColor()->leftColor.value_or(Color::BLACK).ColorToString().c_str(), filter);
        } else {
            json->PutExtAttr("borderColor", Color::BLACK.ColorToString().c_str(), filter);
        }
        if (renderContext->HasBorderStyle()) {
            json->PutExtAttr("borderStyle",
                static_cast<int>(renderContext->GetBorderStyle()->styleLeft.value_or(BorderStyle::NONE)), filter);
        } else {
            json->PutExtAttr("borderStyle", static_cast<int>(BorderStyle::NONE), filter);
        }
        auto bgProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(bgProp);
        const auto& borderWidth = bgProp->GetBorderWidthProperty();
        if (borderWidth != nullptr) {
            json->PutExtAttr("borderWidth",
                borderWidth->leftDimen.value_or(Dimension(0.0)).ToString().c_str(), filter);
        }
        auto borderRadius = bgProp->GetBorderRadius();
        if (borderRadius.has_value()) {
            json->PutExtAttr("borderRadius", borderRadius->radiusTopLeft.value_or(Dimension(0.0, DimensionUnit::VP)).
                ToString().c_str(), filter);
        } else {
            json->PutExtAttr("borderRadius", "0.00vp", filter);
        }
    }
}

FocusPattern SecurityComponentPattern::GetFocusPattern() const
{
    auto frameNode = GetHost();
    RefPtr<FrameNode> buttonNode = GetSecCompChildNode(frameNode, V2::BUTTON_ETS_TAG);
    if (buttonNode != nullptr) {
        auto buttonPattern = buttonNode->GetPattern<ButtonPattern>();
        return buttonPattern->GetFocusPattern();
    }

    return { FocusType::NODE, true, FocusStyleType::OUTER_BORDER };
}

void SecurityComponentPattern::UpdateIconProperty(RefPtr<FrameNode>& scNode, RefPtr<FrameNode>& iconNode)
{
    auto iconLayoutProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    auto scLayoutProp = scNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(scLayoutProp);
    if (scLayoutProp->GetIconSize().has_value()) {
        auto iconSize = scLayoutProp->GetIconSize().value();
        iconLayoutProp->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(iconSize), NG::CalcLength(iconSize)));
    }

    auto scPaintProp = scNode->GetPaintProperty<SecurityComponentPaintProperty>();
    CHECK_NULL_VOID(scPaintProp);
    if (scPaintProp->GetIconColor().has_value() && iconLayoutProp->GetImageSourceInfo().has_value()) {
        auto iconSrcInfo = iconLayoutProp->GetImageSourceInfo().value();
        iconSrcInfo.SetFillColor(scPaintProp->GetIconColor().value());
        iconLayoutProp->UpdateImageSourceInfo(iconSrcInfo);
    }
}

void SecurityComponentPattern::UpdateTextProperty(RefPtr<FrameNode>& scNode, RefPtr<FrameNode>& textNode)
{
    auto scLayoutProp = scNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    auto textLayoutProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    if (scLayoutProp->GetFontSize().has_value()) {
        textLayoutProp->UpdateFontSize(scLayoutProp->GetFontSize().value());
    }
    if (scLayoutProp->GetFontStyle().has_value()) {
        textLayoutProp->UpdateItalicFontStyle(scLayoutProp->GetFontStyle().value());
    }
    if (scLayoutProp->GetFontWeight().has_value()) {
        textLayoutProp->UpdateFontWeight(scLayoutProp->GetFontWeight().value());
    }
    if (scLayoutProp->GetFontFamily().has_value()) {
        textLayoutProp->UpdateFontFamily(scLayoutProp->GetFontFamily().value());
    }
    auto scPaintProp = scNode->GetPaintProperty<SecurityComponentPaintProperty>();
    if (scPaintProp->GetFontColor().has_value()) {
        textLayoutProp->UpdateTextColor(scPaintProp->GetFontColor().value());
    }
    if (scLayoutProp->GetMaxFontScale().has_value()) {
        textLayoutProp->UpdateMaxFontScale(scLayoutProp->GetMaxFontScale().value());
    }
    if (scLayoutProp->GetMinFontScale().has_value()) {
        textLayoutProp->UpdateMinFontScale(scLayoutProp->GetMinFontScale().value());
    }
    if (scLayoutProp->GetMaxLines().has_value()) {
        textLayoutProp->UpdateMaxLines(scLayoutProp->GetMaxLines().value());
    }
    if (scLayoutProp->GetAdaptMaxFontSize().has_value()) {
        textLayoutProp->UpdateAdaptMaxFontSize(scLayoutProp->GetAdaptMaxFontSize().value());
    }
    if (scLayoutProp->GetAdaptMinFontSize().has_value()) {
        textLayoutProp->UpdateAdaptMinFontSize(scLayoutProp->GetAdaptMinFontSize().value());
    }
    if (scLayoutProp->GetHeightAdaptivePolicy().has_value()) {
        textLayoutProp->UpdateHeightAdaptivePolicy(scLayoutProp->GetHeightAdaptivePolicy().value());
    }
}

void SecurityComponentPattern::HandleEnabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);
    auto alpha = theme->GetBgDisabledAlpha();
    auto originalOpacity = renderContext->GetOpacityValue(1.0);
    renderContext->OnOpacityUpdate(enabled ? originalOpacity : alpha * originalOpacity);
}

void SecurityComponentPattern::UpdateButtonProperty(RefPtr<FrameNode>& scNode, RefPtr<FrameNode>& buttonNode)
{
    auto scLayoutProp = scNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    auto scPaintProp = scNode->GetPaintProperty<SecurityComponentPaintProperty>();
    auto buttonLayoutProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    const auto& buttonRender = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(buttonRender);
    auto buttonEventHub = buttonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);

    if (scLayoutProp->GetBackgroundBorderWidth().has_value()) {
        BorderWidthProperty widthProp;
        widthProp.SetBorderWidth(scLayoutProp->GetBackgroundBorderWidth().value());
        buttonLayoutProp->UpdateBorderWidth(widthProp);
    }

    if (scPaintProp->GetBackgroundBorderStyle().has_value()) {
        BorderStyleProperty style;
        style.SetBorderStyle(scPaintProp->GetBackgroundBorderStyle().value());
        buttonRender->UpdateBorderStyle(style);
    }
    if (scLayoutProp->GetBackgroundBorderRadius().has_value()) {
        buttonLayoutProp->UpdateBorderRadius(
            BorderRadiusProperty(scLayoutProp->GetBackgroundBorderRadius().value()));
    }
    if (scPaintProp->GetBackgroundColor().has_value()) {
        buttonRender->UpdateBackgroundColor(scPaintProp->GetBackgroundColor().value());
    }
    if (scPaintProp->GetBackgroundBorderColor().has_value()) {
        BorderColorProperty borderColor;
        borderColor.SetColor(scPaintProp->GetBackgroundBorderColor().value());
        buttonRender->UpdateBorderColor(borderColor);
    }
    if (scLayoutProp->GetStateEffect().has_value()) {
        buttonEventHub->SetStateEffect(scLayoutProp->GetStateEffect().value());
    }
    if (scLayoutProp->GetHoverEffect().has_value()) {
        auto inputHub = buttonEventHub->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        inputHub->SetHoverEffect(scLayoutProp->GetHoverEffect().value());
    }
    HandleEnabled();
}

void SecurityComponentPattern::OnModifyDone()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);

    RefPtr<FrameNode> iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    if (iconNode != nullptr) {
        UpdateIconProperty(frameNode, iconNode);
        iconNode->MarkModifyDone();
    }

    RefPtr<FrameNode> textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    if (textNode != nullptr) {
        UpdateTextProperty(frameNode, textNode);
        textNode->MarkModifyDone();
    }

    RefPtr<FrameNode> buttonNode = GetSecCompChildNode(frameNode, V2::BUTTON_ETS_TAG);
    if (buttonNode != nullptr) {
        UpdateButtonProperty(frameNode, buttonNode);
        buttonNode->MarkModifyDone();
    }

    InitOnClick(frameNode, iconNode, textNode, buttonNode);
    InitOnKeyEvent(frameNode);
    InitAppearCallback(frameNode);
    InitOnTouch(frameNode);
}

bool SecurityComponentPattern::IsFontColorSet()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto prop = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    if (prop && prop->GetIsFontColorSet().has_value()) {
        return prop->GetIsFontColorSet().value();
    }
    return false;
}

void SecurityComponentPattern::OnColorConfigurationUpdate()
{
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    node->SetNeedCallChildrenUpdate(IsFontColorSet());
}

void SecurityComponentPattern::InitAppearCallback(RefPtr<FrameNode>& frameNode)
{
    if (isAppearCallback_) {
        return;
    }
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);

    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    auto onAppear = [weak = WeakClaim(this), instanceId]() {
        ContainerScope scope(instanceId);
#ifdef SECURITY_COMPONENT_ENABLE
        auto securityComponentPattern = weak.Upgrade();
        CHECK_NULL_VOID(securityComponentPattern);
        securityComponentPattern->isAppear_ = true;
        securityComponentPattern->RegisterSecurityComponent();
#endif
    };

    auto onDisAppear = [weak = WeakClaim(this)]() {
#ifdef SECURITY_COMPONENT_ENABLE
        auto securityComponentPattern = weak.Upgrade();
        CHECK_NULL_VOID(securityComponentPattern);
        securityComponentPattern->isAppear_ = false;
        securityComponentPattern->UnregisterSecurityComponent();
#endif
    };
    eventHub->SetOnAppear(std::move(onAppear));
    eventHub->SetOnDisappear(std::move(onDisAppear));
    isAppearCallback_ = true;
}

void SecurityComponentPattern::OnWindowHide()
{
#ifdef SECURITY_COMPONENT_ENABLE
    UnregisterSecurityComponent();
#endif
}

void SecurityComponentPattern::OnWindowShow()
{
#ifdef SECURITY_COMPONENT_ENABLE
    if (!isAppear_) {
        return;
    }
    RegisterSecurityComponent();
#endif
}

#ifdef SECURITY_COMPONENT_ENABLE
void SecurityComponentPattern::RegisterSecurityComponentRetry()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    // service is shutdowning, try to load it.
    int32_t retryCount = MAX_RETRY_TIMES;
    while (retryCount > 0) {
        int32_t res = SecurityComponentHandler::RegisterSecurityComponent(frameNode, scId_);
        if (res == Security::SecurityComponent::SCErrCode::SC_OK) {
            regStatus_ = SecurityComponentRegisterStatus::REGISTERED;
            return;
        } else if (res != Security::SecurityComponent::SCErrCode::SC_SERVICE_ERROR_SERVICE_NOT_EXIST) {
            SC_LOG_WARN("Register security component failed, err %{public}d.", res);
            regStatus_ = SecurityComponentRegisterStatus::UNREGISTERED;
            return;
        }

        retryCount--;
        std::this_thread::sleep_for(std::chrono::milliseconds(REGISTER_RETRY_INTERVAL));
    }
    regStatus_ = SecurityComponentRegisterStatus::UNREGISTERED;
    SC_LOG_WARN("Register security component failed, retry %{public}d", MAX_RETRY_TIMES);
}

void SecurityComponentPattern::RegisterSecurityComponent()
{
    if (regStatus_ == SecurityComponentRegisterStatus::REGISTERED ||
        regStatus_ == SecurityComponentRegisterStatus::REGISTERING) {
        return;
    }

    if (SecurityComponentHandler::IsSecurityComponentServiceExist()) {
        RegisterSecurityComponentRetry();
        return;
    }
    regStatus_ = SecurityComponentRegisterStatus::REGISTERING;
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    taskExecutor->PostTask(
        [weak = WeakClaim(this), weakContext = WeakPtr(pipeline)] {
            if (!SecurityComponentHandler::LoadSecurityComponentService()) {
                SC_LOG_WARN("load security component service failed.");
                return;
            }
            auto context = weakContext.Upgrade();
            CHECK_NULL_VOID(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weak, instanceID = context->GetInstanceId()] {
                    ContainerScope scope(instanceID);
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    if (pattern->regStatus_ != SecurityComponentRegisterStatus::REGISTERING) {
                        return;
                    }

                    pattern->RegisterSecurityComponentRetry();
                },
                TaskExecutor::TaskType::UI, "ArkUISecurityComponentRegisterRetry");
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUISecurityComponentRegister");
}

void SecurityComponentPattern::UnregisterSecurityComponent()
{
    if (regStatus_ == SecurityComponentRegisterStatus::REGISTERED) {
        SecurityComponentHandler::UnregisterSecurityComponent(scId_);
    } else {
        SC_LOG_INFO("security component has not registered, regStatus %{public}d.", regStatus_);
    }
    regStatus_ = SecurityComponentRegisterStatus::UNREGISTERED;
    scId_ = -1;
}

void SecurityComponentPattern::DoTriggerOnclick(int32_t result)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto jsonNode = JsonUtil::Create(true);
    CHECK_NULL_VOID(jsonNode);
    if (result != 0) {
        jsonNode->Put("handleRes", static_cast<int32_t>(SecurityComponentHandleResult::CLICK_GRANT_FAILED));
    } else {
        jsonNode->Put("handleRes", static_cast<int32_t>(SecurityComponentHandleResult::CLICK_SUCCESS));
    }

    std::shared_ptr<JsonValue> jsonShrd(jsonNode.release());
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    gestureEventHub->ActClick(jsonShrd);
}

void SecurityComponentPattern::DelayReleaseNode(uint64_t index)
{
    if (uiEventHandler_ == nullptr) {
        SC_LOG_WARN("UIEventHandler invalid");
        return;
    }
    bool res = uiEventHandler_->PostTask([index] {
        std::lock_guard<std::mutex> lock(g_scMutex);
        g_scNodeMap.erase(index);
        if (g_omittedNodeIndex.size() != 0) {
            for (auto item : g_omittedNodeIndex) {
                g_scNodeMap.erase(item);
            }
            g_omittedNodeIndex.clear();
        }
        SC_LOG_INFO("Security component frameNode cached size: %{public}zu, index: %{public}" PRId64,
            g_scNodeMap.size(), index);
        return;
    },
    DELAY_RELEASE_MILLSEC);
    if (!res) {
        SC_LOG_ERROR("Security component post task failed.");
        g_omittedNodeIndex.push_back(index);
    }
}

std::function<int32_t(int32_t)> SecurityComponentPattern::CreateFirstUseDialogCloseFunc(
    RefPtr<FrameNode>& frameNode, RefPtr<PipelineContext>& pipeline, const std::string& taskName)
{
    return [weak = WeakClaim(this), weakContext = WeakPtr(pipeline),
        node = frameNode, taskName = taskName](int32_t result) mutable {
        std::lock_guard<std::mutex> lock(g_scMutex);
        g_scNodeMap[++g_scIndex] = std::move(node);
        auto pattern = weak.Upgrade();
        if (pattern == nullptr) {
            return -1;
        }
        auto context = weakContext.Upgrade();
        if (context == nullptr) {
            pattern->DelayReleaseNode(g_scIndex);
            return -1;
        }
        auto taskExecutor = context->GetTaskExecutor();
        if (taskExecutor == nullptr) {
            pattern->DelayReleaseNode(g_scIndex);
            return -1;
        }
        bool res = taskExecutor->PostTask(
            [weak, instanceId = context->GetInstanceId(), result, index = g_scIndex] {
                ContainerScope scope(instanceId);
                std::lock_guard<std::mutex> lock(g_scMutex);
                SC_LOG_INFO("Security component frameNode cached size: %{public}zu, index: %{public}" PRId64,
                    g_scNodeMap.size(), index);
                if (g_omittedNodeIndex.size() != 0) {
                    for (auto item : g_omittedNodeIndex) {
                        g_scNodeMap.erase(item);
                    }
                    g_omittedNodeIndex.clear();
                }
                if (result == static_cast<int32_t>(SecurityComponentHandleResult::GRANT_CANCEL)) {
                    g_scNodeMap.erase(index);
                    return;
                }
                auto pattern = weak.Upgrade();
                if (pattern == nullptr) {
                    g_scNodeMap.erase(index);
                    return;
                }
                pattern->DoTriggerOnclick(result);
                g_scNodeMap.erase(index);
            },
            TaskExecutor::TaskType::UI, taskName);
        if (!res) {
            SC_LOG_ERROR("Security component post task failed.");
            g_omittedNodeIndex.push_back(g_scIndex);
        }
        return 0;
    };
}

int32_t SecurityComponentPattern::ReportSecurityComponentClickEvent(GestureEvent& event)
{
    if (regStatus_ == SecurityComponentRegisterStatus::UNREGISTERED) {
        SC_LOG_WARN("ClickEventHandler: security component has not registered.");
        return -1;
    }
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, -1);
    if (regStatus_ == SecurityComponentRegisterStatus::REGISTERING) {
        RegisterSecurityComponentRetry();
    }
    if (regStatus_ != SecurityComponentRegisterStatus::REGISTERED) {
        SC_LOG_WARN("ClickEventHandler: security component try to register failed.");
        return -1;
    }

    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, -1);
    std::function<void (int32_t)> OnClickAfterFirstUseDialog;
    if (frameNode->GetTag() == V2::PASTE_BUTTON_ETS_TAG) {
        OnClickAfterFirstUseDialog = [] (int32_t) {};
        return SecurityComponentHandler::ReportSecurityComponentClickEvent(scId_,
            frameNode, event, std::move(OnClickAfterFirstUseDialog));
    }

    OnClickAfterFirstUseDialog = CreateFirstUseDialogCloseFunc(
        frameNode, pipeline, "ArkUISecurityComponentGestureTriggerOnClick");

    return SecurityComponentHandler::ReportSecurityComponentClickEvent(scId_,
        frameNode, event, std::move(OnClickAfterFirstUseDialog));
}

int32_t SecurityComponentPattern::ReportSecurityComponentClickEvent(const KeyEvent& event)
{
    if (regStatus_ == SecurityComponentRegisterStatus::UNREGISTERED) {
        SC_LOG_WARN("KeyEventHandler: security component has not registered.");
        return -1;
    }
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, -1);
    if (regStatus_ == SecurityComponentRegisterStatus::REGISTERING) {
        RegisterSecurityComponentRetry();
    }
    if (regStatus_ != SecurityComponentRegisterStatus::REGISTERED) {
        SC_LOG_WARN("KeyEventHandler: security component try to register failed.");
        return -1;
    }

    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, -1);
    std::function<void (int32_t)> OnClickAfterFirstUseDialog;
    if (frameNode->GetTag() == V2::PASTE_BUTTON_ETS_TAG) {
        OnClickAfterFirstUseDialog = [] (int32_t) {};
        return SecurityComponentHandler::ReportSecurityComponentClickEvent(scId_,
            frameNode, event, std::move(OnClickAfterFirstUseDialog));
    }

    OnClickAfterFirstUseDialog = CreateFirstUseDialogCloseFunc(
        frameNode, pipeline, "ArkUISecurityComponentKeyTriggerOnClick");

    return SecurityComponentHandler::ReportSecurityComponentClickEvent(scId_,
        frameNode, event, std::move(OnClickAfterFirstUseDialog));
}
#endif
} // namespace OHOS::Ace::NG
