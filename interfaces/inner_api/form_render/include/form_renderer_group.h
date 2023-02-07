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

#include <map>

#include "form_renderer.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormRendererGroup
 * FormRendererGroup interface is used to form renderer group.
 */
class FormRendererGroup {
public:
    FormRendererGroup() = default;
    ~FormRendererGroup() = default;
    
    void AddForm();
    void UpdateForm();

private:
    std::map<std::string, std::shared_ptr<FormRenderer>> rendererMap_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_GROUP_H
