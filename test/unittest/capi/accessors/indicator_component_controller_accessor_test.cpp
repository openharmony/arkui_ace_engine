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
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"
#include "core/interfaces/native/implementation/indicator_component_controller_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
class MockIndicatorController : public IndicatorController {
public:
    MOCK_METHOD(void, ShowPrevious, (), (const));
    MOCK_METHOD(void, ShowNext, (), (const));
    MOCK_METHOD(void, ChangeIndex, (int32_t index, bool useAnimation), (const));
};
} // namespace

class IndicatorComponentControllerAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIIndicatorComponentControllerAccessor,
    &GENERATED_ArkUIAccessors::getIndicatorComponentControllerAccessor, IndicatorComponentControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        mockIndicatorController_ = AceType::MakeRefPtr<MockIndicatorController>();
        ASSERT_NE(mockIndicatorController_, nullptr);

        ASSERT_NE(peer_, nullptr);
        RefPtr<OHOS::Ace::NG::FrameNode> frameNode = nullptr;
        peer_->SetController(mockIndicatorController_, frameNode);
    }

    void TearDown() override
    {
        mockIndicatorController_ = nullptr;
    }

    RefPtr<MockIndicatorController> mockIndicatorController_ = nullptr;
};

/**
 * @tc.name: showNextTest
 * @tc.desc: Check the functionality of IndicatorComponentControllerAccessor.showNext
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentControllerAccessorTest, showNextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showNext, nullptr);

    EXPECT_CALL(*mockIndicatorController_, ShowNext()).Times(1);
    accessor_->showNext(peer_);
}

/**
 * @tc.name: showPreviousTest
 * @tc.desc: Check the functionality of IndicatorComponentControllerAccessor.showPrevious
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentControllerAccessorTest, showPreviousTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showPrevious, nullptr);

    EXPECT_CALL(*mockIndicatorController_, ShowPrevious()).Times(1);
    accessor_->showPrevious(peer_);
}

/**
 * @tc.name: changeIndexTest
 * @tc.desc: Check the functionality of IndicatorComponentControllerAccessor.changeIndex
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentControllerAccessorTest, DISABLED_changeIndexTest, TestSize.Level1)
{
    constexpr int indexValidValue = 10;

    ASSERT_NE(accessor_->changeIndex, nullptr);

    auto arkNumValid = ArkValue<Opt_Int32>(indexValidValue);
    auto arkNumInvalid = ArkValue<Opt_Int32>(INT_MIN);
    auto optBoolTrue = ArkValue<Opt_Boolean>(true);
    auto optBoolFalse = ArkValue<Opt_Boolean>(false);
    auto optBoolUndef = ArkValue<Opt_Boolean>();

    EXPECT_CALL(*mockIndicatorController_, ChangeIndex(indexValidValue, true)).Times(1);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolTrue);

    EXPECT_CALL(*mockIndicatorController_, ChangeIndex(indexValidValue, false)).Times(3);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolFalse);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolUndef);
    accessor_->changeIndex(peer_, &arkNumValid, nullptr);

    EXPECT_CALL(*mockIndicatorController_, ChangeIndex(0, false)).Times(1);
    accessor_->changeIndex(peer_, &arkNumInvalid, nullptr);
}
} // namespace OHOS::Ace::NG