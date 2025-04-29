/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include <memory>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/property/border_property.h"

using namespace testing;
using namespace testing::ext;

class BorderPropertyTestNg : public testing::Test {};

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
}

/**
 * @tc.name: BorderPropertyTestNg001
 * @tc.desc: Test BorderStyleProperty::ToJsonValue function.
 * @tc.type: FUNC
 */
HWTEST_F(BorderPropertyTestNg, BorderPropertyTestNg001, TestSize.Level1)
{
    BorderStyleProperty borderStyleProperty;
    borderStyleProperty.multiValued = true;

    /**
     * @tc.steps: step1. set multiValued is true, use the default borderStyle and call ToJsonValue
     * @tc.expected: the return value is false.
     */
    auto json = JsonUtil::Create(true);
    auto borderJson = JsonUtil::Create(true);
    borderStyleProperty.ToJsonValue(json, borderJson, filter);

    auto ret = json->GetValue("borderStyle")->GetString("left", "");
    EXPECT_EQ(ret, "BorderStyle.Solid");
    ret = json->GetValue("borderStyle")->GetString("top", "");
    EXPECT_EQ(ret, "BorderStyle.Solid");
    ret = json->GetValue("borderStyle")->GetString("right", "");
    EXPECT_EQ(ret, "BorderStyle.Solid");
    ret = json->GetValue("borderStyle")->GetString("bottom", "");
    EXPECT_EQ(ret, "BorderStyle.Solid");

    /**
     * @tc.steps: step2. set multiValued is true, use the default borderStyle and call ToJsonValue
     * @tc.expected: the return value is false.
     */
    json = JsonUtil::Create(true);
    borderJson = JsonUtil::Create(true);
    borderStyleProperty.styleLeft = BorderStyle::DASHED;
    borderStyleProperty.styleTop = BorderStyle::DOTTED;
    borderStyleProperty.styleRight = BorderStyle::NONE;
    borderStyleProperty.styleBottom = BorderStyle::DASHED;
    borderStyleProperty.ToJsonValue(json, borderJson, filter);

    ret = json->GetValue("borderStyle")->GetString("left", "");
    EXPECT_EQ(ret, "BorderStyle.Dashed");
    ret = json->GetValue("borderStyle")->GetString("top", "");
    EXPECT_EQ(ret, "BorderStyle.Dotted");
    ret = json->GetValue("borderStyle")->GetString("right", "");
    EXPECT_EQ(ret, "BorderStyle.None");
    ret = json->GetValue("borderStyle")->GetString("bottom", "");
    EXPECT_EQ(ret, "BorderStyle.Dashed");
}

/**
 * @tc.name: BorderPropertyTestNg002
 * @tc.desc: Test BorderWidthPropertyT<Dimension>::ToString function.
 * @tc.type: FUNC
 */
HWTEST_F(BorderPropertyTestNg, BorderPropertyTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set SetBorderWidth is 1px and call ToString
     * @tc.expected: the return value is "leftDimen: [1.00px]rightDimen: [1.00px]topDimen: [1.00px]bottomDimen:
     * [1.00px]".
     */
    BorderWidthPropertyT<Dimension> borderWidthProperty;
    auto borderWidth = Dimension(1.0f);
    borderWidthProperty.SetBorderWidth(borderWidth);
    auto ret = borderWidthProperty.ToString();
    EXPECT_EQ(ret, "[1.00px,1.00px,1.00px,1.00px]");
}

/**
 * @tc.name: BorderPropertyTestNg003
 * @tc.desc: Test BorderWidthPropertyT<Dimension>::ToJsonValue function.
 * @tc.type: FUNC
 */
