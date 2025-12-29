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

#include "core/components_ng/pattern/web/web_dom_document.h"

#include "base/log/dump_log.h"

namespace {
constexpr char WEB_JSON_ID[] = "$ID";
constexpr char WEB_JSON_TYPE[] = "$type";
constexpr char WEB_JSON_TYPE_OUTER[] = "type";
constexpr char WEB_JSON_ATTRS[] = "$attrs";
constexpr char WEB_JSON_RECT[] = "$rect";
constexpr char WEB_JSON_CHILDREN[] = "$children";
constexpr char WEB_JSON_URL[] = "url";
constexpr char WEB_JSON_TITLE[] = "title";
constexpr char WEB_JSON_CHILD[] = "$child";

constexpr char WEB_ATTR_X[] = "x";
constexpr char WEB_ATTR_Y[] = "y";
constexpr char WEB_ATTR_WIDTH[] = "width";
constexpr char WEB_ATTR_HEIGHT[] = "height";
constexpr char WEB_ATTR_IS_SCROLLABLE[] = "isScrollable";
constexpr char WEB_ATTR_SCROLL_LEFT[] = "scrollLeft";
constexpr char WEB_ATTR_SCROLL_TOP[] = "scrollTop";
constexpr char WEB_ATTR_SCROLL_WIDTH[] = "scrollWidth";
constexpr char WEB_ATTR_SCROLL_HEIGHT[] = "scrollHeight";
constexpr char WEB_ATTR_XPATH[] = "xpath";
constexpr char WEB_ATTR_SRC[] = "src";

constexpr char WEB_ERROR_STRING[] = "";
constexpr int32_t WEB_ERROR_INT = -1;
constexpr double WEB_ERROR_DOUBLE = 0.0;

constexpr int32_t WEB_MAX_DOM_DEPTH = 5000;
}

namespace OHOS::Ace::NG {

WebDomNode::WebDomNode(int32_t id, const std::string& tagName)
    : id_(id), tagName_(tagName) {}

void WebDomNode::SetAttributes(std::unique_ptr<JsonValue> attributes)
{
    attributes_ = std::move(attributes);
}

std::unique_ptr<JsonValue> ActiveNode::ToJson(const WebDomDocument& document) const
{
    auto nodeJson = JsonUtil::Create(true);
    nodeJson->Put(WEB_JSON_ID, id);
    nodeJson->Put(WEB_JSON_TYPE, tagName.c_str());
    nodeJson->Put(WEB_JSON_TYPE_OUTER, type.c_str());

    auto absoluteRect = rect + document.GetOffset();
    nodeJson->Put(WEB_JSON_RECT, absoluteRect.ToBounds().c_str());

    if (attributes && attributes->IsValid()) {
        nodeJson->Put(WEB_JSON_ATTRS, attributes);
    } else {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebDomNode has no attributes");
    }

    std::unique_ptr<JsonValue> outputChildren = JsonUtil::CreateArray(true);
    for (auto& child : children) {
        outputChildren->Put(child.ToJson(document));
    }

    nodeJson->PutRef(WEB_JSON_CHILDREN, std::move(outputChildren));
    return nodeJson;
}

WebDomDocument::WebDomDocument()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::WebDomDocument");
}

std::shared_ptr<WebDomNode> WebDomDocument::CreateNode(std::unique_ptr<JsonValue>& json)
{
    int32_t id = json->GetInt(WEB_JSON_ID, WEB_ERROR_INT);
    std::string tagName = json->GetString(WEB_JSON_TYPE, WEB_ERROR_STRING);

    auto node = std::make_shared<WebDomNode>(id, tagName);
    idToNodeMap_[id] = node;

    auto x = json->GetDouble(WEB_ATTR_X, WEB_ERROR_DOUBLE);
    auto y = json->GetDouble(WEB_ATTR_Y, WEB_ERROR_DOUBLE);
    auto width = json->GetDouble(WEB_ATTR_WIDTH, WEB_ERROR_DOUBLE);
    auto height = json->GetDouble(WEB_ATTR_HEIGHT, WEB_ERROR_DOUBLE);
    node->rect_ = RectF(x, y, width, height);

    if (json->Contains(WEB_JSON_ATTRS) && json->GetValue(WEB_JSON_ATTRS)->IsObject()) {
        auto current = json->GetValue(WEB_JSON_ATTRS);
        node->SetAttributes(std::move(current));
    }

    if (json->Contains(WEB_JSON_CHILDREN) && json->GetValue(WEB_JSON_CHILDREN)->IsArray()) {
        auto children = json->GetValue(WEB_JSON_CHILDREN);
        for (int32_t i = 0; i < children->GetArraySize(); ++i) {
            auto item = children->GetArrayItem(i);
            auto child = CreateNode(item);
            child->parent_ = node;
            node->children_.push_back(child);
        }
    }
    return node;
}

