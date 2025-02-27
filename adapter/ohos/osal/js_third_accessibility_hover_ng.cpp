/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "js_third_provider_interaction_operation.h"

#include "accessibility_system_ability_client.h"
#include "frameworks/core/components_ng/pattern/web/web_pattern.h"
#include "js_third_accessibility_hover_ng.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;
using namespace std;

namespace OHOS::Ace::Framework {
constexpr int32_t ACCESSIBILITY_FOCUS_WITHOUT_EVENT = -2100001;

namespace {
bool IsTouchExplorationEnabled(const RefPtr<NG::PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, true);
    auto jsAccessibilityManager = context->GetAccessibilityManager();
    CHECK_NULL_RETURN(jsAccessibilityManager, true);
    auto accessibilityWorkMode = jsAccessibilityManager->GenerateAccessibilityWorkMode();
    return accessibilityWorkMode.isTouchExplorationEnabled;
}
} // namespace

bool AccessibilityHoverManagerForThirdNG::GetElementInfoForThird(
    int64_t elementId,
    AccessibilityElementInfo& info,
    int64_t hostElementId)
{
    // this function only for third party hover process
    auto jsThirdProviderOperator =
        GetJsThirdProviderInteractionOperation(hostElementId).lock();
    if (jsThirdProviderOperator == nullptr) {
        TAG_LOGE(AceLogTag::ACE_ACCESSIBILITY,
            "third jsThirdProviderOperator ptr is null, hostElementId %{public}" PRId64,
            hostElementId);
        return false;
    }

    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = jsThirdProviderOperator->FindAccessibilityNodeInfosByIdFromProvider(
        elementId, 0, 0, infos, true); // offset in hover no need fix host offset
    if ((!ret) || (infos.size() == 0)) {
        TAG_LOGE(AceLogTag::ACE_ACCESSIBILITY,
            "cannot get third elementinfo :%{public}" PRId64 ", ret: %{public}d",
            elementId, ret);
        return false;
    }
    info = infos.front();
    return true;
}

void AccessibilityHoverManagerForThirdNG::UpdateSearchStrategyByHitTestModeStr(
    std::string& hitTestMode,
    bool& shouldSearchSelf,
    bool& shouldSearchChildren)
{
    if (hitTestMode == "HitTestMode.Block") {
        shouldSearchChildren = false;
    }  else if (hitTestMode == "HitTestMode.None") {
        shouldSearchSelf = false;
    }
}

bool AccessibilityHoverManagerForThirdNG::HasAccessibilityTextOrDescription(
    const AccessibilityElementInfo& nodeInfo)
{
    std::optional<std::string> accessibilityText = nodeInfo.GetAccessibilityText();
    std::optional<std::string> accessibilityDescription = nodeInfo.GetDescriptionInfo();
    return !accessibilityText.value_or("").empty() ||
        !accessibilityDescription.value_or("").empty();
}

bool AccessibilityHoverManagerForThirdNG::IsAccessibilityFocusable(
    const AccessibilityElementInfo& nodeInfo)
{
    auto level = nodeInfo.GetAccessibilityLevel();
    if (level == NG::AccessibilityProperty::Level::YES_STR) {
        return true;
    }
    if (level == NG::AccessibilityProperty::Level::NO_STR) {
        return false;
    }
    if (nodeInfo.GetAccessibilityGroup() ||
        !nodeInfo.GetActionList().empty() ||
        HasAccessibilityTextOrDescription(nodeInfo) ||
        !nodeInfo.GetContent().empty()) {
        return true;
    }
    // expand to enabled and clickable
    // default tag
    if (NG::AccessibilityProperty::IsAccessibilityFocusableTag(
        nodeInfo.GetComponentType()) == true) {
        return true;
    }
    return false;
}

