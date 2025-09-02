/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_base.h"
#include "ui/base/geometry/dimension.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {

class TextTestNineNg : public TextBases {
public:
    static void SetUpTestSuite();
    RefPtr<FrameNode> frameNode;
    RefPtr<TextPattern> pattern;
    void CreateText(std::string value)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        stack->StartGetAccessRecordingFor(0);
        TextModelNG textModelNG;
        textModelNG.Create(value);
        stack->StopGetAccessRecording();
        auto frameNode = AceType::DynamicCast<FrameNode>(stack->Finish());
        auto pattern = frameNode->GetPattern<TextPattern>();
        auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
        FlushUITasks(frameNode);
        return;
    }
};

void TextTestNineNg::SetUpTestSuite()
{
    TextBases::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
}

/**
 * @tc.name: OnHandleScrolling001
 * @tc.desc: test base_text_select_overlay.cpp OnHandleScrolling function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnHandleScrolling001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    RefPtr<FrameNode> scrollableNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto scrollNode = AccessibilityManager::WeakClaim(AceType::RawPtr(scrollableNode));
    textSelectOverlay->hasRegisterListener_ = true;
    textSelectOverlay->OnHandleScrolling(scrollNode);
    EXPECT_FALSE(textSelectOverlay->hasRegisterListener_);
}

/**
 * @tc.name: GlobalOffsetInSelectedArea001
 * @tc.desc: test text_pattern.cpp GlobalOffsetInSelectedArea function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, GlobalOffsetInSelectedArea001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->selectOverlay_->HasRenderTransform());
    Offset globalOffset(1.0, 1.0);
    EXPECT_FALSE(pattern->GlobalOffsetInSelectedArea(globalOffset));
}

/**
 * @tc.name: HandleOnTranslate001
 * @tc.desc: test text_pattern.cpp HandleOnTranslate001 function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, HandleOnTranslate001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(0);
    TextModelNG textModelNG;
    textModelNG.Create("TextValue");
    stack->StopGetAccessRecording();
    auto frameNode = AceType::DynamicCast<FrameNode>(stack->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    FlushUITasks(frameNode);

    auto textSelectOverlay = pattern->selectOverlay_;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern->HandleOnSelectAll();
    FlushUITasks(frameNode);
    textSelectOverlay->HandleOnTranslate();
    EXPECT_FALSE(textSelectOverlay->originalMenuIsShow_);
}

/**
 * @tc.name: OnHandleMoveStart001
 * @tc.desc: test text_pattern.cpp OnHandleMoveStart001 function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnHandleMoveStart001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(0);
    TextModelNG textModelNG;
    textModelNG.Create("TextValue");
    stack->StopGetAccessRecording();
    auto frameNode = AceType::DynamicCast<FrameNode>(stack->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    FlushUITasks(frameNode);

    GestureEvent info;
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    auto textSelectOverlay = pattern->selectOverlay_;
    textSelectOverlay->OnBind(manager);
    textSelectOverlay->OnOverlayClick(info, true);
    textSelectOverlay->OnHandleMoveStart(info, true);
    EXPECT_TRUE(textSelectOverlay->isHandleDragging_);
}

/**
 * @tc.name: OnMenuItemAction001
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnMenuItemAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get text pattern
     */
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(0);
    TextModelNG textModelNG;
    textModelNG.Create("TextValue");
    stack->StopGetAccessRecording();
    auto frameNode = AceType::DynamicCast<FrameNode>(stack->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    FlushUITasks(frameNode);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = frameNode->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();
    FlushUITasks(frameNode);

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */

    pattern->textSelector_.Update(0, 2);
    pattern->CalculateHandleOffsetAndShowOverlay();
    OverlayRequest request;
    request.menuIsShow = true;
    request.hideHandle = false;
    request.animation = false;
    request.hideHandleLine = false;
    request.requestCode = 0;
    pattern->ShowSelectOverlay(request);

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    pattern->isMousePressed_ = true;
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::MOUSE_MENU);
    EXPECT_FALSE(pattern->SelectOverlayIsOn());
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::SELECT_ALL, OptionMenuType::MOUSE_MENU);
    EXPECT_FALSE(pattern->SelectOverlayIsOn());
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::TRANSLATE, OptionMenuType::MOUSE_MENU);
    EXPECT_FALSE(pattern->SelectOverlayIsOn());
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::SEARCH, OptionMenuType::MOUSE_MENU);
    EXPECT_FALSE(pattern->SelectOverlayIsOn());
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::SHARE, OptionMenuType::MOUSE_MENU);
    EXPECT_FALSE(pattern->SelectOverlayIsOn());
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::CAMERA_INPUT, OptionMenuType::MOUSE_MENU);
    EXPECT_FALSE(pattern->SelectOverlayIsOn());
}

