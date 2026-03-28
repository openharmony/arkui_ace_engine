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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "text_base.h"

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/rosen/mock_canvas.h"
 #include "core/components_ng/pattern/text/span/tlv_util.h"

#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_select_overlay.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text/text_select_overlay.h"
#include "core/event/mouse_event.h"

namespace OHOS::Ace::NG {

class TextFieldTenPatternNg : public TextBases {
public:
};

class MockTextBase : public TextBase {
public:
    MOCK_METHOD1(BetweenSelectedPosition, bool(const Offset& globalOffset));
};

/**
 * @tc.name: OnVisibleChange001
 * @tc.desc: test OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnVisibleChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    bool isVisible = false;
    pattern->textDetectEnable_ = true;
    pattern->OnVisibleChange(isVisible);
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_FALSE(pattern->dataDetectorAdapter_->aiDetectDelayTask_);
}

/**
 * @tc.name: GetTextResultObject001
 * @tc.desc: test TextPattern GetTextResultObject
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetTextResultObject001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<UINode> uinode = nullptr;
    int32_t index = 10;
    int32_t start = 1;
    int32_t end = 100;

    pattern->GetTextResultObject(uinode, index, start, end);
    auto node = AceType::DynamicCast<SpanNode>(uinode);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: GetImageResultObject001
 * @tc.desc: test TextPattern GetImageResultObject
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetImageResultObject001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<UINode> uinode = nullptr;
    int32_t index = -10;
    int32_t start = 1;
    int32_t end = 100;

    pattern->GetImageResultObject(uinode, index, start, end);
    auto ret = pattern->GetSpanItemByIndex(index);
    EXPECT_EQ(ret, nullptr);

    index = 10;
    pattern->GetImageResultObject(uinode, index, start, end);
    auto node = AceType::DynamicCast<FrameNode>(uinode);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: MountImageNode001
 * @tc.desc: test TextPattern MountImageNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, MountImageNode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);

    auto imageItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    imageItem->options.imageAttribute = ImageSpanAttribute();
    imageItem->options.imageAttribute->colorFilterMatrix = std::vector<float>{0.5f, 1.0f, 0.2f, 1.0f};

    pattern->MountImageNode(imageItem);

    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        imageItem->nodeId_, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->HasImageFit(), false);
}

/**
 * @tc.name: ProcessSpanString001
 * @tc.desc: test TextPattern ProcessSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ProcessSpanString001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->textDetectEnable_ = true;
    EXPECT_TRUE(pattern->CanStartAITask());
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_FALSE(pattern->dataDetectorAdapter_->aiDetectInitialized_);

    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    pattern->ProcessSpanString();
    EXPECT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SetExternalSpanItem001
 * @tc.desc: test TextPattern SetExternalSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetExternalSpanItem001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    std::list<RefPtr<SpanItem>> spans;
    spans.emplace_back(spanItem);
    
    pattern->SetExternalSpanItem(spans);
    EXPECT_NE(pattern->styledString_, nullptr);
}

/**
 * @tc.name: PauseSymbolAnimation001
 * @tc.desc: test PauseSymbolAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, PauseSymbolAnimation001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->SetIsLoopAnimation(true);
    pattern->PauseSymbolAnimation();
    auto testSymbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    EXPECT_FALSE(testSymbolEffectOptions.GetIsTxtActive());

    SymbolEffectOptions symbolEffectOptions;
    symbolEffectOptions.SetIsTxtActive(true);
    layoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    testSymbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    EXPECT_TRUE(testSymbolEffectOptions.GetIsTxtActive());
    pattern->PauseSymbolAnimation();
    testSymbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    EXPECT_FALSE(testSymbolEffectOptions.GetIsTxtActive());
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSurfaceChanged001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, pattern);

    pattern->HandleSurfaceChanged(10, 10, 20, 20, WindowSizeChangeReason::UNDEFINED);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_TRUE(layoutProperty->propNeedReCreateParagraph_);
}

/**
 * @tc.name: AddImageToSpanItem001
 * @tc.desc: test AddImageToSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, AddImageToSpanItem001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::RICH_EDITOR_ETS_TAG, 0, pattern);

    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    pattern->AddImageToSpanItem(imageSpanNode);
    EXPECT_EQ(pattern->spans_.size(), 1);
}

/**
 * @tc.name: DumpSpanItem001
 * @tc.desc: test DumpSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, DumpSpanItem001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.push_back(spanItem);
    pattern->spans_.push_back(nullptr);
    pattern->isSpanStringMode_ = true;

    auto& dumpLog = DumpLog::GetInstance();
    pattern->DumpSpanItem();
    auto it = std::find(dumpLog.description_.begin(), dumpLog.description_.end(), "-----SpanDumpInfo-----\n");
    EXPECT_NE(it, dumpLog.description_.end());
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, DumpInfo001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, pattern);
    pattern->textStyle_ = TextStyle();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    pattern->pManager_ = nullptr;

    pattern->DumpInfo();
    auto& dumpLog = DumpLog::GetInstance();
    auto it = std::find(dumpLog.description_.begin(), dumpLog.description_.end(), "PaintInfo: NA\n");
    EXPECT_EQ(it, dumpLog.description_.end());
}

/**
 * @tc.name: HasContent001
 * @tc.desc: test TextPattern HasContent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HasContent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto span1 = AceType::MakeRefPtr<SpanItem>();
    span1->spanItemType = SpanItemType::NORMAL;
    pattern->spans_.push_back(span1);
    auto ret = pattern->HasContent();
    EXPECT_FALSE(ret);

    auto span2 = AceType::MakeRefPtr<SpanItem>();
    span2->spanItemType = SpanItemType::CustomSpan;
    pattern->spans_.push_back(span2);
    ret = pattern->HasContent();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ChangeHandleHeight001
 * @tc.desc: test TextPattern ChangeHandleHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ChangeHandleHeight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent event;
    bool isFirst = false;
    bool isOverlayMode = false;

    pattern->ChangeHandleHeight(event, isFirst, isOverlayMode);
    bool isChangeFirstHandle = isFirst ?
        (!pattern->textSelector_.StartGreaterDest()) : pattern->textSelector_.StartGreaterDest();
    EXPECT_FALSE(isChangeFirstHandle);
}

/**
 * @tc.name: ChangeFirstHandleHeight001
 * @tc.desc: test TextPattern ChangeFirstHandleHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ChangeFirstHandleHeight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    Offset touchOffset = Offset(10.0f, 5.0f);
    RectF handleRect = RectF(10.0f, 10.0f, 10.0f, 10.0f);
    pattern->ChangeFirstHandleHeight(touchOffset, handleRect);
    bool isTouchHandleCircle = LessNotEqual(touchOffset.GetY(), handleRect.Top());
    EXPECT_TRUE(isTouchHandleCircle);
}

/**
 * @tc.name: DumpInfoTest001
 * @tc.desc: test TextPattern DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, DumpInfoTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo info1;
    pattern->pManager_->paragraphs_.push_back(info1);

    SystemProperties::debugEnabled_ = true;
    pattern->DumpInfo(json);
    EXPECT_NE(pattern->pManager_, nullptr);
    EXPECT_FALSE(pattern->pManager_->GetParagraphs().empty());
    EXPECT_TRUE(SystemProperties::GetDebugEnabled());
    EXPECT_FALSE(json->Contains("Content"));
    EXPECT_FALSE(json->Contains("PaintInfo"));
    EXPECT_FALSE(json->Contains("contentRect"));
}

/**
 * @tc.name: LogForFormRender001
 * @tc.desc: test LogForFormRender
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, LogForFormRender001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    auto host = pattern->GetHost();
    auto pipeline = host->GetContext();
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();

    std::string logTag = "logTag";
    pipeline->SetIsFormRender(true);
    pattern->spans_.clear();
    pattern->spans_.push_back(spanItem);
    pattern->isSensitive_ = false;
    pattern->LogForFormRender(logTag);
    EXPECT_FALSE(pattern->IsSetObscured());

    pipeline->SetIsFormRender(true);
    pattern->spans_.clear();
    pattern->spans_.push_back(spanItem);
    pattern->isSensitive_ = true;
    pattern->LogForFormRender(logTag);
    EXPECT_FALSE(pattern->IsSetObscured());

    pipeline->SetIsFormRender(false);
    pattern->spans_.clear();
    pattern->isSensitive_ = false;
    pattern->LogForFormRender(logTag);
    EXPECT_FALSE(pattern->IsSensitiveEnable());

    pipeline->SetIsFormRender(false);
    pattern->spans_.clear();
    pattern->spans_.push_back(spanItem);
    pattern->isSensitive_ = false;
    pattern->LogForFormRender(logTag);
    EXPECT_FALSE(pattern->IsSensitiveEnable());
}

/**
 * @tc.name: HandleMouseLeftMoveAction001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseLeftMoveAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::None;

    /**
     * @tc.steps: step2. Set IsSelectableAndCopy is true.
     * @tc.expect: isMousePressed_ value will  be change.
     */
    MouseInfo info;
    Offset offset(1, 1);
    pattern->HandleMouseLeftMoveAction(info, offset);
    EXPECT_EQ(pattern->isMousePressed_, false);
}

