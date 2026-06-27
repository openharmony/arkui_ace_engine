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

#ifndef SELECTION_CONTAINER_TEST_COMMON_H
#define SELECTION_CONTAINER_TEST_COMMON_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/resource/pattern_resource_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/select_content_overlay/selection_container.h"
#include "core/components_ng/manager/select_content_overlay/selection_container_child.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/selection_container/selection_container_event_hub.h"
#include "core/components_ng/pattern/selection_container/selection_container_layout_property.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/components_ng/pattern/selection_container/selection_select_overlay.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/event/key_event.h"

namespace OHOS::Ace::NG {

constexpr int32_t SCT_TEST_NODE_ID = 100;
constexpr int32_t SCT_TEST_NODE_ID_CHILD1 = 200;
constexpr int32_t SCT_TEST_NODE_ID_CHILD2 = 300;
constexpr int32_t SCT_TEST_START_INDEX = 10;
constexpr int32_t SCT_TEST_END_INDEX = 20;
constexpr int32_t SCT_TEST_FIXED_INDEX = 15;
constexpr int32_t SCT_TEST_SELECT_ALL_END_INDEX = 100;
constexpr float SCT_TEST_OFFSET_X = 50.0f;
constexpr float SCT_TEST_OFFSET_Y = 100.0f;
constexpr float SCT_TEST_WIDTH = 200.0f;
constexpr float SCT_TEST_HEIGHT = 50.0f;
const std::string SCT_TEST_TAG("SelectionContainer");
const std::u16string SCT_TEST_SELECTION_TEXT1 = u"SelectedText1";
const std::u16string SCT_TEST_SELECTION_TEXT2 = u"SelectedText2";
const std::u16string SCT_TEST_EMPTY_TEXT = u"";
const Color SCT_TEST_CARET_COLOR = Color(0xFF0000FF);
const Color SCT_TEST_SELECTED_BG_COLOR = Color(0xFFFF0000);

/**
 * Mock child implementing SelectionContainerChild for controlled test behaviour.
 * Each setter flips internal state so assertions can verify interactions.
 */
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
        return { SCT_TEST_START_INDEX, SCT_TEST_END_INDEX };
    }

    int32_t GetSelectionIndexByPoint(const OffsetF& point) override
    {
        return SCT_TEST_FIXED_INDEX;
    }

    void SelectTextByIndex(int32_t startIndex, int32_t endIndex) override
    {
        startIndex_ = startIndex;
        endIndex_ = endIndex;
        bool valid = startIndex >= 0 && endIndex >= 0 && startIndex <= endIndex;
        selectionText_ = valid ? SCT_TEST_SELECTION_TEXT1 : u"";
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

    HandleVisibleContentResult GetHandleVisibleContentRect(
        const RectF&, RectF& visibleContentRect, HandleLevelMode) override
    {
        visibleContentRect = RectF(0.0f, 0.0f, SCT_TEST_WIDTH, SCT_TEST_HEIGHT);
        return HandleVisibleContentResult::NEED_CHECK;
    }

    std::optional<RectF> GetAncestorNodeViewPortForChild() override
    {
        return RectF(0.0f, 0.0f, SCT_TEST_WIDTH, SCT_TEST_HEIGHT);
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
        selectionText_ = SCT_TEST_SELECTION_TEXT1;
        startIndex_ = 0;
        endIndex_ = SCT_TEST_SELECT_ALL_END_INDEX;
    }

    bool BetweenSelectedPosition(const Offset& globalOffset) override
    {
        return betweenSelectedPosition_;
    }

    void SetBetweenSelectedPosition(bool between)
    {
        betweenSelectedPosition_ = between;
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
        onWillCopyCalled_ = true;
        return onWillCopyAllowed_;
    }

    void SetOnWillCopyAllowed(bool allowed)
    {
        onWillCopyAllowed_ = allowed;
    }

    bool GetOnWillCopyCalled() const
    {
        return onWillCopyCalled_;
    }

    void ResetOnWillCopyCalled()
    {
        onWillCopyCalled_ = false;
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

    CopyOptions GetCopyOption() const override
    {
        return copyOption_;
    }

    void SetCopyOption(CopyOptions option)
    {
        copyOption_ = option;
    }

    void StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex) override {}

private:
    RefPtr<FrameNode> hostNode_;
    std::u16string selectionText_;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    bool hasSelectableText_ = false;
    bool isSelectAll_ = false;
    bool canSelect_ = false;
    bool betweenSelectedPosition_ = false;
    bool handleInfoUpdated_ = false;
    bool textReported_ = false;
    bool propertyUpdated_ = false;
    uint32_t lastPropertyUpdateFlags_ = 0;
    TextSpanType spanType_ = TextSpanType::TEXT;
    bool onWillCopyAllowed_ = true;
    bool onWillCopyCalled_ = false;
    bool onCopyFired_ = false;
    bool caretPositionReset_ = false;
    CopyOptions copyOption_ = CopyOptions::None;
    SelectionCopyPayload copyPayload_;
};

/**
 * Test fixture shared by all test files.
 * Sets up a pattern with a host FrameNode and two mock children.
 */
class SelectionContainerPatternTestNg : public testing::Test {
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

private:
    void InitContainer();
    void CreateChild(const std::string& tag, int32_t nodeId,
        RefPtr<MockSelectionContainerChild>& child, RefPtr<FrameNode>& childNode);
};

inline void SelectionContainerPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

inline void SelectionContainerPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

inline void SelectionContainerPatternTestNg::InitContainer()
{
    pattern_ = AceType::MakeRefPtr<SelectionContainerPattern>();
    containerNode_ = FrameNode::CreateFrameNode(SCT_TEST_TAG, SCT_TEST_NODE_ID, pattern_, true);
    containerNode_->AttachToMainTree();
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_FALSE(!layoutProperty);
}

inline void SelectionContainerPatternTestNg::CreateChild(const std::string& tag, int32_t nodeId,
    RefPtr<MockSelectionContainerChild>& child, RefPtr<FrameNode>& childNode)
{
    child = AceType::MakeRefPtr<MockSelectionContainerChild>();
    childNode = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    child->SetHostNode(childNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(SCT_TEST_WIDTH, SCT_TEST_HEIGHT));
    childNode->SetGeometryNode(geometryNode);
    childNode->SetParent(containerNode_);
}

inline void SelectionContainerPatternTestNg::SetUp()
{
    InitContainer();
    CreateChild("Child1", SCT_TEST_NODE_ID_CHILD1, child1_, childNode1_);
    CreateChild("Child2", SCT_TEST_NODE_ID_CHILD2, child2_, childNode2_);
}

inline void SelectionContainerPatternTestNg::TearDown()
{
    pattern_ = nullptr;
    containerNode_ = nullptr;
    child1_ = nullptr;
    childNode1_ = nullptr;
    child2_ = nullptr;
    childNode2_ = nullptr;
}

} // namespace OHOS::Ace::NG

#endif // SELECTION_CONTAINER_TEST_COMMON_H
