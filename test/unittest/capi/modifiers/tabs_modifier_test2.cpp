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
#include "swiper_modifier_test.h"

#include "core/interfaces/arkoala/implementation/tabs_controller_modifier_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class TabsModifierTest2 : public ModifierTestBase<GENERATED_ArkUITabsModifier,
    &GENERATED_ArkUINodeModifiers::getTabsModifier, GENERATED_ARKUI_TABS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<TabTheme>();
    }
};
/**
 * @tc.name: setTabsOptionsTest
 * @tc.desc: Check the functionality of TabsInterfaceModifier.SetTabsOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(TabsModifierTest2, setTabsOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTabsOptions, nullptr);

    Type_TabsInterface_setTabsOptions_Arg0 options = {
        .barPosition = Converter::ArkValue<Opt_BarPosition>(Ark_Empty()),
        .controller = Converter::ArkValue<Opt_TabsController>(Ark_Empty()),
        .index = Converter::ArkValue<Opt_Number>(Ark_Empty())
    };
    auto optionsOpt = Converter::ArkValue<Opt_Type_TabsInterface_setTabsOptions_Arg0>(options);

    // assume nothing bad with invalid and empty options
    modifier_->setTabsOptions(node_, nullptr);
    auto optionsUndef = Converter::ArkValue<Opt_Type_TabsInterface_setTabsOptions_Arg0>(Ark_Empty());
    modifier_->setTabsOptions(node_, &optionsUndef);
 
    // set the invoke checker INTO the internal controller
    bool checkInvoke = false;
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto internalSwiperController = TabsModelNG::GetSwiperController(frameNode);
    ASSERT_NE(internalSwiperController, nullptr);
    internalSwiperController->SetSwipeToImpl([&checkInvoke](int32_t, bool) {
        checkInvoke = true;
    });

    // create the external TabsController peer and attach it to modifier
    GeneratedModifier::TabsControllerPeerImpl peer;
    optionsOpt.value.controller = Converter::ArkValue<Opt_TabsController>(&peer);
    modifier_->setTabsOptions(node_, &optionsOpt);

    // check initial state of invoke checker
    EXPECT_FALSE(checkInvoke);

    // simulate the action from the external peer
    peer.TriggerChangeIndex(1);

    // check the expected state of invoke checker
    EXPECT_TRUE(checkInvoke);
}
} // namespace OHOS::Ace::NG
