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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ACTUAL_TRUE = true;
    const auto ACTUAL_FALSE = false;
    const auto EXPECTED_CONTEXT_ID = 123;
    const auto EXPECTED_NODE_ID = 555;
    const auto INVALID_REASON_MIN_VALUE = -1;
    const auto INVALID_REASON_MAX_VALUE = INT_MAX;

    const std::vector<std::pair<uint32_t, std::optional<BindSheetDismissReason>>> bindSheetDismissReasonTestPlan = {
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::BACK_PRESSED),
            std::make_optional(BindSheetDismissReason::BACK_PRESSED) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::TOUCH_OUTSIDE),
            std::make_optional(BindSheetDismissReason::TOUCH_OUTSIDE) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::CLOSE_BUTTON),
            std::make_optional(BindSheetDismissReason::CLOSE_BUTTON) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::SLIDE_DOWN),
            std::make_optional(BindSheetDismissReason::SLIDE_DOWN) },
        { INVALID_REASON_MIN_VALUE, std::nullopt },
        { INVALID_REASON_MAX_VALUE, std::nullopt },
    };
    using SheetTestType = std::variant<SheetType, int32_t>;
    const std::vector<std::pair<uint32_t, std::optional<SheetTestType>>> sheetTypeTestPlan = {
        { std::underlying_type_t<SheetType>(SheetType::SHEET_BOTTOM), std::make_optional(SheetType::SHEET_BOTTOM) },
        { std::underlying_type_t<SheetType>(SheetType::SHEET_CENTER), std::make_optional(SheetType::SHEET_CENTER) },
        { std::underlying_type_t<SheetType>(SheetType::SHEET_POPUP), std::make_optional(SheetType::SHEET_POPUP) },
        { std::underlying_type_t<SheetType>(SheetType::SHEET_BOTTOMLANDSPACE), std::nullopt },
        { std::underlying_type_t<SheetType>(SheetType::SHEET_BOTTOM_FREE_WINDOW), std::nullopt },
        { std::underlying_type_t<SheetType>(SheetType::SHEET_BOTTOM_OFFSET), std::nullopt },
        { INVALID_REASON_MIN_VALUE, std::nullopt },
        { INVALID_REASON_MAX_VALUE, std::nullopt },
    };
    const std::vector<std::pair<int32_t, std::optional<SheetTestType>>> numberInt32TestPlan = {
        { 100, std::make_optional(100) },
        { 0, std::make_optional(0) },
        { -100, std::make_optional(-100) },
        { 12, std::make_optional(12) },
        { -56, std::make_optional(-56) },
    };
    struct CheckEvent {
        int32_t resourceId;
        std::optional<SheetTestType> reason;
    };
    struct CheckBuilderEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    struct CheckNestedEvent {
        int32_t resourceId;
        std::optional<BindSheetDismissReason> reason;
        bool fired;
    };
    static std::optional<CheckBuilderEvent> checkBuilderEvent = std::nullopt;
    static std::optional<CheckNestedEvent> checkNestedEvent = std::nullopt;
    static std::optional<CheckEvent> checkEvent = std::nullopt;
}
namespace Converter {

} // namespace Converter

