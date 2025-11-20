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

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/interfaces/native/implementation/canvas_path_peer_impl.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto EXPECTED_NUMBER_OF_CALLS = 3;
const auto FIRST_X_VALUE = 100;
const auto FIRST_Y_VALUE = 75;
const auto DEFAULT_START_VALUE = 0.0;
const auto PI_VALUE = 3.14;
const auto TWO_PI_VALUE = 6.28;
const auto DEFAULT_BOOL_VALUE = false;
const auto SECOND_X_VALUE = 150;
const auto SECOND_Y_VALUE = 20;
const auto THIRD_X_VALUE = 100;
const auto THIRD_Y_VALUE = 70;
const auto RADIUS_VALUE = 50;
const auto CPX_VALUE = 20;
const auto CPY_VALUE = 100;
const auto CPX_VALUE_TWO = 200;
const auto CPY_VALUE_TWO = 100;
const double DEFAULT_DOUBLE_VALUE = 10.0;
const auto RADIUS_Y_VALUE = 100;
const auto DEFAULT_ROTATION_VALUE = 0.0;
const std::string DEFAULT_STRING_VALUE = "text";
const std::string INVALID_STRING_VALUE = "";

class MockCanvasPath : public CanvasPath2D {
public:
    MockCanvasPath() = default;
    ~MockCanvasPath() override = default;

    MOCK_METHOD(void, Rect, (double x, double y, double width, double height));
    MOCK_METHOD(void, Arc, (double x, double y, double radius, double startAngle, double endAngle, double ccw));
    MOCK_METHOD(void, ArcTo, (double x1, double y1, double x2, double y2, double radius));
    MOCK_METHOD(void, BezierCurveTo, (double cp1x, double cp1y, double cp2x, double cp2y, double x, double y));
    MOCK_METHOD(void, Ellipse,
        (double x, double y, double radiusX, double radiusY, double rotation, double startAngle, double endAngle,
            double ccw));
    MOCK_METHOD(void, LineTo, (double x, double y));
    MOCK_METHOD(void, MoveTo, (double x, double y));
    MOCK_METHOD(void, QuadraticCurveTo, (double cpx, double cpy, double x, double y));
};
} // namespace

class CanvasPathAccessorTest
    : public AccessorTestBase<GENERATED_ArkUICanvasPathAccessor,
        &GENERATED_ArkUIAccessors::getCanvasPathAccessor, CanvasPathPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockPattern_ = new MockCanvasPath();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasPathPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        RefPtr<CanvasPath2D> patternKeeper = mockPatternKeeper_;
        peerImpl->SetCanvasPath2d(patternKeeper);
        ASSERT_NE(mockPattern_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        mockPatternKeeper_ = nullptr;
        mockPattern_ = nullptr;
    }

    MockCanvasPath* mockPattern_ = nullptr;
    RefPtr<MockCanvasPath> mockPatternKeeper_ = nullptr;
};

