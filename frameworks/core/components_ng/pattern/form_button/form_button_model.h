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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FORM_BUTTON_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FORM_BUTTON_MODEL_H

#include <memory>
#include <mutex>

#include "core/components/common/properties/alignment.h"
#include "core/components/form/resource/form_request_data.h"

namespace OHOS::Ace {
class FormButtonModel {
public:
    static FormButtonModel* GetInstance();
    virtual ~FormButtonModel() = default;

    virtual void Create(const std::string& action, const RequestFormInfo& info) = 0;
    virtual void Create(Alignment align, const std::string& action, const RequestFormInfo& info) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FORM_BUTTON_MODEL_H