ActiveNode WebDomDocument::BuildActiveNode(const std::shared_ptr<WebDomNode>& domNode,
    int32_t parentId) const
{
    ActiveNode node;
    node.id = domNode->id_;
    node.tagName = domNode->tagName_;
    node.type = domNode->type_;
    node.rect = domNode->rect_;

    node.parentId = parentId;
    node.attributes = domNode->attributes_ ? domNode->attributes_->Duplicate() : nullptr;
    node.children.reserve(domNode->children_.size());

    for (auto& child : domNode->children_) {
        node.children.push_back(BuildActiveNode(child, node.id));
    }
    return node;
}

void WebDomDocument::BuildActiveNodeMap(const ActiveNode& node,
    std::unordered_map<int32_t, const ActiveNode*>& map)
{
    map[node.id] = &node;
    for (const auto& child : node.children) {
        BuildActiveNodeMap(child, map);
    }
}

void WebDomDocument::Commit()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::Commit");
    auto activeDocument = std::make_shared<ActiveDocument>();
    if (!root_) {
        TAG_LOGE(AceLogTag::ACE_WEB, "Commit no root");
        return;
    }
    activeDocument->root = BuildActiveNode(root_, WEB_ERROR_INT);
    BuildActiveNodeMap(activeDocument->root, activeDocument->idToActiveNodeMap);

    std::unique_lock<std::shared_mutex> lock(activeMutex_);
    active_ = std::move(activeDocument);
}

void WebDomDocument::MarkDirty()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::MarkDirty");
    Commit();
}

void WebDomDocument::CreateFromJsonString(const std::string &jsonString)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument CreateFromJsonString size:%{public}zu",
        jsonString.size());
    snapshot_ = JsonUtil::ParseJsonString(jsonString);
    if (!snapshot_ || !snapshot_->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CreateFromJsonString snapshot is not valid");
        return;
    }
    if (snapshot_->Contains(WEB_JSON_ATTRS) && snapshot_->GetValue(WEB_JSON_ATTRS)->IsObject()) {
        url_ = snapshot_->GetValue(WEB_JSON_ATTRS)->GetString(WEB_JSON_URL, WEB_ERROR_STRING);
        title_ = snapshot_->GetValue(WEB_JSON_ATTRS)->GetString(WEB_JSON_TITLE, WEB_ERROR_STRING);
    } else {
        TAG_LOGI(AceLogTag::ACE_WEB, "CreateFromJsonString root has no url and title");
        url_ = WEB_ERROR_STRING;
        title_ =WEB_ERROR_STRING;
    }
    if (snapshot_->Contains(WEB_JSON_CHILD) && snapshot_->GetValue(WEB_JSON_CHILD)->IsObject()) {
        idToNodeMap_.clear();
        auto child = snapshot_->GetValue(WEB_JSON_CHILD);
        root_ = CreateNode(child);
        MarkDirty();
    } else {
        TAG_LOGI(AceLogTag::ACE_WEB, "CreateFromJsonString no root");
    }
}

void WebDomDocument::UpdateNodeScrollInfo(WebDomNode* node, const OffsetF& delta)
{
    if (!node) {
        return;
    }

    node->rect_ -= delta;
    for (auto& child : node->children_) {
        UpdateNodeScrollInfo(child.get(), delta);
    }
}

