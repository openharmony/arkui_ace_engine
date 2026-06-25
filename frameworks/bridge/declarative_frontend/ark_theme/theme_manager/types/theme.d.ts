/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// interface_sdk-js/api/@ohos.arkui.theme.d.ts
declare interface Colors {
  brand: ResourceColor;
  warning: ResourceColor;
  alert: ResourceColor;
  confirm: ResourceColor;
  fontPrimary: ResourceColor;
  fontSecondary: ResourceColor;
  fontTertiary: ResourceColor;
  fontFourth: ResourceColor;
  fontOnPrimary: ResourceColor;
  fontOnSecondary: ResourceColor;
  fontOnTertiary: ResourceColor;
  fontOnFourth: ResourceColor;
  fontEmphasize: ResourceColor;
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
  primary?: ResourceColor;
  onPrimary?: ResourceColor;
  container?: ResourceColor;
}

// interface_sdk-js/api/@ohos.arkui.theme.d.ts
declare interface Theme {
    colors: Colors;
}

// interface_sdk-js/api/@ohos.arkui.theme.d.ts
declare type CustomColors = Partial<Colors>;
// interface_sdk-js/api/@ohos.arkui.theme.d.ts
declare type CustomDarkColors = Partial<Colors>;

// interface_sdk-js/api/@ohos.arkui.theme.d.ts
declare interface CustomTheme {
    /**
    * Define tokens associated with color resources..
    *
    * @type { ?CustomColors }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @crossplatform
    * @atomicservice
    * @since 12 dynamic
    */
    colors?: CustomColors;

    /**
    * Define tokens associated with dark mode color resources.
    *
    * @type { ?CustomDarkColors }
    * @default If not set darkColors, color value will same as colors under light mode and will not change with color
    * mode, unless the color is setted by resource in dark directory.
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @crossplatform
    * @atomicservice
    * @since 20 dynamic
    */
    darkColors?: CustomDarkColors;
}

declare interface WithThemeOptions {
    /**
    * Custom Theme.
    *
    * @type { ?CustomTheme }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @crossplatform
    * @atomicservice
    * @since 12 dynamic
    */
    theme?: CustomTheme;

    /**
    * Theme Color Mode.
    *
    * @type { ?ThemeColorMode }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @crossplatform
    * @atomicservice
    * @since 12 dynamic
    */
    colorMode?: ThemeColorMode;
}

declare interface CustomThemeInternal extends CustomTheme {
    shapes?: CustomShapes;
    typography?: CustomTypography;
}

declare const WithTheme: {
    sendThemeToNative(lightColors: ResourceColor[], darkColors: ResourceColor[], elmtId: number, darkSetStatus: boolean): void;
};