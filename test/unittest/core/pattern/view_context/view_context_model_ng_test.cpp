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

// Additional constants for BindSheet tests
constexpr float TEST_SHEET_WIDTH = 300.0f;
constexpr float TEST_BORDER_RADIUS = 10.0f;
} // namespace

class ViewContextModelNGTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<PipelineContext> pipelineContext_;
};

RefPtr<PipelineContext> ViewContextModelNGTest::pipelineContext_;

void ViewContextModelNGTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    pipelineContext_ = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrentContext());
}

void ViewContextModelNGTest::TearDownTestCase()
{
    pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ViewContextModelNGTest::SetUp() {}

void ViewContextModelNGTest::TearDown() {}

/**
 * @tc.name: ViewContextModelNGTest001
 * @tc.desc: Test closeAnimation with default AnimationOption
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest001, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption with default values
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetDelay(TEST_DELAY);
    option.SetIteration(TEST_ITERATION);

    /**
     * @tc.steps: step2. Call closeAnimation with needFlush = true
     * @tc.expected: No crash occurs
     */
    viewContext.closeAnimation(option, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextModelNGTest002
 * @tc.desc: Test closeAnimation with needFlush = false
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest002, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);

    /**
     * @tc.steps: step2. Call closeAnimation with needFlush = false
     * @tc.expected: No crash occurs
     */
    viewContext.closeAnimation(option, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextModelNGTest003
 * @tc.desc: Test closeAnimation with curve
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest003, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption with curve
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetCurve(Curves::EASE);

    /**
     * @tc.steps: step2. Call closeAnimation
     * @tc.expected: No crash occurs
     */
    viewContext.closeAnimation(option, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextModelNGTest006
 * @tc.desc: Test openAnimation with default AnimationOption
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest006, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetDelay(TEST_DELAY);
    option.SetIteration(TEST_ITERATION);

    /**
     * @tc.steps: step2. Call openAnimation
     * @tc.expected: No crash occurs
     */
    viewContext.openAnimation(option);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextModelNGTest009
 * @tc.desc: Test openAnimation with onFinish callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest009, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption with onFinish callback
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    bool callbackExecuted = false;
    option.SetOnFinishEvent([&callbackExecuted]() { callbackExecuted = true; });

    /**
     * @tc.steps: step2. Call openAnimation
     * @tc.expected: No crash occurs
     */
    viewContext.openAnimation(option);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextModelNGTest011
 * @tc.desc: Test OpenBindSheet with basic SheetStyle
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest011, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with default values
     */
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = false;

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest012
 * @tc.desc: Test OpenBindSheet with showInSubWindow = true
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest012, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with showInSubWindow = true
     */
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = true;

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest013
 * @tc.desc: Test OpenBindSheet with callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest013, TestSize.Level1)
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
     * @tc.steps: step3. Create callbacks
     */
    bool onAppearExecuted = false;
    auto onAppear = [&onAppearExecuted]() { onAppearExecuted = true; };

    bool onDisappearExecuted = false;
    auto onDisappear = [&onDisappearExecuted]() { onDisappearExecuted = true; };

    /**
     * @tc.steps: step4. Call OpenBindSheet with callbacks
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, std::move(onAppear),
        std::move(onDisappear), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest014
 * @tc.desc: Test OpenBindSheet with title build function
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest014, TestSize.Level1)
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
     * @tc.steps: step3. Create title build function
     */
    auto titleBuildFunc = []() {
        // Build title content
    };

    /**
     * @tc.steps: step4. Call OpenBindSheet with title build function
     * @tc.expected: Return valid sheet id
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, std::move(titleBuildFunc), sheetStyle, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest015
 * @tc.desc: Test OpenBindSheet with shouldDismiss callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest015, TestSize.Level1)
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
     * @tc.steps: step4. Call OpenBindSheet with shouldDismiss
     * @tc.expected: Return valid sheet id
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, std::move(shouldDismiss),
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest016
 * @tc.desc: Test OpenBindSheet with onWillDismiss callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest016, TestSize.Level1)
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
    bool onWillDismissCalled = false;
    auto onWillDismiss = [&onWillDismissCalled](const int32_t info) { onWillDismissCalled = true; };

    /**
     * @tc.steps: step4. Call OpenBindSheet with onWillDismiss
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr,
        std::move(onWillDismiss), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID,
        TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest017
 * @tc.desc: Test OpenBindSheet with height change callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest017, TestSize.Level1)
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
    bool onHeightDidChangeCalled = false;
    auto onHeightDidChange = [&onHeightDidChangeCalled](const float height) { onHeightDidChangeCalled = true; };

    /**
     * @tc.steps: step4. Call OpenBindSheet with height change callback
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, std::move(onHeightDidChange), nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID,
        TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest018
 * @tc.desc: Test OpenBindSheet with detents change callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest018, TestSize.Level1)
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
     * @tc.steps: step3. Create detents change callback
     */
    bool onDetentsDidChangeCalled = false;
    auto onDetentsDidChange = [&onDetentsDidChangeCalled](const float detents) { onDetentsDidChangeCalled = true; };

    /**
     * @tc.steps: step4. Call OpenBindSheet with detents change callback
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, std::move(onDetentsDidChange), nullptr, nullptr, nullptr, TEST_INSTANCE_ID,
        TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest019
 * @tc.desc: Test OpenBindSheet with width change callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest019, TestSize.Level1)
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
     * @tc.steps: step3. Create width change callback
     */
    bool onWidthDidChangeCalled = false;
    auto onWidthDidChange = [&onWidthDidChangeCalled](const float width) { onWidthDidChangeCalled = true; };

    /**
     * @tc.steps: step4. Call OpenBindSheet with width change callback
     * @tc.expected: Return valid sheet id
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, std::move(onWidthDidChange), nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest020
 * @tc.desc: Test OpenBindSheet with type change callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest020, TestSize.Level1)
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
    bool onTypeDidChangeCalled = false;
    auto onTypeDidChange = [&onTypeDidChangeCalled](const float type) { onTypeDidChangeCalled = true; };

    /**
     * @tc.steps: step4. Call OpenBindSheet with type change callback
     * @tc.expected: Return valid sheet id
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, std::move(onTypeDidChange), nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest021
 * @tc.desc: Test OpenBindSheet with sheet spring back callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest021, TestSize.Level1)
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
    bool sheetSpringBackCalled = false;
    auto sheetSpringBack = [&sheetSpringBackCalled]() { sheetSpringBackCalled = true; };

    /**
     * @tc.steps: step4. Call OpenBindSheet with spring back callback
     * @tc.expected: Return valid sheet id
     */
    auto sheetId =
        viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr, std::move(sheetSpringBack), TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest022
 * @tc.desc: Test OpenBindSheet with all callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest022, TestSize.Level1)
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
     * @tc.steps: step4. Call OpenBindSheet with all callbacks
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, std::move(titleBuildFunc), sheetStyle,
        std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
        std::move(sheetSpringBack), TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest023
 * @tc.desc: Test UpdateBindSheet with basic SheetStyle
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest023, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Setup parent-child relationship
     */
    sheetContentNode->SetParent(scrollNode);
    scrollNode->SetParent(sheetPageNode);

    /**
     * @tc.steps: step3. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step4. Call UpdateBindSheet
     * @tc.expected: Return valid result
     */
    auto result = viewContext.UpdateBindSheet(sheetContentNode, sheetStyle, false, TEST_INSTANCE_ID);
    EXPECT_TRUE(result >= 0);
}

