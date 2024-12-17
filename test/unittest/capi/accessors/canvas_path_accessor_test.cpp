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

#include "test/mock/core/pattern/mock_canvas_pattern.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/interfaces/native/implementation/canvas_path_accessor_peer_impl.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
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

class MockCanvasPattern : public CanvasPattern {
public:
    MockCanvasPattern() = default;
    ~MockCanvasPattern() override = default;
    MOCK_METHOD(void, AddRect, (const Rect&));
    MOCK_METHOD(void, Arc, (const ArcParam&));
    MOCK_METHOD(void, ArcTo, (const ArcToParam&));
    MOCK_METHOD(void, BezierCurveTo, (const BezierCurveParam&));
    MOCK_METHOD(void, Ellipse, (const EllipseParam&));
    MOCK_METHOD(void, LineTo, (double x, double y));
    MOCK_METHOD(void, MoveTo, (double x, double y));
    MOCK_METHOD(void, QuadraticCurveTo, (const QuadraticCurveParam&));
};
} // namespace

class CanvasPathAccessorTest
    : public AccessorTestBase<GENERATED_ArkUICanvasPathAccessor,
        &GENERATED_ArkUIAccessors::getCanvasPathAccessor, CanvasPathPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockPattern_ = new MockCanvasPattern();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<CanvasPathPeer*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetHandler(mockPatternKeeper_);
        ASSERT_NE(mockPattern_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        mockPatternKeeper_ = nullptr;
        mockPattern_ = nullptr;
    }

    MockCanvasPattern* mockPattern_ = nullptr;
    RefPtr<MockCanvasPattern> mockPatternKeeper_ = nullptr;
};



