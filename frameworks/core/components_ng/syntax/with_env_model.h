/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_ENV_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_ENV_MODEL_H

#include <any>
#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

enum class TextDirection;

class ACE_FORCE_EXPORT WithEnvModel {
public:
    static WithEnvModel* GetInstance();
    virtual ~WithEnvModel() = default;

    virtual void Create() = 0;
    virtual void RemoveSystemEnvProperty(const std::string& key) = 0;
    virtual void SetSystemEnvProperty(const std::string& key, TextDirection value) = 0;
    virtual void SetSystemEnvProperty(const std::string& key, double value) = 0;
    virtual void RemoveCustomEnvProperty(const std::string& key) = 0;
    virtual void SetCustomEnvProperty(const std::string& key, std::any value) = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_ENV_MODEL_H
