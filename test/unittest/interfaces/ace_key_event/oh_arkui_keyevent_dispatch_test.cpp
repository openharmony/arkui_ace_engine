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

#include "key_event_test.h"

#include "frameworks/core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {

HWTEST_F(KeyEventTest, KeyEvent_Dispatch001, TestSize.Level0)
{
    ArkUI_UIInputEvent* nullEvent = nullptr;

    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(node, nullptr);

    OH_ArkUI_KeyEvent_Dispatch(node, nullEvent);

    EXPECT_EQ(nullEvent, nullptr);

    NodeModel::DisposeNode(node);
}


HWTEST_F(KeyEventTest, OH_ArkUI_KeyEvent_Dispatch002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = C_KEY_EVENT_ID,
        .inputEvent = nullptr,
    };

    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(node, nullptr);

    bool flag = false;
    nodeAPI->registerNodeEvent(node, NODE_DISPATCH_KEY_EVENT, 0, &flag);
    NodeModel::AddNodeEventReceiver(node, [](ArkUI_NodeEvent* event) {
        auto* userData = reinterpret_cast<bool*>(event->userData);
        *userData = true;
    });
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node->uiNodeHandle);
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;

    OH_ArkUI_KeyEvent_Dispatch(node, &event);

    EXPECT_FALSE(flag);

    nodeAPI->unregisterNodeEvent(node, NODE_DISPATCH_KEY_EVENT);
    NodeModel::DisposeNode(node);
}

} // namespace OHOS::Ace
