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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
template<>
RichEditorDeleteDirection Convert(const Ark_RichEditorDeleteDirection& src)
{
    RichEditorDeleteDirection dst;
    switch (src) {
        case ARK_RICH_EDITOR_DELETE_DIRECTION_BACKWARD:
            dst = RichEditorDeleteDirection::BACKWARD;
            break;
        case ARK_RICH_EDITOR_DELETE_DIRECTION_FORWARD:
            dst = RichEditorDeleteDirection::FORWARD;
            break;
        default:
            dst = RichEditorDeleteDirection::FORWARD;
            break;
    }
    return dst;
}
} // Converter

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
constexpr int32_t TEST_SELECTION_START = 1;
constexpr int32_t TEST_SELECTION_END = 2;
constexpr int32_t TEST_INSERT_OFFSET = 3;
constexpr auto TEST_INSERT_VALUE = "insert text";
constexpr auto TEST_PREVIEW_TEXT = "preview text";
constexpr auto TEST_TEXT = "just text";
constexpr int32_t TEST_SPAN_IDX = 4;
constexpr int32_t TEST_SPAN_START = 5;
constexpr int32_t TEST_SPAN_END = 6;
constexpr int32_t TEST_FONT_SIZE = 16;
constexpr int32_t TEST_FONT_WEIGHT = 17;
constexpr auto TEST_FONT_FAMILY = "Arial";
constexpr auto TEST_FONT_COLOR = "#FF112233";
constexpr int32_t TEST_START = 2;
constexpr int32_t TEST_END = 3;
constexpr int32_t TEST_OFFSET = 4;
constexpr int32_t TEST_LENGTH = 5;
constexpr auto TEST_DELETE_DIRECTION = RichEditorDeleteDirection::FORWARD;
constexpr bool TEST_IS_CHANGED_IN_EDITING = true;
constexpr Ark_EnterKeyType TEST_ENTER_KEY_TYPE = Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_NEXT;
constexpr int32_t TEST_RANGE_START = 6;
constexpr int32_t TEST_RANGE_END = 7;
constexpr int32_t TEST_RANGE_START_TWO = 8;
constexpr int32_t TEST_RANGE_END_TWO = 9;


using TEST_ID = void* const;
std::map<TEST_ID, bool> g_isCheckedMap;

template<typename T> void SetFlag(const T& id, bool flag = true)
{
    g_isCheckedMap[reinterpret_cast<TEST_ID>(id)] = flag;
}

template<typename T> bool GetFlag(const T& id)
{
    return g_isCheckedMap[reinterpret_cast<TEST_ID>(id)];
}

GENERATED_ArkUIRichEditorEventsReceiver recv;

void onReadyCallback(Ark_Int32 nodeId)
{
    SetFlag(recv.onReady);
}

void onSelectCallback(Ark_Int32 nodeId, const Ark_RichEditorSelection data)
{
    SetFlag(recv.onSelect, false);
    int32_t start = Converter::Convert<int32_t>(data.selection.value0);
    int32_t end = Converter::Convert<int32_t>(data.selection.value1);
    EXPECT_EQ(start, TEST_SELECTION_START);
    EXPECT_EQ(end, TEST_SELECTION_END);
    SetFlag(recv.onSelect);
}

void onSelectionChangeCallback(Ark_Int32 nodeId, const Ark_RichEditorRange data)
{
    SetFlag(recv.onSelectionChange, false);
    auto start = Converter::OptConvert<int32_t>(data.start);
    auto end = Converter::OptConvert<int32_t>(data.end);
    EXPECT_EQ(start.value(), TEST_SELECTION_START);
    EXPECT_EQ(end.value(), TEST_SELECTION_END);
    SetFlag(recv.onSelectionChange);
}

void onAboutToIMEInputCallback(Ark_Int32 nodeId, const Ark_RichEditorInsertValue data)
{
    SetFlag(recv.aboutToIMEInput, false);
    auto offset = Converter::Convert<int32_t>(data.insertOffset);
    auto text = Converter::Convert<std::string>(data.insertValue);
    auto previewText = Converter::OptConvert<std::string>(data.previewText);
    EXPECT_EQ(offset, TEST_INSERT_OFFSET);
    EXPECT_EQ(text, TEST_INSERT_VALUE);
    EXPECT_EQ(previewText.value(), TEST_PREVIEW_TEXT);
    SetFlag(recv.aboutToIMEInput);
}

