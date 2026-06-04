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
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/components_ng/pattern/selection_container/selection_container_layout_property.h"
#include "core/components_ng/pattern/selection_container/selection_select_overlay.h"
#include "core/components_ng/pattern/text/text_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_NODE_ID_CHILD1 = 200;
constexpr int32_t TEST_NODE_ID_CHILD2 = 300;
constexpr int32_t TEST_NODE_ID_OVERLAY_ROOT = 110;
constexpr int32_t TEST_START_INDEX = 10;
constexpr int32_t TEST_END_INDEX = 20;
constexpr int32_t TEST_SELECT_ALL_END_INDEX = 100;
constexpr float TEST_WIDTH = 200.0f;
constexpr float TEST_HEIGHT = 50.0f;
constexpr float TEST_RECT_X = 10.0f;
constexpr float TEST_RECT_Y = 20.0f;
constexpr float TEST_RECT_WIDTH = 100.0f;
constexpr float TEST_RECT_HEIGHT = 30.0f;
const std::string TEST_TAG("SelectionContainer");
const std::string TEST_OVERLAY_ROOT_TAG("OverlayRoot");
const std::u16string TEST_SELECTION_TEXT1 = u"SelectedText1";
const std::u16string TEST_SELECTION_TEXT2 = u"SelectedText2";
const Color TEST_CARET_COLOR = Color(0xFFFF0000);
} // namespace

class MockTextBase : public TextBase {
    DECLARE_ACE_TYPE(MockTextBase, TextBase);

public:
    MockTextBase() = default;
    ~MockTextBase() override = default;

    bool BetweenSelectedPosition(const Offset& globalOffset) override
    {
        return betweenSelectedPosition_;
    }

    void SetBetweenSelectedPosition(bool between)
    {
        betweenSelectedPosition_ = between;
    }

    RefPtr<FrameNode> GetClientHost() const override
    {
        return clientHost_;
    }

    void SetClientHost(const RefPtr<FrameNode>& host)
    {
        clientHost_ = host;
    }

private:
    bool betweenSelectedPosition_ = false;
    RefPtr<FrameNode> clientHost_;
};

class MockSelectionContainerChildForOverlay : public SelectionContainerChild {
    DECLARE_ACE_TYPE(MockSelectionContainerChildForOverlay, SelectionContainerChild);

public:
    MockSelectionContainerChildForOverlay() = default;
    ~MockSelectionContainerChildForOverlay() override = default;

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

    std::optional<RectF> GetFirstHandleRect() override
    {
        if (hasFirstHandle_) {
            return RectF(TEST_RECT_X, TEST_RECT_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT);
        }
        return std::nullopt;
    }

    void SetHasFirstHandle(bool has)
    {
        hasFirstHandle_ = has;
    }

    std::optional<RectF> GetSecondHandleRect() override
    {
        if (hasSecondHandle_) {
            return RectF(TEST_RECT_X + 100.0f, TEST_RECT_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT);
        }
        return std::nullopt;
    }

    void SetHasSecondHandle(bool has)
    {
        hasSecondHandle_ = has;
    }

    RectF GetSelectionArea(const RefPtr<FrameNode>& targetNode, SelectRectsType pos) override
    {
        return RectF(TEST_RECT_X, TEST_RECT_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT);
    }

    SelectionIndexRange GetSelectionIndexesByPoints(const OffsetF& firstPoint, const OffsetF& secondPoint) override
    {
        return { TEST_START_INDEX, TEST_END_INDEX };
    }

