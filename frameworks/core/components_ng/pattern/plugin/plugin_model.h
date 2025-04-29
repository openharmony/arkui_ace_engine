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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_H

#include <mutex>

#include "core/components/plugin/resource/plugin_request_data.h"
#include "core/components_ng/pattern/plugin/plugin_event_hub.h"

namespace OHOS::Ace {
class PluginModel {
public:
    static PluginModel* GetInstance();
    virtual ~PluginModel() = default;

    virtual void Create(const RequestPluginInfo& pluginInfo) = 0;
    virtual void SetOnComplete(std::function<void(const std::string&)>&& OnComplete) = 0;
    virtual void SetOnError(std::function<void(const std::string&)>&& OnError) = 0;
    virtual void SetPluginSize(const Dimension& width, const Dimension& height) = 0;
    virtual void SetWidth(const Dimension& width) = 0;
    virtual void SetHeight(const Dimension& height) = 0;
    virtual void SetData(const std::string& data) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_MODEL_H
