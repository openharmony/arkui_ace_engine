/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_H

#include <mutex>
#include <set>

#include "core/components/xcomponent/xcomponent_controller.h"

namespace OHOS::Ace {
using LoadEvent = std::function<void(const std::string&)>;
using DestroyEvent = std::function<void()>;
class XComponentModel {
public:
    static XComponentModel* GetInstance();
    virtual ~XComponentModel() = default;

    virtual void Create(const std::string& id, XComponentType type, const std::string& libraryname,
        const RefPtr<XComponentController>& xcomponentController) = 0;
    virtual void SetSoPath(const std::string& soPath) = 0;
    virtual void SetOnLoad(LoadEvent&& onLoad) = 0;
    virtual void SetOnDestroy(DestroyEvent&& onDestroy) = 0;
    virtual bool IsTexture()
    {
        return false;
    }

private:
    static std::unique_ptr<XComponentModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_H