    int32_t GetSelectionIndexByPoint(const OffsetF& point) override
    {
        return TEST_START_INDEX;
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

    void SelectAll() override
    {
        startIndex_ = 0;
        endIndex_ = TEST_SELECT_ALL_END_INDEX;
        selectionText_ = TEST_SELECTION_TEXT1;
        isSelectAll_ = true;
    }

    void UpdateSelectionHandleInfo() override
    {
        handleUpdated_ = true;
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

    CopyOptions GetCopyOption() const override
    {
        return copyOption_;
    }

    void SetCopyOption(CopyOptions option)
    {
        copyOption_ = option;
    }

    TextSpanType GetSelectionSpanType() const override
    {
        return TextSpanType::TEXT;
    }

    bool IsAskCeliaSupported() const override
    {
        return askCeliaSupported_;
    }

    void SetAskCeliaSupported(bool supported)
    {
        askCeliaSupported_ = supported;
    }

    bool HandleOnAskCelia(const std::u16string& selectedContent) override
    {
        askCeliaHandled_ = true;
        return askCeliaHandled_;
    }

    bool GetAskCeliaHandled() const
    {
        return askCeliaHandled_;
    }

    bool FireOnWillCopy(const std::u16string& selectedContent) override
    {
        return true;
    }

    void FireOnCopy(const std::u16string& selectedContent) override
    {
        onCopyFired_ = true;
    }

    SelectionCopyPayload GetSelectionCopyPayload() override
    {
        SelectionCopyPayload payload;
        payload.plainText = selectionText_;
        return payload;
    }

    void ResetOriginCaretPosition() override
    {
        caretReset_ = true;
    }

    void ReportSelectionText() override
    {
        textReported_ = true;
    }

    void StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex) override
    {
        vibratorStarted_ = true;
    }

    void OnContainerPropertyUpdate(uint32_t flags) override
    {
        propertyUpdated_ = true;
    }

private:
    RefPtr<FrameNode> hostNode_;
    std::u16string selectionText_;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    bool hasSelectableText_ = false;
    bool isSelectAll_ = false;
    bool canSelect_ = false;
    CopyOptions copyOption_ = CopyOptions::InApp;
    bool hasFirstHandle_ = false;
    bool hasSecondHandle_ = false;
    bool askCeliaSupported_ = false;
    bool askCeliaHandled_ = false;
    bool handleUpdated_ = false;
    bool onCopyFired_ = false;
    bool caretReset_ = false;
    bool textReported_ = false;
    bool vibratorStarted_ = false;
    bool propertyUpdated_ = false;
};

class SelectionSelectOverlayTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<SelectionContainerPattern> pattern_;
    RefPtr<FrameNode> containerNode_;
    RefPtr<MockTextBase> textBase_;
    RefPtr<SelectionSelectOverlay> overlay_;
    RefPtr<MockSelectionContainerChildForOverlay> child1_;
    RefPtr<FrameNode> childNode1_;
    RefPtr<MockSelectionContainerChildForOverlay> child2_;
    RefPtr<FrameNode> childNode2_;
};

void SelectionSelectOverlayTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void SelectionSelectOverlayTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectionSelectOverlayTest::SetUp()
{
    pattern_ = AceType::MakeRefPtr<SelectionContainerPattern>();
    containerNode_ = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern_, true);
    containerNode_->AttachToMainTree();
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    if (!layoutProperty) {
        layoutProperty = AceType::MakeRefPtr<SelectionContainerLayoutProperty>();
        containerNode_->layoutProperty_ = layoutProperty;
    }

    textBase_ = AceType::MakeRefPtr<MockTextBase>();
    textBase_->SetClientHost(containerNode_);

    overlay_ = AceType::MakeRefPtr<SelectionSelectOverlay>(textBase_, pattern_);

    child1_ = AceType::MakeRefPtr<MockSelectionContainerChildForOverlay>();
    childNode1_ = FrameNode::CreateFrameNode("Child1", TEST_NODE_ID_CHILD1, AceType::MakeRefPtr<Pattern>());
    child1_->SetHostNode(childNode1_);
    auto geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    geometryNode1->SetFrameSize(SizeF(TEST_WIDTH, TEST_HEIGHT));
    childNode1_->geometryNode_ = geometryNode1;
    childNode1_->SetParent(containerNode_);

    child2_ = AceType::MakeRefPtr<MockSelectionContainerChildForOverlay>();
    childNode2_ = FrameNode::CreateFrameNode("Child2", TEST_NODE_ID_CHILD2, AceType::MakeRefPtr<Pattern>());
    child2_->SetHostNode(childNode2_);
    auto geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    geometryNode2->SetFrameSize(SizeF(TEST_WIDTH, TEST_HEIGHT));
    childNode2_->geometryNode_ = geometryNode2;
    childNode2_->SetParent(containerNode_);
}

void SelectionSelectOverlayTest::TearDown()
{
    pattern_ = nullptr;
    containerNode_ = nullptr;
    textBase_ = nullptr;
    overlay_ = nullptr;
    child1_ = nullptr;
    childNode1_ = nullptr;
    child2_ = nullptr;
    childNode2_ = nullptr;
}

