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

import { ResourceColor, Color } from 'arkui/component';
import { ArkResourcesHelper } from 'arkui/handwritten/theme/ArkResourcesHelper';
import { BrandColors, ArkThemeResource } from 'arkui/handwritten/theme';
import { Resource } from 'global.resource';
import { ArkUIAniModule } from 'arkui.ani';
import { Colors, CustomColors } from '@ohos/arkui/theme';

export class ArkColorsImpl implements Colors {
    brand: ResourceColor = ArkResourcesHelper.$r('sys.color.brand', 125830976);
    warning: ResourceColor = ArkResourcesHelper.$r('sys.color.warning', 125830979);
    alert: ResourceColor = ArkResourcesHelper.$r('sys.color.alert', 125830980);
    confirm: ResourceColor = ArkResourcesHelper.$r('sys.color.confirm', 125830981);

    fontPrimary: ResourceColor = ArkResourcesHelper.$r('sys.color.font_primary', 125830982);
    fontSecondary: ResourceColor = ArkResourcesHelper.$r('sys.color.font_secondary', 125830983);
    fontTertiary: ResourceColor = ArkResourcesHelper.$r('sys.color.font_tertiary', 125830984);
    fontFourth: ResourceColor = ArkResourcesHelper.$r('sys.color.font_fourth', 125830985);
    fontEmphasize: ResourceColor = ArkResourcesHelper.$r('sys.color.font_emphasize', 125830986);

    fontOnPrimary: ResourceColor = ArkResourcesHelper.$r('sys.color.font_on_primary', 125830987);
    fontOnSecondary: ResourceColor = ArkResourcesHelper.$r('sys.color.font_on_secondary', 125830988);
    fontOnTertiary: ResourceColor = ArkResourcesHelper.$r('sys.color.font_on_tertiary', 125830989);
    fontOnFourth: ResourceColor = ArkResourcesHelper.$r('sys.color.font_on_fourth', 125830990);

    iconPrimary: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_primary', 125830991);
    iconSecondary: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_secondary', 125830992);
    iconTertiary: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_tertiary', 125830993);
    iconFourth: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_fourth', 125830994);
    iconEmphasize: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_emphasize', 125830995);
    iconSubEmphasize: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_sub_emphasize', 125830996);

    iconOnPrimary: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_on_primary', 125831057);
    iconOnSecondary: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_on_secondary', 125831058);
    iconOnTertiary: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_on_tertiary', 125831059);
    iconOnFourth: ResourceColor = ArkResourcesHelper.$r('sys.color.icon_on_fourth', 125831060);

    backgroundPrimary: ResourceColor = ArkResourcesHelper.$r('sys.color.background_primary', 125831061);
    backgroundSecondary: ResourceColor = ArkResourcesHelper.$r('sys.color.background_secondary', 125831062);
    backgroundTertiary: ResourceColor = ArkResourcesHelper.$r('sys.color.background_tertiary', 125831063);
    backgroundFourth: ResourceColor = ArkResourcesHelper.$r('sys.color.background_fourth', 125831064);
    backgroundEmphasize: ResourceColor = ArkResourcesHelper.$r('sys.color.background_emphasize', 125831065);

    compForegroundPrimary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_foreground_primary', 125831003);
    compBackgroundPrimary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_background_primary', 125831004);
    compBackgroundPrimaryTran: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_background_primary_tran');
    compBackgroundPrimaryContrary: ResourceColor = ArkResourcesHelper.$r(
        'sys.color.comp_background_primary_contrary',
        125831005
    );
    compBackgroundGray: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_background_gray', 125831006);
    compBackgroundSecondary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_background_secondary', 125831007);
    compBackgroundTertiary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_background_tertiary', 125831008);
    compBackgroundEmphasize: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_background_emphasize', 125831009);
    compBackgroundNeutral: ResourceColor = ArkResourcesHelper.$r('sys.color.neutral', 125831066);
    compEmphasizeSecondary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_emphasize_secondary', 125831011);
    compEmphasizeTertiary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_emphasize_tertiary', 125831012);
    compDivider: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_divider', 125831013);
    compCommonContrary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_common_contrary', 125831014);
    compBackgroundFocus: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_background_focus', 125831015);
    compFocusedPrimary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_focused_primary', 125831016);
    compFocusedSecondary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_focused_secondary', 125831017);
    compFocusedTertiary: ResourceColor = ArkResourcesHelper.$r('sys.color.comp_focused_tertiary', 125831018);

