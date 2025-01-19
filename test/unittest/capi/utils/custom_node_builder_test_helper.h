// #ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_UTILS_CUSTOM_NODE_BUILDER_TEST_HELPER_CPP
// #define FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_UTILS_CUSTOM_NODE_BUILDER_TEST_HELPER_CPP


#include <utility>
#include "gtest/gtest.h"
#include "arkoala_api_generated.h"

#include "test/unittest/capi/modifiers/modifier_test_base.h"
// #include "interfaces/inner_api/ace_kit/include/ui/view/frame_node.h"
#include "core/interfaces/native/common/extension_companion_node.h"
// #include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
// #include "core/interfaces/native/utility/callback_keeper.h"
// #include "core/interfaces/native/utility/converter.h"
// #include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"

// using namespace testing;
// using namespace testing::ext;

namespace OHOS::Ace::NG {

template<typename T>
class CustomNodeBuilderTestHelper {
public:
    explicit CustomNodeBuilderTestHelper(T* testClassObject, FrameNode* parentNode)
        : testClassObject_(testClassObject),
        expectedParentNode_(parentNode),
        expectedCustomNode_(testClassObject->CreateNode())
        {}

    ~CustomNodeBuilderTestHelper() {
        testClassObject_->DisposeNode(expectedCustomNode_);
        expectedParentNode_ = nullptr;
        testClassObject_ = nullptr;
    }

    void operator()(Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                    const Callback_Pointer_Void continuation) {
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

private:
    T* testClassObject_;
    FrameNode* expectedParentNode_;
    Ark_NodeHandle expectedCustomNode_;
    int callbackCounter_ = 0;
    // std::function<void(Ark_NodeHandle&)> destroyNodeFunction_;
};
}