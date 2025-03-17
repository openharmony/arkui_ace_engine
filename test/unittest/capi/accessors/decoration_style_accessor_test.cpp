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

#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/implementation/decoration_style_peer.h"
#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
 
namespace OHOS::Ace::NG {
namespace {
    const std::vector<std::tuple<std::string, TextDecoration,
        Ark_TextDecorationType>> testFixtureTextDecorationValues = {
        { "TextDecoration::NONE", TextDecoration::NONE, Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE },
        { "TextDecoration::UNDERLINE", TextDecoration::UNDERLINE,
            Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_UNDERLINE },
        { "TextDecoration::OVERLINE", TextDecoration::OVERLINE,
            Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_OVERLINE },
        { "TextDecoration::LINE_THROUGH", TextDecoration::LINE_THROUGH,
            Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_LINE_THROUGH },
        { "TextDecoration::INHERIT", TextDecoration::INHERIT, Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE },
        { "-1", static_cast<TextDecoration>(-1), Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE },
    };

    const std::vector<std::tuple<std::string, TextDecorationStyle,
        Ark_TextDecorationStyle>> testFixtureTextDecorationStyleValues = {
        { "TextDecorationStyle::SOLID", TextDecorationStyle::SOLID,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_SOLID },
        { "TextDecorationStyle::DOUBLE", TextDecorationStyle::DOUBLE,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DOUBLE },
        { "TextDecorationStyle::DOTTED", TextDecorationStyle::DOTTED,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DOTTED },
        { "TextDecorationStyle::DASHED", TextDecorationStyle::DASHED,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DASHED },
        { "TextDecorationStyle::WAVY", TextDecorationStyle::WAVY,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_WAVY },
        { "TextDecorationStyle::INITIAL", TextDecorationStyle::INITIAL,
            static_cast<Ark_TextDecorationStyle>(-1) },
        { "TextDecorationStyle::INHERIT", TextDecorationStyle::INHERIT,
            static_cast<Ark_TextDecorationStyle>(-1) },
        { "-1", static_cast<TextDecorationStyle>(-1),
            static_cast<Ark_TextDecorationStyle>(-1) },
    };

}
 
using namespace testing;
using namespace testing::ext;

class DecorationStyleAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIDecorationStyleAccessor,
        &GENERATED_ArkUIAccessors::getDecorationStyleAccessor, DecorationStylePeer> {
public:
    void* CreatePeerInstance() override
    {
        return accessor_->ctor(nullptr);
    }
    void DestroyPeer(DecorationStylePeer* peer)
    {
        finalyzer_(peer);
        peer = nullptr;
    }
};
 
/**
 * @tc.name: getTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DecorationStyleAccessorTest, getTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getType, nullptr);
    Ark_DecorationStyleInterface* stylePtr = new Ark_DecorationStyleInterface();
    for (auto& [input, value, expected] : testFixtureTextDecorationValues) {
        DestroyPeer(peer_);
        stylePtr->type = Converter::ArkValue<Ark_TextDecorationType>(value);
        peer_ = accessor_->ctor(stylePtr);
        Ark_TextDecorationType type = accessor_->getType(peer_);
        EXPECT_EQ(expected, type) <<
            "Input value is: " << input << ", method: getType";
    }
}

/**
 * @tc.name: getStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DecorationStyleAccessorTest, getStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getStyle, nullptr);
    Ark_DecorationStyleInterface* stylePtr = new Ark_DecorationStyleInterface();
    stylePtr->type = Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE;
    for (auto& [input, value, expected] : testFixtureTextDecorationStyleValues) {
        DestroyPeer(peer_);
        stylePtr->style = Converter::ArkValue<Opt_TextDecorationStyle>(value);
        peer_ = accessor_->ctor(stylePtr);
        auto style = accessor_->getStyle(peer_);
        EXPECT_EQ(expected, style) <<
            "Input value is: " << input << ", method: getStyle";
    }
}

} // namespace OHOS::Ace::NG