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
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
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
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
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
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
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
    auto eventHub = textFieldNode->GetOrCreateEventHub<TextFieldEventHub>();
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
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
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
    eventHub->onDragEnter_(event, extraParams);
    EXPECT_TRUE(pattern_->IsNormalInlineState());

    eventHub->onDragMove_(event, extraParams);
    EXPECT_TRUE(pattern_->IsNormalInlineState());

    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    layoutProperty->UpdateTextInputType(TextInputType::JS_ENUM_URL);
    host->previewOption_.enableEdgeAutoScroll = false;
    eventHub->onDragMove_(event, extraParams);
    EXPECT_FALSE(pattern_->contentScroller_.isScrolling);

    eventHub->onDragLeave_(event, extraParams);
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
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
    fontManager->externalLoadCallbacks_.emplace(WeakPtr(frameNode_), std::make_pair("myFont", fontChangeCallback));
    fontChangeCallback();
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
    layoutProperty_->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetWidth(200.0f);
    layoutProperty_->contentConstraint_ = contentConstraint;
    width = textFieldLayoutAlgorithm->GetMaxIndent(&layoutWrapper, std::numeric_limits<double>::infinity());
    EXPECT_EQ(width, 200.0f);
}
} // namespace OHOS::Ace::NG