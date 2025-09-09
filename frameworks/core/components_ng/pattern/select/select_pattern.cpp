/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select/select_pattern.h"

#include <cstdint>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/json/json_util.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "base/utils/utf_helper.h"
#include "core/animation/curves.h"
#include "core/common/ace_engine.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_row_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/select/select_event_hub.h"
#include "core/components_ng/pattern/select/select_layout_property.h"
#include "core/components_ng/pattern/select/select_paint_property.h"
#include "core/components_ng/pattern/select/select_properties.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {

namespace {

constexpr uint32_t SELECT_ITSELF_TEXT_LINES = 1;

constexpr Dimension OPTION_MARGIN = 8.0_vp;

constexpr Dimension CALIBERATE_X = 4.0_vp;

constexpr Dimension CALIBERATE_Y = 4.0_vp;

constexpr Dimension SELECT_SMALL_PADDING_VP = 4.0_vp;

constexpr Dimension SELECT_MARGIN_VP = 8.0_vp;

constexpr uint32_t RENDERINGSTRATEGY_MULTIPLE_COLOR = 1;

constexpr int32_t FIRST_NODE_INDEX = 0;

static std::string ConvertControlSizeToString(ControlSize controlSize)
{
    std::string result;
    switch (controlSize) {
        case ControlSize::SMALL:
            result = "ControlSize.SMALL";
            break;
        case ControlSize::NORMAL:
            result = "ControlSize.NORMAL";
            break;
        default:
            break;
    }
    return result;
}

void RecordChange(RefPtr<FrameNode> host, int32_t index, const std::string& value)
{
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        auto inspectorId = host->GetInspectorId().value_or("");
        Recorder::EventParamsBuilder builder;
        builder.SetId(inspectorId)
            .SetType(host->GetTag())
            .SetIndex(index)
            .SetText(value)
            .SetHost(host)
            .SetDescription(host->GetAutoEventParamValue(""));
        Recorder::EventRecorder::Get().OnChange(std::move(builder));
        if (!inspectorId.empty()) {
            Recorder::NodeDataCache::Get().PutMultiple(host, inspectorId, value, index);
        }
    }
}

static std::string ConvertVectorToString(std::vector<std::string> vec)
{
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << ((i == 0) ? "" : ",") << vec[i];
    }
    return oss.str();
}
} // namespace

void SelectPattern::OnAttachToFrameNode()
{
    RegisterOnKeyEvent();
    RegisterOnClick();
    RegisterOnPress();
    RegisterOnHover();
}

void SelectPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    CreateSelectedCallback();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<SelectEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->IsEnabled()) {
        SetDisabledStyle();
    }
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->UpdateSelectIndex(selected_);
    InitFocusEvent();
    for (const auto& option : options_) {
        option->MarkModifyDone();
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto selectPaintProperty = host->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(selectPaintProperty);
    if (selectPaintProperty->HasBackgroundColor()) {
        return;
    }
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<SelectTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        renderContext->UpdateBackgroundColor(theme->GetBackgroundColor());
    } else {
        renderContext->UpdateBackgroundColor(theme->GetButtonBackgroundColor());
    }
}

void SelectPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (inspectorId.empty()) {
        return;
    }
    Recorder::NodeDataCache::Get().PutMultiple(host, inspectorId, selectValue_, selected_);
}

void SelectPattern::SetItemSelected(int32_t index, const std::string& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    isSelected_ = true;
    menuPattern->UpdateSelectIndex(index);
    CHECK_NULL_VOID(text_);
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProps);
    SetSelected(index);
    textProps->UpdateContent(value);
    text_->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    menuPattern->HideMenu(HideMenuType::SELECT_SELECTED);
    auto hub = host->GetEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);

    auto onSelect = hub->GetSelectEvent();
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "select choice index %{public}d", index);
    if (onSelect) {
        onSelect(index, value);
    }
    RecordChange(host, index, value);
}

void SelectPattern::ShowSelectMenu()
{
    CHECK_NULL_VOID(!options_.empty());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    UpdateTargetSize();
    auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
    CHECK_NULL_VOID(selectLayoutProps);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (theme->GetExpandDisplay() && selectLayoutProps->GetShowInSubWindowValue(false)) {
        ShowSelectMenuInSubWindow();
        return;
    }
    auto offset = host->GetPaintRectOffset(false, true);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        offset.AddY(selectSize_.Height() + CALIBERATE_Y.ConvertToPx());
        offset.AddX(-CALIBERATE_X.ConvertToPx());
    } else {
        offset.AddY(selectSize_.Height());
    }
    ShowScrollBar();
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "select click to show menu.");
    overlayManager->ShowMenu(host->GetId(), offset, menuWrapper_);
}

void SelectPattern::ShowSelectMenuInSubWindow()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto offset = host->GetPositionToScreenWithTransform();
    auto offsetCustomTitleHeight = static_cast<float>(pipeline->GetCustomTitleHeight().ConvertToPx());
    offset.AddY(selectSize_.Height() + offsetCustomTitleHeight + CALIBERATE_Y.ConvertToPx());
    offset.AddX(-CALIBERATE_X.ConvertToPx());
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateShowInSubWindow(true);
    auto subwindowManager = SubwindowManager::GetInstance();
    CHECK_NULL_VOID(subwindowManager);
    MenuParam menuParam {};
    menuParam.type = MenuType::MENU;
    menuParam.isShowInSubWindow = true;
    menuParam.isShow = true;
    menuParam.setShow = true;
    subwindowManager->ShowMenuNG(menuWrapper_, menuParam, host, offset);
}

void SelectPattern::UpdateOptionsWidth(float selectWidth)
{
    for (size_t i = 0; i < options_.size(); ++i) {
        auto optionNode = options_[i];
        CHECK_NULL_VOID(optionNode);
        auto optionGeoNode = optionNode->GetGeometryNode();
        CHECK_NULL_VOID(optionGeoNode);
        auto optionWidth = selectWidth - OPTION_MARGIN.ConvertToPx();
        auto optionPattern = optionNode->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        optionPattern->SetIsWidthModifiedBySelect(true);
        auto optionPaintProperty = optionNode->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(optionPaintProperty);
        optionPaintProperty->UpdateSelectModifiedWidth(optionWidth);
        optionNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

// add click event to show menu
void SelectPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    GestureEventFunc callback = [weak = WeakClaim(this)](GestureEvent& /* info */) mutable {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);

        auto selected = pattern->GetSelected();
        if (selected > -1 && selected < static_cast<int32_t>(pattern->GetOptions().size())) {
            pattern->UpdateSelectedProps(selected);
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
        CHECK_NULL_VOID(selectLayoutProps);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        if (theme->GetExpandDisplay() && selectLayoutProps->GetShowInSubWindowValue(false) &&
            NG::ViewAbstractModelNG::CheckSkipMenuShow(host)) {
            return;
        }
        pattern->ShowSelectMenu();
    };
    auto gestureHub = host->GetOrCreateGestureEventHub();
    if (!gestureHub->GetTouchable()) {
        return;
    }
    gestureHub->BindMenu(std::move(callback));

    auto targetNode = RawPtr(host);
    CHECK_NULL_VOID(targetNode);
    BindMenuTouch(targetNode, gestureHub);
}

void SelectPattern::BindMenuTouch(FrameNode* targetNode, const RefPtr<GestureEventHub>& gestrueHub)
{
    CHECK_NULL_VOID(targetNode);
    auto weakTarget = AceType::WeakClaim(targetNode);
    auto touchCallback = [weakTarget](const TouchEventInfo& info) {
        auto targetNode = weakTarget.Upgrade();
        CHECK_NULL_VOID(targetNode);
        const auto& touches = info.GetTouches();
        CHECK_EQUAL_VOID(touches.empty(), true);
        auto touchType = touches.front().GetTouchType();
        auto targetId = targetNode->GetId();
        auto subwindow =
            SubwindowManager::GetInstance()->GetSubwindowByType(Container::CurrentId(), SubwindowType::TYPE_MENU);
        CHECK_NULL_VOID(subwindow);
        auto childContainerId = subwindow->GetChildContainerId();
        auto childContainer = AceEngine::Get().GetContainer(childContainerId);
        CHECK_NULL_VOID(childContainer);
        auto subwindowPipline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
        CHECK_NULL_VOID(subwindowPipline);
        auto subwindowOverlay = subwindowPipline->GetOverlayManager();
        CHECK_NULL_VOID(subwindowOverlay);
        if (touchType == TouchType::DOWN) {
            auto wrapperNode = subwindowOverlay->GetMenuNode(targetId);
            CHECK_NULL_VOID(wrapperNode);
            auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_VOID(wrapperPattern);
            if (wrapperPattern->IsShow() || wrapperPattern->GetMenuStatus() == MenuStatus::ON_HIDE_ANIMATION) {
                subwindowOverlay->SkipMenuShow(targetId);
            }
        } else if ((touchType == TouchType::UP || touchType == TouchType::CANCEL) &&
                   subwindowOverlay->CheckSkipMenuShow(targetId)) {
            auto weakOverlay = AceType::WeakClaim(AceType::RawPtr(subwindowOverlay));
            auto taskExecutor = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weakOverlay, targetId]() mutable {
                    auto subwindowOverlay = weakOverlay.Upgrade();
                    CHECK_NULL_VOID(subwindowOverlay);
                    subwindowOverlay->ResumeMenuShow(targetId);
                },
                TaskExecutor::TaskType::PLATFORM, "ArkUIResumeMenuShow");
        }
    };
    gestrueHub->RegisterMenuOnTouch(touchCallback);
}

