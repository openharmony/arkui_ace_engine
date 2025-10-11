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

import { CornerRadius, Paddings, Outlines, Dimension, Borders, Shapes } from '../index';
import { Length } from 'arkui/component/units';
import { _r } from 'arkui/component/resources';

export class ArkSystemCornerRadius implements CornerRadius {
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

    constructor() {
        this.none = _r('', '', 'sys.float.corner_radius_none');
        this.level1 = _r('', '', 'sys.float.corner_radius_level1');
        this.level2 = _r('', '', 'sys.float.corner_radius_level2');
        this.level3 = _r('', '', 'sys.float.corner_radius_level3');
        this.level4 = _r('', '', 'sys.float.corner_radius_level4');
        this.level5 = _r('', '', 'sys.float.corner_radius_level5');
        this.level6 = _r('', '', 'sys.float.corner_radius_level6');
        this.level7 = _r('', '', 'sys.float.corner_radius_level7');
        this.level8 = _r('', '', 'sys.float.corner_radius_level8');
        this.level9 = _r('', '', 'sys.float.corner_radius_level9');
        this.level10 = _r('', '', 'sys.float.corner_radius_level10');
        this.level11 = _r('', '', 'sys.float.corner_radius_level11');
        this.level12 = _r('', '', 'sys.float.corner_radius_level12');
        this.level16 = _r('', '', 'sys.float.corner_radius_level16');
    }
}

export class ArkSystemPaddings implements Paddings {
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

    constructor() {
        this.level0 = _r('', '', 'sys.float.padding_level0');
        this.level1 = _r('', '', 'sys.float.padding_level1');
        this.level2 = _r('', '', 'sys.float.padding_level2');
        this.level3 = _r('', '', 'sys.float.padding_level3');
        this.level4 = _r('', '', 'sys.float.padding_level4');
        this.level5 = _r('', '', 'sys.float.padding_level5');
        this.level6 = _r('', '', 'sys.float.padding_level6');
        this.level7 = _r('', '', 'sys.float.padding_level7');
        this.level8 = _r('', '', 'sys.float.padding_level8');
        this.level9 = _r('', '', 'sys.float.padding_level9');
        this.level10 = _r('', '', 'sys.float.padding_level10');
        this.level11 = _r('', '', 'sys.float.padding_level11');
        this.level12 = _r('', '', 'sys.float.padding_level12');
        this.level16 = _r('', '', 'sys.float.padding_level16');
        this.level24 = _r('', '', 'sys.float.padding_level24');
        this.level32 = _r('', '', 'sys.float.padding_level32');
        this.level36 = _r('', '', 'sys.float.padding_level36');
    }
}

export class ArkSystemOutlines implements Outlines {
    none: Dimension;
    xs: Dimension;
    s: Dimension;
    m: Dimension;
    l: Dimension;
    xl: Dimension;

    constructor() {
        this.none = _r('', '', 'sys.float.outline_none');
        this.xs = _r('', '', 'sys.float.outline_extra_small');
        this.s = _r('', '', 'sys.float.outline_small');
        this.m = _r('', '', 'sys.float.outline_medium');
        this.l = _r('', '', 'sys.float.outline_larger');
        this.xl = _r('', '', 'sys.float.outline_extra_larger');
    }
}

export class ArkSystemBorders implements Borders {
    none: Length;
    xs: Length;
    s: Length;
    m: Length;
    l: Length;
    xl: Length;

    constructor() {
        this.none = _r('', '', 'sys.float.border_none');
        this.xs = _r('', '', 'sys.float.border_extra_small');
        this.s = _r('', '', 'sys.float.border_small');
        this.m = _r('', '', 'sys.float.border_medium');
        this.l = _r('', '', 'sys.float.border_larger');
        this.xl = _r('', '', 'sys.float.border_extra_larger');
    }
}

export class ArkSystemShapes implements Shapes {
    cornerRadius: CornerRadius;
    paddings: Paddings;
    borders: Borders;
    outlines: Outlines;

    constructor() {
        this.cornerRadius = new ArkSystemCornerRadius();
        this.paddings = new ArkSystemPaddings();
        this.borders = new ArkSystemBorders();
        this.outlines = new ArkSystemOutlines();
    }
}