/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "core/accessibility/js_inspector/inspect_badge.h"
#include "core/accessibility/js_inspector/inspect_button.h"
#include "core/accessibility/js_inspector/inspect_camera.h"
#include "core/accessibility/js_inspector/inspect_canvas.h"
#include "core/accessibility/js_inspector/inspect_chart.h"
#include "core/accessibility/js_inspector/inspect_dialog.h"
#include "core/accessibility/js_inspector/inspect_div.h"
#include "core/accessibility/js_inspector/inspect_divider.h"
#include "core/accessibility/js_inspector/inspect_form.h"
#include "core/accessibility/js_inspector/inspect_grid_column.h"
#include "core/accessibility/js_inspector/inspect_grid_container.h"
#include "core/accessibility/js_inspector/inspect_grid_row.h"
#include "core/accessibility/js_inspector/inspect_image.h"
#include "core/accessibility/js_inspector/inspect_image_animator.h"
#include "core/accessibility/js_inspector/inspect_input.h"
#include "core/accessibility/js_inspector/inspect_label.h"
#include "core/accessibility/js_inspector/inspect_list.h"
#include "core/accessibility/js_inspector/inspect_list_item.h"
#include "core/accessibility/js_inspector/inspect_list_item_group.h"
#include "core/accessibility/js_inspector/inspect_marquee.h"
#include "core/accessibility/js_inspector/inspect_menu.h"
#include "core/accessibility/js_inspector/inspect_navigation_bar.h"
#include "core/accessibility/js_inspector/inspect_option.h"
#include "core/accessibility/js_inspector/inspect_panel.h"
#include "core/accessibility/js_inspector/inspect_picker.h"
#include "core/accessibility/js_inspector/inspect_picker_view.h"
#include "core/accessibility/js_inspector/inspect_piece.h"
#include "core/accessibility/js_inspector/inspect_popup.h"
#include "core/accessibility/js_inspector/inspect_progress.h"
#include "core/accessibility/js_inspector/inspect_qrcode.h"
#include "core/accessibility/js_inspector/inspect_rating.h"
#include "core/accessibility/js_inspector/inspect_refresh.h"
#include "core/accessibility/js_inspector/inspect_search.h"
#include "core/accessibility/js_inspector/inspect_select.h"
#include "core/accessibility/js_inspector/inspect_slider.h"
#include "core/accessibility/js_inspector/inspect_span.h"
#include "core/accessibility/js_inspector/inspect_stack.h"
#include "core/accessibility/js_inspector/inspect_stepper.h"
#include "core/accessibility/js_inspector/inspect_stepper_item.h"
#include "core/accessibility/js_inspector/inspect_swiper.h"
#include "core/accessibility/js_inspector/inspect_switch.h"
#include "core/accessibility/js_inspector/inspect_tab_bar.h"
#include "core/accessibility/js_inspector/inspect_tab_content.h"
#include "core/accessibility/js_inspector/inspect_tabs.h"
#include "core/accessibility/js_inspector/inspect_text.h"
#include "core/accessibility/js_inspector/inspect_textarea.h"
#include "core/accessibility/js_inspector/inspect_toggle.h"
#include "core/accessibility/js_inspector/inspect_toolbar.h"
#include "core/accessibility/js_inspector/inspect_toolbar_item.h"
#include "core/accessibility/js_inspector/inspect_video.h"
#include "core/components_v2/inspector/inspector_composed_element.h"

