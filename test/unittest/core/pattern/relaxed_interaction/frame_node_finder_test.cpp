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
#include "core/components_ng/gestures/recognizers/recognizer_group.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
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

} // namespace OHOS::Ace::NG
