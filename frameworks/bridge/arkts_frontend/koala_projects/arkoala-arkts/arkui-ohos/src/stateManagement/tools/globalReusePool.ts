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

import { IVariableOwner, ReusePoolOwnership, IGlobalReusePoolVariable } from '../decorator';
import { ExtendableComponent } from '../../component/extendableComponent';
import { StateUpdateLoop } from '../base/stateUpdateLoop';
import { WrappedBuilder, CustomBuilder } from '../../component/builder';
import { int32 } from '@koalaui/common';
import { Disposable } from '@koalaui/runtime';
import { BuilderNode } from '../../BuilderNode';
import { IReusableInfo } from '../utils';

/**
 * Constructor type for a reusable component class (ViewPU or ViewV2).
 * Accepts any subclass constructor whose name identifies the component
 * registered in the pool's acceptedClasses list.
 */

/**
 * Internal bucket-key suffixes. Reusable components without a user-supplied
 * reuseId are stored under SUFFIX_DEFAULT. SUFFIX_COMPLIMIT is used to record
 * a class-wide maxCount that applies when no per-bucket override exists.
 */
const SUFFIX_DEFAULT: string = 'INTERNAL_DEFAULT';
const SUFFIX_COMPLIMIT: string = 'INTERNAL_COMPLIMIT';
const DEFAULT_MAX_COUNT: int32 = 100;
const USER_MAX_COUNT_LIMIT: int32 = 200;

/**
 * Live IReusableInfo implementation. The fields `count` and `maxCount` are
 * computed against the owning pool on every read — the same instance can be
 * cached and inspected later and will reflect current state.
 */
export class ReusableInfo implements IReusableInfo {
    private readonly pool_: GlobalReusePool;
    private readonly key_: string;
    private readonly classKey_: string;
    public readonly reuseId?: string;

    constructor(pool: GlobalReusePool, key: string, classKey: string, reuseId?: string) {
        this.pool_ = pool;
        this.key_ = key;
        this.classKey_ = classKey;
        this.reuseId = reuseId;
    }

    public get count(): int32 {
        return this.pool_.__getBucketCount_Internal(this.key_);
    }

    public get maxCount(): int32 {
        return this.pool_.__getEffectiveMaxCount_Internal(this.key_, this.classKey_);
    }

    public set maxCount(value: int32) {
        this.pool_.__setMaxCount_Internal(this.classKey_, this.reuseId, value);
    }
}

export class GlobalReusePool implements IGlobalReusePoolVariable {
    public readonly ownership: ReusePoolOwnership;
    public readonly acceptedClasses: Array<string>;
    public readonly owner: IVariableOwner;

    private accepts_: Set<string>;

    // Cache: bucketKey -> array of recycled instances.
    // bucketKey is `${classKey}__${reuseId}` or `${classKey}__${SUFFIX_DEFAULT}`.
    private cached_: Map<string, Array<Object>> = new Map<string, Array<Object>>();

    // maxCount overrides keyed by bucketKey or `${classKey}__${SUFFIX_COMPLIMIT}`.
    private maxCounts_: Map<string, int32> = new Map<string, int32>();

    // Active (on-screen) reuseIds per class — used to surface every reuseId
    // the application has touched, so getReusableInfo() returns entries for
    // them even when their cache count is currently 0.
    private activeReuseIds_: Map<string, Set<string>> = new Map<string, Set<string>>();

    // Re-entrancy guard for pruneBucket_: a bucket's pop() might trigger an
    // aboutToRecycle callback that pushes back into the same bucket.
    private pruning_: Set<string> = new Set<string>();

    private owners_: Set<ExtendableComponent> = new Set<ExtendableComponent>();
    private registryKey_: string | undefined = undefined;

    // for framework re-entrant pop staging
    public static pendingInitializersForReuse: Object | undefined = undefined;
    public static pendingParentQueue: Array<ExtendableComponent> = [];

    /**
     * @internal — active pre-render target pool. When non-undefined, the
     * framework's reusable-component creation path pushes newly built
     * components into this pool instead of attaching them to the UI tree.
     */
    private static preRenderPool_: GlobalReusePool | undefined = undefined;

