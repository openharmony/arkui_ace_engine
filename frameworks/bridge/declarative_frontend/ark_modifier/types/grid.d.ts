/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
declare interface StartLineInfo {
    startIndex: number;
    startLine: number;
    startOffset: number;
    totalOffset: number;
}
declare type OnGetStartIndexByOffsetCallback = (totalOffset: number) => StartLineInfo;
declare type OnGetStartIndexByIndexCallback = (targetIndex: number) => StartLineInfo;
declare interface GridLayoutOptions {
    regularSize: [
        number,
        number
    ];
    irregularIndexes?: number[];
    onGetIrregularSizeByIndex?: (index: number) => [
        number,
        number
    ];
    onGetRectByIndex?: (index: number) => [
        number,
        number,
        number,
        number
    ];
    onGetStartIndexByOffset?: OnGetStartIndexByOffsetCallback;
    onGetStartIndexByIndex?: OnGetStartIndexByIndexCallback;
}
interface GridInterface {
    (scroller?: Scroller, layoutOptions?: GridLayoutOptions): GridAttribute;
}
declare enum GridDirection {
    Row,
    Column,
    RowReverse,
    ColumnReverse
}
declare enum GridItemAlignment {
    DEFAULT = 0,
    STRETCH = 1
}
declare interface ComputedBarAttribute {
    totalOffset: number;
    totalLength: number;
}
declare class GridAttribute extends ScrollableCommonMethod<GridAttribute> {
    columnsTemplate(value: string): GridAttribute;
    columnsTemplate(value: string | ItemFillPolicy): GridAttribute;
    rowsTemplate(value: string): GridAttribute;
    columnsGap(value: Length): GridAttribute;
    rowsGap(value: Length): GridAttribute;
    scrollBarWidth(value: number | string): GridAttribute;
    scrollBarColor(value: Color | number | string): GridAttribute;
    scrollBarColor(color: Color | number | string | Resource): GridAttribute;
    scrollBar(value: BarState): GridAttribute;
    onScrollIndex(event: (first: number, last: number) => void): GridAttribute;
    cachedCount(value: number): GridAttribute;
    cachedCount(count: number, show: boolean): GridAttribute;
    layoutDirection(value: GridDirection): GridAttribute;
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): GridAttribute;
    nestedScroll(value: NestedScrollOptions): GridAttribute;
    enableScrollInteraction(value: boolean): GridAttribute;
    friction(value: number | Resource): GridAttribute;
    syncLoad(enable: boolean): GridAttribute;
    onScroll(event: (scrollOffset: number, scrollState: ScrollState) => void): GridAttribute;
    onReachStart(event: () => void): GridAttribute;
    onReachEnd(event: () => void): GridAttribute;
    onScrollStart(event: () => void): GridAttribute;
    onScrollStop(event: () => void): GridAttribute;
    onScrollFrameBegin(event: OnScrollFrameBeginCallback): GridAttribute;
}
declare const Grid: GridInterface;
declare const GridInstance: GridAttribute;
