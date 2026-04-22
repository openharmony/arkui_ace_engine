/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

type ReusePoolOwnership = 'shared' | 'perInstance';

type ReusableComponentConstructor = Function;

interface IReusableInfo {
  readonly count: number;
  maxCount: number;
  readonly reuseId?: string;
}

// TS declaration for WrappedBuilder
declare class WrappedBuilder<Args extends unknown[] = []> {
  // Property holding the builder function
  builder: (...args: Args) => void;

  // Constructor accepts the builder function
  constructor(builder: (...args: Args) => void);
}

interface IReusePool {
  getReusableInfo(
    constructor: ReusableComponentConstructor,
    reuseId?: string
  ): Array<IReusableInfo> | IReusableInfo | undefined;

  preRender(builder : WrappedBuilder<[]>, n : number) : Promise<void>;

}

/**
 * Implements the `__ReusePool_Internal__` class responsible for managing recycled
 * ViewPU/ViewV2 instances
 * Supports
 *  - Per-instance reuse pools
 *  - Shared reuse pools (across multiple parent views)
 *  - Element ID remapping for recycled nodes
 *  - Owner tracking for shared pool lifecycle management
 */
class __ReusePool_Internal__ implements IReusePool {
    // Key suffixes for internal cache buckets
    private static readonly SUFFIX_DEFAULT = 'INTERNAL_DEFAULT';
    private static readonly SUFFIX_COMPLIMIT = 'INTERNAL_COMPLIMIT';
    private static readonly DEFAULT_MAX_COUNT = 100;
    private static readonly USER_MAX_COUNT_LIMIT = 200;

    // Cached recycled nodes
    private cached_: Map<string, Array<PUV2ViewBase>> = new Map();
    private accepts_: Set<abstract new (...args: PUV2ViewBase[]) => PUV2ViewBase> | undefined;
    private maxCounts_: Map<string, number> = new Map();

    // Maps original element IDs to new recycled element IDs.
    // Used when a recycled node is reattached and receives a new element ID.
    private recycleIdMapping_ = new Map<number, number>();
    // Track active instances (on screen) by their reuseIds
    private activeReuseIds_: Map<string, Set<string>> = new Map(); // clsName -> Set of reuseIds

    private ownership_: ReusePoolOwnership;
    private owners_ = new Set<PUV2ViewBase>();
    // Global registry of shared pools
    static sharedPools_: Map<string, __ReusePool_Internal__> = new Map();

    private static ctorIdCounter_: number = 0;
    private static ctorIdMap_: WeakMap<Function, string> = new WeakMap();

    // Track all names a constructor has been known by
    private static ctorKnownNames_: WeakMap<Function, Set<string>> = new WeakMap();

    // Registers a constructor name so aliased imports are recognized as defaults
    // Used to construct reuse component key with func ptrs of component class
    static registerCtorName(ctor: Function, name: string): void {
        let names = __ReusePool_Internal__.ctorKnownNames_.get(ctor);
        if (!names) {
            names = new Set();
            __ReusePool_Internal__.ctorKnownNames_.set(ctor, names);
        }
        names.add(name);
    }

    // Returns true if reuseId is a default and  not user-specified
    private isDefaultReuseId(cls: Function, reuseId: string): boolean {
        if (reuseId === cls.name) {
            return true;
        }
        // Check if the reuseId matches ANY known name for this constructor
        // (covers aliases like CompA imported as CompB)
        const knownNames = __ReusePool_Internal__.ctorKnownNames_.get(cls);
        if (knownNames?.has(reuseId)) {
            return true;
        }
        return false;
    }

    // Returns or assigns a stable string key for a constructor,used as a cache key prefix
    static getCtorKey(ctor: Function): string {
        let key = __ReusePool_Internal__.ctorIdMap_.get(ctor);
        if (key === undefined) {
            key = `__ctor_${__ReusePool_Internal__.ctorIdCounter_++}`;
            __ReusePool_Internal__.ctorIdMap_.set(ctor, key);
        }
        return key;
    }

    // Registers an owner of this pool
    public addOwner(owner: PUV2ViewBase): void {
        this.owners_.add(owner);
    }