std::pair<bool, bool> AccessibilityHoverManagerForThirdNG::GetSearchStrategyForThird(
    const AccessibilityElementInfo& nodeInfo)
{
    bool shouldSearchSelf = true;
    bool shouldSearchChildren = true;
    auto level = NG::AccessibilityProperty::Level::AUTO;
    do {
        level = nodeInfo.GetAccessibilityLevel();
        bool hasAccessibilityText = HasAccessibilityTextOrDescription(nodeInfo);
        if (level == NG::AccessibilityProperty::Level::YES_STR) {
            break;
        } else if (level == NG::AccessibilityProperty::Level::NO_HIDE_DESCENDANTS) {
            shouldSearchSelf = false;
            shouldSearchChildren = false;
            break;
        } else {
            if (level == NG::AccessibilityProperty::Level::NO_STR) {
                shouldSearchSelf = false;
            } else {
                // shouldSearchSelf is true here
                if (hasAccessibilityText) {
                    break;
                }
            }
        }
    
        auto hitTestMode = nodeInfo.GetHitTestBehavior();
        UpdateSearchStrategyByHitTestModeStr(
            hitTestMode, shouldSearchSelf, shouldSearchChildren);
    } while (0);

    if (IsAccessibilityFocusable(nodeInfo) == false) {
        shouldSearchSelf = false;
    }

    return std::make_pair(shouldSearchSelf, shouldSearchChildren);
}


bool AccessibilityHoverManagerForThirdNG::HoverPathForThirdRecursive(
    const int64_t hostElementId,
    const NG::PointF& hoverPoint,
    const AccessibilityElementInfo& nodeInfo,
    AccessibilityHoverTestPathForThird& path)
{
    bool hitTarget = false;
    auto [shouldSearchSelf, shouldSearchChildren]
        = GetSearchStrategyForThird(nodeInfo);
    auto rectInScreen = nodeInfo.GetRectInScreen();
    auto left = rectInScreen.GetLeftTopXScreenPostion();
    auto right = rectInScreen.GetLeftTopYScreenPostion();
    auto width = rectInScreen.GetRightBottomXScreenPostion() - rectInScreen.GetLeftTopXScreenPostion();
    auto height = rectInScreen.GetRightBottomYScreenPostion() - rectInScreen.GetLeftTopYScreenPostion();
    NG::RectF rect { left, right, width, height };
    bool hitSelf = rect.IsInnerRegion(hoverPoint);
    if (hitSelf && shouldSearchSelf) {
        hitTarget = true;
        path.push_back(nodeInfo.GetAccessibilityId());
    }
    TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY,
            "third hover elementId :%{public}" PRId64\
            ", shouldSearchSelf: %{public}d shouldSearchChildren: %{public}d hitTarget: %{public}d ",
            nodeInfo.GetAccessibilityId(), shouldSearchSelf, shouldSearchChildren, hitTarget);
    if (shouldSearchChildren) {
        auto childrenIds = nodeInfo.GetChildIds();
        for (auto childId = childrenIds.rbegin(); childId != childrenIds.rend(); ++childId) {
            AccessibilityElementInfo childInfo;
            if (GetElementInfoForThird(*childId, childInfo, hostElementId) == false) {
                break;
            }
            if (HoverPathForThirdRecursive(
                hostElementId, hoverPoint, childInfo, path)) {
                return true;
            }
        }
    }
    return hitTarget;
}

AccessibilityHoverTestPathForThird AccessibilityHoverManagerForThirdNG::HoverPathForThird(
    const int64_t hostElementId,
    const NG::PointF& point,
    AccessibilityElementInfo& rootInfo)
{
    AccessibilityHoverTestPathForThird path;
    HoverPathForThirdRecursive(
        hostElementId, point, rootInfo, path);
    return path;
}

void AccessibilityHoverManagerForThirdNG::ResetHoverForThirdState()
{
    hoverForThirdState_.idle = true;
    hoverForThirdState_.nodesHovering.clear();
}

