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

class GlobalScopeCommonAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIGlobalScopeAccessor,
    &GENERATED_ArkUIAccessors::getGlobalScopeAccessor, void> {
    void SetUp(void) override
    {
        // Skip AccessorTestCtorBase's setup, since we don't have peer_
        AccessorTestBaseParent::SetUp();
    }

    void *CreatePeerInstance() override
    {
        return nullptr;
    }
};

/**
 * @tc.name: vp2pxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, vp2pxTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->vp2px, nullptr);

    double density = PipelineBase::GetCurrentDensity();

    auto vpValue1 = 5;
    auto vpValue2 = 10.5f;

    int32_t pxValue1 = vpValue1 * density;
    int32_t pxValue2 = vpValue2 * density;

    Ark_Number arkVpValue1 = Converter::ArkValue<Ark_Number>(vpValue1);
    Ark_Number arkVpValue2 = Converter::ArkValue<Ark_Number>(vpValue2);

    EXPECT_EQ(pxValue1, Converter::Convert<int32_t>(accessor_->vp2px(&arkVpValue1)));
    EXPECT_EQ(pxValue2, Converter::Convert<int32_t>(accessor_->vp2px(&arkVpValue2)));
    EXPECT_EQ(0, Converter::Convert<int32_t>(accessor_->vp2px(nullptr)));
}

/**
 * @tc.name: px2vpTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, px2vpTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->px2vp, nullptr);

    double density = PipelineBase::GetCurrentDensity();
    ASSERT_TRUE(density > 0);

    auto pxValue1 = 5;
    auto pxValue2 = 10.5f;

    int32_t vpValue1 = pxValue1 / density;
    int32_t vpValue2 = pxValue2 / density;

    Ark_Number arkPxValue1 = Converter::ArkValue<Ark_Number>(pxValue1);
    Ark_Number arkPxValue2 = Converter::ArkValue<Ark_Number>(pxValue2);

    EXPECT_EQ(vpValue1, Converter::Convert<int32_t>(accessor_->px2vp(&arkPxValue1)));
    EXPECT_EQ(vpValue2, Converter::Convert<int32_t>(accessor_->px2vp(&arkPxValue2)));
    EXPECT_EQ(0, Converter::Convert<int32_t>(accessor_->px2vp(nullptr)));
}

/**
 * @tc.name: fp2pxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, fp2pxTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->fp2px, nullptr);

    double density = PipelineBase::GetCurrentDensity();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }

    auto fpValue1 = 5;
    auto fpValue2 = 10.5f;

    int32_t pxValue1 = fpValue1 * density * fontScale;
    int32_t pxValue2 = fpValue2 * density * fontScale;

    Ark_Number arkFpValue1 = Converter::ArkValue<Ark_Number>(fpValue1);
    Ark_Number arkFpValue2 = Converter::ArkValue<Ark_Number>(fpValue2);

    EXPECT_EQ(pxValue1, Converter::Convert<int32_t>(accessor_->fp2px(&arkFpValue1)));
    EXPECT_EQ(pxValue2, Converter::Convert<int32_t>(accessor_->fp2px(&arkFpValue2)));
    EXPECT_EQ(0, Converter::Convert<int32_t>(accessor_->fp2px(nullptr)));
}

/**
 * @tc.name: px2fpTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, px2fpTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->px2fp, nullptr);

    double density = PipelineBase::GetCurrentDensity();
    ASSERT_TRUE(density > 0);

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double ratio = density * fontScale;
    ASSERT_TRUE(ratio > 0);

    auto pxValue1 = 5;
    auto pxValue2 = 10.5f;

    int32_t fpValue1 = pxValue1 / ratio;
    int32_t fpValue2 = pxValue2 / ratio;

    Ark_Number arkPxValue1 = Converter::ArkValue<Ark_Number>(pxValue1);
    Ark_Number arkPxValue2 = Converter::ArkValue<Ark_Number>(pxValue2);

    EXPECT_EQ(fpValue1, Converter::Convert<int32_t>(accessor_->px2fp(&arkPxValue1)));
    EXPECT_EQ(fpValue2, Converter::Convert<int32_t>(accessor_->px2fp(&arkPxValue2)));
    EXPECT_EQ(0, Converter::Convert<int32_t>(accessor_->px2fp(nullptr)));
}

/**
 * @tc.name: lpx2pxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, lpx2pxTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->lpx2px, nullptr);

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);

    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto width = pipelineContext->GetCurrentWindowRect().Width();
    WindowConfig windowConfig;
    if (!windowConfig.autoDesignWidth) {
        windowConfig.UpdateDesignWidthScale(width);
    }

    auto lpxValue1 = 5;
    auto lpxValue2 = 10.5f;

    int32_t pxValue1 = lpxValue1 * windowConfig.designWidthScale;
    int32_t pxValue2 = lpxValue2 * windowConfig.designWidthScale;

    Ark_Number arkLpxValue1 = Converter::ArkValue<Ark_Number>(lpxValue1);
    Ark_Number arkLpxValue2 = Converter::ArkValue<Ark_Number>(lpxValue2);

    EXPECT_EQ(pxValue1, Converter::Convert<int32_t>(accessor_->lpx2px(&arkLpxValue1)));
    EXPECT_EQ(pxValue2, Converter::Convert<int32_t>(accessor_->lpx2px(&arkLpxValue2)));
    EXPECT_EQ(0, Converter::Convert<int32_t>(accessor_->lpx2px(nullptr)));
}

/**
 * @tc.name: px2lpxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, px2lpxTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->px2lpx, nullptr);

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);

    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto width = pipelineContext->GetCurrentWindowRect().Width();
    WindowConfig windowConfig;
    if (!windowConfig.autoDesignWidth) {
        windowConfig.UpdateDesignWidthScale(width);
    }

    auto pxValue1 = 5;
    auto pxValue2 = 10.5f;

    int32_t lpxValue1 = pxValue1 / windowConfig.designWidthScale;
    int32_t lpxValue2 = pxValue2 / windowConfig.designWidthScale;

    Ark_Number arkPxValue1 = Converter::ArkValue<Ark_Number>(pxValue1);
    Ark_Number arkPxValue2 = Converter::ArkValue<Ark_Number>(pxValue2);

    EXPECT_EQ(lpxValue1, Converter::Convert<int32_t>(accessor_->px2lpx(&arkPxValue1)));
    EXPECT_EQ(lpxValue2, Converter::Convert<int32_t>(accessor_->px2lpx(&arkPxValue2)));
    EXPECT_EQ(0, Converter::Convert<int32_t>(accessor_->px2lpx(nullptr)));
}

/**
 * @tc.name: animateToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, animateToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->animateTo, nullptr);

    Ark_AnimateParam param;
    param.curve = Converter::ArkValue<Opt_Union_Curve_String_ICurve>(Ark_Empty());
    param.delay = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.duration = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(Ark_Empty());
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(Ark_Empty());
    param.iterations = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.onFinish = Converter::ArkValue<Opt_Callback_Void>(Ark_Empty());
    param.playMode = Converter::ArkValue<Opt_PlayMode>(Ark_Empty());
    param.tempo = Converter::ArkValue<Opt_Number>(Ark_Empty());

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
    param.curve = Converter::ArkValue<Opt_Union_Curve_String_ICurve>(Ark_Empty());
    param.delay = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.duration = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(Ark_Empty());
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(Ark_Empty());
    param.iterations = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.onFinish = Converter::ArkValue<Opt_Callback_Void>(Ark_Empty());
    param.playMode = Converter::ArkValue<Opt_PlayMode>(Ark_Empty());
    param.tempo = Converter::ArkValue<Opt_Number>(Ark_Empty());

    static uint32_t contextId = 123;
    auto event = [](const Ark_Int32 resourceId) {
        EXPECT_EQ(contextId, Converter::Convert<int32_t>(resourceId));
    };
    auto callback = Converter::ArkValue<Callback_Void>(event, contextId);

    accessor_->animateToImmediately(&param, &callback);
}

} // namespace OHOS::Ace::NG