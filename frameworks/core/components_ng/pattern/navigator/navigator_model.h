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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_MODEL_H

#include <memory>
#include <mutex>
#include <string>

#include "base/utils/macros.h"
#include "core/components/navigator/navigator_component.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT NavigatorModel {
public:
    static NavigatorModel* GetInstance();
    virtual ~NavigatorModel() = default;

    virtual void Create() = 0;
    virtual void SetType(NavigatorType value) = 0;
    virtual void SetActive(bool active) = 0;
    virtual void SetUri(const std::string& uri) = 0;
    virtual void SetParams(const std::string& params) = 0;
    virtual void SetIsDefWidth(bool isDefWidth) = 0;
    virtual void SetIsDefHeight(bool isDefWidth) = 0;

private:
    static std::unique_ptr<NavigatorModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_MODEL_H