namespace OHOS::Ace::Framework {
namespace {

const char PAGE_CHANGE_EVENT[] = "pagechange";
const char ROOT_STACK_TAG[] = "rootstacktag";
const char ROOT_DECOR_TAG[] = "rootdecortag";
constexpr int32_t ROOT_STACK_BASE = 1100000;
constexpr int32_t ROOT_DECOR_BASE = 3100000;
constexpr int32_t CARD_NODE_ID_RATION = 10000;
constexpr int32_t CARD_ROOT_NODE_ID = 21000;
constexpr int32_t CARD_BASE = 100000;
constexpr int32_t CARD_MAX_AGP_ID = 20000;

std::atomic<int32_t> g_accessibilityId(ROOT_STACK_BASE);

const char INSPECTOR_TYPE[] = "$type";
const char INSPECTOR_ID[] = "$ID";
const char INSPECTOR_RECT[] = "$rect";
const char INSPECTOR_ATTRS[] = "$attrs";
const char INSPECTOR_STYLES[] = "$styles";

template<class T>
RefPtr<InspectNode> InspectNodeCreator(NodeId nodeId, const std::string& tag)
{
    return AceType::MakeRefPtr<T>(nodeId, tag);
}

#ifndef NG_BUILD
const LinearMapNode<RefPtr<InspectNode> (*)(NodeId, const std::string&)> inspectNodeCreators[] = {
    { DOM_NODE_TAG_BADGE, &InspectNodeCreator<InspectBadge> },
    { DOM_NODE_TAG_BUTTON, &InspectNodeCreator<InspectButton> },
    { DOM_NODE_TAG_CAMERA, &InspectNodeCreator<InspectCamera> },
    { DOM_NODE_TAG_CANVAS, &InspectNodeCreator<InspectCanvas> },
    { DOM_NODE_TAG_CHART, &InspectNodeCreator<InspectChart> },
    { DOM_NODE_TAG_DIALOG, &InspectNodeCreator<InspectDialog> },
    { DOM_NODE_TAG_DIV, &InspectNodeCreator<InspectDiv> },
    { DOM_NODE_TAG_DIVIDER, &InspectNodeCreator<InspectDivider> },
    { DOM_NODE_TAG_FORM, &InspectNodeCreator<InspectForm> },
    { DOM_NODE_TAG_GRID_COLUMN, &InspectNodeCreator<InspectGridColumn> },
    { DOM_NODE_TAG_GRID_CONTAINER, &InspectNodeCreator<InspectGridContainer> },
    { DOM_NODE_TAG_GRID_ROW, &InspectNodeCreator<InspectGridRow> },
    { DOM_NODE_TAG_IMAGE, &InspectNodeCreator<InspectImage> },
    { DOM_NODE_TAG_IMAGE_ANIMATOR, &InspectNodeCreator<InspectImageAnimator> },
    { DOM_NODE_TAG_INPUT, &InspectNodeCreator<InspectInput> },
    { DOM_NODE_TAG_LABEL, &InspectNodeCreator<InspectLabel> },
    { DOM_NODE_TAG_LIST, &InspectNodeCreator<InspectList> },
    { DOM_NODE_TAG_LIST_ITEM, &InspectNodeCreator<InspectListItem> },
    { DOM_NODE_TAG_LIST_ITEM_GROUP, &InspectNodeCreator<InspectListItemGroup> },
    { DOM_NODE_TAG_MARQUEE, &InspectNodeCreator<InspectMarquee> },
    { DOM_NODE_TAG_MENU, &InspectNodeCreator<InspectMenu> },
    { DOM_NODE_TAG_NAVIGATION_BAR, &InspectNodeCreator<InspectNavigationBar> },
    { DOM_NODE_TAG_OPTION, &InspectNodeCreator<InspectOption> },
    { DOM_NODE_TAG_PANEL, &InspectNodeCreator<InspectPanel> },
    { DOM_NODE_TAG_PICKER_DIALOG, &InspectNodeCreator<InspectPicker> },
    { DOM_NODE_TAG_PICKER_VIEW, &InspectNodeCreator<InspectPickerView> },
    { DOM_NODE_TAG_PIECE, &InspectNodeCreator<InspectPiece> },
    { DOM_NODE_TAG_POPUP, &InspectNodeCreator<InspectPopup> },
    { DOM_NODE_TAG_PROGRESS, &InspectNodeCreator<InspectProgress> },
    { DOM_NODE_TAG_QRCODE, &InspectNodeCreator<InspectQRcode> },
    { DOM_NODE_TAG_RATING, &InspectNodeCreator<InspectRating> },
    { DOM_NODE_TAG_REFRESH, &InspectNodeCreator<InspectRefresh> },
    { DOM_NODE_TAG_SEARCH, &InspectNodeCreator<InspectSearch> },
    { DOM_NODE_TAG_SELECT, &InspectNodeCreator<InspectSelect> },
    { DOM_NODE_TAG_SLIDER, &InspectNodeCreator<InspectSlider> },
    { DOM_NODE_TAG_SPAN, &InspectNodeCreator<InspectSpan> },
    { DOM_NODE_TAG_STACK, &InspectNodeCreator<InspectStack> },
    { DOM_NODE_TAG_STEPPER, &InspectNodeCreator<InspectStepper> },
    { DOM_NODE_TAG_STEPPER_ITEM, &InspectNodeCreator<InspectStepperItem> },
    { DOM_NODE_TAG_SWIPER, &InspectNodeCreator<InspectSwiper> },
    { DOM_NODE_TAG_SWITCH, &InspectNodeCreator<InspectSwitch> },
    { DOM_NODE_TAG_TAB_BAR, &InspectNodeCreator<InspectTabBar> },
    { DOM_NODE_TAG_TAB_CONTENT, &InspectNodeCreator<InspectTabContent> },
    { DOM_NODE_TAG_TABS, &InspectNodeCreator<InspectTabs> },
    { DOM_NODE_TAG_TEXT, &InspectNodeCreator<InspectText> },
    { DOM_NODE_TAG_TEXTAREA, &InspectNodeCreator<InspectTextArea> },
    { DOM_NODE_TAG_TOGGLE, &InspectNodeCreator<InspectToggle> },
    { DOM_NODE_TAG_TOOL_BAR, &InspectNodeCreator<InspectToolbar> },
    { DOM_NODE_TAG_TOOL_BAR_ITEM, &InspectNodeCreator<InspectToolbarItem> },
    { DOM_NODE_TAG_VIDEO, &InspectNodeCreator<InspectVideo> },
};
#endif

std::string ConvertStrToPropertyType(const std::string& typeValue)
{
    std::string dstStr;
    std::regex regex("([A-Z])");
    dstStr = regex_replace(typeValue, regex, "-$1");
    std::transform(dstStr.begin(), dstStr.end(), dstStr.begin(), ::tolower);
    return dstStr;
}

inline int32_t GetRootNodeIdFromPage(const RefPtr<JsAcePage>& page)
{
#ifndef NG_BUILD
    auto domDocument = page ? page->GetDomDocument() : nullptr;
    if (domDocument) {
        return domDocument->GetRootNodeId();
    }
#endif
    return -1;
}

int32_t ConvertToNodeId(int32_t cardAccessibilityId)
{
    // cardAccessibilityId is integer total ten digits, top five for agp virtualViewId, end five for ace nodeId,
    // for example 00032 10001 convert to result is 1000001
    int result = 0;
    int32_t nodeId = cardAccessibilityId % CARD_BASE;
    if (nodeId >= CARD_ROOT_NODE_ID) {
        return 0;
    }
    result =
        (static_cast<int32_t>(nodeId / CARD_NODE_ID_RATION)) * DOM_ROOT_NODE_ID_BASE + nodeId % CARD_NODE_ID_RATION;
    return result;
}

} // namespace

const size_t AccessibilityNodeManager::EVENT_DUMP_PARAM_LENGTH_UPPER = 5;
const size_t AccessibilityNodeManager::EVENT_DUMP_PARAM_LENGTH_LOWER = 3;
const size_t AccessibilityNodeManager::PROPERTY_DUMP_PARAM_LENGTH = 2;
const size_t AccessibilityNodeManager::EVENT_DUMP_ORDER_INDEX = 0;
const size_t AccessibilityNodeManager::EVENT_DUMP_ID_INDEX = 1;
const size_t AccessibilityNodeManager::EVENT_DUMP_ACTION_INDEX = 2;
const size_t AccessibilityNodeManager::EVENT_DUMP_ACTION_PARAM_INDEX = 3;

AccessibilityNodeManager::~AccessibilityNodeManager()
{
    auto rootNode = GetAccessibilityNodeById(rootNodeId_ + ROOT_STACK_BASE);
    if (rootNode) {
        RemoveAccessibilityNodes(rootNode);
    }
}

void AccessibilityNodeManager::InitializeCallback() {}

void AccessibilityNodeManager::RegisterSubWindowInteractionOperation(int windowId) {}

void AccessibilityNodeManager::SetPipelineContext(const RefPtr<PipelineBase>& context)
{
    context_ = context;
}

void AccessibilityNodeManager::AddSubPipelineContext(const RefPtr<PipelineBase>& context)
{
    subContexts_.emplace_back(WeakPtr<PipelineBase>(context));
}

void AccessibilityNodeManager::SetRunningPage(const RefPtr<JsAcePage>& page)
{
    indexPage_ = page;
    // send page change event to barrier free when page change.
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.eventType = PAGE_CHANGE_EVENT;
    SendAccessibilityAsyncEvent(accessibilityEvent);
#ifndef NG_BUILD
    if (GetVersion() == AccessibilityVersion::JS_DECLARATIVE_VERSION) {
        auto domDocument = page ? page->GetDomDocument() : nullptr;
        if (domDocument) {
            SetRootNodeId(domDocument->GetRootNodeId());
        }
    }
#endif
}

std::string AccessibilityNodeManager::GetNodeChildIds(const RefPtr<AccessibilityNode>& node)
{
    std::string ids;
    if (node) {
        const auto& children = node->GetChildList();
        if ((node->GetNodeId() == rootNodeId_ + ROOT_STACK_BASE) && !children.empty()) {
            ids.append(std::to_string(children.back()->GetNodeId()));
        } else {
            for (const auto& child : children) {
                if (!ids.empty()) {
                    ids.append(",");
                }
                ids.append(std::to_string(child->GetNodeId()));
            }
        }
    }
    return ids;
}

void AccessibilityNodeManager::AddNodeWithId(const std::string& key, const RefPtr<AccessibilityNode>& node)
{
    if (!node) {
        return;
    }
    nodeWithIdMap_[key] = node;
}

void AccessibilityNodeManager::AddNodeWithTarget(const std::string& key, const RefPtr<AccessibilityNode>& node)
{
    if (!node) {
        return;
    }
    nodeWithTargetMap_[key] = node;
}

void AccessibilityNodeManager::AddComposedElement(const std::string& key, const RefPtr<ComposedElement>& node)
{
    if (!node) {
        return;
    }
    composedElementIdMap_[key] = node;
}

void AccessibilityNodeManager::RemoveComposedElementById(const std::string& key)
{
    auto it = composedElementIdMap_.find(key);
    if (it != composedElementIdMap_.end()) {
        composedElementIdMap_.erase(it);
    }
}

WeakPtr<ComposedElement> AccessibilityNodeManager::GetComposedElementFromPage(NodeId nodeId)
{
    if (isOhosHostCard_) {
        nodeId = ConvertToNodeId(nodeId);
    }
    auto indexPage = indexPage_.Upgrade();
    if (nodeId == 0 && indexPage) {
        auto rootNode = GetRootNodeIdFromPage(indexPage);
        if (rootNode < 0) {
            return nullptr;
        }
        nodeId = rootNode + ROOT_STACK_BASE;
    }

    const auto itNode = composedElementIdMap_.find(std::to_string(nodeId));
    if (itNode == composedElementIdMap_.end()) {
        return nullptr;
    }
    return itNode->second;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::GetAccessibilityNodeFromPage(NodeId nodeId) const
{
    if (isOhosHostCard_) {
        nodeId = ConvertToNodeId(nodeId);
    }
    auto indexPage = indexPage_.Upgrade();
    if (nodeId == 0 && indexPage) {
        auto rootNode = GetRootNodeIdFromPage(indexPage);
        if (rootNode < 0) {
            return nullptr;
        }
        nodeId = rootNode + ROOT_STACK_BASE;
    }

    return GetAccessibilityNodeById(nodeId);
}

std::string AccessibilityNodeManager::GetInspectorNodeById(NodeId nodeId) const
{
    auto node = GetAccessibilityNodeFromPage(nodeId);
    if (!node) {
        return "";
    }
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, node->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, node->GetNodeId());
    jsonNode->Put(INSPECTOR_RECT, node->GetRect().ToBounds().c_str());
    auto result = GetDefaultAttrsByType(node->GetTag(), jsonNode);
    if (!result) {
        return jsonNode->ToString();
    }
    auto attrJsonNode = jsonNode->GetObject(INSPECTOR_ATTRS);
    for (const auto& attr : node->GetAttrs()) {
        if (attrJsonNode->Contains(attr.first)) {
            attrJsonNode->Replace(attr.first.c_str(), attr.second.c_str());
        } else {
            attrJsonNode->Put(attr.first.c_str(), attr.second.c_str());
        }
    }
    auto styleJsonNode = jsonNode->GetObject(INSPECTOR_STYLES);
    for (const auto& style : node->GetStyles()) {
        auto styleType = ConvertStrToPropertyType(style.first);
        if (styleJsonNode->Contains(styleType)) {
            styleJsonNode->Replace(styleType.c_str(), style.second.c_str());
        } else {
            styleJsonNode->Put(styleType.c_str(), style.second.c_str());
        }
    }
    return jsonNode->ToString();
}

void AccessibilityNodeManager::ClearNodeRectInfo(RefPtr<AccessibilityNode>& node, bool isPopDialog)
{
    if (!node) {
        return;
    }
    auto children = node->GetChildList();
    for (auto it = children.begin(); it != children.end(); it++) {
        ClearNodeRectInfo(*it, isPopDialog);
    }
#if defined(PREVIEW)
    if (isPopDialog) {
        node->SetClearRectInfoFlag(true);
    } else {
        node->SetClearRectInfoFlag(false);
    }
#endif
}

void AccessibilityNodeManager::SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent) {}