class CommonMethodModifierTest21 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<SheetTheme>();
    }

    void* CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
    CustomNodeBuilder CreateCustomNodeBuilder(RefPtr<FrameNode>& node)
    {
        checkBuilderEvent.reset();
        static std::optional<RefPtr<UINode>> uiNode = node;
        auto checkCallback = [](
            Ark_VMContext context,
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            checkBuilderEvent = {
                .resourceId = resourceId,
                .parentNode = parentNode
            };
            if (uiNode) {

                std::printf("bindSheet: test *** fired *** CreateCustomNodeBuilder checkBuilderEvent: %d uiNode: %d\n",
                checkBuilderEvent->resourceId,  uiNode->GetRawPtr()->GetId());


                CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
            }
        };
        return Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, EXPECTED_CONTEXT_ID);
    }
    template<typename OptCallback, typename ArkCallback>
    OptCallback CreateOnAppearCallback(FrameNode* frameNode)
    {
        checkEvent.reset();
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvent = {
                .resourceId = resourceId,
            };
            
            std::printf( "bindSheet: test *** fired *** onAppearCommonCallback  checkEvent: %d\n", checkEvent->resourceId);

        };
        auto arkCallback = Converter::ArkValue<ArkCallback>(callback, frameNode->GetId());
        return Converter::ArkValue<OptCallback>(arkCallback);
    }
    template<typename OptCallback, typename ArkCallback, typename ArkReasonType, typename ReasonType>
    OptCallback CreateOnChangeCallback(FrameNode* frameNode)
    {
        checkEvent.reset();
        auto callback = [](const Ark_Int32 resourceId, const ArkReasonType parameter) {

            checkEvent = {
                .resourceId = resourceId,
                .reason = Converter::OptConvert<ReasonType>(parameter),
            };

            SheetType* reason = checkEvent->reason?std::get_if<SheetType>(&(*checkEvent->reason)):nullptr;
            int32_t* reason2 = checkEvent->reason?std::get_if<int32_t>(&(*checkEvent->reason)):nullptr;
            std::printf("bindSheet: test Dismiss *** fired *** check nested reason: %d reason2: %d\n",
                reason?std::underlying_type_t<BindSheetDismissReason>(*reason):-1,
                reason2?std::underlying_type_t<SheetType>(*reason2):-1
            );
        };
        auto arkCallback = Converter::ArkValue<ArkCallback>(callback, frameNode->GetId());
        return Converter::ArkValue<OptCallback>(arkCallback);
    }
    Opt_Callback_SheetDismiss_Void CreateDissmisSheetVoidCallback(FrameNode* frameNode)
    {
        checkNestedEvent.reset();
        auto dismissCallback = [](const Ark_Int32 resourceId, const Ark_SheetDismiss parameter) {

            std::printf("bindSheet: test shouldDismiss *** fired ***\n");


            checkNestedEvent = {
                .resourceId = resourceId,
            };
            auto arkCallback = Converter::OptConvert<Callback_Void>(parameter.dismiss);
            if (arkCallback) {
            
            
            std::printf("bindSheet: test shouldDismiss nested *** fired ***\n");

                auto helper = CallbackHelper(*arkCallback);
                checkNestedEvent->fired = true;
                helper.Invoke();
            }
        };
        auto arkDismissCallback =
            Converter::ArkValue<Callback_SheetDismiss_Void>(dismissCallback, frameNode->GetId());
        return Converter::ArkValue<Opt_Callback_SheetDismiss_Void>(arkDismissCallback);
    }
    Opt_Callback_SpringBackAction_Void CreateDissmisSpringVoidCallback(FrameNode* frameNode)
    {
        checkNestedEvent.reset();
        auto dismissCallback = [](const Ark_Int32 resourceId, const Ark_SpringBackAction parameter) {

            std::printf("bindSheet: test springBack *** fired ***\n");

            checkNestedEvent = {
                .resourceId = resourceId,
            };
            auto arkCallback = Converter::OptConvert<Callback_Void>(parameter.springBack);
            if (arkCallback) {

                std::printf("bindSheet: test springBack nested *** fired ***\n");

                auto helper = CallbackHelper(*arkCallback);
                checkNestedEvent->fired = true;
                helper.Invoke();
            }
        };
        auto arkDismissCallback =
            Converter::ArkValue<Callback_SpringBackAction_Void>(dismissCallback, frameNode->GetId());
        return Converter::ArkValue<Opt_Callback_SpringBackAction_Void>(arkDismissCallback);
    }
    Opt_Callback_DismissSheetAction_Void CreateDissmisSheetReasonCallback(FrameNode* frameNode)
    {
        checkNestedEvent.reset();
        auto dismissCallback = [](const Ark_Int32 resourceId, const Ark_DismissSheetAction parameter) {
            checkNestedEvent = {
                .resourceId = resourceId,
                .reason = Converter::OptConvert<BindSheetDismissReason>(parameter.reason),
            };

            std::printf("bindSheet: test willDismiss *** fired *** parameter.reason: %d checknested: reason: %d\n",
                std::underlying_type_t<Ark_DismissReason>(parameter.reason),
                checkNestedEvent->reason?std::underlying_type_t<BindSheetDismissReason>(*checkNestedEvent->reason):-1
            );
            
            auto arkCallback = Converter::OptConvert<Callback_Void>(parameter.dismiss);
            if (arkCallback) {

                std::printf("bindSheet: test willDismiss nested *** fired ***\n");

                auto helper = CallbackHelper(*arkCallback);
                checkNestedEvent->fired = true;
                helper.Invoke();
            }
        };
        auto arkDismissCallback =
            Converter::ArkValue<Callback_DismissSheetAction_Void>(dismissCallback, frameNode->GetId());
        return Converter::ArkValue<Opt_Callback_DismissSheetAction_Void>(arkDismissCallback);
    }
    RefPtr<SheetPresentationPattern> GetSheetPresentationPattern(const RefPtr<FrameNode>& node)
    {
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        if (!modal) {
            return nullptr;
        }
        auto sheetNode = AceType::DynamicCast<FrameNode>(modal->GetParent());
        if (!sheetNode) {
            return nullptr;
        }
        return sheetNode->GetPattern<SheetPresentationPattern>();
    }
};

