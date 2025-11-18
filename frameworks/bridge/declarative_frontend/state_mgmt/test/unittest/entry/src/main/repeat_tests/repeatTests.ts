/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { eq, neq, gt, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.

declare class PUV2ViewBase {
  protected get isViewV2(): boolean;
}

declare class ViewPU extends PUV2ViewBase{
  public debugInfoStateVars(): string;
  get isViewV2(): boolean;
}

declare class ViewV2 extends PUV2ViewBase{
  public debugInfoStateVars(): string;
  get isViewV2(): boolean;
}

/**
 *  SDK API of Repeat and its attribute functions.
 */
interface RepeatItem<T> {
    readonly item: T;
    readonly index?: number;
}
type RepeatItemGenFunc<T> = (i: RepeatItem<T>) => void;
type RepeatTTypeGenFunc<T> = (item: T, index: number) => string;
type RepeatKeyGenFunc<T> = (item: T, index?: number) => string;
type RepeatTemplateOptions = {
    cachedCount?: number;
};
type RepeatTemplateImplOptions = {
    cachedCountSpecified: boolean;
    cachedCount?: number;
};
type OnMoveHandler = (from: number, to: number) => void;
interface ItemDragEventHandler {
    onLongPress?: (index: number) => void;
    onDragStart?: (index: number) => void;
    onMoveThrough?: (from: number, to: number) => void;
    onDrop?: (index: number) => void;
}
declare const Repeat: <T>(arr: Array<T>, owningView?: PUV2ViewBase) => RepeatAPI<T>;
interface RepeatAPI<T> {
    key: (keyGenFunc: RepeatKeyGenFunc<T>) => RepeatAPI<T>;
    each: (itemGenFunc: RepeatItemGenFunc<T>) => RepeatAPI<T>;
    virtualScroll: (options?: {
        totalCount?: number;
        onTotalCount?(): number;
        onLazyLoading?(index: number): void;
        reusable?: boolean;
    }) => RepeatAPI<T>;
    templateId: (typeFunc: RepeatTTypeGenFunc<T>) => RepeatAPI<T>;
    template: (type: string, itemGenFunc: RepeatItemGenFunc<T>, options?: RepeatTemplateOptions) => RepeatAPI<T>;
    render(isInitialRender: boolean): void;
    onMove: (handler: OnMoveHandler, eventHandler: ItemDragEventHandler) => RepeatAPI<T>;
}
interface __IRepeatItemInternal<T> {
    updateItem: (newItemVal: T) => void;
    updateIndex: (newIndexValue: number) => void;
    aboutToBeDeleted?: () => void;
}
interface __RepeatItemFactoryReturn<T> extends RepeatItem<T>, __IRepeatItemInternal<T> {
}
declare class __RepeatItemPU<T> implements RepeatItem<T>, __IRepeatItemInternal<T> {
    public _observedItem;
    public _observedIndex?;
    constructor(owningView: ViewPU, initialItem: T, initialIndex?: number);
    get item(): T;
    get index(): number | undefined;
    updateItem(newItemValue: T): void;
    updateIndex(newIndex: number): void;
    aboutToBeDeleted(): void;
}
declare class __RepeatItemV2<T> implements RepeatItem<T>, __IRepeatItemInternal<T> {
    constructor(initialItem: T, initialIndex?: number);
    item: T;
    index?: number;
    updateItem(newItemValue: T): void;
    updateIndex(newIndex: number): void;
    hasBindingToIndex(): boolean;
}
interface __RepeatItemInfo<T> {
    key: string;
    index: number;
    repeatItem?: __RepeatItemFactoryReturn<T>;
}
declare class __RepeatDefaultKeyGen {
    public static weakMap_;
    public static lastKey_;
    static func<T>(item: T): string;
    static funcWithIndex<T>(item: T, index: number): string;
    public static funcImpl;
}
interface __RepeatConfig<T> {
    owningView_?: ViewV2;
    arr?: Array<T>;
    itemGenFuncs?: {
        [type: string]: RepeatItemGenFunc<T>;
    };
    keyGenFunc?: RepeatKeyGenFunc<T>;
    keyGenFuncSpecified?: boolean;
    ttypeGenFunc?: RepeatTTypeGenFunc<T>;
    totalCountSpecified?: boolean;
    totalCount?: number | (() => number);
    onLazyLoading?: (index: number) => void;
    templateOptions?: {
        [type: string]: RepeatTemplateImplOptions;
    };
    mkRepeatItem?: (item: T, index?: number) => __RepeatItemFactoryReturn<T>;
    onMoveHandler?: OnMoveHandler;
    itemDragEventHandler?: ItemDragEventHandler;
    reusable?: boolean;
}
declare const RepeatEachFuncTtype: string;
declare class __Repeat<T> implements RepeatAPI<T> {
    public config;
    public impl;
    public isVirtualScroll;
    constructor(owningView: ViewV2 | ViewPU, arr: Array<T>);
    each(itemGenFunc: RepeatItemGenFunc<T>): RepeatAPI<T>;
    key(keyGenFunc: RepeatKeyGenFunc<T>): RepeatAPI<T>;
    virtualScroll(options?: {
        totalCount?: number;
        onTotalCount?: () => number;
        onLazyLoading?: (index: number) => void;
        reusable?: boolean;
    }): RepeatAPI<T>;
    templateId(ttypeGenFunc: RepeatTTypeGenFunc<T>): RepeatAPI<T>;
    template(ttype: string, itemGenFunc: RepeatItemGenFunc<T>, options?: RepeatTemplateOptions): RepeatAPI<T>;
    updateArr(arr: Array<T>): RepeatAPI<T>;
    render(isInitialRender: boolean): void;
    onMove(handler: OnMoveHandler, eventHandler?: ItemDragEventHandler): RepeatAPI<T>;
    aboutToBeDeleted(): void;
    public normTemplateOptions;
}

export class RepeatTest1 implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating StateManagemetTest: ${str}`)
    this.idString = str;
  }

  // Executed before any tests. Can be empty
  public beforeAll(): void {}

  // Executed before every invidual tests. Can be empty
  public beforeEach(): void {}

  // Executed after any tests. Can be empty
  public afterAll () : void {}

  // Executed after every individual tests. Can be empty
  public afterEach () : void {}

  public getId(): string {
    return this.idString;
  }

  /// -- Test cases

  /* Test creation of __Repeat
  * Calls:
   __Repeat.constructor
  */
  public RepeatCreate(): void {
    let viewPU = new ViewPU();
    let repeat = new __Repeat(viewPU, []);
    eq(repeat.config.keyGenFuncSpecified, false, 'RepeatTest1_RepeatCreate_01');
    eq(repeat.config.totalCountSpecified, false, 'RepeatTest1_RepeatCreate_02');
    eq(repeat.config.totalCount, 0, 'RepeatTest1_RepeatCreate_03');
    eq(repeat.config.reusable, true, 'RepeatTest1_RepeatCreate_04');
  }

  /* Test __Repeat.each
  * Calls:
   __Repeat.each
  */
  public RepeatEachFunc(): void {
    let viewPU = new ViewPU();
    let repeat = new __Repeat(viewPU, []);
    eq(repeat.config.itemGenFuncs[''], undefined, 'RepeatTest1_RepeatEachFunc_01');
    eq(repeat.config.templateOptions[''], undefined, 'RepeatTest1_RepeatEachFunc_02');
    repeat.each(() => {});
    neq(repeat.config.itemGenFuncs[''], undefined, 'RepeatTest1_RepeatEachFunc_03');
    eq(repeat.config.templateOptions[''].cachedCountSpecified, false, 'RepeatTest1_RepeatEachFunc_04');
  }

  /* Test __Repeat.key
  * Calls:
   __Repeat.key
  */
  public RepeatKeyFunc(): void {
    let viewPU = new ViewPU();
    let repeat = new __Repeat(viewPU, []);
    repeat.key((item) => { return JSON.stringify(item); });
    let key = repeat.config.keyGenFunc(0);
    eq(key, '0', 'RepeatTest1_RepeatEachFunc_01');
    eq(repeat.config.keyGenFuncSpecified, true, 'RepeatTest1_RepeatKeyFunc_02');
  }
}