bool SelectPattern::CheckSkipMenuShow(const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, false);
    auto subwindow =
        SubwindowManager::GetInstance()->GetSubwindowByType(Container::CurrentId(), SubwindowType::TYPE_MENU);
    CHECK_NULL_RETURN(subwindow, false);
    auto childContainerId = subwindow->GetChildContainerId();
    auto childContainer = AceEngine::Get().GetContainer(childContainerId);
    CHECK_NULL_RETURN(childContainer, false);
    auto subwindowPipline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
    CHECK_NULL_RETURN(subwindowPipline, false);
    auto subwindowOverlay = subwindowPipline->GetOverlayManager();
    CHECK_NULL_RETURN(subwindowOverlay, false);
    return subwindowOverlay->CheckSkipMenuShow(targetNode->GetId());
}

void SelectPattern::PlayBgColorAnimation(bool isHoverChange)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);

    AnimationOption option = AnimationOption();
    if (isHoverChange) {
        option.SetDuration(selectTheme->GetHoverAnimationDuration());
        option.SetCurve(Curves::FRICTION);
    } else {
        option.SetDuration(selectTheme->GetPressAnimationDuration());
        option.SetCurve(Curves::SHARP);
    }

    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->BlendBgColor(pattern->GetBgBlendColor());
    }, nullptr, nullptr, pipeline);
}

// change background color when hovered
void SelectPattern::RegisterOnHover()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseCallback = [weak = WeakClaim(this)](bool isHover) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "select mouse hover %{public}d", isHover);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsHover(isHover);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto* pipeline = host->GetContextWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        auto selectRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(selectRenderContext);
        // update hover status, repaint background color
        if (isHover) {
            float scaleHover = theme->GetSelectHoverOrFocusedScale();
            VectorF scale(scaleHover, scaleHover);
            auto&& transform = selectRenderContext->GetOrCreateTransform();
            CHECK_NULL_VOID(transform);
            if (!transform->HasTransformScale() || transform->GetTransformScale() == scale) {
                selectRenderContext->SetScale(scaleHover, scaleHover);
            }
            pattern->SetBgBlendColor(theme->GetHoverColor());
        } else {
            selectRenderContext->SetScale(1.0f, 1.0f);
            pattern->SetBgBlendColor(Color::TRANSPARENT);
        }
        pattern->PlayBgColorAnimation();
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseCallback));
    inputHub->AddOnHoverEvent(mouseEvent);
}

// change background color when pressed
void SelectPattern::RegisterOnPress()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<SelectEventHub>();
    CHECK_NULL_VOID(eventHub);
    std::function<void(UIState)> callback = [weak = WeakClaim(this)](const UIState& state) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        const auto& renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        // update press status, repaint background color
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "select touch type %{public}zu", (size_t)state);
        if (state == UI_STATE_PRESSED) {
            pattern->SetBgBlendColor(theme->GetClickedColor());
            pattern->PlayBgColorAnimation(false);
        }
        if (state == UI_STATE_NORMAL) {
            if (pattern->IsHover()) {
                pattern->SetBgBlendColor(theme->GetHoverColor());
            } else {
                pattern->SetBgBlendColor(Color::TRANSPARENT);
            }
            pattern->PlayBgColorAnimation(false);
        }
    };
    eventHub->AddSupportedUIStateWithCallback(UI_STATE_PRESSED | UI_STATE_NORMAL, callback, true);
}

void SelectPattern::CreateSelectedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto callback = [weak = WeakClaim(RawPtr(host))](int32_t index) {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern<SelectPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSelected(index);
        pattern->UpdateText(index);
        pattern->isSelected_ = true;
        auto hub = host->GetEventHub<SelectEventHub>();
        CHECK_NULL_VOID(hub);
        // execute change event callback
        if (index >= static_cast<int32_t>(pattern->options_.size()) || index < 0) {
            return;
        }
        auto selectChangeEvent = hub->GetSelectChangeEvent();
        if (selectChangeEvent) {
            selectChangeEvent(index);
        }
        auto valueChangeEvent = hub->GetValueChangeEvent();
        if (valueChangeEvent) {
            auto newSelected = pattern->options_[index]->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(newSelected);
            valueChangeEvent(newSelected->GetText());
        }
        // execute onSelect callback
        auto newSelected = pattern->options_[index]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(newSelected);
        auto value = newSelected->GetText();
        auto onSelect = hub->GetSelectEvent();
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "select choice index %{public}d", index);
        if (onSelect) {
            onSelect(index, value);
        }
        RecordChange(host, index, value);
    };
    for (auto&& option : options_) {
        auto hub = option->GetEventHub<MenuItemEventHub>();
        // no std::move, need to set multiple options
        hub->SetOnSelect(callback);
        option->MarkModifyDone();
    }
}

void SelectPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(selectRenderContext);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto isApplyFocusedStyle = selectTheme->GetoptionApplyFocusedStyle();
    if (!isApplyFocusedStyle) {
        return;
    }
    CHECK_NULL_VOID(!focusEventInitialized_);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusStyleTask();
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurStyleTask();
    };
    focusHub->SetOnBlurInternal(blurTask);
    focusEventInitialized_ = true;
}

void SelectPattern::HandleFocusStyleTask()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    AddIsFocusActiveUpdateEvent();

    if (pipeline->GetIsFocusActive()) {
        SetFocusStyle();
    }
}

void SelectPattern::HandleBlurStyleTask()
{
    RemoveIsFocusActiveUpdateEvent();
    ClearFocusStyle();
}

void SelectPattern::SetFocusStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(selectRenderContext);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(selectTheme);
    auto&& graphics = selectRenderContext->GetOrCreateGraphics();
    CHECK_NULL_VOID(graphics);
    auto&& transform = selectRenderContext->GetOrCreateTransform();
    CHECK_NULL_VOID(transform);

    ShadowStyle shadowStyle = selectTheme->GetSelectNormalShadow();
    Shadow shadow;
    GetShadowFromTheme(shadowStyle, shadow);
    if (!graphics->HasBackShadow() || graphics->GetBackShadowValue() == shadow) {
        shadowModify_ = true;
        shadowStyle = selectTheme->GetSelectFocusedShadow();
        GetShadowFromTheme(shadowStyle, shadow);
        selectRenderContext->UpdateBackShadow(shadow);
    }
    float scaleFocus = selectTheme->GetSelectHoverOrFocusedScale();
    VectorF scale(scaleFocus, scaleFocus);
    if (!transform->HasTransformScale() || transform->GetTransformScale() == scale) {
        scaleModify_ = true;
        selectRenderContext->SetScale(scaleFocus, scaleFocus);
    }
    Color color = selectTheme->GetButtonBackgroundColor();
    bgColorModify_ = selectRenderContext->GetBackgroundColor() == color;
    if (bgColorModify_) {
        selectRenderContext->UpdateBackgroundColor(selectTheme->GetSelectFocusedBackground());
    }
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    focusTextColorModify_ = props->GetTextColor() == selectTheme->GetFontColor();
    if (focusTextColorModify_) {
        props->UpdateTextColor(selectTheme->GetSelectFocusTextColor());
        auto textRenderContext = text_->GetRenderContext();
        CHECK_NULL_VOID(textRenderContext);
        textRenderContext->UpdateForegroundColor(selectTheme->GetSelectFocusTextColor());
        text_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    ModFocusIconStyle(selectTheme, true);
}

void SelectPattern::ClearFocusStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(selectRenderContext);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(selectTheme);

    if (shadowModify_) {
        ShadowStyle shadowStyle = selectTheme->GetSelectNormalShadow();
        Shadow shadow;
        GetShadowFromTheme(shadowStyle, shadow);
        selectRenderContext->UpdateBackShadow(shadow);
        shadowModify_ = false;
    }

    if (scaleModify_) {
        scaleModify_ = false;
        selectRenderContext->SetScale(1.0f, 1.0f);
    }
    if (bgColorModify_) {
        bgColorModify_ = false;
        Color color = selectTheme->GetButtonBackgroundColor();
        selectRenderContext->UpdateBackgroundColor(color);
    }
    if (focusTextColorModify_) {
        focusTextColorModify_ = false;
        auto props = text_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateTextColor(selectTheme->GetFontColor());
        auto textRenderContext = text_->GetRenderContext();
        CHECK_NULL_VOID(textRenderContext);
        textRenderContext->UpdateForegroundColor(selectTheme->GetFontColor());
        text_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    ModFocusIconStyle(selectTheme, false);
}

void SelectPattern::ModFocusIconStyle(RefPtr<SelectTheme> selectTheme, bool focusedFlag)
{
    auto spinnerLayoutProperty = spinner_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(spinnerLayoutProperty);
    focusedFlag ? spinnerLayoutProperty->UpdateSymbolColorList({selectTheme->GetSpinnerFocusedSymbolColor()}) :
        spinnerLayoutProperty->UpdateSymbolColorList({selectTheme->GetSpinnerSymbolColor()});
    spinner_->MarkDirtyNode();
}

void SelectPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto selectPattern = weak.Upgrade();
            CHECK_NULL_VOID(selectPattern);
            isFocusAcitve ? selectPattern->SetFocusStyle() : selectPattern->ClearFocusStyle();
        };
    }

    auto pipline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipline);
    pipline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void SelectPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto pipline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipline);
    pipline->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void SelectPattern::RegisterOnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool SelectPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_ENTER) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto focusHub = host->GetOrCreateFocusHub();
        CHECK_NULL_RETURN(focusHub, false);
        focusHub->OnClick(event);
        return true;
    }
    return false;
}

