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
        this.brand = ArkResourcesHelper.$r('sys.color.brand');
        this.warning = ArkResourcesHelper.$r('sys.color.warning');
        this.alert = ArkResourcesHelper.$r('sys.color.alert');
        this.confirm = ArkResourcesHelper.$r('sys.color.confirm');

        this.fontPrimary = ArkResourcesHelper.$r('sys.color.font_primary');
        this.fontSecondary = ArkResourcesHelper.$r('sys.color.font_secondary');
        this.fontTertiary = ArkResourcesHelper.$r('sys.color.font_tertiary');
        this.fontFourth = ArkResourcesHelper.$r('sys.color.font_fourth');
        this.fontEmphasize = ArkResourcesHelper.$r('sys.color.font_emphasize');

        this.fontOnPrimary = ArkResourcesHelper.$r('sys.color.font_on_primary');
        this.fontOnSecondary = ArkResourcesHelper.$r('sys.color.font_on_secondary');
        this.fontOnTertiary = ArkResourcesHelper.$r('sys.color.font_on_tertiary');
        this.fontOnFourth = ArkResourcesHelper.$r('sys.color.font_on_fourth');

        this.iconPrimary = ArkResourcesHelper.$r('sys.color.icon_primary');
        this.iconSecondary = ArkResourcesHelper.$r('sys.color.icon_secondary');
        this.iconTertiary = ArkResourcesHelper.$r('sys.color.icon_tertiary');
        this.iconFourth = ArkResourcesHelper.$r('sys.color.icon_fourth');
        this.iconEmphasize = ArkResourcesHelper.$r('sys.color.icon_emphasize');
        this.iconSubEmphasize = ArkResourcesHelper.$r('sys.color.icon_sub_emphasize');

        this.iconOnPrimary = ArkResourcesHelper.$r('sys.color.icon_on_primary');
        this.iconOnSecondary = ArkResourcesHelper.$r('sys.color.icon_on_secondary');
        this.iconOnTertiary = ArkResourcesHelper.$r('sys.color.icon_on_tertiary');
        this.iconOnFourth = ArkResourcesHelper.$r('sys.color.icon_on_fourth');

        this.backgroundPrimary = ArkResourcesHelper.$r('sys.color.background_primary');
        this.backgroundSecondary = ArkResourcesHelper.$r('sys.color.background_secondary');
        this.backgroundTertiary = ArkResourcesHelper.$r('sys.color.background_tertiary');
        this.backgroundFourth = ArkResourcesHelper.$r('sys.color.background_fourth');
        this.backgroundEmphasize = ArkResourcesHelper.$r('sys.color.background_emphasize');

        this.compForegroundPrimary = ArkResourcesHelper.$r('sys.color.comp_foreground_primary');
        this.compBackgroundPrimary = ArkResourcesHelper.$r('sys.color.comp_background_primary');
        this.compBackgroundPrimaryTran = ArkResourcesHelper.$r('sys.color.comp_background_primary_tran');
        this.compBackgroundPrimaryContrary = ArkResourcesHelper.$r('sys.color.comp_background_primary_contrary');
        this.compBackgroundGray = ArkResourcesHelper.$r('sys.color.comp_background_gray');
        this.compBackgroundSecondary = ArkResourcesHelper.$r('sys.color.comp_background_secondary');
        this.compBackgroundTertiary = ArkResourcesHelper.$r('sys.color.comp_background_tertiary');
        this.compBackgroundEmphasize = ArkResourcesHelper.$r('sys.color.comp_background_emphasize');
        this.compBackgroundNeutral = ArkResourcesHelper.$r('sys.color.neutral');
        this.compEmphasizeSecondary = ArkResourcesHelper.$r('sys.color.comp_emphasize_secondary');
        this.compEmphasizeTertiary = ArkResourcesHelper.$r('sys.color.comp_emphasize_tertiary');
        this.compDivider = ArkResourcesHelper.$r('sys.color.comp_divider');
        this.compCommonContrary = ArkResourcesHelper.$r('sys.color.comp_common_contrary');
        this.compBackgroundFocus = ArkResourcesHelper.$r('sys.color.comp_background_focus');
        this.compFocusedPrimary = ArkResourcesHelper.$r('sys.color.comp_focused_primary');
        this.compFocusedSecondary = ArkResourcesHelper.$r('sys.color.comp_focused_secondary');
        this.compFocusedTertiary = ArkResourcesHelper.$r('sys.color.comp_focused_tertiary');

        this.interactiveHover = ArkResourcesHelper.$r('sys.color.interactive_hover');
        this.interactivePressed = ArkResourcesHelper.$r('sys.color.interactive_pressed');
        this.interactiveFocus = ArkResourcesHelper.$r('sys.color.interactive_focus');
        this.interactiveActive = ArkResourcesHelper.$r('sys.color.interactive_active');
        this.interactiveSelect = ArkResourcesHelper.$r('sys.color.interactive_select');
        this.interactiveClick = ArkResourcesHelper.$r('sys.color.interactive_click');
    }
}