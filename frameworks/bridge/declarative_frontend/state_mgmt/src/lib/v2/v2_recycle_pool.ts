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
 *
 * File: RecyclePoolV2 - Manages the recycling of cached JS objects for component reuse.
 *
 * Description: This class handles the caching and recycling of JS components in a pool,
 * ensuring that components are reused efficiently when needed, and mapping old element IDs
 * to new ones for recycling purposes.
 */
/**
 * @class RecyclePoolV2
 * @description Manages cached JS objects of components for recycling.
 * This class provides methods for pushing, popping, and mapping recycled elements and their new IDs.
 * It ensures that recycled components are reused when necessary and that element IDs are tracked for mapping
 */
class RecyclePoolV2 {
    // key: recycle element name, value: recycled element JS object
    private cachedRecycleComponents_: Map<string, Array<ViewV2>> = undefined;

    private recycledIdRegistry_?: RecycledIdRegistry;
    // Track pending cache reduction timers per name
    private pendingCacheCleanTimers_: Map<string, any> = undefined;
    // Track maximum cache size per name (for timer restart logic)
    private maxCacheSizes_: Map<string, number> = undefined;
    // Pending nodes for progressive release
    private pendingProgressiveReleaseNodes_: Array<ViewV2> = undefined;
    // Callback to request progressive release (set by parent ViewV2)
    private requestProgressiveReleaseCallback_: () => void = undefined;
    private defaultCacheCount: number;
    private reuseIdForOptimize: Set<string> = new Set<string>();

    constructor() {
      this.cachedRecycleComponents_ = new Map<string, Array<ViewV2>>();
      this.recycledIdRegistry_ = new RecycledIdRegistry();
      this.pendingCacheCleanTimers_ = new Map<string, any>();
      this.maxCacheSizes_ = new Map<string, number>();
      this.pendingProgressiveReleaseNodes_ = new Array<ViewV2>();
      this.defaultCacheCount = 8;
    }
  
    /**
     * @function pushRecycleV2Component
     * @description Adds a recycled component (ViewV2) to the pool based on its reuseId.
     * If the pool does not contain a list for the specified reuseId, it creates one before
     * adding the component.
     *
     * @param {string} reuseId - The id of the component being recycled.
     * @param {ViewV2} reuseComp - The recycled component to be added to the pool.
     */
    public pushRecycleV2Component(reuseId: string, reuseComp: ViewV2): void {
      if (!this.cachedRecycleComponents_.get(reuseId)) {
        this.cachedRecycleComponents_.set(reuseId, new Array<ViewV2>());
      }
      this.cachedRecycleComponents_.get(reuseId)?.push(reuseComp);
      if (reuseComp.__getReusableMemOptStrategy__Internal() === 1) {
        this.reuseIdForOptimize.add(reuseId);
        const cachedComponents = this.cachedRecycleComponents_.get(reuseId);
        if (cachedComponents && cachedComponents.length > this.defaultCacheCount) {
          const currentSize = cachedComponents.length;
          const maxSize = this.maxCacheSizes_.get(reuseId) || 0;
          // Only restart timer if cache size reaches a new maximum
          if (currentSize > maxSize) {
            this.maxCacheSizes_.set(reuseId, currentSize);
            this.scheduleCacheCleanTask(reuseId);
          }
        }
      }
    }

    /**
     * @function popRecycleV2Component
     * @description Retrieves and removes a recycled component (ViewV2) from the pool based on its reuseId.
     * Returns undefined if no recycled component is found for the specified name.
     *
     * @param {string} reuseId - The id of the component being recycled.
     * @returns {ViewV2 | undefined} - The recycled component, or undefined if not found.
     */
    public popRecycleV2Component(reuseId: string): ViewV2 | undefined {
      return this.cachedRecycleComponents_.get(reuseId)?.pop();
    }

    /**
     * @function updateRecycleIdMapping
     * @description Updates the mapping of the recycledElementId element ID to a new element ID in
     * the bi-directional map. This ensures that recycled elements are mapped correctly when
     * their IDs change.
     *
     * @param {number} recycledElementId - The ID of the recycled element.
     * @param {number} newElmtId - The new ID to map the recycled element to.
     */
    public updateRecycleIdMapping(recycledElementId: number, newElmtId: number): void {
      this.recycledIdRegistry_.delete(recycledElementId);
      this.recycledIdRegistry_.add([recycledElementId, newElmtId]);
    }

