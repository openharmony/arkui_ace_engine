/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_container.h"
#include "frameworks/core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {

namespace {
const int32_t TWO = 2;
const int32_t FIVE = 5;
constexpr FrameNodeChangeInfoFlag AVOID_KEYBOARD_END_FALG = 1<<8;
} // namespace

class TextFieldPatternFuncTest : public TextInputBases {
public:
};

Rect MyGetTextContentRect()
{
    return { TWO, TWO, TWO, TWO };
}

int32_t MyGetTextContentLinesNum()
{
    return FIVE;
}

int32_t MyGetCaretIndex()
{
    return FIVE;
}

NG::OffsetF MyGetCaretPosition()
{
    return OffsetF(FIVE, FIVE);
}

/**
 * @tc.name: TextPatternFunc078
 * @tc.desc: test TriggerCustomKeyboardAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc078, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    textFieldManager->usingCustomKeyboardAvoid_ = true;
    pattern->isCustomKeyboardAttached_ = true;
    pattern->selectController_->caretInfo_.rect.SetRect(0.0f, 5.0f, 0.0f, 1.0f);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboardFst);
    auto host = pattern->GetHost();
    auto nodeId = host->GetId();
    pattern->keyboardOverlay_->customKeyboardMap_.emplace(std::make_pair(nodeId, AceType::RawPtr(keyboardScd)));
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->TriggerCustomKeyboardAvoid();
    EXPECT_EQ(keyboardScd->GetPattern<KeyboardPattern>()->safeHeight_, 1);
}

/**
 * @tc.name: TextPatternFunc079
 * @tc.desc: test TriggerCustomKeyboardAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc079, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    textFieldManager->usingCustomKeyboardAvoid_ = true;
    pattern->isCustomKeyboardAttached_ = true;
    pattern->selectController_->caretInfo_.rect.SetRect(0.0f, -2.0f, 0.0f, 5.0f);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboardFst);
    auto host = pattern->GetHost();
    auto nodeId = host->GetId();
    pattern->keyboardOverlay_->customKeyboardMap_.emplace(std::make_pair(nodeId, AceType::RawPtr(keyboardScd)));
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->TriggerCustomKeyboardAvoid();
    EXPECT_EQ(keyboardScd->GetPattern<KeyboardPattern>()->safeHeight_, 3);
}

/**
 * @tc.name: TextPatternFunc080
 * @tc.desc: test TriggerAvoidOnCaretChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc080, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    textFieldManager->usingCustomKeyboardAvoid_ = true;
    pattern->isCustomKeyboardAttached_ = true;
    pattern->selectController_->caretInfo_.rect.SetRect(0.0f, -2.0f, 0.0f, 5.0f);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboardFst);
    auto host = pattern->GetHost();
    auto nodeId = host->GetId();
    pattern->keyboardOverlay_->customKeyboardMap_.emplace(std::make_pair(nodeId, AceType::RawPtr(keyboardScd)));
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->TriggerAvoidOnCaretChange();
    EXPECT_EQ(keyboardScd->GetPattern<KeyboardPattern>()->safeHeight_, 0);
}

/**
 * @tc.name: TextPatternFunc081
 * @tc.desc: test SetClickPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc081, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    MockContainer::SetUp();
    RefPtr<UINode> element = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode));
    ASSERT_NE(element, nullptr);
    element->tag_ = "Panel";
    textFieldNode->SetParent(element, false);
    Offset menuOffset(960, 1660);
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->SetClickPosition(menuOffset);
    EXPECT_NE(textFieldManager->position_, menuOffset);
}

/**
 * @tc.name: TextPatternFunc082
 * @tc.desc: test SetClickPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc082, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    MockContainer::SetUp();
    RefPtr<UINode> element = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode));
    ASSERT_NE(element, nullptr);
    element->tag_ = "SheetPage";
    textFieldNode->SetParent(element, false);
    Offset menuOffset(960, 0.0f);
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->SetClickPosition(menuOffset);
    EXPECT_NE(textFieldManager->position_, menuOffset);
}

/**
 * @tc.name: TextPatternFunc083
 * @tc.desc: test SetClickPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc083, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    MockContainer::SetUp();
    Offset menuOffset(-1.0f, 100);
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->SetClickPosition(menuOffset);
    EXPECT_NE(textFieldManager->optionalPosition_, menuOffset);
}

/**
 * @tc.name: TextPatternFunc084
 * @tc.desc: test SetClickPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc084, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    MockContainer::SetUp();
    Offset menuOffset(960, 100);
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->SetClickPosition(menuOffset);
    EXPECT_NE(textFieldManager->optionalPosition_, menuOffset);
}

/**
 * @tc.name: TextPatternFunc085
 * @tc.desc: test GetKeyboardHeight.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc085, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    auto result = pattern->GetKeyboardHeight();
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: TextPatternFunc086
 * @tc.desc: test SetKeyboardAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc086, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<UINode> element = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode));
    keyboard->children_.emplace_back(element);
    RefPtr<SafeAreaManager> safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    safeAreaManager->SetRawKeyboardHeight(5.0f);
    auto pipeline = pattern->GetHost()->GetContext();
    pipeline->safeAreaManager_ = safeAreaManager;
    pattern->SetKeyboardAreaChange(true);
    EXPECT_EQ(pipeline->safeAreaManager_->GetRawKeyboardHeight(), 0.0f);
}

/**
 * @tc.name: TextPatternFunc088
 * @tc.desc: test SetKeyboardAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc088, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<SafeAreaManager> safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    safeAreaManager->SetRawKeyboardHeight(5.0f);
    auto pipeline = pattern->GetHost()->GetContext();
    pipeline->safeAreaManager_ = safeAreaManager;
    pattern->SetKeyboardAreaChange(false);
    EXPECT_EQ(pipeline->safeAreaManager_->GetRawKeyboardHeight(), 5.0f);
}

/**
 * @tc.name: KeyboardPatternFunc01
 * @tc.desc: test KeyboardPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, KeyboardPatternFunc01, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->BeforeCreateLayoutWrapper();
    pattern->DumpInfo();
    auto spanNode = AceType::MakeRefPtr<NG::SpanNode>(3);
    keyboard->AddChild(spanNode);
    pattern->BeforeCreateLayoutWrapper();
    pattern->GetKeyboardHeight();
    JsonValue jsonValue(nullptr);
    std::unique_ptr<JsonValue> ret = jsonValue.GetChild();
    pattern->DumpInfo(ret);
    EXPECT_EQ(pattern->keyboardHeight_, 0.0f);
}

/**
 * @tc.name: TextPatternFunc089
 * @tc.desc: test OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc089, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetKeyboardOption(true);
    pattern->OnAreaChangedInner();
    EXPECT_EQ(pattern->keyboardHeight_, 0.0f);
}

/**
 * @tc.name: TextPatternFunc091
 * @tc.desc: test OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc091, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetKeyboardOption(true);
    pattern->keyboardHeight_ = 5.0f;
    pattern->OnAreaChangedInner();
    EXPECT_EQ(pattern->keyboardHeight_, 0.0f);
}

/**
 * @tc.name: TextPatternFunc092
 * @tc.desc: test SetOnWillChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc092, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto state = false;
    auto eventHub = pattern->GetHost()->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto callback = [&state](const ChangeValueInfo& info){ return (state = true); };
    eventHub->SetOnWillChangeEvent(callback);

    InsertCommandInfo info;
    info.insertValue = u"openharmony";
    info.reason = InputReason::IME;
    pattern->ExecuteInsertValueCommand(info);
    EXPECT_TRUE(state);
}

/**
 * @tc.name: TextPatternFunc093
 * @tc.desc: test HasOnWillInsertValueEvent/HasOnDidInsertValueEvent/HasOnWillDeleteValueEvent/HasOnDidDeleteValueEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc093, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. Check the return value when no event is set
     * @tc.expected: return value is false
     */
    EXPECT_TRUE(!eventHub_->HasOnDidInsertValueEvent());
    EXPECT_TRUE(!eventHub_->HasOnWillDeleteValueEvent());
    EXPECT_TRUE(!eventHub_->HasOnDidDeleteValueEvent());

    /**
     * @tc.steps: step3. set event
     */
    TextDeleteDirection direction = TextDeleteDirection::BACKWARD;
    int32_t willDeleteOffset = 0;
    std::string willDeleteValue = "";
    auto onWillDeleteChange = [&willDeleteOffset, &willDeleteValue, &direction](const DeleteValueInfo& info) {
        willDeleteOffset = info.deleteOffset;
        willDeleteValue = StringUtils::Str16ToStr8(info.deleteValue);
        direction = info.direction;
        return true;
    };
    eventHub_->SetOnWillDeleteEvent(std::move(onWillDeleteChange));

    int32_t didInsertOffset = 0;
    std::string didInsertValue = "";
    auto onDidInsertChange = [&didInsertOffset, &didInsertValue](const InsertValueInfo& info) {
        didInsertOffset = info.insertOffset;
        didInsertValue = StringUtils::Str16ToStr8(info.insertValue);
        return true;
    };
    eventHub_->SetOnDidInsertValueEvent(std::move(onDidInsertChange));

    TextDeleteDirection didDirection = TextDeleteDirection::BACKWARD;
    int32_t didDeleteOffset = 0;
    std::string didDeleteValue = "";
    auto onDidDeleteChange = [&didDeleteOffset, &didDeleteValue, &didDirection](const DeleteValueInfo& info) {
        didDeleteOffset = info.deleteOffset;
        didDeleteValue = StringUtils::Str16ToStr8(info.deleteValue);
        didDirection = info.direction;
        return true;
    };
    eventHub_->SetOnDidDeleteEvent(std::move(onDidDeleteChange));

    /**
     * @tc.steps: step4. Check the return value
     * @tc.expected: return value is true
     */
    EXPECT_TRUE(eventHub_->HasOnDidInsertValueEvent());
    EXPECT_TRUE(eventHub_->HasOnWillDeleteValueEvent());
    EXPECT_TRUE(eventHub_->HasOnDidDeleteValueEvent());
}

