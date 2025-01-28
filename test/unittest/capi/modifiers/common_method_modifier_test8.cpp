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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_GEOMETRY_TRANSITION_NAME = "geometryTransition";
    const auto ATTRIBUTE_GEOMETRY_TRANSITION_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_RESTORE_ID_NAME = "restoreId";
    const auto ATTRIBUTE_RESTORE_ID_DEFAULT_VALUE = "";
    const auto ATTRIBUE_MONOPOLIZE_EVENTS_NAME = "monopolizeEvents";
    const auto ATTRIBUE_MONOPOLIZE_EVENTS_DEFAULT_VALUE = "false";
    const auto ACTUAL_TRUE = true;
    const auto ACTUAL_FALSE = false;
    const auto EXPECTED_TRUE = "true";
    const auto EXPECTED_FALSE = "false";
    const auto EXPECTED_CONTEXT_ID = 123;
    const auto EXPECTED_NODE_ID = 555;
    const auto INVALID_REASON_VALUE = -1;

    std::vector<std::pair<Opt_ModalTransition, ModalTransition>> modalTransitionTestPlan = {
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_DEFAULT), ModalTransition::DEFAULT },
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_NONE), ModalTransition::NONE },
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_ALPHA), ModalTransition::ALPHA },
        { Converter::ArkValue<Opt_ModalTransition>(static_cast<Ark_ModalTransition>(-1)), ModalTransition::DEFAULT },
        { Converter::ArkValue<Opt_ModalTransition>(Ark_Empty()), ModalTransition::DEFAULT },
    };
    std::vector<std::pair<uint32_t, std::optional<BindSheetDismissReason>>> bindSheetDissmisReasonTestPlan = {
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::BACK_PRESSED),
            std::make_optional(BindSheetDismissReason::BACK_PRESSED) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::TOUCH_OUTSIDE),
            std::make_optional(BindSheetDismissReason::TOUCH_OUTSIDE) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::CLOSE_BUTTON),
            std::make_optional(BindSheetDismissReason::CLOSE_BUTTON) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::SLIDE_DOWN),
            std::make_optional(BindSheetDismissReason::SLIDE_DOWN) },
        { INVALID_REASON_VALUE, std::nullopt },
    };
    std::vector<std::pair<Opt_ResourceColor, std::string>> colorTestPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(static_cast<Ark_Color>(-1)), "#00000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr), "#00000000" },
    };
}
namespace Converter {

} // namespace Converter

class CommonMethodModifierTest8 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
};

