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
#include "richeditor_modifier_test.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/implementation/rich_editor_controller_peer_impl.h"
#include "core/interfaces/native/implementation/rich_editor_styled_string_controller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {
#ifdef WRONG_GEN
static constexpr int TEST_OFFSET = 5;
static constexpr int TEST_OFFSET_2 = 7;
static constexpr int TEST_INDEX = 1;
#endif
static constexpr auto TEST_COLOR = "#FFFF0000";
static const std::u16string TEST_VALUE = u"test value";
#ifdef WRONG_GEN
static const auto TEST_VALUE_2 = u"test value 2";
static constexpr int TEST_INDEX_2 = 2;
#endif
static constexpr int TEST_FONT_WEIGHT = static_cast<int>(FontWeight::BOLD);
static const std::string COLOR_TRANSPARENT = "#00000000";
static constexpr int TEST_RESOURCE_ID = 1000;
static constexpr int32_t NODE_ID = 555;

static const auto ATTRIBUTE_COPY_OPTIONS_NAME = "CopyOption";
static const auto ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE = "CopyOptions.None";
static const auto ATTRIBUTE_COPY_OPTIONS_IN_APP_VALUE = "CopyOptions.InApp";
static const auto ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME = "enableDataDetector";
static const auto ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME = "textPreviewSupported";
static const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME = "dataDetectorConfig";
static const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_VALUE_ARR = {
    ARK_TEXT_DATA_DETECTOR_TYPE_PHONE_NUMBER,
    ARK_TEXT_DATA_DETECTOR_TYPE_URL,
    ARK_TEXT_DATA_DETECTOR_TYPE_EMAIL,
    ARK_TEXT_DATA_DETECTOR_TYPE_ADDRESS,
    ARK_TEXT_DATA_DETECTOR_TYPE_DATE_TIME,
};
static const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_VALUE = "phoneNum,url,email,location,datetime";
static const auto ATTRIBUTE_DATA_DETECTOR_STYLE_VALUE = ARK_TEXT_DECORATION_STYLE_DASHED;
static const auto ATTRIBUTE_PLACEHOLDER_NAME = "placeholder";
static const auto ATTRIBUTE_PLACEHOLDER_VALUE_NAME = "value";
static const auto ATTRIBUTE_PLACEHOLDER_STYLE_NAME = "style";
static const auto ATTRIBUTE_PLACEHOLDER_FONT_COLOR_NAME = "fontColor";
static const auto ATTRIBUTE_PLACEHOLDER_FONT_NAME = "font";
static const auto ATTRIBUTE_PLACEHOLDER_FONT_SIZE_NAME = "size";
static const auto ATTRIBUTE_PLACEHOLDER_FONT_SIZE = "30.00px";
static const auto ATTRIBUTE_PLACEHOLDER_WEIGHT_NAME = "weight";
static const auto ATTRIBUTE_PLACEHOLDER_WEIGHT_NAME_VALUE = "FontWeight.Normal";
static const auto ATTRIBUTE_PLACEHOLDER_STYLE_VALUE = "FontStyle.Normal";
static const auto ATTRIBUTE_ENTER_KEY_TYPE_NAME = "enterKeyType";
static const auto ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE = "EnterKeyType.Begin";
static const auto ATTRIBUTE_ENTER_KEY_TYPE_NEWLINE_VALUE = "EnterKeyType.NEW_LINE";
static const auto ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME = "enableKeyboardOnFocus";
static const auto ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_DEFAULT_VALUE = "true";
static const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME = "enableHapticFeedback";
static const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";
static const auto ATTRIBUTE_BAR_STATE_NAME = "barState";
static const auto ATTRIBUTE_BAR_STATE_DEFAULT = "BarState.Auto";
static const auto ATTRIBUTE_BAR_STATE_VALUE = "BarState.On";
static const auto ATTRIBUTE_CUSTOM_KB_NAME = "keyboardAvoidance";
static const auto ATTRIBUTE_CUSTOM_KB_DEFAULT_VALUE = "false";
static const auto ATTRIBUTE_CUSTOM_KB_VALUE = "true";
static const auto ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE = INT_MAX;
static const auto ATTRIBUTE_MAX_LINES_NAME = "maxLines";
static const auto ATTRIBUTE_MAX_LINES_DEFAULT_STR_VALUE = "4294967295";
static const auto ATTRIBUTE_MAX_LINES_DEFAULT_UINT_VALUE = UINT_MAX;

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
static const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" }};

