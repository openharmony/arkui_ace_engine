/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/manager/uisession_query/component_tree_query.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <unordered_set>
#include <vector>

#include <regex.h>

#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "frameworks/base/json/json_util.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ERR_OK = static_cast<int32_t>(ComponentTreeQueryError::OK);
constexpr int32_t ERR_INVALID_PARAMETER = static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER);
constexpr int32_t ERR_TARGET_NOT_FOUND = static_cast<int32_t>(ComponentTreeQueryError::TARGET_NOT_FOUND);
constexpr int32_t ERR_UNSUPPORTED_FRONTEND = static_cast<int32_t>(ComponentTreeQueryError::UNSUPPORTED_FRONTEND);
constexpr int32_t ERR_DATA_SOURCE_ERROR = static_cast<int32_t>(ComponentTreeQueryError::DATA_SOURCE_ERROR);
constexpr int32_t ERR_SERIALIZATION_ERROR = static_cast<int32_t>(ComponentTreeQueryError::SERIALIZATION_ERROR);
constexpr int32_t ERR_RESOURCE_LIMIT = static_cast<int32_t>(ComponentTreeQueryError::RESOURCE_LIMIT);
constexpr int32_t ERR_INTERNAL_ERROR = static_cast<int32_t>(ComponentTreeQueryError::INTERNAL_ERROR);

const char QUERY_KEY_ERROR_CODE[] = "errorCode";
const char QUERY_KEY_TYPE[] = "type";
const char QUERY_KEY_RESULTS[] = "results";
const char QUERY_KEY_CONTENT[] = "content";
const char QUERY_KEY_NAV_BAR_MATCHES[] = "navBarMatches";
const char QUERY_KEY_INDEX[] = "index";

// Traversal state shared by all preorder walks of this query.
struct ScanState {
    int32_t scanned = 0; // nodes visited so far (resource limit)
    bool limitExceeded = false;
};

// Best point-hit candidate: deepest node wins; equal depth keeps the node
// visited later in preorder (siblings drawn later are on top).
struct HitCandidate {
    RefPtr<FrameNode> node;
    int32_t depth = -1;
};

RectF GetVisibleRectRelativeToWindow(const RefPtr<FrameNode>& node)
{
    if (!node) {
        return RectF();
    }
    // ADR-2: filters inactive nodes and nodes under invisible ancestors by
    // returning an invalid rect (INT32_MAX offset, zero size).
    return node->GetTransformRectRelativeToWindowOnlyVisible();
}

// Collects direct children plus the overlay branch (same order the Inspector uses).
std::vector<RefPtr<UINode>> GetTraversalChildren(const RefPtr<UINode>& node)
{
    std::vector<RefPtr<UINode>> children;
    if (!node) {
        return children;
    }
    for (const auto& child : node->GetChildren()) {
        children.emplace_back(child);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode) {
        auto overlay = frameNode->GetOverlayNode();
        if (overlay) {
            children.emplace_back(overlay);
        }
    }
    return children;
}

bool ConsumeScanQuota(ScanState& state)
{
    ++state.scanned;
    if (state.scanned > COMPONENT_TREE_QUERY_MAX_SCAN_NODES) {
        state.limitExceeded = true;
        return false;
    }
    return true;
}

void VisitForPointHit(const RefPtr<UINode>& node, int32_t depth, float x, float y, ScanState& state,
    HitCandidate& best)
{
    if (!node || !ConsumeScanQuota(state)) {
        return;
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode) {
        auto rect = GetVisibleRectRelativeToWindow(frameNode);
        if (ComponentTreeQuery::IsPointInRectBoundaryInclusive(x, y, rect) &&
            GreatNotEqual(rect.Width(), 0.0f) && GreatNotEqual(rect.Height(), 0.0f)) {
            // Preorder guarantees later visits at the same depth are drawn on top.
            if (depth >= best.depth) {
                best.node = frameNode;
                best.depth = depth;
            }
        }
    }
    for (const auto& child : GetTraversalChildren(node)) {
        VisitForPointHit(child, depth + 1, x, y, state, best);
        if (state.limitExceeded) {
            return;
        }
    }
}

