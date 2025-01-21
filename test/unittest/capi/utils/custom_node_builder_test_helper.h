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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
class ICustomNodeBuilderTestHelper {
public:
    virtual ~ICustomNodeBuilderTestHelper() = default;
    virtual void TestFunction(Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                              const Callback_Pointer_Void continuation) = 0;
};

class TestHelperManager {
public:
    static TestHelperManager& GetInstance()
    {
        static TestHelperManager instance;
        return instance;
    }

    static int32_t Register(ICustomNodeBuilderTestHelper* helper)
    {
        if (helper != nullptr) {
            auto& instances = GetInstance().instances_;
            int32_t uniqueId;
            if (!instances.empty()) {
                // Find the maximum key in the map
                uniqueId = std::max_element(instances.begin(), instances.end(),
                    [](const std::pair<int32_t, ICustomNodeBuilderTestHelper*>& a,
                       const std::pair<int32_t, ICustomNodeBuilderTestHelper*>& b) {
                        return a.first < b.first;
                    })->first + 1;
            } else {
                uniqueId = 1;
            }
            instances[uniqueId] = helper;
            return uniqueId;
        }
        return 0;
    }

    static void Unregister(int32_t uniqueId)
    {
        auto instances = GetInstance().instances_;
        auto it = instances.find(uniqueId);
        if (it != instances.end()) {
            instances.erase(it);
        }
    }

    ICustomNodeBuilderTestHelper* GetHelperById(int32_t uniqueId)
    {
        auto it = instances_.find(uniqueId);
        if (it != instances_.end()) {
            return it->second;
        }
        return nullptr;
    }

private:
    TestHelperManager() {}
    ~TestHelperManager() {}
    std::unordered_map<int32_t, ICustomNodeBuilderTestHelper*> instances_;
    TestHelperManager(const TestHelperManager&) = delete;
    TestHelperManager& operator=(const TestHelperManager&) = delete;
};

template<typename T>
class CustomNodeBuilderTestHelper : public ICustomNodeBuilderTestHelper {
public:
    CustomNodeBuilderTestHelper(T* testClassObject, FrameNode* parentNode)
        : testClassObject_(testClassObject),
        expectedParentNode_(parentNode),
        expectedCustomNode_(testClassObject->CreateNode()),
        uniqueId_(TestHelperManager::Register(this))
        {}

    ~CustomNodeBuilderTestHelper()
    {
        TestHelperManager::Unregister(uniqueId_);
        if (testClassObject_ && expectedCustomNode_) {
            testClassObject_->DisposeNode(expectedCustomNode_);
        }
        expectedParentNode_ = nullptr;
        testClassObject_ = nullptr;
        syncCallbackCounter_ = 0;
        asyncCallbackCounter_ = 0;
    }

    int GetCallsCount() const
    {
        return syncCallbackCounter_;
    }

    CustomNodeBuilder GetBuilder()
    {
        CustomNodeBuilder builder = {
            .resource = {.resourceId = uniqueId_, .hold = nullptr, .release = nullptr},
            .callSync = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                const Callback_Pointer_Void continuation) {
                auto testHelper = TestHelperManager::GetInstance().GetHelperById(resourceId);
                if (testHelper) {
                    testHelper->TestFunction(context, resourceId, parentNode, continuation);
                } else {
                    ASSERT_EQ(testHelper, nullptr);
                }
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

    void TestFunction(Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                    const Callback_Pointer_Void continuation)
    {
        syncCallbackCounter_++;
        EXPECT_EQ(reinterpret_cast<FrameNode*>(parentNode), expectedParentNode_);
        CallbackHelper(continuation).Invoke(reinterpret_cast<Ark_NativePointer>(expectedCustomNode_));
    }

private:
    T* testClassObject_;
    FrameNode* expectedParentNode_;
    Ark_NodeHandle expectedCustomNode_;
    int syncCallbackCounter_ = 0;
    int asyncCallbackCounter_ = 0;
    const int32_t uniqueId_;
};

} // OHOS::Ace::NG

#endif // CUSTOM_NODE_BUILDER_TEST_HELPER_H