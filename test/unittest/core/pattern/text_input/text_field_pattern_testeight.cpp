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
    
 
class TextFieldPatternTestEight : public TextInputBases {
public:
};
 
/**
 * @tc.name: SwapIfLarger001
 * @tc.desc: test SwapIfLarger
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, SwapIfLarger001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t a = 3;
    int32_t b = 2;
    pattern_->Delete(a, b);
    EXPECT_EQ(a, 3);
}

/**
 * @tc.name: CalculateBoundsRect001
 * @tc.desc: test CalculateBoundsRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, CalculateBoundsRect001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    OffsetF offset(4.0f, 5.0f);
    auto host = pattern_->GetHost();
    auto geometryNode = host->GetGeometryNode();
    geometryNode->SetFrameOffset(offset);
    pattern_->CalculateBoundsRect();
}

/**
 * @tc.name: CreateObscuredText001
 * @tc.desc: test CreateObscuredText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, CreateObscuredText001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    std::string language = "ar";
    std::string countryOrRegion;
    std::string script;
    std::string selectLanguage;
    std::string keywordsAndValues;
    Localization::GetInstance()->SetLocaleImpl(language, countryOrRegion, script, selectLanguage, keywordsAndValues);
    auto str = pattern_->CreateObscuredText(12);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    std::string utf8String = converter.to_bytes(str);
    EXPECT_STREQ(utf8String.c_str(), string("************").c_str());
}

/**
 * @tc.name: SetAccessibilityUnitAction001
 * @tc.desc: test SetAccessibilityUnitAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, SetAccessibilityUnitAction001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto groupNode = ViewStackProcessor::GetInstance()->Finish();
    pattern_->unitNode_ =  AceType::DynamicCast<NG::UINode>(
        AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    pattern_->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern_);
    pattern_->SetAccessibilityUnitAction();
}

/**
 * @tc.name: HandleContentSizeChange001
 * @tc.desc: test HandleContentSizeChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleContentSizeChange001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    RectF rect(1.0f, 2.0f, 3.0f, 4.0f);
    auto func = [](float a, float b) {
        return;
    };
    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    eventHub->SetOnContentSizeChange(func);
    pattern_->HandleContentSizeChange(rect);
}

/**
 * @tc.name: CancelDelayProcessOverlay001
 * @tc.desc: test CancelDelayProcessOverlay
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, CancelDelayProcessOverlay001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto func = []() {
        return;
    };
    pattern_->processOverlayDelayTask_ = func;
    pattern_->CancelDelayProcessOverlay();
    EXPECT_EQ(pattern_->processOverlayDelayTask_, nullptr);
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: test OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, OnThemeScopeUpdate001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t themeScopeId = 0;
    auto ret = pattern_->OnThemeScopeUpdate(themeScopeId);
    EXPECT_FALSE(ret);

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->propTextColorFlagByUser_ = Color::TRANSPARENT;
    paintProperty->propBackgroundColor_ = Color::TRANSPARENT;
    paintProperty->propCaretColorFlagByUser_ = true;
    paintProperty->propPlaceholderColorFlagByUser_ = true;
    ret = pattern_->OnThemeScopeUpdate(themeScopeId);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: NotifyImfFinishTextPreview001
 * @tc.desc: test NotifyImfFinishTextPreview
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, NotifyImfFinishTextPreview001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()
        ->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusHub = pattern_->GetFocusHub();
    focusHub->currentFocus_ = false;
    pattern_->NotifyImfFinishTextPreview();
    EXPECT_FALSE(focusHub->IsCurrentFocus());
}

/**
 * @tc.name: CharLineChanged001
 * @tc.desc: test CharLineChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, CharLineChanged001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t caretPosition = -1;
    auto ret = pattern_->CharLineChanged(caretPosition);
    EXPECT_TRUE(ret);

    caretPosition = 123;
    std::string value = "12";
    pattern_->contentController_->SetTextValue(UtfUtils::Str8DebugToStr16(value));
    ret = pattern_->CharLineChanged(caretPosition);
    EXPECT_TRUE(ret);

    caretPosition = 1;
    value = "123";
    pattern_->contentController_->SetTextValue(UtfUtils::Str8DebugToStr16(value));
    ret = pattern_->CharLineChanged(caretPosition);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleCloseKeyboard001
 * @tc.desc: test HandleCloseKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleCloseKeyboard001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->independentControlKeyboard_ = true;
    pattern->HandleCloseKeyboard(true);
    EXPECT_EQ(pattern->connection_, nullptr);
}

/**
 * @tc.name: UpdateRectByTextAlign001
 * @tc.desc: test UpdateRectByTextAlign
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, UpdateRectByTextAlign001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextAlign(TextAlign::LEFT);
    });
    GetFocus();

    RectF textRect = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    pattern_->UpdateRectByTextAlign(textRect);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ToJsonValue001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    std::string testJson = "true";
    std::unique_ptr<JsonValue> jsonconst = JsonUtil::ParseJsonString(testJson);
    InspectorFilter filter;
    filter.filterFixed = 1;
    pattern_->ToJsonValue(jsonconst, filter);

    filter.filterFixed = 0;
    auto container = Container::Current();
    container->apiTargetVersion_ = 15;
    pattern_->isPasswordSymbol_ = true;
    pattern_->ToJsonValue(jsonconst, filter);
}

/**
 * @tc.name: GetDumpTextValue001
 * @tc.desc: test GetDumpTextValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, GetDumpTextValue001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->GetDumpTextValue();
}

/**
 * @tc.name: DumpViewDataPageNode001
 * @tc.desc: test DumpViewDataPageNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, DumpViewDataPageNode001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    std::vector<std::string> placeHolder;
    std::vector<int> type;
    std::vector<std::string> metadata;
    RefPtr<ViewDataWrap> viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    viewDataWrap->SetUserSelected(true);
    bool needsRecordData = true;
    pattern_->autoFillOtherAccount_ = true;
    pattern_->DumpViewDataPageNode(viewDataWrap, needsRecordData);
    EXPECT_FALSE(pattern_->autoFillOtherAccount_);

    needsRecordData = false;
    pattern_->autoFillOtherAccount_ = false;
    pattern_->DumpViewDataPageNode(viewDataWrap, needsRecordData);
    EXPECT_FALSE(pattern_->autoFillOtherAccount_);
}

/**
 * @tc.name: ClearTextContent001
 * @tc.desc: test ClearTextContent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ClearTextContent001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern_->ClearTextContent();
    EXPECT_TRUE(pattern_->contentController_->IsEmpty());

    pattern_->hasPreviewText_ = true;
    std::u16string value = u"n";
    pattern_->contentController_->SetTextValue(value);
    pattern_->ClearTextContent();
    EXPECT_FALSE(pattern_->contentController_->IsEmpty());
}

/**
 * @tc.name: ClearTextContent002
 * @tc.desc: test ClearTextContent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ClearTextContent002, TestSize.Level0)
{
    CreateTextField();

    pattern_->ClearTextContent();
    EXPECT_TRUE(pattern_->contentController_->IsEmpty());

    std::u16string value = u"n";
    pattern_->contentController_->SetTextValue(value);
    pattern_->ClearTextContent();
    EXPECT_FALSE(pattern_->showCountBorderStyle_);
}

/**
 * @tc.name: HandleButtonMouseEvent001
 * @tc.desc: test HandleButtonMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleButtonMouseEvent001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<TextInputResponseArea> responseArea = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern);
    bool isHover = true;
    pattern_->HandleButtonMouseEvent(responseArea, isHover);
    EXPECT_NE(pattern_->textFieldOverlayModifier_, nullptr);

    isHover = false;
    pattern_->HandleButtonMouseEvent(responseArea, isHover);
    EXPECT_NE(pattern_->textFieldOverlayModifier_, nullptr);
}

/**
 * @tc.name: CursorMove001
 * @tc.desc: test CursorMove
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, CursorMove001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    CaretMoveIntent direction = static_cast<CaretMoveIntent>(23);
    pattern_->CursorMove(direction);
    EXPECT_TRUE(pattern_->inputOperations_.empty());
}

/**
 * @tc.name: GetDumpTextValue001
 * @tc.desc: test HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleBlurEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->isOnHover_ = true;
    pattern_->HandleBlurEvent();
    EXPECT_TRUE(pattern_->isOnHover_);
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, OnKeyEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    KeyEvent event;
    event.code = KeyCode::KEY_TAB;
    pattern_->needToRequestKeyboardOnFocus_ = false;
    pattern_->needToRequestKeyboardInner_ = true;
    auto pipeline = pattern_->GetContext();
    auto textFieldManager = AIWriteAdapter::DynamicCast<TextFieldManagerNG>(
        pipeline->GetTextFieldManager());
    textFieldManager->imeShow_ = true;
    auto ret = pattern_->OnKeyEvent(event);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleOnEscape001
 * @tc.desc: test HandleOnEscape
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleOnEscape001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->HandleOnEscape();
    EXPECT_FALSE(ret);
    pattern_->hasPreviewText_ = true;
    ret = pattern_->HandleOnEscape();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleOnUndoAction001
 * @tc.desc: test HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleOnUndoAction001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    TextEditingValueNG t1;
    pattern_->operationRecords_.push_back(t1);
    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    pattern_->HandleOnUndoAction();
    EXPECT_FALSE(pattern_->operationRecords_.empty());

    auto func1 = [](const ChangeValueInfo& info) {
        return true;
    };
    TextEditingValueNG t[22];
    for (int i = 0; i < 22; i++) {
        pattern_->redoOperationRecords_.push_back(t[i]);
    }
    eventHub->onWillChangeEvent_ = func1;
    pattern_->HandleOnUndoAction();
    EXPECT_FALSE(pattern_->operationRecords_.empty());
}

/**
 * @tc.name: HandleOnRedoAction001
 * @tc.desc: test HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleOnRedoAction001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    TextEditingValueNG t1;
    pattern_->redoOperationRecords_.push_back(t1);
    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    pattern_->HandleOnRedoAction();
    EXPECT_FALSE(pattern_->operationRecords_.empty());
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test HandleOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleOnCopy001, TestSize.Level0)
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
    pattern->contentController_->content_ = u"Test";
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
    pattern->HandleOnCopy(true);
    EXPECT_EQ(calledOnCopy, true);
}

/**
 * @tc.name: HandleOnPaste001
 * @tc.desc: test HandleOnPaste
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleOnPaste001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    auto func = [](const std::u16string& str, OHOS::Ace::NG::TextCommonEvent& event) {
        event.preventDefault_ = true;
        return;
    };
    eventHub->SetOnPasteWithEvent(func);
    pattern_->HandleOnPaste();
    EXPECT_NE(pattern_->clipboard_, nullptr);
}

/**
 * @tc.name: IsShowTranslate001
 * @tc.desc: test IsShowTranslate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, IsShowTranslate001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto container = MockContainer::Current();
    container->SetIsSceneBoardWindow(true);
    pattern_->IsShowTranslate();
    auto textFieldTheme = pattern_->GetTheme();
    EXPECT_NE(textFieldTheme, nullptr);
}

/**
 * @tc.name: IsShowSearch001
 * @tc.desc: test IsShowSearch
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, IsShowSearch001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto container = MockContainer::Current();
    container->SetIsSceneBoardWindow(true);
    pattern_->IsShowSearch();
    auto textFieldTheme = pattern_->GetTheme();
    EXPECT_NE(textFieldTheme, nullptr);
}

/**
 * @tc.name: HandleOnCut001
 * @tc.desc: test HandleOnCut
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleOnCut001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty ->UpdateCopyOptions(CopyOptions::None);
    pattern_->HandleOnCut();
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.None");
}

/**
 * @tc.name: HandleTouchUp001
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleTouchUp001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->hasPreviewText_ = true;
    pattern_->isTouchPreviewText_ = true;
    pattern_->HandleTouchUp();
    EXPECT_TRUE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: ResetTouchAndMoveCaretState001
 * @tc.desc: test ResetTouchAndMoveCaretState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ResetTouchAndMoveCaretState001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->moveCaretState_.isTouchCaret = false;
    pattern_->moveCaretState_.isMoveCaret = true;
    pattern_->ResetTouchAndMoveCaretState();
    EXPECT_FALSE(pattern_->moveCaretState_.isMoveCaret);

    pattern_->moveCaretState_.isMoveCaret = true;
    auto focusHub = pattern_->GetFocusHub();
    focusHub->currentFocus_ = false;
    pattern_->ResetTouchAndMoveCaretState();
    EXPECT_FALSE(pattern_->moveCaretState_.isMoveCaret);
}

/**
 * @tc.name: UpdateCaretByTouchMove001
 * @tc.desc: test UpdateCaretByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, UpdateCaretByTouchMove001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    TouchLocationInfo info(1);
    pattern_->contentScroller_.isScrolling = true;
    pattern_->UpdateCaretByTouchMove(info);
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: CreateTextDragInfo001
 * @tc.desc: test CreateTextDragInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, CreateTextDragInfo001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto manager = SelectContentOverlayManager::GetOverlayManager();
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    manager->selectOverlayHolder_ = holder;
    pattern_->selectOverlay_->OnBind(manager);
    manager->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>();
    auto info = pattern_->CreateTextDragInfo();
    EXPECT_EQ(info.maxSelectedWidth, 0);

    pattern_->selectController_->firstHandleInfo_.index = 10;
    pattern_->selectController_->secondHandleInfo_.index = 2;
    auto manager1 = pattern_->selectOverlay_->GetManager<SelectContentOverlayManager>();
    manager1->shareOverlayInfo_->firstHandle.isShow = false;
    manager1->shareOverlayInfo_->secondHandle.isShow = false;
    info = pattern_->CreateTextDragInfo();
    EXPECT_EQ(info.maxSelectedWidth, 0);

    manager1->shareOverlayInfo_->firstHandle.isShow = false;
    manager1->shareOverlayInfo_->secondHandle.isShow = true;
    info = pattern_->CreateTextDragInfo();
    EXPECT_TRUE(info.isFirstHandleAnimation);
    EXPECT_FALSE(info.isSecondHandleAnimation);

    manager1->shareOverlayInfo_->firstHandle.isShow = true;
    manager1->shareOverlayInfo_->secondHandle.isShow = false;
    info = pattern_->CreateTextDragInfo();
    EXPECT_FALSE(info.isFirstHandleAnimation);
    EXPECT_TRUE(info.isSecondHandleAnimation);
}

/**
 * @tc.name: OnDragDrop001
 * @tc.desc: test OnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, OnDragDrop001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto func = pattern_->OnDragDrop();
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string str("test");
    pattern_->dragStatus_ = DragStatus::DRAGGING;
    dragEvent->pressedKeyCodes_.push_back(KeyCode::KEY_CTRL_LEFT);
    func(dragEvent, str);
    EXPECT_FALSE(pattern_->releaseInDrop_);

    pattern_->dragStatus_ = DragStatus::DRAGGING;
    dragEvent->pressedKeyCodes_[0] = KeyCode::KEY_PLUS;
    dragEvent->pressedKeyCodes_.push_back(KeyCode::KEY_CTRL_RIGHT);
    func(dragEvent, str);
    EXPECT_FALSE(pattern_->releaseInDrop_);
 
    pattern_->dragStatus_ = DragStatus::NONE;
    dragEvent->unifiedData_ = AceType::MakeRefPtr<MockUnifiedData>();
    std::vector<uint8_t> data = {1, 2, 3};
    UdmfClient::GetInstance()->AddSpanStringRecord(dragEvent->unifiedData_, data);
    func(dragEvent, str);
    EXPECT_FALSE(pattern_->releaseInDrop_);
}

/**
 * @tc.name: HandleSingleClickEvent001
 * @tc.desc: test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleSingleClickEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->mouseStatus_ = MouseStatus::MOVE;
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);

    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    GestureEvent info;
    bool firstGetFocus = true;
    pattern_->HandleSingleClickEvent(info, firstGetFocus);
    EXPECT_EQ(paintProperty->GetInputStyleValue(InputStyle::DEFAULT), InputStyle::INLINE);

    pattern_->mouseStatus_ = MouseStatus::NONE;
    pattern_->selectOverlay_->isUsingMouse_ = false;
    pattern_->needSelectAll_ = true;
    pattern_->HandleSingleClickEvent(info, firstGetFocus);
    EXPECT_EQ(paintProperty->GetInputStyleValue(InputStyle::DEFAULT), InputStyle::INLINE);
}

/**
 * @tc.name: StopTwinkling001
 * @tc.desc: test StopTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, StopTwinkling001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->obscureTickCountDown_ = 1;
    pattern_->cursorVisible_ = false;
    pattern_->StopTwinkling();
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: ShowCaretAndStopTwinklingg001
 * @tc.desc: test ShowCaretAndStopTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ShowCaretAndStopTwinkling001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->obscureTickCountDown_ = 1;
    pattern_->ShowCaretAndStopTwinkling();
    EXPECT_TRUE(pattern_->cursorVisible_);
}

/**
 * @tc.name: FilterInitializeText001
 * @tc.desc: test FilterInitializeText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, FilterInitializeText001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->showCountBorderStyle_ = true;
    pattern_->isFilterChanged_ = true;
    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    pattern_->FilterInitializeText();
    EXPECT_FALSE(pattern_->isFilterChanged_);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: test HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleLongPress001, TestSize.Level0)
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
 * @tc.name: IsMouseOverScrollBar001
 * @tc.desc: test IsMouseOverScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, IsMouseOverScrollBar001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    BaseEventInfo* info = nullptr;
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF, ShapeMode::DEFAULT);
    auto ret = pattern_->IsMouseOverScrollBar(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: InitValueText001
 * @tc.desc: test InitValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, InitValueText001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::u16string content = u"test";
    pattern_->hasPreviewText_ = true;
    auto ret = pattern_->InitValueText(content);
    EXPECT_FALSE(ret);

    pattern_->hasPreviewText_ = false;
    pattern_->deleteBackwardOperations_.push(11);
    ret = pattern_->InitValueText(content);
    EXPECT_FALSE(ret);

    pattern_->deleteBackwardOperations_.pop();
    content = u"";
    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    ret = pattern_->InitValueText(content);
    EXPECT_FALSE(ret);

    auto func1 = [](const ChangeValueInfo& info) {
        return true;
    };
    eventHub->onWillChangeEvent_ = func1;
    ret = pattern_->InitValueText(content);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: InitPanEvent001
 * @tc.desc: test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, InitPanEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->boxSelectPanEvent_ = nullptr;
    pattern_->InitPanEvent();
    EXPECT_NE(pattern_->boxSelectPanEvent_, nullptr);

    auto actionStartTask = [](const GestureEvent& info) {};
    auto actionUpdateTask = [](const GestureEvent& info) {};
    auto actionEndTask = [](const GestureEvent& info) {};
    GestureEventNoParameter actionCancelTask;
    pattern_->boxSelectPanEvent_ = AceType::MakeRefPtr<PanEvent>(std::move(actionStartTask),
        std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    pattern_->InitPanEvent();
    auto host = pattern_->GetHost();
    auto gestureHub = host->GetOrCreateGestureEventHub();
    auto gestureInfo1 =gestureHub->panEventActuator_->panRecognizer_->GetOrCreateGestureInfo();
    EXPECT_EQ(gestureInfo1->type_, GestureTypeName::TEXTFIELD_BOXSELECT);

    RefPtr<GestureInfo> gestureInfo = AceType::MakeRefPtr<GestureInfo>(
        GestureTypeName::PAN_GESTURE, GestureTypeName::PAN_GESTURE, false);
    std::shared_ptr<BaseGestureEvent> info = nullptr;
    gestureInfo->type_ = GestureTypeName::BOXSELECT;
    gestureInfo->inputEventType_ = InputEventType::MOUSE_BUTTON;
    auto ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo, info);
    EXPECT_EQ(ret, GestureJudgeResult::REJECT);

    gestureInfo->type_ = GestureTypeName::TEXTFIELD_BOXSELECT;
    gestureInfo->inputEventType_ = InputEventType::TOUCH_SCREEN;
    pattern_->moveCaretState_.isMoveCaret = true;
    ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo, info);
    EXPECT_EQ(ret, GestureJudgeResult::CONTINUE);

    gestureInfo->type_ = GestureTypeName::TEXTFIELD_BOXSELECT;
    gestureInfo->inputEventType_ = InputEventType::TOUCH_PAD;
    ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo, info);
    EXPECT_EQ(ret, GestureJudgeResult::REJECT);

    host->draggable_ = true;
    pattern_->isPressSelectedBox_ = true;
    gestureInfo->type_ = GestureTypeName::TEXTFIELD_BOXSELECT;
    gestureInfo->inputEventType_ = InputEventType::MOUSE_BUTTON;
    ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo, info);
    EXPECT_EQ(ret, GestureJudgeResult::REJECT);

    gestureInfo->type_ = GestureTypeName::UNKNOWN;
    gestureInfo->inputEventType_ = InputEventType::KEYBOARD;
    ret = gestureHub->gestureJudgeNativeFunc_(gestureInfo, info);
    EXPECT_EQ(ret, GestureJudgeResult::CONTINUE);
}

/**
 * @tc.name: UpdatePressStyle001
 * @tc.desc: test UpdatePressStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, UpdatePressStyle001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->hoverAndPressBgColorEnabled_ = true;
    pattern_->UpdatePressStyle(true);
    auto theme = pattern_->GetTheme();
    EXPECT_NE(theme->GetBgColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: ChangeMouseState001
 * @tc.desc: test ChangeMouseState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ChangeMouseState001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    Offset location;
    int32_t frameId = 0;
    location.deltaX_ = 1;
    location.deltaY_ = 1;
    pattern_->frameRect_.height_ = 2;
    pattern_->frameRect_.width_ = 2;
    pattern_->ChangeMouseState(location, frameId);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);

    layoutProperty->layoutDirection_ = TextDirection::RTL;
    pattern_->ChangeMouseState(location, frameId);
    EXPECT_EQ(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleMouseEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    MouseInfo info;
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF, ShapeMode::DEFAULT);
    pattern_->scrollBar_->isPressed_ = true;
    pattern_->HandleMouseEvent(info);
    EXPECT_TRUE(pattern_->scrollBar_->isPressed_);

    pattern_->scrollBar_ = nullptr;
    info.button_ = MouseButton::LEFT_BUTTON;
    pattern_->selectController_->firstHandleInfo_.index = 1;
    pattern_->selectController_->secondHandleInfo_.index = 2;
    pattern_->HandleMouseEvent(info);
    EXPECT_TRUE(pattern_->IsSelected());
}

/**
 * @tc.name: HandleRightMousePressEvent001
 * @tc.desc: test HandleRightMousePressEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleRightMousePressEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    MouseInfo info;
    pattern_->selectController_->firstHandleInfo_.index = 1;
    pattern_->selectController_->secondHandleInfo_.index = 1;
    pattern_->hasPreviewText_ = false;
    auto focusHub = pattern_->GetFocusHub();
    focusHub->focusType_ = FocusType::DISABLE;
    pattern_->HandleRightMousePressEvent(info);
    EXPECT_FALSE(focusHub->IsFocusable());
}

/**
 * @tc.name: HandleLeftMousePressEvent001
 * @tc.desc: test HandleLeftMousePressEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleLeftMousePressEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    MouseInfo info;
    pattern_->hasPreviewText_ = true;
    pattern_->HandleLeftMousePressEvent(info);
    EXPECT_TRUE(pattern_->blockPress_);

    pattern_->hasPreviewText_ = false;
    auto focusHub = pattern_->GetFocusHub();
    focusHub->focusType_ = FocusType::DISABLE;
    pattern_->HandleLeftMousePressEvent(info);
    EXPECT_TRUE(pattern_->blockPress_);
}

/**
 * @tc.name: HandleLeftMouseReleaseEvent001
 * @tc.desc: test HandleLeftMouseReleaseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleLeftMouseReleaseEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    MouseInfo info;
    pattern_->blockPress_ = false;
    pattern_->showKeyBoardOnFocus_ = true;
    pattern_->showKeyBoardOnFocus_ = true;
    auto host = pattern_->GetHost();
    auto focusHub = host->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;
    pattern_->customKeyboard_ = nullptr;
    pattern_->customKeyboardBuilder_ = nullptr;
    auto client = AceType::MakeRefPtr<MockTextInputClient>();
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    pattern_->connection_ = AceType::MakeRefPtr<MockTextInputConnection>(client, taskExecutor);
    pattern_->imeShown_ = true;
    pattern_->HandleLeftMouseReleaseEvent(info);
    EXPECT_TRUE(pattern_->RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::MOUSE_RELEASE));
}

/**
 * @tc.name: RequestKeyboard001
 * @tc.desc: test RequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, RequestKeyboard001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    bool forceClose = true;
    bool isStopTwinkling = true;
    auto client = AceType::MakeRefPtr<MockTextInputClient>();
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    pattern_->connection_ = AceType::MakeRefPtr<MockTextInputConnection>(client, taskExecutor);
    pattern_->imeShown_ = true;
    pattern_->CloseKeyboard(forceClose, isStopTwinkling);
    EXPECT_EQ(pattern_->connection_, nullptr);
}

/**
 * @tc.name: RequestCustomKeyboard001
 * @tc.desc: test RequestCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, RequestCustomKeyboard001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto client = AceType::MakeRefPtr<MockTextInputClient>();
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    pattern_->connection_ = AceType::MakeRefPtr<MockTextInputConnection>(client, taskExecutor);
    pattern_->imeShown_ = true;
    pattern_->customKeyboard_ = AceType::DynamicCast<NG::UINode>(
        AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    pattern_->customKeyboardBuilder_ = nullptr;
    pattern_->selectController_->caretInfo_.rect.height_ = 1;
    pattern_->selectController_->caretInfo_.rect.y_ = 2;
    pattern_->RequestCustomKeyboard();
    EXPECT_EQ(pattern_->connection_, nullptr);
}

/**
 * @tc.name: InsertValueByController001
 * @tc.desc: test InsertValueByController
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, InsertValueByController001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::u16string insertValue = u"test";
    int32_t offset = 0;
    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->SetOnWillChangeEvent(func);
    auto ret = pattern_->InsertValueByController(insertValue, offset);
    EXPECT_FALSE(ret);

    auto func1 = [](const ChangeValueInfo& info) {
        return true;
    };
    eventHub->SetOnWillChangeEvent(func1);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLength(123);
    ret = pattern_->InsertValueByController(insertValue, offset);
    EXPECT_EQ(pattern_->focusIndex_, FocuseIndex::TEXT);
}

/**
 * @tc.name: ExecuteInsertValueCommand001
 * @tc.desc: test ExecuteInsertValueCommand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ExecuteInsertValueCommand001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto eventHub = pattern_->GetHost()->GetOrCreateEventHub<TextFieldEventHub>();
    auto state = false;
    auto callback = [&state](const InsertValueInfo&){ return (state = true); };
    eventHub->SetOnWillInsertValueEvent(callback);
    pattern_->selectController_->firstHandleInfo_.index = 0;
    pattern_->selectController_->secondHandleInfo_.index = 0;
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLength(123);
    InsertCommandInfo info;
    info.insertValue = u"";
    info.reason = InputReason::IME;
    pattern_->ExecuteInsertValueCommand(info);
    EXPECT_TRUE(state);

    pattern_->selectController_->firstHandleInfo_.index = 1;
    pattern_->selectController_->secondHandleInfo_.index = 2;
    auto func = [&state](const ChangeValueInfo&){ return (state = false); };
    eventHub->SetOnWillChangeEvent(func);
    info.reason = InputReason::PASTE;
    pattern_->ExecuteInsertValueCommand(info);
    EXPECT_FALSE(state);
}

/**
 * @tc.name: PreferredTextHeight001
 * @tc.desc: test PreferredTextHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, PreferredTextHeight001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    bool isPlaceholder = true;
    bool isAlgorithmMeasure = true;
    Dimension offset = Dimension(-10000.0, DimensionUnit::PX);
    pattern_->adaptFontSize_ = offset;
    offset = Dimension(-10.0, DimensionUnit::VP);
    auto textFieldTheme = pattern_->GetTheme();
    textFieldTheme->fontSize_ = offset;
    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdatePlaceholderMaxLines(-1);
    auto layoutProperty1 = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty1->UpdateTextInputType(TextInputType::UNSPECIFIED);
    pattern_->PreferredTextHeight(isPlaceholder, isAlgorithmMeasure);
    EXPECT_TRUE(pattern_->adaptFontSize_.has_value());
}

/**
 * @tc.name: GetWordLength001
 * @tc.desc: test GetWordLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, GetWordLength001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    int32_t originCaretPosition = 1;
    int32_t directionMove = 0;
    bool skipNewLineChar = true;
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    pattern_->contentController_->content_ = u"   ";
    pattern_->GetWordLength(originCaretPosition, directionMove, skipNewLineChar);
    EXPECT_FALSE(pattern_->contentController_->IsEmpty());
}

/**
 * @tc.name: CursorMoveToParagraphEnd001
 * @tc.desc: test CursorMoveToParagraphEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, CursorMoveToParagraphEnd001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->selectController_->caretInfo_.index = 2;
    pattern_->contentController_->content_ = u" ";
    auto ret = pattern_->CursorMoveToParagraphEnd();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CursorMoveDownOperation001
 * @tc.desc: test CursorMoveDownOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, CursorMoveDownOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLines(2);
    pattern_->selectController_->firstHandleInfo_.index = 0;
    pattern_->selectController_->secondHandleInfo_.index = 0;
    auto ret = pattern_->CursorMoveDownOperation();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleCounterBorder001
 * @tc.desc: test HandleCounterBorder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleCounterBorder001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateShowUnderline(true);
    auto tmpHost = pattern_->GetHost();
    auto layoutProperty1 = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty1->UpdateTextInputType(TextInputType::UNSPECIFIED);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->HandleCounterBorder();
    EXPECT_FALSE(pattern_->showCountBorderStyle_);

    pattern_->showCountBorderStyle_ = true;
    layoutProperty->UpdateShowUnderline(false);
    BorderWidthProperty borderWidthProperty;
    paintProperty->UpdateBorderWidthFlagByUser(borderWidthProperty);
    pattern_->HandleCounterBorder();
    EXPECT_FALSE(layoutProperty->GetShowUnderlineValue(false));
}

/**
 * @tc.name: PerformAction001
 * @tc.desc: test PerformAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, PerformAction001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    TextInputAction action = TextInputAction::NEW_LINE;
    bool forceCloseKeyboard = true;
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLines(3);
    pattern_->textAreaBlurOnSubmit_ = true;
    pattern_->PerformAction(action, forceCloseKeyboard);
    EXPECT_TRUE(pattern_->IsTextArea());
}

/**
 * @tc.name: InitSurfaceChangedCallback001
 * @tc.desc: test InitSurfaceChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, InitSurfaceChangedCallback001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED;
    std::optional<int32_t> temp;
    pattern_->surfaceChangedCallbackId_ = temp;
    pattern_->InitSurfaceChangedCallback();
    auto host = pattern_->GetHost();
    auto pipeline = host->GetContext();
    int32_t id = *pattern_->surfaceChangedCallbackId_;
    pipeline->surfaceChangedCallbackMap_[id](1, 2, 3, 4, type);
    EXPECT_NE(pattern_->surfaceChangedCallbackId_, 0);
}

/**
 * @tc.name: InitSurfacePositionChangedCallback001
 * @tc.desc: test InitSurfacePositionChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, InitSurfacePositionChangedCallback001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::optional<int32_t> temp;
    pattern_->surfacePositionChangedCallbackId_ = temp;
    pattern_->InitSurfacePositionChangedCallback();
    auto host = pattern_->GetHost();
    auto pipeline = host->GetContext();
    int32_t id = *pattern_->surfacePositionChangedCallbackId_;
    pipeline->surfacePositionChangedCallbackMap_[id](1, 2);
    EXPECT_NE(pattern_->surfacePositionChangedCallbackId_, 0);
}

/**
 * @tc.name: DeleteBackwardWord001
 * @tc.desc: test DeleteBackwardWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, DeleteBackwardWord001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->selectController_->caretInfo_.index = -1;
    pattern_->contentController_->content_ = u" ";
    pattern_->DeleteBackwardWord();
    EXPECT_NE(pattern_->contentController_->GetTextUtf16Value().length(), 0);
}

/**
 * @tc.name: DeleteForwardWord001
 * @tc.desc: test DeleteForwardWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, DeleteForwardWord001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->selectController_->caretInfo_.index = 2;
    pattern_->contentController_->content_ = u" ";
    pattern_->DeleteForwardWord();
    EXPECT_NE(pattern_->contentController_->GetTextUtf16Value().length(), 0);
}

/**
 * @tc.name: HandleOnPageUp001
 * @tc.desc: test HandleOnPageUp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleOnPageUp001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLines(3);
    pattern_->HandleOnPageUp();
    EXPECT_NE(layoutProperty->HasMaxLines(), 0);
}

/**
 * @tc.name: HandleOnPageDown001
 * @tc.desc: test HandleOnPageDown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleOnPageDown001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLines(3);
    pattern_->HandleOnPageDown();
    EXPECT_TRUE(pattern_->IsTextArea());
}

/**
 * @tc.name: DeleteForwardOperation001
 * @tc.desc: test DeleteForwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, DeleteForwardOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo&) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    int32_t length = 1;
    pattern_->DeleteForwardOperation(length);
    ChangeValueInfo changeValueInfo;
    EXPECT_FALSE(eventHub->FireOnWillChangeEvent(changeValueInfo));
}

/**
 * @tc.name: HandleSelectionLineEnd001
 * @tc.desc: test HandleSelectionLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, HandleSelectionLineEnd001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->contentController_->content_ = u"Test";
    pattern_->selectController_->firstHandleInfo_.index = 1;
    pattern_->selectController_->secondHandleInfo_.index = 2;
    pattern_->HandleSelectionLineEnd();
    EXPECT_TRUE(pattern_->IsSelected());

    pattern_->selectController_->caretInfo_.index = 1;
    pattern_->HandleSelectionLineEnd();
    EXPECT_FALSE(pattern_->IsSelected());
}

/**
 * @tc.name: GetMaxLines001
 * @tc.desc: test GetMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, GetMaxLines001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    auto& groupProperty = layoutProperty->GetTextLineStyle();
    std::optional<uint32_t> temp;
    groupProperty->propMaxLines = temp;
    pattern_->GetMaxLines();
    EXPECT_FALSE(layoutProperty->HasMaxLines());
}

/**
 * @tc.name: ProcessInlinePaddingAndMargin001
 * @tc.desc: test ProcessInlinePaddingAndMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ProcessInlinePaddingAndMargin001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    PaddingProperty paddingProperty { .top = CalcLength(300), .bottom = CalcLength(300) };
    paintProperty->UpdatePaddingByUser(paddingProperty);
    MarginProperty margin = { CalcLength(1), CalcLength(3), CalcLength(5), CalcLength(7) };
    paintProperty->UpdateMarginByUser(margin);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::CLIP);
    pattern_->ProcessInlinePaddingAndMargin();
    EXPECT_TRUE(layoutProperty->HasTextOverflow());
}

/**
 * @tc.name: ApplyInlineTheme001
 * @tc.desc: test ApplyInlineTheme
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ApplyInlineTheme001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    pattern_->ApplyInlineTheme();
    EXPECT_EQ(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: SetAccessibilityMoveTextAction001
 * @tc.desc: test SetAccessibilityMoveTextAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, SetAccessibilityMoveTextAction001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    pattern_->SetAccessibilityMoveTextAction();
    int32_t moveUnit = 0;
    bool forward = true;
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    pattern_->contentController_->content_ = u"";
    accessibilityProperty->actionMoveTextImpl_(moveUnit, forward);
    EXPECT_TRUE(pattern_->contentController_->IsEmpty());
}

/**
 * @tc.name: NotifyFillRequestSuccess001
 * @tc.desc: test NotifyFillRequestSuccess
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, NotifyFillRequestSuccess001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    RefPtr<ViewDataWrap> viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    RefPtr<PageNodeInfoWrap> nodeWrap = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    AceAutoFillType autoFillType = AceAutoFillType::ACE_UNSPECIFIED;
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    pattern_->contentController_->content_ = u"test";
    auto host = pattern_->GetHost();
    auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo&) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    pattern_->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, autoFillType);
    ChangeValueInfo info;
    EXPECT_FALSE(eventHub->FireOnWillChangeEvent(info));
}

/**
 * @tc.name: IsReachedBoundary001
 * @tc.desc: test IsReachedBoundary
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, IsReachedBoundary001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLines(3);
    float offset = 0.1f;
    pattern_->IsReachedBoundary(offset);
    EXPECT_TRUE(layoutProperty->HasMaxLines());
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: test OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, OnAttachToFrameNode001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto frameNode = pattern_->GetHost();
    auto pipeline = frameNode->GetContext();
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    pattern_->OnAttachToFrameNode();
    EXPECT_NE(pipeline->GetFontManager(), nullptr);
}

/**
 * @tc.name: InitTheme001
 * @tc.desc: test InitTheme
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, InitTheme001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });

    auto frameNode = pattern_->GetHost();
    auto pipeline = frameNode->GetContext();
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();

    int32_t lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_NINE));

    pattern_->InitTheme();

    auto theme = pattern_->GetTheme();
    EXPECT_NE(theme, nullptr);
    EXPECT_NE(pattern_->needToRequestKeyboardOnFocus_, pattern_->independentControlKeyboard_);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
}

/**
 * @tc.name: ProcessCancelButton001
 * @tc.desc: test ProcessCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ProcessCancelButton001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    auto tmpHost = pattern_->GetHost();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLines(1);
    layoutProperty->UpdateIsShowCancelButton(true);
    RefPtr<TextInputResponseArea> responseArea = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern_);
    pattern_->cleanNodeResponseArea_ = AceType::DynamicCast<CleanNodeResponseArea>(responseArea);
    pattern_->ProcessCancelButton();
    EXPECT_TRUE(pattern_->cleanNodeResponseArea_);
}

/**
 * @tc.name: ProcessResponseArea001
 * @tc.desc: test ProcessResponseArea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ProcessResponseArea001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    layoutProperty->UpdateShowPasswordIcon(false);

    pattern_->ProcessResponseArea();
    EXPECT_FALSE(pattern_->IsShowPasswordIcon());

    RefPtr<TextInputResponseArea> responseArea = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern_);
    pattern_->responseArea_ = AceType::DynamicCast<PasswordResponseArea>(responseArea);
    layoutProperty->UpdateShowPasswordIcon(false);
    pattern_->ProcessResponseArea();
    EXPECT_FALSE(pattern_->IsShowPasswordIcon());
}

/**
 * @tc.name: GetInnerFocusPaintRect001
 * @tc.desc: test GetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, GetInnerFocusPaintRect001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    RoundRect paintRect;
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    RefPtr<TextInputResponseArea> responseArea = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern_);
    pattern_->cleanNodeResponseArea_ = AceType::DynamicCast<CleanNodeResponseArea>(responseArea);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(20020);
    auto container = Container::Current();
    container->apiTargetVersion_ = 20;
    pattern_->GetInnerFocusPaintRect(paintRect);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));
}

/**
 * @tc.name: ScrollToSafeArea001
 * @tc.desc: test ScrollToSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ScrollToSafeArea001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto pipeline = host->GetContext();
    pipeline->safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET_WITH_CARET;
    pattern_->ScrollToSafeArea();
    EXPECT_TRUE(pipeline->UsingCaretAvoidMode());
}

/**
 * @tc.name: TextFieldPattern Handle keyEvent.
 * @tc.desc: test ConvertCodeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestEight, ConvertCodeToString, TestSize.Level0)
{
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A };
    EXPECT_EQ(event.ConvertCodeToString(), "A");
    event.pressedCodes = { KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_A };
    EXPECT_EQ(event.ConvertCodeToString(), "A");
    event.enableCapsLock = true;
    EXPECT_EQ(event.ConvertCodeToString(), "a");
}
} // namespace OHOS::Ace::NG,