// Region (circle/rect) collection with tree order and node id dedup.
void VisitForRegion(const RefPtr<UINode>& node, ScanState& state, std::unordered_set<int32_t>& visitedIds,
    const std::function<bool(const RectF&)>& hitTest, std::vector<RefPtr<FrameNode>>& matched)
{
    if (!node || !ConsumeScanQuota(state)) {
        return;
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode && visitedIds.find(node->GetId()) == visitedIds.end()) {
        visitedIds.emplace(node->GetId());
        auto rect = GetVisibleRectRelativeToWindow(frameNode);
        if (GreatNotEqual(rect.Width(), 0.0f) && GreatNotEqual(rect.Height(), 0.0f) && hitTest(rect)) {
            matched.emplace_back(frameNode);
        }
    }
    for (const auto& child : GetTraversalChildren(node)) {
        VisitForRegion(child, state, visitedIds, hitTest, matched);
        if (state.limitExceeded) {
            return;
        }
    }
}

// Walks up from the hit node; returns the first ancestor matching pred together
// with the child on the path directly below it.
RefPtr<UINode> FindAncestorWithDirectChild(const RefPtr<UINode>& hitNode,
    const std::function<bool(const RefPtr<UINode>&)>& pred, RefPtr<UINode>& directChild)
{
    auto current = hitNode;
    while (current) {
        auto parent = current->GetParent();
        if (!parent) {
            break;
        }
        if (pred(parent)) {
            directChild = current;
            return parent;
        }
        current = parent;
    }
    directChild = nullptr;
    return nullptr;
}

std::string BuildErrorJson(int32_t errorCode, const char* type)
{
    auto json = JsonUtil::Create(true);
    json->Put(QUERY_KEY_ERROR_CODE, errorCode);
    json->Put(QUERY_KEY_TYPE, type);
    return json->ToString();
}

std::unique_ptr<JsonValue> ParseJsonOrEmpty(const std::string& jsonStr)
{
    auto parsed = JsonUtil::ParseJsonString(jsonStr);
    if (!parsed || !parsed->IsValid()) {
        return JsonUtil::Create(true);
    }
    return parsed;
}

bool CheckSerializedSize(size_t current)
{
    return current <= COMPONENT_TREE_QUERY_MAX_SERIALIZED_BYTES;
}
} // namespace

// static
bool ComponentTreeQuery::IsFinitePoint(float x, float y)
{
    return std::isfinite(x) && std::isfinite(y);
}

// static
bool ComponentTreeQuery::IsPointInRectBoundaryInclusive(float x, float y, const RectF& rect)
{
    return GreatOrEqual(x, rect.Left()) && LessOrEqual(x, rect.Right()) && GreatOrEqual(y, rect.Top()) &&
           LessOrEqual(y, rect.Bottom());
}

// static
RectF ComponentTreeQuery::NormalizeRect(float x1, float y1, float x2, float y2)
{
    auto left = std::min(x1, x2);
    auto right = std::max(x1, x2);
    auto top = std::min(y1, y2);
    auto bottom = std::max(y1, y2);
    return RectF(left, top, right - left, bottom - top);
}

// static
bool ComponentTreeQuery::IsPositiveAreaRectIntersection(const RectF& lhs, const RectF& rhs)
{
    auto left = std::max(lhs.Left(), rhs.Left());
    auto right = std::min(lhs.Right(), rhs.Right());
    auto top = std::max(lhs.Top(), rhs.Top());
    auto bottom = std::min(lhs.Bottom(), rhs.Bottom());
    // "Only touching" (zero-width/height intersection) does not count (ADR-4).
    return GreatNotEqual(right - left, 0.0f) && GreatNotEqual(bottom - top, 0.0f);
}

