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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_PERFORMANCE_CHECK_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_PERFORMANCE_CHECK_TYPES_H

#include <cstdint>
#include <string>
#include <unordered_map>

namespace OHOS::Ace {
struct PerformanceCheckNode {
    int32_t pageDepth = 0;      // node depth
    int32_t childrenSize = 0;   // node children size
    int32_t codeRow = 0;        // js code row
    int32_t codeCol = 0;        // js code col
    int64_t layoutTime = 0;     // node layout time
    int32_t flexLayouts = 0;    // node flex layout times
    bool isForEachItem = false; // foreach item
    int32_t foreachItems = 0;   // foreach item count
    std::string nodeTag;        // node tag
    std::string pagePath;       // page path
};

using PerformanceCheckNodeMap = std::unordered_map<int32_t, PerformanceCheckNode>;
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_PERFORMANCE_CHECK_TYPES_H
