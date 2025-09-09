/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_clipboard.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
} // namespace

class RichEditorTouchTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<RichEditorPattern> GetRichEditorPattern();
    static void TearDownTestSuite();
};

void RichEditorTouchTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorTouchTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorTouchTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorTouchTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: HandleTouchMove001
 * @tc.desc: test HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::MOVE;
    touchLocationInfo.localLocation_ = Offset(10.0f, 20.0f);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->textSelector_.baseOffset = richEditorPattern->caretPosition_ - 1;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleTouchMove(touchLocationInfo);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, richEditorPattern->caretPosition_);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->HandleTouchMove(touchLocationInfo);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, richEditorPattern->caretPosition_);
    /**
     * @tc.steps: step4. change parameter and call function.
     */
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->HandleTouchMove(touchLocationInfo);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, richEditorPattern->caretPosition_);
    /**
     * @tc.steps: step5. change parameter and call function.
     */
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->selectOverlay_->ProcessOverlay({ .animation = false });
    auto manager = richEditorPattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
    ASSERT_NE(manager, nullptr);
    SelectOverlayInfo info;
    manager->CreateSelectOverlay(info);
    ASSERT_NE(manager->shareOverlayInfo_, nullptr);
    manager->shareOverlayInfo_->isSingleHandle = true;
    richEditorPattern->HandleTouchMove(touchLocationInfo);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, richEditorPattern->caretPosition_);
}

