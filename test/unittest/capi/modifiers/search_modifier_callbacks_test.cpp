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

#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/search/search_pattern.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/paste_event_peer.h"
#include "core/interfaces/native/implementation/search_controller_accessor_peer.h"
#include "base/utils/string_utils.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
// attrs
const auto INPUT_FILTER_ATTR("inputFilter");
// check text
const std::u16string CHECK_TEXT(u"test_text");
const std::u16string ERROR_TEXT(u"test_error_text");
PreviewText PREVIEW_TEXT = { .offset = 1234, .value = u"test_offset" };
const auto EMPTY_TEXT(u"");

const std::vector<TextDeleteDirection> DELETE_DIRECTION_TEST_PLAN = {
    TextDeleteDirection::FORWARD,
    TextDeleteDirection::BACKWARD,
};

// events
bool g_isEditChangeTest(true);
std::u16string g_EventTestString(u"");
std::string g_EventErrorTestString("");
int32_t g_EventTestOffset(0);
int32_t g_startValue(0);
int32_t g_endValue(0);
float g_scrollX(0);
float g_scrollY(0);
TextDeleteDirection g_deleteDirection(TextDeleteDirection::FORWARD);

// length values
const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);

using ArkNumberIntTest = std::pair<Ark_Int32, Ark_Int32>;
using ArkNumberFloatTest = std::pair<float, float>;

const std::vector<ArkNumberIntTest> INT_NUMBER_TEST_PLAN = {
    { AINT32_POS, AINT32_POS },
    { AINT32_NEG, AINT32_NEG },
};

const std::vector<ArkNumberFloatTest> FLOAT_NUMBER_TEST_PLAN = {
    { AFLT32_POS, AFLT32_POS },
    { AFLT32_NEG, AFLT32_NEG },
};

const std::string TEST_CONTENT_ONE = "ContentTestOne";
const std::string TEST_CONTENT_TWO = "ContentTestTwo";
} // namespace

namespace Converter {
    template<>
    PreviewText Convert(const Ark_PreviewText& value);
}

namespace GeneratedModifier {
    const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor();
}

class SearchModifierCallbackTest : public ModifierTestBase<GENERATED_ArkUISearchModifier,
                               &GENERATED_ArkUINodeModifiers::getSearchModifier, GENERATED_ARKUI_SEARCH> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<SearchTheme>();
        SetupTheme<TextFieldTheme>();
        SetupTheme<IconTheme>();
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
 * @tc.name: setSearchOptionsTestSearchController
 * @tc.desc: Check the functionality of setSearchOptions
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setSearchOptionsTestSearchController, TestSize.Level1)
{
    Ark_SearchOptions options = {};
    options.value = ArkValue<Opt_String>(Ark_Empty());
    options.placeholder = ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr);
    options.icon = ArkValue<Opt_String>(Ark_Empty());

    auto controllerPtr =
        fullAPI_->getAccessors()->getSearchControllerAccessor()->construct();
    auto peerImplPtr = reinterpret_cast<SearchControllerPeer*>(controllerPtr);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);

    options.controller = Converter::ArkValue<Opt_SearchController>(controllerPtr);
    auto optOptions = ArkValue<Opt_SearchOptions>(options);

    modifier_->setSearchOptions(node_, &optOptions);

    auto pattern = frameNode->GetPattern<SearchPattern>();
    EXPECT_NE(pattern, nullptr);
    auto controller = pattern->GetSearchController();
    EXPECT_NE(controller, nullptr);

    EXPECT_EQ(peerImplPtr->GetController(), controller);

    Ark_NativePointer finalizerPtr =
        fullAPI_->getAccessors()->getSearchControllerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(SearchControllerPeer *)>(finalizerPtr);
    EXPECT_NE(finalyzer, nullptr);
    finalyzer(reinterpret_cast<SearchControllerPeer *>(controllerPtr));
}

