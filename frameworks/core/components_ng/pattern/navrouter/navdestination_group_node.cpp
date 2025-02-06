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

#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_transition_proxy.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
constexpr double HALF = 0.5;
constexpr float CONTENT_OFFSET_PERCENT = 0.2f;
constexpr float TITLE_OFFSET_PERCENT = 0.02f;
constexpr float REMOVE_CLIP_SIZE = 10000.0f;
constexpr int32_t OPACITY_TITLE_OUT_DELAY = 17;
constexpr int32_t OPACITY_TITLE_IN_DELAY = 33;
constexpr int32_t OPACITY_TITLE_DURATION = 150;
constexpr int32_t OPACITY_BACKBUTTON_IN_DELAY = 150;
constexpr int32_t OPACITY_BACKBUTTON_IN_DURATION = 200;
constexpr int32_t OPACITY_BACKBUTTON_OUT_DURATION = 67;
constexpr int32_t MAX_RENDER_GROUP_TEXT_NODE_COUNT = 50;
constexpr float MAX_RENDER_GROUP_TEXT_NODE_HEIGHT = 150.0f;
constexpr int32_t INVALID_ANIMATION_ID = -1;
constexpr int32_t SYSTEM_FADE_TRANSITION_DURATION = 200;
constexpr int32_t SYSTEM_FADE_TRANSITION_DELAY = 50;
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
        return true;
    }
    return (systemTransitionType_ & NavigationSystemTransitionType::CONTENT) != NavigationSystemTransitionType::NONE;
}

bool NavDestinationGroupNode::TransitionContentInValid()
{
    return (systemTransitionType_ & NavigationSystemTransitionType::CONTENT) == NavigationSystemTransitionType::NONE
        && mode_ == NavDestinationMode::STANDARD;
}

