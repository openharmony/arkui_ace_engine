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
  private cachedRecycleNodes: Map<string, Array<ViewPU>> = undefined

  constructor() {
    this.cachedRecycleNodes = new Map<string, Array<ViewPU>>();
  }

  public pushRecycleNode(name: string, node: ViewPU): void {
    if (!this.cachedRecycleNodes.get(name)) {
      this.cachedRecycleNodes.set(name, new Array<ViewPU>());
    }
    this.cachedRecycleNodes.get(name)?.push(node);
  }

  public popRecycleNode(name: string): ViewPU {
    return this.cachedRecycleNodes.get(name)?.pop();
  }

  // When parent JS View is deleted, release all cached nodes
  public purgeAllCachedRecycleNode(): void {
    this.cachedRecycleNodes.forEach((nodes, _) => {
      nodes.forEach((node) => {
        node.resetRecycleCustomNode();
      })
    })
    this.cachedRecycleNodes.clear();
  }
}

function createWeakRef<T>(o: T) {
  if (typeof o !== "object") {
    return o;
  }
  if (o instanceof ObservedPropertyAbstract) {
    return new WeakRef(o.getUnmonitored());
  }
  return new WeakRef(o);
}
