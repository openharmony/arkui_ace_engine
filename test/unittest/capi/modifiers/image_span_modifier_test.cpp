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
#include <sstream>
#include <vector>

#include "image_common_methods_test.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace  {
    constexpr auto ATTRIBUTE_SRC_NAME = "src";
    constexpr auto ATTRIBUTE_SRC_DEFAULT_VALUE = "";
    constexpr auto ATTRIBUTE_RAWSRC_NAME = "rawSrc";
    constexpr auto ATTRIBUTE_RAWSRC_DEFAULT_VALUE = "";
    const auto TEST_VALUE = "test";
    const std::string IMAGES_OK_STR = "img_public_ok";
} // namespace

class ImageSpanModifierTest : public ModifierTestBase<
    GENERATED_ArkUIImageSpanModifier,
    &GENERATED_ArkUINodeModifiers::getImageSpanModifier,
    GENERATED_ARKUI_IMAGE_SPAN
> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        AddResource(IMAGES_OK_STR, TEST_VALUE);
    }
    RefPtr<PixelMap> CreatePixelMap(std::string& src);
};

RefPtr<PixelMap> ImageSpanModifierTest::CreatePixelMap(std::string& src)
{
    void* ptr = reinterpret_cast<void*>(src.data());
    return PixelMap::CreatePixelMap(ptr);
}