// static
bool ComponentTreeQuery::IsCircleIntersectRectPositiveArea(float centerX, float centerY, float radius,
    const RectF& rect)
{
    if (!std::isfinite(radius) || LessOrEqual(radius, 0.0f)) {
        return false;
    }
    if (LessOrEqual(rect.Width(), 0.0f) || LessOrEqual(rect.Height(), 0.0f)) {
        return false;
    }
    auto nearestX = std::clamp(centerX, rect.Left(), rect.Right());
    auto nearestY = std::clamp(centerY, rect.Top(), rect.Bottom());
    auto dx = centerX - nearestX;
    auto dy = centerY - nearestY;
    // Strictly less: circle/rect tangency does not count as a hit (ADR-4).
    return LessNotEqual(dx * dx + dy * dy, radius * radius);
}

// static
int32_t ComponentTreeQuery::CheckRegex(const std::string& pattern)
{
    if (pattern.empty()) {
        return ERR_INVALID_PARAMETER;
    }
    if (pattern.size() > COMPONENT_TREE_QUERY_MAX_REGEX_BYTES) {
        return ERR_RESOURCE_LIMIT;
    }
    // POSIX regcomp reports syntax errors through the return code instead of
    // throwing, which keeps the UI thread safe under -fno-exceptions.
    regex_t compiled;
    if (regcomp(&compiled, pattern.c_str(), REG_EXTENDED | REG_NOSUB) != 0) {
        return ERR_INVALID_PARAMETER;
    }
    regfree(&compiled);
    return ERR_OK;
}

// static
int32_t ComponentTreeQuery::QueryLazyForEachDataByPoint(float x, float y, std::string& resultJson)
{
    if (!IsFinitePoint(x, y)) {
        resultJson = BuildErrorJson(ERR_INVALID_PARAMETER, "lazyForEachData");
        return ERR_INVALID_PARAMETER;
    }
    auto context = PipelineContext::GetCurrentContextSafely();
    auto root = context ? context->GetRootElement() : nullptr;
    if (!root) {
        resultJson = BuildErrorJson(ERR_INTERNAL_ERROR, "lazyForEachData");
        return ERR_INTERNAL_ERROR;
    }
    ScanState state;
    HitCandidate best;
    VisitForPointHit(root, 0, x, y, state, best);
    if (state.limitExceeded) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "lazyForEachData");
        return ERR_RESOURCE_LIMIT;
    }
    if (!best.node) {
        resultJson = BuildErrorJson(ERR_TARGET_NOT_FOUND, "lazyForEachData");
        return ERR_TARGET_NOT_FOUND;
    }
    // Static ArkTS LazyForEach (ArkoalaLazyNode) can not serve getData.
    RefPtr<UINode> ignored;
    auto staticLazy = FindAncestorWithDirectChild(
        best.node, [](const RefPtr<UINode>& node) { return AceType::InstanceOf<ArkoalaLazyNode>(node); }, ignored);
    if (staticLazy) {
        resultJson = BuildErrorJson(ERR_UNSUPPORTED_FRONTEND, "lazyForEachData");
        return ERR_UNSUPPORTED_FRONTEND;
    }
    RefPtr<UINode> directChild;
    auto lazyForEach = FindAncestorWithDirectChild(
        best.node, [](const RefPtr<UINode>& node) { return AceType::InstanceOf<LazyForEachNode>(node); },
        directChild);
    if (!lazyForEach) {
        resultJson = BuildErrorJson(ERR_TARGET_NOT_FOUND, "lazyForEachData");
        return ERR_TARGET_NOT_FOUND;
    }
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(lazyForEach);
    if (!lazyForEachNode) {
        resultJson = BuildErrorJson(ERR_INTERNAL_ERROR, "lazyForEachData");
        return ERR_INTERNAL_ERROR;
    }
    auto index = lazyForEachNode->GetIndexByUINode(directChild);
    if (index < 0) {
        resultJson = BuildErrorJson(ERR_TARGET_NOT_FOUND, "lazyForEachData");
        return ERR_TARGET_NOT_FOUND;
    }
    auto builder = lazyForEachNode->GetBuilder();
    if (!builder) {
        resultJson = BuildErrorJson(ERR_DATA_SOURCE_ERROR, "lazyForEachData");
        return ERR_DATA_SOURCE_ERROR;
    }
    if (!builder->IsDataExtractionSupported()) {
        resultJson = BuildErrorJson(ERR_UNSUPPORTED_FRONTEND, "lazyForEachData");
        return ERR_UNSUPPORTED_FRONTEND;
    }
    int32_t dataError = ERR_OK;
    auto dataJson = builder->GetDataByIndexAsJson(index, dataError);
    if (dataError != ERR_OK) {
        resultJson = BuildErrorJson(dataError, "lazyForEachData");
        return dataError;
    }
    if (dataJson.empty()) {
        resultJson = BuildErrorJson(ERR_DATA_SOURCE_ERROR, "lazyForEachData");
        return ERR_DATA_SOURCE_ERROR;
    }
    auto parsedData = JsonUtil::ParseJsonString(dataJson);
    if (!parsedData || !parsedData->IsValid()) {
        resultJson = BuildErrorJson(ERR_SERIALIZATION_ERROR, "lazyForEachData");
        return ERR_SERIALIZATION_ERROR;
    }
    auto json = JsonUtil::Create(true);
    json->Put(QUERY_KEY_ERROR_CODE, ERR_OK);
    json->Put(QUERY_KEY_TYPE, "lazyForEachData");
    json->Put(QUERY_KEY_INDEX, index);
    auto results = JsonUtil::CreateArray(true);
    results->PutRef(std::move(parsedData)); // [currentData] per AC-1.1
    json->PutRef(QUERY_KEY_RESULTS, std::move(results));
    resultJson = json->ToString();
    if (!CheckSerializedSize(resultJson.size())) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "lazyForEachData");
        return ERR_RESOURCE_LIMIT;
    }
    return ERR_OK;
}

