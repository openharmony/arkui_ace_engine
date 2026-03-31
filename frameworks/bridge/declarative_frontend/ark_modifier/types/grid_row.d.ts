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
declare interface GridRowSizeOption {
    xs?: Length;
    sm?: Length;
    md?: Length;
    lg?: Length;
    xl?: Length;
    xxl?: Length;
}
declare interface GridRowColumnOption {
    xs?: number;
    sm?: number;
    md?: number;
    lg?: number;
    xl?: number;
    xxl?: number;
}
declare interface GutterOption {
    x?: Length | GridRowSizeOption;
    y?: Length | GridRowSizeOption;
}
declare enum BreakpointsReference {
    WindowSize,
    ComponentSize
}
declare enum GridRowDirection {
    Row,
    RowReverse
}
declare interface BreakPoints {
    value?: Array<string>;
    reference?: BreakpointsReference;
}
declare interface GridRowOptions {
    gutter?: Length | GutterOption;
    columns?: number | GridRowColumnOption;
    breakpoints?: BreakPoints;
    direction?: GridRowDirection;
}
interface GridRowInterface {
    (option?: GridRowOptions): GridRowAttribute;
}
declare class GridRowAttribute extends CommonMethod<GridRowAttribute> {
}
declare const GridRow: GridRowInterface;
declare const GridRowInstance: GridRowAttribute;
