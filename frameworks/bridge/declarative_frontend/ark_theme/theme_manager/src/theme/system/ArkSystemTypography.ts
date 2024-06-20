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
class ArkTypographyWeights {
    public static thin = 100;
    public static ultralight = 200;
    public static light = 300;
    public static regular = 400;
    public static medium = 500;
    public static semibold = 600;
    public static bold = 700;
    public static heavy = 800;
    public static black = 900;
}

class ArkSystemTypography implements Typography {
    // Display
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

    constructor() {
        // Display
        this.displayLarge = {
            weight: ArkTypographyWeights.light,
            size: ArkResourcesHelper.$r('sys.float.Display_L')
        };
        this.displayMiddle = {
            weight: ArkTypographyWeights.light,
            size: ArkResourcesHelper.$r('sys.float.Display_M')
        };
        this.displaySmall = {
            weight: ArkTypographyWeights.light,
            size: ArkResourcesHelper.$r('sys.float.Display_S')
        };

        // Title
        this.titleLarge = {
            weight: ArkTypographyWeights.bold,
            size: ArkResourcesHelper.$r('sys.float.Title_L')
        };
        this.titleMiddle = {
            weight: ArkTypographyWeights.bold,
            size: ArkResourcesHelper.$r('sys.float.Title_M')
        };
        this.titleSmall = {
            weight: ArkTypographyWeights.bold,
            size: ArkResourcesHelper.$r('sys.float.Title_S')
        };

        // Subtitle
        this.subtitleLarge = {
            weight: ArkTypographyWeights.medium,
            size: ArkResourcesHelper.$r('sys.float.Subtitle_L')
        };
        this.subtitleMiddle = {
            weight: ArkTypographyWeights.medium,
            size: ArkResourcesHelper.$r('sys.float.Subtitle_M')
        };
        this.subtitleSmall = {
            weight: ArkTypographyWeights.medium,
            size: ArkResourcesHelper.$r('sys.float.Subtitle_S')
        };

        // Body
        this.bodyLarge = {
            weight: ArkTypographyWeights.medium,
            size: ArkResourcesHelper.$r('sys.float.Body_L')
        };
        this.bodyMiddle = {
            weight: ArkTypographyWeights.regular,
            size: ArkResourcesHelper.$r('sys.float.Body_M')
        };
        this.bodySmall = {
            weight: ArkTypographyWeights.regular,
            size: ArkResourcesHelper.$r('sys.float.Body_S')
        };

        // Caption
        this.captionLarge = {
            weight: ArkTypographyWeights.medium,
            size: ArkResourcesHelper.$r('sys.float.Caption_L')
        };
        this.captionMiddle = {
            weight: ArkTypographyWeights.medium,
            size: ArkResourcesHelper.$r('sys.float.Caption_M')
        };
        this.captionSmall = {
            weight: ArkTypographyWeights.medium,
            size: ArkResourcesHelper.$r('sys.float.Caption_S')
        };
    }
}