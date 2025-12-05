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

#include "test/unittest/capi/stubs/friend_class_accessor.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/interfaces/native/implementation/copy_event_peer.h"
#include "core/interfaces/native/implementation/cut_event_peer.h"
#include "core/interfaces/native/implementation/paste_event_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/submit_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "test/mock/base/mock_pixel_map.h"

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
constexpr auto TEST_TEXT_2 = "just text";
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
const std::string TEST_CONTENT_ONE = "ContentTestOne";
const std::string TEST_CONTENT_TWO = "ContentTestTwo";
Ark_EnterKeyType g_EventTestKey{};
class RichEditorModifierCallbacksTest : public ModifierTestBase<GENERATED_ArkUIRichEditorModifier,
    &GENERATED_ArkUINodeModifiers::getRichEditorModifier, GENERATED_ARKUI_RICH_EDITOR> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<RichEditorTheme>();
    }

    std::vector<MenuItemParam> GetMenuItemParams()
    {
        std::vector<MenuItemParam> params;
        MenuOptionsParam menuOptionItemOne;
        menuOptionItemOne.content = TEST_CONTENT_ONE;
        menuOptionItemOne.action = [](const std::string&) {};
        MenuOptionsParam menuOptionItemTwo;
        menuOptionItemTwo.content = TEST_CONTENT_TWO;
        menuOptionItemTwo.action = [](const std::string&) {};
        MenuItemParam param1;
        param1.menuOptionsParam = menuOptionItemOne;
        MenuItemParam param2;
        param2.menuOptionsParam = menuOptionItemTwo;
        params.push_back(param1);
        params.push_back(param2);
        return params;
    }
};

