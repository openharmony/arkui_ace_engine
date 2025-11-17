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

#include <tuple>
#include <variant>
#include <vector>

#include "accessor_test_base.h"
#include "accessor_test_fixtures.h"
#include "base/memory/ace_type.h"
#include "core/interfaces/native/implementation/length_metrics_peer.h"
#include "core/interfaces/native/implementation/unified_data_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;

namespace {
const double EPSILON = 0.001;

const std::vector<std::pair<DimensionUnit, Ark_LengthUnit>> unitTestPlan = {
    { DimensionUnit::PX, ARK_LENGTH_UNIT_PX },
    { DimensionUnit::VP, ARK_LENGTH_UNIT_VP },
    { DimensionUnit::FP, ARK_LENGTH_UNIT_FP },
    { DimensionUnit::PERCENT, ARK_LENGTH_UNIT_PERCENT },
    { DimensionUnit::LPX, ARK_LENGTH_UNIT_LPX },
};
}

class LengthMetricsAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUILengthMetricsAccessor,
        &GENERATED_ArkUIAccessors::getLengthMetricsAccessor, LengthMetricsPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        dragEvent_ = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        ASSERT_NE(dragEvent_, nullptr);

        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
    void *CreatePeerInstance() override
    {
        auto val = Converter::ArkValue<Ark_Number>(0);
        return accessor_->construct(&val, ARK_LENGTH_UNIT_VP);
    }
    RefPtr<OHOS::Ace::DragEvent> dragEvent_ = nullptr;
};

/**
 * @tc.name: PxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, PxTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixturesDimensionWithPercentAndNegativeValues) {
        auto pointer = reinterpret_cast<LengthMetricsPeer*>(accessor_->px(&value));
        ASSERT_TRUE(pointer);
        EXPECT_EQ(pointer->value.ToString(), expected)  <<
             "Input value is: " << input << ", method: Px";
        accessor_->destroyPeer(pointer);
    }
}

/**
 * @tc.name: VpTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, VpTest, TestSize.Level1)
{
    for (float number : testFixtureFloatValues) {
        Ark_Number value = Converter::ArkValue<Ark_Number>(number);
        auto pointer = reinterpret_cast<LengthMetricsPeer*>(accessor_->vp(&value));
        ASSERT_TRUE(pointer);
        EXPECT_NEAR(pointer->value.Value(), number, EPSILON);
        EXPECT_EQ(pointer->value.Unit(), DimensionUnit::VP);
        accessor_->destroyPeer(pointer);
    }
}

/**
 * @tc.name: FpTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, FpTest, TestSize.Level1)
{
    for (float number : testFixtureFloatValues) {
        Ark_Number value = Converter::ArkValue<Ark_Number>(number);
        auto pointer = reinterpret_cast<LengthMetricsPeer*>(accessor_->fp(&value));
        ASSERT_TRUE(pointer);
        EXPECT_NEAR(pointer->value.Value(), number, EPSILON);
        EXPECT_EQ(pointer->value.Unit(), DimensionUnit::FP);
        accessor_->destroyPeer(pointer);
    }
}

/**
 * @tc.name: PercentTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, PercentTest, TestSize.Level1)
{
    for (float number : testFixtureFloatValues) {
        Ark_Number value = Converter::ArkValue<Ark_Number>(number);
        auto pointer = reinterpret_cast<LengthMetricsPeer*>(accessor_->percent(&value));
        ASSERT_TRUE(pointer);
        EXPECT_NEAR(pointer->value.Value(), number, EPSILON);
        EXPECT_EQ(pointer->value.Unit(), DimensionUnit::PERCENT);
        accessor_->destroyPeer(pointer);
    }
}

/**
 * @tc.name: LpxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, LpxTest, TestSize.Level1)
{
    for (float number : testFixtureFloatValues) {
        Ark_Number value = Converter::ArkValue<Ark_Number>(number);
        auto pointer = reinterpret_cast<LengthMetricsPeer*>(accessor_->lpx(&value));
        ASSERT_TRUE(pointer);
        EXPECT_NEAR(pointer->value.Value(), number, EPSILON);
        EXPECT_EQ(pointer->value.Unit(), DimensionUnit::LPX);
        accessor_->destroyPeer(pointer);
    }
}

/**
 * @tc.name: ResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, ResourceTest, TestSize.Level1)
{
    for (auto& [num_id, str_id, expected] : resourceInitTable) {
        Converter::ConvContext ctx;
        auto expectPointer = std::get_if<Dimension>(&expected);
        ASSERT_TRUE(expectPointer);
        auto resourceNum = Converter::ArkCreate<Ark_Resource>(num_id, ResourceType::FLOAT);
        auto pointerNum = accessor_->resource(&resourceNum);
        ASSERT_TRUE(pointerNum);
        EXPECT_EQ(pointerNum->value.ToString(), expectPointer->ToString())  <<
             "Input value is: " << num_id << ", method: resource";
        accessor_->destroyPeer(pointerNum);

        auto resourceStr = Converter::ArkCreate<Ark_Resource>(str_id, ResourceType::FLOAT, &ctx);
        auto pointerStr = accessor_->resource(&resourceStr);
        ASSERT_TRUE(pointerStr);
        EXPECT_EQ(pointerStr->value.ToString(), expectPointer->ToString())  <<
             "Input value is: " << str_id << ", method: resource";
        accessor_->destroyPeer(pointerStr);
    }
}

/**
 * @tc.name: GetUnitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, GetUnitTest, TestSize.Level1)
{
    for (auto& [value, expected] : unitTestPlan) {
        peer_->value.SetUnit(value);
        Ark_LengthUnit result = accessor_->getUnit(peer_);
        ASSERT_EQ(result, expected);
    }
}

/**
 * @tc.name: SetUnitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, SetUnitTest, TestSize.Level1)
{
    for (auto& [expected, value] : unitTestPlan) {
        accessor_->setUnit(peer_, value);
        DimensionUnit result = peer_->value.Unit();
        ASSERT_EQ(result, expected);
    }
}

/**
 * @tc.name: GetValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, GetValueTest, TestSize.Level1)
{
    for (auto value : testFixtureFloatValues) {
        peer_->value.SetValue(value);
        Ark_Number result = accessor_->getValue(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(result), value);
    }
}

/**
 * @tc.name: SetValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LengthMetricsAccessorTest, SetValueTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberFloatAnythingValidValues) {
        accessor_->setValue(peer_, &value);
        double result = peer_->value.Value();
        EXPECT_NEAR(result, expected, EPSILON);
    }
}
} // namespace OHOS::Ace::NG