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
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/implementation/custom_span_peer.h"
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace Converter {
// Defined in custom_span_accessor.cpp
template<> CustomSpanMetrics Convert(const Ark_CustomSpanMetrics& src);
} // namespace Converter

namespace {
class MockFrameNode : public FrameNode {
public:
    MockFrameNode() : FrameNode("TEST", 0, AceType::MakeRefPtr<Pattern>()) {}

    MOCK_METHOD(void, MarkDirtyNode, (PropertyChangeFlag));
};
}

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
    ASSERT_TRUE(accessor_->getOnMeasure_callback);
    ASSERT_TRUE(accessor_->setOnMeasure_callback);

    static const Ark_Int32 expectedId {123};
    const float expectedValue {9.87f};

    // set valid callback
    auto testCallback = [](Ark_VMContext vmContext, const Ark_Int32 resourceId,
        const Ark_CustomSpanMeasureInfo measureInfo,
        const Callback_CustomSpanMetrics_Void continuation) {
        EXPECT_EQ(resourceId, expectedId);
        Ark_CustomSpanMetrics result {
            .width = measureInfo.fontSize,
            .height = Converter::ArkValue<Opt_Float64>()
        };
        CallbackHelper(continuation).InvokeSync(result);
    };
    auto inputCallback =
        Converter::ArkValue<Callback_CustomSpanMeasureInfo_CustomSpanMetrics>(nullptr, testCallback, expectedId);
    accessor_->setOnMeasure_callback(peer_, &inputCallback);

    // get callback
    auto checkCallback = accessor_->getOnMeasure_callback(peer_);

    // invoke the obtained callback
    Ark_CustomSpanMeasureInfo inputData {
        .fontSize = Converter::ArkValue<Ark_Float64>(expectedValue)
    };
    auto checkData = CallbackHelper(checkCallback).
        InvokeWithConvertResult<CustomSpanMetrics, Ark_CustomSpanMetrics, Callback_CustomSpanMetrics_Void>(inputData);
    EXPECT_FLOAT_EQ(checkData.width, expectedValue);
    EXPECT_FALSE(checkData.height.has_value());
}

/**
 * @tc.name: CustomSpanAccessor.OnDrawTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomSpanAccessorTest, DISABLED_OnDrawTest, TestSize.Level1)
{
    ASSERT_TRUE(accessor_);
    ASSERT_TRUE(accessor_->getOnDraw_callback);
    ASSERT_TRUE(accessor_->setOnDraw_callback);

    static const Ark_Int32 expectedId {123};
    const float expectedValue {9.87f};
    static std::optional<Ark_CustomSpanDrawInfo> checkData {};

    // set valid callback
    auto testCallback = [](Ark_VMContext vmContext, const Ark_Int32 resourceId,
        const Ark_DrawContext context, const Ark_CustomSpanDrawInfo drawInfo) {
        EXPECT_EQ(resourceId, expectedId);
        checkData = drawInfo;
    };
    auto inputCallback =
        Converter::ArkValue<Callback_DrawContext_CustomSpanDrawInfo_Void>(nullptr, testCallback, expectedId);
    accessor_->setOnDraw_callback(peer_, &inputCallback);

    // get callback
    auto checkCallback = accessor_->getOnDraw_callback(peer_);

    // invoke the obtained callback
    Ark_DrawContext inputCtx {nullptr};
    Ark_CustomSpanDrawInfo inputData {
        .x = Converter::ArkValue<Ark_Float64>(expectedValue)
    };
    CallbackHelper(checkCallback).InvokeSync(inputCtx, inputData);
    ASSERT_TRUE(checkData.has_value());
    EXPECT_FLOAT_EQ(Converter::Convert<float>(checkData->x), expectedValue);
}

/**
 * @tc.name: CustomSpanAccessorTest.InvalidateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomSpanAccessorTest, InvalidateTest, TestSize.Level1)
{
    auto value = Converter::ArkUnion<Ark_Union_String_ImageAttachment_CustomSpan, Ark_CustomSpan>(peer_);
    auto inputStyles = Converter::ArkValue<Opt_Array_StyleOptions>();
    Ark_StyledString styledStringPeer =
        accessors_->getStyledStringAccessor()->construct(&value, &inputStyles);
    ASSERT_NE(styledStringPeer, nullptr);

    auto frameNode = AceType::MakeRefPtr<MockFrameNode>();
    auto spanString = styledStringPeer->spanString;
    ASSERT_NE(spanString, nullptr);
    spanString->SetFramNode(frameNode);
    spanString->AddCustomSpan();

    EXPECT_CALL(*frameNode, MarkDirtyNode(_)).Times(1);
    accessor_->invalidate(peer_);
}
} // namespace OHOS::Ace::NG