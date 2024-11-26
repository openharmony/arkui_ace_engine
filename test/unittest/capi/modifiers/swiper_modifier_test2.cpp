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

#include "swiper_modifier_test.h"
#include "modifier_test_base.h"

#include "core/interfaces/native/implementation/swiper_controller_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class SwiperModifierTest2 : public ModifierTestBase<GENERATED_ArkUISwiperModifier,
    &GENERATED_ArkUINodeModifiers::getSwiperModifier, GENERATED_ARKUI_SWIPER> {
};

/**
 * @tc.name: setSwiperOptionsTest
 * @tc.desc: Check the functionality of SwiperInterfaceModifier.SetSwiperOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest2, setSwiperOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSwiperOptions, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setSwiperOptions(node_, nullptr);
    auto controllerUndef = Converter::ArkValue<Opt_SwiperController>();
    modifier_->setSwiperOptions(node_, &controllerUndef);

    // set the invoke checker to the internal controller
    bool checkInvoke = false;
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto internalSwiperController = SwiperModelNG::GetSwiperController(frameNode);
    ASSERT_NE(internalSwiperController, nullptr);
    internalSwiperController->SetShowNextImpl([&checkInvoke]() {
        checkInvoke = true;
    });

    // create the external SwiperController peer and attach modifier to it
    GeneratedModifier::SwiperControllerPeerImpl peer;
    auto controller = Converter::ArkValue<Opt_SwiperController>(&peer);
    modifier_->setSwiperOptions(node_, &controller);

    // check initial state of invoke checker
    EXPECT_FALSE(checkInvoke);

    // simulate the action from the external peer
    peer.TriggerShowNext();

    // check the expected state of invoke checker
    EXPECT_TRUE(checkInvoke);
}
} // namespace OHOS::Ace::NG
