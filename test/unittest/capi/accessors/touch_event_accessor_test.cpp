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
#include "core/interfaces/native/implementation/touch_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class TouchEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUITouchEventAccessor,
        &GENERATED_ArkUIAccessors::getTouchEventAccessor, TouchEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        eventInfo_ = std::make_unique<TouchEventInfo>("unknown");
        peer_->SetEventInfo(eventInfo_.get());
    }

private:
    std::unique_ptr<TouchEventInfo> eventInfo_;
};

/**
 * @tc.name: GetStopPropagationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventAccessorTest, GetStopPropagationTest, TestSize.Level1)
{
    TouchEventInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    Callback_Void callback = accessor_->getStopPropagation(peer_);
    auto callbackHelper = CallbackHelper(callback);
    eventInfo->SetStopPropagation(false);
    EXPECT_FALSE(eventInfo->IsStopPropagation());
    callbackHelper.Invoke();
    EXPECT_TRUE(eventInfo->IsStopPropagation());
    CallbackKeeper::ReleaseReverseCallback<Callback_Void>(callback);
}

/**
 * @tc.name: GetPreventDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventAccessorTest, GetPreventDefaultTest, TestSize.Level1)
{
    TouchEventInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    Callback_Void callback = accessor_->getPreventDefault(peer_);
    auto callbackHelper = CallbackHelper(callback);

    auto checkWithName = [eventInfo, &callbackHelper](const std::string& patternName, bool expected) {
        eventInfo->SetPatternName(patternName);
        eventInfo->SetPreventDefault(false);
        EXPECT_FALSE(eventInfo->IsPreventDefault());
        callbackHelper.Invoke();
        EXPECT_EQ(eventInfo->IsPreventDefault(), expected);
    };

    checkWithName("Checkbox", true);
    checkWithName("RichEditor", false);
    checkWithName("Grid", false);
    checkWithName("Hyperlink", true);

    CallbackKeeper::ReleaseReverseCallback<Callback_Void>(callback);
}

}