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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
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
} // OHOS::Ace::NG::Converter

namespace  {
    const auto ATTRIBUTE_FILL_COLOR_NAME = "fillColor";
    const auto ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto OPACITY_COLOR = "#FF000000";
    const auto ATTRIBUTE_AUTO_RESIZE_NAME = "autoResize";
    const auto ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE = "false";

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

// Valid values for attribute 'autoResize' of method 'autoResize'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> autoResizeAutoResizeValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

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
    initValueAutoResize = std::get<1>(autoResizeAutoResizeValidValues[0]);

    // Verifying attribute's  values
    inputValueAutoResize = initValueAutoResize;
    for (auto&& value: autoResizeAutoResizeValidValues) {
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

    const auto RES_NAME = NamedResourceId{resName.c_str(), NodeModifier::ResourceType::STRING};
    const auto RES_ID = IntResourceId{resID, NodeModifier::ResourceType::STRING};

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
    const auto emptyRes = IntResourceId{-1, NodeModifier::ResourceType::STRING};
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
} // namespace OHOS::Ace::NG
