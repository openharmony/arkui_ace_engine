/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"

#include "core/common/force_split/force_split_utils.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_transition_proxy.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"

namespace OHOS::Ace::NG {
constexpr double HALF = 0.5;
constexpr float TITLE_OFFSET_PERCENT = 0.02f;
constexpr int32_t OPACITY_TITLE_OUT_DELAY = 17;
constexpr int32_t OPACITY_TITLE_IN_DELAY = 33;
constexpr int32_t OPACITY_TITLE_DURATION = 150;
constexpr int32_t OPACITY_BACKBUTTON_IN_DELAY = 150;
constexpr int32_t OPACITY_BACKBUTTON_IN_DURATION = 200;
constexpr int32_t OPACITY_BACKBUTTON_OUT_DURATION = 67;
constexpr int32_t MAX_RENDER_GROUP_TEXT_NODE_COUNT = 50;
constexpr float MAX_RENDER_GROUP_TEXT_NODE_HEIGHT = 150.0f;
constexpr int32_t INVALID_ANIMATION_ID = -1;
constexpr int32_t SYSTEM_ENTER_FADE_TRANSITION_DURATION = 250;
constexpr int32_t SYSTEM_EXIT_FADE_TRANSITION_DURATION = 200;
constexpr int32_t SYSTEM_ENTER_FADE_TRANSITION_DELAY = 50;
constexpr int32_t SYSTEM_EXIT_FADE_TRANSITION_DELAY = 0;
constexpr int32_t SYSTEM_EXPLODE_TRANSITION_MASK_DURATION = 300;
constexpr int32_t SYSTEM_ENTER_POP_EXPLODE_OPACITY_DURATION = 250;
constexpr int32_t SYSTEM_ENTER_POP_EXPLODE_OPACITY_DELAY = 50;
constexpr int32_t SYSTEM_ENTER_PUSH_EXPLODE_OPACITY_DURATION = 300;
constexpr int32_t SYSTEM_ENTER_PUSH_EXPLODE_OPACITY_DELAY = 50;
constexpr int32_t SYSTEM_EXIT_POP_EXPLODE_OPACITY_DURATION = 150;
constexpr int32_t SYSTEM_EXIT_PUSH_EXPLODE_OPACITY_DELAY = 200;
constexpr int32_t SYSTEM_SLIDE_TRANSITION_MASK_DURATION = 350;
const Color SLIDE_ANIMATION_MASK_COLOR = Color::FromARGB(25, 0, 0, 0);

namespace {
const char* TransitionTypeToString(NavigationSystemTransitionType type)
{
    switch (type) {
        case NavigationSystemTransitionType::NONE:
            return "NavigationSystemTransitionType.NONE";
        case NavigationSystemTransitionType::TITLE:
            return "NavigationSystemTransitionType.TITLE";
        case NavigationSystemTransitionType::CONTENT:
            return "NavigationSystemTransitionType.CONTENT";
        case NavigationSystemTransitionType::FADE:
            return "NavigationSystemTransitionType.FADE";
        case NavigationSystemTransitionType::EXPLODE:
            return "NavigationSystemTransitionType.EXPLODE";
        case NavigationSystemTransitionType::SLIDE_RIGHT:
            return "NavigationSystemTransitionType.SLIDE_RIGHT";
        case NavigationSystemTransitionType::SLIDE_BOTTOM:
            return "NavigationSystemTransitionType.SLIDE_BOTTOM";
        default:
            return "NavigationSystemTransitionType.DEFAULT";
    }
}

AnimationOption BuildAnimationOption(const RefPtr<Curve>& curve, std::function<void()>&& onFinishEvent,
    int32_t duration = 0, int32_t delay = 0)
{
    AnimationOption option(curve, duration);
    option.SetDelay(delay);
    option.SetOnFinishEvent(std::move(onFinishEvent));
    return option;
}
}

NavDestinationGroupNode::~NavDestinationGroupNode()
{
    if (contentNode_) {
        contentNode_->Clean();
    }
    ReleaseTextNodeList();
}

RefPtr<NavDestinationGroupNode> NavDestinationGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<NavDestinationGroupNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(tag, nodeId, pattern);
    CHECK_NULL_RETURN(navDestinationNode, nullptr);
    navDestinationNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navDestinationNode);
    return navDestinationNode;
}

bool NavDestinationGroupNode::IsNeedContentTransition()
{
    if (systemTransitionType_ == NavigationSystemTransitionType::DEFAULT) {
        // for HomeNavDestination, DEFAULT equals to NONE when split mode.
        if (!isHomeDestination_) {
            return true;
        }
        auto navNode = AceType::DynamicCast<NavigationGroupNode>(GetNavigationNode());
        CHECK_NULL_RETURN(navNode, true);
        auto pattern = navNode->GetPattern<NavigationPattern>();
        CHECK_NULL_RETURN(pattern, true);
        return pattern->GetNavigationMode() == NavigationMode::STACK;
    }
    return (systemTransitionType_ & NavigationSystemTransitionType::CONTENT) != NavigationSystemTransitionType::NONE;
}

bool NavDestinationGroupNode::TransitionContentInValid()
{
    if (isHomeDestination_) {
        auto navNode = AceType::DynamicCast<NavigationGroupNode>(GetNavigationNode());
        CHECK_NULL_RETURN(navNode, false);
        auto navPattern = navNode->GetPattern<NavigationPattern>();
        CHECK_NULL_RETURN(navPattern, false);
        auto mode = navPattern->GetNavigationMode();
        return mode == NavigationMode::SPLIT;
    }
    return (systemTransitionType_ & NavigationSystemTransitionType::CONTENT) == NavigationSystemTransitionType::NONE
        && mode_ == NavDestinationMode::STANDARD;
}

bool NavDestinationGroupNode::IsNeedTitleTransition()
{
    if (systemTransitionType_ == NavigationSystemTransitionType::DEFAULT) {
        // for HomeNavDestination, DEFAULT equals to NONE when split mode.
        if (!isHomeDestination_) {
            return true;
        }
        auto navNode = AceType::DynamicCast<NavigationGroupNode>(GetNavigationNode());
        CHECK_NULL_RETURN(navNode, true);
        auto pattern = navNode->GetPattern<NavigationPattern>();
        CHECK_NULL_RETURN(pattern, true);
        return pattern->GetNavigationMode() == NavigationMode::STACK;
    }
    if (mode_ == NavDestinationMode::STANDARD) {
        return (systemTransitionType_ & NavigationSystemTransitionType::TITLE) != NavigationSystemTransitionType::NONE;
    }
    return (systemTransitionType_ & NavigationSystemTransitionType::CONTENT) != NavigationSystemTransitionType::NONE;
}

void NavDestinationGroupNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    auto pattern = AceType::DynamicCast<Pattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto contentNode = GetContentNode();
    if (!contentNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_CONTENT_ETS_TAG, nodeId);
        contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, nodeId,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        SetContentNode(contentNode);
        AddChild(contentNode);

        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            auto navdestinationContentNode = AceType::DynamicCast<FrameNode>(contentNode);
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
                .edges = SAFE_AREA_EDGE_ALL };
            navdestinationContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        }
    }
    contentNode->AddChild(child, slot);
}

void NavDestinationGroupNode::DeleteChildFromGroup(int32_t slot)
{
    auto navDestination = GetContentNode();
    CHECK_NULL_VOID(navDestination);
    navDestination->RemoveChildAtIndex(slot);
}

void NavDestinationGroupNode::OnAttachToMainTree(bool recursive)
{
    if (!UseOffscreenProcess()) {
        ProcessShallowBuilder();
    }
    FrameNode::OnAttachToMainTree(recursive);
    SetFreeze(false, true);
}

void NavDestinationGroupNode::OnOffscreenProcess(bool recursive)
{
    ProcessShallowBuilder();
    FrameNode::OnOffscreenProcess(recursive);
}

void NavDestinationGroupNode::ProcessShallowBuilder()
{
    if (isCacheNode_) {
        return;
    }

    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "render navDestination content");
    auto navDestinationPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
    if (shallowBuilder && !shallowBuilder->IsExecuteDeepRenderDone()) {
        auto eventHub = GetOrCreateEventHub<NavDestinationEventHub>();
        if (eventHub) {
            auto ctx = navDestinationPattern->GetNavDestinationContext();
            eventHub->FireOnReady(ctx);
        }
        shallowBuilder->ExecuteDeepRender();
        GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        AceType::DynamicCast<FrameNode>(contentNode_)
            ->GetLayoutProperty()
            ->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
}

RefPtr<CustomNodeBase> NavDestinationGroupNode::GetNavDestinationCustomNode()
{
    return customNode_.Upgrade();
}

int32_t NavDestinationGroupNode::GetNavigationNodeId() const
{
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(GetPattern());
    CHECK_NULL_RETURN(pattern, DEFAULT_NODE_SLOT);
    auto navigationNode = pattern->GetNavigationNode();
    CHECK_NULL_RETURN(navigationNode, DEFAULT_NODE_SLOT);
    return navigationNode->GetId();
}

void NavDestinationGroupNode::SetNavDestinationMode(NavDestinationMode mode)
{
    mode_ = mode;
    auto pattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(pattern);
    auto context = pattern->GetNavDestinationContext();
    CHECK_NULL_VOID(context);
    context->SetMode(mode);
}

void NavDestinationGroupNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    FrameNode::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto titleBarNode = DynamicCast<TitleBarNode>(titleBarNode_);
    if (titleBarNode) {
        std::string title = NavigationTitleUtil::GetTitleString(titleBarNode, GetPrevTitleIsCustomValue(false));
        std::string subtitle = NavigationTitleUtil::GetSubtitleString(titleBarNode);
        json->PutExtAttr("title", title.c_str(), filter);
        json->PutExtAttr("subtitle", subtitle.c_str(), filter);
    }
    auto navBarPattern = GetPattern<NavDestinationPatternBase>();
    if (navBarPattern) {
        auto menuOptionsJson = JsonUtil::Create(true);
        auto moreButtonOptions = navBarPattern->GetMenuOptions();
        moreButtonOptions.ToJsonValue(menuOptionsJson, filter);
        json->PutExtAttr("menuOptions", menuOptionsJson, filter);
    }
    json->PutExtAttr("mode", mode_ == NavDestinationMode::DIALOG
        ? "NavDestinationMode::DIALOG"
        : "NavDestinationMode::STANDARD", filter);
    json->PutExtAttr("systemTransition", TransitionTypeToString(systemTransitionType_), filter);
}