using namespace testing;
using namespace testing::ext;
struct CheckEvent {
    int32_t resourceId;
    Ark_NativePointer parentNode;
};
static std::optional<CheckEvent> checkEvent = std::nullopt;
static std::optional<RefPtr<UINode>> uiNode = std::nullopt;
class RichEditorModifierTest : public ModifierTestBase<GENERATED_ArkUIRichEditorModifier,
    &GENERATED_ArkUINodeModifiers::getRichEditorModifier, GENERATED_ARKUI_RICH_EDITOR> {
public:
    void SetUp(void) override
    {
        ModifierTestBase::SetUp();
        checkEvent = std::nullopt;
    }

    CustomNodeBuilder getBuilderCb()
    {
        auto checkCallback = [](
            Ark_VMContext context,
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            checkEvent = {
                .resourceId = resourceId,
                .parentNode = parentNode
            };
            if (uiNode) {
                CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
            }
        };
        auto checkCallbackAsync = [](
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            checkEvent = {
                .resourceId = resourceId,
                .parentNode = parentNode
            };
            if (uiNode) {
                CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
            }
        };
        CustomNodeBuilder customBuilder =
            Converter::ArkValue<CustomNodeBuilder>(checkCallbackAsync, checkCallback, TEST_RESOURCE_ID);
        return customBuilder;
    }
};

