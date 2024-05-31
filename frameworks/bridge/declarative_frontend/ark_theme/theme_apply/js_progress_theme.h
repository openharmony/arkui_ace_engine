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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_PROGRESS_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_PROGRESS_THEME_H

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/progress/progress_model.h"

namespace OHOS::Ace::Framework {
class JSProgressTheme {
public:
    static void ApplyTheme(const ProgressStyle& style)
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors) {
            // no need to apply custom theme colors
            return;
        }
        if (style != ProgressStyle::Capsule) {
            ProgressModel::GetInstance()->SetBackgroundColor(themeColors->CompBackgroundTertiary());
        }
        if (style == ProgressStyle::Capsule) {
            NG::GradientColor endSideColor;
            NG::GradientColor beginSideColor;
            OHOS::Ace::NG::Gradient gradient;
            endSideColor.SetLinearColor(LinearColor(themeColors->CompEmphasizeSecondary()));
            endSideColor.SetDimension(Dimension(0.0f));
            beginSideColor.SetLinearColor(LinearColor(themeColors->CompEmphasizeSecondary()));
            beginSideColor.SetDimension(Dimension(1.0f));
            gradient.AddColor(endSideColor);
            gradient.AddColor(beginSideColor);
            ProgressModel::GetInstance()->SetGradientColor(gradient);
            ProgressModel::GetInstance()->SetColor(themeColors->CompEmphasizeSecondary());
            // normal
            ViewStackModel::GetInstance()->SetVisualState(VisualState::NORMAL);
            auto borderColor = themeColors->CompEmphasizeSecondary();
            ViewAbstractModel::GetInstance()->SetBorderColor(borderColor, borderColor, borderColor, borderColor);
            ViewAbstractModel::GetInstance()->SetColorBlend(Color::BLACK); // default for restore color after pressed
            // clear state
            ViewStackModel::GetInstance()->ClearVisualState();
        } else if (style == ProgressStyle::Linear || style == ProgressStyle::Eclipse) {
            NG::GradientColor endSideColor;
            NG::GradientColor beginSideColor;
            OHOS::Ace::NG::Gradient gradient;
            endSideColor.SetLinearColor(LinearColor(themeColors->BackgroundEmphasize()));
            endSideColor.SetDimension(Dimension(0.0f));
            beginSideColor.SetLinearColor(LinearColor(themeColors->BackgroundEmphasize()));
            beginSideColor.SetDimension(Dimension(1.0f));
            gradient.AddColor(endSideColor);
            gradient.AddColor(beginSideColor);
            ProgressModel::GetInstance()->SetGradientColor(gradient);
            ProgressModel::GetInstance()->SetColor(themeColors->BackgroundEmphasize());
        }
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_PROGRESS_THEME_H