/**
 * @tc.name: HandleMouseLeftMoveAction002
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseLeftMoveAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. Set IsSelectableAndCopy is false.
     * @tc.expect: mouseStatus_ value result  MOVE.
     */
    MouseInfo info;
    Offset offset(1, 1);
    pattern->isMousePressed_ = true;
    pattern->leftMousePressed_ = true;
    pattern->HandleMouseLeftMoveAction(info, offset);
    EXPECT_EQ(pattern->mouseStatus_, MouseStatus::MOVE);
}

/**
 * @tc.name: HandleMouseRightButton001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseRightButton001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, InitMouseEvent.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetTextDetectEnable(true);
    auto host = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = host->GetPattern<TextPattern>();
    auto inputHub = host->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    inputHub->mouseEventActuator_->inputEvents_.clear();
    pattern->mouseEventInitialized_ = false;
    pattern->InitMouseEvent();

    /**
     * @tc.steps: step2. test HandleMouseRightButton function and MouseButton LEFT_BUTTON.
     * @tc.expect:hasClickedAISpan_ is false.
     */
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    Offset offset(5.f, 5.f);
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->copyOption_ = CopyOptions::None;
    pattern->HandleMouseRightButton(info, offset);
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_FALSE(pattern->dataDetectorAdapter_->hasClickedAISpan_);

    /**
     * @tc.steps: step3. test HandleMouseRightButton function and MouseButton RIGHT_BUTTON..
     * @tc.expect: hasClickedAISpan_ is false.
     */
    pattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->HandleMouseRightButton(info, offset);
    EXPECT_FALSE(pattern->dataDetectorAdapter_->hasClickedAISpan_);

    info.SetAction(MouseAction::PRESS);
    pattern->HandleMouseRightButton(info, offset);
    EXPECT_NE(pattern->dataDetectorAdapter_->hasClickedAISpan_, true);
}

