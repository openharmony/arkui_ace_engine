/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_NG_H

#include "core/components_ng/pattern/plugin/plugin_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT PluginModelNG : public OHOS::Ace::PluginModel {
public:
    void Create(const RequestPluginInfo& pluginInfo) override;
    void SetOnComplete(std::function<void(const std::string&)>&& OnComplete) override;
    void SetOnError(std::function<void(const std::string&)>&& OnError) override;
    void SetPluginSize(const Dimension& width, const Dimension& height) override;
    void SetData(const std::string& data) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;

    static void SetPluginSize(FrameNode* frameNode, const Dimension& width, const Dimension& height);
    static void SetWidth(FrameNode* frameNode, const Dimension& width);
    static void SetHeight(FrameNode* frameNode, const Dimension& height);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_NG_H