bool NavDestinationGroupNode::IsNeedTitleTransition()
{
    if (systemTransitionType_ == NavigationSystemTransitionType::DEFAULT) {
        return true;
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
        auto eventHub = GetEventHub<NavDestinationEventHub>();
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
    json->PutExtAttr("mode", mode_ == NavDestinationMode::DIALOG
        ? "NavDestinationMode::DIALOG"
        : "NavDestinationMode::STANDARD", filter);
    json->PutExtAttr("systemTransition", TransitionTypeToString(systemTransitionType_), filter);
}

void NavDestinationGroupNode::InitSystemTransitionPush(bool transitionIn)
{
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    float isRTL = GetLanguageDirection();
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    if (transitionIn) {
        SetIsOnAnimation(true);
        SetTransitionType(PageTransitionType::ENTER_PUSH);
        auto frameSize = GetGeometryNode()->GetFrameSize();
        if (needContentAnimation) {
            if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
                GetRenderContext()->ClipWithRRect(
                    RectF(0.0f, 0.0f, frameSize.Width() * HALF, REMOVE_CLIP_SIZE), RadiusF(EdgeF(0.0f, 0.0f)));
            } else {
                GetRenderContext()->ClipWithRRect(
                    RectF(frameSize.Width() * HALF, 0.0f, frameSize.Width(), REMOVE_CLIP_SIZE),
                    RadiusF(EdgeF(0.0f, 0.0f)));
            }
            GetRenderContext()->UpdateTranslateInXY({ frameSize.Width() * HALF * isRTL, 0.0f });
        }
        if (titleBarNode && needTitleAnimation) {
            titleBarNode->GetRenderContext()->UpdateTranslateInXY({ frameSize.Width() * HALF * isRTL, 0.0f });
        }
        return;
    }
    SetTransitionType(PageTransitionType::EXIT_PUSH);
    SetIsOnAnimation(true);
    GetRenderContext()->RemoveClipWithRRect();
    if (needContentAnimation) {
        GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
    if (NeedRemoveInPush()) {
        GetEventHub<EventHub>()->SetEnabledInternal(false);
    }
    if (titleBarNode && needTitleAnimation) {
        titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
}

void NavDestinationGroupNode::StartSystemTransitionPush(bool transitionIn)
{
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    auto frameSize = GetGeometryNode()->GetFrameSize();
    float isRTL = GetLanguageDirection();
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    if (transitionIn) {
        if (needContentAnimation) {
            GetRenderContext()->ClipWithRRect(
                RectF(0.0f, 0.0f, frameSize.Width(), REMOVE_CLIP_SIZE), RadiusF(EdgeF(0.0f, 0.0f)));
            GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        }
        if (titleBarNode && needTitleAnimation) {
            titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        }
        return;
    }
    if (needContentAnimation) {
        GetRenderContext()->UpdateTranslateInXY(
            { -frameSize.Width() * CONTENT_OFFSET_PERCENT * isRTL, 0.0f });
    }
    if (titleBarNode && needTitleAnimation) {
        titleBarNode->GetRenderContext()->UpdateTranslateInXY(
            { frameSize.Width() * TITLE_OFFSET_PERCENT  * isRTL, 0.0f });
    }
}

void NavDestinationGroupNode::SystemTransitionPushCallback(bool transitionIn, const int32_t animationId)
{
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

void NavDestinationGroupNode::InitSystemTransitionPop(bool isTransitionIn)
{
    auto frameSize = GetGeometryNode()->GetFrameSize();
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    float isRTL = GetLanguageDirection();
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    if (isTransitionIn) {
        SetTransitionType(PageTransitionType::ENTER_POP);
        GetRenderContext()->RemoveClipWithRRect();
        if (needContentAnimation) {
            GetRenderContext()->UpdateTranslateInXY({ -frameSize.Width() * CONTENT_OFFSET_PERCENT * isRTL, 0.0f });
        }
        if (titleBarNode && needTitleAnimation) {
            titleBarNode->GetRenderContext()->UpdateTranslateInXY(
                { frameSize.Width() * TITLE_OFFSET_PERCENT * isRTL, 0.0f });
        }
        return;
    }
    SetIsOnAnimation(true);
    SetTransitionType(PageTransitionType::EXIT_POP);
    GetEventHub<EventHub>()->SetEnabledInternal(false);
    if (needContentAnimation) {
        GetRenderContext()->ClipWithRRect(RectF(0.0f, 0.0f, frameSize.Width(), REMOVE_CLIP_SIZE),
            RadiusF(EdgeF(0.0f, 0.0f)));
        GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
    if (titleBarNode && needTitleAnimation) {
        titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }
}

void NavDestinationGroupNode::StartSystemTransitionPop(bool transitionIn)
{
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    if (transitionIn) {
        if (needContentAnimation) {
            GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        }
        if (titleBarNode && needTitleAnimation) {
            titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        }
        return;
    }
    auto frameSize = GetGeometryNode()->GetFrameSize();
    float isRTL = GetLanguageDirection();
    if (needContentAnimation) {
        if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
            GetRenderContext()->ClipWithRRect(
                RectF(0.0f, 0.0f, frameSize.Width() * HALF, REMOVE_CLIP_SIZE), RadiusF(EdgeF(0.0f, 0.0f)));
        } else {
            GetRenderContext()->ClipWithRRect(
                RectF(frameSize.Width() * HALF, 0.0f, frameSize.Width(), REMOVE_CLIP_SIZE),
                RadiusF(EdgeF(0.0f, 0.0f)));
        }
        GetRenderContext()->UpdateTranslateInXY({ frameSize.Width() * HALF * isRTL, 0.0f });
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

bool NavDestinationGroupNode::SystemTransitionPopCallback(const int32_t animationId)
{
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
    auto shallowBuilder = preNavDesPattern->GetShallowBuilder();
    if (shallowBuilder && !IsCacheNode()) {
        shallowBuilder->MarkIsExecuteDeepRenderDone(false);
    }
    if (!IsCacheNode() && GetContentNode()) {
        GetContentNode()->Clean();
    }
    GetEventHub<EventHub>()->SetEnabledInternal(true);
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
    if (systemTransitionType_ == NavigationSystemTransitionType::NONE
        || systemTransitionType_ == NavigationSystemTransitionType::TITLE) {
        return;
    }
    auto contentNode = AceType::DynamicCast<FrameNode>(GetContentNode());
    CHECK_NULL_VOID(contentNode);
    auto context = contentNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (isZeroY) {
        context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
        return;
    }
    context->UpdateTransformTranslate({ 0.0f,
        contentNode->GetGeometryNode()->GetFrameSize().Height(), 0.0f });
}

std::shared_ptr<AnimationUtils::Animation> NavDestinationGroupNode::TitleOpacityAnimation(bool isTransitionIn)
{
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
        });
    }
    // recover after transition animation.
    opacityOption.SetDelay(OPACITY_TITLE_OUT_DELAY);
    titleRenderContext->SetOpacity(1.0f);
    return AnimationUtils::StartAnimation(opacityOption,
        [weakRender = WeakPtr<RenderContext>(titleRenderContext)]() {
        auto renderContext = weakRender.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetOpacity(0.0f);
    });
}

std::shared_ptr<AnimationUtils::Animation> NavDestinationGroupNode::BackButtonAnimation(bool isTransitionIn)
{
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
        });
    }
    transitionOption.SetDuration(OPACITY_BACKBUTTON_OUT_DURATION);
    backButtonNodeContext->SetOpacity(1.0f);
    return AnimationUtils::StartAnimation(transitionOption,
        [weakRender = WeakPtr<RenderContext>(backButtonNodeContext)]() {
        auto renderContext = weakRender.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetOpacity(0.0f);
    });
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

