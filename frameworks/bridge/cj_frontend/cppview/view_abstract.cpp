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
#include "view_abstract.h"

#include <regex>

#include "base/geometry/animatable_dimension.h"
#include "base/json/json_util.h"
#include "base/memory/referenced.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/components/box/box_component_helper.h"
#include "core/components/common/layout/align_declaration.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/motion_path_option.h"
#include "core/components/display/display_component.h"
#include "core/components/option/option_component.h"
#include "core/components/split_container/column_split_component.h"
#include "core/components/split_container/row_split_component.h"
#include "core/components/split_container/split_container_component.h"
#include "core/components/text/text_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/extensions/events/on_area_change_extension.h"
#include "core/gestures/long_press_gesture.h"

namespace OHOS::Ace::Framework {
RefPtr<ThemeConstants> ViewAbstract::GetThemeConstants()
{
    auto currentObj = Container::Current();
    if (!currentObj) {
        LOGW("container is null");
        return nullptr;
    }
    auto pipelineContext = currentObj->GetPipelineContext();
    if (!pipelineContext) {
        LOGE("pipeline context is null!");
        return nullptr;
    }
    auto themeManager = pipelineContext->GetThemeManager();
    if (!themeManager) {
        LOGE("theme manager is null!");
        return nullptr;
    }
    return themeManager->GetThemeConstants();
}

} // namespace OHOS::Ace::Framework