/**
 * @tc.name: UpdateShiftFlag001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, UpdateShiftFlag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern and KeyEvent.
     * @tc.expected: Ensure that the pattern is not empty.
     */
    
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    KeyEvent keyEvent;

    /**
     * @tc.steps: step2. pressing the left Shift KeyAction:: DOWN
     * @tc.expected: called UpdateShiftFlag shiftFlag_ should be set to true.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SHIFT_LEFT;
    keyEvent.pressedCodes.push_back(KeyCode::KEY_SHIFT_LEFT);
    pattern->UpdateShiftFlag(keyEvent);
    EXPECT_EQ(pattern->shiftFlag_, true);

    /**
     * @tc.steps: step2. pressing the left Shift KeyAction:: UP
     * @tc.expected: called UpdateShiftFlag shiftFlag_ should be set to false.
     */
    keyEvent.action = KeyAction::UP;
    pattern->shiftFlag_ = true;
    keyEvent.pressedCodes.clear();
    pattern->UpdateShiftFlag(keyEvent);
    EXPECT_EQ(pattern->shiftFlag_, false);
}

/**
 * @tc.name: CreateTextDragInfo001
 * @tc.desc: test CreateTextDragInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, CreateTextDragInfo001, TestSize.Level1)
{
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<TextPattern> pattern = textNode->GetPattern<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    RefPtr<MockTextBase> mockBase = AIWriteAdapter::MakeRefPtr<MockTextBase>();
    WeakPtr<MockTextBase> textBase = mockBase;
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->ToggleMenu();
    pattern->AttachToFrameNode(frameNode);

    RectF paintRect1(2.0, 0.0, 0.0, 0.0);
    RectF paintRect2(1.0, 1.0, 1.0, 1.0);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    pipeline->themeManager_ = theme;
    auto ret = pattern->CreateTextDragInfo();
    EXPECT_NE(ret.firstHandle, paintRect1);
    EXPECT_NE(ret.secondHandle, paintRect2);

    auto manager1 = pattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = paintRect1;

    SelectHandleInfo secondHandle;
    secondHandle.paintRect = paintRect2;
    shareOverlayInfo->firstHandle = firstHandle;
    shareOverlayInfo->secondHandle = secondHandle;
    manager1->shareOverlayInfo_ = shareOverlayInfo;
    manager1->shareOverlayInfo_->firstHandle.isShow = true;
    manager1->shareOverlayInfo_->secondHandle.isShow = true;
    ret = pattern->CreateTextDragInfo();
    EXPECT_EQ(ret.firstHandle, paintRect1);
    EXPECT_EQ(ret.secondHandle, paintRect2);

    manager1->shareOverlayInfo_ = shareOverlayInfo;
    manager1->shareOverlayInfo_->firstHandle.isShow = false;
    manager1->shareOverlayInfo_->secondHandle.isShow = false;
    ret = pattern->CreateTextDragInfo();
    EXPECT_NE(ret.firstHandle, paintRect1);
    EXPECT_NE(ret.secondHandle, paintRect2);
}

/**
 * @tc.name: GetUrlSpanColor001
 * @tc.desc: test GetUrlSpanColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetUrlSpanColor001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    pattern->AttachToFrameNode(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    RefPtr<MockTextBase> mockBase = AIWriteAdapter::MakeRefPtr<MockTextBase>();
    WeakPtr<MockTextBase> textBase = mockBase;

    pattern->selectOverlay_ = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_->ProcessOverlay({ .animation = false });
    pipeline->themeManager_ = theme;
    auto eventHub = pattern->GetHost()->GetEventHub<EventHub>();
    eventHub->enabled_ = true;
    Color ret = pattern->GetUrlSpanColor();
    EXPECT_EQ(ret, pipeline->GetTheme<TextTheme>()->GetUrlDefaultColor());

    eventHub->enabled_ = false;
    ret = pattern->GetUrlSpanColor();
    EXPECT_EQ(ret, pipeline->GetTheme<TextTheme>()->GetUrlDisabledColor());
}

/**
 * @tc.name: ResumeSymbolAnimation001
 * @tc.desc: test ResumeSymbolAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ResumeSymbolAnimation001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 1, pattern);
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->SetIsLoopAnimation(true);
    pattern->ResumeSymbolAnimation();
    EXPECT_TRUE(pattern->GetLayoutProperty<TextLayoutProperty>()->
        GetSymbolEffectOptionsValue(SymbolEffectOptions()).GetIsTxtActive());
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: test OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnThemeScopeUpdate001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    int32_t themeScopeId = 0;
    bool result = pattern->OnThemeScopeUpdate(themeScopeId);
    EXPECT_FALSE(result);

    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateTextColor(Color::RED);
    result = pattern->OnThemeScopeUpdate(themeScopeId);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetOriginCaretPosition001
 * @tc.desc: test GetOriginCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetOriginCaretPosition001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    OffsetF offset(0, 0);
    pattern->ResetOriginCaretPosition();
    bool result = pattern->GetOriginCaretPosition(offset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ProcessBoundRectByTextMarquee001
 * @tc.desc: test ProcessBoundRectByTextMarquee
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ProcessBoundRectByTextMarquee001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    RectF rect = RectF(10, 0, 0, 0);
    pattern->ProcessBoundRectByTextMarquee(rect);
    EXPECT_EQ(rect.Width(), -10);

    RectF testRect = RectF(10, 0, 0, 0);
    frameNode->GetGeometryNode()->SetContentSize({ 10, 10 });
    pattern->ProcessBoundRectByTextMarquee(testRect);
    EXPECT_EQ(testRect.Width(), 0);
}

/**
 * @tc.name: CreateModifier001
 * @tc.desc: test CreateModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, CreateModifier001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetIsCustomFont(true);
    pattern->CreateModifier();
    EXPECT_TRUE(pattern->contentMod_->GetIsCustomFont());
}

/**
 * @tc.name: OnHandleAreaChanged001
 * @tc.desc: test OnHandleAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnHandleAreaChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parentGlobalOffset_ is default vaule { 0, 0 } and call OnHandleAreaChanged.
     * @tc.expect: pattern->GetParentGlobalOffset() is equal to pattern->parentGlobalOffset_.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    pattern->ShowSelectOverlay();
    pattern->OnHandleAreaChanged();
    EXPECT_EQ(pattern->GetParentGlobalOffset(), pattern->parentGlobalOffset_);

    /**
     * @tc.steps: step2. parentGlobalOffset_ is { 1, 1 } and call OnHandleAreaChanged.
     * @tc.expect: pattern->GetParentGlobalOffset() is equal to pattern->parentGlobalOffset_.
     */
    pattern->parentGlobalOffset_ = { 1, 1 };
    pattern->OnHandleAreaChanged();
    EXPECT_EQ(pattern->GetParentGlobalOffset(), pattern->parentGlobalOffset_);
}

