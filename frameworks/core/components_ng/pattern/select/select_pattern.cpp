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
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/select/select_accessibility_property.h"
#include "core/components_ng/pattern/select/select_event_hub.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/utils.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

namespace {

constexpr uint32_t SELECT_ITSELF_TEXT_LINES = 1;

} // namespace

void SelectPattern::OnAttachToFrameNode()
{
    RegisterOnClick();
    RegisterOnPress();
    RegisterOnHover();
    RegisterOnKeyEvent();
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
}

void SelectPattern::ShowSelectMenu()
{
    if (menuWrapper_) {
        LOGI("start executing click callback %d", menuWrapper_->GetId());
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    auto menu = GetMenuNode();
    CHECK_NULL_VOID(menu);
    auto menuLayoutProps = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProps);
    menuLayoutProps->UpdateTargetSize(selectSize_);
    auto offset = GetHost()->GetPaintRectOffset();
    auto isContainerModal = context->GetWindowModal() == WindowModal::CONTAINER_MODAL &&
                            context->GetWindowManager()->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        auto newOffsetX = offset.GetX() + static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx() * 2) +
                          static_cast<float>(CONTENT_PADDING.ConvertToPx() * 2);
        auto newOffsetY = offset.GetY() + static_cast<float>(CONTAINER_TITLE_HEIGHT.ConvertToPx());
        offset.SetX(newOffsetX);
        offset.SetY(newOffsetY);
    }
    offset.AddY(selectSize_.Height());
    LOGD("select offset %{public}s size %{public}s", offset.ToString().c_str(), selectSize_.ToString().c_str());
    overlayManager->ShowMenu(GetHost()->GetId(), offset, menuWrapper_);
}

