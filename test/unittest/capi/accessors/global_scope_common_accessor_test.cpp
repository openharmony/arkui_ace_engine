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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class GlobalScopeCommonAccessorTest : public StaticAccessorTest<GENERATED_ArkUIGlobalScopeAccessor,
    &GENERATED_ArkUIAccessors::getGlobalScopeAccessor> {
};

/**
 * @tc.name: animateToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, animateToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->animateTo, nullptr);

    Ark_AnimateParam param;
    param.curve = Converter::ArkValue<Opt_Union_curves_Curve_String_curves_ICurve>(Ark_Empty());
    param.delay = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.duration = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(Ark_Empty());
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(Ark_Empty());
    param.iterations = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.onFinish = Converter::ArkValue<Opt_Callback_Void>(Ark_Empty());
    param.playMode = Converter::ArkValue<Opt_PlayMode>(Ark_Empty());
    param.tempo = Converter::ArkValue<Opt_Float64>(Ark_Empty());

    static uint32_t contextId = 123;
    auto event = [](const Ark_Int32 resourceId) {
        EXPECT_EQ(contextId, Converter::Convert<int32_t>(resourceId));
    };
    auto callback = Converter::ArkValue<Callback_Void>(event, contextId);

    accessor_->animateTo(&param, &callback);
}

/**
 * @tc.name: animateToImmediatelyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, animateToImmediatelyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->animateToImmediately, nullptr);

    Ark_AnimateParam param;
    param.curve = Converter::ArkValue<Opt_Union_curves_Curve_String_curves_ICurve>(Ark_Empty());
    param.delay = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.duration = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(Ark_Empty());
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(Ark_Empty());
    param.iterations = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.onFinish = Converter::ArkValue<Opt_Callback_Void>(Ark_Empty());
    param.playMode = Converter::ArkValue<Opt_PlayMode>(Ark_Empty());
    param.tempo = Converter::ArkValue<Opt_Float64>(Ark_Empty());

    static uint32_t contextId = 123;
    auto event = [](const Ark_Int32 resourceId) {
        EXPECT_EQ(contextId, Converter::Convert<int32_t>(resourceId));
    };
    auto callback = Converter::ArkValue<Callback_Void>(event, contextId);

    accessor_->animateToImmediately(&param, &callback);
}

} // namespace OHOS::Ace::NG
