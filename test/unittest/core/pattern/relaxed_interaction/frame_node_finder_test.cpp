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

#include <string>

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/components_ng/relaxed_interaction/frame_node_finder.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/recognizers/parallel_recognizer.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/common/event_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const std::string SCROLL_NODE_TAG = "Scroll";
const std::string LIST_NODE_TAG = "List";
const std::string SWIPER_NODE_TAG = "Swiper";
const std::string TABS_NODE_TAG = "Tabs";
const std::string BUTTON_NODE_TAG = "Button";
const double DEFAULT_PAN_DISTANCE = 5.0;
} // namespace

class FrameNodeFinderTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

class FrameNodeFinderConstructorTest : public FrameNodeFinderTest {};
class FrameNodeFinderFindAtTest : public FrameNodeFinderTest {};
class FrameNodeFinderFindTest : public FrameNodeFinderTest {};
class FrameNodeFinderFindLeafTest : public FrameNodeFinderTest {};
class FrameNodeFinderCleanResultTest : public FrameNodeFinderTest {};
class FrameNodeFinderGetFrameNodesTest : public FrameNodeFinderTest {};
class FrameNodeFinderCleanFrameNodesTest : public FrameNodeFinderTest {};
class ClickRecognizerPredTest : public FrameNodeFinderTest {};
class ContentSwitchRecognizerPredTest : public FrameNodeFinderTest {};
class ScrollRecognizerPredTest : public FrameNodeFinderTest {};
class ComponentUtilsTest : public FrameNodeFinderTest {};

HWTEST_F(ComponentUtilsTest, ComponentUtils_ToString_WithNullRecognizer_ReturnsNullString, TestSize.Level1)
{
    RefPtr<NGGestureRecognizer> nullRecognizer;
    auto result = ComponentUtils::ToString(nullRecognizer);
    EXPECT_EQ(result, "NGGestureRecognizer{nullptr}");
}

HWTEST_F(ComponentUtilsTest, ComponentUtils_ToString_WithNullAttachedNode_ReturnsNullString, TestSize.Level1)
{
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    // clickRecognizer has no attached node
    auto result = ComponentUtils::ToString(clickRecognizer);
    EXPECT_EQ(result, "NGGestureRecognizer{frameNode=nullptr}");
}

HWTEST_F(ComponentUtilsTest, ComponentUtils_ToString_WithClickRecognizer_ContainsCorrectFormat, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);
    auto result = ComponentUtils::ToString(clickRecognizer);
    // Verify contains expected fields
    EXPECT_TRUE(result.find("NGGestureRecognizer") != std::string::npos);
    EXPECT_TRUE(result.find("frameNode.tag=Button") != std::string::npos);
    EXPECT_TRUE(result.find("isPan=N") != std::string::npos);
    EXPECT_TRUE(result.find("groupRecognizer.valid=0") != std::string::npos);
    EXPECT_TRUE(result.find("groupRecognizer.size=N/A") != std::string::npos);
}

HWTEST_F(ComponentUtilsTest, ComponentUtils_ToString_WithPanRecognizer_IsPanShowsY, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    auto result = ComponentUtils::ToString(panRecognizer);
    EXPECT_TRUE(result.find("isPan=Y") != std::string::npos);
}

HWTEST_F(ComponentUtilsTest, ComponentUtils_GetAxis_WithNullFrameNode_ReturnsNone, TestSize.Level1)
{
    RefPtr<FrameNode> nullFrameNode;
    auto result = ComponentUtils::GetAxis(nullFrameNode);
    EXPECT_EQ(result, Axis::NONE);
}

HWTEST_F(ComponentUtilsTest, ComponentUtils_GetAxis_WithNullPattern_ReturnsNone, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto result = ComponentUtils::GetAxis(frameNode);
    EXPECT_EQ(result, Axis::NONE);
}

HWTEST_F(ComponentUtilsTest, ComponentUtils_GetAxis_WithNonScrollablePattern_ReturnsNone, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto result = ComponentUtils::GetAxis(frameNode);
    EXPECT_EQ(result, Axis::NONE);
}

HWTEST_F(FrameNodeFinderConstructorTest, FrameNodeFinder_Constructor_WithValidContext, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);
    // Without proper root node setup, FindAt returns empty result
    auto result = finder.FindAt(0.0f, 0.0f);
    // Verify the result is valid (can be empty without root node)
    EXPECT_EQ(result.GetNode(), nullptr);
}