/*
 * @tc.name: setBindSheetIsShowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetIsShowTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);

    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(Ark_Empty());
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    EXPECT_NE(pipeline, nullptr);
    pipeline->FlushAnimationClosure();
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);

    arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_FALSE);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    pipeline->FlushAnimationClosure();
    EXPECT_FALSE(checkBuilderEvent.has_value());
}

/*
 * @tc.name: setBindSheetOnAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetOnAppearTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto optOnAppearCalback = CreateOnAppearCallback<Opt_Callback_Void, Callback_Void>(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onAppear = optOnAppearCalback,
        .onWillAppear = Converter::ArkValue<Opt_Callback_Void>(Ark_Empty())
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
   
    checkBuilderEvent.reset();
    checkEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEvent.has_value()); 
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  
 
    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());
 
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId,  frameNode->GetId());
}

/*
 * @tc.name: setBindSheetOnDisAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetOnDisAppearTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto optOnAppearCalback = CreateOnAppearCallback<Opt_Callback_Void, Callback_Void>(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onDisappear = optOnAppearCalback,
     };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    checkEvent.reset();

    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEvent.has_value()); 
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  
   
    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    std::printf("bindSheet: test === end call === FlushAnimationClosure\n");  

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);
    pattern->OnDisappear();

    std::printf("bindSheet: const checkBuilderEvent: %d checkEvent: %d resourceId: %d parentNode: %d frameNode:%d resourceId: %d\n", 
        checkBuilderEvent.has_value(), checkEvent.has_value(),
        checkBuilderEvent.has_value()?checkBuilderEvent->resourceId:-1,  
        checkBuilderEvent.has_value()?checkBuilderEvent->parentNode? reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode)->GetId():-1:-1,
        frameNode->GetId(),
        checkEvent->resourceId
    );
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId,  frameNode->GetId());
}

/*
 * @tc.name: setBindSheetOnWillAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetOnWillAppearTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto optOnAppearCalback = CreateOnAppearCallback<Opt_Callback_Void, Callback_Void>(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onWillAppear = optOnAppearCalback,
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    checkEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEvent.has_value()); 
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetCurrentContext()->GetTheme<SheetTheme>();
    
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  
    
    
    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());


    std::printf("bindSheet: const checkBuilderEvent: %d checkEvent: %d resourceId: %d parentNode: %d frameNode:%d resourceId: %d\n", 
        checkBuilderEvent.has_value(), checkEvent.has_value(),
        checkBuilderEvent.has_value()?checkBuilderEvent->resourceId:-1,  
        checkBuilderEvent.has_value()?checkBuilderEvent->parentNode? reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode)->GetId():-1:-1,
        frameNode->GetId(),
        checkEvent->resourceId
    );

    

    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId,  frameNode->GetId());
}

/*
 * @tc.name: setBindSheetOnWillDisAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetOnWillDisAppearTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto optOnAppearCalback = CreateOnAppearCallback<Opt_Callback_Void, Callback_Void>(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onWillDisappear = optOnAppearCalback,
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    checkEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEvent.has_value()); 
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetCurrentContext()->GetTheme<SheetTheme>();
    
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  
    
    
    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);
    pattern->OnWillDisappear();

    std::printf("bindSheet: const checkBuilderEvent: %d checkEvent: %d resourceId: %d parentNode: %d frameNode:%d resourceId: %d\n", 
        checkBuilderEvent.has_value(), checkEvent.has_value(),
        checkBuilderEvent.has_value()?checkBuilderEvent->resourceId:-1,  
        checkBuilderEvent.has_value()?checkBuilderEvent->parentNode? reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode)->GetId():-1:-1,
        frameNode->GetId(),
        checkEvent->resourceId
    );
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId,  frameNode->GetId());
}

/*
 * @tc.name: setBindSheetShouldDismissTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetShouldDismissTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto onDismissCallback = CreateDissmisSheetVoidCallback(frameNode); 
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .shouldDismiss = onDismissCallback
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
   
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);

    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  

    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);
    pattern->CallShouldDismiss();
   
    std::printf("bindSheet: const checkBuilderEvent: %d parentNode: %d checkNestedEvent: %d frameNode:%d\n", 
        checkBuilderEvent?checkBuilderEvent->resourceId:-1,  
        checkBuilderEvent?checkBuilderEvent->parentNode? reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode)->GetId():-1:-1,
        checkNestedEvent?checkNestedEvent->resourceId:-1,
        frameNode->GetId()
    );

    EXPECT_TRUE(checkNestedEvent.has_value());
    EXPECT_EQ(checkNestedEvent->resourceId, frameNode->GetId());
    EXPECT_TRUE(checkNestedEvent->fired);
}

/*
 * @tc.name: setBindSheetWillDismissTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetWillDismissTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto onDismissCallback = CreateDissmisSheetReasonCallback(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onWillDismiss = onDismissCallback
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
        
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  
    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);

    for (const auto& [actual, expected] : bindSheetDismissReasonTestPlan) {
        checkNestedEvent.reset();
        EXPECT_FALSE(checkNestedEvent.has_value());
        pattern->CallOnWillDismiss(actual);
        
       std::printf("bindSheet: const checkNestedEvent: resorceId %d actual: %d reason: %d == %d  fired: %d\n",
            checkNestedEvent?checkNestedEvent->resourceId:-1,
            actual,
            checkNestedEvent->reason?std::underlying_type_t<BindSheetDismissReason>(*checkNestedEvent->reason):-1,
            expected?std::underlying_type_t<BindSheetDismissReason>(*expected):-1,
            checkNestedEvent?checkNestedEvent->fired:-1
        );
    
        EXPECT_TRUE(checkNestedEvent.has_value());
        EXPECT_EQ(checkNestedEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkNestedEvent->reason, expected);
        EXPECT_TRUE(checkNestedEvent->fired);
    }
}

/*
 * @tc.name: setBindSheetSpringBackTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetSpringBackTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto onDismissCallback = CreateDissmisSpringVoidCallback(frameNode); 

    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onWillSpringBackWhenDismiss = onDismissCallback
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
        
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  
    
    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);
    pattern->CallSheetSpringBack();
   
    std::printf("bindSheet: const checkBuilderEvent: %d parentNode: %d checkNestedEvent: %d frameNode:%d\n", 
        checkBuilderEvent?checkBuilderEvent->resourceId:-1,  
        checkBuilderEvent?checkBuilderEvent->parentNode? reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode)->GetId():-1:-1,
        checkNestedEvent?checkNestedEvent->resourceId:-1,
        frameNode->GetId()
    );
    EXPECT_TRUE(checkNestedEvent.has_value());
    EXPECT_EQ(checkNestedEvent->resourceId, frameNode->GetId());
    EXPECT_TRUE(checkNestedEvent->fired);
}

/*
 * @tc.name: setBindSheetOnTypeDidChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetOnTypeDidChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto onChangeCallback = CreateOnChangeCallback<Opt_Callback_SheetType_Void,
        Callback_SheetType_Void, Ark_SheetType, SheetType>(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onTypeDidChange = onChangeCallback
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
        
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  

    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);
    for (const auto& [actual, expected] : sheetTypeTestPlan) {
        checkEvent.reset();
        EXPECT_FALSE(checkEvent.has_value());
        pattern->onTypeDidChange(actual);

        SheetType* reason = checkEvent->reason?std::get_if<SheetType>(&(*checkEvent->reason)):nullptr;
        int32_t* reason2 = checkEvent->reason?std::get_if<int32_t>(&(*checkEvent->reason)):nullptr;
        const SheetType* ex = checkEvent->reason?std::get_if<SheetType>(&(*expected)):nullptr;
        const int32_t* ex2 = checkEvent->reason?std::get_if<int32_t>(&(*expected)):nullptr;
         std::printf("bindSheet: test holder checkEvent: resorceId %d actual: %d reason: %d == %d reason2: %d == %d\n",
                checkEvent?checkEvent->resourceId:-1,
                actual,
                reason?std::underlying_type_t<BindSheetDismissReason>(*reason):-1,
                ex?std::underlying_type_t<BindSheetDismissReason>(*ex):-1,
                reason2?std::underlying_type_t<SheetType>(*reason2):-1,
                ex2?std::underlying_type_t<SheetType>(*ex2):-1
        );

        EXPECT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->reason, expected);
    }
}

/*
 * @tc.name: setBindSheetOnHeightDidChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetOnHeightDidChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto onChangeCallback = CreateOnChangeCallback<Opt_Callback_Number_Void,
        Callback_Number_Void, Ark_Number, int32_t>(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onHeightDidChange = onChangeCallback
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
        
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  

    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);
    for (const auto& [actual, expected] : numberInt32TestPlan) {
        checkEvent.reset();
        EXPECT_FALSE(checkEvent.has_value());
        pattern->OnHeightDidChange(actual);

        auto reason_ = checkEvent->reason?std::get_if<int32_t>(&(*checkEvent->reason)):nullptr;
        auto expected_ = checkEvent->reason?std::get_if<int32_t>(&(*expected)):nullptr;
         std::printf("bindSheet: test holder checkEvent: resorceId %d actual: %d reason: %d == %d \n",
                checkEvent?checkEvent->resourceId:-1,
                actual,
                reason_?*reason_:-1,
                expected_?*expected_:-1
        );

        EXPECT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->reason, expected);
    }
}

/*
 * @tc.name: setBindSheetOnWidthDidChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetOnWidthDidChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto onChangeCallback = CreateOnChangeCallback<Opt_Callback_Number_Void,
        Callback_Number_Void, Ark_Number, int32_t>(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onWidthDidChange = onChangeCallback
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
        
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  

    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);
    for (const auto& [actual, expected] : numberInt32TestPlan) {
        checkEvent.reset();
        EXPECT_FALSE(checkEvent.has_value());
        pattern->onWidthDidChange(actual);

        auto reason_ = checkEvent->reason?std::get_if<int32_t>(&(*checkEvent->reason)):nullptr;
        auto expected_ = checkEvent->reason?std::get_if<int32_t>(&(*expected)):nullptr;
         std::printf("bindSheet: test holder checkEvent: resorceId %d actual: %d reason: %d == %d \n",
                checkEvent?checkEvent->resourceId:-1,
                actual,
                reason_?*reason_:-1,
                expected_?*expected_:-1
        );

        EXPECT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->reason, expected);
    }
}

/*
 * @tc.name: setBindSheetOnDetentsDidChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest21, setBindSheetOnDetentsDidChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindSheet, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = CreateCustomNodeBuilder(node);
    auto onChangeCallback = CreateOnChangeCallback<Opt_Callback_Number_Void,
        Callback_Number_Void, Ark_Number, int32_t>(frameNode);
    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_SheetOptions {
        .onDetentsDidChange= onChangeCallback
    };
    auto optOptions = Converter::ArkValue<Opt_SheetOptions>(arkOptions);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    
    modifier_->setBindSheet(node_, arkShow, &customBuilder, &optOptions);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
        
    std::printf("bindSheet: test === start call === FlushAnimationClosure\n");  

    pipeline->FlushAnimationClosure(); 
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    ASSERT_NE(parentNode, nullptr);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());

    auto pattern = GetSheetPresentationPattern(node);
    ASSERT_NE(pattern, nullptr);
    for (const auto& [actual, expected] : numberInt32TestPlan) {
        checkEvent.reset();
        EXPECT_FALSE(checkEvent.has_value());
        pattern->OnDetentsDidChange(actual);

        auto reason_ = checkEvent->reason?std::get_if<int32_t>(&(*checkEvent->reason)):nullptr;
        auto expected_ = checkEvent->reason?std::get_if<int32_t>(&(*expected)):nullptr;
        std::printf("bindSheet: test holder checkEvent: resorceId %d actual: %d reason: %d == %d \n",
                checkEvent?checkEvent->resourceId:-1,
                actual,
                reason_?*reason_:-1,
                expected_?*expected_:-1
        );

        EXPECT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkEvent->reason, expected);
    }
}
}
