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

import { Theme, CustomTheme } from '@ohos/arkui/theme';
import { ResourceColor } from 'arkui/component/units';
import { Color } from 'arkui/component/enums';
import { ThemeColorMode } from 'arkui/component/common';
import { ArkUIAniModule } from 'arkui.ani';
import { CustomColors, Colors } from '@ohos/arkui/theme';
import { ArkThemeScopeManager } from './ArkThemeScopeManager';
import { int32 } from "@koalaui/common"
// import { Serializer } from 'arkui/component';
import { ArkColorsImpl } from './ArkColorsImpl';
import { ThemeOps } from 'arkui/component/idlize';
import { GlobalStateManager } from '@koalaui/runtime';

export class ArkThemeNativeHelper {
    static sendThemeToNative(theme: Theme, elmtId: int32, darkSetStatus: boolean): void {
        const colorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme, false);
        const darkColorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme, true);
        ThemeOps.sendThemeToNative(colorArray, darkColorArray, elmtId, darkSetStatus);
    }
    static setDefaultTheme(theme: CustomTheme | undefined): void {
        const colorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme, false);
        const darkColorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme, true);
        ArkThemeScopeManager.getInstance().onEnterLocalColorMode(ThemeColorMode.LIGHT);
        ThemeOps.setDefaultTheme(colorArray, false);

        ArkThemeScopeManager.getInstance().onEnterLocalColorMode(ThemeColorMode.DARK);
        ThemeOps.setDefaultTheme(darkColorArray, true);
        ArkThemeScopeManager.getInstance().onExitLocalColorMode();
    }
    static createInternal(
        themeScopeId: int32,
        themeId: int32,
        theme: CustomTheme | undefined,
        colorMode: ThemeColorMode,
        onThemeScopeDestroy: () => void,
        darkSetStatus: boolean
    ) {
        // set local color mode if need
        if (colorMode && colorMode !== ThemeColorMode.SYSTEM) {
            ArkThemeScopeManager.getInstance().onEnterLocalColorMode(colorMode);
        }
        const colorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme, false);
        const darkColorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme, true);

        ThemeOps.createAndBindTheme(themeScopeId, themeId, colorArray, darkColorArray, colorMode, onThemeScopeDestroy, darkSetStatus);

        // reset local color mode if need
        if (colorMode && colorMode !== ThemeColorMode.SYSTEM) {
            ArkThemeScopeManager.getInstance().onExitLocalColorMode();
        }
    }
    public static convertThemeToColorArray(theme: Theme | CustomTheme | undefined, isDark: boolean): ResourceColor[] {
        const srcTheme: Theme = { colors: new ArkColorsImpl(), darkColors: new ArkColorsImpl()};
        if (theme instanceof Theme) {
            srcTheme.colors = isDark? theme.darkColors : theme.colors;
        } else if (theme instanceof CustomTheme) {
            if (isDark) {
                const colorArrayDark = (theme as CustomTheme).darkColors;
                if (colorArrayDark) {
                    ArkColorsImpl.assign(srcTheme.colors, colorArrayDark);
                } else {
                    const colorArrayLight = (theme as CustomTheme).colors;
                    ArkColorsImpl.assign(srcTheme.colors, colorArrayLight!);
                }
            } else {
                const colorArrayLight = (theme as CustomTheme).colors;
                if (colorArrayLight) {
                    ArkColorsImpl.assign(srcTheme.colors, colorArrayLight);
                }
            }
        }
        return [
            srcTheme.colors.brand,
            srcTheme.colors.warning,
            srcTheme.colors.alert,
            srcTheme.colors.confirm,
            srcTheme.colors.fontPrimary,
            srcTheme.colors.fontSecondary,
            srcTheme.colors.fontTertiary,
            srcTheme.colors.fontFourth,
            srcTheme.colors.fontEmphasize,
            srcTheme.colors.fontOnPrimary,
            srcTheme.colors.fontOnSecondary,
            srcTheme.colors.fontOnTertiary,
            srcTheme.colors.fontOnFourth,
            srcTheme.colors.iconPrimary,
            srcTheme.colors.iconSecondary,
            srcTheme.colors.iconTertiary,
            srcTheme.colors.iconFourth,
            srcTheme.colors.iconEmphasize,
            srcTheme.colors.iconSubEmphasize,
            srcTheme.colors.iconOnPrimary,
            srcTheme.colors.iconOnSecondary,
            srcTheme.colors.iconOnTertiary,
            srcTheme.colors.iconOnFourth,
            srcTheme.colors.backgroundPrimary,
            srcTheme.colors.backgroundSecondary,
            srcTheme.colors.backgroundTertiary,
            srcTheme.colors.backgroundFourth,
            srcTheme.colors.backgroundEmphasize,
            srcTheme.colors.compForegroundPrimary,
            srcTheme.colors.compBackgroundPrimary,
            srcTheme.colors.compBackgroundPrimaryTran,
            srcTheme.colors.compBackgroundPrimaryContrary,
            srcTheme.colors.compBackgroundGray,
            srcTheme.colors.compBackgroundSecondary,
            srcTheme.colors.compBackgroundTertiary,
            srcTheme.colors.compBackgroundEmphasize,
            srcTheme.colors.compBackgroundNeutral,
            srcTheme.colors.compEmphasizeSecondary,
            srcTheme.colors.compEmphasizeTertiary,
            srcTheme.colors.compDivider,
            srcTheme.colors.compCommonContrary,
            srcTheme.colors.compBackgroundFocus,
            srcTheme.colors.compFocusedPrimary,
            srcTheme.colors.compFocusedSecondary,
            srcTheme.colors.compFocusedTertiary,
            srcTheme.colors.interactiveHover,
            srcTheme.colors.interactivePressed,
            srcTheme.colors.interactiveFocus,
            srcTheme.colors.interactiveActive,
            srcTheme.colors.interactiveSelect,
            srcTheme.colors.interactiveClick,
        ];
    }

    public static convertColorsToArray(colors: Colors | CustomColors | undefined): ResourceColor[] {
        const basisColors = ArkThemeScopeManager.getSystemColors();
        if (!colors) {
            return new Array<ResourceColor>(Object.keys(basisColors).length);
        }
        const colorArray: ResourceColor[] = [];
        for (let attr of Object.values(colors)) {
            const value: ResourceColor = attr as ResourceColor;
            if (ArkColorsImpl.checkIsColor(value)) {
                colorArray.push(value as Color);
                continue;
            }
            colorArray.push(value);
        }
        return colorArray;
    }

    public static currentThemeScopeId(): int32 {
        const stateManager = GlobalStateManager.instance;
        return stateManager.stateBy<int32>("themeScopeId")?.value ?? 0;
    }
}
