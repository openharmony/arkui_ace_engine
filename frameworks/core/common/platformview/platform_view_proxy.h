/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLATFORM_VIEW_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLATFORM_VIEW_PROXY_H

#include <memory>

#include "base/utils/singleton.h"
#include "core/common/platformview/platform_view.h"

namespace OHOS::Ace {

class PlatformViewProxy : public Singleton<PlatformViewProxy>, public PlatformView {
    DECLARE_SINGLETON(PlatformViewProxy);

public:
    void SetDelegate(std::unique_ptr<PlatformView>&& delegate);

    RefPtr<NG::PlatformViewInterface> Attach(const std::string& id) override;

private:
    std::unique_ptr<PlatformView> delegate_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLATFORM_VIEW_PROXY_H