// static
int32_t ComponentTreeQuery::QueryNavigationContentByPoint(
    float x, float y, const std::string& pattern, std::string& resultJson)
{
    auto regexCheck = CheckRegex(pattern);
    if (regexCheck != ERR_OK) {
        resultJson = BuildErrorJson(regexCheck, "navigationContent");
        return regexCheck;
    }
    if (!IsFinitePoint(x, y)) {
        resultJson = BuildErrorJson(ERR_INVALID_PARAMETER, "navigationContent");
        return ERR_INVALID_PARAMETER;
    }
    auto context = PipelineContext::GetCurrentContextSafely();
    auto root = context ? context->GetRootElement() : nullptr;
    if (!root) {
        resultJson = BuildErrorJson(ERR_INTERNAL_ERROR, "navigationContent");
        return ERR_INTERNAL_ERROR;
    }
    ScanState state;
    HitCandidate best;
    VisitForPointHit(root, 0, x, y, state, best);
    if (state.limitExceeded) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "navigationContent");
        return ERR_RESOURCE_LIMIT;
    }
    if (!best.node) {
        resultJson = BuildErrorJson(ERR_TARGET_NOT_FOUND, "navigationContent");
        return ERR_TARGET_NOT_FOUND;
    }
    RefPtr<UINode> ignored;
    auto navigationGroup = FindAncestorWithDirectChild(best.node,
        [](const RefPtr<UINode>& node) { return AceType::InstanceOf<NavigationGroupNode>(node); }, ignored);
    auto navGroupNode = AceType::DynamicCast<NavigationGroupNode>(navigationGroup);
    if (!navGroupNode) {
        resultJson = BuildErrorJson(ERR_TARGET_NOT_FOUND, "navigationContent");
        return ERR_TARGET_NOT_FOUND;
    }
    auto contentNode = navGroupNode->GetContentNode();
    if (!contentNode) {
        resultJson = BuildErrorJson(ERR_TARGET_NOT_FOUND, "navigationContent");
        return ERR_TARGET_NOT_FOUND;
    }
    auto contentJsonStr = Inspector::GetInspectorOfNodeSubtree(contentNode);
    if (!CheckSerializedSize(contentJsonStr.size())) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "navigationContent");
        return ERR_RESOURCE_LIMIT;
    }
    regex_t regex;
    if (regcomp(&regex, pattern.c_str(), REG_EXTENDED | REG_NOSUB) != 0) {
        resultJson = BuildErrorJson(ERR_INVALID_PARAMETER, "navigationContent");
        return ERR_INVALID_PARAMETER;
    }
    std::vector<std::string> matchJsonStrs;
    size_t serializedSize = contentJsonStr.size();
    auto navBarNode = navGroupNode->GetNavBarNode();
    // Preorder walk over NavBar descendants: single node Inspector JSON per
    // node, regex match, tree order kept, dedup by node id (Q-4/Q-6).
    if (navBarNode) {
        std::unordered_set<int32_t> visitedIds;
        std::function<void(const RefPtr<UINode>&)> walk = [&](const RefPtr<UINode>& node) {
            if (!node || !ConsumeScanQuota(state)) {
                return;
            }
            if (visitedIds.find(node->GetId()) == visitedIds.end()) {
                visitedIds.emplace(node->GetId());
                auto nodeJsonStr = Inspector::GetInspectorOfNode(node);
                if (nodeJsonStr.empty() || !CheckSerializedSize(serializedSize + nodeJsonStr.size())) {
                    state.limitExceeded = true;
                    return;
                }
                // POSIX regexec finds a match anywhere in the JSON string.
                if (regexec(&regex, nodeJsonStr.c_str(), 0, nullptr, 0) == 0) {
                    matchJsonStrs.emplace_back(nodeJsonStr);
                    serializedSize += nodeJsonStr.size();
                }
            }
            for (const auto& child : GetTraversalChildren(node)) {
                walk(child);
                if (state.limitExceeded) {
                    return;
                }
            }
        };
        walk(navBarNode);
    }
    regfree(&regex);
    if (state.limitExceeded) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "navigationContent");
        return ERR_RESOURCE_LIMIT;
    }
    auto json = JsonUtil::Create(true);
    json->Put(QUERY_KEY_ERROR_CODE, ERR_OK);
    json->Put(QUERY_KEY_TYPE, "navigationContent");
    json->PutRef(QUERY_KEY_CONTENT, ParseJsonOrEmpty(contentJsonStr));
    auto matches = JsonUtil::CreateArray(true);
    for (const auto& matchStr : matchJsonStrs) {
        matches->PutRef(ParseJsonOrEmpty(matchStr));
    }
    json->PutRef(QUERY_KEY_NAV_BAR_MATCHES, std::move(matches));
    resultJson = json->ToString();
    if (!CheckSerializedSize(resultJson.size())) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "navigationContent");
        return ERR_RESOURCE_LIMIT;
    }
    return ERR_OK;
}

