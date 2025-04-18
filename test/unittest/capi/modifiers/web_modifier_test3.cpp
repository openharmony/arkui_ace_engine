/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "test/unittest/capi/stubs/friend_class_accessor.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "generated/test_fixtures.h"
#include "generated/type_helpers.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "generated/type_helpers.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/interfaces/native/implementation/web_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_modifier_callbacks.h"
#endif // WEB_SUPPORTED
#include "test/unittest/capi/stubs/mock_web_pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
struct SelectionMenuOptionsExt {
    std::optional<Callback_Void> onAppear;
    std::optional<Callback_Void> onDisappear;
    std::optional<CustomNodeBuilder> preview;
    std::optional<Ark_MenuType> menuType;
};

namespace Converter {
void AssignArkValue(Ark_ScriptItem& dst, const std::pair<std::string, std::vector<std::string>>& src)
{
    dst.script = Converter::ArkValue<Ark_String>(src.first, Converter::FC);
    dst.scriptRules = Converter::ArkValue<Array_String>(src.second, Converter::FC);
}
void AssignArkValue(Array_ScriptItem& dst, const ScriptItems& src)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> scriptItems;
    for (const auto& [key, value] : src) {
        auto item = std::make_pair(key, value);
        scriptItems.emplace_back(item);
    }
    dst = Converter::ArkValue<Array_ScriptItem>(scriptItems, Converter::FC);
}
void AssignArkValue(Ark_SelectionMenuOptionsExt& dst, const SelectionMenuOptionsExt& src, ConvContext* ctx = nullptr)
{
    dst.onAppear = Converter::ArkValue<Opt_Callback_Void>(src.onAppear);
    dst.onDisappear = Converter::ArkValue<Opt_Callback_Void>(src.onDisappear);
    dst.preview = Converter::ArkValue<Opt_CustomNodeBuilder>(src.preview);
    dst.menuType = Converter::ArkValue<Opt_MenuType>(src.menuType);
}
} // namespace Converter

