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

import {
    CornerRadius, CustomCornerRadius, Paddings, CustomPaddings, Outlines, Dimension,
    CustomOutlines, Borders, CustomBorders, Shapes, CustomShapes
} from './index';
import { Length } from 'arkui/component/units';
import {
    ArkSystemCornerRadius,
    ArkSystemPaddings,
    ArkSystemBorders,
    ArkSystemOutlines,
} from './system/ArkSystemShapes';
import { _r } from 'arkui/component/resources';

export class ArkCornerRadiusImpl implements CornerRadius {
    none: Length = 0;
    level1: Length = 0;
    level2: Length = 0;
    level3: Length = 0;
    level4: Length = 0;
    level5: Length = 0;
    level6: Length = 0;
    level7: Length = 0;
    level8: Length = 0;
    level9: Length = 0;
    level10: Length = 0;
    level11: Length = 0;
    level12: Length = 0;
    level16: Length = 0;

    constructor(corners: CustomCornerRadius | undefined, baselineCorners: CornerRadius | undefined) {
        if (baselineCorners) {
            ArkCornerRadiusImpl.assign(this, baselineCorners!);
        }
        if (corners) {
            ArkCornerRadiusImpl.assign(this, corners!);
        }
    }

    static assign(dst: CornerRadius, src: CornerRadius): void {
        if (src.none !== undefined) dst.none = src.none!;
        if (src.level1 !== undefined) dst.level1 = src.level1;
        if (src.level2 !== undefined) dst.level2 = src.level2;
        if (src.level3 !== undefined) dst.level3 = src.level3;
        if (src.level4 !== undefined) dst.level4 = src.level4;
        if (src.level5 !== undefined) dst.level5 = src.level5;
        if (src.level6 !== undefined) dst.level6 = src.level6;
        if (src.level7 !== undefined) dst.level7 = src.level7;
        if (src.level8 !== undefined) dst.level8 = src.level8;
        if (src.level9 !== undefined) dst.level9 = src.level9;
        if (src.level10 !== undefined) dst.level10 = src.level10;
        if (src.level11 !== undefined) dst.level11 = src.level11;
        if (src.level12 !== undefined) dst.level12 = src.level12;
        if (src.level16 !== undefined) dst.level16 = src.level16;
    }

    static assign(dst: CornerRadius, src: CustomCornerRadius): void {
        if (src.none !== undefined) dst.none = src.none!;
        if (src.level1 !== undefined) dst.level1 = src.level1!;
        if (src.level2 !== undefined) dst.level2 = src.level2!;
        if (src.level3 !== undefined) dst.level3 = src.level3!;
        if (src.level4 !== undefined) dst.level4 = src.level4!;
        if (src.level5 !== undefined) dst.level5 = src.level5!;
        if (src.level6 !== undefined) dst.level6 = src.level6!;
        if (src.level7 !== undefined) dst.level7 = src.level7!;
        if (src.level8 !== undefined) dst.level8 = src.level8!;
        if (src.level9 !== undefined) dst.level9 = src.level9!;
        if (src.level10 !== undefined) dst.level10 = src.level10!;
        if (src.level11 !== undefined) dst.level11 = src.level11!;
        if (src.level12 !== undefined) dst.level12 = src.level12!;
        if (src.level16 !== undefined) dst.level16 = src.level16!;
    }
}

export class ArkPaddingsImpl implements Paddings {
    level0: Length = 0;
    level1: Length = 0;
    level2: Length = 0;
    level3: Length = 0;
    level4: Length = 0;
    level5: Length = 0;
    level6: Length = 0;
    level7: Length = 0;
    level8: Length = 0;
    level9: Length = 0;
    level10: Length = 0;
    level11: Length = 0;
    level12: Length = 0;
    level16: Length = 0;
    level24: Length = 0;
    level32: Length = 0;
    level36: Length = 0;

