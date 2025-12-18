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
#include "test/unittest/core/base/view_abstract_test_ng.h"
#include "common_method_modifier_test.h"
#include "generated/test_fixtures.h"
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
static std::optional<MenuParam> menuParams = std::nullopt;
static Ark_TransitionEffect effect = nullptr;

constexpr int32_t CONTAINER_INSTANCE_ID = 777;
constexpr auto TEST_RESOURCE_ID = 1000;
constexpr auto TEST_RESOURCE_ID_2 = 1000;
constexpr auto DEFAULT_RESPONSE_TYPE = ARK_RESPONSE_TYPE_RIGHT_CLICK;
static constexpr int32_t NODE_ID = 555;

constexpr auto SCALE_FROM_TEST_VALUE = 0.0f;
constexpr auto SCALE_TO_TEST_VALUE = 1.0f;

constexpr auto LENGTH_TEST_VALUE = 1.0_vp;
constexpr auto X_LENGTH_TEST_VALUE = 1.1f;
constexpr auto Y_LENGTH_TEST_VALUE = 2.2f;

const std::vector<std::tuple<std::string, Ark_Placement, Placement>> testFixtureEnumPlacementValidValues = {
    { "ARK_PLACEMENT_LEFT", ARK_PLACEMENT_LEFT, Placement::LEFT },
    { "ARK_PLACEMENT_RIGHT", ARK_PLACEMENT_RIGHT, Placement::RIGHT },
    { "ARK_PLACEMENT_TOP", ARK_PLACEMENT_TOP, Placement::TOP },
    { "ARK_PLACEMENT_BOTTOM", ARK_PLACEMENT_BOTTOM, Placement::BOTTOM },
    { "ARK_PLACEMENT_TOP_LEFT", ARK_PLACEMENT_TOP_LEFT, Placement::TOP_LEFT },
    { "ARK_PLACEMENT_TOP_RIGHT", ARK_PLACEMENT_TOP_RIGHT, Placement::TOP_RIGHT },
    { "ARK_PLACEMENT_BOTTOM_LEFT", ARK_PLACEMENT_BOTTOM_LEFT, Placement::BOTTOM_LEFT },
    { "ARK_PLACEMENT_BOTTOM_RIGHT", ARK_PLACEMENT_BOTTOM_RIGHT, Placement::BOTTOM_RIGHT },
    { "ARK_PLACEMENT_LEFT_TOP", ARK_PLACEMENT_LEFT_TOP, Placement::LEFT_TOP },
    { "ARK_PLACEMENT_LEFT_BOTTOM", ARK_PLACEMENT_LEFT_BOTTOM, Placement::LEFT_BOTTOM },
    { "ARK_PLACEMENT_RIGHT_TOP", ARK_PLACEMENT_RIGHT_TOP, Placement::RIGHT_TOP },
    { "ARK_PLACEMENT_RIGHT_BOTTOM", ARK_PLACEMENT_RIGHT_BOTTOM, Placement::RIGHT_BOTTOM },
    { "INVALID_ENUM_VAL", INVALID_ENUM_VAL<Ark_Placement>, Placement::BOTTOM_LEFT },
};

const std::vector<std::tuple<std::string, Ark_Boolean, bool>> testFixtureBooleanValidValues = {
    { "true", ArkValue<Ark_Boolean>(true), true },
    { "false", ArkValue<Ark_Boolean>(false), false },
};

const std::vector<std::tuple<std::string, Ark_Length, CalcDimension>> testFixtureDimensionAnyValidValues = {
    { "123.0vp", ArkValue<Ark_Length>("123.0vp"), 123.0_vp },
    { "0.0vp", ArkValue<Ark_Length>("0.0vp"), 0.0_vp },
    { "1.23vp", ArkValue<Ark_Length>("1.23vp"), 1.23_vp },
    { "123.0fp", ArkValue<Ark_Length>("123.0fp"), 123.0_fp },
    { "0.0fp", ArkValue<Ark_Length>("0.0fp"), 0.0_fp },
    { "1.23fp", ArkValue<Ark_Length>("1.23fp"), 1.23_fp },
    { "123.0px", ArkValue<Ark_Length>("123.0px"), 123.0_px },
    { "0.0px", ArkValue<Ark_Length>("0.0px"), 0.0_px },
    { "1.23px", ArkValue<Ark_Length>("1.23px"), 1.23_px },
    { "-2.3vp", ArkValue<Ark_Length>("-2.3vp"), -2.3_vp },
    { "-4.5fp", ArkValue<Ark_Length>("-4.5fp"), -4.5_fp },
    { "-5.6px", ArkValue<Ark_Length>("-5.6px"), -5.6_px },
    { "50%", ArkValue<Ark_Length>("50%"), 0.5_pct },
    { "0%", ArkValue<Ark_Length>("0%"), 0.0_pct },
    { "-80%", ArkValue<Ark_Length>("-80%"), -0.8_pct },
};

