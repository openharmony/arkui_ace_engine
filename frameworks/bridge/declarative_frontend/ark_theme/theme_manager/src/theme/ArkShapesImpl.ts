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
class ArkCornerRadiusImpl implements CornerRadius {
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

    constructor(
        corners: CustomCornerRadius,
        baselineCorners: CornerRadius
    ) {
        Object.assign(this, baselineCorners, corners);
    }
}

class ArkPaddingsImpl implements Paddings {
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

    constructor(
        paddings: CustomPaddings,
        baselinePaddings: Paddings
    ) {
        Object.assign(this, baselinePaddings, paddings);
    }
}

class ArkOutlinesImpl implements Outlines {
    none: Dimension;
    xs: Dimension;
    s: Dimension;
    m: Dimension;
    l: Dimension;
    xl: Dimension;

    constructor(
        outlines: CustomOutlines = {},
        baselineOutlines: Outlines
    ) {
        Object.assign(this, baselineOutlines, outlines);
    }
}

class ArkBordersImpl implements Borders {
    none: Length;
    xs: Length;
    s: Length;
    m: Length;
    l: Length;
    xl: Length;

    constructor(
        borders: CustomBorders = {},
        baselineBorders: Borders
    ) {
        Object.assign(this, baselineBorders, borders);
    }
}

class ArkShapesImpl implements Shapes {
    cornerRadius: CornerRadius;
    paddings: Paddings;
    borders: Borders;
    outlines: Outlines;

    constructor(
        shapes: CustomShapes,
        baselineShapes: Shapes
    ) {
        this.cornerRadius = new ArkCornerRadiusImpl(shapes?.cornerRadius, baselineShapes.cornerRadius);
        this.paddings = new ArkPaddingsImpl(shapes?.paddings, baselineShapes.paddings);
        this.borders = new ArkBordersImpl(shapes?.borders, baselineShapes.borders);
        this.outlines = new ArkOutlinesImpl(shapes?.outlines, baselineShapes.outlines);
    }
}