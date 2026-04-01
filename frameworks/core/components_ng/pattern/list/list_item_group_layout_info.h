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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_LAYOUT_INFO_H

#include <cstdint>
#include <map>

namespace OHOS::Ace::NG {

struct LayoutedItemInfo {
    int32_t startIndex = 0;
    float startPos = 0.0f;
    int32_t endIndex = 0;
    float endPos = 0.0f;
};

struct ListItemGroupInfo {
    int32_t id = -1;
    float startPos = 0.0f;
    float endPos = 0.0f;
    bool isPressed = false;
};

struct ListItemGroupCacheParam {
    bool forward = true;
    bool backward = false;
    bool show = false;
    int32_t cacheCountForward = 0;
    int32_t cacheCountBackward = 0;
    int32_t forwardCachedIndex = -1;
    int32_t backwardCachedIndex = INT_MAX;
    int64_t deadline = 0;
};

struct CachedIndexInfo {
    int32_t forwardCachedCount = 0;
    int32_t backwardCachedCount = 0;
    int32_t forwardCacheMax = 0;
    int32_t backwardCacheMax = 0;
    bool needPredict = false;
};

using ListItemGroupPositionMap = std::map<int32_t, ListItemGroupInfo>;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_LAYOUT_INFO_H
