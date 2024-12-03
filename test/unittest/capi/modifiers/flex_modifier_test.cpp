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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include <gtest/gtest.h>
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME = "constructor";
    const auto ATTRIBUTE_SET_FLEX_DIRECTION_NAME = "direction";
    const auto ATTRIBUTE_SET_FLEX_DIRECTION_DEFAULT_VALUE = "FlexDirection.Row";
    const auto ATTRIBUTE_SET_FLEX_WRAP_NAME = "wrap";
    const auto ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE = "FlexWrap.NoWrap";
    const auto ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME = "justifyContent";
    const auto ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME = "alignItems";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_DEFAULT_VALUE = "ItemAlign.Start";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME = "alignContent";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";
    const auto ATTRIBUTE_SET_FLEX_SPACE_NAME = "space";
    const auto ATTRIBUTE_SET_FLEX_SPACE_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_SET_FLEX_DIRECTION_VALID_VALUE = "FlexDirection.Column";
    const auto ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_VALID_VALUE = "FlexAlign.Center";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_WRAP_VALUE = "ItemAlign.Start";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_VALID_VALUE = "ItemAlign.Center";
    const auto ATTRIBUTE_POINT_LIGHT_NAME = "pointLight";
    const auto ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_NAME = "lightSource";
    const auto ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_DEFAULT_VALUE = "!NOT-DEFINED!";
    const auto ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME = "illuminated";
    const auto ATTRIBUTE_POINT_LIGHT_ILLUMINATED_DEFAULT_VALUE = "!NOT-DEFINED!";
    const auto ATTRIBUTE_POINT_LIGHT_BLOOM_NAME = "bloom";
    const auto ATTRIBUTE_POINT_LIGHT_BLOOM_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class FlexModifierTest : public ModifierTestBase<GENERATED_ArkUIFlexModifier,
 &GENERATED_ArkUINodeModifiers::getFlexModifier, GENERATED_ARKUI_FLEX> {
};