int64_t AccessibilityNodeManager::GenerateNextAccessibilityId()
{
    return g_accessibilityId.fetch_add(1, std::memory_order_relaxed);
}

// combined components which pop up through js api, such as dialog/toast
RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateSpecializedNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId)
{
#if defined(PREVIEW)
    return nullptr;
#endif
    if (nodeId < ROOT_STACK_BASE) {
        return nullptr;
    }
    return CreateAccessibilityNode(tag, nodeId, parentNodeId, -1);
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    if (IsDeclarative()) {
        return CreateDeclarativeAccessibilityNode(tag, nodeId, parentNodeId, itemIndex);
    } else {
        return CreateCommonAccessibilityNode(tag, nodeId, parentNodeId, itemIndex);
    }
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateDeclarativeAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    RefPtr<AccessibilityNode> parentNode;
    if (parentNodeId != -1) {
        parentNode = GetAccessibilityNodeById(parentNodeId);
    } else {
        parentNode = GetRootAccessibilityNode();
    }
    auto accessibilityNode = GetAccessibilityNodeById(nodeId);
    if (!accessibilityNode) {
        accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto result = accessibilityNodes_.try_emplace(nodeId, accessibilityNode);
            if (!result.second) {
                return nullptr;
            }
        }
    }
    accessibilityNode->SetTag(tag);
    accessibilityNode->SetIsRootNode(nodeId == rootNodeId_);
    accessibilityNode->SetPageId(rootNodeId_ - DOM_ROOT_NODE_ID_BASE);
    accessibilityNode->SetFocusableState(true);
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            accessibilityNode->SetWindowId(context->GetWindowId());
        }
    }
    if (parentNode) {
        accessibilityNode->SetParentNode(parentNode);
        accessibilityNode->Mount(itemIndex);
    }
    return accessibilityNode;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateCommonAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    RefPtr<AccessibilityNode> parentNode;
    if (parentNodeId != -1) {
        parentNode = GetAccessibilityNodeById(parentNodeId);
        if (!parentNode) {
            EventReport::SendAccessibilityException(AccessibilityExcepType::CREATE_ACCESSIBILITY_NODE_ERR);
            return nullptr;
        }
    } else {
        parentNode = GetRootAccessibilityNode();
    }

    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            accessibilityNode->SetWindowId(context->GetWindowId());
        }
    }
    accessibilityNode->SetIsRootNode(nodeId == rootNodeId_);
    accessibilityNode->SetPageId(rootNodeId_ - DOM_ROOT_NODE_ID_BASE);
    accessibilityNode->SetParentNode(parentNode);
    accessibilityNode->Mount(itemIndex);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto result = accessibilityNodes_.try_emplace(nodeId, accessibilityNode);
        if (!result.second) {
            return nullptr;
        }
    }
    return accessibilityNode;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::GetRootAccessibilityNode()
{
    // create accessibility root stack node
    auto rootStackId = rootNodeId_ + (!IsDecor() ? ROOT_STACK_BASE : ROOT_DECOR_BASE);
    RefPtr<AccessibilityNode> parentNode = GetAccessibilityNodeById(rootStackId);
    if (!parentNode) {
        parentNode = AceType::MakeRefPtr<AccessibilityNode>(rootStackId, !IsDecor() ? ROOT_STACK_TAG : ROOT_DECOR_TAG);
        if (parentNode && !IsDecor()) {
            parentNode->SetPageId(rootNodeId_ - DOM_ROOT_NODE_ID_BASE);
        }
        std::lock_guard<std::mutex> lock(mutex_);
        accessibilityNodes_.try_emplace(rootStackId, parentNode);
    }
    if (!IsDecor()) {
        auto decor = GetAccessibilityNodeById(ROOT_DECOR_BASE - 1);
        if (decor) {
            decor->SetParentNode(parentNode);
            decor->Mount(-1);
        }
    }
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            parentNode->SetWindowId(context->GetWindowId());
        }
    }
    return parentNode;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::GetAccessibilityNodeById(NodeId nodeId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    const auto itNode = accessibilityNodes_.find(nodeId);
    if (itNode == accessibilityNodes_.end()) {
        return nullptr;
    }
    return itNode->second;
}

