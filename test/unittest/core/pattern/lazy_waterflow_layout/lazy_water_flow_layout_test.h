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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_WATER_FLOW_LAYOUT_TEST_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_WATER_FLOW_LAYOUT_TEST_H

#include <vector>

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/animation/mock_animation_manager.h"

#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class LazyWaterFlowLayoutProperty;

constexpr float LAZY_WATER_FLOW_SCROLL_WIDTH = 200.0f;
constexpr float LAZY_WATER_FLOW_SCROLL_HEIGHT = 450.0f;
constexpr float LAZY_WATER_FLOW_ITEM_HEIGHT = 100.0f;

class LazyWaterFlowLayoutTestBase : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> GetMainFrameNode();
    void CreateWaterFlow(WaterFlowLayoutMode mode = WaterFlowLayoutMode::TOP_DOWN);
    void CreateScroll();
    void CreateList();
    void CreateLazyWaterFlowLayout();
    void CreateContent(const std::vector<float>& heights);
    void CreateContent(int32_t count);
    void FlushIdleTask();

    RefPtr<FrameNode> frameNode_;
    RefPtr<LazyWaterFlowLayoutPattern> pattern_;
    RefPtr<LazyWaterFlowLayoutProperty> layoutProperty_;
    RefPtr<FrameNode> scrollableFrameNode_;
    RefPtr<ScrollablePattern> scrollablePattern_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_WATER_FLOW_LAYOUT_TEST_H
