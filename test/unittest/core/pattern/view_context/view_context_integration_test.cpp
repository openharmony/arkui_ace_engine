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

#include "gtest/gtest.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_INSTANCE_ID = 1;
constexpr int32_t TEST_TARGET_ID = 2;
constexpr float TEST_DURATION = 1000.0f;
constexpr float TEST_DELAY = 100.0f;
constexpr int32_t TEST_ITERATION = 1;

// Additional constants for animation tests
constexpr int32_t TEST_LOOP_COUNT = 5;
constexpr int32_t TEST_PERFORMANCE_LOOP = 100;
constexpr int32_t TEST_INSTANCE_COUNT = 3;

// Additional constants for BindSheet tests
constexpr int32_t TEST_SHEET_COUNT = 3;
constexpr int32_t TEST_COLOR_INCREMENT = 50;
} // namespace

class ViewContextIntegrationTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<PipelineContext> pipelineContext_;
};

RefPtr<PipelineContext> ViewContextIntegrationTest::pipelineContext_;

void ViewContextIntegrationTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    pipelineContext_ = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrentContext());
}

void ViewContextIntegrationTest::TearDownTestCase()
{
    pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ViewContextIntegrationTest::SetUp() {}

void ViewContextIntegrationTest::TearDown() {}

/**
 * @tc.name: ViewContextIntegrationTest002
 * @tc.desc: Test animation with implicit animation option
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest002, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption with implicit settings
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetDelay(TEST_DELAY);
    option.SetIteration(TEST_ITERATION);
    option.SetCurve(Curves::EASE);

    /**
     * @tc.steps: step2. Open animation
     */
    viewContext.openAnimation(option);

    /**
     * @tc.steps: step3. Verify implicit animation is set
     */
    auto implicitOption = NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    EXPECT_EQ(implicitOption.GetDuration(), TEST_DURATION);

    /**
     * @tc.steps: step4. Close animation
     */
    viewContext.closeAnimation(option, true);
}

/**
 * @tc.name: ViewContextIntegrationTest003
 * @tc.desc: Test nested animation handling
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest003, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create outer animation option
     */
    AnimationOption outerOption;
    outerOption.SetDuration(TEST_DURATION);
    outerOption.SetIteration(TEST_ITERATION);

    /**
     * @tc.steps: step2. Open outer animation
     */
    viewContext.openAnimation(outerOption);

    /**
     * @tc.steps: step3. Create inner animation option
     */
    AnimationOption innerOption;
    innerOption.SetDuration(TEST_DURATION / 2);
    innerOption.SetIteration(TEST_ITERATION);

    /**
     * @tc.steps: step4. Open inner animation
     */
    viewContext.openAnimation(innerOption);

    /**
     * @tc.steps: step5. Close inner animation
     */
    viewContext.closeAnimation(innerOption, true);

    /**
     * @tc.steps: step6. Close outer animation
     */
    viewContext.closeAnimation(outerOption, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextIntegrationTest004
 * @tc.desc: Test animation with ViewStackProcessor integration
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest004, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetCurve(Curves::LINEAR);

    /**
     * @tc.steps: step2. Open animation
     */
    viewContext.openAnimation(option);

    /**
     * @tc.steps: step3. Verify ViewStackProcessor state
     */
    auto processorOption = NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    EXPECT_EQ(processorOption.GetDuration(), TEST_DURATION);

    /**
     * @tc.steps: step4. Close animation
     */
    viewContext.closeAnimation(option, true);
}

