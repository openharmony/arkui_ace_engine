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
#include "core/interfaces/native/implementation/background_color_style_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class BackgroundColorStyleAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUIBackgroundColorStyleAccessor,
        &GENERATED_ArkUIAccessors::getBackgroundColorStyleAccessor, BackgroundColorStylePeer> {
public:
    void SetUp() override
    {
        ASSERT_NE(accessor_->construct, nullptr);
        AccessorTestBaseParent::SetUp();
    }
    void TearDown() override
    {
    }
};

/**
 * @tc.name: CtorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundColorStyleAccessorTest, CtorTest, TestSize.Level1)
{
    const std::vector<std::pair<std::string, Dimension>> TEST_PLAN = {
        { "#FF0000FF", Dimension(10.0, DimensionUnit::PX) },
        { "#FF123456", Dimension(100.0, DimensionUnit::PX) },
        { "#11223344", Dimension(10.0, DimensionUnit::VP) },
        { "#00FF0000", Dimension(0.0, DimensionUnit::VP) }
    };
    Converter::ConvContext ctx;
    for (auto& value : TEST_PLAN) {
        Ark_TextBackgroundStyle arkValue;
        arkValue.color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(value.first, &ctx);
        auto radiusUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_Dimension>(value.second, &ctx);
        arkValue.radius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(radiusUnion);
        peer_ = accessor_->construct(&arkValue);
        ASSERT_NE(peer_, nullptr);
        ASSERT_NE(peer_->span, nullptr);
        auto result = peer_->span->GetBackgroundColor();
        ASSERT_TRUE(result.backgroundColor.has_value());
        auto resultColor = result.backgroundColor->ColorToString();
        EXPECT_EQ(resultColor, value.first);
        ASSERT_TRUE(result.backgroundRadius.has_value());
        EXPECT_EQ(result.backgroundRadius, BorderRadiusProperty(value.second));
        finalyzer_(peer_);
    }

    Ark_TextBackgroundStyle arkValue;
    arkValue.color = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
    arkValue.radius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(Ark_Empty());
    peer_ = accessor_->construct(&arkValue);
    ASSERT_NE(peer_, nullptr);
    auto result = peer_->span->GetBackgroundColor();
    EXPECT_FALSE(result.backgroundColor.has_value());
    EXPECT_FALSE(result.backgroundRadius.has_value());
    finalyzer_(peer_);
}

/**
 * @tc.name: GetTextBackgroundStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BackgroundColorStyleAccessorTest, GetTextBackgroundStyleTest, TestSize.Level1)
{
    const std::vector<std::pair<std::string, Dimension>> TEST_PLAN = {
        { "#FF0000FF", Dimension(10.0, DimensionUnit::PX) },
        { "#FF123456", Dimension(100.0, DimensionUnit::PX) },
        { "#11223344", Dimension(10.0, DimensionUnit::VP) },
        { "#00FF0000", Dimension(0.0, DimensionUnit::VP) }
    };
    Converter::ConvContext ctx;
    for (auto& value : TEST_PLAN) {
        Ark_TextBackgroundStyle arkValue;
        arkValue.color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(value.first, &ctx);
        auto radiusUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_Dimension>(value.second, &ctx);
        arkValue.radius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(radiusUnion);
        peer_ = accessor_->construct(&arkValue);
        ASSERT_NE(peer_, nullptr);
        Ark_TextBackgroundStyle style = accessor_->getTextBackgroundStyle(peer_);
        auto aceStyle = Converter::Convert<TextBackgroundStyle>(style);
        ASSERT_TRUE(aceStyle.backgroundColor.has_value());
        EXPECT_EQ(aceStyle.backgroundColor.value().ToString(), value.first);
        ASSERT_TRUE(aceStyle.backgroundRadius.has_value());
        EXPECT_EQ(aceStyle.backgroundRadius, BorderRadiusProperty(value.second));
        finalyzer_(peer_);
    }
}

}