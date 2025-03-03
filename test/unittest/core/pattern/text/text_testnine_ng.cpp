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
} // namespace OHOS::Ace::NG