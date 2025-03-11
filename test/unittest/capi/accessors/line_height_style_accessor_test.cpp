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

#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/interfaces/native/implementation/length_metrics_peer.h"
#include "core/interfaces/native/implementation/line_height_style_peer.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

typedef std::pair<Ark_LengthMetrics, std::string> LengthMetricsOneTestStep;
static std::vector<LengthMetricsOneTestStep> testLengthMetricsValues = {
    { Converter::ArkValue<Ark_LengthMetrics>(123.0_vp), "123.000000" },
    { Converter::ArkValue<Ark_LengthMetrics>(0.0_vp), "0.000000" },
    { Converter::ArkValue<Ark_LengthMetrics>(1.23_vp), "1.230000" },
    { Converter::ArkValue<Ark_LengthMetrics>(123.0_fp), "123.000000" },
    { Converter::ArkValue<Ark_LengthMetrics>(0.0_fp), "0.000000" },
    { Converter::ArkValue<Ark_LengthMetrics>(1.23_fp), "1.230000" },
    { Converter::ArkValue<Ark_LengthMetrics>(123.0_px), "123.000000" },
    { Converter::ArkValue<Ark_LengthMetrics>(0.0_px), "0.000000" },
    { Converter::ArkValue<Ark_LengthMetrics>(1.23_px), "1.230000" },
};

class LineHeightStyleAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUILineHeightStyleAccessor,
        &GENERATED_ArkUIAccessors::getLineHeightStyleAccessor, LineHeightStylePeer> {
public:
    void* CreatePeerInstance() override
    {
        Ark_LengthMetrics metrics = Converter::ArkValue<Ark_LengthMetrics>(0.0_vp);
        return accessor_->ctor(metrics);
    }
};

/**
 * @tc.name: getLineHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LineHeightStyleAccessorTest, getLineHeightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLineHeight, nullptr);

    for (const auto &[arkValue, expected]: testLengthMetricsValues) {
        accessor_->destroyPeer(peer_);
        Ark_LengthMetrics metrics = arkValue;
        peer_ = this->accessor_->ctor(metrics);
        ASSERT_TRUE(peer_);
        Ark_Number retHeight = accessor_->getLineHeight(peer_);
        float number = Converter::Convert<float>(retHeight);
        EXPECT_EQ(std::to_string(number), expected);
    }
}
} // namespace OHOS::Ace::NG