    interactiveHover: ResourceColor = ArkResourcesHelper.$r('sys.color.interactive_hover', 125831019);
    interactivePressed: ResourceColor = ArkResourcesHelper.$r('sys.color.interactive_pressed', 125831020);
    interactiveFocus: ResourceColor = ArkResourcesHelper.$r('sys.color.interactive_focus', 125831021);
    interactiveActive: ResourceColor = ArkResourcesHelper.$r('sys.color.interactive_active', 125831022);
    interactiveSelect: ResourceColor = ArkResourcesHelper.$r('sys.color.interactive_select', 125831023);
    interactiveClick: ResourceColor = ArkResourcesHelper.$r('sys.color.interactive_click', 125831024);

    constructor() {}

    constructor(colors: CustomColors | undefined, baselineColors: Colors) {
        ArkColorsImpl.assign(this, baselineColors);
        if (colors) {
            ArkColorsImpl.assign(this, colors!);
        }
    }

    static assign(dst: Colors, src: Colors): void {
        dst.brand = src.brand;
        dst.warning = src.warning;
        dst.alert = src.alert;
        dst.confirm = src.confirm;

        dst.fontPrimary = src.fontPrimary;
        dst.fontSecondary = src.fontSecondary;
        dst.fontTertiary = src.fontTertiary;
        dst.fontFourth = src.fontFourth;
        dst.fontEmphasize = src.fontEmphasize;

        dst.fontOnPrimary = src.fontOnPrimary;
        dst.fontOnSecondary = src.fontOnSecondary;
        dst.fontOnTertiary = src.fontOnTertiary;
        dst.fontOnFourth = src.fontOnFourth;

        dst.iconPrimary = src.iconPrimary;
        dst.iconSecondary = src.iconSecondary;
        dst.iconTertiary = src.iconTertiary;
        dst.iconFourth = src.iconFourth;
        dst.iconEmphasize = src.iconEmphasize;
        dst.iconSubEmphasize = src.iconSubEmphasize;

        dst.iconOnPrimary = src.iconOnPrimary;
        dst.iconOnSecondary = src.iconOnSecondary;
        dst.iconOnTertiary = src.iconOnTertiary;
        dst.iconOnFourth = src.iconOnFourth;

        dst.backgroundPrimary = src.backgroundPrimary;
        dst.backgroundSecondary = src.backgroundSecondary;
        dst.backgroundTertiary = src.backgroundTertiary;
        dst.backgroundFourth = src.backgroundFourth;
        dst.backgroundEmphasize = src.backgroundEmphasize;

        dst.compForegroundPrimary = src.compForegroundPrimary;
        dst.compBackgroundPrimary = src.compBackgroundPrimary;
        dst.compBackgroundPrimaryTran = src.compBackgroundPrimaryTran;
        dst.compBackgroundPrimaryContrary = src.compBackgroundPrimaryContrary;
        dst.compBackgroundGray = src.compBackgroundGray;
        dst.compBackgroundSecondary = src.compBackgroundSecondary;
        dst.compBackgroundTertiary = src.compBackgroundTertiary;
        dst.compBackgroundEmphasize = src.compBackgroundEmphasize;
        dst.compBackgroundNeutral = src.compBackgroundNeutral;
        dst.compEmphasizeSecondary = src.compEmphasizeSecondary;
        dst.compEmphasizeTertiary = src.compEmphasizeTertiary;
        dst.compDivider = src.compDivider;
        dst.compCommonContrary = src.compCommonContrary;
        dst.compBackgroundFocus = src.compBackgroundFocus;
        dst.compFocusedPrimary = src.compFocusedPrimary;
        dst.compFocusedSecondary = src.compFocusedSecondary;
        dst.compFocusedTertiary = src.compFocusedTertiary;

        dst.interactiveHover = src.interactiveHover;
        dst.interactivePressed = src.interactivePressed;
        dst.interactiveFocus = src.interactiveFocus;
        dst.interactiveActive = src.interactiveActive;
        dst.interactiveSelect = src.interactiveSelect;
        dst.interactiveClick = src.interactiveClick;
    }

