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

#include "test/unittest/core/pattern/test_ng.h"
#include "test/unittest/core/pattern/lazydynamiclayout/mock_lazy_grid_layout_algorithm.h"

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_caches.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SCROLL_WIDTH = 200.f;
constexpr float SCROLL_HEIGHT = 450.f;
constexpr float ITEM_HEIGHT = 100.f;

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
}

class LazyDynamicLayoutTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override {}
    void TearDown() override;
    void CreateRepeatVirtualScrollNode(
        int32_t itemNumber, const std::function<std::pair<uint32_t, uint32_t>(int32_t, bool, bool)>& createFunc);

    void CreateScroll();
    void CreateLazyDynamicLayout(Axis axis);
    void CreateStack(Axis axis);
    RefPtr<FrameNode> GetMainFrameNode();
private:
    RefPtr<FrameNode> frameNode_;
    RefPtr<LazyDynamicLayoutPattern> pattern_;
    RefPtr<ScrollablePattern> scrollablePattern_;
    RefPtr<FrameNode> scrollableFrameNode_;
    RefPtr<LayoutAlgorithm> algorithm_;
};

void LazyDynamicLayoutTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void LazyDynamicLayoutTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void LazyDynamicLayoutTest::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
}

void LazyDynamicLayoutTest::CreateRepeatVirtualScrollNode(
    int32_t itemNumber, const std::function<std::pair<uint32_t, uint32_t>(int32_t, bool, bool)>& onGetRid4Index)
{
    RepeatVirtualScroll2ModelNG repeatModel;
    auto onActiveRange = [](int32_t start, int32_t end, int32_t cacheStart,
        int32_t cacheEnd, bool isCache, bool isImmediate) {};
    auto onPurge = []() {};
    auto onPurgeAll = []() {};
    auto onUpdateDirty = []() {};
    auto onRecycleItems = [](int32_t start, int32_t end) {};
    repeatModel.Create(
        itemNumber,
        itemNumber,
        0,
        onGetRid4Index,
        onRecycleItems,
        onActiveRange,
        nullptr,
        onPurge,
        onPurgeAll,
        onUpdateDirty);
}

void LazyDynamicLayoutTest::CreateScroll()
{
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

RefPtr<FrameNode> LazyDynamicLayoutTest::GetMainFrameNode()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    return AceType::DynamicCast<FrameNode>(element);
}

void LazyDynamicLayoutTest::CreateStack(Axis axis)
{
    StackModelNG stackModel;
    stackModel.Create();
    if (axis == Axis::HORIZONTAL) {
        ViewAbstract::SetHeight(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetWidth(CalcLength(ITEM_HEIGHT));
    } else {
        ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
    }
}

void LazyDynamicLayoutTest::CreateLazyDynamicLayout(Axis axis)
{
    auto customParams = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
    LazyDynamicLayoutModelNG model;
    model.Create(customParams);
    if (axis == Axis::HORIZONTAL) {
        ViewAbstract::SetHeight(CalcLength(SCROLL_WIDTH));
    } else {
        ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    }
    frameNode_ = GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<LazyDynamicLayoutPattern>();
    frameNode_->layoutProperty_ = AceType::MakeRefPtr<LazyGridLayoutProperty>();
    auto info = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    algorithm_ = AceType::MakeRefPtr<MockLazyGridLayoutAlgorithm>(info);
    auto weak = AceType::WeakClaim(AceType::RawPtr(algorithm_));
    customParams->SetOnMeasureSize([weak](LayoutWrapper* layoutWrapper) {
        auto algorithm = weak.Upgrade();
        CHECK_NULL_VOID(algorithm);
        algorithm->Measure(layoutWrapper);
    });
    customParams->SetOnPlaceChildren([weak](LayoutWrapper* layoutWrapper) {
        auto algorithm = weak.Upgrade();
        CHECK_NULL_VOID(algorithm);
        algorithm->Layout(layoutWrapper);
    });
}

/**
 * @tc.name: LazyForEachTest001
 * @tc.desc: Test LazyVGridLayout with LazyForEach generated children.
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutTest, LayoutLazyForEachTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout with LazyForEach
     * @tc.expected: layout visible items
     */
    CreateScroll();
    CreateLazyDynamicLayout(Axis::VERTICAL);
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
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.begin()), 0);
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.rbegin()), 4);

    /**
     * @tc.steps: step2. Scroll 150px
     * @tc.expected: layout visible items
     */
    scrollablePattern_->UpdateCurrentOffset(-120, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.begin()), 1);
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.rbegin()), 5);

    /**
     * @tc.steps: step3. Update LazyGrid0 lanes.
     * @tc.expected: start and end index updated
     */
    auto layoutProperty = pattern_->GetLayoutProperty<LazyGridLayoutProperty>();
    layoutProperty->UpdateColumnsTemplate("1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.begin()), 0);
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.rbegin()), 9);
    EXPECT_EQ(scrollablePattern_->GetTotalOffset(), 20);
}

/**
 * @tc.name: RepeatVirtualScrollTest001
 * @tc.desc: Test LazyVGridLayout with Repeat generated children.
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutTest, RepeatVirtualScrollTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazy grid layout with LazyForEach
     * @tc.expected: layout visible items and predict items
     */
    CreateScroll();
    CreateLazyDynamicLayout(Axis::VERTICAL);
    CreateRepeatVirtualScrollNode(30,
        [](uint32_t index, bool inAnimation, bool isRestoreCache) -> std::pair<uint32_t, uint32_t> {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
            return { index + 1, OnGetRid4IndexResult::CREATED_NEW_NODE };
        }
    );
    CreateDone();
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.begin()), 0);
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.rbegin()), 4);

    /**
     * @tc.steps: step2. Scroll 150px
     * @tc.expected: layout visible items
     */
    scrollablePattern_->UpdateCurrentOffset(-120, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.begin()), 1);
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.rbegin()), 5);

    /**
     * @tc.steps: step3. Update LazyGrid0 lanes.
     * @tc.expected: start and end index updated
     */
    auto layoutProperty = pattern_->GetLayoutProperty<LazyGridLayoutProperty>();
    layoutProperty->UpdateColumnsTemplate("1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.begin()), 0);
    EXPECT_EQ(*(pattern_->prevVisibleIndexes_.rbegin()), 9);
    EXPECT_EQ(scrollablePattern_->GetTotalOffset(), 20);
}
} // namespace OHOS::Ace::NG
