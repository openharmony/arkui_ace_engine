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

#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/implementation/baseline_offset_style_peer.h"
#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace {
    const double EPSILON = 0.00001;
    const std::vector<std::tuple<std::string, Ark_LengthMetrics, Dimension>> testFixtureOffsetValues = {
        { "123.0_vp", Converter::ArkValue<Ark_LengthMetrics>(123.0_vp), 123.0_vp },
        { "0.0_vp", Converter::ArkValue<Ark_LengthMetrics>(0.0_vp), 0.0_vp },
        { "1.23_vp", Converter::ArkValue<Ark_LengthMetrics>(1.23_vp), 1.23_vp },
        { "123.0_fp", Converter::ArkValue<Ark_LengthMetrics>(123.0_fp), 123.0_fp },
        { "0.0_fp", Converter::ArkValue<Ark_LengthMetrics>(0.0_fp), 0.0_fp },
        { "1.23_fp", Converter::ArkValue<Ark_LengthMetrics>(1.23_fp), 1.23_fp },
        { "123.0_px", Converter::ArkValue<Ark_LengthMetrics>(123.0_px), 123.0_px },
        { "0.0_px", Converter::ArkValue<Ark_LengthMetrics>(0.0_px), 0.0_px },
        { "1.23_px", Converter::ArkValue<Ark_LengthMetrics>(1.23_px), 1.23_px },
        { "-2.3_vp", Converter::ArkValue<Ark_LengthMetrics>(-2.3_vp), -2.3_vp },
        { "-4.5_fp", Converter::ArkValue<Ark_LengthMetrics>(-4.5_fp), -4.5_fp },
        { "-5.6_px", Converter::ArkValue<Ark_LengthMetrics>(-5.6_px), -5.6_px },
        { "0.5_pct", Converter::ArkValue<Ark_LengthMetrics>(0.5_pct), 0.0_vp },
        { "0.0_pct", Converter::ArkValue<Ark_LengthMetrics>(0.0_pct), 0.0_vp },
        { "-0.8_pct", Converter::ArkValue<Ark_LengthMetrics>(-0.8_pct), 0.0_vp },
    };
} // namespace

using namespace testing;
using namespace testing::ext;

class BaselineOffsetStyleAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIBaselineOffsetStyleAccessor,
        &GENERATED_ArkUIAccessors::getBaselineOffsetStyleAccessor, BaselineOffsetStylePeer> {
public:
    void* CreatePeerInstance() override
    {
        return accessor_->construct(nullptr);
    }
    void DestroyPeer(BaselineOffsetStylePeer* peer)
    {
        finalyzer_(peer);
        peer = nullptr;
    }
};

/**
 * @tc.name: getBaselineOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaselineOffsetStyleAccessorTest, getBaselineOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getBaselineOffset, nullptr);
    for (auto& [input, value, expected] : testFixtureOffsetValues) {
        DestroyPeer(peer_);
        peer_ = accessor_->construct(&value);
        auto offset = accessor_->getBaselineOffset(peer_);
        EXPECT_NEAR(expected.ConvertToVp(), Converter::Convert<double>(offset), EPSILON) <<
            "Input value is: " << input << ", method: getType";
    }
}

} // namespace OHOS::Ace::NG