    public static beginPreRender(pool: GlobalReusePool): void {
        GlobalReusePool.preRenderPool_ = pool;
    }

    public static endPreRender(): void {
        GlobalReusePool.preRenderPool_ = undefined;
    }

    public static getPreRenderPool(): GlobalReusePool | undefined {
        return GlobalReusePool.preRenderPool_;
    }

    public static isPreRendering(): boolean {
        return GlobalReusePool.preRenderPool_ !== undefined;
    }

    constructor(ownership: ReusePoolOwnership, acceptedClasses: Array<string>, owner: IVariableOwner) {
        if (!acceptedClasses || acceptedClasses.length === 0) {
            throw new Error('GlobalReusePool: poolAccepts must be a non-empty array');
        }
        this.ownership = ownership;
        this.acceptedClasses = acceptedClasses;
        this.owner = owner;
        this.accepts_ = new Set<string>();
        for (const c of acceptedClasses) {
            const lastDot = c.lastIndexOf('.');
            this.accepts_.add(lastDot >= 0 ? c.substring(lastDot + 1) : c);
        }
    }

    public __setRegistryKey_Internal(k: string): void {
        this.registryKey_ = k;
    }
    public __getRegistryKey_Internal(): string | undefined {
        return this.registryKey_;
    }

    // ─────────────────────────────────────────────────────────────────────
    // IGlobalReusePoolVariable — framework API
    // ─────────────────────────────────────────────────────────────────────

    public acceptsComponent(reusableComp: string): boolean {
        const lastDot = reusableComp.lastIndexOf('.');
        const key = lastDot >= 0 ? reusableComp.substring(lastDot + 1) : reusableComp;
        return this.accepts_.has(key);
    }

    public addOwner(owner: ExtendableComponent): void {
        this.owners_.add(owner);
    }

    public removeOwner(owner: ExtendableComponent): void {
        this.owners_.delete(owner);
        if (this.owners_.size === 0) {
            this.deactivate();
            GlobalReusePoolRegistry.remove(this);
        }
    }

    public isActive(): boolean {
        return this.owners_.size > 0;
    }

    private deactivate(): void {
        this.cached_.forEach((arr: Array<Object>) => {
            arr.forEach((scope: Object) => {
                (scope as Disposable).dispose();
            });
        });
        this.cached_.clear();
        this.maxCounts_.clear();
        this.activeReuseIds_.clear();
    }

    /**
     * Pop a recycled instance. If `reuseId` is undefined, the default bucket
     * for this class is used.
     */
    public pop(classKey: string, reuseId?: string): Object | undefined {
        const key = this.buildBucketKey_(classKey, reuseId);
        const arr = this.cached_.get(key);
        const size = arr !== undefined ? arr.length : 0;

        // Respect maxCount=0 (pool disabled for this bucket)
        const currentMax = this.getEffectiveMaxCount_(key, classKey);
        if (currentMax === 0) {
            console.log(`GlobalReuse: Pool POP rejected - maxCount=0 for ${key}`);
            return undefined;
        }

        if (arr === undefined || arr.length === 0) {
            return undefined;
        }
        const inst = arr.pop();

        // Capture the current rendering parent so the framework can re-link
        // the popped instance to it after koalaui restores the cached scope.
        const currentObj = ExtendableComponent.current;
        if (currentObj !== undefined && currentObj instanceof ExtendableComponent) {
            const parent = currentObj as ExtendableComponent;
            GlobalReusePool.pendingParentQueue.push(parent);
            console.log(`GlobalReuse: Pool POP captured pendingParent=${Class.of(currentObj!).getName()} queueSize=${GlobalReusePool.pendingParentQueue.length}`);
        }

        // Track the reuseId as active again (only meaningful for non-default).
        if (reuseId !== undefined && reuseId !== classKey) {
            this.registerActiveReuseId_(classKey, reuseId);
        }
        return inst;
    }