void NavDestinationGroupNode::SystemTransitionPushStart(bool transitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    float isRTL = GetLanguageDirection();
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    if (transitionIn) {
        SetIsOnAnimation(true);
        SetTransitionType(PageTransitionType::ENTER_PUSH);
        if (needContentAnimation) {
            RectF rect = CalcHalfClipRectForTransition(frameSizeWithSafeArea);
            renderContext->ClipWithRRect(rect, RadiusF(EdgeF(0.0f, 0.0f)));
            auto translate = CalcTranslateForTransitionPushStart(frameSizeWithSafeArea, true);
            renderContext->UpdateTranslateInXY(translate);
        }
        if (titleBarNode && needTitleAnimation) {
            titleBarNode->GetRenderContext()->UpdateTranslateInXY({ frameSize.Width() * HALF * isRTL, 0.0f });
        }
        return;
    }
    SetTransitionType(PageTransitionType::EXIT_PUSH);
    SetIsOnAnimation(true);
    renderContext->RemoveClipWithRRect();
    if (needContentAnimation) {
        auto translate = CalcTranslateForTransitionPushStart(frameSize, false);
        renderContext->UpdateTranslateInXY(translate);
    }
    if (NeedRemoveInPush()) {
        GetOrCreateEventHub<EventHub>()->SetEnabledInternal(false);
    }
    if (titleBarNode && needTitleAnimation) {
        titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
}

void NavDestinationGroupNode::InitSoftTransitionPush(bool transitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    bool needContentAnimation = IsNeedContentTransition();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    if (transitionIn) {
        SetIsOnAnimation(true);
        SetTransitionType(PageTransitionType::ENTER_PUSH);
        auto translate = CalcTranslateForTransitionPushStart(frameSizeWithSafeArea, true);
        if (needContentAnimation) {
            renderContext->UpdateTranslateInXY(translate);
        }
        return;
    }
    SetTransitionType(PageTransitionType::EXIT_PUSH);
    SetIsOnAnimation(true);
    auto translate = CalcTranslateForTransitionPushStart(frameSize, false);
    if (needContentAnimation) {
        renderContext->UpdateTranslateInXY(translate);
    }
    if (NeedRemoveInPush()) {
        GetEventHub<EventHub>()->SetEnabledInternal(false);
    }
}

void NavDestinationGroupNode::StartSoftTransitionPush(bool transitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    bool needContentAnimation = IsNeedContentTransition();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (transitionIn) {
        auto translate = CalcTranslateForTransitionPushEnd(frameSizeWithSafeArea, true);
        if (needContentAnimation) {
            renderContext->UpdateTranslateInXY(translate);
        }
        return;
    }
    auto translate = CalcTranslateForTransitionPushEnd(frameSizeWithSafeArea, false);
    if (needContentAnimation) {
        renderContext->UpdateTranslateInXY(translate);
    }
}

void NavDestinationGroupNode::InitSoftTransitionPop(bool isTransitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    bool needContentAnimation = IsNeedContentTransition();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (isTransitionIn) {
        SetTransitionType(PageTransitionType::ENTER_POP);
        auto translate = CalcTranslateForTransitionPopStart(frameSizeWithSafeArea, true);
        if (needContentAnimation) {
            renderContext->UpdateTranslateInXY(translate);
        }
        return;
    }
    SetIsOnAnimation(true);
    SetTransitionType(PageTransitionType::EXIT_POP);
    GetEventHub<EventHub>()->SetEnabledInternal(false);
    auto translate = CalcTranslateForTransitionPopStart(frameSizeWithSafeArea, false);
    if (needContentAnimation) {
        renderContext->UpdateTranslateInXY(translate);
    }
}

void NavDestinationGroupNode::StartSoftTransitionPop(bool transitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    bool needContentAnimation = IsNeedContentTransition();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    if (transitionIn) {
        auto translate = CalcTranslateForTransitionPopEnd(frameSizeWithSafeArea, true);
        if (needContentAnimation) {
            renderContext->UpdateTranslateInXY(translate);
        }
        return;
    }
    auto translate = CalcTranslateForTransitionPopEnd(frameSizeWithSafeArea, false);
    if (needContentAnimation) {
        renderContext->UpdateTranslateInXY(translate);
    }
}

void NavDestinationGroupNode::SystemTransitionPushEnd(bool transitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    float isRTL = GetLanguageDirection();
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (transitionIn) {
        if (needContentAnimation) {
            RectF rect = CalcFullClipRectForTransition(frameSizeWithSafeArea);
            renderContext->ClipWithRRect(rect, RadiusF(EdgeF(0.0f, 0.0f)));
            auto translate = CalcTranslateForTransitionPushEnd(frameSizeWithSafeArea, true);
            renderContext->UpdateTranslateInXY(translate);
        }
        if (titleBarNode && needTitleAnimation) {
            titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        }
        return;
    }
    if (needContentAnimation) {
        auto translate = CalcTranslateForTransitionPushEnd(frameSizeWithSafeArea, false);
        renderContext->UpdateTranslateInXY(translate);
    }
    if (titleBarNode && needTitleAnimation) {
        titleBarNode->GetRenderContext()->UpdateTranslateInXY(
            { frameSize.Width() * TITLE_OFFSET_PERCENT  * isRTL, 0.0f });
    }
}

void NavDestinationGroupNode::SystemTransitionPushFinish(bool transitionIn, int32_t animationId)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    if (animationId != animationId_) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "push animation invalid,curId: %{public}d, targetId: %{public}d",
            animationId_, animationId);
        return;
    }
    SetIsOnAnimation(false);
    if (transitionIn) {
        if (GetTransitionType() != PageTransitionType::ENTER_PUSH) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "curNode has another transition");
            return;
        }
        GetRenderContext()->RemoveClipWithRRect();
        return;
    }
    if (IsNeedContentTransition()) {
        GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
    GetRenderContext()->SetActualForegroundColor(Color::TRANSPARENT);
    auto navDestinationPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(navDestinationPattern->GetNavigationNode());
    CHECK_NULL_VOID(navigation);
    bool isInvisible = IsNodeInvisible(navigation);
    if (GetTransitionType() == PageTransitionType::EXIT_PUSH && isInvisible) {
        GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
        SetJSViewActive(false);
    }
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    if (titleBarNode && IsNeedTitleTransition()) {
        titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
}

void NavDestinationGroupNode::SystemTransitionPopStart(bool transitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    float isRTL = GetLanguageDirection();
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (transitionIn) {
        SetTransitionType(PageTransitionType::ENTER_POP);
        renderContext->RemoveClipWithRRect();
        if (needContentAnimation) {
            auto translate = CalcTranslateForTransitionPopStart(frameSizeWithSafeArea, true);
            renderContext->UpdateTranslateInXY(translate);
        }
        if (titleBarNode && needTitleAnimation) {
            titleBarNode->GetRenderContext()->UpdateTranslateInXY(
                { frameSize.Width() * TITLE_OFFSET_PERCENT * isRTL, 0.0f });
        }
        return;
    }
    SetIsOnAnimation(true);
    SetTransitionType(PageTransitionType::EXIT_POP);
    GetOrCreateEventHub<EventHub>()->SetEnabledInternal(false);
    if (needContentAnimation) {
        RectF rect = CalcFullClipRectForTransition(frameSizeWithSafeArea);
        renderContext->ClipWithRRect(rect, RadiusF(EdgeF(0.0f, 0.0f)));
        auto translate = CalcTranslateForTransitionPopStart(frameSizeWithSafeArea, false);
        renderContext->UpdateTranslateInXY(translate);
    }
    if (titleBarNode && needTitleAnimation) {
        titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
}

void NavDestinationGroupNode::SystemTransitionPopEnd(bool transitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    if (transitionIn) {
        if (needContentAnimation) {
            auto translate = CalcTranslateForTransitionPopEnd(frameSizeWithSafeArea, true);
            renderContext->UpdateTranslateInXY(translate);
        }
        if (titleBarNode && needTitleAnimation) {
            titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        }
        return;
    }
    float isRTL = GetLanguageDirection();
    if (needContentAnimation) {
        RectF rect = CalcHalfClipRectForTransition(frameSizeWithSafeArea);
        renderContext->ClipWithRRect(rect, RadiusF(EdgeF(0.0f, 0.0f)));
        auto translate = CalcTranslateForTransitionPopEnd(frameSizeWithSafeArea, false);
        renderContext->UpdateTranslateInXY(translate);
    }
    if (titleBarNode && needTitleAnimation) {
        titleBarNode->GetRenderContext()->UpdateTranslateInXY({ frameSize.Width() * HALF * isRTL, 0.0f });
    }
}

bool NavDestinationGroupNode::CheckTransitionPop(const int32_t animationId)
{
    if (IsCacheNode()) {
        return false;
    }
    if (animationId_ != animationId) {
        return false;
    }
    if (GetTransitionType() != PageTransitionType::EXIT_POP) {
        return false;
    }
    auto preNavDesPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(preNavDesPattern, false);
    return true;
}

bool NavDestinationGroupNode::SystemTransitionPopFinish(int32_t animationId, bool isNeedCleanContent)
{
    if (destType_ == NavDestinationType::HOME) {
        return true;
    }
    if (animationId_ != animationId) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION,
            "animation id is invalid, curId: %{public}d, targetId: %{public}d",
            animationId_, animationId);
        return false;
    }
    SetIsOnAnimation(false);
    if (GetTransitionType() != PageTransitionType::EXIT_POP) {
        // has another transition, just return
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "preNavDesNode has another transition");
        return false;
    }
    auto preNavDesPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(preNavDesPattern, false);

    // NavRouter will restore the preNavDesNode and needs to set the initial state after the animation ends.
    if (isNeedCleanContent) {
        CleanContent();
    }
    GetOrCreateEventHub<EventHub>()->SetEnabledInternal(true);
    GetRenderContext()->RemoveClipWithRRect();
    if (IsNeedContentTransition()) {
        GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
    auto preTitleNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    if (preTitleNode && IsNeedTitleTransition()) {
        preTitleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        preTitleNode->GetRenderContext()->SetOpacity(1.0);
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(preTitleNode);
        CHECK_NULL_RETURN(titleBarNode, true);
        auto preBackIcon = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
        if (preBackIcon)  {
            preBackIcon->GetRenderContext()->SetOpacity(1.0);
        }
    }
    return true;
}

