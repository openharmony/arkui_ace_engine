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
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "base/utils/utf_helper.h"
#include "core/animation/curves.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/select/select_event_hub.h"
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
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->GetBackgroundColor().has_value()) {
        return;
    }
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<SelectTheme>();
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
    menuPattern->HideMenu();
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

    auto offset = host->GetPaintRectOffset();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        offset.AddY(selectSize_.Height() + CALIBERATE_Y.ConvertToPx());
        offset.AddX(-CALIBERATE_X.ConvertToPx());
    } else {
        offset.AddY(selectSize_.Height());
    }

    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "select click to show menu.");
    overlayManager->ShowMenu(host->GetId(), offset, menuWrapper_);
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
        pattern->ShowSelectMenu();
    };
    auto gestureHub = host->GetOrCreateGestureEventHub();
    if (!gestureHub->GetTouchable()) {
        return;
    }
    gestureHub->BindMenu(std::move(callback));
}

void SelectPattern::PlayBgColorAnimation(bool isHoverChange)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto* pipeline = host->GetContextWithCheck();
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
    });
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
        // update hover status, repaint background color
        if (isHover) {
            pattern->SetBgBlendColor(theme->GetHoverColor());
        } else {
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
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        if (info.GetTouches().empty()) {
            return;
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        auto touchType = info.GetTouches().front().GetTouchType();
        const auto& renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        // update press status, repaint background color
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "select touch type %{public}zu", touchType);
        if (touchType == TouchType::DOWN) {
            pattern->SetBgBlendColor(theme->GetClickedColor());
            pattern->PlayBgColorAnimation(false);
        }
        if (touchType == TouchType::UP) {
            if (pattern->IsHover()) {
                pattern->SetBgBlendColor(theme->GetHoverColor());
            } else {
                pattern->SetBgBlendColor(Color::TRANSPARENT);
            }
            pattern->PlayBgColorAnimation(false);
        }
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    auto gestureHub = host->GetOrCreateGestureEventHub();
    gestureHub->AddTouchEvent(touchEvent);
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
    auto theme = pipeline->GetTheme<SelectTheme>();
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

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
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
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    bool hasRowNode = HasRowNode();
    bool hasTextNode = HasTextNode();
    bool hasSpinnerNode = HasSpinnerNode();
    auto rowId = GetRowId();
    auto textId = GetTextId();
    auto spinnerId = GetSpinnerId();

    auto row = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    CHECK_NULL_VOID(row);
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
    InitTextProps(textProps, theme);
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
    for (size_t i = 0; i < options_.size(); ++i) {
        if (static_cast<int32_t>(i) == selected_ && selectedBgColor_.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetBgColor(color);
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
        if (static_cast<int32_t>(i) == selected_ && selectedFont_.FontColor.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontColor(color);
    }
}

// set props of option node when selected
void SelectPattern::SetSelectedOptionBgColor(const Color& color)
{
    selectedBgColor_ = color;
    if (selected_ >= 0 && selected_ < static_cast<int32_t>(options_.size())) {
        auto pattern = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetBgColor(color);
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
    if (selected_ >= 0 && selected_ < static_cast<int32_t>(options_.size())) {
        auto pattern = options_[selected_]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontColor(color);
    }
}

const std::vector<RefPtr<FrameNode>>& SelectPattern::GetOptions()
{
    return options_;
}

void SelectPattern::ResetOptionProps()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    auto textTheme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(selectTheme && textTheme);

    for (const auto& option : options_) {
        auto pattern = option->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSelected(false);
        pattern->SetBgColor(optionBgColor_.value_or(selectTheme->GetBackgroundColor()));
        pattern->SetFontSize(optionFont_.FontSize.value_or(selectTheme->GetMenuFontSize()));
        pattern->SetItalicFontStyle(optionFont_.FontStyle.value_or(textTheme->GetTextStyle().GetFontStyle()));
        pattern->SetFontWeight(optionFont_.FontWeight.value_or(textTheme->GetTextStyle().GetFontWeight()));
        pattern->SetFontFamily(optionFont_.FontFamily.value_or(textTheme->GetTextStyle().GetFontFamilies()));
        pattern->SetFontColor(optionFont_.FontColor.value_or(selectTheme->GetMenuFontColor()));
    }
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

        lastSelected->SetFontColor(newSelected->GetFontColor());
        lastSelected->SetFontFamily(newSelected->GetFontFamily());
        lastSelected->SetFontSize(newSelected->GetFontSize());
        lastSelected->SetItalicFontStyle(newSelected->GetItalicFontStyle());
        lastSelected->SetFontWeight(newSelected->GetFontWeight());

        lastSelected->SetBgColor(newSelected->GetBgColor());
        lastSelected->SetSelected(false);
        lastSelected->UpdateNextNodeDivider(true);
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

// update selected option props
void SelectPattern::UpdateSelectedProps(int32_t index)
{
    CHECK_NULL_VOID(options_[index]);
    auto newSelected = options_[index]->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(newSelected);

    // set newSelected props
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (selectedFont_.FontColor.has_value()) {
        newSelected->SetFontColor(selectedFont_.FontColor.value());
    } else {
        auto selectedColorText = theme->GetSelectedColorText();
        newSelected->SetFontColor(selectedColorText);
    }
    if (selectedFont_.FontFamily.has_value()) {
        newSelected->SetFontFamily(selectedFont_.FontFamily.value());
    }
    if (selectedFont_.FontSize.has_value()) {
        newSelected->SetFontSize(selectedFont_.FontSize.value());
    }
    if (selectedFont_.FontStyle.has_value()) {
        newSelected->SetItalicFontStyle(selectedFont_.FontStyle.value());
    }
    if (selectedFont_.FontWeight.has_value()) {
        newSelected->SetFontWeight(selectedFont_.FontWeight.value());
    }
    if (selectedBgColor_.has_value()) {
        newSelected->SetBgColor(selectedBgColor_.value());
    } else {
        auto selectedColor = theme->GetSelectedColor();
        newSelected->SetBgColor(selectedColor);
    }
    newSelected->SetSelected(true);
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

void SelectPattern::InitTextProps(const RefPtr<TextLayoutProperty>& textProps, const RefPtr<SelectTheme>& theme)
{
    textProps->UpdateFontSize(theme->GetFontSize());
    textProps->UpdateFontWeight(FontWeight::MEDIUM);
    textProps->UpdateTextColor(theme->GetFontColor());
    textProps->UpdateTextDecoration(theme->GetTextDecoration());
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
    json->PutExtAttr("selectedOptionFont", InspectorGetSelectedFont().c_str(), filter);
    json->PutExtAttr("selectedOptionFontColor",
        selectedFont_.FontColor.value_or(Color::BLACK).ColorToString().c_str(), filter);

    if (options_.empty()) {
        json->PutExtAttr("optionBgColor", "", filter);
        json->PutExtAttr("optionFont", "", filter);
        json->PutExtAttr("optionFontColor", "", filter);
    } else {
        auto optionPattern = options_[0]->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        json->PutExtAttr("optionBgColor", optionPattern->GetBgColor().ColorToString().c_str(), filter);
        json->PutExtAttr("optionFont", optionPattern->InspectorGetFont().c_str(), filter);
        json->PutExtAttr("optionFontColor", optionPattern->GetFontColor().ColorToString().c_str(), filter);
    }
    ToJsonOptionAlign(json, filter);
    for (size_t i = 0; i < options_.size(); ++i) {
        auto optionPaintProperty = options_[i]->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(optionPaintProperty);
        std::string optionWidth = std::to_string(optionPaintProperty->GetSelectModifiedWidthValue(0.0f));
        json->PutExtAttr("optionWidth", optionWidth.c_str(), filter);
    }
    
    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    std::string optionHeight =  std::to_string(menuLayoutProps->GetSelectModifiedHeightValue(0.0f));
    json->PutExtAttr("optionHeight", optionHeight.c_str(), filter);
    ToJsonMenuBackgroundStyle(json, filter);
    ToJsonDivider(json, filter);
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
        json->PutExtAttr("space", rowProps->GetSpace()->ToString().c_str(), filter);

        if (rowProps->GetFlexDirection().value() == FlexDirection::ROW) {
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
            json->PutExtAttr("divider", divider->ToString().c_str(), filter);
        } else {
            json->PutExtAttr("divider", "", filter);
        }
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
    UpdateTargetSize();
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
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);

    auto pattern = host->GetPattern<SelectPattern>();
    auto menuNode = pattern->GetMenuNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    auto renderContext = menuNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(selectTheme->GetBackgroundColor());
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && renderContext->IsUniRenderEnabled()) {
        renderContext->UpdateBackBlurStyle(renderContext->GetBackBlurStyle());
    }

    auto optionNode = menuPattern->GetOptions();
    for (auto child : optionNode) {
        auto optionsPattern = child->GetPattern<MenuItemPattern>();
        optionsPattern->SetFontColor(selectTheme->GetFontColor());

        child->MarkModifyDone();
        child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    SetOptionBgColor(selectTheme->GetBackgroundColor());
    host->SetNeedCallChildrenUpdate(false);
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
        paddings.left = NG::CalcLength(SELECT_MARGIN_VP);
        paddings.right = NG::CalcLength(SELECT_MARGIN_VP);
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

void SelectPattern::SetDivider(const SelectDivider& divider)
{
    for (auto&& option : options_) {
        auto props = option->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateDivider(divider);
    }
}
} // namespace OHOS::Ace::NG