    /**
     * Push a recycled instance into the pool. If pushing would exceed
     * maxCount for the target bucket, the instance is dropped (Disposable.dispose).
     */
    public push(classKey: string, instance: Object, reuseId?: string): boolean {
        const key = this.buildBucketKey_(classKey, reuseId);
        const currentMax = this.getEffectiveMaxCount_(key, classKey);

        let arr = this.cached_.get(key);
        if (arr === undefined) {
            arr = new Array<Object>();
            this.cached_.set(key, arr);
        }

        if (arr.length >= currentMax) {
            console.log(`GlobalReuse: Pool PUSH rejected - maxCount=${currentMax} reached for ${key}`);
            return false;   // ← caller disposes
        }

        // When pushing to pool, the instance is no longer on-screen.
        if (reuseId !== undefined && reuseId !== classKey) {
            this.unregisterActiveReuseId_(classKey, reuseId);
        }
        arr.push(instance);
        console.log(`GlobalReuse: Pool PUSH classKey=${classKey} reuseId=${reuseId ?? '<default>'} newSize=${arr.length}`);
        return true;
    }

    public peek(classKey: string, reuseId?: string): Object | undefined {
        const key = this.buildBucketKey_(classKey, reuseId);
        const arr = this.cached_.get(key);
        if (arr === undefined || arr.length === 0) {
            return undefined;
        }
        return arr[arr.length - 1];
    }

    /**
     * Inspect the pool for a given reusable component class.
     *
     * @param reusableComp The component class constructor (a subclass of
     *     ViewPU or ViewV2). The class name is derived via its `.name`
     *     property and matched against the pool's acceptedClasses.
     * @param reuseId Optional reuseId to scope the lookup to a single bucket.
     *
     */
    public getReusableInfo(
        reusableComp: Class,
        reuseId?: string
    ): IReusableInfo[] | IReusableInfo | undefined {
        // Guard against primitive/invalid class types
        if (reusableComp.isPrimitive() ||
            reusableComp === Class.from<void>() ||
            reusableComp === Class.from<null>() ||
            reusableComp === Class.from<undefined>() ||
            reusableComp === Class.from<Boolean>() ||
            reusableComp === Class.from<Byte>() ||
            reusableComp === Class.from<Short>() ||
            reusableComp === Class.from<Int>() ||
            reusableComp === Class.from<Long>() ||
            reusableComp === Class.from<Char>() ||
            reusableComp === Class.from<Float>() ||
            reusableComp === Class.from<Double>() ||
            reusableComp === Class.from<Number>() ||
            reusableComp === Class.from<String>()) {
            return undefined;
        }

        // Get class name via Class API (adjust method name to match your API)
        let classKey: string = reusableComp.getName();
        if (classKey === undefined || classKey === null || classKey.length === 0) {
            return undefined;
        }

        // Validate: pool accepts this class name?
        if (!this.acceptsComponent(classKey)) {
            return undefined;
        }

        // Normalize to the short name used as the bucket-key prefix throughout
        // the pool (see logs: pop/push use "TestChild", not the fully-qualified
        // name returned by Class.getName()).
        const lastDot = classKey.lastIndexOf('.');
        if (lastDot >= 0) {
            classKey = classKey.substring(lastDot + 1);
        }

        const prefix = `${classKey}__`;
        const defaultKey = `${prefix}${SUFFIX_DEFAULT}`;

        // 2. Specific reuseId → single info
        if (reuseId !== undefined) {
            const key = this.buildBucketKey_(classKey, reuseId);
            return new ReusableInfo(this, key, classKey, reuseId) as IReusableInfo;
        }

        // 3. Discover all known reuseIds for this class
        const allKnownIds = new Set<string>();

        // From cached buckets
        this.cached_.forEach((_v: Array<Object>, k: string) => {
            if (k.startsWith(prefix)) {
                const id = k.substring(prefix.length);
                if (id !== SUFFIX_DEFAULT && id !== SUFFIX_COMPLIMIT) {
                    allKnownIds.add(id);
                }
            }
        });

        // From active reuseIds
        this.activeReuseIds_.get(classKey)?.forEach((id: string) => {
            allKnownIds.add(id);
        });

        // From maxCount overrides
        this.maxCounts_.forEach((_v: int32, k: string) => {
            if (k.startsWith(prefix)) {
                const id = k.substring(prefix.length);
                if (id !== SUFFIX_DEFAULT && id !== SUFFIX_COMPLIMIT) {
                    allKnownIds.add(id);
                }
            }
        });

        // 4. Filter to ids with cached entries or custom maxCount
        const relevantIds: Array<string> = new Array<string>();
        allKnownIds.forEach((id: string) => {
            const k = `${prefix}${id}`;
            const cnt = this.cached_.get(k)?.length ?? 0;
            if (cnt > 0 || this.maxCounts_.has(k)) {
                relevantIds.push(id);
            }
        });
        relevantIds.sort();

        // 5. Decide whether the default bucket should appear in results.
        //    Include it only if the app has actually touched the default bucket:
        //    either there are cached entries under it, or a maxCount override
        //    has been set for it (per-bucket or class-wide).
        const hasDefaultCache = (this.cached_.get(defaultKey)?.length ?? 0) > 0;
        const hasDefaultMaxOverride = this.maxCounts_.has(defaultKey)
            || this.maxCounts_.has(`${prefix}${SUFFIX_COMPLIMIT}`);
        const includeDefault = hasDefaultCache || hasDefaultMaxOverride;

        // 6. No reuseIds touched at all — return a single info for the default bucket.
        if (relevantIds.length === 0) {
            return new ReusableInfo(this, defaultKey, classKey, undefined) as IReusableInfo;
        }

        // 7. Array form: only include the default bucket if it has actually been used.
        const result: Array<IReusableInfo> = new Array<IReusableInfo>();
        if (includeDefault) {
            result.push(new ReusableInfo(this, defaultKey, classKey, undefined) as IReusableInfo);
        }
        for (const id of relevantIds) {
            const k = `${prefix}${id}`;
            result.push(new ReusableInfo(this, k, classKey, id) as IReusableInfo);
        }
        return result;
    }