void AccessibilityHoverManagerForThirdNG::HandleAccessibilityHoverForThird(
    const AccessibilityHoverForThirdConfig& config)
{
    CHECK_NULL_VOID(config.hostNode);
    if (config.eventType == NG::AccessibilityHoverEventType::ENTER) {
        ResetHoverForThirdState();
    }
    std::vector<int64_t> currentNodesHovering;
    std::vector<int64_t> lastNodesHovering = hoverForThirdState_.nodesHovering;
    if (config.eventType != NG::AccessibilityHoverEventType::EXIT) {
        AccessibilityElementInfo rootInfo;
        if (GetElementInfoForThird(-1, rootInfo, config.hostElementId) == false) {
            return;
        }
        AccessibilityHoverTestPathForThird path =
            HoverPathForThird(config.hostElementId, config.point, rootInfo);
        for (const auto& node: path) {
            currentNodesHovering.push_back(node);
        }
    }
    static constexpr int64_t INVALID_NODE_ID = -1;
    int64_t lastHoveringId = INVALID_NODE_ID;
    if (!lastNodesHovering.empty()) {
        lastHoveringId = lastNodesHovering.back();
    }
    int64_t currentHoveringId = INVALID_NODE_ID;
    if (!currentNodesHovering.empty()) {
        currentHoveringId = currentNodesHovering.back();
    }
    auto jsThirdProviderOperator = GetJsThirdProviderInteractionOperation(
        config.hostElementId).lock();
    if (jsThirdProviderOperator == nullptr) {
        TAG_LOGE(AceLogTag::ACE_ACCESSIBILITY, "jsThirdProviderOperator is null, "
            "hostElementId %{public}" PRId64, config.hostElementId);
        return;
    }
    if (lastHoveringId != INVALID_NODE_ID && lastHoveringId != currentHoveringId) {
        jsThirdProviderOperator->SendAccessibilityAsyncEventForThird(lastHoveringId,
            Accessibility::EventType::TYPE_VIEW_HOVER_EXIT_EVENT);
    }
    if ((currentHoveringId != INVALID_NODE_ID) && (currentHoveringId != lastHoveringId)) {
        jsThirdProviderOperator->SendAccessibilityAsyncEventForThird(currentHoveringId,
            Accessibility::EventType::TYPE_VIEW_HOVER_ENTER_EVENT);
    }
    hoverForThirdState_.nodesHovering = std::move(currentNodesHovering);
    hoverForThirdState_.time = config.time;
    hoverForThirdState_.source = config.sourceType;
    hoverForThirdState_.idle = config.eventType == NG::AccessibilityHoverEventType::EXIT;
}

bool AccessibilityHoverManagerForThirdNG::ClearThirdAccessibilityFocus(
    const RefPtr<NG::FrameNode>& hostNode)
{
    CHECK_NULL_RETURN(hostNode, false);
    RefPtr<NG::RenderContext> renderContext = hostNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    renderContext->UpdateAccessibilityFocus(false);
    return true;
}