HWTEST_F(BorderPropertyTestNg, BorderPropertyTestNg003, TestSize.Level1)
{
    BorderWidthPropertyT<Dimension> borderWidthProperty;
    borderWidthProperty.multiValued = true;

    /**
     * @tc.steps: step1. set multiValued is true, use the default borderWidth and call ToJsonValue
     * @tc.expected: the expected value is left: 0.00vp, top: 0.00vp, right: 0.00vp, bottom: 0.00vp.
     */
    auto json = JsonUtil::Create(true);
    auto borderJson = JsonUtil::Create(true);
    borderWidthProperty.ToJsonValue(json, borderJson, filter);

    auto ret = json->GetValue("borderWidth")->GetString("left", "");
    EXPECT_EQ(ret, "0.00vp");
    ret = json->GetValue("borderWidth")->GetString("top", "");
    EXPECT_EQ(ret, "0.00vp");
    ret = json->GetValue("borderWidth")->GetString("right", "");
    EXPECT_EQ(ret, "0.00vp");
    ret = json->GetValue("borderWidth")->GetString("bottom", "");
    EXPECT_EQ(ret, "0.00vp");

    /**
     * @tc.steps: step2. set multiValued is true, set the borderStyle 1px and call ToJsonValue
     * @tc.expected: the expected value is left: 1.00px, top: 1.00px, right: 1.00px, bottom: 1.00px.
     */
    json = JsonUtil::Create(true);
    borderJson = JsonUtil::Create(true);
    auto borderWidth = Dimension(1.0f);
    borderWidthProperty.SetBorderWidth(borderWidth);
    borderWidthProperty.ToJsonValue(json, borderJson, filter);

    ret = json->GetValue("borderWidth")->GetString("left", "");
    EXPECT_EQ(ret, "1.00px");
    ret = json->GetValue("borderWidth")->GetString("top", "");
    EXPECT_EQ(ret, "1.00px");
    ret = json->GetValue("borderWidth")->GetString("right", "");
    EXPECT_EQ(ret, "1.00px");
    ret = json->GetValue("borderWidth")->GetString("bottom", "");
    EXPECT_EQ(ret, "1.00px");
}

/**
 * @tc.name: BorderPropertyTestNg004
 * @tc.desc: Test BorderColorProperty::ToJsonValue function.
 * @tc.type: FUNC
 */
HWTEST_F(BorderPropertyTestNg, BorderPropertyTestNg004, TestSize.Level1)
{
    BorderColorProperty borderColorProperty;
    borderColorProperty.multiValued = true;

    /**
     * @tc.steps: step1. set multiValued is true, use the default borderColor and call ToJsonValue
     * @tc.expected: the expected value is left: #FF000000, top: #FF000000, right: #FF000000, bottom: #FF000000.
     */
    auto json = JsonUtil::Create(true);
    auto borderJson = JsonUtil::Create(true);
    borderColorProperty.ToJsonValue(json, borderJson, filter);

    auto borderColor = json->GetValue("borderColor");
    auto left = borderColor->GetString("left", "");
    EXPECT_EQ(left, "#FF000000");
    auto top = borderColor->GetString("top", "");
    EXPECT_EQ(top, "#FF000000");
    auto right = borderColor->GetString("right", "");
    EXPECT_EQ(right, "#FF000000");
    auto bottom = borderColor->GetString("bottom", "");
    EXPECT_EQ(bottom, "#FF000000");

    /**
     * @tc.steps: step2. set multiValued is true, set the borderColor blue and call ToJsonValue
     * @tc.expected: the expected value is left: #FF0000FF, top: #FF0000FF, right: #FF0000FF, bottom: #FF0000FF.
     */
    json = JsonUtil::Create(true);
    borderJson = JsonUtil::Create(true);
    borderColorProperty.SetColor(Color::BLUE);
    borderColorProperty.ToJsonValue(json, borderJson, filter);

    borderColor = json->GetValue("borderColor");
    left = borderColor->GetString("left", "");
    EXPECT_EQ(left, "#FF0000FF");
    top = borderColor->GetString("top", "");
    EXPECT_EQ(top, "#FF0000FF");
    right = borderColor->GetString("right", "");
    EXPECT_EQ(right, "#FF0000FF");
    bottom = borderColor->GetString("bottom", "");
    EXPECT_EQ(bottom, "#FF0000FF");
}

/**
 * @tc.name: BorderPropertyTestNg005
 * @tc.desc: Test BorderRadiusPropertyT<Dimension>::ToJsonValue function.
 * @tc.type: FUNC
 */
HWTEST_F(BorderPropertyTestNg, BorderPropertyTestNg005, TestSize.Level1)
{
    BorderRadiusPropertyT<Dimension> borderRadiusProperty;
    borderRadiusProperty.multiValued = false;

    /**
     * @tc.steps: step1. set multiValued is true, use the default borderRadius and call ToJsonValue
     * @tc.expected: the expected value is borderRadius: 0.00vp.
     */
    auto json = JsonUtil::Create(true);
    auto borderJson = JsonUtil::Create(true);
    borderRadiusProperty.ToJsonValue(json, borderJson, filter);

    auto borderRadius = json->GetString("borderRadius");
    EXPECT_EQ(borderRadius, "0.00vp");

    /**
     * @tc.steps: step2. set multiValued is true, set the borderRadius 1px and call ToJsonValue
     * @tc.expected: the expected value is borderRadius: 1.00px.
     */
    json = JsonUtil::Create(true);
    borderJson = JsonUtil::Create(true);
    auto borderRadiusVal = Dimension(1.0f);
    borderRadiusProperty.SetRadius(borderRadiusVal);
    borderRadiusProperty.ToJsonValue(json, borderJson, filter);

    borderRadius = json->GetString("borderRadius");
    EXPECT_EQ(borderRadius, "1.00px");
}

