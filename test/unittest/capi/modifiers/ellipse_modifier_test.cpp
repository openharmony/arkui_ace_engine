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
namespace  {
    const auto ATTRIBUTE_WIDTH_NAME = "width";
    const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "0.00vp";

    const auto ATTRIBUTE_HEIGHT_NAME = "height";
    const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "0.00vp";

    // test plans
    typedef std::pair<Opt_Union_String_F64, std::string> DimensionTestStep;
    static const std::vector<DimensionTestStep> VALID_VALUE_TEST_PLAN = {
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_Float64>(1.), "1.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_Float64>(0.), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_Float64>(2.45), "2.45vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("5px"), "5.00px" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("22.35px"), "22.35px" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("7vp"), "7.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("1.65vp"), "1.65vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("65fp"), "65.00fp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("4.3fp"), "4.30fp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("11lpx"), "11.00lpx" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("0.5lpx"), "0.50lpx" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("3"), "3.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("10.65"), "10.65vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("23%"), "23.00%" },
    };
    static const std::vector<DimensionTestStep> INVALID_VALUE_TEST_PLAN = {
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_Float64>(-1.), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_Float64>(-3.56), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("invalid value"), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-8px"), "0.00px" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-15.6px"), "0.00px" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-21vp"), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-8.6vp"), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-32fp"), "0.00fp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-9.99fp"), "0.00fp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-22lpx"), "0.00lpx" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-1.23lpx"), "0.00lpx" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-6"), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_String_F64, Ark_String>("-16.2"), "0.00vp" },
    };
} // namespace

class EllipseModifierTest : public ModifierTestBase<GENERATED_ArkUIEllipseModifier,
    &GENERATED_ArkUINodeModifiers::getEllipseModifier, GENERATED_ARKUI_ELLIPSE> {
};

/*
 * @tc.name: setEllipseOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseModifierTest, setEllipseOptionsTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);

    strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
}

/*
 * @tc.name: setEllipseOptionsTestValidWidthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseModifierTest, setEllipseOptionsTestValidWidthValues, TestSize.Level1)
{
    std::string strResult;
    Opt_EllipseOptions optionsOpt;
    Ark_EllipseOptions options;
    options.height = Converter::ArkValue<Opt_Union_String_F64>(Ark_Empty());

    for (const auto &[width, expected]: VALID_VALUE_TEST_PLAN) {
        options.width = width;
        optionsOpt = Converter::ArkValue<Opt_EllipseOptions>(options);
        modifier_->setEllipseOptions(node_, &optionsOpt);

        strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setEllipseOptionsTestValidHeightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseModifierTest, setEllipseOptionsTestValidHeightValues, TestSize.Level1)
{
    std::string strResult;
    Opt_EllipseOptions optionsOpt;
    Ark_EllipseOptions options;
    options.width = Converter::ArkValue<Opt_Union_String_F64>(Ark_Empty());

    for (const auto &[height, expected]: VALID_VALUE_TEST_PLAN) {
        options.height = height;
        optionsOpt = Converter::ArkValue<Opt_EllipseOptions>(options);
        modifier_->setEllipseOptions(node_, &optionsOpt);

        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, expected);
        strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setEllipseOptionsTestInvalidWidthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseModifierTest, setEllipseOptionsTestInvalidWidthValues, TestSize.Level1)
{
    std::string strResult;
    Opt_EllipseOptions optionsOpt;
    Ark_EllipseOptions options;
    options.height = Converter::ArkValue<Opt_Union_String_F64>(Ark_Empty());

    for (const auto &[width, expected]: INVALID_VALUE_TEST_PLAN) {
        options.width = width;
        optionsOpt = Converter::ArkValue<Opt_EllipseOptions>(options);
        modifier_->setEllipseOptions(node_, &optionsOpt);

        strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setEllipseOptionsTestInvalidHeightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseModifierTest, setEllipseOptionsTestInvalidHeightValues, TestSize.Level1)
{
    std::string strResult;
    Opt_EllipseOptions optionsOpt;
    Ark_EllipseOptions options;
    options.width = Converter::ArkValue<Opt_Union_String_F64>(Ark_Empty());

    for (const auto &[height, expected]: INVALID_VALUE_TEST_PLAN) {
        options.height = height;
        optionsOpt = Converter::ArkValue<Opt_EllipseOptions>(options);
        modifier_->setEllipseOptions(node_, &optionsOpt);

        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, expected);
        strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    }
}
} // namespace OHOS::Ace::NG