void AccessibilityNodeManager::RemoveAccessibilityNodes(RefPtr<AccessibilityNode>& node)
{
    if (!node) {
        return;
    }
    auto children = node->GetChildList();
    for (auto it = children.begin(); it != children.end();) {
        RemoveAccessibilityNodes(*it++);
    }
    auto parentId = node->GetParentId();
    RefPtr<AccessibilityNode> parentNode;
    if (parentId != -1) {
        parentNode = GetAccessibilityNodeById(parentId);
        if (parentNode) {
            parentNode->RemoveNode(node);
        }
    }
    std::lock_guard<std::mutex> lock(mutex_);
    accessibilityNodes_.erase(node->GetNodeId());
    RemoveVisibleChangeNode(node->GetNodeId());
}

void AccessibilityNodeManager::RemoveAccessibilityNodeById(NodeId nodeId)
{
    auto accessibilityNode = GetAccessibilityNodeById(nodeId);
    if (!accessibilityNode) {
        return;
    }
    RemoveAccessibilityNodes(accessibilityNode);
}

void AccessibilityNodeManager::ClearPageAccessibilityNodes(int32_t pageId)
{
    auto rootNodeId = pageId + ROOT_STACK_BASE;
    auto accessibilityNode = GetAccessibilityNodeById(rootNodeId);
    if (!accessibilityNode) {
        return;
    }
    RemoveAccessibilityNodes(accessibilityNode);
}