void NavDestinationGroupNode::InitDialogTransition(bool isZeroY)
{
    if (destType_ == NavDestinationType::HOME) {
        return;
    }
    if (systemTransitionType_ == NavigationSystemTransitionType::NONE
        || systemTransitionType_ == NavigationSystemTransitionType::TITLE) {
        return;
    }
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSizeWithSafeArea = geometryNode->GetFrameSize(true);
    auto contentNode = AceType::DynamicCast<FrameNode>(GetContentNode());
    CHECK_NULL_VOID(contentNode);
    auto context = contentNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (isZeroY) {
        context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
        return;
    }
    auto translateOpts = CalcContentTranslateForDialog(frameSizeWithSafeArea);
    context->UpdateTransformTranslate(translateOpts);
}

std::shared_ptr<AnimationUtils::Animation> NavDestinationGroupNode::TitleOpacityAnimation(bool isTransitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return nullptr;
    }
    if (!IsNeedTitleTransition()) {
        return nullptr;
    }
    CHECK_NULL_RETURN(GetTitleBarNode(), nullptr);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(GetTitleBarNode());
    CHECK_NULL_RETURN(titleNode, nullptr);
    auto titleRenderContext = titleNode->GetRenderContext();
    CHECK_NULL_RETURN(titleRenderContext, nullptr);
    AnimationOption opacityOption;
    opacityOption.SetCurve(Curves::SHARP);
    opacityOption.SetDuration(OPACITY_TITLE_DURATION);
    if (isTransitionIn) {
        opacityOption.SetDelay(OPACITY_TITLE_IN_DELAY);
        titleRenderContext->SetOpacity(0.0f);
        return AnimationUtils::StartAnimation(opacityOption,
            [weakRender = WeakPtr<RenderContext>(titleRenderContext)]() {
            auto renderContext = weakRender.Upgrade();
            CHECK_NULL_VOID(renderContext);
            renderContext->SetOpacity(1.0f);
        }, nullptr /* finishCallback*/, nullptr /* repeatCallback */, GetContextRefPtr());
    }
    // recover after transition animation.
    opacityOption.SetDelay(OPACITY_TITLE_OUT_DELAY);
    titleRenderContext->SetOpacity(1.0f);
    return AnimationUtils::StartAnimation(opacityOption,
        [weakRender = WeakPtr<RenderContext>(titleRenderContext)]() {
        auto renderContext = weakRender.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetOpacity(0.0f);
    }, nullptr /* finishCallback*/, nullptr /* repeatCallback */, GetContextRefPtr());
}

std::shared_ptr<AnimationUtils::Animation> NavDestinationGroupNode::BackButtonAnimation(bool isTransitionIn)
{
    if (destType_ == NavDestinationType::HOME) {
        return nullptr;
    }
    if (!IsNeedTitleTransition()) {
        return nullptr;
    }
    auto titleNode = AceType::DynamicCast<TitleBarNode>(GetTitleBarNode());
    CHECK_NULL_RETURN(titleNode, nullptr);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleNode->GetCustomBackButton());
    if (!backButtonNode) {
        backButtonNode = AceType::DynamicCast<FrameNode>(titleNode->GetBackButton());
    }
    CHECK_NULL_RETURN(backButtonNode, nullptr);
    AnimationOption transitionOption;
    transitionOption.SetCurve(Curves::SHARP);
    auto backButtonNodeContext = backButtonNode->GetRenderContext();
    CHECK_NULL_RETURN(backButtonNodeContext, nullptr);
    if (isTransitionIn) {
        transitionOption.SetDelay(OPACITY_BACKBUTTON_IN_DELAY);
        transitionOption.SetDuration(OPACITY_BACKBUTTON_IN_DURATION);
        backButtonNodeContext->SetOpacity(0.0f);
        return AnimationUtils::StartAnimation(transitionOption,
            [weakRender = WeakPtr<RenderContext>(backButtonNodeContext)]() {
            auto renderContext = weakRender.Upgrade();
            CHECK_NULL_VOID(renderContext);
            renderContext->SetOpacity(1.0f);
        }, nullptr /* finishCallback*/, nullptr /* repeatCallback */, GetContextRefPtr());
    }
    transitionOption.SetDuration(OPACITY_BACKBUTTON_OUT_DURATION);
    backButtonNodeContext->SetOpacity(1.0f);
    return AnimationUtils::StartAnimation(transitionOption,
        [weakRender = WeakPtr<RenderContext>(backButtonNodeContext)]() {
        auto renderContext = weakRender.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetOpacity(0.0f);
    }, nullptr /* finishCallback*/, nullptr /* repeatCallback */, GetContextRefPtr());
}

