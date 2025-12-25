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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_DOM_DOCUMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_DOM_DOCUMENT_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/offset_t.h"
#include "base/json/json_util.h"

namespace OHOS::Ace {
class JsonValue;
}  // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class WebDomDocument;
struct ActiveDocument;

constexpr char WEB_DOM_JSON_CHILDREN[] = "$children-web";
constexpr char WEB_DOM_JSON_TITLE[] = "title";
constexpr char WEB_DOM_JSON_URL[] = "url";
constexpr char WEB_DOM_JSON_TYPE_OUTER[] = "web";

constexpr char WEB_NATIVE_OBJ_DOM[] = "_arkWebDomTree";
constexpr char WEB_NATIVE_FUNC_INIT[] = "init";
constexpr char WEB_NATIVE_FUNC_INCR[] = "incremental";
constexpr char WEB_NATIVE_FUNC_SCROLL[] = "scrollInfo";
constexpr int32_t WEB_NATIVE_PARAM_SIZE = 1;
constexpr int32_t WEB_NATIVE_PARAM_INDEX = 0;

struct ActiveNode {
    int32_t id;
    std::string tagName;
    std::string type;
    RectF rect;
    std::unique_ptr<JsonValue> attributes;
    int32_t parentId;
    std::vector<ActiveNode> children;
    std::unique_ptr<JsonValue> ToJson(const WebDomDocument& document) const;
};

struct ActiveDocument {
    ActiveNode root;
    std::unordered_map<int32_t, const ActiveNode*> idToActiveNodeMap;
};
class WebDomNode : public std::enable_shared_from_this<WebDomNode> {
public:
    WebDomNode(int32_t id, const std::string& tagName);

    void SetAttributes(std::unique_ptr<JsonValue> attributes);

private:
    friend class WebDomDocument;

    int32_t id_;
    std::string tagName_;
    std::string type_ = WEB_DOM_JSON_TYPE_OUTER;
    RectF rect_;
    std::unique_ptr<JsonValue> attributes_;

    std::weak_ptr<WebDomNode> parent_;
    std::vector<std::shared_ptr<WebDomNode>> children_;
};

class WebDomDocument : public virtual AceType {
    DECLARE_ACE_TYPE(WebDomDocument, AceType);

public:
    WebDomDocument();

    void CreateFromJsonString(const std::string& jsonString);
    void UpdateScrollInfoFromJsonString(const std::string& jsonString);

    bool IsValid()
    {
        return root_ != nullptr && active_ != nullptr;
    }

    std::string GetUrl() const
    {
        return url_;
    }

    std::string GetTitle() const
    {
        return title_;
    }

    void UpdateOffset(OffsetF offset)
    {
        offset_ = offset;
    }

    OffsetF GetOffset() const
    {
        return offset_;
    }

    std::unique_ptr<JsonValue> ExportToJson();
    const ActiveNode* GetNodeById(int32_t id) const;
    std::pair<int32_t, RectF> GetScrollAreaInfoById(int32_t id) const;
    std::string GetXpathById(int32_t id) const;
    std::string GetImageUrlById(int32_t id) const;
    void MarkDirty();

private:
    std::string url_ = "";
    std::string title_ = "";
    OffsetF offset_;
    std::unique_ptr<JsonValue> snapshot_;
    std::shared_ptr<WebDomNode> root_;

    std::unordered_map<int32_t, std::shared_ptr<WebDomNode>> idToNodeMap_;

    std::atomic<bool> isDirty_ = false;
    mutable std::shared_mutex activeMutex_;
    std::shared_ptr<const ActiveDocument> active_;

    std::shared_ptr<WebDomNode> CreateNode(std::unique_ptr<JsonValue>& json);
    void UpdateNodeScrollInfo(WebDomNode* node, const OffsetF& delta);
    ActiveNode BuildActiveNode(const std::shared_ptr<WebDomNode>& domNode,
        int32_t parentId) const;
    void BuildActiveNodeMap(const ActiveNode& node,
        std::unordered_map<int32_t, const ActiveNode*>& map);
    std::shared_ptr<const ActiveDocument> GetActiveDocument() const;
    void Commit();
};
}  // namespace OHOS::Ace::NG

#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_DOM_DOCUMENT_H
