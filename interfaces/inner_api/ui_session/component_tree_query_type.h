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

#ifndef FOUNDATION_ACE_INTERFACE_COMPONENT_TREE_QUERY_TYPE_H
#define FOUNDATION_ACE_INTERFACE_COMPONENT_TREE_QUERY_TYPE_H

#include <cstddef>
#include <cstdint>
#include <string>

namespace OHOS::Ace {

// Structured error codes for component tree spatial/context queries (FEAT-031).
// Keep in sync with NG::ComponentTreeQuery usage; positive small ints are safe
// to cross the UISession IPC boundary inside the reported JSON payload.
enum class ComponentTreeQueryError : int32_t {
    OK = 0,
    INVALID_PARAMETER = 1,   // non-finite coords, non-positive radius/rect, invalid regex
    TARGET_NOT_FOUND = 2,    // no LazyForEach / NavigationGroupNode ancestor, no hit node
    UNSUPPORTED_FRONTEND = 3, // static ArkTS / CJ LazyForEach builder
    DATA_SOURCE_ERROR = 4,   // getData(index) threw or returned nothing
    SERIALIZATION_ERROR = 5, // data can not be serialized to JSON
    RESOURCE_LIMIT = 6,      // regex > 1024B / scan > 10000 nodes / serialized > 4MiB
    INTERNAL_ERROR = 7,      // no pipeline / no root node
};

enum class ComponentTreeQueryType : int32_t {
    LAZY_FOREACH_DATA_BY_POINT = 0,
    NAVIGATION_CONTENT_BY_POINT = 1,
    NODES_IN_CIRCLE = 2,
    NODES_IN_RECT = 3,
};

struct ComponentTreeQueryRequest {
    ComponentTreeQueryType type = ComponentTreeQueryType::LAZY_FOREACH_DATA_BY_POINT;
    // Window physical pixel coordinates. Used as point (x, y) for point based
    // queries, as circle center (x, y) + radius for circle queries and as the
    // two rect diagonal corners (x, y) / (extraX, extraY) for rect queries.
    float x = 0.0f;
    float y = 0.0f;
    float extraX = 0.0f;
    float extraY = 0.0f;
    float radius = 0.0f;
    std::string pattern; // regex for Navigation NavBar matching (<= 1024 bytes)
};

// Resource limits shared by the query implementation and its unit tests.
constexpr size_t COMPONENT_TREE_QUERY_MAX_REGEX_BYTES = 1024;
constexpr int32_t COMPONENT_TREE_QUERY_MAX_SCAN_NODES = 10000;
constexpr size_t COMPONENT_TREE_QUERY_MAX_SERIALIZED_BYTES = 4 * 1024 * 1024; // 4 MiB

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_COMPONENT_TREE_QUERY_TYPE_H
