/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
  static onMove(handler: (from: number, to: number) => void);
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
    }
  ): void;
  // invalidate caches in C++ side, trigger render if needed
  static updateRenderState(totalCount: number, visibleItemsChanged: boolean): void;
  // drag and drop
  static onMove(handler: (from: number, to: number) => void);
  static setCreateByTemplate(isCreatedByTemplate: boolean): void;
}
