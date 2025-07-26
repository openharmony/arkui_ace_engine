/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { Measurable, Layoutable, Position, ConstraintSizeOptions, MeasureResult, DirectionalEdgesT,  Length, Padding, Margin, EdgeWidths, GeometryInfo, SizeResult } from 'arkui/component'
import { int64, int32 } from '@koalaui/common'
import { KPointer, KInt } from '@koalaui/interop'
import { ArkCustomComponent } from 'arkui/ArkCustomComponent'

export class ArkUIAniCustomNodeModule {
    static {
        loadLibrary("arkuicustomnode_ani")
    }

    native static _CustomNode_Construct(id: int32, component: ArkCustomComponent): KPointer

}
export class MeasurableLayoutableInner implements Measurable, Layoutable {

    private  measureLayoutChild: int64 = 0;
    
    constructor(measureLayoutChild:int64) {
        if(this.measureLayoutChild == 0){
            this.measureLayoutChild = measureLayoutChild;
        }
    }
    
    uniqueId?: number | undefined;
    measureResult: MeasureResult = {};

    public override measure(constraint: ConstraintSizeOptions): MeasureResult {
        return this.measureInner(constraint);
    }
    public override layout(position: Position) {
        this.layoutInner(position)
    }
    public override getMargin(): DirectionalEdgesT<number> {
        return this.getMarginInner()
    }
    public override getPadding(): DirectionalEdgesT<number> {
        return this.getPaddingInner()
    }
    public override getBorderWidth(): DirectionalEdgesT<number> {
        return this.getBorderWidthInner()
    }
    
    public native layoutInner(position: Position): void;
    public native measureInner(constraint: ConstraintSizeOptions): MeasureResult;
    public native getMarginInner(): DirectionalEdgesT<double>;
    public native getPaddingInner(): DirectionalEdgesT<double>;
    public native getBorderWidthInner(): DirectionalEdgesT<double>;
}

export class ConstraintSizeOptionsInner implements ConstraintSizeOptions {
    minWidth?: Length ;
    maxWidth?: Length ;
    minHeight?: Length ;
    maxHeight?: Length ;
    constructor(minWidth?: Length, minHeight?: Length, maxWidth?: Length, maxHeight?: Length)
    {
        this.minWidth = minWidth;
        this.maxWidth = maxWidth;
        this.minHeight = minHeight;
        this.maxHeight = maxHeight;
    }
}

export class PaddingInner implements Padding {
    top?: Length ;
    right?: Length ;
    bottom?: Length ;
    left?: Length ;
    constructor(top?: Length , right?: Length, bottom?: Length, left?: Length)
    {
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }
}

export class MarginInner implements Margin {
    top?: Length ;
    right?: Length ;
    bottom?: Length ;
    left?: Length ;
    constructor(top?: Length , right?: Length, bottom?: Length, left?: Length)
    {
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }
}

export class EdgeWidthsInner implements EdgeWidths {
    top?: Length ;
    right?: Length ;
    bottom?: Length ;
    left?: Length ;
    constructor(top?: Length , right?: Length, bottom?: Length, left?: Length)
    {
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }
}

export class DirectionalEdgesTInner implements DirectionalEdgesT<double> {
    start: number;
    end: number;
    top: number;
    bottom: number;
    constructor(top: number, bottom: number, start: number, end: number )
    {
        this.start = start;
        this.end = end;
        this.top = top;
        this.bottom = bottom;
    }
}

export class GeometryInfoInner implements GeometryInfo {
    width: number = 0;
    height: number = 0;
    borderWidth: EdgeWidths = {};
    margin: Padding = {};
    padding: Padding = {};
}

export class SizeResultInner implements SizeResult {
    width: number;
    height: number;
    constructor(width: number, height: number)
    {
        this.height = height;
        this.width = width;
    }
}

export class MeasureResultInner implements MeasureResult {
    width: number;
    height: number;
    constructor(width: number, height: number)
    {
        this.height = height;
        this.width = width;
    }
}
