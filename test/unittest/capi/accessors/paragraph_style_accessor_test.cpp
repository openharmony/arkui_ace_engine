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

#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/interfaces/native/implementation/length_metrics_peer.h"
#include "frameworks/core/interfaces/native/implementation/paragraph_style_peer.h"
#include "frameworks/core/components_ng/pattern/text/span/span_object.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "frameworks/core/interfaces/native/utility/callback_helper.h"
#include "frameworks/core/interfaces/native/utility/converter.h"
#include "frameworks/core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

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
}

class ParagraphStyleAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIParagraphStyleAccessor,
        &GENERATED_ArkUIAccessors::getParagraphStyleAccessor, ParagraphStylePeer> {
public:
    ~ParagraphStyleAccessorTest() override
    {
        if (param_.value.textIndent.value) {
            delete param_.value.textIndent.value;
            param_.value.textIndent.value = nullptr;
        }

        if (margin_) {
            delete margin_;
            margin_ = nullptr;
        }
    }
    void* CreatePeerInstance() override
    {
        param_.value.textAlign = Converter::ArkValue<Opt_TextAlign>(TEST_TEXT_ALIGN);
        param_.value.textIndent.value = LengthMetricsPeer::Create(Dimension(TEST_MARGIN));
        param_.value.maxLines = Converter::ArkValue<Opt_Number>(TEST_LINES_NUM);
        param_.value.overflow = Converter::ArkValue<Opt_TextOverflow>(TEST_TEXT_OVERFLOW);
        param_.value.wordBreak = Converter::ArkValue<Opt_WordBreak>(TEST_WORD_BREAK);
        margin_ = LengthMetricsPeer::Create(Dimension(TEST_MARGIN_2));
        param_.value.leadingMargin.value =
            Converter::ArkUnion<Ark_Union_LengthMetrics_LeadingMarginPlaceholder, Ark_LengthMetrics>(margin_);
        return accessor_->ctor(&param_);
    }

private:
    Opt_ParagraphStyleInterface param_ = {};
    Ark_LengthMetrics margin_ = nullptr;
};

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
    EXPECT_EQ(testVal, converted);
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
    auto converted = Converter::Convert<int>(testVal);
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
    auto converted = Converter::Convert<int>(testVal);
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
    EXPECT_EQ(testVal, converted);
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
    EXPECT_EQ(testVal, converted);
}
} // namespace OHOS::Ace::NG