// add click event to show menu
void SelectPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    GestureEventFunc callback = [weak = WeakClaim(this)](GestureEvent& /* info */) mutable {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);

        auto selected = pattern->GetSelected();
        if (selected > -1 && selected < pattern->GetOptions().size()) {
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
    auto pipeline = PipelineBase::GetCurrentContext();
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
        CHECK_NULL_VOID_NOLOG(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID_NOLOG(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID_NOLOG(renderContext);
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
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsHover(isHover);
        auto pipeline = PipelineBase::GetCurrentContext();
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
        auto pattern = weak.Upgrade();
        auto host = pattern->GetHost();
        auto theme = host->GetContext()->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(pattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        const auto& renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        // update press status, repaint background color
        if (touchType == TouchType::DOWN) {
            LOGD("triggers option press");
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
            auto newSelected = pattern->options_[index]->GetPattern<OptionPattern>();
            CHECK_NULL_VOID(newSelected);
            valueChangeEvent(newSelected->GetText());
        }
        auto onSelect = hub->GetSelectEvent();
        // execute onSelect callback
        if (onSelect) {
            auto newSelected = pattern->options_[index]->GetPattern<OptionPattern>();
            CHECK_NULL_VOID(newSelected);
            onSelect(index, newSelected->GetText());
        }
    };
    for (auto&& option : options_) {
        auto hub = option->GetEventHub<OptionEventHub>();
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
        CHECK_NULL_RETURN_NOLOG(pattern, false);
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProps);
    textProps->UpdateTextColor(theme->GetDisabledFontColor());
    text_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

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
    spinner_->MarkModifyDone();
}

void SelectPattern::SetSelected(int32_t index)
{
    // if option is already selected, do nothing
    if (index == selected_) {
        return;
    }
    if (index >= options_.size() || index < 0) {
        LOGW("newly selected index invalid");
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
    // get theme from SelectThemeManager
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();

    auto select = GetHost();

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

    spinner_ = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, spinnerId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(spinner_);
    spinner_->SetInternal();
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    InitSpinner(spinner_, iconTheme, theme);

    // mount triangle and text
    text_->MarkModifyDone();
    if (!hasTextNode) {
        text_->MountToParent(row);
    }
    if (!hasSpinnerNode) {
        spinner_->MountToParent(row);
    }
    spinner_->MarkModifyDone();
    if (!hasRowNode) {
        row->MountToParent(select);
    }
    row->MarkModifyDone();
    row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    // set bgColor and border
    auto renderContext = select->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(theme->GetBackgroundColor());
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
        if (i == selected_ && selectedBgColor_.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetBgColor(color);
    }
}

void SelectPattern::SetOptionFontSize(const Dimension& value)
{
    optionFont_.FontSize = value;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (i == selected_ && selectedFont_.FontSize.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontSize(value);
    }
}

void SelectPattern::SetOptionItalicFontStyle(const Ace::FontStyle& value)
{
    optionFont_.FontStyle = value;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (i == selected_ && selectedFont_.FontStyle.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetItalicFontStyle(value);
    }
}

void SelectPattern::SetOptionFontWeight(const FontWeight& value)
{
    optionFont_.FontWeight = value;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (i == selected_ && selectedFont_.FontWeight.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontWeight(value);
    }
}

void SelectPattern::SetOptionFontFamily(const std::vector<std::string>& value)
{
    optionFont_.FontFamily = value;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (i == selected_ && selectedFont_.FontFamily.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontFamily(value);
    }
}

void SelectPattern::SetOptionFontColor(const Color& color)
{
    optionFont_.FontColor = color;
    for (size_t i = 0; i < options_.size(); ++i) {
        if (i == selected_ && selectedFont_.FontColor.has_value()) {
            continue;
        }
        auto pattern = options_[i]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontColor(color);
    }
}

// set props of option node when selected
void SelectPattern::SetSelectedOptionBgColor(const Color& color)
{
    selectedBgColor_ = color;
    if (selected_ != -1) {
        auto pattern = options_[selected_]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetBgColor(color);
    }
}

void SelectPattern::SetSelectedOptionFontSize(const Dimension& value)
{
    selectedFont_.FontSize = value;
    if (selected_ != -1) {
        auto pattern = options_[selected_]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontSize(value);
    }
}

void SelectPattern::SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value)
{
    selectedFont_.FontStyle = value;
    if (selected_ != -1) {
        auto pattern = options_[selected_]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetItalicFontStyle(value);
    }
}

void SelectPattern::SetSelectedOptionFontWeight(const FontWeight& value)
{
    selectedFont_.FontWeight = value;
    if (selected_ != -1) {
        auto pattern = options_[selected_]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontWeight(value);
    }
}

void SelectPattern::SetSelectedOptionFontFamily(const std::vector<std::string>& value)
{
    selectedFont_.FontFamily = value;
    if (selected_ != -1) {
        auto pattern = options_[selected_]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetFontFamily(value);
    }
}

void SelectPattern::SetSelectedOptionFontColor(const Color& color)
{
    selectedFont_.FontColor = color;
    if (selected_ != -1) {
        auto pattern = options_[selected_]->GetPattern<OptionPattern>();
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    auto textTheme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(selectTheme && textTheme);

    for (const auto& option : options_) {
        auto pattern = option->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
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
    auto newSelected = options_[index]->GetPattern<OptionPattern>();
    CHECK_NULL_VOID(newSelected);
    // set lastSelected option props back to default (unselected) values
    if (selected_ > -1) {
        CHECK_NULL_VOID(options_[selected_]);
        auto lastSelected = options_[selected_]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(lastSelected);

        lastSelected->SetFontColor(newSelected->GetFontColor());
        lastSelected->SetFontFamily(newSelected->GetFontFamily());
        lastSelected->SetFontSize(newSelected->GetFontSize());
        lastSelected->SetItalicFontStyle(newSelected->GetItalicFontStyle());
        lastSelected->SetFontWeight(newSelected->GetFontWeight());

        lastSelected->SetBgColor(newSelected->GetBgColor());
        lastSelected->UpdateNextNodeDivider(true);
        if (selected_ != 0) {
            auto lastSelectedNode = lastSelected->GetHost();
            CHECK_NULL_VOID(lastSelectedNode);
            auto lastSelectedPros = lastSelectedNode->GetPaintProperty<OptionPaintProperty>();
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
    auto newSelected = options_[index]->GetPattern<OptionPattern>();
    CHECK_NULL_VOID(newSelected);

    // set newSelected props
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
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
    newSelected->UpdateNextNodeDivider(false);
    auto newSelectedNode = newSelected->GetHost();
    CHECK_NULL_VOID(newSelectedNode);
    auto newSelectedPros = newSelectedNode->GetPaintProperty<OptionPaintProperty>();
    CHECK_NULL_VOID(newSelectedPros);
    newSelectedPros->UpdateNeedDivider(false);
}

void SelectPattern::UpdateText(int32_t index)
{
    // update text to selected option's text
    CHECK_NULL_VOID(text_);
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProps);
    auto newSelected = options_[index]->GetPattern<OptionPattern>();
    CHECK_NULL_VOID(newSelected);
    textProps->UpdateContent(newSelected->GetText());
    text_->MarkModifyDone();
    LOGD("new text = %s", newSelected->GetText().c_str());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SelectPattern::InitTextProps(const RefPtr<TextLayoutProperty>& textProps, const RefPtr<SelectTheme>& theme)
{
    textProps->UpdateFontSize(theme->GetFontSize());
    textProps->UpdateFontWeight(FontWeight::MEDIUM);
    textProps->UpdateTextColor(theme->GetFontColor());
    textProps->UpdateTextDecoration(theme->GetTextDecoration());
    textProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProps->UpdateMaxLines(SELECT_ITSELF_TEXT_LINES);
    MarginProperty margin;
    margin.left = CalcLength(theme->GetContentMargin());
    textProps->UpdateMargin(margin);
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
    MarginProperty margin;
    margin.right = CalcLength(selectTheme->GetContentMargin());
    spinnerLayoutProperty->UpdateMargin(margin);

    auto spinnerRenderProperty = spinner->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(spinnerRenderProperty);
    spinnerRenderProperty->UpdateSvgFillColor(selectTheme->GetSpinnerColor());
}

// XTS inspector code
void SelectPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("options", InspectorGetOptions().c_str());
    json->Put("selected", std::to_string(selected_).c_str());

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetChildren().empty()) {
        auto row = FrameNode::GetFrameNode(host->GetFirstChild()->GetTag(), host->GetFirstChild()->GetId());
        CHECK_NULL_VOID(row);
        auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
        CHECK_NULL_VOID(rowProps);
        json->Put("space", rowProps->GetSpace()->ToString().c_str());

        if (rowProps->GetFlexDirection().value() == FlexDirection::ROW) {
            json->Put("arrowPosition", "ArrowPosition.END");
        } else {
            json->Put("arrowPosition", "ArrowPosition.START");
        }
    }

    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    json->Put("value", props->GetContent().value_or("").c_str());
    Color fontColor = props->GetTextColor().value_or(Color::BLACK);
    json->Put("fontColor", fontColor.ColorToString().c_str());
    json->Put("font", props->InspectorGetTextFont().c_str());

    json->Put("selectedOptionBgColor", selectedBgColor_->ColorToString().c_str());
    json->Put("selectedOptionFont", InspectorGetSelectedFont().c_str());
    json->Put("selectedOptionFontColor", selectedFont_.FontColor.value_or(Color::BLACK).ColorToString().c_str());

    if (options_.empty()) {
        json->Put("optionBgColor", "");
        json->Put("optionFont", "");
        json->Put("optionFontColor", "");
    } else {
        auto optionPattern = options_[0]->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(optionPattern);
        json->Put("optionBgColor", optionPattern->GetBgColor().ColorToString().c_str());
        json->Put("optionFont", optionPattern->InspectorGetFont().c_str());
        json->Put("optionFontColor", optionPattern->GetFontColor().ColorToString().c_str());
    }
    ToJsonOptionAlign(json);
}

void SelectPattern::ToJsonOptionAlign(std::unique_ptr<JsonValue>& json) const
{
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

    json->Put("menuAlign", optionAlignJson);
}

std::string SelectPattern::InspectorGetOptions() const
{
    auto jsonValue = JsonUtil::Create(true);
    auto jsonOptions = JsonUtil::CreateArray(true);
    for (size_t i = 0; i < options_.size(); ++i) {
        auto temp = JsonUtil::Create(true);
        auto optionPattern = options_[i]->GetPattern<OptionPattern>();
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
    return false;
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
    return textProps->GetContentValue("");
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

} // namespace OHOS::Ace::NG