// static
int32_t ComponentTreeQuery::QueryNodesInCircle(float centerX, float centerY, float radius, std::string& resultJson)
{
    if (!IsFinitePoint(centerX, centerY) || !std::isfinite(radius) || LessOrEqual(radius, 0.0f)) {
        resultJson = BuildErrorJson(ERR_INVALID_PARAMETER, "nodesInCircle");
        return ERR_INVALID_PARAMETER;
    }
    auto context = PipelineContext::GetCurrentContextSafely();
    auto root = context ? context->GetRootElement() : nullptr;
    if (!root) {
        resultJson = BuildErrorJson(ERR_INTERNAL_ERROR, "nodesInCircle");
        return ERR_INTERNAL_ERROR;
    }
    ScanState state;
    std::unordered_set<int32_t> visitedIds;
    std::vector<RefPtr<FrameNode>> matched;
    VisitForRegion(root, state, visitedIds,
        [centerX, centerY, radius](const RectF& rect) {
            return ComponentTreeQuery::IsCircleIntersectRectPositiveArea(centerX, centerY, radius, rect);
        },
        matched);
    if (state.limitExceeded) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "nodesInCircle");
        return ERR_RESOURCE_LIMIT;
    }
    auto json = JsonUtil::Create(true);
    json->Put(QUERY_KEY_ERROR_CODE, ERR_OK);
    json->Put(QUERY_KEY_TYPE, "nodesInCircle");
    auto results = JsonUtil::CreateArray(true);
    size_t serializedSize = 0;
    for (const auto& node : matched) {
        auto nodeJsonStr = Inspector::GetInspectorOfNode(node);
        serializedSize += nodeJsonStr.size();
        if (!CheckSerializedSize(serializedSize)) {
            resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "nodesInCircle");
            return ERR_RESOURCE_LIMIT;
        }
        results->PutRef(ParseJsonOrEmpty(nodeJsonStr));
    }
    json->PutRef(QUERY_KEY_RESULTS, std::move(results));
    resultJson = json->ToString();
    if (!CheckSerializedSize(resultJson.size())) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "nodesInCircle");
        return ERR_RESOURCE_LIMIT;
    }
    return ERR_OK;
}

