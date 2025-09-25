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
#include "accessor_test_base.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

class CustomSpanAccessorTest : public AccessorTestBase<GENERATED_ArkUICustomSpanAccessor,
                                    &GENERATED_ArkUIAccessors::getCustomSpanAccessor, CustomSpanPeer> {};

/**
 * @tc.name: CustomSpanAccessor.OnMeasureTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomSpanAccessorTest, OnMeasureTest, TestSize.Level1)
{
    ASSERT_TRUE(accessor_);
    ASSERT_TRUE(accessor_->getOnMeasure);
    ASSERT_TRUE(accessor_->setOnMeasure);

    static const Ark_Int32 expectedId {123};
    const float expectedValue {9.87f};

    // set valid callback
    auto testCallback = [](Ark_VMContext vmContext, const Ark_Int32 resourceId,
        const Ark_CustomSpanMeasureInfo measureInfo,
        const Callback_CustomSpanMetrics_Void continuation) {
        EXPECT_EQ(resourceId, expectedId);
        Ark_CustomSpanMetrics result {
            .width = measureInfo.fontSize,
            .height = Converter::ArkValue<Opt_Number>()
        };
        CallbackHelper(continuation).InvokeSync(result);
    };
    auto inputCallback =
        Converter::ArkValue<Callback_CustomSpanMeasureInfo_CustomSpanMetrics>(nullptr, testCallback, expectedId);
    accessor_->setOnMeasure(peer_, &inputCallback);

    // get callback
    auto checkCallback = accessor_->getOnMeasure(peer_);

    // invoke the obtained callback
    Ark_CustomSpanMeasureInfo inputData {
        .fontSize = Converter::ArkValue<Ark_Number>(expectedValue)
    };
    auto checkData = CallbackHelper(checkCallback).
        InvokeWithObtainResult<Ark_CustomSpanMetrics, Callback_CustomSpanMetrics_Void>(inputData);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(checkData.width), expectedValue);
    EXPECT_FALSE(Converter::OptConvert<float>(checkData.height).has_value());
}

/**
 * @tc.name: CustomSpanAccessor.OnDrawTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomSpanAccessorTest, OnDrawTest, TestSize.Level1)
{
    ASSERT_TRUE(accessor_);
    ASSERT_TRUE(accessor_->getOnDraw);
    ASSERT_TRUE(accessor_->setOnDraw);

    static const Ark_Int32 expectedId {123};
    const float expectedValue {9.87f};
    static Ark_CustomSpanDrawInfo checkData {};

    // set valid callback
    auto testCallback = [](Ark_VMContext vmContext, const Ark_Int32 resourceId,
        const Ark_DrawContext context, const Ark_CustomSpanDrawInfo drawInfo) {
        EXPECT_EQ(resourceId, expectedId);
        checkData = drawInfo;
    };
    auto inputCallback =
        Converter::ArkValue<Callback_DrawContext_CustomSpanDrawInfo_Void>(nullptr, testCallback, expectedId);
    accessor_->setOnDraw(peer_, &inputCallback);

    // get callback
    auto checkCallback = accessor_->getOnDraw(peer_);

    // invoke the obtained callback
    Ark_DrawContext inputCtx {nullptr};
    Ark_CustomSpanDrawInfo inputData {
        .x = Converter::ArkValue<Ark_Number>(expectedValue)
    };
    CallbackHelper(checkCallback).InvokeSync(inputCtx, inputData);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(checkData.x), expectedValue);
}
} // namespace OHOS::Ace::NG