    static assign(dst: Colors, src: CustomColors): void {
        if (src.brand !== undefined) dst.brand = src.brand!;
        if (src.warning !== undefined) dst.warning = src.warning!;
        if (src.alert !== undefined) dst.alert = src.alert!;
        if (src.confirm !== undefined) dst.confirm = src.confirm!;

        if (src.fontPrimary !== undefined) dst.fontPrimary = src.fontPrimary!;
        if (src.fontSecondary !== undefined) dst.fontSecondary = src.fontSecondary!;
        if (src.fontTertiary !== undefined) dst.fontTertiary = src.fontTertiary!;
        if (src.fontFourth !== undefined) dst.fontFourth = src.fontFourth!;
        if (src.fontEmphasize !== undefined) dst.fontEmphasize = src.fontEmphasize!;

        if (src.fontOnPrimary !== undefined) dst.fontOnPrimary = src.fontOnPrimary!;
        if (src.fontOnSecondary !== undefined) dst.fontOnSecondary = src.fontOnSecondary!;
        if (src.fontOnTertiary !== undefined) dst.fontOnTertiary = src.fontOnTertiary!;
        if (src.fontOnFourth !== undefined) dst.fontOnFourth = src.fontOnFourth!;

        if (src.iconPrimary !== undefined) dst.iconPrimary = src.iconPrimary!;
        if (src.iconSecondary !== undefined) dst.iconSecondary = src.iconSecondary!;
        if (src.iconTertiary !== undefined) dst.iconTertiary = src.iconTertiary!;
        if (src.iconFourth !== undefined) dst.iconFourth = src.iconFourth!;
        if (src.iconEmphasize !== undefined) dst.iconEmphasize = src.iconEmphasize!;
        if (src.iconSubEmphasize !== undefined) dst.iconSubEmphasize = src.iconSubEmphasize!;

        if (src.iconOnPrimary !== undefined) dst.iconOnPrimary = src.iconOnPrimary!;
        if (src.iconOnSecondary !== undefined) dst.iconOnSecondary = src.iconOnSecondary!;
        if (src.iconOnTertiary !== undefined) dst.iconOnTertiary = src.iconOnTertiary!;
        if (src.iconOnFourth !== undefined) dst.iconOnFourth = src.iconOnFourth!;

        if (src.backgroundPrimary !== undefined) dst.backgroundPrimary = src.backgroundPrimary!;
        if (src.backgroundSecondary !== undefined) dst.backgroundSecondary = src.backgroundSecondary!;
        if (src.backgroundTertiary !== undefined) dst.backgroundTertiary = src.backgroundTertiary!;
        if (src.backgroundFourth !== undefined) dst.backgroundFourth = src.backgroundFourth!;
        if (src.backgroundEmphasize !== undefined) dst.backgroundEmphasize = src.backgroundEmphasize!;

        if (src.compForegroundPrimary !== undefined) dst.compForegroundPrimary = src.compForegroundPrimary!;
        if (src.compBackgroundPrimary !== undefined) dst.compBackgroundPrimary = src.compBackgroundPrimary!;
        if (src.compBackgroundPrimaryTran !== undefined) dst.compBackgroundPrimaryTran = src.compBackgroundPrimaryTran!;
        if (src.compBackgroundPrimaryContrary !== undefined)
            dst.compBackgroundPrimaryContrary = src.compBackgroundPrimaryContrary!;
        if (src.compBackgroundGray !== undefined) dst.compBackgroundGray = src.compBackgroundGray!;
        if (src.compBackgroundSecondary !== undefined) dst.compBackgroundSecondary = src.compBackgroundSecondary!;
        if (src.compBackgroundTertiary !== undefined) dst.compBackgroundTertiary = src.compBackgroundTertiary!;
        if (src.compBackgroundEmphasize !== undefined) dst.compBackgroundEmphasize = src.compBackgroundEmphasize!;
        if (src.compBackgroundNeutral !== undefined) dst.compBackgroundNeutral = src.compBackgroundNeutral!;
        if (src.compEmphasizeSecondary !== undefined) dst.compEmphasizeSecondary = src.compEmphasizeSecondary!;
        if (src.compEmphasizeTertiary !== undefined) dst.compEmphasizeTertiary = src.compEmphasizeTertiary!;
        if (src.compDivider !== undefined) dst.compDivider = src.compDivider!;
        if (src.compCommonContrary !== undefined) dst.compCommonContrary = src.compCommonContrary!;
        if (src.compBackgroundFocus !== undefined) dst.compBackgroundFocus = src.compBackgroundFocus!;
        if (src.compFocusedPrimary !== undefined) dst.compFocusedPrimary = src.compFocusedPrimary!;
        if (src.compFocusedSecondary !== undefined) dst.compFocusedSecondary = src.compFocusedSecondary!;
        if (src.compFocusedTertiary !== undefined) dst.compFocusedTertiary = src.compFocusedTertiary!;

        if (src.interactiveHover !== undefined) dst.interactiveHover = src.interactiveHover!;
        if (src.interactivePressed !== undefined) dst.interactivePressed = src.interactivePressed!;
        if (src.interactiveFocus !== undefined) dst.interactiveFocus = src.interactiveFocus!;
        if (src.interactiveActive !== undefined) dst.interactiveActive = src.interactiveActive!;
        if (src.interactiveSelect !== undefined) dst.interactiveSelect = src.interactiveSelect!;
        if (src.interactiveClick !== undefined) dst.interactiveClick = src.interactiveClick!;
    }