void SelectPattern::SetDisabledStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(theme);

    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProps);
    textProps->UpdateTextColor(theme->GetDisabledFontColor());
    text_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        auto spinnerLayoutProperty = spinner_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(spinnerLayoutProperty);
        spinnerLayoutProperty->UpdateSymbolColorList({theme->GetDisabledSpinnerSymbolColor()});
    } else {
        auto spinnerLayoutProperty = spinner_->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(spinnerLayoutProperty);

        ImageSourceInfo imageSourceInfo = spinnerLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo());
        auto iconTheme = pipeline->GetTheme<IconTheme>();
        CHECK_NULL_VOID(iconTheme);
        auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::SPINNER_DISABLE);
        imageSourceInfo.SetSrc(iconPath);
        if (imageSourceInfo.IsSvg()) {
            imageSourceInfo.SetFillColor(theme->GetDisabledSpinnerColor());
        }
        spinnerLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        auto spinnerRenderProperty = spinner_->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(spinnerRenderProperty);
        spinnerRenderProperty->UpdateSvgFillColor(theme->GetDisabledSpinnerColor());
    }
    spinner_->MarkModifyDone();

    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBackgroundColor(renderContext->GetBackgroundColor()
                                                 .value_or(theme->GetButtonBackgroundColor())
                                                 .BlendOpacity(theme->GetDisabledFontColorAlpha()));
    }
}

void SelectPattern::SetSelected(int32_t index)
{
    // if option is already selected, do nothing
    if (index == selected_) {
        return;
    }
    if (index >= static_cast<int32_t>(options_.size()) || index < 0) {
        selected_ = -1;
        ResetOptionProps();
        return;
    }
    UpdateLastSelectedProps(index);
    selected_ = index;
    for (size_t i = 0; i < options_.size(); ++i) {
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        if (pattern) {
            pattern->SetSelected(selected_);
        }
    }
}

void SelectPattern::AddOptionNode(const RefPtr<FrameNode>& option)
{
    CHECK_NULL_VOID(option);
    options_.push_back(option);
}

void SelectPattern::BuildChild()
{
    auto select = GetHost();
    CHECK_NULL_VOID(select);
    // get theme from SelectThemeManager
    auto* pipeline = select->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    CHECK_NULL_VOID(theme);

    bool hasRowNode = HasRowNode();
    auto rowId = GetRowId();
    auto row = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowId, []() { return AceType::MakeRefPtr<MenuItemRowPattern>(); });
    CHECK_NULL_VOID(row);
    if (textApply_ && textId_.has_value()) {
        if (hasRowNode) {
            row->RemoveChild(text_);
            textId_.reset();
        }
    }
    if ((arrowApply_ && SystemProperties::IsNeedSymbol() && spinnerId_.has_value()) ||
        (textApply_ && !arrowApply_ && spinnerId_.has_value())) {
        if (hasRowNode) {
            row->RemoveChild(spinner_);
            spinnerId_.reset();
        }
    }
    bool hasTextNode = HasTextNode();
    bool hasSpinnerNode = HasSpinnerNode();
    auto textId = GetTextId();
    auto spinnerId = GetSpinnerId();

    row->SetInternal();
    auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_VOID(rowProps);
    rowProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    rowProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    rowProps->UpdateFlexDirection(FlexDirection::ROW);
    rowProps->UpdateSpace(theme->GetContentSpinnerPadding());
    text_ =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, textId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(text_);
    text_->SetInternal();
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProps);
    InitTextProps(textProps);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        spinner_ = FrameNode::GetOrCreateFrameNode(
            V2::SYMBOL_ETS_TAG, spinnerId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(spinner_);
        spinner_->SetInternal();
        InitSpinner(spinner_, theme);
    } else {
        spinner_ = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, spinnerId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
        CHECK_NULL_VOID(spinner_);
        spinner_->SetInternal();
        auto iconTheme = pipeline->GetTheme<IconTheme>();
        CHECK_NULL_VOID(iconTheme);
        InitSpinner(spinner_, iconTheme, theme);
    }
    // mount triangle and text
    text_->MarkModifyDone();
    if (!hasTextNode) {
        text_->MountToParent(row);
    }
    spinner_->MarkModifyDone();
    if (!hasSpinnerNode) {
        spinner_->MountToParent(row);
    }
    if (!hasRowNode) {
        row->MountToParent(select);
    }
    row->MarkModifyDone();
    row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    // set bgColor and border
    auto renderContext = select->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!renderContext->HasBorderColor()) {
        BorderColorProperty borderColor;
        borderColor.SetColor(theme->GetSelectNormalBorderColor());
        renderContext->UpdateBorderColor(borderColor);
    }
    if (!renderContext->HasBorderWidth()) {
        auto layoutProperty = select->GetLayoutProperty();
        BorderWidthProperty borderWidth;
        borderWidth.SetBorderWidth(theme->GetSelectNormalBorderWidth());
        layoutProperty->UpdateBorderWidth(borderWidth);
        renderContext->UpdateBorderWidth(borderWidth);
    }
    if (!renderContext->HasBackShadow()) {
        ShadowStyle shadowStyle = theme->GetSelectNormalShadow();
        Shadow shadow;
        GetShadowFromTheme(shadowStyle, shadow);
        renderContext->UpdateBackShadow(shadow);
    }
    renderContext->SetClipToFrame(true);
    BorderRadiusProperty border;
    border.SetRadius(theme->GetSelectBorderRadius());
    renderContext->UpdateBorderRadius(border);
}

void SelectPattern::SetValue(const std::string& value)
{
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateContent(value);
    auto pattern = text_->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    auto modifier = pattern->GetContentModifier();
    CHECK_NULL_VOID(modifier);
    modifier->ContentChange();
    selectValue_ = value;
}

void SelectPattern::SetFontSize(const Dimension& value)
{
    if (value.IsNegative()) {
        return;
    }
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateFontSize(value);
}

void SelectPattern::SetItalicFontStyle(const Ace::FontStyle& value)
{
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateItalicFontStyle(value);
}

void SelectPattern::SetFontWeight(const FontWeight& value)
{
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateFontWeight(value);
}

void SelectPattern::SetFontFamily(const std::vector<std::string>& value)
{
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateFontFamily(value);
}

void SelectPattern::SetFontColor(const Color& color)
{
    fontColor_ = color;
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateTextColor(color);
    auto context = text_->GetRenderContext();
    context->UpdateForegroundColor(color);
    context->UpdateForegroundColorFlag(false);
    context->ResetForegroundColorStrategy();
}

void SelectPattern::SetOptionBgColor(const Color& color)
{
    optionBgColor_ = color;
    if (!optionBgColor_.has_value()) {
        return;
    }
    for (const auto& option : options_) {
        auto paintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdateOptionBgColor(optionBgColor_.value());
    }
}

void SelectPattern::SetOptionFontSize(const Dimension& value)
{
    optionFont_.FontSize = value;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (static_cast<int32_t>(i) == selected_ && selectedFont_.FontSize.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontSize(value);
    }
}

void SelectPattern::SetOptionItalicFontStyle(const Ace::FontStyle& value)
{
    optionFont_.FontStyle = value;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (static_cast<int32_t>(i) == selected_ && selectedFont_.FontStyle.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetItalicFontStyle(value);
    }
}

void SelectPattern::SetOptionFontWeight(const FontWeight& value)
{
    optionFont_.FontWeight = value;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (static_cast<int32_t>(i) == selected_ && selectedFont_.FontWeight.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontWeight(value);
    }
}

void SelectPattern::SetOptionFontFamily(const std::vector<std::string>& value)
{
    optionFont_.FontFamily = value;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (static_cast<int32_t>(i) == selected_ && selectedFont_.FontFamily.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontFamily(value);
    }
}

void SelectPattern::SetOptionFontColor(const Color& color)
{
    optionFont_.FontColor = color;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (optionFont_.FontColor.has_value()) {
            auto paintProperty = options_[i]->GetPaintProperty<MenuItemPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            paintProperty->UpdateOptionFontColor(optionFont_.FontColor.value());
        }

        if (static_cast<int32_t>(i) == selected_ && selectedFont_.FontColor.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetOptionFontColor(color);
    }
}

// set props of option node when selected
void SelectPattern::SetSelectedOptionBgColor(const Color& color)
{
    selectedBgColor_ = color;
    if (!selectedBgColor_.has_value()) {
        return;
    }
    for (const auto& option : options_) {
        auto paintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdateSelectedOptionBgColor(selectedBgColor_.value());
    }
}

void SelectPattern::SetSelectedOptionFontSize(const Dimension& value)
{
    selectedFont_.FontSize = value;
    if (selected_ >= 0 && selected_ < static_cast<int32_t>(options_.size())) {
        auto pattern = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontSize(value);
    }
}

void SelectPattern::SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value)
{
    selectedFont_.FontStyle = value;
    if (selected_ >= 0 && selected_ < static_cast<int32_t>(options_.size())) {
        auto pattern = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetItalicFontStyle(value);
    }
}

void SelectPattern::SetSelectedOptionFontWeight(const FontWeight& value)
{
    selectedFont_.FontWeight = value;
    if (selected_ >= 0 && selected_ < static_cast<int32_t>(options_.size())) {
        auto pattern = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontWeight(value);
    }
}

void SelectPattern::SetSelectedOptionFontFamily(const std::vector<std::string>& value)
{
    selectedFont_.FontFamily = value;
    if (selected_ >= 0 && selected_ < static_cast<int32_t>(options_.size())) {
        auto pattern = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontFamily(value);
    }
}

void SelectPattern::SetSelectedOptionFontColor(const Color& color)
{
    selectedFont_.FontColor = color;
    if (!selectedFont_.FontColor.has_value()) {
        return;
    }
    for (const auto& option : options_) {
        auto paintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdateSelectedOptionFontColor(selectedFont_.FontColor.value());
    }
}

const std::vector<RefPtr<FrameNode>>& SelectPattern::GetOptions()
{
    return options_;
}

void SelectPattern::ResetOptionToInitProps(
    const RefPtr<MenuItemPattern>& optionPattern, const RefPtr<MenuItemPattern>& selectingOptionPattern)
{
    if (textOptionApply_) {
        optionPattern->SetOptionTextModifier(textOptionApply_);
    } else if (textSelectOptionApply_ && !textOptionApply_) {
        optionPattern->ResetSelectTextProps();
        optionPattern->ApplyOptionThemeStyles();
    } else {
        optionPattern->ApplyOptionThemeStyles();
    }
    if (selectingOptionPattern) {
        optionPattern->SetBgColor(selectingOptionPattern->GetBgColor());
    }
}

