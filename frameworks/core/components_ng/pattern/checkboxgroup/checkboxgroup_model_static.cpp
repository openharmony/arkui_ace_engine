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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_static.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void CheckBoxGroupModelStatic::SetSelectAll(FrameNode* frameNode, const std::optional<bool> isSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    pattern->SetUpdateFlag(true);
    if (isSelected.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelect, isSelected.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelect, frameNode);
    }
}

void CheckBoxGroupModelStatic::SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxGroupPaintProperty, CheckBoxGroupSelectedColor, color.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxGroupPaintProperty, CheckBoxGroupSelectedColorFlagByUser, true, frameNode);
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(
            CheckBoxGroupPaintProperty, CheckBoxGroupSelectedColor, PROPERTY_UPDATE_RENDER);
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(
            CheckBoxGroupPaintProperty, CheckBoxGroupSelectedColorFlagByUser, PROPERTY_UPDATE_RENDER);
    }
}

void CheckBoxGroupModelStatic::SetUnSelectedColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxGroupPaintProperty, CheckBoxGroupUnSelectedColor, color.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxGroupPaintProperty, CheckBoxGroupUnSelectedColorFlagByUser, true, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupUnSelectedColor, frameNode);
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(
            CheckBoxGroupPaintProperty, CheckBoxGroupUnSelectedColorFlagByUser, PROPERTY_UPDATE_RENDER);
    }
}

void CheckBoxGroupModelStatic::SetCheckMarkColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkColor, color.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkColorFlagByUser, true, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkColor, frameNode);
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(
            CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkColorFlagByUser, PROPERTY_UPDATE_RENDER);
    }
}

void CheckBoxGroupModelStatic::SetCheckMarkSize(FrameNode* frameNode, const std::optional<Dimension>& size)
{
    if (size.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkSize, size.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkSize, frameNode);
    }
}

void CheckBoxGroupModelStatic::SetCheckMarkWidth(FrameNode* frameNode, const std::optional<Dimension>& width)
{
    if (width.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkWidth, width.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkWidth, frameNode);
    }
}

void CheckBoxGroupModelStatic::SetCheckboxGroupStyle(
    FrameNode* frameNode, const std::optional<CheckBoxStyle>& checkboxGroupStyle)
{
    if (checkboxGroupStyle.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            CheckBoxGroupPaintProperty, CheckBoxGroupSelectedStyle, checkboxGroupStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelectedStyle, frameNode);
    }
}

void CheckBoxGroupModelStatic::SetChangeEvent(FrameNode* frameNode, GroupChangeEvent&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}
} // namespace OHOS::Ace::NG
