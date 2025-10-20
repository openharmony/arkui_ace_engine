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
#include "core/components_ng/pattern/video/video_event_hub.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/interfaces/native/implementation/video_controller_peer_impl.h"
#include "core/interfaces/native/implementation/color_metrics_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_SRC_NAME = "src";
    const auto ATTRIBUTE_SRC_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_BUNDLE_NAME = "bundleName";
    const auto ATTRIBUTE_BUNDLE_NAME_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MODULE_NAME = "moduleName";
    const auto ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_CURRENT_PROGRESS_RATE_NAME = "currentProgressRate";
    const auto ATTRIBUTE_CURRENT_PROGRESS_RATE_DEFAULT_VALUE = 1.0;
    const auto ATTRIBUTE_PREVIEW_URI_NAME = "previewUri";
    const auto ATTRIBUTE_MUTED_NAME = "muted";
    const auto ATTRIBUTE_MUTED_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_AUTO_PLAY_NAME = "autoPlay";
    const auto ATTRIBUTE_AUTO_PLAY_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_CONTROLS_NAME = "controls";
    const auto ATTRIBUTE_CONTROLS_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_LOOP_NAME = "loop";
    const auto ATTRIBUTE_LOOP_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_OBJECT_FIT_NAME = "objectFit";
    const auto ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE = "ImageFit.Cover";
    const auto ATTRIBUTE_ENABLE_ANALYZER_ENABLE_NAME = "enableAnalyzer";
    const auto ATTRIBUTE_ENABLE_ANALYZER_ENABLE_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_ENABLE_SHORTCUT_KEY_NAME = "enableShortcutKey";
    const auto ATTRIBUTE_ENABLE_SHORTCUT_KEY_DEFAULT_VALUE = "false";
#ifdef WRONG_SDK
    const auto ATTRIBUTE_SURFACE_BACKGROUND_COLOR_NAME = "surfaceBackgroundColor";
    const auto ATTRIBUTE_SURFACE_BACKGROUND_COLOR_DEFAULT_VALUE = "#FF000000";
#endif

    const std::string TEST_COLOR_RED = "#FFFF0000";
    const std::string TEST_COLOR_BLACK = "#FF000000";
    const std::string TEST_COLOR_BLUE = "#FF0000FF";
    const auto TEST_COLOR_RED_NUM = 0xFFFF0000;
    const auto TEST_COLOR_BLACK_NUM = 0xFF000000;
    const auto TEST_COLOR_BLUE_NUM = 0xFF0000FF;
} // namespace

class VideoModifierTest : public ModifierTestBase<GENERATED_ArkUIVideoModifier,
    &GENERATED_ArkUINodeModifiers::getVideoModifier, GENERATED_ARKUI_VIDEO> {};

