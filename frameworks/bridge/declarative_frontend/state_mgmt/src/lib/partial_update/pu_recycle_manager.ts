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
 * @class RecycleManager
 * @description manage the JS object cached of current node
 */
class RecycleManager {
  // key: recycle node name
  // value: recycle node JS object
  private cachedRecycleNodes_: Map<string, Array<ViewPU>> = undefined;
  private biMap_: BidirectionalMap = undefined;

  constructor() {
    this.cachedRecycleNodes_ = new Map<string, Array<ViewPU>>();
    this.biMap_ = new BidirectionalMap();
  }

  public updateNodeId(oldElmtId: number, newElmtId: number): void {
    this.biMap_.delete(oldElmtId);
    this.biMap_.add([oldElmtId, newElmtId]);
  }

  public proxyNodeId(oldElmtId: number): number {
    const proxy = this.biMap_.get(oldElmtId);
    if (!proxy) {
      return oldElmtId;
    }
    return proxy;
  }

  public pushRecycleNode(name: string, node: ViewPU): void {
    if (!this.cachedRecycleNodes_.get(name)) {
      this.cachedRecycleNodes_.set(name, new Array<ViewPU>());
    }
    this.cachedRecycleNodes_.get(name)?.push(node);
  }

  public popRecycleNode(name: string): ViewPU {
    return this.cachedRecycleNodes_.get(name)?.pop();
  }

  // When parent JS View is deleted, release all cached nodes
  public purgeAllCachedRecycleNode(): void {
    this.cachedRecycleNodes_.forEach((nodes, _) => {
      nodes.forEach((node) => {
        node.resetRecycleCustomNode();
      });
    })
    this.cachedRecycleNodes_.clear();
  }

  // Set active status for all cached nodes
  public setActive(active): void {
    this.cachedRecycleNodes_.forEach((nodes, _) => {
      nodes.forEach((node) => {
        node.setActiveInternal(active);
      })
    })
  }
}

class BidirectionalMap {
  private fwdMap_: Map<number, number> = undefined;
  private revMap_: Map<number, number> = undefined;

  constructor() {
    this.fwdMap_ = new Map<number, number>();
    this.revMap_ = new Map<number, number>();
  }

  delete(key: number) {
    if (!this.fwdMap_[key]) {
      return;
    }
    const rev = this.fwdMap_[key];
    this.fwdMap_.delete(key);
    this.revMap_.delete(rev);
  }

  get(key: number): number | undefined {
    return this.fwdMap_[key] || this.revMap_[key];
  }

  add(pair: [number, number]) {
    this.fwdMap_[pair[0]] = pair[1];
    this.revMap_[pair[1]] = pair[0];
  }
}
