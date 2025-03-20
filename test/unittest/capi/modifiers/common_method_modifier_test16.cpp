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

#include <utility>

#include "common_method_modifier_test.h"
#include "generated/type_helpers.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/unittest/capi/stubs/mock_subwindow_bind.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"

#include "core/common/ace_engine.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/pipeline/pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;
namespace OHOS::Ace::NG {
namespace GeneratedModifier {
    const GENERATED_ArkUITransitionEffectAccessor* GetTransitionEffectAccessor();
}
namespace {
struct CheckEvent {
    int32_t resourceId;
    Ark_NativePointer parentNode;
};
static std::optional<CheckEvent> checkEvent = std::nullopt;
static std::optional<CheckEvent> checkEvent2 = std::nullopt;
static std::optional<RefPtr<UINode>> uiNode = std::nullopt;
static std::optional<RefPtr<NG::ChainedTransitionEffect>> previewTransition = std::nullopt;
static Ark_TransitionEffect effect = nullptr;
static Ark_TransitionEffects* arkEffects = nullptr;

constexpr auto MESSAGE = "message";
constexpr int32_t CONTAINER_INSTANCE_ID = 777;
constexpr auto TEST_RESOURCE_ID = 1000;
constexpr auto TEST_RESOURCE_ID_2 = 1000;
constexpr auto DEFAULT_RESPONSE_TYPE = ARK_RESPONSE_TYPE_RIGHT_CLICK;
static constexpr int32_t NODE_ID = 555;

constexpr auto SCALE_FROM_TEST_VALUE = 0.0f;
constexpr auto SCALE_TO_TEST_VALUE = 1.0f;

class ACE_EXPORT MockSubwindowBindTest : public MockSubwindowBind {
    DECLARE_ACE_TYPE(MockSubwindowBindTest, Subwindow)
public:
    bool InitContainer() override
    {
        childContainerId_ = CONTAINER_INSTANCE_ID;
        return true;
    }

    int32_t GetChildContainerId() const override
    {
        return childContainerId_;
    }

    void ShowMenuNG(std::function<void()>&& buildFunc, std::function<void()>&& previewBuildFunc,
        const NG::MenuParam& menuParam, const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset) override
    {
        CheckPreviewAnimationOptions(menuParam);
        if (previewBuildFunc && menuParam.previewMode == MenuPreviewMode::CUSTOM &&
            menuParam.contextMenuRegisterType != NG::ContextMenuRegisterType::CUSTOM_TYPE) {
            CheckHoverImageAnimationOptions(menuParam);
        }
        MockSubwindowBind::ShowMenuNG(std::move(buildFunc), std::move(previewBuildFunc), menuParam, targetNode, offset);
    }

private:
    int32_t childContainerId_ = -1;

    void CheckPreviewAnimationOptions(const NG::MenuParam& menuParam)
    {
        EXPECT_EQ(menuParam.previewAnimationOptions.scaleFrom, SCALE_FROM_TEST_VALUE);
        EXPECT_EQ(menuParam.previewAnimationOptions.scaleTo, SCALE_TO_TEST_VALUE);
    }
    void CheckHoverImageAnimationOptions(const NG::MenuParam& menuParam)
    {
        EXPECT_TRUE(menuParam.hasPreviewTransitionEffect);
        EXPECT_TRUE(previewTransition);
        EXPECT_EQ(menuParam.previewTransition, previewTransition);
        EXPECT_EQ(menuParam.hoverImageAnimationOptions.scaleFrom, SCALE_FROM_TEST_VALUE);
        EXPECT_EQ(menuParam.hoverImageAnimationOptions.scaleTo, SCALE_TO_TEST_VALUE);
    }
};

CustomNodeBuilder getBuilderCb()
{
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                             const Callback_Pointer_Void continuation) {
        checkEvent = { .resourceId = resourceId, .parentNode = parentNode };
        if (uiNode) {
            CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
        }
    };
    CustomNodeBuilder customBuilder = ArkValue<CustomNodeBuilder>(nullptr, checkCallback, TEST_RESOURCE_ID);
    return customBuilder;
}

Opt_AnimationRange_Number getAnimationRange()
{
    Ark_AnimationRange_Number range;
    range.value0 = ArkValue<Ark_Number>(SCALE_FROM_TEST_VALUE);
    range.value1 = ArkValue<Ark_Number>(SCALE_TO_TEST_VALUE);
    return ArkValue<Opt_AnimationRange_Number>(range);
}

Opt_TransitionEffect getTransitionEffect()
{
    if (!previewTransition) {
        // TransitionEffect is abstract class
        previewTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    }
    effect = ArkValue<Ark_TransitionEffect>(previewTransition.value());
    return ArkValue<Opt_TransitionEffect>(effect);
}

Opt_ContextMenuAnimationOptions getContextMenuAnimationOptions()
{
    Ark_ContextMenuAnimationOptions options;
    options.scale = getAnimationRange();
    options.transition = getTransitionEffect();
    options.hoverScale = getAnimationRange();
    return ArkValue<Opt_ContextMenuAnimationOptions>(options);
}

Opt_Union_MenuPreviewMode_CustomBuilder getPreviewCustomBuilder()
{
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                             const Callback_Pointer_Void continuation) {
        checkEvent2 = { .resourceId = resourceId, .parentNode = parentNode };
        if (uiNode) {
            CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
        }
    };
    CustomNodeBuilder customBuilder = ArkValue<CustomNodeBuilder>(nullptr, checkCallback, TEST_RESOURCE_ID_2);
    auto builderUnion = ArkUnion<Ark_Union_MenuPreviewMode_CustomBuilder, CustomNodeBuilder>(customBuilder);
    return ArkValue<Opt_Union_MenuPreviewMode_CustomBuilder>(builderUnion);
}

