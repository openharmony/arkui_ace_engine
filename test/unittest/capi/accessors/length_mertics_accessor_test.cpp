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
#include "node_api.h"
#include "base/memory/ace_type.h"
#include "core/interfaces/native/implementation/length_metrics_peer.h"
#include "core/interfaces/native/implementation/unified_data_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;

class LengthMetricsAccessorTest
    : public AccessorTestBase<GENERATED_ArkUILengthMetricsAccessor,
        &GENERATED_ArkUIAccessors::getLengthMetricsAccessor, LengthMetricsPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        dragEvent_ = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        ASSERT_NE(dragEvent_, nullptr);

        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
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
        std::variant<int32_t, std::string> resource = num_id;
        auto resourceNum = Converter::ArkValue<Ark_Resource>(resource, &ctx);
        auto pointerNum = reinterpret_cast<LengthMetricsPeer*>(accessor_->resource(&resourceNum));
        ASSERT_TRUE(pointerNum);
        EXPECT_EQ(pointerNum->value.ToString(), expectPointer->ToString())  <<
             "Input value is: " << num_id << ", method: resource";
        accessor_->destroyPeer(pointerNum);

        resource = str_id;
        auto resourceStr = Converter::ArkValue<Ark_Resource>(resource, &ctx);
        auto pointerStr = reinterpret_cast<LengthMetricsPeer*>(accessor_->resource(&resourceStr));
        ASSERT_TRUE(pointerStr);
        EXPECT_EQ(pointerStr->value.ToString(), expectPointer->ToString())  <<
             "Input value is: " << str_id << ", method: resource";
        accessor_->destroyPeer(pointerStr);
    }
}
} // namespace OHOS::Ace::NG