// static
int32_t ComponentTreeQuery::QueryNodesInRect(float x1, float y1, float x2, float y2, std::string& resultJson)
{
    if (!IsFinitePoint(x1, y1) || !IsFinitePoint(x2, y2)) {
        resultJson = BuildErrorJson(ERR_INVALID_PARAMETER, "nodesInRect");
        return ERR_INVALID_PARAMETER;
    }
    auto queryRect = NormalizeRect(x1, y1, x2, y2);
    if (LessOrEqual(queryRect.Width(), 0.0f) || LessOrEqual(queryRect.Height(), 0.0f)) {
        resultJson = BuildErrorJson(ERR_INVALID_PARAMETER, "nodesInRect");
        return ERR_INVALID_PARAMETER;
    }
    auto context = PipelineContext::GetCurrentContextSafely();
    auto root = context ? context->GetRootElement() : nullptr;
    if (!root) {
        resultJson = BuildErrorJson(ERR_INTERNAL_ERROR, "nodesInRect");
        return ERR_INTERNAL_ERROR;
    }
    ScanState state;
    std::unordered_set<int32_t> visitedIds;
    std::vector<RefPtr<FrameNode>> matched;
    VisitForRegion(root, state, visitedIds,
        [queryRect](const RectF& rect) { return IsPositiveAreaRectIntersection(queryRect, rect); }, matched);
    if (state.limitExceeded) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "nodesInRect");
        return ERR_RESOURCE_LIMIT;
    }
    auto json = JsonUtil::Create(true);
    json->Put(QUERY_KEY_ERROR_CODE, ERR_OK);
    json->Put(QUERY_KEY_TYPE, "nodesInRect");
    auto results = JsonUtil::CreateArray(true);
    size_t serializedSize = 0;
    for (const auto& node : matched) {
        auto nodeJsonStr = Inspector::GetInspectorOfNode(node);
        serializedSize += nodeJsonStr.size();
        if (!CheckSerializedSize(serializedSize)) {
            resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "nodesInRect");
            return ERR_RESOURCE_LIMIT;
        }
        results->PutRef(ParseJsonOrEmpty(nodeJsonStr));
    }
    json->PutRef(QUERY_KEY_RESULTS, std::move(results));
    resultJson = json->ToString();
    if (!CheckSerializedSize(resultJson.size())) {
        resultJson = BuildErrorJson(ERR_RESOURCE_LIMIT, "nodesInRect");
        return ERR_RESOURCE_LIMIT;
    }
    return ERR_OK;
}

// static
int32_t ComponentTreeQuery::Execute(const ComponentTreeQueryRequest& request, std::string& resultJson)
{
    switch (request.type) {
        case ComponentTreeQueryType::LAZY_FOREACH_DATA_BY_POINT:
            return QueryLazyForEachDataByPoint(request.x, request.y, resultJson);
        case ComponentTreeQueryType::NAVIGATION_CONTENT_BY_POINT:
            return QueryNavigationContentByPoint(request.x, request.y, request.pattern, resultJson);
        case ComponentTreeQueryType::NODES_IN_CIRCLE:
            return QueryNodesInCircle(request.x, request.y, request.radius, resultJson);
        case ComponentTreeQueryType::NODES_IN_RECT:
            return QueryNodesInRect(request.x, request.y, request.extraX, request.extraY, resultJson);
        default:
            resultJson = BuildErrorJson(ERR_INVALID_PARAMETER, "unknown");
            return ERR_INVALID_PARAMETER;
    }
}
} // namespace OHOS::Ace::NG
