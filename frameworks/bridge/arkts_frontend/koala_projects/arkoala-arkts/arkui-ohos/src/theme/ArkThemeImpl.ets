/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ArkThemeBase } from './ArkThemeBase';
import { ThemeColorMode } from 'arkui/component/common';
import { ArkShapesImpl } from './ArkShapesImpl';
import { ArkTypographyImpl } from './ArkTypographyImpl';
import { ArkColorsImpl } from './ArkColorsImpl';
import { CustomThemeInternal } from '../theme';
import { CustomTheme } from '@ohos/arkui/theme';

export class ArkThemeImpl extends ArkThemeBase {
    constructor(
        customTheme: CustomTheme | undefined,
        colorMode: ThemeColorMode,
        baselineTheme: ArkThemeBase,
    ) {
        super(
            baselineTheme.id,
            customTheme,
            colorMode,
            new ArkColorsImpl(customTheme ? customTheme.colors : undefined, baselineTheme.colors),
            new ArkColorsImpl(customTheme ? customTheme.darkColors : undefined, baselineTheme.darkColors),
            new ArkShapesImpl(
                customTheme ? (customTheme as CustomThemeInternal).shapes : undefined,
                baselineTheme.shapes
            ),
            new ArkTypographyImpl(
                customTheme ? (customTheme as CustomThemeInternal).typography : undefined,
                baselineTheme.typography
            )
        );
    }
}
