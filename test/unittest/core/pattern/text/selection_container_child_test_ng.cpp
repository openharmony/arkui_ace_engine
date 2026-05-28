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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/select_content_overlay/selection_container_child.h"
#include "core/components_ng/manager/select_content_overlay/selection_container.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/components_ng/pattern/text/span/span_string.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_CONTAINER_ID = 200;
constexpr int32_t TEST_START_INDEX = 10;
constexpr int32_t TEST_END_INDEX = 20;
constexpr float TEST_OFFSET_X = 50.0f;
constexpr float TEST_OFFSET_Y = 100.0f;
const std::string TEST_CHILD_TAG("Child");
const std::string TEST_CONTAINER_TAG("Container");
const std::u16string TEST_SELECTION_TEXT = u"SelectedText";
const std::u16string TEST_EMPTY_TEXT = u"";
} // namespace

class MockSelectionContainerChildImpl : public SelectionContainerChild {
    DECLARE_ACE_TYPE(MockSelectionContainerChildImpl, SelectionContainerChild);

public:
    MockSelectionContainerChildImpl() = default;
    ~MockSelectionContainerChildImpl() override = default;

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

    std::optional<SelectHandleInfo> GetFirstHandleInfo() override
    {
        return std::nullopt;
    }

    std::optional<SelectHandleInfo> GetSecondHandleInfo() override
    {
        return std::nullopt;
    }

    SelectionIndexRange GetSelectionIndexesByPoints(const OffsetF& firstPoint, const OffsetF& secondPoint) override
    {
        return { TEST_START_INDEX, TEST_END_INDEX };
    }

    void SelectTextByIndex(int32_t startIndex, int32_t endIndex) override
    {
        startIndex_ = startIndex;
        endIndex_ = endIndex;
    }

    RefPtr<SpanString> GetSelectedSpanString() override
    {
        return spanString_;
    }

    void SetSpanString(const RefPtr<SpanString>& spanString)
    {
        spanString_ = spanString;
    }

    TextSpanType GetSelectionSpanType() const override
    {
        return spanType_;
    }

    void SetSelectionSpanType(TextSpanType type)
    {
        spanType_ = type;
    }

private:
    RefPtr<FrameNode> hostNode_;
    std::u16string selectionText_;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    RefPtr<SpanString> spanString_;
    TextSpanType spanType_ = TextSpanType::TEXT;
};

class MockSelectionContainerImpl : public SelectionContainer {
    DECLARE_ACE_TYPE(MockSelectionContainerImpl, SelectionContainer);

public:
    MockSelectionContainerImpl() = default;
    ~MockSelectionContainerImpl() override = default;

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

    void CloseSelectOverlay(bool animation = false, CloseReason reason = CloseReason::CLOSE_REASON_NORMAL) override
    {
        overlayClosed_ = true;
    }

    void ProcessOverlay(const OverlayRequest& request) override
    {
        overlayProcessed_ = true;
    }

    void SwitchToOverlayMode() override
    {
        overlayModeSwitched_ = true;
    }

    void ToggleMenu() override
    {
        menuToggled_ = true;
    }

    void HideMenu(bool noAnimation = false, bool showSubMenu = false) override
    {
        menuHidden_ = true;
    }

    bool IsUsingMouse() override
    {
        return usingMouse_;
    }

    void SetUsingMouse(bool useMouse)
    {
        usingMouse_ = useMouse;
    }

    void UpdateHandleColor() override
    {
        handleColorUpdated_ = true;
    }

    bool SelectOverlayIsOn() override
    {
        return overlayOn_;
    }

    void SetSelectOverlayIsOn(bool isOn)
    {
        overlayOn_ = isOn;
    }

    void HandleOnCopy() override
    {
        copyHandled_ = true;
    }

    void HandleOnSelectAll() override
    {
        selectAllHandled_ = true;
    }

    CopyOptions GetCopyOption() const override
    {
        return copyOption_;
    }

    void SetCopyOption(CopyOptions option)
    {
        copyOption_ = option;
    }

    bool GetEnableHapticFeedback() const override
    {
        return enableHapticFeedback_;
    }

    void SetEnableHapticFeedback(bool enable)
    {
        enableHapticFeedback_ = enable;
    }