namespace {
const auto ATTRIBUTE_BIND_SELECTION_MENU_NAME = "bindSelectionMenu";
const auto ATTRIBUTE_BIND_SELECTION_MENU_DEFAULT_VALUE = "";
const std::string TEST_CONTENT_ONE = "ContentTestOne";
const std::string TEST_CONTENT_TWO = "ContentTestTwo";
const auto ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_NAME = "defaultTextEncodingFormat";
const auto ATTRIBUTE_BLUR_ON_KEYBOARD_HIDE_MODE_NAME = "blurOnKeyboardHideMode";
const auto ATTRIBUTE_BLUR_ON_KEYBOARD_HIDE_MODE_DEFAULT_VALUE = "BlurOnKeyboardHideMode.SILENT";
const auto ATTRIBUTE_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT_NAME = "enableFollowSystemFontWeight";
const auto ATTRIBUTE_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT_DEFAULT_VALUE = "empty";
const auto ATTRIBUTE_ENABLE_WEB_AVSESSION_NAME = "enableWebAVSession";
const auto ATTRIBUTE_ENABLE_WEB_AVSESSION_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_OPTIMIZE_PARSER_BUDGET_NAME = "optimizeParserBudget";
const auto ATTRIBUTE_OPTIMIZE_PARSER_BUDGET_DEFAULT_VALUE = "false";

const std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringValidValues = {
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc" },
    { "\"\"", Converter::ArkValue<Ark_String>(""), "UTF-8" },
    { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz"), "xyz" },
};
const std::vector<std::tuple<OHOS::Ace::ScriptItems, std::vector<std::string>>> testFixtureScriptsValidValues = {
    {
        {
            { "script1", { "rule11", "rule12", "rule13" } },
            { "script2", { "rule21", "rule22", "rule23" } },
            { "script3", { "rule31", "rule32", "rule33" } },
        },
        { "script1", "script2", "script3" },
    },
    {
        {
            { "script4", { "rule41", "rule42", "rule43" } },
            { "script5", { "rule51", "rule52", "rule53" } },
        },
        { "script4", "script5" },
    },
    {
        {
            { "script6", { "rule61", "rule62", "rule63" } },
        },
        { "script6" },
    },
};
const std::vector<OHOS::Ace::ScriptItems> testFixtureScriptsInvalidValues = {
    {
        { "", { "rule11", "rule12", "rule13" } },
        { "script2", {} },
    },
    {
        { "", {} },
    },
};
class MockWebFaviconReceived : public OHOS::Ace::WebFaviconReceived {
public:
    MOCK_METHOD(const void*, GetData, ());
    MOCK_METHOD(size_t, GetWidth, ());
    MOCK_METHOD(size_t, GetHeight, ());
    MOCK_METHOD(int, GetColorType, ());
    MOCK_METHOD(int, GetAlphaType, ());
};
} // namespace

class WebModifierTest3 : public ModifierTestBase<GENERATED_ArkUIWebModifier,
    &GENERATED_ArkUINodeModifiers::getWebModifier, GENERATED_ARKUI_WEB> {
public:
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

/*
 * @tc.name: bindSelectionMenuTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, bindSelectionMenuTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BIND_SELECTION_MENU_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BIND_SELECTION_MENU_DEFAULT_VALUE) <<
        "Default value for attribute 'BindSelectionMenu'";
}

/*
 * @tc.name: bindSelectionMenuTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, bindSelectionMenuTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSelectionMenu, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    CustomNodeBuilderTestHelper<WebModifierTest3> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    using OneTestStep = std::tuple<Ark_WebElementType, CustomNodeBuilder, Ark_WebResponseType>;

    static const std::vector<OneTestStep> testPlan = {
        {ARK_WEB_ELEMENT_TYPE_IMAGE, builder, ARK_WEB_RESPONSE_TYPE_LONG_PRESS},
    };

    std::unique_ptr<JsonValue> fullJson;
    std::string resultValue;
    SelectionMenuOptionsExt selectionMenuOptions = {.onAppear = std::nullopt, .onDisappear = std::nullopt,
        .preview = std::nullopt, .menuType = Ark_MenuType::ARK_MENU_TYPE_SELECTION_MENU};
    auto options = Converter::ArkValue<Opt_SelectionMenuOptionsExt>(selectionMenuOptions);

    #ifdef WEB_SUPPORTED_TEST
    int callsCount(0);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    ASSERT_NE(webPattern, nullptr);
    #endif // WEB_SUPPORTED

    for (auto [spanType, builder, responseType]: testPlan) {
        modifier_->setBindSelectionMenu(node_, spanType, &builder, responseType, &options);
        #ifdef WEB_SUPPORTED_TEST
        WebElementType convType = Converter::OptConvert<WebElementType>(spanType).value();
        ResponseType convResponseType = Converter::OptConvert<ResponseType>(responseType).value();
        std::shared_ptr<WebPreviewSelectionMenuParam> reviewSelectionMenuParams =
            webPattern->GetPreviewSelectionMenuParams(convType, convResponseType);
        ASSERT_NE(reviewSelectionMenuParams, nullptr);
        reviewSelectionMenuParams->menuBuilder();
        EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
        #endif // WEB_SUPPORTED

        fullJson = GetJsonValue(node_);
        resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_BIND_SELECTION_MENU_NAME);
    }
    std::string expectedValue = "";
    EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
}

/*
 * @tc.name: setDefaultTextEncodingFormatValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setDefaultTextEncodingFormatValidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    Ark_String initValueDefaultTextEncodingFormat;
    // Initial setup
    initValueDefaultTextEncodingFormat = std::get<1>(testFixtureStringValidValues[0]);
    auto checkValue = [this, &initValueDefaultTextEncodingFormat](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueDefaultTextEncodingFormat = initValueDefaultTextEncodingFormat;
        inputValueDefaultTextEncodingFormat = value;
        modifier_->setDefaultTextEncodingFormat(node_, &inputValueDefaultTextEncodingFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_NAME);
        EXPECT_EQ(resultStr, expectedStr);
    };
    for (auto& [input, value, expected] : testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
#endif
}

/**
 * @tc.name: setEditMenuOptionsTest
 * @tc.desc: setEditMenuOptions test
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setEditMenuOptionsTest, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setEditMenuOptions, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t testID = 323;
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testOnCreateMenuCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Array_TextMenuItem menuItems, const Callback_Array_TextMenuItem_Void continuation) {
        checkEvent = {
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
    pattern->OnUpdateOnCreateMenuCallback(selectOverlayInfo);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback == nullptr);
    modifier_->setEditMenuOptions(node_, &options);
    pattern->OnUpdateOnCreateMenuCallback(selectOverlayInfo);
    ASSERT_NE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback, nullptr);
    selectOverlayInfo.onCreateCallback.onCreateMenuCallback(params);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, testID);

    ASSERT_NE(selectOverlayInfo.onCreateCallback.onMenuItemClick, nullptr);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[0]));
    EXPECT_FALSE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[1]));
#endif
}

/*
 * @tc.name: onFaviconReceivedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, onFaviconReceivedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    auto webFaviconReceived = Referenced::MakeRefPtr<MockWebFaviconReceived>();

    struct CheckEvent {
        int32_t resourceId;
        Ark_PixelMap pixelMapPeer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnFaviconReceivedEvent parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .pixelMapPeer = parameter.favicon
        };
    };

    Callback_OnFaviconReceivedEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnFaviconReceivedEvent_Void>(checkCallback, contextId);

    modifier_->setOnFaviconReceived(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    EXPECT_CALL(*webFaviconReceived, GetData()).Times(1).WillOnce(Return(nullptr));
    EXPECT_CALL(*webFaviconReceived, GetWidth()).Times(1).WillOnce(Return(static_cast<size_t>(200)));
    EXPECT_CALL(*webFaviconReceived, GetHeight()).Times(1).WillOnce(Return(static_cast<size_t>(300)));
    EXPECT_CALL(*webFaviconReceived, GetColorType()).Times(1).WillOnce(Return(1));
    EXPECT_CALL(*webFaviconReceived, GetAlphaType()).Times(1).WillOnce(Return(1));
    webEventHub->FireOnFaviconReceivedEvent(
        std::make_shared<FaviconReceivedEvent>(webFaviconReceived));
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    ASSERT_NE(checkEvent->pixelMapPeer, nullptr);
    ASSERT_NE(checkEvent->pixelMapPeer->pixelMap, nullptr);
}

/*
 * @tc.name: setBlurOnKeyboardHideModeDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setBlurOnKeyboardHideModeDefaultValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setBlurOnKeyboardHideMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLUR_ON_KEYBOARD_HIDE_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLUR_ON_KEYBOARD_HIDE_MODE_DEFAULT_VALUE)
        << "Default value for attribute 'blurOnKeyboardHideMode'";
#endif
}

/*
 * @tc.name: setBlurOnKeyboardHideModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setBlurOnKeyboardHideValidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setBlurOnKeyboardHideMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    auto checkValue = [this](const std::string& input, const std::string& expectedStr,
                          const Ark_BlurOnKeyboardHideMode& value) {
        modifier_->setBlurOnKeyboardHideMode(node_, value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLUR_ON_KEYBOARD_HIDE_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBlurOnKeyboardHideMode, attribute: blurOnKeyboardHideMode";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureEnumBlurOnKeyboardHideModeValidValues) {
        checkValue(input, expected, value);
    }
#endif
}

/*
 * @tc.name: setBlurOnKeyboardHideModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setBlurOnKeyboardHideInvalidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setBlurOnKeyboardHideMode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    auto checkValue = [this](const std::string& input, const Ark_BlurOnKeyboardHideMode& value) {
        modifier_->setBlurOnKeyboardHideMode(node_, value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLUR_ON_KEYBOARD_HIDE_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLUR_ON_KEYBOARD_HIDE_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlurOnKeyboardHideMode, attribute: blurOnKeyboardHideMode";
    };
    for (auto& [input, value] : Fixtures::testFixtureEnumBlurOnKeyboardHideModeInvalidValues) {
        checkValue(input, value);
    }
#endif
}

/*
 * @tc.name: setEnableFollowSystemFontWeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setEnableFollowSystemFontWeightTest, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setEnableFollowSystemFontWeight, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'enableFollowSystemFontWeight'";

    auto checkValue = [this](const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        modifier_->setEnableFollowSystemFontWeight(node_, value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setEnableFollowSystemFontWeight, attribute: enableFollowSystemFontWeight";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
#endif
}

/*
 * @tc.name: setEnableWebAVSessionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setEnableWebAVSessionTest, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setEnableWebAVSession, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_WEB_AVSESSION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_WEB_AVSESSION_DEFAULT_VALUE)
        << "Default value for attribute 'enableWebAVSession'";

    auto checkValue = [this](const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        modifier_->setEnableWebAVSession(node_, value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_WEB_AVSESSION_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setEnableFollowSystemFontWeight, attribute: enableFollowSystemFontWeight";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
#endif
}

/*
 * @tc.name: setOptimizeParserBudgetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setOptimizeParserBudgetTest, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setOptimizeParserBudget, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIMIZE_PARSER_BUDGET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTIMIZE_PARSER_BUDGET_DEFAULT_VALUE)
        << "Default value for attribute 'optimizeParserBudget'";

    auto checkValue = [this](const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        modifier_->setOptimizeParserBudget(node_, value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIMIZE_PARSER_BUDGET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setEnableFollowSystemFontWeight, attribute: enableFollowSystemFontWeight";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
#endif
}

/*
 * @tc.name: setRunJavaScriptOnDocumentStartValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setRunJavaScriptOnDocumentStartValidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setRunJavaScriptOnDocumentStart, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    auto scripts = pattern->GetJavaScriptOnDocumentStartScriptItems();
    auto scriptsByOrder = pattern->GetJavaScriptOnDocumentStartSctiptItemsByOrder();
    ASSERT_EQ(scripts, std::nullopt);
    ASSERT_EQ(scriptsByOrder, std::nullopt);
    EXPECT_TRUE(scripts->empty());
    EXPECT_TRUE(scriptsByOrder->empty());

    auto checkValue = [this, &pattern](const ScriptItems& value, const std::vector<std::string>& expected) {
        Array_ScriptItem array = Converter::ArkValue<Array_ScriptItem>(value, Converter::FC);
        modifier_->setRunJavaScriptOnDocumentStart(node_, &array);
        auto scripts = pattern->GetJavaScriptOnDocumentStartScriptItems();
        auto scriptsByOrder = pattern->GetJavaScriptOnDocumentStartSctiptItemsByOrder();
        ASSERT_NE(scripts, std::nullopt);
        ASSERT_NE(scriptsByOrder, std::nullopt);
        EXPECT_EQ(scripts.value(), value);
        EXPECT_EQ(scriptsByOrder.value(), expected);
    };
    for (auto& [value, expected] : testFixtureScriptsValidValues) {
        checkValue(value, expected);
    }
#endif
}

/*
 * @tc.name: setRunJavaScriptOnDocumentStartInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setRunJavaScriptOnDocumentStartInvalidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setRunJavaScriptOnDocumentStart, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    auto checkValue = [this, &pattern](const ScriptItems& value) {
        Array_ScriptItem array = Converter::ArkValue<Array_ScriptItem>(value, Converter::FC);
        modifier_->setRunJavaScriptOnDocumentStart(node_, &array);
        auto scripts = pattern->GetJavaScriptOnDocumentStartScriptItems();
        auto scriptsByOrder = pattern->GetJavaScriptOnDocumentStartSctiptItemsByOrder();
        ASSERT_TRUE(scripts.has_value());
        EXPECT_TRUE(scripts->empty());
        ASSERT_TRUE(scriptsByOrder.has_value());
        EXPECT_TRUE(scriptsByOrder->empty());
    };
    for (const auto& value : testFixtureScriptsInvalidValues) {
        checkValue(value);
    }
#endif
}

/*
 * @tc.name: setRunJavaScriptOnDocumentEndValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setRunJavaScriptOnDocumentEndValidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setRunJavaScriptOnDocumentEnd, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    auto scripts = pattern->GetJavaScriptOnDocumentEndScriptItems();
    auto scriptsByOrder = pattern->GetJavaScriptOnDocumentEndScriptItemsByOrder();
    ASSERT_EQ(scripts, std::nullopt);
    ASSERT_EQ(scriptsByOrder, std::nullopt);
    EXPECT_TRUE(scripts->empty());
    EXPECT_TRUE(scriptsByOrder->empty());

    auto checkValue = [this, &pattern](const ScriptItems& value, const std::vector<std::string>& expected) {
        Array_ScriptItem array = Converter::ArkValue<Array_ScriptItem>(value, Converter::FC);
        modifier_->setRunJavaScriptOnDocumentEnd(node_, &array);
        auto scripts = pattern->GetJavaScriptOnDocumentEndScriptItems();
        auto scriptsByOrder = pattern->GetJavaScriptOnDocumentEndScriptItemsByOrder();
        ASSERT_NE(scripts, std::nullopt);
        ASSERT_NE(scriptsByOrder, std::nullopt);
        EXPECT_EQ(scripts.value(), value);
        EXPECT_EQ(scriptsByOrder.value(), expected);
    };
    for (auto& [value, expected] : testFixtureScriptsValidValues) {
        checkValue(value, expected);
    }
#endif
}

/*
 * @tc.name: setRunJavaScriptOnDocumentEndInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setRunJavaScriptOnDocumentEndInvalidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setRunJavaScriptOnDocumentEnd, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    auto checkValue = [this, &pattern](const ScriptItems& value) {
        Array_ScriptItem array = Converter::ArkValue<Array_ScriptItem>(value, Converter::FC);
        modifier_->setRunJavaScriptOnDocumentEnd(node_, &array);
        auto scripts = pattern->GetJavaScriptOnDocumentEndScriptItems();
        auto scriptsByOrder = pattern->GetJavaScriptOnDocumentEndScriptItemsByOrder();
        ASSERT_TRUE(scripts.has_value());
        EXPECT_TRUE(scripts->empty());
        ASSERT_TRUE(scriptsByOrder.has_value());
        EXPECT_TRUE(scriptsByOrder->empty());
    };
    for (const auto& value : testFixtureScriptsInvalidValues) {
        checkValue(value);
    }
#endif
}

/*
 * @tc.name: setRunJavaScriptOnHeadEndValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setRunJavaScriptOnHeadEndValidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setRunJavaScriptOnHeadEnd, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    auto scripts = pattern->GetJavaScriptOnHeadReadyScriptItems();
    auto scriptsByOrder = pattern->GetJavaScriptOnHeadReadyScriptItemsByOrder();
    ASSERT_EQ(scripts, std::nullopt);
    ASSERT_EQ(scriptsByOrder, std::nullopt);
    EXPECT_TRUE(scripts->empty());
    EXPECT_TRUE(scriptsByOrder->empty());

    auto checkValue = [this, &pattern](const ScriptItems& value, const std::vector<std::string>& expected) {
        Array_ScriptItem array = Converter::ArkValue<Array_ScriptItem>(value, Converter::FC);
        modifier_->setRunJavaScriptOnHeadEnd(node_, &array);
        auto scripts = pattern->GetJavaScriptOnHeadReadyScriptItems();
        auto scriptsByOrder = pattern->GetJavaScriptOnHeadReadyScriptItemsByOrder();
        ASSERT_NE(scripts, std::nullopt);
        ASSERT_NE(scriptsByOrder, std::nullopt);
        EXPECT_EQ(scripts.value(), value);
        EXPECT_EQ(scriptsByOrder.value(), expected);
    };
    for (auto& [value, expected] : testFixtureScriptsValidValues) {
        checkValue(value, expected);
    }
#endif
}

/*
 * @tc.name: setRunJavaScriptOnHeadEndInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest3, setRunJavaScriptOnHeadEndInvalidValues, TestSize.Level1)
{
#ifdef WEB_SUPPORTED
    ASSERT_NE(modifier_->setRunJavaScriptOnHeadEnd, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(pattern, nullptr);

    auto checkValue = [this, &pattern](const ScriptItems& value) {
        Array_ScriptItem array = Converter::ArkValue<Array_ScriptItem>(value, Converter::FC);
        modifier_->setRunJavaScriptOnHeadEnd(node_, &array);
        auto scripts = pattern->GetJavaScriptOnHeadReadyScriptItems();
        auto scriptsByOrder = pattern->GetJavaScriptOnHeadReadyScriptItemsByOrder();
        ASSERT_TRUE(scripts.has_value());
        EXPECT_TRUE(scripts->empty());
        ASSERT_TRUE(scriptsByOrder.has_value());
        EXPECT_TRUE(scriptsByOrder->empty());
    };
    for (const auto& value : testFixtureScriptsInvalidValues) {
        checkValue(value);
    }
#endif
}
} // namespace OHOS::Ace::NG
