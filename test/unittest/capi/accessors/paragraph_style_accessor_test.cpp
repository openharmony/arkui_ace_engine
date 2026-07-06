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

#include <gmock/gmock.h>

#include "accessor_test_base.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/interfaces/native/implementation/length_metrics_peer.h"
#include "core/interfaces/native/implementation/paragraph_style_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
constexpr auto TEST_MARGIN = 100;
constexpr auto TEST_MARGIN_2 = 200;
constexpr auto TEST_TEXT_ALIGN = TextAlign::RIGHT;
constexpr auto TEST_LINES_NUM = 5;
constexpr auto TEST_TEXT_OVERFLOW = TextOverflow::ELLIPSIS;
constexpr auto TEST_WORD_BREAK = WordBreak::BREAK_ALL;
constexpr auto TEST_TAIL_INDENT_VALUE_1 = 50.0;
constexpr auto TEST_TAIL_INDENT_VALUE_2 = 30.0;
constexpr auto TEST_TAIL_INDENT_NEGATIVE = -10.0;
constexpr auto TEST_TAIL_INDENT_PERCENT_VALUE = 10.0;
}

class ParagraphStyleAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIParagraphStyleAccessor,
        &GENERATED_ArkUIAccessors::getParagraphStyleAccessor, ParagraphStylePeer> {
public:
    void* CreatePeerInstance() override
    {
        auto& interface = TypeHelper::WriteTo(param_);
        interface.textAlign = Converter::ArkValue<Opt_TextAlign>(TEST_TEXT_ALIGN);
        interface.textIndent.value = Converter::ArkValue<Ark_LengthMetrics>(Dimension(TEST_MARGIN));
        interface.maxLines = Converter::ArkValue<Opt_Int32>(TEST_LINES_NUM);
        interface.overflow = Converter::ArkValue<Opt_TextOverflow>(TEST_TEXT_OVERFLOW);
        interface.wordBreak = Converter::ArkValue<Opt_WordBreak>(TEST_WORD_BREAK);

        // Margin holder
        NG::LeadingMargin margin {.size = LeadingMarginSize(Dimension(TEST_MARGIN), Dimension(TEST_MARGIN_2))};
        margin.pixmap = AceType::MakeRefPtr<MockPixelMap>();

        auto leadingMargin = Converter::ArkUnion<Ark_Union_LengthMetrics_LeadingMarginPlaceholder,
            Ark_LeadingMarginPlaceholder>(margin, &ctx_);
        auto& holder = TypeHelper::WriteTo(interface.leadingMargin);
        holder = leadingMargin;

        return accessor_->construct(&param_);
    }

private:
    Opt_ParagraphStyleInterface param_ = {};
    Converter::ConvContext ctx_;
};

// Helper function for tailIndent tests
ParagraphStylePeer CreatePeerWithTailIndent(const std::vector<double>& indentValues,
    DimensionUnit unit = DimensionUnit::VP)
{
    static auto accessor = GENERATED_ArkUIAccessors::getParagraphStyleAccessor();
    Opt_ParagraphStyleInterface localParam {};
    Converter::ConvContext ctx;
    
    auto& interface = TypeHelper::WriteTo(localParam);
    interface.textAlign = Converter::ArkValue<Opt_TextAlign>(TEST_TEXT_ALIGN);
    
    auto& tailIndentUnion = TypeHelper::WriteTo(interface.tailIndents);
    if (indentValues.size() == 1) {
        tailIndentUnion.value.selector = 0;
        tailIndentUnion.value.value0 = Converter::ArkValue<Ark_LengthMetrics>(Dimension(indentValues[0], unit));
    } else {
        tailIndentUnion.value.selector = 1;
        auto arrayData = ctx.AllocateArray<Array_LengthMetrics>(indentValues.size());
        for (size_t i = 0; i < indentValues.size(); i++) {
            arrayData.array[i] = Converter::ArkValue<Ark_LengthMetrics>(Dimension(indentValues[i], unit));
        }
        tailIndentUnion.value.value1 = arrayData;
    }
    
    return accessor->construct(&localParam);
}

