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
#include <tuple>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "generated/test_fixtures.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace Converter {
template<>
LoadImageFailEvent Convert(const Ark_ImageError& info)
{
    auto width = Convert<float>(info.componentWidth);
    auto height = Convert<float>(info.componentHeight);
    auto error = Convert<std::string>(info.message);
    LoadImageFailEvent event(width, height, error);
    return event;
}

template<>
LoadImageSuccessEvent Convert(const Ark_Type_ImageAttribute_onComplete_callback_event& event)
{
    LoadImageSuccessEvent info(
        Convert<float>(event.width),
        Convert<float>(event.height),
        Convert<float>(event.componentWidth),
        Convert<float>(event.componentHeight),
        Convert<int>(event.loadingStatus),
        Convert<float>(event.contentOffsetX),
        Convert<float>(event.contentOffsetY),
        Convert<float>(event.contentWidth),
        Convert<float>(event.contentHeight)
    );
    return info;
}
} // OHOS::Ace::NG::Converter

namespace  {
    const auto ATTRIBUTE_FILL_COLOR_NAME = "fillColor";
    const auto ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto OPACITY_COLOR = "#FF000000";
    const auto ATTRIBUTE_AUTO_RESIZE_NAME = "autoResize";
    const auto ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_DRAGGABLE_NAME = "draggable";
    const auto ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_SOURCE_SIZE_NAME = "sourceSize";
    const auto ATTRIBUTE_SOURCE_SIZE_DEFAULT_VALUE = "[0.00 x 0.00]";


