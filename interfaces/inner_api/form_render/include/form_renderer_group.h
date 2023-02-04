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

#include <unordered_map>
#include <memory>
#include <string>

namespace OHOS {

namespace AbilityRuntime {
class Context;
class Runtime;
}

namespace AAFwk {
class Want;
}

namespace AppExecFwk {
struct FormJsInfo;
}

namespace Ace {

#ifndef ACE_EXPORT
#define ACE_EXPORT __attribute__((visibility("default")))
#endif

class FormRenderer;

/**
 * @class FormRendererGroup
 * FormRendererGroup interface is used to form renderer group.
 * Provider:FormRendererGroup:runtime = 1:1:1
 * FormRendererGroup:FormRenderer = 1:compId
 */
class ACE_EXPORT FormRendererGroup {
public:    
    static std::unique_ptr<FormRendererGroup> Create(const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
                                                     const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime);

    FormRendererGroup(const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
                      const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime);
    ~FormRendererGroup() = default;

    void AddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void UpdateForm(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void DeleteForm(const std::string& compId);

private:
    std::shared_ptr<OHOS::AbilityRuntime::Context> context_;
    std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime_;
    std::unordered_map<std::string, std::shared_ptr<FormRenderer>> rendererMap_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_GROUP_H
