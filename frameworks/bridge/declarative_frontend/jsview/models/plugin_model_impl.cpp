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

#include "bridge/declarative_frontend/jsview/models/plugin_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/plugin/plugin_component.h"

namespace OHOS::Ace::Framework {
void PluginModelImpl::Create(const RequestPluginInfo& pluginInfo)
{
    RefPtr<PluginComponent> plugin = AceType::MakeRefPtr<OHOS::Ace::PluginComponent>();
    plugin->SetPluginRequestInfo(pluginInfo);
    ViewStackProcessor::GetInstance()->Push(plugin, false);
};

void PluginModelImpl::SetOnComplete(std::function<void(const std::string&)>&& onCompleteId)
{
    auto onComplete = EventMarker(std::move(onCompleteId));
    auto plugin = AceType::DynamicCast<PluginComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (plugin) {
        plugin->SetOnCompleteEventId(onComplete);
    }
};

void PluginModelImpl::SetOnError(std::function<void(const std::string&)>&& onErrorId)
{
    auto onError = EventMarker(std::move(onErrorId));
    auto plugin = AceType::DynamicCast<PluginComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (plugin) {
        plugin->SetOnErrorEventId(onError);
    }
};

void PluginModelImpl::SetPluginSize(const Dimension& width, const Dimension& height)
{
    auto plugin = AceType::DynamicCast<PluginComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (plugin) {
        plugin->SetPluginSize(width, height);
    }
};

void PluginModelImpl::SetWidth(const Dimension& width)
{
    auto plugin = AceType::DynamicCast<PluginComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (plugin) {
        plugin->SetWidth(width);
    }
};

void PluginModelImpl::SetHeight(const Dimension& height)
{
    auto plugin = AceType::DynamicCast<PluginComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (plugin) {
        plugin->SetHeight(height);
    }
};

void PluginModelImpl::SetData(const std::string& data)
{
    auto plugin = AceType::DynamicCast<PluginComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (plugin) {
        plugin->SetData(data);
    }
};
} // namespace OHOS::Ace::Framework
