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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_SAFE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_SAFE_INFO_H

#include "core/components_ng/base/frame_node.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include <map>
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h"

namespace OHOS::Rosen {
class AvoidArea;
enum class AvoidAreaType : uint32_t;
} // namespace OHOS::Rosen
#endif

namespace OHOS::Ace::NG {
#ifdef WINDOW_SCENE_SUPPORTED
class UIExtensionSafeInfo : public AceType {
    DECLARE_ACE_TYPE(UIExtensionSafeInfo, AceType);
public:
    void SetAvoidArea(const Rosen::AvoidArea& avoidArea, Rosen::AvoidAreaType type);
    std::map<Rosen::AvoidAreaType, Rosen::AvoidArea> GetAvoidArea() const;

private:
    std::map<Rosen::AvoidAreaType, RefPtr<AvoidArea>> avoidAreas_;
};
#endif
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_SAFE_INFO_H