    /**
     * Pre-render `n` instances using the supplied builder. Created instances
     * are pushed into this pool instead of attaching to the UI tree.
     *
     * The Promise resolves on the next idle tick after the synchronous build
     * loop completes. If any build throws, the Promise rejects.
     */
    public preRender(builder: WrappedBuilder<CustomBuilder>, n: int32): Promise<void> {
        let preRenderError: Error | undefined = undefined;
        try {
            GlobalReusePool.beginPreRender(this);
            const ownerComp = this.owner as ExtendableComponent;
            const uiCtx = ownerComp.getUIContext();
            for (let i: int32 = 0; i < n; i++) {
                const node = new BuilderNode<undefined>(uiCtx);
                node.build(builder);
            }
        } catch (e) {
            preRenderError = e as Error;
        } finally {
            GlobalReusePool.endPreRender();
        }

        return new Promise<void>((resolve, reject) => {
            StateUpdateLoop.queueIdleTask(() => {
                if (preRenderError !== undefined) {
                    reject(preRenderError!);
                } else {
                    resolve(undefined);
                }
            });
        });
    }

    // ─────────────────────────────────────────────────────────────────────
    // ReusableInfo callbacks (package-internal — not part of any interface)
    // ─────────────────────────────────────────────────────────────────────

    public __getBucketCount_Internal(key: string): int32 {
        return (this.cached_.get(key)?.length ?? 0) as int32;
    }

    public __getEffectiveMaxCount_Internal(key: string, classKey: string): int32 {
        return this.getEffectiveMaxCount_(key, classKey);
    }

    public __setMaxCount_Internal(classKey: string, reuseId: string | undefined, value: int32): void {
        this.pruneMaxCount_(classKey, reuseId, value);
    }

    // ─────────────────────────────────────────────────────────────────────
    // Internal helpers
    // ─────────────────────────────────────────────────────────────────────

    private buildBucketKey_(classKey: string, reuseId: string | undefined): string {
        if (reuseId === undefined || reuseId === classKey) {
            return `${classKey}__${SUFFIX_DEFAULT}`;
        }
        return `${classKey}__${reuseId}`;
    }

    private getEffectiveMaxCount_(bucketKey: string, classKey: string): int32 {
        const perBucket = this.maxCounts_.get(bucketKey);
        if (perBucket !== undefined) {
            return perBucket!;
        }
        const compWide = this.maxCounts_.get(`${classKey}__${SUFFIX_COMPLIMIT}`);
        if (compWide !== undefined) {
            return compWide!;
        }
        return DEFAULT_MAX_COUNT;
    }