/**
 * @tc.name: OnMenuItemAction002
 * @tc.desc: test OnMenuItemAction, call memuCallback.onAIMenuOption
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnMenuItemAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get text pattern
     */
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(0);
    TextModelNG textModelNG;
    textModelNG.Create("TextValue");
    stack->StopGetAccessRecording();
    auto frameNode = AceType::DynamicCast<FrameNode>(stack->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    FlushUITasks(frameNode);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = frameNode->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();
    FlushUITasks(frameNode);

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */

    pattern->textSelector_.Update(0, 2);
    pattern->CalculateHandleOffsetAndShowOverlay();
    OverlayRequest request;
    request.menuIsShow = true;
    request.hideHandle = false;
    request.animation = false;
    request.hideHandleLine = false;
    request.requestCode = 0;
    pattern->ShowSelectOverlay(request);

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    pattern->isMousePressed_ = true;
    auto info = pattern->selectOverlay_->GetSelectOverlayInfos();
    info->menuCallback.onAIMenuOption("");
    EXPECT_FALSE(pattern->SelectOverlayIsOn());
    info->menuCallback.onAIMenuOption("test");
    EXPECT_FALSE(pattern->SelectOverlayIsOn());
}

HWTEST_F(TextTestNineNg, CheckHandleVisible001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 12
     * @tc.expected: targetNode != nullptr
     */
    auto lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. get text pattern
     */
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(0);
    TextModelNG textModelNG;
    textModelNG.Create("TextValue");
    stack->StopGetAccessRecording();
    auto frameNode = AceType::DynamicCast<FrameNode>(stack->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    FlushUITasks(frameNode);

    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(150.0f, 75.0f));

    pattern->selectOverlay_->enableHandleLevel_ = true;
    pattern->selectOverlay_->SetHandleLevelMode(HandleLevelMode::EMBED);
    auto isShow1 = pattern->selectOverlay_->CheckHandleVisible(RectF(0.0f, 0.0f, 10.0f, 10.0f));
    EXPECT_EQ(isShow1, true);

    pattern->selectOverlay_->isSingleHandle_ = true;
    auto isShow2 = pattern->selectOverlay_->CheckHandleVisible(RectF(0.0f, 0.0f, 10.0f, 10.0f));
    EXPECT_EQ(isShow2, true);

    /**
     * @tc.steps: step2. recover api version info.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
    MockContainer::Current()->SetApiTargetVersion(lastPlatformVersion);
}

/**
 * @tc.name: SetupMagnifier001
 * @tc.desc: test TextSelectOverlay::UpdateClipHandleViewPort(), while no AncestorNode & API 10.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, SetupMagnifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 10
     * @tc.expected: targetNode != nullptr
     */
    auto lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));

    auto [frameNode, pattern] = Init();
    pattern->contentRect_ = RectF { 0, 0, 30, 30 };
    pattern->copyOption_ = CopyOptions::Local;
    GestureEvent info;
    info.localLocation_ = Offset { 1, 1 };

    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), 0);

    /**
     * @tc.steps: step2. recover api version info.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
    MockContainer::Current()->SetApiTargetVersion(lastPlatformVersion);
}

/**
 * @tc.name: SetupMagnifier002
 * @tc.desc: test TextSelectOverlay::UpdateClipHandleViewPort(), while no AncestorNode & API 12.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, SetupMagnifier002, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->contentRect_ = RectF { 0, 0, 30, 30 };
    pattern->copyOption_ = CopyOptions::Local;
    GestureEvent info;
    info.localLocation_ = Offset { 1, 1 };

    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), 0);
}

/**
 * @tc.name: SetupMagnifier011
 * @tc.desc: test TextSelectOverlay::UpdateClipHandleViewPort(), while AncestorNode.clipEdge=false & visibleRect is
 * always {0，0，0，0} step into prev branch 1, it means text rect.Top() > page rect.Height().
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, SetupMagnifier011, TestSize.Level1)
{
    // 设置api 12
    auto [textNode, pattern] = Init();
    textNode->GetGeometryNode()->SetContentSize({ 5, 12 });
    textNode->GetGeometryNode()->SetContentOffset({ 5, 14 });
    pattern->copyOption_ = CopyOptions::Local;
    GestureEvent info;
    info.localLocation_ = Offset { 1, 1 };

    auto pageNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    textNode->SetParent(pageNode);

    pageNode->GetRenderContext()->UpdateClipEdge(false);
    auto pageGeoNode = pageNode->GetGeometryNode();

    pattern->HandleLongPress(info);
    EXPECT_EQ(5, pattern->magnifierController_->hostViewPort_->Width());
}

/**
 * @tc.name: SetupMagnifier013
 * @tc.desc: test TextSelectOverlay::UpdateClipHandleViewPort(), while AncestorNode.clipEdge=false, step into prev
 * branch 2&3, it means text rect.Top() < page rect.Height(); text rect.Left() > page rect.Width().
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, SetupMagnifier013, TestSize.Level1)
{
    // 设置api 12
    auto [textNode, pattern] = Init();
    textNode->GetGeometryNode()->SetContentSize({ 5, 10 });
    textNode->GetGeometryNode()->SetContentOffset({ 5, -20 });
    pattern->copyOption_ = CopyOptions::Local;
    GestureEvent info;
    info.localLocation_ = Offset { 1, 1 };

    auto pageNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    textNode->SetParent(pageNode);

    pageNode->GetRenderContext()->UpdateClipEdge(false);
    auto pageGeoNode = pageNode->GetGeometryNode();

    pattern->HandleLongPress(info);
    EXPECT_EQ(5, pattern->magnifierController_->hostViewPort_->Width());
}

/**
 * @tc.name: SetupMagnifier014
 * @tc.desc: test TextSelectOverlay::UpdateClipHandleViewPort(), while AncestorNode.clipEdge=false, step into prev
 * branch 2&4, it means text rect.Top() < page rect.Height(); text rect.Left() < page rect.Width().
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, SetupMagnifier014, TestSize.Level1)
{
    auto [textNode, pattern] = Init();
    textNode->GetGeometryNode()->SetContentSize({ 5, 10 });
    textNode->GetGeometryNode()->SetContentOffset({ -11, -20 });
    pattern->copyOption_ = CopyOptions::Local;
    GestureEvent info;
    info.localLocation_ = Offset { 1, 1 };

    auto pageNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    textNode->SetParent(pageNode);

    pageNode->GetRenderContext()->UpdateClipEdge(false);
    auto pageGeoNode = pageNode->GetGeometryNode();

    pattern->HandleLongPress(info);
    EXPECT_EQ(0, pattern->magnifierController_->hostViewPort_->Width());
}

/**
 * @tc.name: SetupMagnifier021
 * @tc.desc: test TextSelectOverlay::UpdateClipHandleViewPort(), while AncestorNode.clipEdge=true, step into clip branch
 * 1,, it means text rect.Top() > page rect.Height().
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, SetupMagnifier021, TestSize.Level1)
{
    auto [textNode, pattern] = Init();
    textNode->GetGeometryNode()->SetContentSize({ 5, 12 });
    textNode->GetGeometryNode()->SetContentOffset({ 5, 14 });
    pattern->copyOption_ = CopyOptions::Local;
    GestureEvent info;
    info.localLocation_ = Offset { 1, 1 };

    auto pageNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    textNode->SetParent(pageNode);

    // 需要给 swiper 加一个主题，主题的GetClip 返回一个true或false
    auto renderContext = pageNode->GetRenderContext();
    renderContext->UpdateClipEdge(true);

    pattern->HandleLongPress(info);
    EXPECT_EQ(5, pattern->magnifierController_->hostViewPort_->Width());
}

/**
 * @tc.name: SetupMagnifier022
 * @tc.desc: test TextSelectOverlay::UpdateClipHandleViewPort(), while AncestorNode.clipEdge=true, step into clip branch
 * 2&3,, it means text rect.Top() < page rect.Height(); text rect.Left() > page rect.Width()
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, SetupMagnifier022, TestSize.Level1)
{
    auto [textNode, pattern] = Init();
    textNode->GetGeometryNode()->SetContentSize({ 5, 10 });
    textNode->GetGeometryNode()->SetContentOffset({ 5, -20 });
    pattern->copyOption_ = CopyOptions::Local;
    GestureEvent info;
    info.localLocation_ = Offset { 1, 1 };

    auto pageNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    textNode->SetParent(pageNode);

    // 需要给 swiper 加一个主题，主题的GetClip 返回一个true或false
    auto renderContext = pageNode->GetRenderContext();
    renderContext->UpdateClipEdge(true);

    pattern->HandleLongPress(info);
    EXPECT_EQ(5, pattern->magnifierController_->hostViewPort_->Width());
}

/**
 * @tc.name: SetupMagnifier024
 * @tc.desc: test TextSelectOverlay::UpdateClipHandleViewPort(), while AncestorNode.clipEdge=true, step into clip branch
 * 2&4,, it means text rect.Top() < page rect.Height(); text rect.Left() < page rect.Width()
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, SetupMagnifier024, TestSize.Level1)
{
    auto [textNode, pattern] = Init();
    textNode->GetGeometryNode()->SetContentSize({ 5, 10 });
    textNode->GetGeometryNode()->SetContentOffset({ -11, -20 });
    pattern->copyOption_ = CopyOptions::Local;
    GestureEvent info;
    info.localLocation_ = Offset { 1, 1 };

    auto pageNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    textNode->SetParent(pageNode);

    // 需要给 swiper 加一个主题，主题的GetClip 返回一个true或false
    auto renderContext = pageNode->GetRenderContext();
    renderContext->UpdateClipEdge(true);

    pattern->HandleLongPress(info);
    EXPECT_EQ(0, pattern->magnifierController_->hostViewPort_->Width());
}

/**
 * @tc.name: CheckAndAdjustHandle001
 * @tc.desc: test text_pattern.cpp CheckAndAdjustHandle function, case clipEdge == false.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, CheckAndAdjustHandle001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    frameNode->GetRenderContext()->UpdateClipEdge(false);
    RectF paintRect = { 0, 0, 10, 10 };
    auto result = pattern->selectOverlay_->CheckAndAdjustHandle(paintRect);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckAndAdjustHandle002
 * @tc.desc: test text_pattern.cpp CheckAndAdjustHandle function, case clipEdge == true.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, CheckAndAdjustHandle002, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    frameNode->GetRenderContext()->UpdateClipEdge(true);
    RectF paintRect = { 0, 0, 10, 10 };
    auto result = pattern->selectOverlay_->CheckAndAdjustHandle(paintRect);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckAndAdjustHandle003
 * @tc.desc: test text_pattern.cpp CheckAndAdjustHandle function, case handleLevelMode_ == HandleLevelMode::EMBED.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, CheckAndAdjustHandle003, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    frameNode->GetRenderContext()->UpdateClipEdge(false);
    RectF paintRect = { 0, 0, 10, 10 };
    pattern->selectOverlay_->handleLevelMode_ = HandleLevelMode::EMBED;
    auto result = pattern->selectOverlay_->CheckAndAdjustHandle(paintRect);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: test text_pattern.cpp OnHandleMove function, case handleLevelMode_ == HandleLevelMode::OVERLAY.
    textPattern->HasContext == false
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnHandleMove001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    frameNode->GetRenderContext()->UpdateClipEdge(false);
    RectF handleRect = { 0, 0, 10, 10 };
    bool isFirst = true;
    pattern->textForDisplay_ = u"";
    pattern->selectOverlay_->handleLevelMode_ = HandleLevelMode::EMBED;
    pattern->selectOverlay_->OnHandleMove(handleRect, isFirst);
    EXPECT_EQ(-1, pattern->GetTextSelector().GetStart());
}

/**
* @tc.name: OnHandleMove002
* @tc.desc: test text_pattern.cpp OnHandleMove function, case textPattern->HasContext == true,
   magnifierController_ != nullptr.
* @tc.type: FUNC
*/
HWTEST_F(TextTestNineNg, OnHandleMove002, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    EXPECT_EQ(-1, pattern->GetTextSelector().GetStart());
    frameNode->GetRenderContext()->UpdateClipEdge(false);
    RectF handleRect = { 0, 0, 10, 10 };
    bool isFirst = true;
    pattern->textForDisplay_ = u"1";
    pattern->selectOverlay_->OnHandleMove(handleRect, isFirst);
    EXPECT_EQ(-1, pattern->GetTextSelector().GetStart());
}

