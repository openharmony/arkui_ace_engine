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
 
#include "core/components_ng/pattern/menu/menu_view_static.h"
 
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_row_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/menu_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components/button/button_theme.h"
#include "frameworks/base/utils/measure_util.h"
 
namespace OHOS::Ace::NG {
 
/**
 * The structure of menu is designed as follows :
 * |--menuWrapper(size is same as root)
 *   |--menu
 *      |--scroll
 *          |--column(for bindMenu/select)
 *            |--options
 *          |--customNode(for custom builder)
 */
 
namespace {
const RefPtr<Curve> CUSTOM_PREVIEW_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 380.0f, 34.0f);
const std::string HOVER_IMAGE_CLIP_PROPERTY_NAME = "hoverImageClip";
} // namespace
 
thread_local std::unordered_map<int32_t, MenuHoverScaleStatus> menuHoverStatusStatic_;
 
void MenuViewStatic::SetMenuHoverScaleStatus(int32_t targetId, MenuHoverScaleStatus status)
{
    menuHoverStatusStatic_[targetId] = status;
}
 
void MenuViewStatic::RemoveMenuHoverScaleStatus(int32_t targetId)
{
    menuHoverStatusStatic_.erase(targetId);
}
 
MenuHoverScaleStatus MenuViewStatic::GetMenuHoverScaleStatus(int32_t targetId)
{
    auto result = menuHoverStatusStatic_.find(targetId);
    return result != menuHoverStatusStatic_.end() ? result->second : MenuHoverScaleStatus::NONE;
}
} // namespace OHOS::Ace::NG