void AccessibilityNodeManager::TriggerVisibleChangeEvent()
{
    if (visibleChangeNodes_.empty()) {
        return;
    }
    for (auto& visibleChangeNode : visibleChangeNodes_) {
        auto visibleNodeId = visibleChangeNode.first;
        auto accessibilityNode = GetAccessibilityNodeById(visibleNodeId);
        if (!accessibilityNode) {
            continue;
        }
        // IntersectionObserver observes size exclude margin.
        auto marginSize = accessibilityNode->GetMarginSize();
        auto visibleRect = accessibilityNode->GetRect() - marginSize;
        auto globalRect = accessibilityNode->GetGlobalRect() - marginSize;
        auto pipeline = context_.Upgrade();
        if (pipeline) {
            pipeline->GetBoundingRectData(visibleNodeId, globalRect);
            globalRect = globalRect * pipeline->GetViewScale() - marginSize;
        }
        auto& nodeCallbackInfoList = visibleChangeNode.second;
        for (auto& nodeCallbackInfo : nodeCallbackInfoList) {
            if (!globalRect.IsValid() || !accessibilityNode->GetVisible()) {
                if (nodeCallbackInfo.currentVisibleType) {
                    nodeCallbackInfo.currentVisibleType = false;
                    if (nodeCallbackInfo.callback) {
                        nodeCallbackInfo.callback(false, 0.0);
                    }
                }
                continue;
            }
            auto visibleRatio = visibleRect.Width() * visibleRect.Height() / (globalRect.Width() * globalRect.Height());
            visibleRatio = std::clamp(visibleRatio, 0.0, 1.0);
            if (GreatNotEqual(visibleRatio, nodeCallbackInfo.visibleRatio) && !nodeCallbackInfo.currentVisibleType) {
                nodeCallbackInfo.currentVisibleType = true;
                if (nodeCallbackInfo.callback) {
                    nodeCallbackInfo.callback(true, visibleRatio);
                }
            }
            if (LessOrEqual(visibleRatio, nodeCallbackInfo.visibleRatio) && nodeCallbackInfo.currentVisibleType) {
                nodeCallbackInfo.currentVisibleType = false;
                if (nodeCallbackInfo.callback) {
                    nodeCallbackInfo.callback(false, visibleRatio);
                }
            }
        }
    }
}

