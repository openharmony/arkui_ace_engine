/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "compatible/components/refresh/render_refresh.h"
#include "core/components/refresh/render_refresh_target.h"

namespace OHOS::Ace::RefreshModifier {
namespace {
void UpdateScrollableOffset(RefPtr<RenderNode> refresh, double delta)
{
    auto renderRefresh = reinterpret_cast<RenderRefresh*>(AceType::RawPtr(refresh));
    renderRefresh->UpdateScrollableOffset(delta);
}
void HandleDragEnd(RefPtr<RenderNode> refresh)
{
    auto renderRefresh = reinterpret_cast<RenderRefresh*>(AceType::RawPtr(refresh));
    renderRefresh->HandleDragEnd();
}
void HandleDragCancel(RefPtr<RenderNode> refresh)
{
    auto renderRefresh = reinterpret_cast<RenderRefresh*>(AceType::RawPtr(refresh));
    renderRefresh->HandleDragCancel();
}
    
}
const ArkUIRefreshModifierCompatible* GetRefreshModifier()
{
    static const ArkUIRefreshModifierCompatible instance = {
        .updateScrollableOffset = UpdateScrollableOffset,
        .handleDragEnd = HandleDragEnd,
        .handleDragCancel = HandleDragCancel,
    };
    return &instance;
}
} // OHOS::Ace::RefreshModifier