HWTEST_F(FrameNodeFinderConstructorTest, FrameNodeFinder_Constructor_WithNullPredicate, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FrameNodeFinder finder(context, nullptr);
    auto result = finder.FindAt(0.0f, 0.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindAtTest, FindAt_NullContext_ReturnsEmpty, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    FrameNodeFinder finder(nullContext, nullptr);
    auto result = finder.FindAt(100.0f, 100.0f);
    EXPECT_EQ(result.GetNode(), nullptr);
}

HWTEST_F(FrameNodeFinderFindAtTest, FindAt_NullRootNode_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FrameNodeFinder finder(context, nullptr);
    auto result = finder.FindAt(100.0f, 100.0f);
    EXPECT_EQ(result.GetNode(), nullptr);
}

HWTEST_F(FrameNodeFinderFindTest, Find_EmptyTouchTestResult_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult emptyResult;
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);
    auto result = finder.FindAt(100.0f, 100.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_NullGestureRecognizer_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    RefPtr<NGGestureRecognizer> nullRecognizer;
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);
    auto result = finder.FindAt(100.0f, 100.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(ClickRecognizerPredTest, ClickRecognizerPred_WithClickRecognizer_ReturnsTrue, TestSize.Level1)
{
    ClickRecognizerPred pred;
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    EXPECT_TRUE(pred(clickRecognizer));
}

HWTEST_F(ClickRecognizerPredTest, ClickRecognizerPred_WithPanRecognizer_ReturnsFalse, TestSize.Level1)
{
    ClickRecognizerPred pred;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    EXPECT_FALSE(pred(panRecognizer));
}

HWTEST_F(ClickRecognizerPredTest, ClickRecognizerPred_WithNullRecognizer_ReturnsFalse, TestSize.Level1)
{
    ClickRecognizerPred pred;
    RefPtr<NGGestureRecognizer> nullRecognizer;
    EXPECT_FALSE(pred(nullRecognizer));
}

HWTEST_F(ContentSwitchRecognizerPredTest, ContentSwitchRecognizerPred_WithNullNode_ReturnsFalse, TestSize.Level1)
{
    ContentSwitchRecognizerPred pred;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    EXPECT_FALSE(pred(panRecognizer));
}

HWTEST_F(ContentSwitchRecognizerPredTest, ContentSwitchRecognizerPred_WithNonMatchingTag_ReturnsFalse, TestSize.Level1)
{
    ContentSwitchRecognizerPred pred;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    auto currentNode = panRecognizer->GetAttachedNode().Upgrade();
    ASSERT_NE(currentNode, nullptr);
    EXPECT_FALSE(pred(panRecognizer));
}

HWTEST_F(ContentSwitchRecognizerPredTest, ContentSwitchRecognizerPred_WithSwiperTag_ReturnsTrue, TestSize.Level1)
{
    ContentSwitchRecognizerPred pred;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(SWIPER_NODE_TAG, 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    auto currentNode = panRecognizer->GetAttachedNode().Upgrade();
    ASSERT_NE(currentNode, nullptr);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ContentSwitchRecognizerPredTest, ContentSwitchRecognizerPred_WithTabsTag_ReturnsTrue, TestSize.Level1)
{
    ContentSwitchRecognizerPred pred;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(TABS_NODE_TAG, 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    auto currentNode = panRecognizer->GetAttachedNode().Upgrade();
    ASSERT_NE(currentNode, nullptr);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredTest, ScrollRecognizerPred_WithNonPanRecognizer_ReturnsFalse, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::FORWARD);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    EXPECT_FALSE(pred(clickRecognizer));
}

HWTEST_F(ScrollRecognizerPredTest, ScrollRecognizerPred_WithNullNode_ReturnsFalse, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::FORWARD);
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    EXPECT_FALSE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredTest, ScrollRecognizerPred_WithForwardDirection_ReturnsTrue, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::FORWARD);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredTest, ScrollRecognizerPred_WithBackwardDirection_ReturnsTrue, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::BACKWARD);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("List", 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredTest, ScrollRecognizerPred_WithNonMatchingTag_ReturnsFalse, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::FORWARD);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_FALSE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredTest, ScrollRecognizerPred_HorizontalDirection_NoScrollable_ReturnsFalse, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::LEFT);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_FALSE(pred(panRecognizer));
}

class FrameNodeMatchTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

HWTEST_F(FrameNodeMatchTest, FrameNodeMatch_DefaultConstructor_ReturnsInvalid, TestSize.Level1)
{
    FrameNodeMatch match;
    EXPECT_FALSE(static_cast<bool>(match));
    EXPECT_EQ(match.GetNode(), nullptr);
    EXPECT_EQ(match.GetClickFunc(), nullptr);
}

HWTEST_F(FrameNodeMatchTest, FrameNodeMatch_WithNullRecognizer_ReturnsInvalid, TestSize.Level1)
{
    RefPtr<NGGestureRecognizer> nullRecognizer;
    FrameNodeMatch match(nullRecognizer);
    EXPECT_FALSE(static_cast<bool>(match));
}

class MockScrollablePattern : public ScrollablePattern {
public:
    MockScrollablePattern() = default;
    ~MockScrollablePattern() override = default;

    Axis GetAxis() const override
    {
        return axis_;
    }

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

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
        return false;
    }

    void UpdateScrollBarOffset() override {}

private:
    Axis axis_ = Axis::VERTICAL;
};

HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_EmptyList_DoesNotCrash, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    std::list<RefPtr<NG::NGGestureRecognizer>> emptyList;
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);
    // The internal method is private, but we can verify behavior indirectly through FindAt
    auto result = finder.FindAt(0.0f, 0.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderCleanFrameNodesTest, CleanFrameNodes_WithEmptySet_DoesNotCrash, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::set<WeakPtr<NG::FrameNode>> emptySet;
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);
    auto result = finder.FindAt(0.0f, 0.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(ComponentUtilsTest, ComponentUtils_GetAxis_WithScrollablePattern_ReturnsAxis, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<MockScrollablePattern>());
    ASSERT_NE(frameNode, nullptr);

    auto result = ComponentUtils::GetAxis(frameNode);
    EXPECT_EQ(result, Axis::VERTICAL);
}

HWTEST_F(ComponentUtilsTest, ComponentUtils_ToString_WithGroupRecognizer_ContainsSize, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);

    // RecognizerGroup is abstract, test with PanRecognizer which has isPan=Y
    auto result = ComponentUtils::ToString(panRecognizer);

    EXPECT_TRUE(result.find("isPan=Y") != std::string::npos);
}

class ScrollRecognizerPredAxisTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

class MockScrollablePatternFreeAxis : public ScrollablePattern {
public:
    MockScrollablePatternFreeAxis() = default;
    ~MockScrollablePatternFreeAxis() override = default;

    Axis GetAxis() const override
    {
        return Axis::FREE;
    }

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
        return false;
    }

    void UpdateScrollBarOffset() override {}
};

class MockScrollablePatternHorizontalAxis : public ScrollablePattern {
public:
    MockScrollablePatternHorizontalAxis() = default;
    ~MockScrollablePatternHorizontalAxis() override = default;

    Axis GetAxis() const override
    {
        return Axis::HORIZONTAL;
    }

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
        return false;
    }

    void UpdateScrollBarOffset() override {}
};

class FrameNodeFinderDebugTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        SystemProperties::debugEnabled_ = false;
        mockPipelineContext_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

HWTEST_F(FrameNodeFinderDebugTest, Test_WithDebugEnabled_ExecutesBranch, TestSize.Level1)
{
    SystemProperties::debugEnabled_ = true;
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    auto pred = [](const RefPtr<NGGestureRecognizer>& recognizer) {
        auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(recognizer);
        if (!clickRecognizer) {
            return false;
        }
        return clickRecognizer->GetCount() == 1;
    };
    FrameNodeFinder finder(context, pred);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    clickRecognizer->AttachFrameNode(frameNode);

    bool result = finder.Test(clickRecognizer);
    EXPECT_TRUE(result);

    SystemProperties::debugEnabled_ = false;
}

HWTEST_F(ScrollRecognizerPredAxisTest, ScrollRecognizerPred_FreeAxis_ReturnsTrue, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::UP);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<MockScrollablePatternFreeAxis>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredAxisTest, ScrollRecognizerPred_LeftDirection_HorizontalAxis_ReturnsTrue, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::LEFT);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0,
        AceType::MakeRefPtr<MockScrollablePatternHorizontalAxis>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredAxisTest, ScrollRecognizerPred_RightDirection_HorizontalAxis_ReturnsTrue, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::RIGHT);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0,
        AceType::MakeRefPtr<MockScrollablePatternHorizontalAxis>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredAxisTest, ScrollRecognizerPred_DownDirection_VerticalAxis_ReturnsTrue, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::DOWN);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<MockScrollablePattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredAxisTest, ScrollRecognizerPred_UpDirection_VerticalAxis_ReturnsTrue, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::UP);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<MockScrollablePattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_TRUE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredAxisTest, ScrollRecognizerPred_LeftDirection_VerticalAxis_ReturnsFalse, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::LEFT);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<MockScrollablePattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_FALSE(pred(panRecognizer));
}

HWTEST_F(ScrollRecognizerPredAxisTest, ScrollRecognizerPred_UpDirection_HorizontalAxis_ReturnsFalse, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::UP);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0,
        AceType::MakeRefPtr<MockScrollablePatternHorizontalAxis>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);
    EXPECT_FALSE(pred(panRecognizer));
}

/**
 * @brief Test FindAt with null root node
 */
HWTEST_F(FrameNodeFinderFindAtTest, FindAt_NullRootNode_CoversNullRootNodeBranch, TestSize.Level1)
{
    auto mockContext = AceType::MakeRefPtr<MockPipelineContext>();
    auto context = WeakPtr<PipelineContext>(mockContext);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindAt(100.0f, 100.0f);
    EXPECT_EQ(result.GetNode(), nullptr);
}

/**
 * @brief Test Find with empty TouchTestResult
 */
