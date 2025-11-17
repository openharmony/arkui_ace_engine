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
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace  {
constexpr auto ATTRIBUTE_WIDTH_NAME = "width";
constexpr auto ATTRIBUTE_HEIGHT_NAME = "height";
constexpr auto ATTRIBUTE_RADIUS_WIDTH_NAME = "radiusWidth";
constexpr auto ATTRIBUTE_RADIUS_HEIGHT_NAME = "radiusHeight";
constexpr auto WIDTH_STR = "111.00vp";
constexpr auto HEIGHT_STR = "222.00vp";
constexpr auto RADIUS_X_STR = "10";
constexpr auto SIZE_STR = "100px";
constexpr int WIDTH = 111;
constexpr int HEIGHT = 222;
constexpr int RADIUS_X = 10;
constexpr int RADIUS_Y = 20;
constexpr int SIZE = 100;
constexpr int DEFAULT_VALUE = -1;
} // namespace

class RectModifierTest : public ModifierTestBase<GENERATED_ArkUIRectModifier,
    &GENERATED_ArkUINodeModifiers::getRectModifier, GENERATED_ARKUI_RECT> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            auto theme = AceType::MakeRefPtr<CheckboxTheme>();
            return theme;
        });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

Opt_Union_RectOptions_RoundedRectOptions BuildRectOptions(int width, int height, int radius)
{
    Ark_RectOptions radiusOpt;
    radiusOpt.width = Converter::ArkUnion<Opt_Length, Ark_Float64>(width);
    radiusOpt.height = Converter::ArkUnion<Opt_Length, Ark_Float64>(height);
    radiusOpt.radius = Converter::ArkUnion<Opt_Union_Length_Array_RadiusItem, Ark_Length>(radius);
    return Converter::ArkUnion<Opt_Union_RectOptions_RoundedRectOptions,
        Ark_RectOptions>(radiusOpt);
}

std::string GetStringAttribute(const RefPtr<PaintProperty>& property, const std::string& name)
{
    static const InspectorFilter inspector;
    auto jsonVal = JsonUtil::Create(true);
    property->ToJsonValue(jsonVal, inspector);
    auto val = jsonVal->GetValue(name);
    return val->ToString();
}

/**
 * @tc.name: RectModifierSetRectOptionsTest001
 * @tc.desc: setRectOptions test
 * @tc.type: FUNC
 */
HWTEST_F(RectModifierTest, DISABLED_RectModifierSetRectOptionsTest, TestSize.Level1)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    auto options = BuildRectOptions(WIDTH, HEIGHT, RADIUS_X);
    modifier_->setRectOptions(frameNode, &options);

    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, WIDTH_STR);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, HEIGHT_STR);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    strResult = GetStringAttribute(paintProperty, ATTRIBUTE_RADIUS_WIDTH_NAME);
    EXPECT_EQ(strResult, RADIUS_X_STR);
    strResult = GetStringAttribute(paintProperty, ATTRIBUTE_RADIUS_HEIGHT_NAME);
    EXPECT_EQ(strResult, RADIUS_X_STR);
}

/**
 * @tc.name: RectModifierSetRadiusWidthTest
 * @tc.desc: setRadiusWidth test
 * @tc.type: FUNC
 */
HWTEST_F(RectModifierTest, RectModifierSetRadiusWidthTest, TestSize.Level1)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    Ark_Union_Number_String options =
        Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(RADIUS_X);
    auto optOptions = Converter::ArkValue<Opt_Union_Number_String>(options);
    modifier_->setRadiusWidth(frameNode, &optOptions);

    auto checkVal1 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_WIDTH_NAME);
    EXPECT_EQ(checkVal1, RADIUS_X);
    auto checkVal2 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_HEIGHT_NAME);
    EXPECT_EQ(checkVal2, DEFAULT_VALUE);

    options = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>(SIZE_STR);
    optOptions = Converter::ArkValue<Opt_Union_Number_String>(options);
    modifier_->setRadiusWidth(frameNode, &optOptions);
    checkVal1 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_WIDTH_NAME);
    EXPECT_EQ(checkVal1, SIZE);
}

/**
 * @tc.name: RectModifierSetRadiusHeightTest
 * @tc.desc: setRadiusHeight test
 * @tc.type: FUNC
 */
HWTEST_F(RectModifierTest, RectModifierSetRadiusHeightTest, TestSize.Level1)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    Ark_Union_Number_String options =
        Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(RADIUS_Y);
    auto optOptions = Converter::ArkValue<Opt_Union_Number_String>(options);
    modifier_->setRadiusHeight(frameNode, &optOptions);

    auto checkVal1 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_WIDTH_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);
    auto checkVal2 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_HEIGHT_NAME);
    EXPECT_EQ(checkVal2, RADIUS_Y);

    options = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>(SIZE_STR);
    optOptions = Converter::ArkValue<Opt_Union_Number_String>(options);
    modifier_->setRadiusHeight(frameNode, &optOptions);
    checkVal1 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_HEIGHT_NAME);
    EXPECT_EQ(checkVal1, SIZE);
}

/**
 * @tc.name: RectModifierSetRadiusTest
 * @tc.desc: setRadius test
 * @tc.type: FUNC
 */
HWTEST_F(RectModifierTest, RectModifierSetRadiusTest, TestSize.Level1)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto checkVal1 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_WIDTH_NAME);
    EXPECT_EQ(checkVal1, 0);
    auto checkVal2 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_HEIGHT_NAME);
    EXPECT_EQ(checkVal2, 0);

    auto optRadius = Converter::ArkUnion<Opt_Union_Length_Array_RadiusItem, Ark_Length>(WIDTH_STR);
    modifier_->setRadius(frameNode, &optRadius);

    checkVal1 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_WIDTH_NAME);
    EXPECT_EQ(checkVal1, WIDTH);
    checkVal2 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_HEIGHT_NAME);
    EXPECT_EQ(checkVal2, WIDTH);

    optRadius = Converter::ArkUnion<Opt_Union_Length_Array_RadiusItem, Ark_Length>(SIZE_STR);
    modifier_->setRadius(frameNode, &optRadius);

    checkVal1 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_WIDTH_NAME);
    EXPECT_EQ(checkVal1, SIZE);
    checkVal2 = GetAttrValue<int>(node_, ATTRIBUTE_RADIUS_HEIGHT_NAME);
    EXPECT_EQ(checkVal2, SIZE);
}
} // namespace OHOS::Ace::NG