/**
 * @tc.name: BorderPropertyTestNg006
 * @tc.desc: Test BorderRadiusPropertyT<Dimension>::UpdateWithCheck function.
 * @tc.type: FUNC
 */
HWTEST_F(BorderPropertyTestNg, BorderPropertyTestNg006, TestSize.Level1)
{
    BorderRadiusPropertyT<Dimension> borderRadiusProperty;

    /**
     * @tc.steps: step1. set a borderRadiusProperty topLeft as 1.0px and call UpdateWithCheck
     * @tc.expected: the return value is true.
     */
    BorderRadiusPropertyT<Dimension> newBorderRadiusProperty;
    newBorderRadiusProperty.radiusTopLeft = Dimension(1.0);
    auto retFlag = borderRadiusProperty.UpdateWithCheck(newBorderRadiusProperty);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step2. set a borderRadiusProperty topRight as 1.0px and call UpdateWithCheck
     * @tc.expected: the return value is true.
     */
    borderRadiusProperty = BorderRadiusPropertyT<Dimension>();
    newBorderRadiusProperty = BorderRadiusPropertyT<Dimension>();
    newBorderRadiusProperty.radiusTopRight = Dimension(1.0);
    retFlag = borderRadiusProperty.UpdateWithCheck(newBorderRadiusProperty);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step3. set a borderRadiusProperty bottomRight as 1.0px and call UpdateWithCheck
     * @tc.expected: the return value is true.
     */
    borderRadiusProperty = BorderRadiusPropertyT<Dimension>();
    newBorderRadiusProperty = BorderRadiusPropertyT<Dimension>();
    newBorderRadiusProperty.radiusBottomRight = Dimension(1.0);
    retFlag = borderRadiusProperty.UpdateWithCheck(newBorderRadiusProperty);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step4. set a borderRadiusProperty bottomLeft as 1.0px and call UpdateWithCheck
     * @tc.expected: the return value is true.
     */
    borderRadiusProperty = BorderRadiusPropertyT<Dimension>();
    newBorderRadiusProperty = BorderRadiusPropertyT<Dimension>();
    newBorderRadiusProperty.radiusBottomLeft = Dimension(1.0);
    retFlag = borderRadiusProperty.UpdateWithCheck(newBorderRadiusProperty);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step5. do not set any borderRadius and call UpdateWithCheck
     * @tc.expected: the return value is false.
     */
    borderRadiusProperty = BorderRadiusPropertyT<Dimension>();
    newBorderRadiusProperty = BorderRadiusPropertyT<Dimension>();
    retFlag = borderRadiusProperty.UpdateWithCheck(newBorderRadiusProperty);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: BorderPropertyTestNg007
 * @tc.desc: Test BorderRadiusPropertyT<Dimension>::ToString function.
 * @tc.type: FUNC
 */
HWTEST_F(BorderPropertyTestNg, BorderPropertyTestNg007, TestSize.Level1)
{
    BorderColorProperty borderColorProperty;
    string strResult = borderColorProperty.ToString();
    const string strTemp = "leftColor: [NA]rightColor: [NA]topColor: [NA]bottomColor: [NA]";
    EXPECT_EQ(strTemp, strResult);

    Color cTemp = Color::FromARGB(25, 0, 0, 0);
    borderColorProperty.SetColor(cTemp);
    EXPECT_TRUE(borderColorProperty.leftColor.has_value());
    strResult = borderColorProperty.ToString();
    EXPECT_NE(strTemp, strResult);

    BorderWidthPropertyT<Dimension> borderWidthProperty;
    BorderWidthPropertyT<Dimension> borderWidthProperty2;
    Dimension dimenTemp(2.0, DimensionUnit::PX);
    borderWidthProperty.SetBorderWidth(dimenTemp);
    EXPECT_TRUE(borderWidthProperty.leftDimen.has_value());
    EXPECT_TRUE(borderWidthProperty.topDimen.has_value());
    EXPECT_TRUE(borderWidthProperty.rightDimen.has_value());
    EXPECT_TRUE(borderWidthProperty.bottomDimen.has_value());
    borderWidthProperty2.SetBorderWidth(dimenTemp);
    EXPECT_EQ(borderWidthProperty, borderWidthProperty2);
}
} // namespace OHOS::Ace::NG