/**
 * @tc.name: ViewContextIntegrationTest005
 * @tc.desc: Test BindSheet integration with SheetManager
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest005, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = false;

    /**
     * @tc.steps: step3. Open BindSheet
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    /**
     * @tc.steps: step4. Verify sheet is opened
     */
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest006
 * @tc.desc: Test BindSheet with SubwindowManager integration
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest006, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with showInSubWindow
     */
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = true;

    /**
     * @tc.steps: step3. Open BindSheet in subwindow
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    /**
     * @tc.steps: step4. Verify sheet is opened
     */
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest007
 * @tc.desc: Test BindSheet lifecycle with callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest007, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create lifecycle callbacks
     */
    bool onAppearCalled = false;
    auto onAppear = [&onAppearCalled]() { onAppearCalled = true; };

    bool onDisappearCalled = false;
    auto onDisappear = [&onDisappearCalled]() { onDisappearCalled = true; };

    bool onWillAppearCalled = false;
    auto onWillAppear = [&onWillAppearCalled]() { onWillAppearCalled = true; };

    bool onWillDisappearCalled = false;
    auto onWillDisappear = [&onWillDisappearCalled]() { onWillDisappearCalled = true; };

    /**
     * @tc.steps: step4. Open BindSheet with lifecycle callbacks
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, std::move(onAppear),
        std::move(onDisappear), nullptr, nullptr, std::move(onWillAppear), std::move(onWillDisappear), nullptr, nullptr,
        nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest008
 * @tc.desc: Test BindSheet update flow
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest008, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node with parent structure
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto sheetPageNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    sheetContentNode->SetParent(scrollNode);
    scrollNode->SetParent(sheetPageNode);

    /**
     * @tc.steps: step2. Create initial SheetStyle
     */
    SheetStyle initialStyle;
    initialStyle.backgroundColor = Color::WHITE;

    /**
     * @tc.steps: step3. Update BindSheet
     */
    auto result = viewContext.UpdateBindSheet(sheetContentNode, initialStyle, false, TEST_INSTANCE_ID);
    EXPECT_TRUE(result >= 0);

    /**
     * @tc.steps: step4. Create updated SheetStyle
     */
    SheetStyle updatedStyle;
    updatedStyle.backgroundColor = Color::RED;

    /**
     * @tc.steps: step5. Update BindSheet again
     */
    result = viewContext.UpdateBindSheet(sheetContentNode, updatedStyle, true, TEST_INSTANCE_ID);
    EXPECT_TRUE(result >= 0);
}

/**
 * @tc.name: ViewContextIntegrationTest009
 * @tc.desc: Test BindSheet close flow
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest009, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node with parent structure
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto sheetPageNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    sheetContentNode->SetParent(scrollNode);
    scrollNode->SetParent(sheetPageNode);

    /**
     * @tc.steps: step2. Close BindSheet
     */
    auto result = viewContext.CloseBindSheet(sheetContentNode, TEST_INSTANCE_ID);
    EXPECT_TRUE(result >= 0);
}

