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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/components_ng/pattern/selection_container/selection_container_layout_property.h"
#include "core/components_ng/pattern/selection_container/selection_container_event_hub.h"
#include "core/components_ng/manager/select_content_overlay/selection_container_child.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "base/json/json_util.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/inspector_filter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_NODE_ID_CHILD1 = 200;
constexpr int32_t TEST_NODE_ID_CHILD2 = 300;
constexpr int32_t TEST_START_INDEX = 10;
constexpr int32_t TEST_END_INDEX = 20;
constexpr int32_t TEST_FIXED_INDEX = 15;
constexpr int32_t TEST_SELECT_ALL_END_INDEX = 100;
constexpr float TEST_OFFSET_X = 50.0f;
constexpr float TEST_OFFSET_Y = 100.0f;
constexpr float TEST_OFFSET_X_SECOND = 150.0f;
constexpr float TEST_OFFSET_Y_SECOND = 200.0f;
constexpr float TEST_WIDTH = 200.0f;
constexpr float TEST_HEIGHT = 50.0f;
const std::string TEST_TAG("SelectionContainer");
const std::u16string TEST_SELECTION_TEXT1 = u"SelectedText1";
const std::u16string TEST_SELECTION_TEXT2 = u"SelectedText2";
const Color TEST_CARET_COLOR = Color(0xFF0000FF);
const Color TEST_SELECTED_BG_COLOR = Color(0xFFFF0000);
} // namespace

class MockSelectionContainerChild : public SelectionContainerChild {
    DECLARE_ACE_TYPE(MockSelectionContainerChild, SelectionContainerChild);

public:
    MockSelectionContainerChild() = default;
    ~MockSelectionContainerChild() override = default;

    void SetHostNode(const RefPtr<FrameNode>& node)
    {
        hostNode_ = node;
    }

    RefPtr<FrameNode> GetHostNode() const override
    {
        return hostNode_;
    }

    std::u16string GetSelectionText() override
    {
        return selectionText_;
    }

    void SetSelectionText(const std::u16string& text)
    {
        selectionText_ = text;
    }

    SelectionIndexRange GetSelectionIndexes() const override
    {
        return { startIndex_, endIndex_ };
    }

    void SetSelectionIndexes(int32_t start, int32_t end)
    {
        startIndex_ = start;
        endIndex_ = end;
    }

    SelectionIndexRange GetSelectionIndexesByPoints(const OffsetF& firstPoint, const OffsetF& secondPoint) override
    {
        return { TEST_START_INDEX, TEST_END_INDEX };
    }

    int32_t GetSelectionIndexByPoint(const OffsetF& point) override
    {
        return TEST_FIXED_INDEX;
    }

    void SelectTextByIndex(int32_t startIndex, int32_t endIndex) override
    {
        startIndex_ = startIndex;
        endIndex_ = endIndex;
        if (startIndex >= 0 && endIndex >= 0 && startIndex <= endIndex) {
            selectionText_ = TEST_SELECTION_TEXT1;
        } else {
            selectionText_ = u"";
        }
    }

    bool HasSelectableText() const override
    {
        return hasSelectableText_;
    }

    void SetHasSelectableText(bool hasText)
    {
        hasSelectableText_ = hasText;
    }

    bool IsSelectAll() const override
    {
        return isSelectAll_;
    }

    void SetIsSelectAll(bool isAll)
    {
        isSelectAll_ = isAll;
    }

    bool CanSelect() const override
    {
        return canSelect_;
    }

    void SetCanSelect(bool can)
    {
        canSelect_ = can;
    }

    std::optional<RectF> GetFirstHandleRect() override
    {
        return std::nullopt;
    }

    std::optional<RectF> GetSecondHandleRect() override
    {
        return std::nullopt;
    }

    void UpdateSelectionHandleInfo() override
    {
        handleInfoUpdated_ = true;
    }

    bool GetHandleInfoUpdated() const
    {
        return handleInfoUpdated_;
    }

    void ResetHandleInfoUpdated()
    {
        handleInfoUpdated_ = false;
    }

    void SelectAll() override
    {
        isSelectAll_ = true;
        selectionText_ = TEST_SELECTION_TEXT1;
        startIndex_ = 0;
        endIndex_ = TEST_SELECT_ALL_END_INDEX;
    }

    bool BetweenSelectedPosition(const Offset& globalOffset) override
    {
        return betweenSelectedPosition_;
    }

    void SetBetweenSelectedPosition(bool between)
    {
        betweenSelectedPosition_ = between;
    }

    void StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex) override
    {
        vibratorStarted_ = true;
    }

    bool GetVibratorStarted() const
    {
        return vibratorStarted_;
    }

    void ResetVibratorStarted()
    {
        vibratorStarted_ = false;
    }

    void ReportSelectionText() override
    {
        textReported_ = true;
    }

    bool GetTextReported() const
    {
        return textReported_;
    }

    void ResetTextReported()
    {
        textReported_ = false;
    }

    void OnContainerPropertyUpdate(uint32_t flags) override
    {
        propertyUpdated_ = true;
        lastPropertyUpdateFlags_ = flags;
    }

    bool GetPropertyUpdated() const
    {
        return propertyUpdated_;
    }

    uint32_t GetLastPropertyUpdateFlags() const
    {
        return lastPropertyUpdateFlags_;
    }

    void ResetPropertyUpdated()
    {
        propertyUpdated_ = false;
        lastPropertyUpdateFlags_ = 0;
    }

    TextSpanType GetSelectionSpanType() const override
    {
        return spanType_;
    }

    void SetSelectionSpanType(TextSpanType type)
    {
        spanType_ = type;
    }

    SelectionCopyPayload GetSelectionCopyPayload() override
    {
        SelectionCopyPayload payload;
        payload.plainText = selectionText_;
        return payload;
    }

    bool FireOnWillCopy(const std::u16string& selectedContent) override
    {
        return onWillCopyAllowed_;
    }

    void SetOnWillCopyAllowed(bool allowed)
    {
        onWillCopyAllowed_ = allowed;
    }

    void FireOnCopy(const std::u16string& selectedContent) override
    {
        onCopyFired_ = true;
    }

    bool GetOnCopyFired() const
    {
        return onCopyFired_;
    }

    void ResetOnCopyFired()
    {
        onCopyFired_ = false;
    }

    void ResetOriginCaretPosition() override
    {
        caretPositionReset_ = true;
    }

    bool GetCaretPositionReset() const
    {
        return caretPositionReset_;
    }

