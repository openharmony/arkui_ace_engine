/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/implementation/web_controller_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "test/unittest/capi/stubs/mock_web_pattern.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class WebModifierTest : public ModifierTestBase<GENERATED_ArkUIWebModifier,
    &GENERATED_ArkUINodeModifiers::getWebModifier, GENERATED_ARKUI_WEB> {
};

/*
 * @tc.name: setOptionsWebControllerTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setOptionsWebControllerTestValidValues, TestSize.Level1)
{
    Ark_WebOptions options;
    options.incognitoMode = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    options.renderMode = Converter::ArkValue<Opt_RenderMode>(Ark_Empty());
    options.sharedRenderProcessToken = Converter::ArkValue<Opt_String>(Ark_Empty());
    options.src = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>("src");

    Ark_NativePointer controllerPtr =
        GeneratedModifier::GetFullAPI()->getAccessors()->getWebControllerAccessor()->ctor();
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::WebControllerPeerImpl*>(controllerPtr);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(pattern, nullptr);

    Ark_WebController arkController;
    arkController.ptr = controllerPtr;
    options.controller =
        Converter::ArkUnion<Ark_Union_WebController_WebviewController, Ark_WebController>(arkController);

    RefPtr<WebController> controller = pattern->GetWebController();
    EXPECT_EQ(controller, nullptr);

    modifier_->setWebOptions(node_, &options);

    controller = pattern->GetWebController();
    EXPECT_NE(controller, nullptr);
    EXPECT_EQ(peerImplPtr->GetController(), controller);

    Ark_NativePointer finalizerPtr =
        GeneratedModifier::GetFullAPI()->getAccessors()->getWebControllerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(WebControllerPeer *)>(finalizerPtr);
    EXPECT_NE(finalyzer, nullptr);
    finalyzer(reinterpret_cast<WebControllerPeer *>(controllerPtr));
}

} // namespace OHOS::Ace::NG