void NavDestinationGroupNode::CleanContent()
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
        GetContentNode()->Clean(false, true);
    }
}

bool NavDestinationGroupNode::IsNodeInvisible(const RefPtr<FrameNode>& node)
{
    auto navigaiton = DynamicCast<NavigationGroupNode>(node);
    CHECK_NULL_RETURN(navigaiton, false);
    int32_t lastStandardIndex = navigaiton->GetLastStandardIndex();
    bool isInvisible = index_ < lastStandardIndex;
    return isInvisible;
}

std::string NavDestinationGroupNode::ToDumpString()
{
    std::string dumpString;
    auto navDestinationPattern = GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, dumpString);
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
    dumpString.append("\" }");
    return dumpString;
}

int32_t NavDestinationGroupNode::DoTransition(NavigationOperation operation, bool isEnter)
{
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
    auto eventHub = GetEventHub<EventHub>();
    if (!canReused_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    animationId_ = MakeUniqueAnimationId();
    auto option = BuildAnimationOption(
        Curves::SHARP, BuildTransitionFinishCallback(), SYSTEM_FADE_TRANSITION_DURATION, SYSTEM_FADE_TRANSITION_DELAY);
    renderContext->OpacityAnimation(option, isEnter ? 0.0f : 1.0f, isEnter ? 1.0f : 0.0f);
    return animationId_;
}

int32_t NavDestinationGroupNode::DoSystemSlideTransition(NavigationOperation operation, bool isEnter)
{
    auto eventHub = GetEventHub<EventHub>();
    if (!canReused_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    animationId_ = MakeUniqueAnimationId();
    if ((operation == NavigationOperation::POP) ^ isEnter) {
        // translate animation
        bool isRight = (systemTransitionType_ & NavigationSystemTransitionType::SLIDE_RIGHT)
            != NavigationSystemTransitionType::NONE;
        std::function<void()> translateEvent = [weak = WeakClaim(this), isEnter, isRight, operation]() {
            auto navDestination = weak.Upgrade();
            CHECK_NULL_VOID(navDestination);
            auto renderContext = navDestination->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            if (!isEnter) {
                auto frameSize = navDestination->GetGeometryNode()->GetFrameSize();
                renderContext->UpdateTranslateInXY(
                    { isRight ? frameSize.Width() : 0.0f, isRight ? 0.0f : frameSize.Height() });
            } else {
                renderContext->UpdateTranslateInXY({ 0.0f, 0.0f });
            }
        };
        auto option = BuildAnimationOption(
            MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f), BuildTransitionFinishCallback());
        if (!isEnter) {
            GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        } else {
            auto frameSize = GetGeometryNode()->GetFrameSize();
            GetRenderContext()->UpdateTranslateInXY(
                { isRight ? frameSize.Width() : 0.0f, isRight ? 0.0f : frameSize.Height() });
        }
        AnimationUtils::Animate(option, translateEvent, option.GetOnFinishEvent());
    } else {
        // mask animation
        auto option = BuildAnimationOption(
            Curves::FRICTION, BuildTransitionFinishCallback(), SYSTEM_SLIDE_TRANSITION_MASK_DURATION);
        auto beginColor = isEnter ? SLIDE_ANIMATION_MASK_COLOR : Color::TRANSPARENT;
        auto endColor = !isEnter ? SLIDE_ANIMATION_MASK_COLOR : Color::TRANSPARENT;
        DoMaskAnimation(option, beginColor, endColor);
    }
    return animationId_;
}


int32_t NavDestinationGroupNode::DoSystemEnterExplodeTransition(NavigationOperation operation)
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_RETURN(renderContext, INVALID_ANIMATION_ID);
    auto eventHub = GetEventHub<EventHub>();
    if (!canReused_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    animationId_ = MakeUniqueAnimationId();
    if (operation == NavigationOperation::POP) {
        // mask animation
        DoMaskAnimation(BuildAnimationOption(Curves::FRICTION, nullptr, SYSTEM_EXPLODE_TRANSITION_MASK_DURATION),
            SLIDE_ANIMATION_MASK_COLOR, Color::TRANSPARENT);
        // opacity animation
        auto option = BuildAnimationOption(Curves::SHARP, BuildTransitionFinishCallback(),
            SYSTEM_ENTER_POP_EXPLODE_OPACITY_DURATION, SYSTEM_ENTER_POP_EXPLODE_OPACITY_DELAY);
        renderContext->OpacityAnimation(option, 0.0f, 1.0f);
        return animationId_;
    }
    // opacity animation
    auto option = BuildAnimationOption(Curves::SHARP, BuildTransitionFinishCallback(),
        SYSTEM_ENTER_PUSH_EXPLODE_OPACITY_DURATION, SYSTEM_ENTER_PUSH_EXPLODE_OPACITY_DELAY);
    renderContext->OpacityAnimation(option, 0.0f, 1.0f);
    // scale animation for enter-push
    auto scaleCurve = MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 36.0f);
    renderContext->ScaleAnimation(
        BuildAnimationOption(scaleCurve, BuildTransitionFinishCallback()), 0.75f, 1.0f);
    return animationId_;
}

