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
import { ArkThemeScopeManager } from 'arkui/handwritten/theme/ArkThemeScopeManager';
import { ArkResourcesHelper } from 'arkui/handwritten/theme/ArkResourcesHelper';
import { ArkSystemShapes } from 'arkui/handwritten/theme/system/ArkSystemShapes';
import { ArkSystemTypography } from 'arkui/handwritten/theme/system/ArkSystemTypography';
import { Shapes, Typography, CustomTypography, CustomShapes, BrandColors, ArkThemeResource } from 'arkui/handwritten/theme';
import { Resource } from 'global.resource';
import { ArkUIAniModule } from 'arkui.ani';

export class Colors {
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

    constructor() { }

    constructor(colors: CustomColors | undefined, baselineColors: Colors) {
        Colors.assign(this, baselineColors);
        if (colors) {
            Colors.assign(this, colors!);
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

    static expandByBrandColor(colors: CustomColors) {
        if (colors.brand) {
            const brandColors: BrandColors = Colors.makeBrandColors(colors.brand);
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
                result.primary = brandColor as string;
                result.secondary = brandColor as string;
                result.tertiary = brandColor as string;
                result.fourth = brandColor as string;
                result.fifth = brandColor as string;
                result.sixth = brandColor as string;
            } else if (brandColor instanceof Resource) {
                result.primary = brandColor as Resource;
                result.secondary = Colors.makeResourceWithOpacity(brandColor as Resource, 0.6) as Resource;
                result.tertiary = Colors.makeResourceWithOpacity(brandColor as Resource, 0.4) as Resource;
                result.fourth = Colors.makeResourceWithOpacity(brandColor as Resource, 0.2) as Resource;
                result.fifth = Colors.makeResourceWithOpacity(brandColor as Resource, 0.1) as Resource;
                result.sixth = Colors.makeResourceWithOpacity(brandColor as Resource, 0.05) as Resource;
            } else {
                const brandColorValue = brandColor as number | string;
                const argbColor = Colors.getColorValue(brandColorValue);
                result.primary = argbColor;
                result.secondary = Colors.blendOpacity(argbColor, 0.6);
                result.tertiary = Colors.blendOpacity(argbColor, 0.4);
                result.fourth = Colors.blendOpacity(argbColor, 0.2);
                result.fifth = Colors.blendOpacity(argbColor, 0.1);
                result.sixth = Colors.blendOpacity(argbColor, 0.05);
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

    static checkIsColor(value: ResourceColor): boolean {
        return value instanceof Color;
    }

    static getColorValue(src: number | string): int {
        if (typeof src === 'number') {
            return ArkUIAniModule._GetNumberColorValue(src as number);
        } else if (typeof src === 'string') {
            return ArkUIAniModule._GetStringColorValue(src as string);
        }
        return 0;
    }
}

export type CustomColors = Colors;

export class Theme {
    colors: Colors;
    shapes: Shapes;
    typography: Typography;

    constructor() {
        this.colors = new Colors();
        this.shapes = new ArkSystemShapes();
        this.typography = new ArkSystemTypography();
    }

    constructor(colors: Colors, shapes: Shapes, typography: Typography) {
        this.colors = colors;
        this.shapes = shapes;
        this.typography = typography;
    }
}

export class CustomTheme {
    colors?: CustomColors;
    shapes?: CustomShapes;
    typography?: CustomTypography;

    constructor() {
        this.colors = undefined;
        this.shapes = undefined;
        this.typography = undefined;
    }

    constructor(colors: CustomColors) {
        this.colors = colors;
    }

    constructor(colors: CustomColors, shapes: CustomShapes, typography: CustomTypography) {
        this.colors = colors;
        this.shapes = shapes;
        this.typography = typography;
    }
}

export class ThemeControl {
    static setDefaultTheme(customTheme: CustomTheme) {
        ArkThemeScopeManager.getInstance().setDefaultTheme(customTheme);
    }
}
