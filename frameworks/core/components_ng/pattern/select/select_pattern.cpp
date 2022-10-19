/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr uint32_t SELECT_ITSELF_TEXT_LINES = 1;
constexpr Dimension SELECT_BORDER = 20.0_vp;
const Edge SELECT_PADDING = Edge(8.0, 9.25, 8.0, 9.25, DimensionUnit::VP);

} // namespace

void SelectPattern::OnModifyDone()
{
    RegisterOnClick();
    RegisterOnHover();
    CreateSelectedCallback();
}

// add click event to show menu
void SelectPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto callback = [id = host->GetId(), menu = menu_](GestureEvent& /*info*/) mutable {
        LOGD("start executing click callback %p", RawPtr(menu));
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->ShowMenu(id, menu);
        // menuNode already registered, nullify
        menu.Reset();
    };
    auto onClick = MakeRefPtr<ClickEvent>(std::move(callback));
    auto gestureHub = host->GetOrCreateGestureEventHub();
    gestureHub->AddClickEvent(onClick);
}

// change background color when hovered
void SelectPattern::RegisterOnHover()
{
    auto host = GetHost();
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        auto host = pattern->GetHost();
        auto theme = host->GetContext()->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(pattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        // update hover status, repaint background color
        if (touchType == TouchType::DOWN) {
            LOGD("triggers option hover");
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateBackgroundColor(theme->GetHoverColor());
        }
        if (touchType == TouchType::UP) {
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateBackgroundColor(theme->GetBackgroundColor());
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

        auto hub = host->GetEventHub<SelectEventHub>();
        CHECK_NULL_VOID(hub);
        auto onScroll = hub->GetSelectEvent();
        // execute onScroll callback
        if (onScroll) {
            auto newSelected = pattern->options_[index]->GetPattern<OptionPattern>();
            CHECK_NULL_VOID(newSelected);
            onScroll(index, newSelected->GetText());
        }
    };
    for (auto&& option : options_) {
        auto hub = option->GetEventHub<OptionEventHub>();
        // no std::move, need to set multiple options
        hub->SetOnSelect(callback);
        option->MarkModifyDone();
    }
}

void SelectPattern::SetSelected(int32_t index)
{
    // if option is already selected, do nothing
    if (index == selected_) {
        return;
    }
    if (index >= options_.size() || index < 0) {
        LOGW("newly selected index invalid");
        return;
    }
    UpdateSelectedProps(index);
    selected_ = index;
}

void SelectPattern::BuildChild()
{
    // get theme from SelectThemeManager
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = DynamicCast<PipelineBase>(pipeline)->GetTheme<SelectTheme>();

    auto row = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));
    auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    rowProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    rowProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<TextPattern>());
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();

    textProps->UpdateTextDecoration(theme->GetTextDecoration());
    textProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProps->UpdateMaxLines(SELECT_ITSELF_TEXT_LINES);

    // mount triangle and text
    text_->MountToParent(row);

    auto select = GetHost();
    text_->MountToParent(select);

    // set bgColor and border
    auto renderContext = select->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(theme->GetBackgroundColor());
    BorderRadiusProperty border;
    border.SetRadius(SELECT_BORDER);
    renderContext->UpdateBorderRadius(border);

    auto props = select->GetLayoutProperty();
    PaddingProperty padding = {
        .left = CalcLength(SELECT_PADDING.Left()),
        .right = CalcLength(SELECT_PADDING.Right()),
        .top = CalcLength(SELECT_PADDING.Top()),
        .bottom = CalcLength(SELECT_PADDING.Bottom()),
    };
    props->UpdatePadding(padding);
    props->UpdateAlignment(Alignment::CENTER);
}

void SelectPattern::SetValue(const std::string& value)
{
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateContent(value);
}

void SelectPattern::SetFontSize(const Dimension& value)
{
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
}

void SelectPattern::SetOptionBgColor(const Color& color)
{
    for (size_t i = 0; i < options_.size(); ++i) {
        if (i == selected_ && selectedBgColor_.has_value()) {
            continue;
        }
        auto renderContext = options_[i]->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBackgroundColor(color);
    }
}

void SelectPattern::SetOptionFontSize(const Dimension& value)
{
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

// update selected option props
void SelectPattern::UpdateSelectedProps(int32_t index)
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

        auto defaultPaintProps = options_[index]->GetPaintProperty<OptionPaintProperty>();
        CHECK_NULL_VOID(defaultPaintProps);
        lastSelected->SetBgColor(newSelected->GetBgColor());
        options_[selected_]->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }

    // set newSelected props
    if (selectedFont_.FontColor.has_value()) {
        newSelected->SetFontColor(selectedFont_.FontColor.value());
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
    }
    options_[index]->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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

    LOGD("new text = %s", newSelected->GetText().c_str());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

} // namespace OHOS::Ace::NG