/**
 * @tc.name: getTextAlignTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getTextAlignTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTextAlign, nullptr);
    auto testVal = accessor_->getTextAlign(peer_);
    auto converted = Converter::ArkValue<Ark_TextAlign>(TEST_TEXT_ALIGN);
    EXPECT_EQ(Converter::GetOpt(testVal), converted);
}

/**
 * @tc.name: getTextIndentTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getTextIndentTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTextIndent, nullptr);
    auto testVal = accessor_->getTextIndent(peer_);
    auto converted = Converter::OptConvert<int>(testVal);
    EXPECT_EQ(converted, TEST_MARGIN);
}

/**
 * @tc.name: getMaxLinesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getMaxLinesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMaxLines, nullptr);
    auto testVal = accessor_->getMaxLines(peer_);
    auto converted = Converter::OptConvert<int>(testVal);
    EXPECT_EQ(converted, TEST_LINES_NUM);
}

/**
 * @tc.name: getOverflowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getOverflowTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getOverflow, nullptr);
    auto testVal = accessor_->getOverflow(peer_);
    auto converted = Converter::ArkValue<Ark_TextOverflow>(TEST_TEXT_OVERFLOW);
    EXPECT_EQ(Converter::GetOpt(testVal), converted);
}

/**
 * @tc.name: getWordBreakTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getWordBreakTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWordBreak, nullptr);
    auto testVal = accessor_->getWordBreak(peer_);
    auto converted = Converter::ArkValue<Ark_WordBreak>(TEST_WORD_BREAK);
    EXPECT_EQ(Converter::GetOpt(testVal), converted);
}

/**
 * @tc.name: getLeadingMarginTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, DISABLED_getLeadingMarginTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLeadingMargin, nullptr);
    auto testVal = accessor_->getLeadingMargin(peer_);
    Converter::VisitUnion(testVal,
        [](const Ark_Float64& metrics) {
            EXPECT_EQ(Converter::Convert<int>(metrics), TEST_MARGIN);
        },
        [](const Ark_LeadingMarginPlaceholder& inMargin) {
            auto convVal0 = Converter::OptConvert<Dimension>(inMargin.size.value0).value_or(Dimension());
            auto convVal1 = Converter::OptConvert<Dimension>(inMargin.size.value1).value_or(Dimension());
            EXPECT_EQ(static_cast<int>(convVal0.ConvertToPx()), TEST_MARGIN);
            EXPECT_EQ(static_cast<int>(convVal1.ConvertToPx()), TEST_MARGIN_2);
            delete inMargin.pixelMap;
        },
        []() {});
}

/**
 * @tc.name: getTailIndentsTest001
 * @tc.desc: Test normal single value tailIndents
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getTailIndentsTest001, TestSize.Level1)
{
    auto localPeer = CreatePeerWithTailIndent({TEST_TAIL_INDENT_VALUE_1});
    ASSERT_NE(accessor_->getTailIndents, nullptr);
    auto testVal = accessor_->getTailIndents(localPeer);
    ASSERT_NE(testVal.tag, InteropTag::INTEROP_TAG_UNDEFINED);
    ASSERT_NE(testVal.value.array, nullptr);
    EXPECT_EQ(testVal.value.length, 1);
    EXPECT_DOUBLE_EQ(testVal.value.array[0], TEST_TAIL_INDENT_VALUE_1);
}

/**
 * @tc.name: getTailIndentsTest002
 * @tc.desc: Test negative value validation - should be reset to 0
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getTailIndentsTest002, TestSize.Level1)
{
    auto localPeer = CreatePeerWithTailIndent({TEST_TAIL_INDENT_NEGATIVE});
    ASSERT_NE(accessor_->getTailIndents, nullptr);
    auto testVal = accessor_->getTailIndents(localPeer);
    ASSERT_NE(testVal.tag, InteropTag::INTEROP_TAG_UNDEFINED);
    ASSERT_NE(testVal.value.array, nullptr);
    EXPECT_EQ(testVal.value.length, 1);
    EXPECT_DOUBLE_EQ(testVal.value.array[0], 0.0);
}

/**
 * @tc.name: getTailIndentsTest003
 * @tc.desc: Test array mode with mixed values - negative value should be reset to 0
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getTailIndentsTest003, TestSize.Level1)
{
    auto localPeer = CreatePeerWithTailIndent({TEST_TAIL_INDENT_VALUE_1,
        TEST_TAIL_INDENT_NEGATIVE, TEST_TAIL_INDENT_VALUE_2});
    ASSERT_NE(accessor_->getTailIndents, nullptr);
    auto testVal = accessor_->getTailIndents(localPeer);
    ASSERT_NE(testVal.tag, InteropTag::INTEROP_TAG_UNDEFINED);
    ASSERT_NE(testVal.value.array, nullptr);
    EXPECT_EQ(testVal.value.length, 3);
    EXPECT_DOUBLE_EQ(testVal.value.array[0], TEST_TAIL_INDENT_VALUE_1);
    EXPECT_DOUBLE_EQ(testVal.value.array[1], 0.0);
    EXPECT_DOUBLE_EQ(testVal.value.array[2], TEST_TAIL_INDENT_VALUE_2);
}

/**
 * @tc.name: getTailIndentsTest004
 * @tc.desc: Test percent value validation - should be reset to 0
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphStyleAccessorTest, getTailIndentsTest004, TestSize.Level1)
{
    auto localPeer = CreatePeerWithTailIndent({TEST_TAIL_INDENT_PERCENT_VALUE}, DimensionUnit::PERCENT);
    ASSERT_NE(accessor_->getTailIndents, nullptr);
    auto testVal = accessor_->getTailIndents(localPeer);
    ASSERT_NE(testVal.tag, InteropTag::INTEROP_TAG_UNDEFINED);
    ASSERT_NE(testVal.value.array, nullptr);
    EXPECT_EQ(testVal.value.length, 1);
    EXPECT_DOUBLE_EQ(testVal.value.array[0], 0.0);
}

} // namespace OHOS::Ace::NG
