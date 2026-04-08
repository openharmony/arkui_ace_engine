/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/licenses-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "lazy_grid_layout_syntax_test.h"

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"

namespace OHOS::Ace::NG {

using GetChildByIndexCallback = std::function<std::pair<std::string, RefPtr<NG::UINode>>(int32_t index)>;

class CustomLazyForEachBuilder : public Framework::MockLazyForEachBuilder {
public:
    CustomLazyForEachBuilder(int32_t itemCnt, GetChildByIndexCallback&& callback)
        : itemCnt_(itemCnt), getChildByIndexCallback_(std::move(callback)) {}

protected:
    int32_t OnGetTotalCount() override
    {
        return itemCnt_;
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        if (getChildByIndexCallback_) {
            return getChildByIndexCallback_(index);
        }
        return { std::to_string(index), nullptr };
    }

private:
    int32_t itemCnt_ = 0;
    GetChildByIndexCallback getChildByIndexCallback_ = nullptr;
};

void LazyGridLayoutSyntaxTest::CreateRepeatVirtualScrollNode(
    int32_t itemNumber, const std::function<std::pair<uint32_t, uint32_t>(int32_t, bool)>& onGetRid4Index)
{
    RepeatVirtualScroll2ModelNG repeatModel;
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onPurge = []() {};
    auto onUpdateDirty = []() {};
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    repeatModel.Create(
        itemNumber,
        itemNumber,
        onGetRid4Index,
        onRecycleItems,
        onActiveRange,
        nullptr,
        onPurge,
        onUpdateDirty);
}

/**
 * @tc.name: LazyForEachTest001
 * @tc.desc: Test LazyVGridLayout with LazyForEach generated children.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutSyntaxTest, LazyForEachTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout with LazyForEach
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    auto mockLazy = AceType::MakeRefPtr<CustomLazyForEachBuilder>(30,
        [](int32_t index) -> std::pair<std::string, RefPtr<NG::UINode>> {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
            auto node = ViewStackProcessor::GetInstance()->Finish();
            return { std::to_string(index), node };
        }
    );
    LazyForEachModelNG lazyForEachModelNG;
    RefPtr<NG::LazyForEachBuilder> builder = mockLazy;
    lazyForEachModelNG.Create(builder);
    CreateDone();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1500);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 200);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 13);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 13);
    EXPECT_EQ(mockLazy->startIndex_, 0);
    EXPECT_EQ(mockLazy->endIndex_, 13);

    /**
     * @tc.steps: UpdateColumnsTemplate 1fr
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("1fr");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 3000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 6);
    EXPECT_EQ(mockLazy->startIndex_, 0);
    EXPECT_EQ(mockLazy->endIndex_, 6);

    /**
     * @tc.steps: UpdateColumnsTemplate 1fr 1fr 1fr
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 14);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 20);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 20);
    EXPECT_EQ(mockLazy->startIndex_, 0);
    EXPECT_EQ(mockLazy->endIndex_, 20);
}

/**
 * @tc.name: RepeatVirtualScrollTest001
 * @tc.desc: Test LazyVGridLayout with Repeat generated children.
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridLayoutSyntaxTest, RepeatVirtualScrollTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout with LazyForEach
     * @tc.expected: layout visible items and predict items
     */
    CreateWaterFlow();
    CreateLazyGridLayout();
    CreateRepeatVirtualScrollNode(30,
        [](uint32_t index, bool inAnimation) -> std::pair<uint32_t, uint32_t> {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
            return { 1, OnGetRid4IndexResult::CREATED_NEW_NODE };
        }
    );
    CreateDone();
    auto repeat = AceType::DynamicCast<RepeatVirtualScroll2Node>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(repeat, nullptr);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1500);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 200);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 13);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 13);
    EXPECT_EQ(repeat->prevActiveRangeStart_, 0);
    EXPECT_EQ(repeat->prevActiveRangeEnd_, 13);

    /**
     * @tc.steps: UpdateColumnsTemplate 1fr
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("1fr");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 3000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 6);
    EXPECT_EQ(repeat->prevActiveRangeStart_, 0);
    EXPECT_EQ(repeat->prevActiveRangeEnd_, 6);

    /**
     * @tc.steps: UpdateColumnsTemplate 1fr 1fr 1fr
     * @tc.expected: start and end index updated
     */
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Height(), 1000);
    EXPECT_EQ(pattern_->layoutInfo_->lanes_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 14);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 20);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 20);
    EXPECT_EQ(repeat->prevActiveRangeStart_, 0);
    EXPECT_EQ(repeat->prevActiveRangeEnd_, 20);
}
} // namespace OHOS::Ace::NG
