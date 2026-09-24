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

#include "core/components_ng/pattern/ui_extension/ui_extension_safe_info.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h"
#include "wm/occupied_area_change_info.h"

namespace OHOS::Ace::NG {
namespace {
void ConvertAvoidArea2AvoidRect(const Rosen::Rect& rect, AvoidRect& avoidRect)
{
    avoidRect = { rect.posX_, rect.posY_, rect.width_, rect.height_ };
}

void ConvertAvoidRect2AvoidArea(const AvoidRect& avoidRect, Rosen::Rect& rect)
{
    rect = { avoidRect.posX_, avoidRect.posY_, avoidRect.width_, avoidRect.height_ };
}
}

void UIExtensionSafeInfo::SetAvoidArea(const Rosen::AvoidArea& avoidArea, Rosen::AvoidAreaType type)
{
    RefPtr<AvoidArea> avoidAreaPtr = AceType::MakeRefPtr<AvoidArea>();
    ConvertAvoidArea2AvoidRect(avoidArea.topRect_, avoidAreaPtr->topRect_);
    ConvertAvoidArea2AvoidRect(avoidArea.leftRect_, avoidAreaPtr->leftRect_);
    ConvertAvoidArea2AvoidRect(avoidArea.rightRect_, avoidAreaPtr->rightRect_);
    ConvertAvoidArea2AvoidRect(avoidArea.bottomRect_, avoidAreaPtr->bottomRect_);
    avoidAreas_[type] = avoidAreaPtr;
}

std::map<Rosen::AvoidAreaType, Rosen::AvoidArea> UIExtensionSafeInfo::GetAvoidArea() const
{
    std::map<Rosen::AvoidAreaType, Rosen::AvoidArea> avoidAreas;
    for (const auto& pair : avoidAreas_) {
        const Rosen::AvoidAreaType& type = pair.first;
        const RefPtr<AvoidArea>& avoidAreaPtr = pair.second;
        Rosen::AvoidArea avoidArea;
        ConvertAvoidRect2AvoidArea(avoidAreaPtr->topRect_, avoidArea.topRect_);
        ConvertAvoidRect2AvoidArea(avoidAreaPtr->leftRect_, avoidArea.leftRect_);
        ConvertAvoidRect2AvoidArea(avoidAreaPtr->rightRect_, avoidArea.rightRect_);
        ConvertAvoidRect2AvoidArea(avoidAreaPtr->bottomRect_, avoidArea.bottomRect_);
        avoidAreas.emplace(type, avoidArea);
    }
    return avoidAreas;
}
} // namespace OHOS::Ace::NG
#endif