    std::optional<Color> GetSelectedBackgroundColor() const override
    {
        return selectedBackgroundColor_;
    }

    void SetSelectedBackgroundColor(const Color& color)
    {
        selectedBackgroundColor_ = color;
    }

    void ResetAllSelection()
    {
        selectionReset_ = true;
    }

    void MarkChildSortDirty()
    {
        sortDirtyMarked_ = true;
    }

    void OnSelectionRangeChanged(const std::vector<std::u16string>& selectedTexts) override
    {
        selectionChanged_ = true;
    }

    void OnChildResponseTypeChanged(TextResponseType responseType) override
    {
        responseTypeChanged_ = true;
    }

    void SetSourceType(SourceType sourceType) override
    {
        sourceTypeSet_ = true;
    }

    void SetMouseMenuOffset(const OffsetF& offset) override
    {
        mouseMenuOffsetSet_ = true;
    }

    bool BetweenSelectedPosition(const Offset& globalOffset) const override
    {
        return betweenSelectedPosition_;
    }

    void SetBetweenSelectedPosition(bool between)
    {
        betweenSelectedPosition_ = between;
    }

    void OnChildSelectedTypeSave() override
    {
        selectedTypeSaved_ = true;
    }

    void OnChildSelectionSpanTypeChanged(int32_t childId, const ChildSelectionSummary& oldSummary,
        const ChildSelectionSummary& newSummary) override
    {
        spanTypeChanged_ = true;
        lastChildId_ = childId;
        lastOldSummary_ = oldSummary;
        lastNewSummary_ = newSummary;
    }

    void UpdateSelectionBoundaryChild(const RefPtr<SelectionContainerChild>& child)
    {
        boundaryChildUpdated_ = true;
    }

    bool IsSelectionSessionOwner(const RefPtr<SelectionContainerChild>& child)
    {
        return isSessionOwner_;
    }

    void SetIsSessionOwner(bool isOwner)
    {
        isSessionOwner_ = isOwner;
    }

    bool IsSelectedBindSelectionMenu() const
    {
        return isBindMenu_;
    }

    void SetIsSelectedBindSelectionMenu(bool isBind)
    {
        isBindMenu_ = isBind;
    }

    void SetSelectionHoldCallback()
    {
        holdCallbackSet_ = true;
    }

    void SaveOldSelectedType() override
    {
        oldSelectedTypeSaved_ = true;
    }

    bool GetOverlayClosed() const
    {
        return overlayClosed_;
    }

    bool GetOverlayProcessed() const
    {
        return overlayProcessed_;
    }

    bool GetOverlayModeSwitched() const
    {
        return overlayModeSwitched_;
    }

    bool GetMenuToggled() const
    {
        return menuToggled_;
    }

    bool GetMenuHidden() const
    {
        return menuHidden_;
    }

    bool GetHandleColorUpdated() const
    {
        return handleColorUpdated_;
    }

    bool GetCopyHandled() const
    {
        return copyHandled_;
    }

    bool GetSelectAllHandled() const
    {
        return selectAllHandled_;
    }

    bool GetSelectionReset() const
    {
        return selectionReset_;
    }

    bool GetSortDirtyMarked() const
    {
        return sortDirtyMarked_;
    }

    bool GetSelectionChanged() const
    {
        return selectionChanged_;
    }

    bool GetResponseTypeChanged() const
    {
        return responseTypeChanged_;
    }

    bool GetSourceTypeSet() const
    {
        return sourceTypeSet_;
    }

    bool GetMouseMenuOffsetSet() const
    {
        return mouseMenuOffsetSet_;
    }

    bool GetSelectedTypeSaved() const
    {
        return selectedTypeSaved_;
    }

    bool GetSpanTypeChanged() const
    {
        return spanTypeChanged_;
    }

    int32_t GetLastChildId() const
    {
        return lastChildId_;
    }

    ChildSelectionSummary GetLastOldSummary() const
    {
        return lastOldSummary_;
    }

    ChildSelectionSummary GetLastNewSummary() const
    {
        return lastNewSummary_;
    }