void onIMEInputCompleteCallback(Ark_Int32 nodeId, const Ark_RichEditorTextSpanResult data)
{
    SetFlag(recv.onIMEInputComplete, false);
    auto text = Converter::Convert<std::string>(data.value);
    auto spanIndex = Converter::Convert<int32_t>(data.spanPosition.spanIndex);
    auto spanRangeStart = Converter::Convert<int32_t>(data.spanPosition.spanRange.value0);
    auto spanRangeEnd = Converter::Convert<int32_t>(data.spanPosition.spanRange.value1);
    auto fontSize = Converter::Convert<int32_t>(data.textStyle.fontSize);
    auto fontStyleSize = Converter::Convert<int32_t>(data.symbolSpanStyle.value.fontSize.value.value0);
    auto fontWeight = Converter::Convert<int32_t>(data.symbolSpanStyle.value.fontWeight.value.value0);
    auto fontColor = Converter::OptConvert<Color>(data.textStyle.fontColor).value();
    auto fontFamily = Converter::Convert<std::string>(data.textStyle.fontFamily);
    auto previewText = Converter::OptConvert<std::string>(data.previewText).value();

    EXPECT_EQ(spanIndex, TEST_SPAN_IDX);
    EXPECT_EQ(spanRangeStart, TEST_SPAN_START);
    EXPECT_EQ(spanRangeEnd, TEST_SPAN_END);
    EXPECT_EQ(text, TEST_TEXT);
    EXPECT_EQ(fontSize, TEST_FONT_SIZE);
    EXPECT_EQ(fontStyleSize, TEST_FONT_SIZE);
    EXPECT_EQ(fontWeight, TEST_FONT_WEIGHT);
    EXPECT_EQ(fontFamily, TEST_FONT_FAMILY);
    EXPECT_EQ(fontColor, Color::FromString(TEST_FONT_COLOR));
    EXPECT_EQ(previewText, TEST_PREVIEW_TEXT);

    SetFlag(recv.onIMEInputComplete);
}

void onDidIMEInputCallback(Ark_Int32 nodeId, const Ark_TextRange data)
{
    SetFlag(recv.onDidIMEInput, false);
    auto start = Converter::OptConvert<int32_t>(data.start).value();
    auto end = Converter::OptConvert<int32_t>(data.end).value();
    EXPECT_EQ(start, TEST_START);
    EXPECT_EQ(end, TEST_END);
    SetFlag(recv.onDidIMEInput);
}

void onAboutToDeleteCallback(Ark_Int32 nodeId, const Ark_RichEditorDeleteValue data)
{
    SetFlag(recv.aboutToDelete, false);
    auto offset = Converter::Convert<int32_t>(data.offset);
    auto length = Converter::Convert<int32_t>(data.length);
    auto direction = Converter::Convert<RichEditorDeleteDirection>(data.direction);
    EXPECT_EQ(offset, TEST_OFFSET);
    EXPECT_EQ(length, TEST_LENGTH);
    EXPECT_EQ(direction, TEST_DELETE_DIRECTION);
    SetFlag(recv.aboutToDelete);
}

void onDeleteCompleteCallback(Ark_Int32 nodeId)
{
    SetFlag(recv.onDeleteComplete);
}

void onPasteCallback(Ark_Int32 nodeId, const Opt_PasteEvent event)
{
    SetFlag(recv.onPaste);
}

void onEditingChangeCallback(Ark_Int32 nodeId, const Ark_Boolean data)
{
    SetFlag(recv.onEditingChange, false);
    auto flag = Converter::Convert<bool>(data);
    EXPECT_EQ(flag, TEST_IS_CHANGED_IN_EDITING);
    SetFlag(recv.onEditingChange);
}