int32_t NavDestinationGroupNode::DoSystemExitExplodeTransition(NavigationOperation operation)
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_RETURN(renderContext, INVALID_ANIMATION_ID);
    auto eventHub = GetEventHub<EventHub>();
    if (!canReused_ && eventHub) {
        eventHub->SetEnabledInternal(false);
    }
    animationId_ = MakeUniqueAnimationId();
    if (operation == NavigationOperation::POP) {
        // opacity animation
        renderContext->OpacityAnimation(
            BuildAnimationOption(Curves::SHARP, nullptr, SYSTEM_EXIT_POP_EXPLODE_OPACITY_DURATION), 1.0f, 0.0f);
        // scale animation
        auto scaleCurve = MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 36.0f);
        auto option = BuildAnimationOption(scaleCurve, BuildTransitionFinishCallback());
        renderContext->ScaleAnimation(option, 1.0f, 0.8f);
        return animationId_;
    }
    // opacity animation
    renderContext->OpacityAnimation(
        BuildAnimationOption(Curves::SHARP, nullptr, SYSTEM_EXIT_PUSH_EXPLODE_OPACITY_DELAY), 1.0f, 0.0f);
    // mask animation
    auto maskOption = BuildAnimationOption(
        Curves::FRICTION, BuildTransitionFinishCallback(), SYSTEM_EXPLODE_TRANSITION_MASK_DURATION);
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
    AnimationUtils::Animate(option, maskEvent, option.GetOnFinishEvent());
}

int32_t NavDestinationGroupNode::DoCustomTransition(NavigationOperation operation, bool isEnter)
{
    auto delegate = navDestinationTransitionDelegate_;
    if (!delegate) {
        return INVALID_ANIMATION_ID;
    }
    auto eventHub = GetEventHub<EventHub>();
    if (!canReused_ && eventHub) {
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
    if (longestAnimationDuration == INT32_MIN) {
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
            navDestination->SetIsOnAnimation(true);
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
    // only do remove or set visibility in longest custom transition animation's finish callback.
    std::function<void()> finish = transition.duration + transition.delay == longestAnimationDuration ?
        BuildTransitionFinishCallback(false, std::move(transition.onTransitionEnd)) :
        std::move(transition.onTransitionEnd);
    AnimationUtils::Animate(option, event, finish);
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
            // only handle current node in latest finish callback.
            if (!navDestination->GetCanReused()) {
                // can't be reused means it is not in navigation stack anymore, so remove it.
                navDestination->CleanContent();
                auto parent = navDestination->GetParent();
                CHECK_NULL_VOID(parent);
                parent->RemoveChild(navDestination);
            } else if (navDestination->HasStandardBefore()) {
                navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                navDestination->SetJSViewActive(false);
            }
            navDestination->SetIsOnAnimation(false);
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
} // namespace OHOS::Ace::NG
