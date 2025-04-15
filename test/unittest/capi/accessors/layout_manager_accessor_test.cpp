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
#include "node_api.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/layout_manager_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace Converter {
template<>
void AssignCast(std::optional<Ace::TextDirection>& dst, const Ark_TextDirection& src)
{
    switch (src) {
        case Ark_TextDirection::ARK_TEXT_DIRECTION_LTR: dst = Ace::TextDirection::LTR; break;
        case Ark_TextDirection::ARK_TEXT_DIRECTION_RTL: dst = Ace::TextDirection::RTL; break;
        default:
            LOGE("Unexpected enum value in Ace::TextDirection: %{public}d", src);
            break;
    }
}
template<>
NG::RectF Convert(const Ark_Rect& src)
{
    auto left = Converter::Convert<float>(src.left);
    auto top = Converter::Convert<float>(src.top);
    auto right = Converter::Convert<float>(src.right);
    auto bottom = Converter::Convert<float>(src.bottom);
    return NG::RectF(left, top, right - left, bottom - top);
}
template<>
ParagraphManager::TextBox Convert(const Ark_TextBox& src)
{
    ParagraphManager::TextBox dst;
    dst.rect_ = Converter::Convert<NG::RectF>(src.rect);
    dst.direction_ = Converter::OptConvert<TextDirection>(src.direction).value_or(TextDirection::LTR);
    return dst;
}
template<>
TextLineMetrics Convert(const Ark_LineMetrics& src)
{
    TextLineMetrics dst;
    dst.startIndex = Converter::Convert<int32_t>(src.startIndex);
    dst.endIndex = Converter::Convert<int32_t>(src.endIndex);
    dst.ascender = Converter::Convert<float>(src.ascent);
    dst.descender = Converter::Convert<float>(src.descent);
    dst.height = Converter::Convert<float>(src.height);
    dst.x = Converter::Convert<float>(src.left);
    dst.baseline = Converter::Convert<float>(src.baseline);
    dst.lineNumber = Converter::Convert<int32_t>(src.lineNumber);
    dst.y = Converter::Convert<float>(src.topHeight);
    return dst;
}
template<>
void AssignCast(std::optional<Ace::TextAffinity>& dst, const Ark_Affinity& src)
{
    switch (src) {
        case ARK_AFFINITY_UPSTREAM: dst = Ace::TextAffinity::UPSTREAM; break;
        case ARK_AFFINITY_DOWNSTREAM: dst = Ace::TextAffinity::DOWNSTREAM; break;
        default:
            LOGE("Unexpected enum value in Ark_Affinity: %{public}d", src);
            break;
    }
}
template<>
PositionWithAffinity Convert(const Ark_PositionWithAffinity& src)
{
    auto position = Converter::Convert<int32_t>(src.position);
    auto affinity = Converter::OptConvert<Ace::TextAffinity>(src.affinity).value_or(Ace::TextAffinity::UPSTREAM);
    return PositionWithAffinity(position, affinity);
}
} // namespace Converter
namespace {
const std::string g_message = "message";
const int32_t EXPECTED_X = 33;
const int32_t EXPECTED_Y = 55;
const RectF EXPECTED_RECTF_1 = RectF(1.0, 2.0, 3.0, 4.0);
const RectF EXPECTED_RECTF_2 = RectF(5.0, 6.0, 7.0, 8.0);
const TextLineMetrics EXPECTED_METRICS = {
    .startIndex = 1,
    .endIndex = 10,
    .ascender = -100,
    .descender = 100,
    .baseline = 32.17,
    .height = 74.08,
    .x = 12.34,
    .y = 56.73,
    .lineNumber = 5,
};
const TextLineMetrics ERROR_METRICS = {
    .startIndex = 0,
    .endIndex = 0,
    .ascender = -1,
    .descender = -1,
    .baseline = -1,
    .height = -1,
    .x = -1.0,
    .y = -1.0,
    .lineNumber = 0,
};
const double FLT_PRECISION = 0.001;

class MockLayoutInfoInterface : public OHOS::Ace::NG::LayoutInfoInterface {
public:
    MockLayoutInfoInterface() = default;
    ~MockLayoutInfoInterface() override = default;

