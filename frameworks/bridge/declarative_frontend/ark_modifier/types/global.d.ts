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

declare global {
    interface Object {
        createComponent: (nativePtr: KNode, classType: ModifierType) => any;
        [key: string]: any;
    }
}

declare function getUINativeModule(): UINativeModule;

interface UINativeModule {
    frameNode: FrameNodeModule;
}

interface FrameNodeModule {
    getNodeInstanceId(nativePtr: KNode): number;
    markDirty(nativePtr: NodePtr, flag: number): void;
    registerFrameCallback(callback: () => void): void;
}

declare function __getCustomProperty__(nodeId: number, key: string): object | undefined;
declare function __getCustomPropertyString__(nodeId: number, key: string): string | undefined;

declare const __JSScopeUtil__: {
    syncInstanceId(instanceId: number): void;
    restoreInstanceId(): void;
};

declare namespace globalThis {
    function requireNapi(moduleName: string): any;
}

declare function applyUIAttributes(modifier: AttributeModifier<CommonAttribute>, nativeNode: NodePtr, component: ArkComponent): void;

interface Map<K, V> {
    setOnChange?(callback: (key: K, value: V) => void): void;
}

declare class WeakRef<T> {
    constructor(target: T);
    deref(): T | undefined;
}

declare global {
    function requireNapi(moduleName: string): any;
    const __JSScopeUtil__: {
        syncInstanceId(instanceId: number): void;
        restoreInstanceId(): void;
    };
}

interface AlphabetIndexerComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface CalendarPickerComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface CheckboxComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
    getCheckboxWidthModifier(): any;
    getCheckboxHeightModifier(): any;
}

interface CheckboxGroupComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface ColumnSplitComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface CounterComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface DataPanelComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface GaugeComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface HyperlinkComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface MarqueeComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface MenuComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface MenuItemComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface PatternLockComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface QRCodeComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface RadioComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface RatingComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface RichEditorComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface RowSplitComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface SearchComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface SideBarContainerComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface SliderComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface StepperComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface StepperItemComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface SymbolGlyphComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface TextClockComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface TimePickerComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

interface WaterFlowComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): any;
}

declare class TextForegroundColorModifier extends ModifierWithKey<object> {
    constructor(value: object);
}
