/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/implementation/mutable_styled_string_peer.h"
#include "core/interfaces/native/implementation/background_color_style_peer.h"
#include "core/interfaces/native/implementation/decoration_style_peer.h"
#include "core/interfaces/native/implementation/text_style_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

template<typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestMutable : public AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType> {
public:
    virtual void SetUp(void)
    {
        ASSERT_NE(this->accessor_->construct, nullptr);
        this->peer_ = static_cast<PeerType *>(this->accessor_->construct(nullptr, nullptr));
        ASSERT_NE(this->peer_, nullptr);
        AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType>::SetUp();
    }
};

class MutableStyledStringAccessorTest : public AccessorTestMutable<GENERATED_ArkUIMutableStyledStringAccessor,
    &GENERATED_ArkUIAccessors::getMutableStyledStringAccessor, MutableStyledStringPeer> {
};


namespace {
struct StyleTestPlan {
    int32_t start;
    int32_t length;
    Color color;
};
std::vector<TextDecoration> ToVec(TextDecoration src)
{
    return {src};
}
} // namespace

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, DISABLED_ctorTest, TestSize.Level1)
{
    auto peer1 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->construct(nullptr, nullptr));
    auto peer2 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->construct(nullptr, nullptr));
    auto peer3 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->construct(nullptr, nullptr));
    ASSERT_NE(peer1, nullptr);
    ASSERT_NE(peer2, nullptr);
    ASSERT_NE(peer3, nullptr);
    ASSERT_NE(peer1->spanString, nullptr);
    ASSERT_NE(peer2->spanString, nullptr);
    ASSERT_NE(peer3->spanString, nullptr);
    finalyzer_(peer1);
    finalyzer_(peer2);
    finalyzer_(peer3);
}