const std::vector<std::tuple<std::string, Ark_MenuPreviewMode, MenuPreviewMode>> testFixtureMenuPreviewMode = {
    { "ARK_MENU_PREVIEW_MODE_NONE", ARK_MENU_PREVIEW_MODE_NONE, MenuPreviewMode::NONE },
    { "ARK_MENU_PREVIEW_MODE_IMAGE", ARK_MENU_PREVIEW_MODE_IMAGE, MenuPreviewMode::IMAGE },
    { "ARK_MENU_PREVIEW_MODE_INVALID", INVALID_ENUM_VAL<Ark_MenuPreviewMode>, MenuPreviewMode::NONE },
};

const std::vector<std::tuple<std::string, Ark_BlurStyle, BlurStyle>> testFixtureBlurStyleActivePolicyValidValues = {
    { "ARK_BLUR_STYLE_THIN", ARK_BLUR_STYLE_THIN, BlurStyle::THIN },
    { "ARK_BLUR_STYLE_REGULAR", ARK_BLUR_STYLE_REGULAR, BlurStyle::REGULAR },
    { "ARK_BLUR_STYLE_THICK", ARK_BLUR_STYLE_THICK, BlurStyle::THICK },
    { "ARK_BLUR_STYLE_BACKGROUND_THIN", ARK_BLUR_STYLE_BACKGROUND_THIN, BlurStyle::BACKGROUND_THIN },
    { "ARK_BLUR_STYLE_BACKGROUND_REGULAR", ARK_BLUR_STYLE_BACKGROUND_REGULAR, BlurStyle::BACKGROUND_REGULAR },
    { "ARK_BLUR_STYLE_BACKGROUND_THICK", ARK_BLUR_STYLE_BACKGROUND_THICK, BlurStyle::BACKGROUND_THICK },
    { "ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK", ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK,
        BlurStyle::BACKGROUND_ULTRA_THICK },
    { "ARK_BLUR_STYLE_NONE", ARK_BLUR_STYLE_NONE, BlurStyle::NO_MATERIAL },
    { "ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN", ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN, BlurStyle::COMPONENT_ULTRA_THIN },
    { "ARK_BLUR_STYLE_COMPONENT_THIN", ARK_BLUR_STYLE_COMPONENT_THIN, BlurStyle::COMPONENT_THIN },
    { "ARK_BLUR_STYLE_COMPONENT_REGULAR", ARK_BLUR_STYLE_COMPONENT_REGULAR, BlurStyle::COMPONENT_REGULAR },
    { "ARK_BLUR_STYLE_COMPONENT_THICK", ARK_BLUR_STYLE_COMPONENT_THICK, BlurStyle::COMPONENT_THICK },
    { "ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK", ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK, BlurStyle::COMPONENT_ULTRA_THICK },
};

const std::vector<std::tuple<std::string, Ark_BlurStyle>> testFixtureEnumBlurStyleInvalidValues = {
    { "-1", static_cast<Ark_BlurStyle>(-1) },
    { "INT_MAX", static_cast<Ark_BlurStyle>(INT_MAX) },
};

class ACE_EXPORT MockSubwindowBindTest : public MockSubwindowBind {
    DECLARE_ACE_TYPE(MockSubwindowBindTest, Subwindow)
public:
    void InitContainer() override
    {
        childContainerId_ = CONTAINER_INSTANCE_ID;
        SetIsRosenWindowCreate(true);
    }

    int32_t GetChildContainerId() const override
    {
        return childContainerId_;
    }

    void ShowMenuNG(std::function<void()>&& buildFunc, std::function<void()>&& previewBuildFunc,
        const NG::MenuParam& menuParam, const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset) override
    {
        menuParams = menuParam;
        CheckOffsetOption(menuParam);
        CheckPreviewAnimationOptions(menuParam);
        if (previewBuildFunc && menuParam.previewMode == MenuPreviewMode::CUSTOM &&
            !menuParam.hasPreviewTransitionEffect && !menuParam.hasTransitionEffect &&
            menuParam.contextMenuRegisterType != NG::ContextMenuRegisterType::CUSTOM_TYPE) {
            CheckHoverImageAnimationOptions(menuParam);
        }
        MockSubwindowBind::ShowMenuNG(std::move(buildFunc), std::move(previewBuildFunc), menuParam, targetNode, offset);
    }

    void SetWindowTouchable(bool touchable) override
    {
    }

private:
    int32_t childContainerId_ = -1;

    void CheckOffsetOption(const NG::MenuParam& menuParam)
    {
        EXPECT_EQ(menuParam.positionOffset.GetX(), X_LENGTH_TEST_VALUE);
        EXPECT_EQ(menuParam.positionOffset.GetY(), Y_LENGTH_TEST_VALUE);
    }

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

Opt_Position getOffset()
{
    Ark_Position arkPosition = {
        .x = ArkValue<Opt_Length>(ArkValue<Ark_Length>(X_LENGTH_TEST_VALUE)),
        .y = ArkValue<Opt_Length>(ArkValue<Ark_Length>(Y_LENGTH_TEST_VALUE))
    };
    return ArkValue<Opt_Position>(arkPosition);
}

Opt_Placement getPlacement(const Ark_Placement& placement = INVALID_ENUM_VAL<Ark_Placement>)
{
    return ArkValue<Opt_Placement>(placement);
}

CustomNodeBuilder getBuilderCb()
{
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                             const Callback_Pointer_Void continuation) {
        checkEvent = { .resourceId = resourceId, .parentNode = parentNode };
        if (uiNode) {
            CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
        }
    };
    CustomNodeBuilder customBuilder = ArkValue<CustomNodeBuilder>(checkCallback, nullptr, TEST_RESOURCE_ID);
    return customBuilder;
}