/*
 * @tc.name: setOptionsSrcTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOptionsSrcTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    std::string src = GetAttrValue<std::string>(resultStr, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(src, ATTRIBUTE_SRC_DEFAULT_VALUE);
    std::string bundleName = GetAttrValue<std::string>(resultStr, ATTRIBUTE_BUNDLE_NAME);
    EXPECT_EQ(bundleName, ATTRIBUTE_BUNDLE_NAME_DEFAULT_VALUE);
    std::string moduleName = GetAttrValue<std::string>(resultStr, ATTRIBUTE_MODULE_NAME);
    EXPECT_EQ(moduleName, ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE);
}

/*
 * @tc.name: setOptionsSrcTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setOptionsSrcTestValidValues, TestSize.Level1)
{
    Ark_VideoOptions options;
    options.src = Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(
        Converter::ArkValue<Ark_String>("source_str"));
    options.previewUri = Converter::ArkValue<Opt_Union_String_PixelMap_Resource>(Ark_Empty());
    options.currentProgressRate = Converter::ArkValue<Opt_Union_F64_String_PlaybackSpeed>(Ark_Empty());
    options.controller = Converter::ArkValue<Opt_VideoController>(Ark_Empty());
    options.imageAIOptions = Converter::ArkValue<Opt_ImageAIOptions>(Ark_Empty());
    modifier_->setVideoOptions(node_, &options);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    std::string src = GetAttrValue<std::string>(resultStr, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(src, "source_str");
    std::string bundleName = GetAttrValue<std::string>(resultStr, ATTRIBUTE_BUNDLE_NAME);
    EXPECT_EQ(bundleName, ATTRIBUTE_BUNDLE_NAME_DEFAULT_VALUE);
    std::string moduleName = GetAttrValue<std::string>(resultStr, ATTRIBUTE_MODULE_NAME);
    EXPECT_EQ(moduleName, ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE);
}

/*
 * @tc.name: setOptionsProgressRateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOptionsProgressRateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    auto result = GetAttrValue<double>(jsonValue, ATTRIBUTE_CURRENT_PROGRESS_RATE_NAME);
    EXPECT_NEAR(result, ATTRIBUTE_CURRENT_PROGRESS_RATE_DEFAULT_VALUE, FLT_EPSILON);
}

// Valid values for attribute 'objectFit' of method 'objectFit'
static std::vector<std::tuple<std::string, Opt_Union_F64_String_PlaybackSpeed, double>>
    playbackSpeedEnumValidValues = {
    {
        "ARK_PLAYBACK_SPEED_SPEED_FORWARD_0_75_X",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_PlaybackSpeed>(
            ARK_PLAYBACK_SPEED_SPEED_FORWARD_0_75_X),
        0.75
    },
    {
        "ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_00_X",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_PlaybackSpeed>(
            ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_00_X),
        1.0
    },
    {
        "ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_25_X",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_PlaybackSpeed>(
            ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_25_X),
        1.25
    },
    {
        "ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_75_X",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_PlaybackSpeed>(
            ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_75_X),
        1.75
    },
    {
        "ARK_PLAYBACK_SPEED_SPEED_FORWARD_2_00_X",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_PlaybackSpeed>(
            ARK_PLAYBACK_SPEED_SPEED_FORWARD_2_00_X),
        2.0
    },
    {
        "3.5",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_String>("3.5"),
        3.5
    },
    {
        "4.0",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_String>("4.0"),
        4.0
    },
    {
        "4.25",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_Float64>(4.25),
        4.25
    },
    {
        "5.0",
        Converter::ArkUnion<Opt_Union_F64_String_PlaybackSpeed, Ark_Float64>(5.0),
        5.0
    },
};

/*
 * @tc.name: setOptionsProgressRateTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setOptionsProgressRateTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;

    Ark_VideoOptions options;
    options.src = Converter::ArkValue<Opt_Union_String_Resource>(Ark_Empty());
    options.previewUri = Converter::ArkValue<Opt_Union_String_PixelMap_Resource>(Ark_Empty());
    options.currentProgressRate = Converter::ArkValue<Opt_Union_F64_String_PlaybackSpeed>(Ark_Empty());
    options.controller = Converter::ArkValue<Opt_VideoController>(Ark_Empty());
    options.imageAIOptions = Converter::ArkValue<Opt_ImageAIOptions>(Ark_Empty());

    for (auto&& value: playbackSpeedEnumValidValues) {
        options.currentProgressRate = std::get<1>(value);
        modifier_->setVideoOptions(node_, &options);
        jsonValue = GetJsonValue(node_);
        auto result = GetAttrValue<double>(jsonValue, ATTRIBUTE_CURRENT_PROGRESS_RATE_NAME);
        auto expected = std::get<2>(value);
        EXPECT_NEAR(result, expected, FLT_EPSILON) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOptionsPreviewUriTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOptionsPreviewUriTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PREVIEW_URI_NAME);
    std::string src = GetAttrValue<std::string>(resultStr, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(src, ATTRIBUTE_SRC_DEFAULT_VALUE);
    std::string bundleName = GetAttrValue<std::string>(resultStr, ATTRIBUTE_BUNDLE_NAME);
    EXPECT_EQ(bundleName, ATTRIBUTE_BUNDLE_NAME_DEFAULT_VALUE);
    std::string moduleName = GetAttrValue<std::string>(resultStr, ATTRIBUTE_MODULE_NAME);
    EXPECT_EQ(moduleName, ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE);
}

/*
 * @tc.name: setOptionsPreviewUriTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setOptionsPreviewUriTestValidValues, TestSize.Level1)
{
    Ark_VideoOptions options;
    options.src = Converter::ArkValue<Opt_Union_String_Resource>(Ark_Empty());
    options.previewUri = Converter::ArkUnion<Opt_Union_String_PixelMap_Resource, Ark_String>(
        Converter::ArkValue<Ark_String>("preview_uri_source"));
    options.currentProgressRate = Converter::ArkValue<Opt_Union_F64_String_PlaybackSpeed>(Ark_Empty());
    options.controller = Converter::ArkValue<Opt_VideoController>(Ark_Empty());
    options.imageAIOptions = Converter::ArkValue<Opt_ImageAIOptions>(Ark_Empty());
    modifier_->setVideoOptions(node_, &options);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PREVIEW_URI_NAME);
    std::string src = GetAttrValue<std::string>(resultStr, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(src, "preview_uri_source");
    std::string bundleName = GetAttrValue<std::string>(resultStr, ATTRIBUTE_BUNDLE_NAME);
    EXPECT_EQ(bundleName, ATTRIBUTE_BUNDLE_NAME_DEFAULT_VALUE);
    std::string moduleName = GetAttrValue<std::string>(resultStr, ATTRIBUTE_MODULE_NAME);
    EXPECT_EQ(moduleName, ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE);
}

/*
 * @tc.name: setOptionsVideoControllerTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOptionsVideoControllerTestValidValues, TestSize.Level1)
{
    Ark_VideoOptions options;
    options.src = Converter::ArkValue<Opt_Union_String_Resource>(Ark_Empty());
    options.previewUri = Converter::ArkValue<Opt_Union_String_PixelMap_Resource>(Ark_Empty());
    options.currentProgressRate = Converter::ArkValue<Opt_Union_F64_String_PlaybackSpeed>(Ark_Empty());
    options.imageAIOptions = Converter::ArkValue<Opt_ImageAIOptions>(Ark_Empty());

    auto controllerPtr =
        fullAPI_->getAccessors()->getVideoControllerAccessor()->construct();
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::VideoControllerPeerImpl*>(controllerPtr);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    EXPECT_NE(pattern, nullptr);

    options.controller = Converter::ArkValue<Opt_VideoController>(controllerPtr);
    modifier_->setVideoOptions(node_, &options);

    RefPtr<VideoControllerV2> controller = pattern->GetVideoController();
    EXPECT_NE(controller, nullptr);

    EXPECT_EQ(peerImplPtr->GetController(), controller);

    Ark_NativePointer finalizerPtr =
        fullAPI_->getAccessors()->getVideoControllerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(VideoControllerPeer *)>(finalizerPtr);
    EXPECT_NE(finalyzer, nullptr);
    finalyzer(reinterpret_cast<VideoControllerPeer *>(controllerPtr));
}

/*
 * @tc.name: setOptionsVideoControllerTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOptionsVideoControllerTestInvalidValues, TestSize.Level1)
{
    Ark_VideoOptions options;
    options.src = Converter::ArkValue<Opt_Union_String_Resource>(Ark_Empty());
    options.previewUri = Converter::ArkValue<Opt_Union_String_PixelMap_Resource>(Ark_Empty());
    options.currentProgressRate = Converter::ArkValue<Opt_Union_F64_String_PlaybackSpeed>(Ark_Empty());
    options.imageAIOptions = Converter::ArkValue<Opt_ImageAIOptions>(Ark_Empty());

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    EXPECT_NE(pattern, nullptr);

    options.controller = Converter::ArkValue<Opt_VideoController>(Ark_Empty());
    modifier_->setVideoOptions(node_, &options);

    RefPtr<VideoControllerV2> controller = pattern->GetVideoController();
    EXPECT_EQ(controller, nullptr);
}

/*
 * @tc.name: DISABLED_setImageAIOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setImageAIOptionsTestValidValues, TestSize.Level1)
{
    // imageAIOptions option is not supported
}

// Valid values for attribute 'muted' of method 'muted'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> mutedMutedValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setMutedTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setMutedTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MUTED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MUTED_DEFAULT_VALUE);
}

/*
 * @tc.name: setMutedTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setMutedTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean inputValueMuted;
    Opt_Boolean initValueMuted;

    // Initial setup
    initValueMuted = std::get<1>(mutedMutedValidValues[0]);

    // Verifying attribute's  values
    inputValueMuted = initValueMuted;
    for (auto&& value: mutedMutedValidValues) {
        inputValueMuted = std::get<1>(value);
        modifier_->setMuted(node_, &inputValueMuted);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MUTED_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setAutoPlayTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setAutoPlayTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_PLAY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_PLAY_DEFAULT_VALUE);
}

// Valid values for attribute 'autoPlay' of method 'autoPlay'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> autoPlayAutoPlayValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setAutoPlayTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setAutoPlayTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean inputValueAutoPlay;
    Opt_Boolean initValueAutoPlay;

    // Initial setup
    initValueAutoPlay = std::get<1>(autoPlayAutoPlayValidValues[0]);

    // Verifying attribute's  values
    inputValueAutoPlay = initValueAutoPlay;
    for (auto&& value: autoPlayAutoPlayValidValues) {
        inputValueAutoPlay = std::get<1>(value);
        modifier_->setAutoPlay(node_, &inputValueAutoPlay);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_PLAY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setControlsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setControlsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROLS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROLS_DEFAULT_VALUE);
}

// Valid values for attribute 'controls' of method 'controls'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> controlsControlsValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setControlsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setControlsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean inputValueControls;
    Opt_Boolean initValueControls;

    // Initial setup
    initValueControls = std::get<1>(controlsControlsValidValues[0]);

    // Verifying attribute's  values
    inputValueControls = initValueControls;
    for (auto&& value: controlsControlsValidValues) {
        inputValueControls = std::get<1>(value);
        modifier_->setControls(node_, &inputValueControls);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROLS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setLoopTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setLoopTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LOOP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LOOP_DEFAULT_VALUE);
}

// Valid values for attribute 'loop' of method 'loop'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> loopLoopValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setLoopTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setLoopTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean inputValueLoop;
    Opt_Boolean initValueLoop;

    // Initial setup
    initValueLoop = std::get<1>(loopLoopValidValues[0]);

    // Verifying attribute's  values
    inputValueLoop = initValueLoop;
    for (auto&& value: loopLoopValidValues) {
        inputValueLoop = std::get<1>(value);
        modifier_->setLoop(node_, &inputValueLoop);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LOOP_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setObjectFitTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setObjectFitTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE);
}

// Valid values for attribute 'objectFit' of method 'objectFit'
static std::vector<std::tuple<std::string, Opt_ImageFit, std::string>> objectFitObjectFitValidValues = {
    {"ARK_IMAGE_FIT_CONTAIN", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_CONTAIN), "ImageFit.Contain"},
    {"ARK_IMAGE_FIT_COVER", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_COVER), "ImageFit.Cover"},
    {"ARK_IMAGE_FIT_AUTO", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_AUTO), "ImageFit.Auto"},
    {"ARK_IMAGE_FIT_FILL", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_FILL), "ImageFit.Fill"},
    {"ARK_IMAGE_FIT_SCALE_DOWN", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_SCALE_DOWN), "ImageFit.ScaleDown"},
    {"ARK_IMAGE_FIT_NONE", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_NONE), "ImageFit.None"},
    {"ARK_IMAGE_FIT_TOP_START", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_TOP_START), "ImageFit.TOP_START"},
    {"ARK_IMAGE_FIT_TOP", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_TOP), "ImageFit.TOP"},
    {"ARK_IMAGE_FIT_TOP_END", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_TOP_END), "ImageFit.TOP_END"},
    {"ARK_IMAGE_FIT_START", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_START), "ImageFit.START"},
    {"ARK_IMAGE_FIT_CENTER", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_CENTER), "ImageFit.CENTER"},
    {"ARK_IMAGE_FIT_END", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_END), "ImageFit.END"},
    {"ARK_IMAGE_FIT_BOTTOM_START", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_BOTTOM_START),
        "ImageFit.BOTTOM_START"},
    {"ARK_IMAGE_FIT_BOTTOM", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_BOTTOM), "ImageFit.BOTTOM"},
    {"ARK_IMAGE_FIT_BOTTOM_END", Converter::ArkValue<Opt_ImageFit>(ARK_IMAGE_FIT_BOTTOM_END), "ImageFit.BOTTOM_END"},
};

/*
 * @tc.name: setObjectFitTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setObjectFitTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_ImageFit inputValueObjectFit;
    Opt_ImageFit initValueObjectFit;

    // Initial setup
    initValueObjectFit = std::get<1>(objectFitObjectFitValidValues[0]);

    // Verifying attribute's  values
    inputValueObjectFit = initValueObjectFit;
    for (auto&& value: objectFitObjectFitValidValues) {
        inputValueObjectFit = std::get<1>(value);
        modifier_->setObjectFit(node_, &inputValueObjectFit);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'objectFit' of method 'objectFit'
static std::vector<std::tuple<std::string, Opt_ImageFit>> objectFitObjectFitInvalidValues = {
    {"static_cast<Ark_ImageFit>(-1)", Converter::ArkValue<Opt_ImageFit>(static_cast<Ark_ImageFit>(-1))},
};

/*
 * @tc.name: setObjectFitTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setObjectFitTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_ImageFit inputValueObjectFit;
    Opt_ImageFit initValueObjectFit;

    // Initial setup
    initValueObjectFit = std::get<1>(objectFitObjectFitValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: objectFitObjectFitInvalidValues) {
        inputValueObjectFit = initValueObjectFit;
        modifier_->setObjectFit(node_, &inputValueObjectFit);
        inputValueObjectFit = std::get<1>(value);
        modifier_->setObjectFit(node_, &inputValueObjectFit);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
        expectedStr = ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOnStartTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnStartTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onStart = [](Ark_VMContext context, const Ark_Int32 resourceId)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
        };
    };

    auto arkCallback = Converter::ArkValue<VoidCallback>(onStart, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_VoidCallback>(arkCallback);
    modifier_->setOnStart(node_, &optCallback);

    EXPECT_FALSE(checkEvent);
    eventHub->FireStartEvent();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnPauseTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnPauseTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onPause = [](Ark_VMContext context, const Ark_Int32 resourceId)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
        };
    };

    auto arkCallback = Converter::ArkValue<VoidCallback>(onPause, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_VoidCallback>(arkCallback);
    modifier_->setOnPause(node_, &optCallback);

    EXPECT_FALSE(checkEvent);
    eventHub->FirePauseEvent();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnFinishTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnFinishTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onFinish = [](Ark_VMContext context, const Ark_Int32 resourceId)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
        };
    };

    auto arkCallback = Converter::ArkValue<VoidCallback>(onFinish, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_VoidCallback>(arkCallback);
    modifier_->setOnFinish(node_, &optCallback);

    EXPECT_FALSE(checkEvent);
    eventHub->FireFinishEvent();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnFullscreenChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnFullscreenChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool fullscreen;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onFullscreenChange = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_FullscreenInfo parameter)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
            .fullscreen = Converter::Convert<bool>(parameter.fullscreen),
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_FullscreenInfo_Void>(onFullscreenChange, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_FullscreenInfo_Void>(arkCallback);
    modifier_->setOnFullscreenChange(node_, &optCallback);

    EXPECT_FALSE(checkEvent);

    eventHub->FireFullScreenChangeEvent(true);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->fullscreen, true);

    eventHub->FireFullScreenChangeEvent(false);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->fullscreen, false);
}

/*
 * @tc.name: setOnPreparedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnPreparedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t duration;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onPrepared = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_PreparedInfo parameter)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
            .duration = Converter::Convert<int32_t>(parameter.duration),
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_PreparedInfo_Void>(onPrepared, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_PreparedInfo_Void>(arkCallback);
    modifier_->setOnPrepared(node_, &optCallback);

    EXPECT_FALSE(checkEvent);

    eventHub->FirePreparedEvent(1.25f);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->duration, 1);

    eventHub->FirePreparedEvent(3.75f);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->duration, 3);
}

/*
 * @tc.name: setOnSeekingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setOnSeekingTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t time;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onSeeking = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_PlaybackInfo parameter)
    {
        printf("CHECK ");
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
            .time = Converter::Convert<int32_t>(parameter.time),
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_PlaybackInfo_Void>(onSeeking, frameNode->GetId());

    auto optCallback = Converter::ArkValue<Opt_Callback_PlaybackInfo_Void>(arkCallback);
    modifier_->setOnSeeking(node_, &optCallback);

    EXPECT_FALSE(checkEvent);

    eventHub->FireSeekingEvent(1.25f);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->time, 1);

    eventHub->FireSeekingEvent(3.75f);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->time, 3);
}

/*
 * @tc.name: setOnSeekedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnSeekedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t time;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onSeeked = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_PlaybackInfo parameter)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
            .time = Converter::Convert<int32_t>(parameter.time),
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_PlaybackInfo_Void>(onSeeked, frameNode->GetId());

    auto optCallback = Converter::ArkValue<Opt_Callback_PlaybackInfo_Void>(arkCallback);
    modifier_->setOnSeeked(node_, &optCallback);

    EXPECT_FALSE(checkEvent);

    eventHub->FireSeekedEvent(1.25f);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->time, 1);

    eventHub->FireSeekedEvent(3.75f);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->time, 3);
}

/*
 * @tc.name: setOnUpdateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnUpdateTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t time;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onUpdate = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_PlaybackInfo parameter)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
            .time = Converter::Convert<int32_t>(parameter.time),
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_PlaybackInfo_Void>(onUpdate, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_PlaybackInfo_Void>(arkCallback);
    modifier_->setOnUpdate(node_, &optCallback);

    EXPECT_FALSE(checkEvent);

    eventHub->FireUpdateEvent(1.25f);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->time, 1);

    eventHub->FireUpdateEvent(3.75f);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->time, 3);
}

/*
 * @tc.name: setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnErrorTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onError = [](Ark_VMContext context, const Ark_Int32 resourceId)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_Void>(onError, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnError(node_, &optCallback);

    EXPECT_FALSE(checkEvent);
    eventHub->FireErrorEvent();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnStopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setOnStopTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    ASSERT_TRUE(eventHub);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onStop = [](Ark_VMContext context, const Ark_Int32 resourceId)
    {
        checkEvent = CheckEvent{
            .nodeId = Converter::Convert<int32_t>(resourceId),
        };
    };

    auto arkCallback = Converter::ArkValue<VoidCallback>(onStop, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_VoidCallback>(arkCallback);
    modifier_->setOnStop(node_, &optCallback);

    EXPECT_FALSE(checkEvent);
    eventHub->FireStopEvent();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setEnableAnalyzerTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setEnableAnalyzerTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANALYZER_ENABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_ANALYZER_ENABLE_DEFAULT_VALUE);
}

// Valid values for attribute 'enableAnalyzerEnable' of method 'enableAnalyzer'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> enableAnalyzerEnableAnalyzerEnableValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setEnableAnalyzerTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setEnableAnalyzerTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean inputValueEnableAnalyzerEnable;
    Opt_Boolean initValueEnableAnalyzerEnable;

    // Initial setup
    initValueEnableAnalyzerEnable = std::get<1>(enableAnalyzerEnableAnalyzerEnableValidValues[0]);

    // Verifying attribute's  values
    inputValueEnableAnalyzerEnable = initValueEnableAnalyzerEnable;
    for (auto&& value: enableAnalyzerEnableAnalyzerEnableValidValues) {
        inputValueEnableAnalyzerEnable = std::get<1>(value);
        modifier_->setEnableAnalyzer(node_, &inputValueEnableAnalyzerEnable);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANALYZER_ENABLE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: DISABLED_setAnalyzerConfigTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setAnalyzerConfigTestDefaultValues, TestSize.Level1)
{
    // analyzerConfig attribute is not implemented
}

/*
 * @tc.name: DISABLED_setAnalyzerConfigTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setAnalyzerConfigTestValidValues, TestSize.Level1)
{
    // analyzerConfig attribute is not implemented
}

/*
 * @tc.name: DISABLED_setAnalyzerConfigTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setAnalyzerConfigTestInvalidValues, TestSize.Level1)
{
    // analyzerConfig attribute is not implemented
}

static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> enableShortcutKeyTesdtPlan = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setEnableShortcutKey
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, setEnableShortcutKey, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SHORTCUT_KEY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_SHORTCUT_KEY_DEFAULT_VALUE);

    std::string expectedStr;
    Opt_Boolean inputValueEnableShortcutKey;

    for (auto&& value: enableShortcutKeyTesdtPlan) {
        inputValueEnableShortcutKey = std::get<1>(value);
        modifier_->setEnableShortcutKey(node_, &inputValueEnableShortcutKey);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SHORTCUT_KEY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, uint32_t, std::string>> setSurfaceBackgroundColorPlan = {
    {"BLACK", TEST_COLOR_BLACK_NUM, TEST_COLOR_BLACK},
    {"BLUE", TEST_COLOR_BLUE_NUM, TEST_COLOR_BLUE},
    {"RED", TEST_COLOR_RED_NUM, TEST_COLOR_RED},
};

/*
 * @tc.name: setSurfaceBackgroundColor
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoModifierTest, DISABLED_setSurfaceBackgroundColor, TestSize.Level1)
{
#ifdef WRONG_SDK
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SURFACE_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SURFACE_BACKGROUND_COLOR_DEFAULT_VALUE);
    std::string expectedStr;

    for (auto&& value: setSurfaceBackgroundColorPlan) {
        ColorMetricsPeer metrix;
        metrix.colorValue.value = std::get<1>(value);
        Opt_ColorMetrics backgroundColor = Converter::ArkValue<Opt_ColorMetrics>(&metrix);
        modifier_->setSurfaceBackgroundColor(node_, &backgroundColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SURFACE_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
#endif
}
} // namespace OHOS::Ace::NG
