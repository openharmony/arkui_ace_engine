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

#include "modifier_test_base.h"
#include "core/interfaces/native/implementation/pattern_lock_controller_accessor_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_static.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class PatternLockModifierTest2 : public ModifierTestBase<GENERATED_ArkUIPatternLockModifier,
    &GENERATED_ArkUINodeModifiers::getPatternLockModifier, GENERATED_ARKUI_PATTERN_LOCK> {
};

/**
 * @tc.name: setPatternLockOptionsTest
 * @tc.desc: Check the functionality of PatternLockInterfaceModifier.SetPatternLockOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockModifierTest2, setPatternLockOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPatternLockOptions, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setPatternLockOptions(node_, nullptr);
    auto controllerUndef = Converter::ArkValue<Opt_PatternLockController>();
    modifier_->setPatternLockOptions(node_, &controllerUndef);

    // set the invoke checker to the internal controller
    bool checkInvoke = false;
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto internalController = PatternLockModelStatic::GetController(frameNode);
    ASSERT_NE(internalController, nullptr);
    internalController->SetResetImpl([&checkInvoke]() {
        checkInvoke = true;
    });

    // create the external PatternLockController peer and attach modifier to it
    GeneratedModifier::PatternLockControllerPeerImpl peer;
    auto controller = Converter::ArkValue<Opt_PatternLockController>(&peer);
    modifier_->setPatternLockOptions(node_, &controller);

    // check initial state of invoke checker
    EXPECT_FALSE(checkInvoke);

    // simulate the action from the external peer
    peer.handler->Reset();

    // check the expected state of invoke checker
    EXPECT_TRUE(checkInvoke);
}
} // namespace OHOS::Ace::NG
