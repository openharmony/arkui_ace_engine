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
#include "core/interfaces/native/implementation/click_event_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    const std::vector<std::pair<Ark_Number, int>> accessibilityHoverLocationTestPlan = {
        { Converter::ArkValue<Ark_Number>(5), 5 },
        { Converter::ArkValue<Ark_Number>(2.4), 2 },
        { Converter::ArkValue<Ark_Number>(1), 1 },
        { Converter::ArkValue<Ark_Number>(0), 0 },
        { Converter::ArkValue<Ark_Number>(-1), -1 },
        { Converter::ArkValue<Ark_Number>(-2.4), -2 },
        { Converter::ArkValue<Ark_Number>(-5), -5 },
    };
} // namespace

class ClickEventAccessorTest : public AccessorTestBase<GENERATED_ArkUIClickEventAccessor,
    &GENERATED_ArkUIAccessors::getClickEventAccessor, ClickEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        ASSERT_NE(peer_, nullptr);
        eventInfo_ = std::make_unique<GestureEvent>();
        peer_->SetEventInfo(eventInfo_.get());
    }

    std::unique_ptr<GestureEvent> eventInfo_;
};

/**
 * @tc.name: ClickEventAccessorDisplaySetGetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventAccessorTest, ClickEventAccessorDisplaySetGetXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDisplayX, nullptr);
    ASSERT_NE(accessor_->getDisplayX, nullptr);

    for (auto& [actual, expected] : accessibilityHoverLocationTestPlan) {
        accessor_->setDisplayX(peer_, &actual);
        auto result = Converter::Convert<int>(accessor_->getDisplayX(peer_));
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: ClickEventAccessorDisplaySetGetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventAccessorTest, ClickEventAccessorDisplaySetGetYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDisplayY, nullptr);
    ASSERT_NE(accessor_->getDisplayY, nullptr);

    for (auto& [actual, expected] : accessibilityHoverLocationTestPlan) {
        accessor_->setDisplayY(peer_, &actual);
        auto result = Converter::Convert<int>(accessor_->getDisplayY(peer_));
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: ClickEventAccessorWindowAndScreenSetGetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventAccessorTest, ClickEventAccessorWindowAndScreenSetGetXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setWindowX, nullptr);
    ASSERT_NE(accessor_->getWindowX, nullptr);

    for (auto& [actual, expected] : accessibilityHoverLocationTestPlan) {
        accessor_->setWindowX(peer_, &actual);
        auto result = Converter::Convert<int>(accessor_->getWindowX(peer_));
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: ClickEventAccessorWindowAndScreenSetGetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventAccessorTest, ClickEventAccessorWindowAndScreenSetGetYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setWindowY, nullptr);
    ASSERT_NE(accessor_->getWindowY, nullptr);

    for (auto& [actual, expected] : accessibilityHoverLocationTestPlan) {
        accessor_->setWindowY(peer_, &actual);
        auto result = Converter::Convert<int>(accessor_->getWindowY(peer_));
        EXPECT_EQ(result, expected);
    }
}


/**
 * @tc.name: ClickEventAccessorSetGetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventAccessorTest, ClickEventAccessorSetGetXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setX, nullptr);
    ASSERT_NE(accessor_->getX, nullptr);

    for (auto& [actual, expected] : accessibilityHoverLocationTestPlan) {
        accessor_->setX(peer_, &actual);
        auto result = Converter::Convert<int>(accessor_->getX(peer_));
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: ClickEventAccessorSetGetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventAccessorTest, ClickEventAccessorSetGetYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setY, nullptr);
    ASSERT_NE(accessor_->getY, nullptr);

    for (auto& [actual, expected] : accessibilityHoverLocationTestPlan) {
        accessor_->setY(peer_, &actual);
        auto result = Converter::Convert<int>(accessor_->getY(peer_));
        EXPECT_EQ(result, expected);
    }
}
}