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

    std::vector<std::tuple<Opt_ModalTransition, ModalTransition, bool>> modalTransitionTestPlan = {
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_DEFAULT), ModalTransition::DEFAULT, true },
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_NONE), ModalTransition::NONE, false },
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_ALPHA), ModalTransition::ALPHA, false },
        { Converter::ArkValue<Opt_ModalTransition>(static_cast<Ark_ModalTransition>(-1)), ModalTransition::DEFAULT,
            false },
        { Converter::ArkValue<Opt_ModalTransition>(Ark_Empty()), ModalTransition::DEFAULT, false },
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
HWTEST_F(CommonMethodModifierTest8, setBindContentCover0IsShowTest, TestSize.Level1)
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
    modifier_->setBindContentCover0(node_, arkShowTrue, &customBuilder, &optModal);

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
        
    auto arkShowFalse = Converter::ArkValue<Ark_Boolean>(ACTUAL_FALSE);
    checkEvent.reset();    

    // test show
    std::printf("bindContent0: test ============ start false =========\n");
    modalNode = uiNode->GetRawPtr()->GetParent();
    modalNodeId = modalNode? modalNode->GetId(): -1;
    std::printf("bindContent0: test const false uiNode: %d modalNode: %d\n",  uiNode->GetRawPtr()->GetId(), modalNodeId);
    // test show eof

    EXPECT_FALSE(checkEvent.has_value());
    modifier_->setBindContentCover0(node_, arkShowFalse, &customBuilder, &optModal);

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
HWTEST_F(CommonMethodModifierTest8, setBindContentCover0ModalTransitionTest, TestSize.Level1)
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

    for (auto& [actual, expected, builderCalled] : modalTransitionTestPlan) {
        checkEvent.reset();

        // test show
        {
        std::printf("bindContent0: test ============ start =========\n");
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        auto pattern = modal->GetPattern<ModalPresentationPattern>();
        auto transition = pattern? std::underlying_type_t<ModalTransition>(pattern->GetType()):-1;
        auto expectedTransition = std::underlying_type_t<ModalTransition>(expected);
        std::printf("bindContent0: test const uiNode: %d modal: %d pattern: %d == %d checkEvent: %d\n",
            uiNode->GetRawPtr()->GetId(), modal->GetId(), transition, expectedTransition, 
            checkEvent ? checkEvent->resourceId : -1);
        }
        // test show eof

        EXPECT_FALSE(checkEvent.has_value());
        modifier_->setBindContentCover0(node_, arkShowTrue, &customBuilder, &actual);
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        auto pattern = modal->GetPattern<ModalPresentationPattern>();

        // test show
        std::printf("bindContent0: test ============ end =========\n");
        auto transition = pattern? std::underlying_type_t<ModalTransition>(pattern->GetType()):-1;
        auto expectedTransition = std::underlying_type_t<ModalTransition>(expected);
        std::printf("bindContent0: test holder uiNode: %d modal: %d pattern: %d == %d checkEvent: %d\n",
            uiNode->GetRawPtr()->GetId(), modal->GetId(), transition, expectedTransition, 
            checkEvent ? checkEvent->resourceId : -1);
        // test show eof

        if (builderCalled) {
            EXPECT_TRUE(checkEvent.has_value());
            EXPECT_EQ(checkEvent->resourceId, contextId);
        } else {
            EXPECT_FALSE(checkEvent.has_value());
        }
        EXPECT_EQ(pattern->GetType(), expected);
    }
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setBindContentCover1Test, TestSize.Level1)
{
    std::printf("\nbindeContent1: test start\n\n");
   
}

/**
 * @tc.name: setKeyboardShortcutTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setKeyboardShortcutTest, TestSize.Level1)
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


    // eventHub->FireOnInputFilterError(ERROR_TEXT);
    // ASSERT_TRUE(checkEvent.has_value());
    // EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    // EXPECT_EQ(checkEvent->error, ERROR_TEXT);
    // auto attrValue = GetStringAttribute(node_, ATTRIBUTE_INPUT_FILTER_NAME);
    // EXPECT_EQ(attrValue, STR_TEST_TEXT);
    
    // checkEvent.reset();


    // static const auto CHECK_TEXT(u"test_text");
    // static const Ark_Int32 AINT32_POS(1234);
    // const Ark_Int32 AINT32_NEG(INT_MIN);

    // static const Ark_Int32 expectedResId = 123;
    // auto onWillInsertHandler = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_InsertValue data,
    //     const Callback_Boolean_Void cbReturn) {
    //     EXPECT_EQ(resourceId, expectedResId);
    //     EXPECT_EQ(Converter::Convert<std::u16string>(data.insertValue), CHECK_TEXT);
    //     auto result = Converter::Convert<int32_t>(data.insertOffset) > 0;
    //     CallbackHelper(cbReturn).Invoke(Converter::ArkValue<Ark_Boolean>(result));
    // };
    // auto arkCallback = Converter::ArkValue<Callback_InsertValue_Boolean>(nullptr, onWillInsertHandler, expectedResId);
    // modifier_->setOnWillInsert(node_, &arkCallback);

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