private:
    RefPtr<FrameNode> hostNode_;
    std::u16string selectionText_;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    bool hasSelectableText_ = false;
    bool isSelectAll_ = false;
    bool canSelect_ = false;
    bool betweenSelectedPosition_ = false;
    bool vibratorStarted_ = false;
    bool handleInfoUpdated_ = false;
    bool textReported_ = false;
    bool propertyUpdated_ = false;
    uint32_t lastPropertyUpdateFlags_ = 0;
    TextSpanType spanType_ = TextSpanType::TEXT;
    bool onWillCopyAllowed_ = true;
    bool onCopyFired_ = false;
    bool caretPositionReset_ = false;
};

class SelectionContainerPatternTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<SelectionContainerPattern> pattern_;
    RefPtr<FrameNode> containerNode_;
    RefPtr<MockSelectionContainerChild> child1_;
    RefPtr<FrameNode> childNode1_;
    RefPtr<MockSelectionContainerChild> child2_;
    RefPtr<FrameNode> childNode2_;
};

void SelectionContainerPatternTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void SelectionContainerPatternTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectionContainerPatternTest::SetUp()
{
    pattern_ = AceType::MakeRefPtr<SelectionContainerPattern>();
    containerNode_ = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern_, true);
    containerNode_->AttachToMainTree();
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    if (!layoutProperty) {
        layoutProperty = AceType::MakeRefPtr<SelectionContainerLayoutProperty>();
        containerNode_->layoutProperty_ = layoutProperty;
    }

    child1_ = AceType::MakeRefPtr<MockSelectionContainerChild>();
    childNode1_ = FrameNode::CreateFrameNode("Child1", TEST_NODE_ID_CHILD1, AceType::MakeRefPtr<Pattern>());
    child1_->SetHostNode(childNode1_);
    auto geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    geometryNode1->SetFrameSize(SizeF(TEST_WIDTH, TEST_HEIGHT));
    childNode1_->geometryNode_ = geometryNode1;
    childNode1_->SetParent(containerNode_);

    child2_ = AceType::MakeRefPtr<MockSelectionContainerChild>();
    childNode2_ = FrameNode::CreateFrameNode("Child2", TEST_NODE_ID_CHILD2, AceType::MakeRefPtr<Pattern>());
    child2_->SetHostNode(childNode2_);
    auto geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    geometryNode2->SetFrameSize(SizeF(TEST_WIDTH, TEST_HEIGHT));
    childNode2_->geometryNode_ = geometryNode2;
    childNode2_->SetParent(containerNode_);
}

void SelectionContainerPatternTest::TearDown()
{
    pattern_ = nullptr;
    containerNode_ = nullptr;
    child1_ = nullptr;
    childNode1_ = nullptr;
    child2_ = nullptr;
    childNode2_ = nullptr;
}

