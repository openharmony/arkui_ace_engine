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
import { ResourceColor, Color } from 'arkui/component';
import { ThemeColorMode } from 'arkui/component/common';
import { ArkUIAniModule } from 'arkui.ani';
import { CustomColors, Colors } from '@ohos/arkui/theme';
import { ArkThemeScopeManager } from './ArkThemeScopeManager';
import { int32 } from "@koalaui/common"
import { KPointer, runtimeType, RuntimeType } from '@koalaui/interop';
import { Serializer } from 'arkui/component';
import { TypeChecker } from '#components';
import { Resource } from 'global.resource';
import { SerializeUtils } from '../utils/SerializeUtils';
import { ArkColorsImpl } from './ArkColorsImpl';
import { ThemeInternal } from '../theme';

export class ArkThemeNativeHelper {
    static sendThemeToNative(theme: Theme, elmtId: int32): void {
        const thisSerializer : Serializer = Serializer.hold();
        const colorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme);
        SerializeUtils.writeColorArray(thisSerializer, colorArray);
        ArkUIAniModule._SendThemeToNative(thisSerializer.asBuffer(), thisSerializer.length(), elmtId);
        thisSerializer.release();
    }
    static setDefaultTheme(theme: CustomTheme | undefined): void {
        const colorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme!);
        ArkThemeScopeManager.getInstance().onEnterLocalColorMode(ThemeColorMode.LIGHT);
        ArkThemeNativeHelper.setDefaultTheme_serialize(colorArray, false);

        ArkThemeScopeManager.getInstance().onEnterLocalColorMode(ThemeColorMode.DARK);
        ArkThemeNativeHelper.setDefaultTheme_serialize(colorArray, true);
        ArkThemeScopeManager.getInstance().onExitLocalColorMode();
    }
    static setDefaultTheme_serialize(colorArray: ResourceColor[], isDark: boolean): void {
        const thisSerializer : Serializer = Serializer.hold();
        SerializeUtils.writeColorArray(thisSerializer, colorArray);
        ArkUIAniModule._SetDefaultTheme(thisSerializer.asBuffer(), thisSerializer.length(), isDark);
        thisSerializer.release();
    }
    static createInternal(
        themeScopeId: int32,
        themeId: int32,
        theme: CustomTheme | undefined,
        colorMode: ThemeColorMode,
        onThemeScopeDestroy: () => void
    ) {
        // set local color mode if need
        if (colorMode && colorMode !== ThemeColorMode.SYSTEM) {
            ArkThemeScopeManager.getInstance().onEnterLocalColorMode(colorMode);
        }
        const thisSerializer : Serializer = Serializer.hold();
        const colorArray = ArkThemeNativeHelper.convertColorsToArray(theme?.colors);
        SerializeUtils.writeColorArray(thisSerializer, colorArray);
        ArkUIAniModule._CreateAndBindTheme(themeScopeId, themeId,
            thisSerializer.asBuffer(), thisSerializer.length(), colorMode, onThemeScopeDestroy);
        // getUINativeModule().theme.createAndBindTheme(themeScopeId, themeId,
        //     ArkThemeNativeHelper.convertColorsToArray(theme?.colors), colorMode, onThemeScopeDestroy);

        // reset local color mode if need
        if (colorMode && colorMode !== ThemeColorMode.SYSTEM) {
            ArkThemeScopeManager.getInstance().onExitLocalColorMode();
        }
    }
    public static convertThemeToColorArray(theme: Theme | CustomTheme | undefined): ResourceColor[] {
        if (!theme) {
            return new Array<ResourceColor>(Object.keys(new ArkColorsImpl()).length);
        }
        const srcTheme: Theme = { colors: new ArkColorsImpl() };
        if (theme instanceof Theme) {
            srcTheme.colors = theme.colors;
        } else {
            ArkColorsImpl.assign(srcTheme.colors, (theme as CustomTheme).colors!)
        }
        return [
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.brand),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.warning),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.alert),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.confirm),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontPrimary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontSecondary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontTertiary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontFourth),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontEmphasize),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontOnPrimary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontOnSecondary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontOnTertiary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.fontOnFourth),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconPrimary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconSecondary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconTertiary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconFourth),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconEmphasize),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconSubEmphasize),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconOnPrimary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconOnSecondary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconOnTertiary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.iconOnFourth),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.backgroundPrimary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.backgroundSecondary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.backgroundTertiary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.backgroundFourth),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.backgroundEmphasize),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compForegroundPrimary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundPrimary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundPrimaryTran),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundPrimaryContrary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundGray),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundSecondary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundTertiary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundEmphasize),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundNeutral),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compEmphasizeSecondary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compEmphasizeTertiary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compDivider),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compCommonContrary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compBackgroundFocus),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compFocusedPrimary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compFocusedSecondary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.compFocusedTertiary),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.interactiveHover),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.interactivePressed),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.interactiveFocus),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.interactiveActive),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.interactiveSelect),
            ArkThemeNativeHelper.convertColorEnumToValue(srcTheme.colors.interactiveClick),
        ];
    }

    private static convertColorEnumToValue(color: ResourceColor): ResourceColor {
        if (ArkColorsImpl.checkIsColor(color)) {
            return ArkColorsImpl.convertColorEnumToValue(color as Color);
        }
        return color;
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
                colorArray.push(ArkColorsImpl.convertColorEnumToValue(value as Color));
                continue;
            }
            colorArray.push(value);
        }
        return colorArray;
    }
}
