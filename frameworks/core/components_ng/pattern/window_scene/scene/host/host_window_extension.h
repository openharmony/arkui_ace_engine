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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOST_WINDOW_EXTENSION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOST_WINDOW_EXTENSION_H

#include "core/components_ng/pattern/window_scene/scene/host/host_window_pattern.h"

namespace OHOS::Ace::NG {

class HostWindowExtension : public HostWindowPattern {
    DECLARE_ACE_TYPE(HostWindowExtension, HostWindowPattern);

public:
    HostWindowExtension(const sptr<Rosen::Session>& session) : HostWindowPattern(session) {}
    ~HostWindowExtension() override = default;

protected:
    /**
     * Whether this extension has starting page.
     * If true, starting page will show first until the first frame of surface node is drawn.
     * Otherwise, no content will be shown until the first frame of surface node is drawn.
     */
    bool HasStartingPage() override
    {
        return false;
    }

    ACE_DISALLOW_COPY_AND_MOVE(HostWindowExtension);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOST_WINDOW_EXTENSION_H
