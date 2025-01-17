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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_SCROLL_BAR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_SCROLL_BAR_MODEL_H

#include <mutex>

#include "base/memory/referenced.h"
#include "core/components/scroll_bar/scroll_bar_component.h"
#include "core/components/scroll_bar/scroll_bar_proxy.h"
#include "core/components/scroll_bar/scroll_proxy.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT ScrollBarModel {
public:
    static ScrollBarModel* GetInstance();
    virtual ~ScrollBarModel() = default;

    virtual RefPtr<ScrollProxy> GetScrollBarProxy(const RefPtr<ScrollProxy>& scrollProxy) = 0;
    virtual void Create(const RefPtr<ScrollProxy>& proxy, bool infoflag, bool proxyFlag,
        int directionValue, int stateValue) = 0;
    virtual void SetEnableNestedScroll(bool enableNestedSroll) = 0;
private:
    static std::unique_ptr<ScrollBarModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_SCROLL_BAR_MODEL_H