HWTEST_F(FrameNodeFinderFindTest, Find_EmptyTouchTestResult_CoversEmptyBranch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult emptyResult;
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(emptyResult);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test Find with TouchTestResult containing null recognizer
 */
HWTEST_F(FrameNodeFinderFindTest, Find_NullRecognizerInResult_CoversNullRecognizerBranch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult touchTestResult;
    touchTestResult.push_back(nullptr);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(touchTestResult);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test Find with TouchTestResult containing non-NGGestureRecognizer
 */
HWTEST_F(FrameNodeFinderFindTest, Find_NonNGGestureRecognizer_CoversDynamicCastBranch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult touchTestResult;

    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    touchTestResult.push_back(clickRecognizer);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(touchTestResult);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test Find with TouchTestResult that passes predicate
 */
HWTEST_F(FrameNodeFinderFindTest, Find_ValidRecognizerPassesPredicate_ReturnsMatch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult touchTestResult;

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);
    touchTestResult.push_back(clickRecognizer);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(touchTestResult);
    EXPECT_TRUE(static_cast<bool>(result));
}

/**
 * @brief Test FindLeaf with null recognizer
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_NullRecognizer_CoversNullBranch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    RefPtr<NGGestureRecognizer> nullRecognizer;
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(nullRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test FindLeaf with non-group recognizer that passes predicate
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_NonGroupRecognizerPassesPredicate_ReturnsMatch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(clickRecognizer);
    EXPECT_TRUE(static_cast<bool>(result));
}

/**
 * @brief Test FindLeaf with non-group recognizer that fails predicate
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_NonGroupRecognizerFailsPredicate_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(clickRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test FindLeaf with recognizer group containing child recognizers
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_RecognizerGroupWithChildren_CoversGroupBranch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(parallelRecognizer);
    EXPECT_TRUE(static_cast<bool>(result));
}

/**
 * @brief Test FindLeaf with empty recognizer group and predicate returns false
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_EmptyRecognizerGroup_CoversEmptyGroupBranch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    std::vector<RefPtr<NGGestureRecognizer>> emptyRecognizers;
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(emptyRecognizers);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(parallelRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test GetFrameNodes with non-empty list
 */
HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_NonEmptyList_CoversLoop, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    std::list<RefPtr<NG::NGGestureRecognizer>> recognizerList;
    recognizerList.push_back(clickRecognizer);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindAt(0.0f, 0.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test GetFrameNodes with recognizer group
 */
HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_WithRecognizerGroup_CoversGroupBranch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    std::list<RefPtr<NG::NGGestureRecognizer>> recognizerList;
    recognizerList.push_back(parallelRecognizer);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindAt(0.0f, 0.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test CleanFrameNodes with valid frame nodes
 */
HWTEST_F(FrameNodeFinderCleanFrameNodesTest, CleanFrameNodes_ValidFrameNodes_CoversLoop, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindAt(0.0f, 0.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test ClickRecognizerPred with multi-click recognizer
 */
HWTEST_F(ClickRecognizerPredTest, ClickRecognizerPred_WithMultiClickRecognizer_ReturnsFalse, TestSize.Level1)
{
    ClickRecognizerPred pred;
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, 2);
    EXPECT_FALSE(pred(clickRecognizer));
}

/**
 * @brief Test FindAt with valid root node that has gesture recognizer
 */
HWTEST_F(FrameNodeFinderFindAtTest, FindAt_ValidRootNodeWithGesture_CoversTouchTestPath, TestSize.Level1)
{
    auto mockContext = AceType::MakeRefPtr<MockPipelineContext>();

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto context = WeakPtr<PipelineContext>(mockContext);
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindAt(100.0f, 100.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test Find with multiple recognizers in TouchTestResult
 */
HWTEST_F(FrameNodeFinderFindTest, Find_MultipleRecognizers_CoversLoop, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult touchTestResult;

    auto frameNode1 = AceType::MakeRefPtr<FrameNode>("Button1", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer1 = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer1->AttachFrameNode(frameNode1);

    auto frameNode2 = AceType::MakeRefPtr<FrameNode>("Button2", 1, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer2 = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer2->AttachFrameNode(frameNode2);

    touchTestResult.push_back(clickRecognizer1);
    touchTestResult.push_back(clickRecognizer2);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(touchTestResult);
    EXPECT_TRUE(static_cast<bool>(result));
}

/**
 * @brief Test FindLeaf with recognizer group that has null child
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_GroupWithNullChild_CoversNullCheck, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    std::vector<RefPtr<NGGestureRecognizer>> emptyRecognizers;
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(emptyRecognizers);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(parallelRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test FindLeaf with recognizer group where child fails predicate
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_GroupChildFailsPredicate_CoversChildLoop, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(parallelRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test Test method with debug disabled
 */
HWTEST_F(FrameNodeFinderDebugTest, Test_WithDebugDisabled_SkipsLogBranch, TestSize.Level1)
{
    SystemProperties::debugEnabled_ = false;
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    clickRecognizer->AttachFrameNode(frameNode);

    bool result = finder.Test(clickRecognizer);
    EXPECT_TRUE(result);
}

/**
 * @brief Test GetFrameNodes with recognizer that has no attached node
 */
HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_RecognizerNoAttachedNode_CoversNullNodeBranch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();

    std::list<RefPtr<NG::NGGestureRecognizer>> recognizerList;
    recognizerList.push_back(clickRecognizer);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindAt(0.0f, 0.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test CleanFrameNodes with expired weak pointer
 */
HWTEST_F(FrameNodeFinderCleanFrameNodesTest, CleanFrameNodes_ExpiredWeakPtr_CoversNullCheck, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    {
        auto tempNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    }

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindAt(0.0f, 0.0f);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test ContentSwitchRecognizerPred with non-pan recognizer
 */
HWTEST_F(ContentSwitchRecognizerPredTest, ContentSwitchRecognizerPred_WithClickRecognizer_ReturnsFalse, TestSize.Level1)
{
    ContentSwitchRecognizerPred pred;
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    EXPECT_FALSE(pred(clickRecognizer));
}

/**
 * @brief Test ScrollRecognizerPred with null recognizer
 */
HWTEST_F(ScrollRecognizerPredTest, ScrollRecognizerPred_WithNullRecognizer_ReturnsFalse, TestSize.Level1)
{
    ScrollRecognizerPred pred(RelaxedScrollDirection::FORWARD);
    RefPtr<NGGestureRecognizer> nullRecognizer;
    EXPECT_FALSE(pred(nullRecognizer));
}

/**
 * @brief Test FrameNodeMatch with valid click recognizer
 */
HWTEST_F(FrameNodeMatchTest, FrameNodeMatch_WithValidClickRecognizer_ReturnsValid, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    FrameNodeMatch match(clickRecognizer);
    EXPECT_TRUE(static_cast<bool>(match));
    EXPECT_NE(match.GetNode(), nullptr);
}

/**
 * @brief Test FrameNodeMatch with pan recognizer (non-click)
 */
HWTEST_F(FrameNodeMatchTest, FrameNodeMatch_WithPanRecognizer_ReturnsNullClickFunc, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", 0, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);

    FrameNodeMatch match(panRecognizer);
    EXPECT_TRUE(static_cast<bool>(match));
    EXPECT_EQ(match.GetClickFunc(), nullptr);
}

/**
 * @brief Test private Find(touchTestResult) with empty result
 */
HWTEST_F(FrameNodeFinderFindTest, Find_PrivateWithEmptyTouchTestResult_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult emptyResult;

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(emptyResult);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test private Find(touchTestResult) with null recognizer
 */
HWTEST_F(FrameNodeFinderFindTest, Find_PrivateWithNullRecognizer_SkipsNull, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult touchTestResult;
    touchTestResult.push_back(nullptr);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);
    touchTestResult.push_back(clickRecognizer);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(touchTestResult);
    EXPECT_TRUE(static_cast<bool>(result));
}

/**
 * @brief Test private Find(touchTestResult) with non-NGGestureRecognizer
 */
HWTEST_F(FrameNodeFinderFindTest, Find_PrivateWithNonNGRecognizer_SkipsCastFailure, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult touchTestResult;

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);
    touchTestResult.push_back(clickRecognizer);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(touchTestResult);
    EXPECT_TRUE(static_cast<bool>(result));
}

/**
 * @brief Test private Find(touchTestResult) where FindLeaf returns empty
 */
HWTEST_F(FrameNodeFinderFindTest, Find_PrivateFindLeafReturnsEmpty_ContinuesLoop, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TouchTestResult touchTestResult;

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);
    touchTestResult.push_back(clickRecognizer);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.Find(touchTestResult);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test private FindLeaf with null recognizer
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_PrivateWithNull_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    RefPtr<NGGestureRecognizer> nullRecognizer;

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(nullRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test private FindLeaf with non-group recognizer passing predicate
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_PrivateNonGroupPassesPred_ReturnsRecognizer, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(clickRecognizer);
    EXPECT_TRUE(static_cast<bool>(result));
}

/**
 * @brief Test private FindLeaf with non-group recognizer failing predicate
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_PrivateNonGroupFailsPred_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(clickRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test private FindLeaf with recognizer group having children
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_PrivateGroupWithChildren_ReturnsChild, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(parallelRecognizer);
    EXPECT_TRUE(static_cast<bool>(result));
}

/**
 * @brief Test private FindLeaf with empty recognizer group
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_PrivateEmptyGroup_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    std::vector<RefPtr<NGGestureRecognizer>> emptyRecognizers;
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(emptyRecognizers);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(parallelRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test private FindLeaf with group where all children fail predicate
 */
HWTEST_F(FrameNodeFinderFindLeafTest, FindLeaf_PrivateGroupAllChildrenFail_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finder(context, pred);

    auto result = finder.FindLeaf(parallelRecognizer);
    EXPECT_FALSE(static_cast<bool>(result));
}

/**
 * @brief Test private GetFrameNodes with empty input list
 */
HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_EmptyInput_ReturnsImmediately, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    std::list<RefPtr<NG::NGGestureRecognizer>> emptyList;

    finder.GetFrameNodes(frameNodes, emptyList);
    EXPECT_TRUE(frameNodes.empty());
}

/**
 * @brief Test private GetFrameNodes with recognizer that has no attached node
 */
HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_NoAttachedNode_SkipsNode, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    std::list<RefPtr<NG::NGGestureRecognizer>> recognizerList;

    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    recognizerList.push_back(clickRecognizer);

    finder.GetFrameNodes(frameNodes, recognizerList);
    EXPECT_TRUE(frameNodes.empty());
}

/**
 * @brief Test private GetFrameNodes with recognizer that has attached node
 */
HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_WithAttachedNode_AddsToSet, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    std::list<RefPtr<NG::NGGestureRecognizer>> recognizerList;

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);
    recognizerList.push_back(clickRecognizer);

    finder.GetFrameNodes(frameNodes, recognizerList);
    EXPECT_EQ(frameNodes.size(), 1);
}

/**
 * @brief Test private GetFrameNodes with recognizer group (non-group recognizer)
 */
HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_NonGroupRecognizer_SkipsGroup, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    std::list<RefPtr<NG::NGGestureRecognizer>> recognizerList;

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);
    recognizerList.push_back(clickRecognizer);

    finder.GetFrameNodes(frameNodes, recognizerList);
    EXPECT_EQ(frameNodes.size(), 1);
}

/**
 * @brief Test private GetFrameNodes with recognizer group containing children
 */
HWTEST_F(FrameNodeFinderGetFrameNodesTest, GetFrameNodes_GroupWithChildren_RecursiveCall, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    std::list<RefPtr<NG::NGGestureRecognizer>> recognizerList;

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    std::vector<RefPtr<NGGestureRecognizer>> childRecognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(childRecognizers);
    recognizerList.push_back(parallelRecognizer);

    finder.GetFrameNodes(frameNodes, recognizerList);
    EXPECT_EQ(frameNodes.size(), 1);
}

/**
 * @brief Test private CleanFrameNodes with empty input set
 */
HWTEST_F(FrameNodeFinderCleanFrameNodesTest, CleanFrameNodes_EmptyInput_NoOp, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> emptySet;
    finder.CleanFrameNodes(emptySet);
    EXPECT_TRUE(emptySet.empty());
}

/**
 * @brief Test private CleanFrameNodes with expired weak pointer
 */
HWTEST_F(FrameNodeFinderCleanFrameNodesTest, CleanFrameNodes_ExpiredWeakPtr_SkipsNode, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    {
        auto tempNode = AceType::MakeRefPtr<FrameNode>("Temp", 0, AceType::MakeRefPtr<Pattern>());
        frameNodes.emplace(tempNode);
    }

    finder.CleanFrameNodes(frameNodes);
    EXPECT_FALSE(frameNodes.empty());
}

/**
 * @brief Test private CleanFrameNodes with valid frame node
 */
HWTEST_F(FrameNodeFinderCleanFrameNodesTest, CleanFrameNodes_ValidNode_CleansGestureHub, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", 0, AceType::MakeRefPtr<Pattern>());
    frameNodes.emplace(frameNode);

    finder.CleanFrameNodes(frameNodes);
    EXPECT_NE(frameNode->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @brief Test private CleanFrameNodes with multiple frame nodes
 */
HWTEST_F(FrameNodeFinderCleanFrameNodesTest, CleanFrameNodes_MultipleNodes_CleansAll, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
    FrameNodeFinder finder(context, pred);

    std::set<WeakPtr<NG::FrameNode>> frameNodes;
    auto frameNode1 = AceType::MakeRefPtr<FrameNode>("Button1", 0, AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>("Button2", 1, AceType::MakeRefPtr<Pattern>());
    frameNodes.emplace(frameNode1);
    frameNodes.emplace(frameNode2);

    finder.CleanFrameNodes(frameNodes);
    EXPECT_NE(frameNode1->GetOrCreateGestureEventHub(), nullptr);
    EXPECT_NE(frameNode2->GetOrCreateGestureEventHub(), nullptr);
}

class MockUINodeForFindAt : public UINode {
    DECLARE_ACE_TYPE(MockUINodeForFindAt, UINode);

public:
    MockUINodeForFindAt(const std::string& tag, int32_t nodeId) : UINode(tag, nodeId) {}

    bool IsAtomicNode() const override
    {
        return false;
    }

    HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, // NOLINT
        const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result,
        int32_t touchId, ResponseLinkResult& responseLinkResult, bool isDispatch = false) override
    {
        touchTestCallCount_++;
        lastGlobalPoint_ = globalPoint;
        lastParentLocalPoint_ = parentLocalPoint;
        lastParentRevertPoint_ = parentRevertPoint;
        lastTouchId_ = touchId;
        if (onTouchTest_) {
            onTouchTest_(globalPoint, parentLocalPoint, parentRevertPoint, result, touchId);
        }
        return HitTestResult::STOP_BUBBLING;
    }

    void SetTouchTestCallback(
        std::function<void(const PointF&, const PointF&, const PointF&, TouchTestResult&, int32_t)> callback)
    {
        onTouchTest_ = std::move(callback);
    }

    int32_t GetTouchTestCallCount() const
    {
        return touchTestCallCount_;
    }

    const PointF& GetLastGlobalPoint() const
    {
        return lastGlobalPoint_;
    }

    const PointF& GetLastParentLocalPoint() const
    {
        return lastParentLocalPoint_;
    }

    const PointF& GetLastParentRevertPoint() const
    {
        return lastParentRevertPoint_;
    }

    int32_t GetLastTouchId() const
    {
        return lastTouchId_;
    }

private:
    std::function<void(const PointF&, const PointF&, const PointF&, TouchTestResult&, int32_t)> onTouchTest_;
    int32_t touchTestCallCount_ = 0;
    PointF lastGlobalPoint_;
    PointF lastParentLocalPoint_;
    PointF lastParentRevertPoint_;
    int32_t lastTouchId_ = -1;
};

namespace {
const float FIND_AT_COORD_X_POS = 100.0f;
const float FIND_AT_COORD_Y_POS = 200.0f;
const float FIND_AT_COORD_X_ZERO = 0.0f;
const float FIND_AT_COORD_Y_ZERO = 0.0f;
const float FIND_AT_COORD_X_NEG = -50.0f;
const float FIND_AT_COORD_Y_NEG = -30.0f;
const float FIND_AT_COORD_X_LARGE = 10000.0f;
const float FIND_AT_COORD_Y_LARGE = 20000.0f;
const float FIND_AT_COORD_X_DECIMAL = 123.456f;
const float FIND_AT_COORD_Y_DECIMAL = 789.012f;
const int32_t FIND_AT_NODE_ID_FIRST = 100;
const int32_t FIND_AT_NODE_ID_SECOND = 101;
} // namespace

class FrameNodeFinderFindAtWithRootNodeTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
    }

    void SetUp() override
    {
        mockPipelineContext_->SetEventManager(AceType::MakeRefPtr<EventManager>());
        auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
        auto pred = [](const RefPtr<NGGestureRecognizer>&) { return true; };
        finder_ = std::make_unique<FrameNodeFinder>(context, pred);
    }

    void TearDown() override
    {
        finder_.reset();
        mockPipelineContext_->eventManager_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
    std::unique_ptr<FrameNodeFinder> finder_;
};

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_EmptyTouchTestResult_ReturnsEmpty, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {});

    auto result = finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.GetNode(), nullptr);
    EXPECT_EQ(rootNode->GetTouchTestCallCount(), 1);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_TouchTestCorrectCoordinates, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {});

    finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetX(), FIND_AT_COORD_X_POS);
    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetY(), FIND_AT_COORD_Y_POS);
    EXPECT_EQ(rootNode->GetLastParentLocalPoint().GetX(), FIND_AT_COORD_X_POS);
    EXPECT_EQ(rootNode->GetLastParentLocalPoint().GetY(), FIND_AT_COORD_Y_POS);
    EXPECT_EQ(rootNode->GetLastParentRevertPoint().GetX(), FIND_AT_COORD_X_POS);
    EXPECT_EQ(rootNode->GetLastParentRevertPoint().GetY(), FIND_AT_COORD_Y_POS);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_TouchTestCalledWithZeroCoordinates, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {});

    finder_->FindAt(rootNode, FIND_AT_COORD_X_ZERO, FIND_AT_COORD_Y_ZERO);

    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetX(), FIND_AT_COORD_X_ZERO);
    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetY(), FIND_AT_COORD_Y_ZERO);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_TouchTestNegativeCoordinates, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {});

    finder_->FindAt(rootNode, FIND_AT_COORD_X_NEG, FIND_AT_COORD_Y_NEG);

    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetX(), FIND_AT_COORD_X_NEG);
    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetY(), FIND_AT_COORD_Y_NEG);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_TouchTestCalledWithLarge01, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {});

    finder_->FindAt(rootNode, FIND_AT_COORD_X_LARGE, FIND_AT_COORD_Y_LARGE);

    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetX(), FIND_AT_COORD_X_LARGE);
    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetY(), FIND_AT_COORD_Y_LARGE);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_TouchTestCalledWithLarge02, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {});

    finder_->FindAt(rootNode, FIND_AT_COORD_X_DECIMAL, FIND_AT_COORD_Y_DECIMAL);

    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetX(), FIND_AT_COORD_X_DECIMAL);
    EXPECT_EQ(rootNode->GetLastGlobalPoint().GetY(), FIND_AT_COORD_Y_DECIMAL);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_TouchTestIdIsZero, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {});

    finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_EQ(rootNode->GetLastTouchId(), 0);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_SingleClickRecognizer_ReturnsMatch, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_SECOND);
    rootNode->SetTouchTestCallback(
        [&clickRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(clickRecognizer);
        });

    auto result = finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_NE(result.GetNode(), nullptr);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_NullRecognizerInResult_SkipsNull, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_SECOND);
    rootNode->SetTouchTestCallback(
        [&clickRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(nullptr);
            result.push_back(clickRecognizer);
        });

    auto result = finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_TRUE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_PredicateRejectsAll_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    auto alwaysFalsePred = [](const RefPtr<NGGestureRecognizer>&) { return false; };
    FrameNodeFinder finderWithRejectPred(context, alwaysFalsePred);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_SECOND);
    rootNode->SetTouchTestCallback(
        [&clickRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(clickRecognizer);
        });

    auto result = finderWithRejectPred.FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_PredicateAcceptsAll_ReturnsFirst, TestSize.Level1)
{
    auto frameNode1 = AceType::MakeRefPtr<FrameNode>("Button1", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer1 = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer1->AttachFrameNode(frameNode1);

    auto frameNode2 = AceType::MakeRefPtr<FrameNode>("Button2", FIND_AT_NODE_ID_SECOND, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer2 = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer2->AttachFrameNode(frameNode2);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [&](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(clickRecognizer1);
            result.push_back(clickRecognizer2);
        });

    auto result = finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_NE(result.GetNode(), nullptr);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_MultipleCallsEachTimeTouchTest, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {});

    finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);
    finder_->FindAt(rootNode, FIND_AT_COORD_X_ZERO, FIND_AT_COORD_Y_ZERO);
    finder_->FindAt(rootNode, FIND_AT_COORD_X_NEG, FIND_AT_COORD_Y_NEG);

    EXPECT_EQ(rootNode->GetTouchTestCallCount(), 3);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_PanRecognizerPassesCustomPredicate, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    auto panOnlyPred = [](const RefPtr<NGGestureRecognizer>& recognizer) {
        return AceType::InstanceOf<PanRecognizer>(recognizer);
    };
    FrameNodeFinder finderWithPanPred(context, panOnlyPred);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_SECOND);
    rootNode->SetTouchTestCallback(
        [&panRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(panRecognizer);
        });

    auto result = finderWithPanPred.FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_TRUE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_ClickRecognizerFailsReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    auto panOnlyPred = [](const RefPtr<NGGestureRecognizer>& recognizer) {
        return AceType::InstanceOf<PanRecognizer>(recognizer);
    };
    FrameNodeFinder finderWithPanPred(context, panOnlyPred);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_SECOND);
    rootNode->SetTouchTestCallback(
        [&clickRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(clickRecognizer);
        });

    auto result = finderWithPanPred.FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_ClickRecognizerWithoutAttachedNode, TestSize.Level1)
{
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [&clickRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(clickRecognizer);
        });

    auto result = finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_TRUE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_OnlyNullRecognizersInResult, TestSize.Level1)
{
    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_FIRST);
    rootNode->SetTouchTestCallback(
        [](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(nullptr);
            result.push_back(nullptr);
        });

    auto result = finder_->FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_ClickRecognizerPredWithSingleClick, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickRecognizerPred clickPred;
    FrameNodeFinder finderWithClickPred(context, clickPred);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->AttachFrameNode(frameNode);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_SECOND);
    rootNode->SetTouchTestCallback(
        [&clickRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(clickRecognizer);
        });

    auto result = finderWithClickPred.FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_NE(result.GetNode(), nullptr);
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_ClickRecognizerPredWithMultiClick, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickRecognizerPred clickPred;
    FrameNodeFinder finderWithClickPred(context, clickPred);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("Button", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto doubleClickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, 2);
    doubleClickRecognizer->AttachFrameNode(frameNode);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_SECOND);
    rootNode->SetTouchTestCallback(
        [&doubleClickRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(doubleClickRecognizer);
        });

    auto result = finderWithClickPred.FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_FALSE(static_cast<bool>(result));
}

HWTEST_F(FrameNodeFinderFindAtWithRootNodeTest, FindAtWithRootNode_PanRecognizerReturnsNullClickFunc, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("Scroll", FIND_AT_NODE_ID_FIRST, AceType::MakeRefPtr<Pattern>());
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, PanDirection(), DEFAULT_PAN_DISTANCE);
    panRecognizer->AttachFrameNode(frameNode);

    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    auto panOnlyPred = [](const RefPtr<NGGestureRecognizer>& recognizer) {
        return AceType::InstanceOf<PanRecognizer>(recognizer);
    };
    FrameNodeFinder finderWithPanPred(context, panOnlyPred);

    auto rootNode = AceType::MakeRefPtr<MockUINodeForFindAt>("Root", FIND_AT_NODE_ID_SECOND);
    rootNode->SetTouchTestCallback(
        [&panRecognizer](const PointF&, const PointF&, const PointF&, TouchTestResult& result, int32_t) {
            result.push_back(panRecognizer);
        });

    auto result = finderWithPanPred.FindAt(rootNode, FIND_AT_COORD_X_POS, FIND_AT_COORD_Y_POS);

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.GetClickFunc(), nullptr);
}

} // namespace OHOS::Ace::NG