/**
 * @tc.name: SetTextDetectEnable001
 * @tc.desc: test SetTextDetectEnable
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetTextDetectEnable001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    bool enable = false;
    pattern->SetTextDetectEnable(enable);
    EXPECT_FALSE(pattern->textDetectEnable_);

    pattern->textDetectEnable_ = true;
    pattern->SetTextDetectEnable(enable);
    EXPECT_FALSE(pattern->textDetectEnable_);
}

/**
 * @tc.name: FireOnMarqueeStateChange001
 * @tc.desc: test FireOnMarqueeStateChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, FireOnMarqueeStateChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    TextMarqueeState state = TextMarqueeState::FINISH;
    pattern->isMarqueeRunning_ = true;
    pattern->FireOnMarqueeStateChange(state);
    EXPECT_FALSE(pattern->isMarqueeRunning_);
}

/**
 * @tc.name: HandleSelectionChange001
 * @tc.desc: test HandleSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSelectionChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->unicode = 1;
    pattern->spans_.push_back(spanItem);

    int32_t start = 1;
    int32_t end = 1;
    pattern->HandleSelectionChange(start, end);
    EXPECT_EQ(pattern->textSelector_.GetStart(), start);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), end);
}

/**
 * @tc.name: GetBuilderResultObject001
 * @tc.desc: test GetBuilderResultObject
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetBuilderResultObject001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    int32_t index = -1;
    int32_t start = 0;
    int32_t end = 0;
    ResultObject resultObject;
    ResultObject result = pattern->GetBuilderResultObject(frameNode, index, start, end);
    EXPECT_EQ(result.spanPosition.spanIndex, resultObject.spanPosition.spanIndex);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.push_back(spanItem);
    pattern->spans_.push_back(spanItem);
    index = 1;
    start = -100;
    end = -100;
    result = pattern->GetBuilderResultObject(frameNode, index, start, end);
    EXPECT_EQ(result.spanPosition.spanIndex, resultObject.spanPosition.spanIndex);

    start = 100;
    result = pattern->GetBuilderResultObject(frameNode, index, start, end);
    EXPECT_EQ(result.spanPosition.spanIndex, resultObject.spanPosition.spanIndex);
}

/**
 * @tc.name: ProcessMarqueeVisibleAreaCallback001
 * @tc.desc: test TextPattern ProcessMarqueeVisibleAreaCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ProcessMarqueeVisibleAreaCallback001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);

    /**
     * @tc.steps: visible is 0, ratio is 0, raceAnimation_ is null.
     * @tc.expected: marqueeState_ is default value MarqueeState::IDLE.
     */
    RefPtr<TextContentModifier> contentMod =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    pattern->contentMod_ = contentMod;
    EXPECT_NE(pattern->contentMod_, nullptr);
    pattern->ProcessMarqueeVisibleAreaCallback();
    EXPECT_EQ(pattern->contentMod_->marqueeState_, MarqueeState::IDLE);
}

