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
 
    private recycledIdRegistry_? : RecycledIdRegistry;

    constructor() {
      this.cachedRecycleComponents_ = new Map<string, Array<ViewV2>>();
      this.recycledIdRegistry_ = new RecycledIdRegistry();
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
    public updateRecycleIdMapping(recycledElementId : number, newElmtId: number): void {
      this.recycledIdRegistry_.delete(recycledElementId );
      this.recycledIdRegistry_.add([recycledElementId , newElmtId]);
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
      const mappedId  = this.recycledIdRegistry_.get(recycledElementId );
      if (!mappedId ) {
        return recycledElementId ;
      }
      return mappedId ;
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
  
      this.cachedRecycleComponents_.forEach((components_, _) => {
        components_.forEach((node) => {
          node.resetRecycleCustomNode();
        });
      })
      this.cachedRecycleComponents_.clear();
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
    delete(key: number) {
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
    add(pair: [number, number]) {
      this.fwdMap_[pair[0]] = pair[1];
      this.revMap_[pair[1]] = pair[0];
    }

  }