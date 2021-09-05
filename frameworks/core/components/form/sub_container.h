/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_SUB_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_SUB_CONTAINER_H

#include "base/thread/task_executor.h"
#include "frameworks/bridge/card_frontend/card_frontend.h"
#include "frameworks/core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
class ACE_EXPORT SubContainer : public virtual AceType {
    DECLARE_ACE_TYPE(SubContainer, AceType);

public:
    using OnFormAcquiredCallback = std::function<void(const size_t)>;

    SubContainer(const WeakPtr<PipelineContext>& context) : outSidePipelineContext_(context) {}
    ~SubContainer() = default;

    void Initialize();
    void RunCard(const int64_t id, const std::string path, const std::string module, const std::string data);
    void UpdateCard(const std::string content);
    void Destroy();

    void SetStageElement(const RefPtr<Element>& stage)
    {
        stageElement_ = stage;
        frontend_->SetPageParentElement(stageElement_);
    }

    void SetFormElement(const WeakPtr<Element>& element)
    {
        formElement_ = element;
    }

    const WeakPtr<Element> GetFormElement() const
    {
        return formElement_;
    }

    void SetFormComponet(const RefPtr<Component>& mountPoint)
    {
        formComponent_ = mountPoint;
    }

    void SetRootElementScale(double scale)
    {
        scale_ = scale;
    }

    double GetRootElementScale() const
    {
        return scale_;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const
    {
        return taskExecutor_;
    }

    RefPtr<PipelineContext> GetPipelineContext() const
    {
        return pipelineContext_;
    }

    void AddFormAcquireCallback(const OnFormAcquiredCallback& callback)
    {
        if (callback) {
            onFormAcquiredCallback_ = callback;
        }
    }

    void SetAllowUpdate(bool update)
    {
        allowUpdate_ = update;
    }

    int64_t GetRunningCardId() const
    {
        return runningCardId_;
    }

private:
    RefPtr<CardFrontend> frontend_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<TaskExecutor> subTaskExecutor_;
    RefPtr<PipelineContext> pipelineContext_;
    WeakPtr<PipelineContext> outSidePipelineContext_;
    RefPtr<AssetManager> assetManager_;

    int64_t runningCardId_ = 0;
    double scale_ = 1.0f;

    bool allowUpdate_ = true;

    RefPtr<Element> stageElement_;
    RefPtr<Component> formComponent_;
    WeakPtr<Element> formElement_;
    OnFormAcquiredCallback onFormAcquiredCallback_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_SUB_CONTAINER_H