/**
 * @tc.name: AddChildSpanItem001
 * @tc.desc: test AddChildSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, AddChildSpanItem001, TestSize.Level1)
{
    /**
     * @tc.steps: set isOverlayNode_ to true and call AddChildSpanItem.
     * @tc.expected: spans_ is null.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->SetIsOverlayNode(true);
    pattern->AddChildSpanItem(frameNode);
    EXPECT_EQ(pattern->spans_.size(), 0);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: colorModeChange_ is default value false and call OnColorConfigurationUpdate.
     * @tc.expected: colorModeChange_ is true.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(pattern->magnifierController_->colorModeChange_);
}

/**
 * @tc.name: RecordOriginCaretPosition001
 * @tc.desc: test RecordOriginCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, RecordOriginCaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: offset is negative value and call RecordOriginCaretPosition.
     * @tc.expected: result is false.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    OffsetF offset(-1, -1);
    bool result = pattern->RecordOriginCaretPosition(offset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetResponseRegion001
 * @tc.desc: test SetResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetResponseRegion001, TestSize.Level1)
{
    /**
     * @tc.steps: set isUserSetResponseRegion_ to true and call SetResponseRegion.
     * @tc.expected: isUserSetResponseRegion_ is true and SetResponseRegion function return.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    SizeF frameSize(0, 0);
    SizeF boundsSize(0, 0);
    pattern->SetIsUserSetResponseRegion(true);
    pattern->SetResponseRegion(frameSize, boundsSize);
    EXPECT_TRUE(pattern->isUserSetResponseRegion_);
}

/**
 * @tc.name: GetStartAndEnd001
 * @tc.desc: test TextPattern GetStartAndEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetStartAndEnd001, TestSize.Level1)
{
    RefPtr<SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    int32_t StartIndex = 0;
    int32_t EndIndex = 3;
    auto urlSpan = AceType::MakeRefPtr<UrlSpan>("test", StartIndex, EndIndex);
    urlSpan->AddUrlStyle(spanItem1);
    auto [frameNode, pattern] = Init();
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"test");
    pattern->styledString_->text_ = u"testText";
    pattern->styledString_->AddSpan(urlSpan);

    int32_t start = 0;
    auto ret = pattern->GetStartAndEnd(start, spanItem1);
    EXPECT_EQ(ret.first, StartIndex);
    EXPECT_EQ(ret.second, EndIndex);

    start = -1;
    ret = pattern->GetStartAndEnd(start, spanItem1);
    EXPECT_EQ(ret.first, 0);
    EXPECT_EQ(ret.second, 0);

    start = 10;
    ret = pattern->GetStartAndEnd(start, spanItem1);
    EXPECT_EQ(ret.first, 0);
    EXPECT_EQ(ret.second, 0);
}

/**
 * @tc.name: EncodeTlvSpanItems002
 * @tc.desc: test TextPattern EncodeTlvSpanItems
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, EncodeTlvSpanItems002, TestSize.Level1)
{
    int32_t cursor = 1;
    auto [frameNode, pattern] = Init();
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->spanItemType = SpanItemType::SYMBOL;
    int32_t textSelectorLength = pattern->textSelector_.GetTextEnd() - pattern->textSelector_.GetTextStart();
    
    std::string pasteData;
    std::vector<uint8_t> buff;

    spanItem->position = pattern->textSelector_.GetTextEnd() + 1;
    spanItem->length = textSelectorLength + 2;
    pattern->spans_.push_back(spanItem);
    pattern->EncodeTlvSpanItems(pasteData, buff);
    int32_t size = TLVUtil::ReadInt32(buff, cursor);
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: BeforeSyncGeometryProperties002
 * @tc.desc: test TextPattern BeforeSyncGeometryProperties
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, BeforeSyncGeometryProperties002, TestSize.Level1)
{
    DirtySwapConfig config;
    int32_t test = 1;
    auto [frameNode, pattern] = Init();
    std::function<void()> callback = [&]() {
        test++;
        return;
    };
    pattern->afterLayoutCallback_ = callback;
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(test, 2);
}

/**
 * @tc.name: HandleKeyEvent001
 * @tc.desc:  test DeleteRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initialize textModelNG and textSelector_.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step3. test the enter key is or not legal.
     * @tc.expect: the key is legal result is true.
     */
    KeyEvent event;
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_A);
    event.code = KeyCode::KEY_A;
    event.action = KeyAction::DOWN;
    EXPECT_TRUE(textPattern->HandleKeyEvent(event));
}