void NavDestinationGroupNode::UpdateTextNodeListAsRenderGroup(
    bool isPopPage, const RefPtr<NavigationTransitionProxy>& proxy)
{
    if (isPopPage) {
        CollectTextNodeAsRenderGroup(isPopPage);
    } else {
        CHECK_NULL_VOID(proxy);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterLayoutTask([weakNavDestiniation = WeakClaim(this),
            weakProxy = WeakPtr<NavigationTransitionProxy>(proxy)] () {
            auto navDestination = weakNavDestiniation.Upgrade();
            CHECK_NULL_VOID(navDestination);
            auto proxy = weakProxy.Upgrade();
            if (proxy && proxy->GetIsFinished()) {
                return;
            }
            navDestination->CollectTextNodeAsRenderGroup(false);
        });
        pipeline->RequestFrame();
    }
}

void NavDestinationGroupNode::CollectTextNodeAsRenderGroup(bool isPopPage)
{
    ReleaseTextNodeList();
    std::queue<RefPtr<UINode>> childrenLoopQueue;
    childrenLoopQueue.push(contentNode_);

    // only the first 50 text nodes will be marked, avoid too much time for traversal
    // and off-screen drawing at first few frames
    int32_t remainTextNodeNeedRenderGroup = MAX_RENDER_GROUP_TEXT_NODE_COUNT;
    while (!childrenLoopQueue.empty() && remainTextNodeNeedRenderGroup > 0) {
        auto currentNode = childrenLoopQueue.front();
        childrenLoopQueue.pop();
        CHECK_NULL_CONTINUE(currentNode);
        for (auto& child : currentNode->GetChildren()) {
            if (remainTextNodeNeedRenderGroup <= 0) {
                break;
            }
            CHECK_NULL_CONTINUE(child);
            childrenLoopQueue.push(child);
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            if (!frameNode || (frameNode->GetTag() != V2::TEXT_ETS_TAG)) {
                continue;
            }
            auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
            if (!layoutProperty ||
                (layoutProperty->GetTextOverflowValue(TextOverflow::CLIP) == TextOverflow::MARQUEE)) {
                continue;
            }
            auto& renderContext = frameNode->GetRenderContext();
            if (!renderContext || renderContext->GetRenderGroupValue(false)) {
                continue;
            }
            renderContext->SetMarkNodeGroup(isPopPage ||
                (renderContext->GetPaintRectWithoutTransform().Height() < MAX_RENDER_GROUP_TEXT_NODE_HEIGHT));
            textNodeList_.emplace_back(WeakPtr<UINode>(child));
            --remainTextNodeNeedRenderGroup;
            auto pattern = AceType::DynamicCast<TextPattern>(frameNode->GetPattern());
            CHECK_NULL_CONTINUE(pattern);
            pattern->RegisterAfterLayoutCallback([weakRenderContext = WeakPtr<RenderContext>(renderContext)]() {
                auto renderContext = weakRenderContext.Upgrade();
                if (renderContext && !(renderContext->GetRenderGroupValue(false))) {
                    renderContext->SetMarkNodeGroup(
                        renderContext->GetPaintRectWithoutTransform().Height() < MAX_RENDER_GROUP_TEXT_NODE_HEIGHT);
                }
            });
        }
    }
}

void NavDestinationGroupNode::ReleaseTextNodeList()
{
    for (auto& child : textNodeList_) {
        auto textNode = AceType::DynamicCast<FrameNode>(child.Upgrade());
        if (!textNode) {
            continue;
        }
        auto pattern = AceType::DynamicCast<TextPattern>(textNode->GetPattern());
        if (pattern) {
            pattern->UnRegisterAfterLayoutCallback();
        }
        auto renderContext = textNode->GetRenderContext();
        if (renderContext) {
            renderContext->SetMarkNodeGroup(renderContext->GetRenderGroupValue(false));
        }
    }
    textNodeList_.clear();
}

void NavDestinationGroupNode::CleanContent(bool cleanDirectly, bool allowTransition)
{
    // cacheNode is cached for pip info, and is no need to clean when clean content node
    if (IsCacheNode()) {
        return;
    }
    auto pattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(pattern);
    auto shallowBuilder = pattern->GetShallowBuilder();
    if (shallowBuilder) {
        shallowBuilder->MarkIsExecuteDeepRenderDone(false);
    }
    if (GetContentNode()) {
        GetContentNode()->Clean(cleanDirectly, allowTransition);
    }
}

bool NavDestinationGroupNode::IsNodeInvisible(const RefPtr<FrameNode>& node)
{
    auto navigation = DynamicCast<NavigationGroupNode>(node);
    CHECK_NULL_RETURN(navigation, false);
    int32_t lastStandardIndex = navigation->GetLastStandardIndex();
    bool isInvisible = index_ < lastStandardIndex;
    if (!isHomeDestination_) {
        return isInvisible;
    }
    auto navPattern = navigation->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navPattern, isInvisible);
    auto mode = navPattern->GetNavigationMode();
    if (mode == NavigationMode::STACK) {
        return isInvisible;
    }
    return false;
}