    // Removes an owner
    // If no owners remain, the pool is automatically deactivated.
    public removeOwner(owner: PUV2ViewBase): void {
        this.owners_.delete(owner);
        if (this.owners_.size === 0) {
            this.deactivate();
        }
    }

    isActive(): boolean {
        return this.owners_.size > 0;
    }

    deactivate(): void {
        this.purgeAllCachedRecycleNode();
        this.recycleIdMapping_.clear();
        this.activeReuseIds_.clear();
    }

    /**
     * @param ownership Defines who owns the reuse pool.
     * @param poolAccepts List of accepted view constructors eligible for reuse.
     *
     * Requirements:
     * - Must be a non-empty array, otherwise an error is thrown.
     * - Entries must be constructors of ViewV2 or ViewPU (same as getReusableInfo).
     * - Only @Reusable / @ReusableV2 annotated views are allowed.
     *
    */
    private constructor(
        ownership: ReusePoolOwnership,
        poolAccepts: Array<new (...args: PUV2ViewBase[]) => PUV2ViewBase>)
    {
        if (!poolAccepts || poolAccepts.length === 0) {
            throw new Error('poolAccepts must be a non-empty array');
        }
        for (const ctor of poolAccepts) {
            if (typeof ctor !== 'function') {
                throw new Error('poolAccepts must contain constructors only');
            }
        }
        this.ownership_ = ownership;
        this.accepts_ = new Set(poolAccepts);
    }

    // Called by framework when a component is created (in reuseOrCreateNewComponent)
    public registerActiveReuseId(cls: abstract new (...args: unknown[]) => PUV2ViewBase, reuseId: string): void {
        const ctorKey = __ReusePool_Internal__.getCtorKey(cls);
        let set = this.activeReuseIds_.get(ctorKey);
        if (!set) {
            set = new Set();
            this.activeReuseIds_.set(ctorKey, set);
        }
        set.add(reuseId);
    }

    // Called by framework when component is recycled
    public unregisterActiveReuseId(cls: abstract new (...args: unknown[]) => PUV2ViewBase, reuseId: string): void {
        const ctorKey = __ReusePool_Internal__.getCtorKey(cls);
        const set = this.activeReuseIds_.get(ctorKey);
        if (set) {
            set.delete(reuseId);
            if (set.size === 0) {
                this.activeReuseIds_.delete(ctorKey);
            }
        }
    }

    // Updates the max count for a reuseId (or all buckets if id is undefined) and prunes excess cached nodes
    private pruneMaxCount(prefix: string, id: string | undefined, componentLimitKey: string, value: number): void {
        // Clamp negative values to 0; user-supplied positive values (including > 100) are allowed
        if (value < 0) {
            stateMgmtConsole.warn(`GlobalReuse: maxCount=${value} is set to negative, clamping to 0`);
            value = 0;
        }
        if (value > __ReusePool_Internal__.USER_MAX_COUNT_LIMIT) {
            stateMgmtConsole.warn(`GlobalReuse: maxCount=${value} exceeds maximum allowed. Max can be only ${__ReusePool_Internal__.USER_MAX_COUNT_LIMIT},
                Set to ${__ReusePool_Internal__.USER_MAX_COUNT_LIMIT}`);
            value = __ReusePool_Internal__.USER_MAX_COUNT_LIMIT;
        }

        if (id === undefined) {
            this.maxCounts_.set(componentLimitKey, value);
            // Prune ALL buckets for this class
            for (const [k, arr] of this.cached_) {
                if (k.startsWith(prefix)) {
                    while (arr.length > value) {
                        arr.pop()?.resetRecycleCustomNode();
                    }
                }
            }
        } else {
            const key = prefix + id;
            this.maxCounts_.set(key, value);
            const arr = this.cached_.get(key);
            if (arr) {
                while (arr.length > value) {
                    arr.pop()?.resetRecycleCustomNode();
                }
            }
        }
    }