/**
 * @tc.name: OnCloseOverlay001
 * @tc.desc: test text_select_overlay.cpp OnCloseOverlay function, case CloseReason == CLOSE_REASON_HOLD_BY_OTHER,
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnCloseOverlay001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->HandleOnSelectAll();
    EXPECT_EQ(0, pattern->GetTextSelector().GetStart());
    auto info = AceType::MakeRefPtr<OverlayInfo>();
    pattern->selectOverlay_->OnCloseOverlay(OptionMenuType::MOUSE_MENU, CloseReason::CLOSE_REASON_HOLD_BY_OTHER, info);
    EXPECT_EQ(-1, pattern->GetTextSelector().GetStart());
}

/**
 * @tc.name: OnCloseOverlay002
 * @tc.desc: test text_select_overlay.cpp OnCloseOverlay function, case CloseReason == CLOSE_REASON_TOOL_BAR,
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnCloseOverlay002, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->HandleOnSelectAll();
    EXPECT_EQ(0, pattern->GetTextSelector().GetStart());
    auto info = AceType::MakeRefPtr<OverlayInfo>();
    pattern->selectOverlay_->OnCloseOverlay(OptionMenuType::MOUSE_MENU, CloseReason::CLOSE_REASON_TOOL_BAR, info);
    EXPECT_EQ(-1, pattern->GetTextSelector().GetStart());
}

/**
 * @tc.name: OnCloseOverlay003
 * @tc.desc: test text_select_overlay.cpp OnCloseOverlay function, case CloseReason == CLOSE_REASON_BACK_PRESSED,
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnCloseOverlay003, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->HandleOnSelectAll();
    EXPECT_EQ(0, pattern->GetTextSelector().GetStart());
    auto info = AceType::MakeRefPtr<OverlayInfo>();
    pattern->selectOverlay_->OnCloseOverlay(OptionMenuType::MOUSE_MENU, CloseReason::CLOSE_REASON_BACK_PRESSED, info);
    EXPECT_EQ(-1, pattern->GetTextSelector().GetStart());
}

/**
* @tc.name: OnHandleGlobalTouchEvent001
* @tc.desc: test text_select_overlay.cpp OnHandleGlobalTouchEvent function, case sourceType == SourceType::MOUSE &&
    touchType == TouchType::DOWN, touchInside = false
* @tc.type: FUNC
*/
HWTEST_F(TextTestNineNg, OnHandleGlobalTouchEvent001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->HandleOnSelectAll();
    EXPECT_EQ(0, pattern->GetTextSelector().GetStart());
    pattern->selectOverlay_->OnHandleGlobalTouchEvent(SourceType::MOUSE, TouchType::DOWN, false);
    EXPECT_EQ(-1, pattern->GetTextSelector().GetStart());
}

