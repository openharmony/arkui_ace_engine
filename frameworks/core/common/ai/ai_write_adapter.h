/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AI_WRITE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AI_WRITE_H

#include <functional>
#include <string>

#include "base/memory/ace_type.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "interfaces/inner_api/ace/modal_ui_extension_config.h"

namespace OHOS::AAFwk {
class Want;
class WantParams;
} // namespace OHOS::AAFwk

namespace OHOS::Ace {
struct AIWriteInfo {
    // The position relative to the beginning and end of all text.
    int32_t selectStart = 0;
    int32_t selectEnd = 0;
    int32_t selectLength = -1;
    int32_t maxLength = -1;
    // The beginning and end positions relative to the sentence-level text.
    int32_t start = 0;
    int32_t end = 0;

    std::string componentType;
    std::string firstHandle;
    std::string secondHandle;
    PlatformVersion apiVersion = PlatformVersion::VERSION_THIRTEEN;
    std::vector<uint8_t> selectBuffer;
    std::vector<uint8_t> sentenceBuffer;
};

class AIWriteAdapter : public AceType {
    DECLARE_ACE_TYPE(AIWriteAdapter, AceType);

public:
    AIWriteAdapter() = default;
    ~AIWriteAdapter() override = default;

    bool IsSentenceBoundary(const wchar_t value);
    void CloseModalUIExtension();
    void ShowModalUIExtension(const AIWriteInfo& info,
        std::function<void(std::vector<uint8_t>&)> resultCallback);
    std::vector<uint8_t> GetBufferParam(const std::string& key, const AAFwk::WantParams& wantParams);
    bool GetBoolParam(const std::string& key, const AAFwk::WantParams& wantParams);
    uint32_t GetSelectLengthOnlyText(const std::wstring& content);
    void SetPipelineContext(const WeakPtr<NG::PipelineContext>& pipelineContext)
    {
        pipelineContext_ = pipelineContext;
    }
    WeakPtr<NG::PipelineContext> GetPipelineContext() const
    {
        return pipelineContext_;
    }
    void SetBundleName(const std::string& bundleName)
    {
        bundleName_ = bundleName;
    }
    void SetAbilityName(const std::string& abilityName)
    {
        abilityName_ = abilityName;
    }
    const std::string& GetBundleName() const
    {
        return bundleName_;
    }
    const std::string& GetAbilityName() const
    {
        return abilityName_;
    }
    void SetAIWrite(const bool clickAIWrite)
    {
        clickAIWrite_ = clickAIWrite;
    }
    bool GetAIWrite()
    {
        return clickAIWrite_;
    }
private:
    void SetWantParams(const AIWriteInfo& info, AAFwk::Want& want);
    void SendData();
    void SetArrayParam(AAFwk::WantParams& wantParams, const std::string& key, const std::vector<uint8_t>& value);
    void BindModalUIExtensionCallback(
        Ace::ModalUIExtensionCallbacks& callbacks, std::function<void(std::vector<uint8_t>&)> resultCallback);
    void SetModalUIExtensionProxy(const std::shared_ptr<Ace::ModalUIExtensionProxy>& proxy)
    {
        modalUIExtensionProxy_ = proxy;
    }
    std::shared_ptr<Ace::ModalUIExtensionProxy> GetModalUIExtensionProxy()
    {
        return modalUIExtensionProxy_;
    }
    int32_t sessionId_ = -1;
    std::string bundleName_;
    std::string abilityName_;
    WeakPtr<NG::PipelineContext> pipelineContext_;
    bool clickAIWrite_ = false;
    AIWriteInfo aiWriteInfo_;
    std::shared_ptr<Ace::ModalUIExtensionProxy> modalUIExtensionProxy_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AI_WRITE_H