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
declare enum SelectStatus {
    All,
    Part,
    None
}
declare interface CheckboxGroupOptions {
    group?: string;
}
declare interface CheckboxGroupResult {
    name: Array<string>;
    status: SelectStatus;
}
interface CheckboxGroupInterface {
    (options?: CheckboxGroupOptions): CheckboxGroupAttribute;
}
declare type OnCheckboxGroupChangeCallback = (value: CheckboxGroupResult) => void;
declare interface CheckBoxGroupConfiguration extends CommonConfiguration<CheckBoxGroupConfiguration> {
    name: string;
    status: SelectStatus;
    triggerChange: Callback<boolean>;
}
declare class CheckboxGroupAttribute extends CommonMethod<CheckboxGroupAttribute> {
    selectAll(value: boolean): CheckboxGroupAttribute;
    selectAll(isAllSelected: Optional<boolean>): CheckboxGroupAttribute;
    selectedColor(value: ResourceColor): CheckboxGroupAttribute;
    selectedColor(resColor: Optional<ResourceColor>): CheckboxGroupAttribute;
    unselectedColor(value: ResourceColor): CheckboxGroupAttribute;
    unselectedColor(resColor: Optional<ResourceColor>): CheckboxGroupAttribute;
    mark(value: MarkStyle): CheckboxGroupAttribute;
    mark(style: Optional<MarkStyle>): CheckboxGroupAttribute;
    onChange(callback: OnCheckboxGroupChangeCallback): CheckboxGroupAttribute;
    onChange(callback: Optional<OnCheckboxGroupChangeCallback>): CheckboxGroupAttribute;
    checkboxShape(value: CheckBoxShape): CheckboxGroupAttribute;
    checkboxShape(shape: Optional<CheckBoxShape>): CheckboxGroupAttribute;
    contentModifier(modifier: Optional<ContentModifier<CheckBoxGroupConfiguration>>): CheckboxGroupAttribute;
}
declare const CheckboxGroup: CheckboxGroupInterface;
declare const CheckboxGroupInstance: CheckboxGroupAttribute;

interface LazyCheckboxGroupComponent {
    _modifiersWithKeys: any;

    setMap(): void;
    allowChildCount(): number;
    initialize(value: CheckboxGroupOptions): LazyCheckboxGroupComponent;
    selectAll(value: boolean): LazyCheckboxGroupComponent;
    selectedColor(value: ResourceColor): LazyCheckboxGroupComponent;
    unselectedColor(value: ResourceColor): LazyCheckboxGroupComponent;
    mark(value: MarkStyle): LazyCheckboxGroupComponent;
    onChange(value: OnCheckboxGroupChangeCallback): LazyCheckboxGroupComponent;
    size(value: SizeOptions): LazyCheckboxGroupComponent;
    width(value: Length): LazyCheckboxGroupComponent;
    height(value: Length): LazyCheckboxGroupComponent;
    checkboxShape(value: CheckBoxShape): LazyCheckboxGroupComponent;
}

interface CheckboxGroupComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): LazyCheckboxGroupComponent;
}
