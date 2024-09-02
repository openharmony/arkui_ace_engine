/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FORM_FORM_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FORM_FORM_MODEL_H

#include <mutex>

#include "core/components/form/resource/form_request_data.h"
#include "core/components_ng/pattern/form/form_event_hub.h"

namespace OHOS::Ace {
class FormModel {
public:
    static FormModel* GetInstance();
    virtual ~FormModel() = default;

    virtual void Create(const RequestFormInfo& info) = 0;
    virtual void SetDimension(int32_t value) = 0;
    virtual void SetSize(const Dimension& width, const Dimension& height) = 0;
    virtual void AllowUpdate(bool value) = 0;
    virtual void SetModuleName(const std::string& value) = 0;
    virtual void SetOnAcquired(std::function<void(const std::string&)>&& onAcquired) = 0;
    virtual void SetOnError(std::function<void(const std::string&)>&& onError) = 0;
    virtual void SetOnUninstall(std::function<void(const std::string&)>&& onUninstall) = 0;
    virtual void SetOnRouter(std::function<void(const std::string&)>&& onRouter) = 0;
    virtual void SetOnLoad(std::function<void(const std::string&)>&& onLoad) = 0;
    virtual void SetVisible(VisibleType visible) = 0;
    virtual void SetVisibility(VisibleType visible) = 0;
    virtual void SetObscured(const std::vector<ObscuredReasons>& reasons) = 0;
    virtual int32_t RequestPublishFormWithSnapshot(const AAFwk::Want& want,
        const std::string& formBindingDataStr, int64_t& formId, std::string &errMsg) = 0;

private:
    static std::unique_ptr<FormModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FORM_FORM_MODEL_H
