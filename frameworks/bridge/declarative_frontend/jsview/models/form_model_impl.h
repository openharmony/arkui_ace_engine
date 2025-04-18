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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FORM_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FORM_MODEL_IMPL_H

#include "core/components_ng/pattern/form/form_model.h"

namespace OHOS::Ace::Framework {
class FormModelImpl : public OHOS::Ace::FormModel {
public:
    void Create(const RequestFormInfo& info) override;
    void SetSize(const Dimension& width, const Dimension& height) override;
    void SetDimension(int32_t value) override;
    void AllowUpdate(bool value) override;
    void SetModuleName(const std::string& value) override;
    void SetOnAcquired(std::function<void(const std::string&)>&& onAcquired) override;
    void SetOnError(std::function<void(const std::string&)>&& onError) override;
    void SetOnUninstall(std::function<void(const std::string&)>&& onUninstall) override;
    void SetOnRouter(std::function<void(const std::string&)>&& onRouter) override;
    void SetOnLoad(std::function<void(const std::string&)>&& onLoad) override;
    void SetOnUpdate(std::function<void(const std::string&)>&& onUpdate) override;
    void SetVisible(VisibleType visible) override;
    void SetVisibility(VisibleType visible) override;
    void SetObscured(const std::vector<ObscuredReasons>& reasons) override;
    int32_t RequestPublishFormWithSnapshot(const AAFwk::Want& want,
        const std::string& formBindingDataStr, int64_t& formId, std::string &errMsg) override;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FORM_MODEL_IMPL_H
