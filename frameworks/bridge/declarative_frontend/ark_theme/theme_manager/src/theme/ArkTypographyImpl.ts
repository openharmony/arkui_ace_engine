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
class ArkTypographyImpl implements Typography {
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

    constructor(
        typography: CustomTypography,
        baselineTypography: Typography)
    {
        // Display
        this.displayLarge = {
            weight: typography?.displayLarge?.weight ?? ArkTypographyWeights.light,
            size: typography?.displayLarge?.size ?? baselineTypography.displayLarge.size
        };
        this.displayMiddle = {
            weight: typography?.displayMiddle?.weight ?? ArkTypographyWeights.light,
            size: typography?.displayMiddle?.size ?? baselineTypography.displayMiddle.size
        };
        this.displaySmall = {
            weight: typography?.displaySmall?.weight ?? ArkTypographyWeights.light,
            size: typography?.displaySmall?.size ?? baselineTypography.displaySmall.size
        };

        // Title
        this.titleLarge = {
            weight: typography?.titleLarge?.weight ?? ArkTypographyWeights.bold,
            size: typography?.titleLarge?.size ?? baselineTypography.titleLarge.size
        };
        this.titleMiddle = {
            weight: typography?.titleMiddle?.weight ?? ArkTypographyWeights.bold,
            size: typography?.titleMiddle?.size ?? baselineTypography.titleMiddle.size
        };
        this.titleSmall = {
            weight: typography?.titleSmall?.weight ?? ArkTypographyWeights.bold,
            size: typography?.titleSmall?.size ?? baselineTypography.titleSmall.size
        };

        // Subtitle
        this.subtitleLarge = {
            weight: typography?.subtitleLarge?.weight ?? ArkTypographyWeights.medium,
            size: typography?.subtitleLarge?.size ?? baselineTypography.subtitleLarge.size
        };
        this.subtitleMiddle = {
            weight: typography?.subtitleMiddle?.weight ?? ArkTypographyWeights.medium,
            size: typography?.subtitleMiddle?.size ?? baselineTypography.subtitleMiddle.size
        };
        this.subtitleSmall = {
            weight: typography?.subtitleSmall?.weight ?? ArkTypographyWeights.medium,
            size: typography?.subtitleSmall?.size ?? baselineTypography.subtitleSmall.size
        };

        // Body
        this.bodyLarge = {
            weight: typography?.bodyLarge?.weight ?? ArkTypographyWeights.medium,
            size: typography?.bodyLarge?.size ?? baselineTypography.bodyLarge.size
        };
        this.bodyMiddle = {
            weight: typography?.bodyMiddle?.weight ?? ArkTypographyWeights.regular,
            size: typography?.bodyMiddle?.size ?? baselineTypography.bodyMiddle.size
        };
        this.bodySmall = {
            weight: typography?.bodySmall?.weight ?? ArkTypographyWeights.regular,
            size: typography?.bodySmall?.size ?? baselineTypography.bodySmall.size
        };

        // Caption
        this.captionLarge = {
            weight: typography?.captionLarge?.weight ?? ArkTypographyWeights.medium,
            size: typography?.captionLarge?.size ?? baselineTypography.captionLarge.size
        };
        this.captionMiddle = {
            weight: typography?.captionMiddle?.weight ?? ArkTypographyWeights.medium,
            size: typography?.captionMiddle?.size ?? baselineTypography.captionMiddle.size
        };
        this.captionSmall = {
            weight: typography?.captionSmall?.weight ?? ArkTypographyWeights.medium,
            size: typography?.captionSmall?.size ?? baselineTypography.captionSmall.size
        };
    }
}