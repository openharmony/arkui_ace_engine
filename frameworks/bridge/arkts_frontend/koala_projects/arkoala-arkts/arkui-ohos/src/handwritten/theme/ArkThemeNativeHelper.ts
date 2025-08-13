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
        const colorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme);
        SerializeUtils.writeColorArray(thisSerializer, colorArray);
        ArkUIAniModule._CreateAndBindTheme(themeScopeId, themeId,
            thisSerializer.asBuffer(), thisSerializer.length(), colorMode, onThemeScopeDestroy);

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
}