    MOCK_METHOD(OHOS::Ace::NG::PositionWithAffinity, GetGlyphPositionAtCoordinate, (int32_t, int32_t), ());
    MOCK_METHOD(OHOS::Ace::TextLineMetrics, GetLineMetrics, (int32_t), ());
    MOCK_METHOD(std::vector<ParagraphManager::TextBox>, GetRectsForRange,
        (int32_t, int32_t, Ace::RectHeightStyle, Ace::RectWidthStyle), ());
};
} // namespace
class LayoutManagerAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUILayoutManagerAccessor,
    &GENERATED_ArkUIAccessors::getLayoutManagerAccessor, LayoutManagerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        handlerKeeper_ = AceType::MakeRefPtr<MockLayoutInfoInterface>();
        peer_->handler = handlerKeeper_;
    }
    void* CreatePeerInstance() override
    {
        return accessor_->ctor();
    }
    void TearDown() override
    {
        AccessorTestCtorBase::TearDown();
        handlerKeeper_ = nullptr;
    }

    RefPtr<MockLayoutInfoInterface> handlerKeeper_ = nullptr;
};
/**
 * @tc.name: getLineCountTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, getLineCountTest, TestSize.Level1)
{
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    auto value = Converter::Convert<int32_t>(accessor_->getLineCount(peer_));
    ASSERT_EQ(value, 0);
    value = Converter::Convert<int32_t>(accessor_->getLineCount(nullptr));
    ASSERT_EQ(value, 0);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, GetGlyphPositionAtCoordinate, TestSize.Level1)
{
    ASSERT_NE(accessor_->getGlyphPositionAtCoordinate, nullptr);

    auto actualX = Converter::ArkValue<Ark_Number>(EXPECTED_X);
    auto actualY = Converter::ArkValue<Ark_Number>(EXPECTED_Y);
    auto target = PositionWithAffinity(32, TextAffinity::DOWNSTREAM);
    auto targetError = PositionWithAffinity(1111, static_cast<TextAffinity>(-1));

    ON_CALL(*handlerKeeper_, GetGlyphPositionAtCoordinate(_, _)).WillByDefault(Return(targetError));
    EXPECT_CALL(*handlerKeeper_, GetGlyphPositionAtCoordinate(EXPECTED_X, EXPECTED_Y)).WillOnce(Return(target));
    Ark_PositionWithAffinity result = accessor_->getGlyphPositionAtCoordinate(peer_, &actualX, &actualY);

    PositionWithAffinity position = Converter::Convert<PositionWithAffinity>(result);
    EXPECT_EQ(position.position_, target.position_);
    EXPECT_EQ(position.affinity_, target.affinity_);
}

/**
 * @tc.name: GetLineMetrics
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, GetLineMetrics, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLineMetrics, nullptr);

    auto actual = Converter::ArkValue<Ark_Number>(EXPECTED_X);
    TextLineMetrics target = EXPECTED_METRICS;
    TextLineMetrics targetError = ERROR_METRICS;

    ON_CALL(*handlerKeeper_, GetLineMetrics(_)).WillByDefault(Return(targetError));
    EXPECT_CALL(*handlerKeeper_, GetLineMetrics(EXPECTED_X)).WillOnce(Return(target));
    auto result = accessor_->getLineMetrics(peer_, &actual);

    auto lineMetrics = Converter::Convert<TextLineMetrics>(result);
    EXPECT_EQ(lineMetrics.startIndex, EXPECTED_METRICS.startIndex);
    EXPECT_EQ(lineMetrics.endIndex, EXPECTED_METRICS.endIndex);
    EXPECT_EQ(lineMetrics.lineNumber, EXPECTED_METRICS.lineNumber);
    EXPECT_NEAR(lineMetrics.ascender, EXPECTED_METRICS.ascender, FLT_PRECISION);
    EXPECT_NEAR(lineMetrics.descender, EXPECTED_METRICS.descender, FLT_PRECISION);
    EXPECT_NEAR(lineMetrics.height, EXPECTED_METRICS.height, FLT_PRECISION);
    EXPECT_NEAR(lineMetrics.x, EXPECTED_METRICS.x, FLT_PRECISION);
    EXPECT_NEAR(lineMetrics.y, EXPECTED_METRICS.y, FLT_PRECISION);
    EXPECT_NEAR(lineMetrics.baseline, EXPECTED_METRICS.baseline, FLT_PRECISION);
}

/**
 * @tc.name: GetRectsForRange
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, GetRectsForRange, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRectsForRange, nullptr);

    Ark_TextRange range { .start = Converter::ArkValue<Opt_Number>(EXPECTED_X),
        .end = Converter::ArkValue<Opt_Number>(EXPECTED_Y) };
    Ark_RectWidthStyle styleW = ARK_RECT_WIDTH_STYLE_MAX;
    Ark_RectHeightStyle styleH = ARK_RECT_HEIGHT_STYLE_STRUT;
    auto actualW = RectWidthStyle::MAX;
    auto actualH = RectHeightStyle::STRUT;
    ParagraphManager::TextBox item(EXPECTED_RECTF_1, TextDirection::LTR);
    ParagraphManager::TextBox item2(EXPECTED_RECTF_2, TextDirection::RTL);
    std::vector<ParagraphManager::TextBox> target = { item, item2 };
    std::vector<ParagraphManager::TextBox> targetError;

    ON_CALL(*handlerKeeper_, GetRectsForRange(_, _, _, _)).WillByDefault(Return(targetError));
    EXPECT_CALL(*handlerKeeper_, GetRectsForRange(EXPECTED_X, EXPECTED_Y, actualH, actualW)).WillOnce(Return(target));
    auto result = accessor_->getRectsForRange(peer_, &range, styleW, styleH);

    std::vector<ParagraphManager::TextBox> rects = Converter::Convert<std::vector<ParagraphManager::TextBox>>(result);
    ASSERT_EQ(rects.size(), target.size());
    for (size_t i = 0; i < target.size(); i++) {
        ASSERT_EQ(rects[i].rect_, target[i].rect_);
        ASSERT_EQ(rects[i].direction_, target[i].direction_);
    }
}
} // namespace OHOS::Ace::NG
