/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_paint_property.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MenuWrapperPaintPropertyTestNg : public testing::Test {};
} // namespace
/**
 * @tc.name: MenuWrapperPaintPropertyTestNg001
 * @tc.desc: Verify GetEnableArrow.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintPropertyTestNg, MenuWrapperPaintPropertyTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object MenuWrapperPaintProperty.
     * @tc.expected: enableArrow has not value.
     */
    MenuWrapperPaintProperty property;
    EXPECT_FALSE(property.GetEnableArrow().has_value());
    /**
     * @tc.steps: step2. update enableArrow
     * @tc.expected: enableArrow value are as expected.
     */
    property.UpdateEnableArrow(true);
    ASSERT_TRUE(property.GetEnableArrow().has_value());
    EXPECT_TRUE(property.GetEnableArrow().value());
}

/**
 * @tc.name: MenuWrapperPaintPropertyTestNg002
 * @tc.desc: Verify GetArrowOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintPropertyTestNg, MenuWrapperPaintPropertyTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object MenuWrapperPaintProperty.
     * @tc.expected: arrowOffset has not value.
     */
    MenuWrapperPaintProperty property;
    EXPECT_FALSE(property.GetArrowOffset().has_value());
    /**
     * @tc.steps: step2. update arrowOffset
     * @tc.expected: arrowOffset value are as expected.
     */
    property.UpdateArrowOffset(Dimension(10.0f));
    ASSERT_TRUE(property.GetArrowOffset().has_value());
    EXPECT_EQ(property.GetArrowOffset().value(), Dimension(10.0f));
}

/**
 * @tc.name: MenuWrapperPaintPropertyTestNg003
 * @tc.desc: Verify GetArrowPosition.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintPropertyTestNg, MenuWrapperPaintPropertyTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object MenuWrapperPaintProperty.
     * @tc.expected: arrowPosition has not value.
     */
    MenuWrapperPaintProperty property;
    EXPECT_FALSE(property.GetArrowPosition().has_value());
    /**
     * @tc.steps: step2. update arrowPosition
     * @tc.expected: arrowPosition value are as expected.
     */
    property.UpdateArrowPosition(OffsetF(10.0f, 10.0f));
    ASSERT_TRUE(property.GetArrowPosition().has_value());
    EXPECT_EQ(property.GetArrowPosition().value(), OffsetF(10.0f, 10.0f));
}

/**
 * @tc.name: MenuWrapperPaintPropertyTestNg004
 * @tc.desc: Verify GetArrowPlacement.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintPropertyTestNg, MenuWrapperPaintPropertyTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object MenuWrapperPaintProperty.
     * @tc.expected: arrowPlacement has not value.
     */
    MenuWrapperPaintProperty property;
    EXPECT_FALSE(property.GetArrowPlacement().has_value());
    /**
     * @tc.steps: step2. update arrowPlacement
     * @tc.expected: arrowPlacement value are as expected.
     */
    property.UpdateArrowPlacement(Placement::TOP);
    ASSERT_TRUE(property.GetArrowPlacement().has_value());
    EXPECT_EQ(property.GetArrowPlacement().value(), Placement::TOP);
}

/**
 * @tc.name: MenuWrapperPaintPropertyTestNg005
 * @tc.desc: Verify Reset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintPropertyTestNg, MenuWrapperPaintPropertyTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object MenuWrapperPaintProperty, update property
     * @tc.expected: property value are as expected.
     */
    MenuWrapperPaintProperty property;
    property.UpdateEnableArrow(true);
    property.UpdateArrowOffset(Dimension(10.0f));
    property.UpdateArrowPosition(OffsetF(10.0f, 10.0f));
    property.UpdateArrowPlacement(Placement::TOP);
    EXPECT_TRUE(property.GetEnableArrow().has_value());
    EXPECT_TRUE(property.GetArrowOffset().has_value());
    EXPECT_TRUE(property.GetArrowPosition().has_value());
    EXPECT_TRUE(property.GetArrowPlacement().has_value());
    /**
     * @tc.steps: step2. reset property
     * @tc.expected: property value are as expected.
     */
    property.Reset();
    EXPECT_FALSE(property.GetEnableArrow().has_value());
    EXPECT_FALSE(property.GetArrowOffset().has_value());
    EXPECT_FALSE(property.GetArrowPosition().has_value());
    EXPECT_FALSE(property.GetArrowPlacement().has_value());
}

/**
 * @tc.name: MenuWrapperPaintPropertyTestNg006
 * @tc.desc: Verify Clone.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintPropertyTestNg, MenuWrapperPaintPropertyTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object MenuWrapperPaintProperty, update property
     */
    MenuWrapperPaintProperty property;
    property.UpdateEnableArrow(true);
    property.UpdateArrowOffset(Dimension(10.0f));
    property.UpdateArrowPosition(OffsetF(10.0f, 10.0f));
    property.UpdateArrowPlacement(Placement::TOP);
    /**
     * @tc.steps: step2. clone property
     * @tc.expected: property value are as expected.
     */
    auto cloneProperty = AceType::DynamicCast<MenuWrapperPaintProperty>(property.Clone());
    ASSERT_NE(cloneProperty, nullptr);
    EXPECT_EQ(property.GetEnableArrow().value(), cloneProperty->GetEnableArrow().value());
    EXPECT_EQ(property.GetArrowOffset().value(), cloneProperty->GetArrowOffset().value());
    EXPECT_EQ(property.GetArrowPosition().value(), cloneProperty->GetArrowPosition().value());
    EXPECT_EQ(property.GetArrowPlacement().value(), cloneProperty->GetArrowPlacement().value());
}

/**
 * @tc.name: MenuWrapperPaintPropertyTestNg007
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintPropertyTestNg, MenuWrapperPaintPropertyTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object MenuWrapperPaintProperty, update property
     */
    MenuWrapperPaintProperty property;
    property.UpdateEnableArrow(true);
    property.UpdateArrowOffset(Dimension(10.0f));
    property.UpdateArrowPosition(OffsetF(10.0f, 10.0f));
    property.UpdateArrowPlacement(Placement::TOP);
    /**
     * @tc.steps: step2. property to json
     * @tc.expected: property jsonValue are as expected.
     */
    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json);
    EXPECT_EQ(json->GetString("enableArrow"), V2::ConvertBoolToString(true).c_str());
    EXPECT_EQ(json->GetString("arrowOffset"), Dimension(10.0f).ToString().c_str());
    EXPECT_EQ(json->GetString("arrowPosition"), OffsetF(10.0f, 10.0f).ToString().c_str());
    EXPECT_EQ(json->GetString("arrowPlacement"), property.ConvertPlacementToString(Placement::TOP).c_str());
}

/**
 * @tc.name: MenuWrapperPaintPropertyTestNg008
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintPropertyTestNg, MenuWrapperPaintPropertyTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object MenuWrapperPaintProperty
     */
    MenuWrapperPaintProperty property;
    /**
     * @tc.steps: step2. property to json
     * @tc.expected: property jsonValue are as expected.
     */
    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json);
    EXPECT_EQ(json->GetString("enableArrow"), V2::ConvertBoolToString(false).c_str());
    EXPECT_EQ(json->GetString("arrowOffset"), Dimension(0.0, DimensionUnit::VP).ToString().c_str());
    EXPECT_EQ(json->GetString("arrowPosition"), OffsetF(0.0f, 0.0f).ToString().c_str());
    EXPECT_EQ(json->GetString("arrowPlacement"), property.ConvertPlacementToString(Placement::NONE).c_str());
}
} // namespace OHOS::Ace::NG