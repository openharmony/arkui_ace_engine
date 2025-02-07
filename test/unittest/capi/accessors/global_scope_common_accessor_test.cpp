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

class GlobalScopeCommonAccessorTest : public AccessorTestBase<GENERATED_ArkUIGlobalScope_commonAccessor,
    &GENERATED_ArkUIAccessors::getGlobalScope_commonAccessor, GlobalScope_commonPeer> {
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

    EXPECT_EQ(pxValue1, accessor_->vp2px(&arkVpValue1));
    EXPECT_EQ(pxValue2, accessor_->vp2px(&arkVpValue2));
    EXPECT_EQ(0, accessor_->vp2px(nullptr));
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

    EXPECT_EQ(vpValue1, accessor_->px2vp(&arkPxValue1));
    EXPECT_EQ(vpValue2, accessor_->px2vp(&arkPxValue2));
    EXPECT_EQ(0, accessor_->px2vp(nullptr));
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

    EXPECT_EQ(pxValue1, accessor_->fp2px(&arkFpValue1));
    EXPECT_EQ(pxValue2, accessor_->fp2px(&arkFpValue2));
    EXPECT_EQ(0, accessor_->fp2px(nullptr));
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

    EXPECT_EQ(fpValue1, accessor_->px2fp(&arkPxValue1));
    EXPECT_EQ(fpValue2, accessor_->px2fp(&arkPxValue2));
    EXPECT_EQ(0, accessor_->px2fp(nullptr));
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

    EXPECT_EQ(pxValue1, accessor_->lpx2px(&arkLpxValue1));
    EXPECT_EQ(pxValue2, accessor_->lpx2px(&arkLpxValue2));
    EXPECT_EQ(0, accessor_->lpx2px(nullptr));
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

    EXPECT_EQ(lpxValue1, accessor_->px2lpx(&arkPxValue1));
    EXPECT_EQ(lpxValue2, accessor_->px2lpx(&arkPxValue2));
    EXPECT_EQ(0, accessor_->px2lpx(nullptr));
}

/**
 * @tc.name: requestFocusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, requestFocusTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->requestFocus, nullptr);

    std::string inspectorKey = "inspectorKey";
    Ark_String arkInspectorKey = Converter::ArkValue<Ark_String>(inspectorKey);

    EXPECT_EQ(false, accessor_->requestFocus(&arkInspectorKey));
    EXPECT_EQ(false, accessor_->requestFocus(nullptr));
}

/**
 * @tc.name: setCursorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, setCursorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setCursor, nullptr);
    accessor_->setCursor(ARK_POINTER_STYLE_LOADING);
}

/**
 * @tc.name: restoreDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeCommonAccessorTest, restoreDefaultTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->restoreDefault, nullptr);
    accessor_->restoreDefault();
}

} // namespace OHOS::Ace::NG