    /**
     * Returns reuse pool statistics and limits for a given reusable component.
     *
     * This API allows querying and configuring reuse behavior for a component
     * stored in this __ReusePool_Internal__.
     *
     * Behavior depends on whether a specific `reuseId` is provided and whether
     * the component has been recycled with reuseIds.
     *
     * @param cls
     *   Constructor of the reusable component (@ReusableV2/@ComponentV2 or
     *   @Reusable/@Component) whose pool information should be queried.
     *
     * @param reuseId (optional)
     *   Specific reuse identifier. When provided, information is returned only
     *   for that reuseId.
     *
     * @returns
     * - `undefined`
     *     If this pool does not accept the given component type.
     *
     * - `IReusableInfo`
     *     If a specific `reuseId` is requested OR if the component has not
     *     been recycled using reuseIds (total pool view).
     *
     * - `IReusableInfo[]`
     *     If the component has been recycled using reuseIds and no specific
     *     `reuseId` is requested. One entry is returned for each reuseId.
     *
     * Notes:
     * - `count` reflects the number of instances currently cached in the pool.
     * - `maxCount` controls the maximum number of instances allowed in the pool.
     * - Updating `maxCount` may immediately evict cached instances if the
     *   current pool size exceeds the new limit.
    */
    getReusableInfo( cls: abstract new (...args: PUV2ViewBase[]) => PUV2ViewBase, reuseId?: string
        ): IReusableInfo | IReusableInfo[] | undefined {

        if (!this.acceptsComponent(cls)) {
            return undefined;
        }

        const ctorKey = __ReusePool_Internal__.getCtorKey(cls);
        const prefix = ctorKey + '__';
        const defaultKey = `${prefix}${__ReusePool_Internal__.SUFFIX_DEFAULT}`;
        const componentLimitKey = `${prefix}${__ReusePool_Internal__.SUFFIX_COMPLIMIT}`;
        const self = this;

        // Creates a live IReusableInfo whose count/maxCount always reflect current pool state.
        const createInfo = (id?: string): IReusableInfo => {
            const key = id === undefined ? defaultKey : prefix + id;
            return {
                reuseId: id,

                get count(): number {
                    return self.cached_.get(key)?.length ?? 0;
                },
                get maxCount(): number {
                    return self.getEffectiveMaxCount(key, cls);
                },
                set maxCount(value: number) {
                    self.pruneMaxCount(prefix, id, componentLimitKey, value);
                }
            };
        };

        // Specific reuseId requested — direct lookup
        if (reuseId !== undefined) {
            return createInfo(reuseId);
        }

        // Discover all known reuseIds for this class from cache, active instances, and maxCounts
        const allKnownIds = new Set<string>();

        for (const key of this.cached_.keys()) {
            if (!key.startsWith(prefix)) {
                continue;
            }
            const id = key.slice(prefix.length);
            if (id !== __ReusePool_Internal__.SUFFIX_DEFAULT && id !== __ReusePool_Internal__.SUFFIX_COMPLIMIT) {
                allKnownIds.add(id);
            }
        }

        this.activeReuseIds_.get(ctorKey)?.forEach(id => allKnownIds.add(id));

        for (const key of this.maxCounts_.keys()) {
            if (!key.startsWith(prefix)) {
                continue;
            }
            const id = key.slice(prefix.length);
            if (id !== __ReusePool_Internal__.SUFFIX_DEFAULT && id !== __ReusePool_Internal__.SUFFIX_COMPLIMIT) {
                allKnownIds.add(id);
            }
        }

        // Keep only reuseIds with cached instances or a custom maxCount
        const relevantIds: string[] = [];
        for (const id of allKnownIds) {
            const key = prefix + id;
            if ((this.cached_.get(key)?.length ?? 0) > 0 || this.maxCounts_.has(key)) {
                relevantIds.push(id);
            }
        }
        relevantIds.sort();

        if (relevantIds.length === 0) {
            return createInfo(undefined);
        }

        const result: IReusableInfo[] = [createInfo(undefined)];
        for (const id of relevantIds) {
            result.push(createInfo(id));
        }
        return result;
    }