/*
 * @tc.name: SetFlexOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, SetFlexOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SET_FLEX_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SET_FLEX_SPACE_DEFAULT_VALUE);

    auto fullJson = GetJsonValue(node_);
    auto flexConstructorAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME);

    auto flexDirection = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_DIRECTION_NAME);
    EXPECT_EQ(flexDirection, ATTRIBUTE_SET_FLEX_DIRECTION_DEFAULT_VALUE);

    auto wrapAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_WRAP_NAME);
    EXPECT_EQ(wrapAttr, ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE);

    auto justifyContentAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(justifyContentAttr, ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_DEFAULT_VALUE);

    auto alignItemAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME);
    EXPECT_EQ(alignItemAttr, ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_DEFAULT_VALUE);

    auto alignContent = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME);
    EXPECT_EQ(alignContent, ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: SetFlexOptionsTestNoWrapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, SetFlexOptionsTestNoWrapValues, TestSize.Level1)
{
    std::string strResult;
    Opt_FlexOptions inputValue;
    Ark_FlexOptions flexOptions;
    flexOptions.direction.value = Converter::ArkValue<Ark_FlexDirection>(ARK_FLEX_DIRECTION_COLUMN);
    flexOptions.wrap.value = Converter::ArkValue<Ark_FlexWrap>(ARK_FLEX_WRAP_NO_WRAP);
    flexOptions.justifyContent.value = Converter::ArkValue<Ark_FlexAlign>(ARK_FLEX_ALIGN_CENTER);
    flexOptions.alignItems.value =  Converter::ArkValue<Ark_ItemAlign>(ARK_ITEM_ALIGN_CENTER);
    inputValue = Converter::ArkValue<Opt_FlexOptions>(flexOptions);
    modifier_->setFlexOptions(node_, &inputValue);
    auto fullJson = GetJsonValue(node_);

    auto flexConstructorAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME);

    auto wrapAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_WRAP_NAME);
    EXPECT_EQ(wrapAttr, ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE);

    auto alignItemAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME);
    EXPECT_EQ(alignItemAttr, ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_VALID_VALUE);

    auto justifyContentAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(justifyContentAttr, ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_VALID_VALUE);

    auto flexDirection = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_DIRECTION_NAME);
    EXPECT_EQ(flexDirection, ATTRIBUTE_SET_FLEX_DIRECTION_VALID_VALUE);

    auto alignContent = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME);
    EXPECT_EQ(alignContent, ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: SetFlexOptionsTestEmptyWrapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, SetFlexOptionsTestEmptyWrapValues, TestSize.Level1)
{
    std::string strResult;
    Opt_FlexOptions inputValue;
    Ark_FlexOptions flexOptions;
    flexOptions.direction = Converter::ArkValue<Opt_FlexDirection>(ARK_FLEX_DIRECTION_COLUMN);
    flexOptions.wrap = Converter::ArkValue<Opt_FlexWrap>(Ark_Empty());
    flexOptions.justifyContent = Converter::ArkValue<Opt_FlexAlign>(ARK_FLEX_ALIGN_CENTER);
    flexOptions.alignItems =  Converter::ArkValue<Opt_ItemAlign>(ARK_ITEM_ALIGN_CENTER);
    inputValue = Converter::ArkValue<Opt_FlexOptions>(flexOptions);
    modifier_->setFlexOptions(node_, &inputValue);
    auto fullJson = GetJsonValue(node_);

    auto flexConstructorAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME);

    auto wrapAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_WRAP_NAME);
    EXPECT_EQ(wrapAttr, ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE);

    auto alignItemAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME);
    EXPECT_EQ(alignItemAttr, ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_VALID_VALUE);

    auto justifyContentAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(justifyContentAttr, ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_VALID_VALUE);

    auto flexDirection = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_DIRECTION_NAME);
    EXPECT_EQ(flexDirection, ATTRIBUTE_SET_FLEX_DIRECTION_VALID_VALUE);

    auto alignContent = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME);
    EXPECT_EQ(alignContent, ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: SetFlexOptionsTestWrapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, SetFlexOptionsTestWrapValues, TestSize.Level1)
{
    std::string strResult;
    Opt_FlexOptions inputValue;
    Ark_FlexOptions flexOptions;
    flexOptions.direction.value = Converter::ArkValue<Ark_FlexDirection>(ARK_FLEX_DIRECTION_COLUMN);
    flexOptions.wrap.value = Converter::ArkValue<Ark_FlexWrap>(ARK_FLEX_WRAP_WRAP);
    flexOptions.justifyContent.value = Converter::ArkValue<Ark_FlexAlign>(ARK_FLEX_ALIGN_CENTER);
    flexOptions.alignItems.value =  Converter::ArkValue<Ark_ItemAlign>(ARK_ITEM_ALIGN_CENTER);

    inputValue = Converter::ArkValue<Opt_FlexOptions>(flexOptions);
    modifier_->setFlexOptions(node_, &inputValue);
    auto fullJson = GetJsonValue(node_);
    auto flexConstructorAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME);

    auto wrapAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_WRAP_NAME);
    EXPECT_EQ(wrapAttr, ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE);

    auto alignItemAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME);
    EXPECT_EQ(alignItemAttr, ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_WRAP_VALUE);

    auto justifyContentAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(justifyContentAttr, ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_DEFAULT_VALUE);

    auto flexDirection = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_DIRECTION_NAME);
    EXPECT_EQ(flexDirection, ATTRIBUTE_SET_FLEX_DIRECTION_VALID_VALUE);

    auto alignContent = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME);
    EXPECT_EQ(alignContent, ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: setPointLightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest,  DISABLED_setPointLightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultPointLight =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_BLOOM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_BLOOM_DEFAULT_VALUE);
}

/*
 * @tc.name: setPointLightTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest,  DISABLED_setPointLightTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPointLight;
    std::string resultStr;
    Ark_PointLightStyle inputValuePointLight;

    //Initial setup

    inputValuePointLight.illuminated = Converter::ArkValue<Opt_IlluminatedType>(ARK_ILLUMINATED_TYPE_NONE);
    // Valid values are not defined for attribute 'bloom' of type 'Opt_Number'

    // Test
    modifier_->setPointLight(node_, &inputValuePointLight);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_NAME);
    EXPECT_EQ(resultStr, "!NOT-DEFINED!");
    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, "IlluminatedType.NONE");
    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_BLOOM_NAME);
    EXPECT_EQ(resultStr, "!NOT-DEFINED!");

    // Verifying attribute's 'illuminated' other values
    inputValuePointLight.illuminated = Converter::ArkValue<Opt_IlluminatedType>(ARK_ILLUMINATED_TYPE_BORDER);
    modifier_->setPointLight(node_, &inputValuePointLight);
    jsonValue = GetJsonValue(node_);
    resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, "IlluminatedType.BORDER");

    inputValuePointLight.illuminated = Converter::ArkValue<Opt_IlluminatedType>(ARK_ILLUMINATED_TYPE_CONTENT);
    modifier_->setPointLight(node_, &inputValuePointLight);
    jsonValue = GetJsonValue(node_);
    resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, "IlluminatedType.CONTENT");

    inputValuePointLight.illuminated = Converter::ArkValue<Opt_IlluminatedType>(ARK_ILLUMINATED_TYPE_BORDER_CONTENT);
    modifier_->setPointLight(node_, &inputValuePointLight);
    jsonValue = GetJsonValue(node_);
    resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, "IlluminatedType.BORDER_CONTENT");

    inputValuePointLight.illuminated = Converter::ArkValue<Opt_IlluminatedType>(ARK_ILLUMINATED_TYPE_BLOOM_BORDER);
    modifier_->setPointLight(node_, &inputValuePointLight);
    jsonValue = GetJsonValue(node_);
    resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, "IlluminatedType.BLOOM_BORDER");

    inputValuePointLight.illuminated =
     Converter::ArkValue<Opt_IlluminatedType>(ARK_ILLUMINATED_TYPE_BLOOM_BORDER_CONTENT);
    modifier_->setPointLight(node_, &inputValuePointLight);
    jsonValue = GetJsonValue(node_);
    resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
}

/*
 * @tc.name: setPointLightTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest,  DISABLED_setPointLightTestInvalidValues, TestSize.Level1)
{
}
} // namespace OHOS::Ace::NG