Opt_ContextMenuOptions getContextMenuOptions()
{
    Ark_ContextMenuOptions options;
    options.previewAnimationOptions = getContextMenuAnimationOptions();
    options.preview = getPreviewCustomBuilder();
    return ArkValue<Opt_ContextMenuOptions>(options);
}
} // namespace

namespace Converter {
void AssignArkValue(Ark_TransitionEffect& dst, const RefPtr<NG::ChainedTransitionEffect>& src)
{
    Ark_String arkType = Converter::ArkValue<Ark_String>(MESSAGE);
    arkEffects = new (Ark_TransitionEffects);
    const auto peer = GeneratedModifier::GetTransitionEffectAccessor()->ctor(&arkType, arkEffects);
    peer->handler = src;
    dst = peer;
}
} // namespace Converter

class CommonMethodModifierTest16 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
                                       &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
                                       GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
                                       > {
public:
    void* CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<SelectTheme>();
    }
};

/*
 * @tc.name: BindContextMenu0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, BindContextMenu0Test, TestSize.Level1)
{
    auto containerId = Container::CurrentId();
    uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto taskExecutorFalse = AceType::MakeRefPtr<MockTaskExecutor>(false);
    MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutorFalse);
    auto builder = getBuilderCb();
    auto options = getContextMenuOptions();
    modifier_->setBindContextMenu0(node_, &builder, DEFAULT_RESPONSE_TYPE, &options);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_TRUE(eventHub);
    auto focusHub = eventHub->GetFocusHub();
    ASSERT_TRUE(focusHub);
    KeyEvent event;
    event.code = KeyCode::KEY_MENU;
    event.action = KeyAction::DOWN;
    event.keyIntention = KeyIntention::INTENTION_MENU;
    auto subwindowBind = AceType::MakeRefPtr<MockSubwindowBindTest>();
    SubwindowManager::GetInstance()->AddSubwindow(containerId, subwindowBind);
    SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindowBind);
    focusHub->ProcessOnKeyEventInternal(event);

    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, TEST_RESOURCE_ID);
    checkEvent->parentNode = nullptr;
    checkEvent = std::nullopt;
    checkEvent2 = std::nullopt;
    uiNode->Reset();
    previewTransition->Reset();
    auto inputEventHub = eventHub->GetInputEventHub();
    inputEventHub->ClearUserOnMouse();
    previewTransition = std::nullopt;
    uiNode = std::nullopt;
    SubwindowManager::GetInstance()->RemoveSubwindow(containerId);
    GeneratedModifier::GetTransitionEffectAccessor()->destroyPeer(effect);
    effect = nullptr;
    arkEffects = nullptr;
}

/*
 * @tc.name: BindContextMenu0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, BindContextMenu1Test, TestSize.Level1)
{
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(CONTAINER_INSTANCE_ID, MockContainer::container_);
    auto containerId = Container::CurrentId();
    uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto taskExecutorFalse = AceType::MakeRefPtr<MockTaskExecutor>(true);
    MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutorFalse);
    auto builder = getBuilderCb();
    auto options = getContextMenuOptions();
    auto isShown = ArkValue<Ark_Boolean>(true);
    auto subwindowBind = AceType::MakeRefPtr<MockSubwindowBindTest>();
    subwindowBind->InitContainer();
    SubwindowManager::GetInstance()->AddSubwindow(containerId, subwindowBind);
    SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindowBind);
    EXPECT_CALL(*subwindowBind, GetOverlayManager()).Times(1);
    modifier_->setBindContextMenu1(node_, isShown, &builder, &options);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, TEST_RESOURCE_ID);
    checkEvent->parentNode = nullptr;
    checkEvent = std::nullopt;
    checkEvent2 = std::nullopt;
    uiNode->Reset();
    previewTransition->Reset();
    previewTransition = std::nullopt;
    uiNode = std::nullopt;
    SubwindowManager::GetInstance()->RemoveSubwindow(containerId);
    aceEngine.RemoveContainer(CONTAINER_INSTANCE_ID);
    GeneratedModifier::GetTransitionEffectAccessor()->destroyPeer(effect);
    effect = nullptr;
    arkEffects = nullptr;
}
} // namespace OHOS::Ace::NG