std::string NavDestinationGroupNode::ToDumpString()
{
    std::string dumpString;
    auto navDestinationPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, dumpString);
    std::string navDestinationType;
    switch (destType_) {
        case NavDestinationType::DETAIL:
            navDestinationType = "DETAIL";
            break;
        case NavDestinationType::HOME:
            navDestinationType = "HOME";
            break;
        case NavDestinationType::PROXY:
            navDestinationType = "PROXY";
            break;
        default:
            navDestinationType = "INVALID";
            break;
    }
    dumpString.append("| [");
    dumpString.append(std::to_string(index_));
    dumpString.append("]{ ID: ");
    dumpString.append(std::to_string(navDestinationPattern->GetNavDestinationId()));
    dumpString.append(", Name: \"");
    dumpString.append(navDestinationPattern->GetName());
    dumpString.append("\", Mode: \"");
    dumpString.append(mode_ == NavDestinationMode::STANDARD ? "STANDARD" : "DIALOG");
    dumpString.append("\", IsOnShow: \"");
    dumpString.append(navDestinationPattern->GetIsOnShow() ? "TRUE" : "FALSE");
    dumpString.append("\", navDestinationType: \"");
    dumpString.append(navDestinationType);
    dumpString.append("\", Visible? \"");
    dumpString.append(IsVisible() ? "Yes" : "No");
    int32_t count = 0;
    int32_t depth = 0;
    GetPageNodeCountAndDepth(&count, &depth);
    dumpString.append("\", Count: " + std::to_string(count));
    dumpString.append(", Depth: " + std::to_string(depth) + " }");
    return dumpString;
}

int32_t NavDestinationGroupNode::DoTransition(NavigationOperation operation, bool isEnter)
{
    if (destType_ == NavDestinationType::HOME) {
        return INVALID_ANIMATION_ID;
    }
    if (navDestinationTransitionDelegate_) {
        return DoCustomTransition(operation, isEnter);
    }
    return DoSystemTransition(operation, isEnter);
}

int32_t NavDestinationGroupNode::DoSystemTransition(NavigationOperation operation, bool isEnter)
{
    auto noneSystemTransition = NavigationSystemTransitionType::NONE;
    if ((systemTransitionType_ & NavigationSystemTransitionType::FADE) != noneSystemTransition) {
        return DoSystemFadeTransition(isEnter);
    }
    if ((systemTransitionType_ & NavigationSystemTransitionType::SLIDE_RIGHT) != noneSystemTransition ||
        (systemTransitionType_ & NavigationSystemTransitionType::SLIDE_BOTTOM) != noneSystemTransition) {
        return DoSystemSlideTransition(operation, isEnter);
    }
    if ((systemTransitionType_ & NavigationSystemTransitionType::EXPLODE) != noneSystemTransition) {
        return isEnter ? DoSystemEnterExplodeTransition(operation) : DoSystemExitExplodeTransition(operation);
    }
    return INVALID_ANIMATION_ID;
}

int32_t NavDestinationGroupNode::DoSystemFadeTransition(bool isEnter)
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_RETURN(renderContext, INVALID_ANIMATION_ID);
    auto eventHub = GetOrCreateEventHub<EventHub>();
    if (!inCurrentStack_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    animationId_ = MakeUniqueAnimationId();
    SetIsOnAnimation(true);
    auto option = BuildAnimationOption(Curves::SHARP, BuildTransitionFinishCallback(),
        isEnter ? SYSTEM_ENTER_FADE_TRANSITION_DURATION : SYSTEM_EXIT_FADE_TRANSITION_DURATION,
        isEnter ? SYSTEM_ENTER_FADE_TRANSITION_DELAY : SYSTEM_EXIT_FADE_TRANSITION_DELAY);
    OnStartOneTransitionAnimation();
    renderContext->OpacityAnimation(option, isEnter ? 0.0f : 1.0f, isEnter ? 1.0f : 0.0f);
    return animationId_;
}

int32_t NavDestinationGroupNode::DoSystemSlideTransition(NavigationOperation operation, bool isEnter)
{
    auto eventHub = GetOrCreateEventHub<EventHub>();
    if (!inCurrentStack_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    animationId_ = MakeUniqueAnimationId();
    SetIsOnAnimation(true);
    if ((operation == NavigationOperation::POP) ^ isEnter) {
        // translate animation
        bool isRight = (systemTransitionType_ & NavigationSystemTransitionType::SLIDE_RIGHT)
            != NavigationSystemTransitionType::NONE;
        std::function<void()> translateEvent = [weak = WeakClaim(this), isEnter, isRight, operation]() {
            auto navDestination = weak.Upgrade();
            CHECK_NULL_VOID(navDestination);
            auto renderContext = navDestination->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            auto paintRect = renderContext->GetPaintRectWithoutTransform().GetSize();
            auto translate = navDestination->CalcTranslateForSlideTransition(paintRect, isRight, isEnter, true);
            renderContext->UpdateTranslateInXY(translate);
        };
        RefPtr<Curve> curve = isRight ? MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f)
            : MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 36.0f);
        auto option = BuildAnimationOption(curve, BuildTransitionFinishCallback());
        auto renderContext = GetRenderContext();
        auto paintRect = renderContext->GetPaintRectWithoutTransform().GetSize();
        auto translate = CalcTranslateForSlideTransition(paintRect, isRight, isEnter, false);
        renderContext->UpdateTranslateInXY(translate);
        OnStartOneTransitionAnimation();
        AnimationUtils::Animate(
            option, translateEvent, option.GetOnFinishEvent(), nullptr /* repeatCallback */, GetContextRefPtr());
    } else {
        // mask animation
        auto option = BuildAnimationOption(
            Curves::FRICTION, BuildTransitionFinishCallback(), SYSTEM_SLIDE_TRANSITION_MASK_DURATION);
        auto beginColor = isEnter ? SLIDE_ANIMATION_MASK_COLOR : Color::TRANSPARENT;
        auto endColor = !isEnter ? SLIDE_ANIMATION_MASK_COLOR : Color::TRANSPARENT;
        OnStartOneTransitionAnimation();
        DoMaskAnimation(option, beginColor, endColor);
    }
    return animationId_;
}


