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
#include "core/interfaces/native/implementation/text_shadow_style_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

constexpr double TEST_BLUR_RADIUS = 10.0f;
constexpr double TEST_OFFSET_X = 3.0f;
constexpr double TEST_OFFSET_Y = 4.0f;

using namespace testing;
using namespace testing::ext;

class TextShadowStyleAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUITextShadowStyleAccessor,
        &GENERATED_ArkUIAccessors::getTextShadowStyleAccessor, TextShadowStylePeer> {
public:
    void SetUp() override
    {
        ASSERT_NE(this->accessor_->construct, nullptr);
        AccessorTestBaseParent::SetUp();
    }
    void TearDown() override
    {
    }
};

/**
 * @tc.name: CtorAndGetTextShadowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextShadowStyleAccessorTest, CtorAndGetTextShadowTest, TestSize.Level1)
{
    Shadow expected(TEST_BLUR_RADIUS, Offset(TEST_OFFSET_X, TEST_OFFSET_Y),
        Color::FromRGB(0, 0, 0xff), ShadowStyle::None);
    auto arg = Converter::ArkValue<Ark_ShadowOptions>(expected, Converter::FC);
    auto argUnion = Converter::ArkUnion<Ark_Union_ShadowOptions_Array_ShadowOptions, Ark_ShadowOptions>(arg);
    peer_ = accessor_->construct(&argUnion);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->span, nullptr);
    auto shadows = peer_->span->GetTextShadow();
    ASSERT_EQ(shadows.size(), 1);
    EXPECT_EQ(shadows[0], expected);
    auto resultArk = accessor_->getTextShadow(peer_);
    auto result = Converter::Convert<std::vector<Shadow>>(resultArk);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], expected);
    finalyzer_(peer_);
}

}