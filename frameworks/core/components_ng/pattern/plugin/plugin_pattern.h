/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_PATTERN_H

#include "core/components/plugin/resource/plugin_request_data.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/plugin/plugin_event_hub.h"
#include "core/components_ng/pattern/plugin/plugin_layout_property.h"

namespace OHOS::Ace {
class PluginSubContainer;
class PluginManagerDelegate;
class DrawDelegate;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class PluginPattern : public Pattern {
    DECLARE_ACE_TYPE(PluginPattern, Pattern);

public:
    PluginPattern() = default;
    ~PluginPattern() override;

    void OnActionEvent(const std::string& action) const;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<PluginLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<PluginEventHub>();
    }

    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;

    void ReplaceAll(std::string& str, const std::string& pattern, const std::string& newPattern);

    std::unique_ptr<DrawDelegate> GetDrawDelegate();

    const RefPtr<PluginSubContainer>& GetPluginSubContainer() const;

    const std::string& GetData() const
    {
        return data_;
    }

    const RequestPluginInfo& GetPluginRequestInfo() const
    {
        return pluginInfo_;
    }

    void FlushReload() const;

private:
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void InitPluginManagerDelegate();
    void CreatePluginSubContainer();

    void FireOnCompleteEvent() const;
    void FireOnErrorEvent(const std::string& code, const std::string& msg);

    bool ISAllowUpdate() const;

    void SplitString(const std::string& str, char tag, std::vector<std::string>& strList) const;
    std::string GetPackagePath(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const;
    std::string GetPackagePathByWant(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const;
    std::string GetPackagePathByAbsolutePath(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const;
    void GetAbilityNameByWant(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const;
    std::string GerPackagePathByBms(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info,
        const std::vector<std::string>& strList, const std::vector<int32_t>& userIds) const;

    RefPtr<PluginSubContainer> pluginSubContainer_;
    RefPtr<PluginManagerDelegate> pluginManagerBridge_;

    std::string data_;
    RequestPluginInfo pluginInfo_;
    bool loadFialState_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(PluginPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_PATTERN_H