/**
 * @tc.name: GetSelectionTextTest001
 * @tc.desc: Test GetSelectionText with no children
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetSelectionTextTest001, TestSize.Level1)
{
    auto text = pattern_->GetSelectionText();
    EXPECT_TRUE(text.empty());
}

/**
 * @tc.name: GetSelectionTextTest002
 * @tc.desc: Test GetSelectionText with one child having selection
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetSelectionTextTest002, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    
    auto text = pattern_->GetSelectionText();
    EXPECT_EQ(text, TEST_SELECTION_TEXT1);
}

/**
 * @tc.name: GetSelectionTextTest003
 * @tc.desc: Test GetSelectionText with multiple children having selection
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetSelectionTextTest003, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child2_->SetSelectionText(TEST_SELECTION_TEXT2);
    
    auto text = pattern_->GetSelectionText();
    auto separator = pattern_->GetTextJoinSeparator();
    std::u16string expected = TEST_SELECTION_TEXT1 + separator + TEST_SELECTION_TEXT2;
    EXPECT_EQ(text, expected);
}

/**
 * @tc.name: GetHostNodeTest001
 * @tc.desc: Test GetHostNode returns host frame node
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetHostNodeTest001, TestSize.Level1)
{
    auto hostNode = pattern_->GetHostNode();
    EXPECT_EQ(hostNode, containerNode_);
}

/**
 * @tc.name: RegisterChildTest001
 * @tc.desc: Test RegisterChild adds child to list
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, RegisterChildTest001, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    auto childList = pattern_->GetChildList();
    EXPECT_EQ(childList.size(), 1);
    auto registeredChild = childList.front().Upgrade();
    EXPECT_EQ(registeredChild, child1_);
}

/**
 * @tc.name: RegisterChildTest002
 * @tc.desc: Test RegisterChild prevents duplicate registration
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, RegisterChildTest002, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child1_);
    auto childList = pattern_->GetChildList();
    EXPECT_EQ(childList.size(), 1);
}

/**
 * @tc.name: RegisterChildTest003
 * @tc.desc: Test RegisterChild with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, RegisterChildTest003, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    auto childList = pattern_->GetChildList();
    EXPECT_EQ(childList.size(), 2);
}

/**
 * @tc.name: UnregisterChildTest001
 * @tc.desc: Test UnregisterChild removes child from list
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, UnregisterChildTest001, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->UnregisterChild(TEST_NODE_ID_CHILD1);
    auto childList = pattern_->GetChildList();
    EXPECT_EQ(childList.size(), 0);
}

/**
 * @tc.name: UnregisterChildTest002
 * @tc.desc: Test UnregisterChild clears selection state
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, UnregisterChildTest002, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->selectionStartChild_ = child1_;
    pattern_->selectionEndChild_ = child1_;
    pattern_->selectionFixedChild_ = child1_;
    pattern_->selectionFixedIndex_ = TEST_FIXED_INDEX;
    
    pattern_->UnregisterChild(TEST_NODE_ID_CHILD1);
    
    EXPECT_TRUE(pattern_->selectionStartChild_.Upgrade() == nullptr);
    EXPECT_TRUE(pattern_->selectionEndChild_.Upgrade() == nullptr);
    EXPECT_TRUE(pattern_->selectionFixedChild_.Upgrade() == nullptr);
    EXPECT_EQ(pattern_->selectionFixedIndex_, -1);
}

/**
 * @tc.name: HandleSelectionStartTest001
 * @tc.desc: Test HandleSelectionStart with valid event info
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, HandleSelectionStartTest001, TestSize.Level1)
{
    SelectionStartEventInfo eventInfo;
    eventInfo.child = child1_;
    eventInfo.localPoint = OffsetF(TEST_OFFSET_X, TEST_OFFSET_Y);
    eventInfo.startIndex = TEST_START_INDEX;
    eventInfo.endIndex = TEST_END_INDEX;
    
    pattern_->RegisterChild(child1_);
    auto result = pattern_->HandleSelectionStart(eventInfo);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(pattern_->hasSelectionStartEvent_);
    EXPECT_EQ(pattern_->selectionStartIndex_, TEST_START_INDEX);
    EXPECT_EQ(pattern_->selectionEndIndex_, TEST_END_INDEX);
}

/**
 * @tc.name: HandleSelectionStartTest002
 * @tc.desc: Test HandleSelectionStart with null child
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, HandleSelectionStartTest002, TestSize.Level1)
{
    SelectionStartEventInfo eventInfo;
    eventInfo.child = nullptr;
    
    auto result = pattern_->HandleSelectionStart(eventInfo);
    
    EXPECT_FALSE(result);
    EXPECT_FALSE(pattern_->hasSelectionStartEvent_);
}

/**
 * @tc.name: HandleSelectionStartTest003
 * @tc.desc: Test HandleSelectionStart with direct parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, HandleSelectionStartTest003, TestSize.Level1)
{
    OffsetF fixedPoint(TEST_OFFSET_X, TEST_OFFSET_Y);
    
    auto result = pattern_->HandleSelectionStart(
        fixedPoint, child1_, TEST_START_INDEX, TEST_END_INDEX, true);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(pattern_->hasSelectionStartEvent_);
    EXPECT_EQ(pattern_->fixedPointInContainer_, fixedPoint);
    EXPECT_EQ(pattern_->selectionFixedChild_.Upgrade(), child1_);
}

/**
 * @tc.name: IsSelectionSessionOwnerTest001
 * @tc.desc: Test IsSelectionSessionOwner when child is owner
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectionSessionOwnerTest001, TestSize.Level1)
{
    pattern_->selectionFixedChild_ = child1_;
    
    auto result = pattern_->IsSelectionSessionOwner(child1_);
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsSelectionSessionOwnerTest002
 * @tc.desc: Test IsSelectionSessionOwner when child is not owner
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectionSessionOwnerTest002, TestSize.Level1)
{
    pattern_->selectionFixedChild_ = child1_;
    
    auto result = pattern_->IsSelectionSessionOwner(child2_);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleSelectionUpdateTest001
 * @tc.desc: Test HandleSelectionUpdate when no selection start event
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, HandleSelectionUpdateTest001, TestSize.Level1)
{
    SelectionEndEventInfo eventInfo;
    eventInfo.child = child1_;
    eventInfo.localPoint = OffsetF(TEST_OFFSET_X_SECOND, TEST_OFFSET_Y_SECOND);
    
    auto result = pattern_->HandleSelectionUpdate(eventInfo);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResetAllSelectionTest001
 * @tc.desc: Test ResetAllSelection clears all children selection
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ResetAllSelectionTest001, TestSize.Level1)
{
    child1_->SetCanSelect(true);
    child1_->SelectTextByIndex(TEST_START_INDEX, TEST_END_INDEX);
    pattern_->RegisterChild(child1_);
    pattern_->selectionStartChild_ = child1_;
    pattern_->selectionEndChild_ = child1_;
    
    pattern_->ResetAllSelection();
    
    auto indexes = child1_->GetSelectionIndexes();
    EXPECT_EQ(indexes.startIndex, -1);
    EXPECT_EQ(indexes.endIndex, -1);
    EXPECT_TRUE(pattern_->selectionStartChild_.Upgrade() == nullptr);
    EXPECT_TRUE(pattern_->selectionEndChild_.Upgrade() == nullptr);
}

/**
 * @tc.name: IsSelectAllTest001
 * @tc.desc: Test IsSelectAll when all children are selected
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectAllTest001, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    child1_->SetIsSelectAll(true);
    child2_->SetHasSelectableText(true);
    child2_->SetIsSelectAll(true);
    
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    auto result = pattern_->IsSelectAll();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsSelectAllTest002
 * @tc.desc: Test IsSelectAll when not all children are selected
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectAllTest002, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    child1_->SetIsSelectAll(true);
    child2_->SetHasSelectableText(true);
    child2_->SetIsSelectAll(false);
    
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    auto result = pattern_->IsSelectAll();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HasSelectableTextTest001
 * @tc.desc: Test HasSelectableText when children have selectable text
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, HasSelectableTextTest001, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    
    auto result = pattern_->HasSelectableText();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HasSelectableTextTest002
 * @tc.desc: Test HasSelectableText when no selectable text
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, HasSelectableTextTest002, TestSize.Level1)
{
    child1_->SetHasSelectableText(false);
    child2_->SetHasSelectableText(false);
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    auto result = pattern_->HasSelectableText();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UpdateSelectionBoundaryChildTest001
 * @tc.desc: Test UpdateSelectionBoundaryChild
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, UpdateSelectionBoundaryChildTest001, TestSize.Level1)
{
    pattern_->UpdateSelectionBoundaryChild(child1_);
    
    EXPECT_EQ(pattern_->selectionStartChild_.Upgrade(), child1_);
    EXPECT_EQ(pattern_->selectionEndChild_.Upgrade(), child1_);
}

/**
 * @tc.name: GetTextJoinSeparatorTest001
 * @tc.desc: Test GetTextJoinSeparator returns newline by default
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetTextJoinSeparatorTest001, TestSize.Level1)
{
    auto separator = pattern_->GetTextJoinSeparator();
    EXPECT_EQ(separator, u"\n");
}

/**
 * @tc.name: GetTextJoinSeparatorTest002
 * @tc.desc: Test GetTextJoinSeparator returns empty when style is DIRECT
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetTextJoinSeparatorTest002, TestSize.Level1)
{
    pattern_->SetTextJoinStyle(SelectionContainerTextJoinStyle::DIRECT);
    auto separator = pattern_->GetTextJoinSeparator();
    EXPECT_TRUE(separator.empty());
}

/**
 * @tc.name: SetTextJoinStyleTest001
 * @tc.desc: Test SetTextJoinStyle changes join style
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, SetTextJoinStyleTest001, TestSize.Level1)
{
    pattern_->SetTextJoinStyle(SelectionContainerTextJoinStyle::DIRECT);
    auto separator = pattern_->GetTextJoinSeparator();
    EXPECT_TRUE(separator.empty());
    
    pattern_->SetTextJoinStyle(SelectionContainerTextJoinStyle::NEWLINE);
    separator = pattern_->GetTextJoinSeparator();
    EXPECT_EQ(separator, u"\n");
}

/**
 * @tc.name: IsUsingMouseTest001
 * @tc.desc: Test IsUsingMouse returns false when source type is NONE
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsUsingMouseTest001, TestSize.Level1)
{
    pattern_->SetSourceType(SourceType::NONE);
    auto result = pattern_->IsUsingMouse();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsUsingMouseTest002
 * @tc.desc: Test IsUsingMouse returns true when source type is MOUSE
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsUsingMouseTest002, TestSize.Level1)
{
    pattern_->SetSourceType(SourceType::MOUSE);
    auto result = pattern_->IsUsingMouse();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetEnableHapticFeedbackTest001
 * @tc.desc: Test SetEnableHapticFeedback changes haptic feedback flag
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, SetEnableHapticFeedbackTest001, TestSize.Level1)
{
    pattern_->SetEnableHapticFeedback(false);
    auto result = pattern_->GetEnableHapticFeedback();
    EXPECT_FALSE(result);
    
    pattern_->SetEnableHapticFeedback(true);
    result = pattern_->GetEnableHapticFeedback();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetCopyOptionTest001
 * @tc.desc: Test GetCopyOption returns default InApp when no property
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetCopyOptionTest001, TestSize.Level1)
{
    auto result = pattern_->GetCopyOption();
    EXPECT_EQ(result, CopyOptions::InApp);
}

/**
 * @tc.name: GetCopyOptionTest002
 * @tc.desc: Test GetCopyOption returns value from layout property
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetCopyOptionTest002, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    layoutProperty->UpdateCopyOption(CopyOptions::Distributed);
    
    auto result = pattern_->GetCopyOption();
    EXPECT_EQ(result, CopyOptions::Distributed);
}

/**
 * @tc.name: GetSelectedBackgroundColorTest001
 * @tc.desc: Test GetSelectedBackgroundColor returns nullopt when no property
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetSelectedBackgroundColorTest001, TestSize.Level1)
{
    auto result = pattern_->GetSelectedBackgroundColor();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetSelectedBackgroundColorTest002
 * @tc.desc: Test GetSelectedBackgroundColor returns color from property
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetSelectedBackgroundColorTest002, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    layoutProperty->UpdateSelectedBackgroundColor(TEST_SELECTED_BG_COLOR);
    
    auto result = pattern_->GetSelectedBackgroundColor();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), TEST_SELECTED_BG_COLOR);
}

/**
 * @tc.name: OnChildResponseTypeChangedTest001
 * @tc.desc: Test OnChildResponseTypeChanged updates textResponseType
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, OnChildResponseTypeChangedTest001, TestSize.Level1)
{
    pattern_->OnChildResponseTypeChanged(TextResponseType::SELECTED_BY_MOUSE);
    EXPECT_EQ(pattern_->textResponseType_, TextResponseType::SELECTED_BY_MOUSE);
}

/**
 * @tc.name: OnChildSelectedTypeSaveTest001
 * @tc.desc: Test OnChildSelectedTypeSave calls SaveOldSelectedType
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, OnChildSelectedTypeSaveTest001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::TEXT;
    pattern_->oldSelectedType_ = TextSpanType::NONE;
    
    pattern_->OnChildSelectedTypeSave();
    
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::TEXT);
}

/**
 * @tc.name: SaveOldSelectedTypeTest001
 * @tc.desc: Test SaveOldSelectedType saves current selected type
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, SaveOldSelectedTypeTest001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::IMAGE;
    pattern_->oldSelectedType_ = TextSpanType::TEXT;
    
    pattern_->SaveOldSelectedType();
    
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::IMAGE);
}

/**
 * @tc.name: SaveOldSelectedTypeTest002
 * @tc.desc: Test SaveOldSelectedType uses NONE when no selected type
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, SaveOldSelectedTypeTest002, TestSize.Level1)
{
    pattern_->selectedType_ = std::nullopt;
    
    pattern_->SaveOldSelectedType();
    
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::NONE);
}

/**
 * @tc.name: IsSelectedTypeChangeTest001
 * @tc.desc: Test IsSelectedTypeChange returns true when type changed
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectedTypeChangeTest001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::IMAGE;
    pattern_->oldSelectedType_ = TextSpanType::TEXT;
    
    auto result = pattern_->IsSelectedTypeChange();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsSelectedTypeChangeTest002
 * @tc.desc: Test IsSelectedTypeChange returns false when type not changed
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectedTypeChangeTest002, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::TEXT;
    pattern_->oldSelectedType_ = TextSpanType::TEXT;
    
    auto result = pattern_->IsSelectedTypeChange();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSelectedTypeChangeTest003
 * @tc.desc: Test IsSelectedTypeChange returns false when no selected type
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectedTypeChangeTest003, TestSize.Level1)
{
    pattern_->selectedType_ = std::nullopt;
    
    auto result = pattern_->IsSelectedTypeChange();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckSelectedTypeChangeTest001
 * @tc.desc: Test CheckSelectedTypeChange updates old type when changed
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, CheckSelectedTypeChangeTest001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::IMAGE;
    pattern_->oldSelectedType_ = TextSpanType::TEXT;
    
    auto result = pattern_->CheckSelectedTypeChange();
    
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::IMAGE);
}

/**
 * @tc.name: RebuildSelectionSpanTypeByFullScanTest001
 * @tc.desc: Test RebuildSelectionSpanTypeByFullScan clears and rebuilds summary
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, RebuildSelectionSpanTypeByFullScanTest001, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetSelectionSpanType(TextSpanType::TEXT);
    pattern_->RegisterChild(child1_);
    
    pattern_->RebuildSelectionSpanTypeByFullScan();
    
    EXPECT_EQ(pattern_->selectedTextCount_, 1);
    EXPECT_EQ(pattern_->selectedImageCount_, 0);
    EXPECT_EQ(pattern_->selectedBuilderCount_, 0);
    EXPECT_EQ(pattern_->selectedType_, TextSpanType::TEXT);
}

/**
 * @tc.name: RebuildSelectionSpanTypeByFullScanTest002
 * @tc.desc: Test RebuildSelectionSpanTypeByFullScan with mixed types
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, RebuildSelectionSpanTypeByFullScanTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetSelectionSpanType(TextSpanType::TEXT);
    child2_->SetSelectionText(TEST_SELECTION_TEXT2);
    child2_->SetSelectionSpanType(TextSpanType::IMAGE);
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    pattern_->RebuildSelectionSpanTypeByFullScan();
    
    EXPECT_EQ(pattern_->selectedTextCount_, 1);
    EXPECT_EQ(pattern_->selectedImageCount_, 1);
    EXPECT_EQ(pattern_->selectedType_, TextSpanType::MIXED);
}

/**
 * @tc.name: OnChildSelectionSpanTypeChangedTest001
 * @tc.desc: Test OnChildSelectionSpanTypeChanged updates summary
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, OnChildSelectionSpanTypeChangedTest001, TestSize.Level1)
{
    ChildSelectionSummary oldSummary = { false, TextSpanType::NONE };
    ChildSelectionSummary newSummary = { true, TextSpanType::TEXT };
    
    pattern_->OnChildSelectionSpanTypeChanged(TEST_NODE_ID_CHILD1, oldSummary, newSummary);
    
    EXPECT_EQ(pattern_->selectedTextCount_, 1);
    EXPECT_EQ(pattern_->selectedType_, TextSpanType::TEXT);
}

/**
 * @tc.name: HandleOnSelectAllTest001
 * @tc.desc: Test HandleOnSelectAll selects all children with selectable text
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, HandleOnSelectAllTest001, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    child1_->SetCanSelect(true);
    pattern_->RegisterChild(child1_);
    
    pattern_->HandleOnSelectAll();
    
    EXPECT_TRUE(child1_->IsSelectAll());
    EXPECT_TRUE(child1_->GetHandleInfoUpdated());
    EXPECT_TRUE(child1_->GetTextReported());
    EXPECT_EQ(pattern_->selectionStartChild_.Upgrade(), child1_);
    EXPECT_EQ(pattern_->selectionEndChild_.Upgrade(), child1_);
}

/**
 * @tc.name: HandleOnSelectAllTest002
 * @tc.desc: Test HandleOnSelectAll with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, HandleOnSelectAllTest002, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    child1_->SetCanSelect(true);
    child2_->SetHasSelectableText(true);
    child2_->SetCanSelect(true);
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    pattern_->HandleOnSelectAll();
    
    EXPECT_TRUE(child1_->IsSelectAll());
    EXPECT_TRUE(child2_->IsSelectAll());
    EXPECT_EQ(pattern_->selectionStartChild_.Upgrade(), child1_);
    EXPECT_EQ(pattern_->selectionEndChild_.Upgrade(), child2_);
}

/**
 * @tc.name: MarkContainerPropertyUpdateTest001
 * @tc.desc: Test MarkContainerPropertyUpdate sets pending flags
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, MarkContainerPropertyUpdateTest001, TestSize.Level1)
{
    uint32_t flags = static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION);
    pattern_->MarkContainerPropertyUpdate(flags);
    
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, flags);
}

/**
 * @tc.name: MarkContainerPropertyUpdateTest002
 * @tc.desc: Test MarkContainerPropertyUpdate accumulates flags
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, MarkContainerPropertyUpdateTest002, TestSize.Level1)
{
    uint32_t flags1 = static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION);
    uint32_t flags2 = static_cast<uint32_t>(SelectionContainerPropertyChange::ENABLE_HAPTIC_FEEDBACK);
    pattern_->MarkContainerPropertyUpdate(flags1);
    pattern_->MarkContainerPropertyUpdate(flags2);
    
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, flags1 | flags2);
}

/**
 * @tc.name: NotifyRegisteredChildrenPropertyUpdateTest001
 * @tc.desc: Test NotifyRegisteredChildrenPropertyUpdate notifies children
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, NotifyRegisteredChildrenPropertyUpdateTest001, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    uint32_t flags = static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR);
    pattern_->NotifyRegisteredChildrenPropertyUpdate(flags);
    
    EXPECT_TRUE(child1_->GetPropertyUpdated());
    EXPECT_TRUE(child2_->GetPropertyUpdated());
    EXPECT_EQ(child1_->GetLastPropertyUpdateFlags(), flags);
    EXPECT_EQ(child2_->GetLastPropertyUpdateFlags(), flags);
}

/**
 * @tc.name: BetweenSelectedPositionTest001
 * @tc.desc: Test BetweenSelectedPosition when child returns true
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, BetweenSelectedPositionTest001, TestSize.Level1)
{
    child1_->SetBetweenSelectedPosition(true);
    pattern_->RegisterChild(child1_);
    
    Offset globalOffset;
    auto result = pattern_->BetweenSelectedPosition(globalOffset);
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: BetweenSelectedPositionTest002
 * @tc.desc: Test BetweenSelectedPosition when all children return false
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, BetweenSelectedPositionTest002, TestSize.Level1)
{
    child1_->SetBetweenSelectedPosition(false);
    child2_->SetBetweenSelectedPosition(false);
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    Offset globalOffset;
    auto result = pattern_->BetweenSelectedPosition(globalOffset);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResetSelectionSessionStateTest001
 * @tc.desc: Test ResetSelectionSessionState clears all state
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ResetSelectionSessionStateTest001, TestSize.Level1)
{
    pattern_->hasSelectionStartEvent_ = true;
    pattern_->selectionStartIndex_ = TEST_START_INDEX;
    pattern_->selectionEndIndex_ = TEST_END_INDEX;
    pattern_->fixedHandleIsTopOnStart_ = false;
    
    pattern_->ResetSelectionSessionState();
    
    EXPECT_FALSE(pattern_->hasSelectionStartEvent_);
    EXPECT_EQ(pattern_->selectionStartIndex_, -1);
    EXPECT_EQ(pattern_->selectionEndIndex_, -1);
    EXPECT_TRUE(pattern_->fixedHandleIsTopOnStart_);
}

/**
 * @tc.name: ReportSelectionTextTest001
 * @tc.desc: Test ReportSelectionText reports all children
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ReportSelectionTextTest001, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    pattern_->ReportSelectionText();
    
    EXPECT_TRUE(child1_->GetTextReported());
    EXPECT_TRUE(child2_->GetTextReported());
}

/**
 * @tc.name: BindSelectionMenuTest001
 * @tc.desc: Test BindSelectionMenu adds menu params
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, BindSelectionMenuTest001, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    menuParam.isValid = true;
    
    pattern_->BindSelectionMenu(
        TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    EXPECT_TRUE(menuParams != nullptr);
    EXPECT_TRUE(menuParams->isValid);
}

/**
 * @tc.name: BindSelectionMenuTest002
 * @tc.desc: Test BindSelectionMenu removes menu when builder is null
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, BindSelectionMenuTest002, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    pattern_->BindSelectionMenu(
        TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    
    std::function<void()> nullBuilder = nullptr;
    pattern_->BindSelectionMenu(
        TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, nullBuilder, menuParam);
    
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    EXPECT_TRUE(menuParams == nullptr);
}

/**
 * @tc.name: GetMenuParamsTest001
 * @tc.desc: Test GetMenuParams returns nullptr when not found
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetMenuParamsTest001, TestSize.Level1)
{
    auto menuParams = pattern_->GetMenuParams(TextSpanType::IMAGE, TextResponseType::SELECTED_BY_MOUSE);
    EXPECT_TRUE(menuParams == nullptr);
}

/**
 * @tc.name: IsSelectedBindSelectionMenuTest001
 * @tc.desc: Test IsSelectedBindSelectionMenu returns false when no menu
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectedBindSelectionMenuTest001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::TEXT;
    
    auto result = pattern_->IsSelectedBindSelectionMenu();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSelectedBindSelectionMenuTest002
 * @tc.desc: Test IsSelectedBindSelectionMenu returns true when menu exists
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, IsSelectedBindSelectionMenuTest002, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    menuParam.isValid = true;
    pattern_->BindSelectionMenu(
        TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    pattern_->selectedType_ = TextSpanType::TEXT;
    
    auto result = pattern_->IsSelectedBindSelectionMenu();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CreateLayoutPropertyTest001
 * @tc.desc: Test CreateLayoutProperty returns SelectionContainerLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, CreateLayoutPropertyTest001, TestSize.Level1)
{
    auto property = pattern_->CreateLayoutProperty();
    auto selectionProperty = AceType::DynamicCast<SelectionContainerLayoutProperty>(property);
    EXPECT_TRUE(selectionProperty != nullptr);
}

/**
 * @tc.name: CreateEventHubTest001
 * @tc.desc: Test CreateEventHub returns SelectionContainerEventHub
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, CreateEventHubTest001, TestSize.Level1)
{
    auto eventHub = pattern_->CreateEventHub();
    auto selectionEventHub = AceType::DynamicCast<SelectionContainerEventHub>(eventHub);
    EXPECT_TRUE(selectionEventHub != nullptr);
}

/**
 * @tc.name: GetFocusPatternTest001
 * @tc.desc: Test GetFocusPattern returns correct focus pattern
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetFocusPatternTest001, TestSize.Level1)
{
    auto focusPattern = pattern_->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::SCOPE);
    EXPECT_EQ(focusPattern.styleType_, FocusStyleType::OUTER_BORDER);
}

/**
 * @tc.name: UpdatePropertyImplTest001
 * @tc.desc: Test UpdatePropertyImpl updates caret color
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, UpdatePropertyImplTest001, TestSize.Level1)
{
    auto propertyValue = AceType::MakeRefPtr<PropertyValueBase>();
    propertyValue->SetValue(TEST_CARET_COLOR);
    
    pattern_->UpdatePropertyImpl("SelectionContainerCaretColor", propertyValue);
    
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    auto caretColor = layoutProperty->GetCaretColorValue(Color::TRANSPARENT);
    EXPECT_EQ(caretColor, TEST_CARET_COLOR);
}

/**
 * @tc.name: UpdatePropertyImplTest002
 * @tc.desc: Test UpdatePropertyImpl updates selected background color
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, UpdatePropertyImplTest002, TestSize.Level1)
{
    auto propertyValue = AceType::MakeRefPtr<PropertyValueBase>();
    propertyValue->SetValue(TEST_SELECTED_BG_COLOR);
    
    pattern_->UpdatePropertyImpl("SelectionContainerSelectedBackgroundColor", propertyValue);
    
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    auto bgColor = layoutProperty->GetSelectedBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), TEST_SELECTED_BG_COLOR);
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_,
        static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR));
}

/**
 * @tc.name: OnModifyDoneTest001
 * @tc.desc: Test OnModifyDone initializes when has selectable text
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, OnModifyDoneTest001, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->hasModifyDone_ = false;
    
    pattern_->OnModifyDone();
    
    EXPECT_TRUE(pattern_->hasModifyDone_);
    EXPECT_TRUE(pattern_->keyEventInitialized_);
}

/**
 * @tc.name: OnModifyDoneTest002
 * @tc.desc: Test OnModifyDone notifies pending property updates
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, OnModifyDoneTest002, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->hasModifyDone_ = true;
    uint32_t flags = static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR);
    pattern_->pendingContainerPropertyUpdateFlags_ = flags;
    
    pattern_->OnModifyDone();
    
    EXPECT_TRUE(child1_->GetPropertyUpdated());
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, 0);
}

/**
 * @tc.name: SetSelectionMenuItemClickWithTextCallbackTest001
 * @tc.desc: Test SetSelectionMenuItemClickWithTextCallback sets callback
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, SetSelectionMenuItemClickWithTextCallbackTest001, TestSize.Level1)
{
    std::function<bool(const MenuItemParam&, const std::u16string&)> callback =
        [](const MenuItemParam& param, const std::u16string& text) { return true; };
    
    pattern_->SetSelectionMenuItemClickWithTextCallback(std::move(callback));
    
    EXPECT_TRUE(pattern_->onMenuItemClickWithText_ != nullptr);
}

/**
 * @tc.name: GetChildListTest001
 * @tc.desc: Test GetChildList returns registered children
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetChildListTest001, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    auto childList = pattern_->GetChildList();
    
    EXPECT_EQ(childList.size(), 2);
}

/**
 * @tc.name: GetChildListTest002
 * @tc.desc: Test GetChildList filters out expired weak pointers
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetChildListTest002, TestSize.Level1)
{
    pattern_->registeredChildList_.push_back(WeakPtr<SelectionContainerChild>(child1_));
    pattern_->registeredChildList_.push_back(WeakPtr<SelectionContainerChild>(nullptr));
    pattern_->registeredChildList_.push_back(WeakPtr<SelectionContainerChild>(child2_));
    
    auto childList = pattern_->GetChildList();
    
    EXPECT_EQ(childList.size(), 2);
}

/**
 * @tc.name: MarkChildSortDirtyTest001
 * @tc.desc: Test MarkChildSortDirty sets sortDirty flag
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, MarkChildSortDirtyTest001, TestSize.Level1)
{
    pattern_->sortDirty_ = false;
    pattern_->MarkChildSortDirty();
    
    EXPECT_TRUE(pattern_->sortDirty_);
}

/**
 * @tc.name: RefreshChildSortResultTest001
 * @tc.desc: Test RefreshChildSortResult removes expired children
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, RefreshChildSortResultTest001, TestSize.Level1)
{
    pattern_->registeredChildList_.push_back(WeakPtr<SelectionContainerChild>(child1_));
    pattern_->registeredChildList_.push_back(WeakPtr<SelectionContainerChild>(nullptr));
    pattern_->registeredChildList_.push_back(WeakPtr<SelectionContainerChild>(child2_));
    
    pattern_->RefreshChildSortResult();
    
    EXPECT_EQ(pattern_->registeredChildList_.size(), 2);
}

/**
 * @tc.name: ProcessSelectionEndCommonTest001
 * @tc.desc: Test ProcessSelectionEndCommon without selection start event
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ProcessSelectionEndCommonTest001, TestSize.Level1)
{
    pattern_->hasSelectionStartEvent_ = false;
    
    auto result = pattern_->ProcessSelectionEndCommon(true);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ProcessSelectionEndCommonTest002
 * @tc.desc: Test ProcessSelectionEndCommon with selection start event
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ProcessSelectionEndCommonTest002, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->hasSelectionStartEvent_ = true;
    pattern_->selectionStartChild_ = child1_;
    pattern_->selectionEndChild_ = child1_;
    pattern_->selectionFixedChild_ = child1_;
    
    auto result = pattern_->ProcessSelectionEndCommon(true);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(child1_->GetHandleInfoUpdated());
}

/**
 * @tc.name: ProcessGestureSelectionEndTest001
 * @tc.desc: Test ProcessGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ProcessGestureSelectionEndTest001, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->hasSelectionStartEvent_ = true;
    pattern_->selectionStartChild_ = child1_;
    pattern_->selectionEndChild_ = child1_;
    
    SelectionEndEventInfo eventInfo;
    eventInfo.child = child1_;
    eventInfo.localPoint = OffsetF(TEST_OFFSET_X, TEST_OFFSET_Y);
    
    auto result = pattern_->ProcessGestureSelectionEnd(eventInfo);
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ProcessMouseLeftReleaseTest001
 * @tc.desc: Test ProcessMouseLeftRelease
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ProcessMouseLeftReleaseTest001, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->hasSelectionStartEvent_ = true;
    pattern_->selectionStartChild_ = child1_;
    pattern_->selectionEndChild_ = child1_;
    
    SelectionEndEventInfo eventInfo;
    eventInfo.child = child1_;
    eventInfo.localPoint = OffsetF(TEST_OFFSET_X, TEST_OFFSET_Y);
    
    auto result = pattern_->ProcessMouseLeftRelease(eventInfo);
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ProcessHandleMoveSelectionEndTest001
 * @tc.desc: Test ProcessHandleMoveSelectionEnd without selection start event
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ProcessHandleMoveSelectionEndTest001, TestSize.Level1)
{
    pattern_->hasSelectionStartEvent_ = false;
    
    OffsetF movingPoint(TEST_OFFSET_X, TEST_OFFSET_Y);
    auto result = pattern_->ProcessHandleMoveSelectionEnd(movingPoint);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ProcessHandleMoveSelectionEndTest002
 * @tc.desc: Test ProcessHandleMoveSelectionEnd with selection start event
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ProcessHandleMoveSelectionEndTest002, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->hasSelectionStartEvent_ = true;
    pattern_->selectionStartChild_ = child1_;
    pattern_->selectionEndChild_ = child1_;
    
    OffsetF movingPoint(TEST_OFFSET_X, TEST_OFFSET_Y);
    auto result = pattern_->ProcessHandleMoveSelectionEnd(movingPoint);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(child1_->GetTextReported());
}

/**
 * @tc.name: ExtendSelectionFromFixedAnchorTest001
 * @tc.desc: Test ExtendSelectionFromFixedAnchor without fixed child
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ExtendSelectionFromFixedAnchorTest001, TestSize.Level1)
{
    SelectionEndEventInfo eventInfo;
    eventInfo.child = child1_;
    eventInfo.localPoint = OffsetF(TEST_OFFSET_X, TEST_OFFSET_Y);
    
    auto result = pattern_->ExtendSelectionFromFixedAnchor(eventInfo);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ExtendSelectionFromFixedAnchorTest002
 * @tc.desc: Test ExtendSelectionFromFixedAnchor with invalid fixed index
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ExtendSelectionFromFixedAnchorTest002, TestSize.Level1)
{
    pattern_->selectionFixedChild_ = child1_;
    pattern_->selectionFixedIndex_ = -1;
    
    SelectionEndEventInfo eventInfo;
    eventInfo.child = child1_;
    eventInfo.localPoint = OffsetF(TEST_OFFSET_X, TEST_OFFSET_Y);
    
    auto result = pattern_->ExtendSelectionFromFixedAnchor(eventInfo);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ExtendSelectionFromFixedAnchorTest003
 * @tc.desc: Test ExtendSelectionFromFixedAnchor with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, ExtendSelectionFromFixedAnchorTest003, TestSize.Level1)
{
    child1_->SetCanSelect(true);
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->selectionFixedChild_ = child1_;
    pattern_->selectionFixedIndex_ = TEST_FIXED_INDEX;
    
    SelectionEndEventInfo eventInfo;
    eventInfo.child = child1_;
    eventInfo.localPoint = OffsetF(TEST_OFFSET_X, TEST_OFFSET_Y);
    
    EXPECT_TRUE(pattern_->ExtendSelectionFromFixedAnchor(eventInfo));
    
    EXPECT_TRUE(pattern_->hasSelectionStartEvent_);
    EXPECT_EQ(pattern_->selectionStartIndex_, TEST_FIXED_INDEX);
    EXPECT_EQ(pattern_->selectionEndIndex_, TEST_FIXED_INDEX);
}

/**
 * @tc.name: GetSelectionStartChildTest001
 * @tc.desc: Test GetSelectionStartChild
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetSelectionStartChildTest001, TestSize.Level1)
{
    pattern_->selectionStartChild_ = child1_;
    
    auto result = pattern_->GetSelectionStartChild();
    
    EXPECT_EQ(result, child1_);
}

/**
 * @tc.name: GetSelectionEndChildTest001
 * @tc.desc: Test GetSelectionEndChild
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetSelectionEndChildTest001, TestSize.Level1)
{
    pattern_->selectionEndChild_ = child1_;
    
    auto result = pattern_->GetSelectionEndChild();
    
    EXPECT_EQ(result, child1_);
}

/**
 * @tc.name: CopyOptionsToStrTest001
 * @tc.desc: Test SelectionContainerLayoutProperty::CopyOptionsToStr maps all enum values
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, CopyOptionsToStrTest001, TestSize.Level1)
{
    EXPECT_STREQ(SelectionContainerLayoutProperty::CopyOptionsToStr(CopyOptions::None), "None");
    EXPECT_STREQ(SelectionContainerLayoutProperty::CopyOptionsToStr(CopyOptions::InApp), "InApp");
    EXPECT_STREQ(SelectionContainerLayoutProperty::CopyOptionsToStr(CopyOptions::Local), "Local");
    EXPECT_STREQ(SelectionContainerLayoutProperty::CopyOptionsToStr(CopyOptions::Distributed), "Distributed");
}

/**
 * @tc.name: SelectionContainerLayoutToJsonValueTest001
 * @tc.desc: Test SelectionContainerLayoutProperty::ToJsonValue dumps copyOption
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, SelectionContainerLayoutToJsonValueTest001, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOption(CopyOptions::Local);
    auto json = JsonUtil::Create(true);
    const InspectorFilter filter;
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("copyOption"), "Local");
}

/**
 * @tc.name: GetCaretColorStrTest001
 * @tc.desc: Test GetCaretColorStr resolves explicit value and theme default
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetCaretColorStrTest001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    pipeline->themeManager_ = themeManager;
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCaretColor(TEST_CARET_COLOR);
    EXPECT_EQ(pattern_->GetCaretColorStr(), TEST_CARET_COLOR.ColorToString());

    layoutProperty->ResetCaretColor();
    auto theme = containerNode_->GetContext()->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    EXPECT_EQ(pattern_->GetCaretColorStr(), theme->GetCaretColor().ColorToString());
}

/**
 * @tc.name: GetSelectedBackgroundColorStrTest001
 * @tc.desc: Test GetSelectedBackgroundColorStr resolves explicit value and theme default
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetSelectedBackgroundColorStrTest001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    pipeline->themeManager_ = themeManager;
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSelectedBackgroundColor(TEST_SELECTED_BG_COLOR);
    EXPECT_EQ(pattern_->GetSelectedBackgroundColorStr(), TEST_SELECTED_BG_COLOR.ColorToString());

    layoutProperty->ResetSelectedBackgroundColor();
    auto theme = containerNode_->GetContext()->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    EXPECT_EQ(pattern_->GetSelectedBackgroundColorStr(), theme->GetSelectedColor().ColorToString());
}

/**
 * @tc.name: GetBindSelectionMenuInJsonTest001
 * @tc.desc: Test GetBindSelectionMenuInJson with no registered menu
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, GetBindSelectionMenuInJsonTest001, TestSize.Level1)
{
    EXPECT_EQ(pattern_->GetBindSelectionMenuInJson(), "[]");
}

/**
 * @tc.name: SelectionContainerToJsonValueTest001
 * @tc.desc: Test SelectionContainerPattern::ToJsonValue dumps pattern-level keys
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTest, SelectionContainerToJsonValueTest001, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    const InspectorFilter filter;
    pattern_->ToJsonValue(json, filter);
    EXPECT_TRUE(json->Contains("enableHapticFeedback"));
    EXPECT_TRUE(json->Contains("caretColor"));
    EXPECT_TRUE(json->Contains("bindSelectionMenu"));
    EXPECT_TRUE(json->Contains("content"));
}
} // namespace OHOS::Ace::NG
