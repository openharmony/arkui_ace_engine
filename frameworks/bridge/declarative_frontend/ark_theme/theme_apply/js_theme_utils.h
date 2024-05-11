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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_THEME_UTILS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_THEME_UTILS_H

#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::Framework {
class JSThemeUtils {
private:
    /**
     * Obtain the Id of WithTheme container which corresponds to current node.
     * This invokes the globalThis.themeScopeMgr.getWithThemeIdForElmtId method on JS level.
     */
    static int32_t GetWithThemeId()
    {
        // use default theme if theme scope is desabled
        int32_t ret = 0;
        if (!JSThemeScope::jsThemeScopeEnabled) {
            return ret;
        }
        // take theme scope id from js level method
        auto elmId = NG::ViewStackProcessor::GetInstance()->GetNodeIdToAccountFor();
        auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
        CHECK_NULL_RETURN(runtime, ret);
        auto global = runtime->GetGlobal();
        auto scopeMgr = global->GetProperty(runtime, "themeScopeMgr");
        if (!scopeMgr->IsObject(runtime)) {
            return ret;
        }
        auto func = scopeMgr->GetProperty(runtime, "getWithThemeIdForElmtId");
        if (!func->IsFunction(runtime)) {
            return ret;
        }
        std::vector<shared_ptr<JsValue>> argv;
        argv.push_back(runtime->NewInt32(elmId));
        auto retVal = func->Call(runtime, scopeMgr, argv, argv.size());
        CHECK_NULL_RETURN(retVal, ret);
        ret = retVal->ToInt32(runtime);
        return ret;
    }

public:
    static constexpr int32_t DEFAULT_ALPHA = 255;
    static constexpr double DEFAULT_OPACITY = 0.2;
    
    static std::optional<JSTheme> GetTheme()
    {
        auto themeId = GetWithThemeId();
        auto it = JSThemeScope::jsThemes.find(themeId);
        return (it != JSThemeScope::jsThemes.end()) ? std::make_optional(it->second) : std::nullopt;
    }

    static std::optional<JSThemeColors> GetThemeColors()
    {
        auto themeId = GetWithThemeId();
        auto it = JSThemeScope::jsThemes.find(themeId);
        return (it != JSThemeScope::jsThemes.end()) ? std::make_optional(it->second.Colors()) : std::nullopt;
    }
};
}
#endif //FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_THEME_UTILS_H