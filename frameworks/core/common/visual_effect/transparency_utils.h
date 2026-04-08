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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_VISUAL_EFFECT_TRANSPARENCY_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_VISUAL_EFFECT_TRANSPARENCY_UTILS_H

#include <cstdint>
#include <functional>
#include <list>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "ui/base/referenced.h"

namespace OHOS::Ace {
enum class UiMaterialLevel;
enum class UiMaterialTransparency;

namespace NG {
class FrameNode;
} // namespace NG

using TransparencyCallback = std::function<void(int32_t)>;
using TransparencyLevelMap = std::unordered_map<UiMaterialLevel, UiMaterialTransparency>;

struct TransparencyMapData {
    TransparencyCallback callback;
    WeakPtr<NG::FrameNode> node;
    int32_t containerId;
};

using TransparencyIdMap = std::unordered_map<int32_t, TransparencyMapData>;

class TransparencyUtils {
public:
    static int32_t GetTransparencyLevel(int32_t materialLevel);
    static std::optional<int32_t> RegisterTransparencyListener(
        const WeakPtr<NG::FrameNode>& node, TransparencyCallback&& callback);
    static void UnRegisterTransparencyListener(int32_t callbackId);

private:
    static void OnParameterChanged(const std::string& key, int32_t userId);
    static void ExecuteTransparencyCallback();
    static void HandleNodesCallback(const std::list<TransparencyMapData>& datas, int32_t transparency);
    static bool RegisterListenerInner();
    static int32_t GetCurrentUserId();
    static void AdjustTransparencyForLevel(int32_t transparency);
    static TransparencyLevelMap& GetLevelMap();
    static std::shared_mutex& GetLevelLock();
    static UiMaterialTransparency LookupTransparency(UiMaterialLevel level);

    static int32_t userId_;
    static bool userIdGet_;
    static bool listenerSet_;
    static bool transparencyLevelGet_;
    static TransparencyIdMap callbackIdsMap_;
    static std::mutex callbackMutex_;
    static int32_t callbackId_;
};
}  // namespace OHOS::Ace
#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_VISUAL_EFFECT_TRANSPARENCY_UTILS_H
