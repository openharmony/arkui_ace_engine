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

#include "core/components_ng/pattern/checkbox/checkbox_model_static.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

static constexpr Dimension CHECK_MARK_SIZE_DEFAULT{20, DimensionUnit::VP};

}

void CheckBoxModelStatic::SetSelect(FrameNode* frameNode, const std::optional<bool>& isSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected.value_or(false));
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    if (isSelected.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelect, isSelected.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelect, frameNode);
    }
}

void CheckBoxModelStatic::SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColor, color.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColorFlagByUser, true, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColor, frameNode);
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColorFlagByUser, frameNode);
    }
}

void CheckBoxModelStatic::SetUnSelectedColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxUnSelectedColor, color.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxUnSelectedColorFlagByUser, true, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxUnSelectedColor, frameNode);
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxUnSelectedColorFlagByUser, frameNode);
    }
}

void CheckBoxModelStatic::SetCheckMarkColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkColor, color.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkColorFlagByUser, true, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkColor, frameNode);
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkColorFlagByUser, frameNode);
    }
}

void CheckBoxModelStatic::ResetCheckMarkColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxCheckMarkColor, PROPERTY_UPDATE_RENDER, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxCheckMarkColorFlagByUser, PROPERTY_UPDATE_RENDER, frameNode);
}

void CheckBoxModelStatic::SetCheckMarkSize(FrameNode* frameNode, const std::optional<Dimension>& size)
{
    if (size.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkSize, size.value(), frameNode);
    } else {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxPaintProperty, CheckBoxCheckMarkSize, CHECK_MARK_SIZE_DEFAULT, frameNode);
    }
}

void CheckBoxModelStatic::SetCheckMarkWidth(FrameNode* frameNode, const std::optional<Dimension>& width)
{
    if (width.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkWidth, width.value(), frameNode);
    } else {
        CHECK_NULL_VOID(frameNode);
        auto markNode = reinterpret_cast<FrameNode*>(frameNode);
        CHECK_NULL_VOID(markNode);
        auto markLayoutProperty = markNode->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(markLayoutProperty);
        auto pipelineContext = markNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<CheckboxTheme>();
        auto defaultStroke = theme ? theme->GetCheckStroke() : Dimension();
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkWidth, defaultStroke, frameNode);
    }
}

void CheckBoxModelStatic::SetBuilder(FrameNode* frameNode, std::function<void(void)>&& buildFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto checkBoxPattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(checkBoxPattern);
    checkBoxPattern->SetIndicatorBuilder(buildFunc);
    frameNode->MarkModifyDone();
}

void CheckBoxModelStatic::SetBuilder(FrameNode* frameNode, std::optional<std::function<void(void)>>& buildFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto checkBoxPattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(checkBoxPattern);
    checkBoxPattern->SetIndicatorBuilder(buildFunc);
}

void CheckBoxModelStatic::SetCheckboxStyle(FrameNode* frameNode, const std::optional<CheckBoxStyle>& checkboxStyle)
{
    CHECK_NULL_VOID(frameNode);
    if (checkboxStyle.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedStyle, checkboxStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedStyle, frameNode);
    }
}

void CheckBoxModelStatic::SetChangeEvent(FrameNode* frameNode, ChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}

void CheckBoxModelStatic::TriggerChange(FrameNode* frameNode, bool value)
{
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateUIStatus(value);
}
} // namespace OHOS::Ace::NG
