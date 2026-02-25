/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "gmock/gmock.h"

#include "core/components_ng/pattern/node_container/node_container_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const int64_t TEST_NODE_ID = 1001;
const int32_t TEST_FLAGS = 0;
} // namespace

class NodeContainerOpsAccessorTest : public StaticAccessorTest<GENERATED_ArkUINodeContainerOpsAccessor,
    &GENERATED_ArkUIAccessors::getNodeContainerOpsAccessor> {
};

/**
 * @tc.name: setOnDestoryEventTest
 * @tc.desc: Test SetOnDestoryEvent callback invocation with nodeId converted to Ark_Float64
 * @tc.type: FUNC
 */
HWTEST_F(NodeContainerOpsAccessorTest, setOnDestoryEventTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setOnDestoryEvent, nullptr);

    // Create a node container using the accessor's construct function
    Ark_NativePointer nodePtr = accessor_->nodeContainerOpsConstruct(TEST_NODE_ID, TEST_FLAGS);
    ASSERT_NE(nodePtr, nullptr);

    auto* frameNode = reinterpret_cast<FrameNode*>(nodePtr);
    ASSERT_NE(frameNode, nullptr);

    // Prepare callback verification
    static std::optional<int64_t> receivedNodeId;
    receivedNodeId.reset();
    // According to arkoala_api_generated.h, Callback_OnDestory_Void expects Ark_Int64 nodeId
    // Implementation passes Converter::ArkValue<Ark_Float64>(nodeId), need to handle conversion
    auto callbackCall = [](const Ark_Int32 resourceId, const Ark_Int64 nodeId) {
        receivedNodeId = Converter::Convert<int64_t>(nodeId);
    };

    // Create Ark callback with both async and sync functions
    auto arkCallback = Converter::ArkCallback<Callback_OnDestory_Void>(callbackCall);

    // Set the callback
    accessor_->setOnDestoryEvent(nodePtr, &arkCallback);

    // Verify callback was set
    EXPECT_TRUE(frameNode->HasOnNodeDestroyCallback());

    // Trigger the node destroy callback
    frameNode->FireOnNodeDestroyCallback();

    // Verify callback was invoked with correct nodeId
    ASSERT_TRUE(receivedNodeId.has_value());

    EXPECT_EQ(receivedNodeId, TEST_NODE_ID);
}

} // namespace OHOS::Ace::NG