void AccessibilityNodeManager::AddVisibleChangeNode(NodeId nodeId, double ratio, VisibleRatioCallback callback)
{
    VisibleCallbackInfo info;
    info.callback = callback;
    info.visibleRatio = ratio;
    info.currentVisibleType = false;
    auto iter = visibleChangeNodes_.find(nodeId);
    if (iter != visibleChangeNodes_.end()) {
        auto& callbackList = visibleChangeNodes_[nodeId];
        callbackList.emplace_back(info);
    } else {
        std::list<VisibleCallbackInfo> callbackList;
        callbackList.emplace_back(info);
        visibleChangeNodes_[nodeId] = callbackList;
    }
}

void AccessibilityNodeManager::RemoveVisibleChangeNode(NodeId nodeId)
{
    auto key = visibleChangeNodes_.find(nodeId);
    if (key != visibleChangeNodes_.end()) {
        visibleChangeNodes_.erase(key);
    }
}

void AccessibilityNodeManager::TrySaveTargetAndIdNode(
    const std::string& id, const std::string& target, const RefPtr<AccessibilityNode>& node)
{
    if (!id.empty()) {
        AddNodeWithId(id, node);
    }

    if (!target.empty()) {
        AddNodeWithTarget(target, node);
    }
}

void AccessibilityNodeManager::OnDumpInfo(const std::vector<std::string>& params)
{
    if (params.size() == 1) {
        DumpTree(0, 0);
    } else if (params.size() == PROPERTY_DUMP_PARAM_LENGTH) {
        DumpProperty(params);
    } else if (params.size() >= EVENT_DUMP_PARAM_LENGTH_LOWER) {
        DumpHandleEvent(params);
    }
}