    /**
     * Pre-renders reusable component instances using the provided builder.
     *
     * @param builder
     *   WrappedBuilder that constructs the component to be pre-rendered.
     *
     * @param n
     *   Number of component instances to pre-render.
     *
     * @returns
     *   A Promise that resolves when the pre-render process completes.
     *
     * Notes:
     * - All builder executions occur within a pre-render context.
     * - If an error occurs during rendering, it is logged and the pre-render
     *   context is safely cleared.
     * - The pre-render context is always cleaned up via `endPreRender()`.
    */
    async preRender(builder: WrappedBuilder<[]>, n: number): Promise<void> {
        let preRenderError: unknown;
        try {
            // Activate pre-render context
            PUV2ViewBase.beginPreRender(this);

            for (let i = 0; i < n; i++)  {
                builder.builder();
            }
        } catch (e) {
            stateMgmtConsole.error('ERROR: PreRender error:', e);
            preRenderError = e;
        }
        finally {
            // clear context
            PUV2ViewBase.endPreRender();
        }
        // Queue the resolve as the final idle task
        // It will fire after all the queued component creations complete
        return new Promise<void>((resolve, reject) => {
            ObserveV2.getObserve().queueIdleTask(() => {
                preRenderError ? reject(preRenderError) : resolve()
            });
        });
    }

    // Constructs the cache key for a given class and reuseId
    // Maps default/alias reuseIds to the INTERNAL_DEFAULT bucket
    private buildKey( cls: abstract new (...args: PUV2ViewBase[]) => PUV2ViewBase, reuseId?: string ): string {
        if (!cls) {
            stateMgmtConsole.debug(`GlobalReuse: buildKey called with undefined cls, reuseId=${reuseId}`);
            return `unknown__${reuseId || 'default'}`;
        }
        const ctorKey = __ReusePool_Internal__.getCtorKey(cls);
        if (!reuseId || this.isDefaultReuseId(cls, reuseId)) {
            return `${ctorKey}__${__ReusePool_Internal__.SUFFIX_DEFAULT}`;
        }
        return `${ctorKey}__${reuseId}`;
    }

    /**
     * Returns the mapped reuse ID for a given element ID.
     * @param elmtId - Original element ID
     * @returns The mapped element ID
    */
    public proxyNodeId(elmtId: number): number {
        return this.recycleIdMapping_.get(elmtId) ?? elmtId;
    }

    /* Updates the mapping from old element ID to new element ID
     * @param oldElmtId - Original element ID
     * @param newElmtId - New element ID to map to
    */
    public updateReuseIdMapping(oldElmtId: number, newElmtId: number): void {
        if (oldElmtId !== newElmtId) {
            this.recycleIdMapping_.set(oldElmtId, newElmtId);
        }
    }

    // When parent JS View is deleted, release all cached nodes
    public purgeAllCachedRecycleNode(): void {
        this.cached_.forEach(arr => arr.forEach(v => v.resetRecycleCustomNode()));
        this.cached_.clear();
    }

    // Clears all element ID mappings
    public purgeAllCachedRecycleElmtIds(): void {
        this.recycleIdMapping_.clear();
    }

    /**
     * Factory method to create a __ReusePool_Internal__
     * @param config Optional configuration
     * @param config.reusePool - 'shared' or 'perInstance'
     * @param config.poolAccepts - Optional class references this pool accepts
     * @returns __ReusePool_Internal__ instance
     */
    public static create(config?: {
        reusePool?: ReusePoolOwnership,
        poolAccepts?: Array<new (...args: PUV2ViewBase[]) => PUV2ViewBase>,
        owner?: PUV2ViewBase
    }): __ReusePool_Internal__ {

        const ownership: ReusePoolOwnership =
            config?.reusePool ?? 'shared';

        const accepted = config?.poolAccepts;

        // poolAccepts is mandatory for all cases
        if (!accepted || accepted.length === 0) {
            throw new Error('Global Reuse Pool requires a non-empty poolAccepts array');
        }

        if (ownership === 'shared') {
            if (!config.owner || !config.owner.constructor) {
                throw new Error('Global Reuse: shared pool requires a valid owner with a constructor');
            }
            const ownerKey = __ReusePool_Internal__.getCtorKey(config.owner.constructor);
            const acceptedKeys = accepted.map(c => __ReusePool.getCtorKey(c)).sort().join('_');
            const key = `${ownerKey}_${acceptedKeys}`;

            let pool = __ReusePool_Internal__.sharedPools_.get(key);

            if (!pool) {
                pool = new __ReusePool_Internal__('shared', accepted);
                __ReusePool_Internal__.sharedPools_.set(key, pool);
            }
            return pool;
        }
        return new __ReusePool_Internal__('perInstance', accepted);
    }