    /**
     * Update the max count for a bucket (or the class-wide default if reuseId
     * is undefined) and prune any excess cached entries.
     */
    private pruneMaxCount_(classKey: string, reuseId: string | undefined, value: int32): void {
        // Negative → 0
        if (value < 0) {
            console.log(`GlobalReuse: maxCount=${value} negative, clamping to 0`);
            value = 0 as int32;
        }
        // Cap at USER_MAX_COUNT_LIMIT
        if (value > USER_MAX_COUNT_LIMIT) {
            console.log(`GlobalReuse: maxCount=${value} exceeds ${USER_MAX_COUNT_LIMIT}, clamping`);
            value = USER_MAX_COUNT_LIMIT;
        }

        const prefix = `${classKey}__`;

        if (reuseId === undefined) {
            // Class-wide default
            this.maxCounts_.set(`${prefix}${SUFFIX_COMPLIMIT}`, value);
            // Snapshot keys first; pruneBucket_ may mutate cached_ via dispose callbacks.
            const keys: Array<string> = new Array<string>();
            this.cached_.forEach((_v: Array<Object>, k: string) => {
                if (k.startsWith(prefix)) {
                    keys.push(k);
                }
            });
            for (const k of keys) {
                this.pruneBucket_(k, value);
            }
        } else {
            const key = this.buildBucketKey_(classKey, reuseId);
            this.maxCounts_.set(key, value);
            this.pruneBucket_(key, value);
        }
    }

    private pruneBucket_(key: string, max: int32): void {
        if (this.pruning_.has(key)) {
            return;
        }
        this.pruning_.add(key);
        try {
            const arr = this.cached_.get(key);
            if (arr === undefined) {
                return;
            }
            while (arr.length > max) {
                const inst = arr.pop();
                if (inst !== undefined) {
                    (inst as Disposable).dispose();
                }
            }
        } finally {
            this.pruning_.delete(key);
        }
    }

    private registerActiveReuseId_(classKey: string, reuseId: string): void {
        let set = this.activeReuseIds_.get(classKey);
        if (set === undefined) {
            set = new Set<string>();
            this.activeReuseIds_.set(classKey, set);
        }
        set.add(reuseId);
    }

    private unregisterActiveReuseId_(classKey: string, reuseId: string): void {
        const set = this.activeReuseIds_.get(classKey);
        if (set !== undefined) {
            set.delete(reuseId);
            if (set.size === 0) {
                this.activeReuseIds_.delete(classKey);
            }
        }
    }
}

export class GlobalReusePoolRegistry {
    private static sharedPools_: Map<string, GlobalReusePool> = new Map<string, GlobalReusePool>();

    static create(
        ownership: ReusePoolOwnership,
        acceptedClasses: Array<string>,
        owner: IVariableOwner
    ): GlobalReusePool {
        if (ownership === ReusePoolOwnership.SHARED) {
            const ownerClassName = Class.of(owner).getName();
            const sorted = acceptedClasses.slice();
            sorted.sort();
            const acceptedKey = sorted.join('_');
            const key = `${ownerClassName}__${acceptedKey}`;
            let pool = GlobalReusePoolRegistry.sharedPools_.get(key);
            if (pool === undefined) {
                pool = new GlobalReusePool(ReusePoolOwnership.SHARED, acceptedClasses, owner);
                pool.__setRegistryKey_Internal(key);
                GlobalReusePoolRegistry.sharedPools_.set(key, pool);
            }
            return pool;
        }
        // PER_INSTANCE pools are not stored in sharedPools_, so they don't need
        // a registry key. GlobalReusePoolRegistry.remove() is a no-op for them.
        return new GlobalReusePool(ReusePoolOwnership.PER_INSTANCE, acceptedClasses, owner);
    }

    static remove(pool: GlobalReusePool): void {
        const foundKey = pool.__getRegistryKey_Internal();
        if (foundKey !== undefined) {
            GlobalReusePoolRegistry.sharedPools_.delete(foundKey);
        }
    }
}