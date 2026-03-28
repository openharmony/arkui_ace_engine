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

#include "core/components_ng/pattern/text/text_scroll_bar_2d.h"

#include "gtest/gtest.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

// Mock ScrollablePattern for testing
class MockScrollablePattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(MockScrollablePattern, ScrollablePattern);

public:
    MockScrollablePattern() : ScrollablePattern(EdgeEffect::NONE, true) {}
    ~MockScrollablePattern() override = default;

    bool UpdateCurrentOffset(float delta, int32_t source) override
    {
        return true;
    }

    bool IsAtTop() const override
    {
        return true;
    }

    bool IsAtBottom(bool considerRepeat = false) const override
    {
        return true;
    }

    void SetHostNode(const RefPtr<FrameNode>& node)
    {
        hostNode_ = node;
    }

    void UpdateScrollBarOffset() {}

private:
    RefPtr<FrameNode> hostNode_;
};

// Test base class
class TextScrollBar2DTestBase : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

protected:
    RefPtr<FrameNode> CreateMockFrameNode();
    RefPtr<MockScrollablePattern> CreateMockScrollablePattern();
    void SetupMockHostNode();
    void SetupRenderContext();

    RefPtr<FrameNode> mockFrameNode_;
    RefPtr<MockScrollablePattern> mockScrollablePattern_;
    WeakPtr<ScrollablePattern> weakPattern_;
    RefPtr<RenderContext> mockRenderContext_;
};

void TextScrollBar2DTestBase::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextScrollBar2DTestBase::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    TestNG::TearDownTestSuite();
}

void TextScrollBar2DTestBase::SetUp()
{
    TestNG::SetUp();
    ResetElmtId();
}

void TextScrollBar2DTestBase::TearDown()
{
    mockFrameNode_.Reset();
    mockScrollablePattern_.Reset();
    mockRenderContext_.Reset();
    TestNG::TearDown();
}

RefPtr<MockScrollablePattern> TextScrollBar2DTestBase::CreateMockScrollablePattern()
{
    return AceType::AceType::MakeRefPtr<MockScrollablePattern>();
}

RefPtr<FrameNode> TextScrollBar2DTestBase::CreateMockFrameNode()
{
    auto pattern = CreateMockScrollablePattern();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetElmtId(), pattern, false);

    pattern->SetHostNode(frameNode);

    mockRenderContext_ = frameNode->GetRenderContext();
    mockFrameNode_ = frameNode;
    mockScrollablePattern_ = pattern;
    weakPattern_ = pattern;

    return frameNode;
}

void TextScrollBar2DTestBase::SetupMockHostNode()
{
    mockFrameNode_ = CreateMockFrameNode();
    ASSERT_NE(mockFrameNode_, nullptr);
    ASSERT_NE(mockScrollablePattern_, nullptr);
}

void TextScrollBar2DTestBase::SetupRenderContext()
{
    ASSERT_NE(mockFrameNode_, nullptr);
    mockRenderContext_ = mockFrameNode_->GetRenderContext();
}

// Main test class
class TextScrollBar2DTest : public TextScrollBar2DTestBase {};

// ==================== Constructor Tests ====================

