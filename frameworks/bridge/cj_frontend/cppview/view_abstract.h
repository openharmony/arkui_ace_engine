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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_ABSTRACT_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_ABSTRACT_H

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/json/json_util.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/common/container.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/placement.h"
#ifndef __OHOS_NG__
#include "core/components/box/box_component.h"
#include "core/components/display/display_component.h"
#include "core/components/menu/menu_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/components/transform/transform_component.h"
#endif
#include "core/gestures/tap_gesture.h"
#include "core/pipeline/base/component.h"
#include "ffi_remote_data.h"

namespace OHOS::Ace::Framework {

enum class Align {
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
};

enum class CJResponseType : int32_t {
    RIGHT_CLICK = 0,
    LONGPRESS,
};

class ACE_EXPORT ViewAbstract : public OHOS::FFI::FFIData {
DECL_TYPE(ViewAbstract, OHOS::FFI::FFIData)
public:
    ViewAbstract() : FFIData() {}

    template<typename T>
    static RefPtr<T> GetTheme()
    {
        auto currentObj = Container::Current();
        if (!currentObj) {
            LOGW("container is null");
            return nullptr;
        }
        auto pipelineContext = currentObj->GetPipelineContext();
        if (!pipelineContext) {
            LOGE("pipelineContext is null!");
            return nullptr;
        }
        auto themeManager = pipelineContext->GetThemeManager();
        if (!themeManager) {
            LOGE("themeManager is null!");
            return nullptr;
        }
        return themeManager->GetTheme<T>();
    }

    static RefPtr<ThemeConstants> GetThemeConstants();
    static void CjEnabled(bool enabled);

};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_ABSTRACT_H
