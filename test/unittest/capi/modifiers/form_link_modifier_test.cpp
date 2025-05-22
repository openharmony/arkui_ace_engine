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

#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace Converter;
namespace  {
    const auto ATTRIBUTE_FORM_LINK_INFO = "formLinkInfo";
    const auto ATTRIBUTE_ACTION_NAME = "action";
    const auto ATTRIBUTE_ACTION_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MODULE_NAME_NAME = "moduleName";
    const auto ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_BUNDLE_NAME_NAME = "bundleName";
    const auto ATTRIBUTE_BUNDLE_NAME_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_ABILITY_NAME_NAME = "abilityName";
    const auto ATTRIBUTE_ABILITY_NAME_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_URI_NAME = "uri";
    const auto ATTRIBUTE_URI_DEFAULT_VALUE = "";

    const auto ACTION_1_NAME = "router";
    const auto MODULE_NAME = "testModule";
    const auto BUNDLE_NAME = "example.com";
    const auto ABILITY_NAME = "EntryAbiliy";
    const auto URI = "Index";

inline Ark_FormLinkOptions FormLinkOpt(const char *actionName)
{
    return {
        .action = ArkValue<Ark_String>(actionName),
        .moduleName = ArkValue<Opt_String>(MODULE_NAME),
        .bundleName = ArkValue<Opt_String>(BUNDLE_NAME),
        .abilityName = ArkValue<Opt_String>(ABILITY_NAME),
        .uri = ArkValue<Opt_String>(URI),
        .params = ArkValue<Opt_Object>(),
    };
}
} // namespace

class FormLinkModifierTest : public ModifierTestBase<GENERATED_ArkUIFormLinkModifier,
    &GENERATED_ArkUINodeModifiers::getFormLinkModifier, GENERATED_ARKUI_FORM_LINK> {
};

/*
 * @tc.name: setFormLinkOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormLinkModifierTest, DISABLED_setFormLinkOptionsTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_ACTION_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ACTION_DEFAULT_VALUE);

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_MODULE_NAME_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE);

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_BUNDLE_NAME_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_BUNDLE_NAME_DEFAULT_VALUE);

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_ABILITY_NAME_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ABILITY_NAME_DEFAULT_VALUE);

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_URI_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_URI_DEFAULT_VALUE);
}

/*
 * @tc.name: setFormLinkOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormLinkModifierTest, DISABLED_setFormLinkOptionsTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_FormLinkOptions inputValue = FormLinkOpt(ACTION_1_NAME);

    // Test
    modifier_->setFormLinkOptions(node_, &inputValue);

    // Initial verification
    auto json = GetJsonValue(node_);
    auto jsonInfo = json->GetObject(ATTRIBUTE_FORM_LINK_INFO);
    strResult = jsonInfo->GetString(ATTRIBUTE_ACTION_NAME);
    EXPECT_EQ(strResult, ACTION_1_NAME);
    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_MODULE_NAME_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE);

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_BUNDLE_NAME_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_BUNDLE_NAME_DEFAULT_VALUE);

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_ABILITY_NAME_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ABILITY_NAME_DEFAULT_VALUE);

    strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_URI_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_URI_DEFAULT_VALUE);
}
} // namespace OHOS::Ace::NG