    bool GetBoundaryChildUpdated() const
    {
        return boundaryChildUpdated_;
    }

private:
    RefPtr<FrameNode> hostNode_;
    std::u16string selectionText_;
    bool overlayClosed_ = false;
    bool overlayProcessed_ = false;
    bool overlayModeSwitched_ = false;
    bool menuToggled_ = false;
    bool menuHidden_ = false;
    bool usingMouse_ = false;
    bool handleColorUpdated_ = false;
    bool overlayOn_ = false;
    bool copyHandled_ = false;
    bool selectAllHandled_ = false;
    bool selectionReset_ = false;
    bool sortDirtyMarked_ = false;
    bool selectionChanged_ = false;
    bool responseTypeChanged_ = false;
    bool sourceTypeSet_ = false;
    bool mouseMenuOffsetSet_ = false;
    bool betweenSelectedPosition_ = false;
    bool selectedTypeSaved_ = false;
    bool spanTypeChanged_ = false;
    bool boundaryChildUpdated_ = false;
    bool isSessionOwner_ = false;
    bool isBindMenu_ = false;
    bool holdCallbackSet_ = false;
    bool oldSelectedTypeSaved_ = false;
    bool enableHapticFeedback_ = false;
    CopyOptions copyOption_ = CopyOptions::InApp;
    std::optional<Color> selectedBackgroundColor_;
    int32_t lastChildId_ = -1;
    ChildSelectionSummary lastOldSummary_;
    ChildSelectionSummary lastNewSummary_;
};

class SelectionContainerChildTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<MockSelectionContainerChildImpl> child_;
    RefPtr<FrameNode> childNode_;
    RefPtr<MockSelectionContainerImpl> container_;
    RefPtr<FrameNode> containerNode_;
};

void SelectionContainerChildTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void SelectionContainerChildTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectionContainerChildTest::SetUp()
{
    child_ = AceType::MakeRefPtr<MockSelectionContainerChildImpl>();
    childNode_ = FrameNode::CreateFrameNode(TEST_CHILD_TAG, TEST_NODE_ID, AceType::MakeRefPtr<Pattern>());
    child_->SetHostNode(childNode_);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 50.0f));
    childNode_->geometryNode_ = geometryNode;

    container_ = AceType::MakeRefPtr<MockSelectionContainerImpl>();
    containerNode_ = FrameNode::CreateFrameNode(TEST_CONTAINER_TAG, TEST_CONTAINER_ID, AceType::MakeRefPtr<Pattern>());
    container_->SetHostNode(containerNode_);
}

void SelectionContainerChildTest::TearDown()
{
    child_ = nullptr;
    childNode_ = nullptr;
    container_ = nullptr;
    containerNode_ = nullptr;
}

