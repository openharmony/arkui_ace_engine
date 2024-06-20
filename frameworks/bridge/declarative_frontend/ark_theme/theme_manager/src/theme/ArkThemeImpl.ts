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

class ArkThemeImpl implements ThemeInternal {
    colors: Colors;
    shapes: Shapes;
    typography: Typography;

    constructor(baselineTheme: ThemeInternal, colors?: CustomColors, shapes?: CustomShapes, typography?: CustomTypography) {
      this.colors = new ArkColorsImpl(colors, baselineTheme.colors);
      this.shapes = new ArkShapesImpl(shapes, baselineTheme.shapes);
      this.typography = new ArkTypographyImpl(typography, baselineTheme.typography);
    }
}