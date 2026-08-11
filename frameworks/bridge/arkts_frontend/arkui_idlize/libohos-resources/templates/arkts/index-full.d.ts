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

declare interface IDataSource<T> {
    totalCount(): number;

    getData(index: number): T;

    registerDataChangeListener(listener: DataChangeListener): void;

    unregisterDataChangeListener(listener: DataChangeListener): void;
}

declare class LazyForEachAttribute implements DynamicNode {
    onMove(handler: OnMoveHandler | undefined, eventHandler?: ItemDragEventHandler): DynamicNode;
}

interface LazyForEachInterface<T> {
    (
        dataSource: IDataSource<T>,
        itemGenerator: (item: T, index: number) => void,
        keyGenerator?: (item: T, index: number) => string
    ): LazyForEachAttribute;
}

declare function ForEach<T> (
    arr: Array<T>,
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
): ForEachAttribute<T>;

declare class ForEachAttribute<T> implements DynamicNode {
    onMove(handler: OnMoveHandler | undefined, eventHandler?: ItemDragEventHandler): DynamicNode;
}

interface ForEachInterface<T> {
    (
        arr: Array<T>,
        itemGenerator: (item: T, index: number) => void,
        keyGenerator?: (item: T, index: number) => string,
    ): ForEachAttribute<T>
// Improve: have overloads for [] and Array
    /*
      (
        arr: T[],
        itemGenerator: (item: T, index: number) => void,
        keyGenerator?: (item: T, index: number) => string,
      ): ForEachAttribute<T>;
    */
}

declare function LazyForEach<T>(
    dataSource: IDataSource<T>,
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
): LazyForEachAttribute // extends LazyForEachInterface<T> {}

// Until we have full sdk
declare interface LayoutChild {}

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

declare class WrappedBuilder {
    builder: ((arg: Object) => void);
}

declare namespace window {
    enum Orientation {
        UNSPECIFIED = 0,
        PORTRAIT = 1,
        LANDSCAPE = 2,
        PORTRAIT_INVERTED = 3,
        LANDSCAPE_INVERTED = 4,
        AUTO_ROTATION = 5,
        AUTO_ROTATION_PORTRAIT = 6,
        AUTO_ROTATION_LANDSCAPE = 7,
        AUTO_ROTATION_RESTRICTED = 8,
        AUTO_ROTATION_PORTRAIT_RESTRICTED = 9,
        AUTO_ROTATION_LANDSCAPE_RESTRICTED = 10,
        LOCKED = 11,
        AUTO_ROTATION_UNSPECIFIED = 12,
        USER_ROTATION_PORTRAIT = 13,
        USER_ROTATION_LANDSCAPE = 14,
        USER_ROTATION_PORTRAIT_INVERTED = 15,
        USER_ROTATION_LANDSCAPE_INVERTED = 16,
        FOLLOW_DESKTOP = 17
    }
}

declare class GestureGroup {
    static $_instantiate(factory: () => GestureGroup, mode: GestureMode, ...gesture: GestureType[]): GestureGroup;
    onCancel(event: () => void): GestureGroup;
}