void SelectPattern::UpdateOptionCustomProperties(const RefPtr<MenuItemPattern>& optionPattern)
{
    if (optionFont_.FontColor.has_value()) {
        optionPattern->SetFontColor(optionFont_.FontColor.value());
    }
    if (optionFont_.FontFamily.has_value()) {
        optionPattern->SetFontFamily(optionFont_.FontFamily.value());
    }
    if (optionFont_.FontSize.has_value()) {
        optionPattern->SetFontSize(optionFont_.FontSize.value());
    }
    if (optionFont_.FontStyle.has_value()) {
        optionPattern->SetItalicFontStyle(optionFont_.FontStyle.value());
    }
    if (optionFont_.FontWeight.has_value()) {
        optionPattern->SetFontWeight(optionFont_.FontWeight.value());
    }
    if (optionBgColor_.has_value()) {
        optionPattern->SetBgColor(optionBgColor_.value());
    }
}

void SelectPattern::ResetSelectedOptionToInitProps(const RefPtr<MenuItemPattern>& optionPattern)
{
    if (textSelectOptionApply_) {
        optionPattern->SetSelectedOptionTextModifier(textSelectOptionApply_);
    } else if (!textSelectOptionApply_ && textOptionApply_) {
        optionPattern->ResetSelectTextProps();
        optionPattern->ApplySelectedThemeStyles();
    } else {
        optionPattern->ApplySelectedThemeStyles();
    }
}

void SelectPattern::UpdateSelectedOptionCustomProperties(const RefPtr<MenuItemPattern>& optionPattern)
{
    if (selectedFont_.FontColor.has_value()) {
        optionPattern->SetFontColor(selectedFont_.FontColor.value());
    }
    if (selectedFont_.FontFamily.has_value()) {
        optionPattern->SetFontFamily(selectedFont_.FontFamily.value());
    } else if (optionFont_.FontFamily.has_value()) {
        optionPattern->SetFontFamily(optionFont_.FontFamily.value());
    }
    if (selectedFont_.FontSize.has_value()) {
        optionPattern->SetFontSize(selectedFont_.FontSize.value());
    } else if (optionFont_.FontSize.has_value()) {
        optionPattern->SetFontSize(optionFont_.FontSize.value());
    }
    if (selectedFont_.FontStyle.has_value()) {
        optionPattern->SetItalicFontStyle(selectedFont_.FontStyle.value());
    } else if (optionFont_.FontStyle.has_value()) {
        optionPattern->SetItalicFontStyle(optionFont_.FontStyle.value());
    }
    if (selectedFont_.FontWeight.has_value()) {
        optionPattern->SetFontWeight(selectedFont_.FontWeight.value());
    } else if (optionFont_.FontWeight.has_value()) {
        optionPattern->SetFontWeight(optionFont_.FontWeight.value());
    }
    if (selectedBgColor_.has_value()) {
        optionPattern->SetBgColor(selectedBgColor_.value());
    }
}

void SelectPattern::ResetLastSelectedOptionFlags(const RefPtr<MenuItemPattern>& optionPattern)
{
    CHECK_NULL_VOID(optionPattern);
    optionPattern->SetSelected(false);
    optionPattern->UpdateNextNodeDivider(true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
    CHECK_NULL_VOID(selectLayoutProps);
    if (selectLayoutProps->GetShowDefaultSelectedIconValue(false)) {
        optionPattern->SetCheckMarkVisibleType(VisibleType::INVISIBLE);
    }
}

void SelectPattern::ResetOptionProps()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
    for (const auto& option : options_) {
        auto pattern = option->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSelected(false);
        ResetOptionToInitProps(pattern);
        UpdateOptionCustomProperties(pattern);
        if (selectLayoutProps && selectLayoutProps->GetShowDefaultSelectedIconValue(false)) {
            pattern->SetCheckMarkVisibleType(VisibleType::INVISIBLE);
        }
    }
}

void SelectPattern::UpdateComponentColor(const Color& color, const SelectColorType selectColorType)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (pipelineContext->IsSystmColorChange()) {
        switch (selectColorType) {
            case SelectColorType::FONT_COLOR:
                SetFontColor(color);
                text_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
                break;
            case SelectColorType::BACKGROUND_COLOR:
                renderContext->UpdateBackgroundColor(color);
                break;
            case SelectColorType::SELECTED_OPTION_BG_COLOR:
                SetSelectedOptionBgColor(color);
                host->MarkModifyDone();
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                break;
            case SelectColorType::SELECTED_OPTION_FONT_COLOR:
                SetSelectedOptionFontColor(color);
                host->MarkModifyDone();
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                break;
            case SelectColorType::OPTION_BG_COLOR:
                SetOptionBgColor(color);
                host->MarkModifyDone();
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                break;
            case SelectColorType::OPTION_FONT_COLOR:
                SetOptionFontColor(color);
                host->MarkModifyDone();
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                break;
            case SelectColorType::MENU_BACKGROUND_COLOR:
                SetMenuBackgroundColor(color);
                host->MarkModifyDone();
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                break;
            default:
                break;
        }
    }

    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void SelectPattern::UpdateMenuOption(int32_t index, const std::string& value, const SelectOptionType optionType)
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    switch (optionType) {
        case SelectOptionType::TEXT:
            menuPattern->UpdateSelectOptionTextByIndex(index, value);
            break;
        case SelectOptionType::ICON:
            menuPattern->UpdateSelectOptionIconByIndex(index, value);
            break;
        default:
            break;
    }
    menu->MarkModifyDone();
    menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SelectPattern::UpdateLastSelectedProps(int32_t index)
{
    CHECK_NULL_VOID(options_[index]);
    auto newSelected = options_[index]->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(newSelected);
    // set lastSelected option props back to default (unselected) values
    if (selected_ >= 0 && selected_ < static_cast<int32_t>(options_.size())) {
        CHECK_NULL_VOID(options_[selected_]);
        auto lastSelected = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(lastSelected);
        ResetOptionToInitProps(lastSelected, newSelected);
        UpdateOptionCustomProperties(lastSelected);
        ResetLastSelectedOptionFlags(lastSelected);
        if (optionFont_.FontColor.has_value()) {
            lastSelected->SetOptionFontColor(optionFont_.FontColor.value());
        }
        if (selected_ != 0) {
            auto lastSelectedNode = lastSelected->GetHost();
            CHECK_NULL_VOID(lastSelectedNode);
            auto lastSelectedPros = lastSelectedNode->GetPaintProperty<MenuItemPaintProperty>();
            CHECK_NULL_VOID(lastSelectedPros);
            lastSelectedPros->UpdateNeedDivider(true);
        }
        options_[selected_]->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    }
}

void SelectPattern::SetShowInSubWindow(bool isShowInSubWindow)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
    CHECK_NULL_VOID(selectLayoutProps);
    selectLayoutProps->UpdateShowInSubWindow(isShowInSubWindow);
    auto menuNode = GetMenuNode();
    CHECK_NULL_VOID(menuNode);
    auto menuLayoutProps = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateShowInSubWindow(isShowInSubWindow);
}

void SelectPattern::ResetShowInSubWindow()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    bool isExpandDisplay = selectTheme->GetExpandDisplay();
    bool isShowInSubWindow = isExpandDisplay;
    SetShowInSubWindow(isShowInSubWindow);
}

void SelectPattern::SetShowDefaultSelectedIcon(bool show)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
    CHECK_NULL_VOID(selectLayoutProps);
    selectLayoutProps->UpdateShowDefaultSelectedIcon(show);
    auto menuNode = GetMenuNode();
    CHECK_NULL_VOID(menuNode);
    auto menuLayoutProps = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateShowDefaultSelectedIcon(show);
    for (size_t i = 0; i < options_.size(); ++i) {
        auto menuItemPattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(menuItemPattern);
        menuItemPattern->SetShowDefaultSelectedIcon(show);
    }
    if (show) {
        ResetOptionProps();
    }
}

void SelectPattern::ResetShowDefaultSelectedIcon()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
    CHECK_NULL_VOID(selectLayoutProps);
    selectLayoutProps->ResetShowDefaultSelectedIcon();
    auto menuNode = GetMenuNode();
    CHECK_NULL_VOID(menuNode);
    auto menuLayoutProps = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->ResetShowDefaultSelectedIcon();
    for (size_t i = 0; i < options_.size(); ++i) {
        auto menuItemPattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(menuItemPattern);
        menuItemPattern->SetShowDefaultSelectedIcon(false);
    }
}

// update selected option props
void SelectPattern::UpdateSelectedProps(int32_t index)
{
    CHECK_NULL_VOID(options_[index]);
    auto newSelected = options_[index]->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(newSelected);

    // set newSelected props
    ResetSelectedOptionToInitProps(newSelected);
    UpdateSelectedOptionCustomProperties(newSelected);
    newSelected->SetSelected(true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
    if (selectLayoutProps && selectLayoutProps->GetShowDefaultSelectedIconValue(false)) {
        newSelected->SetCheckMarkVisibleType(VisibleType::VISIBLE);
        if (index != static_cast<int32_t>(GetOptions().size()) - 1) {
            newSelected->UpdateNextNodeDivider(true);
        }
        if (index != FIRST_NODE_INDEX) {
            auto newSelectedNode = newSelected->GetHost();
            CHECK_NULL_VOID(newSelectedNode);
            auto newSelectedPros = newSelectedNode->GetPaintProperty<MenuItemPaintProperty>();
            CHECK_NULL_VOID(newSelectedPros);
            newSelectedPros->UpdateNeedDivider(true);
        }
        return;
    }
    newSelected->UpdateNextNodeDivider(false);
    auto newSelectedNode = newSelected->GetHost();
    CHECK_NULL_VOID(newSelectedNode);
    auto newSelectedPros = newSelectedNode->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(newSelectedPros);
    newSelectedPros->UpdateNeedDivider(false);
}

void SelectPattern::UpdateText(int32_t index)
{
    // update text to selected option's text
    CHECK_NULL_VOID(text_);
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProps);
    if (index >= static_cast<int32_t>(options_.size()) || index < 0) {
        return;
    }
    auto newSelected = options_[index]->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(newSelected);
    textProps->UpdateContent(newSelected->GetText());
    text_->MarkModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    selectValue_ = newSelected->GetText();
}

