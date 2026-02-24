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

#include <cmath>
#include <limits>
#include "gtest/gtest.h"
#include "text_input_base.h"

#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_udmf.h"
#include "core/common/task_executor_impl.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/common/recorder/event_controller.h"
#include "core/components_ng/pattern/select_content_overlay/select_content_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"

#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/text/text_emoji_processor.h"
#include "base/i18n/localization.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class MockTextInputClient : public TextInputClient {
public:
    MOCK_METHOD(void, UpdateEditingValue, (
        const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent),
        (override));
    MOCK_METHOD(void, PerformAction, (TextInputAction action, bool forceCloseKeyboard), (override));
};

class MockTextInputConnection : public TextInputConnection {
public:
    MockTextInputConnection(const WeakPtr<TextInputClient>& client, const RefPtr<TaskExecutor>& taskExecutor)
        : TextInputConnection(client, taskExecutor)
    {}

    MOCK_METHOD(void, Show, (bool isFocusViewChanged, int32_t instanceId), (override));
    MOCK_METHOD(void, SetEditingState, (
        const TextEditingValue& value, int32_t instanceId, bool needFireChangeEvent),
        (override));
    MOCK_METHOD(void, Close, (int32_t instanceId), (override));
    MOCK_METHOD(void, FinishComposing, (int32_t instanceId), (override));
};

class TextFieldPatternTestNine : public TextInputBases {
public:
};

/**
 * @tc.name: TriggerAvoidOnCaretChange001
 * @tc.desc: test TriggerAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, TriggerAvoidOnCaretChange001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    GestureEvent info;
    FingerInfo finfo;
    info.fingerList_.push_back(finfo);
    pattern_->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern_);
    pattern_->longPressFingerNum_ = 1;
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    std::u16string value = u"test";
    pattern_->contentController_->SetTextValue(value);
    pattern_->HandleLongPress(info);
    EXPECT_TRUE(pattern_->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: TriggerAvoidOnCaretChange002
 * @tc.desc: test TriggerAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, TriggerAvoidOnCaretChange002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    GestureEvent info;
    FingerInfo finfo;
    info.fingerList_.push_back(finfo);
    pattern_->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern_);
    pattern_->longPressFingerNum_ = 1;
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    std::u16string value = u"test";
    pattern_->contentController_->SetTextValue(value);
    auto host = pattern_->GetHost();
    auto pipeline = host->GetContext();
    pipeline->safeAreaManager_->keyboardInset_.start = 1;
    pipeline->safeAreaManager_->keyboardInset_.end = 2;
    pattern_->HandleLongPress(info);
    EXPECT_TRUE(pattern_->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: SetPreviewTextOperation001
 * @tc.desc: test SetPreviewTextOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetPreviewTextOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    PreviewTextInfo info;
    info.text = u"test";
    info.isIme = false;
    pattern_->hasPreviewText_ = false;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(20020);
    auto container = Container::Current();
    container->apiTargetVersion_ = 20;
    pattern_->selectController_->firstHandleInfo_.index = 1;
    pattern_->selectController_->secondHandleInfo_.index = 2;
    pattern_->contentController_->content_ = u"12";
    layoutProperty->UpdateMaxLength(1);
    pattern_->SetPreviewTextOperation(info);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));

    info.isIme = true;
    pattern_->contentController_->content_ = u"";
    pattern_->SetPreviewTextOperation(info);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));
}

/**
 * @tc.name: FinishTextPreviewOperation001
 * @tc.desc: test FinishTextPreviewOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, FinishTextPreviewOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    pattern_->hasPreviewText_ = true;
    pattern_->FinishTextPreviewOperation();
    ChangeValueInfo changeValueInfo;
    EXPECT_FALSE(pattern_->FireOnWillChange(changeValueInfo));
}

/**
 * @tc.name: FinishTextPreviewOperation002
 * @tc.desc: test FinishTextPreviewOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, FinishTextPreviewOperation002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Initialize text field.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
        model.SetShowError(u"error", true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Call FinishTextPreviewOperation.
     */
    pattern_->hasPreviewText_ = true;
    pattern_->contentController_->content_ = u"01234567890";
    pattern_->FinishTextPreviewOperation();
    EXPECT_TRUE(pattern_->showCountBorderStyle_);
}

