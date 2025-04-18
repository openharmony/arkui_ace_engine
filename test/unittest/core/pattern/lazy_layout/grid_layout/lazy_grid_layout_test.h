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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_TEST_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_TEST_H

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/core/animation/mock_animation_manager.h"

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float SCROLL_WIDTH = 200.f;
constexpr float SCROLL_HEIGHT = 450.f;
constexpr float ITEM_HEIGHT = 100.f;

class LazyGridLayoutTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> GetMainFrameNode();
    void CreateStack(Axis axis = Axis::VERTICAL);
    void CreateLazyGridLayout(Axis axis = Axis::VERTICAL);
    void CreateContent(int32_t count = 20);
    void CreateWaterFlow(WaterFlowLayoutMode mode = WaterFlowLayoutMode::TOP_DOWN);
    void AddChild();
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
    void FlushIdleTask(const RefPtr<LazyGridLayoutPattern>& pattern);

    RefPtr<FrameNode> frameNode_;
    RefPtr<LazyGridLayoutPattern> pattern_;
    RefPtr<LazyGridLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePattern> scrollablePattern_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_TEST_H
