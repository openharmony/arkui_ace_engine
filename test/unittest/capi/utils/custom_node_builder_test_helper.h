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

    static int64_t Register(ICustomNodeBuilderTestHelper* helper)
    {
        if (helper != nullptr) {
            auto uniqueId = reinterpret_cast<int64_t>(helper);
            GetInstance().instances_[uniqueId] = helper;
            return uniqueId;
        }
        return 0;
    }

    static void Unregister(int64_t uniqueId)
    {
        auto instances = GetInstance().instances_;
        auto it = instances.find(uniqueId);
        if (it != instances.end()) {
            instances.erase(it);
        }
    }

    ICustomNodeBuilderTestHelper* GetHelperById(int64_t uniqueId)
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
    std::unordered_map<int64_t, ICustomNodeBuilderTestHelper*> instances_;
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
        if (helperSwitcher_ == uniqueId_) {
            helperSwitcher_ = 0;
        }
        TestHelperManager::Unregister(uniqueId_);
        if (testClassObject_ && expectedCustomNode_) {
            testClassObject_->DisposeNode(expectedCustomNode_);
        }
        expectedParentNode_ = nullptr;
        testClassObject_ = nullptr;
    }

    int GetCallsCount() const
    {
        return callbackCounter_;
    }

    CustomNodeBuilder GetBuilder()
    {
        SetSelector();
        CustomNodeBuilder builder = {
            .callSync = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                const Callback_Pointer_Void continuation) {
                auto testHelper = TestHelperManager::GetInstance().GetHelperById(helperSwitcher_);
                if (testHelper) {
                    testHelper->TestFunction(context, resourceId, parentNode, continuation);
                } else {
                    ASSERT_EQ(testHelper, nullptr);
                }
            }
        };
        return builder;
    }

    void SetSelector()
    {
        helperSwitcher_ = uniqueId_;
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
        callbackCounter_++;
        EXPECT_EQ(reinterpret_cast<FrameNode*>(parentNode), expectedParentNode_);
        CallbackHelper(continuation).Invoke(reinterpret_cast<Ark_NativePointer>(expectedCustomNode_));
    }

private:
    T* testClassObject_;
    FrameNode* expectedParentNode_;
    Ark_NodeHandle expectedCustomNode_;
    int callbackCounter_ = 0;
    const int64_t uniqueId_;
    static inline int64_t helperSwitcher_;
};

} // OHOS::Ace::NG

#endif // CUSTOM_NODE_BUILDER_TEST_HELPER_H