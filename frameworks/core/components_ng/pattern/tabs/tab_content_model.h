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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_MODEL_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace {

class TabContentModel {
public:
    static TabContentModel* GetInstance();
    virtual ~TabContentModel() = default;

    virtual void Create() = 0;
    virtual void Create(std::function<void()>&& deepRenderFunc) = 0;
    virtual void Pop() = 0;
    virtual void SetTabBar(const std::optional<std::string>& text, const std::optional<std::string>& icon,
        std::function<void()>&& builder, bool useContentOnly) = 0;

private:
    static std::unique_ptr<TabContentModel> instance_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_MODEL_H