Opt_AnimationNumberRange getAnimationRange()
{
    Ark_AnimationNumberRange range;
    range.value0 = ArkValue<Ark_Float64>(SCALE_FROM_TEST_VALUE);
    range.value1 = ArkValue<Ark_Float64>(SCALE_TO_TEST_VALUE);
    return ArkValue<Opt_AnimationNumberRange>(range);
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

Opt_Union_MenuPreviewMode_CustomNodeBuilder getPreviewCustomBuilder()
{
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                             const Callback_Pointer_Void continuation) {
        checkEvent2 = { .resourceId = resourceId, .parentNode = parentNode };
        if (uiNode) {
            CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
        }
    };
    CustomNodeBuilder customBuilder = ArkValue<CustomNodeBuilder>(checkCallback, nullptr, TEST_RESOURCE_ID_2);
    auto builderUnion = ArkUnion<Ark_Union_MenuPreviewMode_CustomNodeBuilder, CustomNodeBuilder>(customBuilder);
    return ArkValue<Opt_Union_MenuPreviewMode_CustomNodeBuilder>(builderUnion);
}

Opt_ContextMenuOptions getContextMenuOptions(Ark_ContextMenuOptions options = {})
{
    options.offset = getOffset();
    options.previewAnimationOptions = getContextMenuAnimationOptions();
    return ArkValue<Opt_ContextMenuOptions>(options);
}
} // namespace

namespace Converter {
void AssignArkValue(Ark_TransitionEffect& dst, const RefPtr<NG::ChainedTransitionEffect>& src)
{
    const auto peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
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
        auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);
        MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutor);
        MockContainer::Current()->SetTaskExecutor(taskExecutor);
        SetupTheme<SelectTheme>();
        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
    static void InitBindContextMenu0()
    {
        uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
    }

    static AceEngine& InitBindContextMenu1()
    {
        AceEngine& aceEngine = AceEngine::Get();
        aceEngine.AddContainer(CONTAINER_INSTANCE_ID, MockContainer::container_);
        uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
        return aceEngine;
    }

    static void TearDownTestCase()
    {
        MockContainer::Current()->SetTaskExecutor(nullptr);
        ModifierTestBase::TearDownTestCase();
    }

    static void EmitFocusEvent(Ark_NodeHandle node)
    {
        auto containerId = Container::CurrentId();
        auto frameNode = reinterpret_cast<FrameNode*>(node);
        auto eventHub = frameNode->GetEventHub<EventHub>();
        ASSERT_TRUE(eventHub);
        auto focusHub = eventHub->GetFocusHub();
        ASSERT_TRUE(focusHub);
        KeyEvent event;
        event.code = KeyCode::KEY_MENU;
        event.action = KeyAction::DOWN;
        event.keyIntention = KeyIntention::INTENTION_MENU;
        auto subwindowBind = AceType::MakeRefPtr<::testing::NiceMock<MockSubwindowBindTest>>();
        subwindowBind->InitContainer();
        SubwindowManager::GetInstance()->AddSubwindow(containerId, SubwindowType::TYPE_MENU, subwindowBind);
        SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindowBind);
        focusHub->ProcessOnKeyEventInternal(event);
    }

    static void EmitLongPressEvent(Ark_NodeHandle node)
    {
        auto containerId = Container::CurrentId();
        auto frameNode = reinterpret_cast<FrameNode*>(node);
        auto eventHub = frameNode->GetEventHub<EventHub>();
        ASSERT_TRUE(eventHub);
        auto gestureEventHub = eventHub->GetGestureEventHub();
        ASSERT_TRUE(gestureEventHub);
        auto subwindowBind = AceType::MakeRefPtr<MockSubwindowBindTest>();
        subwindowBind->InitContainer();
        SubwindowManager::GetInstance()->AddSubwindow(containerId, SubwindowType::TYPE_MENU, subwindowBind);
        SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindowBind);
        gestureEventHub->ActLongClick();
    }

    static void ResetParams(Ark_NodeHandle node)
    {
        auto containerId = Container::CurrentId();
        checkEvent->parentNode = nullptr;
        checkEvent = std::nullopt;
        checkEvent2 = std::nullopt;
        menuParams = std::nullopt;
        uiNode->Reset();
        uiNode = std::nullopt;
        previewTransition->Reset();
        previewTransition = std::nullopt;
        auto frameNode = reinterpret_cast<FrameNode*>(node);
        auto eventHub = frameNode->GetEventHub<EventHub>();
        SubwindowManager::GetInstance()->RemoveSubwindow(containerId, SubwindowType::TYPE_MENU);
        GeneratedModifier::GetTransitionEffectAccessor()->destroyPeer(effect);
        effect = nullptr;
        CHECK_NULL_VOID(eventHub);
        auto inputEventHub = eventHub->GetInputEventHub();
        CHECK_NULL_VOID(inputEventHub);
        inputEventHub->ClearUserOnMouse();
    }

    static void ResetAceEngine(Ark_NodeHandle node, AceEngine& aceEngine)
    {
        ResetParams(node);
        aceEngine.RemoveContainer(CONTAINER_INSTANCE_ID);
    }

    static void SetSubwindow()
    {
        auto containerId = Container::CurrentId();
        auto subwindowBind = AceType::MakeRefPtr<MockSubwindowBindTest>();
        subwindowBind->InitContainer();
        SubwindowManager::GetInstance()->AddSubwindow(containerId, subwindowBind);
        SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindowBind);
        EXPECT_CALL(*subwindowBind, GetOverlayManager()).Times(AnyNumber());
    }
};

