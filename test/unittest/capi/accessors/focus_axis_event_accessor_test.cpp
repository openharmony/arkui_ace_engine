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

#include <memory>

#include "accessor_test_base.h"
#include "gmock/gmock.h"
#include "core/interfaces/native/implementation/focus_axis_event_accessor.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace GeneratedModifier::FocusAxisEventAccessor;

namespace Converter {
template<>
void AssignCast(std::optional<AxisModel>& dst, const Ark_AxisModel& src)
{
    switch (src) {
        case ARK_AXIS_MODEL_ABS_X: dst = AxisModel::ABS_X; break;
        case ARK_AXIS_MODEL_ABS_Y: dst = AxisModel::ABS_Y; break;
        case ARK_AXIS_MODEL_ABS_Z: dst = AxisModel::ABS_Z; break;
        case ARK_AXIS_MODEL_ABS_RZ: dst = AxisModel::ABS_RZ; break;
        case ARK_AXIS_MODEL_ABS_GAS: dst = AxisModel::ABS_GAS; break;
        case ARK_AXIS_MODEL_ABS_BRAKE: dst = AxisModel::ABS_BRAKE; break;
        case ARK_AXIS_MODEL_ABS_HAT0X: dst = AxisModel::ABS_HAT0X; break;
        case ARK_AXIS_MODEL_ABS_HAT0Y: dst = AxisModel::ABS_HAT0Y; break;
        default:
            LOGE("Unexpected enum value in Ark_AxisModel: %{public}d", src);
    }
}

template<>
std::map<AxisModel, float> Convert(const Map_AxisModel_Number& src)
{
    std::map<AxisModel, float> dst;
    CHECK_NULL_RETURN(src.keys && src.values && (src.size > 0), dst);
    auto size = Converter::Convert<int>(src.size);
    for (int i = 0; i < size; i++) {
        auto optKey = OptConvert<AxisModel>(src.keys[i]);
        auto value = Convert<float>(src.values[i]);
        if (!optKey) {
            dst.clear();
            return dst;
        }
        dst.emplace(*optKey, value);
    }
    return dst;
}
} // namespace Converter

class FocusAxisEventAccessorTest : public AccessorTestBase<GENERATED_ArkUIFocusAxisEventAccessor,
                                       &GENERATED_ArkUIAccessors::getFocusAxisEventAccessor, FocusAxisEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        ASSERT_NE(peer_, nullptr);
        auto event = FocusAxisEvent();
        initEvent(event);
        eventInfo_ = std::make_unique<FocusAxisEventInfo>(event);
        peer_->SetEventInfo(eventInfo_.get());
    }
    std::unique_ptr<FocusAxisEventInfo> eventInfo_;

private:
    void initEvent(FocusAxisEvent& event)
    {
        event.absXValue = 1.0f;
        event.absYValue = 2.0f;
        event.absZValue = 3.0f;
        event.absRzValue = 4.0f;
        event.absGasValue = 5.0f;
        event.absBrakeValue = 6.0f;
        event.absHat0XValue = 7.0f;
        event.absHat0YValue = 8.0f;
    }
};

/**
 * @tc.name: setDisplayXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusAxisEventAccessorTest, getAxisMapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getAxisMap, nullptr);
    auto arkAxisMap = accessor_->getAxisMap(peer_);
    auto optConvertedAxisMap = OptConvert<std::map<AxisModel, float>>(arkAxisMap);
    ASSERT_TRUE(optConvertedAxisMap);
    EXPECT_EQ(*optConvertedAxisMap, getAxisMapFromInfo(*eventInfo_));
}

/**
 * @tc.name: GetStopPropagationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusAxisEventAccessorTest, getStopPropagationTest, TestSize.Level1)
{
    FocusAxisEventInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    Callback_Void callback = accessor_->getStopPropagation(peer_);
    auto callbackHelper = CallbackHelper(callback);
    eventInfo->SetStopPropagation(false);
    EXPECT_FALSE(eventInfo->IsStopPropagation());
    callbackHelper.Invoke();
    EXPECT_TRUE(eventInfo->IsStopPropagation());
    CallbackKeeper::ReleaseReverseCallback<Callback_Void>(callback);
}

} // namespace OHOS::Ace::NG