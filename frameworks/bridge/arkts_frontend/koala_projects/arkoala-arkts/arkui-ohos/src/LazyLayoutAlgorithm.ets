/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { int32, int64, float32 } from '@koalaui/common'
import { FrameNode, LayoutConstraint } from 'arkui.FrameNode';
import { NodePosition } from 'arkui.Graphics';
import { Axis } from './component/enums';

export enum LazyLayoutDirection {
    FORWARD = 0,
    BACKWARD = 1,
}

export class LazyLayoutInfo {
    viewStart: int32;
    viewEnd: int32;
    lazyLayoutDirection: LazyLayoutDirection;
    constructor(viewStart: int32, viewEnd: int32, lazyLayoutDirection: LazyLayoutDirection) {
        this.viewStart = viewStart;
        this.viewEnd = viewEnd;
        this.lazyLayoutDirection = lazyLayoutDirection;
    }
}

export interface LazyLayoutAlgorithm {
}

export class LazyLayoutResult {
    adjustedOffset: int32 = 0;
    inActiveChildren: int32[] = [];
}

export class LazyLayoutHelper {
    private info: LazyLayoutInfo;
    public result: LazyLayoutResult = new LazyLayoutResult();

    constructor(info: LazyLayoutInfo) {
        this.info = info;
    }

    getViewStart(): int32 {
        return this.info.viewStart;
    }

    getViewEnd(): int32 {
        return this.info.viewEnd;
    }

    getLazyLayoutDirection(): LazyLayoutDirection {
        return this.info.lazyLayoutDirection;
    }

    setAdjustedOffset(offset: int32): void {
        this.result.adjustedOffset = offset;
    }

    setChildrenInactive(children: int32[]): void {
        this.result.inActiveChildren = children;
    }

    getResult(): LazyLayoutResult {
        return this.result;
    }
}

export interface LazyCustomLayoutAlgorithmOptions {
    axis?: Axis;
}

function getOptionalVal<T>(defaultVal: T, arg?: T): T {
    return arg !== undefined ? arg : defaultVal;
}

export class LazyCustomLayoutAlgorithm implements LazyLayoutAlgorithm {
    public axis: Axis;

    constructor(option?: LazyCustomLayoutAlgorithmOptions) {
        this.axis = getOptionalVal(Axis.Vertical, option?.axis);
    }

    onMeasure(self: FrameNode, constraint: LayoutConstraint, helper?: LazyLayoutHelper): void {}

    onLayout(self: FrameNode, position: NodePosition): void {}

    __onMeasure__(self: FrameNode, constraint: LayoutConstraint, info: LazyLayoutInfo): LazyLayoutResult {
        let helper = new LazyLayoutHelper(info);
        this.onMeasure(self, constraint, helper);
        return helper.getResult();
    }
}