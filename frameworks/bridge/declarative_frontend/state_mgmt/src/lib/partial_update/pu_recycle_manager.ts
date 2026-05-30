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
  // Track pending cache clean timers per name
  private pendingCacheCleanTimers_: Map<string, any> = undefined;
  // Track maximum cache size per name (for timer restart logic)
  private maxCacheSizes_: Map<string, number> = undefined;
  // Pending nodes for progressive release
  private pendingProgressiveReleaseNodes_: Array<ViewPU> = undefined;
  // Callback to request progressive release (set by parent ViewPU)
  private requestProgressiveReleaseCallback_: () => void = undefined;
  private defaultCacheCount: number;
  private reuseIdForOptimize: Set<string> = new Set<string>();

  constructor() {
    this.cachedRecycleNodes_ = new Map<string, Array<ViewPU>>();
    this.biMap_ = new BidirectionalMap();
    this.pendingCacheCleanTimers_ = new Map<string, any>();
    this.maxCacheSizes_ = new Map<string, number>();
    this.pendingProgressiveReleaseNodes_ = new Array<ViewPU>();
    this.defaultCacheCount = 8;
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
    if (node.__getReusableMemOptStrategy__Internal() === 1) {
      this.reuseIdForOptimize.add(name);
      const cachedNodes = this.cachedRecycleNodes_.get(name);
      if (cachedNodes && cachedNodes.length > this.defaultCacheCount) {
        const currentSize = cachedNodes.length;
        const maxSize = this.maxCacheSizes_.get(name) || 0;
        // Only restart timer if cache size reaches a new maximum
        if (currentSize > maxSize) {
          this.maxCacheSizes_.set(name, currentSize);
          this.scheduleCacheCleanTask(name);
        }
      }
    }
  }

  /**
   * @function setRequestProgressiveReleaseCallback
   * @description
   * Sets the callback function to request progressive release from C++ side.
   *
   * @param {() => void} callback - The callback function.
   */
  public setRequestProgressiveReleaseCallback(callback: () => void): void {
    this.requestProgressiveReleaseCallback_ = callback;
  }

  /**
   * @function prepareCleanCacheToTargetProgressive
   * @description
   * Prepares to clean cache to target size by moving excess nodes to the pending progressive release list.
   * The actual release will be done later by releaseCachedNodesProgressive.
   *
   * @param {string} name - The name identifier for the cached nodes.
   * @param {number} targetSize - The target cache size.
   * @returns {number} - The number of nodes prepared for release.
   */
  public prepareCleanCacheToTargetProgressive(name: string, targetSize: number): number {
    const cachedNodes = this.cachedRecycleNodes_.get(name);
    if (!cachedNodes || cachedNodes.length <= targetSize) {
      return 0;
    }

    const nodesToRemove = cachedNodes.length - targetSize;
    for (let i = 0; i < nodesToRemove; i++) {
      const node = cachedNodes.shift();
      if (node) {
        this.pendingProgressiveReleaseNodes_.push(node);
      }
    }

    this.pendingCacheCleanTimers_.delete(name);
    this.maxCacheSizes_.delete(name);

    return nodesToRemove;
  }

  private scheduleCacheCleanTask(name: string): void {
    const existingTimer = this.pendingCacheCleanTimers_.get(name);
    if (existingTimer !== undefined) {
      clearTimeout(existingTimer);
    }

    const timerId = setTimeout(() => {
      // Prepare nodes for progressive release
      const pendingCount = this.prepareCleanCacheToTargetProgressive(name, this.defaultCacheCount);

      // If there are nodes to release and callback is available, request progressive release
      if (pendingCount > 0 && this.requestProgressiveReleaseCallback_) {
        this.requestProgressiveReleaseCallback_();
      }
    }, 300000); // 5 minutes

    this.pendingCacheCleanTimers_.set(name, timerId);
  }

  public popRecycleNode(name: string): ViewPU {
    return this.cachedRecycleNodes_.get(name)?.pop();
  }

  // When parent JS View is deleted, release all cached nodes
  public purgeAllCachedRecycleNode(): void {
    this.pendingCacheCleanTimers_.forEach((timerId) => {
      clearTimeout(timerId);
    });
    this.pendingCacheCleanTimers_.clear();
    this.maxCacheSizes_.clear();

    this.cachedRecycleNodes_.forEach((nodes, _) => {
      nodes.forEach((node) => {
        node.resetRecycleCustomNode();
      });
    })
    this.cachedRecycleNodes_.clear();

    this.pendingProgressiveReleaseNodes_.forEach((node) => {
        node.resetRecycleCustomNode();
    });
    this.pendingProgressiveReleaseNodes_ = new Array<ViewPU>();
  }

  public purgeAllCleanableRecycleNode(): void {
    this.pendingCacheCleanTimers_.forEach((timerId) => {
      clearTimeout(timerId);
    });
    this.pendingCacheCleanTimers_.clear();
    this.maxCacheSizes_.clear();

    this.cachedRecycleNodes_.forEach((nodes, reuseId) => {
      if (!this.reuseIdForOptimize.has(reuseId)) {
        return;
      }
      nodes.forEach((node) => {
        node.resetRecycleCustomNode();
      });
    });
    this.reuseIdForOptimize.forEach((reuseId) => {
      this.cachedRecycleNodes_.delete(reuseId);
    });
    this.reuseIdForOptimize.clear();

    this.pendingProgressiveReleaseNodes_.forEach((node) => {
        node.resetRecycleCustomNode();
    });
    this.pendingProgressiveReleaseNodes_ = new Array<ViewPU>();
  }

  /**
   * @function preparePurgeAllCleanableRecycleNodeProgressive
   * @description
   * Prepares to release all cleanable nodes by moving them to the pending progressive release list.
   * The actual release will be done later by releaseCachedNodesProgressive.
   *
   * @returns {number} - The number of nodes prepared for release.
   */
  public preparePurgeAllCleanableRecycleNodeProgressive(): number {
    this.pendingCacheCleanTimers_.forEach((timerId) => {
      clearTimeout(timerId);
    });
    this.pendingCacheCleanTimers_.clear();
    this.maxCacheSizes_.clear();

    let count = 0;
    this.cachedRecycleNodes_.forEach((nodes, reuseId) => {
      if (!this.reuseIdForOptimize.has(reuseId)) {
        return;
      }
      nodes.forEach((node) => {
        this.pendingProgressiveReleaseNodes_.push(node);
        count++;
      });
    });
    this.reuseIdForOptimize.forEach((reuseId) => {
      this.cachedRecycleNodes_.delete(reuseId);
    });
    this.reuseIdForOptimize.clear();
    return count;
  }

  /**
   * @function releaseCachedNodesProgressive
   * @description
   * Releases nodes from the pending progressive release list based on remaining time.
   * Each release operation is timed to prevent blocking.
   * At least one node is released per call.
   *
   * @param {number} remainingTimeMs - The remaining time in milliseconds.
   * @returns {boolean} - true if all pending nodes are released, false if timeout occurred.
   */
  public releaseCachedNodesProgressive(remainingTimeMs: number): boolean {
    // If no nodes to release, return true
    if (this.pendingProgressiveReleaseNodes_.length === 0) {
      return true;
    }

    // Record start time for releasing remaining nodes
    const startTime = Date.now();
    let elapsedMs: number = 0;
    do {
      const node = this.pendingProgressiveReleaseNodes_.shift();
      if (node) {
        node.resetRecycleCustomNode();
      }
      elapsedMs = Date.now() - startTime;
    } while (this.pendingProgressiveReleaseNodes_.length > 0 && elapsedMs < remainingTimeMs)

    return this.pendingProgressiveReleaseNodes_.length === 0;
  }

  // Set active status for all cached nodes
  public setActive(active): void {
    this.cachedRecycleNodes_.forEach((nodes, _) => {
      nodes.forEach((node) => {
        node.setActiveInternal(active, true);
      })
    })
  }

  public getDumpInfo(): string {
    const result = Array.from(this.cachedRecycleNodes_.entries())
      .map(([reuseKey, views]) => ({
        reuseKey,
        nodeId: views.map(view => view.id__())
      }))
    return JSON.stringify(result);
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
    if (!this.fwdMap_.has(key)) {
      return;
    }
    const rev = this.fwdMap_.get(key);
    this.fwdMap_.delete(key);
    this.revMap_.delete(rev);
  }

  get(key: number): number | undefined {
    return this.fwdMap_.get(key) ?? this.revMap_.get(key);
  }

  add(pair: [number, number]) {
    this.fwdMap_.set(pair[0], pair[1]);
    this.revMap_.set(pair[1], pair[0]);
  }
}
