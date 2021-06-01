/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/inspector/js_inspector_manager.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include "frameworks/bridge/common/inspector/inspect_button.h"
#include "frameworks/bridge/common/inspector/inspect_canvas.h"
#include "frameworks/bridge/common/inspector/inspect_chart.h"
#include "frameworks/bridge/common/inspector/inspect_dialog.h"
#include "frameworks/bridge/common/inspector/inspect_div.h"
#include "frameworks/bridge/common/inspector/inspect_divider.h"
#include "frameworks/bridge/common/inspector/inspect_image.h"
#include "frameworks/bridge/common/inspector/inspect_image_animator.h"
#include "frameworks/bridge/common/inspector/inspect_input.h"
#include "frameworks/bridge/common/inspector/inspect_label.h"
#include "frameworks/bridge/common/inspector/inspect_list.h"
#include "frameworks/bridge/common/inspector/inspect_list_item.h"
#include "frameworks/bridge/common/inspector/inspect_list_item_group.h"
#include "frameworks/bridge/common/inspector/inspect_marquee.h"
#include "frameworks/bridge/common/inspector/inspect_menu.h"
#include "frameworks/bridge/common/inspector/inspect_option.h"
#include "frameworks/bridge/common/inspector/inspect_picker.h"
#include "frameworks/bridge/common/inspector/inspect_picker_view.h"
#include "frameworks/bridge/common/inspector/inspect_popup.h"
#include "frameworks/bridge/common/inspector/inspect_progress.h"
#include "frameworks/bridge/common/inspector/inspect_rating.h"
#include "frameworks/bridge/common/inspector/inspect_refresh.h"
#include "frameworks/bridge/common/inspector/inspect_search.h"
#include "frameworks/bridge/common/inspector/inspect_select.h"
#include "frameworks/bridge/common/inspector/inspect_slider.h"
#include "frameworks/bridge/common/inspector/inspect_span.h"
#include "frameworks/bridge/common/inspector/inspect_stack.h"
#include "frameworks/bridge/common/inspector/inspect_swiper.h"
#include "frameworks/bridge/common/inspector/inspect_switch.h"
#include "frameworks/bridge/common/inspector/inspect_tab_bar.h"
#include "frameworks/bridge/common/inspector/inspect_tab_content.h"
#include "frameworks/bridge/common/inspector/inspect_tabs.h"
#include "frameworks/bridge/common/inspector/inspect_text.h"
#include "frameworks/bridge/common/inspector/inspect_textarea.h"
#include "frameworks/bridge/common/inspector/inspect_video.h"
#include "frameworks/bridge/common/inspector/inspector_client.h"

