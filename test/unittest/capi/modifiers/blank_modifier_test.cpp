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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class BlankModifierTest : public ModifierTestBase<GENERATED_ArkUIBlankModifier,
    &GENERATED_ArkUINodeModifiers::getBlankModifier, GENERATED_ARKUI_BLANK> {
};

/**
 * @tc.name: setColorTestVariant001
 * @tc.desc: Check the functionality of BlankModifier.setColor
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, DISABLED_setColorTestVariant001, TestSize.Level1)
{
    constexpr auto propName = "color";
    ASSERT_NE(modifier_->setColor, nullptr);

    auto checkVal1 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal1, Eq("#00000000"));
    Opt_ResourceColor optColor = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setColor(node_, &optColor);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal2, Eq("#FFFFFFFF"));

    Opt_ResourceColor optNumberInt = Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456);
    modifier_->setColor(node_, &optNumberInt);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal3, Eq("#FF123456"));

    Opt_ResourceColor optNumberFlt = Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0.5f);
    modifier_->setColor(node_, &optNumberFlt);
    auto checkVal4 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal4, Eq("#00000000"));

    Opt_ResourceColor optStrColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344");
    modifier_->setColor(node_, &optStrColor);
    auto checkVal5 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal5, Eq("#11223344"));

    Opt_ResourceColor optStrNumber = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535");
    modifier_->setColor(node_, &optStrNumber);
    auto checkVal6 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal6, Eq("#FF00FFFF"));

    auto optResNameColor = CreateResourceUnion<Opt_ResourceColor>(
        NamedResourceId{"aa.bb.cc", ResourceType::COLOR});
    modifier_->setColor(node_, &optResNameColor);
    auto checkVal7 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal7, Eq("#FFFF0000")); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto optResIdColor = CreateResourceUnion<Opt_ResourceColor>(IntResourceId{1234, ResourceType::COLOR});
    modifier_->setColor(node_, &optResIdColor);
    auto checkVal8 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal8, Eq("#FFFF0000")); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setBlankOptionsTestVariant002
 * @tc.desc: Check the functionality of BlankModifier.setBlankOptions
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, DISABLED_setBlankOptionsTestVariant002, TestSize.Level1)
{
    constexpr auto propName = "min";
    ASSERT_NE(modifier_->setBlankOptions, nullptr);

    auto checkVal1 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal1, Eq("0.00px"));

    auto intNegVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-123.);
    modifier_->setBlankOptions(node_, &intNegVal);
    auto checkVal7 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal7, Eq("0.00px"));

    auto floatNegVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-1.23f);
    modifier_->setBlankOptions(node_, &floatNegVal);
    auto checkVal8 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal8, Eq("0.00px"));

    auto pxNegVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("-4.5px");
    modifier_->setBlankOptions(node_, &pxNegVal);
    auto checkVal9 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal9, Eq("0.00px"));

    auto vpNegVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("-56vp");
    modifier_->setBlankOptions(node_, &vpNegVal);
    auto checkVal10 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal10, Eq("0.00px"));

    auto undefVal = Converter::ArkValue<Opt_Union_F64_String>();
    modifier_->setBlankOptions(node_, &undefVal);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal2, Eq("0.00px"));

    auto intVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(123.);
    modifier_->setBlankOptions(node_, &intVal);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal3, Eq("123.00vp"));

    auto floatVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.23);
    modifier_->setBlankOptions(node_, &floatVal);
    auto checkVal4 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal4, Eq("1.23vp"));

    auto pxVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("45px");
    modifier_->setBlankOptions(node_, &pxVal);
    auto checkVal5 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal5, Eq("45.00px"));

    auto vpVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("5.6vp");
    modifier_->setBlankOptions(node_, &vpVal);
    auto checkVal6 = GetAttrValue<std::string>(node_, propName);
    EXPECT_THAT(checkVal6, Eq("5.60vp"));
}
} // namespace OHOS::Ace::NG
