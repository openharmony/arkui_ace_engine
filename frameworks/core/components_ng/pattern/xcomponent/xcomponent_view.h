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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/xcomponent/xcomponent_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT XComponentView {
public:
    static void Create(const std::string& id, const std::string& type, const std::string& libraryname,
        const RefPtr<XComponentController>& xcomponentController);
    static void SetOnLoad(LoadEvent&& onLoad);
    static void SetOnDestroy(DestroyEvent&& onDestroy);
    static void SetOnSurfaceDestroyEvent(DestroyEvent&& onSurfaceDestroyEvent);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_VIEW_H