    constructor(
        paddings: CustomPaddings | undefined,
        baselinePaddings: Paddings
    ) {
        ArkPaddingsImpl.assign(this, baselinePaddings);
        if (paddings) {
            ArkPaddingsImpl.assign(this, paddings!);
        }
    }

    static assign(dst: Paddings, src: Paddings): void {
        if (src.level0 !== undefined) dst.level0 = src.level0;
        if (src.level1 !== undefined) dst.level1 = src.level1;
        if (src.level2 !== undefined) dst.level2 = src.level2;
        if (src.level3 !== undefined) dst.level3 = src.level3;
        if (src.level4 !== undefined) dst.level4 = src.level4;
        if (src.level5 !== undefined) dst.level5 = src.level5;
        if (src.level6 !== undefined) dst.level6 = src.level6;
        if (src.level7 !== undefined) dst.level7 = src.level7;
        if (src.level8 !== undefined) dst.level8 = src.level8;
        if (src.level9 !== undefined) dst.level9 = src.level9;
        if (src.level10 !== undefined) dst.level10 = src.level10;
        if (src.level11 !== undefined) dst.level11 = src.level11;
        if (src.level12 !== undefined) dst.level12 = src.level12;
        if (src.level16 !== undefined) dst.level16 = src.level16;
        if (src.level24 !== undefined) dst.level24 = src.level24;
        if (src.level32 !== undefined) dst.level32 = src.level32;
        if (src.level36 !== undefined) dst.level36 = src.level36;
    }

    static assign(dst: Paddings, src: CustomPaddings): void {
        if (src.level0 !== undefined) dst.level0 = src.level0!;
        if (src.level1 !== undefined) dst.level1 = src.level1!;
        if (src.level2 !== undefined) dst.level2 = src.level2!;
        if (src.level3 !== undefined) dst.level3 = src.level3!;
        if (src.level4 !== undefined) dst.level4 = src.level4!;
        if (src.level5 !== undefined) dst.level5 = src.level5!;
        if (src.level6 !== undefined) dst.level6 = src.level6!;
        if (src.level7 !== undefined) dst.level7 = src.level7!;
        if (src.level8 !== undefined) dst.level8 = src.level8!;
        if (src.level9 !== undefined) dst.level9 = src.level9!;
        if (src.level10 !== undefined) dst.level10 = src.level10!;
        if (src.level11 !== undefined) dst.level11 = src.level11!;
        if (src.level12 !== undefined) dst.level12 = src.level12!;
        if (src.level16 !== undefined) dst.level16 = src.level16!;
        if (src.level24 !== undefined) dst.level24 = src.level24!;
        if (src.level32 !== undefined) dst.level32 = src.level32!;
        if (src.level36 !== undefined) dst.level36 = src.level36!;
    }
}

export class ArkOutlinesImpl implements Outlines {
    none: Dimension = _r('', '', 'sys.float.outline_none');
    xs: Dimension = _r('', '', 'sys.float.outline_extra_small');
    s: Dimension = _r('', '', 'sys.float.outline_small');
    m: Dimension = _r('', '', 'sys.float.outline_medium');
    l: Dimension = _r('', '', 'sys.float.outline_larger');
    xl: Dimension = _r('', '', 'sys.float.outline_extra_larger');

    constructor(outlines: CustomOutlines | undefined, baselineOutlines: Outlines) {
        ArkOutlinesImpl.assign(this, baselineOutlines);
        if (outlines) {
            ArkOutlinesImpl.assign(this, outlines!);
        }
    }

    static assign(dst: Outlines, src: Outlines): void {
        if (src.none !== undefined) dst.none = src.none;
        if (src.xs !== undefined) dst.xs = src.xs;
        if (src.s !== undefined) dst.s = src.s;
        if (src.m !== undefined) dst.m = src.m;
        if (src.l !== undefined) dst.l = src.l;
        if (src.xl !== undefined) dst.xl = src.xl;
    }