    /**
     * Checks if this pool accepts a component class
     * @param cls - Component class to check
     * @returns true if accepted, false otherwise
    */
    acceptsComponent(cls: abstract new (...args: PUV2ViewBase[]) => PUV2ViewBase): boolean {
        return !this.accepts_ || this.accepts_.has(cls);
    }

    // Returns the effective maxCount for a cache bucket.
    // Priority: bucket-specific limit → component-wide limit → unlimited.
    private getEffectiveMaxCount(key: string, cls: abstract new (...args: PUV2ViewBase[]) => PUV2ViewBase): number {
        const ctorKey = __ReusePool_Internal__.getCtorKey(cls);
        return this.maxCounts_.get(key) ?? // bucket with its own limit
            this.maxCounts_.get(`${ctorKey}__${__ReusePool_Internal__.SUFFIX_COMPLIMIT}`) ?? // a component-wide default
            __ReusePool_Internal__.DEFAULT_MAX_COUNT; // default cap of 100
    }

    /**
     * Pushes a node into the pool for a given reuse ID
     * @param reuseId - Reuse identifier
     * @param node - View instance to recycle
     * @param cls - Component class
    */
    push<T extends PUV2ViewBase>(reuseId: string, node: PUV2ViewBase, cls: abstract new (...args: PUV2ViewBase[]) => PUV2ViewBase): void {
        if (!this.acceptsComponent(cls)) {
            stateMgmtConsole.error(`GlobalReuse Push does not acceptComponent: ${cls.name} so returns FAIL`)
            return;
        }

        const key = this.buildKey(cls, reuseId);

        // Check maxCount before allowing push
        const currentMax = this.getEffectiveMaxCount(key, cls);

        let currentArr = this.cached_.get(key);
        if (!currentArr) {
            currentArr = [];
            this.cached_.set(key, currentArr);
        }

        // If current count already at or above maxCount, reject the push
        if (currentArr.length >= currentMax) {
            stateMgmtConsole.error(`Global Reuse: Push rejected - maxCount=${currentMax} reached for ${key}`);
            // Instead of pushing to pool, destroy the node
            node.resetRecycleCustomNode();
            return;
        }

        // When pushing to pool, unregister from active instances
        if (!this.isDefaultReuseId(cls, reuseId)) {
            this.unregisterActiveReuseId(cls, reuseId);
        }
        currentArr.push(node);
        stateMgmtConsole.debug(`PUSH reuseId=${reuseId} → ` + currentArr.map(v => `${v.constructor?.name}[${v.id__()}]`).join(', '));
    }

   /**
     * Pops a node from the pool for a given reuse ID
     * @param reuseId - Reuse identifier
     * @param cls - Component class
     * @returns Recycled View instance or undefined if none
    */
    pop<T extends PUV2ViewBase>(reuseId: string, cls: abstract new (...args: PUV2ViewBase[]) => T): T | undefined {
        if (!this.acceptsComponent(cls)) {
            return undefined;
        }

        const key = this.buildKey(cls, reuseId);
        const currentMax = this.getEffectiveMaxCount(key, cls);

        // If maxCount is 0, no instances should be available
        if (currentMax === 0) {
            stateMgmtConsole.error(`Global Reuse Pool: Pop rejected - maxCount=0 for ${key}`);
            return undefined;
        }

        const arr = this.cached_.get(key);
        const ret = arr?.pop() as T | undefined;

        stateMgmtConsole.debug(`Reuse Pop status of ${reuseId} — Reusing node: ${ret}`);
        // When popping from pool, register as active again - but only for real reuseIds
        if (ret && reuseId && !this.isDefaultReuseId(cls, reuseId)) {
            this.registerActiveReuseId(cls, reuseId);
        }
        return ret;
    }

    public getDumpInfo(): string {
        const result = Array.from(this.cached_.entries())
        .map(([reuseKey, views]) => ({
            reuseKey,
            className: views[0]?.constructor?.name ?? 'unknown',
            nodeId: views.map(view => view.id__())
        }))
        return JSON.stringify(result);
    }
}
// Temporary alias since ace-loader still references __ReusePool
// Remove once they switch to use __ReusePool_Internal__
const __ReusePool = __ReusePool_Internal__;