/**
 * @tc.name: ArcTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, DISABLED_ArcTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->arc, nullptr);
    auto x = Converter::ArkValue<Ark_Float64>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Float64>(FIRST_Y_VALUE);
    auto radius = Converter::ArkValue<Ark_Float64>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto startAngle = Converter::ArkValue<Ark_Float64>(DEFAULT_START_VALUE);
    auto endAngle = Converter::ArkValue<Ark_Float64>(TWO_PI_VALUE);
    auto clockwise = Converter::ArkValue<Opt_Boolean>(DEFAULT_BOOL_VALUE);

    EXPECT_CALL(*mockPattern_, Arc(_, _, _, _, _, _)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->arc(peer_, x, y, radius, startAngle, endAngle, &clockwise);
    accessor_->arc(peer_, x, y, radius, startAngle, endAngle, &clockwise);
    accessor_->arc(nullptr, x, y, radius, startAngle, endAngle, &clockwise);
    accessor_->arc(peer_, x, y, radius, startAngle, endAngle, &clockwise);
}
/**
 * @tc.name: ArcToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, DISABLED_ArcToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->arcTo, nullptr);
    auto x1 = Converter::ArkValue<Ark_Float64>(SECOND_X_VALUE);
    auto y1 = Converter::ArkValue<Ark_Float64>(SECOND_Y_VALUE);
    auto x2 = Converter::ArkValue<Ark_Float64>(SECOND_X_VALUE);
    auto y2 = Converter::ArkValue<Ark_Float64>(THIRD_Y_VALUE);
    auto radius = Converter::ArkValue<Ark_Float64>(RADIUS_VALUE);

    EXPECT_CALL(*mockPattern_, ArcTo(_, _, _, _, _)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->arcTo(peer_, x1, y1, x2, y2, radius);
    accessor_->arcTo(peer_, x1, y1, x2, y2, radius);
    accessor_->arcTo(nullptr, x1, y1, x2, y2, radius);
    accessor_->arcTo(peer_, x1, y1, x2, y2, radius);
}
/**
 * @tc.name: BezierCurveToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, DISABLED_BezierCurveToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->bezierCurveTo, nullptr);
    auto cp1x = Converter::ArkValue<Ark_Float64>(CPX_VALUE);
    auto cp1y = Converter::ArkValue<Ark_Float64>(CPY_VALUE);
    auto cp2x = Converter::ArkValue<Ark_Float64>(CPX_VALUE_TWO);
    auto cp2y = Converter::ArkValue<Ark_Float64>(CPY_VALUE_TWO);
    auto x = Converter::ArkValue<Ark_Float64>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Float64>(FIRST_Y_VALUE);

    EXPECT_CALL(*mockPattern_, BezierCurveTo(_, _, _, _, _, _)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->bezierCurveTo(peer_, cp1x, cp1y, cp2x, cp2y, x, y);
    accessor_->bezierCurveTo(nullptr, cp1x, cp1y, cp2x, cp2y, x, y);
    accessor_->bezierCurveTo(peer_, cp1x, cp1y, cp2x, cp2y, x, y);
    accessor_->bezierCurveTo(peer_, cp1x, cp1y, cp2x, cp2y, x, y);
}
/**
 * @tc.name:EllipseTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, DISABLED_EllipseTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->ellipse, nullptr);
    auto x = Converter::ArkValue<Ark_Float64>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Float64>(FIRST_Y_VALUE);
    auto radiusX = Converter::ArkValue<Ark_Float64>(RADIUS_VALUE);
    auto radiusY = Converter::ArkValue<Ark_Float64>(RADIUS_Y_VALUE);
    auto rotation = Converter::ArkValue<Ark_Float64>(DEFAULT_ROTATION_VALUE);
    auto startAngle = Converter::ArkValue<Ark_Float64>(PI_VALUE);
    auto endAngle = Converter::ArkValue<Ark_Float64>(TWO_PI_VALUE);
    auto clockwise = Converter::ArkValue<Opt_Boolean>(DEFAULT_BOOL_VALUE);

    EXPECT_CALL(*mockPattern_, Ellipse(_, _, _, _, _, _, _, _)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->ellipse(peer_, x, y, radiusX, radiusY, rotation, startAngle, endAngle, &clockwise);
    accessor_->ellipse(peer_, x, y, radiusX, radiusY, rotation, startAngle, endAngle, &clockwise);
    accessor_->ellipse(nullptr, x, y, radiusX, radiusY, rotation, startAngle, endAngle, &clockwise);
    accessor_->ellipse(peer_, x, y, radiusX, radiusY, rotation, startAngle, endAngle, &clockwise);
}
/**
 * @tc.name: LineToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, DISABLED_LineToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->lineTo, nullptr);
    auto x1 = Converter::ArkValue<Ark_Float64>(FIRST_X_VALUE);
    auto y1 = Converter::ArkValue<Ark_Float64>(FIRST_Y_VALUE);
    auto x2 = Converter::ArkValue<Ark_Float64>(SECOND_X_VALUE);
    auto y2 = Converter::ArkValue<Ark_Float64>(SECOND_Y_VALUE);
    auto x3 = Converter::ArkValue<Ark_Float64>(THIRD_X_VALUE);
    auto y3 = Converter::ArkValue<Ark_Float64>(THIRD_Y_VALUE);

    EXPECT_CALL(*mockPattern_, LineTo(FIRST_X_VALUE, FIRST_Y_VALUE)).Times(1);
    accessor_->lineTo(peer_, x1, y1);
    EXPECT_CALL(*mockPattern_, LineTo(SECOND_X_VALUE, SECOND_Y_VALUE)).Times(1);
    accessor_->lineTo(peer_, x2, y2);
    EXPECT_CALL(*mockPattern_, LineTo(THIRD_X_VALUE, THIRD_Y_VALUE)).Times(1);
    accessor_->lineTo(peer_, x3, y3);
    EXPECT_CALL(*mockPattern_, LineTo(THIRD_X_VALUE, THIRD_Y_VALUE)).Times(0);
    accessor_->lineTo(nullptr, x3, y3);
}
/**
 * @tc.name: MoveToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, DISABLED_MoveToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->moveTo, nullptr);
    auto x1 = Converter::ArkValue<Ark_Float64>(FIRST_X_VALUE);
    auto y1 = Converter::ArkValue<Ark_Float64>(FIRST_Y_VALUE);
    auto x2 = Converter::ArkValue<Ark_Float64>(SECOND_X_VALUE);
    auto y2 = Converter::ArkValue<Ark_Float64>(SECOND_Y_VALUE);
    auto x3 = Converter::ArkValue<Ark_Float64>(THIRD_X_VALUE);
    auto y3 = Converter::ArkValue<Ark_Float64>(THIRD_Y_VALUE);

    EXPECT_CALL(*mockPattern_, MoveTo(FIRST_X_VALUE, FIRST_Y_VALUE)).Times(1);
    accessor_->moveTo(peer_, x1, y1);
    EXPECT_CALL(*mockPattern_, MoveTo(SECOND_X_VALUE, SECOND_Y_VALUE)).Times(1);
    accessor_->moveTo(peer_, x2, y2);
    EXPECT_CALL(*mockPattern_, MoveTo(THIRD_X_VALUE, THIRD_Y_VALUE)).Times(1);
    accessor_->moveTo(peer_, x3, y3);
    EXPECT_CALL(*mockPattern_, MoveTo(THIRD_X_VALUE, THIRD_Y_VALUE)).Times(0);
    accessor_->moveTo(nullptr, x3, y3);
}
/**
 * @tc.name: QuadraticCurveToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, DISABLED_QuadraticCurveToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->arcTo, nullptr);
    auto cpx = Converter::ArkValue<Ark_Float64>(CPX_VALUE);
    auto cpy = Converter::ArkValue<Ark_Float64>(CPY_VALUE);
    auto x = Converter::ArkValue<Ark_Float64>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Float64>(FIRST_Y_VALUE);

    EXPECT_CALL(*mockPattern_, QuadraticCurveTo(_, _, _, _)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->quadraticCurveTo(peer_, cpx, cpy, x, y);
    accessor_->quadraticCurveTo(peer_, cpx, cpy, x, y);
    accessor_->quadraticCurveTo(nullptr, cpx, cpy, x, y);
    accessor_->quadraticCurveTo(peer_, cpx, cpy, x, y);
}
/**
 * @tc.name: AddRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, DISABLED_AddRectTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->rect, nullptr);
    auto x = Converter::ArkValue<Ark_Float64>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Float64>(FIRST_Y_VALUE);
    auto arkD = Converter::ArkValue<Ark_Float64>(static_cast<float>(DEFAULT_DOUBLE_VALUE));

    EXPECT_CALL(*mockPattern_, Rect(FIRST_X_VALUE, FIRST_Y_VALUE, DEFAULT_DOUBLE_VALUE, DEFAULT_DOUBLE_VALUE))
        .Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->rect(peer_, x, y, arkD, arkD);
    accessor_->rect(peer_, x, y, arkD, arkD);
    accessor_->rect(nullptr, x, y, arkD, arkD);
    accessor_->rect(peer_, x, y, arkD, arkD);
}
} // namespace OHOS::Ace::NG