bool AccessibilityHoverManagerForThirdNG::ActThirdAccessibilityFocus(
    int64_t elementId,
    const AccessibilityElementInfo& nodeInfo,
    const RefPtr<NG::FrameNode>& hostNode,
    const RefPtr<NG::PipelineContext>& context,
    bool isNeedClear)
{
    if (!isNeedClear && !IsTouchExplorationEnabled(context)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "third Accessibility focus or update focus but is not in touch mode");
        return true;
    }

    CHECK_NULL_RETURN(hostNode, false);
    RefPtr<NG::RenderContext> renderContext = nullptr;
    renderContext = hostNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (isNeedClear) {
        renderContext->UpdateAccessibilityFocus(false);
        TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY,
            "third act Accessibility element Id %{public}" PRId64 "Focus clear",
            nodeInfo.GetAccessibilityId());
        return true;
    }
    renderContext->UpdateAccessibilityFocus(false);
    auto rectInScreen = nodeInfo.GetRectInScreen();
    auto left = rectInScreen.GetLeftTopXScreenPostion();
    auto right = rectInScreen.GetLeftTopYScreenPostion();
    auto width = rectInScreen.GetRightBottomXScreenPostion() - rectInScreen.GetLeftTopXScreenPostion();
    auto height = rectInScreen.GetRightBottomYScreenPostion() - rectInScreen.GetLeftTopYScreenPostion();
    if ((width == 0) && (height == 0)) {
        renderContext->UpdateAccessibilityFocus(false);
        TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY,
            "third act Accessibility element Id %{public}" PRId64 "Focus clear by null rect",
            nodeInfo.GetAccessibilityId());
        return true;
    }

    NG::RectT<int32_t> rectInt { static_cast<int32_t>(left), static_cast<int32_t>(right),
        static_cast<int32_t>(width), static_cast<int32_t>(height) };
    
    renderContext->UpdateAccessibilityFocusRect(rectInt);
    renderContext->UpdateAccessibilityFocus(true, ACCESSIBILITY_FOCUS_WITHOUT_EVENT);
    TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY,
            "third act Accessibility element Id %{public}" PRId64 "Focus",
            nodeInfo.GetAccessibilityId());
    return true;
}

void AccessibilityHoverManagerForThirdNG::RegisterJsThirdProviderInteractionOperation(
    int64_t hostElementId,
    const std::shared_ptr<JsThirdProviderInteractionOperation>& jsThirdProviderOperator)
{
    jsThirdProviderOperator_[hostElementId] = jsThirdProviderOperator;
}

void AccessibilityHoverManagerForThirdNG::DeregisterJsThirdProviderInteractionOperation(
    int64_t hostElementId)
{
    jsThirdProviderOperator_.erase(hostElementId);
}