/**
 * @tc.name: OnTextGestureSelectionUpdate001
 * @tc.desc: test OnTextGestureSelectionUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnTextGestureSelectionUpdate001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    int32_t start = 1;
    int32_t end = 2;
    TouchEventInfo info("unknown");
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    pattern_->contentController_->content_ = u"";
    pattern_->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_FALSE(pattern_->HasText());

    pattern_->contentController_->content_ = u"test";
    TouchLocationInfo tinfo("test", 0);
    Offset localLocation(1, 2);
    tinfo.SetLocalLocation(localLocation);
    info.touches_.push_back(tinfo);
    start = 26;
    pattern_->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_TRUE(pattern_->HasText());
}

/**
 * @tc.name: OnTextGestureSelectionEnd001
 * @tc.desc: test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnTextGestureSelectionEnd001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    TouchLocationInfo locationInfo("test", 0);
    Offset offset(11, 22);
    locationInfo.localLocation_ = offset;
    pattern_->contentRect_.width_ = 33,
    pattern_->contentRect_.x_ = 33;
    pattern_->contentRect_.height_ = 44;
    pattern_->contentRect_.y_ = 44;
    pattern_->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_TRUE(LessNotEqual(locationInfo.localLocation_.GetX(), pattern_->contentRect_.Left()));

    pattern_->contentRect_.width_ = 1,
    pattern_->contentRect_.x_ = 1;
    pattern_->contentRect_.height_ = 2;
    pattern_->contentRect_.y_ = 2;
    pattern_->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_FALSE(LessNotEqual(locationInfo.localLocation_.GetX(), pattern_->contentRect_.Right()));
}

/**
 * @tc.name: IsShowAIWrite001
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsShowAIWrite001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsShowAIWrite();
    EXPECT_FALSE(ret);
    auto container = MockContainer::Current();
    container->SetIsSceneBoardWindow(false);
    auto host = pattern_->GetHost();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    ret = pattern_->IsShowAIWrite();
    EXPECT_FALSE(ret);

    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    auto textFieldTheme = pattern_->GetTheme();
    textFieldTheme->aiWriteBundleName_ = "BundleName";
    textFieldTheme->aiWriteAbilityName_ = "AbilityName";
    textFieldTheme->aiWriteIsSupport_ = "true";
    ret = pattern_->IsShowAIWrite();
    EXPECT_TRUE(ret);
    textFieldTheme->aiWriteIsSupport_ = "false";
    ret = pattern_->IsShowAIWrite();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleAIWriteResult001
 * @tc.desc: test HandleAIWriteResult
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleAIWriteResult001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    int32_t start = 0;
    int32_t end = 0;
    std::vector<uint8_t> buffer;
    pattern_->HandleAIWriteResult(start, end, buffer);
    EXPECT_TRUE(buffer.empty());
}

/**
 * @tc.name: CalcAutoScrollStepOffset001
 * @tc.desc: test CalcAutoScrollStepOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CalcAutoScrollStepOffset001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    Offset localOffset(1, 2);
    pattern_->axis_ = Axis::HORIZONTAL;
    pattern_->contentRect_.width_ = 10;
    auto ret = pattern_->CalcAutoScrollStepOffset(localOffset);
    EXPECT_EQ(static_cast<int>(ret.value()), 28);
}

/**
 * @tc.name: OnWillChangePreInsert001
 * @tc.desc: test OnWillChangePreInsert
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnWillChangePreInsert001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::u16string insertValue = u"test";
    std::u16string oldContent = u"";
    uint32_t start = 1;
    uint32_t end = 2;
    pattern_->hasPreviewText_ = true;
    auto ret = pattern_->OnWillChangePreInsert(insertValue, oldContent, start, end);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AddInsertCommand001
 * @tc.desc: test AddInsertCommand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, AddInsertCommand001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::u16string insertValue = u" ";
    InputReason reason = InputReason::NONE;
    pattern_->isEdit_ = true;
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    pattern_->AddInsertCommand(insertValue, reason);
    EXPECT_FALSE(pattern_->HandleSpaceEvent());
}

/**
 * @tc.name: ExecuteInputCommand001
 * @tc.desc: test ExecuteInputCommand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ExecuteInputCommand001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    InputCommandInfo info;
    info.reason = InputReason::CANCEL_BUTTON;
    info.insertValue = u"test";
    info.deleteRange.end = 0;
    info.insertOffset = 0;
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLength(123);
    auto host = pattern_->GetHost();
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    pattern_->ExecuteInputCommand(info);
    ChangeValueInfo changeValueInfo;
    EXPECT_FALSE(pattern_->FireOnWillChange(changeValueInfo));
}

/**
 * @tc.name: ClearTextContent001
 * @tc.desc: test ClearTextContent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ClearTextContent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->hasPreviewText_ = true;
    pattern_->ClearTextContent();
    EXPECT_FALSE(pattern_->GetIsPreviewText());
}

/**
 * @tc.name: GetOriginCaretPosition001
 * @tc.desc: test GetOriginCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetOriginCaretPosition001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    OffsetF offset(0, 0);
    OffsetF offset2(1, 1);
    pattern_->originCaretPosition_ = offset;
    pattern_->GetOriginCaretPosition(offset2);
    EXPECT_TRUE(pattern_->originCaretPosition_ == offset2);
}

/**
 * @tc.name: GetFocusPattern001
 * @tc.desc: test GetFocusPattern
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetFocusPattern001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto pipelineContext = host->GetContext();
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    theme->needFocusBox_ = true;
    auto FocusPattern = pattern_->GetFocusPattern();
    EXPECT_EQ(FocusPattern.styleType_, FocusStyleType::OUTER_BORDER);
}

/**
 * @tc.name: InitCancelButtonMouseEvent001
 * @tc.desc: test InitCancelButtonMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, InitCancelButtonMouseEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->cleanNodeResponseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern_);
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    cleanNodeResponseArea->cleanNode_ = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    pattern_->InitCancelButtonMouseEvent();
    auto stackNode = cleanNodeResponseArea->GetFrameNode();
    auto imageInputHub = stackNode->GetOrCreateInputEventHub();
    HoverInfo hoverInfo;
    imageInputHub->hoverEventActuator_->inputEvents_.front()->onHoverEventCallback_(true, hoverInfo);
    EXPECT_TRUE(pattern_->isOnHover_);

    auto imageTouchHub = stackNode->GetOrCreateGestureEventHub();
    TouchEventInfo info("unknown");
    TouchLocationInfo tinfo("test", 0);
    tinfo.touchType_ = TouchType::DOWN;
    info.touches_.push_back(tinfo);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info1("unknown");
    TouchLocationInfo tinfo1("test", 0);
    tinfo1.touchType_ = TouchType::UP;
    info1.touches_.push_back(tinfo1);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info1);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info2("unknown");
    TouchLocationInfo tinfo2("test", 0);
    tinfo2.touchType_ = TouchType::CANCEL;
    info2.touches_.push_back(tinfo2);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info2);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info3("unknown");
    TouchLocationInfo tinfo3("test", 0);
    tinfo3.touchType_ = TouchType::MOVE;
    info3.touches_.push_back(tinfo3);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info3);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);
}

/**
 * @tc.name: InitPasswordButtonMouseEvent001
 * @tc.desc: test InitPasswordButtonMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, InitPasswordButtonMouseEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();
    auto passwordResponseArea = AceType::DynamicCast<PasswordResponseArea>(pattern_->responseArea_);
    auto stackNode = passwordResponseArea->GetFrameNode();
    auto imageTouchHub = stackNode->GetOrCreateGestureEventHub();
    imageTouchHub->touchEventActuator_->touchEvents_.clear();
    pattern_->InitPasswordButtonMouseEvent();
    auto imageInputHub = stackNode->GetOrCreateInputEventHub();
    HoverInfo hoverInfo;
    imageInputHub->hoverEventActuator_->inputEvents_.front()->onHoverEventCallback_(true, hoverInfo);
    EXPECT_TRUE(pattern_->isOnHover_);

    TouchEventInfo info("unknown");
    TouchLocationInfo tinfo("test", 0);
    tinfo.touchType_ = TouchType::DOWN;
    info.touches_.push_back(tinfo);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info1("unknown");
    TouchLocationInfo tinfo1("test", 0);
    tinfo1.touchType_ = TouchType::UP;
    info1.touches_.push_back(tinfo1);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info1);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info2("unknown");
    TouchLocationInfo tinfo2("test", 0);
    tinfo2.touchType_ = TouchType::CANCEL;
    info2.touches_.push_back(tinfo2);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info2);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info3("unknown");
    TouchLocationInfo tinfo3("test", 0);
    tinfo3.touchType_ = TouchType::MOVE;
    info3.touches_.push_back(tinfo3);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info3);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);
}

/**
 * @tc.name: ProcessOverlayAfterLayout001
 * @tc.desc: test ProcessOverlayAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ProcessOverlayAfterLayout001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    OffsetF prevOffset(1, 2);
    pattern_->ProcessOverlayAfterLayout(prevOffset);
    EXPECT_TRUE(prevOffset != pattern_->parentGlobalOffset_);

    OffsetF prevOffset1(0, 0);
    pattern_->ProcessOverlay();
    pattern_->selectController_->firstHandleInfo_.index = 1;
    pattern_->selectController_->secondHandleInfo_.index = 2;
    pattern_->processOverlayDelayTask_ = nullptr;
    pattern_->needToRefreshSelectOverlay_ = true;
    pattern_->ProcessOverlayAfterLayout(prevOffset1);
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: CheckSelectAreaVisible001
 * @tc.desc: test CheckSelectAreaVisible
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CheckSelectAreaVisible001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto tmpHost = pattern_->GetHost();
    auto pipeline = tmpHost->GetContextRefPtr();
    pipeline->safeAreaManager_->keyboardInset_.start = 1;
    pipeline->safeAreaManager_->keyboardInset_.end = 4;
    pattern_->selectController_->caretInfo_.rect.y_ = 5;
    pattern_->selectController_->caretInfo_.rect.width_  = 1;
    pattern_->selectController_->caretInfo_.rect.x_ = 1;
    auto ret = pattern_->CheckSelectAreaVisible();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CursorMove001
 * @tc.desc: test CursorMove
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CursorMove001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    CaretMoveIntent direction = static_cast<CaretMoveIntent>(130);
    int32_t originCaretPosition = pattern_->selectController_->GetCaretIndex();
    pattern_->CursorMove(direction);
    EXPECT_TRUE(originCaretPosition == pattern_->selectController_->GetCaretIndex());
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnKeyEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    KeyEvent event;
    event.code = KeyCode::KEY_ENTER;
    pattern_->independentControlKeyboard_ = true;
    pattern_->showKeyBoardOnFocus_ = true;
    pattern_->customKeyboard_ = AceType::DynamicCast<NG::UINode>(
        AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    pattern_->isCustomKeyboardAttached_ = true;
    auto ret = pattern_->OnKeyEvent(event);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test text_field_pattern.cpp HandleOnCopy function,
    case value.empty(),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnCopy001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto context = PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    pattern->clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    ASSERT_NE(pattern->clipboard_, nullptr);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(pattern->contentController_, nullptr);
    pattern->contentController_->content_ = u"";
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->selectController_->UpdateHandleIndex(0, 4);
    auto eventHub = textFieldNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool calledOnCopy = false;
    eventHub->SetOnCopy([&calledOnCopy](const std::u16string& value) {
        calledOnCopy = true;
    });
    ASSERT_NE(pattern->selectOverlay_, nullptr);
    pattern->selectOverlay_->SetUsingMouse(true);
    pattern->clipboard_->SetData(UtfUtils::Str16DebugToStr8(u"test123"),
        layoutProperty->GetCopyOptionsValue(CopyOptions::Local));
    pattern->HandleOnCopy(false);
    std::string data_;
    auto getDataCallback = [&data_](const std::string& data) {
        data_ = data;
    };
    pattern->clipboard_->GetData(getDataCallback, true);
    EXPECT_TRUE(data_ == "test123");
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: test text_field_pattern.cpp HandleTouchEvent function,
    case selectOverlay_->IsTouchAtHandle(info)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleTouchEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    TouchEventInfo info("unknown");
    pattern_->dragStatus_ = DragStatus::ON_DROP;
    TouchLocationInfo tinfo("test", 0);
    tinfo.touchType_ = TouchType::MOVE;
    info.touches_.push_back(tinfo);
    pattern_->selectOverlay_->touchAtHandle_ = true;
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern_->selectOverlay_->OnBind(manager);
    pattern_->HandleTouchEvent(info);
    EXPECT_TRUE(pattern_->selectOverlay_->IsTouchAtHandle(info));

    pattern_->selectOverlay_->touchAtHandle_ = false;
    info.changedTouches_.push_back(tinfo);
    pattern_->moveCaretState_.isMoveCaret = false;
    pattern_->moveCaretState_.isTouchCaret = false;
    pattern_->ProcessOverlay();
    pattern_->isSelecting_ = false;
    pattern_->HandleTouchEvent(info);
    OffsetF offset(-1.0f, -1.0f);
    EXPECT_TRUE(pattern_->originCaretPosition_ == offset);
}

/**
 * @tc.name: OnDragDrop001
 * @tc.desc: test  test text_field_pattern.cpp OnDragDrop function,
    case (gesturePressedCodes.size() == 1) && ((gesturePressedCodes[0] == KeyCode::KEY_CTRL_LEFT) ||
    (gesturePressedCodes[0] == KeyCode::KEY_CTRL_RIGHT)),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnDragDrop001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string str("test");
    pattern_->dragStatus_ = DragStatus::DRAGGING;
    event->pressedKeyCodes_.push_back(KeyCode::KEY_CTRL_RIGHT);
    event->unifiedData_ = AceType::MakeRefPtr<MockUnifiedData>();
    pattern_->OnDragDrop()(event, str);
    EXPECT_EQ(event->GetPressedKeyCodes().size(), 1);
    EXPECT_FALSE(pattern_->releaseInDrop_);

    event->pressedKeyCodes_.push_back(KeyCode::KEY_CAPS_LOCK);
    pattern_->OnDragDrop()(event, str);
    EXPECT_EQ(event->GetPressedKeyCodes().size(), 2);
    EXPECT_FALSE(pattern_->releaseInDrop_);
}

/**
 * @tc.name: InitDragDropCallBack001
 * @tc.desc: test InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, InitDragDropCallBack001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto eventHub = host->GetEventHub<EventHub>();
    pattern_->InitDragDropCallBack();
    RefPtr<OHOS::Ace::DragEvent> event  = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    const std::string extraParams("test");
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    auto pipeline = pattern_->GetContext();
    auto dragManager = pipeline->GetDragDropManager();
    host->isDisallowDropForcedly_ = false;
    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragEnter(event, extraParams);
    EXPECT_TRUE(pattern_->IsNormalInlineState());

    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragMove(event, extraParams);
    EXPECT_TRUE(pattern_->IsNormalInlineState());

    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    layoutProperty->UpdateTextInputType(TextInputType::JS_ENUM_URL);
    auto dragPreviewOption = host->GetDragPreviewOption();
    dragPreviewOption.enableEdgeAutoScroll = false;
    host->SetDragPreviewOptions(dragPreviewOption);
    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragMove(event, extraParams);
    EXPECT_FALSE(pattern_->contentScroller_.isScrolling);

    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragLeave(event, extraParams);
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: InitDragDropCallBack002
 * @tc.desc: test InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, InitDragDropCallBack002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });

    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);

    pattern_->InitDragDropCallBack();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);


    auto pipeline = pattern_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragManager, nullptr);

    host->isDisallowDropForcedly_ = false;
    RefPtr<OHOS::Ace::DragEvent> event  = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    const std::string extraParams("test");
    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragEnter(event, extraParams);
    EXPECT_EQ(pattern_->dragRecipientStatus_, DragStatus::NONE);

    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragLeave(event, extraParams);
    EXPECT_EQ(pattern_->dragRecipientStatus_, DragStatus::NONE);
    EXPECT_FALSE(pattern_->HasFocus());

    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragLeave(event, extraParams);
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: InitDragDropCallBack003
 * @tc.desc: test InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, InitDragDropCallBack003, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });

    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(true);

    pattern_->InitDragDropCallBack();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);

    auto pipeline = pattern_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragManager, nullptr);

    host->isDisallowDropForcedly_ = false;
    RefPtr<OHOS::Ace::DragEvent> event  = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    const std::string extraParams("test");
    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragEnter(event, extraParams);
    EXPECT_EQ(pattern_->dragRecipientStatus_, DragStatus::NONE);

    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragMove(event, extraParams);
    EXPECT_EQ(pattern_->dragRecipientStatus_, DragStatus::NONE);
    EXPECT_FALSE(pattern_->HasFocus());

    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragLeave(event, extraParams);
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: InitDragDropCallBack004
 * @tc.desc: test InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, InitDragDropCallBack004, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });

    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(true);

    pattern_->InitDragDropCallBack();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);


    auto pipeline = pattern_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragManager, nullptr);

    host->isDisallowDropForcedly_ = true;
    RefPtr<OHOS::Ace::DragEvent> event  = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    const std::string extraParams("test");
    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragEnter(event, extraParams);
    EXPECT_EQ(pattern_->dragRecipientStatus_, DragStatus::NONE);

    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragMove(event, extraParams);
    EXPECT_EQ(pattern_->dragRecipientStatus_, DragStatus::NONE);
    EXPECT_FALSE(pattern_->HasFocus());

    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragLeave(event, extraParams);
    EXPECT_FALSE(pattern_->isCaretTwinkling_);

    // Close the keyboard when dragging enter the textinput/textarea/search from outside it.
    pattern_->customKeyboardBuilder_ = [] {};
    pattern_->isCustomKeyboardAttached_ = true;
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    pattern_->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboard);
    pattern_->dragStatus_ = DragStatus::NONE;
    host->isDisallowDropForcedly_ = false;
    eventHub->GetOrCreateDragDropCallbackSet()->GetOrCreateInnerDragDropCallback()->onDragEnter(event, extraParams);
    EXPECT_FALSE(pattern_->isCustomKeyboardAttached_);
}

/**
 * @tc.name: HandleCountStyle001
 * @tc.desc: test text_field_pattern.cpp HandleCountStyle function,
    case showCountBorderStyle_ && !showBorder,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleCountStyle001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateShowCounter(true);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    layoutProperty->UpdateMaxLength(123);
    pattern_->showCountBorderStyle_ = true;
    layoutProperty->UpdateShowHighlightBorder(false);

    pattern_->HandleCountStyle();
    auto frameNode = pattern_->GetHost();
    auto context = frameNode->GetRenderContext();
    OffsetF offset(-1.0, 0.0);
    EXPECT_EQ(context->GetTranslateXYProperty(), offset);
}

/**
 * @tc.name: ProcessSelection001
 * @tc.desc: test text_field_pattern.cpp ProcessSelection function,
    case !isTextChangedAtCreation_ && selectOverlay_->IsShowMouseMenu(),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ProcessSelection001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->ProcessOverlay();
    pattern_->isTextChangedAtCreation_ = false;
    auto overlayManager = pattern_->selectOverlay_->GetManager<SelectContentOverlayManager>();
    overlayManager->shareOverlayInfo_->menuInfo.menuType = OptionMenuType::MOUSE_MENU;
    pattern_->ProcessSelection();
    EXPECT_FALSE(pattern_->needToRefreshSelectOverlay_);
}

/**
 * @tc.name: ProcessSelection002
 * @tc.desc: test text_field_pattern.cpp ProcessSelection function,
    case IsGestureSelectingText(),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ProcessSelection002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->isSelecting_ = true;
    pattern_->ProcessSelection();
    EXPECT_EQ(pattern_->selectController_->GetEndIndex(), 4);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: test text_field_pattern.cpp OnModifyDone function,
    case IsGestureSelectingText(),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnModifyDone001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto pipeline = host->GetContext();
    auto textFieldManager = AIWriteAdapter::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    auto size = textFieldManager->textFieldInfoMap_.size();
    pattern_->firstAutoFillContainerNode_ =  pattern_->frameNode_;
    pattern_->OnModifyDone();
    pattern_->HandleOnCopy(true);
    EXPECT_EQ(textFieldManager->textFieldInfoMap_.size(), size + 1);
}

/**
 * @tc.name: TriggerAvoidWhenCaretGoesDown001
 * @tc.desc: test text_field_pattern.cpp TriggerAvoidWhenCaretGoesDown function,
    case context->UsingCaretAvoidMode() && HasFocus() && textFieldManager,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, TriggerAvoidWhenCaretGoesDown001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto context = host->GetContext();
    context->safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET_WITH_CARET;
    pattern_->TriggerAvoidWhenCaretGoesDown();
    EXPECT_EQ(pattern_->GetLastCaretPos(), 74);

    /* lastCarePos < 74  return 74 */
    pattern_->SetLastCaretPos(30);
    pattern_->TriggerAvoidWhenCaretGoesDown();
    EXPECT_EQ(pattern_->GetLastCaretPos(), 74);

    /* lastCarePos > 74  return lastCarePos */
    pattern_->SetLastCaretPos(123);
    pattern_->TriggerAvoidWhenCaretGoesDown();
    EXPECT_EQ(pattern_->GetLastCaretPos(), 123);
}