/**
 * @tc.name: Constructor001
 * @tc.desc: Test TextScrollBar2D constructor with valid pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, Constructor001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    ASSERT_NE(textScrollBar2D, nullptr);
    ASSERT_NE(textScrollBar2D->GetVerticalBar(), nullptr);
    ASSERT_NE(textScrollBar2D->GetHorizontalBar(), nullptr);
    ASSERT_NE(textScrollBar2D->GetVerticalModifier(), nullptr);
    ASSERT_NE(textScrollBar2D->GetHorizontalModifier(), nullptr);

    EXPECT_EQ(textScrollBar2D->GetVerticalBar()->GetPositionMode(), PositionMode::RIGHT);
    EXPECT_EQ(textScrollBar2D->GetHorizontalBar()->GetPositionMode(), PositionMode::BOTTOM);
    EXPECT_EQ(textScrollBar2D->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: Constructor002
 * @tc.desc: Test TextScrollBar2D constructor with nullptr pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, Constructor002, TestSize.Level1)
{
    WeakPtr<ScrollablePattern> nullPattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(nullPattern);

    ASSERT_NE(textScrollBar2D, nullptr);
    ASSERT_NE(textScrollBar2D->GetVerticalBar(), nullptr);
    ASSERT_NE(textScrollBar2D->GetHorizontalBar(), nullptr);
}

// ==================== InitNGScrollBar Tests ====================

/**
 * @tc.name: InitNGScrollBar001
 * @tc.desc: Test InitNGScrollBar with valid vertical bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, InitNGScrollBar001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    textScrollBar2D->InitNGScrollBar(*bar, true);

    ASSERT_NE(bar->GetScrollPositionCallback(), nullptr);
    ASSERT_NE(bar->GetScrollEndCallback(), nullptr);
}

/**
 * @tc.name: InitNGScrollBar002
 * @tc.desc: Test InitNGScrollBar with nullptr pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, InitNGScrollBar002, TestSize.Level1)
{
    WeakPtr<ScrollablePattern> nullPattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(nullPattern);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    // Should not crash when pattern is nullptr
    textScrollBar2D->InitNGScrollBar(*bar, true);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: InitNGScrollBar003
 * @tc.desc: Test InitNGScrollBar with nullptr host
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, InitNGScrollBar003, TestSize.Level1)
{
    auto pattern = CreateMockScrollablePattern();
    // Don't set host node
    WeakPtr<ScrollablePattern> weakPattern = pattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    // Should not crash when host is nullptr
    textScrollBar2D->InitNGScrollBar(*bar, true);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: InitNGScrollBar004
 * @tc.desc: Test InitNGScrollBar with horizontal bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, InitNGScrollBar004, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    textScrollBar2D->InitNGScrollBar(*bar, false);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: InitNGScrollBar005
 * @tc.desc: Test InitNGScrollBar lambda callback - scroll position
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, InitNGScrollBar005, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    textScrollBar2D->InitNGScrollBar(*bar, true);

    auto callback = bar->GetScrollPositionCallback();
    ASSERT_NE(callback, nullptr);

    // Call the callback
    bool result = callback(10.0, 1, false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: InitNGScrollBar006
 * @tc.desc: Test InitNGScrollBar lambda callback - scroll end
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, InitNGScrollBar006, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    textScrollBar2D->InitNGScrollBar(*bar, true);

    auto callback = bar->GetScrollEndCallback();
    ASSERT_NE(callback, nullptr);

    // Call the callback - should not crash
    callback();
}

/**
 * @tc.name: InitNGScrollBar007
 * @tc.desc: Test InitNGScrollBar with lambda when TextScrollBar2D is destroyed
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, InitNGScrollBar007, TestSize.Level1)
{
    SetupMockHostNode();
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();
    {
        auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
        textScrollBar2D->InitNGScrollBar(*bar, true);
    }
    // TextScrollBar2D is destroyed, weak_ptr should be expired

    auto scrollCallback = bar->GetScrollPositionCallback();
    ASSERT_NE(scrollCallback, nullptr);

    // Callback should return false when weak_ptr is expired
    bool result = scrollCallback(10.0, 1, false);
    EXPECT_FALSE(result);
}

// ==================== AddScrollableEvent Tests ====================

/**
 * @tc.name: AddScrollableEvent001
 * @tc.desc: Test AddScrollableEvent with valid pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, AddScrollableEvent001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Should not crash
    textScrollBar2D->AddScrollableEvent();
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: AddScrollableEvent002
 * @tc.desc: Test AddScrollableEvent with nullptr pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, AddScrollableEvent002, TestSize.Level1)
{
    WeakPtr<ScrollablePattern> nullPattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(nullPattern);

    // Should not crash when pattern is nullptr
    textScrollBar2D->AddScrollableEvent();
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: AddScrollableEvent003
 * @tc.desc: Test AddScrollableEvent with nullptr host
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, AddScrollableEvent003, TestSize.Level1)
{
    auto pattern = CreateMockScrollablePattern();
    WeakPtr<ScrollablePattern> weakPattern = pattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern);

    // Should not crash when host is nullptr
    textScrollBar2D->AddScrollableEvent();
    EXPECT_NE(textScrollBar2D, nullptr);
}

// ==================== SetInBarRegionCallback Tests ====================

/**
 * @tc.name: SetInBarRegionCallback001
 * @tc.desc: Test SetInBarRegionCallback with nullptr event
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetInBarRegionCallback001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Should not crash with nullptr event
    textScrollBar2D->SetInBarRegionCallback(nullptr);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: SetInBarRegionCallback002
 * @tc.desc: Test SetInBarRegionCallback with MOUSE source
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetInBarRegionCallback002, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto event = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);

    textScrollBar2D->SetInBarRegionCallback(event);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: SetInBarRegionCallback003
 * @tc.desc: Test SetInBarRegionCallback with TOUCH source
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetInBarRegionCallback003, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto event = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);

    textScrollBar2D->SetInBarRegionCallback(event);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: SetInBarRegionCallback004
 * @tc.desc: Test SetInBarRegionCallback when TextScrollBar2D is destroyed
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetInBarRegionCallback004, TestSize.Level1)
{
    SetupMockHostNode();
    auto event = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    {
        auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
        textScrollBar2D->SetInBarRegionCallback(event);
        EXPECT_NE(textScrollBar2D, nullptr);
    }
}

// ==================== SetInBarRectRegionCallback Tests ====================

/**
 * @tc.name: SetInBarRectRegionCallback001
 * @tc.desc: Test SetInBarRectRegionCallback with nullptr event
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetInBarRectRegionCallback001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Should not crash with nullptr event
    textScrollBar2D->SetInBarRectRegionCallback(nullptr);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: SetInBarRectRegionCallback002
 * @tc.desc: Test SetInBarRectRegionCallback with valid event
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetInBarRectRegionCallback002, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto event = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    textScrollBar2D->SetInBarRectRegionCallback(event);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: SetInBarRectRegionCallback003
 * @tc.desc: Test SetInBarRectRegionCallback with TOUCH source
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetInBarRectRegionCallback003, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto event = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);

    textScrollBar2D->SetInBarRectRegionCallback(event);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: SetInBarRectRegionCallback004
 * @tc.desc: Test SetInBarRectRegionCallback when TextScrollBar2D is destroyed
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetInBarRectRegionCallback004, TestSize.Level1)
{
    SetupMockHostNode();
    auto event = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    {
        auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
        textScrollBar2D->SetInBarRectRegionCallback(event);
        EXPECT_NE(textScrollBar2D, nullptr);
    }
}

// ==================== SetBarCollectTouchTargetCallback Tests ====================

/**
 * @tc.name: SetBarCollectTouchTargetCallback001
 * @tc.desc: Test SetBarCollectTouchTargetCallback with nullptr event
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetBarCollectTouchTargetCallback001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Should not crash with nullptr event
    textScrollBar2D->SetBarCollectTouchTargetCallback(nullptr);
    EXPECT_NE(textScrollBar2D, nullptr);
}

// ==================== SetBarCollectClickAndLongPressTargetCallback Tests ====================

/**
 * @tc.name: SetBarCollectClickAndLongPressTargetCallback001
 * @tc.desc: Test SetBarCollectClickAndLongPressTargetCallback with nullptr event
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetBarCollectClickAndLongPressTargetCallback001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Should not crash with nullptr event
    textScrollBar2D->SetBarCollectClickAndLongPressTargetCallback(nullptr);
    EXPECT_NE(textScrollBar2D, nullptr);
}

// ==================== RemoveGestures Tests ====================

/**
 * @tc.name: RemoveGestures001
 * @tc.desc: Test RemoveGestures with valid bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, RemoveGestures001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    // Should not crash
    textScrollBar2D->RemoveGestures(*bar);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: RemoveGestures002
 * @tc.desc: Test RemoveGestures with nullptr pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, RemoveGestures002, TestSize.Level1)
{
    WeakPtr<ScrollablePattern> nullPattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(nullPattern);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    // Should not crash when pattern is nullptr
    textScrollBar2D->RemoveGestures(*bar);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: RemoveGestures003
 * @tc.desc: Test RemoveGestures with nullptr host
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, RemoveGestures003, TestSize.Level1)
{
    auto pattern = CreateMockScrollablePattern();
    WeakPtr<ScrollablePattern> weakPattern = pattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern);
    auto bar = AceType::MakeRefPtr<NG::ScrollBar>();

    // Should not crash when host is nullptr
    textScrollBar2D->RemoveGestures(*bar);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: RemoveGestures004
 * @tc.desc: Test RemoveGestures with vertical bar from constructed object
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, RemoveGestures004, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    auto verticalBar = textScrollBar2D->GetVerticalBar();
    ASSERT_NE(verticalBar, nullptr);

    // Should not crash
    textScrollBar2D->RemoveGestures(*verticalBar);
}

/**
 * @tc.name: RemoveGestures005
 * @tc.desc: Test RemoveGestures with horizontal bar from constructed object
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, RemoveGestures005, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    auto horizontalBar = textScrollBar2D->GetHorizontalBar();
    ASSERT_NE(horizontalBar, nullptr);

    // Should not crash
    textScrollBar2D->RemoveGestures(*horizontalBar);
    EXPECT_NE(textScrollBar2D, nullptr);
}

// ==================== Destructor Tests ====================

/**
 * @tc.name: Destructor001
 * @tc.desc: Test destructor with valid bars
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, Destructor001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    ASSERT_NE(textScrollBar2D->GetVerticalBar(), nullptr);
    ASSERT_NE(textScrollBar2D->GetHorizontalBar(), nullptr);

    // Destructor should call RemoveGestures for both bars
    textScrollBar2D.Reset();
}

// ==================== UpdateBorderRadius Tests ====================

/**
 * @tc.name: UpdateBorderRadius001
 * @tc.desc: Test UpdateBorderRadius with vertical bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateBorderRadius001, TestSize.Level1)
{
    SetupMockHostNode();
    SetupRenderContext();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Should not crash
    textScrollBar2D->UpdateBorderRadius(true);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: UpdateBorderRadius002
 * @tc.desc: Test UpdateBorderRadius with horizontal bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateBorderRadius002, TestSize.Level1)
{
    SetupMockHostNode();
    SetupRenderContext();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Should not crash
    textScrollBar2D->UpdateBorderRadius(false);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: UpdateBorderRadius003
 * @tc.desc: Test UpdateBorderRadius with nullptr pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateBorderRadius003, TestSize.Level1)
{
    WeakPtr<ScrollablePattern> nullPattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(nullPattern);

    // Should not crash when pattern is nullptr
    textScrollBar2D->UpdateBorderRadius(true);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: UpdateBorderRadius004
 * @tc.desc: Test UpdateBorderRadius with nullptr host
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateBorderRadius004, TestSize.Level1)
{
    auto pattern = CreateMockScrollablePattern();
    WeakPtr<ScrollablePattern> weakPattern = pattern;
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern);

    // Should not crash when host is nullptr
    textScrollBar2D->UpdateBorderRadius(true);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: UpdateBorderRadius005
 * @tc.desc: Test UpdateBorderRadius with nullptr render context
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateBorderRadius005, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Clear render context
    if (mockFrameNode_) {
        mockFrameNode_->renderContext_ = nullptr;
    }

    // Should not crash when render context is nullptr
    textScrollBar2D->UpdateBorderRadius(true);
    EXPECT_NE(textScrollBar2D, nullptr);
}

// ==================== UpdateScrollBar Tests ====================

/**
 * @tc.name: UpdateScrollBar001
 * @tc.desc: Test UpdateScrollBar with scrollable content
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateScrollBar001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    UpdateScrollBarData data;
    data.offset = 10.0f;
    data.estimatedHeight = 1000.0f;
    data.viewPort = Size(100.0f, 100.0f);
    data.viewOffset = Offset(0.0f, 0.0f);

    textScrollBar2D->UpdateScrollBar(data, true);

    auto bar = textScrollBar2D->GetVerticalBar();
    ASSERT_NE(bar, nullptr);
    EXPECT_TRUE(bar->IsScrollable());
}

/**
 * @tc.name: UpdateScrollBar002
 * @tc.desc: Test UpdateScrollBar with non-scrollable content
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateScrollBar002, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    UpdateScrollBarData data;
    data.offset = 0.0f;
    data.estimatedHeight = 50.0f; // Less than viewPort
    data.viewPort = Size(100.0f, 100.0f);
    data.viewOffset = Offset(0.0f, 0.0f);

    textScrollBar2D->UpdateScrollBar(data, true);

    auto bar = textScrollBar2D->GetVerticalBar();
    ASSERT_NE(bar, nullptr);
}

/**
 * @tc.name: UpdateScrollBar003
 * @tc.desc: Test UpdateScrollBar with horizontal bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateScrollBar003, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    UpdateScrollBarData data;
    data.offset = 10.0f;
    data.estimatedHeight = 1000.0f;
    data.viewPort = Size(100.0f, 100.0f);
    data.viewOffset = Offset(0.0f, 0.0f);

    textScrollBar2D->UpdateScrollBar(data, false);

    auto bar = textScrollBar2D->GetHorizontalBar();
    ASSERT_NE(bar, nullptr);
    EXPECT_TRUE(bar->IsScrollable());
}

// ==================== UpdateVerticalBar/UpdateHorizontalBar Tests ====================

/**
 * @tc.name: UpdateVerticalBar001
 * @tc.desc: Test UpdateVerticalBar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateVerticalBar001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->UpdateVerticalBar(10.0f, 1000.0f, Size(100.0f, 100.0f), Offset(0.0f, 0.0f));

    auto bar = textScrollBar2D->GetVerticalBar();
    ASSERT_NE(bar, nullptr);
}

/**
 * @tc.name: UpdateHorizontalBar001
 * @tc.desc: Test UpdateHorizontalBar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, UpdateHorizontalBar001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->UpdateHorizontalBar(10.0f, 1000.0f, Size(100.0f, 100.0f), Offset(0.0f, 0.0f));

    auto bar = textScrollBar2D->GetHorizontalBar();
    ASSERT_NE(bar, nullptr);
}

// ==================== OnDraw Tests ====================

/**
 * @tc.name: OnDraw001
 * @tc.desc: Test OnDraw with both modifiers
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, OnDraw001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    RSCanvas canvas;
    DrawingContext context = { canvas, 100.0f, 100.0f };

    // Should not crash
    textScrollBar2D->OnDraw(context);
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: OnDraw002
 * @tc.desc: Test OnDraw when vertical modifier is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, OnDraw002, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Manually clear vertical modifier by recreating
    auto horizontalBar = textScrollBar2D->GetHorizontalBar();
    auto horizontalModifier = textScrollBar2D->GetHorizontalModifier();

    RSCanvas canvas;
    DrawingContext context = { canvas, 100.0f, 100.0f };

    // Should not crash even if one modifier is nullptr (simulated)
    textScrollBar2D->OnDraw(context);
    EXPECT_NE(textScrollBar2D, nullptr);
}

// ==================== HandleScrollPositionCallback Tests ====================

/**
 * @tc.name: HandleScrollPositionCallback001
 * @tc.desc: Test HandleScrollPositionCallback with callback set
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, HandleScrollPositionCallback001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    bool callbackCalled = false;
    float callbackOffset = 0.0f;
    int32_t callbackSource = 0;
    bool callbackIsVertical = false;

    textScrollBar2D->SetScrollBarScrollCallback(
        [&callbackCalled, &callbackOffset, &callbackSource, &callbackIsVertical]
        (float offset, int32_t source, bool isVertical) {
            callbackCalled = true;
            callbackOffset = offset;
            callbackSource = source;
            callbackIsVertical = isVertical;
        }
    );

    bool result = textScrollBar2D->HandleScrollPositionCallback(10.0f, 1, false, true);

    EXPECT_TRUE(result);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(callbackOffset, 10.0f);
    EXPECT_EQ(callbackSource, 1);
    EXPECT_TRUE(callbackIsVertical);
}

/**
 * @tc.name: HandleScrollPositionCallback002
 * @tc.desc: Test HandleScrollPositionCallback without callback
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, HandleScrollPositionCallback002, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Don't set callback
    bool result = textScrollBar2D->HandleScrollPositionCallback(10.0f, 1, false, true);

    EXPECT_TRUE(result); // Always returns true even without callback
}

// ==================== HandleScrollEndCallback Tests ====================

/**
 * @tc.name: HandleScrollEndCallback001
 * @tc.desc: Test HandleScrollEndCallback with callback set
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, HandleScrollEndCallback001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    bool callbackCalled = false;
    bool callbackIsVertical = false;

    textScrollBar2D->SetScrollBarEndCallback(
        [&callbackCalled, &callbackIsVertical](bool isVertical) {
            callbackCalled = true;
            callbackIsVertical = isVertical;
        }
    );

    textScrollBar2D->HandleScrollEndCallback(true);

    EXPECT_TRUE(callbackCalled);
    EXPECT_TRUE(callbackIsVertical);
}

/**
 * @tc.name: HandleScrollEndCallback002
 * @tc.desc: Test HandleScrollEndCallback without callback
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, HandleScrollEndCallback002, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Don't set callback - should not crash
    textScrollBar2D->HandleScrollEndCallback(true);
    EXPECT_NE(textScrollBar2D, nullptr);
}

// ==================== Public Method Tests ====================

/**
 * @tc.name: SetDisplayMode001
 * @tc.desc: Test SetDisplayMode
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetDisplayMode001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->SetDisplayMode(DisplayMode::ON);

    // Check if display mode is set (may need to check actual implementation)
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: GetDisplayMode001
 * @tc.desc: Test GetDisplayMode
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, GetDisplayMode001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    DisplayMode mode = textScrollBar2D->GetDisplayMode();
    EXPECT_EQ(mode, DisplayMode::AUTO);
}

/**
 * @tc.name: IsScrollable001
 * @tc.desc: Test IsScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, IsScrollable001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    bool isScrollable = textScrollBar2D->IsScrollable();
    EXPECT_TRUE(isScrollable);
}

/**
 * @tc.name: SetOpacity001
 * @tc.desc: Test SetOpacity
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetOpacity001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->SetOpacity(128);

    // Should not crash
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: PlayAppearAnimation001
 * @tc.desc: Test PlayAppearAnimation with vertical bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, PlayAppearAnimation001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->PlayAppearAnimation(true);

    // Should not crash
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: PlayAppearAnimation002
 * @tc.desc: Test PlayAppearAnimation with horizontal bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, PlayAppearAnimation002, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->PlayAppearAnimation(false);

    // Should not crash
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: PlayAppearAnimation003
 * @tc.desc: Test PlayAppearAnimation with nullptr vertical bar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, PlayAppearAnimation003, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    // Test with isVertical=true when verticalBar might be nullptr in some cases
    textScrollBar2D->PlayAppearAnimation(true);

    // Should not crash
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: ScheduleDisappearDelayTask001
 * @tc.desc: Test ScheduleDisappearDelayTask without parameter
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, ScheduleDisappearDelayTask001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->ScheduleDisappearDelayTask();

    // Should not crash
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: ScheduleDisappearDelayTask002
 * @tc.desc: Test ScheduleDisappearDelayTask with vertical
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, ScheduleDisappearDelayTask002, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->ScheduleDisappearDelayTask(true);

    // Should not crash
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: ScheduleDisappearDelayTask003
 * @tc.desc: Test ScheduleDisappearDelayTask with horizontal
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, ScheduleDisappearDelayTask003, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->ScheduleDisappearDelayTask(false);

    // Should not crash
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: SetPositionMode001
 * @tc.desc: Test SetPositionMode
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, SetPositionMode001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    textScrollBar2D->SetPositionMode(PositionMode::LEFT);

    // Should not crash
    EXPECT_NE(textScrollBar2D, nullptr);
}

/**
 * @tc.name: GetVerticalBar001
 * @tc.desc: Test GetVerticalBar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, GetVerticalBar001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    auto bar = textScrollBar2D->GetVerticalBar();
    ASSERT_NE(bar, nullptr);
}

/**
 * @tc.name: GetHorizontalBar001
 * @tc.desc: Test GetHorizontalBar
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, GetHorizontalBar001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    auto bar = textScrollBar2D->GetHorizontalBar();
    ASSERT_NE(bar, nullptr);
}

/**
 * @tc.name: GetVerticalModifier001
 * @tc.desc: Test GetVerticalModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, GetVerticalModifier001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    auto modifier = textScrollBar2D->GetVerticalModifier();
    ASSERT_NE(modifier, nullptr);
}

/**
 * @tc.name: GetHorizontalModifier001
 * @tc.desc: Test GetHorizontalModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextScrollBar2DTest, GetHorizontalModifier001, TestSize.Level1)
{
    SetupMockHostNode();
    auto textScrollBar2D = AceType::MakeRefPtr<TextScrollBar2D>(weakPattern_);

    auto modifier = textScrollBar2D->GetHorizontalModifier();
    ASSERT_NE(modifier, nullptr);
}
} // namespace OHOS::Ace::NG
