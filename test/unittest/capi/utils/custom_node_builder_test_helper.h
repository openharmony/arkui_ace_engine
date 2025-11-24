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

#ifndef CUSTOM_NODE_BUILDER_TEST_HELPER_H
#define CUSTOM_NODE_BUILDER_TEST_HELPER_H

#include <utility>
#include "gtest/gtest.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/common/extension_companion_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
class ICustomNodeBuilderTestHelper {
public:
    virtual ~ICustomNodeBuilderTestHelper() = default;
    virtual void TestFunction(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                              const Callback_Pointer_Void continuation) = 0;
    virtual void TestFunctionSync(Ark_VMContext context, const Ark_Int32 resourceId,
                                  const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation) = 0;
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

template<class T>
class CustomNodeBuilderTestHelper : public ICustomNodeBuilderTestHelper {
public:
    CustomNodeBuilderTestHelper(T* testClassObject, FrameNode* parentNode, Ark_NodeHandle customNode = nullptr)
        : testClassObject_(testClassObject),
        expectedParentNode_(parentNode),
        expectedCustomNode_(call_CreateNode(testClassObject, customNode)),
        uniqueId_(TestHelperManager::Register(this))
        {}

    ~CustomNodeBuilderTestHelper()
    {
        TestHelperManager::Unregister(uniqueId_);
        if (testClassObject_ && expectedCustomNode_) {
            call_DisposeNode(testClassObject_, expectedCustomNode_);
        }
        expectedParentNode_ = nullptr;
        expectedCustomNode_ = nullptr;
        testClassObject_ = nullptr;
        syncCallbackCounter_ = 0;
        asyncCallbackCounter_ = 0;
    }

    int GetCallsCount() const
    {
        return syncCallbackCounter_;
    }

    int GetCallsCountAsync() const
    {
        return asyncCallbackCounter_;
    }

    int GetCallsCountAll() const
    {
        return syncCallbackCounter_ + asyncCallbackCounter_;
    }

    CustomNodeBuilder GetBuilder() const
    {
        CustomNodeBuilder builder;
        builder.resource = {.resourceId = uniqueId_, .hold = [](InteropInt32){}, .release = [](InteropInt32){}};
        builder.call =  [](const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                const Callback_Pointer_Void continuation) {
                auto testHelper = TestHelperManager::GetInstance().GetHelperById(resourceId);
                ASSERT_NE(testHelper, nullptr);
                testHelper->TestFunction(resourceId, parentNode, continuation);
            };
        builder.callSync = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                const Callback_Pointer_Void continuation) {
                auto testHelper = TestHelperManager::GetInstance().GetHelperById(resourceId);
                ASSERT_NE(testHelper, nullptr);
                testHelper->TestFunctionSync(context, resourceId, parentNode, continuation);
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

    void TestFunction(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                    const Callback_Pointer_Void continuation)
    {
        asyncCallbackCounter_++;
        EXPECT_EQ(reinterpret_cast<FrameNode*>(parentNode), expectedParentNode_);
        CallbackHelper(continuation).InvokeSync(reinterpret_cast<Ark_NativePointer>(expectedCustomNode_));
    }

    void TestFunctionSync(Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                    const Callback_Pointer_Void continuation)
    {
        syncCallbackCounter_++;
        EXPECT_EQ(reinterpret_cast<FrameNode*>(parentNode), expectedParentNode_);
        CallbackHelper(continuation).InvokeSync(reinterpret_cast<Ark_NativePointer>(expectedCustomNode_));
    }

private:
    T* testClassObject_;
    FrameNode* expectedParentNode_;
    Ark_NodeHandle expectedCustomNode_;
    int syncCallbackCounter_ = 0;
    int asyncCallbackCounter_ = 0;
    const int32_t uniqueId_;

    // Helper trait for checking the presence of the CreateNode method
    template <typename U, typename = void>
    struct has_CreateNode : std::false_type {};

    template <typename U>
    struct has_CreateNode<U, decltype(std::declval<U>().CreateNode(), void())> : std::true_type {};

    // Helper trait for checking the presence of the DisposeNode method
    template <typename U, typename = void>
    struct has_DisposeNode : std::false_type {};

    template <typename U>
    struct has_DisposeNode<U, decltype(std::declval<U>().DisposeNode(std::declval<Ark_NodeHandle&>()), void())> :
        std::true_type {};

    // Overloading functions to select CreateNode and DisposeNode methods
    template <class U>
    static std::enable_if_t<has_CreateNode<U>::value, Ark_NodeHandle> call_CreateNode(U* testClassObject,
                                                                                      Ark_NodeHandle)
    {
        Ark_NodeHandle customNode = testClassObject->CreateNode();
        return customNode;
    }

    template <class U>
    static std::enable_if_t<!has_CreateNode<U>::value, Ark_NodeHandle> call_CreateNode(U*, Ark_NodeHandle customNode)
    {
        return customNode;
    }

    template <class U>
    static std::enable_if_t<has_DisposeNode<U>::value, void> call_DisposeNode(U* testClassObject, Ark_NodeHandle& node)
    {
        if (node) {
            testClassObject->DisposeNode(node);
        }
    }

    template <class U>
    static std::enable_if_t<!has_DisposeNode<U>::value, void> call_DisposeNode(U* testClassObject, Ark_NodeHandle& node)
    {
        // No default action if there is no DisposeNode method
    }
};

} // OHOS::Ace::NG

#endif // CUSTOM_NODE_BUILDER_TEST_HELPER_H