namespace {

bool GetDumpInfoArgument(const std::vector<std::string>& params, DumpInfoArgument& argument)
{
    if (params.empty()) {
        return false;
    }
    argument.isDumpSimplify = params[0].compare("-simplify") == 0;
    for (auto arg = params.begin() + 1; arg != params.end(); ++arg) {
        if (*arg == "-w") {
            argument.useWindowId = true;
        } else if (*arg == "--root") {
            ++arg;
            if (arg == params.end()) {
                DumpLog::GetInstance().Print(std::string("Error: --root is used to set the root node, ") +
                    "e.g. '--root ${AccessibilityId}'!");
                return false;
            }
            argument.rootId = StringUtils::StringToLongInt(*arg);
        } else if (*arg == "--hover-test") {
            argument.mode = DumpMode::HOVER_TEST;
            static constexpr int32_t NUM_POINT_DIMENSION = 2;
            if (std::distance(arg, params.end()) <= NUM_POINT_DIMENSION) {
                DumpLog::GetInstance().Print(std::string("Error: --hover-test is used to get nodes at a point ") +
                    "relative to the root node, e.g. '--hover-test ${x} ${y}'!");
                return false;
            }
            ++arg;
            argument.pointX = StringUtils::StringToInt(*arg);
            ++arg;
            argument.pointY = StringUtils::StringToInt(*arg);
        } else if (*arg == "-v") {
            argument.verbose = true;
        } else if (*arg == "-json") {
            argument.mode = DumpMode::TREE;
        } else {
            if (argument.mode == DumpMode::NODE) {
                argument.mode = DumpMode::HANDLE_EVENT;
                argument.action = StringUtils::StringToInt(*arg);
                break;
            } else {
                argument.mode = DumpMode::NODE;
                argument.nodeId = StringUtils::StringToLongInt(*arg);
            }
        }
    }
    return true;
}

void DumpTreeNodeInfoForThird(
    Accessibility::AccessibilityElementInfo& info, int32_t depth)
{
    DumpLog::GetInstance().AddDesc("ID: " + std::to_string(info.GetAccessibilityId()));
    DumpLog::GetInstance().AddDesc("compid: " + info.GetInspectorKey());
    DumpLog::GetInstance().AddDesc("text: " + info.GetContent());
    DumpLog::GetInstance().AddDesc(
        "accessibilityText: " + info.GetAccessibilityText());
    DumpLog::GetInstance().AddDesc("accessibilityGroup: " +
        std::to_string(info.GetAccessibilityGroup()));
    DumpLog::GetInstance().AddDesc(
        "accessibilityLevel: " + info.GetAccessibilityLevel());
    auto rectInScreen = info.GetRectInScreen();
    DumpLog::GetInstance().AddDesc("top: " + std::to_string(rectInScreen.GetLeftTopYScreenPostion()));
    DumpLog::GetInstance().AddDesc("left: " + std::to_string(rectInScreen.GetLeftTopXScreenPostion()));
    DumpLog::GetInstance().AddDesc("width: " +
        std::to_string(rectInScreen.GetRightBottomXScreenPostion() - rectInScreen.GetLeftTopXScreenPostion()));
    DumpLog::GetInstance().AddDesc("height: " +
        std::to_string(rectInScreen.GetRightBottomYScreenPostion() - rectInScreen.GetLeftTopYScreenPostion()));
    DumpLog::GetInstance().AddDesc("visible: " + std::to_string(info.IsVisible()));
    DumpLog::GetInstance().AddDesc(
        "clickable: " + std::to_string(info.IsClickable()));
    DumpLog::GetInstance().AddDesc("longclickable: " +
        std::to_string(info.IsLongClickable()));
    DumpLog::GetInstance().AddDesc(
        "checkable: " + std::to_string(info.IsCheckable()));
    DumpLog::GetInstance().AddDesc(
        "scrollable: " + std::to_string(info.IsScrollable()));
    DumpLog::GetInstance().AddDesc(
        "checked: " + std::to_string(info.IsChecked()));
    DumpLog::GetInstance().AddDesc(
        "hint: " + info.GetHint());
    DumpLog::GetInstance().Print(depth, info.GetComponentType(), info.GetChildCount());
}

void DumpTreeForThird(
    int64_t elementId,
    const std::shared_ptr<JsThirdProviderInteractionOperation>& jsThirdProviderOperator,
    int32_t depth)
{
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        elementId, splitElementId, splitTreeId);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = jsThirdProviderOperator->FindAccessibilityNodeInfosByIdFromProvider(
        splitElementId, 0, 0, infos);
    if ((!ret) || (infos.size() == 0)) {
        return;
    }
    Accessibility::AccessibilityElementInfo info = infos.front();
    DumpTreeNodeInfoForThird(info, depth);
    auto childrenIds = info.GetChildIds();
    for (auto childId = childrenIds.rbegin(); childId != childrenIds.rend(); ++childId) {
        DumpTreeForThird(*childId, jsThirdProviderOperator, depth+1);
    }
}

bool IsDumpTreeForThird(
    int64_t inputRootId,
    const std::shared_ptr<JsThirdProviderInteractionOperation>& jsThirdProviderOperator
)
{
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        inputRootId, splitElementId, splitTreeId);
    if (splitTreeId == jsThirdProviderOperator->GetBelongTreeId()) {
        return true;
    }
    return false;
}

class MockDumpOperatorCallBack : public Accessibility::AccessibilityElementOperatorCallback {
public:
    ~MockDumpOperatorCallBack() = default;

    void SetSearchElementInfoByAccessibilityIdResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const int32_t requestId)  override
    {
    }

    void SetSearchElementInfoByTextResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const int32_t requestId) override
    {
    }

    void SetSearchDefaultFocusByWindowIdResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const int32_t requestId) override
    {
    }

    void SetFindFocusedElementInfoResult(
        const Accessibility::AccessibilityElementInfo &info,
        const int32_t requestId) override
    {
    }

    void SetFocusMoveSearchResult(const Accessibility::AccessibilityElementInfo &info, const int32_t requestId) override
    {
    }

    void SetExecuteActionResult(const bool succeeded, const int32_t requestId) override
    {
        if (succeeded) {
            DumpLog::GetInstance().Print("Result: action execute succeeded");
        } else {
            DumpLog::GetInstance().Print("Result: action execute fail");
        }
    }

    void SetCursorPositionResult(const int32_t cursorPosition, const int32_t requestId) override
    {
    }
};