void SelectPattern::InitTextProps(const RefPtr<TextLayoutProperty>& textProps)
{
    auto select = GetHost();
    CHECK_NULL_VOID(select);
    auto* pipeline = select->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>(select->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    textProps->UpdateFontSize(theme->GetFontSize());
    textProps->UpdateFontWeight(FontWeight::MEDIUM);
    textProps->UpdateTextColor(theme->GetFontColor());
    textProps->UpdateTextDecoration({theme->GetTextDecoration()});
    textProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProps->UpdateMaxLines(SELECT_ITSELF_TEXT_LINES);
}

void SelectPattern::InitSpinner(
    const RefPtr<FrameNode>& spinner, const RefPtr<IconTheme>& iconTheme, const RefPtr<SelectTheme>& selectTheme)
{
    ImageSourceInfo imageSourceInfo;
    auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::SPINNER);
    imageSourceInfo.SetSrc(iconPath);
    imageSourceInfo.SetFillColor(selectTheme->GetSpinnerColor());

    auto spinnerLayoutProperty = spinner->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(spinnerLayoutProperty);
    spinnerLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    CalcSize idealSize = { CalcLength(selectTheme->GetSpinnerWidth()), CalcLength(selectTheme->GetSpinnerHeight()) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    spinnerLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
    auto spinnerRenderProperty = spinner->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(spinnerRenderProperty);
    spinnerRenderProperty->UpdateSvgFillColor(selectTheme->GetSpinnerColor());
}

void SelectPattern::InitSpinner(
    const RefPtr<FrameNode>& spinner, const RefPtr<SelectTheme>& selectTheme)
{
    auto spinnerLayoutProperty = spinner->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(spinnerLayoutProperty);
    uint32_t symbolId = selectTheme->GetSpinnerSource();
    spinnerLayoutProperty->UpdateSymbolSourceInfo(SymbolSourceInfo{symbolId});
    spinnerLayoutProperty->UpdateSymbolColorList({selectTheme->GetSpinnerSymbolColor()});
    spinnerLayoutProperty->UpdateFontSize(selectTheme->GetFontSize());
    spinnerLayoutProperty->UpdateSymbolRenderingStrategy(RENDERINGSTRATEGY_MULTIPLE_COLOR);
}

// XTS inspector code
void SelectPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        ToJsonArrowAndText(json, filter);
        ToJsonOptionAlign(json, filter);
        ToJsonMenuBackgroundStyle(json, filter);
        return;
    }
    json->PutExtAttr("options", InspectorGetOptions().c_str(), filter);
    json->PutExtAttr("selected", std::to_string(selected_).c_str(), filter);
    ToJsonArrowAndText(json, filter);
    json->PutExtAttr("selectedOptionBgColor", selectedBgColor_->ColorToString().c_str(), filter);
    ToJsonSelectedOptionFontAndColor(json, filter);
    if (options_.empty()) {
        json->PutExtAttr("optionBgColor", "", filter);
        json->PutExtAttr("optionFont", "", filter);
        json->PutExtAttr("optionFontColor", "", filter);
    } else {
        auto optionPattern = options_[0]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        auto bgColor = selected_ == 0 ? selectedBgColor_ : optionPattern->GetBgColor();
        json->PutExtAttr("optionBgColor", bgColor->ColorToString().c_str(), filter);
        json->PutExtAttr("optionFont", optionPattern->InspectorGetFont().c_str(), filter);
        auto fontColor =
            selected_ == 0 ? selectedFont_.FontColor.value_or(Color::BLACK) : optionPattern->GetFontColor();
        json->PutExtAttr("optionFontColor", fontColor.ColorToString().c_str(), filter);
    }
    ToJsonOptionAlign(json, filter);
    for (size_t i = 0; i < options_.size(); ++i) {
        auto optionPaintProperty = options_[i]->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(optionPaintProperty);
        std::string optionWidth = std::to_string(optionPaintProperty->GetSelectModifiedWidthValue(0.0f));
        json->PutExtAttr("optionWidth", optionWidth.c_str(), filter);
    }
    ToJsonOptionMaxlines(json, filter);
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    std::string optionHeight =  std::to_string(menuLayoutProps->GetSelectModifiedHeightValue(0.0f));
    json->PutExtAttr("optionHeight", optionHeight.c_str(), filter);
    ToJsonMenuBackgroundStyle(json, filter);
    ToJsonDivider(json, filter);
}

void SelectPattern::ToJsonSelectedOptionFontAndColor(std::unique_ptr<JsonValue>& json,
    const InspectorFilter& filter) const
{
    if (filter.IsFastFilter()) {
        return;
    }
    if (textSelectOptionApply_) {
        if (options_.empty() || options_.size() <= static_cast<size_t>(selected_)) {
            json->PutExtAttr("selectedOptionFont", InspectorGetSelectedFont().c_str(), filter);
            json->PutExtAttr("selectedOptionFontColor",
                selectedFont_.FontColor.value_or(Color::BLACK).ColorToString().c_str(), filter);
            return;
        }
        CHECK_NULL_VOID(options_[selected_]);
        auto optionPattern = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        json->PutExtAttr("selectedOptionFont", optionPattern->InspectorGetFont().c_str(), filter);
        json->PutExtAttr("selectedOptionFontColor", optionPattern->GetFontColor().ColorToString().c_str(), filter);
        return;
    }
    json->PutExtAttr("selectedOptionFont", InspectorGetSelectedFont().c_str(), filter);
    json->PutExtAttr(
        "selectedOptionFontColor", selectedFont_.FontColor.value_or(Color::BLACK).ColorToString().c_str(), filter);
}

void SelectPattern::ToJsonArrowAndText(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetChildren().empty()) {
        auto row = FrameNode::GetFrameNode(host->GetFirstChild()->GetTag(), host->GetFirstChild()->GetId());
        CHECK_NULL_VOID(row);
        auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
        CHECK_NULL_VOID(rowProps);
        json->PutExtAttr("space", rowProps->GetSpaceValue(Dimension()).ToString().c_str(), filter);

        if (rowProps->GetFlexDirection().value_or(FlexDirection::ROW) == FlexDirection::ROW) {
            json->PutExtAttr("arrowPosition", "ArrowPosition.END", filter);
        } else {
            json->PutExtAttr("arrowPosition", "ArrowPosition.START", filter);
        }
    }

    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    json->PutExtAttr("value", UtfUtils::Str16ToStr8(props->GetContent().value_or(u"")).c_str(), filter);
    Color fontColor = props->GetTextColor().value_or(Color::BLACK);
    json->PutExtAttr("fontColor", fontColor.ColorToString().c_str(), filter);
    json->PutExtAttr("font", props->InspectorGetTextFont().c_str(), filter);
    json->PutExtAttr("controlSize", ConvertControlSizeToString(controlSize_).c_str(), filter);
    auto maxLines = (props->GetMaxLines().has_value() ? std::to_string(props->GetMaxLines().value()) : "");
    json->PutExtAttr("maxLines", maxLines.c_str(), filter);
    if (arrowApply_ && spinner_->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolLayoutProperty = spinner_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        const std::unique_ptr<FontStyle>& symbolStyle = symbolLayoutProperty->GetFontStyle();
        CHECK_NULL_VOID(symbolStyle);
        auto fontSize = symbolStyle->GetFontSize();
        json->PutExtAttr("symbolFontSize", (fontSize.has_value() ? fontSize.value().ToString() : "").c_str(), filter);
        const std::optional<std::vector<Color>>& colorListOptional = symbolStyle->GetSymbolColorList();
        if (colorListOptional.has_value()) {
            std::string colorString = StringUtils::SymbolColorListToString(colorListOptional.value());
            json->PutExtAttr("symbolColorList", colorString.c_str(), filter);
        } else {
            json->PutExtAttr("symbolColorList", "", filter);
        }
    }
}

void SelectPattern::ToJsonMenuBackgroundStyle(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuRenderContext = menu->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    json->PutExtAttr("menuBackgroundColor",
        menuRenderContext->GetBackgroundColor()->ColorToString().c_str(), filter);
    if (menuRenderContext->GetBackBlurStyle().has_value()) {
        BlurStyleOption blurStyleOption = menuRenderContext->GetBackBlurStyle().value();
        auto jsonValue = JsonUtil::Create(true);
        blurStyleOption.ToJsonValue(jsonValue, filter);
        json->PutExtAttr("menuBackgroundBlurStyle",
            jsonValue->GetValue("backgroundBlurStyle")->GetValue("value"), filter);
    } else {
        json->PutExtAttr("menuBackgroundBlurStyle", "", filter);
    }
}

void SelectPattern::ToJsonDivider(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (options_.empty()) {
        json->PutExtAttr("divider", "", filter);
    } else {
        auto props = options_[0]->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(props);
        auto divider = JsonUtil::Create(true);
        if (props->HasDivider()) {
            divider->Put("strokeWidth", props->GetDividerValue().strokeWidth.ToString().c_str());
            divider->Put("startMargin", props->GetDividerValue().startMargin.ToString().c_str());
            divider->Put("endMargin", props->GetDividerValue().endMargin.ToString().c_str());
            divider->Put("color", props->GetDividerValue().color.ColorToString().c_str());
            ToJsonDividerMode(divider);
            json->PutExtAttr("divider", divider->ToString().c_str(), filter);
        } else {
            json->PutExtAttr("divider", "", filter);
        }
    }
}

