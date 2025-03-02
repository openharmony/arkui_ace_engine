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

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class MutableStyledStringAccessorTest : public AccessorTestBase<GENERATED_ArkUIMutableStyledStringAccessor,
    &GENERATED_ArkUIAccessors::getMutableStyledStringAccessor, MutableStyledStringPeer> {
protected:
    Ark_VMContext vmContext_ = nullptr;
};


namespace {
struct StyleTestPlan {
    int32_t start;
    int32_t length;
    Ark_Color color;
};
} // namespace


/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, ctorTest, TestSize.Level1)
{
    auto peer1 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->ctor());
    auto peer2 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->ctor());
    auto peer3 = reinterpret_cast<MutableStyledStringPeer*>(this->accessor_->ctor());
    ASSERT_NE(peer1, nullptr);
    ASSERT_NE(peer2, nullptr);
    ASSERT_NE(peer3, nullptr);
    EXPECT_EQ(peer1->spanString, nullptr);
    EXPECT_EQ(peer2->spanString, nullptr);
    EXPECT_EQ(peer3->spanString, nullptr);
    finalyzer_(peer1);
    finalyzer_(peer2);
    finalyzer_(peer3);
}

/**
 * @tc.name: replaceStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStringTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("replaceStringTest");
    const auto start = Converter::ArkValue<Ark_Number>(7);
    const auto length = Converter::ArkValue<Ark_Number>(6);
    const auto str = Converter::ArkValue<Ark_String>("MutableStyled");
    accessor_->replaceString(vmContext_, peer_, &start, &length, &str);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetString(), "replaceMutableStyledTest");
}

/**
 * @tc.name: replaceStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStringInvalidTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("replaceStringInvalidTest");
    const auto start = Converter::ArkValue<Ark_Number>(-1);
    const auto length = Converter::ArkValue<Ark_Number>(-2);
    const auto str = Converter::ArkValue<Ark_String>("UnusedString");
    accessor_->replaceString(vmContext_, nullptr, &start, &length, &str);
    accessor_->replaceString(vmContext_, peer_, nullptr, &length, &str);
    accessor_->replaceString(vmContext_, peer_, &start, nullptr, &str);
    accessor_->replaceString(vmContext_, peer_, &start, &length, nullptr);
    accessor_->replaceString(vmContext_, peer_, &start, &length, &str);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetString(), "replaceStringInvalidTest");
}

/**
 * @tc.name: insertStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, insertStringTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("insertStringTest");
    const auto start = Converter::ArkValue<Ark_Number>(6);
    const auto str = Converter::ArkValue<Ark_String>("MutableStyled");
    accessor_->insertString(vmContext_, peer_, &start, &str);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetString(), "insertMutableStyledStringTest");
}

/**
 * @tc.name: insertStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, insertStringInvalidTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("insertStringInvalidTest");
    const auto start = Converter::ArkValue<Ark_Number>(-1);
    const auto str = Converter::ArkValue<Ark_String>("UnusedString");
    accessor_->insertString(vmContext_, nullptr, &start, &str);
    accessor_->insertString(vmContext_, peer_, nullptr, &str);
    accessor_->insertString(vmContext_, peer_, &start, nullptr);
    accessor_->insertString(vmContext_, peer_, &start, &str);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetString(), "insertStringInvalidTest");
}

/**
 * @tc.name: removeStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeStringTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("removeStringTest");
    const auto start = Converter::ArkValue<Ark_Number>(5);
    const auto length = Converter::ArkValue<Ark_Number>(4);
    accessor_->removeString(vmContext_, peer_, &start, &length);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetString(), "removingTest");
}

/**
 * @tc.name: removeStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeStringInvalidTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("removeStringInvalidTest");
    const auto start = Converter::ArkValue<Ark_Number>(-10);
    const auto length = Converter::ArkValue<Ark_Number>(-2);
    accessor_->removeString(vmContext_, nullptr, &start, &length);
    accessor_->removeString(vmContext_, peer_, nullptr, &length);
    accessor_->removeString(vmContext_, peer_, &start, nullptr);
    accessor_->removeString(vmContext_, peer_, &start, &length);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetString(), "removeStringInvalidTest");
}

/**
 * @tc.name: replaceStyleTest
 * @tc.desc: Checking the correct operation of the span replacement.
 * The conversion of all spans is checked in the tests for StyledStringAccessor ctor.
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, DISABLED_replaceStyleTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("replaceStyleTest");
    const std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = Color::RED }, 0, 7),
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = Color::GREEN }, 7, 12),
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = Color::BLUE }, 12, 16)
    };
    peer_->spanString->BindWithSpans(spans);

    const std::vector<StyleTestPlan> testPlan {
        { 0, 7, ARK_COLOR_BLACK },
        { 7, 5, ARK_COLOR_GRAY },
        { 12, 4, ARK_COLOR_WHITE },
    };
    for (const auto& plan : testPlan) {
#ifdef WRON_TYPE
        const Ark_TextStyle_styled_string arkStyle {
            .fontColor = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(plan.color),
            .fontFamily = Converter::ArkValue<Opt_String>(Ark_Empty()),
            .fontSize = Converter::ArkValue<Opt_Number>(Ark_Empty()),
            .fontWeight = Converter::ArkValue<Opt_Number>(Ark_Empty()),
            .fontStyle = Converter::ArkValue<Opt_FontStyle>(Ark_Empty())
        };
#endif
        const Ark_SpanStyle arkSpan {
            .start = Converter::ArkValue<Ark_Number>(plan.start),
            .length = Converter::ArkValue<Ark_Number>(plan.length),
            .styledKey = ARK_STYLED_STRING_KEY_FONT,
#ifdef  WRON_TYPE
            .styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_TextStyle_styled_string>(arkStyle)
#endif
        };
        accessor_->replaceStyle(vmContext_, peer_, &arkSpan);
        ASSERT_NE(peer_->spanString, nullptr);
        const auto currentSpans = peer_->spanString->GetSpans(plan.start, plan.length);
        ASSERT_EQ(currentSpans.size(), 1);
        const auto fontSpan = AceType::DynamicCast<FontSpan>(currentSpans.front());
        ASSERT_NE(fontSpan, nullptr);
        EXPECT_EQ(fontSpan->GetFont().fontColor, Converter::OptConvert<Color>(plan.color).value_or(Color::TRANSPARENT));
    }
    EXPECT_EQ(peer_->spanString->GetString(), "replaceStyleTest");
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
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("replaceStyleInvalidTest");
    const std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = COLOR }, start, length)
    };
    peer_->spanString->BindWithSpans(spans);

    accessor_->replaceStyle(vmContext_, peer_, nullptr);
#ifdef WRONG_TYPE
    const Ark_TextStyle_styled_string arkStyle {
        .fontColor = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty()),
        .fontFamily = Converter::ArkValue<Opt_String>(Ark_Empty()),
        .fontSize = Converter::ArkValue<Opt_Number>(Ark_Empty()),
        .fontWeight = Converter::ArkValue<Opt_Number>(Ark_Empty()),
        .fontStyle = Converter::ArkValue<Opt_FontStyle>(Ark_Empty())
    };
#endif
    Ark_SpanStyle arkSpan {
        .start = Converter::ArkValue<Ark_Number>(0),
        .length = Converter::ArkValue<Ark_Number>(-7),
        .styledKey = ARK_STYLED_STRING_KEY_FONT,
#ifdef WRONG_TYPE
        .styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_TextStyle_styled_string>(arkStyle)
#endif
    };
    accessor_->replaceStyle(vmContext_, peer_, &arkSpan);
    arkSpan.start = Converter::ArkValue<Ark_Number>(-7);
    arkSpan.length = Converter::ArkValue<Ark_Number>(0);
    accessor_->replaceStyle(vmContext_, peer_, &arkSpan);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto currentSpans = peer_->spanString->GetSpans(start, length);
    ASSERT_EQ(currentSpans.size(), 1);
    const auto fontSpan = AceType::DynamicCast<FontSpan>(currentSpans.front());
    ASSERT_NE(fontSpan, nullptr);
    EXPECT_EQ(fontSpan->GetFont().fontColor, COLOR);
    EXPECT_EQ(peer_->spanString->GetString(), "replaceStyleInvalidTest");
}

/**
 * @tc.name: setStyleTest
 * @tc.desc: Checking the correct operation of the span setting.
 * The conversion of all spans is checked in the tests for StyledStringAccessor ctor.
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, DISABLED_setStyleTest, TestSize.Level1)
{
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("setStyleTest");
    const std::vector<StyleTestPlan> testPlan {
        { 0, 3, ARK_COLOR_RED },
        { 3, 5, ARK_COLOR_GREEN },
        { 8, 4, ARK_COLOR_BLUE },
    };
    for (const auto& plan : testPlan) {
#ifdef WRONG_TYPE
        Ark_BackgroundColorStyle arkStyle {
            .textBackgroundStyle {
                .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(plan.color),
                .radius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(Ark_Empty())
            },
        };
#endif
        const Ark_SpanStyle arkSpan {
            .start = Converter::ArkValue<Ark_Number>(plan.start),
            .length = Converter::ArkValue<Ark_Number>(plan.length),
            .styledKey = ARK_STYLED_STRING_KEY_BACKGROUND_COLOR,
#ifdef WRONG_TYPE
            .styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_BackgroundColorStyle>(arkStyle)
#endif
        };
        accessor_->setStyle(vmContext_, peer_, &arkSpan);
        ASSERT_NE(peer_->spanString, nullptr);
        const auto currentSpans = peer_->spanString->GetSpans(plan.start, plan.length);
        ASSERT_EQ(currentSpans.size(), 1);
        const auto backgroundColorSpan = AceType::DynamicCast<BackgroundColorSpan>(currentSpans.front());
        ASSERT_NE(backgroundColorSpan, nullptr);
        const auto backgroundColor = backgroundColorSpan->GetBackgroundColor().backgroundColor;
        ASSERT_TRUE(backgroundColor.has_value());
        EXPECT_EQ(backgroundColor.value(), Converter::OptConvert<Color>(plan.color).value_or(Color::TRANSPARENT));
    }
    EXPECT_EQ(peer_->spanString->GetString(), "setStyleTest");
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
    peer_->spanString = AceType::MakeRefPtr<MutableSpanString>("setStyleInvalidTest");
    const std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<DecorationSpan>(TextDecoration::UNDERLINE, std::nullopt, std::nullopt, start, length)
    };
    peer_->spanString->BindWithSpans(spans);

    accessor_->setStyle(vmContext_, peer_, nullptr);
#ifdef WRONG_TYPE
    const Ark_DecorationStyle arkStyle {
        .type = ARK_TEXT_DECORATION_TYPE_OVERLINE,
        .color = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty()),
        .style = Converter::ArkValue<Opt_TextDecorationStyle>(Ark_Empty())
    };
#endif
    Ark_SpanStyle arkSpan {
        .start = Converter::ArkValue<Ark_Number>(-1),
        .length = Converter::ArkValue<Ark_Number>(7),
        .styledKey = ARK_STYLED_STRING_KEY_DECORATION,
#ifdef WRONG_TYPE
        .styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_DecorationStyle>(arkStyle)
#endif
    };
    accessor_->setStyle(vmContext_, peer_, &arkSpan);
    arkSpan.start = Converter::ArkValue<Ark_Number>(0);
    arkSpan.length = Converter::ArkValue<Ark_Number>(0);
    accessor_->setStyle(vmContext_, peer_, &arkSpan);
    ASSERT_NE(peer_->spanString, nullptr);
    auto currentSpans = peer_->spanString->GetSpans(start, length);
    ASSERT_EQ(currentSpans.size(), 1);
    auto decorationSpan = AceType::DynamicCast<DecorationSpan>(currentSpans.front());
    ASSERT_NE(decorationSpan, nullptr);
    EXPECT_EQ(decorationSpan->GetTextDecorationType(), TextDecoration::UNDERLINE);
    EXPECT_EQ(peer_->spanString->GetString(), "setStyleInvalidTest");
}

static RefPtr<MutableSpanString> CreateTestSpans(const std::string& str)
{
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(str);
    std::vector<RefPtr<SpanBase>> spans {
        AceType::MakeRefPtr<FontSpan>(Font { .fontColor = Color::RED }, 0, 1),
        AceType::MakeRefPtr<DecorationSpan>(TextDecoration::UNDERLINE, std::nullopt, std::nullopt, 0, str.length()),
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
    const std::string testString("removeStyleTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Number>(0);
    const auto arkLength = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(testString.length()));
    accessor_->removeStyle(vmContext_, peer_, &arkStart, &arkLength, ARK_STYLED_STRING_KEY_DECORATION);
    ASSERT_NE(peer_->spanString, nullptr);
    auto currentSpans = peer_->spanString->GetSpans(0, testString.length());
    ASSERT_EQ(currentSpans.size(), 2);
    EXPECT_NE(AceType::DynamicCast<FontSpan>(currentSpans[0]), nullptr);
    EXPECT_NE(AceType::DynamicCast<BaselineOffsetSpan>(currentSpans[1]), nullptr);
    const auto arkLength1 = Converter::ArkValue<Ark_Number>(1);
    accessor_->removeStyle(vmContext_, peer_, &arkStart, &arkLength1, ARK_STYLED_STRING_KEY_FONT);
    currentSpans = peer_->spanString->GetSpans(0, testString.length());
    ASSERT_EQ(currentSpans.size(), 1);
    EXPECT_NE(AceType::DynamicCast<BaselineOffsetSpan>(currentSpans[0]), nullptr);
    accessor_->removeStyle(vmContext_, peer_, &arkStart, &arkLength, ARK_STYLED_STRING_KEY_BASELINE_OFFSET);
    currentSpans = peer_->spanString->GetSpans(0, testString.length());
    EXPECT_EQ(currentSpans.size(), 0);
    EXPECT_EQ(peer_->spanString->GetString(), testString);
}

/**
 * @tc.name: removeInvalidStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeInvalidStyleTest, TestSize.Level1)
{
    const std::string testString("removeInvalidStyleTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Number>(-1);
    const auto arkLength = Converter::ArkValue<Ark_Number>(0);
    accessor_->removeStyle(vmContext_, nullptr, nullptr, nullptr, ARK_STYLED_STRING_KEY_DECORATION);
    accessor_->removeStyle(vmContext_, peer_, nullptr, nullptr, ARK_STYLED_STRING_KEY_DECORATION);
    accessor_->removeStyle(vmContext_, peer_, &arkStart, nullptr, ARK_STYLED_STRING_KEY_DECORATION);
    accessor_->removeStyle(vmContext_, peer_, &arkStart, &arkLength, ARK_STYLED_STRING_KEY_DECORATION);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetString(), testString);
}

/**
 * @tc.name: removeStylesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeStylesTest, TestSize.Level1)
{
    const std::string testString("removeStylesTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Number>(0);
    const auto arkLength1 = Converter::ArkValue<Ark_Number>(1);
    accessor_->removeStyles(vmContext_, peer_, &arkStart, &arkLength1);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 2);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::BaselineOffset).size(), 1);
    const auto arkLength = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(testString.length()));
    accessor_->removeStyles(vmContext_, peer_, &arkStart, &arkLength);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 0);
    EXPECT_EQ(peer_->spanString->GetString(), testString);
}

/**
 * @tc.name: removeInvalidStylesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, removeInvalidStylesTest, TestSize.Level1)
{
    const std::string testString("removeInvalidStylesTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Number>(0);
    const auto arkLength = Converter::ArkValue<Ark_Number>(-1);
    accessor_->removeStyles(vmContext_, nullptr, nullptr, nullptr);
    accessor_->removeStyles(vmContext_, peer_, nullptr, nullptr);
    accessor_->removeStyles(vmContext_, peer_, &arkStart, nullptr);
    accessor_->removeStyles(vmContext_, peer_, &arkStart, &arkLength);
    ASSERT_NE(peer_->spanString, nullptr);
    auto currentSpans = peer_->spanString->GetSpans(0, testString.length());
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetString(), testString);
}

/**
 * @tc.name: clearStylesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, clearStylesTest, TestSize.Level1)
{
    const std::string testString("clearStylesTest");
    peer_->spanString = CreateTestSpans(testString);

    accessor_->clearStyles(peer_);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 0);
    EXPECT_EQ(peer_->spanString->GetString(), testString);
}

/**
 * @tc.name: clearInvalidStylesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, clearInvalidStylesTest, TestSize.Level1)
{
    const std::string testString("clearInvalidStylesTest");
    peer_->spanString = CreateTestSpans(testString);

    accessor_->clearStyles(nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, testString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetString(), testString);
}

static RefPtr<MutableSpanString> CreateTestSpans2(const std::string& str)
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
    const std::string testString1("replaceStyledStringTest");
    const std::string testString2("secondString");
    peer_->spanString = CreateTestSpans(testString1);
    MutableStyledStringPeer peer2;
    peer2.spanString = CreateTestSpans2(testString2);

    const auto arkStart = Converter::ArkValue<Ark_Number>(0);
    const auto arkLength = Converter::ArkValue<Ark_Number>(19);
    accessor_->replaceStyledString(vmContext_, peer_, &arkStart, &arkLength, &peer2);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetString();
    EXPECT_EQ(resultString, "secondStringTest");
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 4);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::LetterSpacing).size(), 1);

    ASSERT_NE(peer2.spanString, nullptr);
    EXPECT_EQ(peer2.spanString->GetString(), testString2);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length()).size(), 2);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length(), SpanType::LetterSpacing).size(), 1);
}

/**
 * @tc.name: replaceStyledStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, replaceStyledStringInvalidTest, TestSize.Level1)
{
    const std::string testString("replaceStyledStringInvalidTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Number>(-1);
    const auto arkLength = Converter::ArkValue<Ark_Number>(-10);
    accessor_->replaceStyledString(vmContext_, nullptr, nullptr, nullptr, nullptr);
    accessor_->replaceStyledString(vmContext_, peer_, nullptr, nullptr, nullptr);
    accessor_->replaceStyledString(vmContext_, peer_, &arkStart, nullptr, nullptr);
    accessor_->replaceStyledString(vmContext_, peer_, &arkStart, &arkLength, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetString();
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
    const std::string testString1("insertStyledStringTest");
    const std::string testString2("Second");
    peer_->spanString = CreateTestSpans(testString1);
    MutableStyledStringPeer peer2;
    peer2.spanString = CreateTestSpans2(testString2);

    const auto arkStart = Converter::ArkValue<Ark_Number>(12);
    accessor_->insertStyledString(vmContext_, peer_, &arkStart, &peer2);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetString();
    EXPECT_EQ(resultString, "insertStyledSecondStringTest");
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 7);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 2);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 2);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::LetterSpacing).size(), 1);

    ASSERT_NE(peer2.spanString, nullptr);
    EXPECT_EQ(peer2.spanString->GetString(), testString2);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length()).size(), 2);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length(), SpanType::LetterSpacing).size(), 1);
}

/**
 * @tc.name: insertStyledStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, insertStyledStringInvalidTest, TestSize.Level1)
{
    const std::string testString("insertStyledStringInvalidTest");
    peer_->spanString = CreateTestSpans(testString);

    const auto arkStart = Converter::ArkValue<Ark_Number>(-1);
    accessor_->insertStyledString(vmContext_, nullptr, nullptr, nullptr);
    accessor_->insertStyledString(vmContext_, peer_, nullptr, nullptr);
    accessor_->insertStyledString(vmContext_, peer_, &arkStart, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetString();
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
    const std::string testString1("appendStyledStringTest");
    const std::string testString2("End");
    peer_->spanString = CreateTestSpans(testString1);
    MutableStyledStringPeer peer2;
    peer2.spanString = CreateTestSpans2(testString2);

    accessor_->appendStyledString(peer_, &peer2);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetString();
    EXPECT_EQ(resultString, "appendStyledStringTestEnd");
    auto currentSpans = peer_->spanString->GetSpans(0, resultString.length());
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 5);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::LetterSpacing).size(), 1);

    ASSERT_NE(peer2.spanString, nullptr);
    EXPECT_EQ(peer2.spanString->GetString(), testString2);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length()).size(), 2);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length(), SpanType::TextShadow).size(), 1);
    EXPECT_EQ(peer2.spanString->GetSpans(0, testString2.length(), SpanType::LetterSpacing).size(), 1);
}

/**
 * @tc.name: appendStyledStringInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MutableStyledStringAccessorTest, appendStyledStringInvalidTest, TestSize.Level1)
{
    const std::string testString("appendStyledStringInvalidTest");
    peer_->spanString = CreateTestSpans(testString);

    accessor_->appendStyledString(nullptr, nullptr);
    accessor_->appendStyledString(peer_, nullptr);
    ASSERT_NE(peer_->spanString, nullptr);
    const auto resultString = peer_->spanString->GetString();
    EXPECT_EQ(resultString, testString);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length()).size(), 3);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Font).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::Decoration).size(), 1);
    EXPECT_EQ(peer_->spanString->GetSpans(0, resultString.length(), SpanType::BaselineOffset).size(), 1);
}

} // namespace OHOS::Ace::NG