/**
 * @tc.name: HandleSelectionUp001
 * @tc.desc:  test DeleteRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSelectionUp001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initialize textModelNG and textSelector_.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step3.set the line count is 1.
     * @tc.expect: the key is legal result is true.
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    textPattern->HandleSelectionUp();
    EXPECT_EQ(textPattern->pManager_->GetLineCount(), 1);
}

/**
 * @tc.name: HandleSelectionDown001
 * @tc.desc:  test DeleteRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSelectionDown001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initialize textModelNG and textSelector_.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step3.set the line count is 1.
     * @tc.expect: the key is legal result is true.
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    textPattern->HandleSelectionDown();
    EXPECT_EQ(textPattern->pManager_->GetLineCount(), 1);
}

/**
 * @tc.name: SetTextSelectableMode001
 * @tc.desc: test DeleteRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetTextSelectableMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2.Set the selectable mode to SELECTABLE_FOCUSABLE.
     * @tc.expected: The focusable value of focusHub is true.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    TextSelectableMode value = TextSelectableMode::SELECTABLE_FOCUSABLE;
    textPattern->SetTextSelectableMode(value);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    EXPECT_TRUE(focusHub->focusable_);
}

/**
 * @tc.name: GetTextHeight001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetTextHeight001, TestSize.Level1)
{
   /**
     * @tc.steps: step1. Create a textFrameNode and  textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    ASSERT_NE(textPattern->pManager_, nullptr);

    auto layoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set GetLineCount return value of 1.
     */
    auto paragraph1 = MockParagraph::GetOrCreateMockParagraph();
    auto paragraph2 = MockParagraph::GetOrCreateMockParagraph();
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph1, .start = 0, .end = 2 });
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph2, .start = 2, .end = 4 });
    EXPECT_CALL(*paragraph1, GetLineCount()).WillRepeatedly(Return(1));
    EXPECT_CALL(*paragraph2, GetLineCount()).WillRepeatedly(Return(1));
    
    /**
     * @tc.steps: step3. UpdateMaxLines of lines in the layout property to 3
     * @tc.expected: The result of GetTextHeight is 0.0.
     */
    layoutProperty->UpdateMaxLines(3);
    double result = textPattern->GetTextHeight(1, true);
    EXPECT_EQ(result, 0.0);
    result = textPattern->GetTextHeight(3, true);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: HandleSpanLongPressEvent001
 * @tc.desc: test TextPattern HandleSpanLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSpanLongPressEvent001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    GestureEvent info;
    info.localLocation_ = Offset(15.0f, 15.0f);
    pattern->contentRect_ = RectF { 0, 0, 30, 30 };
    RefPtr<SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> spanItem2 = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.push_back(nullptr);
    pattern->spans_.push_back(spanItem1);
    pattern->spans_.push_back(spanItem2);
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();

    /**
     * @tc.steps: Cover the branch when isInRegion is true, spans_.empty() is false and pManager_has value.
     * @tc.expected: spans_ has value, isInRegion is true.
     */
    pattern->HandleSpanLongPressEvent(info);
    auto localLocation = info.GetLocalLocation();
    bool isInRegion = pattern->contentRect_.IsInRegion(
        PointF(static_cast<float>(localLocation.GetX()), static_cast<float>(localLocation.GetY())));
    bool isSpansEmpty = pattern->spans_.empty();
    EXPECT_TRUE(isInRegion);
    EXPECT_FALSE(isSpansEmpty);
}

