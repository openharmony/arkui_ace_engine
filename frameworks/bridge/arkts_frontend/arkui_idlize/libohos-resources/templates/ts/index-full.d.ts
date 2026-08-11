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

declare function $$<T>(value: T): T

declare const Component: ClassDecorator & ((options: ComponentOptions) => ClassDecorator);

declare const ComponentV2: ClassDecorator & ((options: ComponentOptions) => ClassDecorator);

declare type LocalStorageReference = string

declare interface EntryOptions {
    routeName? : string,
    storage? : LocalStorageReference,
    useSharedStorage? : boolean,
}

declare const Entry: ClassDecorator & ((options?: LocalStorageReference | EntryOptions) => ClassDecorator);

declare const Observed: ClassDecorator;

declare const ObservedV2: ClassDecorator;

declare const Preview: ClassDecorator & ((value: PreviewParams) => ClassDecorator);

declare const Require: PropertyDecorator;

declare const BuilderParam: PropertyDecorator;

declare const Local: PropertyDecorator;

declare const Param: PropertyDecorator;

declare const Once: PropertyDecorator;

declare const Event: PropertyDecorator;

declare const State: PropertyDecorator;

declare const Track: PropertyDecorator;

declare const Trace: PropertyDecorator;

declare const Prop: PropertyDecorator;

declare const Link: PropertyDecorator;

declare const ObjectLink: PropertyDecorator;

declare interface ProvideOptions {
    allowOverride?: string,
}

declare const Provide: PropertyDecorator & ((value: string | ProvideOptions) => PropertyDecorator);

declare const Provider: (aliasName?: string) => PropertyDecorator;

declare const Consume: PropertyDecorator & ((value: string) => PropertyDecorator);

declare const Consumer: (aliasName?: string) => PropertyDecorator;

declare const Computed: MethodDecorator;

declare const StorageProp: (value: string) => PropertyDecorator;

declare const StorageLink: (value: string) => PropertyDecorator;

declare const Watch: (value: string) => PropertyDecorator;

declare const Builder: MethodDecorator;

declare const LocalBuilder: MethodDecorator;

declare const Styles: MethodDecorator;

declare const Extend: MethodDecorator & ((value: any) => MethodDecorator);

declare const AnimatableExtend: MethodDecorator & ((value: Object) => MethodDecorator);

declare const Monitor: MonitorDecorator;

declare type MonitorDecorator = (value: string, ...args: string[]) => MethodDecorator;

declare const Concurrent: MethodDecorator;

declare const Sendable: ClassDecorator;

declare const CustomDialog: ClassDecorator;

declare const LocalStorageLink: (value: string) => PropertyDecorator;

declare const LocalStorageProp: (value: string) => PropertyDecorator;

declare const Reusable: ClassDecorator;

declare class DynamicNode {}

declare class ForEachAttribute implements DynamicNode {
    onMove(handler: OnMoveHandler | undefined, eventHandler?: ItemDragEventHandler): DynamicNode;
}

interface ForEachInterface {
    (
        arr: Array<any>,
        itemGenerator: (item: any, index: number) => void,
        keyGenerator?: (item: any, index: number) => string,
    ): ForEachAttribute;
}

declare const ForEach: ForEachInterface;

declare class TextEncoder {
    encode(input?: string): Uint8Array;
    encodeInto(input?: string): Uint8Array;
    encodeInto(input: string, dest: Uint8Array): { read: number; written: number };
}

declare class TextDecoder {
    decode(input: Uint8Array, options?: { stream?: false }): string;
}

declare class performance {
    static now(): number;
}

declare interface ComponentOptions {
    freezeWhenInactive : boolean,
}

declare interface PreviewParams {
    title?: string;
    width?: number;
    height?: number;
    locale?: string;
    colorMode?: string;
    deviceType?: string;
    dpi?: number;
    orientation?: string;
    roundScreen?: boolean;
}
