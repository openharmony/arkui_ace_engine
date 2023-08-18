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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVDESTINATION_NAVDESTINATION_MODEL_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVDESTINATION_NAVDESTINATION_MODEL_H

#include <mutex>

#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace {
class NavDestinationModel {
public:
    static NavDestinationModel* GetInstance();
    virtual ~NavDestinationModel() = default;

    virtual void Create() = 0;
    virtual void Create(std::function<void()>&& deepRenderFunc) = 0;
    virtual void SetHideTitleBar(bool hideTitleBar) = 0;
    virtual void SetTitle(const std::string& title, bool hasSubTitle) = 0;
    virtual void SetSubtitle(const std::string& subtitle) = 0;
    virtual void SetCustomTitle(const RefPtr<AceType>& customNode) = 0;
    virtual void SetTitleHeight(int32_t height) = 0;
    virtual void SetTitleHeight(const Dimension& titleHeight) = 0;
    virtual void SetOnShown(std::function<void()>&& onShow) = 0;
    virtual void SetOnHidden(std::function<void()>&& onHidden) = 0;
    virtual void SetOnBackPressed(std::function<bool()>&& onBackPressed) = 0;
    virtual RefPtr<AceType> CreateEmpty()
    {
        return nullptr;
    }

private:
    static std::unique_ptr<NavDestinationModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVDESTINATION_NAVDESTINATION_MODEL_H