int32_t NavDestinationGroupNode::DoSystemEnterExplodeTransition(NavigationOperation operation)
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_RETURN(renderContext, INVALID_ANIMATION_ID);
    auto eventHub = GetOrCreateEventHub<EventHub>();
    if (!inCurrentStack_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    animationId_ = MakeUniqueAnimationId();
    SetIsOnAnimation(true);
    if (operation == NavigationOperation::POP) {
        OnStartOneTransitionAnimation();
        // mask animation
        DoMaskAnimation(
            BuildAnimationOption(Curves::FRICTION, BuildEmptyFinishCallback(), SYSTEM_EXPLODE_TRANSITION_MASK_DURATION),
            SLIDE_ANIMATION_MASK_COLOR, Color::TRANSPARENT);
        // opacity animation
        auto option = BuildAnimationOption(Curves::SHARP, BuildTransitionFinishCallback(),
            SYSTEM_ENTER_POP_EXPLODE_OPACITY_DURATION, SYSTEM_ENTER_POP_EXPLODE_OPACITY_DELAY);
        OnStartOneTransitionAnimation();
        renderContext->OpacityAnimation(option, 0.0f, 1.0f);
        return animationId_;
    }
    // opacity animation
    auto option = BuildAnimationOption(Curves::SHARP, BuildTransitionFinishCallback(),
        SYSTEM_ENTER_PUSH_EXPLODE_OPACITY_DURATION, SYSTEM_ENTER_PUSH_EXPLODE_OPACITY_DELAY);
    OnStartOneTransitionAnimation();
    renderContext->OpacityAnimation(option, 0.0f, 1.0f);
    // scale animation for enter-push
    auto scaleCurve = MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 36.0f);
    OnStartOneTransitionAnimation();
    renderContext->ScaleAnimation(
        BuildAnimationOption(scaleCurve, BuildTransitionFinishCallback()), 0.75f, 1.0f);
    return animationId_;
}

int32_t NavDestinationGroupNode::DoSystemExitExplodeTransition(NavigationOperation operation)
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_RETURN(renderContext, INVALID_ANIMATION_ID);
    auto eventHub = GetOrCreateEventHub<EventHub>();
    if (!inCurrentStack_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    animationId_ = MakeUniqueAnimationId();
    SetIsOnAnimation(true);
    if (operation == NavigationOperation::POP) {
        OnStartOneTransitionAnimation();
        // opacity animation
        renderContext->OpacityAnimation(BuildAnimationOption(
            Curves::SHARP, BuildEmptyFinishCallback(), SYSTEM_EXIT_POP_EXPLODE_OPACITY_DURATION), 1.0f, 0.0f);
        // scale animation
        auto scaleCurve = MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 36.0f);
        auto option = BuildAnimationOption(scaleCurve, BuildTransitionFinishCallback());
        OnStartOneTransitionAnimation();
        renderContext->ScaleAnimation(option, 1.0f, 0.8f);
        return animationId_;
    }
    OnStartOneTransitionAnimation();
    // opacity animation
    renderContext->OpacityAnimation(
        BuildAnimationOption(Curves::SHARP, BuildEmptyFinishCallback(), SYSTEM_EXIT_PUSH_EXPLODE_OPACITY_DELAY),
        1.0f, 0.0f);
    // mask animation
    auto maskOption = BuildAnimationOption(
        Curves::FRICTION, BuildTransitionFinishCallback(), SYSTEM_EXPLODE_TRANSITION_MASK_DURATION);
    OnStartOneTransitionAnimation();
    DoMaskAnimation(maskOption, Color::TRANSPARENT, SLIDE_ANIMATION_MASK_COLOR);
    return animationId_;
}

void NavDestinationGroupNode::DoMaskAnimation(const AnimationOption& option, Color begin, Color end)
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    std::function<void()> maskEvent = [weak = WeakClaim(this), end]() {
        auto navDestination = weak.Upgrade();
        CHECK_NULL_VOID(navDestination);
        auto renderContext = navDestination->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetActualForegroundColor(end);
    };

    // initial property
    renderContext->SetActualForegroundColor(begin);
    AnimationUtils::Animate(
        option, maskEvent, option.GetOnFinishEvent(), nullptr /* repeatCallback */, GetContextRefPtr());
}

int32_t NavDestinationGroupNode::DoCustomTransition(NavigationOperation operation, bool isEnter)
{
    auto delegate = navDestinationTransitionDelegate_;
    if (!delegate) {
        return INVALID_ANIMATION_ID;
    }
    auto eventHub = GetOrCreateEventHub<EventHub>();
    if (!inCurrentStack_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    auto allTransitions = delegate(operation, isEnter);
    if (!allTransitions.has_value()) {
        return INVALID_ANIMATION_ID;
    }
    int32_t longestAnimationDuration = INT32_MIN;
    for (auto transition: allTransitions.value()) {
        if (transition.duration + transition.delay > longestAnimationDuration) {
            longestAnimationDuration = transition.duration + transition.delay;
        }
    }
    if (longestAnimationDuration != INT32_MIN) {
        SetIsOnAnimation(true);
    } else {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "navDestination custom transition array is empty!");
    }
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, INVALID_ANIMATION_ID);
    pipeline->FlushBuild();
    pipeline->FlushUITasks();
    animationId_ = MakeUniqueAnimationId();
    bool hasRest = false;
    for (auto transition: allTransitions.value()) {
        StartCustomTransitionAnimation(transition, isEnter, hasRest, longestAnimationDuration);
    }
    return animationId_;
}

void NavDestinationGroupNode::StartCustomTransitionAnimation(NavDestinationTransition& transition,
    bool isEnter, bool& hasResetProperties, int32_t longestAnimationDuration)
{
    AnimationOption option;
    option.SetDuration(transition.duration);
    option.SetCurve(transition.curve);
    option.SetDelay(transition.delay);

    std::function<void()> event =
        [transitionEvent = std::move(transition.event), weak = WeakClaim(this), isEnter, &hasResetProperties]() {
            // do necessary system-side tasks
            auto navDestination = weak.Upgrade();
            CHECK_NULL_VOID(navDestination);
            if (!hasResetProperties && isEnter) {
                auto pattern = navDestination->GetPattern<NavDestinationPattern>();
                CHECK_NULL_VOID(pattern);
                auto navigation = AceType::DynamicCast<NavigationGroupNode>(pattern->GetNavigationNode());
                if (navigation) {
                    /*
                    *  Reset the system animation properties in custom transition
                    *  animation closure to prevent animation mutation.
                    */
                    navigation->ResetSystemAnimationProperties(navDestination);
                }
                hasResetProperties = true;
            }
            // do user-set task
            transitionEvent();
            auto pipeline = navDestination->GetContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->FlushBuild();
            pipeline->FlushUITasks();
        };
    std::function<void()> finish;
    // only do remove or set visibility in longest custom transition animation's finish callback.
    if (transition.duration + transition.delay == longestAnimationDuration) {
        finish = BuildTransitionFinishCallback(false, std::move(transition.onTransitionEnd));
    } else {
        finish = [onTransitionEnd = std::move(transition.onTransitionEnd), weak = WeakClaim(this)]() {
            auto node = weak.Upgrade();
            if (onTransitionEnd) {
                onTransitionEnd();
            }
            CHECK_NULL_VOID(node);
            node->OnFinishOneTransitionAnimation();
        };
    }
    OnStartOneTransitionAnimation();
    AnimationUtils::Animate(option, event, finish, nullptr /* repeatCallback */, GetContextRefPtr());
    auto pattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(pattern);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s trigger custom transition, duration: %{public}d, delay: %{public}d, curve: %{public}s",
        pattern->GetName().c_str(), transition.duration, transition.delay, transition.curve->ToString().c_str());
}

