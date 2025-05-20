/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_scroll_bar_modifier.h"

#include "interfaces/native/node/node_model.h"

#include "base/geometry/calc_dimension.h"
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/scroll/scroll_position_controller.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/native/node/node_api.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
void setScrollBarEnableNestedScroll(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarModelNG::SetEnableNestedScroll(frameNode, static_cast<bool>(value));
}

void resetScrollBarEnableNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarModelNG::SetEnableNestedScroll(frameNode, false);
}

void SetScrollBarScrollBarColor(ArkUINodeHandle node, ArkUI_Int32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarModelNG::SetScrollBarColor(frameNode, Color(color));
}

void ResetScrollBarScrollBarColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarModelNG::ResetScrollBarColor(frameNode);
}

namespace NodeModifier {
const ArkUIScrollBarModifier* GetScrollBarModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIScrollBarModifier modifier = {
        .setScrollBarDirection = nullptr,
        .resetScrollBarDirection = nullptr,
        .setScrollBarState = nullptr,
        .resetScrollBarState = nullptr,
        .setScrollBarScroller = nullptr,
        .setScrollBarEnableNestedScroll = setScrollBarEnableNestedScroll,
        .resetScrollBarEnableNestedScroll = resetScrollBarEnableNestedScroll,
        .setScrollBarScrollBarColor = SetScrollBarScrollBarColor,
        .resetScrollBarScrollBarColor = ResetScrollBarScrollBarColor,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    /* clang-format on */
    return &modifier;
}

const CJUIScrollBarModifier* GetCJUIScrollBarModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIScrollBarModifier modifier = {
        .setScrollBarDirection = nullptr,
        .resetScrollBarDirection = nullptr,
        .setScrollBarState = nullptr,
        .resetScrollBarState = nullptr,
        .setScrollBarScroller = nullptr,
        .setScrollBarEnableNestedScroll = setScrollBarEnableNestedScroll,
        .resetScrollBarEnableNestedScroll = resetScrollBarEnableNestedScroll,
        .setScrollBarScrollBarColor = SetScrollBarScrollBarColor,
        .resetScrollBarScrollBarColor = ResetScrollBarScrollBarColor,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    /* clang-format on */
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
