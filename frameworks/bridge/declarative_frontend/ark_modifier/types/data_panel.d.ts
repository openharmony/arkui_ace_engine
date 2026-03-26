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
declare enum DataPanelType {
    Line,
    Circle
}
declare interface ColorStop {
    color: ResourceColor;
    offset: Length;
}
declare class LinearGradient {
    constructor(colorStops: ColorStop[]);
}
declare interface DataPanelShadowOptions extends MultiShadowOptions {
    colors?: Array<ResourceColor | LinearGradient>;
}
declare interface DataPanelOptions {
    values: number[];
    max?: number;
    type?: DataPanelType;
}
interface DataPanelInterface {
    (options: DataPanelOptions): DataPanelAttribute;
}
declare interface DataPanelConfiguration extends CommonConfiguration<DataPanelConfiguration> {
    values: number[];
    maxValue: number;
}
declare class DataPanelAttribute extends CommonMethod<DataPanelAttribute> {
    closeEffect(value: boolean): DataPanelAttribute;
    valueColors(value: Array<ResourceColor | LinearGradient>): DataPanelAttribute;
    trackBackgroundColor(value: ResourceColor): DataPanelAttribute;
    strokeWidth(value: Length): DataPanelAttribute;
    trackShadow(value: DataPanelShadowOptions): DataPanelAttribute;
    contentModifier(modifier: ContentModifier<DataPanelConfiguration>): DataPanelAttribute;
}
declare const DataPanel: DataPanelInterface;
declare const DataPanelInstance: DataPanelAttribute;

interface LazyDataPanelComponent {
    _modifiersWithKeys: any;

    setMap(): void;

    closeEffect(value: boolean): LazyDataPanelComponent;
    valueColors(value: Array<ResourceColor | LinearGradient>): LazyDataPanelComponent;
    trackBackgroundColor(value: ResourceColor): LazyDataPanelComponent;
    strokeWidth(value: Length): LazyDataPanelComponent;
    trackShadow(value: DataPanelShadowOptions): LazyDataPanelComponent;
    contentModifier(value: ContentModifier<DataPanelConfiguration>): LazyDataPanelComponent;
}

interface DataPanelComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): LazyDataPanelComponent;
}
