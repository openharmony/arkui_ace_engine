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

#include "test/unittest/core/layout/safe_area/expand_safe_area_test_ng.h"

#include <cstdint>
#include <cstdlib>
#include <map>
#include <memory>

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected
namespace OHOS::Ace::NG {
namespace {
constexpr float WINDOW_WIDTH = 720.0f;
constexpr float WINDOW_HEIGHT = 1280.0f;
constexpr int32_t CHILD_COUNT_1 = 1;
constexpr float ITEM_HEIGHT_100 = 100.0f;
constexpr float ITEM_HEIGHT_50 = 50.0f;
constexpr float SAFE_AREA_LENGTH_TOP = 80.0f;
constexpr float SAFE_AREA_LENGTH_BOTTOM = 100.0f;
constexpr float SAFE_AREA_LENGTH_LEFT = 20.0f;
constexpr float SAFE_AREA_LENGTH_RIGHT = 20.0f;
constexpr float SAFE_AREA_KEYBOARD = 500.0f;
} // namespace

/**
 * @brief Initialize test suite before all test cases.
 */
void ExpandSafeAreaTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

/**
 * @brief Clean up test suite after all test cases.
 */
void ExpandSafeAreaTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @brief Initialize test environment before each test case.
 */
void ExpandSafeAreaTestNg::SetUp() {}

/**
 * @brief Initialize SafeAreaManager with given config.
 * @param config AvoidConfig containing isFullScreen, isNeedAvoidWindow, ignoreSafeArea flags.
 */
void ExpandSafeAreaTestNg::InitSafeAreaManager(AvoidConfig config)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    safeAreaManager->SetIsFullScreen(config.isFullScreen);
    safeAreaManager->SetIsNeedAvoidWindow(config.isNeedAvoidWindow);
    safeAreaManager->SetIgnoreSafeArea(config.ignoreSafeArea);
    safeAreaManager->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET);
}

/**
 * @brief Clean up test environment after each test case.
 */
void ExpandSafeAreaTestNg::TearDown()
{
    frameNode_ = nullptr;
    pagePattern_ = nullptr;
}

/**
 * @brief Get the FrameNode instance from ViewStackProcessor and set constraintNotChanged flag.
 */
void ExpandSafeAreaTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    frameNode_->isConstraintNotChanged_ = true;
    pagePattern_ = frameNode_->GetPattern();
}

/**
 * @brief Create a test page with given callback and optionally flush layout.
 * @param callback The callback function to build UI components.
 * @param flushLayout Whether to flush UI tasks after creation.
 */
void ExpandSafeAreaTestNg::Create(const std::function<void()>& callback, bool flushLayout)
{
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, -1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ViewStackProcessor::GetInstance()->Push(pageNode);
    ViewAbstract::SetWidth(CalcLength(WINDOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(WINDOW_HEIGHT));
    if (callback) {
        callback();
    }
    GetInstance();
    if (flushLayout) {
        FlushUITasks(frameNode_);
    }
}

/**
 * @brief Create a test page with one child item and execute callback.
 * @param callback The callback function to build UI components.
 */
void ExpandSafeAreaTestNg::CreateWithItem(const std::function<void()>& callback)
{
    Create([callback]() {
        if (callback) {
            callback();
        }
        CreateItem(CHILD_COUNT_1);
    });
}

/**
 * @brief Create multiple RelativeContainer items.
 * @param number The number of items to create.
 * @param defineSize Whether to set FILL_LENGTH height for each item.
 */
void ExpandSafeAreaTestNg::CreateItem(int32_t number, bool defineSize)
{
    for (int32_t i = 0; i < number; i++) {
        RelativeContainerModelNG relativeContainerModel;
        relativeContainerModel.Create();
        if (defineSize) {
            ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

/**
 * @brief Add multiple Stack children to frameNode_ with alternating heights (100/50).
 * @param number The number of children to add.
 */
void ExpandSafeAreaTestNg::AddItems(int32_t number)
{
    for (int i = 0; i < number; ++i) {
        auto child = FrameNode::GetOrCreateFrameNode(
            V2::STACK_ETS_TAG, -1, []() { return AceType::MakeRefPtr<StackPattern>(); });
        if (i & 1) {
            child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(ITEM_HEIGHT_100))));
        } else {
            child->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(FILL_LENGTH), CalcLength(Dimension(ITEM_HEIGHT_50))));
        }
        frameNode_->AddChild(child);
    }
}

