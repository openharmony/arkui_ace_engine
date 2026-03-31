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
declare interface CheckboxOptions {
    name?: string;
    group?: string;
    indicatorBuilder?: CustomBuilder;
}
declare interface CheckBoxConfiguration extends CommonConfiguration<CheckBoxConfiguration> {
    name: string;
    selected: boolean;
    triggerChange: Callback<boolean>;
}
interface CheckboxInterface {
    (options?: CheckboxOptions): CheckboxAttribute;
}
declare type OnCheckboxChangeCallback = (value: boolean) => void;
declare class CheckboxAttribute extends CommonMethod<CheckboxAttribute> {
    select(value: boolean): CheckboxAttribute;
    select(isSelected: Optional<boolean>): CheckboxAttribute;
    selectedColor(value: ResourceColor): CheckboxAttribute;
    selectedColor(resColor: Optional<ResourceColor>): CheckboxAttribute;
    shape(value: CheckBoxShape): CheckboxAttribute;
    shape(shape: Optional<CheckBoxShape>): CheckboxAttribute;
    unselectedColor(value: ResourceColor): CheckboxAttribute;
    unselectedColor(resColor: Optional<ResourceColor>): CheckboxAttribute;
    mark(value: MarkStyle): CheckboxAttribute;
    mark(style: Optional<MarkStyle>): CheckboxAttribute;
    onChange(callback: OnCheckboxChangeCallback): CheckboxAttribute;
    onChange(callback: Optional<OnCheckboxChangeCallback>): CheckboxAttribute;
    contentModifier(modifier: ContentModifier<CheckBoxConfiguration>): CheckboxAttribute;
    contentModifier(modifier: Optional<ContentModifier<CheckBoxConfiguration>>): CheckboxAttribute;
}
declare const Checkbox: CheckboxInterface;
declare const CheckboxInstance: CheckboxAttribute;

interface LazyCheckboxComponent {
    _modifiersWithKeys: any;

    setMap(): void;
    allowChildCount(): number;
    initialize(value: CheckboxOptions): LazyCheckboxComponent;
    shape(value: CheckBoxShape): LazyCheckboxComponent;
    width(value: Length): LazyCheckboxComponent;
    height(value: Length): LazyCheckboxComponent;
    select(value: boolean): LazyCheckboxComponent;
    selectedColor(value: ResourceColor): LazyCheckboxComponent;
    unselectedColor(value: ResourceColor): LazyCheckboxComponent;
    mark(value: MarkStyle): LazyCheckboxComponent;
    padding(value: Padding | Length): LazyCheckboxComponent;
    size(value: SizeOptions): LazyCheckboxComponent;
    responseRegion(value: Array<Rectangle> | Rectangle): LazyCheckboxComponent;
    margin(value: Margin | Length): LazyCheckboxComponent;
    contentModifier(value: ContentModifier<CheckBoxConfiguration>): LazyCheckboxComponent;
    onChange(callback: OnCheckboxChangeCallback): LazyCheckboxComponent;
}

interface CheckboxComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): LazyCheckboxComponent;
}
