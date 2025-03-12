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
#include "core/interfaces/native/implementation/text_style_styled_string_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const Ark_Color g_fontColor = ARK_COLOR_BLUE;
const std::string g_fontFamily = "Arial";
const Dimension g_fontSize = 55._px;
const std::string g_fontWeight = "200";
const Ace::FontStyle g_fontSyle = Ace::FontStyle::ITALIC;
} // namespace

class TextStyleStyledStringAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUITextStyle_styled_stringAccessor,
    &GENERATED_ArkUIAccessors::getTextStyle_styled_stringAccessor, TextStyle_styled_stringPeer> {
public:
    static void SetUpTestCase()
    {
        AccessorTestCtorBase::SetUpTestCase();
        AccessorTestCtorBase::SetupTheme<TextTheme>();
        themeConstants_->LoadTheme(0);
    }

    void *CreatePeerInstance() override
    {
        auto arkFontColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(g_fontColor);
        Ark_TextStyleInterface options {
            .fontColor = Converter::ArkValue<Opt_ResourceColor>(arkFontColor),
            .fontFamily = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(g_fontFamily, Converter::FC),
            .fontSize = Converter::ArkValue<Opt_LengthMetrics>(g_fontSize),
            .fontWeight = Converter::ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(
                g_fontWeight, Converter::FC),
            .fontStyle = Converter::ArkValue<Opt_FontStyle>(g_fontSyle)
        };
        Opt_TextStyleInterface optionsOpt = Converter::ArkValue<Opt_TextStyleInterface>(options);
        return accessor_->ctor(&optionsOpt);
    }
};

/*
 * @tc.name: emptyOptionsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleStyledStringAccessorTest, emptyOptionsTest, TestSize.Level1)
{
    // finalize base peer
    finalyzer_(peer_);

    // create new peer
    peer_ = accessor_->ctor(nullptr);
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getFontFamily(peer_)), "");
    EXPECT_NEAR(Converter::Convert<float>(accessor_->getFontSize(peer_)), 0, FLT_EPSILON);
    EXPECT_EQ(static_cast<Ace::FontWeight>(Converter::Convert<int32_t>(accessor_->getFontWeight(peer_))),
        Ace::FontWeight::W100);
    std::optional<Ace::FontStyle> fontStyleOpt = Converter::OptConvert<Ace::FontStyle>(accessor_->getFontStyle(peer_));
    ASSERT_TRUE(fontStyleOpt.has_value());
    EXPECT_EQ(fontStyleOpt.value(), Ace::FontStyle::NORMAL);
}

/*
 * @tc.name: getFontFamilyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleStyledStringAccessorTest, getFontFamilyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFontFamily, nullptr);
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getFontFamily(peer_)), g_fontFamily);
}

/*
 * @tc.name: getFontSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleStyledStringAccessorTest, getFontSizeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFontSize, nullptr);
    EXPECT_NEAR(Converter::Convert<float>(accessor_->getFontSize(peer_)), g_fontSize.ConvertToPx(), FLT_EPSILON);
}

/*
 * @tc.name: getFontWeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleStyledStringAccessorTest, getFontWeightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFontWeight, nullptr);
    EXPECT_EQ(static_cast<Ace::FontWeight>(Converter::Convert<int32_t>(accessor_->getFontWeight(peer_))),
        Ace::FontWeight::W200);
}

/*
 * @tc.name: getFontStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleStyledStringAccessorTest, getFontStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFontStyle, nullptr);
    std::optional<Ace::FontStyle> fontStyleOpt = Converter::OptConvert<Ace::FontStyle>(accessor_->getFontStyle(peer_));
    ASSERT_TRUE(fontStyleOpt.has_value());
    EXPECT_EQ(fontStyleOpt.value(), g_fontSyle);
}

} // namespace OHOS::Ace::NG