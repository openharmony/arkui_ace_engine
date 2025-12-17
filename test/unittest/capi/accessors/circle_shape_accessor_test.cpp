/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "accessor_test_base.h"
#include "accessor_test_utils.h"
#include "node_api.h"
#include "frameworks/base/geometry/shape.h"
#include "core/interfaces/native/implementation/circle_shape_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
constexpr double TEST_WIDTH = 100.0;
constexpr double TEST_HEIGHT = 200.0;
constexpr double TEST_WIDTH_2 = 300.0;
constexpr double TEST_HEIGHT_2 = 400.0;
constexpr double TEST_WIDTH_3 = 500.0;
constexpr double TEST_HEIGHT_3 = 600.0;
constexpr double X = 10.0;
constexpr double Y = 20.0;
} // namespace

class CircleShapeAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUICircleShapeAccessor,
    &GENERATED_ArkUIAccessors::getCircleShapeAccessor, CircleShapePeer> {
public:
    void *CreatePeerInstance() override
    {
        auto width = Converter::ArkValue<Ark_Number>(TEST_WIDTH);
        auto height = Converter::ArkValue<Ark_Number>(TEST_HEIGHT);
        Opt_ShapeSize options;
        options.value.width = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(width);
        options.value.height = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(height);
        Ark_CircleShape ret = accessor_->construct(&options);
        return ret;
    }
};

/**
 * @tc.name: sizeInitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleShapeAccessorTest, sizeInitTest, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    EXPECT_EQ(peer_->shape->GetWidth().ConvertToPx(), TEST_WIDTH);
    EXPECT_EQ(peer_->shape->GetHeight().ConvertToPx(), TEST_HEIGHT);
}

/**
 * @tc.name: offsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleShapeAccessorTest, offsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->offset, nullptr);
    Ark_Position offset = {
        .x = Converter::ArkValue<Opt_Length>(X),
        .y = Converter::ArkValue<Opt_Length>(Y)
    };
    auto peer = accessor_->offset(peer_, &offset);
    auto retOffset = peer->shape->GetOffset();
    EXPECT_EQ(retOffset.GetX().ConvertToPx(), X);
    EXPECT_EQ(retOffset.GetY().ConvertToPx(), Y);
}

/**
 * @tc.name: fillTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleShapeAccessorTest, fillTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->fill, nullptr);
    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED);
    auto peer = accessor_->fill(peer_, &color);
    auto aceColor = peer->shape->GetColor();
    EXPECT_EQ(aceColor, Color::FromRGB(255, 0, 0));
}

/**
 * @tc.name: positionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleShapeAccessorTest, positionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->position, nullptr);
    Ark_Position position = {
        .x = Converter::ArkValue<Opt_Length>(X),
        .y = Converter::ArkValue<Opt_Length>(Y) };
    auto peer = accessor_->position(peer_, &position);
    DimensionOffset acePosition = peer->shape->GetPosition();
    EXPECT_EQ(acePosition.GetX().ConvertToPx(), X);
    EXPECT_EQ(acePosition.GetY().ConvertToPx(), Y);
}

/**
 * @tc.name: widthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleShapeAccessorTest, widthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->width, nullptr);
    Ark_Length length = Converter::ArkValue<Ark_Length>(TEST_WIDTH_2);
    auto peer = accessor_->width(peer_, &length);
    auto width = peer->shape->GetWidth();
    EXPECT_EQ(width.ConvertToPx(), TEST_WIDTH_2);
}

/**
 * @tc.name: heightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleShapeAccessorTest, heightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->height, nullptr);
    Ark_Length length = Converter::ArkValue<Ark_Length>(TEST_HEIGHT_2);
    auto peer = accessor_->height(peer_, &length);
    auto height = peer->shape->GetHeight();
    EXPECT_EQ(height.ConvertToPx(), TEST_HEIGHT_2);
}

/**
 * @tc.name: sizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CircleShapeAccessorTest, sizeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->size, nullptr);
    Ark_SizeOptions sizes = {
        .width = Converter::ArkValue<Opt_Length>(TEST_WIDTH_3),
        .height = Converter::ArkValue<Opt_Length>(TEST_HEIGHT_3)
    };
    auto peer = accessor_->size(peer_, &sizes);
    auto width = peer->shape->GetWidth();
    auto height = peer->shape->GetHeight();
    EXPECT_EQ(width.ConvertToPx(), TEST_WIDTH_3);
    EXPECT_EQ(height.ConvertToPx(), TEST_HEIGHT_3);
}
} // namespace OHOS::Ace::NG
