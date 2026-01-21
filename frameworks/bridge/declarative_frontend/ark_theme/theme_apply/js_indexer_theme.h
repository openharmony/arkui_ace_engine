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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_INDEXER_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_INDEXER_THEME_H

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/components_ng/pattern/indexer/indexer_model.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::Framework {
class JSIndexerTheme {
public:
    static void ApplyTheme()
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors) {
            // no need to apply custom theme colors
            return;
        }
        auto* stack = NG::ViewStackProcessor::GetInstance();
        CHECK_NULL_VOID(stack);
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(stack->GetMainFrameNode());
        CHECK_NULL_VOID(frameNode);
        NG::IndexerModelNG::SetColor(frameNode, themeColors->FontSecondary());
        NG::IndexerModelNG::SetSelectedColor(frameNode, themeColors->FontEmphasize());
        NG::IndexerModelNG::SetPopupColor(frameNode, themeColors->FontEmphasize());
        NG::IndexerModelNG::SetPopupUnselectedColor(frameNode, themeColors->FontPrimary());
        NG::IndexerModelNG::SetPopupTitleBackground(frameNode, themeColors->CompBackgroundTertiary());
        NG::IndexerModelNG::SetSelectedBackgroundColor(frameNode, themeColors->CompEmphasizeSecondary());
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_INDEXER_THEME_H