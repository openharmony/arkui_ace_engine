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

import { FontWeight } from 'arkui/component/enums';
import { Length, ResourceColor } from 'arkui/component/units';
import { Resource } from 'global.resource';
import { CustomTheme, Theme } from '@ohos/arkui/theme';
import { int32 } from "@koalaui/common"

export type Dimension = Resource;

export interface CornerRadius {
    none: Length;
    level1: Length;
    level2: Length;
    level3: Length;
    level4: Length;
    level5: Length;
    level6: Length;
    level7: Length;
    level8: Length;
    level9: Length;
    level10: Length;
    level11: Length;
    level12: Length;
    level16: Length;
}

/**
 * Defines the struct of Paddings.
 *
 * @interface Paddings
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface Paddings {
    level0: Length;
    level1: Length;
    level2: Length;
    level3: Length;
    level4: Length;
    level5: Length;
    level6: Length;
    level7: Length;
    level8: Length;
    level9: Length;
    level10: Length;
    level11: Length;
    level12: Length;
    level16: Length;
    level24: Length;
    level32: Length;
    level36: Length;
}

/**
 * Defines the struct of Borders.
 *
 * @interface Borders
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface Borders {
    none: Length;
    xs: Length;
    s: Length;
    m: Length;
    l: Length;
    xl: Length;
}

/**
 * Defines the struct of Outlines.
 *
 * @interface Outlines
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface Outlines {
    none: Dimension;
    xs: Dimension;
    s: Dimension;
    m: Dimension;
    l: Dimension;
    xl: Dimension;
}

/**
 * Defines the struct of Shapes.
 *
 * @interface Shapes
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface Shapes {

    /**
    * CornerRadius Value Set.
    *
    * @type { CornerRadius }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @crossplatform
    * @atomicservice
    * @since 12
    */
    cornerRadius: CornerRadius;

    /**
    * Paddings Value Set.
    *
    * @type { Paddings }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @crossplatform
    * @atomicservice
    * @since 12
    */
    paddings: Paddings;

    /**
    * Borders Value Set.
    *
    * @type { Borders }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @crossplatform
    * @atomicservice
    * @since 12
    */
    borders: Borders;

    /**
    * Outlines Value Set.
    *
    * @type { Outlines }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @crossplatform
    * @atomicservice
    * @since 12
    */
    outlines: Outlines;
}

/**
 * Defines the struct of TypographyStyle.
 *
 * @interface TypographyStyle
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface TypographyStyle {
    weight: FontWeight | number | string | int32;
    size: Length;
}

/**
 * Defines the struct of Typography.
 *
 * @interface Typography
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface Typography {

    //display
    displayLarge: TypographyStyle;
    displayMiddle: TypographyStyle;
    displaySmall: TypographyStyle;

    // Title
    titleLarge: TypographyStyle;
    titleMiddle: TypographyStyle;
    titleSmall: TypographyStyle;

    // Subtitle
    subtitleLarge: TypographyStyle;
    subtitleMiddle: TypographyStyle;
    subtitleSmall: TypographyStyle;

    // Body
    bodyLarge: TypographyStyle;
    bodyMiddle: TypographyStyle;
    bodySmall: TypographyStyle;

    // Caption
    captionLarge: TypographyStyle;
    captionMiddle: TypographyStyle;
    captionSmall: TypographyStyle;
}
export interface CustomCornerRadius {
    none?: Length;
    level1?: Length;
    level2?: Length;
    level3?: Length;
    level4?: Length;
    level5?: Length;
    level6?: Length;
    level7?: Length;
    level8?: Length;
    level9?: Length;
    level10?: Length;
    level11?: Length;
    level12?: Length;
    level16?: Length;
}
export interface CustomPaddings {
    level0?: Length;
    level1?: Length;
    level2?: Length;
    level3?: Length;
    level4?: Length;
    level5?: Length;
    level6?: Length;
    level7?: Length;
    level8?: Length;
    level9?: Length;
    level10?: Length;
    level11?: Length;
    level12?: Length;
    level16?: Length;
    level24?: Length;
    level32?: Length;
    level36?: Length;
}
export interface CustomBorders {
    none?: Length;
    xs?: Length;
    s?: Length;
    m?: Length;
    l?: Length;
    xl?: Length;
}
export interface CustomOutlines {
    none?: Dimension;
    xs?: Dimension;
    s?: Dimension;
    m?: Dimension;
    l?: Dimension;
    xl?: Dimension;
}
export interface CustomShapes {
    cornerRadius?: CustomCornerRadius;
    paddings?: CustomPaddings;
    borders?: CustomBorders;
    outlines?: CustomOutlines;
}
export interface CustomTypographyStyle {
    weight?: FontWeight | number | string | int32;
    size?: Length;
}
export interface CustomTypography {
    displayLarge?: CustomTypographyStyle;
    displayMiddle?: CustomTypographyStyle;
    displaySmall?: CustomTypographyStyle;
    titleLarge?: CustomTypographyStyle;
    titleMiddle?: CustomTypographyStyle;
    titleSmall?: CustomTypographyStyle;
    subtitleLarge?: CustomTypographyStyle;
    subtitleMiddle?: CustomTypographyStyle;
    subtitleSmall?: CustomTypographyStyle;
    bodyLarge?: CustomTypographyStyle;
    bodyMiddle?: CustomTypographyStyle;
    bodySmall?: CustomTypographyStyle;
    captionLarge?: CustomTypographyStyle;
    captionMiddle?: CustomTypographyStyle;
    captionSmall?: CustomTypographyStyle;
}

export class BrandColors {
    primary: ResourceColor | undefined;
    secondary: ResourceColor | undefined;
    tertiary: ResourceColor | undefined;
    fourth: ResourceColor | undefined;
    fifth: ResourceColor | undefined;
    sixth: ResourceColor | undefined;
}

export function makeRecordfromObj(obj: Object): Record<string, Any> {
    let record: Record<string, Any> = {};
    const keys = Object.keys(obj);
    const values = Object.values(obj);
    keys.forEach((key: string, index: number) => {
        record[key] = values[index as int32];
    })
    return record;
}

export interface ArkThemeResource extends Resource {
    bundleName: string;
    moduleName: string;
    id: long;
    params?: Array<string | int | long | double | Resource>;
    type?: int;
    opacityRatio: number;
}

export interface ThemeInternal extends Theme {
    shapes: Shapes;
    typography: Typography;
}

export interface CustomThemeInternal extends CustomTheme {
    shapes?: CustomShapes;
    typography?: CustomTypography;
}

export { ArkThemeScopeManager } from './ArkThemeScopeManager';
