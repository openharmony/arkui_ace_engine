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
        corners: CustomCornerRadius = {},
        baselineCorners: CornerRadius
    ) {
        this.none = corners?.none ?? baselineCorners.none;
        this.level1 = corners?.level1 ?? baselineCorners.level1;
        this.level2 = corners?.level2 ?? baselineCorners.level2;
        this.level3 = corners?.level3 ?? baselineCorners.level3;
        this.level4 = corners?.level4 ?? baselineCorners.level4;
        this.level5 = corners?.level5 ?? baselineCorners.level5;
        this.level6 = corners?.level6 ?? baselineCorners.level6;
        this.level7 = corners?.level7 ?? baselineCorners.level7;
        this.level8 = corners?.level8 ?? baselineCorners.level8;
        this.level9 = corners?.level9 ?? baselineCorners.level9;
        this.level10 = corners?.level10 ?? baselineCorners.level10;
        this.level11 = corners?.level11 ?? baselineCorners.level11;
        this.level12 = corners?.level12 ?? baselineCorners.level12;
        this.level16 = corners?.level16 ?? baselineCorners.level16;
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
        paddings: CustomPaddings = {},
        baselinePaddings: Paddings
    ) {
        this.level0 = paddings?.level0 ?? baselinePaddings.level0;
        this.level1 = paddings?.level1 ?? baselinePaddings.level1;
        this.level2 = paddings?.level2 ?? baselinePaddings.level2;
        this.level3 = paddings?.level3 ?? baselinePaddings.level3;
        this.level4 = paddings?.level4 ?? baselinePaddings.level4;
        this.level5 = paddings?.level5 ?? baselinePaddings.level5;
        this.level6 = paddings?.level6 ?? baselinePaddings.level6;
        this.level7 = paddings?.level7 ?? baselinePaddings.level7;
        this.level8 = paddings?.level8 ?? baselinePaddings.level8;
        this.level9 = paddings?.level9 ?? baselinePaddings.level9;
        this.level10 = paddings?.level10 ?? baselinePaddings.level10;
        this.level11 = paddings?.level11 ?? baselinePaddings.level11;
        this.level12 = paddings?.level12 ?? baselinePaddings.level12;
        this.level16 = paddings?.level16 ?? baselinePaddings.level16;
        this.level24 = paddings?.level24 ?? baselinePaddings.level24;
        this.level32 = paddings?.level32 ?? baselinePaddings.level32;
        this.level36 = paddings?.level36 ?? baselinePaddings.level36;
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
        this.none = outlines?.none ?? baselineOutlines.none;
        this.xs = outlines?.xs ?? baselineOutlines.xs;
        this.s = outlines?.s ?? baselineOutlines.s;
        this.m = outlines?.m ?? baselineOutlines.m;
        this.l = outlines?.l ?? baselineOutlines.l;
        this.xl = outlines?.xl ?? baselineOutlines.xl;
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
        this.none = borders?.none ?? baselineBorders.none;
        this.xs = borders?.xs ?? baselineBorders.xs;
        this.s = borders?.s ?? baselineBorders.s;
        this.m = borders?.m ?? baselineBorders.m;
        this.l = borders?.l ?? baselineBorders.l;
        this.xl = borders?.xl ?? baselineBorders.xl;
    }
}

class ArkShapesImpl implements Shapes {
    cornerRadius: CornerRadius;
    paddings: Paddings;
    borders: Borders;
    outlines: Outlines;

    constructor(
        shapes: CustomShapes = {},
        baselineShapes: Shapes
    ) {
        this.cornerRadius = new ArkCornerRadiusImpl(shapes?.cornerRadius, baselineShapes.cornerRadius);
        this.paddings = new ArkPaddingsImpl(shapes?.paddings, baselineShapes.paddings);
        this.borders = new ArkBordersImpl(shapes?.borders, baselineShapes.borders);
        this.outlines = new ArkOutlinesImpl(shapes?.outlines, baselineShapes.outlines);
    }
}