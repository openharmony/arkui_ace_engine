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

void NavDestinationGroupNode::EndSystemTransitionPush(bool transitionIn)
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

void NavDestinationGroupNode::FinishSystemTransitionPush(bool transitionIn, const int32_t animationId)
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

void NavDestinationGroupNode::InitSystemTransitionPop(bool transitionIn)
{
    auto frameSize = GetGeometryNode()->GetFrameSize();
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    float isRTL = GetLanguageDirection();
    bool needContentAnimation = IsNeedContentTransition();
    bool needTitleAnimation = IsNeedTitleTransition();
    if (transitionIn) {
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

void NavDestinationGroupNode::EndSystemTransitionPop(bool transitionIn)
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
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleNode->GetBackButton());
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

void NavDestinationGroupNode::FinishSystemTransitionAnimationPush(RefPtr<FrameNode>& preNode,
    RefPtr<FrameNode>& naviagtionNode, bool transitionIn, const int32_t animationId)
{
    auto navigaiton = DynamicCast<NavigationGroupNode>(naviagtionNode);
    CHECK_NULL_VOID(navigaiton);
    if (NeedRemoveInPush()) {
        auto preDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        CHECK_NULL_VOID(preDestination);
        navigaiton->GetHideNodes().emplace_back(std::make_pair(preDestination, true));
        return;
    }
    FinishSystemTransitionPush(transitionIn, animationId);
    GetRenderContext()->SetOpacity(1.0f);
}
} // namespace OHOS::Ace::NG
