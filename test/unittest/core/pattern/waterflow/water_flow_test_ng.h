/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_TEST_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_TEST_NG_H

#include "test/unittest/core/pattern/scrollable/scrollable_utils_test_ng.h"
#define protected public
#define private public
#include "test/unittest/core/syntax/mock_lazy_for_each_actuator.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_paint_method.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
const InspectorFilter filter;
constexpr float WATER_FLOW_WIDTH = 480.f;
constexpr float WATER_FLOW_HEIGHT = 800.f;
constexpr int32_t TOTAL_LINE_NUMBER = 10;
constexpr int32_t VIEW_LINE_NUMBER = 8;
constexpr float BIG_ITEM_MAIN_SIZE = ITEM_MAIN_SIZE * 2;
#define TOP_TO_DOWN pattern_->layoutInfo_->Mode() == WaterFlowLayoutMode::TOP_DOWN

class WaterFlowMockLazy : public Framework::MockLazyForEachBuilder {
public:
    WaterFlowMockLazy(int32_t itemCnt, std::function<float(int32_t)>&& getHeight)
        : itemCnt_(itemCnt), getHeight_(getHeight)
    {}

    void SetTotalCount(int32_t totalCount)
    {
        itemCnt_ = totalCount;
    }

protected:
    int32_t OnGetTotalCount() override
    {
        return itemCnt_;
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override;

private:
    int32_t itemCnt_ = 0;
    const std::function<float(int32_t)> getHeight_;
};

class WaterFlowTestNg : public ScrollableUtilsTestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    virtual void GetWaterFlow();

    WaterFlowModelNG CreateWaterFlow();
    void CreateItemsInRepeat(int32_t itemNumber, std::function<float(uint32_t)>&& getSize);
    RefPtr<WaterFlowMockLazy> CreateItemsInLazyForEach(int32_t itemNumber, std::function<float(int32_t)>&& getHeight);
    void CreateWaterFlowItems(int32_t itemNumber = TOTAL_LINE_NUMBER);
    WaterFlowItemModelNG CreateWaterFlowItem(float mainSize);
    void CreateFocusableWaterFlowItems(int32_t itemNumber = TOTAL_LINE_NUMBER);
    void CreateRandomWaterFlowItems(int32_t itemNumber);
    void CreateItemWithHeight(float height);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    std::function<void()> GetDefaultHeaderBuilder();
    void AddItems(int32_t itemNumber);
    void AddItemsAtSlot(int32_t itemNumber, float height, int32_t slotIdx);
    void HandleDrag(float offset);
    RectF GetLazyChildRect(int32_t itemIndex);
    RefPtr<FrameNode> GetItem(int32_t index, bool isCache = false);
    void AddItemInLazyForEach(int32_t index);
    void DeleteItemInLazyForEach(int32_t index);
    RefPtr<WaterFlowPaintMethod> UpdateOverlayModifier();
    RefPtr<WaterFlowPaintMethod> UpdateContentModifier();

    RefPtr<WaterFlowPattern> pattern_;
    RefPtr<WaterFlowEventHub> eventHub_;
    RefPtr<WaterFlowLayoutProperty> layoutProperty_;
    RefPtr<WaterFlowAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_TEST_NG_H