int32_t NavDestinationGroupNode::MakeUniqueAnimationId()
{
    auto navDestinationPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, INVALID_ANIMATION_ID);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navDestinationPattern->GetNavigationNode());
    CHECK_NULL_RETURN(navigationNode, INVALID_ANIMATION_ID);
    return navigationNode->MakeUniqueAnimationId();
}

std::function<void()> NavDestinationGroupNode::BuildTransitionFinishCallback(
    bool isSystemTransition, std::function<void()>&& extraOption)
{
    std::function<void()> finish = [extraOption = std::move(extraOption), weak = WeakClaim(this),
        animationId = animationId_, isSystemTransition]() {
            auto navDestination = weak.Upgrade();
            CHECK_NULL_VOID(navDestination);
            auto destinationPattern = navDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(destinationPattern);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s transition finish", destinationPattern->GetName().c_str());
            // do extraOption first
            if (extraOption) {
                extraOption();
            }
            // do necessary system-side tasks
            if (animationId != navDestination->GetAnimationId()) {
                return;
            }
            if (isSystemTransition) {
                navDestination->ResetCustomTransitionAnimationProperties();
            }
            if (navDestination->IsHomeDestination()) {
                auto navNode = AceType::DynamicCast<NavigationGroupNode>(navDestination->GetNavigationNode());
                CHECK_NULL_VOID(navNode);
                auto navPattern = navNode->GetPattern<NavigationPattern>();
                CHECK_NULL_VOID(navPattern);
                auto mode = navPattern->GetNavigationMode();
                if (mode == NavigationMode::STACK && navDestination->HasStandardBefore()) {
                    navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                    navDestination->SetJSViewActive(false);
                }
                navDestination->SetIsOnAnimation(false);
                return;
            }
            // only handle current node in latest finish callback.
            if (!navDestination->GetInCurrentStack()) {
                // can't be reused means it is not in navigation stack anymore, so remove it.
                navDestination->CleanContent(false, true);
                auto parent = navDestination->GetParent();
                CHECK_NULL_VOID(parent);
                parent->RemoveChild(navDestination);
                parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            } else if (navDestination->HasStandardBefore()) {
                navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                navDestination->SetJSViewActive(false);
            }
            navDestination->SetIsOnAnimation(false);
        };
    auto finisWrapper = [onFinish = std::move(finish), weak = WeakClaim(this)]() {
        auto node = weak.Upgrade();
        if (onFinish) {
            onFinish();
        }
        CHECK_NULL_VOID(node);
        node->OnFinishOneTransitionAnimation();
    };
    return finisWrapper;
}

std::function<void()> NavDestinationGroupNode::BuildEmptyFinishCallback()
{
    auto finish = [weak = WeakClaim(this)]() {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->OnFinishOneTransitionAnimation();
    };
    return finish;
}

bool NavDestinationGroupNode::HasStandardBefore() const
{
    auto navDestinationPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, false);
    auto navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(navDestinationPattern->GetNavigationNode());
    CHECK_NULL_RETURN(navigationNode, false);
    return index_ < navigationNode->GetLastStandardIndex();
}

void NavDestinationGroupNode::ResetCustomTransitionAnimationProperties()
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTranslateInXY({ 0.0f, 0.0f });
    renderContext->SetOpacity(userSetOpacity_);
    renderContext->SetActualForegroundColor(Color::TRANSPARENT);
}

RefPtr<UINode> NavDestinationGroupNode::GetNavigationNode()
{
    auto navDestinationPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, nullptr);
    return navDestinationPattern->GetNavigationNode();
}

NavDestinationMode NavDestinationGroupNode::GetNavDestinationMode() const
{
    if (destType_ == NavDestinationType::PROXY) {
        auto primaryNode = primaryNode_.Upgrade();
        CHECK_NULL_RETURN(primaryNode, mode_);
        return primaryNode->GetNavDestinationMode();
    }
    return mode_;
}

RefPtr<NavDestinationGroupNode> NavDestinationGroupNode::GetOrCreateProxyNode()
{
    if (proxyNode_) {
        return proxyNode_;
    }

    auto proxyNode = ForceSplitUtils::CreateNavDestinationProxyNode();
    CHECK_NULL_RETURN(proxyNode, nullptr);
    proxyNode->SetPrimaryNode(WeakClaim(this));
    auto proxyPattern = proxyNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(proxyPattern, nullptr);
    proxyPattern->SetIndex(index_);
    proxyNode_ = proxyNode;
    return proxyNode_;
}

void NavDestinationGroupNode::SetIndex(int32_t index, bool updatePrimary)
{
    index_ = index;
    if (destType_ == NavDestinationType::PROXY && updatePrimary) {
        auto primaryNode = primaryNode_.Upgrade();
        CHECK_NULL_VOID(primaryNode);
        primaryNode->SetIndex(index, false);
    } else if (proxyNode_) {
        proxyNode_->SetIndex(index, false);
    }
}

void NavDestinationGroupNode::SetCanReused(bool canReused)
{
    if (destType_ == NavDestinationType::PROXY) {
        auto primaryNode = primaryNode_.Upgrade();
        if (primaryNode) {
            primaryNode->SetCanReused(canReused);
        }
    }
    canReused_ = canReused;
}

bool NavDestinationGroupNode::GetCanReused() const
{
    if (destType_ == NavDestinationType::PROXY) {
        auto primaryNode = primaryNode_.Upgrade();
        if (primaryNode) {
            return primaryNode->GetCanReused();
        }
    }
    return canReused_;
}
} // namespace OHOS::Ace::NG