    // Valid values for boolean values
    const std::vector<std::tuple<std::string, Ark_Boolean, std::string>> validBoolean = {
        {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
        {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
    };

    struct EventsTracker {
        static inline GENERATED_ArkUIImageEventsReceiver getImageEventsReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getImageEventsReceiver = [] () -> const GENERATED_ArkUIImageEventsReceiver* {
                return &getImageEventsReceiver;
            }
        };
    }; // EventsTracker
} // namespace

class ImageModifierTest : public ModifierTestBase<GENERATED_ArkUIImageModifier,
    &GENERATED_ArkUINodeModifiers::getImageModifier,
    GENERATED_ARKUI_IMAGE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        for (auto&& res : Fixtures::resourceInitTable) {
            AddResource(std::get<0>(res), std::get<2>(res)); // 2 - index of resource
            AddResource(std::get<1>(res), std::get<2>(res)); // 2 - index of resource
        }
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};
/*
 * @tc.name: setFillColorTestDefaultValues
 * @tc.desc: Check functionality of ImageModifier.setFillColor
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFillColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setFillColorTestValidValues
 * @tc.desc: Check functionality of ImageModifier.setFillColor
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFillColorTestValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        modifier_->setFillColor(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor,
            Ark_String>(std::get<1>(value)), OPACITY_COLOR);
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)),
            ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setAutoResizeTestDefaultValues
 * @tc.desc: Check functionality of ImageModifier.setAutoResize
 * Disabled because the default value should be false, but the returned value is true.
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAutoResizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE);
}

/*
 * @tc.name: setAutoResizeTestValidValues
 * @tc.desc: Check set color functionality of setCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAutoResizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueAutoResize;
    Ark_Boolean initValueAutoResize;

    // Initial setup
    initValueAutoResize = std::get<1>(validBoolean[0]);

    // Verifying attribute's  values
    inputValueAutoResize = initValueAutoResize;
    for (auto&& value: validBoolean) {
        inputValueAutoResize = std::get<1>(value);
        modifier_->setAutoResize(node_, inputValueAutoResize);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESIZE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOnFinishTest
 * @tc.desc: Check functionality of ImageModifier.setOnFinish
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setOnFinishTest, TestSize.Level1)
{
    Callback_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::getImageEventsReceiver.onFinish = [](
        Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
        };
    };

    EXPECT_FALSE(checkEvent.has_value());
    modifier_->setOnFinish(node_, &func);
    eventHub->FireFinishEvent();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnErrorTest
 * @tc.desc: Check functionality of ImageModifier.setOnError
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setOnErrorTest, TestSize.Level1)
{
    ImageErrorCallback func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    const auto width = 0.5f;
    const auto height = 0.6f;
    const auto error = "error_test";
    LoadImageFailEvent event(width, height, error);

    struct CheckEvent {
        int32_t nodeId;
        double width;
        double height;
        std::string error;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::getImageEventsReceiver.onError = [](
        Ark_Int32 nodeId, const Ark_ImageError error)
    {
        auto event = Converter::Convert<LoadImageFailEvent>(error);
        checkEvent = {
            .nodeId = nodeId,
            .width = event.GetComponentWidth(),
            .height = event.GetComponentHeight(),
            .error = event.GetErrorMessage()
        };
    };

    EXPECT_FALSE(checkEvent.has_value());
    modifier_->setOnError(node_, &func);
    eventHub->FireErrorEvent(event);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_NEAR(checkEvent->width, width, FLT_EPSILON);
    EXPECT_NEAR(checkEvent->height, height, FLT_EPSILON);
    EXPECT_EQ(checkEvent->error, error);
}

/**
 * @tc.name: ObjectFit_SetFitType
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, ObjectFit_SetFitType, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::vector<std::pair<std::string, Ark_ImageFit>> testMap = {
        {"ImageFit.Contain", Ark_ImageFit::ARK_IMAGE_FIT_CONTAIN},
        {"ImageFit.Cover", Ark_ImageFit::ARK_IMAGE_FIT_COVER},
        {"ImageFit.Auto", Ark_ImageFit::ARK_IMAGE_FIT_AUTO},
        {"ImageFit.Fill", Ark_ImageFit::ARK_IMAGE_FIT_FILL},
        {"ImageFit.ScaleDown", Ark_ImageFit::ARK_IMAGE_FIT_SCALE_DOWN},
        {"ImageFit.None", Ark_ImageFit::ARK_IMAGE_FIT_NONE},
    };

    for (auto& tv : testMap) {
        modifier_->setObjectFit(frameNode, tv.second);
        auto json = GetJsonValue(node_);
        ASSERT_TRUE(json);
        ASSERT_EQ(tv.first, GetAttrValue<std::string>(json, "objectFit"));
    }
}

/**
 * @tc.name: ObjectFit_SetDefaultedFitType
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, ObjectFit_SetDefaultedFitType, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string key = "objectFit";
    std::string defaultedFit = "ImageFit.Cover";

    modifier_->setObjectFit(
        frameNode,
        static_cast<Ark_ImageFit>(INT_MAX)
    );
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(defaultedFit, GetAttrValue<std::string>(json, key));
}

/**
 * @tc.name: SetImageOptions_SetResourceUrl
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, SetImageOptions_SetResourceUrl, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string urlString = "https://www.example.com/xxx.png";
    std::string resName = "app.string.image_url";
    AddResource(resName, urlString);

    int resID = 2345;
    std::string urlStringId = "https://www.example.com/xxx_id.png";
    AddResource(resID, urlStringId);

    const auto RES_NAME = NamedResourceId{resName.c_str(), Converter::ResourceType::STRING};
    const auto RES_ID = IntResourceId{resID, Converter::ResourceType::STRING};

    std::vector<std::pair<Ark_ResourceStr, std::string>> tests = {
        {CreateResourceUnion<Ark_ResourceStr>(RES_NAME), urlString},
        {CreateResourceUnion<Ark_ResourceStr>(RES_ID), urlStringId}
    };

    for (auto & v: tests) {
        auto imageRc = Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(
            v.first);
        modifier_->setImageOptions0(node_, &imageRc);
        auto json = GetJsonValue(node_);
        ASSERT_TRUE(json);
        ASSERT_EQ(v.second, GetAttrValue<std::string>(json, "src"));
        ASSERT_EQ(v.second, GetAttrValue<std::string>(json, "rawSrc"));
    }
}

/**
 * @tc.name: SetImageOptions_SetUndefinedResourceUrl
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, SetImageOptions_SetUndefinedResourceUrl, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    // set initial nondefault state
    std::string urlString = "https://www.example.com/xxx.jpg";
    auto image = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(Converter::ArkValue<Ark_String>(urlString));
    auto imageBefore = Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(image);
    modifier_->setImageOptions0(node_, &imageBefore);
    // verify the change
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "src"));
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "rawSrc"));
    // try unknown resource id
    const auto emptyRes = IntResourceId{-1, Converter::ResourceType::STRING};
    auto resUnion = CreateResourceUnion<Ark_ResourceStr>(emptyRes);
    auto imageRc = Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(resUnion);
    modifier_->setImageOptions0(node_, &imageRc);
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    // our predefined state must retain
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "src"));
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "rawSrc"));
}

/**
 * @tc.name: SetImageOptions_SetStringUrl
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, SetImageOptions_SetStringUrl, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string urlString = "https://www.example.com/xxx.jpg";
    auto image = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(Converter::ArkValue<Ark_String>(urlString));
    auto imageRc = Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(image);

    modifier_->setImageOptions0(node_, &imageRc);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "src"));
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "rawSrc"));
}

/**
 * @tc.name: SetImageOptions_SetStringUrl
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, SetImageOptions_SetEmptyUrl, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    // set initial state
    std::string urlString = "https://www.example.com/xxx.jpg";
    auto image = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(Converter::ArkValue<Ark_String>(urlString));
    auto imageRc = Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(image);

    modifier_->setImageOptions0(node_, &imageRc);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "src"));
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "rawSrc"));

    urlString = "";
    image = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(Converter::ArkValue<Ark_String>(urlString));
    imageRc = Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(image);

    modifier_->setImageOptions0(node_, &imageRc);
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "src"));
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "rawSrc"));
}


/**
 * @tc.name: SetImageOptions_NullOptions
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, SetImageOptions_NullOptions, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto json = GetJsonValue(node_);
    auto srcBefore = GetAttrValue<std::string>(json, "src");
    modifier_->setImageOptions0(node_, nullptr);
    json = GetJsonValue(node_);
    auto srcAfter = GetAttrValue<std::string>(json, "src");
    ASSERT_EQ(srcBefore, srcAfter);
}

/*
 * @tc.name: setDraggableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setDraggableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OnModifyDone();

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DRAGGABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE) << "Default value for attribute 'draggable'";
}

/*
 * @tc.name: setDraggableTestDraggableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setDraggableTestDraggableValidValues, TestSize.Level1)
{
    Ark_Boolean initValueDraggable;

    // Initial setup
    initValueDraggable = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueDraggable](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueDraggable = initValueDraggable;

        inputValueDraggable = value;
        modifier_->setDraggable(node_, inputValueDraggable);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto imagePattern = frameNode->GetPattern();
        ASSERT_NE(imagePattern, nullptr);
        imagePattern->OnModifyDone();
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DRAGGABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDraggable, attribute: draggable";
    };

    for (auto& [input, value, expected] : validBoolean) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setSourceSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setSourceSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto resultSourceSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SOURCE_SIZE_NAME);
    EXPECT_EQ(resultSourceSize, ATTRIBUTE_SOURCE_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'sourceSize'";
}

/*
 * @tc.name: setSourceSizeTestSourceSizeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setSourceSizeTestSourceSizeWidthValues, TestSize.Level1)
{
    // Fixture 'NumberAnything' for type 'Ark_Number'
    const std::vector<std::tuple<std::string, Ark_Number, std::string>> testPlan = {
        { "100", Converter::ArkValue<Ark_Number>(100), "[100.00 x 100.00]" },
        { "0", Converter::ArkValue<Ark_Number>(0), "[0.00 x 100.00]" },
        { "-100", Converter::ArkValue<Ark_Number>(-100), "[0.00 x 0.00]" },
        { "12.34", Converter::ArkValue<Ark_Number>(12.34), "[12.34 x 100.00]" },
        { "-56.78", Converter::ArkValue<Ark_Number>(-56.78), "[0.00 x 0.00]" },
    };

    Ark_ImageSourceSize initValueSourceSize;

    // Initial setup
    initValueSourceSize.width = std::get<1>(testPlan[0]);
    initValueSourceSize.height = std::get<1>(testPlan[0]);

    auto checkValue = [this, &initValueSourceSize](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_ImageSourceSize inputValueSourceSize = initValueSourceSize;

        inputValueSourceSize.width = value;
        modifier_->setSourceSize(node_, &inputValueSourceSize);
        std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
        auto resultSourceSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SOURCE_SIZE_NAME);
        EXPECT_EQ(resultSourceSize, expectedStr) <<
            "Default value for attribute 'sourceSize'";
    };

    for (auto& [input, value, expected] : testPlan) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setSourceSizeTestSourceSizeHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setSourceSizeTestSourceSizeHeightValues, TestSize.Level1)
{
    // Fixture 'NumberAnything' for type 'Ark_Number'
    const std::vector<std::tuple<std::string, Ark_Number, std::string>> testPlan = {
        { "100", Converter::ArkValue<Ark_Number>(100), "[100.00 x 100.00]" },
        { "0", Converter::ArkValue<Ark_Number>(0), "[100.00 x 0.00]" },
        { "-100", Converter::ArkValue<Ark_Number>(-100), "[0.00 x 0.00]" },
        { "12.34", Converter::ArkValue<Ark_Number>(12.34), "[100.00 x 12.34]" },
        { "-56.78", Converter::ArkValue<Ark_Number>(-56.78), "[0.00 x 0.00]" },
    };

    Ark_ImageSourceSize initValueSourceSize;

    // Initial setup
    initValueSourceSize.width = std::get<1>(testPlan[0]);
    initValueSourceSize.height = std::get<1>(testPlan[0]);

    auto checkValue = [this, &initValueSourceSize](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_ImageSourceSize inputValueSourceSize = initValueSourceSize;

        inputValueSourceSize.height = value;
        modifier_->setSourceSize(node_, &inputValueSourceSize);
        std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
        auto resultSourceSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SOURCE_SIZE_NAME);
        EXPECT_EQ(resultSourceSize, expectedStr) <<
            "Default value for attribute 'sourceSize'";
    };

    for (auto& [input, value, expected] : testPlan) {
        checkValue(input, expected, value);
    }
}

MATCHER_P2(CompareLoadImageSuccessEvent, event1, event2, "LoadImageSuccessEvent compare")
{
    return event1.width == event2.width &&
        event1.height == event2.height &&
        event1.componentWidth == event2.componentWidth &&
        event1.componentHeight == event2.componentHeight &&
        event1.loadingStatus == event2.loadingStatus &&
        event1.contentOffsetX == event2.contentOffsetX &&
        event1.contentOffsetY == event2.contentOffsetY &&
        event1.contentWidth == event2.contentWidth &&
        event1.contentHeight == event2.contentHeight;
}
/*
 * @tc.name: setOnCompleteTest
 * @tc.desc: Check functionality of ImageModifier.setOnComplete
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setOnCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    auto widthHeight = 100.0f;
    static constexpr int32_t contextId = 123;
    const LoadImageSuccessEvent info (widthHeight, widthHeight, widthHeight, widthHeight, 0,
        widthHeight, widthHeight, widthHeight, widthHeight);

    struct CheckEvent {
        int32_t resourceId;
        LoadImageSuccessEvent info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onComplete = [](
        const Ark_Int32 resourceId, const Opt_Type_ImageAttribute_onComplete_callback_event event)
    {
        auto info = Converter::OptConvert<LoadImageSuccessEvent>(event);
        if (info) {
            checkEvent = {
                .resourceId = resourceId,
                .info = *info,
            };
        }
    };

    auto arkCallback =
        Converter::ArkValue<Callback_Type_ImageAttribute_onComplete_callback_event_Void>(onComplete, contextId);

    EXPECT_FALSE(checkEvent);
    modifier_->setOnComplete(node_, &arkCallback);
    eventHub->FireCompleteEvent(info);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    CompareLoadImageSuccessEvent(checkEvent->info, info);
}
} // namespace OHOS::Ace::NG
