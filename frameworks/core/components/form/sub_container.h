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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_SUB_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_SUB_CONTAINER_H

#ifndef ARKUI_CAPI_UNITTEST
#include "ashmem.h"
#include "form_ashmem.h"
#endif // ARKUI_CAPI_UNITTEST

#include "base/thread/task_executor.h"
#include "core/common/frontend.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "frameworks/bridge/card_frontend/card_frontend.h"
#include "frameworks/bridge/card_frontend/card_frontend_declarative.h"
#include "frameworks/core/pipeline/pipeline_context.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

#ifdef ARKUI_CAPI_UNITTEST
namespace OHOS {
class Ashmem;
template<typename T>
class sptr;
namespace AppExecFwk {
class FormAshmem;
}
} // namespace OHOS::Ace
#endif // ARKUI_CAPI_UNITTEST

namespace OHOS::Ace {
class ACE_EXPORT SubContainer : public virtual AceType {
    DECLARE_ACE_TYPE(SubContainer, AceType);

public:
    using OnFormAcquiredCallback = std::function<void(const int64_t)>;
    using OnFormLoadCallback = std::function<void()>;
    using OnFormVisibleCallback = std::function<void()>;

    explicit SubContainer(const WeakPtr<PipelineBase>& context) : outSidePipelineContext_(context) {}
    SubContainer(const WeakPtr<PipelineBase>& context, int32_t instanceId)
        : outSidePipelineContext_(context), instanceId_(instanceId)
    {}
    ~SubContainer();

    void Initialize();
    void RunCard(int64_t formId, const std::string& path, const std::string& module, const std::string& data,
        const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap, const std::string& formSrc,
        const FrontendType& cardType, const FrontendType& uiSyntax);
    void RunSameCard();
    void UpdateCard(
        const std::string& content, const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap);
    void Destroy();
    void GetNamesOfSharedImage(std::vector<std::string>& picNameArray);
    void UpdateSharedImage(std::vector<std::string>& picNameArray, std::vector<int32_t>& byteLenArray,
        std::vector<int32_t>& fileDescriptorArray);
    void GetImageDataFromAshmem(
        const std::string& picName, Ashmem& ashmem, const RefPtr<PipelineBase>& pipelineContext, int len);
    void ProcessSharedImage(const std::map<std::string, sptr<AppExecFwk::FormAshmem>> imageDataMap);

    void SetFormElement(const WeakPtr<Element>& element)
    {
        formElement_ = element;
    }

    const WeakPtr<Element> GetFormElement() const
    {
        return formElement_;
    }

    void SetFormComponent(const RefPtr<Component>& mountPoint)
    {
        formComponent_ = mountPoint;
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
    void UpdateSurfaceSizeWithAnimathion();
    void UpdateConfiguration();
    void AddFormAcquireCallback(const OnFormAcquiredCallback& callback)
    {
        if (callback) {
            onFormAcquiredCallback_ = callback;
        }
    }

    void AddFormVisiableCallback(OnFormVisibleCallback&& callback)
    {
        onFormVisibleCallback_ = std::move(callback);
    }

    void SetAllowUpdate(bool update)
    {
        allowUpdate_ = update;
    }

    int64_t GetRunningCardId() const
    {
        return runningCardId_;
    }
    bool Dump(const std::vector<std::string>& params);

    WindowConfig GetWindowConfig() const
    {
        return cardWindowConfig_;
    }

    void SetWindowConfig(const WindowConfig cardWindowConfig)
    {
        cardWindowConfig_ = cardWindowConfig;
    }

    void SetFormPattern(const WeakPtr<NG::FormPattern>& formPattern)
    {
        formPattern_ = formPattern;
    }

    RefPtr<NG::FormPattern> GetFormPattern() const
    {
        return formPattern_.Upgrade();
    }

    FrontendType GetCardType() const
    {
        return cardType_;
    }

    FrontendType GetUISyntaxType() const
    {
        return uiSyntax_;
    }

    void SetNodeId(int32_t nodeId)
    {
        nodeId_ = static_cast<int64_t>(nodeId);
    }

    void SetFormLoadCallback(const OnFormLoadCallback&& callback)
    {
        onFormLoadCallback_ = std::move(callback);
    }

    int64_t GetNodeId() const
    {
        return nodeId_;
    }

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

private:
    void InitFrontend(const std::string &path, const std::string &module,
        const std::map<std::string, sptr<AppExecFwk::FormAshmem>> &imageDataMap,
        const std::string& formSrc,
        const FrontendType &cardType);
    void InitCardThemeManager(const std::string &path, int32_t instanceId, const std::string &module,
        const std::map<std::string, sptr<AppExecFwk::FormAshmem>> &imageDataMap, RefPtr<AssetManager> assetManager);
    RefPtr<AssetManager> GetAssetManager(const std::string& path, const std::string& module);
    void InitPipelineContext();
    void RunJSCard(const std::string& data);
    RefPtr<CardFrontend> frontend_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<PipelineBase> pipelineContext_;
    WeakPtr<PipelineBase> outSidePipelineContext_;
    RefPtr<AssetManager> assetManager_;
    int32_t instanceId_;

    int64_t runningCardId_ = 0;
    int64_t windowId_ = -1;

    bool allowUpdate_ = true;

    FrontendType cardType_ = FrontendType::JS_CARD;
    FrontendType uiSyntax_ = FrontendType::JS_CARD;

    RefPtr<Component> formComponent_;
    WeakPtr<Element> formElement_;
    OnFormAcquiredCallback onFormAcquiredCallback_;

    OnFormLoadCallback onFormLoadCallback_;
    OnFormVisibleCallback onFormVisibleCallback_;
    WindowConfig cardWindowConfig_;

    double surfaceWidth_ = 1.0f;
    double surfaceHeight_ = 1.0f;
    Dimension rootWidht_ = 0.0_vp;
    Dimension rootHeight_ = 0.0_vp;
    double density_ = 1.0f;

    // Use for NG.
    WeakPtr<NG::FormPattern> formPattern_;
    int64_t nodeId_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_SUB_CONTAINER_H