/**
 * @tc.name: ctorTestCustomSpan
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, ctorTestCustomSpan, TestSize.Level1)
{
    auto styles = Converter::ArkValue<Opt_Array_StyleOptions>();
    Ark_CustomSpan customSpan = accessors_->getCustomSpanAccessor()->construct();
    auto value = Converter::ArkUnion<Ark_Union_String_ImageAttachment_CustomSpan, Ark_CustomSpan>(customSpan);
    auto peer = this->accessor_->construct(&value, &styles);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->GetMutableString(), nullptr);
}

/**
 * @tc.name: replaceStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStringTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"replaceStringTest");
    const auto start = Converter::ArkValue<Ark_Int32>(7);
    const auto length = Converter::ArkValue<Ark_Int32>(6);
    const auto str = Converter::ArkValue<Ark_String>("MutableStyled");
    accessor_->replaceString(peer_, start, length, &str);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetU16string(), u"replaceMutableStyledTest");
}

/**
 * @tc.name: replaceStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStringInvalidTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"replaceStringInvalidTest");
    const auto start = Converter::ArkValue<Ark_Int32>(-1);
    const auto length = Converter::ArkValue<Ark_Int32>(-2);
    const auto str = Converter::ArkValue<Ark_String>("UnusedString");
    accessor_->replaceString(peer_, start, length, &str);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetU16string(), u"replaceStringInvalidTest");
}

/**
 * @tc.name: insertStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, insertStringTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"insertStringTest");
    const auto start = Converter::ArkValue<Ark_Int32>(6);
    const auto str = Converter::ArkValue<Ark_String>("MutableStyled");
    accessor_->insertString(peer_, start, &str);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetU16string(), u"insertMutableStyledStringTest");
}

/**
 * @tc.name: insertStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, insertStringInvalidTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"insertStringInvalidTest");
    const auto start = Converter::ArkValue<Ark_Int32>(-1);
    const auto str = Converter::ArkValue<Ark_String>("UnusedString");
    accessor_->insertString(peer_, start, &str);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetU16string(), u"insertStringInvalidTest");
}

/**
 * @tc.name: removeStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeStringTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"removeStringTest");
    const auto start = Converter::ArkValue<Ark_Int32>(5);
    const auto length = Converter::ArkValue<Ark_Int32>(4);
    accessor_->removeString(peer_, start, length);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetU16string(), u"removingTest");
}

/**
 * @tc.name: removeStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeStringInvalidTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"removeStringInvalidTest");
    const auto start = Converter::ArkValue<Ark_Int32>(-10);
    const auto length = Converter::ArkValue<Ark_Int32>(-2);
    accessor_->removeString(peer_, start, length);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetU16string(), u"removeStringInvalidTest");
}

/**
 * @tc.name: replaceStyleTest
 * @tc.desc: Checking the correct operation of the span replacement.
 * The conversion of all spans is checked in the tests for StyledStringAccessor construct.
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStyleTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"replaceStyleTest");
    const std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = Color::RED }, 0, 7),
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = Color::GREEN }, 7, 12),
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = Color::BLUE }, 12, 16)
    };
    peer_->spanString->BindWithSpans(spans);

    const std::vector<StyleTestPlan> testPlan {
        { 0, 7, Color::BLACK },
        { 7, 5, Color::GRAY },
        { 12, 4, Color::WHITE },
    };
    for (const auto& plan : testPlan) {
        auto arkStyle = PeerUtils::CreatePeer<TextStylePeer>();
        arkStyle->span = Referenced::MakeRefPtr<FontSpan>(Font {
            .fontColor = plan.color
        });
        const Ark_SpanStyle arkSpan {
            .start = Converter::ArkValue<Ark_Int32>(plan.start),
            .length = Converter::ArkValue<Ark_Int32>(plan.length),
            .styledKey = ARK_STYLED_STRING_KEY_FONT,
            .styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_TextStyle>(arkStyle)
        };
        accessor_->replaceStyle(peer_, &arkSpan);
        ASSERT_NE(peer_->spanString, nullptr);
        const auto currentSpans = peer_->spanString->GetSpans(plan.start, plan.length);
        ASSERT_EQ(currentSpans.size(), 1);
        const auto fontSpan = AceType::DynamicCast<FontSpan>(currentSpans.front());
        ASSERT_NE(fontSpan, nullptr);
        EXPECT_EQ(fontSpan->GetFont().fontColor, plan.color);
    }
    EXPECT_EQ(peer_->spanString->GetU16string(), u"replaceStyleTest");
}

/**
 * @tc.name: replaceStyleInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStyleInvalidTest, TestSize.Level1)
{
    static constexpr auto start = 0;
    static constexpr auto length = 7;
    static const auto COLOR = Color::RED;
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"replaceStyleInvalidTest");
    const std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = COLOR }, start, length)
    };
    peer_->spanString->BindWithSpans(spans);

    accessor_->replaceStyle(peer_, nullptr);

    auto arkStyle = PeerUtils::CreatePeer<TextStylePeer>();
    arkStyle->span = Referenced::MakeRefPtr<FontSpan>();
    Ark_SpanStyle arkSpan {
        .start = Converter::ArkValue<Ark_Int32>(0),
        .length = Converter::ArkValue<Ark_Int32>(-7),
        .styledKey = ARK_STYLED_STRING_KEY_FONT,
        .styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_TextStyle>(arkStyle)
    };
    accessor_->replaceStyle(peer_, &arkSpan);
    arkSpan.start = Converter::ArkValue<Ark_Int32>(-7);
    arkSpan.length = Converter::ArkValue<Ark_Int32>(0);
    accessor_->replaceStyle(peer_, &arkSpan);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto currentSpans = peer_->spanString->GetSpans(start, length);
    ASSERT_EQ(currentSpans.size(), 1);
    const auto fontSpan = AceType::DynamicCast<FontSpan>(currentSpans.front());
    ASSERT_NE(fontSpan, nullptr);
    EXPECT_EQ(fontSpan->GetFont().fontColor, COLOR);
    EXPECT_EQ(peer_->spanString->GetU16string(), u"replaceStyleInvalidTest");
}

/**
 * @tc.name: setStyleTest
 * @tc.desc: Checking the correct operation of the span setting.
 * The conversion of all spans is checked in the tests for StyledStringAccessor construct.
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, setStyleTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"setStyleTest");
    const std::vector<StyleTestPlan> testPlan {
        { 0, 3, Color::RED },
        { 3, 5, Color::GREEN },
        { 8, 4, Color::BLUE },
    };
    for (const auto& plan : testPlan) {
        auto arkStyle = PeerUtils::CreatePeer<BackgroundColorStylePeer>();
        arkStyle->span = Referenced::MakeRefPtr<BackgroundColorSpan>(TextBackgroundStyle {
            .backgroundColor = plan.color
        });
        const Ark_SpanStyle arkSpan {
            .start = Converter::ArkValue<Ark_Int32>(plan.start),
            .length = Converter::ArkValue<Ark_Int32>(plan.length),
            .styledKey = ARK_STYLED_STRING_KEY_BACKGROUND_COLOR,
            .styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_BackgroundColorStyle>(arkStyle)
        };
        accessor_->setStyle(peer_, &arkSpan);
        ASSERT_NE(peer_->spanString, nullptr);
        const auto currentSpans = peer_->spanString->GetSpans(plan.start, plan.length);
        ASSERT_EQ(currentSpans.size(), 1);
        const auto backgroundColorSpan = AceType::DynamicCast<BackgroundColorSpan>(currentSpans.front());
        ASSERT_NE(backgroundColorSpan, nullptr);
        const auto backgroundColor = backgroundColorSpan->GetBackgroundColor().backgroundColor;
        ASSERT_TRUE(backgroundColor.has_value());
        EXPECT_EQ(backgroundColor.value(), plan.color);
    }
    EXPECT_EQ(peer_->spanString->GetU16string(), u"setStyleTest");
}

/**
 * @tc.name: setStyleInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, setStyleInvalidTest, TestSize.Level1)
{
    static constexpr auto start = 0;
    static constexpr auto length = 5;
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>(u"setStyleInvalidTest");
    const std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<DecorationSpan>(ToVec(TextDecoration::UNDERLINE), std::nullopt, std::nullopt, std::nullopt,
            start, length)
    };
    peer_->spanString->BindWithSpans(spans);

    accessor_->setStyle(peer_, nullptr);
    auto arkStyle = PeerUtils::CreatePeer<DecorationStylePeer>();
    arkStyle->span = Referenced::MakeRefPtr<DecorationSpan>(ToVec(TextDecoration::OVERLINE), std::nullopt,
        std::nullopt, std::nullopt);
    Ark_SpanStyle arkSpan {
        .start = Converter::ArkValue<Ark_Int32>(-1),
        .length = Converter::ArkValue<Ark_Int32>(7),
        .styledKey = ARK_STYLED_STRING_KEY_DECORATION,
        .styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_DecorationStyle>(arkStyle)
    };
    accessor_->setStyle(peer_, &arkSpan);
    arkSpan.start = Converter::ArkValue<Ark_Int32>(0);
    arkSpan.length = Converter::ArkValue<Ark_Int32>(0);
    accessor_->setStyle(peer_, &arkSpan);
    ASSERT_NE(peer_->spanString, nullptr);
    auto currentSpans = peer_->spanString->GetSpans(start, length);
    ASSERT_EQ(currentSpans.size(), 1);
    auto decorationSpan = AceType::DynamicCast<DecorationSpan>(currentSpans.front());
    ASSERT_NE(decorationSpan, nullptr);
    EXPECT_EQ(decorationSpan->GetTextDecorationTypes(), ToVec(TextDecoration::UNDERLINE));
    EXPECT_EQ(peer_->spanString->GetU16string(), u"setStyleInvalidTest");
}

static RefPtr<MutableSpanString> CreateTestSpans(const std::u16string& str)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(str);
    std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = Color::RED }, 0, 1),
        AceType::MakeRefPtr<DecorationSpan>(ToVec(TextDecoration::UNDERLINE), std::nullopt, std::nullopt,
            std::nullopt, 0, str.length()),
        AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(10), 0, str.length()),
    };
    spanString->BindWithSpans(spans);
    return spanString;
}

/**
 * @tc.name: removeStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeStyleTest, TestSize.Level1)
{
    const std::u16string testString(u"removeStyleTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Int32>(0);
    const auto arkLength = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(testString.length()));
    accessor_->removeStyle(peer_, arkStart, arkLength, ARK_STYLED_STRING_KEY_DECORATION);
    ASSERT_NE(peer_->spanString, nullptr);
    auto currentSpans = peer_->spanString->GetSpans(0, testString.length());
    ASSERT_EQ(currentSpans.size(), 2);
    EXPECT_NE(AceType::DynamicCast<FontSpan>(currentSpans[0]), nullptr);
    EXPECT_NE(AceType::DynamicCast<BaselineOffsetSpan>(currentSpans[1]), nullptr);
    const auto arkLength1 = Converter::ArkValue<Ark_Int32>(1);
    accessor_->removeStyle(peer_, arkStart, arkLength1, ARK_STYLED_STRING_KEY_FONT);
    currentSpans = peer_->spanString->GetSpans(0, testString.length());
    ASSERT_EQ(currentSpans.size(), 1);
    EXPECT_NE(AceType::DynamicCast<BaselineOffsetSpan>(currentSpans[0]), nullptr);
    accessor_->removeStyle(peer_, arkStart, arkLength, ARK_STYLED_STRING_KEY_BASELINE_OFFSET);
    currentSpans = peer_->spanString->GetSpans(0, testString.length());
    EXPECT_EQ(currentSpans.size(), 0);
    EXPECT_EQ(peer_->spanString->GetU16string(), testString);
}

/**
 * @tc.name: removeInvalidStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeInvalidStyleTest, TestSize.Level1)
{
    const std::u16string testString(u"removeInvalidStyleTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Int32>(-1);
    const auto arkLength = Converter::ArkValue<Ark_Int32>(0);
    accessor_->removeStyle(peer_, arkStart, arkLength, ARK_STYLED_STRING_KEY_DECORATION);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetU16string(), testString);
}

/**
 * @tc.name: removeStylesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeStylesTest, TestSize.Level1)
{
    const std::u16string testString(u"removeStylesTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Int32>(0);
    const auto arkLength1 = Converter::ArkValue<Ark_Int32>(1);
    accessor_->removeStyles(peer_, arkStart, arkLength1);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 2);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::BaselineOffset).size(), 1);
    const auto arkLength = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(testString.length()));
    accessor_->removeStyles(peer_, arkStart, arkLength);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 0);
    EXPECT_EQ(peer_->spanString->GetU16string(), testString);
}

/**
 * @tc.name: removeInvalidStylesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeInvalidStylesTest, TestSize.Level1)
{
    const std::u16string testString(u"removeInvalidStylesTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Int32>(0);
    const auto arkLength = Converter::ArkValue<Ark_Int32>(-1);
    accessor_->removeStyles(peer_, arkStart, arkLength);
    ASSERT_NE(peer_->spanString, nullptr);
    auto currentSpans = peer_->spanString->GetSpans(0, testString.length());
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetU16string(), testString);
}

/**
 * @tc.name: clearStylesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, clearStylesTest, TestSize.Level1)
{
    const std::u16string testString(u"clearStylesTest");
    peer_->spanString = CreateTestSpans(testString);

    accessor_->clearStyles(peer_);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 0);
    EXPECT_EQ(peer_->spanString->GetU16string(), testString);
}

/**
 * @tc.name: clearInvalidStylesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, clearInvalidStylesTest, TestSize.Level1)
{
    const std::u16string testString(u"clearInvalidStylesTest");
    peer_->spanString = CreateTestSpans(testString);

    accessor_->clearStyles(nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetU16string(), testString);
}

static RefPtr<MutableSpanString> CreateTestSpans2(const std::u16string& str)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(str);
    std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<TextShadowSpan>(std::vector<Shadow> {
            Shadow::CreateShadow(ShadowStyle::OuterDefaultLG)
        }, 0, str.length()),
        AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(20), 0, str.length())
    };
    spanString->BindWithSpans(spans);
    return spanString;
}

/**
 * @tc.name: replaceStyledStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStyledStringTest, TestSize.Level1)
{
    const std::u16string testString1(u"replaceStyledStringTest");
    const std::u16string testString2(u"secondString");
    peer_->spanString = CreateTestSpans(testString1);
    auto *peer2 = PeerUtils::CreatePeer<MutableStyledStringPeer>();
    peer2->spanString = CreateTestSpans2(testString2);

    const auto arkStart = Converter::ArkValue<Ark_Int32>(0);
    const auto arkLength = Converter::ArkValue<Ark_Int32>(19);
    accessor_->replaceStyledString(peer_, arkStart, arkLength, peer2);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetU16string();
    EXPECT_EQ(resultString, u"secondStringTest");
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 4);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::LetterSpacing).size(), 1);

    ASSERT_NE(peer2->spanString, nullptr);
    EXPECT_EQ(peer2->spanString->GetU16string(), testString2);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length()).size(), 2);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length(), SpanType::LetterSpacing).size(), 1);
}

/**
 * @tc.name: replaceStyledStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStyledStringInvalidTest, TestSize.Level1)
{
    const std::u16string testString(u"replaceStyledStringInvalidTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Int32>(-1);
    const auto arkLength = Converter::ArkValue<Ark_Int32>(-10);
    accessor_->replaceStyledString(peer_, arkStart, arkLength, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetU16string();
    EXPECT_EQ(resultString, testString);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 1);
}

/**
 * @tc.name: insertStyledStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, insertStyledStringTest, TestSize.Level1)
{
    const std::u16string testString1(u"insertStyledStringTest");
    const std::u16string testString2(u"Second");
    peer_->spanString = CreateTestSpans(testString1);
    auto *peer2 = PeerUtils::CreatePeer<MutableStyledStringPeer>();
    peer2->spanString = CreateTestSpans2(testString2);

    const auto arkStart = Converter::ArkValue<Ark_Int32>(12);
    accessor_->insertStyledString(peer_, arkStart, peer2);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetU16string();
    EXPECT_EQ(resultString, u"insertStyledSecondStringTest");
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 7);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 2);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 2);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::LetterSpacing).size(), 1);

    ASSERT_NE(peer2->spanString, nullptr);
    EXPECT_EQ(peer2->spanString->GetU16string(), testString2);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length()).size(), 2);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length(), SpanType::LetterSpacing).size(), 1);
}

/**
 * @tc.name: insertStyledStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, insertStyledStringInvalidTest, TestSize.Level1)
{
    const std::u16string testString(u"insertStyledStringInvalidTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Int32>(-1);
    accessor_->insertStyledString(peer_, arkStart, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetU16string();
    EXPECT_EQ(resultString, testString);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 1);
}

/**
 * @tc.name: appendStyledStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, appendStyledStringTest, TestSize.Level1)
{
    const std::u16string testString1(u"appendStyledStringTest");
    const std::u16string testString2(u"End");
    peer_->spanString = CreateTestSpans(testString1);
    auto *peer2 = PeerUtils::CreatePeer<MutableStyledStringPeer>();
    peer2->spanString = CreateTestSpans2(testString2);

    accessor_->appendStyledString(peer_, peer2);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetU16string();
    EXPECT_EQ(resultString, u"appendStyledStringTestEnd");
    auto currentSpans = peer_->spanString->GetSpans(0, resultString.length());
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 5);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::LetterSpacing).size(), 1);

    ASSERT_NE(peer2->spanString, nullptr);
    EXPECT_EQ(peer2->spanString->GetU16string(), testString2);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length()).size(), 2);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer2->spanString->GetSpans(0, testString2.length(), SpanType::LetterSpacing).size(), 1);
}

/**
 * @tc.name: appendStyledStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, appendStyledStringInvalidTest, TestSize.Level1)
{
    const std::u16string testString(u"appendStyledStringInvalidTest");
    peer_->spanString = CreateTestSpans(testString);

    accessor_->appendStyledString(nullptr, nullptr);
    accessor_->appendStyledString(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetU16string();
    EXPECT_EQ(resultString, testString);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 1);
}

} // namespace OHOS::Ace::NG