/*
 * @tc.name: BindContextMenu0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0Test, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    CommonMethodModifierTest16::InitBindContextMenu0();
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(DEFAULT_RESPONSE_TYPE);
    auto options = getContextMenuOptions();
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    CommonMethodModifierTest16::EmitFocusEvent(node_);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, TEST_RESOURCE_ID);
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestPlacementTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestPlacementTest, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(DEFAULT_RESPONSE_TYPE);
    for (auto& [text, value, expected] : testFixtureEnumPlacementValidValues) {
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .placement = getPlacement(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitFocusEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->placement, expected) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetParams(node_);
    }
}

/*
 * @tc.name: BindContextMenu0TestEnableArrow
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestEnableArrow, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(DEFAULT_RESPONSE_TYPE);
    for (auto& [text, value, expected] : testFixtureBooleanValidValues) {
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .placement = ArkValue<Opt_Placement>(),
            .enableArrow = ArkValue<Opt_Boolean>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitFocusEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->enableArrow, expected) << "Passed value is: " << text;
        auto expectedPlacement = expected ? Placement::TOP : Placement::BOTTOM_LEFT;
        EXPECT_EQ(menuParams->placement, expectedPlacement) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetParams(node_);
    }
}

/*
 * @tc.name: BindContextMenu0TestArrowOffset
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestArrowOffset, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(DEFAULT_RESPONSE_TYPE);
    for (auto& [text, value, expected] : testFixtureDimensionAnyValidValues) {
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .arrowOffset = ArkValue<Opt_Length>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitFocusEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->arrowOffset, expected) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetParams(node_);
    }
}

/*
 * @tc.name: BindContextMenu0TestPreviewPreviewMode
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestPreviewPreviewMode, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    for (auto& [text, value, expected] : testFixtureMenuPreviewMode) {
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .preview = ArkUnion<Opt_Union_MenuPreviewMode_CustomNodeBuilder, Ark_MenuPreviewMode>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitFocusEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->previewMode, expected) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetParams(node_);
    }
}

/*
 * @tc.name: BindContextMenu0TestPreviewCustomBuilder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestPreviewCustomBuilder, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    Ark_ContextMenuOptions optionsPlacement = {
        .preview = getPreviewCustomBuilder(),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(menuParams);
    EXPECT_EQ(menuParams->previewMode, MenuPreviewMode::CUSTOM)
        << "Passed value is: " << static_cast<int>(MenuPreviewMode::CUSTOM);
    ASSERT_TRUE(checkEvent2);
    EXPECT_EQ(checkEvent2->resourceId, TEST_RESOURCE_ID_2);
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestBorderRadiusLength
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestBorderRadiusLength, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    auto arkLength = ArkValue<Ark_Length>(LENGTH_TEST_VALUE);
    auto radiuses = ArkUnion<Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses, Ark_Length>(arkLength);
    Ark_ContextMenuOptions optionsPlacement = {
        .borderRadius = ArkValue<Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses>(radiuses),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(menuParams);
    ASSERT_TRUE(menuParams->borderRadius);
    EXPECT_THAT(menuParams->borderRadius.value(), CompareBorderRadius(LENGTH_TEST_VALUE, false));
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestBorderRadiusBorderRadiuses
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestBorderRadiusBorderRadiuses, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    auto arkLength = ArkValue<Ark_Length>(LENGTH_TEST_VALUE);
    Ark_BorderRadiuses arkRadiuses = {
        .topLeft = ArkValue<Opt_Length>(arkLength),
        .topRight = ArkValue<Opt_Length>(arkLength),
        .bottomLeft = ArkValue<Opt_Length>(arkLength),
        .bottomRight = ArkValue<Opt_Length>(arkLength),
    };
    auto radiuses = ArkUnion<Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses, Ark_BorderRadiuses>(arkRadiuses);
    Ark_ContextMenuOptions optionsPlacement = {
        .borderRadius = ArkValue<Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses>(radiuses),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(menuParams);
    ASSERT_TRUE(menuParams->borderRadius);
    EXPECT_THAT(menuParams->borderRadius.value(), CompareBorderRadius(LENGTH_TEST_VALUE, false));
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestBorderRadiusLocalizedRadius
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestBorderRadiusLocalizedRadius, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    auto arkLength = ArkValue<Ark_LengthMetrics>(LENGTH_TEST_VALUE);
    Ark_LocalizedBorderRadiuses arkRadiuses = {
        .topStart = ArkValue<Opt_LengthMetrics>(arkLength),
        .topEnd = ArkValue<Opt_LengthMetrics>(arkLength),
        .bottomStart = ArkValue<Opt_LengthMetrics>(arkLength),
        .bottomEnd = ArkValue<Opt_LengthMetrics>(arkLength),
    };
    auto radiuses =
        ArkUnion<Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses, Ark_LocalizedBorderRadiuses>(arkRadiuses);
    Ark_ContextMenuOptions optionsPlacement = {
        .borderRadius = ArkValue<Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses>(radiuses),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(menuParams);
    ASSERT_TRUE(menuParams->borderRadius);
    EXPECT_THAT(menuParams->borderRadius.value(), CompareBorderRadius(LENGTH_TEST_VALUE, true));
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestOnAppear
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestOnAppear, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkCallbackEvent = std::nullopt;
    auto onAppear = [](const Ark_Int32 resourceId) {
        checkCallbackEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
        };
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto arkCallback = ArkValue<Callback_Void>(onAppear, frameNode->GetId());
    Ark_ContextMenuOptions optionsPlacement = {
        .onAppear = ArkValue<Opt_Callback_Void>(arkCallback),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    EXPECT_FALSE(checkCallbackEvent);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(checkCallbackEvent);
    EXPECT_EQ(checkCallbackEvent->nodeId, frameNode->GetId());
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestOnDisappear
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestOnDisappear, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkCallbackEvent = std::nullopt;
    auto onDisappear = [](const Ark_Int32 resourceId) {
        checkCallbackEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
        };
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto arkCallback = ArkValue<Callback_Void>(onDisappear, frameNode->GetId());
    Ark_ContextMenuOptions optionsPlacement = {
        .onDisappear = ArkValue<Opt_Callback_Void>(arkCallback),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    EXPECT_FALSE(checkCallbackEvent);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(checkCallbackEvent);
    EXPECT_EQ(checkCallbackEvent->nodeId, frameNode->GetId());
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestAboutToAppear
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestAboutToAppear, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkCallbackEvent = std::nullopt;
    auto aboutToAppear = [](const Ark_Int32 resourceId) {
        checkCallbackEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
        };
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto arkCallback = ArkValue<Callback_Void>(aboutToAppear, frameNode->GetId());
    Ark_ContextMenuOptions optionsPlacement = {
        .aboutToAppear = ArkValue<Opt_Callback_Void>(arkCallback),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    EXPECT_FALSE(checkCallbackEvent);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(checkCallbackEvent);
    EXPECT_EQ(checkCallbackEvent->nodeId, frameNode->GetId());
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestAboutToDisappear
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestAboutToDisappear, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkCallbackEvent = std::nullopt;
    auto aboutToDisappear = [](const Ark_Int32 resourceId) {
        checkCallbackEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
        };
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto arkCallback = ArkValue<Callback_Void>(aboutToDisappear, frameNode->GetId());
    Ark_ContextMenuOptions optionsPlacement = {
        .aboutToDisappear = ArkValue<Opt_Callback_Void>(arkCallback),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    EXPECT_FALSE(checkCallbackEvent);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(checkCallbackEvent);
    EXPECT_EQ(checkCallbackEvent->nodeId, frameNode->GetId());
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestLayoutRegionMargin
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestLayoutRegionMargin, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    auto arkLength = ArkValue<Ark_Length>(LENGTH_TEST_VALUE);
    Ark_Padding arkPadding = {
        .left = ArkValue<Opt_Length>(arkLength),
        .right = ArkValue<Opt_Length>(arkLength),
        .bottom = ArkValue<Opt_Length>(arkLength),
        .top = ArkValue<Opt_Length>(arkLength),
    };
    Ark_ContextMenuOptions optionsPlacement = {
        .layoutRegionMargin = ArkValue<Opt_Padding>(arkPadding),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(menuParams);
    ASSERT_TRUE(menuParams->layoutRegionMargin);
    EXPECT_THAT(menuParams->layoutRegionMargin.value(), CompareMarginPadding(CalcLength(LENGTH_TEST_VALUE)));
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestBackgroundColorValidValues, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto checkValue = [this](const std::string& input, const std::string& expected, Opt_ResourceColor colorValue) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .backgroundColor = colorValue,
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitLongPressEvent(node_);
        ASSERT_TRUE(menuParams);
        ASSERT_TRUE(menuParams->backgroundColor);
        EXPECT_THAT(menuParams->backgroundColor->ToString(), expected) << "Color: " << input;
        CommonMethodModifierTest16::ResetParams(node_);
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}
/*
 * @tc.name: BindContextMenu0TestBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestBackgroundColorInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto checkValue = [this](const std::string& input, Opt_ResourceColor colorValue) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .backgroundColor = colorValue,
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitLongPressEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_FALSE(menuParams->backgroundColor) << "Color: " << input;
        CommonMethodModifierTest16::ResetParams(node_);
    };
    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: BindContextMenu0TestBackgroundBlurStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestBackgroundBlurStyleValidValues, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    for (auto& [input, value, expected] : testFixtureBlurStyleActivePolicyValidValues) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .backgroundBlurStyle = ArkValue<Opt_BlurStyle>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitLongPressEvent(node_);
        ASSERT_TRUE(menuParams);
        ASSERT_TRUE(menuParams->backgroundBlurStyle) << "BlurStyle: " << input;
        EXPECT_EQ(menuParams->backgroundBlurStyle, static_cast<int32_t>(expected))
            << "BlurStyleActivePolicy: " << input;
        CommonMethodModifierTest16::ResetParams(node_);
    }
}

/*
 * @tc.name: BindContextMenu0TestBackgroundBlurStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestBackgroundBlurStyleInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    for (auto& [input, value] : testFixtureEnumBlurStyleInvalidValues) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .backgroundBlurStyle = ArkValue<Opt_BlurStyle>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitLongPressEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_FALSE(menuParams->backgroundBlurStyle) << "BlurStyle: " << input;
        CommonMethodModifierTest16::ResetParams(node_);
    }
}

/*
 * @tc.name: BindContextMenu0TestTransition
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestTransition, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    CommonMethodModifierTest16::InitBindContextMenu0();
    Ark_ContextMenuOptions optionsPlacement = {
        .transition = getTransitionEffect(),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(menuParams);
    EXPECT_TRUE(menuParams->hasTransitionEffect);
    EXPECT_EQ(menuParams->transition, effect->handler);
    CommonMethodModifierTest16::ResetParams(node_);
}

/*
 * @tc.name: BindContextMenu0TestEnableHoverMode
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu0TestEnableHoverMode, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    for (auto& [text, value, expected] : testFixtureBooleanValidValues) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(DEFAULT_RESPONSE_TYPE);
        CommonMethodModifierTest16::InitBindContextMenu0();
        Ark_ContextMenuOptions optionsPlacement = {
            .enableHoverMode = ArkValue<Opt_Boolean>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitFocusEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->enableHoverMode, expected) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetParams(node_);
    }
}

/*
 * @tc.name: BindContextMenu1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1Test, TestSize.Level1)
{
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto options = getContextMenuOptions();
    auto isShown = ArkValue<Opt_Boolean>(true);
    CommonMethodModifierTest16::SetSubwindow();
    modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, TEST_RESOURCE_ID);
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: BindContextMenu1TestPlacementTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestPlacementTest, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    for (auto& [text, value, expected] : testFixtureEnumPlacementValidValues) {
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .placement = getPlacement(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        auto isShown = ArkValue<Opt_Boolean>(true);
        CommonMethodModifierTest16::SetSubwindow();
        modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->resourceId, TEST_RESOURCE_ID);
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    }
}

/*
 * @tc.name: BindContextMenu1TestEnableArrow
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestEnableArrow, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    for (auto& [text, value, expected] : testFixtureBooleanValidValues) {
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .placement = ArkValue<Opt_Placement>(),
            .enableArrow = ArkValue<Opt_Boolean>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        auto isShown = ArkValue<Opt_Boolean>(true);
        CommonMethodModifierTest16::SetSubwindow();
        modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->enableArrow, expected) << "Passed value is: " << text;
        std::optional<Placement> expectedPlacement = std::nullopt;
        if (expected) {
            expectedPlacement = Placement::TOP;
        }
        EXPECT_EQ(menuParams->placement, expectedPlacement) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    }
}

/*
 * @tc.name: BindContextMenu1TestArrowOffset
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestArrowOffset, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    for (auto& [text, value, expected] : testFixtureDimensionAnyValidValues) {
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .arrowOffset = ArkValue<Opt_Length>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        auto isShown = ArkValue<Opt_Boolean>(true);
        CommonMethodModifierTest16::SetSubwindow();
        modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->arrowOffset, expected) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    }
}

/*
 * @tc.name: BindContextMenu1TestPreviewPreviewMode
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestPreviewPreviewMode, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    for (auto& [text, value, expected] : testFixtureMenuPreviewMode) {
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .preview = ArkUnion<Opt_Union_MenuPreviewMode_CustomNodeBuilder, Ark_MenuPreviewMode>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        auto isShown = ArkValue<Opt_Boolean>(true);
        CommonMethodModifierTest16::SetSubwindow();
        modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->previewMode, expected) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    }
}

/*
 * @tc.name: BindContextMenu1TestPreviewCustomBuilder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestPreviewCustomBuilder, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    Ark_ContextMenuOptions optionsPlacement = {
        .preview = getPreviewCustomBuilder(),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    auto isShown = ArkValue<Opt_Boolean>(true);
    CommonMethodModifierTest16::SetSubwindow();
    modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
    ASSERT_TRUE(menuParams);
    EXPECT_EQ(menuParams->previewMode, MenuPreviewMode::CUSTOM)
        << "Passed value is: " << static_cast<int>(MenuPreviewMode::CUSTOM);
    ASSERT_TRUE(checkEvent2);
    EXPECT_EQ(checkEvent2->resourceId, TEST_RESOURCE_ID_2);
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: BindContextMenu1TestBorderRadiusLength
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestBorderRadiusLength, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    auto arkLength = ArkValue<Ark_Length>(LENGTH_TEST_VALUE);
    auto radiuses = ArkUnion<Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses, Ark_Length>(arkLength);
    Ark_ContextMenuOptions optionsPlacement = {
        .borderRadius = ArkValue<Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses>(radiuses),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    auto isShown = ArkValue<Opt_Boolean>(true);
    CommonMethodModifierTest16::SetSubwindow();
    modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
    ASSERT_TRUE(menuParams);
    ASSERT_TRUE(menuParams->borderRadius);
    EXPECT_THAT(menuParams->borderRadius.value(), CompareBorderRadius(LENGTH_TEST_VALUE, false));
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: BindContextMenu1TestBorderRadiusBorderRadiuses
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestBorderRadiusBorderRadiuses, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    auto arkLength = ArkValue<Ark_Length>(LENGTH_TEST_VALUE);
    Ark_BorderRadiuses arkRadiuses = {
        .topLeft = ArkValue<Opt_Length>(arkLength),
        .topRight = ArkValue<Opt_Length>(arkLength),
        .bottomLeft = ArkValue<Opt_Length>(arkLength),
        .bottomRight = ArkValue<Opt_Length>(arkLength),
    };
    auto radiuses = ArkUnion<Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses,
    Ark_BorderRadiuses>(arkRadiuses); Ark_ContextMenuOptions optionsPlacement = {
        .borderRadius = ArkValue<Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses>(radiuses),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    auto isShown = ArkValue<Opt_Boolean>(true);
    CommonMethodModifierTest16::SetSubwindow();
    modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
    ASSERT_TRUE(menuParams);
    ASSERT_TRUE(menuParams->borderRadius);
    EXPECT_THAT(menuParams->borderRadius.value(), CompareBorderRadius(LENGTH_TEST_VALUE, false));
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: BindContextMenu1TestBorderRadiusLocalizedRadius
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestBorderRadiusLocalizedRadius, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    auto arkLength = ArkValue<Ark_LengthMetrics>(LENGTH_TEST_VALUE);
    Ark_LocalizedBorderRadiuses arkRadiuses = {
        .topStart = ArkValue<Opt_LengthMetrics>(arkLength),
        .topEnd = ArkValue<Opt_LengthMetrics>(arkLength),
        .bottomStart = ArkValue<Opt_LengthMetrics>(arkLength),
        .bottomEnd = ArkValue<Opt_LengthMetrics>(arkLength),
    };
    auto radiuses =
        ArkUnion<Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses, Ark_LocalizedBorderRadiuses>(arkRadiuses);
    Ark_ContextMenuOptions optionsPlacement = {
        .borderRadius = ArkValue<Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses>(radiuses),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    auto isShown = ArkValue<Opt_Boolean>(true);
    CommonMethodModifierTest16::SetSubwindow();
    modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
    ASSERT_TRUE(menuParams);
    ASSERT_TRUE(menuParams->borderRadius);
    EXPECT_THAT(menuParams->borderRadius.value(), CompareBorderRadius(LENGTH_TEST_VALUE, true));
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestOnAppear, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkCallbackEvent = std::nullopt;
    auto onAppear = [](const Ark_Int32 resourceId) {
        checkCallbackEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
        };
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto arkCallback = ArkValue<Callback_Void>(onAppear, frameNode->GetId());
    Ark_ContextMenuOptions optionsPlacement = {
        .onAppear = ArkValue<Opt_Callback_Void>(arkCallback),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    EXPECT_FALSE(checkCallbackEvent);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(checkCallbackEvent);
    EXPECT_EQ(checkCallbackEvent->nodeId, frameNode->GetId());
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestOnDisappear, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkCallbackEvent = std::nullopt;
    auto onDisappear = [](const Ark_Int32 resourceId) {
        checkCallbackEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
        };
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto arkCallback = ArkValue<Callback_Void>(onDisappear, frameNode->GetId());
    Ark_ContextMenuOptions optionsPlacement = {
        .onDisappear = ArkValue<Opt_Callback_Void>(arkCallback),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    EXPECT_FALSE(checkCallbackEvent);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(checkCallbackEvent);
    EXPECT_EQ(checkCallbackEvent->nodeId, frameNode->GetId());
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestAboutToAppear, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkCallbackEvent = std::nullopt;
    auto aboutToAppear = [](const Ark_Int32 resourceId) {
        checkCallbackEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
        };
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto arkCallback = ArkValue<Callback_Void>(aboutToAppear, frameNode->GetId());
    Ark_ContextMenuOptions optionsPlacement = {
        .aboutToAppear = ArkValue<Opt_Callback_Void>(arkCallback),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    EXPECT_FALSE(checkCallbackEvent);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(checkCallbackEvent);
    EXPECT_EQ(checkCallbackEvent->nodeId, frameNode->GetId());
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestAboutToDisappear, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkCallbackEvent = std::nullopt;
    auto aboutToDisappear = [](const Ark_Int32 resourceId) {
        checkCallbackEvent = CheckEvent{
            .nodeId = Convert<int32_t>(resourceId),
        };
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto arkCallback = ArkValue<Callback_Void>(aboutToDisappear, frameNode->GetId());
    Ark_ContextMenuOptions optionsPlacement = {
        .aboutToDisappear = ArkValue<Opt_Callback_Void>(arkCallback),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
    EXPECT_FALSE(checkCallbackEvent);
    CommonMethodModifierTest16::EmitLongPressEvent(node_);
    ASSERT_TRUE(checkCallbackEvent);
    EXPECT_EQ(checkCallbackEvent->nodeId, frameNode->GetId());
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: BindContextMenu1TestLayoutRegionMargin
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestLayoutRegionMargin, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    auto arkLength = ArkValue<Ark_Length>(LENGTH_TEST_VALUE);
    Ark_Padding arkPadding = {
        .left = ArkValue<Opt_Length>(arkLength),
        .right = ArkValue<Opt_Length>(arkLength),
        .bottom = ArkValue<Opt_Length>(arkLength),
        .top = ArkValue<Opt_Length>(arkLength),
    };
    Ark_ContextMenuOptions optionsPlacement = {
        .layoutRegionMargin = ArkValue<Opt_Padding>(arkPadding),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    auto isShown = ArkValue<Opt_Boolean>(true);
    CommonMethodModifierTest16::SetSubwindow();
    modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
    ASSERT_TRUE(menuParams);
    ASSERT_TRUE(menuParams->layoutRegionMargin);
    EXPECT_THAT(menuParams->layoutRegionMargin.value(), CompareMarginPadding(CalcLength(LENGTH_TEST_VALUE)));
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: BindContextMenu1TestBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestBackgroundColorValidValues, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto checkValue = [this](const std::string& input, const std::string& expected, Opt_ResourceColor colorValue) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .backgroundColor = colorValue,
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitLongPressEvent(node_);
        ASSERT_TRUE(menuParams);
        ASSERT_TRUE(menuParams->backgroundColor);
        EXPECT_THAT(menuParams->backgroundColor->ToString(), expected) << "Color: " << input;
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}
/*
 * @tc.name: BindContextMenu1TestBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestBackgroundColorInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    auto checkValue = [this](const std::string& input, Opt_ResourceColor colorValue) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .backgroundColor = colorValue,
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitLongPressEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_FALSE(menuParams->backgroundColor) << "Color: " << input;
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    };
    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: BindContextMenu1TestBackgroundBlurStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestBackgroundBlurStyleValidValues, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    for (auto& [input, value, expected] : testFixtureBlurStyleActivePolicyValidValues) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .backgroundBlurStyle = ArkValue<Opt_BlurStyle>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitLongPressEvent(node_);
        ASSERT_TRUE(menuParams);
        ASSERT_TRUE(menuParams->backgroundBlurStyle) << "BlurStyle: " << input;
        EXPECT_EQ(menuParams->backgroundBlurStyle, static_cast<int32_t>(expected))
            << "BlurStyleActivePolicy: " << input;
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    }
}

/*
 * @tc.name: BindContextMenu1TestBackgroundBlurStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestBackgroundBlurStyleInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    for (auto& [input, value] : testFixtureEnumBlurStyleInvalidValues) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .backgroundBlurStyle = ArkValue<Opt_BlurStyle>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitLongPressEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_FALSE(menuParams->backgroundBlurStyle) << "BlurStyle: " << input;
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    }
}

/*
 * @tc.name: BindContextMenu1TestTransition
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestTransition, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu1);
    auto builder = getBuilderCb();
    auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
    Ark_ContextMenuOptions optionsPlacement = {
        .transition = getTransitionEffect(),
    };
    auto options = getContextMenuOptions(optionsPlacement);
    auto isShown = ArkValue<Opt_Boolean>(true);
    CommonMethodModifierTest16::SetSubwindow();
    modifier_->setBindContextMenu1(node_, &isShown, &arkBuilder, &options);
    ASSERT_TRUE(menuParams);
    EXPECT_TRUE(menuParams->hasTransitionEffect);
    EXPECT_EQ(menuParams->transition, effect->handler);
    CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
}

/*
 * @tc.name: BindContextMenu1TestEnableHoverMode
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest16, DISABLED_BindContextMenu1TestEnableHoverMode, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setBindContextMenu0);
    for (auto& [text, value, expected] : testFixtureBooleanValidValues) {
        auto builder = getBuilderCb();
        auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
        auto responseType = Converter::ArkValue<Opt_ResponseType>(DEFAULT_RESPONSE_TYPE);
        auto& aceEngine = CommonMethodModifierTest16::InitBindContextMenu1();
        Ark_ContextMenuOptions optionsPlacement = {
            .enableHoverMode = ArkValue<Opt_Boolean>(value),
        };
        auto options = getContextMenuOptions(optionsPlacement);
        modifier_->setBindContextMenu0(node_, &arkBuilder, &responseType, &options);
        CommonMethodModifierTest16::EmitFocusEvent(node_);
        ASSERT_TRUE(menuParams);
        EXPECT_EQ(menuParams->enableHoverMode, expected) << "Passed value is: " << text;
        CommonMethodModifierTest16::ResetAceEngine(node_, aceEngine);
    }
}
} // namespace OHOS::Ace::NG