/*
 * @tc.name: setImageSpanOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setImageSpanOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SRC_DEFAULT_VALUE) << "Default value for attribute 'src'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RAWSRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RAWSRC_DEFAULT_VALUE) << "Default value for attribute 'rawSrc'";
}

/*
 * @tc.name: setImageSpanOptionsTestValidStrValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setImageSpanOptionsTestValidStrValues, TestSize.Level1)
{
    std::string strResult;
    std::string resultStr;
    std::string expectedStr = TEST_VALUE;
    auto subvalue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(Converter::ArkValue<Ark_String>(TEST_VALUE));
    auto options = Converter::ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(subvalue);
    modifier_->setImageSpanOptions(node_, &options);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(resultStr, expectedStr);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RAWSRC_NAME);
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setImageSpanOptionsTestValidResValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setImageSpanOptionsTestValidResValues, TestSize.Level1)
{
    std::string resultStr;
    std::string expectedStr = TEST_VALUE;
    auto subvalue = Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(
        CreateResource(IMAGES_OK_STR.c_str(), ResourceType::STRING));
    auto options = Converter::ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(subvalue);
    modifier_->setImageSpanOptions(node_, &options);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(resultStr, expectedStr);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RAWSRC_NAME);
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setImageSpanOptionsTestValidPixMapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setImageSpanOptionsTestValidPixMapValues, TestSize.Level1)
{
    std::string resultStr;
    std::string imagesSrc = TEST_VALUE;
    RefPtr<PixelMap> pixelMap = CreatePixelMap(imagesSrc);
    image_PixelMapPeer pixelMapPeer;
    pixelMapPeer.pixelMap = pixelMap;
    auto options = Converter::ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_image_PixelMap>(&pixelMapPeer);
    modifier_->setImageSpanOptions(node_, &options);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto imageProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageProperty, nullptr);
    auto imgInfo = imageProperty->GetImageSourceInfo();
    ASSERT_TRUE(imgInfo.has_value());
    EXPECT_EQ(imgInfo.value().GetPixmap(), pixelMap);
}

/*
 * @tc.name: setAltTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setAltTestValidValues, TestSize.Level1)
{
    std::string resultStr;
    std::string imagesSrc = TEST_VALUE;
    RefPtr<PixelMap> pixelMap = CreatePixelMap(imagesSrc);
    image_PixelMapPeer pixelMapPeer;
    pixelMapPeer.pixelMap = pixelMap;
    auto optPixelMap = Converter::ArkValue<Opt_image_PixelMap>(&pixelMapPeer);
    modifier_->setAlt(node_, &optPixelMap);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto imageProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageProperty, nullptr);
    auto imgInfo = imageProperty->GetAlt();
    ASSERT_TRUE(imgInfo.has_value());
    EXPECT_EQ(imgInfo.value().GetPixmap(), pixelMap);
}

const std::vector<LoadImageSuccessEvent> COMPLETE_EVENT_TEST_PLAN = {
    { LoadImageSuccessEvent(100, 100, 100, 100, 1, 100, 100, 100, 100) },
    { LoadImageSuccessEvent(10, 10, 10, 10, 1, 0, 0, 0, 0) },
    { LoadImageSuccessEvent(100, 100, 100, 100, 0, 100, 100, 0, 0) },
    { LoadImageSuccessEvent(10, 20, 30, 40, 1, 50, 60, 70, 80) },
};

/*
 * @tc.name: setColorFilterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, DISABLED_setColorFilterTest, TestSize.Level1)
{
#ifdef WRONG_SDK
    constexpr auto PRECISION = 6;
    ASSERT_TRUE(modifier_->setColorFilter);
    auto accessor = GeneratedModifier::GetColorFilterAccessor();
    ASSERT_TRUE(accessor);
    auto jsonValue = GetJsonValue(node_);
    auto result = GetAttrValue<std::string>(jsonValue, ColorFilter::ATTRIBUTE_COLOR_FILTER_NAME);
    EXPECT_EQ(result, ColorFilter::ATTRIBUTE_COLOR_FILTER_DEFAULT_VALUE);
    for (auto& [name, value, expected] : ColorFilter::floatMatrixTest) {
        std::stringstream expectedStream;
        expectedStream << std::fixed << std::setprecision(PRECISION);
        auto peer = accessor->construct(&value);
        ASSERT_TRUE(peer);
        auto unionValue = Converter::ArkUnion<Ark_Union_ColorFilter_drawing_ColorFilter, Ark_ColorFilter>(peer);
        auto optUnionValue = Converter::ArkValue<Opt_Union_ColorFilter_drawing_ColorFilter>(unionValue);
        modifier_->setColorFilter(node_, &optUnionValue);
        jsonValue = GetJsonValue(node_);
        for (const auto& elem : expected) {
            expectedStream << std::fixed << elem << " ";
        }
        result = GetAttrValue<std::string>(jsonValue, ColorFilter::ATTRIBUTE_COLOR_FILTER_NAME);
        EXPECT_EQ(result, expectedStream.str());
    }
#endif
}

/*
 * @tc.name: setOnCompleteTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, DISABLED_setOnCompleteTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnComplete, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static double width = 0.0;
    static double height = 0.0;
    static double componentWidth = 0.0;
    static double componentHeight = 0.0;
    static int32_t loadingStatus = 1;
    static double contentWidth = 0.0;
    static double contentHeight = 0.0;
    static double contentOffsetX = 0.0;
    static double contentOffsetY = 0.0;
    auto onComplete = [](const Ark_Int32 resourceId, const Ark_ImageLoadResult parameter) {
        width = Converter::Convert<float>(parameter.width);
        height = Converter::Convert<float>(parameter.height);
        componentWidth = Converter::Convert<float>(parameter.componentWidth);
        componentHeight = Converter::Convert<float>(parameter.componentHeight);
        loadingStatus = Converter::Convert<int32_t>(parameter.loadingStatus);
        contentWidth = Converter::Convert<float>(parameter.contentWidth);
        contentHeight = Converter::Convert<float>(parameter.contentHeight);
        contentOffsetX = Converter::Convert<float>(parameter.contentOffsetX);
        contentOffsetY = Converter::Convert<float>(parameter.contentOffsetY);
    };
    ImageCompleteCallback func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onComplete
    };

    auto optFunc = Converter::ArkValue<Opt_ImageCompleteCallback>(func);
    modifier_->setOnComplete(node_, &optFunc);

    for (const auto& testValue : COMPLETE_EVENT_TEST_PLAN) {
        eventHub->FireCompleteEvent(testValue);

        EXPECT_NEAR(width, testValue.GetWidth(), FLT_EPSILON);
        EXPECT_NEAR(height, testValue.GetHeight(), FLT_EPSILON);
        EXPECT_NEAR(componentWidth, testValue.GetComponentWidth(), FLT_EPSILON);
        EXPECT_NEAR(componentHeight, testValue.GetComponentHeight(), FLT_EPSILON);
        EXPECT_EQ(loadingStatus, testValue.GetLoadingStatus());
        EXPECT_NEAR(contentWidth, testValue.GetContentWidth(), FLT_EPSILON);
        EXPECT_NEAR(contentHeight, testValue.GetContentHeight(), FLT_EPSILON);
        EXPECT_NEAR(contentOffsetX, testValue.GetContentOffsetX(), FLT_EPSILON);
        EXPECT_NEAR(contentOffsetY, testValue.GetContentOffsetY(), FLT_EPSILON);
    };
}

const std::vector<LoadImageFailEvent> ERROR_EVENT_TEST_PLAN = {
    { LoadImageFailEvent(100, 100, "Error 1") },
    { LoadImageFailEvent(100, 10, "Error 2") },
    { LoadImageFailEvent(10, 100, "Error 3") },
    { LoadImageFailEvent(0, 0, "") },
};

/*
 * @tc.name: setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, DISABLED_setOnErrorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnComplete, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static double componentWidth = 0.0;
    static double componentHeight = 0.0;
    static std::string message;
    auto onError = [](const Ark_Int32 resourceId, const Ark_ImageError parameter) {
        componentWidth = Converter::Convert<float>(parameter.componentWidth);
        componentHeight = Converter::Convert<float>(parameter.componentHeight);
        message = Converter::Convert<std::string>(parameter.message);
    };
    ImageErrorCallback func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onError
    };
    auto optFunc = Converter::ArkValue<Opt_ImageErrorCallback>(func);
    modifier_->setOnError(node_, &optFunc);

    for (const auto& testValue : ERROR_EVENT_TEST_PLAN) {
        eventHub->FireErrorEvent(testValue);
        EXPECT_NEAR(componentWidth, testValue.GetComponentWidth(), FLT_EPSILON);
        EXPECT_NEAR(componentHeight, testValue.GetComponentHeight(), FLT_EPSILON);
        EXPECT_EQ(message, testValue.GetErrorMessage());
    };
}

} // namespace OHOS::Ace::NG
