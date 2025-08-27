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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_GROUP_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_GROUP_H

#include <memory>
#include <string>
#include <vector>

#include "form_js_info.h"
#include "want.h"
#include "event_handler.h"

namespace OHOS {
namespace AbilityRuntime {
class Context;
class Runtime;
}

namespace AppExecFwk {
class Configuration;
class EventHandler;
}

namespace Ace {
#ifndef ACE_EXPORT
#define ACE_EXPORT __attribute__((visibility("default")))
#endif

class FormRenderer;

struct FormRequest {
    std::string compId;
    OHOS::AAFwk::Want want;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    bool isDynamic = true;
    bool hasRelease = false;
    bool operator() (const FormRequest& info) const
    {
        return compId == info.compId && formJsInfo.formId == info.formJsInfo.formId;
    }
};

/**
 * @class FormRendererGroup
 * FormRendererGroup interface is used to form renderer group.
 * Provider:FormRendererGroup:runtime = 1:1:1
 * FormRendererGroup:FormRenderer = 1:1
 */
class ACE_EXPORT FormRendererGroup {
public:
    static std::shared_ptr<FormRendererGroup> Create(const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
                                                     const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime,
                                                     std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler);

    FormRendererGroup(const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
                      const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime,
                      std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler);
    ~FormRendererGroup();

    void AddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void OnUnlock();
    void SetVisibleChange(bool isVisible);
    void UpdateForm(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void DeleteForm();
    void DeleteForm(const std::string& compId);
    void ReloadForm(const AppExecFwk::FormJsInfo& formJsInfo);
    void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config);
    bool IsFormRequestsEmpty();
    const std::vector<FormRequest>& GetAllRendererFormRequests() const;
    std::pair<std::vector<std::string>, std::string> GetOrderedAndCurrentCompIds() const;
    void RecycleForm(std::string& statusData) const;
    void RecoverRenderer(const std::vector<FormRequest>& formRequests, size_t currentCompIndex);
    void UpdateFormSizeOfFormRequests(double width, double height, float borderWidth);
    bool IsManagerDelegateValid(const OHOS::AAFwk::Want& want);
private:
    enum class FormRendererInitState {
        UNINITIALIZED,
        PRE_INITIALIZED,
        INITIALIZED
    };
    void InnerAddForm(const FormRequest& formRequest);
    void PreInitAddForm(const FormRequest& formRequest);
    std::shared_ptr<OHOS::AbilityRuntime::Context> context_;
    std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime_;
    std::shared_ptr<FormRenderer> formRenderer_;
    std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler_;
    std::vector<FormRequest> formRequests_;
    std::string currentCompId_;
    FormRendererInitState initState_ = FormRendererInitState::UNINITIALIZED;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_GROUP_H