/**
 * @tc.name: GetSelectionCopyPayloadTest001
 * @tc.desc: Test GetSelectionCopyPayload001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, GetSelectionCopyPayloadTest001, TestSize.Level1)
{
    child_->SetSelectionText(TEST_SELECTION_TEXT);
    
    auto payload = child_->GetSelectionCopyPayload();
    
    EXPECT_EQ(payload.plainText, TEST_SELECTION_TEXT);
    EXPECT_TRUE(payload.spanString == nullptr);
}

/**
 * @tc.name: GetSelectionCopyPayloadTest002
 * @tc.desc: Test GetSelectionCopyPayload002 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, GetSelectionCopyPayloadTest002, TestSize.Level1)
{
    child_->SetSelectionText(TEST_EMPTY_TEXT);
    
    auto payload = child_->GetSelectionCopyPayload();
    
    EXPECT_TRUE(payload.plainText.empty());
}

/**
 * @tc.name: SetSelectionContainerTest001
 * @tc.desc: Test SetSelectionContainer with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SetSelectionContainerTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    auto result = child_->GetSelectionContainer();
    
    EXPECT_EQ(result, container_);
}

/**
 * @tc.name: ClearSelectionContainerTest001
 * @tc.desc: Test ClearSelectionContainer001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, ClearSelectionContainerTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    ChildSelectionSummary summary;
    summary.contributes = true;
    summary.type = TextSpanType::TEXT;
    child_->lastReportedSelectionSummary_ = summary;
    
    child_->ClearSelectionContainer();
    
    EXPECT_TRUE(child_->GetSelectionContainer() == nullptr);
    EXPECT_FALSE(child_->lastReportedSelectionSummary_.has_value());
}

/**
 * @tc.name: ClearSelectionContainerTest002
 * @tc.desc: Test ClearSelectionContainer002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, ClearSelectionContainerTest002, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->ClearSelectionContainer();
    
    EXPECT_TRUE(child_->GetSelectionContainer() == nullptr);
}

/**
 * @tc.name: NotifyContainerSelectionSpanTypeChangedTest001
 * @tc.desc: Test NotifyContainerSelectionSpanTypeChanged001 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifyContainerSelectionSpanTypeChangedTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    child_->lastReportedSelectionSummary_ = ChildSelectionSummary {};
    
    ChildSelectionSummary newSummary;
    newSummary.contributes = true;
    newSummary.type = TextSpanType::TEXT;
    
    child_->NotifyContainerSelectionSpanTypeChanged(newSummary);
    
    EXPECT_TRUE(container_->GetSpanTypeChanged());
    EXPECT_EQ(container_->GetLastChildId(), TEST_NODE_ID);
    EXPECT_TRUE(child_->lastReportedSelectionSummary_.has_value());
    EXPECT_EQ(child_->lastReportedSelectionSummary_->contributes, true);
}

/**
 * @tc.name: NotifyContainerSelectionSpanTypeChangedTest002
 * @tc.desc: Test NotifyContainerSelectionSpanTypeChanged002 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifyContainerSelectionSpanTypeChangedTest002, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    ChildSelectionSummary summary;
    summary.contributes = true;
    summary.type = TextSpanType::TEXT;
    child_->lastReportedSelectionSummary_ = summary;
    
    child_->NotifyContainerSelectionSpanTypeChanged(summary);
    
    EXPECT_FALSE(container_->GetSpanTypeChanged());
}

/**
 * @tc.name: NotifyContainerSelectionSpanTypeChangedTest003
 * @tc.desc: Test NotifyContainerSelectionSpanTypeChanged003 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifyContainerSelectionSpanTypeChangedTest003, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    ChildSelectionSummary oldSummary;
    oldSummary.contributes = true;
    oldSummary.type = TextSpanType::TEXT;
    child_->lastReportedSelectionSummary_ = oldSummary;
    
    ChildSelectionSummary newSummary;
    newSummary.contributes = false;
    newSummary.type = TextSpanType::NONE;
    
    child_->NotifyContainerSelectionSpanTypeChanged(newSummary);
    
    EXPECT_TRUE(container_->GetSpanTypeChanged());
    EXPECT_FALSE(child_->lastReportedSelectionSummary_.has_value());
}

/**
 * @tc.name: NotifyContainerSelectionSpanTypeChangedTest004
 * @tc.desc: Test NotifyContainerSelectionSpanTypeChanged004 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifyContainerSelectionSpanTypeChangedTest004, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    ChildSelectionSummary oldSummary;
    oldSummary.contributes = true;
    oldSummary.type = TextSpanType::TEXT;
    child_->lastReportedSelectionSummary_ = oldSummary;
    
    ChildSelectionSummary newSummary;
    newSummary.contributes = true;
    newSummary.type = TextSpanType::IMAGE;
    
    child_->NotifyContainerSelectionSpanTypeChanged(newSummary);
    
    EXPECT_TRUE(container_->GetSpanTypeChanged());
    EXPECT_EQ(child_->lastReportedSelectionSummary_->type, TextSpanType::IMAGE);
}

/**
 * @tc.name: NotifyContainerSelectionSpanTypeChangedTest005
 * @tc.desc: Test NotifyContainerSelectionSpanTypeChanged005 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifyContainerSelectionSpanTypeChangedTest005, TestSize.Level1)
{
    child_->SetSelectionContainer(nullptr);
    
    ChildSelectionSummary newSummary;
    newSummary.contributes = true;
    newSummary.type = TextSpanType::TEXT;
    
    child_->NotifyContainerSelectionSpanTypeChanged(newSummary);
    
    EXPECT_FALSE(container_->GetSpanTypeChanged());
}

/**
 * @tc.name: CloseSelectOverlayTest001
 * @tc.desc: Test CloseSelectOverlay001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, CloseSelectOverlayTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->CloseSelectOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
    
    EXPECT_TRUE(container_->GetOverlayClosed());
}

/**
 * @tc.name: SwitchToOverlayModeTest001
 * @tc.desc: Test SwitchToOverlayMode001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SwitchToOverlayModeTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->SwitchToOverlayMode();
    
    EXPECT_TRUE(container_->GetOverlayModeSwitched());
}

/**
 * @tc.name: ToggleMenuTest001
 * @tc.desc: Test ToggleMenu001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, ToggleMenuTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->ToggleMenu();
    
    EXPECT_TRUE(container_->GetMenuToggled());
}

/**
 * @tc.name: HideMenuTest001
 * @tc.desc: Test HideMenu001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, HideMenuTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->HideMenu(true, false);
    
    EXPECT_TRUE(container_->GetMenuHidden());
}

/**
 * @tc.name: IsUsingMouseTest001
 * @tc.desc: Test IsUsingMouse001 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, IsUsingMouseTest001, TestSize.Level1)
{
    container_->SetUsingMouse(true);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->IsUsingMouse();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsUsingMouseTest002
 * @tc.desc: Test IsUsingMouse002 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, IsUsingMouseTest002, TestSize.Level1)
{
    container_->SetUsingMouse(false);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->IsUsingMouse();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UpdateHandleColorTest001
 * @tc.desc: Test UpdateHandleColor001 handles event correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, UpdateHandleColorTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->UpdateHandleColor();
    
    EXPECT_TRUE(container_->GetHandleColorUpdated());
}

/**
 * @tc.name: SelectOverlayIsOnTest001
 * @tc.desc: Test SelectOverlayIsOn001 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SelectOverlayIsOnTest001, TestSize.Level1)
{
    container_->SetSelectOverlayIsOn(true);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->SelectOverlayIsOn();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectOverlayIsOnTest002
 * @tc.desc: Test SelectOverlayIsOn002 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SelectOverlayIsOnTest002, TestSize.Level1)
{
    container_->SetSelectOverlayIsOn(false);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->SelectOverlayIsOn();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleOnCopyTest001
 * @tc.desc: Test HandleOnCopy001 handles event correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, HandleOnCopyTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    auto result = child_->HandleOnCopy();
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(container_->GetCopyHandled());
}

/**
 * @tc.name: HandleOnSelectAllTest001
 * @tc.desc: Test HandleOnSelectAll001 handles event correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, HandleOnSelectAllTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    auto result = child_->HandleOnSelectAll();
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(container_->GetSelectAllHandled());
}

/**
 * @tc.name: NotifySelectionChangedTest001
 * @tc.desc: Test NotifySelectionChanged001 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifySelectionChangedTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->NotifySelectionChanged(TEST_SELECTION_TEXT);
    
    EXPECT_TRUE(container_->GetSelectionChanged());
}

/**
 * @tc.name: NotifyResponseTypeChangedTest001
 * @tc.desc: Test NotifyResponseTypeChanged001 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifyResponseTypeChangedTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->NotifyResponseTypeChanged(TextResponseType::SELECTED_BY_MOUSE);
    
    EXPECT_TRUE(container_->GetResponseTypeChanged());
}

/**
 * @tc.name: NotifySourceTypeChangedTest001
 * @tc.desc: Test NotifySourceTypeChanged001 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifySourceTypeChangedTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->NotifySourceTypeChanged(SourceType::MOUSE);
    
    EXPECT_TRUE(container_->GetSourceTypeSet());
}

/**
 * @tc.name: SetMouseMenuOffsetTest001
 * @tc.desc: Test SetMouseMenuOffset with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SetMouseMenuOffsetTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    OffsetF offset(TEST_OFFSET_X, TEST_OFFSET_Y);
    
    child_->SetMouseMenuOffset(offset);
    
    EXPECT_TRUE(container_->GetMouseMenuOffsetSet());
}

/**
 * @tc.name: BetweenContainerSelectedPositionTest001
 * @tc.desc: Test BetweenContainerSelectedPosition001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, BetweenContainerSelectedPositionTest001, TestSize.Level1)
{
    container_->SetBetweenSelectedPosition(true);
    child_->SetSelectionContainer(container_);
    
    Offset globalOffset;
    auto result = child_->BetweenContainerSelectedPosition(globalOffset);
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: BetweenContainerSelectedPositionTest002
 * @tc.desc: Test BetweenContainerSelectedPosition002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, BetweenContainerSelectedPositionTest002, TestSize.Level1)
{
    container_->SetBetweenSelectedPosition(false);
    child_->SetSelectionContainer(container_);
    
    Offset globalOffset;
    auto result = child_->BetweenContainerSelectedPosition(globalOffset);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NotifySelectedTypeSaveTest001
 * @tc.desc: Test NotifySelectedTypeSave001 notifies correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, NotifySelectedTypeSaveTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->NotifySelectedTypeSave();
    
    EXPECT_TRUE(container_->GetSelectedTypeSaved());
}

/**
 * @tc.name: GetContainerCopyOptionTest001
 * @tc.desc: Test GetContainerCopyOption001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, GetContainerCopyOptionTest001, TestSize.Level1)
{
    container_->SetCopyOption(CopyOptions::Distributed);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->GetContainerCopyOption();
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CopyOptions::Distributed);
}

/**
 * @tc.name: GetContainerEnableHapticFeedbackTest001
 * @tc.desc: Test GetContainerEnableHapticFeedback001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, GetContainerEnableHapticFeedbackTest001, TestSize.Level1)
{
    container_->SetEnableHapticFeedback(true);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->GetContainerEnableHapticFeedback();
    
    EXPECT_TRUE(result.has_value());
    EXPECT_TRUE(result.value());
}

/**
 * @tc.name: GetContainerEnableHapticFeedbackTest002
 * @tc.desc: Test GetContainerEnableHapticFeedback002 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, GetContainerEnableHapticFeedbackTest002, TestSize.Level1)
{
    container_->SetEnableHapticFeedback(false);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->GetContainerEnableHapticFeedback();
    
    EXPECT_TRUE(result.has_value());
    EXPECT_FALSE(result.value());
}

/**
 * @tc.name: GetContainerSelectedBackgroundColorTest001
 * @tc.desc: Test GetContainerSelectedBackgroundColor001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, GetContainerSelectedBackgroundColorTest001, TestSize.Level1)
{
    Color bgColor = Color(0xFFFF0000);
    container_->SetSelectedBackgroundColor(bgColor);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->GetContainerSelectedBackgroundColor();
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), bgColor);
}

/**
 * @tc.name: GetContainerSelectedBackgroundColorTest002
 * @tc.desc: Test GetContainerSelectedBackgroundColor002 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, GetContainerSelectedBackgroundColorTest002, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    auto result = child_->GetContainerSelectedBackgroundColor();
    
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: IsSelectedBindSelectionMenuTest001
 * @tc.desc: Test IsSelectedBindSelectionMenu001 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, IsSelectedBindSelectionMenuTest001, TestSize.Level1)
{
    container_->SetIsSelectedBindSelectionMenu(true);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->IsSelectedBindSelectionMenu();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsSelectedBindSelectionMenuTest002
 * @tc.desc: Test IsSelectedBindSelectionMenu002 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, IsSelectedBindSelectionMenuTest002, TestSize.Level1)
{
    container_->SetIsSelectedBindSelectionMenu(false);
    child_->SetSelectionContainer(container_);
    
    auto result = child_->IsSelectedBindSelectionMenu();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetSelectionHoldCallbackTest001
 * @tc.desc: Test SetSelectionHoldCallback with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SetSelectionHoldCallbackTest001, TestSize.Level1)
{
    child_->SetSelectionContainer(container_);
    
    child_->SetSelectionHoldCallback();
    
    EXPECT_TRUE(container_->holdCallbackSet_);
}

/**
 * @tc.name: SelectionCopyPayloadTest001
 * @tc.desc: Test SelectionCopyPayload001 operations
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SelectionCopyPayloadTest001, TestSize.Level1)
{
    SelectionCopyPayload payload1;
    payload1.plainText = TEST_SELECTION_TEXT;
    
    SelectionCopyPayload payload2(payload1);
    
    EXPECT_EQ(payload2.plainText, TEST_SELECTION_TEXT);
}

/**
 * @tc.name: SelectionCopyPayloadTest002
 * @tc.desc: Test SelectionCopyPayload002 operations
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SelectionCopyPayloadTest002, TestSize.Level1)
{
    SelectionCopyPayload payload1;
    payload1.plainText = TEST_SELECTION_TEXT;
    
    SelectionCopyPayload payload2(std::move(payload1));
    
    EXPECT_EQ(payload2.plainText, TEST_SELECTION_TEXT);
}

/**
 * @tc.name: SelectionCopyPayloadTest003
 * @tc.desc: Test SelectionCopyPayload003 operations
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SelectionCopyPayloadTest003, TestSize.Level1)
{
    SelectionCopyPayload payload1;
    payload1.plainText = TEST_SELECTION_TEXT;
    
    SelectionCopyPayload payload2;
    payload2 = payload1;
    
    EXPECT_EQ(payload2.plainText, TEST_SELECTION_TEXT);
}

/**
 * @tc.name: SelectionCopyPayloadTest004
 * @tc.desc: Test SelectionCopyPayload004 operations
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, SelectionCopyPayloadTest004, TestSize.Level1)
{
    SelectionCopyPayload payload1;
    payload1.plainText = TEST_SELECTION_TEXT;
    
    SelectionCopyPayload payload2;
    payload2 = std::move(payload1);
    
    EXPECT_EQ(payload2.plainText, TEST_SELECTION_TEXT);
}

/**
 * @tc.name: ChildSelectionSummaryEqualityTest001
 * @tc.desc: Test ChildSelectionSummaryEquality001 compares correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, ChildSelectionSummaryEqualityTest001, TestSize.Level1)
{
    ChildSelectionSummary summary1;
    summary1.contributes = true;
    summary1.type = TextSpanType::TEXT;
    
    ChildSelectionSummary summary2;
    summary2.contributes = true;
    summary2.type = TextSpanType::TEXT;
    
    EXPECT_TRUE(summary1 == summary2);
}

/**
 * @tc.name: ChildSelectionSummaryEqualityTest002
 * @tc.desc: Test ChildSelectionSummaryEquality002 compares correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, ChildSelectionSummaryEqualityTest002, TestSize.Level1)
{
    ChildSelectionSummary summary1;
    summary1.contributes = true;
    summary1.type = TextSpanType::TEXT;
    
    ChildSelectionSummary summary2;
    summary2.contributes = false;
    summary2.type = TextSpanType::TEXT;
    
    EXPECT_FALSE(summary1 == summary2);
}

/**
 * @tc.name: ChildSelectionSummaryEqualityTest003
 * @tc.desc: Test ChildSelectionSummaryEquality003 compares correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, ChildSelectionSummaryEqualityTest003, TestSize.Level1)
{
    ChildSelectionSummary summary1;
    summary1.contributes = true;
    summary1.type = TextSpanType::TEXT;
    
    ChildSelectionSummary summary2;
    summary2.contributes = true;
    summary2.type = TextSpanType::IMAGE;
    
    EXPECT_FALSE(summary1 == summary2);
}

/**
 * @tc.name: ChildSelectionSummaryInequalityTest001
 * @tc.desc: Test ChildSelectionSummaryInequality001 compares correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, ChildSelectionSummaryInequalityTest001, TestSize.Level1)
{
    ChildSelectionSummary summary1;
    summary1.contributes = true;
    summary1.type = TextSpanType::TEXT;
    
    ChildSelectionSummary summary2;
    summary2.contributes = true;
    summary2.type = TextSpanType::IMAGE;
    
    EXPECT_TRUE(summary1 != summary2);
}

/**
 * @tc.name: ChildSelectionSummaryInequalityTest002
 * @tc.desc: Test ChildSelectionSummaryInequality002 compares correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerChildTest, ChildSelectionSummaryInequalityTest002, TestSize.Level1)
{
    ChildSelectionSummary summary1;
    summary1.contributes = true;
    summary1.type = TextSpanType::TEXT;
    
    ChildSelectionSummary summary2;
    summary2.contributes = true;
    summary2.type = TextSpanType::TEXT;
    
    EXPECT_FALSE(summary1 != summary2);
}

} // namespace OHOS::Ace::NG