/**
 * @tc.name: ArcTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, ArcTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->arc, nullptr);
    auto x = Converter::ArkValue<Ark_Number>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Number>(FIRST_Y_VALUE);
    auto radius = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto startAngle = Converter::ArkValue<Ark_Number>(DEFAULT_START_VALUE);
    auto endAngle = Converter::ArkValue<Ark_Number>(TWO_PI_VALUE);
    auto clockwise = Converter::ArkValue<Opt_Boolean>(std::optional<bool>(DEFAULT_BOOL_VALUE));

    holder->SetUp();
    EXPECT_CALL(*mockPattern_, Arc(_)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->arc(peer_, &x, &y, &radius, &startAngle, &endAngle, &clockwise);
    accessor_->arc(peer_, &x, &y, &radius, &startAngle, &endAngle, &clockwise);
    accessor_->arc(nullptr, &x, &y, &radius, &startAngle, &endAngle, &clockwise);
    accessor_->arc(peer_, &x, &y, &radius, &startAngle, &endAngle, &clockwise);
    holder->TearDown();
}
/**
 * @tc.name: ArcToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, ArcToTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->arcTo, nullptr);
    auto x1 = Converter::ArkValue<Ark_Number>(SECOND_X_VALUE);
    auto y1 = Converter::ArkValue<Ark_Number>(SECOND_Y_VALUE);
    auto x2 = Converter::ArkValue<Ark_Number>(SECOND_X_VALUE);
    auto y2 = Converter::ArkValue<Ark_Number>(THIRD_Y_VALUE);
    auto radius = Converter::ArkValue<Ark_Number>(RADIUS_VALUE);
    
    holder->SetUp();
    EXPECT_CALL(*mockPattern_, ArcTo(_)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->arcTo(peer_, &x1, &y1, &x2, &y2,  &radius);
    accessor_->arcTo(peer_, &x1, &y1, &x2, &y2,  &radius);
    accessor_->arcTo(nullptr, &x1, &y1, &x2, &y2,  &radius);
    accessor_->arcTo(peer_, &x1, &y1, &x2, &y2,  &radius);
    holder->TearDown();
}
/**
 * @tc.name: BezierCurveToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, BezierCurveToTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->bezierCurveTo, nullptr);
    auto cp1x = Converter::ArkValue<Ark_Number>(CPX_VALUE);
    auto cp1y = Converter::ArkValue<Ark_Number>(CPY_VALUE);
    auto cp2x = Converter::ArkValue<Ark_Number>(CPX_VALUE_TWO);
    auto cp2y = Converter::ArkValue<Ark_Number>(CPY_VALUE_TWO);
    auto x = Converter::ArkValue<Ark_Number>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Number>(FIRST_Y_VALUE);
    
    holder->SetUp();
    EXPECT_CALL(*mockPattern_, BezierCurveTo(_)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->bezierCurveTo(peer_, &cp1x, &cp1y, &cp2x, &cp2y, &x, &y);
    accessor_->bezierCurveTo(nullptr, &cp1x, &cp1y, &cp2x, &cp2y, &x, &y);
    accessor_->bezierCurveTo(peer_, &cp1x, &cp1y, &cp2x, &cp2y, &x, &y);
    accessor_->bezierCurveTo(peer_, &cp1x, &cp1y, &cp2x, &cp2y, &x, &y);
    holder->TearDown();
}
/**
 * @tc.name:EllipseTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, EllipseTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->ellipse, nullptr);
    auto x = Converter::ArkValue<Ark_Number>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Number>(FIRST_Y_VALUE);
    auto radiusX = Converter::ArkValue<Ark_Number>(RADIUS_VALUE);
    auto radiusY = Converter::ArkValue<Ark_Number>(RADIUS_Y_VALUE);
    auto rotation = Converter::ArkValue<Ark_Number>(DEFAULT_ROTATION_VALUE);
    auto startAngle = Converter::ArkValue<Ark_Number>(PI_VALUE);
    auto endAngle = Converter::ArkValue<Ark_Number>(TWO_PI_VALUE);
    auto clockwise = Converter::ArkValue<Opt_Boolean>(std::optional<bool>(DEFAULT_BOOL_VALUE));

    holder->SetUp();
    EXPECT_CALL(*mockPattern_, Ellipse(_)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->ellipse(peer_, &x, &y, &radiusX, &radiusY, &rotation, &startAngle, &endAngle, &clockwise);
    accessor_->ellipse(peer_, &x, &y, &radiusX, &radiusY, &rotation, &startAngle, &endAngle, &clockwise);
    accessor_->ellipse(nullptr, &x, &y, &radiusX, &radiusY, &rotation, &startAngle, &endAngle, &clockwise);
    accessor_->ellipse(peer_, &x, &y, &radiusX, &radiusY, &rotation, &startAngle, &endAngle, &clockwise);
    holder->TearDown();
}
/**
 * @tc.name: LineToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, LineToTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->lineTo, nullptr);
    auto x1 = Converter::ArkValue<Ark_Number>(FIRST_X_VALUE);
    auto y1 = Converter::ArkValue<Ark_Number>(FIRST_Y_VALUE);
    auto x2 = Converter::ArkValue<Ark_Number>(SECOND_X_VALUE);
    auto y2 = Converter::ArkValue<Ark_Number>(SECOND_Y_VALUE);
    auto x3 = Converter::ArkValue<Ark_Number>(THIRD_X_VALUE);
    auto y3 = Converter::ArkValue<Ark_Number>(THIRD_Y_VALUE);  
    holder->SetUp();

    EXPECT_CALL(*mockPattern_, LineTo(FIRST_X_VALUE, FIRST_Y_VALUE)).Times(1);
    accessor_->lineTo(peer_, &x1, &y1);
    EXPECT_CALL(*mockPattern_, LineTo(SECOND_X_VALUE, SECOND_Y_VALUE)).Times(1);
    accessor_->lineTo(peer_, &x2, &y2);
    EXPECT_CALL(*mockPattern_, LineTo(THIRD_X_VALUE, THIRD_Y_VALUE)).Times(1);
    accessor_->lineTo(peer_, &x3, &y3);
    EXPECT_CALL(*mockPattern_, LineTo(THIRD_X_VALUE, THIRD_Y_VALUE)).Times(0);
    accessor_->lineTo(nullptr, &x3, &y3);
    holder->TearDown();
}
/**
 * @tc.name: MoveToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, MoveToTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->moveTo, nullptr);
    auto x1 = Converter::ArkValue<Ark_Number>(FIRST_X_VALUE);
    auto y1 = Converter::ArkValue<Ark_Number>(FIRST_Y_VALUE);
    auto x2 = Converter::ArkValue<Ark_Number>(SECOND_X_VALUE);
    auto y2 = Converter::ArkValue<Ark_Number>(SECOND_Y_VALUE);
    auto x3 = Converter::ArkValue<Ark_Number>(THIRD_X_VALUE);
    auto y3 = Converter::ArkValue<Ark_Number>(THIRD_Y_VALUE);
    holder->SetUp();

    EXPECT_CALL(*mockPattern_, MoveTo(FIRST_X_VALUE, FIRST_Y_VALUE)).Times(1);
    accessor_->moveTo(peer_, &x1, &y1);
    EXPECT_CALL(*mockPattern_, MoveTo(SECOND_X_VALUE, SECOND_Y_VALUE)).Times(1);
    accessor_->moveTo(peer_, &x2, &y2);
    EXPECT_CALL(*mockPattern_, MoveTo(THIRD_X_VALUE, THIRD_Y_VALUE)).Times(1);
    accessor_->moveTo(peer_, &x3, &y3);
    EXPECT_CALL(*mockPattern_, MoveTo(THIRD_X_VALUE, THIRD_Y_VALUE)).Times(0);
    accessor_->moveTo(nullptr, &x3, &y3);
    holder->TearDown();
}
/**
 * @tc.name: QuadraticCurveToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, QuadraticCurveToTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->arcTo, nullptr);
    auto cpx = Converter::ArkValue<Ark_Number>(CPX_VALUE);
    auto cpy = Converter::ArkValue<Ark_Number>(CPY_VALUE);
    auto x = Converter::ArkValue<Ark_Number>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Number>(FIRST_Y_VALUE);
    
    holder->SetUp();
    EXPECT_CALL(*mockPattern_, QuadraticCurveTo(_)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->quadraticCurveTo(peer_, &cpx, &cpy, &x, &y);
    accessor_->quadraticCurveTo(peer_, &cpx, &cpy, &x, &y);
    accessor_->quadraticCurveTo(nullptr, &cpx, &cpy, &x, &y);
    accessor_->quadraticCurveTo(peer_, &cpx, &cpy, &x, &y);
    holder->TearDown();
}
/**
 * @tc.name: AddRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPathAccessorTest, AddRectTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->rect, nullptr);
    auto x = Converter::ArkValue<Ark_Number>(FIRST_X_VALUE);
    auto y = Converter::ArkValue<Ark_Number>(FIRST_Y_VALUE);
    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    Rect r = Rect(static_cast<double>(Converter::Convert<float>(x)),
                  static_cast<double>(Converter::Convert<float>(y)),
                  static_cast<double>(Converter::Convert<float>(arkD)),
                  static_cast<double>(Converter::Convert<float>(arkD)));
    holder->SetUp();
    EXPECT_CALL(*mockPattern_, AddRect(r)).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->rect(peer_, &x, &y, &arkD, &arkD);
    accessor_->rect(peer_, &x, &y, &arkD, &arkD);
    accessor_->rect(nullptr, &x, &y, &arkD, &arkD);
    accessor_->rect(peer_, &x, &y, &arkD, &arkD);
    holder->TearDown();
}
} // namespace OHOS::Ace::NG