/**
* @tc.name: OnHandleGlobalTouchEvent002
* @tc.desc: test text_select_overlay.cpp OnHandleGlobalTouchEvent function, case sourceType == SourceType::MOUSE &&
    touchType == TouchType::DOWN, touchInside = true
* @tc.type: FUNC
*/
HWTEST_F(TextTestNineNg, OnHandleGlobalTouchEvent002, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->HandleOnSelectAll();
    pattern->selectOverlay_->OnHandleGlobalTouchEvent(SourceType::MOUSE, TouchType::DOWN, true);
    EXPECT_EQ(0, pattern->GetTextSelector().GetStart());
}

/**
* @tc.name: OnHandleGlobalTouchEvent003
* @tc.desc: test text_select_overlay.cpp OnHandleGlobalTouchEvent function, case sourceType == SourceType::TOUCH &&
    touchType == TouchType::DOWN, touchInside = false
* @tc.type: FUNC
*/
HWTEST_F(TextTestNineNg, OnHandleGlobalTouchEvent003, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->HandleOnSelectAll();
    pattern->selectOverlay_->OnHandleGlobalTouchEvent(SourceType::TOUCH, TouchType::DOWN, false);
    EXPECT_EQ(0, pattern->GetTextSelector().GetStart());
}

/**
* @tc.name: OnHandleGlobalTouchEvent004
* @tc.desc: test text_select_overlay.cpp OnHandleGlobalTouchEvent function, case sourceType == SourceType::MOUSE &&
    touchType == TouchType::UP, touchInside = false
* @tc.type: FUNC
*/
HWTEST_F(TextTestNineNg, OnHandleGlobalTouchEvent004, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->HandleOnSelectAll();
    pattern->selectOverlay_->OnHandleGlobalTouchEvent(SourceType::MOUSE, TouchType::UP, false);
    EXPECT_EQ(0, pattern->GetTextSelector().GetStart());
}

