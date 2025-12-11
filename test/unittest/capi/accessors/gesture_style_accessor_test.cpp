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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/gesture_style_peer.h"
#include "accessor_test_base.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

static bool g_onClick = false;
static bool g_onLongPress = false;

class GestureStyleAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIGestureStyleAccessor,
        &GENERATED_ArkUIAccessors::getGestureStyleAccessor, GestureStylePeer> {
public:
    void* CreatePeerInstance() override
    {
        Ark_Int32 resId = 1;
        auto onClick = [](const Ark_Int32 resourceId, const Ark_ClickEvent event) {
            g_onClick = true;
        };
        param_.value.onClick.value = Converter::ArkValue<Callback_ClickEvent_Void>(onClick, resId);

        auto onLongPress = [](const Ark_Int32 resourceId, const Ark_GestureEvent event) {
            g_onLongPress = true;
        };
        param_.value.onLongPress.value = Converter::ArkValue<Callback_GestureEvent_Void>(onLongPress, resId);
        return accessor_->construct(&param_);
    }

    Opt_GestureStyleInterface param_;
};

/**
 * @tc.name: callbacksTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureStyleAccessorTest, callbacksTest, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    auto style = peer_->span->GetGestureStyle();
    EXPECT_NE(style.onClick, nullptr);
    EXPECT_NE(style.onLongPress, nullptr);
}

} // namespace OHOS::Ace::NG