/**
 * @tc.name: HandleTouchMove002
 * @tc.desc: test HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchMove002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->editingLongPress_ = false;
    richEditorPattern->moveCaretState_.isTouchCaret = true;
    richEditorPattern->moveCaretState_.isMoveCaret = false;
    richEditorPattern->moveCaretState_.touchDownOffset = Offset(5.0f, 5.0f);
    richEditorPattern->caretTwinkling_ = true;
    Offset offset(5.0f, 5.0f);
    auto moveDistance = (offset - richEditorPattern->moveCaretState_.touchDownOffset).GetDistance();
    ASSERT_GT(richEditorPattern->moveCaretState_.minDistance.ConvertToPx(), moveDistance);
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetGlobalLocation(offset);
    richEditorPattern->HandleTouchMove(touchLocationInfo);
    EXPECT_EQ(richEditorPattern->moveCaretState_.touchFingerId, touchLocationInfo.fingerId_);
}

/**
 * @tc.name: HandleTouchMove003
 * @tc.desc: test HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchMove003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->editingLongPress_ = false;
    richEditorPattern->moveCaretState_.isTouchCaret = true;
    richEditorPattern->moveCaretState_.isMoveCaret = true;
    richEditorPattern->moveCaretState_.touchDownOffset = Offset(5.0f, 5.0f);
    Offset offset(5.01f, 5.01f);
    auto moveDistance = (offset - richEditorPattern->moveCaretState_.touchDownOffset).GetDistance();
    ASSERT_LE(moveDistance, richEditorPattern->moveCaretState_.minDistance.ConvertToPx() + 0.001f);
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetGlobalLocation(offset);
    richEditorPattern->HandleTouchMove(touchLocationInfo);
    EXPECT_NE(richEditorPattern->moveCaretState_.touchFingerId, touchLocationInfo.fingerId_);
}

/**
 * @tc.name: HandleTouchUp001
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchUp001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->moveCaretState_.isTouchCaret = true;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->magnifierController_->isShowMagnifier_ = true;
    richEditorPattern->HandleTouchUp();
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: HandleTouchUp002
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchUp002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->moveCaretState_.isMoveCaret = true;
    richEditorPattern->HandleTouchUp();
    EXPECT_FALSE(richEditorPattern->isCursorAlwaysDisplayed_);
}

/**
 * @tc.name: HandleTouchUp003
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchUp003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->magnifierController_->isShowMagnifier_ = true;
    auto removeFrameNode = richEditorPattern->magnifierController_->removeFrameNode_;
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->HandleTouchUp();
    EXPECT_FALSE(removeFrameNode);
}

/**
 * @tc.name: HandleTouchUp004
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchUp004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    richEditorPattern->editingLongPress_ = true;
    richEditorPattern->isEditing_ = false;
    richEditorPattern->HandleTouchUp();
    EXPECT_EQ(richEditorPattern->editingLongPress_, false);
    richEditorPattern->editingLongPress_ = true;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->HandleTouchUp();
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchEvent001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    auto touchInfo = touchEventInfo.GetTouches().front();
    auto touchType = touchInfo.GetTouchType();
    EXPECT_EQ(touchType, TouchType::DOWN);
}

/**
 * @tc.name: HandleTouchEvent002
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchEvent002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::UP;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    auto touchInfo = touchEventInfo.GetTouches().front();
    auto touchType = touchInfo.GetTouchType();
    EXPECT_EQ(touchType, TouchType::UP);
}

/**
 * @tc.name: HandleTouchEvent003
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchEvent003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::MOVE;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    auto touchInfo = touchEventInfo.GetTouches().front();
    auto touchType = touchInfo.GetTouchType();
    EXPECT_EQ(touchType, TouchType::MOVE);
}

/**
 * @tc.name: HandleTouchEvent004
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchEvent004, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::UNKNOWN;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    auto touchInfo = touchEventInfo.GetTouches().front();
    auto touchType = touchInfo.GetTouchType();
    EXPECT_EQ(touchType, TouchType::UNKNOWN);
}

/**
 * @tc.name: HandleTouchEvent005
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchEvent005, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->hasUrlSpan_ = true;
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(richEditorPattern->moveCaretState_.touchDownOffset, touchLocationInfo.localLocation_);
}

/**
 * @tc.name: HandleTouchEvent006
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleTouchEvent006, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::UP;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->hasUrlSpan_ = true;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: UpdateSelectionByTouchMove001
 * @tc.desc: test UpdateSelectionByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, UpdateSelectionByTouchMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isEditing_ = true;
    Offset touchOffset(11.0f, 11.0f);
    richEditorPattern->UpdateSelectionByTouchMove(touchOffset);
    EXPECT_TRUE(richEditorPattern->isShowMenu_);
}

/**
 * @tc.name: UpdateSelectionByTouchMove002
 * @tc.desc: test UpdateSelectionByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, UpdateSelectionByTouchMove002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isEditing_ = true;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_1);
    Offset touchOffset(20.0f, 20.0f);
    richEditorPattern->UpdateSelectionByTouchMove(touchOffset);
    ASSERT_NE(richEditorPattern->magnifierController_, nullptr);
    EXPECT_EQ(touchOffset.GetX(), richEditorPattern->magnifierController_->localOffset_.GetX());
    EXPECT_EQ(touchOffset.GetY(), richEditorPattern->magnifierController_->localOffset_.GetY());
    EXPECT_TRUE(richEditorPattern->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: UpdateSelectionByTouchMove003
 * @tc.desc: test UpdateSelectionByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, UpdateSelectionByTouchMove003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isEditing_ = true;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_1);
    Offset touchOffset(20.0f, 20.0f);
    richEditorPattern->magnifierController_ = nullptr;
    richEditorPattern->UpdateSelectionByTouchMove(touchOffset);
    EXPECT_TRUE(richEditorPattern->isShowMenu_);
}

/**
 * @tc.name: UpdateSelectionByTouchMove004
 * @tc.desc: test UpdateSelectionByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, UpdateSelectionByTouchMove004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isEditing_ = true;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->textSelector_.Update(0, 10);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_1);
    Offset touchOffset(20.0f, 20.0f);
    richEditorPattern->UpdateSelectionByTouchMove(touchOffset);
    EXPECT_TRUE(richEditorPattern->isShowMenu_);
}

/**
 * @tc.name: UpdateCaretByTouchMove001
 * @tc.desc: test UpdateCaretByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, UpdateCaretByTouchMove001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    Offset offset(1, 1);
    richEditorPattern->moveCaretState_.isMoveCaret = true;
    bool exist = richEditorPattern->magnifierController_->magnifierNodeExist_;
    richEditorPattern->magnifierController_ = nullptr;
    richEditorPattern->UpdateCaretByTouchMove(offset);
    EXPECT_FALSE(exist);
}

/**
 * @tc.name: OnOverlayTouchDown001
 * @tc.desc: test OnOverlayTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, OnOverlayTouchDown001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo info("text");
    richEditorPattern->selectOverlay_->OnOverlayTouchDown(info);
    EXPECT_FALSE(richEditorPattern->isOnlyRequestFocus_);
}

/**
 * @tc.name: OnOverlayTouchDown002
 * @tc.desc: test OnOverlayTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, OnOverlayTouchDown002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo info("text");
    info.SetSourceTool(SourceTool::MOUSE);
    richEditorPattern->selectOverlay_->OnOverlayTouchDown(info);
    EXPECT_EQ(info.GetSourceTool(), SourceTool::MOUSE);
    EXPECT_FALSE(richEditorPattern->isOnlyRequestFocus_);
}

/**
 * @tc.name: IsTouchInFrameArea001
 * @tc.desc: test IsTouchInFrameArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, IsTouchInFrameArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    PointF touchPoint;
    auto ret = richEditorPattern->IsTouchInFrameArea(touchPoint);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: TestRichEditorUpdateSelectionByTouchMove001
 * @tc.desc: test UpdateSelectionByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, TestRichEditorUpdateSelectionByTouchMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto richOffset = Offset(40, 30);
    richEditorPattern->UpdateSelectionByTouchMove(richOffset);
    auto host = richEditorPattern->GetContentHost();
    ASSERT_NE(host, nullptr);
    ASSERT_NE((host->layoutProperty_->propertyChangeFlag_) & PROPERTY_UPDATE_RENDER, 0);
}

/**
 * @tc.name: TestTestTouchedFingerCount
 * @tc.desc: test TestTouchedFingerCount
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, TestTouchedFingerCount, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& fingerCount = richEditorPattern->touchedFingerCount_;
    fingerCount = 0;
    TouchLocationInfo touchLocationInfo(0);
    richEditorPattern->HandleTouchDown(touchLocationInfo);
    EXPECT_NE(fingerCount, 0);
    richEditorPattern->HandleTouchUp();
    EXPECT_EQ(fingerCount, 0);
}

/**
 * @tc.name: HandleUserTouchEvent001
 * @tc.desc: test HandleUserTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTouchTestNg, HandleUserTouchEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    bool isTouchTrigger = false;
    firstSpanItem->onTouch = [&isTouchTrigger](TouchEventInfo& info) { isTouchTrigger = true; };
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    TouchEventInfo info = TouchEventInfo("default");
    TouchLocationInfo locationInfo = TouchLocationInfo(0);
    locationInfo.SetLocalLocation(Offset(3, 3));
    info.AddTouchLocationInfo(std::move(locationInfo));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    richEditorPattern->HandleUserTouchEvent(info);
    EXPECT_TRUE(isTouchTrigger);
}

}