void AccessibilityNodeManager::DumpHandleEvent(const std::vector<std::string>& params) {}

void AccessibilityNodeManager::DumpProperty(const std::vector<std::string>& params) {}

std::unique_ptr<JsonValue> AccessibilityNodeManager::DumpComposedElementsToJson() const
{
    auto json = JsonUtil::Create(true);
    auto infos = JsonUtil::CreateArray(true);
    for (auto& [id, element] : composedElementIdMap_) {
        auto inspector = element.Upgrade();
        if (inspector) {
            auto info = JsonUtil::Create(true);
            info->Put("id", id.c_str());
            info->Put("type", TypeInfoHelper::TypeName(*inspector));
            infos->Put(info);
        }
    }
    json->Put("inspectors", infos);
    return json;
}

std::unique_ptr<JsonValue> AccessibilityNodeManager::DumpComposedElementToJson(NodeId nodeId)
{
    auto composedElement = GetComposedElementFromPage(nodeId);
    auto inspector = AceType::DynamicCast<V2::InspectorComposedElement>(composedElement.Upgrade());
    if (!inspector) {
        return nullptr;
    }
    return inspector->ToJsonObject();
}

void AccessibilityNodeManager::SetCardViewParams(const std::string& key, bool focus) {}

void AccessibilityNodeManager::SetCardViewPosition(int id, float offsetX, float offsetY)
{
    cardOffset_ = Offset(offsetX, offsetY);
    if (id < 0 || id > CARD_MAX_AGP_ID) {
        cardId_ = 0;
    } else {
        cardId_ = id;
    }
    isOhosHostCard_ = true;
}

void AccessibilityNodeManager::UpdateEventTarget(NodeId id, BaseEventInfo& info)
{
#ifndef NG_BUILD
    auto composedElement = GetComposedElementFromPage(id);
    auto inspector = AceType::DynamicCast<V2::InspectorComposedElement>(composedElement.Upgrade());
    if (!inspector) {
        return;
    }
    auto rectInLocal = inspector->GetRenderRectInLocal();
    auto rectInGlobal = inspector->GetRenderRect();
    auto marginLeft = inspector->GetMargin(AnimatableType::PROPERTY_MARGIN_LEFT).ConvertToPx();
    auto marginRight = inspector->GetMargin(AnimatableType::PROPERTY_MARGIN_RIGHT).ConvertToPx();
    auto marginTop = inspector->GetMargin(AnimatableType::PROPERTY_MARGIN_TOP).ConvertToPx();
    auto marginBottom = inspector->GetMargin(AnimatableType::PROPERTY_MARGIN_BOTTOM).ConvertToPx();
    auto& target = info.GetTargetWithModify();
    auto LocalOffset = rectInLocal.GetOffset();
    target.area.SetOffset(DimensionOffset(Offset(LocalOffset.GetX() + marginLeft, LocalOffset.GetY() + marginTop)));
    auto globalOffset = rectInGlobal.GetOffset();
    target.origin =
        DimensionOffset(Offset(globalOffset.GetX() - LocalOffset.GetX(), globalOffset.GetY() - LocalOffset.GetY()));
    target.area.SetWidth(Dimension(rectInLocal.Width() - marginLeft - marginRight));
    target.area.SetHeight(Dimension(rectInLocal.Height() - marginTop - marginBottom));
#endif
}

