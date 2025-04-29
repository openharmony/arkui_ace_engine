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

class ArkColorsImpl implements Colors {
    brand: ResourceColor;
    warning: ResourceColor;
    alert: ResourceColor;
    confirm: ResourceColor;

    fontPrimary: ResourceColor;
    fontSecondary: ResourceColor;
    fontTertiary: ResourceColor;
    fontFourth: ResourceColor;
    fontEmphasize: ResourceColor;

    fontOnPrimary: ResourceColor;
    fontOnSecondary: ResourceColor;
    fontOnTertiary: ResourceColor;
    fontOnFourth: ResourceColor;

    iconPrimary: ResourceColor;
    iconSecondary: ResourceColor;
    iconTertiary: ResourceColor;
    iconFourth: ResourceColor;
    iconEmphasize: ResourceColor;
    iconSubEmphasize: ResourceColor;

    iconOnPrimary: ResourceColor;
    iconOnSecondary: ResourceColor;
    iconOnTertiary: ResourceColor;
    iconOnFourth: ResourceColor;

    backgroundPrimary: ResourceColor;
    backgroundSecondary: ResourceColor;
    backgroundTertiary: ResourceColor;
    backgroundFourth: ResourceColor;
    backgroundEmphasize: ResourceColor;

    compForegroundPrimary: ResourceColor;
    compBackgroundPrimary: ResourceColor;
    compBackgroundPrimaryTran: ResourceColor;
    compBackgroundPrimaryContrary: ResourceColor;
    compBackgroundGray: ResourceColor;
    compBackgroundSecondary: ResourceColor;
    compBackgroundTertiary: ResourceColor;
    compBackgroundEmphasize: ResourceColor;
    compBackgroundNeutral: ResourceColor;
    compEmphasizeSecondary: ResourceColor;
    compEmphasizeTertiary: ResourceColor;
    compDivider: ResourceColor;
    compCommonContrary: ResourceColor;
    compBackgroundFocus: ResourceColor;
    compFocusedPrimary: ResourceColor;
    compFocusedSecondary: ResourceColor;
    compFocusedTertiary: ResourceColor;

    interactiveHover: ResourceColor;
    interactivePressed: ResourceColor;
    interactiveFocus: ResourceColor;
    interactiveActive: ResourceColor;
    interactiveSelect: ResourceColor;
    interactiveClick: ResourceColor;

    constructor(
        colors: CustomColors,
        baselineColors: Colors
    ) {
        Object.assign(this, baselineColors, colors);
    }

    static expandByBrandColor(colors: CustomColors) {
        if (colors.brand) {
            const brandColors: BrandColors = ArkColorsImpl.makeBrandColors(colors.brand);
            colors.fontEmphasize = colors.fontEmphasize ?? brandColors.primary;

            colors.iconEmphasize = colors.iconEmphasize ?? brandColors.primary;
            colors.iconSubEmphasize = colors.iconSubEmphasize ?? brandColors.tertiary;

            colors.backgroundEmphasize = colors.backgroundEmphasize ?? brandColors.primary;

            colors.compBackgroundEmphasize = colors.compBackgroundEmphasize ?? brandColors.primary;

            colors.compEmphasizeSecondary = colors.compEmphasizeSecondary ?? brandColors.fourth;
            colors.compEmphasizeTertiary = colors.compEmphasizeTertiary ?? brandColors.fifth;

            colors.interactiveFocus = colors.interactiveFocus ?? brandColors.primary;
            colors.interactiveActive = colors.interactiveActive ?? brandColors.primary;
        }
    }

    static makeBrandColors(brandColor: ResourceColor | undefined) : BrandColors {
        const result: BrandColors = {
            primary: undefined,
            secondary: undefined,
            tertiary: undefined,
            fourth: undefined,
            fifth: undefined,
            sixth: undefined
        };
        if (brandColor) {
            if (brandColor instanceof Object) {
                result.primary = brandColor as Resource;
                result.secondary = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.6) as Resource;
                result.tertiary = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.4) as Resource;
                result.fourth = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.2) as Resource;
                result.fifth = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.1) as Resource;
                result.sixth = ArkColorsImpl.makeResourceWithOpacity(brandColor as Resource, 0.05) as Resource;
            } else {
                const argbColor = getUINativeModule().resource.getColorValue(brandColor);
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

    static makeResourceWithOpacity(resourceColor: Resource, opacityRatio: number) : Object {
        return {
            'id': resourceColor.id,
            'type': resourceColor.type,
            'params': [...resourceColor.params],
            'bundleName': resourceColor.bundleName,
            'moduleName': resourceColor.moduleName,
            'opacityRatio': opacityRatio
        };
    }

    static blendOpacity(argbColor: number, opacityRatio: number): number {
        if (opacityRatio < 0 || opacityRatio > 1.0) {
            return argbColor;
        }
        const alpha = (argbColor >> 24) & 0xFF;
        const outAlpha = (alpha * opacityRatio) & 0xFF;
        return ((argbColor & 0x00FFFFFF) | (outAlpha & 0xFF) << 24) >>> 0;
    }
}