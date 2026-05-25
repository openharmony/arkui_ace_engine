/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_COLUMN_LAYOUT_TEST_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_COLUMN_LAYOUT_TEST_H

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/animation/mock_animation_manager.h"

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_pattern.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_info.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float SCROLL_WIDTH = 200.f;
constexpr float SCROLL_HEIGHT = 450.f;
constexpr float ITEM_HEIGHT = 100.f;
using VisibleIndexesChangeEvent = std::function<void(int32_t, int32_t)>;

class LazyColumnLayoutTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> GetMainFrameNode();
    void CreateLazyColumnLayout(VisibleIndexesChangeEvent&& callback = nullptr);
    void CreateLazyVGridLayout();
    void CreateStack(const CalcLength& width = CalcLength(1, DimensionUnit::PERCENT),
        const CalcLength& height = CalcLength(ITEM_HEIGHT));
    void CreateContent(int32_t count, const CalcLength& width = CalcLength(1, DimensionUnit::PERCENT),
        const CalcLength& height = CalcLength(ITEM_HEIGHT));
    void CreateScroll();
    void CreateWaterFlow(WaterFlowLayoutMode mode = WaterFlowLayoutMode::TOP_DOWN);
    void CreateFlowItem();
    void CreateList();
    void CreateListItems();
    void CreateListWithLazyColumnLayout(int32_t initialIndex = 0, bool stackFromEnd = false);
    void AddChildAtIndex(int32_t index = 0);
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
    void FlushIdleTask(const RefPtr<LazyColumnLayoutPattern>& pattern);
    void FlushListIdleTask(const RefPtr<ListPattern>& listPattern);
    void CreateRepeatVirtualScrollNode(
        int32_t itemNumber, const std::function<std::pair<uint32_t, uint32_t>(int32_t, bool)>& createFunc);

    RefPtr<FrameNode> frameNode_;
    RefPtr<LazyColumnLayoutPattern> pattern_;
    RefPtr<LazyColumnLayoutProperty> layoutProperty_;
    RefPtr<FrameNode> lazyGridFrameNode_;
    RefPtr<LazyGridLayoutPattern> lazyGridPattern_;
    RefPtr<ScrollablePattern> scrollablePattern_;
    RefPtr<FrameNode> scrollableFrameNode_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_COLUMN_LAYOUT_TEST_H
