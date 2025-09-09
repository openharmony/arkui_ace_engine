/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

/**
 * ForEach for partial update
 * Repeat aka ForEach and LazyForEach with child update
 *
 * all definitions in this file are framework internal
 * 
 * Note: the API for ForEach with partial update and with full update
 * are different. Only this declaration file or the one for full update
 * can be used. Using both would lead to syntax error.
 *
 */

declare class ForEach {
  static create(): void;
  static pop(): void;
  static setIdArray(elmtId: number, newIdArray: string[], diffIndexArray: number[],
    duplicateIds: number[], removedChildElmtIds: number[]): void;
  static createNewChildStart(id: string, parentView: NativeViewPartialUpdate): void;
  static createNewChildFinish(id: string, parentView: NativeViewPartialUpdate): void;
}

// Repeat maps to C++ RepeatNode 
declare class RepeatNative {
  static startRender(): void;
  static finishRender(removedChildElmtIds: Array<number>): void;
  static moveChild(fromIndex: number): void;
  static createNewChildStart(id: string): void;
  static createNewChildFinish(id: string): void;
  static afterAddChild(): void;
  static onMove(handler: (from: number, to: number) => void, eventHandler?: ItemDragEventHandler);
  static reuse(index: number): void;
  static recycle(index: number): void;
}

// Repeat.virtualScroll maps to C++ RepeatVirtualScrollNode 
declare class RepeatVirtualScrollNative {
  static create(
    totalCount: number,
    templateOptions: [string, RepeatTemplateOptions][],
    handlers: {
      onCreateNode: (forIndex: number) => void;
      onUpdateNode: (fromKey: string, forIndex: number) => void;
      onGetKeys4Range: (from: number, toNumber: number) => Array<string>;
      onGetTypes4Range: (from: number, toNumber: number) => Array<string>;
      onSetActiveRange: (from: number, to: number) => void;
    },
    reusable: boolean
  ): void;
  // invalidate caches in C++ side, trigger render if needed
  static updateRenderState(totalCount: number, visibleItemsChanged: boolean): void;
  // drag and drop
  static onMove(handler: (from: number, to: number) => void, eventHandler?: ItemDragEventHandler);
  static setCreateByTemplate(isCreatedByTemplate: boolean): void;
}

// Repeat.virtualScroll (v2) maps to C++ RepeatVirtualScroll2Node 
declare class RepeatVirtualScroll2Native {
  static create(
    arrLen: number,
    totalCount: number,
    handlers: {
      onGetRid4Index: (forIndex: number) => [number, number],
      onRecycleItems: (fromIndex: number, toIndex: number) => void,
      onActiveRange: (fromIndex: number, toIndex: number, vStart: number, vEnd: number, isLoop: boolean) => void,
      onMoveFromTo: (moveFrom: number, moveTo: number) => void,
      onPurge: () => void;
    }
  ): void;

  // purge node with given Repeat Item Id (Rid)
  static removeNode(rid: number): void;

  // Drop node with given Repeat Item Id (Rid) from L1 cache
  static setInvalid(repeatelmtId: number, rid: number): void;

  // invalidate owning Container layout starting from Repeat child index
  static requestContainerReLayout(repeatElmtId: number, arrLen: number, totalCount: number, index?: number): void;

  static notifyContainerLayoutChange(repeatElmtId: number, arrLen: number, totalCount: number,
    index: number, count: number, notificationType: number): void;

  static updateL1Rid4Index(repeatElmtId: number,
    arrLen: number,
    totalCount: number,
    invalidateContainerLayoutFromChildIndex: number,
    l1rid4index: Array<Array<number>>,
    ridNeedToRecycle: Array<number>): void;

  // drag and drop
  static onMove(repeatElmtId: number, handler: (from: number, to: number) => void, eventHandler?: ItemDragEventHandler);
  static setCreateByTemplate(isCreatedByTemplate: boolean): void;
}