/**
 * @tc.name: setRichEditorOptions0Test
 * @tc.desc: Check the functionality of setRichEditorOptions0
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setRichEditorOptions0Test, TestSize.Level1)
{
#ifdef WRONG_GEN
    ASSERT_NE(modifier_->setRichEditorOptions0, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setRichEditorOptions0(node_, nullptr);

    auto controllerUndef = Converter::ArkValue<Opt_RichEditorOptions>(Ark_Empty());
    modifier_->setRichEditorOptions0(node_, &controllerUndef.value);

    // Check the internal controller
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto internalController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(internalController, nullptr);
    auto controller = AceType::DynamicCast<RichEditorController>(internalController);
    ImageSpanOptions imageOptions;
    controller->AddImageSpan(imageOptions);

    RichEditorControllerPeer peer;
    auto options = Converter::ArkValue<Ark_RichEditorOptions>(&peer);
    modifier_->setRichEditorOptions0(node_, &options);

    TextSpanOptions textSpanOptions;
    textSpanOptions.offset = TEST_OFFSET;
    textSpanOptions.value = TEST_VALUE;
    int32_t result = peer.AddTextSpanImpl(textSpanOptions);
    ASSERT_EQ(result, TEST_INDEX);

    TextSpanOptions textSpanOptions2;
    textSpanOptions.offset = TEST_OFFSET_2;
    textSpanOptions.value = TEST_VALUE_2;
    result = peer.AddTextSpanImpl(textSpanOptions2);
    ASSERT_EQ(result, TEST_INDEX_2);
#endif
}

/**
 * @tc.name: setRichEditorOptions1Test
 * @tc.desc: Check the functionality of setRichEditorOptions1
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setRichEditorOptions1Test, TestSize.Level1)
{
#ifdef WRONG_GEN
    ASSERT_NE(modifier_->setRichEditorOptions1, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setRichEditorOptions1(node_, nullptr);

    Ark_RichEditorStyledStringOptions controllerUndef;
    controllerUndef.controller = nullptr;
    modifier_->setRichEditorOptions1(node_, &controllerUndef);

    // Check the internal controller
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto internalController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(internalController, nullptr);
    auto controller = AceType::DynamicCast<RichEditorStyledStringController>(internalController);
    ASSERT_NE(controller, nullptr);
    ASSERT_NE(controller->GetStyledString(), nullptr);

    RichEditorStyledStringControllerPeer peer;
    auto options = Converter::ArkValue<Ark_RichEditorStyledStringOptions>(&peer);
    modifier_->setRichEditorOptions1(node_, &options);

    auto string = peer.GetStyledString();
    ASSERT_NE(string, nullptr);
    peer.SetStyledString(string);
    ASSERT_NE(string, peer.GetStyledString());
#endif
}

/**
 * @tc.name: setCopyOptionTest
 * @tc.desc: Check the functionality of setCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setCopyOptionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCopyOptions, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetLayoutJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE);

    auto optionsConverted = ARK_COPY_OPTIONS_IN_APP;
    auto optOptionsConverted = Converter::ArkValue<Opt_CopyOptions>(optionsConverted);
    modifier_->setCopyOptions(node_, &optOptionsConverted);

    jsonValue = GetLayoutJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_IN_APP_VALUE);
}

/**
 * @tc.name: setEnableDataDetectorTest
 * @tc.desc: Check the functionality of setEnableDataDetector
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableDataDetectorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableDataDetector, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
    EXPECT_EQ(resultStr, "false");

    auto enabled = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnableDataDetector(node_, &enabled);

    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
    EXPECT_EQ(resultStr, "true");
}

/**
 * @tc.name: setEnablePreviewTextTest
 * @tc.desc: Check the functionality of setEnablePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setEnablePreviewTextTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnablePreviewText, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
    EXPECT_EQ(resultStr, "true");

    auto enabled = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnablePreviewText(node_, &enabled);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
    EXPECT_EQ(resultStr, "false");

    enabled = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnablePreviewText(node_, &enabled);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
    EXPECT_EQ(resultStr, "true");
}

/**
 * @tc.name: setDataDetectorConfigTest
 * @tc.desc: Check the functionality of setDataDetectorConfig
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setDataDetectorConfigTest, TestSize.Level1)
{
    Converter::ConvContext ctx;
    ASSERT_NE(modifier_->setDataDetectorConfig, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME);
    EXPECT_EQ(resultStr, "");

    Ark_TextDataDetectorConfig config;
    config.color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(TEST_COLOR);
    config.types = Converter::ArkValue<Opt_Array_TextDataDetectorType>(ATTRIBUTE_DATA_DETECTOR_CONFIG_VALUE_ARR, &ctx);
    config.decoration = Converter::ArkValue<Opt_DecorationStyleInterface>(Ark_DecorationStyleInterface{
        .style = Converter::ArkValue<Opt_TextDecorationStyle>(ATTRIBUTE_DATA_DETECTOR_STYLE_VALUE)
    });

    auto configConverted = Converter::ArkValue<Ark_TextDataDetectorConfig>(config);
    auto optConfigConverted = Converter::ArkValue<Opt_TextDataDetectorConfig>(configConverted);
    modifier_->setDataDetectorConfig(node_, &optConfigConverted);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME);
    auto jsonConfig = JsonUtil::ParseJsonString(resultStr);
    resultStr = GetAttrValue<std::string>(jsonConfig, "color");
    EXPECT_EQ(resultStr, TEST_COLOR);
    resultStr = GetAttrValue<std::string>(jsonConfig, "types");
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_VALUE);
    resultStr = GetAttrValue<std::string>(jsonConfig, "decoration");
    auto jsonStyle = JsonUtil::ParseJsonString(resultStr);
    int testValue = GetAttrValue<int>(jsonStyle, "style");
    EXPECT_EQ(testValue, static_cast<int>(ATTRIBUTE_DATA_DETECTOR_STYLE_VALUE));
}

void FixValue(std::string& value)
{
    size_t pos = 0;
    auto issue1 = "\"{\"";
    while ((pos = value.find(issue1, pos)) != std::string::npos) {
        value.replace(pos, strlen(issue1), "{\"");
        pos++;
    }
    pos = 0;
    auto issue2 = "\"}\"";
    while ((pos = value.find(issue2, pos)) != std::string::npos) {
        value.replace(pos, strlen(issue2), "\"}");
        pos++;
    }
}

/**
 * @tc.name: setPlaceholderTest
 * @tc.desc: Check the functionality of setPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholder, nullptr);

    Converter::ConvContext ctx;
    Ark_ResourceStr value = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(TEST_VALUE, &ctx);
    Ark_Font label;
    label.size = Converter::ArkValue<Opt_Length>("30px");
    label.weight = Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(TEST_FONT_WEIGHT);
    label.style = Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_NORMAL);
    Ark_PlaceholderStyle style;
    style.font = Converter::ArkValue<Opt_Font>(label);
    style.fontColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(TEST_COLOR);
    auto optStyle = Converter::ArkValue<Opt_PlaceholderStyle>(style);

    auto optValue = Converter::ArkValue<Opt_ResourceStr>(value);
    modifier_->setPlaceholder(node_, &optValue, &optStyle);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
    FixValue(resultStr);
    std::unique_ptr<JsonValue> placeholderValue = JsonUtil::ParseJsonData(resultStr.c_str());

    resultStr = GetAttrValue<std::string>(placeholderValue, ATTRIBUTE_PLACEHOLDER_VALUE_NAME);
    EXPECT_EQ(StringUtils::Str8ToStr16(resultStr), TEST_VALUE);

    std::unique_ptr<JsonValue> styleValue = placeholderValue->GetObject(ATTRIBUTE_PLACEHOLDER_STYLE_NAME);
    resultStr = GetAttrValue<std::string>(styleValue, ATTRIBUTE_PLACEHOLDER_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, TEST_COLOR);

    std::unique_ptr<JsonValue> fontValue = styleValue->GetObject(ATTRIBUTE_PLACEHOLDER_FONT_NAME);
    resultStr = GetAttrValue<std::string>(fontValue, ATTRIBUTE_PLACEHOLDER_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_SIZE);

    resultStr = GetAttrValue<std::string>(fontValue, ATTRIBUTE_PLACEHOLDER_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_WEIGHT_NAME_VALUE);

    resultStr = GetAttrValue<std::string>(fontValue, ATTRIBUTE_PLACEHOLDER_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_STYLE_VALUE);
}

/**
 * @tc.name: setCaretColorTest
 * @tc.desc: Check the functionality of setCaretColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setCaretColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCaretColor, nullptr);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setCaretColor(node_, &optValue);
        auto checkVal = GetAttrValue<std::string>(node_, "caretColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedBackgroundColorTest
 * @tc.desc: Check the functionality of setSelectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setSelectedBackgroundColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedBackgroundColor, nullptr);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setSelectedBackgroundColor(node_, &optValue);
        auto checkVal = GetAttrValue<std::string>(node_, "selectedBackgroundColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnterKeyTypeTest
 * @tc.desc: Check the functionality of setEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setEnterKeyTypeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnterKeyType, nullptr);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE);

    auto optValue = Converter::ArkValue<Opt_EnterKeyType>(Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_NEW_LINE);
    modifier_->setEnterKeyType(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENTER_KEY_TYPE_NEWLINE_VALUE);
}

/**
 * @tc.name: setEnableKeyboardOnFocusTest
 * @tc.desc: Check the functionality of setEnableKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableKeyboardOnFocusTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableKeyboardOnFocus, nullptr);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_DEFAULT_VALUE);

    auto optValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnableKeyboardOnFocus(node_, &optValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
    EXPECT_EQ(resultStr, "false");

    optValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnableKeyboardOnFocus(node_, &optValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
    EXPECT_EQ(resultStr, "true");
}

/**
 * @tc.name: setEnableHapticFeedbackTest
 * @tc.desc: Check the functionality of setEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableHapticFeedbackTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableHapticFeedback, nullptr);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE);

    auto optValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnableHapticFeedback(node_, &optValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, "false");

    optValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnableHapticFeedback(node_, &optValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, "true");
}

/**
 * @tc.name: setBarStateTest
 * @tc.desc: Check the functionality of setBarState
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setBarStateTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBarState, nullptr);
    std::unique_ptr<JsonValue> jsonValue = GetLayoutJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT);

    auto optValue = Converter::ArkValue<Opt_BarState>(Ark_BarState::ARK_BAR_STATE_ON);
    modifier_->setBarState(node_, &optValue);

    jsonValue = GetLayoutJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_VALUE);
}

static bool g_onAppear = false;
static bool g_onDisappear = false;

/**
 * @tc.name: setBindSelectionMenuTest
 * @tc.desc: Check the functionality of setBindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setBindSelectionMenuTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(modifier_->setBindSelectionMenu, nullptr);
    // Prepare callbacks
    auto onAppearCallback = [](const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end) {
        g_onAppear = true;
    };
    auto onDisappearCallback = [](const Ark_Int32 resourceId) {
        g_onDisappear = true;
    };
    // Prepare options
    auto responseType = Converter::ArkUnion<Ark_Union_ResponseType_RichEditorResponseType, Ark_ResponseType>(
        Ark_ResponseType::ARK_RESPONSE_TYPE_LONG_PRESS);
    Ark_SelectionMenuOptions value;
    value.menuType = Converter::ArkValue<Opt_MenuType>(Ark_MenuType::ARK_MENU_TYPE_PREVIEW_MENU);
    auto onAppearCb = Converter::ArkValue<MenuOnAppearCallback>(onAppearCallback, TEST_RESOURCE_ID);
    value.onAppear = Converter::ArkValue<Opt_MenuOnAppearCallback>(onAppearCb);
    auto onDisappearCb = Converter::ArkValue<VoidCallback>(onDisappearCallback, TEST_RESOURCE_ID);
    value.onDisappear = Converter::ArkValue<Opt_VoidCallback>(onDisappearCb);
    auto options = Converter::ArkValue<Opt_SelectionMenuOptions>(value);
    uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
    auto buildFunc = getBuilderCb();
    auto optBuildFunc = Converter::ArkValue<Opt_CustomNodeBuilder>(buildFunc);
    auto optResponseType = Converter::ArkValue<Opt_Union_ResponseType_RichEditorResponseType>(responseType);
    auto optValue =
        Converter::ArkValue<Opt_RichEditorSpanType>(Ark_RichEditorSpanType::ARK_RICH_EDITOR_SPAN_TYPE_TEXT);
    modifier_->setBindSelectionMenu(node_, &optValue, &optBuildFunc, &optResponseType, &options);
    EXPECT_FALSE(g_onAppear);
    EXPECT_FALSE(g_onDisappear);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectOverlayInfo selectInfo;
    pattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    ASSERT_NE(selectInfo.menuInfo.menuBuilder, nullptr);
    selectInfo.menuInfo.menuBuilder();
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, TEST_RESOURCE_ID);
    selectInfo.menuCallback.onAppear();
    EXPECT_TRUE(g_onAppear);
    selectInfo.menuCallback.onDisappear();
    EXPECT_TRUE(g_onDisappear);
    uiNode = std::nullopt;
}

/**
 * @tc.name: setCustomKeyboardTest
 * @tc.desc: Check the functionality of setCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setCustomKeyboardTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(modifier_->setCustomKeyboard, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CUSTOM_KB_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CUSTOM_KB_DEFAULT_VALUE);

    Ark_KeyboardOptions keyboardOptions;
    keyboardOptions.supportAvoidance = Converter::ArkValue<Opt_Boolean>(true);
    auto options = Converter::ArkValue<Opt_KeyboardOptions>(keyboardOptions);
    uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
    auto buildFunc = getBuilderCb();
    auto optBuildFunc = Converter::ArkValue<Opt_CustomNodeBuilder>(buildFunc);
    modifier_->setCustomKeyboard(node_, &optBuildFunc, &options);

    // Testing callback
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    bool built = pattern->RequestCustomKeyboard();
    EXPECT_TRUE(built);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, TEST_RESOURCE_ID);

    // Testing value
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CUSTOM_KB_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CUSTOM_KB_VALUE);
    uiNode = std::nullopt;
}

/**
 * @tc.name: setMaxLengthTestDefaultValues
 * @tc.desc: Check the functionality of setMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setMaxLengthTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLength, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetMaxLength(), ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE);
}

/**
 * @tc.name: setMaxLengthTestValidValues
 * @tc.desc: Check the functionality of setMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setMaxLengthTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLength, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t resultValue;

    using OneTestStep = std::tuple<Opt_Int32, int32_t>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Int32>(123321), 123321},
        {Converter::ArkValue<Opt_Int32>(321123), 321123},
    };

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMaxLength(node_, &inputValue);
        resultValue = pattern->GetMaxLength();
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setMaxLengthTestInvalidValues
 * @tc.desc: Check the functionality of setMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setMaxLengthTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLength, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t resultValue;

    auto validValue = Converter::ArkValue<Opt_Int32>(100);
    using OneTestStep = std::tuple<Opt_Int32, int32_t>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Int32>(), ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_Int32>(-1), ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMaxLength(node_, &validValue);
        modifier_->setMaxLength(node_, &inputValue);
        resultValue = pattern->GetMaxLength();
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setMaxLinesTestDefaultValues
 * @tc.desc: Check the functionality of setMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setMaxLinesTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLines, nullptr);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_STR_VALUE);
}

/**
 * @tc.name: setMaxLinesTestValidValues
 * @tc.desc: Check the functionality of setMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setMaxLinesTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLines, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t resultValue;

    using OneTestStep = std::tuple<Opt_Int32, uint32_t>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Int32>(123321), 123321},
        {Converter::ArkValue<Opt_Int32>(321123), 321123},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMaxLines(node_, &inputValue);
        resultValue = pattern->GetMaxLines();
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setMaxLinesTestInvalidValues
 * @tc.desc: Check the functionality of setMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setMaxLinesTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLines, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t resultValue;

    auto validValue = Converter::ArkValue<Opt_Int32>(100);
    using OneTestStep = std::tuple<Opt_Int32, uint32_t>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Int32>(), ATTRIBUTE_MAX_LINES_DEFAULT_UINT_VALUE},
        {Converter::ArkValue<Opt_Int32>(-1), ATTRIBUTE_MAX_LINES_DEFAULT_UINT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMaxLines(node_, &validValue);
        modifier_->setMaxLines(node_, &inputValue);
        resultValue = pattern->GetMaxLines();
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setStopBackPressTest
 * @tc.desc: Check the functionality of setStopBackPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setStopBackPressTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setStopBackPress, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsStopBackPress());

    modifier_->setStopBackPress(node_, nullptr);
    EXPECT_TRUE(pattern->IsStopBackPress());

    Opt_Boolean testTrue = Converter::ArkValue<Opt_Boolean>(true);
    Opt_Boolean testFalse = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setStopBackPress(node_, &testTrue);
    EXPECT_TRUE(pattern->IsStopBackPress());
    modifier_->setStopBackPress(node_, &testFalse);
    EXPECT_FALSE(pattern->IsStopBackPress());
}

/**
 * @tc.name: setKeyboardAppearanceTest
 * @tc.desc: Check the functionality of setKeyboardAppearance
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setKeyboardAppearanceTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKeyboardAppearance, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto testNone = Converter::ArkValue<Opt_KeyboardAppearance>(
        Ark_KeyboardAppearance::ARK_KEYBOARD_APPEARANCE_NONE_IMMERSIVE);
    auto testLight = Converter::ArkValue<Opt_KeyboardAppearance>(
        Ark_KeyboardAppearance::ARK_KEYBOARD_APPEARANCE_LIGHT_IMMERSIVE);
    auto testImmersive = Converter::ArkValue<Opt_KeyboardAppearance>(
        Ark_KeyboardAppearance::ARK_KEYBOARD_APPEARANCE_DARK_IMMERSIVE);
    modifier_->setKeyboardAppearance(node_, &testNone);
    EXPECT_EQ(pattern->GetKeyboardAppearance(), KeyboardAppearance::NONE_IMMERSIVE);
    modifier_->setKeyboardAppearance(node_, &testLight);
    EXPECT_EQ(pattern->GetKeyboardAppearance(), KeyboardAppearance::LIGHT_IMMERSIVE);
    modifier_->setKeyboardAppearance(node_, &testImmersive);
    EXPECT_EQ(pattern->GetKeyboardAppearance(), KeyboardAppearance::DARK_IMMERSIVE);
}
} // namespace OHOS::Ace::NG
