/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_view_inner_modifier.h"

#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/select/select_model.h"

namespace OHOS::Ace::NG {
namespace InnerModifier {
const ArkUIMenuViewInnerModifier* GetMenuViewInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIMenuViewInnerModifier modifier = {
        .createWithOptionParams = NG::MenuView::Create,
        .createWithCustomNode = NG::MenuView::Create,
        .createWithSelectParams = NG::MenuView::Create,
        .removeMenuHoverScaleStatus = NG::MenuView::RemoveMenuHoverScaleStatus,
        .executeMenuDisappearAnimation = NG::MenuView::ExecuteMenuDisappearAnimation,
        .updateMenuNodePosition = NG::MenuView::UpdateMenuNodePosition,
        .updateMenuParam = NG::MenuView::UpdateMenuParam,
        .updateMenuProperties = NG::MenuView::UpdateMenuProperties,
        .getMenuPixelMap = NG::MenuView::GetMenuPixelMap,
        .setMenuHoverScaleStatus = NG::MenuView::SetMenuHoverScaleStatus,
        .getMenuHoverScaleStatus = NG::MenuView::GetMenuHoverScaleStatus,
        .setMenuSystemMaterial = NG::MenuView::SetMenuSystemMaterial,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

} // namespace InnerModifier
} // namespace OHOS::Ace::NG