void SelectPattern::ToJsonDividerMode(std::unique_ptr<JsonValue>& json) const
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    auto mode = menuLayoutProps->GetItemDividerMode();
    if (!mode.has_value()) {
        return;
    }
    if (mode.value() == DividerMode::FLOATING_ABOVE_MENU) {
        json->Put("dividerMode", "FLOATING_ABOVE_MENU");
    } else if (mode.value() == DividerMode::EMBEDDED_IN_MENU) {
        json->Put("dividerMode", "EMBEDDED_IN_MENU");
    }
}

void SelectPattern::ToJsonOptionMaxlines(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (!options_.empty()) {
        std::string optionMaxLines;
        for (size_t i = 0; i < options_.size(); ++i) {
            auto optionPattern = options_[i]->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(optionPattern);
            auto textNode = AceType::DynamicCast<FrameNode>(optionPattern->GetTextNode());
            CHECK_NULL_VOID(textNode);
            auto props = textNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(props);
            auto maxLines = (props->GetMaxLines().has_value() ? std::to_string(props->GetMaxLines().value()) : "");
            if (static_cast<int32_t>(i) == selected_) {
                json->PutExtAttr("selectedOptionMaxLines", maxLines.c_str(), filter);
            } else if (optionMaxLines.empty()) {
                optionMaxLines = maxLines;
            }
        }
        json->PutExtAttr("optionMaxLines", optionMaxLines.c_str(), filter);
    }
}

void SelectPattern::ToJsonOptionAlign(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto optionAlignJson = JsonUtil::Create(true);
    std::string alignTypeString = "MenuAlignType.Start";
    if (menuAlign_.alignType == MenuAlignType::START) {
        alignTypeString = "MenuAlignType.Start";
    } else if (menuAlign_.alignType == MenuAlignType::CENTER) {
        alignTypeString = "MenuAlignType.Center";
    } else if (menuAlign_.alignType == MenuAlignType::END) {
        alignTypeString = "MenuAlignType.End";
    }
    optionAlignJson->Put("alignType", alignTypeString.c_str());

    auto offsetValueJson = JsonUtil::Create(true);
    offsetValueJson->Put("dX", menuAlign_.offset.GetX().Value());
    offsetValueJson->Put("dY", menuAlign_.offset.GetY().Value());
    optionAlignJson->Put("offset", offsetValueJson);

    json->PutExtAttr("menuAlign", optionAlignJson, filter);
}

std::string SelectPattern::InspectorGetOptions() const
{
    auto jsonValue = JsonUtil::Create(true);
    auto jsonOptions = JsonUtil::CreateArray(true);
    for (size_t i = 0; i < options_.size(); ++i) {
        auto temp = JsonUtil::Create(true);
        auto optionPattern = options_[i]->GetPattern<MenuItemPattern>();
        temp->Put("value", optionPattern->GetText().c_str());
        temp->Put("icon", optionPattern->GetIcon().c_str());
        auto index = std::to_string(i);
        jsonOptions->Put(index.c_str(), temp);
    }
    jsonValue->Put("options", jsonOptions);
    return jsonValue->ToString();
}

std::string SelectPattern::InspectorGetSelectedFont() const
{
    TextStyle font;
    if (selectedFont_.FontFamily.has_value()) {
        font.SetFontFamilies(selectedFont_.FontFamily.value());
    }
    if (selectedFont_.FontSize.has_value()) {
        font.SetFontSize(selectedFont_.FontSize.value());
    }
    if (selectedFont_.FontStyle.has_value()) {
        font.SetFontStyle(selectedFont_.FontStyle.value());
    }
    if (selectedFont_.FontWeight.has_value()) {
        font.SetFontWeight(selectedFont_.FontWeight.value());
    }
    return V2::GetTextStyleInJson(font);
}

bool SelectPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    SetSelectSize(geometryNode->GetFrameSize());
    CHECK_NULL_RETURN(menuWrapper_, false);
    auto wrapperPattern = menuWrapper_->GetPattern<MenuWrapperPattern>();
    if (wrapperPattern && wrapperPattern->IsShow()) {
        UpdateTargetSize();
    }
    return false;
}

void SelectPattern::UpdateTargetSize()
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateTargetSize(selectSize_);
    if (isFitTrigger_) {
        auto selectWidth = selectSize_.Width();
        auto menuPattern = menu->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);
        menuPattern->SetIsWidthModifiedBySelect(true);
        menuLayoutProps->UpdateSelectMenuModifiedWidth(selectWidth);
        auto scroll = DynamicCast<FrameNode>(menu->GetFirstChild());
        CHECK_NULL_VOID(scroll);
        auto scrollPattern = scroll->GetPattern<ScrollPattern>();
        CHECK_NULL_VOID(scrollPattern);
        scrollPattern->SetIsWidthModifiedBySelect(true);
        auto scrollLayoutProps = scroll->GetLayoutProperty<ScrollLayoutProperty>();
        CHECK_NULL_VOID(scrollLayoutProps);
        scrollLayoutProps->UpdateScrollWidth(selectWidth);
        UpdateOptionsWidth(selectWidth);
    }
    menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SelectPattern::ShowScrollBar()
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto scroll = DynamicCast<FrameNode>(menu->GetFirstChild());
    CHECK_NULL_VOID(scroll);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->TriggerScrollBarDisplay();
}

void SelectPattern::SetSpace(const Dimension& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetChildren().empty()) {
        auto row = FrameNode::GetFrameNode(host->GetFirstChild()->GetTag(), host->GetFirstChild()->GetId());
        auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
        rowProps->UpdateSpace(value);
        row->MarkModifyDone();
        row->MarkDirtyNode();
    }
}

void SelectPattern::SetArrowPosition(const ArrowPosition value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetChildren().empty()) {
        auto row = FrameNode::GetFrameNode(host->GetFirstChild()->GetTag(), host->GetFirstChild()->GetId());
        auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();

        if (value == ArrowPosition::END) {
            rowProps->UpdateFlexDirection(FlexDirection::ROW);
        } else {
            rowProps->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
        }
        row->MarkModifyDone();
        row->MarkDirtyNode();
    }
}

std::string SelectPattern::GetValue()
{
    CHECK_NULL_RETURN(text_, "");
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProps, "");
    return UtfUtils::Str16ToStr8(textProps->GetContentValue(u""));
}

void SelectPattern::SetMenuAlign(const MenuAlign& menuAlign)
{
    menuAlign_ = menuAlign;
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateAlignType(menuAlign.alignType);
    menuLayoutProps->UpdateOffset(menuAlign.offset);
}

void SelectPattern::SetAvoidance(AvoidanceMode mode)
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateSelectAvoidanceMode(mode);
}

std::string SelectPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    jsonObj->Put("selected", selected_);
    jsonObj->Put("isSelected", isSelected_);
    return jsonObj->ToString();
}

void SelectPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("selected");
    auto jsonIsSelect = info->GetValue("isSelected");
    if (jsonIsSelect->GetBool()) {
        SetSelected(jsonIsOn->GetInt());
        UpdateText(jsonIsOn->GetInt());
    }
}

void SelectPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(selectTheme);

    auto pattern = host->GetPattern<SelectPattern>();
    auto menuNode = pattern->GetMenuNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto renderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && renderContext->IsUniRenderEnabled()) {
        renderContext->UpdateBackBlurStyle(renderContext->GetBackBlurStyle());
    } else {
        renderContext->UpdateBackgroundColor(selectTheme->GetBackgroundColor());
        if (!SystemProperties::ConfigChangePerform()) {
            SetOptionBgColor(selectTheme->GetBackgroundColor());
        }
    }

    auto optionNode = menuPattern->GetOptions();
    for (auto child : optionNode) {
        auto optionsPattern = child->GetPattern<MenuItemPattern>();
        optionsPattern->SetFontColor(selectTheme->GetFontColor());
        auto selectLayoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
        if (selectLayoutProps && selectLayoutProps->GetShowDefaultSelectedIconValue(false)) {
            optionsPattern->UpdateCheckMarkColor(selectTheme->GetCheckMarkColor());
        }

        child->MarkModifyDone();
        child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    UpdateMenuScrollColorConfiguration(menuNode);
    host->SetNeedCallChildrenUpdate(false);
    SetColorByUser(host, selectTheme);
}

void SelectPattern::SetMenuBackgroundColorByUser(const Color& color, const RefPtr<SelectPaintProperty>& props)
{
    CHECK_NULL_VOID(props);
    if (props->GetMenuBackgroundColorSetByUserValue(false)) {
        return;
    }
    SetMenuBackgroundColor(color);
}

void SelectPattern::SetOptionBgColorByUser(const Color& color, const RefPtr<SelectPaintProperty>& props)
{
    CHECK_NULL_VOID(props);
    if (props->GetOptionBgColorSetByUserValue(false)) {
        return;
    }
    optionBgColor_ = color;
    if (!optionBgColor_.has_value()) {
        return;
    }
    for (const auto& option : options_) {
        auto paintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdateOptionBgColor(optionBgColor_.value());
        option->MarkModifyDone();
        option->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    }
}

