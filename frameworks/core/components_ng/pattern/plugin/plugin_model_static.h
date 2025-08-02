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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_STATIC_H

#include "core/components_ng/pattern/plugin/plugin_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT PluginModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetRequestPluginInfo(FrameNode *frameNode, const std::optional<RequestPluginInfo>& pluginInfo);
    static void SetData(FrameNode *frameNode, const std::optional<std::string>& data);
    static void SetOnComplete(FrameNode *frameNode, std::function<void(const std::string&)>&& OnComplete);
    static void SetOnError(FrameNode *frameNode, std::function<void(const std::string&)>&& OnError);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_STATIC_H