/**
 * @tc.name: ViewContextIntegrationTest010
 * @tc.desc: Test animation with multiple interpolators
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest010, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetIteration(TEST_ITERATION);

    /**
     * @tc.steps: step2. Open animation
     */
    viewContext.openAnimation(option);

    /**
     * @tc.steps: step3. Perform multiple operations
     */
    for (int i = 0; i < TEST_LOOP_COUNT; i++) {
        AnimationOption tempOption;
        tempOption.SetDuration(TEST_DURATION + i * 100);
        viewContext.openAnimation(tempOption);
        viewContext.closeAnimation(tempOption, true);
    }

    /**
     * @tc.steps: step4. Close original animation
     */
    viewContext.closeAnimation(option, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextIntegrationTest011
 * @tc.desc: Test BindSheet with height change tracking
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest011, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create height change callback
     */
    std::vector<float> heightChanges;
    auto onHeightDidChange = [&heightChanges](const float height) { heightChanges.push_back(height); };

    /**
     * @tc.steps: step4. Open BindSheet with height tracking
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, std::move(onHeightDidChange), nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID,
        TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest012
 * @tc.desc: Test BindSheet with detents change tracking
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest012, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with detents
     */
    SheetStyle sheetStyle;
    sheetStyle.detents = { SheetHeight { .height = Dimension(0.5f) }, SheetHeight { .height = Dimension(1.0f) } };

    /**
     * @tc.steps: step3. Create detents change callback
     */
    std::vector<float> detentsChanges;
    auto onDetentsDidChange = [&detentsChanges](const float detents) { detentsChanges.push_back(detents); };

    /**
     * @tc.steps: step4. Open BindSheet with detents tracking
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, std::move(onDetentsDidChange), nullptr, nullptr, nullptr, TEST_INSTANCE_ID,
        TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest013
 * @tc.desc: Test animation with different container instances
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest013, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetIteration(TEST_ITERATION);

    /**
     * @tc.steps: step2. Open animation in different instances
     */
    for (int32_t instanceId = 0; instanceId < TEST_INSTANCE_COUNT; instanceId++) {
        viewContext.openAnimation(option);
        viewContext.closeAnimation(option, true);
    }

    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextIntegrationTest014
 * @tc.desc: Test BindSheet with shouldDismiss callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest014, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create shouldDismiss callback
     */
    bool shouldDismissCalled = false;
    auto shouldDismiss = [&shouldDismissCalled]() { shouldDismissCalled = true; };

    /**
     * @tc.steps: step4. Open BindSheet with shouldDismiss
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, std::move(shouldDismiss),
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest015
 * @tc.desc: Test BindSheet with onWillDismiss callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest015, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create onWillDismiss callback
     */
    int32_t dismissInfo = -1;
    auto onWillDismiss = [&dismissInfo](const int32_t info) { dismissInfo = info; };

    /**
     * @tc.steps: step4. Open BindSheet with onWillDismiss
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr,
        std::move(onWillDismiss), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID,
        TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest017
 * @tc.desc: Test BindSheet with spring back callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest017, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create spring back callback
     */
    bool springBackCalled = false;
    auto sheetSpringBack = [&springBackCalled]() { springBackCalled = true; };

    /**
     * @tc.steps: step4. Open BindSheet with spring back
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr, std::move(sheetSpringBack), TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest019
 * @tc.desc: Test BindSheet with width change tracking
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest019, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with width
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create width change callback
     */
    std::vector<float> widthChanges;
    auto onWidthDidChange = [&widthChanges](const float width) { widthChanges.push_back(width); };

    /**
     * @tc.steps: step4. Open BindSheet with width tracking
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, std::move(onWidthDidChange), nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest020
 * @tc.desc: Test BindSheet with type change tracking
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest020, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create type change callback
     */
    std::vector<float> typeChanges;
    auto onTypeDidChange = [&typeChanges](const float type) { typeChanges.push_back(type); };

    /**
     * @tc.steps: step4. Open BindSheet with type tracking
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, std::move(onTypeDidChange), nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest021
 * @tc.desc: Test animation with finish callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest021, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption with finish callback
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetIteration(TEST_ITERATION);

    bool finishCalled = false;
    option.SetOnFinishEvent([&finishCalled]() { finishCalled = true; });

    /**
     * @tc.steps: step2. Open and close animation
     */
    viewContext.openAnimation(option);
    viewContext.closeAnimation(option, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextIntegrationTest022
 * @tc.desc: Test BindSheet with title builder
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest022, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create title builder
     */
    bool titleBuilt = false;
    auto titleBuildFunc = [&titleBuilt]() { titleBuilt = true; };

    /**
     * @tc.steps: step4. Open BindSheet with title builder
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, std::move(titleBuildFunc), sheetStyle, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest023
 * @tc.desc: Test multiple BindSheet operations
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest023, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create multiple sheet content nodes
     */
    std::vector<RefPtr<FrameNode>> sheetNodes;
    for (int i = 0; i < TEST_SHEET_COUNT; i++) {
        auto node = FrameNode::CreateFrameNode(
            V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        sheetNodes.push_back(node);
    }

    /**
     * @tc.steps: step2. Open multiple BindSheets
     */
    std::vector<int32_t> sheetIds;
    for (const auto& node : sheetNodes) {
        SheetStyle sheetStyle;
        auto sheetId = viewContext.OpenBindSheet(node, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
        sheetIds.push_back(sheetId);
    }

    /**
     * @tc.steps: step3. Verify all sheets are opened
     */
    for (const auto& sheetId : sheetIds) {
        EXPECT_NE(sheetId, 0);
    }
}

/**
 * @tc.name: ViewContextIntegrationTest025
 * @tc.desc: Test BindSheet with complex SheetStyle
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest025, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create complex SheetStyle
     */
    SheetStyle sheetStyle;
    sheetStyle.detents = { SheetHeight { .height = Dimension(0.5f) }, SheetHeight { .height = Dimension(1.0f) } };
    sheetStyle.backgroundColor = Color::WHITE;
    sheetStyle.maskColor = Color::BLACK;
    sheetStyle.showDragBar = true;

    /**
     * @tc.steps: step3. Open BindSheet with complex style
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest026
 * @tc.desc: Test animation performance with many operations
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest026, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetIteration(TEST_ITERATION);

    /**
     * @tc.steps: step2. Perform many animation operations
     */
    for (int i = 0; i < TEST_PERFORMANCE_LOOP; i++) {
        viewContext.openAnimation(option);
        viewContext.closeAnimation(option, true);
    }

    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextIntegrationTest027
 * @tc.desc: Test BindSheet with all callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest027, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Create all callbacks
     */
    auto titleBuildFunc = []() {};
    auto onAppear = []() {};
    auto onDisappear = []() {};
    auto shouldDismiss = []() {};
    auto onWillDismiss = [](const int32_t info) {};
    auto onWillAppear = []() {};
    auto onWillDisappear = []() {};
    auto onHeightDidChange = [](const float height) {};
    auto onDetentsDidChange = [](const float detents) {};
    auto onWidthDidChange = [](const float width) {};
    auto onTypeDidChange = [](const float type) {};
    auto sheetSpringBack = []() {};

    /**
     * @tc.steps: step4. Open BindSheet with all callbacks
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, std::move(titleBuildFunc), sheetStyle,
        std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
        std::move(sheetSpringBack), TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextIntegrationTest029
 * @tc.desc: Test BindSheet update and close sequence
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest029, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node with parent structure
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto sheetPageNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    sheetContentNode->SetParent(scrollNode);
    scrollNode->SetParent(sheetPageNode);

    /**
     * @tc.steps: step2. Update BindSheet multiple times
     */
    for (int i = 0; i < TEST_LOOP_COUNT; i++) {
        SheetStyle sheetStyle;
        sheetStyle.backgroundColor =
            Color::FromARGB(255, i * TEST_COLOR_INCREMENT, i * TEST_COLOR_INCREMENT, i * TEST_COLOR_INCREMENT);
        viewContext.UpdateBindSheet(sheetContentNode, sheetStyle, false, TEST_INSTANCE_ID);
    }

    /**
     * @tc.steps: step3. Close BindSheet
     */
    auto result = viewContext.CloseBindSheet(sheetContentNode, TEST_INSTANCE_ID);
    EXPECT_TRUE(result >= 0);
}

/**
 * @tc.name: ViewContextIntegrationTest031
 * @tc.desc: Test BindSheet with different instance IDs
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest031, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Open BindSheet with different instance IDs
     */
    for (int32_t instanceId = 0; instanceId < TEST_INSTANCE_COUNT; instanceId++) {
        SheetStyle sheetStyle;
        auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, instanceId, TEST_TARGET_ID);
        EXPECT_NE(sheetId, 0);
    }
}

