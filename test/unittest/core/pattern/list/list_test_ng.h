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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LIST_LIST_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LIST_LIST_TEST_NG_H

#include <functional>
#include <optional>

#include "gtest/gtest.h"
#include "test/mock/base/mock_drag_window.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/safe_area_insets.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "bridge/common/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_model.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float LIST_WIDTH = 480.f;
constexpr float LIST_HEIGHT = 800.f;
constexpr int32_t TOTAL_LINE_NUMBER = 10;
constexpr int32_t VIEW_LINE_NUMBER = 8;
constexpr float ITEM_WIDTH = LIST_WIDTH / VIEW_LINE_NUMBER;
constexpr float ITEM_HEIGHT = LIST_HEIGHT / VIEW_LINE_NUMBER;
constexpr int32_t GROUP_NUMBER = 4;
constexpr int32_t GROUP_LINE_NUMBER = 4;
constexpr float GROUP_HEADER_LEN = 50.f;
constexpr float START_NODE_LEN = 80.f;
constexpr float END_NODE_LEN = 100.f;
constexpr float DELETE_AREA_DISTANCE = 50.f;
constexpr Dimension GROUP_MARGIN = 12.0_vp;
constexpr float DEFAULT_STIFFNESS = 228;
constexpr float DEFAULT_DAMPING = 30;
constexpr float SWIPER_SPEED_TH = 1200.f;
constexpr float SWIPER_TH = 0.25f;
constexpr int32_t DEFAULT_LANES = 1;
constexpr int32_t DEFAULT_SPACE = 0;
constexpr float DEFAULT_STARTOFFSET = 0.f;
constexpr float SPACE = 10.f;
constexpr float STROKE_WIDTH = 5.f;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(STROKE_WIDTH), Dimension(10), Dimension(20), Color(0x000000) };
struct SwipeActionItem {
    std::function<void()> builderAction;
    Dimension actionAreaDistance;
    OnDeleteEvent onDelete;
    OnEnterDeleteAreaEvent onEnterDeleteArea;
    OnExitDeleteAreaEvent onExitDeleteArea;
    OnStateChangedEvent onStateChange;
};

class ListTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void Create(const std::function<void(ListModelNG)>& callback);
    void CreateWithItem(const std::function<void(ListModelNG)>& callback);
    void CreateWithSwipe(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber = TOTAL_LINE_NUMBER);
    void CreateWithSwipeAction(
        SwipeActionItem& item, bool isStartArea, OnOffsetChangeFunc onOffsetChange, V2::SwipeEdgeEffect effect);

    static void CreateItem(
        int32_t itemNumber, Axis axis = Axis::VERTICAL, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    static void CreateItemWithSize(
        int32_t itemNumber, SizeT<Dimension> itemSize, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    static void CreateGroup(int32_t groupNumber, Axis axis = Axis::VERTICAL);
    static void CreateGroupWithSetting(int32_t groupNumber, Axis axis, V2::ListItemGroupStyle listItemGroupStyle,
        int32_t itemNumber = GROUP_LINE_NUMBER);
    static void CreateItemWithSwipe(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    static std::function<void()> GetDefaultSwiperBuilder(float crossSize);
    static std::function<void()> GetDefaultHeaderBuilder();

    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    float GetInterval();
    void ScrollUp(float itemNumber = 1);
    void ScrollDown(float itemNumber = 1);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    void ScrollToIndex(int32_t index, bool smooth, ScrollAlign align);
    void ScrollToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align);
    void DragSwiperItem(int32_t index, float mainDelta, float mainVelocity = SWIPER_SPEED_TH);
    void HandleDragStart(int32_t index);
    void HandleDragUpdate(int32_t index, float mainDelta);
    void HandleDragEnd(int32_t index, float mainVelocity = SWIPER_SPEED_TH);

    AssertionResult VerifyPosition(
        const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset);
    AssertionResult VerifyItemPosition(
        const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, int32_t initialIndex);
    AssertionResult VerifyGroupItemPosition(
        const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset);
    AssertionResult IsEqualTotalOffset(float expectOffset);
    AssertionResult ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset);
    AssertionResult ScrollToItemInGroup(
        int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align, float expectOffset);
    std::vector<RefPtr<FrameNode>> GetALLItem();
    int32_t findFocusNodeIndex(RefPtr<FocusHub>& focusNode);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ListLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
    RefPtr<ListAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LIST_LIST_TEST_NG_H