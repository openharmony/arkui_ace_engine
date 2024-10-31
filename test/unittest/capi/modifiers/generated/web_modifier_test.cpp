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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_NAME = "javaScriptProxy";
const auto ATTRIBUTE_MEDIA_OPTIONS_NAME = "mediaOptions";
const auto ATTRIBUTE_NESTED_SCROLL_NAME = "nestedScroll";
const auto ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME = "registerNativeEmbedRule";
const auto ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME = "enableNativeMediaPlayer";
const auto ATTRIBUTE_VALUE_I_SRC_NAME = "src";
const auto ATTRIBUTE_VALUE_I_SRC_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_CONTROLLER_NAME = "controller";
const auto ATTRIBUTE_VALUE_I_CONTROLLER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_RENDER_MODE_NAME = "renderMode";
const auto ATTRIBUTE_VALUE_I_RENDER_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_INCOGNITO_MODE_NAME = "incognitoMode";
const auto ATTRIBUTE_VALUE_I_INCOGNITO_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_SHARED_RENDER_PROCESS_TOKEN_NAME = "sharedRenderProcessToken";
const auto ATTRIBUTE_VALUE_I_SHARED_RENDER_PROCESS_TOKEN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_JAVA_SCRIPT_ACCESS_NAME = "javaScriptAccess";
const auto ATTRIBUTE_JAVA_SCRIPT_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FILE_ACCESS_NAME = "fileAccess";
const auto ATTRIBUTE_FILE_ACCESS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ONLINE_IMAGE_ACCESS_NAME = "onlineImageAccess";
const auto ATTRIBUTE_ONLINE_IMAGE_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_DOM_STORAGE_ACCESS_NAME = "domStorageAccess";
const auto ATTRIBUTE_DOM_STORAGE_ACCESS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_IMAGE_ACCESS_NAME = "imageAccess";
const auto ATTRIBUTE_IMAGE_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_MIXED_MODE_NAME = "mixedMode";
const auto ATTRIBUTE_MIXED_MODE_DEFAULT_VALUE = "MixedMode.None";
const auto ATTRIBUTE_ZOOM_ACCESS_NAME = "zoomAccess";
const auto ATTRIBUTE_ZOOM_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_GEOLOCATION_ACCESS_NAME = "geolocationAccess";
const auto ATTRIBUTE_GEOLOCATION_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_NAME_NAME = "name";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_NAME_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_METHOD_LIST_NAME = "methodList";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_METHOD_LIST_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_CONTROLLER_NAME = "controller";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_CONTROLLER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_ASYNC_METHOD_LIST_NAME = "asyncMethodList";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_ASYNC_METHOD_LIST_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_PERMISSION_NAME = "permission";
const auto ATTRIBUTE_JAVA_SCRIPT_PROXY_I_PERMISSION_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PASSWORD_NAME = "password";
const auto ATTRIBUTE_PASSWORD_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_CACHE_MODE_NAME = "cacheMode";
const auto ATTRIBUTE_CACHE_MODE_DEFAULT_VALUE = "CacheMode.Default";
const auto ATTRIBUTE_DARK_MODE_NAME = "darkMode";
const auto ATTRIBUTE_DARK_MODE_DEFAULT_VALUE = "WebDarkMode.Off";
const auto ATTRIBUTE_FORCE_DARK_ACCESS_NAME = "forceDarkAccess";
const auto ATTRIBUTE_FORCE_DARK_ACCESS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_MEDIA_OPTIONS_I_RESUME_INTERVAL_NAME = "resumeInterval";
const auto ATTRIBUTE_MEDIA_OPTIONS_I_RESUME_INTERVAL_DEFAULT_VALUE = "-1";
const auto ATTRIBUTE_MEDIA_OPTIONS_I_AUDIO_EXCLUSIVE_NAME = "audioExclusive";
const auto ATTRIBUTE_MEDIA_OPTIONS_I_AUDIO_EXCLUSIVE_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_TABLE_DATA_NAME = "tableData";
const auto ATTRIBUTE_TABLE_DATA_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_WIDE_VIEW_MODE_ACCESS_NAME = "wideViewModeAccess";
const auto ATTRIBUTE_WIDE_VIEW_MODE_ACCESS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_OVERVIEW_MODE_ACCESS_NAME = "overviewModeAccess";
const auto ATTRIBUTE_OVERVIEW_MODE_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_OVER_SCROLL_MODE_NAME = "overScrollMode";
const auto ATTRIBUTE_OVER_SCROLL_MODE_DEFAULT_VALUE = "OverScrollMode.NEVER";
const auto ATTRIBUTE_TEXT_ZOOM_ATIO_NAME = "textZoomAtio";
const auto ATTRIBUTE_TEXT_ZOOM_ATIO_DEFAULT_VALUE = "100";
const auto ATTRIBUTE_TEXT_ZOOM_RATIO_NAME = "textZoomRatio";
const auto ATTRIBUTE_TEXT_ZOOM_RATIO_DEFAULT_VALUE = "100";
const auto ATTRIBUTE_DATABASE_ACCESS_NAME = "databaseAccess";
const auto ATTRIBUTE_DATABASE_ACCESS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_INITIAL_SCALE_NAME = "initialScale";
const auto ATTRIBUTE_INITIAL_SCALE_DEFAULT_VALUE = "empty";
const auto ATTRIBUTE_USER_AGENT_NAME = "userAgent";
const auto ATTRIBUTE_USER_AGENT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_META_VIEWPORT_NAME = "metaViewport";
const auto ATTRIBUTE_META_VIEWPORT_DEFAULT_VALUE = "empty";
const auto ATTRIBUTE_MEDIA_PLAY_GESTURE_ACCESS_NAME = "mediaPlayGestureAccess";
const auto ATTRIBUTE_MEDIA_PLAY_GESTURE_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_MULTI_WINDOW_ACCESS_NAME = "multiWindowAccess";
const auto ATTRIBUTE_MULTI_WINDOW_ACCESS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_WEB_STANDARD_FONT_NAME = "webStandardFont";
const auto ATTRIBUTE_WEB_STANDARD_FONT_DEFAULT_VALUE = "sans-serif";
const auto ATTRIBUTE_WEB_SERIF_FONT_NAME = "webSerifFont";
const auto ATTRIBUTE_WEB_SERIF_FONT_DEFAULT_VALUE = "serif";
const auto ATTRIBUTE_WEB_SANS_SERIF_FONT_NAME = "webSansSerifFont";
const auto ATTRIBUTE_WEB_SANS_SERIF_FONT_DEFAULT_VALUE = "sans-serif";
const auto ATTRIBUTE_WEB_FIXED_FONT_NAME = "webFixedFont";
const auto ATTRIBUTE_WEB_FIXED_FONT_DEFAULT_VALUE = "monospace";
const auto ATTRIBUTE_WEB_FANTASY_FONT_NAME = "webFantasyFont";
const auto ATTRIBUTE_WEB_FANTASY_FONT_DEFAULT_VALUE = "fantasy";
const auto ATTRIBUTE_WEB_CURSIVE_FONT_NAME = "webCursiveFont";
const auto ATTRIBUTE_WEB_CURSIVE_FONT_DEFAULT_VALUE = "cursive";
const auto ATTRIBUTE_DEFAULT_FIXED_FONT_SIZE_NAME = "defaultFixedFontSize";
const auto ATTRIBUTE_DEFAULT_FIXED_FONT_SIZE_DEFAULT_VALUE = "13";
const auto ATTRIBUTE_DEFAULT_FONT_SIZE_NAME = "defaultFontSize";
const auto ATTRIBUTE_DEFAULT_FONT_SIZE_DEFAULT_VALUE = "16";
const auto ATTRIBUTE_MIN_FONT_SIZE_NAME = "minFontSize";
const auto ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE = "8";
const auto ATTRIBUTE_MIN_LOGICAL_FONT_SIZE_NAME = "minLogicalFontSize";
const auto ATTRIBUTE_MIN_LOGICAL_FONT_SIZE_DEFAULT_VALUE = "8";
const auto ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_NAME = "defaultTextEncodingFormat";
const auto ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_DEFAULT_VALUE = "UTF-8";
const auto ATTRIBUTE_FORCE_DISPLAY_SCROLL_BAR_NAME = "forceDisplayScrollBar";
const auto ATTRIBUTE_FORCE_DISPLAY_SCROLL_BAR_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_BLOCK_NETWORK_NAME = "blockNetwork";
const auto ATTRIBUTE_BLOCK_NETWORK_DEFAULT_VALUE = "empty";
const auto ATTRIBUTE_HORIZONTAL_SCROLL_BAR_ACCESS_NAME = "horizontalScrollBarAccess";
const auto ATTRIBUTE_HORIZONTAL_SCROLL_BAR_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_VERTICAL_SCROLL_BAR_ACCESS_NAME = "verticalScrollBarAccess";
const auto ATTRIBUTE_VERTICAL_SCROLL_BAR_ACCESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_PINCH_SMOOTH_NAME = "pinchSmooth";
const auto ATTRIBUTE_PINCH_SMOOTH_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ALLOW_WINDOW_OPEN_METHOD_NAME = "allowWindowOpenMethod";
const auto ATTRIBUTE_ALLOW_WINDOW_OPEN_METHOD_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_START_NAME = "javaScriptOnDocumentStart";
const auto ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_START_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_END_NAME = "javaScriptOnDocumentEnd";
const auto ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_END_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_LAYOUT_MODE_NAME = "layoutMode";
const auto ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE = "WebLayoutMode.NONE";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME = "scrollForward";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME = "scrollBackward";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME = "scrollUp";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_DEFAULT_VALUE = "NestedScrollMode.SELF_FIRST";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME = "scrollDown";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_DEFAULT_VALUE = "NestedScrollMode.SELF_FIRST";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME = "scrollRight";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_DEFAULT_VALUE = "NestedScrollMode.SELF_FIRST";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME = "scrollLeft";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_DEFAULT_VALUE = "NestedScrollMode.SELF_FIRST";
const auto ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_NAME = "enableNativeEmbedMode";
const auto ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_NAME = "tag";
const auto ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_DEFAULT_VALUE = "";
const auto ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_NAME = "type";
const auto ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_COPY_OPTIONS_NAME = "copyOptions";
const auto ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE = "CopyOptions.CROSS_DEVICE";
const auto ATTRIBUTE_TEXT_AUTOSIZING_NAME = "textAutosizing";
const auto ATTRIBUTE_TEXT_AUTOSIZING_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_NAME = "enable";
const auto ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_NAME = "shouldOverlay";
const auto ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ENABLE_SMOOTH_DRAG_RESIZE_NAME = "enableSmoothDragResize";
const auto ATTRIBUTE_ENABLE_SMOOTH_DRAG_RESIZE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_SELECTION_MENU_OPTIONS_NAME = "selectionMenuOptions";
const auto ATTRIBUTE_SELECTION_MENU_OPTIONS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_KEYBOARD_AVOID_MODE_NAME = "keyboardAvoidMode";
const auto ATTRIBUTE_KEYBOARD_AVOID_MODE_DEFAULT_VALUE = "empty";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME = "enableHapticFeedback";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "empty";
} // namespace

