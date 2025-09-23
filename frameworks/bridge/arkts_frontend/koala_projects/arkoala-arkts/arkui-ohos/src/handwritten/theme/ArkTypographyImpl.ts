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

import { Typography, TypographyStyle, CustomTypography } from 'arkui/handwritten/theme';
import { ArkTypographyWeights } from './system/ArkSystemTypography';

export class ArkTypographyImpl implements Typography {
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
        typography: CustomTypography | undefined,
        baselineTypography: Typography) {
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

    static assign(dst: Typography, src: Typography): void {
        // Display
        if (src.displayLarge !== undefined) dst.displayLarge = src.displayLarge;
        if (src.displayMiddle !== undefined) dst.displayMiddle = src.displayMiddle;
        if (src.displaySmall !== undefined) dst.displaySmall = src.displaySmall;
        
        // Title
        if (src.titleLarge !== undefined) dst.titleLarge = src.titleLarge;
        if (src.titleMiddle !== undefined) dst.titleMiddle = src.titleMiddle;
        if (src.titleSmall !== undefined) dst.titleSmall = src.titleSmall;
        
        // Subtitle
        if (src.subtitleLarge !== undefined) dst.subtitleLarge = src.subtitleLarge;
        if (src.subtitleMiddle !== undefined) dst.subtitleMiddle = src.subtitleMiddle;
        if (src.subtitleSmall !== undefined) dst.subtitleSmall = src.subtitleSmall;
        
        // Body
        if (src.bodyLarge !== undefined) dst.bodyLarge = src.bodyLarge;
        if (src.bodyMiddle !== undefined) dst.bodyMiddle = src.bodyMiddle;
        if (src.bodySmall !== undefined) dst.bodySmall = src.bodySmall;
        
        // Caption
        if (src.captionLarge !== undefined) dst.captionLarge = src.captionLarge;
        if (src.captionMiddle !== undefined) dst.captionMiddle = src.captionMiddle;
        if (src.captionSmall !== undefined) dst.captionSmall = src.captionSmall;
    }

    static assign(dst: Typography, src: CustomTypography): void {
        // Display
        if (src.displayLarge?.weight !== undefined) dst.displayLarge.weight = src.displayLarge!.weight!;
        if (src.displayLarge?.size !== undefined) dst.displayLarge.size = src.displayLarge!.size!;
        
        if (src.displayMiddle?.weight !== undefined) dst.displayMiddle.weight = src.displayMiddle!.weight!;
        if (src.displayMiddle?.size !== undefined) dst.displayMiddle.size = src.displayMiddle!.size!;
        
        if (src.displaySmall?.weight !== undefined) dst.displaySmall.weight = src.displaySmall!.weight!;
        if (src.displaySmall?.size !== undefined) dst.displaySmall.size = src.displaySmall!.size!;

        // Title
        if (src.titleLarge?.weight !== undefined) dst.titleLarge.weight = src.titleLarge!.weight!;
        if (src.titleLarge?.size !== undefined) dst.titleLarge.size = src.titleLarge!.size!;
        
        if (src.titleMiddle?.weight !== undefined) dst.titleMiddle.weight = src.titleMiddle!.weight!;
        if (src.titleMiddle?.size !== undefined) dst.titleMiddle.size = src.titleMiddle!.size!;
        
        if (src.titleSmall?.weight !== undefined) dst.titleSmall.weight = src.titleSmall!.weight!;
        if (src.titleSmall?.size !== undefined) dst.titleSmall.size = src.titleSmall!.size!;

        // Subtitle
        if (src.subtitleLarge?.weight !== undefined) dst.subtitleLarge.weight = src.subtitleLarge!.weight!;
        if (src.subtitleLarge?.size !== undefined) dst.subtitleLarge.size = src.subtitleLarge!.size!;
        
        if (src.subtitleMiddle?.weight !== undefined) dst.subtitleMiddle.weight = src.subtitleMiddle!.weight!;
        if (src.subtitleMiddle?.size !== undefined) dst.subtitleMiddle.size = src.subtitleMiddle!.size!;
        
        if (src.subtitleSmall?.weight !== undefined) dst.subtitleSmall.weight = src.subtitleSmall!.weight!;
        if (src.subtitleSmall?.size !== undefined) dst.subtitleSmall.size = src.subtitleSmall!.size!;

        // Body
        if (src.bodyLarge?.weight !== undefined) dst.bodyLarge.weight = src.bodyLarge!.weight!;
        if (src.bodyLarge?.size !== undefined) dst.bodyLarge.size = src.bodyLarge!.size!;
        
        if (src.bodyMiddle?.weight !== undefined) dst.bodyMiddle.weight = src.bodyMiddle!.weight!;
        if (src.bodyMiddle?.size !== undefined) dst.bodyMiddle.size = src.bodyMiddle!.size!;
        
        if (src.bodySmall?.weight !== undefined) dst.bodySmall.weight = src.bodySmall!.weight!;
        if (src.bodySmall?.size !== undefined) dst.bodySmall.size = src.bodySmall!.size!;

        // Caption
        if (src.captionLarge?.weight !== undefined) dst.captionLarge.weight = src.captionLarge!.weight!;
        if (src.captionLarge?.size !== undefined) dst.captionLarge.size = src.captionLarge!.size!;
        
        if (src.captionMiddle?.weight !== undefined) dst.captionMiddle.weight = src.captionMiddle!.weight!;
        if (src.captionMiddle?.size !== undefined) dst.captionMiddle.size = src.captionMiddle!.size!;
        
        if (src.captionSmall?.weight !== undefined) dst.captionSmall.weight = src.captionSmall!.weight!;
        if (src.captionSmall?.size !== undefined) dst.captionSmall.size = src.captionSmall!.size!;
    }
}