void WebDomDocument::UpdateScrollInfoFromJsonString(const std::string& jsonString)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument UpdateScrollInfoFromJsonString size:%{public}zu",
        jsonString.size());
    auto update = JsonUtil::ParseJsonString(jsonString);
    if (!update || !update->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "UpdateScrollInfoFromJsonString is not valid");
        return;
    }

    int32_t id = update->GetInt(WEB_JSON_ID, WEB_ERROR_INT);
    double updateLeft = update->GetDouble(WEB_ATTR_SCROLL_LEFT, WEB_ERROR_DOUBLE);
    double updateTop = update->GetDouble(WEB_ATTR_SCROLL_TOP, WEB_ERROR_DOUBLE);
    TAG_LOGI(AceLogTag::ACE_WEB, "UpdateScrollInfo id:%{public}d, left:%{public}f, top:%{public}f",
        id, updateLeft, updateTop);

    auto it = idToNodeMap_.find(id);
    if (it == idToNodeMap_.end()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "UpdateScrollInfo node not find");
        return;
    }

    auto& current = it->second;
    if (!current->attributes_ || !current->attributes_->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "UpdateScrollInfo no attributes");
        return;
    }
    double oldLeft = current->attributes_->GetDouble(WEB_ATTR_SCROLL_LEFT, WEB_ERROR_DOUBLE);
    double oldTop = current->attributes_->GetDouble(WEB_ATTR_SCROLL_TOP, WEB_ERROR_DOUBLE);

    auto deltaLeft = updateLeft - oldLeft;
    auto deltaTop = updateTop - oldTop;
    if (NearZero(deltaLeft) && NearZero(deltaTop)) {
        TAG_LOGI(AceLogTag::ACE_WEB, "UpdateScrollInfo near no change");
        return;
    }

    current->attributes_->Replace(WEB_ATTR_SCROLL_LEFT, updateLeft);
    current->attributes_->Replace(WEB_ATTR_SCROLL_TOP, updateTop);

    UpdateNodeScrollInfo(it->second.get(), OffsetF(deltaLeft, deltaTop));
    MarkDirty();
}

std::unique_ptr<JsonValue> WebDomDocument::ExportToJson()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::ExportToJson");
    std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
    if (IsValid()) {
        auto rootJson = active_->root.ToJson(*this);
        children->Put(rootJson);
        return children;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "document root is null");
    return children;
}

std::shared_ptr<const ActiveDocument> WebDomDocument::GetActiveDocument() const
{
    std::shared_lock<std::shared_mutex> lock(activeMutex_);
    return active_;
}

const ActiveNode* WebDomDocument::GetNodeById(int32_t id) const
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::GetNodeById id : %{public}d", id);
    auto active = GetActiveDocument();
    if (!active) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebDomDocument active is null");
        return nullptr;
    }
    auto it = active->idToActiveNodeMap.find(id);
    if (it == active->idToActiveNodeMap.end()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebDomDocument::GetNodeById key is null");
        return nullptr;
    }
    if (!it->second) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebDomDocument::GetNodeById value is null");
        return nullptr;
    }
    return it->second;
}

std::pair<int32_t, RectF> WebDomDocument::GetScrollAreaInfoById(int32_t id) const
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::GetScrollAreaInfoById id : %{public}d", id);
    auto current = GetNodeById(id);
    if (!current) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebDomDocument::GetScrollAreaInfoById key is null");
        return {WEB_ERROR_INT, RectF()};
    }
    int32_t depthCounter = 0;
    while (current && current->attributes && current->attributes->IsValid()) {
        if (current->attributes->GetBool(WEB_ATTR_IS_SCROLLABLE, true)) {
            auto scrollLeft = current->attributes->GetDouble(WEB_ATTR_SCROLL_LEFT, WEB_ERROR_DOUBLE);
            auto scrollTop = current->attributes->GetDouble(WEB_ATTR_SCROLL_TOP, WEB_ERROR_DOUBLE);
            auto scrollWidth = current->attributes->GetDouble(WEB_ATTR_SCROLL_WIDTH, WEB_ERROR_DOUBLE);
            auto scrollHeight = current->attributes->GetDouble(WEB_ATTR_SCROLL_HEIGHT, WEB_ERROR_DOUBLE);
            return {current->id, RectF(scrollLeft, scrollTop, scrollWidth, scrollHeight)};
        }
        depthCounter++;
        if (depthCounter > WEB_MAX_DOM_DEPTH) {
            TAG_LOGE(AceLogTag::ACE_WEB, "WebDomDocument::GetScrollArea max depth !");
            return {WEB_ERROR_INT, RectF()};
        }
        current = GetNodeById(current->parentId);
    }
    return {WEB_ERROR_INT, RectF()};
}

std::string WebDomDocument::GetXpathById(int32_t id) const
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::GetXpathById id : %{public}d", id);
    auto current = GetNodeById(id);
    if (current == nullptr || !current->attributes || !current->attributes->IsValid()) {
        return WEB_ERROR_STRING;
    }
    return current->attributes->GetString(WEB_ATTR_XPATH, WEB_ERROR_STRING);
}

std::string WebDomDocument::GetImageUrlById(int32_t id) const
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::GetImageUrlById id : %{public}d", id);
    auto current = GetNodeById(id);
    if (current == nullptr || !current->attributes || !current->attributes->IsValid()) {
        return WEB_ERROR_STRING;
    }
    return current->attributes->GetString(WEB_ATTR_SRC, WEB_ERROR_STRING);
}

}  // namespace OHOS::Ace::NG