void onSubmitCallback(Ark_Int32 nodeId,
                      const Ark_EnterKeyType enterKey,
                      const Ark_SubmitEvent event)
{
    SetFlag(recv.onSubmit, false);
    auto submitText = Converter::OptConvert<std::string>(event.text).value();
    EXPECT_EQ(submitText, TEST_TEXT);
    EXPECT_EQ(TEST_ENTER_KEY_TYPE, enterKey);
    SetFlag(recv.onSubmit);
}

void onWillChangeCallback(Ark_Int32 nodeId, const Ark_RichEditorChangeValue data)
{
    SetFlag(recv.onWillChange, false);
    auto rangeStart = Converter::OptConvert<int32_t>(data.rangeBefore.start).value();
    auto rangeEnd = Converter::OptConvert<int32_t>(data.rangeBefore.end).value();
    EXPECT_EQ(rangeStart, TEST_RANGE_START);
    EXPECT_EQ(rangeEnd, TEST_RANGE_END);
    SetFlag(recv.onWillChange);
}

void onDidChangeCallback(Ark_Int32 nodeId,
                         const Ark_TextRange rangeBefore,
                         const Ark_TextRange rangeAfter)
{
    SetFlag(recv.onDidChange, false);
    auto inBeforeStart = Converter::OptConvert<int32_t>(rangeBefore.start).value();
    auto inBeforeEnd = Converter::OptConvert<int32_t>(rangeBefore.end).value();
    auto inAfterStart = Converter::OptConvert<int32_t>(rangeAfter.start).value();
    auto inAfterEnd = Converter::OptConvert<int32_t>(rangeAfter.end).value();
    EXPECT_EQ(inBeforeStart, TEST_RANGE_START);
    EXPECT_EQ(inBeforeEnd, TEST_RANGE_END);
    EXPECT_EQ(inAfterStart, TEST_RANGE_START_TWO);
    EXPECT_EQ(inAfterEnd, TEST_RANGE_END_TWO);
    SetFlag(recv.onDidChange);
}

void onCutCallback(Ark_Int32 nodeId, const Ark_CutEvent data)
{
    SetFlag(recv.onCut);
}

void onCopyCallback(Ark_Int32 nodeId, const Ark_CopyEvent data)
{
    SetFlag(recv.onCopy);
}
} // namespace

static const GENERATED_ArkUIRichEditorEventsReceiver* getEventsReceiverTest()
{
    return &recv;
};

static const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getRichEditorEventsReceiver = getEventsReceiverTest };
    return &eventsImpl;
};

class RichEditorModifierCallbacksTest : public ModifierTestBase<GENERATED_ArkUIRichEditorModifier,
    &GENERATED_ArkUINodeModifiers::getRichEditorModifier, GENERATED_ARKUI_RICH_EDITOR> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<RichEditorTheme>();
        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());

        // Setup all callbacks
        recv.onReady = onReadyCallback;
        recv.onSelect = onSelectCallback;
        recv.onSelectionChange = onSelectionChangeCallback;
        recv.aboutToIMEInput = onAboutToIMEInputCallback;
        recv.onIMEInputComplete = onIMEInputCompleteCallback;
        recv.onDidIMEInput = onDidIMEInputCallback;
        recv.aboutToDelete = onAboutToDeleteCallback;
        recv.onDeleteComplete = onDeleteCompleteCallback;
        recv.onPaste = onPasteCallback;
        recv.onEditingChange = onEditingChangeCallback;
        recv.onSubmit = onSubmitCallback;
        recv.onWillChange = onWillChangeCallback;
        recv.onDidChange = onDidChangeCallback;
        recv.onCut = onCutCallback;
        recv.onCopy = onCopyCallback;
    }
};

