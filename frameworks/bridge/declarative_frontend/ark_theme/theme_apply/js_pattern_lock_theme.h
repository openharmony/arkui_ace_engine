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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_PATTERN_LOCK_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_PATTERN_LOCK_THEME_H

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/components_ng/pattern/patternlock/patternlock_model.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::Framework {
class JSPatternLockTheme {
public:
    static void ApplyTheme()
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors) {
            // no need to apply custom theme colors
            return;
        }

        auto* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        NG::PatternLockModelNG::SetRegularColor(frameNode, themeColors->CompBackgroundNeutral());
        NG::PatternLockModelNG::SetActiveColor(frameNode, themeColors->CompBackgroundNeutral());
        NG::PatternLockModelNG::SetSelectedColor(frameNode, themeColors->CompBackgroundNeutral());
        NG::PatternLockModelNG::SetPathColor(frameNode, themeColors->CompDivider());
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_PATTERN_LOCK_THEME_H