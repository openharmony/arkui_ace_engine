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

import { CustomTheme, Theme, Colors } from '@ohos/arkui/theme';
import { ThemeColorMode } from 'arkui/component/common';
import { InteropNativeModule } from '@koalaui/interop';
import { ArkThemeBase } from './ArkThemeBase';
import { ArkSystemTheme } from './system/ArkSystemTheme';
import { ArkThemeCache } from './ArkThemeCache';
import { ArkThemeImpl } from './ArkThemeImpl';
import { ArkThemeNativeHelper } from './ArkThemeNativeHelper';

type ViewPuInternal = Object;

export class ArkThemeScopeManager {
    private static instance: ArkThemeScopeManager | undefined = undefined;
    private static systemTheme = new ArkSystemTheme();
    /**
     * Theme update listeners
     */
    private listeners: ViewPuInternal[] = [];
    /**
     * The default Theme
     */
    private defaultTheme: ArkThemeBase | undefined = undefined;

    /**
     * Obtain System Colors
     *
     * @returns System Colors
     */
    static getSystemColors(): Colors {
        return ArkThemeScopeManager.systemTheme.colors;
    }

    /**
     * Enter to the local color mode scope
     *
     * @param colorMode local color mode
     */
    onEnterLocalColorMode(colorMode: ThemeColorMode) {
        // getUINativeModule().resource.updateColorMode(colorMode);
    }

    /**
     * Exit from the local color mode scope
     */
    onExitLocalColorMode() {
        // getUINativeModule().resource.restore();
    }

    /**
     * Create CustomTheme instance based on given Custom theme with the additional expands
     *
     * @param customTheme instance of CustomTheme used to create theme
     * @returns theme instance
     */
    static cloneCustomThemeWithExpand(customTheme: CustomTheme): CustomTheme {
        const theme = ArkThemeBase.copyCustomTheme(customTheme);
        if (theme?.colors) {
            Colors.expandByBrandColor(theme!.colors!);
        }
        return theme!;
    }

    /**
     * Create Theme instance
     *
     * @param customTheme instance of CustomTheme used to create theme
     * @param colorMode local colorm mode used for theme
     * @returns theme instance
     */
    makeTheme(customTheme: CustomTheme, colorMode: ThemeColorMode): ArkThemeBase {
        const baselineTheme = this.defaultTheme ?? ArkThemeScopeManager.systemTheme;
        // try to take theme from the cache
        const theme = ArkThemeCache.getInstance().get(baselineTheme.id, customTheme, colorMode);

        // return theme instance from cache or create new theme instance
        return theme ? theme : new ArkThemeImpl(customTheme, colorMode, baselineTheme);
    }

    /**
     * Notifies listeners about app Theme change
     */
    private notifyGlobalThemeChanged() {
        this.listeners.forEach((listener) => {
            // if (listener.parent_ === undefined) {
            //     listener.onGlobalThemeChanged();
            // }
        });
    }

    setDefaultTheme(customTheme: CustomTheme) {
        // unbind previous default theme from 0 theme scope
        this.defaultTheme?.unbindFromScope(0);
        this.defaultTheme = ArkThemeScopeManager.systemTheme;
        const cloneTheme = ArkThemeScopeManager.cloneCustomThemeWithExpand(customTheme);
        this.defaultTheme = this.makeTheme(customTheme, ThemeColorMode.SYSTEM);
        // bind new default theme to 0 theme scope
        this.defaultTheme?.bindToScope(0);

        // keep for backward compatibility
        ArkThemeNativeHelper.sendThemeToNative(this.defaultTheme!, 0); // 0 means default Theme scope id
        // new approach to apply theme in native side
        ArkThemeNativeHelper.setDefaultTheme(cloneTheme);

        this.notifyGlobalThemeChanged();
    }
    static getInstance(): ArkThemeScopeManager {
        if (!ArkThemeScopeManager.instance) {
            ArkThemeScopeManager.instance = new ArkThemeScopeManager();
        }
        return ArkThemeScopeManager.instance!;
    }
}
