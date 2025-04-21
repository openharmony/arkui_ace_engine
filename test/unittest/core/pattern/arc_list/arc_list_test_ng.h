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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_ARC_LIST_ARC_LIST_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_ARC_LIST_ARC_LIST_TEST_NG_H

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
#include "test/unittest/core/syntax/mock_lazy_for_each_actuator.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "bridge/common/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/list/arc_list_item_theme.h"
#include "core/components/list/arc_list_theme.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_layout_algorithm.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/list/list_accessibility_property.h"
#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_model.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/syntax/for_each_model_ng.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_ng/syntax/syntax_item.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float LIST_WIDTH = 240.f;
constexpr float LIST_HEIGHT = 400.f;
constexpr float ITEM_WIDTH = 60.f;
constexpr float ITEM_HEIGHT = 100.f;
constexpr int32_t TOTAL_ITEM_NUMBER = 6;
constexpr int32_t VIEW_ITEM_NUMBER = 4;
constexpr int32_t GROUP_NUMBER = 4;
constexpr int32_t GROUP_ITEM_NUMBER = 2;
constexpr float GROUP_HEADER_LEN = 50.f;
constexpr float START_NODE_LEN = 80.f;
constexpr float END_NODE_LEN = 100.f;
constexpr float DELETE_AREA_DISTANCE = 50.f;
constexpr Dimension GROUP_MARGIN = 12.0_vp;
constexpr float DEFAULT_STIFFNESS = 228;
constexpr float DEFAULT_DAMPING = 30;
constexpr float SWIPER_SPEED_TH = 1500.f;
constexpr float SWIPER_TH = 0.25f;
constexpr int32_t DEFAULT_LANES = 1;
constexpr int32_t DEFAULT_SPACE = 0;
constexpr float DEFAULT_STARTOFFSET = 0.f;
constexpr float SPACE = 10.f;
constexpr float MID_OFFSET = LIST_HEIGHT / 2.0 - ITEM_HEIGHT / 2.0;
constexpr float STROKE_WIDTH = 5.f;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(STROKE_WIDTH), Dimension(10), Dimension(20), Color(0x000000) };
constexpr float ARC_LIST_ITER_SCALE = 0.92f;
constexpr float DRAG_FIX_OFFSET_RATIO = 0.85f;
constexpr float ARC_LIST_ITEM_SNAP_SIZE = 72.5f;
constexpr float ARC_LIST_FRICTION = 0.8f;
constexpr float ARC_LIST_ITEM_MOVE_THRESHOLD_RATIO = 0.4f;
constexpr float START_MAIN_POS = 200.0f;
constexpr float PREDICT_SNAPEND_POS = 34.5f;
constexpr int32_t DEFAULT_ITEM_COUNT = 3;
constexpr int32_t ARC_ITEM_COUNT = 20;
constexpr int32_t ARC_ITEM_COUNT2 = 2;
constexpr float DEVIATION_HEIGHT = 20.f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
class ArcListTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void FlushUITasks(const RefPtr<FrameNode>& frameNode);
    void GetList();
    ListModelNG CreateList();
    void AddHeader(ListModelNG* model);
    ListModelNG CreateListWithHeader();
    ListItemModelNG CreateListItem(V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    void CreateListItems(int32_t itemNumber, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);

    void CreateListItemsWithSize(
        int32_t itemNumber, SizeT<Dimension> itemSize, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    void CreateListItemsWithSize(
        std::vector<SizeT<Dimension>>& itemSizes, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);
    ListItemModelNG CreateListItemWithSize(
        SizeT<Dimension> itemSize, V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE);

    void CreateItemWithSize(int32_t itemNumber, SizeT<Dimension> itemSize);
    void CreateItemWithSwipe(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    std::function<void()> GetDefaultSwiperBuilder(float crossSize);
    std::function<void()> GetDefaultHeaderBuilder();

    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    float GetInterval();
    void ScrollUp(float itemNumber = 1);
    void ScrollDown(float itemNumber = 1);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    void ScrollToIndex(int32_t index, bool smooth, ScrollAlign align);
    void DragSwiperItem(int32_t index, float mainDelta, float mainVelocity = SWIPER_SPEED_TH);
    void HandleDragStart(int32_t index);
    void HandleDragUpdate(int32_t index, float mainDelta);
    void HandleDragEnd(int32_t index, float mainVelocity = SWIPER_SPEED_TH);
    void ScrollSnap(float offset, float velocity);
    void ScrollSnapForEqualHeightItem(float offset, float velocity);

    AssertionResult VerifyPosition(
        const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset);
    AssertionResult VerifyItemPosition(
        const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, int32_t initialIndex);
    AssertionResult IsEqualTotalOffset(float expectOffset);
    AssertionResult ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset);
    std::vector<RefPtr<FrameNode>> GetALLItem();
    int32_t findFocusNodeIndex(RefPtr<FocusHub>& focusNode);
    void ScrollTo(float position);
    void SetChildrenMainSize(
        const RefPtr<FrameNode>& frameNode, int32_t startIndex, const std::vector<float>& newChildrenSize);
        
    RefPtr<FrameNode> frameNode_;
    RefPtr<ArcListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ArcListLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
    RefPtr<ListAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_ARC_LIST_ARC_LIST_TEST_NG_H