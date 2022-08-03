/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_DIALOG_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_DIALOG_IMPL_H

#include "interfaces/inner_api/ace/ui_dialog_base.h"

#include "ability.h"
#include "resource_manager.h"

#include "base/utils/macros.h"
namespace OHOS::Ace {
class ACE_EXPORT UIDialogImpl : public UIDialogBase {
public:
    UIDialogImpl() = default;
    ~UIDialogImpl() override = default;

    // show system dialog
    virtual void ShowDialog(
        const std::string& name,
        const std::string& params,
        uint32_t windowType,
        int x,
        int y,
        int width,
        int height,
        const std::function<void(int32_t, const std::string&, const std::string&)>& dialogCallback,
        int32_t dialogId) override;

    // update system dialog
    virtual void UpdateDialog(int id, const std::string& data) override;

    // cancel system dialog
    virtual void CancelDialog(int32_t id, const std::function<void()>& destroyCallback) override;
private:
    std::shared_ptr<OHOS::AppExecFwk::Ability> CreateAbility();
    void InitResourceManager();

    std::shared_ptr<Global::Resource::ResourceManager> resourceManager_;
    std::unordered_map<int32_t, std::shared_ptr<OHOS::AppExecFwk::Ability>> abilityMaps_;
    float density_ = 2.0f;
};
}
#endif