    static assign(dst: Outlines, src: CustomOutlines): void {
        if (src.none !== undefined) dst.none = src.none!;
        if (src.xs !== undefined) dst.xs = src.xs!;
        if (src.s !== undefined) dst.s = src.s!;
        if (src.m !== undefined) dst.m = src.m!;
        if (src.l !== undefined) dst.l = src.l!;
        if (src.xl !== undefined) dst.xl = src.xl!;
    }
}

export class ArkBordersImpl implements Borders {
    none: Length = 0;
    xs: Length = 0;
    s: Length = 0;
    m: Length = 0;
    l: Length = 0;
    xl: Length = 0;

    constructor(borders: CustomBorders | undefined, baselineBorders: Borders) {
        ArkBordersImpl.assign(this, baselineBorders);
        if (borders) {
            ArkBordersImpl.assign(this, borders!);
        }
    }

    static assign(dst: Borders, src: Borders): void {
        if (src.none !== undefined) dst.none = src.none;
        if (src.xs !== undefined) dst.xs = src.xs;
        if (src.s !== undefined) dst.s = src.s;
        if (src.m !== undefined) dst.m = src.m;
        if (src.l !== undefined) dst.l = src.l;
        if (src.xl !== undefined) dst.xl = src.xl;
    }

    static assign(dst: Borders, src: CustomBorders): void {
        if (src.none !== undefined) dst.none = src.none!;
        if (src.xs !== undefined) dst.xs = src.xs!;
        if (src.s !== undefined) dst.s = src.s!;
        if (src.m !== undefined) dst.m = src.m!;
        if (src.l !== undefined) dst.l = src.l!;
        if (src.xl !== undefined) dst.xl = src.xl!;
    }
}

export class ArkShapesImpl implements Shapes {
    cornerRadius: CornerRadius = new ArkSystemCornerRadius();
    paddings: Paddings = new ArkSystemPaddings();
    borders: Borders = new ArkSystemBorders();
    outlines: Outlines = new ArkSystemOutlines();

    constructor(
        shapes: CustomShapes | undefined,
        baselineShapes: Shapes
    ) {
        if (!shapes) {
            this.cornerRadius = new ArkCornerRadiusImpl(undefined, baselineShapes.cornerRadius);
            this.paddings = new ArkPaddingsImpl(undefined, baselineShapes.paddings);
            this.borders = new ArkBordersImpl(undefined, baselineShapes.borders);
            this.outlines = new ArkOutlinesImpl(undefined, baselineShapes.outlines);
            return;
        }
        this.cornerRadius = new ArkCornerRadiusImpl(shapes!.cornerRadius, baselineShapes.cornerRadius);
        this.paddings = new ArkPaddingsImpl(shapes!.paddings, baselineShapes.paddings);
        this.borders = new ArkBordersImpl(shapes!.borders, baselineShapes.borders);
        this.outlines = new ArkOutlinesImpl(shapes!.outlines, baselineShapes.outlines);
    }

    static assign(dst: Shapes, src: Shapes): void {
        if (src.cornerRadius !== undefined) {
            ArkCornerRadiusImpl.assign(dst.cornerRadius, src.cornerRadius);
        }
        if (src.paddings !== undefined) {
            ArkPaddingsImpl.assign(dst.paddings, src.paddings);
        }
        if (src.borders !== undefined) {
            ArkBordersImpl.assign(dst.borders, src.borders);
        }
        if (src.outlines !== undefined) {
            ArkOutlinesImpl.assign(dst.outlines, src.outlines);
        }
    }

    static assign(dst: Shapes, src: CustomShapes): void {
        if (src.cornerRadius !== undefined) {
            ArkCornerRadiusImpl.assign(dst.cornerRadius, src.cornerRadius!);
        }
        if (src.paddings !== undefined) {
            ArkPaddingsImpl.assign(dst.paddings, src.paddings!);
        }
        if (src.borders !== undefined) {
            ArkBordersImpl.assign(dst.borders, src.borders!);
        }
        if (src.outlines !== undefined) {
            ArkOutlinesImpl.assign(dst.outlines, src.outlines!);
        }
    }
}