/**
 * @tc.name: OnReadyCallbackTest
 * @tc.desc: OnReadyCallbackTest test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnReadyCallbackTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Void func{};
    modifier_->setOnReady(node_, &func);
    EXPECT_EQ(GetFlag(recv.onReady), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnReady();
    EXPECT_EQ(GetFlag(recv.onReady), true);
}

/**
 * @tc.name: OnSelectCallbackTest
 * @tc.desc: setOnSelect test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSelectCallbackTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_RichEditorSelection_Void func{};
    modifier_->setOnSelect(node_, &func);
    EXPECT_EQ(GetFlag(recv.onSelect), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    SelectionInfo value;
    value.SetSelectionStart(TEST_SELECTION_START);
    value.SetSelectionEnd(TEST_SELECTION_END);
    eventHub->FireOnSelect(&value);
    EXPECT_EQ(GetFlag(recv.onSelect), true);
}

/**
 * @tc.name: OnSelectionChange
 * @tc.desc: setOnSelectionChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSelectionChange, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_RichEditorRange_Void func{};
    modifier_->setOnSelectionChange(node_, &func);
    EXPECT_EQ(GetFlag(recv.onSelectionChange), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    SelectionInfo value;
    value.SetSelectionStart(TEST_SELECTION_START);
    value.SetSelectionEnd(TEST_SELECTION_END);
    eventHub->FireOnSelectionChange(&value);
    EXPECT_EQ(GetFlag(recv.onSelectionChange), true);
}

/**
 * @tc.name: OnAboutToInputCallbackTest
 * @tc.desc: setAboutToIMEInput test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnAboutToInputCallbackTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_RichEditorInsertValue_Boolean func{};
    modifier_->setAboutToIMEInput(node_, &func);
    EXPECT_EQ(GetFlag(recv.aboutToIMEInput), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorInsertValue info;
    info.SetInsertOffset(TEST_INSERT_OFFSET);
    info.SetInsertValue(TEST_INSERT_VALUE);
    info.SetPreviewText(TEST_PREVIEW_TEXT);
    eventHub->FireAboutToIMEInput(info);
    EXPECT_EQ(GetFlag(recv.aboutToIMEInput), true);
}

/**
 * @tc.name: OnIMEInputCompleteTest
 * @tc.desc: setOnIMEInputComplete test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnIMEInputCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_RichEditorTextSpanResult_Void func{};
    modifier_->setOnIMEInputComplete(node_, &func);
    EXPECT_EQ(GetFlag(recv.onIMEInputComplete), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    RichEditorAbstractSpanResult info;
    info.SetValue(TEST_TEXT);
    info.SetSpanIndex(TEST_SPAN_IDX);
    info.SetSpanRangeStart(TEST_SPAN_START);
    info.SetSpanRangeEnd(TEST_SPAN_END);
    info.SetFontFamily(TEST_FONT_FAMILY);
    info.SetFontSize(TEST_FONT_SIZE);
    info.SetFontColor(TEST_FONT_COLOR);
    info.SetPreviewText(TEST_PREVIEW_TEXT);

    SymbolSpanStyle symbolSpanStyle;
    symbolSpanStyle.fontSize = TEST_FONT_SIZE;
    symbolSpanStyle.fontWeight = TEST_FONT_WEIGHT;
    info.SetSymbolSpanStyle(symbolSpanStyle);

    eventHub->FireOnIMEInputComplete(info);
    EXPECT_EQ(GetFlag(recv.onIMEInputComplete), true);
}

/**
 * @tc.name: OnDidIMEInputTest
 * @tc.desc: setOnDidIMEInput test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnDidIMEInputTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_TextRange_Void func{};
    modifier_->setOnDidIMEInput(node_, &func);
    EXPECT_EQ(GetFlag(recv.onDidIMEInput), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextRange range;
    range.start = TEST_START;
    range.end = TEST_END;
    eventHub->FireOnDidIMEInput(range);
    EXPECT_EQ(GetFlag(recv.onDidIMEInput), true);
}

/**
 * @tc.name: OnSetAboutToDeleteTest
 * @tc.desc: setAboutToDelete test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSetAboutToDeleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_RichEditorDeleteValue_Boolean func{};
    modifier_->setAboutToDelete(node_, &func);
    EXPECT_EQ(GetFlag(recv.aboutToDelete), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorDeleteValue value;
    value.SetLength(TEST_LENGTH);
    value.SetOffset(TEST_OFFSET);
    value.SetRichEditorDeleteDirection(TEST_DELETE_DIRECTION);
    eventHub->FireAboutToDelete(value);
    EXPECT_EQ(GetFlag(recv.aboutToDelete), true);
}

/**
 * @tc.name: OnSetDeleteCompleteTest
 * @tc.desc: setOnDeleteComplete test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSetDeleteCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Void func{};
    modifier_->setOnDeleteComplete(node_, &func);
    EXPECT_EQ(GetFlag(recv.onDeleteComplete), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnDeleteComplete();
    EXPECT_EQ(GetFlag(recv.onDeleteComplete), true);
}

/**
 * @tc.name: OnPasteTest
 * @tc.desc: setOnDeleteComplete test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnPasteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    PasteEventCallback func{};
    modifier_->setOnPaste(node_, &func);
    EXPECT_EQ(GetFlag(recv.onPaste), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    NG::TextCommonEvent value;
    eventHub->FireOnPaste(value);
    EXPECT_EQ(GetFlag(recv.onPaste), true);
}

/**
 * @tc.name: OnEditingChangeTest
 * @tc.desc: setOnEditingChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnEditingChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Boolean_Void func{};
    modifier_->setOnEditingChange(node_, &func);
    EXPECT_EQ(GetFlag(recv.onEditingChange), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEditing = TEST_IS_CHANGED_IN_EDITING;
    eventHub->FireOnEditingChange(isEditing);
    EXPECT_EQ(GetFlag(recv.onEditingChange), true);
}

/**
 * @tc.name: OnSubmitTest
 * @tc.desc: setOnSubmit test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSubmitTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    SubmitCallback func{};
    modifier_->setOnSubmit(node_, &func);
    EXPECT_EQ(GetFlag(recv.onSubmit), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    int32_t value = TEST_ENTER_KEY_TYPE;
    NG::TextFieldCommonEvent event;
    event.SetText(TEST_TEXT);
    eventHub->FireOnSubmit(value, event);
    EXPECT_EQ(GetFlag(recv.onSubmit), true);
}

/**
 * @tc.name: OnWillChangeTest
 * @tc.desc: setOnWillChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnWillChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_RichEditorChangeValue_Boolean func{};
    modifier_->setOnWillChange(node_, &func);
    EXPECT_EQ(GetFlag(recv.onWillChange), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorChangeValue info;
    TextRange rangeBefore = {.start = TEST_RANGE_START, .end = TEST_RANGE_END};
    info.SetRangeBefore(rangeBefore);
    eventHub->FireOnWillChange(info);
    EXPECT_EQ(GetFlag(recv.onWillChange), true);
}

/**
 * @tc.name: OnDidChangeTest
 * @tc.desc: setOnDidChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnDidChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    OnDidChangeCallback func{};
    modifier_->setOnDidChange(node_, &func);
    EXPECT_EQ(GetFlag(recv.onDidChange), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorChangeValue changeValue;
    changeValue.SetRangeBefore({.start = TEST_RANGE_START, .end = TEST_RANGE_END});
    changeValue.SetRangeAfter({.start = TEST_RANGE_START_TWO, .end = TEST_RANGE_END_TWO});
    eventHub->FireOnDidChange(changeValue);
    EXPECT_EQ(GetFlag(recv.onDidChange), true);
}

/**
 * @tc.name: OnCopyTest
 * @tc.desc: setOnCopy test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnCopyTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_CopyEvent_Void func{};
    modifier_->setOnCopy(node_, &func);
    EXPECT_EQ(GetFlag(recv.onCopy), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    NG::TextCommonEvent event;
    eventHub->FireOnCopy(event);
    EXPECT_EQ(GetFlag(recv.onCopy), true);
}

/**
 * @tc.name: OnCutTest
 * @tc.desc: setOnCut test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnCutTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_CutEvent_Void func{};
    modifier_->setOnCut(node_, &func);
    EXPECT_EQ(GetFlag(recv.onCut), false);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    NG::TextCommonEvent event;
    eventHub->FireOnCut(event);
    EXPECT_EQ(GetFlag(recv.onCut), true);
}
} // namespace OHOS::Ace::NG