/**
 * @tc.name: CheckHandleVisibleTest001
 * @tc.desc: Test CheckHandleVisible001 handles event correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, CheckHandleVisibleTest001, TestSize.Level1)
{
    RectF paintRect(TEST_RECT_X, TEST_RECT_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT);
    EXPECT_TRUE(overlay_->CheckHandleVisible(paintRect));
}

/**
 * @tc.name: CheckHandleVisibleTest002
 * @tc.desc: Test CheckHandleVisible002 handles event correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, CheckHandleVisibleTest002, TestSize.Level1)
{
    RectF emptyRect;
    EXPECT_FALSE(overlay_->CheckHandleVisible(emptyRect));
}

/**
 * @tc.name: CheckHandleVisibleTest003
 * @tc.desc: Test CheckHandleVisible003 handles event correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, CheckHandleVisibleTest003, TestSize.Level1)
{
    RectF zeroSizeRect(TEST_RECT_X, TEST_RECT_Y, 0.0f, 0.0f);
    EXPECT_FALSE(overlay_->CheckHandleVisible(zeroSizeRect));
}

/**
 * @tc.name: GetOwnerTest001
 * @tc.desc: Test GetOwner001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetOwnerTest001, TestSize.Level1)
{
    auto owner = overlay_->GetOwner();
    EXPECT_EQ(owner, containerNode_);
}

/**
 * @tc.name: PreProcessOverlayTest001
 * @tc.desc: Test PreProcessOverlay001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, PreProcessOverlayTest001, TestSize.Level1)
{
    OverlayRequest request;
    request.animation = true;
    EXPECT_TRUE(overlay_->PreProcessOverlay(request));
}

/**
 * @tc.name: PreProcessOverlayTest002
 * @tc.desc: Test PreProcessOverlay002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, PreProcessOverlayTest002, TestSize.Level1)
{
    pattern_->SetSourceType(SourceType::MOUSE);
    OverlayRequest request;
    EXPECT_TRUE(overlay_->PreProcessOverlay(request));
}

/**
 * @tc.name: GetFirstHandleInfoTest001
 * @tc.desc: Test GetFirstHandleInfo001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetFirstHandleInfoTest001, TestSize.Level1)
{
    auto result = overlay_->GetFirstHandleInfo();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetFirstHandleInfoTest002
 * @tc.desc: Test GetFirstHandleInfo002 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetFirstHandleInfoTest002, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->selectionStartChild_ = child1_;
    child1_->SetHasFirstHandle(true);
    
    auto result = overlay_->GetFirstHandleInfo();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->paintRect.GetX(), TEST_RECT_X);
}

/**
 * @tc.name: GetSecondHandleInfoTest001
 * @tc.desc: Test GetSecondHandleInfo001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetSecondHandleInfoTest001, TestSize.Level1)
{
    auto result = overlay_->GetSecondHandleInfo();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetSecondHandleInfoTest002
 * @tc.desc: Test GetSecondHandleInfo002 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetSecondHandleInfoTest002, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->selectionEndChild_ = child1_;
    child1_->SetHasSecondHandle(true);
    
    auto result = overlay_->GetSecondHandleInfo();
    EXPECT_TRUE(result.has_value());
}

/**
 * @tc.name: OnUpdateMenuInfoTest001
 * @tc.desc: Test OnUpdateMenuInfo001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnUpdateMenuInfoTest001, TestSize.Level1)
{
    SelectMenuInfo menuInfo;
    overlay_->OnUpdateMenuInfo(menuInfo, DIRTY_COPY_ALL_ITEM);
    
    EXPECT_FALSE(menuInfo.showCopy);
    EXPECT_FALSE(menuInfo.showCopyAll);
    EXPECT_FALSE(menuInfo.showCut);
    EXPECT_FALSE(menuInfo.showPaste);
}

/**
 * @tc.name: OnUpdateMenuInfoTest002
 * @tc.desc: Test OnUpdateMenuInfo002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnUpdateMenuInfoTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::InApp);
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    
    SelectMenuInfo menuInfo;
    overlay_->OnUpdateMenuInfo(menuInfo, DIRTY_COPY_ALL_ITEM);
    
    EXPECT_TRUE(menuInfo.showCopy);
    EXPECT_TRUE(menuInfo.showCopyAll);
}

/**
 * @tc.name: OnUpdateMenuInfoTest003
 * @tc.desc: Test OnUpdateMenuInfo003
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnUpdateMenuInfoTest003, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::InApp);
    child1_->SetHasSelectableText(true);
    child1_->SetIsSelectAll(true);
    pattern_->RegisterChild(child1_);
    
    SelectMenuInfo menuInfo;
    overlay_->OnUpdateMenuInfo(menuInfo, DIRTY_COPY_ALL_ITEM);
    
    EXPECT_TRUE(menuInfo.showCopy);
    EXPECT_FALSE(menuInfo.showCopyAll);
}

/**
 * @tc.name: OnResetTextSelectionTest001
 * @tc.desc: Test OnResetTextSelection001 resets state correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnResetTextSelectionTest001, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    pattern_->RegisterChild(child1_);
    pattern_->selectionStartChild_ = child1_;
    pattern_->selectionEndChild_ = child1_;
    
    overlay_->OnResetTextSelection();
    
    EXPECT_TRUE(pattern_->selectionStartChild_.Upgrade() == nullptr);
    EXPECT_TRUE(pattern_->selectionEndChild_.Upgrade() == nullptr);
}

/**
 * @tc.name: GetHandleColorTest001
 * @tc.desc: Test GetHandleColor001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetHandleColorTest001, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    layoutProperty->UpdateCaretColor(TEST_CARET_COLOR);
    
    auto result = overlay_->GetHandleColor();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), TEST_CARET_COLOR);
}

/**
 * @tc.name: GetHandleColorTest002
 * @tc.desc: Test GetHandleColor002 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetHandleColorTest002, TestSize.Level1)
{
    auto result = overlay_->GetHandleColor();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetSelectedTextTest001
 * @tc.desc: Test GetSelectedText001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetSelectedTextTest001, TestSize.Level1)
{
    auto result = overlay_->GetSelectedText();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetSelectedTextTest002
 * @tc.desc: Test GetSelectedText002 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetSelectedTextTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    pattern_->RegisterChild(child1_);
    
    auto result = overlay_->GetSelectedText();
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: OnMenuItemActionTest001
 * @tc.desc: Test OnMenuItemAction001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnMenuItemActionTest001, TestSize.Level1)
{
    overlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemActionTest002
 * @tc.desc: Test OnMenuItemAction002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnMenuItemActionTest002, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    child1_->SetCanSelect(true);
    pattern_->RegisterChild(child1_);
    
    overlay_->OnMenuItemAction(OptionMenuActionId::SELECT_ALL, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemActionTest003
 * @tc.desc: Test OnMenuItemAction003
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnMenuItemActionTest003, TestSize.Level1)
{
    overlay_->OnMenuItemAction(OptionMenuActionId::TRANSLATE, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemActionTest004
 * @tc.desc: Test OnMenuItemAction004
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnMenuItemActionTest004, TestSize.Level1)
{
    overlay_->OnMenuItemAction(OptionMenuActionId::SEARCH, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemActionTest005
 * @tc.desc: Test OnMenuItemAction005
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnMenuItemActionTest005, TestSize.Level1)
{
    overlay_->OnMenuItemAction(OptionMenuActionId::SHARE, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemActionWithLabelTest001
 * @tc.desc: Test OnMenuItemActionWithLabel001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnMenuItemActionWithLabelTest001, TestSize.Level1)
{
    overlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::MOUSE_MENU, "label");
}

/**
 * @tc.name: AllowTranslateTest001
 * @tc.desc: Test AllowTranslate001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, AllowTranslateTest001, TestSize.Level1)
{
    EXPECT_FALSE(overlay_->AllowTranslate());
}

/**
 * @tc.name: AllowTranslateTest002
 * @tc.desc: Test AllowTranslate002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, AllowTranslateTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::Distributed);
    pattern_->RegisterChild(child1_);
    
    EXPECT_TRUE(overlay_->AllowTranslate());
}

/**
 * @tc.name: AllowSearchTest001
 * @tc.desc: Test AllowSearch001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, AllowSearchTest001, TestSize.Level1)
{
    EXPECT_FALSE(overlay_->AllowSearch());
}

/**
 * @tc.name: AllowSearchTest002
 * @tc.desc: Test AllowSearch002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, AllowSearchTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::Distributed);
    pattern_->RegisterChild(child1_);
    
    EXPECT_TRUE(overlay_->AllowSearch());
}

/**
 * @tc.name: AllowShareTest001
 * @tc.desc: Test AllowShare001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, AllowShareTest001, TestSize.Level1)
{
    EXPECT_FALSE(overlay_->AllowShare());
}

/**
 * @tc.name: AllowShareTest002
 * @tc.desc: Test AllowShare002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, AllowShareTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::Distributed);
    pattern_->RegisterChild(child1_);
    
    EXPECT_TRUE(overlay_->AllowShare());
}

/**
 * @tc.name: ResolveCopyOptionTest001
 * @tc.desc: Test ResolveCopyOption001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, ResolveCopyOptionTest001, TestSize.Level1)
{
    auto result = overlay_->ResolveCopyOptionForSelectedText();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: ResolveCopyOptionTest002
 * @tc.desc: Test ResolveCopyOption002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, ResolveCopyOptionTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::Distributed);
    pattern_->RegisterChild(child1_);
    
    auto result = overlay_->ResolveCopyOptionForSelectedText();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CopyOptions::Distributed);
}

/**
 * @tc.name: ResolveCopyOptionTest003
 * @tc.desc: Test ResolveCopyOption003
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, ResolveCopyOptionTest003, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::Distributed);
    
    child2_->SetSelectionText(TEST_SELECTION_TEXT2);
    child2_->SetCanSelect(true);
    child2_->SetCopyOption(CopyOptions::InApp);
    
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    
    auto result = overlay_->ResolveCopyOptionForSelectedText();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CopyOptions::InApp);
}

/**
 * @tc.name: ResolveCopyOptionTest004
 * @tc.desc: Test ResolveCopyOption004
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, ResolveCopyOptionTest004, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(false);
    child1_->SetCopyOption(CopyOptions::InApp);
    pattern_->RegisterChild(child1_);
    
    auto result = overlay_->ResolveCopyOptionForSelectedText();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: ResolveCopyOptionTest005
 * @tc.desc: Test ResolveCopyOption005
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, ResolveCopyOptionTest005, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::None);
    pattern_->RegisterChild(child1_);
    
    auto result = overlay_->ResolveCopyOptionForSelectedText();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: IsAskCeliaSupportedTest001
 * @tc.desc: Test IsAskCeliaSupported001 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, IsAskCeliaSupportedTest001, TestSize.Level1)
{
    EXPECT_FALSE(overlay_->IsAskCeliaSupported());
}

/**
 * @tc.name: IsAskCeliaSupportedTest002
 * @tc.desc: Test IsAskCeliaSupported002 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, IsAskCeliaSupportedTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetAskCeliaSupported(true);
    pattern_->RegisterChild(child1_);
    
    EXPECT_TRUE(overlay_->IsAskCeliaSupported());
}

/**
 * @tc.name: IsAskCeliaSupportedTest003
 * @tc.desc: Test IsAskCeliaSupported003 returns correct result
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, IsAskCeliaSupportedTest003, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetAskCeliaSupported(false);
    pattern_->RegisterChild(child1_);
    
    EXPECT_FALSE(overlay_->IsAskCeliaSupported());
}

/**
 * @tc.name: HandleOnAskCeliaTest001
 * @tc.desc: Test HandleOnAskCelia001 handles event correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, HandleOnAskCeliaTest001, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetAskCeliaSupported(true);
    pattern_->RegisterChild(child1_);
    
    overlay_->HandleOnAskCelia();
    
    EXPECT_TRUE(child1_->GetAskCeliaHandled());
}

/**
 * @tc.name: OnUpdateSelectOverlayInfoTest001
 * @tc.desc: Test OnUpdateSelectOverlayInfo001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnUpdateSelectOverlayInfoTest001, TestSize.Level1)
{
    SelectOverlayInfo overlayInfo;
    overlay_->OnUpdateSelectOverlayInfo(overlayInfo, 0);
    
    EXPECT_EQ(overlayInfo.clipHandleDrawRect, overlay_->IsClipHandleWithViewPort());
}

/**
 * @tc.name: OnUpdateSelectOverlayInfoTest002
 * @tc.desc: Test OnUpdateSelectOverlayInfo002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, OnUpdateSelectOverlayInfoTest002, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    layoutProperty->UpdateCaretColor(TEST_CARET_COLOR);
    
    SelectOverlayInfo overlayInfo;
    overlay_->OnUpdateSelectOverlayInfo(overlayInfo, 0);
    
    EXPECT_TRUE(overlayInfo.handlerColor.has_value());
    EXPECT_EQ(overlayInfo.handlerColor.value(), TEST_CARET_COLOR);
}

/**
 * @tc.name: HasValidSelectedTextTest001
 * @tc.desc: Test HasValidSelectedText001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, HasValidSelectedTextTest001, TestSize.Level1)
{
    EXPECT_FALSE(overlay_->HasValidSelectedText());
}

/**
 * @tc.name: HasValidSelectedTextTest002
 * @tc.desc: Test HasValidSelectedText002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, HasValidSelectedTextTest002, TestSize.Level1)
{
    child1_->SetSelectionText(TEST_SELECTION_TEXT1);
    child1_->SetCanSelect(true);
    child1_->SetCopyOption(CopyOptions::Distributed);
    pattern_->RegisterChild(child1_);
    
    EXPECT_TRUE(overlay_->HasValidSelectedText());
}

/**
 * @tc.name: CalcHandleLevelModeTest001
 * @tc.desc: Test CalcHandleLevelMode001 handles event correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, CalcHandleLevelModeTest001, TestSize.Level1)
{
    RectF firstRect(TEST_RECT_X, TEST_RECT_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT);
    RectF secondRect(TEST_RECT_X + 100.0f, TEST_RECT_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT);
    
    overlay_->CalcHandleLevelMode(firstRect, secondRect);
}

/**
 * @tc.name: GetSelectAreaFromRectsTest001
 * @tc.desc: Test GetSelectAreaFromRects001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetSelectAreaFromRectsTest001, TestSize.Level1)
{
    overlay_->pattern_ = nullptr;
    
    auto result = overlay_->GetSelectAreaFromRects(SelectRectsType::ALL_LINES);
    
    EXPECT_TRUE(result.IsEmpty());
}

/**
 * @tc.name: GetContainerVisibleRectTest001
 * @tc.desc: Test GetContainerVisibleRect001 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetContainerVisibleRectTest001, TestSize.Level1)
{
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH, TEST_HEIGHT));
    containerNode_->geometryNode_ = geometryNode;
    
    RefPtr<FrameNode> overlayRoot =
        FrameNode::CreateFrameNode(TEST_OVERLAY_ROOT_TAG, TEST_NODE_ID_OVERLAY_ROOT, AceType::MakeRefPtr<Pattern>());
    
    auto result = overlay_->GetContainerVisibleRect(containerNode_, overlayRoot);
    
    EXPECT_FALSE(result.IsEmpty());
}

/**
 * @tc.name: GetContainerVisibleRectTest002
 * @tc.desc: Test GetContainerVisibleRect002 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetContainerVisibleRectTest002, TestSize.Level1)
{
    RefPtr<FrameNode> nullContainer = nullptr;
    RefPtr<FrameNode> overlayRoot =
        FrameNode::CreateFrameNode(TEST_OVERLAY_ROOT_TAG, TEST_NODE_ID_OVERLAY_ROOT, AceType::MakeRefPtr<Pattern>());
    
    auto result = overlay_->GetContainerVisibleRect(nullContainer, overlayRoot);
    
    EXPECT_TRUE(result.IsEmpty());
}

/**
 * @tc.name: GetContainerVisibleRectTest003
 * @tc.desc: Test GetContainerVisibleRect003 returns expected value
 * @tc.type: FUNC
 */
HWTEST_F(SelectionSelectOverlayTest, GetContainerVisibleRectTest003, TestSize.Level1)
{
    RefPtr<FrameNode> overlayRoot = nullptr;
    
    auto result = overlay_->GetContainerVisibleRect(containerNode_, overlayRoot);
    
    EXPECT_TRUE(result.IsEmpty());
}

} // namespace OHOS::Ace::NG