/**
 * @tc.name: FindScrollableParent001
 * @tc.desc: test text_select_overlay.cpp FindScrollableParent function, case parent is page
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, FindScrollableParent001, TestSize.Level1)
{
    auto [textNode, pattern] = Init();
    auto pageNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    textNode->SetParent(pageNode);

    auto value = pattern->selectOverlay_->FindScrollableParent();
    EXPECT_EQ(value, nullptr);
}

/**
 * @tc.name: FindScrollableParent002
 * @tc.desc: test text_select_overlay.cpp FindScrollableParent function, case parent is list && scrollable
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, FindScrollableParent002, TestSize.Level1)
{
    auto [textNode, pattern] = Init();
    auto listNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ListPattern>(); });
    textNode->SetParent(listNode);
    auto listPattern = listNode->GetPattern<ListPattern>();
    listPattern->isScrollable_ = true;

    auto value = pattern->selectOverlay_->FindScrollableParent();
    EXPECT_EQ(value, listPattern);
}

/**
 * @tc.name: FindScrollableParent003
 * @tc.desc: test text_select_overlay.cpp FindScrollableParent function, case parent is list && !scrollable
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, FindScrollableParent003, TestSize.Level1)
{
    auto [textNode, pattern] = Init();
    auto listNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ListPattern>(); });
    textNode->SetParent(listNode);
    auto listPattern = listNode->GetPattern<ListPattern>();
    listPattern->isScrollable_ = false;

    auto value = pattern->selectOverlay_->FindScrollableParent();
    EXPECT_EQ(value, nullptr);
}

/**
 * @tc.name: UpdateShaderStyle001
 * @tc.desc: test UpdateShaderStyle of multiple paragraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateShaderStyle001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    pattern->AttachToFrameNode(frameNode);
    auto multipleAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    multipleAlgorithm->UpdateShaderStyle(layoutProperty, textStyle);
    EXPECT_EQ(textStyle.GetGradient(), std::nullopt);
    Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    layoutProperty->UpdateGradientShaderStyle(gradient);
    multipleAlgorithm->UpdateShaderStyle(layoutProperty, textStyle);
    auto advancedTextStyle = textStyle.advancedTextStyle_;
    EXPECT_NE(advancedTextStyle, nullptr);
    EXPECT_EQ(advancedTextStyle->GetGradient().value().GetType(), Ace::GradientType::RADIAL);
    EXPECT_EQ(textStyle.GetGradient().value().GetType(), Ace::GradientType::RADIAL);
    auto radius = 10.0;
    auto value = CalcDimension(radius);
    gradient.GetRadialGradient()->radialCenterX = value;
    gradient.GetRadialGradient()->radialCenterY = value;
    gradient.GetRadialGradient()->radialVerticalSize = value;
    gradient.GetRadialGradient()->radialHorizontalSize = value;
    layoutProperty->UpdateGradientShaderStyle(gradient);
    multipleAlgorithm->UpdateShaderStyle(layoutProperty, textStyle);
    AnimatableDimension result(value);
    EXPECT_EQ(textStyle.GetGradient().value().GetRadialGradient().radialCenterX, result);
    EXPECT_EQ(textStyle.GetGradient().value().GetRadialGradient().radialCenterY, result);
    EXPECT_EQ(textStyle.GetGradient().value().GetRadialGradient().radialVerticalSize, result);
    EXPECT_EQ(textStyle.GetGradient().value().GetRadialGradient().radialHorizontalSize, result);
}

/**
 * @tc.name: UpdateShaderStyle002
 * @tc.desc: test UpdateShaderStyle of multiple paragraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateShaderStyle002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    pattern->AttachToFrameNode(frameNode);
    auto multipleAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    multipleAlgorithm->UpdateShaderStyle(layoutProperty, textStyle);
    EXPECT_EQ(textStyle.GetGradient(), std::nullopt);
    Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    layoutProperty->UpdateGradientShaderStyle(gradient);
    multipleAlgorithm->UpdateShaderStyle(layoutProperty, textStyle);
    EXPECT_EQ(textStyle.GetGradient().value().GetType(), OHOS::Ace::GradientType::LINEAR);
    auto value = 10.0;
    auto values = CalcDimension(value);
    gradient.GetLinearGradient()->angle = values;
    gradient.GetLinearGradient()->linearX = GradientDirection::LEFT;
    gradient.GetLinearGradient()->linearY = GradientDirection::RIGHT;
    layoutProperty->UpdateGradientShaderStyle(gradient);
    multipleAlgorithm->UpdateShaderStyle(layoutProperty, textStyle);
    AnimatableDimension result(value);
    EXPECT_EQ(textStyle.GetGradient().value().GetLinearGradient().angle, result);
    EXPECT_EQ(textStyle.GetGradient().value().GetLinearGradient().linearX, OHOS::Ace::GradientDirection::LEFT);
    EXPECT_EQ(textStyle.GetGradient().value().GetLinearGradient().linearY, OHOS::Ace::GradientDirection::RIGHT);
}

/**
 * @tc.name: UpdateShaderStyle003
 * @tc.desc: Test ResetGradientShaderStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateShaderStyle003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    pattern->AttachToFrameNode(frameNode);
    Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    auto value = 10.0;
    auto values = CalcDimension(value);
    gradient.GetLinearGradient()->angle = values;
    gradient.GetLinearGradient()->linearX = GradientDirection::LEFT;
    gradient.GetLinearGradient()->linearY = GradientDirection::RIGHT;
    layoutProperty->UpdateGradientShaderStyle(gradient);
    auto gradientValue = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    AnimatableDimension result(value);
    ASSERT_NE(gradientValue.GetLinearGradient(), nullptr);
    EXPECT_EQ(gradientValue.GetLinearGradient()->angle, result);
    EXPECT_EQ(gradientValue.GetLinearGradient()->linearX, GradientDirection::LEFT);
    EXPECT_EQ(gradientValue.GetLinearGradient()->linearY, GradientDirection::RIGHT);
    layoutProperty->ResetGradientShaderStyle();
    auto gradientValue1 = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    EXPECT_EQ(gradientValue1.GetLinearGradient(), nullptr);
}

/**
 * @tc.name: UpdateShaderStyle004
 * @tc.desc: test UpdateShaderStyle of multiple paragraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateShaderStyle004, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    pattern->AttachToFrameNode(frameNode);
    auto multipleAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    multipleAlgorithm->UpdateShaderStyle(layoutProperty, textStyle);
    EXPECT_EQ(textStyle.GetGradient(), std::nullopt);
    Color color = Color::GREEN;
    layoutProperty->UpdateColorShaderStyle(color);
    multipleAlgorithm->UpdateShaderStyle(layoutProperty, textStyle);
    EXPECT_EQ(textStyle.GetColorShaderStyle().value(), Color::GREEN);
}

/**
 * @tc.name: UpdateShaderStyle005
 * @tc.desc: Test UpdateShaderStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateShaderStyle005, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test2", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    pattern->AttachToFrameNode(frameNode);
    Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    auto value = 5.0;
    auto values = CalcDimension(value);
    gradient.GetLinearGradient()->angle = values;
    gradient.GetLinearGradient()->linearX = GradientDirection::RIGHT;
    gradient.GetLinearGradient()->linearY = GradientDirection::LEFT;
    layoutProperty->UpdateGradientShaderStyle(gradient);

    auto gradientValue = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    AnimatableDimension result(value);
    ASSERT_NE(gradientValue.GetLinearGradient(), nullptr);
    EXPECT_EQ(gradientValue.GetLinearGradient()->angle, result);
    EXPECT_EQ(gradientValue.GetLinearGradient()->linearX, GradientDirection::RIGHT);
    EXPECT_EQ(gradientValue.GetLinearGradient()->linearY, GradientDirection::LEFT);
    layoutProperty->ResetGradientShaderStyle();
    auto gradientValue1 = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    EXPECT_EQ(gradientValue1.GetLinearGradient(), nullptr);
}

/**
 * @tc.name: UpdateShaderStyle006
 * @tc.desc: Test UpdateShaderStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateShaderStyle006, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test2", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    pattern->AttachToFrameNode(frameNode);
    Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    auto value = 5.0;
    auto values = CalcDimension(value);
    gradient.GetRadialGradient()->radialCenterX = values;
    gradient.GetRadialGradient()->radialCenterY = values;
    layoutProperty->UpdateGradientShaderStyle(gradient);

    auto gradientValue = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    AnimatableDimension result(value);
    ASSERT_NE(gradientValue.GetRadialGradient(), nullptr);
    EXPECT_EQ(gradientValue.GetRadialGradient()->radialCenterX, result);
    EXPECT_EQ(gradientValue.GetRadialGradient()->radialCenterY, result);
    layoutProperty->ResetGradientShaderStyle();
    auto gradientValue1 = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    EXPECT_EQ(gradientValue1.GetRadialGradient(), nullptr);
}

/**
 * @tc.name: UpdateShaderStyle007
 * @tc.desc: Test UpdateShaderStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateShaderStyle007, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test2", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    pattern->AttachToFrameNode(frameNode);
    Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    auto value1 = 5.0;
    auto values1 = CalcDimension(value1);
    auto value2 = 10.0;
    auto values2 = CalcDimension(value2);
    gradient.GetRadialGradient()->radialCenterX = values1;
    gradient.GetRadialGradient()->radialCenterY = values2;
    layoutProperty->UpdateGradientShaderStyle(gradient);

    auto gradientValue = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    AnimatableDimension result1(value1);
    AnimatableDimension result2(value2);
    ASSERT_NE(gradientValue.GetRadialGradient(), nullptr);
    EXPECT_EQ(gradientValue.GetRadialGradient()->radialCenterX, result1);
    EXPECT_EQ(gradientValue.GetRadialGradient()->radialCenterY, result2);
    layoutProperty->ResetGradientShaderStyle();
    auto gradientValue1 = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    EXPECT_EQ(gradientValue1.GetRadialGradient(), nullptr);
}

/**
 * @tc.name: UpdateShaderStyle008
 * @tc.desc: Test UpdateShaderStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateShaderStyle008, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test2", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    pattern->AttachToFrameNode(frameNode);
    Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    auto value1 = 5.0;
    auto values1 = CalcDimension(value1);
    auto value2 = 10.0;
    auto values2 = CalcDimension(value2);
    gradient.GetRadialGradient()->radialVerticalSize = values1;
    gradient.GetRadialGradient()->radialHorizontalSize = values2;
    layoutProperty->UpdateGradientShaderStyle(gradient);

    auto gradientValue = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    AnimatableDimension result1(value1);
    AnimatableDimension result2(value2);
    ASSERT_NE(gradientValue.GetRadialGradient(), nullptr);
    EXPECT_EQ(gradientValue.GetRadialGradient()->radialVerticalSize, result1);
    EXPECT_EQ(gradientValue.GetRadialGradient()->radialHorizontalSize, result2);
    layoutProperty->ResetGradientShaderStyle();
    auto gradientValue1 = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
    EXPECT_EQ(gradientValue1.GetRadialGradient(), nullptr);
}

/**
 * @tc.name: UpdateRelayoutShaderStyle
 * @tc.desc: Test UpdateRelayoutShaderStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, UpdateRelayoutShaderStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and Create function
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    textLayoutAlgorithm->UpdateRelayoutShaderStyle(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(textLayoutAlgorithm, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    textLayoutAlgorithm->paragraphManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 2 });
    TextStyle textStyle;
    Ace::Gradient gradient;
    textStyle.SetGradient(gradient);
    textLayoutAlgorithm->textStyle_ = textStyle;
    textLayoutAlgorithm->UpdateRelayoutShaderStyle(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(textLayoutAlgorithm->spans_.empty(), true);
    auto spanNode = AceType::MakeRefPtr<ImageSpanNode>("Test1", 1, pattern);
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    textLayoutAlgorithm->spans_.emplace_back(spanItem);
    textLayoutAlgorithm->UpdateRelayoutShaderStyle(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(textLayoutAlgorithm->spans_.empty(), false);
}

/**
 * @tc.name: IsFixIdealSizeAndNoMaxSize
 * @tc.desc: Test IsFixIdealSizeAndNoMaxSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, IsFixIdealSizeAndNoMaxSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and Create function
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    auto ret = textLayoutAlgorithm->IsFixIdealSizeAndNoMaxSize(AccessibilityManager::RawPtr(layoutWrapper), true);
    EXPECT_FALSE(ret);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    ret = textLayoutAlgorithm->IsFixIdealSizeAndNoMaxSize(AccessibilityManager::RawPtr(layoutWrapper), true);
    EXPECT_FALSE(ret);
    CalcSize size;
    layoutProperty->UpdateUserDefinedIdealSize(size);
    ret = textLayoutAlgorithm->IsFixIdealSizeAndNoMaxSize(AccessibilityManager::RawPtr(layoutWrapper), true);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CalcContentConstraint
 * @tc.desc: Test CalcContentConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, CalcContentConstraint, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and Create function
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(0.0f, 0.0f));
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    /**
     * @tc.steps: step2. call CalcContentConstraint.
     */
    LayoutConstraintF constraint;
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    auto newContentConstraint = textLayoutAlgorithm->CalcContentConstraint(constraint, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(newContentConstraint.maxSize.Width(), std::numeric_limits<double>::infinity());
    EXPECT_EQ(newContentConstraint.maxSize.Height(), std::numeric_limits<double>::infinity());

    MeasureProperty measureProp;
    measureProp.maxSize = CalcSize(CalcLength(200.0f, DimensionUnit::PX), CalcLength(200.0f, DimensionUnit::PX));
    measureProp.minSize = CalcSize(CalcLength(100.0f, DimensionUnit::PX), CalcLength(100.0f, DimensionUnit::PX));
    layoutProperty->UpdateCalcLayoutProperty(measureProp);
    LayoutConstraintF layoutConstraint;
    layoutProperty->layoutConstraint_ = layoutConstraint;
    newContentConstraint = textLayoutAlgorithm->CalcContentConstraint(constraint, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(newContentConstraint.maxSize.Width(), 200.0f);
    EXPECT_EQ(newContentConstraint.maxSize.Height(), 200.0f);

    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    constraint.parentIdealSize = OptionalSizeF(1000.0f, 2000.0f);
    newContentConstraint = textLayoutAlgorithm->CalcContentConstraint(constraint, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(newContentConstraint.selfIdealSize.Width(), 1000.0f);
    EXPECT_EQ(newContentConstraint.selfIdealSize.Height(), 2000.0f);

    constraint.maxSize = SizeF(500.0f, 500.0f);
    constraint.parentIdealSize = OptionalSizeF();
    newContentConstraint = textLayoutAlgorithm->CalcContentConstraint(constraint, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(newContentConstraint.selfIdealSize.Width(), std::nullopt);
    EXPECT_EQ(newContentConstraint.selfIdealSize.Height(), std::nullopt);
}

/**
 * @tc.name: MeasureWithFixAtIdealSize
 * @tc.desc: Test MeasureWithFixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, MeasureWithFixAtIdealSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and Create function
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(0.0f, 0.0f));
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraintF;
    layoutProperty->UpdateLayoutConstraint(layoutConstraintF);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    /**
     * @tc.steps: step2. call MeasureWithFixAtIdealSize.
     */
    // no layoutpolicy
    textLayoutAlgorithm->MeasureWithFixAtIdealSize(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(0.0f, 0.0f));

    // width = FIX_AT_IDEAL_SIZE, height = NO_MATCH
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    geometryNode->SetFrameSize(SizeF(0.0f, 0.0f));
    textLayoutAlgorithm->MeasureWithFixAtIdealSize(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(100.0f, 0.0f));

    // width = NO_MATCH, height = FIX_AT_IDEAL_SIZE
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    geometryNode->SetFrameSize(SizeF(0.0f, 0.0f));
    textLayoutAlgorithm->MeasureWithFixAtIdealSize(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(0.0f, 100.0f));

    // width = FIX_AT_IDEAL_SIZE, height = FIX_AT_IDEAL_SIZE
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    geometryNode->SetFrameSize(SizeF(0.0f, 0.0f));
    textLayoutAlgorithm->MeasureWithFixAtIdealSize(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(100.0f, 100.0f));

    // width = FIX_AT_IDEAL_SIZE, height = FIX_AT_IDEAL_SIZE maxCalcSize
    MeasureProperty calcProperty;
    calcProperty.maxSize =
        CalcSize(CalcLength(Dimension(80.0f, DimensionUnit::PX)), CalcLength(Dimension(80.0f, DimensionUnit::PX)));
    layoutProperty->UpdateCalcLayoutProperty(calcProperty);
    geometryNode->SetFrameSize(SizeF(0.0f, 0.0f));
    textLayoutAlgorithm->MeasureWithFixAtIdealSize(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(80.0f, 80.0f));
}
} // namespace OHOS::Ace::NG