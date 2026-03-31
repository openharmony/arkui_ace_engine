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
interface ColumnSplitInterface {
    (): ColumnSplitAttribute;
}
interface ColumnSplitDividerStyle {
    startMargin?: Dimension;
    endMargin?: Dimension;
}
declare class ColumnSplitAttribute extends CommonMethod<ColumnSplitAttribute> {
    resizeable(value: boolean): ColumnSplitAttribute;
    divider(value: ColumnSplitDividerStyle | null): ColumnSplitAttribute;
}
declare const ColumnSplitInstance: ColumnSplitAttribute;
declare const ColumnSplit: ColumnSplitInterface;

interface LazyColumnSplitComponent {
    _modifiersWithKeys: any;

    setMap(): void;

    resizeable(value: boolean): LazyColumnSplitComponent;
    divider(value: ColumnSplitDividerStyle | null): LazyColumnSplitComponent;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): LazyColumnSplitComponent;
}

interface ColumnSplitComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): LazyColumnSplitComponent;
}