class WebModifierTest : public ModifierTestBase<GENERATED_ArkUIWebModifier,
                            &GENERATED_ArkUINodeModifiers::getWebModifier, GENERATED_ARKUI_WEB> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setWebOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setWebOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_SRC_DEFAULT_VALUE) << "Default value for attribute 'value.src'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_CONTROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_CONTROLLER_DEFAULT_VALUE)
        << "Default value for attribute 'value.controller'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_RENDER_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_RENDER_MODE_DEFAULT_VALUE)
        << "Default value for attribute 'value.renderMode'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_INCOGNITO_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_INCOGNITO_MODE_DEFAULT_VALUE)
        << "Default value for attribute 'value.incognitoMode'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_SHARED_RENDER_PROCESS_TOKEN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_SHARED_RENDER_PROCESS_TOKEN_DEFAULT_VALUE)
        << "Default value for attribute 'value.sharedRenderProcessToken'";
}

/*
 * @tc.name: setWebOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setWebOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setJavaScriptAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setJavaScriptAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JAVA_SCRIPT_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptAccess'";
}

/*
 * @tc.name: setJavaScriptAccessTestJavaScriptAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setJavaScriptAccessTestJavaScriptAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueJavaScriptAccess;

    // Initial setup
    initValueJavaScriptAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueJavaScriptAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueJavaScriptAccess = initValueJavaScriptAccess;

        inputValueJavaScriptAccess = value;
        modifier_->setJavaScriptAccess(node_, inputValueJavaScriptAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JAVA_SCRIPT_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setJavaScriptAccess, attribute: javaScriptAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFileAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setFileAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILE_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FILE_ACCESS_DEFAULT_VALUE) << "Default value for attribute 'fileAccess'";
}

/*
 * @tc.name: setFileAccessTestFileAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setFileAccessTestFileAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueFileAccess;

    // Initial setup
    initValueFileAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueFileAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueFileAccess = initValueFileAccess;

        inputValueFileAccess = value;
        modifier_->setFileAccess(node_, inputValueFileAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILE_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFileAccess, attribute: fileAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setOnlineImageAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setOnlineImageAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ONLINE_IMAGE_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ONLINE_IMAGE_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'onlineImageAccess'";
}

/*
 * @tc.name: setOnlineImageAccessTestOnlineImageAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setOnlineImageAccessTestOnlineImageAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueOnlineImageAccess;

    // Initial setup
    initValueOnlineImageAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueOnlineImageAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueOnlineImageAccess = initValueOnlineImageAccess;

        inputValueOnlineImageAccess = value;
        modifier_->setOnlineImageAccess(node_, inputValueOnlineImageAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ONLINE_IMAGE_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setOnlineImageAccess, attribute: onlineImageAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDomStorageAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDomStorageAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DOM_STORAGE_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DOM_STORAGE_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'domStorageAccess'";
}

/*
 * @tc.name: setDomStorageAccessTestDomStorageAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDomStorageAccessTestDomStorageAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueDomStorageAccess;

    // Initial setup
    initValueDomStorageAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueDomStorageAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueDomStorageAccess = initValueDomStorageAccess;

        inputValueDomStorageAccess = value;
        modifier_->setDomStorageAccess(node_, inputValueDomStorageAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DOM_STORAGE_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDomStorageAccess, attribute: domStorageAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setImageAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setImageAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IMAGE_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IMAGE_ACCESS_DEFAULT_VALUE) << "Default value for attribute 'imageAccess'";
}

/*
 * @tc.name: setImageAccessTestImageAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setImageAccessTestImageAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueImageAccess;

    // Initial setup
    initValueImageAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueImageAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueImageAccess = initValueImageAccess;

        inputValueImageAccess = value;
        modifier_->setImageAccess(node_, inputValueImageAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IMAGE_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setImageAccess, attribute: imageAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMixedModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMixedModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIXED_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIXED_MODE_DEFAULT_VALUE) << "Default value for attribute 'mixedMode'";
}

/*
 * @tc.name: setMixedModeTestMixedModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMixedModeTestMixedModeValidValues, TestSize.Level1)
{
    Ark_MixedMode initValueMixedMode;

    // Initial setup
    initValueMixedMode = std::get<1>(Fixtures::testFixtureEnumMixedModeValidValues[0]);

    auto checkValue = [this, &initValueMixedMode](
                          const std::string& input, const Ark_MixedMode& value, const std::string& expectedStr) {
        Ark_MixedMode inputValueMixedMode = initValueMixedMode;

        inputValueMixedMode = value;
        modifier_->setMixedMode(node_, inputValueMixedMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIXED_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMixedMode, attribute: mixedMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumMixedModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMixedModeTestMixedModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMixedModeTestMixedModeInvalidValues, TestSize.Level1)
{
    Ark_MixedMode initValueMixedMode;

    // Initial setup
    initValueMixedMode = std::get<1>(Fixtures::testFixtureEnumMixedModeValidValues[0]);

    auto checkValue = [this, &initValueMixedMode](const std::string& input, const Ark_MixedMode& value) {
        Ark_MixedMode inputValueMixedMode = initValueMixedMode;

        modifier_->setMixedMode(node_, inputValueMixedMode);
        inputValueMixedMode = value;
        modifier_->setMixedMode(node_, inputValueMixedMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIXED_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIXED_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMixedMode, attribute: mixedMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumMixedModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setZoomAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setZoomAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ZOOM_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ZOOM_ACCESS_DEFAULT_VALUE) << "Default value for attribute 'zoomAccess'";
}

/*
 * @tc.name: setZoomAccessTestZoomAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setZoomAccessTestZoomAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueZoomAccess;

    // Initial setup
    initValueZoomAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueZoomAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueZoomAccess = initValueZoomAccess;

        inputValueZoomAccess = value;
        modifier_->setZoomAccess(node_, inputValueZoomAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ZOOM_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setZoomAccess, attribute: zoomAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setGeolocationAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setGeolocationAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GEOLOCATION_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_GEOLOCATION_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'geolocationAccess'";
}

/*
 * @tc.name: setGeolocationAccessTestGeolocationAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setGeolocationAccessTestGeolocationAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueGeolocationAccess;

    // Initial setup
    initValueGeolocationAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueGeolocationAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueGeolocationAccess = initValueGeolocationAccess;

        inputValueGeolocationAccess = value;
        modifier_->setGeolocationAccess(node_, inputValueGeolocationAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GEOLOCATION_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setGeolocationAccess, attribute: geolocationAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setJavaScriptProxyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptProxyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultJavaScriptProxy =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_JAVA_SCRIPT_PROXY_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultJavaScriptProxy, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_NAME_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_NAME_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptProxy.name'";

    resultStr = GetAttrValue<std::string>(resultJavaScriptProxy, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_METHOD_LIST_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_METHOD_LIST_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptProxy.methodList'";

    resultStr = GetAttrValue<std::string>(resultJavaScriptProxy, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_CONTROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_CONTROLLER_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptProxy.controller'";

    resultStr = GetAttrValue<std::string>(resultJavaScriptProxy, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_ASYNC_METHOD_LIST_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_ASYNC_METHOD_LIST_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptProxy.asyncMethodList'";

    resultStr = GetAttrValue<std::string>(resultJavaScriptProxy, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_PERMISSION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_PROXY_I_PERMISSION_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptProxy.permission'";
}

/*
 * @tc.name: setJavaScriptProxyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptProxyTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setPasswordTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setPasswordTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_DEFAULT_VALUE) << "Default value for attribute 'password'";
}

/*
 * @tc.name: setPasswordTestPasswordValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setPasswordTestPasswordValidValues, TestSize.Level1)
{
    Ark_Boolean initValuePassword;

    // Initial setup
    initValuePassword = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValuePassword](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValuePassword = initValuePassword;

        inputValuePassword = value;
        modifier_->setPassword(node_, inputValuePassword);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setPassword, attribute: password";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setCacheModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCacheModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHE_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CACHE_MODE_DEFAULT_VALUE) << "Default value for attribute 'cacheMode'";
}

/*
 * @tc.name: setCacheModeTestCacheModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCacheModeTestCacheModeValidValues, TestSize.Level1)
{
    Ark_CacheMode initValueCacheMode;

    // Initial setup
    initValueCacheMode = std::get<1>(Fixtures::testFixtureEnumCacheModeValidValues[0]);

    auto checkValue = [this, &initValueCacheMode](
                          const std::string& input, const Ark_CacheMode& value, const std::string& expectedStr) {
        Ark_CacheMode inputValueCacheMode = initValueCacheMode;

        inputValueCacheMode = value;
        modifier_->setCacheMode(node_, inputValueCacheMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHE_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCacheMode, attribute: cacheMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCacheModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setCacheModeTestCacheModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCacheModeTestCacheModeInvalidValues, TestSize.Level1)
{
    Ark_CacheMode initValueCacheMode;

    // Initial setup
    initValueCacheMode = std::get<1>(Fixtures::testFixtureEnumCacheModeValidValues[0]);

    auto checkValue = [this, &initValueCacheMode](const std::string& input, const Ark_CacheMode& value) {
        Ark_CacheMode inputValueCacheMode = initValueCacheMode;

        modifier_->setCacheMode(node_, inputValueCacheMode);
        inputValueCacheMode = value;
        modifier_->setCacheMode(node_, inputValueCacheMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHE_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CACHE_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCacheMode, attribute: cacheMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCacheModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDarkModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDarkModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DARK_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DARK_MODE_DEFAULT_VALUE) << "Default value for attribute 'darkMode'";
}

/*
 * @tc.name: setDarkModeTestDarkModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDarkModeTestDarkModeValidValues, TestSize.Level1)
{
    Ark_WebDarkMode initValueDarkMode;

    // Initial setup
    initValueDarkMode = std::get<1>(Fixtures::testFixtureEnumWebDarkModeValidValues[0]);

    auto checkValue = [this, &initValueDarkMode](
                          const std::string& input, const Ark_WebDarkMode& value, const std::string& expectedStr) {
        Ark_WebDarkMode inputValueDarkMode = initValueDarkMode;

        inputValueDarkMode = value;
        modifier_->setDarkMode(node_, inputValueDarkMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DARK_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDarkMode, attribute: darkMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWebDarkModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDarkModeTestDarkModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDarkModeTestDarkModeInvalidValues, TestSize.Level1)
{
    Ark_WebDarkMode initValueDarkMode;

    // Initial setup
    initValueDarkMode = std::get<1>(Fixtures::testFixtureEnumWebDarkModeValidValues[0]);

    auto checkValue = [this, &initValueDarkMode](const std::string& input, const Ark_WebDarkMode& value) {
        Ark_WebDarkMode inputValueDarkMode = initValueDarkMode;

        modifier_->setDarkMode(node_, inputValueDarkMode);
        inputValueDarkMode = value;
        modifier_->setDarkMode(node_, inputValueDarkMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DARK_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DARK_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setDarkMode, attribute: darkMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumWebDarkModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setForceDarkAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setForceDarkAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORCE_DARK_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FORCE_DARK_ACCESS_DEFAULT_VALUE) << "Default value for attribute 'forceDarkAccess'";
}

/*
 * @tc.name: setForceDarkAccessTestForceDarkAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setForceDarkAccessTestForceDarkAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueForceDarkAccess;

    // Initial setup
    initValueForceDarkAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueForceDarkAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueForceDarkAccess = initValueForceDarkAccess;

        inputValueForceDarkAccess = value;
        modifier_->setForceDarkAccess(node_, inputValueForceDarkAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORCE_DARK_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setForceDarkAccess, attribute: forceDarkAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMediaOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMediaOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultMediaOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MEDIA_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultMediaOptions, ATTRIBUTE_MEDIA_OPTIONS_I_RESUME_INTERVAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MEDIA_OPTIONS_I_RESUME_INTERVAL_DEFAULT_VALUE)
        << "Default value for attribute 'mediaOptions.resumeInterval'";

    resultStr = GetAttrValue<std::string>(resultMediaOptions, ATTRIBUTE_MEDIA_OPTIONS_I_AUDIO_EXCLUSIVE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MEDIA_OPTIONS_I_AUDIO_EXCLUSIVE_DEFAULT_VALUE)
        << "Default value for attribute 'mediaOptions.audioExclusive'";
}

/*
 * @tc.name: setMediaOptionsTestMediaOptionsResumeIntervalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMediaOptionsTestMediaOptionsResumeIntervalValidValues, TestSize.Level1)
{
    Ark_WebMediaOptions initValueMediaOptions;

    // Initial setup
    initValueMediaOptions.resumeInterval =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]));
    initValueMediaOptions.audioExclusive =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueMediaOptions](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WebMediaOptions inputValueMediaOptions = initValueMediaOptions;

        inputValueMediaOptions.resumeInterval = value;
        modifier_->setMediaOptions(node_, &inputValueMediaOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMediaOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MEDIA_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMediaOptions, ATTRIBUTE_MEDIA_OPTIONS_I_RESUME_INTERVAL_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMediaOptions, attribute: mediaOptions.resumeInterval";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, Converter::ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setMediaOptionsTestMediaOptionsResumeIntervalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMediaOptionsTestMediaOptionsResumeIntervalInvalidValues, TestSize.Level1)
{
    Ark_WebMediaOptions initValueMediaOptions;

    // Initial setup
    initValueMediaOptions.resumeInterval =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]));
    initValueMediaOptions.audioExclusive =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueMediaOptions](const std::string& input, const Opt_Number& value) {
        Ark_WebMediaOptions inputValueMediaOptions = initValueMediaOptions;

        modifier_->setMediaOptions(node_, &inputValueMediaOptions);
        inputValueMediaOptions.resumeInterval = value;
        modifier_->setMediaOptions(node_, &inputValueMediaOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMediaOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MEDIA_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMediaOptions, ATTRIBUTE_MEDIA_OPTIONS_I_RESUME_INTERVAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MEDIA_OPTIONS_I_RESUME_INTERVAL_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMediaOptions, attribute: mediaOptions.resumeInterval";
    };

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Number>());
}

/*
 * @tc.name: setMediaOptionsTestMediaOptionsAudioExclusiveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMediaOptionsTestMediaOptionsAudioExclusiveValidValues, TestSize.Level1)
{
    Ark_WebMediaOptions initValueMediaOptions;

    // Initial setup
    initValueMediaOptions.resumeInterval =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]));
    initValueMediaOptions.audioExclusive =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueMediaOptions](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Ark_WebMediaOptions inputValueMediaOptions = initValueMediaOptions;

        inputValueMediaOptions.audioExclusive = value;
        modifier_->setMediaOptions(node_, &inputValueMediaOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMediaOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MEDIA_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMediaOptions, ATTRIBUTE_MEDIA_OPTIONS_I_AUDIO_EXCLUSIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMediaOptions, attribute: mediaOptions.audioExclusive";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, Converter::ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setMediaOptionsTestMediaOptionsAudioExclusiveInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMediaOptionsTestMediaOptionsAudioExclusiveInvalidValues, TestSize.Level1)
{
    Ark_WebMediaOptions initValueMediaOptions;

    // Initial setup
    initValueMediaOptions.resumeInterval =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]));
    initValueMediaOptions.audioExclusive =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueMediaOptions](const std::string& input, const Opt_Boolean& value) {
        Ark_WebMediaOptions inputValueMediaOptions = initValueMediaOptions;

        modifier_->setMediaOptions(node_, &inputValueMediaOptions);
        inputValueMediaOptions.audioExclusive = value;
        modifier_->setMediaOptions(node_, &inputValueMediaOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMediaOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MEDIA_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMediaOptions, ATTRIBUTE_MEDIA_OPTIONS_I_AUDIO_EXCLUSIVE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MEDIA_OPTIONS_I_AUDIO_EXCLUSIVE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMediaOptions, attribute: mediaOptions.audioExclusive";
    };

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setTableDataTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setTableDataTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TABLE_DATA_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TABLE_DATA_DEFAULT_VALUE) << "Default value for attribute 'tableData'";
}

/*
 * @tc.name: setTableDataTestTableDataValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setTableDataTestTableDataValidValues, TestSize.Level1)
{
    Ark_Boolean initValueTableData;

    // Initial setup
    initValueTableData = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueTableData](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueTableData = initValueTableData;

        inputValueTableData = value;
        modifier_->setTableData(node_, inputValueTableData);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TABLE_DATA_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTableData, attribute: tableData";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setWideViewModeAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setWideViewModeAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDE_VIEW_MODE_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WIDE_VIEW_MODE_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'wideViewModeAccess'";
}

/*
 * @tc.name: setWideViewModeAccessTestWideViewModeAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setWideViewModeAccessTestWideViewModeAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueWideViewModeAccess;

    // Initial setup
    initValueWideViewModeAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueWideViewModeAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueWideViewModeAccess = initValueWideViewModeAccess;

        inputValueWideViewModeAccess = value;
        modifier_->setWideViewModeAccess(node_, inputValueWideViewModeAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDE_VIEW_MODE_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWideViewModeAccess, attribute: wideViewModeAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setOverviewModeAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setOverviewModeAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OVERVIEW_MODE_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OVERVIEW_MODE_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'overviewModeAccess'";
}

/*
 * @tc.name: setOverviewModeAccessTestOverviewModeAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setOverviewModeAccessTestOverviewModeAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueOverviewModeAccess;

    // Initial setup
    initValueOverviewModeAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueOverviewModeAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueOverviewModeAccess = initValueOverviewModeAccess;

        inputValueOverviewModeAccess = value;
        modifier_->setOverviewModeAccess(node_, inputValueOverviewModeAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OVERVIEW_MODE_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setOverviewModeAccess, attribute: overviewModeAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setOverScrollModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setOverScrollModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OVER_SCROLL_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OVER_SCROLL_MODE_DEFAULT_VALUE) << "Default value for attribute 'overScrollMode'";
}

/*
 * @tc.name: setOverScrollModeTestOverScrollModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setOverScrollModeTestOverScrollModeValidValues, TestSize.Level1)
{
    Ark_OverScrollMode initValueOverScrollMode;

    // Initial setup
    initValueOverScrollMode = std::get<1>(Fixtures::testFixtureEnumOverScrollModeValidValues[0]);

    auto checkValue = [this, &initValueOverScrollMode](
                          const std::string& input, const Ark_OverScrollMode& value, const std::string& expectedStr) {
        Ark_OverScrollMode inputValueOverScrollMode = initValueOverScrollMode;

        inputValueOverScrollMode = value;
        modifier_->setOverScrollMode(node_, inputValueOverScrollMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OVER_SCROLL_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setOverScrollMode, attribute: overScrollMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumOverScrollModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setOverScrollModeTestOverScrollModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setOverScrollModeTestOverScrollModeInvalidValues, TestSize.Level1)
{
    Ark_OverScrollMode initValueOverScrollMode;

    // Initial setup
    initValueOverScrollMode = std::get<1>(Fixtures::testFixtureEnumOverScrollModeValidValues[0]);

    auto checkValue = [this, &initValueOverScrollMode](const std::string& input, const Ark_OverScrollMode& value) {
        Ark_OverScrollMode inputValueOverScrollMode = initValueOverScrollMode;

        modifier_->setOverScrollMode(node_, inputValueOverScrollMode);
        inputValueOverScrollMode = value;
        modifier_->setOverScrollMode(node_, inputValueOverScrollMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OVER_SCROLL_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OVER_SCROLL_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setOverScrollMode, attribute: overScrollMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumOverScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setTextZoomAtioTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setTextZoomAtioTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ZOOM_ATIO_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_ZOOM_ATIO_DEFAULT_VALUE) << "Default value for attribute 'textZoomAtio'";
}

/*
 * @tc.name: setTextZoomAtioTestTextZoomAtioValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setTextZoomAtioTestTextZoomAtioValidValues, TestSize.Level1)
{
    Ark_Number initValueTextZoomAtio;

    // Initial setup
    initValueTextZoomAtio = std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]);

    auto checkValue = [this, &initValueTextZoomAtio](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueTextZoomAtio = initValueTextZoomAtio;

        inputValueTextZoomAtio = value;
        modifier_->setTextZoomAtio(node_, &inputValueTextZoomAtio);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ZOOM_ATIO_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextZoomAtio, attribute: textZoomAtio";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextZoomRatioTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setTextZoomRatioTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ZOOM_RATIO_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_ZOOM_RATIO_DEFAULT_VALUE) << "Default value for attribute 'textZoomRatio'";
}

/*
 * @tc.name: setTextZoomRatioTestTextZoomRatioValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setTextZoomRatioTestTextZoomRatioValidValues, TestSize.Level1)
{
    Ark_Number initValueTextZoomRatio;

    // Initial setup
    initValueTextZoomRatio = std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]);

    auto checkValue = [this, &initValueTextZoomRatio](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueTextZoomRatio = initValueTextZoomRatio;

        inputValueTextZoomRatio = value;
        modifier_->setTextZoomRatio(node_, &inputValueTextZoomRatio);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ZOOM_RATIO_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextZoomRatio, attribute: textZoomRatio";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDatabaseAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDatabaseAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DATABASE_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATABASE_ACCESS_DEFAULT_VALUE) << "Default value for attribute 'databaseAccess'";
}

/*
 * @tc.name: setDatabaseAccessTestDatabaseAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDatabaseAccessTestDatabaseAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueDatabaseAccess;

    // Initial setup
    initValueDatabaseAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueDatabaseAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueDatabaseAccess = initValueDatabaseAccess;

        inputValueDatabaseAccess = value;
        modifier_->setDatabaseAccess(node_, inputValueDatabaseAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DATABASE_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDatabaseAccess, attribute: databaseAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setInitialScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setInitialScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INITIAL_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_INITIAL_SCALE_DEFAULT_VALUE) << "Default value for attribute 'initialScale'";
}

/*
 * @tc.name: setInitialScaleTestInitialScaleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setInitialScaleTestInitialScaleValidValues, TestSize.Level1)
{
    Ark_Number initValueInitialScale;

    // Initial setup
    initValueInitialScale = std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]);

    auto checkValue = [this, &initValueInitialScale](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueInitialScale = initValueInitialScale;

        inputValueInitialScale = value;
        modifier_->setInitialScale(node_, &inputValueInitialScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INITIAL_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setInitialScale, attribute: initialScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setUserAgentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setUserAgentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_USER_AGENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USER_AGENT_DEFAULT_VALUE) << "Default value for attribute 'userAgent'";
}

/*
 * @tc.name: setUserAgentTestUserAgentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setUserAgentTestUserAgentValidValues, TestSize.Level1)
{
    Ark_String initValueUserAgent;

    // Initial setup
    initValueUserAgent = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueUserAgent](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueUserAgent = initValueUserAgent;

        inputValueUserAgent = value;
        modifier_->setUserAgent(node_, &inputValueUserAgent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_USER_AGENT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setUserAgent, attribute: userAgent";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMetaViewportTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMetaViewportTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_META_VIEWPORT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_META_VIEWPORT_DEFAULT_VALUE) << "Default value for attribute 'metaViewport'";
}

/*
 * @tc.name: setMetaViewportTestMetaViewportValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMetaViewportTestMetaViewportValidValues, TestSize.Level1)
{
    Ark_Boolean initValueMetaViewport;

    // Initial setup
    initValueMetaViewport = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueMetaViewport](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueMetaViewport = initValueMetaViewport;

        inputValueMetaViewport = value;
        modifier_->setMetaViewport(node_, inputValueMetaViewport);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_META_VIEWPORT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMetaViewport, attribute: metaViewport";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMediaPlayGestureAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMediaPlayGestureAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MEDIA_PLAY_GESTURE_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MEDIA_PLAY_GESTURE_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'mediaPlayGestureAccess'";
}

/*
 * @tc.name: setMediaPlayGestureAccessTestMediaPlayGestureAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMediaPlayGestureAccessTestMediaPlayGestureAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueMediaPlayGestureAccess;

    // Initial setup
    initValueMediaPlayGestureAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueMediaPlayGestureAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueMediaPlayGestureAccess = initValueMediaPlayGestureAccess;

        inputValueMediaPlayGestureAccess = value;
        modifier_->setMediaPlayGestureAccess(node_, inputValueMediaPlayGestureAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MEDIA_PLAY_GESTURE_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMediaPlayGestureAccess, attribute: mediaPlayGestureAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMultiWindowAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMultiWindowAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MULTI_WINDOW_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MULTI_WINDOW_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'multiWindowAccess'";
}

/*
 * @tc.name: setMultiWindowAccessTestMultiWindowAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMultiWindowAccessTestMultiWindowAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueMultiWindowAccess;

    // Initial setup
    initValueMultiWindowAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueMultiWindowAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueMultiWindowAccess = initValueMultiWindowAccess;

        inputValueMultiWindowAccess = value;
        modifier_->setMultiWindowAccess(node_, inputValueMultiWindowAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MULTI_WINDOW_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMultiWindowAccess, attribute: multiWindowAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setWebStandardFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebStandardFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_STANDARD_FONT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEB_STANDARD_FONT_DEFAULT_VALUE) << "Default value for attribute 'webStandardFont'";
}

/*
 * @tc.name: setWebStandardFontTestWebStandardFontValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebStandardFontTestWebStandardFontValidValues, TestSize.Level1)
{
    Ark_String initValueWebStandardFont;

    // Initial setup
    initValueWebStandardFont = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueWebStandardFont](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueWebStandardFont = initValueWebStandardFont;

        inputValueWebStandardFont = value;
        modifier_->setWebStandardFont(node_, &inputValueWebStandardFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_STANDARD_FONT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWebStandardFont, attribute: webStandardFont";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setWebSerifFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebSerifFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_SERIF_FONT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEB_SERIF_FONT_DEFAULT_VALUE) << "Default value for attribute 'webSerifFont'";
}

/*
 * @tc.name: setWebSerifFontTestWebSerifFontValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebSerifFontTestWebSerifFontValidValues, TestSize.Level1)
{
    Ark_String initValueWebSerifFont;

    // Initial setup
    initValueWebSerifFont = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueWebSerifFont](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueWebSerifFont = initValueWebSerifFont;

        inputValueWebSerifFont = value;
        modifier_->setWebSerifFont(node_, &inputValueWebSerifFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_SERIF_FONT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWebSerifFont, attribute: webSerifFont";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setWebSansSerifFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebSansSerifFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_SANS_SERIF_FONT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEB_SANS_SERIF_FONT_DEFAULT_VALUE)
        << "Default value for attribute 'webSansSerifFont'";
}

/*
 * @tc.name: setWebSansSerifFontTestWebSansSerifFontValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebSansSerifFontTestWebSansSerifFontValidValues, TestSize.Level1)
{
    Ark_String initValueWebSansSerifFont;

    // Initial setup
    initValueWebSansSerifFont = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueWebSansSerifFont](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueWebSansSerifFont = initValueWebSansSerifFont;

        inputValueWebSansSerifFont = value;
        modifier_->setWebSansSerifFont(node_, &inputValueWebSansSerifFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_SANS_SERIF_FONT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWebSansSerifFont, attribute: webSansSerifFont";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setWebFixedFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebFixedFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_FIXED_FONT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEB_FIXED_FONT_DEFAULT_VALUE) << "Default value for attribute 'webFixedFont'";
}

/*
 * @tc.name: setWebFixedFontTestWebFixedFontValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebFixedFontTestWebFixedFontValidValues, TestSize.Level1)
{
    Ark_String initValueWebFixedFont;

    // Initial setup
    initValueWebFixedFont = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueWebFixedFont](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueWebFixedFont = initValueWebFixedFont;

        inputValueWebFixedFont = value;
        modifier_->setWebFixedFont(node_, &inputValueWebFixedFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_FIXED_FONT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWebFixedFont, attribute: webFixedFont";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setWebFantasyFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebFantasyFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_FANTASY_FONT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEB_FANTASY_FONT_DEFAULT_VALUE) << "Default value for attribute 'webFantasyFont'";
}

/*
 * @tc.name: setWebFantasyFontTestWebFantasyFontValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebFantasyFontTestWebFantasyFontValidValues, TestSize.Level1)
{
    Ark_String initValueWebFantasyFont;

    // Initial setup
    initValueWebFantasyFont = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueWebFantasyFont](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueWebFantasyFont = initValueWebFantasyFont;

        inputValueWebFantasyFont = value;
        modifier_->setWebFantasyFont(node_, &inputValueWebFantasyFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_FANTASY_FONT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWebFantasyFont, attribute: webFantasyFont";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setWebCursiveFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebCursiveFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_CURSIVE_FONT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEB_CURSIVE_FONT_DEFAULT_VALUE) << "Default value for attribute 'webCursiveFont'";
}

/*
 * @tc.name: setWebCursiveFontTestWebCursiveFontValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setWebCursiveFontTestWebCursiveFontValidValues, TestSize.Level1)
{
    Ark_String initValueWebCursiveFont;

    // Initial setup
    initValueWebCursiveFont = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueWebCursiveFont](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueWebCursiveFont = initValueWebCursiveFont;

        inputValueWebCursiveFont = value;
        modifier_->setWebCursiveFont(node_, &inputValueWebCursiveFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEB_CURSIVE_FONT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWebCursiveFont, attribute: webCursiveFont";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDefaultFixedFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDefaultFixedFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_FIXED_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DEFAULT_FIXED_FONT_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'defaultFixedFontSize'";
}

/*
 * @tc.name: setDefaultFixedFontSizeTestDefaultFixedFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDefaultFixedFontSizeTestDefaultFixedFontSizeValidValues, TestSize.Level1)
{
    Ark_Number initValueDefaultFixedFontSize;

    // Initial setup
    initValueDefaultFixedFontSize = std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]);

    auto checkValue = [this, &initValueDefaultFixedFontSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueDefaultFixedFontSize = initValueDefaultFixedFontSize;

        inputValueDefaultFixedFontSize = value;
        modifier_->setDefaultFixedFontSize(node_, &inputValueDefaultFixedFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_FIXED_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDefaultFixedFontSize, attribute: defaultFixedFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDefaultFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDefaultFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DEFAULT_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'defaultFontSize'";
}

/*
 * @tc.name: setDefaultFontSizeTestDefaultFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDefaultFontSizeTestDefaultFontSizeValidValues, TestSize.Level1)
{
    Ark_Number initValueDefaultFontSize;

    // Initial setup
    initValueDefaultFontSize = std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]);

    auto checkValue = [this, &initValueDefaultFontSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueDefaultFontSize = initValueDefaultFontSize;

        inputValueDefaultFontSize = value;
        modifier_->setDefaultFontSize(node_, &inputValueDefaultFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDefaultFontSize, attribute: defaultFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMinFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMinFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'minFontSize'";
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMinFontSizeTestMinFontSizeValidValues, TestSize.Level1)
{
    Ark_Number initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]);

    auto checkValue = [this, &initValueMinFontSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueMinFontSize = initValueMinFontSize;

        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMinLogicalFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMinLogicalFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_LOGICAL_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_LOGICAL_FONT_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'minLogicalFontSize'";
}

/*
 * @tc.name: setMinLogicalFontSizeTestMinLogicalFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setMinLogicalFontSizeTestMinLogicalFontSizeValidValues, TestSize.Level1)
{
    Ark_Number initValueMinLogicalFontSize;

    // Initial setup
    initValueMinLogicalFontSize = std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]);

    auto checkValue = [this, &initValueMinLogicalFontSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueMinLogicalFontSize = initValueMinLogicalFontSize;

        inputValueMinLogicalFontSize = value;
        modifier_->setMinLogicalFontSize(node_, &inputValueMinLogicalFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_LOGICAL_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMinLogicalFontSize, attribute: minLogicalFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDefaultTextEncodingFormatTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setDefaultTextEncodingFormatTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_DEFAULT_VALUE)
        << "Default value for attribute 'defaultTextEncodingFormat'";
}

/*
 * @tc.name: setDefaultTextEncodingFormatTestDefaultTextEncodingFormatValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    WebModifierTest, DISABLED_setDefaultTextEncodingFormatTestDefaultTextEncodingFormatValidValues, TestSize.Level1)
{
    Ark_String initValueDefaultTextEncodingFormat;

    // Initial setup
    initValueDefaultTextEncodingFormat = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueDefaultTextEncodingFormat](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueDefaultTextEncodingFormat = initValueDefaultTextEncodingFormat;

        inputValueDefaultTextEncodingFormat = value;
        modifier_->setDefaultTextEncodingFormat(node_, &inputValueDefaultTextEncodingFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_TEXT_ENCODING_FORMAT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setDefaultTextEncodingFormat, attribute: defaultTextEncodingFormat";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setForceDisplayScrollBarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setForceDisplayScrollBarTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORCE_DISPLAY_SCROLL_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FORCE_DISPLAY_SCROLL_BAR_DEFAULT_VALUE)
        << "Default value for attribute 'forceDisplayScrollBar'";
}

/*
 * @tc.name: setForceDisplayScrollBarTestForceDisplayScrollBarValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setForceDisplayScrollBarTestForceDisplayScrollBarValidValues, TestSize.Level1)
{
    Ark_Boolean initValueForceDisplayScrollBar;

    // Initial setup
    initValueForceDisplayScrollBar = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueForceDisplayScrollBar](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueForceDisplayScrollBar = initValueForceDisplayScrollBar;

        inputValueForceDisplayScrollBar = value;
        modifier_->setForceDisplayScrollBar(node_, inputValueForceDisplayScrollBar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORCE_DISPLAY_SCROLL_BAR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setForceDisplayScrollBar, attribute: forceDisplayScrollBar";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setBlockNetworkTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setBlockNetworkTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_NETWORK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_NETWORK_DEFAULT_VALUE) << "Default value for attribute 'blockNetwork'";
}

/*
 * @tc.name: setBlockNetworkTestBlockNetworkValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setBlockNetworkTestBlockNetworkValidValues, TestSize.Level1)
{
    Ark_Boolean initValueBlockNetwork;

    // Initial setup
    initValueBlockNetwork = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueBlockNetwork](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueBlockNetwork = initValueBlockNetwork;

        inputValueBlockNetwork = value;
        modifier_->setBlockNetwork(node_, inputValueBlockNetwork);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_NETWORK_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBlockNetwork, attribute: blockNetwork";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setHorizontalScrollBarAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setHorizontalScrollBarAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HORIZONTAL_SCROLL_BAR_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HORIZONTAL_SCROLL_BAR_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'horizontalScrollBarAccess'";
}

/*
 * @tc.name: setHorizontalScrollBarAccessTestHorizontalScrollBarAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setHorizontalScrollBarAccessTestHorizontalScrollBarAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHorizontalScrollBarAccess;

    // Initial setup
    initValueHorizontalScrollBarAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHorizontalScrollBarAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueHorizontalScrollBarAccess = initValueHorizontalScrollBarAccess;

        inputValueHorizontalScrollBarAccess = value;
        modifier_->setHorizontalScrollBarAccess(node_, inputValueHorizontalScrollBarAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HORIZONTAL_SCROLL_BAR_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setHorizontalScrollBarAccess, attribute: horizontalScrollBarAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setVerticalScrollBarAccessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setVerticalScrollBarAccessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VERTICAL_SCROLL_BAR_ACCESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VERTICAL_SCROLL_BAR_ACCESS_DEFAULT_VALUE)
        << "Default value for attribute 'verticalScrollBarAccess'";
}

/*
 * @tc.name: setVerticalScrollBarAccessTestVerticalScrollBarAccessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setVerticalScrollBarAccessTestVerticalScrollBarAccessValidValues, TestSize.Level1)
{
    Ark_Boolean initValueVerticalScrollBarAccess;

    // Initial setup
    initValueVerticalScrollBarAccess = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueVerticalScrollBarAccess](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueVerticalScrollBarAccess = initValueVerticalScrollBarAccess;

        inputValueVerticalScrollBarAccess = value;
        modifier_->setVerticalScrollBarAccess(node_, inputValueVerticalScrollBarAccess);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VERTICAL_SCROLL_BAR_ACCESS_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input
                                          << ", method: setVerticalScrollBarAccess, attribute: verticalScrollBarAccess";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setPinchSmoothTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setPinchSmoothTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PINCH_SMOOTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PINCH_SMOOTH_DEFAULT_VALUE) << "Default value for attribute 'pinchSmooth'";
}

/*
 * @tc.name: setPinchSmoothTestPinchSmoothValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setPinchSmoothTestPinchSmoothValidValues, TestSize.Level1)
{
    Ark_Boolean initValuePinchSmooth;

    // Initial setup
    initValuePinchSmooth = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValuePinchSmooth](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValuePinchSmooth = initValuePinchSmooth;

        inputValuePinchSmooth = value;
        modifier_->setPinchSmooth(node_, inputValuePinchSmooth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PINCH_SMOOTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setPinchSmooth, attribute: pinchSmooth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setAllowWindowOpenMethodTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setAllowWindowOpenMethodTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_WINDOW_OPEN_METHOD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALLOW_WINDOW_OPEN_METHOD_DEFAULT_VALUE)
        << "Default value for attribute 'allowWindowOpenMethod'";
}

/*
 * @tc.name: setAllowWindowOpenMethodTestAllowWindowOpenMethodValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setAllowWindowOpenMethodTestAllowWindowOpenMethodValidValues, TestSize.Level1)
{
    Ark_Boolean initValueAllowWindowOpenMethod;

    // Initial setup
    initValueAllowWindowOpenMethod = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueAllowWindowOpenMethod](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueAllowWindowOpenMethod = initValueAllowWindowOpenMethod;

        inputValueAllowWindowOpenMethod = value;
        modifier_->setAllowWindowOpenMethod(node_, inputValueAllowWindowOpenMethod);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_WINDOW_OPEN_METHOD_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setAllowWindowOpenMethod, attribute: allowWindowOpenMethod";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setJavaScriptOnDocumentStartTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptOnDocumentStartTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_START_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptOnDocumentStart'";
}

/*
 * @tc.name: setJavaScriptOnDocumentStartTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptOnDocumentStartTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setJavaScriptOnDocumentEndTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptOnDocumentEndTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_END_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_END_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptOnDocumentEnd'";
}

/*
 * @tc.name: setJavaScriptOnDocumentEndTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptOnDocumentEndTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setLayoutModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setLayoutModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE) << "Default value for attribute 'layoutMode'";
}

/*
 * @tc.name: setLayoutModeTestLayoutModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setLayoutModeTestLayoutModeValidValues, TestSize.Level1)
{
    Ark_WebLayoutMode initValueLayoutMode;

    // Initial setup
    initValueLayoutMode = std::get<1>(Fixtures::testFixtureEnumWebLayoutModeValidValues[0]);

    auto checkValue = [this, &initValueLayoutMode](
                          const std::string& input, const Ark_WebLayoutMode& value, const std::string& expectedStr) {
        Ark_WebLayoutMode inputValueLayoutMode = initValueLayoutMode;

        inputValueLayoutMode = value;
        modifier_->setLayoutMode(node_, inputValueLayoutMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setLayoutMode, attribute: layoutMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWebLayoutModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setLayoutModeTestLayoutModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setLayoutModeTestLayoutModeInvalidValues, TestSize.Level1)
{
    Ark_WebLayoutMode initValueLayoutMode;

    // Initial setup
    initValueLayoutMode = std::get<1>(Fixtures::testFixtureEnumWebLayoutModeValidValues[0]);

    auto checkValue = [this, &initValueLayoutMode](const std::string& input, const Ark_WebLayoutMode& value) {
        Ark_WebLayoutMode inputValueLayoutMode = initValueLayoutMode;

        modifier_->setLayoutMode(node_, inputValueLayoutMode);
        inputValueLayoutMode = value;
        modifier_->setLayoutMode(node_, inputValueLayoutMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLayoutMode, attribute: layoutMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumWebLayoutModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultNestedScroll =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollForward'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollBackward'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollUp'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollDown'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollRight'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollLeft'";
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollForwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollScrollForwardValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Ark_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollForward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollForwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollScrollForwardInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollForward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollBackwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollScrollBackwardValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Ark_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollBackward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollBackwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollScrollBackwardInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollBackward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollUpValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollUpValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Opt_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollUp = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollUp";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, Converter::ArkValue<Opt_NestedScrollMode>(value), expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollUpInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollUpInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollUp = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollUp";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, Converter::ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollDownValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollDownValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Opt_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollDown = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollDown";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, Converter::ArkValue<Opt_NestedScrollMode>(value), expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollDownInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollDownInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollDown = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollDown";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, Converter::ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollRightValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Opt_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollRight = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, Converter::ArkValue<Opt_NestedScrollMode>(value), expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollRightInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollRight = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, Converter::ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollLeftValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Opt_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollLeft = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, Converter::ArkValue<Opt_NestedScrollMode>(value), expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollLeftInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        Converter::ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollLeft = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, Converter::ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setEnableNativeEmbedModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableNativeEmbedModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_DEFAULT_VALUE)
        << "Default value for attribute 'enableNativeEmbedMode'";
}

/*
 * @tc.name: setEnableNativeEmbedModeTestEnableNativeEmbedModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableNativeEmbedModeTestEnableNativeEmbedModeValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableNativeEmbedMode;

    // Initial setup
    initValueEnableNativeEmbedMode = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableNativeEmbedMode](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableNativeEmbedMode = initValueEnableNativeEmbedMode;

        inputValueEnableNativeEmbedMode = value;
        modifier_->setEnableNativeEmbedMode(node_, inputValueEnableNativeEmbedMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableNativeEmbedMode, attribute: enableNativeEmbedMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setRegisterNativeEmbedRuleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setRegisterNativeEmbedRuleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultRegisterNativeEmbedRule =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME);
    std::string resultStr;

    resultStr =
        GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_DEFAULT_VALUE)
        << "Default value for attribute 'registerNativeEmbedRule.tag'";

    resultStr =
        GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_DEFAULT_VALUE)
        << "Default value for attribute 'registerNativeEmbedRule.type'";
}

/*
 * @tc.name: setRegisterNativeEmbedRuleTestRegisterNativeEmbedRuleTagValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setRegisterNativeEmbedRuleTestRegisterNativeEmbedRuleTagValidValues, TestSize.Level1)
{
    Ark_String initValueTag;
    Ark_String initValueType;

    // Initial setup
    initValueTag = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueType = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueTag, &initValueType](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueTag = initValueTag;
        Ark_String inputValueType = initValueType;

        inputValueTag = value;
        modifier_->setRegisterNativeEmbedRule(node_, &inputValueTag, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultRegisterNativeEmbedRule =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setRegisterNativeEmbedRule, attribute: registerNativeEmbedRule.tag";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setRegisterNativeEmbedRuleTestRegisterNativeEmbedRuleTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setRegisterNativeEmbedRuleTestRegisterNativeEmbedRuleTypeValidValues, TestSize.Level1)
{
    Ark_String initValueTag;
    Ark_String initValueType;

    // Initial setup
    initValueTag = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueType = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueTag, &initValueType](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueTag = initValueTag;
        Ark_String inputValueType = initValueType;

        inputValueType = value;
        modifier_->setRegisterNativeEmbedRule(node_, &inputValueTag, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultRegisterNativeEmbedRule =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setRegisterNativeEmbedRule, attribute: registerNativeEmbedRule.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setCopyOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCopyOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE) << "Default value for attribute 'copyOptions'";
}

/*
 * @tc.name: setCopyOptionsTestCopyOptionsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCopyOptionsTestCopyOptionsValidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOptions;

    // Initial setup
    initValueCopyOptions = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOptions](
                          const std::string& input, const Ark_CopyOptions& value, const std::string& expectedStr) {
        Ark_CopyOptions inputValueCopyOptions = initValueCopyOptions;

        inputValueCopyOptions = value;
        modifier_->setCopyOptions(node_, inputValueCopyOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCopyOptions, attribute: copyOptions";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setCopyOptionsTestCopyOptionsInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCopyOptionsTestCopyOptionsInvalidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOptions;

    // Initial setup
    initValueCopyOptions = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOptions](const std::string& input, const Ark_CopyOptions& value) {
        Ark_CopyOptions inputValueCopyOptions = initValueCopyOptions;

        modifier_->setCopyOptions(node_, inputValueCopyOptions);
        inputValueCopyOptions = value;
        modifier_->setCopyOptions(node_, inputValueCopyOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCopyOptions, attribute: copyOptions";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCopyOptionsInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setTextAutosizingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setTextAutosizingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_AUTOSIZING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_AUTOSIZING_DEFAULT_VALUE) << "Default value for attribute 'textAutosizing'";
}

/*
 * @tc.name: setTextAutosizingTestTextAutosizingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setTextAutosizingTestTextAutosizingValidValues, TestSize.Level1)
{
    Ark_Boolean initValueTextAutosizing;

    // Initial setup
    initValueTextAutosizing = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueTextAutosizing](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueTextAutosizing = initValueTextAutosizing;

        inputValueTextAutosizing = value;
        modifier_->setTextAutosizing(node_, inputValueTextAutosizing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_AUTOSIZING_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextAutosizing, attribute: textAutosizing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEnableNativeMediaPlayerTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableNativeMediaPlayerTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultEnableNativeMediaPlayer =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME);
    std::string resultStr;

    resultStr =
        GetAttrValue<std::string>(resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_DEFAULT_VALUE)
        << "Default value for attribute 'enableNativeMediaPlayer.enable'";

    resultStr = GetAttrValue<std::string>(
        resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_DEFAULT_VALUE)
        << "Default value for attribute 'enableNativeMediaPlayer.shouldOverlay'";
}

/*
 * @tc.name: setEnableNativeMediaPlayerTestEnableNativeMediaPlayerEnableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableNativeMediaPlayerTestEnableNativeMediaPlayerEnableValidValues, TestSize.Level1)
{
    Ark_NativeMediaPlayerConfig initValueEnableNativeMediaPlayer;

    // Initial setup
    initValueEnableNativeMediaPlayer.enable = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueEnableNativeMediaPlayer.shouldOverlay = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableNativeMediaPlayer](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_NativeMediaPlayerConfig inputValueEnableNativeMediaPlayer = initValueEnableNativeMediaPlayer;

        inputValueEnableNativeMediaPlayer.enable = value;
        modifier_->setEnableNativeMediaPlayer(node_, &inputValueEnableNativeMediaPlayer);
        auto jsonValue = GetJsonValue(node_);
        auto resultEnableNativeMediaPlayer =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setEnableNativeMediaPlayer, attribute: enableNativeMediaPlayer.enable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEnableNativeMediaPlayerTestEnableNativeMediaPlayerShouldOverlayValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    WebModifierTest, setEnableNativeMediaPlayerTestEnableNativeMediaPlayerShouldOverlayValidValues, TestSize.Level1)
{
    Ark_NativeMediaPlayerConfig initValueEnableNativeMediaPlayer;

    // Initial setup
    initValueEnableNativeMediaPlayer.enable = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueEnableNativeMediaPlayer.shouldOverlay = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableNativeMediaPlayer](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_NativeMediaPlayerConfig inputValueEnableNativeMediaPlayer = initValueEnableNativeMediaPlayer;

        inputValueEnableNativeMediaPlayer.shouldOverlay = value;
        modifier_->setEnableNativeMediaPlayer(node_, &inputValueEnableNativeMediaPlayer);
        auto jsonValue = GetJsonValue(node_);
        auto resultEnableNativeMediaPlayer =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setEnableNativeMediaPlayer, attribute: enableNativeMediaPlayer.shouldOverlay";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEnableSmoothDragResizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableSmoothDragResizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SMOOTH_DRAG_RESIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_SMOOTH_DRAG_RESIZE_DEFAULT_VALUE)
        << "Default value for attribute 'enableSmoothDragResize'";
}

/*
 * @tc.name: setEnableSmoothDragResizeTestEnableSmoothDragResizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableSmoothDragResizeTestEnableSmoothDragResizeValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableSmoothDragResize;

    // Initial setup
    initValueEnableSmoothDragResize = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableSmoothDragResize](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableSmoothDragResize = initValueEnableSmoothDragResize;

        inputValueEnableSmoothDragResize = value;
        modifier_->setEnableSmoothDragResize(node_, inputValueEnableSmoothDragResize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SMOOTH_DRAG_RESIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableSmoothDragResize, attribute: enableSmoothDragResize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setSelectionMenuOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setSelectionMenuOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTION_MENU_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_MENU_OPTIONS_DEFAULT_VALUE)
        << "Default value for attribute 'selectionMenuOptions'";
}

/*
 * @tc.name: setSelectionMenuOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setSelectionMenuOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setKeyboardAvoidModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setKeyboardAvoidModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_AVOID_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_AVOID_MODE_DEFAULT_VALUE)
        << "Default value for attribute 'keyboardAvoidMode'";
}

/*
 * @tc.name: setKeyboardAvoidModeTestKeyboardAvoidModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setKeyboardAvoidModeTestKeyboardAvoidModeValidValues, TestSize.Level1)
{
    Ark_WebKeyboardAvoidMode initValueKeyboardAvoidMode;

    // Initial setup
    initValueKeyboardAvoidMode = std::get<1>(Fixtures::testFixtureEnumWebKeyboardAvoidModeValidValues[0]);

    auto checkValue = [this, &initValueKeyboardAvoidMode](const std::string& input,
                          const Ark_WebKeyboardAvoidMode& value, const std::string& expectedStr) {
        Ark_WebKeyboardAvoidMode inputValueKeyboardAvoidMode = initValueKeyboardAvoidMode;

        inputValueKeyboardAvoidMode = value;
        modifier_->setKeyboardAvoidMode(node_, inputValueKeyboardAvoidMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_AVOID_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setKeyboardAvoidMode, attribute: keyboardAvoidMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWebKeyboardAvoidModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setKeyboardAvoidModeTestKeyboardAvoidModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setKeyboardAvoidModeTestKeyboardAvoidModeInvalidValues, TestSize.Level1)
{
    Ark_WebKeyboardAvoidMode initValueKeyboardAvoidMode;

    // Initial setup
    initValueKeyboardAvoidMode = std::get<1>(Fixtures::testFixtureEnumWebKeyboardAvoidModeValidValues[0]);

    auto checkValue = [this, &initValueKeyboardAvoidMode](
                          const std::string& input, const Ark_WebKeyboardAvoidMode& value) {
        Ark_WebKeyboardAvoidMode inputValueKeyboardAvoidMode = initValueKeyboardAvoidMode;

        modifier_->setKeyboardAvoidMode(node_, inputValueKeyboardAvoidMode);
        inputValueKeyboardAvoidMode = value;
        modifier_->setKeyboardAvoidMode(node_, inputValueKeyboardAvoidMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_AVOID_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_AVOID_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setKeyboardAvoidMode, attribute: keyboardAvoidMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumWebKeyboardAvoidModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE)
        << "Default value for attribute 'enableHapticFeedback'";
}

/*
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableHapticFeedback](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}
} // namespace OHOS::Ace::NG
