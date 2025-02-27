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
#include "core/interfaces/native/implementation/submit_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor();
}

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
constexpr auto TEST_INSERT_VALUE = u"insert text";
constexpr auto TEST_PREVIEW_TEXT = u"preview text";
constexpr auto TEST_TEXT = u"just text";
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
constexpr int32_t TEST_RANGE_START = 6;
constexpr int32_t TEST_RANGE_END = 7;
constexpr int32_t TEST_RANGE_START_TWO = 8;
constexpr int32_t TEST_RANGE_END_TWO = 9;
Ark_EnterKeyType g_EventTestKey{};
class RichEditorModifierCallbacksTest : public ModifierTestBase<GENERATED_ArkUIRichEditorModifier,
    &GENERATED_ArkUINodeModifiers::getRichEditorModifier, GENERATED_ARKUI_RICH_EDITOR> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<RichEditorTheme>();
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
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](Ark_Int32 nodeId) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(nodeId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(onChange, frameNode->GetId());
    modifier_->setOnReady(node_, &arkCallback);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    EXPECT_FALSE(checkEvent);
    eventHub->FireOnReady();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
}

/**
 * @tc.name: OnSelectCallbackTest
 * @tc.desc: setOnSelect test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSelectCallbackTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        SelectionInfo info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](Ark_Int32 nodeId, Ark_RichEditorSelection data) {
        auto start = Converter::OptConvert<int32_t>(data.selection.value0);
        auto end = Converter::OptConvert<int32_t>(data.selection.value1);
        SelectionInfo info;
        if (start) {
            info.SetSelectionStart(*start);
        }
        if (end) {
            info.SetSelectionEnd(*end);
        }
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(nodeId),
            .info = info,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_RichEditorSelection_Void>(onChange, frameNode->GetId());
    modifier_->setOnSelect(node_, &arkCallback);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    EXPECT_FALSE(checkEvent);
    SelectionInfo value;
    value.SetSelectionStart(TEST_SELECTION_START);
    value.SetSelectionEnd(TEST_SELECTION_END);
    eventHub->FireOnSelect(&value);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
}

/**
 * @tc.name: OnSelectionChange
 * @tc.desc: setOnSelectionChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSelectionChange, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        SelectionInfo info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onSelect = [](Ark_Int32 nodeId, Ark_RichEditorRange data) {
        auto start = Converter::OptConvert<int32_t>(data.start);
        auto end = Converter::OptConvert<int32_t>(data.end);
        SelectionInfo info;
        if (start) {
            info.SetSelectionStart(*start);
        }
        if (end) {
            info.SetSelectionEnd(*end);
        }
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(nodeId),
            .info = info,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_RichEditorRange_Void>(onSelect, frameNode->GetId());
    modifier_->setOnSelectionChange(node_, &arkCallback);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    EXPECT_FALSE(checkEvent);
    SelectionInfo value;
    value.SetSelectionStart(TEST_SELECTION_START);
    value.SetSelectionEnd(TEST_SELECTION_END);
    eventHub->FireOnSelectionChange(&value);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_EQ(checkEvent->info.GetSelection().selection[0], TEST_SELECTION_START);
    EXPECT_EQ(checkEvent->info.GetSelection().selection[1], TEST_SELECTION_END);
}

/**
 * @tc.name: AboutToIMEInputTest
 * @tc.desc: setAboutToIMEInput test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, AboutToIMEInputTest, TestSize.Level1)
{
    static const int32_t expectedResId = 123;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        RichEditorInsertValue info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto inputCallback = [] (Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_RichEditorInsertValue parameter, const Callback_Boolean_Void continuation) {
        RichEditorInsertValue info;
        info.SetInsertOffset(Converter::Convert<int32_t>(parameter.insertOffset));
        info.SetInsertValue(Converter::Convert<std::u16string>(parameter.insertValue));
        auto previewText = Converter::OptConvert<std::u16string>(parameter.previewText);
        if (previewText) {
            info.SetPreviewText(*previewText);
        }
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto func = Converter::ArkValue<Callback_RichEditorInsertValue_Boolean>(nullptr, inputCallback, expectedResId);
    modifier_->setAboutToIMEInput(node_, &func);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorInsertValue info;
    info.SetInsertOffset(TEST_INSERT_OFFSET);
    info.SetInsertValue(TEST_INSERT_VALUE);
    info.SetPreviewText(TEST_PREVIEW_TEXT);
    EXPECT_FALSE(checkEvent);
    auto result = eventHub->FireAboutToIMEInput(info);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
    EXPECT_TRUE(result);
    EXPECT_EQ(checkEvent->info.GetInsertOffset(), info.GetInsertOffset());
    EXPECT_EQ(checkEvent->info.GetInsertValue(), info.GetInsertValue());
    EXPECT_EQ(checkEvent->info.GetPreviewText(), info.GetPreviewText());
}

/**
 * @tc.name: OnIMEInputCompleteTest
 * @tc.desc: setOnIMEInputComplete test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnIMEInputCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);

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

    struct CheckEvent {
        int32_t resourceId;
        RichEditorAbstractSpanResult info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onIMEIcomplete = [](const Ark_Int32 resourceId, const Ark_RichEditorTextSpanResult data) {
        RichEditorAbstractSpanResult info;
        // need fill info from data
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_RichEditorTextSpanResult_Void>(onIMEIcomplete, frameNode->GetId());
    modifier_->setOnIMEInputComplete(node_, &arkCallback);
    EXPECT_FALSE(checkEvent);
    eventHub->FireOnIMEInputComplete(info);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
}

/**
 * @tc.name: OnDidIMEInputTest
 * @tc.desc: setOnDidIMEInput test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnDidIMEInputTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    struct CheckEvent {
        int32_t resourceId;
        TextRange info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onCallback = [](const Ark_Int32 resourceId, const Ark_TextRange parameter) {
        TextRange info;
        if (auto start = Converter::OptConvert<int32_t>(parameter.start); start) {
            info.start = *start;
        }
        if (auto end = Converter::OptConvert<int32_t>(parameter.end); end) {
            info.end = *end;
        }
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_TextRange_Void>(onCallback, frameNode->GetId());
    EXPECT_FALSE(checkEvent);
    TextRange range;
    range.start = TEST_START;
    range.end = TEST_END;
    modifier_->setOnDidIMEInput(node_, &arkCallback);
    eventHub->FireOnDidIMEInput(range);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_EQ(checkEvent->info.start, TEST_START);
    EXPECT_EQ(checkEvent->info.end, TEST_END);
}

/**
 * @tc.name: OnSetAboutToDeleteTest
 * @tc.desc: setAboutToDelete test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSetAboutToDeleteTest, TestSize.Level1)
{
    static const int32_t expectedResId = 123;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        RichEditorDeleteValue info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto inputCallback = [] (Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_RichEditorDeleteValue parameter,
        const Callback_Boolean_Void continuation) {
        RichEditorDeleteValue info;
        info.SetLength(Converter::Convert<int32_t>(parameter.length));
        info.SetOffset(Converter::Convert<int32_t>(parameter.offset));
        info.SetRichEditorDeleteDirection(Converter::Convert<RichEditorDeleteDirection>(parameter.direction));
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto func = Converter::ArkValue<Callback_RichEditorDeleteValue_Boolean>(nullptr, inputCallback, expectedResId);
    modifier_->setAboutToDelete(node_, &func);
    RichEditorDeleteValue value;
    value.SetLength(TEST_LENGTH);
    value.SetOffset(TEST_OFFSET);
    value.SetRichEditorDeleteDirection(TEST_DELETE_DIRECTION);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    auto result = eventHub->FireAboutToDelete(value);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
    EXPECT_TRUE(result);
    EXPECT_EQ(checkEvent->info.GetLength(), value.GetLength());
    EXPECT_EQ(checkEvent->info.GetOffset(), value.GetOffset());
    EXPECT_EQ(checkEvent->info.GetRichEditorDeleteDirection(), value.GetRichEditorDeleteDirection());
}

/**
 * @tc.name: OnSetDeleteCompleteTest
 * @tc.desc: setOnDeleteComplete test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSetDeleteCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](Ark_Int32 nodeId) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(nodeId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(onChange, frameNode->GetId());
    modifier_->setOnDeleteComplete(node_, &arkCallback);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    EXPECT_FALSE(checkEvent);
    eventHub->FireOnDeleteComplete();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
}

/**
 * @tc.name: OnPasteTest
 * @tc.desc: setOnDeleteComplete test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnPasteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Opt_PasteEvent event) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        auto pasteEvent = Converter::OptConvert<Ark_PasteEvent>(event);
        auto arkCallback = pasteEvent ? Converter::OptConvert<Callback_Void>(pasteEvent->preventDefault) : std::nullopt;
        if (arkCallback) {
            auto helper = CallbackHelper(*arkCallback);
            helper.Invoke();
        }
    };
    auto arkCallback = Converter::ArkValue<PasteEventCallback>(nullptr, testCallback, frameNode->GetId());
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    modifier_->setOnPaste(node_, &arkCallback);
    EXPECT_FALSE(checkEvent);
    NG::TextCommonEvent value;
    EXPECT_FALSE(value.IsPreventDefault());
    eventHub->FireOnPaste(value);
    ASSERT_TRUE(checkEvent);
    EXPECT_TRUE(value.IsPreventDefault());
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
}

/**
 * @tc.name: OnEditingChangeTest
 * @tc.desc: setOnEditingChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnEditingChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](const Ark_Int32 resourceId, const Ark_Boolean parameter) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .result = Converter::Convert<bool>(parameter),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Boolean_Void>(onChange, frameNode->GetId());
    modifier_->setOnEditingChange(node_, &arkCallback);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    EXPECT_FALSE(checkEvent);
    eventHub->FireOnEditingChange(true);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/**
 * @tc.name: OnSubmitTest
 * @tc.desc: setOnSubmit test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnSubmitTest, TestSize.Level1)
{
    static const int expectedResId = 123;
    static const std::u16string testValue(u"string text");
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onSubmitFunc = [](Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Ark_SubmitEvent event) {
        auto peer = reinterpret_cast<SubmitEventPeer*>(event.ptr);
        ASSERT_NE(peer, nullptr);
        auto submitEventInfo = peer->GetEventInfo();
        ASSERT_NE(submitEventInfo, nullptr);
        EXPECT_EQ(submitEventInfo->GetText(), testValue);
        GeneratedModifier::GetSubmitEventAccessor()->destroyPeer(peer);
        EXPECT_EQ(resourceId, expectedResId);
        g_EventTestKey = enterKeyType;
    };

    auto func = Converter::ArkValue<SubmitCallback>(onSubmitFunc, expectedResId);
    modifier_->setOnSubmit(node_, &func);
    TextFieldCommonEvent event;
    event.SetText(testValue);
    eventHub->FireOnSubmit(111, event);
    EXPECT_EQ(g_EventTestKey, -1);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestKey, 5);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_GO, event);
    EXPECT_EQ(g_EventTestKey, 2);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEARCH, event);
    EXPECT_EQ(g_EventTestKey, 3);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEND, event);
    EXPECT_EQ(g_EventTestKey, 4);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestKey, 5);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_DONE, event);
    EXPECT_EQ(g_EventTestKey, 6);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_PREVIOUS, event);
    EXPECT_EQ(g_EventTestKey, 7);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEW_LINE, event);
    EXPECT_EQ(g_EventTestKey, 8);
}

/**
 * @tc.name: OnWillChangeTest
 * @tc.desc: setOnWillChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnWillChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        RichEditorChangeValue info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto inputCallback = [] (Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_RichEditorChangeValue parameter, const Callback_Boolean_Void continuation) {
        RichEditorChangeValue value;
        auto rangeStart = Converter::OptConvert<int32_t>(parameter.rangeBefore.start);
        auto rangeEnd = Converter::OptConvert<int32_t>(parameter.rangeBefore.end);
        TextRange rangeBefore;
        if (rangeStart) {
            rangeBefore.start = *rangeStart;
        }
        if (rangeEnd) {
            rangeBefore.end = *rangeEnd;
        }
        value.SetRangeBefore(rangeBefore);
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = value,
        };
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto func = Converter::ArkValue<Callback_RichEditorChangeValue_Boolean>(nullptr, inputCallback, frameNode->GetId());
    modifier_->setOnWillChange(node_, &func);
    RichEditorChangeValue value;
    TextRange rangeBefore = {.start = TEST_RANGE_START, .end = TEST_RANGE_END};
    value.SetRangeBefore(rangeBefore);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    auto result = eventHub->FireOnWillChange(value);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_TRUE(result);
    EXPECT_EQ(checkEvent->info.GetRangeBefore().start, TEST_RANGE_START);
    EXPECT_EQ(checkEvent->info.GetRangeBefore().end, TEST_RANGE_END);
}

/**
 * @tc.name: OnDidChangeTest
 * @tc.desc: setOnDidChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnDidChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        RichEditorChangeValue info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto inputCallback = [] (const Ark_Int32 resourceId, const Ark_TextRange rangeBefore,
        const Ark_TextRange rangeAfter) {
        RichEditorChangeValue changeValue;
        changeValue.SetRangeBefore({
            .start = Converter::OptConvert<int32_t>(rangeBefore.start).value_or(-1),
            .end = Converter::OptConvert<int32_t>(rangeBefore.end).value_or(-1),
        });
        changeValue.SetRangeAfter({
            .start = Converter::OptConvert<int32_t>(rangeAfter.start).value_or(-1),
            .end = Converter::OptConvert<int32_t>(rangeAfter.end).value_or(-1),
        });
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = changeValue,
        };
    };
    auto func = Converter::ArkValue<OnDidChangeCallback>(inputCallback, frameNode->GetId());
    modifier_->setOnDidChange(node_, &func);
    RichEditorChangeValue changeValue;
    changeValue.SetRangeBefore({.start = TEST_RANGE_START, .end = TEST_RANGE_END});
    changeValue.SetRangeAfter({.start = TEST_RANGE_START_TWO, .end = TEST_RANGE_END_TWO});
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    eventHub->FireOnDidChange(changeValue);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_EQ(checkEvent->info.GetRangeBefore().start, TEST_RANGE_START);
    EXPECT_EQ(checkEvent->info.GetRangeBefore().end, TEST_RANGE_END);
    EXPECT_EQ(checkEvent->info.GetRangeAfter().start, TEST_RANGE_START_TWO);
    EXPECT_EQ(checkEvent->info.GetRangeAfter().end, TEST_RANGE_END_TWO);
}

/**
 * @tc.name: OnCopyTest
 * @tc.desc: setOnCopy test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnCopyTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_CopyEvent parameter) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        auto arkCallback = Converter::OptConvert<Callback_Void>(parameter.preventDefault);
        if (arkCallback) {
            auto helper = CallbackHelper(*arkCallback);
            helper.Invoke();
        }
    };
    auto arkCallback = Converter::ArkValue<Callback_CopyEvent_Void>(nullptr, testCallback, frameNode->GetId());
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    modifier_->setOnCopy(node_, &arkCallback);
    EXPECT_FALSE(checkEvent);
    NG::TextCommonEvent event;
    EXPECT_FALSE(event.IsPreventDefault());
    eventHub->FireOnCopy(event);
    ASSERT_TRUE(checkEvent);
    EXPECT_TRUE(event.IsPreventDefault());
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
}

/**
 * @tc.name: OnCutTest
 * @tc.desc: setOnCut test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, OnCutTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_CutEvent parameter) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        auto arkCallback = Converter::OptConvert<Callback_Void>(parameter.preventDefault);
        if (arkCallback) {
            auto helper = CallbackHelper(*arkCallback);
            helper.Invoke();
        }
    };
    auto arkCallback = Converter::ArkValue<Callback_CutEvent_Void>(nullptr, testCallback, frameNode->GetId());
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    modifier_->setOnCut(node_, &arkCallback);
    EXPECT_FALSE(checkEvent);
    NG::TextCommonEvent event;
    EXPECT_FALSE(event.IsPreventDefault());
    eventHub->FireOnCut(event);
    ASSERT_TRUE(checkEvent);
    EXPECT_TRUE(event.IsPreventDefault());
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
}
}
} // namespace OHOS::Ace::NG