    static expandByBrandColor(colors: CustomColors) {
        console.warn(`FZY expandByBrandColor ${Object.keys(colors)}`)
        console.warn(`FZY expandByBrandColor ${Object.values(colors)}`)
        if (colors!.brand) {
            const brandColors: BrandColors = ArkColorsImpl.makeBrandColors(colors.brand);
            colors.fontEmphasize = colors.fontEmphasize ?? brandColors.primary!;

            colors.iconEmphasize = colors.iconEmphasize ?? brandColors.primary!;
            colors.iconSubEmphasize = colors.iconSubEmphasize ?? brandColors.tertiary!;

            colors.backgroundEmphasize = colors.backgroundEmphasize ?? brandColors.primary!;

            colors.compBackgroundEmphasize = colors.compBackgroundEmphasize ?? brandColors.primary!;

            colors.compEmphasizeSecondary = colors.compEmphasizeSecondary ?? brandColors.fourth!;
            colors.compEmphasizeTertiary = colors.compEmphasizeTertiary ?? brandColors.fifth!;

            colors.interactiveFocus = colors.interactiveFocus ?? brandColors.primary!;
            colors.interactiveActive = colors.interactiveActive ?? brandColors.primary!;
        }
    }

    static makeBrandColors(brandColor: ResourceColor | undefined): BrandColors {
        const result: BrandColors = {
            primary: undefined,
            secondary: undefined,
            tertiary: undefined,
            fourth: undefined,
            fifth: undefined,
            sixth: undefined,
        };
        if (brandColor) {
            if (brandColor instanceof Color) {
                result.primary = ArkColorsImpl.convertColorEnumToValue(brandColor) as string;
                result.secondary = ArkColorsImpl.convertColorEnumToValue(brandColor) as string;
                result.tertiary = ArkColorsImpl.convertColorEnumToValue(brandColor) as string;
                result.fourth = ArkColorsImpl.convertColorEnumToValue(brandColor) as string;
                result.fifth = ArkColorsImpl.convertColorEnumToValue(brandColor) as string;
                result.sixth = ArkColorsImpl.convertColorEnumToValue(brandColor) as string;
            } else if (brandColor instanceof Resource) {
                result.primary = brandColor as Resource;
                result.secondary = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.6) as Resource;
                result.tertiary = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.4) as Resource;
                result.fourth = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.2) as Resource;
                result.fifth = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.1) as Resource;
                result.sixth = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.05) as Resource;
            } else {
                const brandColorValue = brandColor as number | string;
                const argbColor = ArkUIAniModule._GetColorValue(brandColorValue);
                result.primary = argbColor;
                result.secondary = ArkColorsImpl.blendOpacity(argbColor, 0.6);
                result.tertiary = ArkColorsImpl.blendOpacity(argbColor, 0.4);
                result.fourth = ArkColorsImpl.blendOpacity(argbColor, 0.2);
                result.fifth = ArkColorsImpl.blendOpacity(argbColor, 0.1);
                result.sixth = ArkColorsImpl.blendOpacity(argbColor, 0.05);
            }
        }
        return result;
    }

    static makeResourceWithOpacity(resourceColor: Resource, opacityRatio: number): ArkThemeResource {
        return {
            id: resourceColor.id,
            type: resourceColor.type,
            params: [...resourceColor.params!],
            bundleName: resourceColor.bundleName,
            moduleName: resourceColor.moduleName,
            opacityRatio: opacityRatio,
        } as ArkThemeResource;
    }

    static blendOpacity(argbColor: number, opacityRatio: number): number {
        if (opacityRatio < 0 || opacityRatio > 1.0) {
            return argbColor;
        }
        const alpha = (argbColor >> 24) & 0xff;
        const outAlpha = (alpha * opacityRatio) & 0xff;
        return ((argbColor & 0x00ffffff) | ((outAlpha & 0xff) << 24)) >>> 0;
    }

    static convertColorEnumToValue(color: Color): string {
        switch (color) {
            case Color.WHITE:
            case Color.White:
                return '#ffffffff';
            case Color.BLACK:
            case Color.Black:
                return '#ff000000';
            case Color.BLUE:
            case Color.Blue:
                return '#ff0000ff';
            case Color.BROWN:
            case Color.Brown:
                return '#ffa52a2a';
            case Color.GRAY:
            case Color.Gray:
                return '#ff808080';
            case Color.GREEN:
            case Color.Green:
                return '#ff008000';
            case Color.GREY:
            case Color.Grey:
                return '#ff808080';
            case Color.ORANGE:
            case Color.Orange:
                return '#ffffa500';
            case Color.PINK:
            case Color.Pink:
                return '#ffffc0cb';
            case Color.RED:
            case Color.Red:
                return '#ffff0000';
            case Color.YELLOW:
            case Color.Yellow:
                return '#ffffff00';
            case Color.TRANSPARENT:
            case Color.Transparent:
                return '#00000000';
        }
        // Do not match the color, return the default.
        return '#ff000000';
    }

    static checkIsColor(value: ResourceColor): boolean {
        return value instanceof Color;
    }
}