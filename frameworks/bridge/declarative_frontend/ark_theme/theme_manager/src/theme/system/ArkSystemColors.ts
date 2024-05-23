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
class ArkSystemColors implements Colors {
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

    constructor() {
        this.brand = ArkResourcesHelper.$r('sys.color.brand', 125830976);
        this.warning = ArkResourcesHelper.$r('sys.color.warning', 125830979);
        this.alert = ArkResourcesHelper.$r('sys.color.alert', 125830980);
        this.confirm = ArkResourcesHelper.$r('sys.color.confirm', 125830981);

        this.fontPrimary = ArkResourcesHelper.$r('sys.color.font_primary', 125830982);
        this.fontSecondary = ArkResourcesHelper.$r('sys.color.font_secondary', 125830983);
        this.fontTertiary = ArkResourcesHelper.$r('sys.color.font_tertiary', 125830984);
        this.fontFourth = ArkResourcesHelper.$r('sys.color.font_fourth', 125830985);
        this.fontEmphasize = ArkResourcesHelper.$r('sys.color.font_emphasize', 125830986);

        this.fontOnPrimary = ArkResourcesHelper.$r('sys.color.font_on_primary', 125830987);
        this.fontOnSecondary = ArkResourcesHelper.$r('sys.color.font_on_secondary', 125830988);
        this.fontOnTertiary = ArkResourcesHelper.$r('sys.color.font_on_tertiary', 125830989);
        this.fontOnFourth = ArkResourcesHelper.$r('sys.color.font_on_fourth', 125830990);

        this.iconPrimary = ArkResourcesHelper.$r('sys.color.icon_primary', 125830991);
        this.iconSecondary = ArkResourcesHelper.$r('sys.color.icon_secondary', 125830992);
        this.iconTertiary = ArkResourcesHelper.$r('sys.color.icon_tertiary', 125830993);
        this.iconFourth = ArkResourcesHelper.$r('sys.color.icon_fourth', 125830994);
        this.iconEmphasize = ArkResourcesHelper.$r('sys.color.icon_emphasize', 125830995);
        this.iconSubEmphasize = ArkResourcesHelper.$r('sys.color.icon_sub_emphasize', 125830996);

        this.iconOnPrimary = ArkResourcesHelper.$r('sys.color.icon_on_primary', 125831057);
        this.iconOnSecondary = ArkResourcesHelper.$r('sys.color.icon_on_secondary', 125831058);
        this.iconOnTertiary = ArkResourcesHelper.$r('sys.color.icon_on_tertiary', 125831059);
        this.iconOnFourth = ArkResourcesHelper.$r('sys.color.icon_on_fourth', 125831060);

        this.backgroundPrimary = ArkResourcesHelper.$r('sys.color.background_primary', 125831061);
        this.backgroundSecondary = ArkResourcesHelper.$r('sys.color.background_secondary', 125831062);
        this.backgroundTertiary = ArkResourcesHelper.$r('sys.color.background_tertiary', 125831063);
        this.backgroundFourth = ArkResourcesHelper.$r('sys.color.background_fourth', 125831064);
        this.backgroundEmphasize = ArkResourcesHelper.$r('sys.color.background_emphasize', 125831065);

        this.compForegroundPrimary = ArkResourcesHelper.$r('sys.color.comp_foreground_primary', 125831003);
        this.compBackgroundPrimary = ArkResourcesHelper.$r('sys.color.comp_background_primary', 125831004);
        this.compBackgroundPrimaryTran = ArkResourcesHelper.$r('sys.color.comp_background_primary_tran');
        this.compBackgroundPrimaryContrary = ArkResourcesHelper.$r('sys.color.comp_background_primary_contrary', 125831005);
        this.compBackgroundGray = ArkResourcesHelper.$r('sys.color.comp_background_gray', 125831006);
        this.compBackgroundSecondary = ArkResourcesHelper.$r('sys.color.comp_background_secondary', 125831007);
        this.compBackgroundTertiary = ArkResourcesHelper.$r('sys.color.comp_background_tertiary', 125831008);
        this.compBackgroundEmphasize = ArkResourcesHelper.$r('sys.color.comp_background_emphasize', 125831009);
        this.compBackgroundNeutral = ArkResourcesHelper.$r('sys.color.neutral', 125831066);
        this.compEmphasizeSecondary = ArkResourcesHelper.$r('sys.color.comp_emphasize_secondary', 125831011);
        this.compEmphasizeTertiary = ArkResourcesHelper.$r('sys.color.comp_emphasize_tertiary', 125831012);
        this.compDivider = ArkResourcesHelper.$r('sys.color.comp_divider', 125831013);
        this.compCommonContrary = ArkResourcesHelper.$r('sys.color.comp_common_contrary', 125831014);
        this.compBackgroundFocus = ArkResourcesHelper.$r('sys.color.comp_background_focus', 125831015);
        this.compFocusedPrimary = ArkResourcesHelper.$r('sys.color.comp_focused_primary', 125831016);
        this.compFocusedSecondary = ArkResourcesHelper.$r('sys.color.comp_focused_secondary', 125831017);
        this.compFocusedTertiary = ArkResourcesHelper.$r('sys.color.comp_focused_tertiary', 125831018);

        this.interactiveHover = ArkResourcesHelper.$r('sys.color.interactive_hover', 125831019);
        this.interactivePressed = ArkResourcesHelper.$r('sys.color.interactive_pressed', 125831020);
        this.interactiveFocus = ArkResourcesHelper.$r('sys.color.interactive_focus', 125831021);
        this.interactiveActive = ArkResourcesHelper.$r('sys.color.interactive_active', 125831022);
        this.interactiveSelect = ArkResourcesHelper.$r('sys.color.interactive_select', 125831023);
        this.interactiveClick = ArkResourcesHelper.$r('sys.color.interactive_click', 125831024);
    }
}