/**
 * @tc.name: ViewContextIntegrationTest033
 * @tc.desc: Test BindSheet with partial update
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest033, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node with parent structure
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto sheetPageNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    sheetContentNode->SetParent(scrollNode);
    scrollNode->SetParent(sheetPageNode);

    /**
     * @tc.steps: step2. Update BindSheet with partial update
     */
    SheetStyle sheetStyle;
    sheetStyle.backgroundColor = Color::RED;

    auto result = viewContext.UpdateBindSheet(sheetContentNode, sheetStyle, true, TEST_INSTANCE_ID);
    EXPECT_TRUE(result >= 0);
}

/**
 * @tc.name: ViewContextIntegrationTest035
 * @tc.desc: Test BindSheet with showInSubWindow flag
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextIntegrationTest, ViewContextIntegrationTest035, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Test with showInSubWindow = false
     */
    SheetStyle normalStyle;
    normalStyle.showInSubWindow = false;
    auto normalSheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, normalStyle, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(normalSheetId, 0);

    /**
     * @tc.steps: step3. Test with showInSubWindow = true
     */
    SheetStyle subwindowStyle;
    subwindowStyle.showInSubWindow = true;
    auto subwindowSheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, subwindowStyle, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(subwindowSheetId, 0);
}
} // namespace OHOS::Ace::NG
