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
/!*<!-- BOF CLEAN -->*/
let SHAPES_TOKENS_ARE_ENABLED = false
let TYPOGRAPHY_TOKENS_ARE_ENABLED = false
let OTHER_TOKENS_ARE_ENABLED = false
const arkUINativeModule = globalThis.getArkUINativeModule();
function getUINativeModule(): any {
  if (arkUINativeModule) {
    return arkUINativeModule;
  }
  return arkUINativeModule;
}
const UI_STATE_NORMAL = 0;
const UI_STATE_PRESSED = 1;
const UI_STATE_FOCUSED = 1 << 1;
const UI_STATE_DISABLED = 1 << 2;
const UI_STATE_SELECTED = 1 << 3;
class ViewStackProcessor {
    static GetElmtIdToAccountFor(): number { return 0 }
    static visualState(state?: string): void {}
}
interface ViewPuInternal {
    parent_: ViewPuInternal
    themeScope_: ArkThemeScope
    id__(): number
    onGlobalThemeChanged(): void
    forceRerenderNode(elmtId: number): void
    onWillApplyTheme(theme: Theme): void
}
class UINodeRegisterProxy {
    static ElementIdToOwningViewPU_: Map<any, any>
}

enum ThemeColorMode {
    SYSTEM,
    LIGHT,
    DARK,
}
  
// Hidden interfaces
declare interface CustomThemeInternal extends CustomTheme {
    shapes?: CustomShapes
    typography?: CustomTypography
}
declare interface CustomCornerRadius {
    none?: Length
    level1?: Length
    level2?: Length
    level3?: Length
    level4?: Length
    level5?: Length
    level6?: Length
    level7?: Length
    level8?: Length
    level9?: Length
    level10?: Length
    level11?: Length
    level12?: Length
    level16?: Length
}
declare interface CustomPaddings {
    level0?: Length
    level1?: Length
    level2?: Length
    level3?: Length
    level4?: Length
    level5?: Length
    level6?: Length
    level7?: Length
    level8?: Length
    level9?: Length
    level10?: Length
    level11?: Length
    level12?: Length
    level16?: Length
    level24?: Length
    level32?: Length
    level36?: Length
}
declare interface CustomBorders {
    none?: Length
    xs?: Length
    s?: Length
    m?: Length
    l?: Length
    xl?: Length
}
declare interface CustomOutlines {
    none?: Dimension
    xs?: Dimension
    s?: Dimension
    m?: Dimension
    l?: Dimension
    xl?: Dimension
}
declare interface CustomShapes {
    cornerRadius?: CustomCornerRadius
    paddings?: CustomPaddings
    borders?: CustomBorders
    outlines?: CustomOutlines
}
declare interface CustomTypographyStyle {
    weight?: FontWeight | number | string
    size?: Length
}
declare interface CustomTypography {
    displayLarge?: CustomTypographyStyle
    displayMiddle?: CustomTypographyStyle
    displaySmall?: CustomTypographyStyle
    titleLarge?: CustomTypographyStyle
    titleMiddle?: CustomTypographyStyle
    titleSmall?: CustomTypographyStyle
    subtitleLarge?: CustomTypographyStyle
    subtitleMiddle?: CustomTypographyStyle
    subtitleSmall?: CustomTypographyStyle
    bodyLarge?: CustomTypographyStyle
    bodyMiddle?: CustomTypographyStyle
    bodySmall?: CustomTypographyStyle
    captionLarge?: CustomTypographyStyle
    captionMiddle?: CustomTypographyStyle
    captionSmall?: CustomTypographyStyle
}
/!*<!-- EOF CLEAN -->*/