/**
 * @tc.name: GetTextContentRect001
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentRect001, TestSize.Level1)
{
    TextFieldController textFieldController;
    textFieldController.SetGetTextContentRect(MyGetTextContentRect);
    auto result = textFieldController.GetTextContentRect();
    EXPECT_EQ(result.GetOffset().GetX(), 2);
}

/**
 * @tc.name: GetTextContentRect002
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentRect002, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto result = textFieldController.GetTextContentRect();
    EXPECT_EQ(result.GetOffset().GetX(), 0);
}

/**
 * @tc.name: GetTextContentRect003
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentRect003, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto pattern_ = AceType::MakeRefPtr<TextFieldPattern>();
    pattern_->GetTextSelectController()->caretInfo_.rect.SetRect(1, 1, 1, 1);
    textFieldController.SetPattern(pattern_);
    auto result = textFieldController.GetTextContentRect();
    EXPECT_EQ(result.GetOffset().GetX(), 1);
}

/**
 * @tc.name: GetTextContentRect004
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentRect004, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto pattern_ = AceType::MakeRefPtr<TextFieldPattern>();
    pattern_->GetTextContentController()->SetTextValue(u"value");
    RectF textRect(3, 3, 3, 3);
    pattern_->SetTextRect(textRect);
    textFieldController.SetPattern(pattern_);
    auto result = textFieldController.GetTextContentRect();
    EXPECT_EQ(result.GetOffset().GetX(), 3);
}

/**
 * @tc.name: GetTextContentRect001
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentLinesNum001, TestSize.Level1)
{
    TextFieldController textFieldController;
    textFieldController.SetGetTextContentLinesNum(MyGetTextContentLinesNum);
    auto result = textFieldController.GetTextContentLinesNum();
    EXPECT_EQ(result, 5);
}

/**
 * @tc.name: GetCaretIndex001
 * @tc.desc: test GetCaretIndex.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetCaretIndex001, TestSize.Level1)
{
    TextFieldController textFieldController;
    textFieldController.SetGetCaretIndex(MyGetCaretIndex);
    auto result = textFieldController.GetCaretIndex();
    EXPECT_EQ(result, 5);
}

/**
 * @tc.name: GetCaretIndex002
 * @tc.desc: test GetCaretIndex.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetCaretIndex002, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto result = textFieldController.GetCaretIndex();
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GetCaretPosition001
 * @tc.desc: test GetCaretPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetCaretPosition001, TestSize.Level1)
{
    TextFieldController textFieldController;
    textFieldController.SetGetCaretPosition(MyGetCaretPosition);
    auto result = textFieldController.GetCaretPosition();
    EXPECT_EQ(result.GetX(), 5);
}

/**
 * @tc.name: GetCaretPosition002
 * @tc.desc: test GetCaretPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetCaretPosition002, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto result = textFieldController.GetCaretPosition();
    EXPECT_EQ(result.GetX(), -1);
}

/**
 * @tc.name: GetKeyboardAppearance001
 * @tc.desc: test SetKeyboardAppearance.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetKeyboardAppearance001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. check KeyboardAppearance's size and default value.
     */
    EXPECT_TRUE(pattern->GetKeyboardAppearance() == KeyboardAppearance::NONE_IMMERSIVE);
    /**
     * @tc.steps: step3. call SetKeyboardAppearance and use GetKeyboardAppearance to check
     */
    pattern->SetKeyboardAppearance(KeyboardAppearance::DARK_IMMERSIVE);
    EXPECT_TRUE(pattern->GetKeyboardAppearance() == KeyboardAppearance::DARK_IMMERSIVE);
    pattern->SetKeyboardAppearance(KeyboardAppearance::NONE_IMMERSIVE);
    EXPECT_TRUE(pattern->GetKeyboardAppearance() == KeyboardAppearance::NONE_IMMERSIVE);
}

