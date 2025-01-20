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

#ifndef CUSTOM_NODE_BUILDER_TEST_HELPER_H
#define CUSTOM_NODE_BUILDER_TEST_HELPER_H

#include <utility>
#include "gtest/gtest.h"
#include "arkoala_api_generated.h"
#include "test/unittest/capi/modifiers/modifier_test_base.h"
#include "core/interfaces/native/common/extension_companion_node.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
template<typename T>
class CustomNodeBuilderTestHelper {
public:
    explicit CustomNodeBuilderTestHelper(T* testClassObject, FrameNode* parentNode)
        : testClassObject_(testClassObject),
        expectedParentNode_(parentNode),
        expectedCustomNode_(testClassObject->CreateNode())
        {}

    ~CustomNodeBuilderTestHelper()
    {
        testClassObject_->DisposeNode(expectedCustomNode_);
        expectedParentNode_ = nullptr;
        testClassObject_ = nullptr;
    }

    void operator()(Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                    const Callback_Pointer_Void continuation)
    {
        callbackCounter_++;
        EXPECT_EQ(reinterpret_cast<FrameNode*>(parentNode), expectedParentNode_);
        CallbackHelper(continuation).Invoke(reinterpret_cast<Ark_NativePointer>(expectedCustomNode_));
    }

    int GetCallsCount() const
    {
        return callbackCounter_;
    }

    CustomNodeBuilder GetBuilder()
    {
        static CustomNodeBuilderTestHelper* builderFunctor = this;
        CustomNodeBuilder builder = {
            .callSync = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                const Callback_Pointer_Void continuation) {
                (*builderFunctor)(context, resourceId, parentNode, continuation);
            }
        };
        return builder;
    }

    Ark_NodeHandle GetCustomNodeHandle() const
    {
        return expectedCustomNode_;
    }

    FrameNode* GetCustomNode() const
    {
        return reinterpret_cast<FrameNode*>(expectedCustomNode_);
    }

private:
    T* testClassObject_;
    FrameNode* expectedParentNode_;
    Ark_NodeHandle expectedCustomNode_;
    int callbackCounter_ = 0;
};
}
#endif // CUSTOM_NODE_BUILDER_TEST_HELPER_H