/**
 * @tc.name: setInputFilterTest
 * @tc.desc: Check the functionality of setInputFilter
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setInputFilterTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_TRUE(textFieldChild);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_TRUE(textFieldEventHub);
    struct CheckEvent {
        int32_t nodeId;
        std::string textBreakpoints;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto callback = [] (const Ark_Int32 resourceId, const Ark_String breakpoints) {
        checkEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
            .textBreakpoints = Convert<std::string>(breakpoints),
        };
    };
    auto arkCallback = ArkValue<Callback_String_Void>(callback, textFieldChild->GetId());
    auto optCallback = ArkValue<Opt_Callback_String_Void>(arkCallback);
    auto sendResource = ArkUnion<Ark_ResourceStr, Ark_String>(ArkValue<Ark_String>(ERROR_TEXT, Converter::FC));
    modifier_->setInputFilter(node_, &sendResource, &optCallback);
    textFieldEventHub->FireOnInputFilterError(ERROR_TEXT);
    ASSERT_TRUE(checkEvent);
    auto jsonValue = GetJsonValue(node_);
    auto filterValue = GetAttrValue<std::string>(jsonValue, INPUT_FILTER_ATTR);
    EXPECT_EQ(checkEvent->nodeId, textFieldChild->GetId());
    EXPECT_EQ(checkEvent->textBreakpoints, UtfUtils::Str16ToStr8(ERROR_TEXT));
    EXPECT_EQ(filterValue, UtfUtils::Str16ToStr8(ERROR_TEXT));
    // reset callback
    optCallback = ArkValue<Opt_Callback_String_Void>();
    checkEvent.reset();
    modifier_->setInputFilter(node_, &sendResource, &optCallback);
    textFieldEventHub->FireOnInputFilterError(ERROR_TEXT);
    ASSERT_FALSE(checkEvent);
}

/**
 * @tc.name: setOnTextSelectionChangeTest
 * @tc.desc: Check the functionality of setOnTextSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnTextSelectionChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnTextSelectionChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    OnTextSelectionChangeCallback onTextSelectionChangeCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Number selectionStart, const Ark_Number selectionEnd) {
            g_startValue = Convert<int32_t>(selectionStart);
            g_endValue = Convert<int32_t>(selectionEnd);
        }
    };
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();

    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        modifier_->setOnTextSelectionChange(node_, &onTextSelectionChangeCallback);
        textFieldEventHub->FireOnSelectionChange(value, value);
        EXPECT_EQ(g_startValue, expectVal);
        EXPECT_EQ(g_endValue, expectVal);
    }
}

/**
 * @tc.name: setOnCopyTest
 * @tc.desc: Test Seacrh setOnCopy event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnCopyTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnCopy, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    Callback_String_Void onCopyCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, Ark_String value) {
            g_EventTestString = Convert<std::u16string>(value);
        }
    };
    g_EventTestString.clear();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnCopy(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    modifier_->setOnCopy(node_, &onCopyCallback);
    textFieldEventHub->FireOnCopy(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, CHECK_TEXT);
}

/**
 * @tc.name: setOnCutTest
 * @tc.desc: Test Seacrh setOnCut event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnCutTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnCut, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    Callback_String_Void onCutCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, Ark_String value) {
            g_EventTestString = Convert<std::u16string>(value);
        }
    };
    g_EventTestString = EMPTY_TEXT;
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnCut(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    modifier_->setOnCut(node_, &onCutCallback);
    textFieldEventHub->FireOnCut(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, CHECK_TEXT);
}

/**
 * @tc.name: setOnCutTest
 * @tc.desc: Test Seacrh setOnCut event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnPasteTestCallEvent, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnPaste, nullptr);
    TextCommonEvent event;
    const std::u16string testString = u"testText";
    const int contextId = 99999;
    struct CheckEvent {
        int32_t resourceId;
        std::u16string content;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .content = Convert<std::u16string>(content),
        };
        if (event) {
            event->HandlePreventDefault();
        }
    };
    auto arkCallback = ArkValue<OnPasteCallback>(testCallback, contextId);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    modifier_->setOnPaste(node_, &arkCallback);
    EXPECT_FALSE(checkEvent);
    EXPECT_FALSE(event.IsPreventDefault());
    textFieldEventHub->FireOnPasteWithEvent(testString, event);
    ASSERT_TRUE(checkEvent);
    EXPECT_TRUE(event.IsPreventDefault());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->content, testString);
}

/**
 * @tc.name: setOnPasteTest
 * @tc.desc: Test Seacrh setOnPaste event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnPasteTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnPaste, nullptr);
    TextCommonEvent event;
    const std::u16string testString = u"testText";
    const int contextId = 99999;
    struct CheckEvent {
        int32_t resourceId;
        std::u16string content;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .content = Convert<std::u16string>(content),
        };
    };
    auto arkCallback = ArkValue<OnPasteCallback>(testCallback, contextId);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    modifier_->setOnPaste(node_, &arkCallback);
    EXPECT_FALSE(checkEvent);
    EXPECT_FALSE(event.IsPreventDefault());
    textFieldEventHub->FireOnPasteWithEvent(testString, event);
    ASSERT_TRUE(checkEvent);
    EXPECT_FALSE(event.IsPreventDefault());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->content, testString);
}

/**
 * @tc.name: setOnContentScrollTest
 * @tc.desc: Check the functionality of setOnContentScroll
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnContentScrollTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnContentScroll, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    OnContentScrollCallback onContentScroll = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, Ark_Number totalOffsetX, Ark_Number totalOffsetY) {
            g_scrollX = Convert<float>(totalOffsetX);
            g_scrollY = Convert<float>(totalOffsetY);
        }
    };
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();

    for (const auto& [value, expectVal] : FLOAT_NUMBER_TEST_PLAN) {
        modifier_->setOnContentScroll(node_, &onContentScroll);
        textFieldEventHub->FireOnScrollChangeEvent(value, value);
        EXPECT_EQ(g_scrollX, expectVal);
        EXPECT_EQ(g_scrollY, expectVal);
    }
}

/**
 * @tc.name: setOnEditChangeTest
 * @tc.desc: Test Seacrh setOnEditChange event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnEditChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Boolean_Void onEditChange = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Boolean isEditChange) {
            g_isEditChangeTest = isEditChange;
        }
    };
    modifier_->setOnEditChange(node_, &onEditChange);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    EXPECT_EQ(g_isEditChangeTest, true);
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnEditChanged(false);
    EXPECT_EQ(g_isEditChangeTest, false);
    textFieldEventHub->FireOnEditChanged(true);
    EXPECT_EQ(g_isEditChangeTest, true);
}
/**
 * @tc.name: setOnSubmit0Test
 * @tc.desc: Test Seacrh setOnSubmit0 event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnSubmit0Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnSubmit0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    static std::u16string testString;
    Callback_String_Void onSubmit0Callback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_String value) {
            testString.clear();
            testString.append(Converter::Convert<std::u16string>(value));
        }
    };

    testString.clear();
    modifier_->setOnSubmit0(node_, &onSubmit0Callback);
    auto searchEventHub = frameNode->GetEventHub<SearchEventHub>();
    EXPECT_EQ(testString, EMPTY_TEXT);
    ASSERT_NE(searchEventHub, nullptr);
    NG::TextFieldCommonEvent event;
    searchEventHub->FireOnSubmit(CHECK_TEXT, event);
    EXPECT_EQ(testString, CHECK_TEXT);
    searchEventHub->FireOnSubmit(EMPTY_TEXT, event);
    EXPECT_EQ(testString, EMPTY_TEXT);
}

/**
 * @tc.name: setOnSubmit1Test
 * @tc.desc: Test Seacrh setOnSubmit1 event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnSubmit1Test, TestSize.Level1)
{
    static const int expectedResId = 123;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::u16string testString;
    auto onSubmitFunc = [](
        Ark_VMContext, Ark_Int32 resourceId, const Ark_String searchContent, const Opt_SubmitEvent event
    ) {
        auto value = Converter::Convert<std::u16string>(searchContent);
        auto eventValue = Converter::OptConvert<Ark_SubmitEvent>(event);
        ASSERT_TRUE(eventValue);
        auto peer = eventValue.value();
        ASSERT_NE(peer, nullptr);
        auto submitEventInfo = peer->GetEventInfo();
        ASSERT_NE(submitEventInfo, nullptr);
        EXPECT_EQ(submitEventInfo->GetText(), value);
        GeneratedModifier::GetSubmitEventAccessor()->destroyPeer(peer);
        EXPECT_EQ(resourceId, expectedResId);
        testString.clear();
        testString.append(value);
    };

    auto func = Converter::ArkValue<SearchSubmitCallback>(onSubmitFunc, expectedResId);
    testString.clear();
    modifier_->setOnSubmit1(node_, &func);
    NG::TextFieldCommonEvent event;
    EXPECT_EQ(testString, EMPTY_TEXT);
    eventHub->FireOnSubmit(CHECK_TEXT, event);
    EXPECT_EQ(testString, CHECK_TEXT);
    eventHub->FireOnSubmit(EMPTY_TEXT, event);
    EXPECT_EQ(testString, EMPTY_TEXT);
}

/**
 * @tc.name: setOnChangeTest
 * @tc.desc: Test Seacrh setOnChange event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    static std::u16string eventTestString = u"";
    static int32_t eventTestOffset = 0;
    EditableTextOnChangeCallback onChangeCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_String value, const Opt_PreviewText previewText,
            Opt_TextChangeOptions options) {
            auto convValue = Converter::Convert<std::u16string>(value);
            auto convPreviewText = Converter::OptConvert<PreviewText>(previewText).value_or(PREVIEW_TEXT);
            eventTestOffset = convPreviewText.offset;
            eventTestString.append(convValue).append(convPreviewText.value);
        }
    };

    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    EXPECT_EQ(eventTestString, EMPTY_TEXT);
    EXPECT_EQ(eventTestOffset, 0);
    modifier_->setOnChange(node_, &onChangeCallback);
    textFieldEventHub->FireOnChange({.value = CHECK_TEXT, .previewText = PREVIEW_TEXT});
    std::u16string checkString = CHECK_TEXT;
    checkString.append(PREVIEW_TEXT.value);
    EXPECT_EQ(eventTestString, checkString);
    EXPECT_EQ(eventTestOffset, PREVIEW_TEXT.offset);
}

/**
 * @tc.name: setOnWillInsertTest
 * @tc.desc: Test Seacrh setOnWillInsert event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnWillInsertTest, TestSize.Level1)
{
    static const Ark_Int32 expectedResId = 123;
    auto onWillInsertHandler = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_InsertValue data,
        const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Convert<std::u16string>(data.insertValue), CHECK_TEXT);
        auto result = Convert<int32_t>(data.insertOffset) > 0;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkFunc = Converter::ArkValue<Callback_InsertValue_Boolean>(nullptr, onWillInsertHandler, expectedResId);
    modifier_->setOnWillInsert(node_, &arkFunc);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);

    {
        InsertValueInfo checkValue = { .insertOffset = AINT32_POS, .insertValue = CHECK_TEXT };
        auto returnVal = textFieldEventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_TRUE(returnVal);
    }

    {
        InsertValueInfo checkValue = { .insertOffset = AINT32_NEG, .insertValue = CHECK_TEXT };
        auto returnVal = textFieldEventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_FALSE(returnVal);
    }
}

/**
 * @tc.name: setOnDidInsertTest
 * @tc.desc: Test Seacrh setOnDidInsert event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnDidInsertTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    EXPECT_NE(textFieldEventHub, nullptr);
    static std::u16string eventTestString = u"";
    static int32_t eventTestOffset = 0;
    Callback_InsertValue_Void onDidInsert = {
        .resource = {.resourceId = frameNode->GetId()},
        .call =[](Ark_Int32 nodeId, const Ark_InsertValue data) {
            eventTestString = Convert<std::u16string>(data.insertValue);
            eventTestOffset = Convert<int32_t>(data.insertOffset);
        }
    };

    InsertValueInfo checkValueDefault;
    textFieldEventHub->FireOnDidInsertValueEvent(checkValueDefault);
    EXPECT_EQ(eventTestString, EMPTY_TEXT);
    EXPECT_EQ(eventTestOffset, 0);
    modifier_->setOnDidInsert(node_, &onDidInsert);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        InsertValueInfo checkValue = { .insertOffset = value, .insertValue = CHECK_TEXT };
        textFieldEventHub->FireOnDidInsertValueEvent(checkValue);
        EXPECT_EQ(eventTestString, CHECK_TEXT);
        EXPECT_EQ(eventTestOffset, expectVal);
    }
}

/**
 * @tc.name: setOnWillDeleteTest
 * @tc.desc: Test Seacrh setOnWillDelete event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnWillDeleteTest, TestSize.Level1)
{
    static const Ark_Int32 expectedResId = 123;
    static const Ark_Int32 expectedOffset = AINT32_POS;

    ASSERT_NE(modifier_->setOnWillDelete, nullptr);
    auto onWillDeleteHandler = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_DeleteValue data, const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Convert<std::u16string>(data.deleteValue), CHECK_TEXT);
        EXPECT_EQ(Convert<int32_t>(data.deleteOffset), expectedOffset);
        auto willDeleteDirection = OptConvert<TextDeleteDirection>(data.direction);
        auto result = willDeleteDirection == TextDeleteDirection::FORWARD;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkFunc = Converter::ArkValue<Callback_DeleteValue_Boolean>(nullptr, onWillDeleteHandler, expectedResId);
    modifier_->setOnWillDelete(node_, &arkFunc);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    DeleteValueInfo checkValueDefault;

    {
        DeleteValueInfo checkValue = {
            .deleteOffset = expectedOffset, .deleteValue = CHECK_TEXT, .direction = TextDeleteDirection::FORWARD
        };
        auto checkVal = textFieldEventHub->FireOnWillDeleteEvent(checkValue);
        EXPECT_TRUE(checkVal);
    }

    {
        DeleteValueInfo checkValue = {
            .deleteOffset = expectedOffset, .deleteValue = CHECK_TEXT, .direction = TextDeleteDirection::BACKWARD
        };
        auto checkVal = textFieldEventHub->FireOnWillDeleteEvent(checkValue);
        EXPECT_FALSE(checkVal);
    }
}

/**
 * @tc.name: setOnDidDeleteTest
 * @tc.desc: Test Seacrh setOnDidlDelete event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setOnDidDeleteTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDidDelete, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    g_EventTestString = u"";
    g_EventTestOffset = 0;
    Callback_DeleteValue_Void onDidDeleteCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_DeleteValue data) {
            g_EventTestString = Convert<std::u16string>(data.deleteValue);
            g_EventTestOffset = Convert<int32_t>(data.deleteOffset);
            auto didDeleteDirection = OptConvert<TextDeleteDirection>(data.direction);
            if (didDeleteDirection) {
                g_deleteDirection = didDeleteDirection.value();
            }
        }
    };
    g_deleteDirection = TextDeleteDirection::FORWARD;
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    DeleteValueInfo checkValueDefault;
    textFieldEventHub->FireOnDidDeleteValueEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    EXPECT_EQ(g_deleteDirection, TextDeleteDirection::FORWARD);
    modifier_->setOnDidDelete(node_, &onDidDeleteCallback);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        for (const auto& deleteDirection : DELETE_DIRECTION_TEST_PLAN) {
            DeleteValueInfo checkValue = {
                .deleteOffset = value, .deleteValue = CHECK_TEXT, .direction = deleteDirection
            };
            textFieldEventHub->FireOnDidDeleteValueEvent(checkValue);
            EXPECT_EQ(g_EventTestString, CHECK_TEXT);
            EXPECT_EQ(g_EventTestOffset, expectVal);
            EXPECT_EQ(g_deleteDirection, deleteDirection);
        }
    }
}

/**
 * @tc.name: setEditMenuOptionsTest
 * @tc.desc: setEditMenuOptions test
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierCallbackTest, setEditMenuOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEditMenuOptions, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
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
    auto arkCreateCallback = Converter::ArkValue<
        AsyncCallback_Array_TextMenuItem_Array_TextMenuItem>(testOnCreateMenuCallback, testID);

    auto testOnMenuItemClickCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation) {
        auto item = Converter::OptConvert<MenuOptionsParam>(menuItem);
        ASSERT_TRUE(item.has_value());
        ASSERT_TRUE(item->content.has_value());
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(*item->content == TEST_CONTENT_ONE));
    };
    auto arkClickCallback = Converter::ArkValue<
        AsyncCallback_TextMenuItem_TextRange_Boolean>(testOnMenuItemClickCallback, testID);

    Ark_EditMenuOptions options {
        .onCreateMenu = arkCreateCallback,
        .onMenuItemClick = arkClickCallback
    };

    SelectOverlayInfo selectOverlayInfo;
    auto params = GetMenuItemParams();
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback == nullptr);
    modifier_->setEditMenuOptions(node_, &options);
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    ASSERT_NE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback, nullptr);
    selectOverlayInfo.onCreateCallback.onCreateMenuCallback(params);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, testID);

    ASSERT_NE(selectOverlayInfo.onCreateCallback.onMenuItemClick, nullptr);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[0]));
    EXPECT_FALSE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[1]));
}
} // namespace OHOS::Ace::NG