/**
 * @tc.name: OnReadyCallbackTest
 * @tc.desc: OnReadyCallbackTest test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnReadyCallbackTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](Ark_Int32 nodeId) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(nodeId),
        };
    };
    auto arkCallback = Converter::ArkValue<VoidCallback>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_VoidCallback>(arkCallback);
    modifier_->setOnReady(node_, &optCallback);
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
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnSelectCallbackTest, TestSize.Level1)
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(nodeId),
            .info = info,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_RichEditorSelection_Void>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_RichEditorSelection_Void>(arkCallback);
    modifier_->setOnSelect(node_, &optCallback);
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
 * @tc.name: OnSelectCallbackWithTextSpanTest
 * @tc.desc: Test setOnSelect with text span data
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnSelectCallbackWithTextSpanTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        bool hasTextSpan = false;
        bool hasImageSpan = false;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onChange = [](Ark_Int32 nodeId, Ark_RichEditorSelection data) {
        bool hasText = false;
        bool hasImage = false;
        Converter::VisitUnion(data.spans.array[0],
            [&hasText](const Ark_RichEditorTextSpanResult& value) {
                hasText = true;
                EXPECT_EQ(Converter::Convert<std::string>(value.value), TEST_TEXT_2);
            },
            [&hasImage](const Ark_RichEditorImageSpanResult& value) {
                hasImage = true;
            },
            []() {}
        );

        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(nodeId), .hasTextSpan = hasText, .hasImageSpan = hasImage
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_RichEditorSelection_Void>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_RichEditorSelection_Void>(arkCallback);
    modifier_->setOnSelect(node_, &optCallback);

    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    EXPECT_FALSE(checkEvent);

    SelectionInfo value;
    value.SetSelectionStart(TEST_SELECTION_START);
    value.SetSelectionEnd(TEST_SELECTION_END);

    ResultObject textResult;
    textResult.type = SelectSpanType::TYPESPAN;
    textResult.valueString = TEST_TEXT;
    textResult.textStyle.fontColor = TEST_FONT_COLOR;
    textResult.textStyle.fontSize = 16.0;
    textResult.spanPosition.spanIndex = 1;
    textResult.spanPosition.spanRange[0] = TEST_RANGE_START;
    textResult.spanPosition.spanRange[1] = TEST_RANGE_END;

    value.SetResultObjectList({ textResult });

    eventHub->FireOnSelect(&value);

    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->hasTextSpan);
    EXPECT_FALSE(checkEvent->hasImageSpan);
}

/**
 * @tc.name: OnSelectCallbackWithImageSpanTest
 * @tc.desc: Test setOnSelect with image span data
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnSelectCallbackWithImageSpanTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        bool hasTextSpan = false;
        bool hasPixelMap = false;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onChange = [](Ark_Int32 nodeId, Ark_RichEditorSelection data) {
        bool hasText = false;
        bool hasPixelMap = false;

        Converter::VisitUnion(data.spans.array[0],
            [&hasText](const Ark_RichEditorTextSpanResult& value) { hasText = true; },
            [&hasPixelMap](const Ark_RichEditorImageSpanResult& value) {
                auto pixelMapPeer = Converter::GetOpt(value.valuePixelMap).value_or(nullptr);
                hasPixelMap = pixelMapPeer && pixelMapPeer->pixelMap;
            },
            []() {}
        );

        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(nodeId),
            .hasTextSpan = hasText, .hasPixelMap = hasPixelMap
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_RichEditorSelection_Void>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_RichEditorSelection_Void>(arkCallback);
    modifier_->setOnSelect(node_, &optCallback);

    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    EXPECT_FALSE(checkEvent);

    SelectionInfo value;
    value.SetSelectionStart(TEST_SELECTION_START);
    value.SetSelectionEnd(TEST_SELECTION_END);

    RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();

    ResultObject imageResult;
    imageResult.type = SelectSpanType::TYPEIMAGE;
    imageResult.valuePixelMap = pixelMap;
    imageResult.spanPosition.spanIndex = 1;
    imageResult.spanPosition.spanRange[0] = TEST_RANGE_START;
    imageResult.spanPosition.spanRange[1] = TEST_RANGE_END;
    imageResult.imageStyle.verticalAlign = static_cast<int32_t>(VerticalAlign::BOTTOM);
    imageResult.imageStyle.objectFit = static_cast<int32_t>(ImageFit::COVER);

    value.SetResultObjectList({ imageResult });

    eventHub->FireOnSelect(&value);

    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_FALSE(checkEvent->hasTextSpan);
    EXPECT_TRUE(checkEvent->hasPixelMap);
}

/**
 * @tc.name: OnSelectionChange
 * @tc.desc: setOnSelectionChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnSelectionChange, TestSize.Level1)
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(nodeId),
            .info = info,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_RichEditorRange_Void>(onSelect, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_RichEditorRange_Void>(arkCallback);
    modifier_->setOnSelectionChange(node_, &optCallback);
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
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_AboutToIMEInputTest, TestSize.Level1)
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto func = Converter::ArkValue<Callback_RichEditorInsertValue_Boolean>(nullptr, inputCallback, expectedResId);
    auto optFunc = Converter::ArkValue<Opt_Callback_RichEditorInsertValue_Boolean>(func);
    modifier_->setAboutToIMEInput(node_, &optFunc);
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
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnIMEInputCompleteTest, TestSize.Level1)
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_RichEditorTextSpanResult_Void>(onIMEIcomplete, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_RichEditorTextSpanResult_Void>(arkCallback);
    modifier_->setOnIMEInputComplete(node_, &optCallback);
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
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnDidIMEInputTest, TestSize.Level1)
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_TextRange_Void>(onCallback, frameNode->GetId());
    EXPECT_FALSE(checkEvent);
    TextRange range;
    range.start = TEST_START;
    range.end = TEST_END;
    auto optCallback = Converter::ArkValue<Opt_Callback_TextRange_Void>(arkCallback);
    modifier_->setOnDidIMEInput(node_, &optCallback);
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
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnSetAboutToDeleteTest, TestSize.Level1)
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto func = Converter::ArkValue<Callback_RichEditorDeleteValue_Boolean>(nullptr, inputCallback, expectedResId);
    auto optFunc = Converter::ArkValue<Opt_Callback_RichEditorDeleteValue_Boolean>(func);
    modifier_->setAboutToDelete(node_, &optFunc);
    RichEditorDeleteValue value;
    value.SetLength(TEST_LENGTH);
    value.SetOffset(TEST_OFFSET);
    value.SetRichEditorDeleteDirection(TEST_DELETE_DIRECTION);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
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
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnSetDeleteCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](Ark_Int32 nodeId) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(nodeId),
        };
    };
    auto arkCallback = Converter::ArkValue<VoidCallback>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_VoidCallback>(arkCallback);
    modifier_->setOnDeleteComplete(node_, &optCallback);
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        auto pasteEvent = Converter::GetOpt(event);
        if (pasteEvent.has_value() && pasteEvent.value()) {
            pasteEvent.value()->HandlePreventDefault();
        }
    };
    auto arkCallback = Converter::ArkValue<PasteEventCallback>(testCallback, frameNode->GetId());
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto optCallback = Converter::ArkValue<Opt_PasteEventCallback>(arkCallback);
    modifier_->setOnPaste(node_, &optCallback);
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
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnEditingChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChange = [](const Ark_Int32 resourceId, const Ark_Boolean parameter) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .result = Converter::Convert<bool>(parameter),
        };
    };
    auto arkCallback = Converter::ArkValue<arkui_component_common_Callback_Boolean_Void>(onChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_arkui_component_common_Callback_Boolean_Void>(arkCallback);
    modifier_->setOnEditingChange(node_, &optCallback);
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

    auto onSubmitFunc = [](
        Ark_VMContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Ark_SubmitEvent event
    ) {
        auto peer = event;
        ASSERT_NE(peer, nullptr);
        auto submitEventInfo = peer->GetEventInfo();
        ASSERT_NE(submitEventInfo, nullptr);
        EXPECT_EQ(submitEventInfo->GetText(), testValue);
        GeneratedModifier::GetSubmitEventAccessor()->destroyPeer(peer);
        EXPECT_EQ(resourceId, expectedResId);
        g_EventTestKey = enterKeyType;
    };

    auto func = Converter::ArkValue<SubmitCallback>(onSubmitFunc, expectedResId);
    auto optFunc = Converter::ArkValue<Opt_SubmitCallback>(func);
    modifier_->setOnSubmit(node_, &optFunc);
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
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnWillChangeTest, TestSize.Level1)
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = value,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto func = Converter::ArkValue<Callback_RichEditorChangeValue_Boolean>(nullptr, inputCallback, frameNode->GetId());
    auto optFunc = Converter::ArkValue<Opt_Callback_RichEditorChangeValue_Boolean>(func);
    modifier_->setOnWillChange(node_, &optFunc);
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
 * @tc.name: OnWillChangeTest2
 * @tc.desc: setOnWillChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnWillChangeTest2, TestSize.Level1)
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
        auto& spanPosition = parameter.replacedSpans.array[0].spanPosition;
        auto idx = Converter::OptConvert<int32_t>(spanPosition.spanIndex).value_or(-1);
        auto start = Converter::OptConvert<int32_t>(spanPosition.spanRange.value0).value_or(-1);
        auto end = Converter::OptConvert<int32_t>(spanPosition.spanRange.value1).value_or(-1);
        RichEditorAbstractSpanResult span;
        span.SetSpanIndex(idx);
        span.SetSpanRangeStart(start);
        span.SetSpanRangeEnd(end);
        value.SetRichEditorReplacedSpans(span);
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = value,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto func = Converter::ArkValue<Callback_RichEditorChangeValue_Boolean>(nullptr, inputCallback, frameNode->GetId());
    auto optFunc = Converter::ArkValue<Opt_Callback_RichEditorChangeValue_Boolean>(func);
    modifier_->setOnWillChange(node_, &optFunc);
    RichEditorChangeValue value;
    RichEditorAbstractSpanResult span;
    span.SetSpanIndex(TEST_OFFSET);
    span.SetSpanRangeStart(TEST_START);
    span.SetSpanRangeEnd(TEST_END);
    value.SetRichEditorReplacedSpans(span);
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_TRUE(eventHub);
    auto result = eventHub->FireOnWillChange(value);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_TRUE(result);
    auto& testSpans = checkEvent->info.GetRichEditorReplacedSpans();
    EXPECT_FALSE(testSpans.empty());
    auto& testSpan = testSpans[0];
    EXPECT_EQ(testSpan.GetSpanIndex(), TEST_OFFSET);
    EXPECT_EQ(testSpan.GetSpanRangeStart(), TEST_START);
    EXPECT_EQ(testSpan.GetSpanRangeEnd(), TEST_END);
}

/**
 * @tc.name: OnDidChangeTest
 * @tc.desc: setOnDidChange test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, DISABLED_OnDidChangeTest, TestSize.Level1)
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = changeValue,
        };
    };
    auto func = Converter::ArkValue<OnDidChangeCallback>(inputCallback, frameNode->GetId());
    auto optFunc = Converter::ArkValue<Opt_OnDidChangeCallback>(func);
    modifier_->setOnDidChange(node_, &optFunc);
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        if (parameter) {
            parameter->HandlePreventDefault();
        }
    };
    auto arkCallback = Converter::ArkValue<Callback_CopyEvent_Void>(nullptr, testCallback, frameNode->GetId());
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto optCallback = Converter::ArkValue<Opt_Callback_CopyEvent_Void>(arkCallback);
    modifier_->setOnCopy(node_, &optCallback);
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
    ASSERT_NE(frameNode, nullptr);
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_CutEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        if (parameter) {
            parameter->HandlePreventDefault();
        }
    };
    auto arkCallback = Converter::ArkValue<Callback_CutEvent_Void>(testCallback, frameNode->GetId());
    auto eventHub = frameNode->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto optCallback = Converter::ArkValue<Opt_Callback_CutEvent_Void>(arkCallback);
    modifier_->setOnCut(node_, &optCallback);
    EXPECT_FALSE(checkEvent);
    NG::TextCommonEvent event;
    EXPECT_FALSE(event.IsPreventDefault());
    eventHub->FireOnCut(event);
    ASSERT_TRUE(checkEvent);
    EXPECT_TRUE(event.IsPreventDefault());
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
}

/**
 * @tc.name: setEditMenuOptionsTest
 * @tc.desc: setEditMenuOptions test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierCallbacksTest, setEditMenuOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEditMenuOptions, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t testID = 323;
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testOnCreateMenuCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Array_TextMenuItem menuItems, const Callback_Array_TextMenuItem_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        CallbackHelper(continuation).Invoke(menuItems);
    };
    auto arkCreateCallback = Converter::ArkValue<::OnCreateMenuCallback>(testOnCreateMenuCallback, testID);

    auto testOnMenuItemClickCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation) {
        auto item = Converter::OptConvert<MenuOptionsParam>(menuItem);
        ASSERT_TRUE(item.has_value());
        ASSERT_TRUE(item->content.has_value());
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(*item->content == TEST_CONTENT_ONE));
    };
    auto arkClickCallback = Converter::ArkValue<::OnMenuItemClickCallback>(testOnMenuItemClickCallback, testID);
    auto optOnCreateMenuCallback = Converter::ArkValue<Opt_OnCreateMenuCallback>(arkCreateCallback);
    auto optOnMenuItemClickCallback = Converter::ArkValue<Opt_OnMenuItemClickCallback>(arkClickCallback);

    Ark_EditMenuOptions options { .onCreateMenu = optOnCreateMenuCallback,
        .onMenuItemClick = optOnMenuItemClickCallback };

    SelectOverlayInfo selectOverlayInfo;
    auto params = GetMenuItemParams();
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback == nullptr);
    auto optOptions = Converter::ArkValue<Opt_EditMenuOptions>(options);
    modifier_->setEditMenuOptions(node_, &optOptions);
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    ASSERT_NE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback, nullptr);
    selectOverlayInfo.onCreateCallback.onCreateMenuCallback(params);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, testID);

    ASSERT_NE(selectOverlayInfo.onCreateCallback.onMenuItemClick, nullptr);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[0]));
    EXPECT_FALSE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[1]));
}
}
} // namespace OHOS::Ace::NG