namespace OHOS::Ace::Framework {
namespace {

const char BORDER_BOTTOM[] = "borderBottom";
const char BORDER_LEFT[] = "borderLeft";
const char BORDER_RIGHT[] = "borderRight";
const char BORDER_TOP[] = "borderTop";
const char SCALE_DOWN[] = "scaleDown";
const char PROPERTY_ALIGN_CONTENT[] = "align-content";
const char PROPERTY_ALIGN_ITEMS[] = "align-items";
const char PROPERTY_ALLOW_SCALE[] = "allow-scale";
const char PROPERTY_BACKGROUND_COLOR[] = "background-color";
const char PROPERTY_BACKGROUND_IMAGE[] = "background-image";
const char PROPERTY_BACKGROUND_POSITION[] = "background-position";
const char PROPERTY_BACKGROUND_REPEAT[] = "background-repeat";
const char PROPERTY_BACKGROUND_SIZE[] = "background-size";
const char PROPERTY_BLOCK_COLOR[] = "block-color";
const char PROPERTY_BORDER_BOTTOM[] = "border-bottom";
const char PROPERTY_BORDER_BOTTOM_COLOR[] = "border-bottom-color";
const char PROPERTY_BORDER_BOTTOM_LEFT_RADIUS[] = "border-bottom-left-radius";
const char PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS[] = "border-bottom-right-radius";
const char PROPERTY_BORDER_BOTTOM_STYLE[] = "border-bottom-style";
const char PROPERTY_BORDER_BOTTOM_WIDTH[] = "border-bottom-width";
const char PROPERTY_BORDER_COLOR[] = "border-color";
const char PROPERTY_BORDER_LEFT[] = "border-left";
const char PROPERTY_BORDER_LEFT_COLOR[] = "border-left-color";
const char PROPERTY_BORDER_LEFT_STYLE[] = "border-left-style";
const char PROPERTY_BORDER_LEFT_WIDTH[] = "border-left-width";
const char PROPERTY_BORDER_RADIUS[] = "border-radius";
const char PROPERTY_BORDER_RIGHT[] = "border-right";
const char PROPERTY_BORDER_RIGHT_COLOR[] = "border-right-color";
const char PROPERTY_BORDER_RIGHT_STYLE[] = "border-right-style";
const char PROPERTY_BORDER_RIGHT_WIDTH[] = "border-right-width";
const char PROPERTY_BORDER_STYLE[] = "border-style";
const char PROPERTY_BORDER_TOP[] = "border-top";
const char PROPERTY_BORDER_TOP_COLOR[] = "border-top-color";
const char PROPERTY_BORDER_TOP_LEFT_RADIUS[] = "border-top-left-radius";
const char PROPERTY_BORDER_TOP_RIGHT_RADIUS[] = "border-top-right-radius";
const char PROPERTY_BORDER_TOP_STYLE[] = "border-top-style";
const char PROPERTY_BORDER_TOP_WIDTH[] = "border-top-width";
const char PROPERTY_BORDER_WIDTH[] = "border-width";
const char PROPERTY_CENTER_X[] = "center-x";
const char PROPERTY_CENTER_Y[] = "center-y";
const char PROPERTY_COLUMN_SPAN[] = "column-span";
const char PROPERTY_FADE_COLOR[] = "fade-color";
const char PROPERTY_FIT_ORIGINAL_SIZE[] = "fit-original-size";
const char PROPERTY_FLEX_BASIS[] = "flex-basis";
const char PROPERTY_FLEX_DIRECTION[] = "flex-direction";
const char PROPERTY_FLEX_GROW[] = "flex-grow";
const char PROPERTY_FLEX_SHRINK[] = "flex-shrink";
const char PROPERTY_FLEX_WRAP[] = "flex-wrap";
const char PROPERTY_FOCUS_COLOR[] = "focus-color";
const char PROPERTY_FOCUS_FONT_SIZE[] = "focus-font-size";
const char PROPERTY_FONT_FAMILY[] = "font-family";
const char PROPERTY_FONT_SIZE[] = "font-size";
const char PROPERTY_FONT_SIZE_STEP[] = "font-size-step";
const char PROPERTY_FONT_STYLE[] = "font-style";
const char PROPERTY_FONT_WEIGHT[] = "font-weight";
const char PROPERTY_GRID_COLUMN_END[] = "grid-column-end";
const char PROPERTY_GRID_COLUMN_START[] = "grid-column-start";
const char PROPERTY_GRID_COLUMNS_GAP[] = "grid-columns-gap";
const char PROPERTY_GRID_ROW_END[] = "grid-row-end";
const char PROPERTY_GRID_ROW_START[] = "grid-row-start";
const char PROPERTY_GRID_ROWS_GAP[] = "grid-rows-gap";
const char PROPERTY_GRID_TEMPLATE_COLUMNS[] = "grid-template-columns";
const char PROPERTY_GRID_TEMPLATE_ROWS[] = "grid-template-rows";
const char PROPERTY_ICON_HEIGHT[] = "icon-height";
const char PROPERTY_ICON_WIDTH[] = "icon-width";
const char PROPERTY_INDICATOR_BOTTOM[] = "indicator-bottom";
const char PROPERTY_INDICATOR_COLOR[] = "indicator-color";
const char PROPERTY_INDICATOR_LEFT[] = "indicator-left";
const char PROPERTY_INDICATOR_RIGHT[] = "indicator-right";
const char PROPERTY_INDICATOR_SELECTED_COLOR[] = "indicator-selected-color";
const char PROPERTY_INDICATOR_SIZE[] = "indicator-size";
const char PROPERTY_INDICATOR_TOP[] = "indicator-top";
const char PROPERTY_ITEM_EXTENT[] = "item-extent";
const char PROPERTY_JUSTIFY_CONTENT[] = "justify-content";
const char PROPERTY_LETTER_SPACING[] = "letter-spacing";
const char PROPERTY_LINE_CAP[] = "line-cap";
const char PROPERTY_LINE_HEIGHT[] = "line-height";
const char PROPERTY_MARGIN_BOTTOM[] = "margin-bottom";
const char PROPERTY_MARGIN_END[] = "margin-end";
const char PROPERTY_MARGIN_LEFT[] = "margin-left";
const char PROPERTY_MARGIN_RIGHT[] = "margin-right";
const char PROPERTY_MARGIN_START[] = "margin-start";
const char PROPERTY_MARGIN_TOP[] = "margin-top";
const char PROPERTY_MASK_COLOR[] = "mask-color";
const char PROPERTY_MATCH_TEXT_DIRECTION[] = "match-text-direction";
const char PROPERTY_MAX_FONT_SIZE[] = "max-font-size";
const char PROPERTY_MAX_LINES[] = "max-lines";
const char PROPERTY_MIN_FONT_SIZE[] = "min-font-size";
const char PROPERTY_OBJECT_FIT[] = "object-fit";
const char PROPERTY_PADDING_BOTTOM[] = "padding-bottom";
const char PROPERTY_PADDING_END[] = "padding-end";
const char PROPERTY_PADDING_LEFT[] = "padding-left";
const char PROPERTY_PADDING_RIGHT[] = "padding-right";
const char PROPERTY_PADDING_START[] = "padding-start";
const char PROPERTY_PADDING_TOP[] = "padding-top";
const char PROPERTY_PLACEHOLDER_COLOR[] = "placeholder-color";
const char PROPERTY_PREFER_FONT_SIZES[] = "prefer-font-sizes";
const char PROPERTY_PROGRESS_COLOR[] = "progress-color";
const char PROPERTY_RTL_FLIP[] = "rtl-flip";
const char PROPERTY_SCALE_DOWN[] = "scale-down";
const char PROPERTY_SCALE_NUMBER[] = "scale-number";
const char PROPERTY_SCALE_WIDTH[] = "scale-width";
const char PROPERTY_SECONDARY_COLOR[] = "secondary-color";
const char PROPERTY_SELECTED_COLOR[] = "selected-color";
const char PROPERTY_SELECTED_FONT_SIZE[] = "selected-font-size";
const char PROPERTY_STAR_BACKGROUND[] = "star-background";
const char PROPERTY_STAR_FOREGROUND[] = "star-foreground";
const char PROPERTY_STAR_SECONDARY[] = "star-secondary";
const char PROPERTY_STAR_ANGLE[] = "start-angle";
const char PROPERTY_STROKE_WIDTH[] = "stroke-width";
const char PROPERTY_TEXT_ALIGN[] = "text-align";
const char PROPERTY_TEXT_COLOR[] = "text-color";
const char PROPERTY_TEXT_DECORATION[] = "text-decoration";
const char PROPERTY_TEXT_OVERFLOW[] = "text-overflow";
const char PROPERTY_TEXT_PADDING[] = "text-padding";
const char PROPERTY_TEXTOFF_COLOR[] = "textoff-color";
const char PROPERTY_TEXTON_COLOR[] = "texton-color";
const char PROPERTY_TOTAL_ANGLE[] = "total-angle";
const char INSPECTOR_CURRENT_VERSION[] = "1.0";
const char INSPECTOR_DEVICE_TYPE[] = "deviceType";
const char INSPECTOR_DEFAULT_VALUE[] = "defaultValue";
const char INSPECTOR_TYPE[] = "$type";
const char INSPECTOR_ROOT[] = "root";
const char INSPECTOR_VERSION[] = "version";
const char INSPECTOR_WIDTH[] = "width";
const char INSPECTOR_HEIGHT[] = "height";
const char INSPECTOR_RESOLUTION[] = "$resolution";
const char INSPECTOR_CHILDREN[] = "$children";
const char INSPECTOR_RECT[] = "$rect";

} // namespace


template<class T>
RefPtr<InspectNode> InspectNodeCreator(NodeId nodeId, const std::string& tag)
{
    return AceType::MakeRefPtr<T>(nodeId, tag);
}

void JsInspectorManager::InitializeCallback()
{
    auto assembleJSONTreeCallback = [weak = WeakClaim(this)](std::string &jsonTreeStr) {
        auto jsInspectorManager = weak.Upgrade();
        if (!jsInspectorManager) {
            return false;
        }
        jsInspectorManager->AssembleJSONTree(jsonTreeStr);
        return true;
    };
    InspectorClient::GetInstance().RegisterJSONTreeCallback(assembleJSONTreeCallback);
    auto assembleDefaultJSONTreeCallback = [weak = WeakClaim(this)](std::string &jsonTreeStr) {
        auto jsInspectorManager = weak.Upgrade();
        if (!jsInspectorManager) {
            return false;
        }
        jsInspectorManager->AssembleDefaultJSONTree(jsonTreeStr);
        return true;
    };
    InspectorClient::GetInstance().RegisterDefaultJSONTreeCallback(assembleDefaultJSONTreeCallback);
}

// assemble the JSON tree using all depth-1 nodes and root nodes.
void JsInspectorManager::AssembleJSONTree(std::string& jsonStr)
{
    auto jsonNode = JsonUtil::Create(true);
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    GetNodeJSONStrMap();

    jsonNode->Put(INSPECTOR_TYPE, INSPECTOR_ROOT);
    auto context = GetPipelineContext().Upgrade();
    if (context) {
        float scale = context->GetViewScale();
        double rootHeight = context->GetRootHeight();
        double rootWidth = context->GetRootWidth();
        jsonNode->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
        jsonNode->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    }
    jsonNode->Put(INSPECTOR_RESOLUTION, std::to_string(SystemProperties::GetResolution()).c_str());
    auto firstDepthNodeVec = nodeJSONInfoMap_[1];
    for (auto nodeJSONInfo : firstDepthNodeVec) {
        auto nodeJSONValue = JsonUtil::ParseJsonString(nodeJSONInfo.second.c_str());
        jsonNodeArray->Put(nodeJSONValue);
    }
    jsonNode->Put(INSPECTOR_CHILDREN, jsonNodeArray);
    jsonStr = jsonNode->ToString();
}

std::string GetDeviceTypeStr(const DeviceType &deviceType)
{
    std::string deviceName = "";
    if (deviceType == DeviceType::TV) {
        deviceName = "TV";
    } else if (deviceType == DeviceType::WATCH) {
        deviceName = "Watch";
    } else if (deviceType == DeviceType::CAR) {
        deviceName = "Car";
    } else {
        deviceName = "Phone";
    }
    return deviceName;
}

// assemble the default attrs and styles for all components
void JsInspectorManager::AssembleDefaultJSONTree(std::string& jsonStr)
{
    auto jsonNode = JsonUtil::Create(true);
    std::string deviceName = GetDeviceTypeStr(SystemProperties::GetDeviceType());

    jsonNode->Put(INSPECTOR_VERSION, INSPECTOR_CURRENT_VERSION);
    jsonNode->Put(INSPECTOR_DEVICE_TYPE, deviceName.c_str());
    static const std::vector<std::string> tagNames = { DOM_NODE_TAG_BUTTON, DOM_NODE_TAG_CANVAS, DOM_NODE_TAG_CHART,
        DOM_NODE_TAG_DIALOG, DOM_NODE_TAG_DIV, DOM_NODE_TAG_DIVIDER, DOM_NODE_TAG_IMAGE, DOM_NODE_TAG_IMAGE_ANIMATOR,
        DOM_NODE_TAG_INPUT, DOM_NODE_TAG_LABEL, DOM_NODE_TAG_LIST, DOM_NODE_TAG_LIST_ITEM, DOM_NODE_TAG_LIST_ITEM_GROUP,
        DOM_NODE_TAG_MARQUEE, DOM_NODE_TAG_MENU, DOM_NODE_TAG_OPTION, DOM_NODE_TAG_PICKER_DIALOG,
        DOM_NODE_TAG_PICKER_VIEW, DOM_NODE_TAG_POPUP, DOM_NODE_TAG_PROGRESS, DOM_NODE_TAG_RATING, DOM_NODE_TAG_REFRESH,
        DOM_NODE_TAG_SEARCH, DOM_NODE_TAG_SELECT, DOM_NODE_TAG_SLIDER, DOM_NODE_TAG_SPAN, DOM_NODE_TAG_STACK,
        DOM_NODE_TAG_SWIPER, DOM_NODE_TAG_SWITCH, DOM_NODE_TAG_TAB_BAR, DOM_NODE_TAG_TAB_CONTENT, DOM_NODE_TAG_TABS,
        DOM_NODE_TAG_TEXT, DOM_NODE_TAG_TEXTAREA, DOM_NODE_TAG_VIDEO };

    static const LinearMapNode<RefPtr<InspectNode>(*)(NodeId, const std::string&)> inspectNodeCreators[] = {
        { DOM_NODE_TAG_BUTTON, &InspectNodeCreator<InspectButton> },
        { DOM_NODE_TAG_CANVAS, &InspectNodeCreator<InspectCanvas> },
        { DOM_NODE_TAG_CHART, &InspectNodeCreator<InspectChart> },
        { DOM_NODE_TAG_DIALOG, &InspectNodeCreator<InspectDialog> },
        { DOM_NODE_TAG_DIV, &InspectNodeCreator<InspectDiv> },
        { DOM_NODE_TAG_DIVIDER, &InspectNodeCreator<InspectDivider> },
        { DOM_NODE_TAG_IMAGE, &InspectNodeCreator<InspectImage> },
        { DOM_NODE_TAG_IMAGE_ANIMATOR, &InspectNodeCreator<InspectImageAnimator> },
        { DOM_NODE_TAG_INPUT, &InspectNodeCreator<InspectInput> },
        { DOM_NODE_TAG_LABEL, &InspectNodeCreator<InspectLabel> },
        { DOM_NODE_TAG_LIST, &InspectNodeCreator<InspectList> },
        { DOM_NODE_TAG_LIST_ITEM, &InspectNodeCreator<InspectListItem> },
        { DOM_NODE_TAG_LIST_ITEM_GROUP, &InspectNodeCreator<InspectListItemGroup> },
        { DOM_NODE_TAG_MARQUEE, &InspectNodeCreator<InspectMarquee> },
        { DOM_NODE_TAG_MENU, &InspectNodeCreator<InspectMenu> },
        { DOM_NODE_TAG_OPTION, &InspectNodeCreator<InspectOption> },
        { DOM_NODE_TAG_PICKER_DIALOG, &InspectNodeCreator<InspectPickerDialog> },
        { DOM_NODE_TAG_PICKER_VIEW, &InspectNodeCreator<InspectPickerView> },
        { DOM_NODE_TAG_POPUP, &InspectNodeCreator<InspectPopup> },
        { DOM_NODE_TAG_PROGRESS, &InspectNodeCreator<InspectProgress> },
        { DOM_NODE_TAG_RATING, &InspectNodeCreator<InspectRating> },
        { DOM_NODE_TAG_REFRESH, &InspectNodeCreator<InspectRefresh> },
        { DOM_NODE_TAG_SEARCH, &InspectNodeCreator<InspectSearch> },
        { DOM_NODE_TAG_SELECT, &InspectNodeCreator<InspectSelect> },
        { DOM_NODE_TAG_SLIDER, &InspectNodeCreator<InspectSlider> },
        { DOM_NODE_TAG_SPAN, &InspectNodeCreator<InspectSpan> },
        { DOM_NODE_TAG_STACK, &InspectNodeCreator<InspectStack> },
        { DOM_NODE_TAG_SWIPER, &InspectNodeCreator<InspectSwiper> },
        { DOM_NODE_TAG_SWITCH, &InspectNodeCreator<InspectSwitch> },
        { DOM_NODE_TAG_TAB_BAR, &InspectNodeCreator<InspectTabBar> },
        { DOM_NODE_TAG_TAB_CONTENT, &InspectNodeCreator<InspectTabContent> },
        { DOM_NODE_TAG_TABS, &InspectNodeCreator<InspectTabs> },
        { DOM_NODE_TAG_TEXT, &InspectNodeCreator<InspectText> },
        { DOM_NODE_TAG_TEXTAREA, &InspectNodeCreator<InspectTextArea> },
        { DOM_NODE_TAG_VIDEO, &InspectNodeCreator<InspectVideo> },
    };
    auto jsonDefaultValue = JsonUtil::Create(true);
    for (std::size_t i = 0; i < tagNames.size(); i++) {
        auto jsonDefaultAttrs = JsonUtil::Create(true);
        NodeId nodeId = -1;
        auto tag = tagNames[i];
        RefPtr<InspectNode> inspectNode;
        int64_t creatorIndex = BinarySearchFindIndex(inspectNodeCreators, ArraySize(inspectNodeCreators), tag.c_str());
        if (creatorIndex >= 0) {
            inspectNode = inspectNodeCreators[creatorIndex].value(nodeId, tag);
        } else {
            LOGW("node type %{public}s is invalid", tag.c_str());
            return;
        }
        inspectNode->InitCommonStyles();
        inspectNode->PackAttrAndStyle();
        inspectNode->SetAllAttr(jsonDefaultAttrs);
        inspectNode->SetAllStyle(jsonDefaultAttrs);
        jsonDefaultValue->Put(tag.c_str(), jsonDefaultAttrs);
    }
    jsonNode->Put(INSPECTOR_DEFAULT_VALUE, jsonDefaultValue);
    jsonStr = jsonNode->ToString();
}

void JsInspectorManager::GetNodeJSONStrMap()
{
    ClearContainer();
    DumpNodeTreeInfo(0, 0);

    if (depthNodeIdVec_.empty()) {
        LOGE("page is empty");
        return;
    }

    for (auto depthNodeId : depthNodeIdVec_) {
        depthNodeIdMap_[depthNodeId.first].push_back(depthNodeId.second);
    }

    auto maxItem =  std::max_element(depthNodeIdVec_.begin(), depthNodeIdVec_.end());
    for (int depth = maxItem->first; depth > 0; depth--) {
        auto depthNodeId = depthNodeIdMap_[depth];
        for (auto nodeId : depthNodeId) {
            auto node = GetAccessibilityNodeFromPage(nodeId);
            auto jsonNode = JsonUtil::Create(true);
            auto jsonNodeArray = JsonUtil::CreateArray(true);
            jsonNode->Put(INSPECTOR_TYPE, node->GetTag().c_str());
            jsonNode->Put(INSPECTOR_RECT, UpdateNodeRectStrInfo(node).c_str());
            for (auto attr : node->GetAttrs()) {
                jsonNode->Put(ConvertStrToPropertyType(attr.first).c_str(), attr.second.c_str());
            }
            for (auto style : node->GetStyles()) {
                jsonNode->Put(ConvertStrToPropertyType(style.first).c_str(), style.second.c_str());
            }
            if (node->GetChildList().size() > 0) {
                GetChildrenJSONArray(depth, node, jsonNodeArray);
                jsonNode->Put(INSPECTOR_CHILDREN, jsonNodeArray);
            }
            nodeJSONInfoMap_[depth].emplace_back(nodeId, jsonNode->ToString());
        }
    }
}

// clear the memory occupied by each item in map and vector.
void JsInspectorManager::ClearContainer()
{
    std::vector<std::pair<int32_t, int32_t>>().swap(depthNodeIdVec_);
    std::unordered_map<int32_t, std::vector<std::pair<int32_t, std::string>>>().swap(nodeJSONInfoMap_);
    nodeJSONInfoMap_.clear();
    std::unordered_map<int32_t, std::vector<int32_t>>().swap(depthNodeIdMap_);
    depthNodeIdMap_.clear();
}

std::string JsInspectorManager::UpdateNodeRectStrInfo(RefPtr<AccessibilityNode> node)
{
    PositionInfo positionInfo = {0, 0, 0, 0};
    if (node->GetTag() == DOM_NODE_TAG_SPAN) {
        positionInfo = {
                node->GetParentNode()->GetWidth(), node->GetParentNode()->GetHeight(),
                node->GetParentNode()->GetLeft(), node->GetParentNode()->GetTop()
        };
    } else {
        positionInfo = {node->GetWidth(), node->GetHeight(), node->GetLeft(), node->GetTop()};
    }
    if (!node->GetVisible()) {
        positionInfo = {0, 0, 0, 0};
    }
    // the dialog node is hidden, while the position and size of the node are not cleared.
    if (node->GetClearRectInfoFlag() == true) {
        positionInfo = {0, 0, 0, 0};
    }
    std::string strRec = std::to_string(positionInfo.left).append(",").
            append(std::to_string(positionInfo.top)).
            append(",").append(std::to_string(positionInfo.width)).
            append(",").append(std::to_string(positionInfo.height));
    return strRec;
}

void JsInspectorManager::DumpNodeTreeInfo(int32_t depth, NodeId nodeID)
{
    auto node = GetAccessibilityNodeFromPage(nodeID);
    if (!node) {
        LOGE("JsInspectorManager::DumpNodeTreeInfo return");
        return;
    }

    // get the vector of nodeID per depth
    depthNodeIdVec_.emplace_back(depth, nodeID);
    for (const auto& item : node->GetChildList()) {
        DumpNodeTreeInfo(depth + 1, item->GetNodeId());
    }
}

// find children of the current node and combine them with this node to form a JSON array object.
void JsInspectorManager::GetChildrenJSONArray(
    int32_t depth, RefPtr<AccessibilityNode> node, std::unique_ptr<JsonValue>& childJSONArray)
{
    auto  childNodeJSONVec = nodeJSONInfoMap_[depth + 1];
    for (auto item : node->GetChildList()) {
        auto childVec = std::find_if(std::begin(childNodeJSONVec), std::end(childNodeJSONVec),
            [item](const std::pair<int32_t, std::string>& upper) {
                return upper.first == item->GetNodeId();
            });
        if (childVec != std::end(childNodeJSONVec)) {
            auto childJSONValue = JsonUtil::ParseJsonString(childVec->second.c_str());
            childJSONArray->Put(childJSONValue);
        }
    }
}

std::string JsInspectorManager::ConvertStrToPropertyType(const std::string& typeValue)
{
    // static linear map must be sorted by key.
    static const LinearMapNode<std::string> propertyMap[] = {
        {DOM_ALIGN_CONTENT, PROPERTY_ALIGN_CONTENT},
        {DOM_ALIGN_ITEMS, PROPERTY_ALIGN_ITEMS},
        {DOM_TEXT_ALLOW_SCALE, PROPERTY_ALLOW_SCALE},
        {DOM_BACKGROUND_COLOR, PROPERTY_BACKGROUND_COLOR},
        {DOM_BACKGROUND_IMAGE, PROPERTY_BACKGROUND_IMAGE},
        {DOM_BACKGROUND_IMAGE_POSITION, PROPERTY_BACKGROUND_POSITION},
        {DOM_BACKGROUND_IMAGE_REPEAT, PROPERTY_BACKGROUND_REPEAT},
        {DOM_BACKGROUND_IMAGE_SIZE, PROPERTY_BACKGROUND_SIZE},
        {DOM_BLOCK_COLOR, PROPERTY_BLOCK_COLOR},
        {BORDER_BOTTOM, PROPERTY_BORDER_BOTTOM},
        {DOM_BORDER_BOTTOM_COLOR, PROPERTY_BORDER_BOTTOM_COLOR},
        {DOM_BORDER_BOTTOM_LEFT_RADIUS, PROPERTY_BORDER_BOTTOM_LEFT_RADIUS},
        {DOM_BORDER_BOTTOM_RIGHT_RADIUS, PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS},
        {DOM_BORDER_BOTTOM_STYLE, PROPERTY_BORDER_BOTTOM_STYLE},
        {DOM_BORDER_BOTTOM_WIDTH, PROPERTY_BORDER_BOTTOM_WIDTH},
        {DOM_BORDER_COLOR, PROPERTY_BORDER_COLOR},
        {BORDER_LEFT, PROPERTY_BORDER_LEFT},
        {DOM_BORDER_LEFT_COLOR, PROPERTY_BORDER_LEFT_COLOR},
        {DOM_BORDER_LEFT_STYLE, PROPERTY_BORDER_LEFT_STYLE},
        {DOM_BORDER_LEFT_WIDTH, PROPERTY_BORDER_LEFT_WIDTH},
        {DOM_BORDER_RADIUS, PROPERTY_BORDER_RADIUS},
        {BORDER_RIGHT, PROPERTY_BORDER_RIGHT},
        {DOM_BORDER_RIGHT_COLOR, PROPERTY_BORDER_RIGHT_COLOR},
        {DOM_BORDER_RIGHT_STYLE, PROPERTY_BORDER_RIGHT_STYLE},
        {DOM_BORDER_RIGHT_WIDTH, PROPERTY_BORDER_RIGHT_WIDTH},
        {DOM_BORDER_STYLE, PROPERTY_BORDER_STYLE},
        {BORDER_TOP, PROPERTY_BORDER_TOP},
        {DOM_BORDER_TOP_COLOR, PROPERTY_BORDER_TOP_COLOR},
        {DOM_BORDER_TOP_LEFT_RADIUS, PROPERTY_BORDER_TOP_LEFT_RADIUS},
        {DOM_BORDER_TOP_RIGHT_RADIUS, PROPERTY_BORDER_TOP_RIGHT_RADIUS},
        {DOM_BORDER_TOP_STYLE, PROPERTY_BORDER_TOP_STYLE},
        {DOM_BORDER_TOP_WIDTH, PROPERTY_BORDER_TOP_WIDTH},
        {DOM_BORDER_WIDTH, PROPERTY_BORDER_WIDTH},
        {DOM_CENTER_X, PROPERTY_CENTER_X},
        {DOM_CENTER_Y, PROPERTY_CENTER_Y},
        {DOM_LISTITEM_COLUMN_SPAN, PROPERTY_COLUMN_SPAN},
        {FADE_COLOR, PROPERTY_FADE_COLOR},
        {DOM_IMAGE_FIT_ORIGINAL_SIZE, PROPERTY_FIT_ORIGINAL_SIZE},
        {FLEX_BASIS, PROPERTY_FLEX_BASIS},
        {DOM_FLEX_DIRECTION, PROPERTY_FLEX_DIRECTION},
        {DOM_FLEX_GROW, PROPERTY_FLEX_GROW},
        {DOM_FLEX_SHRINK, PROPERTY_FLEX_SHRINK},
        {DOM_FLEX_WRAP, PROPERTY_FLEX_WRAP},
        {DOM_INPUT_FOCUS_COLOR, PROPERTY_FOCUS_COLOR},
        {DOM_PICKER_FOCUS_SIZE, PROPERTY_FOCUS_FONT_SIZE},
        {DOM_TEXT_FONT_FAMILY, PROPERTY_FONT_FAMILY},
        {DOM_TEXT_FONT_SIZE, PROPERTY_FONT_SIZE},
        {DOM_TEXT_FONT_SIZE_STEP, PROPERTY_FONT_SIZE_STEP},
        {DOM_TEXT_FONT_STYLE, PROPERTY_FONT_STYLE},
        {DOM_TEXT_FONT_WEIGHT, PROPERTY_FONT_WEIGHT},
        {DOM_GRID_COLUMN_END, PROPERTY_GRID_COLUMN_END},
        {DOM_GRID_COLUMN_START, PROPERTY_GRID_COLUMN_START},
        {DOM_GRID_COLUMN_GAP, PROPERTY_GRID_COLUMNS_GAP},
        {DOM_GRID_ROW_END, PROPERTY_GRID_ROW_END},
        {DOM_GRID_ROW_START, PROPERTY_GRID_ROW_START},
        {DOM_GRID_ROW_GAP, PROPERTY_GRID_ROWS_GAP},
        {DOM_GRID_TEMPLATE_COLUMNS, PROPERTY_GRID_TEMPLATE_COLUMNS},
        {DOM_GRID_TEMPLATE_ROWS, PROPERTY_GRID_TEMPLATE_ROWS},
        {DOM_BUTTON_ICON_HEIGHT, PROPERTY_ICON_HEIGHT},
        {DOM_BUTTON_ICON_WIDTH, PROPERTY_ICON_WIDTH},
        {DOM_INDICATOR_BOTTOM, PROPERTY_INDICATOR_BOTTOM},
        {DOM_INDICATOR_COLOR, PROPERTY_INDICATOR_COLOR},
        {DOM_INDICATOR_LEFT, PROPERTY_INDICATOR_LEFT},
        {DOM_INDICATOR_RIGHT, PROPERTY_INDICATOR_RIGHT},
        {DOM_INDICATOR_SELECTEDCOLOR, PROPERTY_INDICATOR_SELECTED_COLOR},
        {DOM_INDICATOR_SIZE, PROPERTY_INDICATOR_SIZE},
        {DOM_INDICATOR_TOP, PROPERTY_INDICATOR_TOP},
        {DOM_LIST_ITEM_EXTENT, PROPERTY_ITEM_EXTENT},
        {DOM_JUSTIFY_CONTENT, PROPERTY_JUSTIFY_CONTENT},
        {DOM_TEXT_LETTER_SPACING, PROPERTY_LETTER_SPACING},
        {DOM_DIVIDER_LINE_CAP, PROPERTY_LINE_CAP},
        {DOM_TEXT_LINE_HEIGHT, PROPERTY_LINE_HEIGHT},
        {DOM_MARGIN_BOTTOM, PROPERTY_MARGIN_BOTTOM},
        {DOM_MARGIN_END, PROPERTY_MARGIN_END},
        {DOM_MARGIN_LEFT, PROPERTY_MARGIN_LEFT},
        {DOM_MARGIN_RIGHT, PROPERTY_MARGIN_RIGHT},
        {DOM_MARGIN_START, PROPERTY_MARGIN_START},
        {DOM_MARGIN_TOP, PROPERTY_MARGIN_TOP},
        {DOM_MASK_COLOR, PROPERTY_MASK_COLOR},
        {DOM_IMAGE_MATCH_TEXT_DIRECTION, PROPERTY_MATCH_TEXT_DIRECTION},
        {DOM_TEXT_MAX_FONT_SIZE, PROPERTY_MAX_FONT_SIZE},
        {DOM_TEXT_MAX_LINES, PROPERTY_MAX_LINES},
        {DOM_TEXT_MIN_FONT_SIZE, PROPERTY_MIN_FONT_SIZE},
        {IMAGE_FIT, PROPERTY_OBJECT_FIT},
        {DOM_PADDING_BOTTOM, PROPERTY_PADDING_BOTTOM},
        {DOM_PADDING_END, PROPERTY_PADDING_END},
        {DOM_PADDING_LEFT, PROPERTY_PADDING_LEFT},
        {DOM_PADDING_RIGHT, PROPERTY_PADDING_RIGHT},
        {DOM_PADDING_START, PROPERTY_PADDING_START},
        {DOM_PADDING_TOP, PROPERTY_PADDING_TOP},
        {DOM_TEXTAREA_PLACEHOLDER_COLOR, PROPERTY_PLACEHOLDER_COLOR},
        {DOM_TEXT_PREFER_FONT_SIZES, PROPERTY_PREFER_FONT_SIZES},
        {DOM_REFRESH_PROGRESS_COLOR, PROPERTY_PROGRESS_COLOR},
        {DOM_RTL_FLIP, PROPERTY_RTL_FLIP},
        {SCALE_DOWN, PROPERTY_SCALE_DOWN},
        {DOM_SCALE_NUMBER, PROPERTY_SCALE_NUMBER},
        {DOM_SCALE_WIDTH, PROPERTY_SCALE_WIDTH},
        {DOM_PROGRESS_SECONDARY_COLOR, PROPERTY_SECONDARY_COLOR},
        {DOM_SELECTED_COLOR, PROPERTY_SELECTED_COLOR},
        {DOM_PICKER_SELECT_SIZE, PROPERTY_SELECTED_FONT_SIZE},
        {DOM_BACKGROUND_SRC, PROPERTY_STAR_BACKGROUND},
        {DOM_FOREGROUND_SRC, PROPERTY_STAR_FOREGROUND},
        {DOM_SECONDARY_SRC, PROPERTY_STAR_SECONDARY},
        {DOM_START_DEGREE, PROPERTY_STAR_ANGLE},
        {DOM_PROGRESS_STROKE_WIDTH, PROPERTY_STROKE_WIDTH},
        {DOM_TEXT_ALIGN, PROPERTY_TEXT_ALIGN},
        {DOM_PICKER_TEXT_COLOR, PROPERTY_TEXT_COLOR},
        {DOM_TEXT_DECORATION, PROPERTY_TEXT_DECORATION},
        {DOM_TEXT_OVERFLOW, PROPERTY_TEXT_OVERFLOW},
        {DOM_TEXT_PADDING, PROPERTY_TEXT_PADDING},
        {DOM_TEXT_OFF_COLOR, PROPERTY_TEXTOFF_COLOR},
        {DOM_TEXT_ON_COLOR, PROPERTY_TEXTON_COLOR},
        {DOM_SWEEP_DEGREE, PROPERTY_TOTAL_ANGLE},
    };
    std::string dstStr;
    int64_t idx = BinarySearchFindIndex(propertyMap, ArraySize(propertyMap), typeValue.c_str());
    if (idx >= 0) {
        dstStr = propertyMap[idx].value;
    } else {
        dstStr = ConvertPseudoClassStyle(typeValue);
    }
    return dstStr;
}

// pseudoClass styles, such as covert borderBottomColor:focus to border-bottom-color:focus
std::string JsInspectorManager::ConvertPseudoClassStyle(const std::string pseudoClassValue)
{
    std::string pesudoName;
    std::string remPseudoStr;
    std::string dstStr;
    if (pseudoClassValue.find(":") != std::string::npos) {
        int32_t pos = pseudoClassValue.find(":");
        remPseudoStr = pseudoClassValue.substr(0, pos);
        pesudoName = pseudoClassValue.substr(pos, pseudoClassValue.length() - pos);
        dstStr = ConvertStrToPropertyType(remPseudoStr);
        dstStr.append(pesudoName);
        return dstStr;
    }
    return pseudoClassValue;
}

} // namespace OHOS::Ace::Framework
