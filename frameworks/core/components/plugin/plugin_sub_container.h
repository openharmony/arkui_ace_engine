/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_SUB_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_SUB_CONTAINER_H

#include "base/thread/task_executor.h"
#include "bridge/plugin_frontend/plugin_frontend.h"
#include "core/components_ng/pattern/plugin/plugin_node.h"
#include "core/components_ng/pattern/plugin/plugin_pattern.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
class ACE_EXPORT PluginSubContainer : public virtual AceType {
    DECLARE_ACE_TYPE(PluginSubContainer, AceType);

public:
    using OnPluginAcquiredCallback = std::function<void(const size_t)>;
    using onPluginUpdateWithValueParams = std::function<void(const std::string&)>;

    explicit PluginSubContainer(const WeakPtr<PipelineBase>& context) : outSidePipelineContext_(context) {}
    PluginSubContainer(const WeakPtr<PipelineBase>& context, int32_t instanceId)
        : outSidePipelineContext_(context), instanceId_(instanceId)
    {}
    ~PluginSubContainer() = default;

    void Initialize(const std::string& codeLanguage);
    void RunPlugin(const std::string& path, const std::string& module, const std::string& source,
        const std::string& moduleResPath, const std::string& data);
    void RunDecompressedPlugin(const std::string& path, const std::string& module, const std::string& source,
        const std::string& moduleResPath, const std::string& data);
    void UpdatePlugin(const std::string& content);
    void Destroy();

    void SetPluginElement(const WeakPtr<Element>& element)
    {
        pluginElement_ = element;
    }

    const WeakPtr<Element> GetPluginElement() const
    {
        return pluginElement_;
    }

    void SetPluginComponent(const RefPtr<Component>& mountPoint)
    {
        pluginComponent_ = mountPoint;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const
    {
        return taskExecutor_;
    }

    RefPtr<PipelineBase> GetPipelineContext() const
    {
        return pipelineContext_;
    }

    void UpdateRootElementSize();
    void UpdateSurfaceSize();

    void AddPluginAcquireCallback(const OnPluginAcquiredCallback& callback)
    {
        if (callback) {
            onPluginAcquiredCallback_ = callback;
        }
    }

    void SetAllowUpdate(bool update)
    {
        allowUpdate_ = update;
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    void SetPluginPattern(const WeakPtr<NG::PluginPattern>& pluginPattern)
    {
        pluginPattern_ = pluginPattern;
    }

    RefPtr<NG::PluginPattern> GetPluginPattern() const
    {
        return pluginPattern_.Upgrade();
    }

    void SetPluginNode(const WeakPtr<NG::FrameNode>& pluginNode)
    {
        pluginNode_ = pluginNode;
    }

    WeakPtr<NG::FrameNode> GetPluginNode() const
    {
        return pluginNode_;
    }

    void FlushReload() const
    {
        auto pattern = pluginPattern_.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FlushReload();
    }

    void SetDeclarativeOnUpdateWithValueParamsCallback(onPluginUpdateWithValueParams&& callback)
    {
        if (frontend_) {
            frontend_->SetDeclarativeOnUpdateWithValueParamsCallback(std::move(callback));
        }
    }

    void SetPluginBundleName(const std::string& pluginBundleName)
    {
        if (frontend_) {
            frontend_->SetPluginBundleName(pluginBundleName);
        }
    }

    void SetPluginModuleName(const std::string& pluginModuleName)
    {
        if (frontend_) {
            frontend_->SetPluginModuleName(pluginModuleName);
        }
    }

    void SetPluginWindowId(const int32_t pluginWindowId)
    {
        pluginWindowId_ = pluginWindowId;
    }

private:
    void SetPluginComponentTheme(const std::string& path, const RefPtr<AssetManager>& assetManager);
    void SetActionEventHandler();
    RefPtr<AssetManager> SetAssetManager(const std::string& path, const std::string& module);
    RefPtr<AssetManager> GetDecompressedAssetManager(const std::string& path, const std::string& module);

private:
    RefPtr<PluginFrontend> frontend_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<PipelineBase> pipelineContext_;
    WeakPtr<PipelineBase> outSidePipelineContext_;
    RefPtr<AssetManager> assetManager_;

    int32_t instanceId_ = 0;
    int32_t pluginWindowId_ = -1;

    bool allowUpdate_ = true;

    RefPtr<Component> pluginComponent_;
    WeakPtr<Element> pluginElement_;

    double surfaceWidth_ = 1.0f;
    double surfaceHeight_ = 1.0f;
    Dimension rootWidth_ = 0.0_vp;
    Dimension rootHeight_ = 0.0_vp;
    double density_ = 1.0f;

    // Use for NG.
    OnPluginAcquiredCallback onPluginAcquiredCallback_;
    onPluginUpdateWithValueParams onUpdateWithValueParams_;
    WeakPtr<NG::PluginPattern> pluginPattern_;
    WeakPtr<NG::FrameNode> pluginNode_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_SUB_CONTAINER_H
