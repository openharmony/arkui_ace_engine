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

/// <reference path='../import.ts' />

class ArkThemeImpl extends ArkThemeBase {
    constructor(
        customTheme: CustomThemeInternal,
        colorMode: ThemeColorMode,
        baselineTheme: ArkThemeBase,
    ) {
        if (!customTheme) {
            super(baselineTheme.id, undefined, colorMode,
              new ArkColorsImpl(undefined, baselineTheme.colors),
              new ArkColorsImpl(undefined, baselineTheme.darkColors),
              new ArkShapesImpl(undefined, baselineTheme.shapes),
              new ArkTypographyImpl(undefined, baselineTheme.typography))
            return;
        }
        super(baselineTheme.id, customTheme, colorMode,
          new ArkColorsImpl(customTheme.colors, baselineTheme.colors),
          new ArkColorsImpl(customTheme.darkColors, baselineTheme.darkColors),
          new ArkShapesImpl(customTheme.shapes, baselineTheme.shapes),
          new ArkTypographyImpl(customTheme.typography, baselineTheme.typography))
    }
}