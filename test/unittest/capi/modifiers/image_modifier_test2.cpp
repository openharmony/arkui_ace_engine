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
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "generated/test_fixtures.h"
#include "point_light_test.h"
#include "generated/type_helpers.h"
#include "arkoala_api_generated.h"
#include "test/unittest/capi/stubs/ace_pixelmap_stub.h"
#include "core/components/image/image_theme.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::TypeHelper;
using namespace OHOS::Ace::NG::PointLight;

namespace OHOS::Ace::NG {
namespace Converter {

} // OHOS::Ace::NG::Converter

namespace  {
    const auto ATTRIBUTE_ALT_NAME = "alt";
    const auto ATTRIBUTE_ALT_DEFAULT_VALUE = "";

    const std::string CHECK_RESOURCE_THEME_STR("www.example.test/image_source.png");
    const std::string CHECK_RESOURCE_LOCAL_STR("path/to/image/image_source.png");
    const std::string IMAGE_RESOURCE_THEME_KEY = "image_source";
    const auto IMAGE_RES_ID = 555;

} // namespace

class ImageModifierTest2 : public ModifierTestBase<GENERATED_ArkUIImageModifier,
    &GENERATED_ArkUINodeModifiers::getImageModifier,
    GENERATED_ARKUI_IMAGE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        auto themeStyle = SetupThemeStyle(THEME_PATTERN_IMAGE);
        SetupTheme<ImageTheme>();
        AddResource(IMAGE_RESOURCE_THEME_KEY, CHECK_RESOURCE_THEME_STR);
        AddResource(IMAGE_RES_ID, CHECK_RESOURCE_THEME_STR);
    }
};

/*
 * @tc.name: setAltTestDefaultValues
 * @tc.desc: Check functionality of ImageModifier.setAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest2, setAltTestDefaultValues, TestSize.Level1)
{
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALT_DEFAULT_VALUE);
}

/*
 * @tc.name: setAlt_ArkStringUnion_Test
 * @tc.desc: Check functionality of ImageModifier.setAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest2, setAlt_ArkStringUnion_Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAlt, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string expectedStr = CHECK_RESOURCE_LOCAL_STR;
    auto inputStr = Converter::ArkUnion<Ark_Union_String_Resource_PixelMap, Ark_String>(
        Converter::ArkValue<Ark_String>(expectedStr));
    modifier_->setAlt(frameNode, &inputStr);
    auto fullJson = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(fullJson, ATTRIBUTE_ALT_NAME);
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setAlt_ArkResourceUnion_Test
 * @tc.desc: Check functionality of ImageModifier.setAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest2, setAlt_ArkResourceUnion_Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAlt, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string expectedStr = CHECK_RESOURCE_THEME_STR;
    std::vector<std::string> paramsVector = {IMAGE_RESOURCE_THEME_KEY};
    Converter::ArkArrayHolder<Array_String> paramsStringArrayHolder(paramsVector);
    Array_String paramsArkArrayValues = paramsStringArrayHolder.ArkValue();
    Ark_Resource expectedArkResource = {
        .bundleName = Converter::ArkValue<Ark_String>("testBundle"),
        .moduleName = Converter::ArkValue<Ark_String>("testModule"),
        .id = Converter::ArkValue<Ark_Number>(IMAGE_RES_ID),
        .params = Converter::ArkValue<Opt_Array_String>(paramsArkArrayValues),
        .type = Converter::ArkValue<Opt_Number>(10003) // ResourceType::STRING = 10003
    };
    auto inputArkResource = Converter::ArkUnion<Ark_Union_String_Resource_PixelMap, Ark_Resource>(expectedArkResource);
    modifier_->setAlt(frameNode, &inputArkResource);
    auto fullJson = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(fullJson, ATTRIBUTE_ALT_NAME);
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setAlt_PixelMapUnion_Test
 * @tc.desc: Check functionality of ImageModifier.setAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest2, setAlt_PixelMapUnion_Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAlt, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    Ace::RefPtr<Ace::PixelMap> expectedPixelMapRefPtr = AceType::MakeRefPtr<Ace::PixelMapStub>();
    PixelMapPeer pixelMapPeer;
    pixelMapPeer.pixelMap = expectedPixelMapRefPtr;
    Ark_PixelMap expectedPixelMap{.ptr = reinterpret_cast<Ark_NativePointer>(&pixelMapPeer)};
    auto inputArkPixelMap = Converter::ArkUnion<Ark_Union_String_Resource_PixelMap, Ark_PixelMap>(expectedPixelMap);
    modifier_->setAlt(frameNode, &inputArkPixelMap);

    auto imageLayoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    std::optional<ImageSourceInfo> alt = imageLayoutProperty->GetAlt();
    EXPECT_TRUE(alt.has_value());
    EXPECT_TRUE(alt->IsPixmap());

    auto resultPixelMap = alt->GetPixmap();
    EXPECT_EQ(resultPixelMap, expectedPixelMapRefPtr);
}

} // namespace OHOS::Ace::NG