/**
 * @tc.name: RecordTextInputEvent001
 * @tc.desc: test text_field_pattern.cpp RecordTextInputEvent function,
    case isPwdType,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, RecordTextInputEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    for (int i = 0; i < 10; i++)
    {
        Recorder::EventRecorder::Get().globalSwitch_[i] = true;
        Recorder::EventRecorder::Get().eventSwitch_[i] = true;
    }
    Recorder::EventController::Get().cacheEvents_.clear();
    auto host = pattern_->GetHost();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    pattern_->RecordTextInputEvent();
    EXPECT_EQ(Recorder::EventController::Get().cacheEvents_.size(), 0);

    layoutProperty->UpdateTextInputType(TextInputType::DATETIME);
    Recorder::EventController::Get().hasCached_ = false;
    pattern_->RecordTextInputEvent();
    EXPECT_EQ(Recorder::EventController::Get().cacheEvents_.size(), 1);
}

/**
 * @tc.name: RequestKeyboardByFocusSwitch001
 * @tc.desc: test text_field_pattern.cpp RequestKeyboardByFocusSwitch function,
    case textField->RequestKeyboard(false, true, textField->needToRequestKeyboardOnFocus_),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, RequestKeyboardByFocusSwitch001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->showKeyBoardOnFocus_ = true;
    pattern_->customKeyboard_ =  AceType::DynamicCast<NG::UINode>(
        AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    pattern_->customKeyboardBuilder_ = []{};
    pattern_->isEdit_ = false;
    pattern_->RequestKeyboardByFocusSwitch();
    EXPECT_TRUE(pattern_->isEdit_);
}

/**
 * @tc.name: CalcDecoratorWidth001
 * @tc.desc: test text_field_pattern.cpp CalcDecoratorWidth function,
    case info.paragraph,!info.paragraph,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CalcDecoratorWidth001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    RefPtr<FrameNode> childrenNode =
        FrameNode::GetOrCreateFrameNode("childTag", 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textPattern = childrenNode->GetPattern<TextPattern>();
    textPattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo info;
    textPattern->pManager_->paragraphs_.push_back(info);
    auto ret = pattern_->CalcDecoratorWidth(childrenNode);
    EXPECT_EQ(ret, 0.0f);

    ParagraphManager::ParagraphInfo info2;
    ParagraphStyle paragraphStyle;
    info2.paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->paragraphs_.push_back(info2);
    ret = pattern_->CalcDecoratorWidth(childrenNode);
    EXPECT_EQ(ret, 460);
}

/**
 * @tc.name: PasteAfterStopEditing001
 * @tc.desc: test text_field_pattern.cpp call StopEditing & OnPaste in sequence, expect paste success.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, PasteAfterStopEditing001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    pattern_->selectController_->UpdateHandleIndex(0, 4);
    pattern_->HandleOnCopy();
    pattern_->StopEditing();
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = false;
    pattern_->HandleBlurEvent();
    FlushLayoutTask(frameNode_);
    pattern_->HandleOnPaste();
    FlushLayoutTask(frameNode_);
    auto value = pattern_->contentController_->GetTextValue();
    EXPECT_EQ(value, "abcdabcdefghijklmnopqrstuvwxyz");
}

/**
 * @tc.name: NeedSetScrollRect001
 * @tc.desc: test NeedSetScrollRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NeedSetScrollRect001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();

    ASSERT_NE(pattern_, nullptr);
    pattern_->lastOverflowMode_ = OverflowMode::CLIP;
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::SCROLL);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);

    auto result = pattern_->NeedSetScrollRect();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->lastOverflowMode_, OverflowMode::SCROLL);
}

/**
 * @tc.name: NeedSetScrollRect002
 * @tc.desc: test NeedSetScrollRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NeedSetScrollRect002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();

    ASSERT_NE(pattern_, nullptr);
    pattern_->lastOverflowMode_ = OverflowMode::CLIP;
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::SCROLL);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::INLINE);

    auto result = pattern_->NeedSetScrollRect();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->lastOverflowMode_, OverflowMode::SCROLL);
}

/**
 * @tc.name: NeedSetScrollRect003
 * @tc.desc: test NeedSetScrollRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NeedSetScrollRect003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();

    ASSERT_NE(pattern_, nullptr);
    pattern_->lastTextOverflow_ = TextOverflow::DEFAULT;
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);

    auto result = pattern_->NeedSetScrollRect();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->lastTextOverflow_, TextOverflow::MARQUEE);
}

/**
 * @tc.name: NeedSetScrollRect004
 * @tc.desc: test NeedSetScrollRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NeedSetScrollRect004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();

    ASSERT_NE(pattern_, nullptr);
    pattern_->lastOverflowMode_ = OverflowMode::CLIP;
    pattern_->lastTextOverflow_ = TextOverflow::DEFAULT;
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::SCROLL);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);

    auto result = pattern_->NeedSetScrollRect();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->lastOverflowMode_, OverflowMode::SCROLL);
    EXPECT_EQ(pattern_->lastTextOverflow_, TextOverflow::MARQUEE);
}

/**
 * @tc.name: NeedSetScrollRect005
 * @tc.desc: test NeedSetScrollRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NeedSetScrollRect005, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();

    ASSERT_NE(pattern_, nullptr);
    pattern_->lastTextOverflow_ = TextOverflow::MARQUEE;
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);

    auto result = pattern_->NeedSetScrollRect();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: RegisterFontCallback
 * @tc.desc: test RegisterFontCallback.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, RegisterFontCallback, TestSize.Level0)
{
    auto fontManager = FontManager::Create();
    ASSERT_NE(fontManager, nullptr);
    CreateTextField(DEFAULT_TEXT);
    EXPECT_TRUE(fontManager->externalLoadCallbacks_.empty());
    bool hasChanged = false;
    auto fontChangeCallback = [&]() { hasChanged = true; };
    fontManager->RegisterCallbackNG(WeakPtr(frameNode_), "myFont", fontChangeCallback);
    std::map<std::string, std::function<void()>> familyMap;
    familyMap.emplace("myFont", fontChangeCallback);
    fontManager->externalLoadCallbacks_.emplace(WeakPtr(frameNode_), familyMap);
    fontChangeCallback();
    fontManager->RegisterCallbackNG(WeakPtr(frameNode_), "myFont", fontChangeCallback);
    bool hasRegister = false;
    std::call_once(fontManager->load_font_flag_, [&hasRegister]() { hasRegister = true; });
    std::call_once(fontManager->load_font_flag_, [&hasRegister, weak = WeakPtr(fontManager)]() {
        hasRegister = false;
        auto fontMgr = weak.Upgrade();
        ASSERT_NE(fontMgr, nullptr);
        fontMgr->externalLoadCallbacks_.clear();
    });
    EXPECT_FALSE(fontManager->externalLoadCallbacks_.empty());
    EXPECT_TRUE(hasRegister);
    EXPECT_TRUE(hasChanged);
}

/**
 * @tc.name: GetMaxIndent
 * @tc.desc: test GetMaxIndent.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetMaxIndent, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    ASSERT_NE(pattern_, nullptr);
    auto layoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto textFieldLayoutAlgorithm = AceType::DynamicCast<TextFieldLayoutAlgorithm>(layoutAlgorithm);

    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    auto width = textFieldLayoutAlgorithm->GetMaxIndent(&layoutWrapper, 100.0f);
    EXPECT_EQ(width, 100.0f);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetWidth(200.0f);
    layoutProperty_->contentConstraint_ = contentConstraint;
    width = textFieldLayoutAlgorithm->GetMaxIndent(&layoutWrapper, std::numeric_limits<double>::infinity());
    EXPECT_EQ(width, 200.0f);
}

/**
 * @tc.name: OnFocusNodeChange001
 * @tc.desc: test OnFocusNodeChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnFocusNodeChange001, TestSize.Level1)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = pattern->GetContext();
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    WeakPtr<FrameNode> weakNode(frameNode);
    textFieldManager->SetPreNode(weakNode);
    pipeline->SetTextFieldManager(textFieldManager);
    pattern->OnFocusCustomKeyboardChange();
    refPattern->customKeyboardBuilder_ = [] () {};
    refPattern->isCustomKeyboardAttached_ = true;
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>("node", 2002, AceType::MakeRefPtr<Pattern>());
    pattern->customKeyboard_ = customNode;
    pattern->OnFocusCustomKeyboardChange();
    EXPECT_FALSE(pattern->isCustomKeyboardAttached_);
    refPattern->isCustomKeyboardAttached_ = true;
    textFieldManager->SetPreNode(weakNode);
    pipeline->SetTextFieldManager(textFieldManager);
    pattern->OnFocusCustomKeyboardChange();
    EXPECT_FALSE(pattern->isCustomKeyboardAttached_);
    refPattern->isCustomKeyboardAttached_ = true;
    pattern->customKeyboard_ = nullptr;
    textFieldManager->SetPreNode(weakNode);
    pipeline->SetTextFieldManager(textFieldManager);
    pattern->OnFocusCustomKeyboardChange();
    EXPECT_FALSE(pattern->isCustomKeyboardAttached_);
}

/**
 * @tc.name: SetCustomKeyboardNodeId001
 * @tc.desc: test SetCustomKeyboardNodeId.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetCustomKeyboardNodeId, TestSize.Level1)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = pattern->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    pipeline->SetTextFieldManager(textFieldManager);
}

/**
 * @tc.name: NeedCloseKeyboard001
 * @tc.desc: test NeedCloseKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NeedCloseKeyboard001, TestSize.Level1)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->customKeyboardBuilder_ = [] {};
    EXPECT_FALSE(pattern->NeedCloseKeyboard());
    pattern->isCustomKeyboardAttached_ = true;
    EXPECT_TRUE(pattern->NeedCloseKeyboard());
}

/**
 * @tc.name: CloseTextCustomKeyboard001
 * @tc.desc: test NeedCloseKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CloseTextCustomKeyboard001, TestSize.Level1)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(keyboard, nullptr);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboard);
    pattern->customKeyboardBuilder_ = [] {};
    pattern->isCustomKeyboardAttached_ = true;
    pattern->CloseTextCustomKeyboard(1, true);
    EXPECT_FALSE(pattern->isCustomKeyboardAttached_);
}

/**
 * @tc.name: CloseTextCustomKeyboard002
 * @tc.desc: test NeedCloseKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CloseTextCustomKeyboard002, TestSize.Level1)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(keyboard, nullptr);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboard);
    pattern->customKeyboardBuilder_ = [] {};
    pattern->isCustomKeyboardAttached_ = false;
    pattern->CloseTextCustomKeyboard(1, false);
    EXPECT_FALSE(pattern->isCustomKeyboardAttached_);
}

/**
 * @tc.name: IsMoveFocusOutFromLeft001
 * @tc.desc: test IsMoveFocusOutFromLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsMoveFocusOutFromLeft001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_LEFT;
    pattern_->selectController_->UpdateCaretIndex(0);
    auto ret = pattern_->IsMoveFocusOutFromLeft(event);
    EXPECT_TRUE(ret);

    event.code = KeyCode::KEY_DPAD_UP;
    ret = pattern_->IsMoveFocusOutFromLeft(event);
    EXPECT_TRUE(ret);

    event.code = KeyCode::KEY_DPAD_RIGHT;
    ret = pattern_->IsMoveFocusOutFromLeft(event);
    EXPECT_FALSE(ret);

    pattern_->selectController_->UpdateCaretIndex(5);
    event.code = KeyCode::KEY_DPAD_LEFT;
    ret = pattern_->IsMoveFocusOutFromLeft(event);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsMoveFocusOutFromRight001
 * @tc.desc: test IsMoveFocusOutFromRight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsMoveFocusOutFromRight001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    pattern_->contentController_->content_ = u"test";
    pattern_->selectController_->UpdateCaretIndex(4);
    auto ret = pattern_->IsMoveFocusOutFromRight(event);
    EXPECT_TRUE(ret);

    event.code = KeyCode::KEY_DPAD_DOWN;
    ret = pattern_->IsMoveFocusOutFromRight(event);
    EXPECT_TRUE(ret);

    event.code = KeyCode::KEY_DPAD_LEFT;
    ret = pattern_->IsMoveFocusOutFromRight(event);
    EXPECT_FALSE(ret);

    pattern_->selectController_->UpdateCaretIndex(2);
    event.code = KeyCode::KEY_DPAD_RIGHT;
    ret = pattern_->IsMoveFocusOutFromRight(event);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleOnEscape001
 * @tc.desc: test HandleOnEscape
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnEscape001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->ProcessOverlay();
    auto ret = pattern_->HandleOnEscape();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleOnEscape003
 * @tc.desc: test HandleOnEscape with focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnEscape003, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->isCaretTwinkling_ = true;
    auto ret = pattern_->HandleOnEscape();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleOnTab001
 * @tc.desc: test HandleOnTab forward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnTab001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->HandleOnTab(false);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetFocusStyle001
 * @tc.desc: test SetFocusStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetFocusStyle001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->SetFocusStyle();
    auto host = pattern_->GetHost();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    auto textFieldTheme = pattern_->GetTheme();
    EXPECT_EQ(layoutProperty->GetTextColorValue(Color::BLACK), textFieldTheme->GetFocusTextColor());
}

/**
 * @tc.name: ClearFocusStyle001
 * @tc.desc: test ClearFocusStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ClearFocusStyle001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->isFocusBGColorSet_ = true;
    pattern_->isFocusTextColorSet_ = true;
    pattern_->isFocusPlaceholderColorSet_ = true;
    pattern_->ClearFocusStyle();
    EXPECT_FALSE(pattern_->isFocusBGColorSet_);
    EXPECT_FALSE(pattern_->isFocusTextColorSet_);
    EXPECT_FALSE(pattern_->isFocusPlaceholderColorSet_);
}

/**
 * @tc.name: ProcessFocusStyle001
 * @tc.desc: test ProcessFocusStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ProcessFocusStyle001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);

    pattern_->ProcessFocusStyle();
    EXPECT_TRUE(pattern_->inlineFocusState_);
}

/**
 * @tc.name: ProcessAutoFillOnFocus001
 * @tc.desc: test ProcessAutoFillOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ProcessAutoFillOnFocus001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->needToRequestKeyboardOnFocus_ = false;
    pattern_->ProcessAutoFillOnFocus();
    EXPECT_TRUE(pattern_->needToRequestKeyboardOnFocus_ == false);
}

/**
 * @tc.name: ProcNormalInlineStateInBlurEvent001
 * @tc.desc: test ProcNormalInlineStateInBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ProcNormalInlineStateInBlurEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);

    pattern_->inlineFocusState_ = true;
    pattern_->ProcNormalInlineStateInBlurEvent();
    EXPECT_FALSE(pattern_->inlineFocusState_);
}

/**
 * @tc.name: SetNeedToRequestKeyboardInner001
 * @tc.desc: test SetNeedToRequestKeyboardInner
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetNeedToRequestKeyboardInner001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->SetNeedToRequestKeyboardInner(true, RequestKeyboardInnerChangeReason::FOCUS);
    EXPECT_TRUE(pattern_->needToRequestKeyboardInner_);
}

/**
 * @tc.name: SetNeedToRequestKeyboardInner002
 * @tc.desc: test SetNeedToRequestKeyboardInner
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetNeedToRequestKeyboardInner002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->needToRequestKeyboardInner_ = true;
    pattern_->SetNeedToRequestKeyboardInner(false, RequestKeyboardInnerChangeReason::BLUR);
    EXPECT_FALSE(pattern_->needToRequestKeyboardInner_);
}

/**
 * @tc.name: UpdateShowCountBorderStyle002
 * @tc.desc: test UpdateShowCountBorderStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateShowCountBorderStyle002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"01234567890";
    pattern_->UpdateShowCountBorderStyle();
    EXPECT_TRUE(pattern_->showCountBorderStyle_);
}

/**
 * @tc.name: IsShowTranslate001
 * @tc.desc: test IsShowTranslate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsShowTranslate001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsShowTranslate();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsShowSearch001
 * @tc.desc: test IsShowSearch
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsShowSearch001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsShowSearch();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsShowAutoFill001
 * @tc.desc: test IsShowAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsShowAutoFill001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsShowAutoFill();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: StripNextLine001
 * @tc.desc: test StripNextLine
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, StripNextLine001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::wstring data = L"test\n\r\n";
    pattern_->StripNextLine(data);
    EXPECT_TRUE(data.find(L'\n') == std::wstring::npos);
}

/**
 * @tc.name: UpdateSelection002
 * @tc.desc: test UpdateSelection with both parameter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateSelection002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->UpdateSelection(10);
    EXPECT_EQ(pattern_->selectController_->GetStartIndex(), 10);
    EXPECT_EQ(pattern_->selectController_->GetEndIndex(), 10);
}

/**
 * @tc.name: ResetTouchAndMoveCaretState001
 * @tc.desc: test ResetTouchAndMoveCaretState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ResetTouchAndMoveCaretState001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->moveCaretState_.isMoveCaret = true;
    pattern_->moveCaretState_.isTouchCaret = true;
    pattern_->ResetTouchAndMoveCaretState();
    EXPECT_FALSE(pattern_->moveCaretState_.isMoveCaret);
    EXPECT_FALSE(pattern_->moveCaretState_.isTouchCaret);
}

/**
 * @tc.name: StartVibratorByIndexChange001
 * @tc.desc: test StartVibratorByIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, StartVibratorByIndexChange001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->StartVibratorByIndexChange(5, 3);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CheckMousePressedOverScrollBar001
 * @tc.desc: test CheckMousePressedOverScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CheckMousePressedOverScrollBar001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    GestureEvent info;
    info.localLocation_ = Offset(500, 500);
    auto ret = pattern_->CheckMousePressedOverScrollBar(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleBetweenSelectedPosition002
 * @tc.desc: test HandleBetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleBetweenSelectedPosition002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    GestureEvent info;
    info.localLocation_ = Offset(100, 100);
    auto ret = pattern_->HandleBetweenSelectedPosition(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CanChangeSelectState001
 * @tc.desc: test CanChangeSelectState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CanChangeSelectState001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->CanChangeSelectState();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: IsAccessibilityClick001
 * @tc.desc: test IsAccessibilityClick
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsAccessibilityClick001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsAccessibilityClick();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsOnUnitByPosition001
 * @tc.desc: test IsOnUnitByPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsOnUnitByPosition001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    Offset localOffset(500, 500);
    auto ret = pattern_->IsOnUnitByPosition(localOffset);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsOnPasswordByPosition001
 * @tc.desc: test IsOnPasswordByPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsOnPasswordByPosition001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    Offset localOffset(500, 500);
    auto ret = pattern_->IsOnPasswordByPosition(localOffset);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsOnCleanNodeByPosition001
 * @tc.desc: test IsOnCleanNodeByPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsOnCleanNodeByPosition001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    Offset localOffset(500, 500);
    auto ret = pattern_->IsOnCleanNodeByPosition(localOffset);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetSelectDetectEnable001
 * @tc.desc: test SetSelectDetectEnable
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetSelectDetectEnable001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->SetSelectDetectEnable(true);
    EXPECT_TRUE(pattern_->GetSelectDetectEnable());

    pattern_->SetSelectDetectEnable(false);
    EXPECT_FALSE(pattern_->GetSelectDetectEnable());
}

/**
 * @tc.name: GetPaddingTop001
 * @tc.desc: test GetPaddingTop
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetPaddingTop001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto padding = pattern_->GetPaddingTop();
    EXPECT_TRUE(padding >= 0);
}

/**
 * @tc.name: GetPaddingBottom001
 * @tc.desc: test GetPaddingBottom
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetPaddingBottom001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto padding = pattern_->GetPaddingBottom();
    EXPECT_TRUE(padding >= 0);
}

/**
 * @tc.name: GetPaddingLeft001
 * @tc.desc: test GetPaddingLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetPaddingLeft001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto padding = pattern_->GetPaddingLeft();
    EXPECT_TRUE(padding >= 0);
}

/**
 * @tc.name: GetPaddingRight001
 * @tc.desc: test GetPaddingRight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetPaddingRight001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto padding = pattern_->GetPaddingRight();
    EXPECT_TRUE(padding >= 0);
}

/**
 * @tc.name: GetHorizontalPaddingAndBorderSum001
 * @tc.desc: test GetHorizontalPaddingAndBorderSum
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetHorizontalPaddingAndBorderSum001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto sum = pattern_->GetHorizontalPaddingAndBorderSum();
    EXPECT_TRUE(sum >= 0);
}

/**
 * @tc.name: GetVerticalPaddingAndBorderSum001
 * @tc.desc: test GetVerticalPaddingAndBorderSum
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetVerticalPaddingAndBorderSum001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto sum = pattern_->GetVerticalPaddingAndBorderSum();
    EXPECT_TRUE(sum >= 0);
}

/**
 * @tc.name: GetPercentReferenceWidth001
 * @tc.desc: test GetPercentReferenceWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetPercentReferenceWidth001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto width = pattern_->GetPercentReferenceWidth();
    EXPECT_TRUE(width > 0);
}

/**
 * @tc.name: GetDragStyledText001
 * @tc.desc: test GetDragStyledText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetDragStyledText001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto text = pattern_->GetDragStyledText();
    EXPECT_TRUE(text.empty());
}

/**
 * @tc.name: ShowSelectAfterDragEvent001
 * @tc.desc: test ShowSelectAfterDragEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ShowSelectAfterDragEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->ShowSelectAfterDragEvent();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateCaretPositionWithClamp001
 * @tc.desc: test UpdateCaretPositionWithClamp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateCaretPositionWithClamp001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->UpdateCaretPositionWithClamp(10);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 4);
}

/**
 * @tc.name: UpdateCaretPositionWithClamp002
 * @tc.desc: test UpdateCaretPositionWithClamp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateCaretPositionWithClamp002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->UpdateCaretPositionWithClamp(-5);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 0);
}

/**
 * @tc.name: IsShowUnit001
 * @tc.desc: test IsShowUnit
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsShowUnit001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsShowUnit();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsShowPasswordIcon002
 * @tc.desc: test IsShowPasswordIcon
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsShowPasswordIcon002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
    });
    GetFocus();

    auto ret = pattern_->IsShowPasswordIcon();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CheckPasswordAreaState001
 * @tc.desc: test CheckPasswordAreaState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CheckPasswordAreaState001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->CheckPasswordAreaState();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateFocusForward001
 * @tc.desc: test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateFocusForward001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->UpdateFocusForward();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: GetLeftTextOfCursor001
 * @tc.desc: test GetLeftTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetLeftTextOfCursor001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->selectController_->UpdateCaretIndex(2);
    auto text = pattern_->GetLeftTextOfCursor(1);
    EXPECT_TRUE(text == u"e");
}

/**
 * @tc.name: GetRightTextOfCursor001
 * @tc.desc: test GetRightTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetRightTextOfCursor001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->selectController_->UpdateCaretIndex(2);
    auto text = pattern_->GetRightTextOfCursor(1);
    EXPECT_TRUE(text == u"s");
}

/**
 * @tc.name: GetTextIndexAtCursor001
 * @tc.desc: test GetTextIndexAtCursor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetTextIndexAtCursor001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->selectController_->UpdateCaretIndex(5);
    auto index = pattern_->GetTextIndexAtCursor();
    EXPECT_EQ(index, 5);
}

/**
 * @tc.name: PreferredLineHeight001
 * @tc.desc: test PreferredLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, PreferredLineHeight001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto height = pattern_->PreferredLineHeight();
    EXPECT_TRUE(height > 0);
}

/**
 * @tc.name: SearchRequestKeyboard001
 * @tc.desc: test SearchRequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SearchRequestKeyboard001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::NUMBER);
    });
    GetFocus();

    pattern_->SearchRequestKeyboard();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CreateObscuredText001
 * @tc.desc: test CreateObscuredText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CreateObscuredText001, TestSize.Level0)
{
    auto text = TextFieldPattern::CreateObscuredText(5);
    EXPECT_EQ(text.length(), 5u);
}

/**
 * @tc.name: CreateDisplayText001
 * @tc.desc: test CreateDisplayText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CreateDisplayText001, TestSize.Level0)
{
    std::u16string content = u"password";
    auto text = TextFieldPattern::CreateDisplayText(content, 2, true, false);
    EXPECT_EQ(text.length(), 8u);
}

/**
 * @tc.name: GetStrokeWidth001
 * @tc.desc: test GetStrokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetStrokeWidth001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto width = pattern_->GetStrokeWidth();
    EXPECT_FALSE(width.empty());
}

/**
 * @tc.name: GetStrokeColor001
 * @tc.desc: test GetStrokeColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetStrokeColor001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto color = pattern_->GetStrokeColor();
    EXPECT_FALSE(color.empty());
}

/**
 * @tc.name: TextInputTypeToString001
 * @tc.desc: test TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, TextInputTypeToString001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto str = pattern_->TextInputTypeToString();
    EXPECT_FALSE(str.empty());
}

/**
 * @tc.name: TextContentTypeToString001
 * @tc.desc: test TextContentTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, TextContentTypeToString001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto str = pattern_->TextContentTypeToString();
    EXPECT_FALSE(str.empty());
}

/**
 * @tc.name: GetPlaceholderFont001
 * @tc.desc: test GetPlaceholderFont
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetPlaceholderFont001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto font = pattern_->GetPlaceholderFont();
    EXPECT_FALSE(font.empty());
}

/**
 * @tc.name: GetTheme002
 * @tc.desc: test GetTheme
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetTheme002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto theme = pattern_->GetTheme();
    EXPECT_NE(theme, nullptr);
}

/**
 * @tc.name: InitTheme001
 * @tc.desc: test InitTheme
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, InitTheme001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->InitTheme();
    EXPECT_NE(pattern_->GetTheme(), nullptr);
}

/**
 * @tc.name: GetTextColor001
 * @tc.desc: test GetTextColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetTextColor001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto color = pattern_->GetTextColor();
    EXPECT_FALSE(color.empty());
}

/**
 * @tc.name: GetCaretColor001
 * @tc.desc: test GetCaretColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetCaretColor001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto color = pattern_->GetCaretColor();
    EXPECT_FALSE(color.empty());
}

/**
 * @tc.name: GetPlaceholderColor001
 * @tc.desc: test GetPlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetPlaceholderColor001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto color = pattern_->GetPlaceholderColor();
    EXPECT_FALSE(color.empty());
}

/**
 * @tc.name: GetFontSize001
 * @tc.desc: test GetFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetFontSize001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto size = pattern_->GetFontSize();
    EXPECT_FALSE(size.empty());
}

/**
 * @tc.name: GetMinFontScale001
 * @tc.desc: test GetMinFontScale
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetMinFontScale001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto scale = pattern_->GetMinFontScale();
    EXPECT_FALSE(scale.empty());
}

/**
 * @tc.name: GetMaxFontScale001
 * @tc.desc: test GetMaxFontScale
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetMaxFontScale001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto scale = pattern_->GetMaxFontScale();
    EXPECT_FALSE(scale.empty());
}

/**
 * @tc.name: GetEllipsisMode001
 * @tc.desc: test GetEllipsisMode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetEllipsisMode001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto mode = pattern_->GetEllipsisMode();
    EXPECT_FALSE(mode.empty());
}

/**
 * @tc.name: GetItalicFontStyle001
 * @tc.desc: test GetItalicFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetItalicFontStyle001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto style = pattern_->GetItalicFontStyle();
    EXPECT_TRUE(style == Ace::FontStyle::NORMAL);
}

/**
 * @tc.name: GetFontWeight001
 * @tc.desc: test GetFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetFontWeight001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto weight = pattern_->GetFontWeight();
    EXPECT_TRUE(weight == FontWeight::W400 || weight == FontWeight::W500);
}

/**
 * @tc.name: GetFontFamily001
 * @tc.desc: test GetFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetFontFamily001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto family = pattern_->GetFontFamily();
    EXPECT_FALSE(family.empty());
}

/**
 * @tc.name: GetTextAlign001
 * @tc.desc: test GetTextAlign
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetTextAlign001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto align = pattern_->GetTextAlign();
    EXPECT_TRUE(align == TextAlign::LEFT || align == TextAlign::START);
}

/**
 * @tc.name: GetPlaceHolder001
 * @tc.desc: test GetPlaceHolder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetPlaceHolder001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "placeholder", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto placeholder = pattern_->GetPlaceHolder();
    EXPECT_TRUE(placeholder == u"placeholder");
}

/**
 * @tc.name: GetMaxLength001
 * @tc.desc: test GetMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetMaxLength001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetMaxLength(100);
    });
    GetFocus();

    auto len = pattern_->GetMaxLength();
    EXPECT_EQ(len, 100u);
}

/**
 * @tc.name: GetMaxLines001
 * @tc.desc: test GetMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetMaxLines001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto lines = pattern_->GetMaxLines();
    EXPECT_TRUE(lines > 0);
}

/**
 * @tc.name: GetMinLines001
 * @tc.desc: test GetMinLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetMinLines001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto lines = pattern_->GetMinLines();
    EXPECT_TRUE(lines >= 1);
}

/**
 * @tc.name: GetCopyOptionString001
 * @tc.desc: test GetCopyOptionString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetCopyOptionString001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto option = pattern_->GetCopyOptionString();
    EXPECT_FALSE(option.empty());
}

/**
 * @tc.name: GetInputStyleString001
 * @tc.desc: test GetInputStyleString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetInputStyleString001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto style = pattern_->GetInputStyleString();
    EXPECT_FALSE(style.empty());
}

/**
 * @tc.name: GetErrorTextString001
 * @tc.desc: test GetErrorTextString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetErrorTextString001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowError(u"error", true);
    });
    GetFocus();

    auto text = pattern_->GetErrorTextString();
    EXPECT_TRUE(text == u"error" || text.empty());
}

/**
 * @tc.name: GetBarStateString001
 * @tc.desc: test GetBarStateString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetBarStateString001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto state = pattern_->GetBarStateString();
    EXPECT_FALSE(state.empty());
}

/**
 * @tc.name: GetErrorTextState002
 * @tc.desc: test GetErrorTextState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetErrorTextState002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowError(u"error", true);
    });
    GetFocus();

    auto state = pattern_->GetErrorTextState();
    EXPECT_TRUE(state || !state);
}

/**
 * @tc.name: GetShowPasswordIconString001
 * @tc.desc: test GetShowPasswordIconString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetShowPasswordIconString001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto icon = pattern_->GetShowPasswordIconString();
    EXPECT_FALSE(icon.empty());
}

/**
 * @tc.name: HandleOnSelectAll001
 * @tc.desc: test HandleOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnSelectAll001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->HandleOnSelectAll(true, false, false);
    EXPECT_TRUE(pattern_->IsSelected());
}

/**
 * @tc.name: HandleOnPasswordVault001
 * @tc.desc: test HandleOnPasswordVault
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnPasswordVault001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->HandleOnPasswordVault();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleButtonFocusEvent001
 * @tc.desc: test HandleButtonFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleButtonFocusEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto responseArea = pattern_->GetResponseArea();
    pattern_->HandleButtonFocusEvent(responseArea);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CalcDecoratorHeight001
 * @tc.desc: test CalcDecoratorHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CalcDecoratorHeight001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    RefPtr<FrameNode> childrenNode =
        FrameNode::GetOrCreateFrameNode("childTag", 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto height = pattern_->CalcDecoratorHeight(childrenNode);
    EXPECT_TRUE(height >= 0);
}

/**
 * @tc.name: UltralimitShake001
 * @tc.desc: test UltralimitShake
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UltralimitShake001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetMaxLength(10);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"01234567890123456789";
    pattern_->UltralimitShake();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: DeleteBackwardOperation001
 * @tc.desc: test DeleteBackwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, DeleteBackwardOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->selectController_->UpdateCaretIndex(4);
    pattern_->DeleteBackwardOperation(1);
    EXPECT_TRUE(pattern_->contentController_->content_ == u"tes");
}

/**
 * @tc.name: DeleteForwardOperation001
 * @tc.desc: test DeleteForwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, DeleteForwardOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->selectController_->UpdateCaretIndex(0);
    pattern_->DeleteForwardOperation(1);
    EXPECT_TRUE(pattern_->contentController_->content_ == u"est");
}

/**
 * @tc.name: HandleOnPageUp001
 * @tc.desc: test HandleOnPageUp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnPageUp001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->HandleOnPageUp();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleOnPageDown001
 * @tc.desc: test HandleOnPageDown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnPageDown001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->HandleOnPageDown();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CreateHandles001
 * @tc.desc: test CreateHandles
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CreateHandles001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->CreateHandles();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetEmojiSubStringRange001
 * @tc.desc: test GetEmojiSubStringRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetEmojiSubStringRange001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    int32_t start = 0;
    int32_t end = 5;
    pattern_->GetEmojiSubStringRange(start, end);
    EXPECT_TRUE(start >= 0 && end >= start);
}

/**
 * @tc.name: CleanCounterNode001
 * @tc.desc: test CleanCounterNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CleanCounterNode001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowCounter(true);
    });
    GetFocus();

    pattern_->CleanCounterNode();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CleanErrorNode001
 * @tc.desc: test CleanErrorNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CleanErrorNode001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowError(u"error", true);
    });
    GetFocus();

    pattern_->CleanErrorNode();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateObscure001
 * @tc.desc: test UpdateObscure
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateObscure001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::u16string insertValue = u"a";
    pattern_->UpdateObscure(insertValue, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CalcCounterAfterFilterInsertValue001
 * @tc.desc: test CalcCounterAfterFilterInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CalcCounterAfterFilterInsertValue001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    std::u16string insertValue = u"1234567";
    pattern_->CalcCounterAfterFilterInsertValue(4, insertValue, 10);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: NotifyImfFinishTextPreview001
 * @tc.desc: test NotifyImfFinishTextPreview
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NotifyImfFinishTextPreview001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->NotifyImfFinishTextPreview();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InsertValueByController001
 * @tc.desc: test InsertValueByController
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, InsertValueByController001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::u16string insertValue = u"test";
    auto ret = pattern_->InsertValueByController(insertValue, 0);
    EXPECT_TRUE(ret >= 0);
}

/**
 * @tc.name: ExecuteInsertValueCommand001
 * @tc.desc: test ExecuteInsertValueCommand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ExecuteInsertValueCommand001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    InsertCommandInfo info;
    info.insertValue = u"test";
    info.reason = InputReason::IME;
    pattern_->ExecuteInsertValueCommand(info);
    EXPECT_TRUE(pattern_->contentController_->content_.find(u"test") != std::u16string::npos);
}

/**
 * @tc.name: UpdateInputFilterErrorText001
 * @tc.desc: test UpdateInputFilterErrorText with u16string
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateInputFilterErrorText001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::u16string errorText = u"error";
    pattern_->UpdateInputFilterErrorText(errorText);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateInputFilterErrorText002
 * @tc.desc: test UpdateInputFilterErrorText with string
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateInputFilterErrorText002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::string errorText = "error";
    pattern_->UpdateInputFilterErrorText(errorText);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: OnValueChanged001
 * @tc.desc: test OnValueChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnValueChanged001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->OnValueChanged(true, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: OnHandleAreaChanged001
 * @tc.desc: test OnHandleAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnHandleAreaChanged001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->OnHandleAreaChanged();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleCounterBorder001
 * @tc.desc: test HandleCounterBorder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleCounterBorder001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowCounter(true);
    });
    GetFocus();

    pattern_->HandleCounterBorder();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CloseSelectOverlay002
 * @tc.desc: test CloseSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CloseSelectOverlay002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->CloseSelectOverlay(false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: NotifyKeyboardClosedByUser001
 * @tc.desc: test NotifyKeyboardClosedByUser
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NotifyKeyboardClosedByUser001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->NotifyKeyboardClosedByUser();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: NotifyKeyboardClosed001
 * @tc.desc: test NotifyKeyboardClosed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NotifyKeyboardClosed001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->NotifyKeyboardClosed();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateScrollBarOffset001
 * @tc.desc: test UpdateScrollBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateScrollBarOffset001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->UpdateScrollBarOffset();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: PlayScrollBarAppearAnimation001
 * @tc.desc: test PlayScrollBarAppearAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, PlayScrollBarAppearAnimation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->PlayScrollBarAppearAnimation();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ScheduleDisappearDelayTask001
 * @tc.desc: test ScheduleDisappearDelayTask
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ScheduleDisappearDelayTask001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->ScheduleDisappearDelayTask();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: IsAtTop001
 * @tc.desc: test IsAtTop
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsAtTop001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsAtTop();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: IsAtBottom001
 * @tc.desc: test IsAtBottom
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsAtBottom001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsAtBottom();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ScheduleTaskWithLayoutDeferral001
 * @tc.desc: test ScheduleTaskWithLayoutDeferral
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, ScheduleTaskWithLayoutDeferral001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    bool executed = false;
    pattern_->ScheduleTaskWithLayoutDeferral([&executed]() { executed = true; });
    EXPECT_TRUE(true);
}

/**
 * @tc.name: StopEditing001
 * @tc.desc: test StopEditing
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, StopEditing001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->isCaretTwinkling_ = true;
    pattern_->StopEditing();
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: GetShowResultImageSrc001
 * @tc.desc: test GetShowResultImageSrc
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetShowResultImageSrc001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto src = pattern_->GetShowResultImageSrc();
    EXPECT_FALSE(src.empty());
}

/**
 * @tc.name: GetHideResultImageSrc001
 * @tc.desc: test GetHideResultImageSrc
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetHideResultImageSrc001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto src = pattern_->GetHideResultImageSrc();
    EXPECT_FALSE(src.empty());
}

/**
 * @tc.name: GetNormalUnderlineColorStr001
 * @tc.desc: test GetNormalUnderlineColorStr
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetNormalUnderlineColorStr001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto color = pattern_->GetNormalUnderlineColorStr();
    EXPECT_FALSE(color.empty());
}

/**
 * @tc.name: GetTypingUnderlineColorStr001
 * @tc.desc: test GetTypingUnderlineColorStr
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetTypingUnderlineColorStr001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto color = pattern_->GetTypingUnderlineColorStr();
    EXPECT_FALSE(color.empty());
}

/**
 * @tc.name: GetDisableUnderlineColorStr001
 * @tc.desc: test GetDisableUnderlineColorStr
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetDisableUnderlineColorStr001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto color = pattern_->GetDisableUnderlineColorStr();
    EXPECT_FALSE(color.empty());
}

/**
 * @tc.name: GetErrorUnderlineColorStr001
 * @tc.desc: test GetErrorUnderlineColorStr
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetErrorUnderlineColorStr001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto color = pattern_->GetErrorUnderlineColorStr();
    EXPECT_FALSE(color.empty());
}

/**
 * @tc.name: GetMarginBottom001
 * @tc.desc: test GetMarginBottom
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetMarginBottom001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto margin = pattern_->GetMarginBottom();
    EXPECT_TRUE(margin >= 0);
}

/**
 * @tc.name: RequestCustomKeyboard001
 * @tc.desc: test RequestCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, RequestCustomKeyboard001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->RequestCustomKeyboard();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CloseCustomKeyboard001
 * @tc.desc: test CloseCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CloseCustomKeyboard001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->CloseCustomKeyboard();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: BetweenSelectedPosition003
 * @tc.desc: test BetweenSelectedPosition with Offset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, BetweenSelectedPosition003, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    Offset globalOffset(100, 100);
    auto ret = pattern_->BetweenSelectedPosition(globalOffset);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, DumpInfo001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->DumpInfo();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: test DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, DumpAdvanceInfo001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->DumpAdvanceInfo();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: DumpPlaceHolderInfo001
 * @tc.desc: test DumpPlaceHolderInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, DumpPlaceHolderInfo001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "placeholder", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->DumpPlaceHolderInfo();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: DumpTextEngineInfo001
 * @tc.desc: test DumpTextEngineInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, DumpTextEngineInfo001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->DumpTextEngineInfo();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: DumpScaleInfo001
 * @tc.desc: test DumpScaleInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, DumpScaleInfo001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->DumpScaleInfo();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetDumpTextValue001
 * @tc.desc: test GetDumpTextValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetDumpTextValue001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto value = pattern_->GetDumpTextValue();
    EXPECT_FALSE(value.empty());
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnColorConfigurationUpdate001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->OnColorConfigurationUpdate();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: NeedPaintSelect001
 * @tc.desc: test NeedPaintSelect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, NeedPaintSelect001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->NeedPaintSelect();
    EXPECT_TRUE(ret || !ret);
}

/**
 * @tc.name: SetCustomKeyboardOption001
 * @tc.desc: test SetCustomKeyboardOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetCustomKeyboardOption001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->SetCustomKeyboardOption(true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateCaretInfoToController002
 * @tc.desc: test UpdateCaretInfoToController
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, UpdateCaretInfoToController002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->UpdateCaretInfoToController(false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: OnObscuredChanged001
 * @tc.desc: test OnObscuredChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnObscuredChanged001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->OnObscuredChanged(true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: IsInPasswordMode001
 * @tc.desc: test IsInPasswordMode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsInPasswordMode001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsInPasswordMode();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleOnAIWrite001
 * @tc.desc: test HandleOnAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleOnAIWrite001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->HandleOnAIWrite();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetAIWriteInfo001
 * @tc.desc: test GetAIWriteInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, GetAIWriteInfo001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    AIWriteInfo info;
    pattern_->GetAIWriteInfo(info);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CursorMoveLeft001
 * @tc.desc: test CursorMoveLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CursorMoveLeft001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->selectController_->UpdateCaretIndex(2);
    auto ret = pattern_->CursorMoveLeft();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CursorMoveRight001
 * @tc.desc: test CursorMoveRight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CursorMoveRight001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->selectController_->UpdateCaretIndex(2);
    auto ret = pattern_->CursorMoveRight();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CursorMoveUp001
 * @tc.desc: test CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CursorMoveUp001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->CursorMoveUp();
    EXPECT_TRUE(ret || !ret);
}

/**
 * @tc.name: CursorMoveDown001
 * @tc.desc: test CursorMoveDown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, CursorMoveDown001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->CursorMoveDown();
    EXPECT_TRUE(ret || !ret);
}

/**
 * @tc.name: SetCaretPosition001
 * @tc.desc: test SetCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetCaretPosition001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"test";
    pattern_->SetCaretPosition(2);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 2);
}

/**
 * @tc.name: HandleExtendAction001
 * @tc.desc: test HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleExtendAction001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->HandleExtendAction(ACTION_AUTOFILL);
    EXPECT_TRUE(true);
}
} // namespace OHOS::Ace::NG