/**
 * @brief Create a RelativeContainer item with specified height.
 * @param height The height of the item.
 */
void ExpandSafeAreaTestNg::CreateItemWithHeight(float height)
{
    RelativeContainerModelNG relativeContainerModelNG;
    relativeContainerModelNG.Create();
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(Dimension(height)));
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @brief Initialize SafeAreaInsets based on given expand options.
 * @param opts SafeAreaExpandOpts specifying type and edges to expand.
 */
void ExpandSafeAreaTestNg::InitSafeArea(SafeAreaExpandOpts opts)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    SafeAreaInsets insets;
    if (opts.edges & SAFE_AREA_EDGE_TOP) {
        insets.top_ = { 0.0f, SAFE_AREA_LENGTH_TOP };
    }
    if (opts.edges & SAFE_AREA_EDGE_START) {
        insets.left_ = { 0.0f, SAFE_AREA_LENGTH_LEFT };
    }
    if (opts.edges & SAFE_AREA_EDGE_END) {
        insets.right_ = { WINDOW_WIDTH, WINDOW_WIDTH - SAFE_AREA_LENGTH_RIGHT };
    }
    if (opts.edges & SAFE_AREA_EDGE_BOTTOM) {
        insets.bottom_ = { WINDOW_HEIGHT - SAFE_AREA_LENGTH_BOTTOM, WINDOW_HEIGHT };
    }
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    // for tdd, we assume opt type in this function is used to update one specific type
    switch (opts.type) {
        case SAFE_AREA_TYPE_SYSTEM:
            pipeline->UpdateSystemSafeArea(insets, false);
            break;
        case SAFE_AREA_TYPE_CUTOUT:
            pipeline->UpdateCutoutSafeArea(insets, false);
            break;
        case SAFE_AREA_TYPE_KEYBOARD:
            safeAreaManager->UpdateKeyboardOffset(SAFE_AREA_KEYBOARD);
            break;
        default:
            break;
    }
}

/**
 * @brief Get current SafeAreaInsets from SafeAreaManager.
 * @return SafeAreaInsets containing top, bottom, left, right insets.
 */
SafeAreaInsets ExpandSafeAreaTestNg::GetSafeAreaInsets()
{
    SafeAreaInsets insets;
    auto pipeline = MockPipelineContext::GetCurrent();
    CHECK_NULL_RETURN(pipeline, insets);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, insets);
    insets = safeAreaManager->GetSafeArea();
    return insets;
}

/**
 * @tc.name: Manager001
 * @tc.desc: Test SafeAreaManager top & bottom system safeArea.
 * @tc.type: FUNC
 */
HWTEST_F(ExpandSafeAreaTestNg, Manager001, TestSize.Level0)
{
    /**@tc.steps: step1 Initialize SafeAreaManager with isFullScreen=true.*/
    AvoidConfig config { .isFullScreen = true };
    InitSafeAreaManager(config);
    
    /**@tc.steps: step2 Set system safeArea for top and bottom edges.*/
    SafeAreaExpandOpts opts { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP | SAFE_AREA_EDGE_BOTTOM };
    InitSafeArea(opts);
    
    /**@tc.steps: step3 Get safeAreaInsets and verify top/bottom values, left/right should be zero.*/
    auto safeAreaInsets = GetSafeAreaInsets();
    EXPECT_TRUE(safeAreaInsets.left_.Length() == 0);
    EXPECT_FALSE(safeAreaInsets.top_.Length() == 0);
    EXPECT_TRUE(safeAreaInsets.top_.start == 0);
    EXPECT_TRUE(safeAreaInsets.top_.end == SAFE_AREA_LENGTH_TOP);
    EXPECT_TRUE(safeAreaInsets.right_.Length() == 0);
    EXPECT_FALSE(safeAreaInsets.bottom_.Length() == 0);
    EXPECT_EQ(safeAreaInsets.bottom_.start, (WINDOW_HEIGHT - SAFE_AREA_LENGTH_BOTTOM));
    EXPECT_EQ(safeAreaInsets.bottom_.end, WINDOW_HEIGHT);
}
} // namespace OHOS::Ace::NG
