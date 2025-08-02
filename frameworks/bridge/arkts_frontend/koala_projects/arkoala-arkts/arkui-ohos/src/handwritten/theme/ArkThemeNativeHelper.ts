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
import { CustomColors } from '@ohos/arkui/theme';
import { ArkThemeScopeManager } from './ArkThemeScopeManager';
import { int32 } from "@koalaui/common"
import { Colors } from '@ohos/arkui/theme';
import { KPointer, runtimeType, RuntimeType } from '@koalaui/interop';
import { Serializer } from 'arkui/component';
import { TypeChecker } from '#components';
import { Resource } from 'global.resource';

export class ArkThemeNativeHelper {
    static writeColorArray(thisSerializer: Serializer, colorArray: ResourceColor[]) {
        thisSerializer.writeInt32(colorArray.length as int32);
        for (let i = 0; i < colorArray.length; i++) {
            let color_type : int32 = runtimeType(colorArray[i]);
            if (TypeChecker.isColor(colorArray[i])) {
                thisSerializer.writeInt8(0 as int32)
                const color_0  = colorArray[i] as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
            }
            else if (RuntimeType.NUMBER == color_type) {
                thisSerializer.writeInt8(1 as int32)
                const color_1  = colorArray[i] as number
                thisSerializer.writeNumber(color_1)
            }
            else if (RuntimeType.STRING == color_type) {
                thisSerializer.writeInt8(2 as int32)
                const color_2  = colorArray[i] as string
                thisSerializer.writeString(color_2)
            }
            else if (RuntimeType.OBJECT == color_type) {
                thisSerializer.writeInt8(3 as int32)
                const color_3  = colorArray[i] as Resource
                thisSerializer.writeResource(color_3)
            }
        }
    }
    static sendThemeToNative(theme: Theme, elmtId: int32): void {
        const thisSerializer : Serializer = Serializer.hold();
        const colorArray = ArkThemeNativeHelper.convertThemeToColorArray(theme);
        ArkThemeNativeHelper.writeColorArray(thisSerializer, colorArray);
        ArkUIAniModule._SendThemeToNative(thisSerializer.asBuffer(), thisSerializer.length(), elmtId);
        thisSerializer.release();
    }
    static setDefaultTheme(theme: CustomTheme): void {
        const colorArray = ArkThemeNativeHelper.convertColorsToArray(theme?.colors);
        ArkThemeScopeManager.getInstance().onEnterLocalColorMode(ThemeColorMode.LIGHT);
        ArkThemeNativeHelper.setDefaultTheme_serialize(colorArray, false);

        ArkThemeScopeManager.getInstance().onEnterLocalColorMode(ThemeColorMode.DARK);
        ArkThemeNativeHelper.setDefaultTheme_serialize(colorArray, true);
        ArkThemeScopeManager.getInstance().onExitLocalColorMode();
    }
    static setDefaultTheme_serialize(colorArray: ResourceColor[], isDark: boolean): void {
        const thisSerializer : Serializer = Serializer.hold();
        ArkThemeNativeHelper.writeColorArray(thisSerializer, colorArray);
        ArkUIAniModule._SetDefaultTheme(thisSerializer.asBuffer(), thisSerializer.length(), isDark);
        thisSerializer.release();
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
            return new Array<ResourceColor>(Object.keys(basisColors).length);
        }
        const colorArray: ResourceColor[] = [];
        for (let attr of Object.values(colors)) {
            const value: ResourceColor = attr as ResourceColor;
            if (Colors.checkIsColor(value)) {
                colorArray.push(value as string);
                continue;
            }
            colorArray.push(value);
        }
        return colorArray;
    }
}