/**
 * @tc.name: TextFieldSelectOverlay001
 * @tc.desc: test OnOverlayClick.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call OnOverlayClick and expect no error.
     */
    GestureEvent event;
    pattern->selectOverlay_->OnOverlayClick(event, true);
    pattern->selectOverlay_->isSingleHandle_ = true;
    pattern->selectOverlay_->OnOverlayClick(event, true);
    pattern->multipleClickRecognizer_ = pattern->GetOrCreateMultipleClickRecognizer();
    pattern->multipleClickRecognizer_->clickCountTask_.Reset([] {});
    pattern->selectOverlay_->OnOverlayClick(event, true);
    pattern->multipleClickRecognizer_->lastClickPosition_ = Offset(0.0f, 0.0f);
    event.SetGlobalLocation(Offset(100.0f, 100.0f));
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    event.SetTimeStamp(timeStampAce);
    pattern->multipleClickRecognizer_->lastClickTimeStamp_ = TimeStamp(std::chrono::nanoseconds(0));
    pattern->selectOverlay_->OnOverlayClick(event, true);
}

/**
 * @tc.name: TextFieldSelectOverlay002
 * @tc.desc: test OnHandleMoveStart.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call OnHandleMoveStart and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->isSingleHandle_ = true;
    GestureEvent event;
    pattern->selectOverlay_->OnHandleMoveStart(event, true);
    pattern->contentController_->content_ = u"";
    pattern->selectOverlay_->OnHandleMoveStart(event, true);
    EXPECT_FALSE(pattern->contentScroller_.isScrolling);
}

/**
 * @tc.name: TextFieldSelectOverlay003
 * @tc.desc: test AllowTranslate.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call AllowTranslate and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto layoutProperty = textFieldNode->GetLayoutPropertyPtr<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    EXPECT_FALSE(pattern->selectOverlay_->AllowTranslate());
    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    layoutProperty->UpdateTextInputType(TextInputType::NEW_PASSWORD);
    EXPECT_FALSE(pattern->selectOverlay_->AllowTranslate());
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    EXPECT_TRUE(pattern->selectOverlay_->AllowTranslate());
}

/**
 * @tc.name: TextFieldSelectOverlay004
 * @tc.desc: test AllowSearch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call AllowSearch and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto layoutProperty = textFieldNode->GetLayoutPropertyPtr<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    EXPECT_FALSE(pattern->selectOverlay_->AllowSearch());
    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    layoutProperty->UpdateTextInputType(TextInputType::NEW_PASSWORD);
    EXPECT_FALSE(pattern->selectOverlay_->AllowSearch());
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    EXPECT_TRUE(pattern->selectOverlay_->AllowSearch());
}

/**
 * @tc.name: TextFieldSelectOverlay005
 * @tc.desc: test GetHandleColor.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call GetHandleColor and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->ResetCursorColor();
    EXPECT_EQ(pattern->selectOverlay_->GetHandleColor(), std::nullopt);
    paintProperty->UpdateCursorColor(Color::GREEN);
    EXPECT_EQ(pattern->selectOverlay_->GetHandleColor(), Color::GREEN);
    pattern->selectOverlay_->hostTextBase_.Reset();
    EXPECT_EQ(pattern->selectOverlay_->GetHandleColor(), std::nullopt);
}

/**
 * @tc.name: TextFieldSelectOverlay006
 * @tc.desc: test UpdateAllHandlesOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call UpdateAllHandlesOffset and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    pattern->selectOverlay_->dragHandleIndex_ = DragHandleIndex::NONE;
    pattern->selectOverlay_->UpdateAllHandlesOffset();
    pattern->selectOverlay_->dragHandleIndex_ = DragHandleIndex::FIRST;
    pattern->selectOverlay_->UpdateAllHandlesOffset();
    pattern->selectOverlay_->dragHandleIndex_ = DragHandleIndex::SECOND;
    pattern->selectOverlay_->UpdateAllHandlesOffset();
}

/**
 * @tc.name: BaseTextSelectOverlay000
 * @tc.desc: test base_text_select_overlay.cpp ToggleMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay000, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ToggleMenu and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->ToggleMenu();
    EXPECT_NE(pattern->selectOverlay_->GetManager<SelectContentOverlayManager>(), nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay001
 * @tc.desc: test base_text_select_overlay.cpp DisableMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call DisableMenu and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->DisableMenu();
    EXPECT_NE(pattern->selectOverlay_->GetManager<SelectContentOverlayManager>(), nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay002
 * @tc.desc: test base_text_select_overlay.cpp OnHandleGlobalTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call OnHandleGlobalTouchEvent and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto sourceType = SourceType::MOUSE;
    auto touchType = TouchType::DOWN;
    pattern->selectOverlay_->OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_EQ(pattern->selectOverlay_->IsMouseClickDown(sourceType, touchType), true);
}

/**
 * @tc.name: BaseTextSelectOverlay003
 * @tc.desc: test base_text_select_overlay.cpp CheckTouchInHostNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call CheckTouchInHostNode and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    PointF point;
    pattern->selectOverlay_->CheckTouchInHostNode(point);
    EXPECT_NE(pattern->selectOverlay_->GetOwner(), nullptr);
    EXPECT_NE(pattern->selectOverlay_->GetOwner()->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay004
 * @tc.desc: test base_text_select_overlay.cpp OnUpdateSelectOverlayInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call OnUpdateSelectOverlayInfo and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->hasTransform_ = true;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    pattern->selectOverlay_->hasTransform_ = false;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay005
 * @tc.desc: test base_text_select_overlay.cpp RemoveSelectionHoldCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call RemoveSelectionHoldCallback and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->RemoveSelectionHoldCallback();
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}
 
/**
 * @tc.name: BaseTextSelectOverlay006
 * @tc.desc: test base_text_select_overlay.cpp GetVisibleContentRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call GetVisibleContentRect and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->enableHandleLevel_ = true;
    pattern->selectOverlay_->handleLevelMode_ = HandleLevelMode::EMBED;
    pattern->selectOverlay_->GetVisibleContentRect(false);
    EXPECT_NE(pattern->selectOverlay_->GetPattern<Pattern>(), nullptr);
    EXPECT_NE(pattern->selectOverlay_->GetPattern<Pattern>()->GetHost(), nullptr);
    EXPECT_NE(pattern->selectOverlay_->GetPattern<Pattern>()->GetHost()->GetContext(), nullptr);
    EXPECT_NE(pattern->selectOverlay_->GetPattern<Pattern>()->GetHost()->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay007
 * @tc.desc: test base_text_select_overlay.cpp MergeSelectedBoxes
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call MergeSelectedBoxes and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    std::vector<RectF> boxes;
    RectF contentRect(1.0f, 2.0f, 3.0f, 4.0f);
    RectF textRect(1.0f, 2.0f, 3.0f, 4.0f);
    OffsetF paintOffset(0.0f, 0.0f);
    auto rect = pattern->selectOverlay_->MergeSelectedBoxes(boxes, contentRect, textRect, paintOffset);
    EXPECT_EQ(rect.GetX(), 0);
    EXPECT_EQ(rect.GetY(), 0);
}
 
/**
 * @tc.name: BaseTextSelectOverlay008
 * @tc.desc: test base_text_select_overlay.cpp GetLocalPointWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call GetLocalPointWithTransform and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    OffsetF localOffset(0.0f, 0.0f);
    pattern->selectOverlay_->hasTransform_ = false;
    pattern->selectOverlay_->GetLocalPointWithTransform(localOffset);
    pattern->selectOverlay_->hasTransform_ = true;
    pattern->selectOverlay_->GetLocalPointWithTransform(localOffset);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay009
 * @tc.desc: test base_text_select_overlay.cpp ConvertPaintInfoToRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ConvertPaintInfoToRect and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    SelectHandlePaintInfo paintInfo;
    auto rect = pattern->selectOverlay_->ConvertPaintInfoToRect(paintInfo);
    EXPECT_EQ(rect.GetX(), 0);
    EXPECT_EQ(rect.GetY(), 0);
}

/**
 * @tc.name: BaseTextSelectOverlay010
 * @tc.desc: test base_text_select_overlay.cpp GetHandleLocalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call GetHandleLocalPaintRect and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    DragHandleIndex dragHandleIndex = DragHandleIndex::FIRST;
    auto rect = pattern->selectOverlay_->GetHandleLocalPaintRect(dragHandleIndex);
    EXPECT_EQ(rect.GetX(), 0);
    EXPECT_EQ(rect.GetY(), 0);
}
 
/**
 * @tc.name: BaseTextSelectOverlay011
 * @tc.desc: test base_text_select_overlay.cpp UpdateMenuWhileAncestorNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateMenuWhileAncestorNodeChanged and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    bool shouldHideMenu = false;
    bool shouldShowMenu = false;
    FrameNodeChangeInfoFlag extraFlag = AVOID_KEYBOARD_END_FALG;
    pattern->selectOverlay_->UpdateMenuWhileAncestorNodeChanged(shouldHideMenu, shouldShowMenu, extraFlag);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}
 
/**
 * @tc.name: BaseTextSelectOverlay012
 * @tc.desc: test base_text_select_overlay.cpp RegisterScrollingListener
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call RegisterScrollingListener and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->hasRegisterListener_ = true;
    pattern->selectOverlay_->RegisterScrollingListener(nullptr);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay013
 * @tc.desc: test base_text_select_overlay.cpp ConvertWindowToScreenDomain with Rect input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ConvertWindowToScreenDomain and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    RectF inputRectf;
    auto outputRecf = pattern->selectOverlay_->ConvertWindowToScreenDomain(inputRectf);
    EXPECT_EQ(outputRecf.GetX(), 0);
    EXPECT_EQ(outputRecf.GetY(), 0);
}

/**
 * @tc.name: BaseTextSelectOverlay014
 * @tc.desc: test base_text_select_overlay.cpp ConvertWindowToScreenDomain with Edge input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ConvertWindowToScreenDomain and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    EdgeF edgeF;
    auto outputEdgeF = pattern->selectOverlay_->ConvertWindowToScreenDomain(edgeF);
    EXPECT_EQ(outputEdgeF.x, 0);
    EXPECT_EQ(outputEdgeF.y, 0);
}

/**
 * @tc.name: BaseTextSelectOverlay015
 * @tc.desc: test base_text_select_overlay.cpp GetTranslateParamRectStr
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call GetTranslateParamRectStr and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);

    RectF rectf1(1.0f, 2.0f, 3.0f, 4.0f);
    EdgeF edgeF1(0.0f, 0.0f);
    EdgeF edgeF2(0.0f, 0.0f);
    pattern->selectOverlay_->GetTranslateParamRectStr(rectf1, edgeF1, edgeF2);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay016
 * @tc.desc: test base_text_select_overlay.cpp IsHandleVisible
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call IsHandleVisible and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto isHandleVisible = pattern->selectOverlay_->IsHandleVisible(false);
    EXPECT_EQ(isHandleVisible, false);
}

/**
 * @tc.name: BaseTextSelectOverlay017
 * @tc.desc: test base_text_select_overlay.cpp SetTransformPaintInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call SetTransformPaintInfo and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    SelectHandleInfo handleInfo;
    RectF rect;
    pattern->selectOverlay_->hasTransform_ = true;
    pattern->selectOverlay_->SetTransformPaintInfo(handleInfo, rect);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: UpdateMagnifier
 * @tc.desc: test text_field_select_overlay.cpp UpdateMagnifier
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, UpdateMagnifier, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateMagnifier and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    pattern->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    ASSERT_NE(overlayNode, nullptr);
    overlayNode->MountToParent(textFieldNode);
    manager->selectOverlayNode_ = overlayNode;
    pattern->selectOverlay_->OnBind(manager);

    pattern->selectOverlay_->SetIsSingleHandle(true);
    pattern->selectController_->floatingCaretInfo_.rect = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->floatCaretState_.lastFloatingCursorY = 50.0f;
    pattern->contentScroller_.isScrolling = true;
    pattern->selectOverlay_->UpdateMagnifier(OffsetF(), false);

    EXPECT_EQ(pattern->magnifierController_->localOffset_, OffsetF());
    pattern->selectOverlay_->UpdateMagnifier(OffsetF(), true);
    EXPECT_EQ(pattern->magnifierController_->localOffset_, OffsetF(50.0f, 50.0f));
}

/**
 * @tc.name: CheckIfInterruptProcessing
 * @tc.desc: test text_field_select_overlay.cpp CheckIfInterruptProcessing
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, CheckIfInterruptProcessing, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateMagnifier and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    ASSERT_NE(overlayNode, nullptr);
    overlayNode->MountToParent(textFieldNode);
    manager->selectOverlayNode_ = overlayNode;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    pattern->selectOverlay_->OnBind(manager);

    auto ret = pattern->selectOverlay_->CheckIfInterruptProcessing({});
    EXPECT_FALSE(ret);
    pattern->selectOverlay_->SetUsingMouse(true);
    shareOverlayInfo->menuInfo.menuType = OptionMenuType::MOUSE_MENU;
    shareOverlayInfo->selectText = "";
    ret = pattern->selectOverlay_->CheckIfInterruptProcessing({ .requestCode = 1 << 2 });
    EXPECT_TRUE(ret);
    pattern->selectOverlay_->SetUsingMouse(false);
    pattern->selectOverlay_->ProcessOverlayAfterLayout({});
    EXPECT_TRUE(pattern->selectOverlay_->enableHandleLevel_);
}

/**
 * @tc.name: SelectOverlay Menu avoid keyboard.
 * @tc.desc: test GetKeyboardInsetImpl.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetKeyboardInsetImpl, TestSize.Level1)
{
    RefPtr<SafeAreaManager> safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::NONE;
    SafeAreaInsets::Inset inset = { .start = 1000, .end = 2000 };
    safeAreaManager->keyboardInset_ = inset;

    EXPECT_EQ(safeAreaManager->GetKeyboardInset().Length(), 0);
    EXPECT_EQ(safeAreaManager->GetKeyboardInsetImpl().Length(), 1000);
}

/**
 * @tc.name: OnHandleBeforeMenuVisibiltyChanged
 * @tc.desc: test text_field_select_overlay.cpp OnHandleBeforeMenuVisibiltyChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, OnHandleBeforeMenuVisibiltyChanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call OnHandleBeforeMenuVisibiltyChanged and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    shareOverlayInfo->isUseOverlayNG = true;
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    ASSERT_NE(overlayNode, nullptr);
    overlayNode->MountToParent(textFieldNode);
    manager->selectOverlayNode_ = overlayNode;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    pattern->selectOverlay_->OnBind(manager);
    manager->SetHolder(pattern->selectOverlay_);
    pattern->selectOverlay_->SetShowPaste(false);
    pattern->selectOverlay_->UpdatePasteMenu();
    EXPECT_TRUE(pattern->selectOverlay_->needRefreshPasteButton_);
    pattern->selectOverlay_->ShowMenu();
    EXPECT_FALSE(pattern->selectOverlay_->needRefreshPasteButton_);
}
} // namespace OHOS::Ace
