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
#include "core/interfaces/native/implementation/accessiblt_hover_event_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::vector<std::pair<Ark_AccessibilityHoverType, AccessibilityHoverAction>> accessibilityHoverTypeTestPlan = {
    { ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_ENTER, AccessibilityHoverAction::HOVER_ENTER },
    { ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_MOVE, AccessibilityHoverAction::HOVER_MOVE },
    { ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_EXIT, AccessibilityHoverAction::HOVER_EXIT },
    { ARK_ACCESSIBILITY_HOVER_TYPE_HOVER_CANCEL, AccessibilityHoverAction::HOVER_CANCEL },
};
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

class AccessibilityHoverEventAccessorTest : public AccessorTestBase<GENERATED_ArkUIAccessibilityHoverEventAccessor,
    &GENERATED_ArkUIAccessors::getAccessibilityHoverEventAccessor, AccessibilityHoverEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        ASSERT_NE(peer_, nullptr);
        eventInfo_ = std::make_unique<AccessibilityHoverInfo>();
        peer_->SetEventInfo(eventInfo_.get());
    }

    std::unique_ptr<AccessibilityHoverInfo> eventInfo_;
};

/**
 * @tc.name: accessibilityHoverEventAcrGetTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverEventAccessorTest, DISABLED_accessibilityHoverEventAcrGetTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getType, nullptr);
}

/**
 * @tc.name: accessibilityHoverEventAcrSetTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverEventAccessorTest, accessibilityHoverEventAcrSetTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setType, nullptr);

    for (auto& [actual, expected] : accessibilityHoverTypeTestPlan) {
        accessor_->setType(peer_, actual);
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        EXPECT_EQ(info->GetActionType(), expected);
    }
}

/**
 * @tc.name: accessibilityHoverEventAcrSetGetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverEventAccessorTest, accessibilityHoverEventAcrSetGetXTest, TestSize.Level1)
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
 * @tc.name: accessibilityHoverEventAcrSetGetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverEventAccessorTest, accessibilityHoverEventAcrSetGetYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setY, nullptr);
    ASSERT_NE(accessor_->getY, nullptr);

    for (auto& [actual, expected] : accessibilityHoverLocationTestPlan) {
        accessor_->setY(peer_, &actual);
        auto result = Converter::Convert<int>(accessor_->getY(peer_));
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: accessibilityHoverEventAcrDisplaySetGetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverEventAccessorTest, accessibilityHoverEventAcrDisplaySetGetXTest, TestSize.Level1)
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
 * @tc.name: accessibilityHoverEventAcrDisplaySetGetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverEventAccessorTest, accessibilityHoverEventAcrDisplaySetGetYTest, TestSize.Level1)
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
 * @tc.name: accessibilityHoverEventAcrWindowSetGetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverEventAccessorTest, accessibilityHoverEventAcrWindowSetGetXTest, TestSize.Level1)
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
 * @tc.name: accessibilityHoverEventAcrWindowSetGetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverEventAccessorTest, accessibilityHoverEventAcrWindowSetGetYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setWindowY, nullptr);
    ASSERT_NE(accessor_->getWindowY, nullptr);

    for (auto& [actual, expected] : accessibilityHoverLocationTestPlan) {
        accessor_->setWindowY(peer_, &actual);
        auto result = Converter::Convert<int>(accessor_->getWindowY(peer_));
        EXPECT_EQ(result, expected);
    }
}
}