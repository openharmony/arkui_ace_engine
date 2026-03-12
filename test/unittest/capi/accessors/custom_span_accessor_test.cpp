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

class CustomSpanNativeAccessorTest : public AccessorTestBase<GENERATED_ArkUICustomSpanNativeAccessor,
                                    &GENERATED_ArkUIAccessors::getCustomSpanNativeAccessor, CustomSpanNativePeer> {};

/**
 * @tc.name: setOnMeasure_callbackTestOnMeasure.OnMeasureTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomSpanNativeAccessorTest, DISABLED_setOnMeasure_callbackTestOnMeasure, TestSize.Level1)
{
    ASSERT_TRUE(accessor_);
    // CustomSpanNativeAccessor no longer has draw callbacks in this generation.
}

/**
 * @tc.name: setOnDraw_callbackTestOnDraw.OnDrawTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomSpanNativeAccessorTest, DISABLED_setOnDraw_callbackTestOnDraw, TestSize.Level1)
{
    ASSERT_TRUE(accessor_);
    // CustomSpanNativeAccessor no longer has draw callbacks in this generation.
}

/**
 * @tc.name: invalidateTest.InvalidateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomSpanNativeAccessorTest, invalidateTest, TestSize.Level1)
{
    Ark_CustomSpanWrapper wrap {
        .nativeObj = peer_
    };
    auto value = Converter::ArkUnion<Ark_Union_String_ImageAttachment_CustomSpanWrapper, Ark_CustomSpanWrapper>(wrap);
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