void SelectPattern::SetColorByUser(const RefPtr<FrameNode>& host, const RefPtr<SelectTheme>& theme)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(theme);
    auto props = host->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(props);
    auto themeBgcolor = theme->GetMenuBlendBgColor() ? theme->GetBackgroundColor() : Color::TRANSPARENT;
    SetMenuBackgroundColorByUser(themeBgcolor, props);
    SetOptionBgColorByUser(Color::TRANSPARENT, props);
    auto layoutProps = host->GetLayoutProperty<SelectLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    SetSelectedOptionBgColorByUser(theme, props, layoutProps);
    SetModifierByUser(theme, props);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SelectPattern::UpdateMenuScrollColorConfiguration(const RefPtr<FrameNode>& menuNode)
{
    CHECK_NULL_VOID(menuNode);
    auto scrollNode = AceType::DynamicCast<NG::FrameNode>(menuNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->OnColorConfigurationUpdate();
}

bool SelectPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    bool result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(themeScopeId);
    CHECK_NULL_RETURN(selectTheme, false);

    if (!fontColor_.has_value()) {
        ResetFontColor();
        text_->MarkDirtyNode();
        result = true;
    }

    auto selectRenderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(selectRenderContext, false);
    auto selectPaintProperty = host->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_RETURN(selectPaintProperty, false);
    if (!selectPaintProperty->HasBackgroundColor()) {
        selectRenderContext->UpdateBackgroundColor(selectTheme->GetButtonBackgroundColor());
        result = true;
    }
    return result;
}

void SelectPattern::OnLanguageConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto index = pattern->selected_;
            pattern->UpdateText(index);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto hub = host->GetEventHub<SelectEventHub>();
            CHECK_NULL_VOID(hub);
            if (index >= static_cast<int32_t>(pattern->options_.size()) || index < 0) {
                return;
            }
            auto newSelected = pattern->options_[index]->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(newSelected);
            auto value = newSelected->GetText();
            auto valueChangeEvent = hub->GetValueChangeEvent();
            if (valueChangeEvent) {
                valueChangeEvent(value);
            }
            auto onSelect = hub->GetSelectEvent();
            if (onSelect) {
                onSelect(index, value);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUISelectLanguageConfigUpdate");
}

Dimension SelectPattern::GetFontSize()
{
    Dimension defaultRet = Dimension();
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, defaultRet);
    auto host = props->GetHost();
    CHECK_NULL_RETURN(host, defaultRet);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, defaultRet);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, defaultRet);
    return props->GetFontSize().value_or(selectTheme->GetFontSize());
}

void SelectPattern::SetOptionWidth(const Dimension& value)
{
    isFitTrigger_ = false;
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetIsWidthModifiedBySelect(true);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateSelectMenuModifiedWidth(value.ConvertToPx() + OPTION_MARGIN.ConvertToPx());

    auto scroll = DynamicCast<FrameNode>(menu->GetFirstChild());
    CHECK_NULL_VOID(scroll);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->SetIsWidthModifiedBySelect(true);
    auto scrollLayoutProps = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(scrollLayoutProps);
    scrollLayoutProps->UpdateScrollWidth(value.ConvertToPx() + OPTION_MARGIN.ConvertToPx());

    for (size_t i = 0; i < options_.size(); ++i) {
        auto optionWidth = value.ConvertToPx();
        auto optionPattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        optionPattern->SetIsWidthModifiedBySelect(true);
        auto optionPaintProperty = options_[i]->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(optionPaintProperty);
        optionPaintProperty->UpdateSelectModifiedWidth(optionWidth);
    }
}

void SelectPattern::SetOptionWidthFitTrigger(bool isFitTrigger)
{
    isFitTrigger_ = isFitTrigger;
}

void SelectPattern::SetHasOptionWidth(bool hasOptionWidth)
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetHasOptionWidth(true);
    auto scroll = DynamicCast<FrameNode>(menu->GetFirstChild());
    CHECK_NULL_VOID(scroll);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->SetHasOptionWidth(true);
    for (size_t i = 0; i < options_.size(); ++i) {
        auto optionPattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        optionPattern->SetHasOptionWidth(true);
    }
}

void SelectPattern::SetOptionHeight(const Dimension& value)
{
    auto menuMaxHeight = value.ConvertToPx();
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetIsHeightModifiedBySelect(true);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateSelectModifiedHeight(menuMaxHeight);
}

void SelectPattern::SetMenuBackgroundColor(const Color& color)
{
    menuBackgroundColor_ = color;
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto renderContext = menu->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(color);
}

void SelectPattern::SetMenuBackgroundBlurStyle(const BlurStyleOption& blurStyle)
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto renderContext = menu->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackBlurStyle(blurStyle);
}

void SelectPattern::ResetParams()
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    auto select = GetHost();
    CHECK_NULL_VOID(select);
    auto* pipeline = select->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto layoutProperty = select->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(selectTheme->GetSelectMinWidth(controlSize_)),
        CalcLength(selectTheme->GetSelectDefaultHeight(controlSize_))));
    SetFontSize(selectTheme->GetFontSize(controlSize_));
    auto spinnerLayoutProperty = spinner_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(spinnerLayoutProperty);
    spinnerLayoutProperty->UpdateFontSize(selectTheme->GetFontSize(controlSize_));
    auto renderContext = select->GetRenderContext();
    BorderRadiusProperty border;
    border.SetRadius(selectTheme->GetSelectDefaultBorderRadius(controlSize_));
    renderContext->UpdateBorderRadius(border);

    NG::PaddingProperty paddings;
    paddings.top = std::nullopt;
    paddings.bottom = std::nullopt;
    if (controlSize_ == ControlSize::SMALL) {
        paddings.left = NG::CalcLength(SELECT_SMALL_PADDING_VP);
        paddings.right = NG::CalcLength(SELECT_SMALL_PADDING_VP);
    } else {
        paddings.left = NG::CalcLength(selectTheme->GetSelectNormalLeftRightMargin());
        paddings.right = NG::CalcLength(selectTheme->GetSelectNormalLeftRightMargin());
    }
    ViewAbstract::SetPadding(paddings);
}

void SelectPattern::SetControlSize(const ControlSize& controlSize)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    controlSize_ = controlSize;
    ResetParams();
}

void SelectPattern::SetLayoutDirection(TextDirection value)
{
    auto select = GetHost();
    auto menu = GetMenuNode();
    std::function<void (decltype(select))> updateDirectionFunc = [&](decltype(select) node) {
        if (!node) return;
        auto updateProperty = node->GetLayoutProperty();
        updateProperty->UpdateLayoutDirection(value);
        if (node->GetHostTag() == V2::SCROLL_ETS_TAG) {
            auto scrollPattern = AceType::DynamicCast<ScrollPattern>(node->GetPattern());
            if (scrollPattern) scrollPattern->TriggerModifyDone();
        }
        for (auto child : node->GetAllChildrenWithBuild()) {
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            if (!frameNode) continue;
            updateDirectionFunc(frameNode);
        }
    };
    updateDirectionFunc(select);
    updateDirectionFunc(menu);
}

ControlSize SelectPattern::GetControlSize()
{
    return controlSize_;
}

Dimension SelectPattern::GetSelectLeftRightMargin() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SELECT_MARGIN_VP);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, SELECT_MARGIN_VP);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, SELECT_MARGIN_VP);
    return selectTheme->GetSelectNormalLeftRightMargin();
}

bool SelectPattern::GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_RETURN(context, false);
    auto shadowTheme = context->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, false);
    auto colorMode = context->GetColorMode();
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

void SelectPattern::SetDivider(const SelectDivider& divider)
{
    for (auto&& option : options_) {
        auto props = option->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateDivider(divider);
        auto optionPattern = option->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        auto frameNode = optionPattern->GetBottomDivider();
        if (!frameNode) {
            continue;
        }
        auto dividerProperty = frameNode->GetPaintProperty<MenuDividerPaintProperty>();
        CHECK_NULL_VOID(dividerProperty);
        dividerProperty->UpdateStrokeWidth(divider.strokeWidth);
        dividerProperty->UpdateDividerColor(divider.color);
        dividerProperty->UpdateStartMargin(divider.startMargin);
        dividerProperty->UpdateEndMargin(divider.endMargin);
    }
}

void SelectPattern::ResetFontColor()
{
    if (fontColor_.has_value()) {
        fontColor_.reset();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(selectTheme);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateTextColor(selectTheme->GetFontColor());
    auto context = text_->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateForegroundColor(selectTheme->GetFontColor());
    context->UpdateForegroundColorFlag(false);
    context->ResetForegroundColorStrategy();
}

void SelectPattern::SetDividerMode(const std::optional<DividerMode>& mode)
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    if (mode.has_value()) {
        menuLayoutProps->UpdateItemDividerMode(mode.value());
    } else {
        menuLayoutProps->ResetItemDividerMode();
    }
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->UpdateMenuItemDivider();
}

void SelectPattern::SetMenuOutline(const MenuParam& menuParam)
{
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto renderContext = menu->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetOuterBorderWidth(menuParam.outlineWidth.value_or(BorderWidthProperty()));
    renderContext->SetOuterBorderColor(menuParam.outlineColor.value_or(BorderColorProperty()));
}

void SelectPattern::SetTextModifierApply(const std::function<void(WeakPtr<NG::FrameNode>)>& textApply)
{
    textApply_ = textApply;
    if (textApply) {
        auto textLayoutProperty = text_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        std::optional<Dimension> backupFontSize;
        std::optional<Dimension> backupMaxFontSize;
        std::optional<Dimension> backupMinFontSize;
        if (textLayoutProperty->HasFontSize()) {
            backupFontSize = textLayoutProperty->GetFontSizeValue(Dimension());
        }
        if (textLayoutProperty->HasAdaptMaxFontSize()) {
            backupMaxFontSize = textLayoutProperty->GetAdaptMaxFontSizeValue(Dimension());
        }
        if (textLayoutProperty->HasAdaptMinFontSize()) {
            backupMinFontSize = textLayoutProperty->GetAdaptMinFontSizeValue(Dimension());
        }
        textLayoutProperty->ResetFontSize();
        textLayoutProperty->ResetAdaptMaxFontSize();
        textLayoutProperty->ResetAdaptMinFontSize();
        textApply(AceType::WeakClaim(AceType::RawPtr(text_)));
        if (!textLayoutProperty->HasFontSize() && !textLayoutProperty->HasAdaptMinFontSize() &&
            !textLayoutProperty->HasAdaptMaxFontSize()) {
            // restore
            if (backupFontSize.has_value()) {
                textLayoutProperty->UpdateFontSize(backupFontSize.value());
            }
            if (backupMaxFontSize.has_value()) {
                textLayoutProperty->UpdateAdaptMaxFontSize(backupMaxFontSize.value());
            }
            if (backupMinFontSize.has_value()) {
                textLayoutProperty->UpdateAdaptMinFontSize(backupMinFontSize.value());
            }
        }
        text_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        text_->MarkModifyDone();
    }
}

