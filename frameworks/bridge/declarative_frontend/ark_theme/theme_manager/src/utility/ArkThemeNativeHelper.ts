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

class ArkThemeNativeHelper {
    static sendThemeToNative(theme: ThemeInternal, elmtId: number) {
        // @ts-ignore
        const lightColorArray = ArkThemeNativeHelper.convertColorsToArray(theme.colors);
        const darkColorArray = ArkThemeNativeHelper.convertColorsToArray(theme.darkColors);
        WithTheme.sendThemeToNative(lightColorArray, darkColorArray, elmtId);
    }

    static createInternal(themeScopeId: number, themeId: number, theme: CustomTheme, colorMode: ThemeColorMode,
        onThemeScopeDestroy: () => void
    ) {
        // set local color mode if need
        if (colorMode && colorMode !== ThemeColorMode.SYSTEM) {
            ArkThemeScopeManager.getInstance().onEnterLocalColorMode(colorMode);
        }

        const lightColorArray = ArkThemeNativeHelper.convertColorsToArray(theme?.colors);
        const darkColorArray = ArkThemeNativeHelper.convertColorsToArray(theme?.darkColors);
        getUINativeModule().theme.createAndBindTheme(themeScopeId, themeId, lightColorArray, darkColorArray, colorMode, onThemeScopeDestroy );

        // reset local color mode if need
        if (colorMode && colorMode !== ThemeColorMode.SYSTEM) {
            ArkThemeScopeManager.getInstance().onExitLocalColorMode();
        }
    }

    static setDefaultTheme(theme: CustomTheme) {
        const colorArray = ArkThemeNativeHelper.convertColorsToArray(theme?.colors);
        const darkColorArray = ArkThemeNativeHelper.convertColorsToArray(theme?.darkColors);

        ArkThemeScopeManager.getInstance().onEnterLocalColorMode(ThemeColorMode.LIGHT);
        getUINativeModule().theme.setDefaultTheme(colorArray, false);
        ArkThemeScopeManager.getInstance().onEnterLocalColorMode(ThemeColorMode.DARK);
        getUINativeModule().theme.setDefaultTheme(darkColorArray, true);
        ArkThemeScopeManager.getInstance().onExitLocalColorMode();
    }

    private static convertThemeToColorArray(theme: Theme): ResourceColor[] {
        return [
            theme.colors.brand,
            theme.colors.warning,
            theme.colors.alert,
            theme.colors.confirm,
            theme.colors.fontPrimary,
            theme.colors.fontSecondary,
            theme.colors.fontTertiary,
            theme.colors.fontFourth,
            theme.colors.fontEmphasize,
            theme.colors.fontOnPrimary,
            theme.colors.fontOnSecondary,
            theme.colors.fontOnTertiary,
            theme.colors.fontOnFourth,
            theme.colors.iconPrimary,
            theme.colors.iconSecondary,
            theme.colors.iconTertiary,
            theme.colors.iconFourth,
            theme.colors.iconEmphasize,
            theme.colors.iconSubEmphasize,
            theme.colors.iconOnPrimary,
            theme.colors.iconOnSecondary,
            theme.colors.iconOnTertiary,
            theme.colors.iconOnFourth,
            theme.colors.backgroundPrimary,
            theme.colors.backgroundSecondary,
            theme.colors.backgroundTertiary,
            theme.colors.backgroundFourth,
            theme.colors.backgroundEmphasize,
            theme.colors.compForegroundPrimary,
            theme.colors.compBackgroundPrimary,
            theme.colors.compBackgroundPrimaryTran,
            theme.colors.compBackgroundPrimaryContrary,
            theme.colors.compBackgroundGray,
            theme.colors.compBackgroundSecondary,
            theme.colors.compBackgroundTertiary,
            theme.colors.compBackgroundEmphasize,
            theme.colors.compBackgroundNeutral,
            theme.colors.compEmphasizeSecondary,
            theme.colors.compEmphasizeTertiary,
            theme.colors.compDivider,
            theme.colors.compCommonContrary,
            theme.colors.compBackgroundFocus,
            theme.colors.compFocusedPrimary,
            theme.colors.compFocusedSecondary,
            theme.colors.compFocusedTertiary,
            theme.colors.interactiveHover,
            theme.colors.interactivePressed,
            theme.colors.interactiveFocus,
            theme.colors.interactiveActive,
            theme.colors.interactiveSelect,
            theme.colors.interactiveClick,
        ];
    }

    private static convertColorsToArray(colors: CustomColors | undefined): ResourceColor[] {
        const basisColors = ArkThemeScopeManager.getSystemColors();
        if (!colors) {
            return new Array(Object.keys(basisColors).length).fill(undefined);
        }
        const colorArray: ResourceColor[] = [];
        for (let attr in basisColors) {
            colorArray.push(colors[attr]);
        }
        return colorArray;
    }
}