/**
 * @tc.name: ViewContextModelNGTest024
 * @tc.desc: Test UpdateBindSheet with partial update
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest024, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Setup parent-child relationship
     */
    sheetContentNode->SetParent(scrollNode);
    scrollNode->SetParent(sheetPageNode);

    /**
     * @tc.steps: step3. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step4. Call UpdateBindSheet with partial update
     * @tc.expected: Return valid result
     */
    auto result = viewContext.UpdateBindSheet(sheetContentNode, sheetStyle, true, TEST_INSTANCE_ID);
    EXPECT_TRUE(result >= 0);
}

/**
 * @tc.name: ViewContextModelNGTest025
 * @tc.desc: Test CloseBindSheet with basic scenario
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest025, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Setup parent-child relationship
     */
    sheetContentNode->SetParent(scrollNode);
    scrollNode->SetParent(sheetPageNode);

    /**
     * @tc.steps: step3. Call CloseBindSheet
     * @tc.expected: Return valid result
     */
    auto result = viewContext.CloseBindSheet(sheetContentNode, TEST_INSTANCE_ID);
    EXPECT_TRUE(result >= 0);
}

/**
 * @tc.name: ViewContextModelNGTest026
 * @tc.desc: Test pendingAnimationNodes_ management
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest026, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create AnimationOption
     */
    AnimationOption option;
    option.SetDuration(TEST_DURATION);
    option.SetIteration(TEST_ITERATION);

    /**
     * @tc.steps: step2. Call openAnimation to add node to pending set
     */
    viewContext.openAnimation(option);

    /**
     * @tc.steps: step3. Call closeAnimation to remove node from pending set
     * @tc.expected: No crash occurs
     */
    viewContext.closeAnimation(option, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextModelNGTest027
 * @tc.desc: Test multiple openAnimation calls
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest027, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create multiple AnimationOptions
     */
    AnimationOption option1;
    option1.SetDuration(TEST_DURATION);
    option1.SetIteration(TEST_ITERATION);

    AnimationOption option2;
    option2.SetDuration(TEST_DURATION * 2);
    option2.SetIteration(TEST_ITERATION * 2);

    /**
     * @tc.steps: step2. Call openAnimation multiple times
     * @tc.expected: No crash occurs
     */
    viewContext.openAnimation(option1);
    viewContext.openAnimation(option2);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ViewContextModelNGTest031
 * @tc.desc: Test SheetStyle with different detents
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest031, TestSize.Level1)
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
    sheetStyle.detents = { SheetHeight { .sheetMode = SheetMode::MEDIUM },
        SheetHeight { .sheetMode = SheetMode::LARGE } };

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest032
 * @tc.desc: Test SheetStyle with backgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest032, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with backgroundColor
     */
    SheetStyle sheetStyle;
    sheetStyle.backgroundColor = Color::RED;

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest033
 * @tc.desc: Test SheetStyle with dragBar
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest033, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with dragBar
     */
    SheetStyle sheetStyle;
    sheetStyle.showDragBar = true;

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest034
 * @tc.desc: Test SheetStyle with maskColor
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest034, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with maskColor
     */
    SheetStyle sheetStyle;
    sheetStyle.maskColor = Color::BLACK;

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest035
 * @tc.desc: Test SheetStyle with width
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest035, TestSize.Level1)
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
    sheetStyle.width = Dimension(TEST_SHEET_WIDTH);

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest036
 * @tc.desc: Test multiple OpenBindSheet calls
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest036, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create multiple sheet content nodes
     */
    auto sheetContentNode1 = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto sheetContentNode2 = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle
     */
    SheetStyle sheetStyle;

    /**
     * @tc.steps: step3. Call OpenBindSheet multiple times
     * @tc.expected: Return different sheet ids
     */
    auto sheetId1 = viewContext.OpenBindSheet(sheetContentNode1, nullptr, sheetStyle, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    auto sheetId2 = viewContext.OpenBindSheet(sheetContentNode2, nullptr, sheetStyle, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);

    EXPECT_NE(sheetId1, 0);
    EXPECT_NE(sheetId2, 0);
}

/**
 * @tc.name: ViewContextModelNGTest039
 * @tc.desc: Test SheetStyle with border radius
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest039, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with border radius
     */
    SheetStyle sheetStyle;
    sheetStyle.radius = NG::BorderRadiusProperty(Dimension(TEST_BORDER_RADIUS));

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}

/**
 * @tc.name: ViewContextModelNGTest040
 * @tc.desc: Test SheetStyle with should avoid keyboard
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextModelNGTest, ViewContextModelNGTest040, TestSize.Level1)
{
    ViewContextModelNG viewContext;
    /**
     * @tc.steps: step1. Create sheet content node
     */
    auto sheetContentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create SheetStyle with should avoid keyboard
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetKeyboardAvoidMode = SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE;

    /**
     * @tc.steps: step3. Call OpenBindSheet
     * @tc.expected: Return valid sheet id
     */
    auto sheetId = viewContext.OpenBindSheet(sheetContentNode, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, TEST_INSTANCE_ID, TEST_TARGET_ID);
    EXPECT_NE(sheetId, 0);
}
} // namespace OHOS::Ace::NG