    /**
     * @function getRecycleIdMapping
     * @description Retrieves the mapped ID for a recycled element, if available.
     * If no mapping exists, returns the original element ID.
     *
     * @param {number} recycledElementId - The ID of the recycled element.
     * @returns {number} - The mapped ID or the original ID if no mapping exists.
     */
    public getRecycleIdMapping(recycledElementId : number): number {
      const mappedId = this.recycledIdRegistry_.get(recycledElementId);
      if (!mappedId) {
        return recycledElementId;
      }
      return mappedId;
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
     * @param {string} reuseId - The reuse identifier for the cached components.
     * @param {number} targetSize - The target cache size.
     * @returns {number} - The number of nodes prepared for release.
     */
    public prepareCleanCacheToTargetProgressive(reuseId: string, targetSize: number): number {
      const cachedComponents = this.cachedRecycleComponents_.get(reuseId);
      if (!cachedComponents || cachedComponents.length <= targetSize) {
        return 0;
      }

      const componentsToRemove = cachedComponents.length - targetSize;
      for (let i = 0; i < componentsToRemove; i++) {
        const node = cachedComponents.shift();
        if (node) {
          this.pendingProgressiveReleaseNodes_.push(node);
        }
      }

      // Clear the timer tracking and max size
      this.pendingCacheCleanTimers_.delete(reuseId);
      this.maxCacheSizes_.delete(reuseId);

      return componentsToRemove;
    }

    private scheduleCacheCleanTask(reuseId: string): void {
      const existingTimer = this.pendingCacheCleanTimers_.get(reuseId);
      if (existingTimer !== undefined) {
        clearTimeout(existingTimer);
      }

      const timerId = setTimeout(() => {
        // Prepare nodes for progressive release
        const pendingCount = this.prepareCleanCacheToTargetProgressive(reuseId, this.defaultCacheCount);

        // If there are nodes to release and callback is available, request progressive release
        if (pendingCount > 0 && this.requestProgressiveReleaseCallback_) {
          this.requestProgressiveReleaseCallback_();
        }
      }, 300000); // 5 minutes

      this.pendingCacheCleanTimers_.set(reuseId, timerId);
    }

    /**
     * @function purgeAllCachedRecycleElements
     * @description
     * Clears all cached components from the recycle pool by clearing them
     * from the cached components map. This function is invoked when a parent JS view
     * is deleted to clean up all recycled components associated with it.
     *
     * It in turn calls the native `resetRecycleCustomNode` function to restore the
     * custom node linked to the JSView object:
     * - If the JSView object has been garbage collected, the CustomNode is deleted.
     * - If the JSView object is managed by the RecyclePool, the CustomNode is reused.
     */
    public purgeAllCachedRecycleElmtIds(): void {
      this.pendingCacheCleanTimers_.forEach((timerId) => {
        clearTimeout(timerId);
      });
      this.pendingCacheCleanTimers_.clear();
      this.maxCacheSizes_.clear();

      this.cachedRecycleComponents_.forEach((components_, _) => {
        components_.forEach((node) => {
          node.resetRecycleCustomNode();
        });
      });
      this.cachedRecycleComponents_.clear();

      this.pendingProgressiveReleaseNodes_.forEach((node) => {
        node.resetRecycleCustomNode();
      });
      this.pendingProgressiveReleaseNodes_ = new Array<ViewV2>();
    }

    public purgeAllCleanableRecycleElmtIds(): void {
      this.pendingCacheCleanTimers_.forEach((timerId) => {
        clearTimeout(timerId);
      });
      this.pendingCacheCleanTimers_.clear();
      this.maxCacheSizes_.clear();

      this.cachedRecycleComponents_.forEach((components_, reuseId) => {
        if (!this.reuseIdForOptimize.has(reuseId)) {
          return;
        }
        components_.forEach((node) => {
          node.resetRecycleCustomNode();
        });
      });
      this.reuseIdForOptimize.forEach((reuseId) => {
        this.cachedRecycleComponents_.delete(reuseId);
      });
      this.reuseIdForOptimize.clear();

      this.pendingProgressiveReleaseNodes_.forEach((node) => {
        node.resetRecycleCustomNode();
      });
      this.pendingProgressiveReleaseNodes_ = new Array<ViewV2>();
    }

    /**
     * @function preparePurgeAllCleanableRecycleElmtIdsProgressive
     * @description
     * Prepares to release all cleanable components by moving them to the pending progressive release list.
     * The actual release will be done later by releaseCachedNodesProgressive.
     *
     * @returns {number} - The number of nodes prepared for release.
     */
    public preparePurgeAllCleanableRecycleElmtIdsProgressive(): number {
      this.pendingCacheCleanTimers_.forEach((timerId) => {
        clearTimeout(timerId);
      });
      this.pendingCacheCleanTimers_.clear();
      this.maxCacheSizes_.clear();

      let count = 0;
      this.cachedRecycleComponents_.forEach((components_, reuseId) => {
        if (!this.reuseIdForOptimize.has(reuseId)) {
          return;
        }
        components_.forEach((node) => {
          this.pendingProgressiveReleaseNodes_.push(node);
          count++;
        });
      });
      this.reuseIdForOptimize.forEach((reuseId) => {
        this.cachedRecycleComponents_.delete(reuseId);
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
  }

  /**
   * @class RecycledIdRegistry
   * @description A helper class that maintains a bi-directional map of recycle element ID with
   * the new elementID that gets created on every initial render.
   * This class supports adding, retrieving, and deleting mappings between old and new element IDs
   *  for recycling purposes.
   */
  class RecycledIdRegistry {
    private fwdMap_: Map<number, number>;
    private revMap_: Map<number, number>;

    constructor() {
      this.fwdMap_ = new Map<number, number>();
      this.revMap_ = new Map<number, number>();
    }

    /**
     * @function delete
     * @description Deletes the mapping for a given element ID from both the
     * forward and reverse maps.
     *
     * @param {number} key - The element ID to be removed from the map.
     */
    delete(key: number): void {
      if (!this.fwdMap_[key]) {
        return;
      }
      const rev = this.fwdMap_[key];
      this.fwdMap_.delete(key);
      this.revMap_.delete(rev);
    }

    /**
     * @function get
     * @description Retrieves the mapped ID for a given element ID, either from the
     * forward or reverse map.
     *
     * @param {number} key - The element ID for which the mapped ID is requested.
     * @returns {number | undefined} - The mapped ID or undefined if no mapping exists.
     */
    get(key: number): number | undefined {
      return this.fwdMap_[key] || this.revMap_[key];
    }

    /**
     * @function add
     * @description Adds a new mapping pair between an old and new element ID to both
     * the forward and reverse maps.
     *
     * @param {Array<number>} pair - A pair of old and new element IDs to be added to the mapping.
     */
    add(pair: [number, number]): void {
      this.fwdMap_[pair[0]] = pair[1];
      this.revMap_[pair[1]] = pair[0];
    }
  }