void AccessibilityNodeManager::SetWindowPos(int32_t left, int32_t top, int32_t windowId)
{
    WindowPos windowPos;
    windowPos.left = left;
    windowPos.top = top;
    windowPosMap_.insert_or_assign(windowId, windowPos);
}

bool AccessibilityNodeManager::IsDeclarative()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }

    return context->GetIsDeclarative();
}

bool AccessibilityNodeManager::GetDefaultAttrsByType(
    const std::string& type, std::unique_ptr<JsonValue>& jsonDefaultAttrs)
{
#ifdef NG_BUILD
    return false;
#else
    NodeId nodeId = -1;
    RefPtr<InspectNode> inspectNode;
    int64_t creatorIndex = BinarySearchFindIndex(inspectNodeCreators, ArraySize(inspectNodeCreators), type.c_str());
    if (creatorIndex >= 0) {
        inspectNode = inspectNodeCreators[creatorIndex].value(nodeId, type);
    } else {
        return false;
    }
    inspectNode->InitCommonStyles();
    inspectNode->PackAttrAndStyle();
    inspectNode->SetAllAttr(jsonDefaultAttrs, INSPECTOR_ATTRS);
    inspectNode->SetAllStyle(jsonDefaultAttrs, INSPECTOR_STYLES);
    return true;
#endif
}

void AccessibilityNodeManager::DumpTree(int32_t depth, int64_t nodeID, bool isDumpSimplify)
{
    if (!DumpLog::GetInstance().GetDumpFile()) {
        return;
    }

    auto node = GetAccessibilityNodeFromPage(nodeID);
    if (!node) {
        DumpLog::GetInstance().Print("Error: failed to get accessibility node with ID " + std::to_string(nodeID));
        return;
    }

    DumpLog::GetInstance().AddDesc("ID: " + std::to_string(node->GetNodeId()));
    if (!isDumpSimplify) {
        DumpLog::GetInstance().AddDesc("compid: " + node->GetJsComponentId());
        DumpLog::GetInstance().AddDesc("text: " + node->GetText());
        DumpLog::GetInstance().AddDesc("visible: " + std::to_string(node->GetShown() && node->GetVisible()));
        DumpLog::GetInstance().AddDesc("clickable: " + std::to_string(node->GetClickableState()));
        DumpLog::GetInstance().AddDesc("checkable: " + std::to_string(node->GetCheckableState()));
    }
    auto top = node->GetTop() + GetWindowTop(node->GetWindowId());
    auto left = node->GetLeft() + GetWindowLeft(node->GetWindowId());
    if (!isDumpSimplify || (!NearZero(top, 0.0) && !NearZero(left, 0.0))) {
        DumpLog::GetInstance().AddDesc("top: " + std::to_string(top));
        DumpLog::GetInstance().AddDesc("left: " + std::to_string(left));
    }
    if (node->GetTag() == "SideBarContainer") {
        Rect sideBarRect = node->GetRect();
        for (const auto& childNode : node->GetChildList()) {
            sideBarRect = sideBarRect.CombineRect(childNode->GetRect());
        }
        DumpLog::GetInstance().AddDesc("width: " + std::to_string(sideBarRect.Width()));
        DumpLog::GetInstance().AddDesc("height: " + std::to_string(sideBarRect.Height()));
    } else {
        DumpLog::GetInstance().AddDesc("width: " + std::to_string(node->GetWidth()));
        DumpLog::GetInstance().AddDesc("height: " + std::to_string(node->GetHeight()));
    }
    DumpLog::GetInstance().Print(depth, node->GetTag(), node->GetChildList().size());
    for (const auto& item : node->GetChildList()) {
        AccessibilityNodeManager::DumpTree(depth + 1, item->GetNodeId(), isDumpSimplify);
    }
}

} // namespace OHOS::Ace::Framework