void DumpHandleAction(
    const std::vector<std::string>& params,
    const WeakPtr<JsAccessibilityManager>& jsAccessibilityManager,
    const std::shared_ptr<JsThirdProviderInteractionOperation>& jsThirdProviderOperator)
{
    auto jsAccessibilityManagerTemp = jsAccessibilityManager.Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManagerTemp);
    if (!jsAccessibilityManagerTemp->CheckDumpHandleEventParams(params)) {
        return;
    }

    ActionType op;
    int64_t nodeId;
    if (!jsAccessibilityManagerTemp->CheckGetActionIdAndOp(params, nodeId, op)) {
        return DumpLog::GetInstance().Print("Error: params is illegal!");
    }

    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(nodeId, splitElementId, splitTreeId);
    nodeId = splitElementId;

    std::map<std::string, std::string> paramsMap;
    jsAccessibilityManagerTemp->ProcessParameters(op, params, paramsMap);
    
    MockDumpOperatorCallBack operatorCallback;
    jsThirdProviderOperator->ExecuteAction(nodeId, op, paramsMap, 0, operatorCallback);
}
} // namespace

void AccessibilityHoverManagerForThirdNG::DumpPropertyForThird(
    int64_t elementId,
    const WeakPtr<JsAccessibilityManager>& jsAccessibilityManager,
    const std::shared_ptr<JsThirdProviderInteractionOperation>& jsThirdProviderOperator)
{
    auto jsAccessibilityManagerTemp = jsAccessibilityManager.Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManagerTemp);
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        elementId, splitElementId, splitTreeId);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = jsThirdProviderOperator->FindAccessibilityNodeInfosByIdFromProvider(
        splitElementId, 0, 0, infos);
    if ((!ret) || (infos.size() == 0)) {
        return;
    }

    Accessibility::AccessibilityElementInfo info = infos.front();
    jsAccessibilityManagerTemp->DumpCommonPropertyNG(info, splitTreeId);
    jsAccessibilityManagerTemp->DumpAccessibilityPropertyNG(info);
    DumpLog::GetInstance().Print(0, info.GetComponentType(), info.GetChildCount());
}

bool AccessibilityHoverManagerForThirdNG::OnDumpChildInfoForThirdRecursive(
    int64_t hostElementId,
    const std::vector<std::string>& params,
    std::vector<std::string>& info,
    const WeakPtr<JsAccessibilityManager>& jsAccessibilityManager)
{
    DumpInfoArgument argument;
    if (GetDumpInfoArgument(params, argument) == false) {
        return true;
    }
    auto jsThirdProviderOperator =
        GetJsThirdProviderInteractionOperation(hostElementId).lock();
    if (jsThirdProviderOperator == nullptr) {
        DumpLog::GetInstance().Print("Error: need start screenReader first");
        return true;
    }
    switch (argument.mode) {
        case DumpMode::NODE:
            DumpPropertyForThird(argument.nodeId, jsAccessibilityManager, jsThirdProviderOperator);
            break;
        case DumpMode::TREE:
            if (!IsDumpTreeForThird(argument.rootId, jsThirdProviderOperator)) {
                break;
            }
            DumpTreeForThird(argument.rootId, jsThirdProviderOperator, 0);
            break;
        case DumpMode::HANDLE_EVENT:
            DumpHandleAction(params, jsAccessibilityManager, jsThirdProviderOperator);
            break;
        case DumpMode::HOVER_TEST:
        default:
            DumpLog::GetInstance().Print("Error: invalid arguments!");
            break;
    }
    return true;
}


} // namespace OHOS::Ace::Framework
