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
}

// add click event to show menu
void SelectPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto callback = [id = host->GetId(), menu = menu_](GestureEvent& /*info*/) mutable {
        LOGI("start executing callback %p", RawPtr(menu));
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
    if (disabled_) {
        textProps->UpdateTextColor(theme->GetDisabledColor());
    }

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
    for (auto&& option : options_) {
        auto renderContext = option->GetRenderContext();
        renderContext->UpdateBackgroundColor(color);
    }
}

void SelectPattern::SetOptionFontSize(const Dimension& value)
{
    for (auto&& option : options_) {
        auto pattern = option->GetPattern<OptionPattern>();
        pattern->SetFontSize(value);
    }
}

void SelectPattern::SetOptionItalicFontStyle(const Ace::FontStyle& value)
{
    for (auto&& option : options_) {
        auto pattern = option->GetPattern<OptionPattern>();
        pattern->SetItalicFontStyle(value);
    }
}

void SelectPattern::SetOptionFontWeight(const FontWeight& value)
{
    for (auto&& option : options_) {
        auto pattern = option->GetPattern<OptionPattern>();
        pattern->SetFontWeight(value);
    }
}

void SelectPattern::SetOptionFontFamily(const std::vector<std::string>& value)
{
    for (auto&& option : options_) {
        auto pattern = option->GetPattern<OptionPattern>();
        pattern->SetFontFamily(value);
    }
}

void SelectPattern::SetOptionFontColor(const Color& color)
{
    for (auto&& option : options_) {
        auto pattern = option->GetPattern<OptionPattern>();
        pattern->SetFontColor(color);
    }
}

} // namespace OHOS::Ace::NG