void SelectPattern::SetArrowModifierApply(const std::function<void(WeakPtr<NG::FrameNode>)>& arrowApply)
{
    arrowApply_ = arrowApply;
    if (arrowApply) {
        arrowApply(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(spinner_)));
        spinner_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        spinner_->MarkModifyDone();
    }
}

void SelectPattern::SetArrowColor(const Color& color)
{
    CHECK_NULL_VOID(spinner_);
    if (spinner_->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolLayoutProperty = spinner_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        symbolLayoutProperty->UpdateSymbolColorList({color});
        spinner_->MarkModifyDone();
        spinner_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

std::function<void(WeakPtr<NG::FrameNode>)>& SelectPattern::GetTextModifier()
{
    return textApply_;
}

std::function<void(WeakPtr<NG::FrameNode>)>& SelectPattern::GetArrowModifier()
{
    return arrowApply_;
}

void SelectPattern::SetOptionTextModifier(const std::function<void(WeakPtr<NG::FrameNode>)>& textOptionApply)
{
    textOptionApply_ = textOptionApply;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (static_cast<int32_t>(i) == selected_ && textOptionApply_) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetOptionTextModifier(textOptionApply);
        if (textOptionApply) {
            UpdateOptionFontFromPattern(pattern);
        }
    }
}

void SelectPattern::UpdateOptionFontFromPattern(const RefPtr<MenuItemPattern>& optionPattern)
{
    if (optionFont_.FontColor.has_value()) {
        optionPattern->SetFontColor(optionFont_.FontColor.value());
    }
    if (optionFont_.FontFamily.has_value()) {
        optionPattern->SetFontFamily(optionFont_.FontFamily.value());
    }
    if (optionFont_.FontSize.has_value()) {
        optionPattern->SetFontSize(optionFont_.FontSize.value());
    }
    if (optionFont_.FontStyle.has_value()) {
        optionPattern->SetItalicFontStyle(optionFont_.FontStyle.value());
    }
    if (optionFont_.FontWeight.has_value()) {
        optionPattern->SetFontWeight(optionFont_.FontWeight.value());
    }
}

void SelectPattern::SetSelectedOptionTextModifier(
    const std::function<void(WeakPtr<NG::FrameNode>)>& textSelectOptionApply)
{
    textSelectOptionApply_ = textSelectOptionApply;
    if (selected_ >= 0 && selected_ < static_cast<int32_t>(options_.size())) {
        auto pattern = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSelectedOptionTextModifier(textSelectOptionApply);
        if (textSelectOptionApply) {
            UpdateSelectedOptionFontFromPattern(pattern);
        }
    }
}

void SelectPattern::UpdateSelectedOptionFontFromPattern(const RefPtr<MenuItemPattern>& optionPattern)
{
    if (selectedFont_.FontColor.has_value()) {
        optionPattern->SetOptionFontColor(selectedFont_.FontColor.value());
    }
    if (selectedFont_.FontFamily.has_value()) {
        optionPattern->SetFontFamily(selectedFont_.FontFamily.value());
    } else if (optionFont_.FontFamily.has_value()) {
        optionPattern->SetFontFamily(optionFont_.FontFamily.value());
    }
    if (selectedFont_.FontSize.has_value()) {
        optionPattern->SetFontSize(selectedFont_.FontSize.value());
    } else if (optionFont_.FontSize.has_value()) {
        optionPattern->SetFontSize(optionFont_.FontSize.value());
    }
    if (selectedFont_.FontStyle.has_value()) {
        optionPattern->SetItalicFontStyle(selectedFont_.FontStyle.value());
    } else if (optionFont_.FontStyle.has_value()) {
        optionPattern->SetItalicFontStyle(optionFont_.FontStyle.value());
    }
    if (selectedFont_.FontWeight.has_value()) {
        optionPattern->SetFontWeight(selectedFont_.FontWeight.value());
    } else if (optionFont_.FontWeight.has_value()) {
        optionPattern->SetFontWeight(optionFont_.FontWeight.value());
    }
}

void SelectPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc("Selected: " + std::to_string(selected_));
    DumpLog::GetInstance().AddDesc("FontColor: " + fontColor_.value_or(Color()).ToString());
    DumpLog::GetInstance().AddDesc(
        "SelectedOptionFontSize: " + selectedFont_.FontSize.value_or(Dimension()).ToString());
    DumpLog::GetInstance().AddDesc(
        "SelectedOptionFontStyle: " + StringUtils::ToString(selectedFont_.FontStyle.value_or(Ace::FontStyle::NORMAL)));
    DumpLog::GetInstance().AddDesc("SelectedOptionFontWeight: " +
        StringUtils::FontWeightToString(selectedFont_.FontWeight.value_or(FontWeight::NORMAL)));
    DumpLog::GetInstance().AddDesc("SelectedOptionFontFamily: " +
        ConvertVectorToString(selectedFont_.FontFamily.value_or(std::vector<std::string>())));
    DumpLog::GetInstance().AddDesc("SelectedOptionFontColor: " + selectedFont_.FontColor.value_or(Color()).ToString());
    DumpLog::GetInstance().AddDesc("SelectedBgColor: " + selectedBgColor_.value_or(Color()).ToString());
    DumpLog::GetInstance().AddDesc("OptionFontSize: " + optionFont_.FontSize.value_or(Dimension()).ToString());
    DumpLog::GetInstance().AddDesc(
        "OptionFontStyle: " + StringUtils::ToString(optionFont_.FontStyle.value_or(Ace::FontStyle::NORMAL)));
    DumpLog::GetInstance().AddDesc(
        "OptionFontWeight: " + StringUtils::FontWeightToString(optionFont_.FontWeight.value_or(FontWeight::NORMAL)));
    DumpLog::GetInstance().AddDesc(
        "OptionFontFamily: " + ConvertVectorToString(optionFont_.FontFamily.value_or(std::vector<std::string>())));
    DumpLog::GetInstance().AddDesc("OptionFontColor: " + optionFont_.FontColor.value_or(Color()).ToString());
    DumpLog::GetInstance().AddDesc("OptionBgColor: " + optionBgColor_.value_or(Color()).ToString());
    DumpLog::GetInstance().AddDesc("ControlSize: " + ConvertControlSizeToString(controlSize_));
}

void SelectPattern::SetOptionTextModifierByUser(
    const RefPtr<SelectTheme>& theme, const RefPtr<SelectPaintProperty>& props)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(props);
    if (!props->GetOptionFontColorSetByUserValue(false)) {
        SetOptionFontColor(theme->GetFontColor());
    }

    if (props->GetOptionTextModifierSetByUserValue(false)) {
        SetOptionTextModifier(textOptionApply_);
    }
}

void SelectPattern::SetSelectedOptionTextModifierByUser(
    const RefPtr<SelectTheme>& theme, const RefPtr<SelectPaintProperty>& props)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(props);
    if (!props->GetSelectedOptionFontColorSetByUserValue(false)) {
        SetSelectedOptionFontColor(theme->GetSelectedColorText());
    }

    if (props->GetSelectedOptionTextModifierSetByUserValue(false)) {
        SetSelectedOptionTextModifier(textSelectOptionApply_);
    }
}

void SelectPattern::SetArrowModifierByUser(
    const RefPtr<SelectTheme>& theme, const RefPtr<SelectPaintProperty>& props)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(props);
    if (!props->GetArrowModifierSetByUserValue(false)) {
        auto spinnerId = GetSpinnerId();
        auto spinner = FrameNode::GetOrCreateFrameNode(
            V2::SYMBOL_ETS_TAG, spinnerId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(spinner);
        InitSpinner(spinner, theme);
        spinner->MarkModifyDone();
        auto rowId = GetRowId();
        auto row = FrameNode::GetOrCreateFrameNode(
            V2::ROW_ETS_TAG, rowId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
        CHECK_NULL_VOID(row);
        row->MarkModifyDone();
        row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    } else {
        SetArrowModifierApply(arrowApply_);
    }
}

void SelectPattern::SetSelectedOptionBgColorByUser(const RefPtr<SelectTheme>& theme,
    const RefPtr<SelectPaintProperty>& props, const RefPtr<SelectLayoutProperty>& layoutProps)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(props);
    CHECK_NULL_VOID(layoutProps);
    if (layoutProps->GetShowDefaultSelectedIconValue(false)) {
        return;
    }

    if (!props->GetSelectedOptionBgColorSetByUserValue(false)) {
        SetSelectedOptionBgColor(theme->GetSelectedColor());
    }
}

void SelectPattern::SetModifierByUser(const RefPtr<SelectTheme>& theme, const RefPtr<SelectPaintProperty>& props)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(props);
    if (!props->GetFontColorSetByUserValue(false)) {
        ResetFontColor();
        text_->MarkDirtyNode();
    }

    if (props->GetTextModifierSetByUserValue(false)) {
        SetTextModifierApply(textApply_);
    }

    SetOptionTextModifierByUser(theme, props);
    SetSelectedOptionTextModifierByUser(theme, props);
    SetArrowModifierByUser(theme, props);
}
} // namespace OHOS::Ace::NG