///////// GeometryTransition
/*
 * @tc.name: setGeometryTransitionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setGeometryTransitionTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_GEOMETRY_TRANSITION_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_GEOMETRY_TRANSITION_DEFAULT_VALUE);
}

/*
 * @tc.name: setGeometryTransitionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC /data/home/mlobakh/BZ_OHOS/OHOS/interface/sdk-js/api/@internal/component/ets/common.d.ts
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setGeometryTransitionTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setGeometryTransition0, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("id1"), "id1"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setGeometryTransition0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_GEOMETRY_TRANSITION_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

///////// RestoreId
/*
 * @tc.name: setRestoreIdTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setRestoreIdTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_RESTORE_ID_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_RESTORE_ID_DEFAULT_VALUE);
}

/*
 * @tc.name: setRestoreIdTestValidValues
 * @tc.desc:
 * @tc.type: FUNC /data/home/mlobakh/BZ_OHOS/OHOS/interface/sdk-js/api/@internal/component/ets/common.d.ts
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setRestoreIdTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setRestoreId, nullptr);
    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(1), "1"},
        {Converter::ArkValue<Ark_Number>(2), "2"},
        {Converter::ArkValue<Ark_Number>(3), "3"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setRestoreId(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_RESTORE_ID_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setMonopolizeEventsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setMonopolizeEventsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMonopolizeEvents, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto fullJson = GetJsonValue(node_);
    auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUE_MONOPOLIZE_EVENTS_NAME);
    EXPECT_EQ(resultValue, ATTRIBUE_MONOPOLIZE_EVENTS_DEFAULT_VALUE);

    Ark_Boolean arkTrueValue = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    modifier_->setMonopolizeEvents(node_, arkTrueValue);
    fullJson = GetJsonValue(node_);
    resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUE_MONOPOLIZE_EVENTS_NAME);
    EXPECT_EQ(resultValue, EXPECTED_TRUE);

    Ark_Boolean arkFalseValue = Converter::ArkValue<Ark_Boolean>(ACTUAL_FALSE);
    modifier_->setMonopolizeEvents(node_, arkFalseValue);
    fullJson = GetJsonValue(node_);
    resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUE_MONOPOLIZE_EVENTS_NAME);
    EXPECT_EQ(resultValue, EXPECTED_FALSE);
}

/*
 * @tc.name: setBindContentCover0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover0IsShowTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover0, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    int32_t nodeId = EXPECTED_NODE_ID;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
    static std::optional<RefPtr<UINode>> uiNode = node;
    auto checkCallback = [](
        Ark_VMContext context,
        const Ark_Int32 resourceId,
        const Ark_NativePointer parentNode,
        const Callback_Pointer_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .parentNode = parentNode
        };
        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };
    static constexpr int32_t contextId = EXPECTED_CONTEXT_ID;
    CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto optModal = Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_ALPHA);
   
    // test show
    std::printf("bindContent0: test ============ start true =========\n");
    auto modalNode = uiNode->GetRawPtr()->GetParent();
    auto modalNodeId = modalNode? modalNode->GetId(): -1;
    std::printf("bindContent0: test const true uiNode: %d modalNode: %d checkEvent: %d\n",  
        uiNode->GetRawPtr()->GetId(),  modalNodeId, checkEvent ? checkEvent->resourceId:-1
    );
    // test show eof

    EXPECT_FALSE(checkEvent.has_value());
    modifier_->setBindContentCover0(node_, arkShow, &customBuilder, &optModal);

    // test show
    std::printf("bindContent0: test ============ end true =========\n");
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    auto pattern = modal->GetPattern<ModalPresentationPattern>();
    auto transition = std::underlying_type_t<ModalTransition>(pattern->GetType());
    std::printf("bindContent0: test holder true uiNode: %d modal: %d pattern: %d checkEvent: %d\n",  
    uiNode->GetRawPtr()->GetId(), modal->GetId(), transition, checkEvent?checkEvent->resourceId:-1);
    // test show eof

    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
        
    arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_FALSE);
    checkEvent.reset();    

    // test show
    std::printf("bindContent0: test ============ start false =========\n");
    modalNode = uiNode->GetRawPtr()->GetParent();
    modalNodeId = modalNode? modalNode->GetId(): -1;
    std::printf("bindContent0: test const false uiNode: %d modalNode: %d\n",  uiNode->GetRawPtr()->GetId(), modalNodeId);
    // test show eof

    EXPECT_FALSE(checkEvent.has_value());
    modifier_->setBindContentCover0(node_, arkShow, &customBuilder, &optModal);

    // test show
    std::printf("bindContent0: test ============ end false =========\n");
    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    pattern = modal->GetPattern<ModalPresentationPattern>();
    transition = pattern?std::underlying_type_t<ModalTransition>(pattern->GetType()):-1;
    std::printf("bindContent0: test holder false uiNode: %d modal: %d pattern: %d checkEvent: %d\n",  
    uiNode->GetRawPtr()->GetId(), modal->GetId(), transition, checkEvent?checkEvent->resourceId:-1);
    // test show eof

    EXPECT_FALSE(checkEvent.has_value());
}

/*
 * @tc.name: setBindContentCover0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover0ModalTransitionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover0, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    int32_t nodeId = EXPECTED_NODE_ID;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
    static std::optional<RefPtr<UINode>> uiNode = node;
    auto checkCallback = [](
        Ark_VMContext context,
        const Ark_Int32 resourceId,
        const Ark_NativePointer parentNode,
        const Callback_Pointer_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .parentNode = parentNode
        };
        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };
    static constexpr int32_t contextId = EXPECTED_CONTEXT_ID;
    CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);
    auto arkShowTrue = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);

    for (auto& [actual, expected] : modalTransitionTestPlan) {
        // test show
        {
        std::printf("bindContent0: test ============ start =========\n");
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        auto pattern = modal?modal->GetPattern<ModalPresentationPattern>():nullptr;
        auto transition = pattern? std::underlying_type_t<ModalTransition>(pattern->GetType()):-1;
        auto expectedTransition = std::underlying_type_t<ModalTransition>(expected);
        std::printf("bindContent0: test const uiNode: %d modal: %d pattern: %d == %d checkEvent: %d\n",
            uiNode->GetRawPtr()->GetId(), 
            modal?modal->GetId():-1,
            transition, expectedTransition, 
            checkEvent ? checkEvent->resourceId : -1);
        }
        // test show eof

        
        modifier_->setBindContentCover0(node_, arkShowTrue, &customBuilder, &actual);
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        EXPECT_NE(modal,nullptr);
        auto pattern = modal->GetPattern<ModalPresentationPattern>();
        EXPECT_NE(pattern,nullptr);
        
        // test show
        {
        std::printf("bindContent0: test ============ end =========\n");
        auto transition = pattern? std::underlying_type_t<ModalTransition>(pattern->GetType()):-1;
        auto expectedTransition = std::underlying_type_t<ModalTransition>(expected);
        std::printf("bindContent0: test holder uiNode: %d modal: %d pattern: %d == %d checkEvent: %d\n",
            uiNode->GetRawPtr()->GetId(), modal->GetId(), transition, expectedTransition, 
            checkEvent ? checkEvent->resourceId : -1);
        }
        // test show eof

        EXPECT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->resourceId, contextId);
        EXPECT_EQ(pattern->GetType(), expected);
    }
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1IsShowTest, TestSize.Level1)
{
    std::printf("\nbindeContent1: [===test_111===] start\n");
    
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
   
    struct CheckBuilderEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckBuilderEvent> checkBuilderEvent = std::nullopt;
    int32_t nodeId = EXPECTED_NODE_ID;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
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
        
        // test!!!
        FrameNode* parenFrametNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
        std::printf("bindContent1: [===test_111===] *** fired *** checkCallback builder  id: %d resourceId: %d parent: %d\n", 
        uiNode.value()->GetId(),  checkBuilderEvent->resourceId, parenFrametNode->GetId());
        // test!!! eof

        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };
    static constexpr int32_t contextId = EXPECTED_CONTEXT_ID;
    CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(Ark_Empty());

    // test!!!
    std::printf("bindContent1: [===test_111===] ============ start =========\n");
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    auto pattern = modal ? modal->GetPattern<ModalPresentationPattern>() : nullptr;
    std::printf("bindContent1: [===test_111===] const  modal:%s pattern:%s checkBuilderEvent: %d\n",
        modal ? "[+]" : "-", pattern ? "[+]" : "-", checkBuilderEvent ? checkBuilderEvent->resourceId : -1);
    // test!!! eof

    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindContentCover1(node_, arkShow, &customBuilder, &optOptions);

    // test!!!
    std::printf("bindContent1: [===test_111===] ============ ready =========\n");
    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    pattern = modal->GetPattern<ModalPresentationPattern>();
    std::printf("bindContent1: [===test_111===] hover  modal:%s pattern:%s  transition: %d dismiss: %d checkBuilderEvent: %d\n", 
        modal ? "[+]" : "-", pattern ? "[+]" : "-", 
        std::underlying_type_t<ModalTransition>(pattern->GetType()), pattern->HasOnWillDismiss(),
        checkBuilderEvent ? checkBuilderEvent->resourceId : -1
        );
    std::printf("\n");
    // test!!! eof

    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    
    arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_FALSE);
    checkBuilderEvent.reset();

    // test!!!
    std::printf("bindContent1: [===test_111===] ============ start =========\n");
    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    pattern = modal ? modal->GetPattern<ModalPresentationPattern>() : nullptr;
    std::printf("bindContent1: [===test_111===] const  modal:%s pattern:%s checkBuilderEvent: %d\n", modal ? "[+]" : "-", pattern ? "[+]" : "-",
    checkBuilderEvent ? checkBuilderEvent->resourceId : -1);
    // test!!! eof

    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindContentCover1(node_, arkShow, &customBuilder, &optOptions);

    // test!!!
    std::printf("bindContent1: [===test_111===] ============ ready =========\n");
    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    pattern = modal->GetPattern<ModalPresentationPattern>();
    std::printf("bindContent1: [===test_111===] hover  modal:%s pattern:%s  transition: %d dismiss: %d checkBuilderEvent: %d\n", 
        modal ? "[+]" : "-", pattern ? "[+]" : "-", 
        std::underlying_type_t<ModalTransition>(pattern->GetType()), pattern->HasOnWillDismiss(),
        checkBuilderEvent ? checkBuilderEvent->resourceId : -1);
    std::printf("\n\n\n");
    // test!!! eof

    EXPECT_FALSE(checkBuilderEvent.has_value());
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1AppearCallbacksTest, TestSize.Level1)
{
    // test!!!
    std::printf("\nbindeContent1: test start\n\n");
    // test!!! eof
    
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEventAppear = std::nullopt;
    static std::optional<CheckEvent> checkEventDisAppear = std::nullopt;
    static std::optional<CheckEvent> checkEventWillAppear = std::nullopt;
    static std::optional<CheckEvent> checkEventWillDisAppear = std::nullopt;
    
    auto onAppearCallback = [](Ark_Int32 nodeId) {
        checkEventAppear = {
            .nodeId = nodeId,
        };
        // test!!!
        std::printf("bindContent1: test2 *** fired *** low level onAppearCallback id: %d\n", checkEventAppear.value().nodeId);
        // test!!! eof
    };
    auto arkOnAppearCalback = Converter::ArkValue<Callback_Void>(onAppearCallback, frameNode->GetId());
    auto optOnAppearCalback = Converter::ArkValue<Opt_Callback_Void>(arkOnAppearCalback);
   
   auto onDisAppearCallback = [](Ark_Int32 nodeId) {
        checkEventDisAppear = {
            .nodeId = nodeId,
        };
        // test!!!
        auto time = GetCurrentTimestamp();
        std::printf("bindContent1: test3 *** fired *** low level onDisAppearCallback id: %d time: %zu\n",
        checkEventDisAppear.value().nodeId, time );
        // test!!! eof

    };
    auto arkOnDisAppearCalback = Converter::ArkValue<Callback_Void>(onDisAppearCallback, frameNode->GetId());
    auto optOnDisAppearCalback = Converter::ArkValue<Opt_Callback_Void>(arkOnDisAppearCalback);

    auto onWillAppearCallback = [](Ark_Int32 nodeId) {
        checkEventWillAppear = {
            .nodeId = nodeId,
        };
        // test!!!
        std::printf("bindContent1: test4 *** fired *** low level onWillAppearCallback id: %d\n", checkEventWillAppear.value().nodeId);
        // test!!! eof

    };
    auto arkOnWillAppearCalback = Converter::ArkValue<Callback_Void>(onWillAppearCallback, frameNode->GetId());
    auto optOnWillAppearCalback = Converter::ArkValue<Opt_Callback_Void>(arkOnWillAppearCalback);
   
    auto onWillDisAppearCallback = [](Ark_Int32 nodeId) {
        checkEventWillDisAppear = {
            .nodeId = nodeId,
        };
        // test!!!
        auto time = GetCurrentTimestamp();
        std::printf("bindContent1: test5 *** fired *** low level onWillDisAppearCallback id: %d time: %zu\n", 
        checkEventWillDisAppear.value().nodeId, time );
        // test!!! eof
    };
    auto arkOnWillDisAppearCalback = Converter::ArkValue<Callback_Void>(onWillDisAppearCallback, frameNode->GetId());
    auto optOnWillDisAppearCalback = Converter::ArkValue<Opt_Callback_Void>(arkOnWillDisAppearCalback);
    
    struct CheckBuilderEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckBuilderEvent> checkBuilderEvent = std::nullopt;

    int32_t nodeId = EXPECTED_NODE_ID;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
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

        // test!!!     
        FrameNode* parenFrametNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
        std::printf("bindContent1: test8 *** fired *** checkCallback builder  id: %d resourceId: %d parent: %d\n", 
        uiNode.value()->GetId(),  checkBuilderEvent->resourceId, parenFrametNode->GetId());
        // test!!! eof

        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };
    static constexpr int32_t contextId = EXPECTED_CONTEXT_ID;
    CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);

    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_ContentCoverOptions {
        .onAppear = optOnAppearCalback,
        .onDisappear = optOnDisAppearCalback,
        .onWillAppear = optOnWillAppearCalback,
        .onWillDisappear = optOnWillDisAppearCalback,
    };
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);

    // test!!!
    {
        std::printf("bindContent1: test9 ============ start =========\n");
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        std::printf("bindContent1: test9 modal:%s\n", modal ? "[+]" : "-");
        auto pattern = modal ? modal->GetPattern<ModalPresentationPattern>() : nullptr;
        std::printf("bindContent1: test10 const  modal:%s pattern:%s  transition: %d dismiss: %d\n",
            modal ? "[+]" : "-", pattern ? "[+]" : "-",
            pattern ? std::underlying_type_t<ModalTransition>(pattern->GetType()) : -1,
            pattern ? pattern->HasOnWillDismiss() : -1);

        std::printf("bindContent1: test10 const  checkAppear:%d checkDisAppear: %d checkWillAppear: %d "
                    "checkWillDisAppear: %d\n",
            checkEventAppear ? checkEventAppear->nodeId : -1, checkEventDisAppear ? checkEventDisAppear->nodeId : -1,
            checkEventWillAppear ? checkEventWillAppear->nodeId : -1,
            checkEventWillDisAppear ? checkEventWillDisAppear->nodeId : -1);
    }
    // test!!! eof

    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_EQ(modal, nullptr);
    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEventAppear.has_value());
    EXPECT_FALSE(checkEventDisAppear.has_value());
    EXPECT_FALSE(checkEventWillAppear.has_value());
    EXPECT_FALSE(checkEventWillDisAppear.has_value());
    
    modifier_->setBindContentCover1(node_, arkShow, &customBuilder, &optOptions);

    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_NE(modal, nullptr);
    auto pattern = modal->GetPattern<ModalPresentationPattern>();
    EXPECT_NE(pattern, nullptr);
   

    // test!!!
    {
    auto time  = GetCurrentTimestamp();
    std::printf("bindContent1: test11 ============ ready ========= %zu\n", time );
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    std::printf("bindContent1: test12 modal:%s\n",modal ? "[+]" : "-");
    auto pattern = modal?modal->GetPattern<ModalPresentationPattern>():nullptr;
    std::printf("bindContent1: test12 hover  modal:%s pattern:%s  transition: %d dismiss: %d\n", 
        modal ? "[+]" : "-", pattern ? "[+]" : "-", 
        pattern? std::underlying_type_t<ModalTransition>(pattern->GetType()):-1, pattern?pattern->HasOnWillDismiss():-1);

    std::printf("bindContent1: test12 const  checkAppear:%d checkDisAppear: %d checkWillAppear: %d checkWillDisAppear: %d time: %zu\n",
        checkEventAppear? checkEventAppear->nodeId: -1,
        checkEventDisAppear? checkEventDisAppear->nodeId: -1,
        checkEventWillAppear? checkEventWillAppear->nodeId: -1,
        checkEventWillDisAppear? checkEventWillDisAppear->nodeId: -1,
        time
     );
     FrameNode* parenFrametNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
     std::printf("bindContent1: node:%d frameNode: %d modal: %d bilder: resourceId: %d parentNode: %d\n",
        node->GetId(), frameNode->GetId(), modal->GetId(), checkBuilderEvent->resourceId, parenFrametNode->GetId()
     );
    }
    // test!!! eof 

    pattern->OnDisappear();
    pattern->OnWillDisappear();
  

    // test!!!
    {
    auto time  = GetCurrentTimestamp();
    std::printf("bindContent1: test12 const  checkAppear:%d checkDisAppear: %d checkWillAppear: %d checkWillDisAppear: %d time: %zu\n",
        checkEventAppear? checkEventAppear->nodeId: -1,
        checkEventDisAppear? checkEventDisAppear->nodeId: -1,
        checkEventWillAppear? checkEventWillAppear->nodeId: -1,
        checkEventWillDisAppear? checkEventWillDisAppear->nodeId: -1,
        time
     );
    }
    // test!!! eof
   
        auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    EXPECT_NE(parentNode, nullptr);
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());
    EXPECT_TRUE(checkEventAppear.has_value());
    EXPECT_EQ(checkEventAppear->nodeId,frameNode->GetId());
    EXPECT_TRUE(checkEventDisAppear.has_value());
    EXPECT_EQ(checkEventDisAppear->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEventWillAppear.has_value());
    EXPECT_EQ(checkEventWillAppear->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEventWillDisAppear.has_value());
    EXPECT_EQ(checkEventWillDisAppear->nodeId, frameNode->GetId());

}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1DissmisCallbackTest, TestSize.Level1)
{
    std::printf("\nbindeContent1: test start\n\n");
    
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    struct CheckNestedEvent {
        int32_t resourceId;
        std::optional<BindSheetDismissReason> reason;
        bool fired;
    };
    static std::optional<CheckNestedEvent> checkNestedEvent = std::nullopt;
    auto dismissCallback = [](const Ark_Int32 resourceId, const Ark_DismissContentCoverAction parameter) {
        checkNestedEvent = {
            .resourceId = resourceId,
            .reason = Converter::OptConvert<BindSheetDismissReason>(parameter.reason)
        };
        auto arkCallback = Converter::OptConvert<Callback_Void>(parameter.dismiss);

        // test!!!
        auto reason = checkNestedEvent->reason? std::underlying_type_t<BindSheetDismissReason>(*checkNestedEvent->reason):-1;
        std::printf("bindContent1: test6 *** fired *** dismissCallback id: %d arkCallback:%s ark reason: %d\n", 
        checkNestedEvent.value().resourceId, arkCallback?"[+]":"-", reason);
        // test!!! eof

        if (arkCallback) {
            auto helper = CallbackHelper(*arkCallback);
            checkNestedEvent->fired = true;
            std::printf("bindContent1: test7 *** fired *** low level dismissCallback arkCallback\n");

            helper.Invoke();

        }
    };
    auto arkDismissCallback = Converter::ArkValue<Callback_DismissContentCoverAction_Void>(dismissCallback, frameNode->GetId());

    struct CheckBuilderEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckBuilderEvent> checkBuilderEvent = std::nullopt;

    int32_t nodeId = EXPECTED_NODE_ID;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
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
        
        // test!!!
        FrameNode* parenFrametNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
        std::printf("bindContent1: test8 *** fired *** checkCallback builder  id: %d resourceId: %d parent: %d\n", 
        uiNode.value()->GetId(),  checkBuilderEvent->resourceId, parenFrametNode->GetId());
        // test!!! eof

        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };
    static constexpr int32_t contextId = EXPECTED_CONTEXT_ID;
    CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);

    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_ContentCoverOptions {
        .onWillDismiss = Converter::ArkValue<Opt_Callback_DismissContentCoverAction_Void>(arkDismissCallback),
    };
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);

    // test!!!
    {
        std::printf("bindContent1: test9 ============ start =========\n");
        // test show
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        RefPtr<ModalPresentationPattern> pattern = modal ? modal->GetPattern<ModalPresentationPattern>() : nullptr;
        std::printf("bindContent1: test10 const  modal:%s pattern:%s\n", modal ? "[+]" : "-", pattern ? "[+]" : "-");
    }
    // test!!! eof 

    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_EQ(modal, nullptr);
   
    modifier_->setBindContentCover1(node_, arkShow, &customBuilder, &optOptions);

    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_NE(modal, nullptr);
    auto pattern = modal->GetPattern<ModalPresentationPattern>();
    EXPECT_NE(pattern, nullptr);

    for (auto& [actual, expected] : bindSheetDissmisReasonTestPlan) {
        checkNestedEvent.reset();
        EXPECT_FALSE(checkNestedEvent.has_value());
    
    
    // test!!!
    {
    std::printf("bindContent1: test11 ============ ready =========\n");
    
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    auto pattern = modal->GetPattern<ModalPresentationPattern>();
    std::printf("bindContent1: test12 hover  modal:%s pattern:%s frameNode: %d transition: %d dismiss: %d\n", 
        modal ? "[+]" : "-", pattern ? "[+]" : "-", frameNode->GetId(), 
        std::underlying_type_t<ModalTransition>(pattern->GetType()), pattern->HasOnWillDismiss());
    std::printf("bindContent1: test14 hover dismiss func start actual: %d expected: %d\n", actual,
    expected?std::underlying_type_t<BindSheetDismissReason>(*expected):-1
    );
    std::printf("bindContent1: test14 before dismissCallback id: %d ark reason: %d fired: %d expected: %d\n", 
        checkNestedEvent->resourceId, 
        checkNestedEvent->reason?std::underlying_type_t<BindSheetDismissReason>(*checkNestedEvent->reason):-1,
        checkNestedEvent->fired,
        expected?std::underlying_type_t<BindSheetDismissReason>(*expected):-1
    );
    }
    // test!!! eof
   

    pattern->CallOnWillDismiss(actual);

    // test!!!
    {
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        auto pattern = modal->GetPattern<ModalPresentationPattern>();
        std::printf("bindContent1: test15 hover  modal:%s pattern:%s  transition: %d dismiss: %d\n",
            modal ? "[+]" : "-", pattern ? "[+]" : "-", std::underlying_type_t<ModalTransition>(pattern->GetType()),
            pattern->HasOnWillDismiss());
        std::printf("bindContent1: test15 after dismissCallback id: %d ark reason: %d fired: %d expected: %d\n",
            checkNestedEvent->resourceId,
            checkNestedEvent->reason ? std::underlying_type_t<BindSheetDismissReason>(*checkNestedEvent->reason) : -1,
            checkNestedEvent->fired,
            expected?std::underlying_type_t<BindSheetDismissReason>(*expected):-1
            );
    }
    // test!!! eof

    EXPECT_TRUE(checkNestedEvent.has_value());
    EXPECT_EQ(checkNestedEvent->resourceId, frameNode->GetId());
    EXPECT_EQ(checkNestedEvent->reason, expected);
    EXPECT_TRUE(checkNestedEvent->fired);

    }

    

}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1BackgroundColorTest, TestSize.Level1)
{
    std::printf("\nbindeContent1: test start\n\n");
    
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    
    // custom builder
    struct CheckBuilderEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckBuilderEvent> checkBuilderEvent = std::nullopt;

    int32_t nodeId = EXPECTED_NODE_ID;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
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

        // test!!!
        FrameNode* parenFrametNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
        std::printf("bindContent1: test8 *** fired *** checkCallback builder  id: %d resourceId: %d parent: %d\n", 
        uiNode.value()->GetId(),  checkBuilderEvent->resourceId, parenFrametNode->GetId());
        // test!!! eof

        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };
    static constexpr int32_t contextId = EXPECTED_CONTEXT_ID;
    CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);
    
    for(auto&[actual, expected]: colorTestPlan) {
        auto arkOptions = Ark_ContentCoverOptions {
            .backgroundColor = actual,
        };
        auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
       
        // test!!!
        {
            std::printf("bindContent1: test9 ============ start =========\n");
            // test show
            auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
            RefPtr<ModalPresentationPattern> pattern = modal ? modal->GetPattern<ModalPresentationPattern>() : nullptr;
            std::printf("bindContent1: test10 const  modal:%s pattern:%s\n",
                modal ? std::to_string(modal->GetId()).c_str() : "-", pattern ? "[+]" : "-");

            auto fullJson = GetJsonValue(node_);
            auto resultValue = GetAttrValue<std::string>(fullJson, "backgroundColor");
            std::printf("bindContent1: const fullJson: %s  modal: %s backgroundColor: %s actual: %s, expected: %s\n",
                resultValue.c_str(), modal ? std::to_string(modal->GetId()).c_str() : "-",
                modal ? modal->GetRenderContext()->GetBackgroundColor()->ToString().c_str() : "-",
                Converter::OptConvert<Color>(actual)?Converter::OptConvert<Color>(actual)->ToString().c_str():"-",
                expected.c_str());
        }
        // test!!! eof

        modifier_->setBindContentCover1(node_, arkShow, &customBuilder, &optOptions);

        // test!!!
        {
            std::printf("bindContent1: test11 ============ ready =========\n");

            auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
            auto pattern = modal->GetPattern<ModalPresentationPattern>();
            std::printf("bindContent1: test12 hover  modal:%s pattern:%s  transition: %d dismiss: %d\n",
                modal ? std::to_string(modal->GetId()).c_str() : "-", pattern ? "[+]" : "-",
                std::underlying_type_t<ModalTransition>(pattern->GetType()), pattern->HasOnWillDismiss());
       
            auto fullJson = GetJsonValue(node_);
            auto resultValue = GetAttrValue<std::string>(fullJson, "backgroundColor");
            std::printf("bindContent1: const fullJson backgroundColor: %s modal: %s backgroundColor: %s == %s\n",
                resultValue.c_str(), modal ? std::to_string(modal->GetId()).c_str() : "-",
                modal ? modal->GetRenderContext()->GetBackgroundColor()->ToString().c_str() : "-",
                expected.c_str());
        }
        // test!!! eof

        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        EXPECT_NE(modal, nullptr);
        auto context = modal->GetRenderContext();
        EXPECT_NE(context, nullptr);
        auto backgroundColor = context->GetBackgroundColor();
        EXPECT_TRUE(backgroundColor.has_value());
        EXPECT_EQ(backgroundColor->ToString(), expected);
    }
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setBindContentCover1ModalTransitionTest, TestSize.Level1)
{
    std::printf("\nbindeContent1: test start\n\n");
    
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    struct CheckBuilderEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckBuilderEvent> checkBuilderEvent = std::nullopt;

    int32_t nodeId = 555;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
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

        // test!!!       
        FrameNode* parenFrametNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
        std::printf("bindContent1: test8 *** fired *** checkCallback builder  id: %d resourceId: %d parent: %d\n", 
        uiNode.value()->GetId(),  checkBuilderEvent->resourceId, parenFrametNode->GetId());
        // test!!! eof

        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };
    static constexpr int32_t contextId = 123;
    CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);


    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);

    auto arkOptions = Ark_ContentCoverOptions {
        .modalTransition = Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_NONE),
    };

    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);

    std::printf("bindContent1: test9 ============ start =========\n");
    // test show
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    RefPtr<ModalPresentationPattern> pattern = modal ? modal->GetPattern<ModalPresentationPattern>() : nullptr;
    std::printf("bindContent1: test10 const  modal:%s pattern:%s\n", modal ? "[+]" : "-", pattern ? "[+]" : "-");

    modifier_->setBindContentCover1(node_, arkShow, &customBuilder, &optOptions);

    std::printf("bindContent1: test11 ============ ready =========\n");
    
    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    pattern = modal->GetPattern<ModalPresentationPattern>();
    std::printf("bindContent1: test12 hover  modal:%s pattern:%s  transition: %d dismiss: %d\n", 
        modal ? "[+]" : "-", pattern ? "[+]" : "-", 
        std::underlying_type_t<ModalTransition>(pattern->GetType()), pattern->HasOnWillDismiss());
   
 
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setBindContentCover1Test, TestSize.Level1)
{
    std::printf("\nbindeContent1: test start\n\n");
    
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    // callback
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onAppearCallback = [](Ark_Int32 nodeId) {
        checkEvent = {
            .nodeId = nodeId,
        };
        std::printf("bindContent1: test2 *** fired *** low level onAppearCallback id: %d\n", checkEvent.value().nodeId);
    };
    
    auto arkOnAppearCalback = Converter::ArkValue<Callback_Void>(onAppearCallback, frameNode->GetId());
    auto optOnAppearCalback = Converter::ArkValue<Opt_Callback_Void>(arkOnAppearCalback);
   
   auto onDisAppearCallback = [](Ark_Int32 nodeId) {
        checkEvent = {
            .nodeId = nodeId,
        };
        std::printf("bindContent1: test3 *** fired *** low level onDisAppearCallback id: %d\n", checkEvent.value().nodeId);
    };
    auto arkOnDisAppearCalback = Converter::ArkValue<Callback_Void>(onDisAppearCallback, frameNode->GetId());
    auto optOnDisAppearCalback = Converter::ArkValue<Opt_Callback_Void>(arkOnDisAppearCalback);


    auto onWillAppearCallback = [](Ark_Int32 nodeId) {
        checkEvent = {
            .nodeId = nodeId,
        };
        std::printf("bindContent1: test4 *** fired *** low level onWillAppearCallback id: %d\n", checkEvent.value().nodeId);
    };
    
    auto arkOnWillAppearCalback = Converter::ArkValue<Callback_Void>(onWillAppearCallback, frameNode->GetId());
    auto optOnWillAppearCalback = Converter::ArkValue<Opt_Callback_Void>(arkOnWillAppearCalback);
   
    auto onWillDisAppearCallback = [](Ark_Int32 nodeId) {
        checkEvent = {
            .nodeId = nodeId,
        };
        std::printf("bindContent1: test5 *** fired *** low level onWillDisAppearCallback id: %d\n", checkEvent.value().nodeId);
    };
    
    auto arkOnWillDisAppearCalback = Converter::ArkValue<Callback_Void>(onWillDisAppearCallback, frameNode->GetId());
    auto optOnWillDisAppearCalback = Converter::ArkValue<Opt_Callback_Void>(arkOnWillDisAppearCalback);
 

    // nested callback

    struct CheckNestedEvent {
        int32_t resourceId;
        std::optional<BindSheetDismissReason> reason;
    };
    static std::optional<CheckNestedEvent> checkNestedEvent = std::nullopt;
    auto dismissCallback = [](const Ark_Int32 resourceId, const Ark_DismissContentCoverAction parameter) {
        checkNestedEvent = {
            .resourceId = resourceId,
            .reason = Converter::OptConvert<BindSheetDismissReason>(parameter.reason)
        };
        auto arkCallback = Converter::OptConvert<Callback_Void>(parameter.dismiss);

        auto reason = checkNestedEvent->reason? std::underlying_type_t<BindSheetDismissReason>(*checkNestedEvent->reason):-1;
        std::printf("bindContent1: test6 *** fired *** dismissCallback id: %d arkCallback:%s ark reason: %d\n", 
        checkNestedEvent.value().resourceId, arkCallback?"[+]":"-", reason);

        if (arkCallback) {
            auto helper = CallbackHelper(*arkCallback);

            std::printf("bindContent1: test7 *** fired *** low level dismissCallback arkCallback\n");

            helper.Invoke();

        }
    };
   
    auto arkDismissCallback = Converter::ArkValue<Callback_DismissContentCoverAction_Void>(dismissCallback, frameNode->GetId());
    // auto optDismissCalback = Converter::ArkValue<Opt_Callback_DismissContentCoverAction_Void>(arkDismissCalback);

    
     // custom builder
    struct CheckBuilderEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckBuilderEvent> checkBuilderEvent = std::nullopt;

    int32_t nodeId = 555;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
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
        
        FrameNode* parenFrametNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
        std::printf("bindContent1: test8 *** fired *** checkCallback builder  id: %d resourceId: %d parent: %d\n", 
        uiNode.value()->GetId(),  checkBuilderEvent->resourceId, parenFrametNode->GetId());

        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };
    static constexpr int32_t contextId = 123;
    CustomNodeBuilder customBuilder = Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);


    // parameters
    auto arkShow = Converter::ArkValue<Ark_Boolean>(ACTUAL_TRUE);

    Ark_TransitionEffect arkEffect;
     auto arkScale = Ark_ScaleOptions {
        .centerX = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(7.0f),
        .centerY = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(12.0f),
        .x = Converter::ArkValue<Opt_Number>(10.0f),
        .y = Converter::ArkValue<Opt_Number>(20.0f),
        .z = Converter::ArkValue<Opt_Number>(25.0f),
    };
    const auto accessor = GeneratedModifier::GetFullAPI()->getAccessors()->getTransitionEffectAccessor();
    auto peer = accessor->scale(&arkScale);
    arkEffect.ptr = peer;
    
    auto arkOptions = Ark_ContentCoverOptions {
        .backgroundColor = Converter::ArkValue<Opt_ResourceColor>( Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE)),
        .modalTransition = Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_NONE),
        .onAppear = optOnAppearCalback,
        .onDisappear = optOnDisAppearCalback,
        .onWillAppear = optOnWillAppearCalback,
        .onWillDisappear = optOnWillDisAppearCalback,
        .onWillDismiss = Converter::ArkValue<Opt_Callback_DismissContentCoverAction_Void>(arkDismissCallback),
        // comment to get onAppear callback fired
        .transition = Converter::ArkValue<Opt_TransitionEffect>(arkEffect)
    };

    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);

    std::printf("bindContent1: test9 ============ start =========\n");
    // test show
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    RefPtr<ModalPresentationPattern> pattern = modal ? modal->GetPattern<ModalPresentationPattern>() : nullptr;
    std::printf("bindContent1: test10 const  modal:%s pattern:%s\n", modal ? "[+]" : "-", pattern ? "[+]" : "-");

    modifier_->setBindContentCover1(node_, arkShow, &customBuilder, &optOptions);

    std::printf("bindContent1: test11 ============ ready =========\n");
    
    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    pattern = modal->GetPattern<ModalPresentationPattern>();
    std::printf("bindContent1: test12 hover  modal:%s pattern:%s  transition: %d dismiss: %d\n", 
        modal ? "[+]" : "-", pattern ? "[+]" : "-", 
        std::underlying_type_t<ModalTransition>(pattern->GetType()), pattern->HasOnWillDismiss());
   
   
    auto reason = std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::SLIDE_DOWN);
    std::printf("bindContent1: test14 hover dismiss func start reason: %d\n", reason);
    pattern->CallOnWillDismiss(reason);

#ifdef CUSTOM_TIME_CODE
    int counter = 0;
    auto time = GetCurrentTimestamp();
    while (!checkEventDisAppear) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        time = GetCurrentTimestamp();
        std::printf("bindContent1: test12 sleep time: %zu\n", time);
        counter++;
        if (counter > 50) {
            break;
        }
    }
#endif

}

/**
 * @tc.name: setKeyboardShortcutTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setKeyboardShortcutTest, TestSize.Level1)
{
    std::printf("\nkeyboardShortcut: test start\n\n");

    ASSERT_NE(modifier_->setKeyboardShortcut, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto callback = [](Ark_Int32 nodeId) {
        checkEvent = {
            .nodeId = nodeId,
        };
    };
    
    // Callback_Void callBackValue = {
    //     .resource = Ark_CallbackResource {
    //         .resourceId = frameNode->GetId(),
    //         .hold = nullptr,
    //         .release = nullptr,
    //     },
    //     .call = callback
    // };
    auto arkCalback = Converter::ArkValue<Callback_Void>(callback, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCalback);
   
    // parameters
    auto value = Converter::ArkUnion<Ark_Union_String_FunctionKey, Ark_String>("A");
    std::vector<Ark_ModifierKey> modifiers = {
      Ark_ModifierKey::ARK_MODIFIER_KEY_ALT,
      Ark_ModifierKey::ARK_MODIFIER_KEY_SHIFT,
    };
    Converter::ArkArrayHolder<Array_ModifierKey> keyHolder(modifiers);
    Array_ModifierKey keys = keyHolder.ArkValue();

    std::printf("keyboard: const checkEvent: %d\n", checkEvent? checkEvent.value().nodeId:-1);

    modifier_->setKeyboardShortcut(node_, &value, &keys, &optCallback);
    EXPECT_FALSE(checkEvent.has_value());
    
    std::vector<KeyboardShortcut> shortcuts = eventHub->GetKeyboardShortcut();
    auto size  = shortcuts.size();
    std::printf("keyboard: holder  size: %zu\n", size);
    auto count  = 0;
    for(KeyboardShortcut& shortcut: shortcuts){
        std::printf("keyboard: holder  shorcut: %s count: %d\n", shortcut.value.c_str(), count);
        auto action  = shortcut.onKeyboardShortcutAction;
        if(action){
            std::printf("keyboard: holder  shorcut: %s count %d run \n", shortcut.value.c_str(), count);
            action();
        }
        std::printf("keyboard: holder checkEvent: %d == %d\n", checkEvent? checkEvent.value().nodeId:-1, frameNode->GetId());
        count++;
        checkEvent.reset();

    }


    
    // auto frameNode = reinterpret_cast<FrameNode*>(node_);
    // auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    // ASSERT_NE(eventHub, nullptr);

    // {
    //     InsertValueInfo checkValue = { .insertOffset = AINT32_POS, .insertValue = CHECK_TEXT };
    //     auto returnVal = eventHub->FireOnWillInsertValueEvent(checkValue);
    //     EXPECT_TRUE(returnVal);
    // }
    // {
    //     InsertValueInfo checkValue = { .insertOffset = AINT32_NEG, .insertValue = CHECK_TEXT };
    //     auto returnVal = eventHub->FireOnWillInsertValueEvent(checkValue);
    //     EXPECT_FALSE(returnVal);
    // }
}

HWTEST_F(CommonMethodModifierTest8, setBindContentCover0Test3, TestSize.Level1)
{
 int *p = nullptr;
 *p = 0;
}
}