/**
 * @tc.name: BaseTextSelectOverlayTest001
 * @tc.desc: test CheckSwitchToMode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, BaseTextSelectOverlayTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    pattern->AttachToFrameNode(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    RefPtr<MockTextBase> mockBase = AIWriteAdapter::MakeRefPtr<MockTextBase>();
    WeakPtr<MockTextBase> textBase = mockBase;

    pattern->selectOverlay_ = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_->EnableMenu();
    pattern->selectOverlay_->BaseTextSelectOverlay::CheckSwitchToMode(HandleLevelMode::OVERLAY);
    pattern->selectOverlay_->BaseTextSelectOverlay::NeedsProcessMenuOnWinChange();
    EXPECT_EQ(pattern->selectOverlay_->BaseTextSelectOverlay::GetHandleLocalPaintRect(
        OHOS::Ace::NG::DragHandleIndex::NONE), RectF(0.0f, 0.0f, 0.0f, 0.0f));
}


/**
 * @tc.name: GetAncestorNodeViewPort001
 * @tc.desc: test base_text_select_overlay.cpp GetAncestorNodeViewPort001 function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetAncestorNodeViewPort001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    auto parentPattern1 = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(parentPattern1, nullptr);
    auto parentFrameNode1 = FrameNode::CreateFrameNode("ParentTest", 1, parentPattern1);
    ASSERT_NE(parentFrameNode1, nullptr);
    ASSERT_NE(pattern->GetHost(), nullptr);
    pattern->GetHost()->SetParent(parentFrameNode1);

    textSelectOverlay->hasTransform_ = false;
    EXPECT_EQ(textSelectOverlay->GetAncestorNodeViewPort(), RectF(0.0f, 0.0f, 0.0f, 0.0f));
    textSelectOverlay->hasTransform_ = true;
    EXPECT_EQ(textSelectOverlay->GetAncestorNodeViewPort(), RectF(0.0f, 0.0f, 0.0f, 0.0f));
}

/**
 * @tc.name: LeftMouseRelease.
 * @tc.desc: test clear selection by left mouse.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, LeftMouseRelease, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    auto paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _))
        .WillOnce(Return(5))
        .WillOnce(Return(10))
        .WillOnce(Return(15))
        .WillRepeatedly(Return(0));
    ParagraphManager::ParagraphInfo pInfo = { .paragraph = paragraph };
    pattern->pManager_->AddParagraph(std::move(pInfo));

    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_EQ(pattern->GetTextSelector().GetStart(), 5);
    EXPECT_EQ(pattern->GetTextSelector().GetEnd(), 5);

    mouseInfo.SetAction(MouseAction::MOVE);
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_EQ(pattern->GetTextSelector().GetStart(), 5);
    EXPECT_EQ(pattern->GetTextSelector().GetEnd(), 10);

    mouseInfo.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_EQ(pattern->GetTextSelector().GetStart(), 5);
    EXPECT_EQ(pattern->GetTextSelector().GetEnd(), 15);

    mouseInfo.SetAction(MouseAction::PRESS);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEvent(mouseInfo);
    auto start = pattern->GetTextSelector().GetStart();
    auto end = pattern->GetTextSelector().GetStart();
    EXPECT_EQ(start, -1);
    EXPECT_EQ(end, -1);
}

/**
 * @tc.name: GetVisibleDragViewHandles
 * @tc.desc: test TextSelectOverlay::GetVisibleDragViewHandles
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetVisibleDragViewHandles, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, pattern);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    pattern->selectOverlay_->OnBind(manager);

    RectF firstRect;
    RectF secondRect;
    pattern->selectOverlay_->GetVisibleDragViewHandles(firstRect, secondRect);
    EXPECT_EQ(firstRect, RectF());
    EXPECT_EQ(secondRect, RectF());

    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    manager->shareOverlayInfo_ = std::move(shareOverlayInfo);
    ASSERT_NE(manager->shareOverlayInfo_, nullptr);
    manager->shareOverlayInfo_->firstHandle.paintRect = RectF(10.0f, 10.0f, 5.0f, 10.0f);
    manager->shareOverlayInfo_->secondHandle.paintRect = RectF(20.0f, 20.0f, 5.0f, 10.0f);
    manager->shareOverlayInfo_->handleLevelMode = HandleLevelMode::OVERLAY;
    manager->shareOverlayInfo_->firstHandle.isShow = false;
    manager->shareOverlayInfo_->secondHandle.isShow = false;
    pattern->selectOverlay_->GetVisibleDragViewHandles(firstRect, secondRect);
    EXPECT_EQ(firstRect, RectF());
    EXPECT_EQ(secondRect, RectF());

    manager->shareOverlayInfo_->firstHandle.isShow = true;
    manager->shareOverlayInfo_->secondHandle.isShow = true;
    pattern->selectOverlay_->GetVisibleDragViewHandles(firstRect, secondRect);
    EXPECT_EQ(firstRect, RectF(10.0f, 10.0f, 5.0f, 10.0f));
    EXPECT_EQ(secondRect, RectF(20.0f, 20.0f, 5.0f, 10.0f));
}

/**
 * @tc.name: ApplySelectAreaWithKeyboard
 * @tc.desc: test ApplySelectAreaWithKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ApplySelectAreaWithKeyboard, TestSize.Level1)
{
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<TextPattern> pattern = textNode->GetPattern<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    RefPtr<MockTextBase> mockBase = AIWriteAdapter::MakeRefPtr<MockTextBase>();
    WeakPtr<MockTextBase> textBase = mockBase;
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->AttachToFrameNode(frameNode);

    RectF area = RectF(0.0f, -10, 10, 20);
    pattern->selectOverlay_->ApplySelectAreaWithKeyboard(area);
    EXPECT_EQ(area.Top(), 0.0f);
    EXPECT_EQ(area.Height(), 10.0f);
}
} // namespace OHOS::Ace::NG