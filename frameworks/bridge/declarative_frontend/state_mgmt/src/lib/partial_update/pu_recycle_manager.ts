/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 *
 *  * RecycleManager - Recycle cache manager
 *
* all definitions in this file are framework internal
*/

/**
 * Manage the js cache of all recycled node
 */
class RecycleManager {
  private cachedRecycleNodes: Map<string, Array<ViewPU>> = undefined
  // key: recycleNode element ID
  // value: current assigned ID, used for sort rerender dirty element nodes
  private recycleElmtIdMap: Map<number, number> = undefined

  constructor() {
    this.cachedRecycleNodes = new Map<string, Array<ViewPU>>();
    this.recycleElmtIdMap = new Map<number, number>();
  }

  public add(name: string, node: ViewPU): void {
    if (!this.cachedRecycleNodes.get(name)) {
      this.cachedRecycleNodes.set(name, new Array<ViewPU>());
    }
    this.cachedRecycleNodes.get(name)?.push(node);
  }

  public get(name: string): ViewPU {
    return this.cachedRecycleNodes.get(name)?.pop();
  }

  public queryRecycleNodeCurrentElmtId(recycleElmtId: number): number {
    if (this.recycleElmtIdMap.has(recycleElmtId)) {
      return this.recycleElmtIdMap.get(recycleElmtId);
    }
    return recycleElmtId;
  }

  public setRecycleNodeCurrentElmtId(recycleElmtId: number, currentElmtId: number): void {
    this.recycleElmtIdMap.set(recycleElmtId, currentElmtId);
  }

  public purgeAllCachedRecycleNode(removedElmtIds: number[]): void {
    this.cachedRecycleNodes.forEach((nodes, _) => {
      nodes.forEach((node) => {
        removedElmtIds.push(node.id__())
      })
    })
    this.cachedRecycleNodes.clear();
    this.recycleElmtIdMap.clear();
  }
}