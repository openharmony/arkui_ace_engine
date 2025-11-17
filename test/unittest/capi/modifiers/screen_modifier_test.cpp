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
#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/stubs/mock_window_scene.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace  {
const int SCREEN_ID = 10;
}

class ScreenModifierTest : public ModifierTestBase<GENERATED_ArkUIScreenModifier,
    &GENERATED_ArkUINodeModifiers::getScreenModifier, GENERATED_ARKUI_SCREEN> {
};

/*
 * @tc.name: setScreenOptionsTest
 * @tc.desc: test fucntion of setScreenOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScreenModifierTest, setScreenOptionsTest, TestSize.Level1)
{
    Ark_Number screenId = Converter::ArkValue<Ark_Number>(SCREEN_ID);
    modifier_->setScreenOptions(node_, &screenId);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScreenPattern>();
    ASSERT_NE(pattern, nullptr);
    auto session = pattern->GetScreenSession();
    ASSERT_NE(session, nullptr);
    auto id = session->GetScreenId();
    EXPECT_EQ(id, SCREEN_ID);
}

} // namespace OHOS::Ace::NG
