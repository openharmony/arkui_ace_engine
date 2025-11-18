/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ArkWithThemeComponent, WithThemeOptions } from 'arkui/component/withTheme';
import { int32 } from "@koalaui/common"
import { ThemeColorMode } from "arkui/component/common"
import { ArkThemeScopeManager, WithThemeScopeItem } from 'arkui/theme/ArkThemeScopeManager';
import { ArkThemeBase } from 'arkui/theme/ArkThemeBase';
import { ArkThemeNativeHelper } from 'arkui/theme/ArkThemeNativeHelper';

export function hookWithThemeOptions(receiver: ArkWithThemeComponent, options: WithThemeOptions | undefined) {
    const elmtId: int32 = receiver.getPeer()?.getId() ?? 0;
    const colorMode = options?.colorMode ?? ThemeColorMode.SYSTEM;
    const cloneTheme = ArkThemeScopeManager.cloneCustomThemeWithExpand(options?.theme);
    const theme: ArkThemeBase = ArkThemeScopeManager.getInstance().makeTheme(cloneTheme, colorMode);
    // bind theme to theme scope with elmtId
    theme.bindToScope(elmtId);

    ArkThemeScopeManager.getInstance().themeOptionsStack.push({
        options: options,
        themeScopeId: elmtId,
    } as WithThemeScopeItem);

    // prepare on theme scope destroy callback
    const onThemeScopeDestroy = () => {
        ArkThemeScopeManager.getInstance().onScopeDestroy(elmtId);
    };

    // keep for backward compatibility
    ArkThemeNativeHelper.sendThemeToNative(theme, elmtId);
    // new approach to apply theme in native side
    ArkThemeNativeHelper.createInternal(elmtId, theme.id, cloneTheme, colorMode, onThemeScopeDestroy);

    ArkThemeScopeManager.getInstance().onScopeEnter(elmtId, options ?? ({} as WithThemeOptions), theme);
}
