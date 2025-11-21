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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/layout_manager_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace Converter {
template<>
PositionWithAffinity Convert(const Ark_PositionWithAffinity& src)
{
    auto position = Converter::Convert<int32_t>(src.position);
#ifdef WRONG_SDK
    auto affinity = Converter::OptConvert<Ace::TextAffinity>(src.affinity).value_or(Ace::TextAffinity::UPSTREAM);
#else
    auto affinity = Ace::TextAffinity::UPSTREAM;
#endif
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
        return accessor_->construct();
    }
    void TearDown() override
    {
        AccessorTestCtorBase::TearDown();
        handlerKeeper_ = nullptr;
    }

    RefPtr<MockLayoutInfoInterface> handlerKeeper_ = nullptr;
};

/**
 * @tc.name: getLineCountTest01
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, getLineCountTest01, TestSize.Level1)
{
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    auto value = Converter::OptConvert<int32_t>(accessor_->getLineCount(peer_));
    ASSERT_EQ(value, 0);
    value = Converter::OptConvert<int32_t>(accessor_->getLineCount(nullptr));
    ASSERT_EQ(value, std::nullopt);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate01
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, GetGlyphPositionAtCoordinate01, TestSize.Level1)
{
    ASSERT_NE(accessor_->getGlyphPositionAtCoordinate, nullptr);

    auto actualX = Converter::ArkValue<Ark_Float64>(EXPECTED_X);
    auto actualY = Converter::ArkValue<Ark_Float64>(EXPECTED_Y);

    auto target = PositionWithAffinity(32, TextAffinity::DOWNSTREAM);
    auto targetError = PositionWithAffinity(1111, static_cast<TextAffinity>(-1));

    ON_CALL(*handlerKeeper_, GetGlyphPositionAtCoordinate(_, _)).WillByDefault(Return(targetError));
    EXPECT_CALL(*handlerKeeper_, GetGlyphPositionAtCoordinate(EXPECTED_X, EXPECTED_Y)).WillOnce(Return(target));

    auto result = accessor_->getGlyphPositionAtCoordinate(peer_, actualX, actualY);
#ifdef WRONG_GEN
    auto resultArk = Converter::GetOpt(resultOpt);
    ASSERT_TRUE(resultArk.has_value());
    auto result = resultArk.value();
#endif
    PositionWithAffinity position = Converter::Convert<PositionWithAffinity>(result);
    EXPECT_EQ(position.position_, target.position_);
#ifdef WRONG_SDK
    EXPECT_EQ(position.affinity_, target.affinity_);
#endif
}
} // namespace OHOS::Ace::NG
