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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_GLOBAL_PIPELINE_CONTEXT_MANAGER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_GLOBAL_PIPELINE_CONTEXT_MANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "wm/window.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/thread_model_impl.h"
#include "core/common/window.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
class WindowLifeCycle : public Rosen::IWindowLifeCycle {
public:
    explicit WindowLifeCycle(const std::string& name) : name_(name) {};
    ~WindowLifeCycle() override = default;

    void AfterDestroyed() override;

private:
    std::string name_;
};

class GlobalPipelineContextManager final : public AceType {
    DECLARE_ACE_TYPE(GlobalPipelineContextManager, AceType);

public:
    ~GlobalPipelineContextManager() override = default;

    static GlobalPipelineContextManager* GetInstance();

    RefPtr<NG::PipelineContext> GetGlobalPipelineContext(const std::string& name) const;

    RefPtr<NG::PipelineContext> CreateGlobalPipelineContext(const std::string& name,
        const sptr<OHOS::Rosen::Window>& rsWindow, FrontendType frontendType, int32_t instanceId);

    RefPtr<NG::PipelineContext> RemoveGlobalPipelineContext(const std::string& name);

    RefPtr<NG::FrameNode> RemoveModalPageNode(const std::string& name);

    RefPtr<NG::FrameNode> GetModalPageNode(const std::string& name);

    void ProcessModalPageNode(const std::string& name, int32_t instanceId);

    void RegisterSessionId(const std::string& name, int32_t sessionId);

    int32_t GetSessionId(const std::string& name);

    void RemoveSessionId(const std::string& name);

    std::string GetUecNameBySessionId(int32_t sessionId);

private:
    GlobalPipelineContextManager();

    void AddGlobalPipelineContext(const std::string& name, const RefPtr<NG::PipelineContext>& pipelineContext);

    std::unordered_map<std::string, RefPtr<NG::PipelineContext>> globalContextMap_;
    std::unordered_map<std::string, RefPtr<NG::FrameNode>> modalPageMap_;
    std::unordered_map<std::string, int32_t> sessionIdMap_;

    std::unique_ptr<ThreadModelImpl> threadModelImpl_ = nullptr;
};
} // namespace OHOS::Ace

#endif
