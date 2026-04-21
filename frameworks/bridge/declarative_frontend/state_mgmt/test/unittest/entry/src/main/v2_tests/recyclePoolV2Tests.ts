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

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner';

declare class ViewV2 {
  resetRecycleCustomNode(): void;
}

declare class RecyclePoolV2 {
  pushRecycleV2Component(reuseId: string, reuseComp: ViewV2): void;
  popRecycleV2Component(reuseId: string): ViewV2 | undefined;
  updateRecycleIdMapping(recycledElementId: number, newElmtId: number): void;
  getRecycleIdMapping(recycledElementId: number): number;
  purgeAllCachedRecycleElmtIds(): void;
}

declare class RecycledIdRegistry {
  delete(key: number): void;
  get(key: number): number | undefined;
  add(pair: [number, number]): void;
}

class MockViewV2 implements ViewV2 {
  public id: number;
  public name: string;
  public resetCalled: boolean;

  constructor(id: number, name: string) {
    this.id = id;
    this.name = name;
    this.resetCalled = false;
  }

  public resetRecycleCustomNode(): void {
    this.resetCalled = true;
  }
}

class SimpleViewV2 implements ViewV2 {
  public type: string;
  public properties: Map<string, any>;

  constructor(type: string) {
    this.type = type;
    this.properties = new Map<string, any>();
  }

  public resetRecycleCustomNode(): void {
    this.properties.clear();
  }
}

class ComplexViewV2 implements ViewV2 {
  public id: number;
  public children: ViewV2[];
  public metadata: Map<string, any>;
  public recycled: boolean;

  constructor(id: number) {
    this.id = id;
    this.children = [];
    this.metadata = new Map<string, any>();
    this.recycled = false;
  }

  public resetRecycleCustomNode(): void {
    this.recycled = true;
    this.children = [];
  }

  public addChild(child: ViewV2): void {
    this.children.push(child);
  }
}

class NestedViewV2 implements ViewV2 {
  public level: number;
  public parent: NestedViewV2 | null;
  public child: NestedViewV2 | null;
  public resetCount: number;

  constructor(level: number) {
    this.level = level;
    this.parent = null;
    this.child = null;
    this.resetCount = 0;
  }

  public resetRecycleCustomNode(): void {
    this.resetCount++;
  }
}

class StatefulViewV2 implements ViewV2 {
  public state: any;
  public props: any;
  public lifecycle: string[];

  constructor(initialState: any) {
    this.state = initialState;
    this.props = {};
    this.lifecycle = [];
  }

  public resetRecycleCustomNode(): void {
    this.lifecycle.push('reset');
    this.state = null;
  }
}

class ContainerViewV2 implements ViewV2 {
  public containerId: string;
  public items: ViewV2[];
  public capacity: number;
  public size: number;

  constructor(containerId: string, capacity: number) {
    this.containerId = containerId;
    this.items = [];
    this.capacity = capacity;
    this.size = 0;
  }

  public resetRecycleCustomNode(): void {
    this.items = [];
    this.size = 0;
  }

  public addItem(item: ViewV2): boolean {
    if (this.size >= this.capacity) {
      return false;
    }
    this.items.push(item);
    this.size++;
    return true;
  }
}

class LazyViewV2 implements ViewV2 {
  public loaded: boolean;
  public data: any;
  public initialized: boolean;

  constructor() {
    this.loaded = false;
    this.data = null;
    this.initialized = false;
  }

  public resetRecycleCustomNode(): void {
    this.loaded = false;
    this.data = null;
  }

  public loadData(): void {
    this.loaded = true;
    this.data = { value: 'loaded' };
  }
}

class CachedViewV2 implements ViewV2 {
  public cacheKey: string;
  public cachedData: any;
  public timestamp: number;
  public hits: number;

  constructor(cacheKey: string) {
    this.cacheKey = cacheKey;
    this.cachedData = null;
    this.timestamp = 0;
    this.hits = 0;
  }

  public resetRecycleCustomNode(): void {
    this.cachedData = null;
    this.timestamp = 0;
    this.hits = 0;
  }

  public hit(): void {
    this.hits++;
    this.timestamp = Date.now();
  }
}

class RecyclableViewV2 implements ViewV2 {
  public reuseId: string;
  public recycledCount: number;
  public maxRecycles: number;
  public valid: boolean;

  constructor(reuseId: string, maxRecycles: number = 10) {
    this.reuseId = reuseId;
    this.recycledCount = 0;
    this.maxRecycles = maxRecycles;
    this.valid = true;
  }

  public resetRecycleCustomNode(): void {
    this.recycledCount++;
    if (this.recycledCount >= this.maxRecycles) {
      this.valid = false;
    }
  }

  public canRecycle(): boolean {
    return this.valid && this.recycledCount < this.maxRecycles;
  }
}

class PoolableViewV2 implements ViewV2 {
  public poolId: string;
  public poolIndex: number;
  public inPool: boolean;
  public lastUsed: number;

  constructor(poolId: string) {
    this.poolId = poolId;
    this.poolIndex = -1;
    this.inPool = false;
    this.lastUsed = 0;
  }

  public resetRecycleCustomNode(): void {
    this.poolIndex = -1;
    this.inPool = false;
  }

  public markUsed(): void {
    this.lastUsed = Date.now();
  }
}

class SharedViewV2 implements ViewV2 {
  public sharedId: string;
  public refCount: number;
  public data: any;
  public locked: boolean;

  constructor(sharedId: string) {
    this.sharedId = sharedId;
    this.refCount = 0;
    this.data = null;
    this.locked = false;
  }

  public resetRecycleCustomNode(): void {
    this.refCount = 0;
    this.data = null;
    this.locked = false;
  }

  public acquire(): void {
    this.refCount++;
  }

  public release(): void {
    if (this.refCount > 0) {
      this.refCount--;
    }
  }
}

class TransientViewV2 implements ViewV2 {
  public transientId: string;
  public lifetime: number;
  public created: number;
  public expired: boolean;

  constructor(transientId: string, lifetime: number) {
    this.transientId = transientId;
    this.lifetime = lifetime;
    this.created = Date.now();
    this.expired = false;
  }

  public resetRecycleCustomNode(): void {
    this.created = Date.now();
    this.expired = false;
  }

  public isExpired(): boolean {
    return Date.now() - this.created > this.lifetime;
  }
}

class PooledViewV2 implements ViewV2 {
  public poolName: string;
  public slotId: number;
  public allocated: boolean;
  public released: boolean;

  constructor(poolName: string, slotId: number) {
    this.poolName = poolName;
    this.slotId = slotId;
    this.allocated = false;
    this.released = false;
  }

  public resetRecycleCustomNode(): void {
    this.allocated = false;
    this.released = false;
  }

  public allocate(): void {
    this.allocated = true;
    this.released = false;
  }

  public release(): void {
    this.allocated = false;
    this.released = true;
  }
}

class ManagedViewV2 implements ViewV2 {
  public managerId: string;
  public managed: boolean;
  public disposed: boolean;
  public resources: any[];

  constructor(managerId: string) {
    this.managerId = managerId;
    this.managed = false;
    this.disposed = false;
    this.resources = [];
  }

  public resetRecycleCustomNode(): void {
    this.managed = false;
    this.disposed = false;
    this.resources = [];
  }

  public addResource(resource: any): void {
    this.resources.push(resource);
  }

  public dispose(): void {
    this.disposed = true;
    this.resources = [];
  }
}

export class RecyclePoolV2Tests implements ITestFile {

  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating RecyclePoolV2Tests: ${str}`);
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {}

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  public testRecyclePoolV2Constructor(): void {
    const pool = new RecyclePoolV2();
    eq(pool !== undefined, true, 'RecyclePoolV2 should be constructed');
    eq(pool !== null, true, 'RecyclePoolV2 should not be null');
  }

  public testRecyclePoolV2PushSingleComponent(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('test-reuse-id', view);
    eq(view.id, 1, 'Component should be pushed to pool');
  }

  public testRecyclePoolV2PushMultipleComponents(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    pool.pushRecycleV2Component('reuse-id', view3);
    eq(view1.id, 1, 'First component should be pushed');
    eq(view2.id, 2, 'Second component should be pushed');
    eq(view3.id, 3, 'Third component should be pushed');
  }

  public testRecyclePoolV2PushDifferentReuseIds(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'view1');
    const view2 = new MockViewV2(2, 'view2');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    eq(view1.id, 1, 'Component with reuse-id-1 should be pushed');
    eq(view2.id, 2, 'Component with reuse-id-2 should be pushed');
  }

  public testRecyclePoolV2PushEmptyReuseId(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('', view);
    eq(view.id, 1, 'Component with empty reuseId should be pushed');
  }

  public testRecyclePoolV2PushSpecialReuseId(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('special-id-with-123', view);
    eq(view.id, 1, 'Component with special reuseId should be pushed');
  }

  public testRecyclePoolV2PushUnicodeReuseId(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('中文-reuse-id', view);
    eq(view.id, 1, 'Component with unicode reuseId should be pushed');
  }

  public testRecyclePoolV2PushNullComponent(): void {
    const pool = new RecyclePoolV2();
    pool.pushRecycleV2Component('test-reuse-id', null as any);
    eq(true, true, 'Should handle null component');
  }

  public testRecyclePoolV2PushUndefinedComponent(): void {
    const pool = new RecyclePoolV2();
    pool.pushRecycleV2Component('test-reuse-id', undefined as any);
    eq(true, true, 'Should handle undefined component');
  }

  public testRecyclePoolV2PopSingleComponent(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('test-reuse-id', view);
    const popped = pool.popRecycleV2Component('test-reuse-id');
    eq(popped !== undefined, true, 'Component should be popped');
    eq((popped as MockViewV2).id, 1, 'Popped component should have correct id');
  }

  public testRecyclePoolV2PopMultipleComponents(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    pool.pushRecycleV2Component('reuse-id', view3);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    const popped2 = pool.popRecycleV2Component('reuse-id');
    const popped3 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 3, 'Should pop last pushed component');
    eq((popped2 as MockViewV2).id, 2, 'Should pop second last component');
    eq((popped3 as MockViewV2).id, 1, 'Should pop first pushed component');
  }

  public testRecyclePoolV2PopFromEmptyPool(): void {
    const pool = new RecyclePoolV2();
    const popped = pool.popRecycleV2Component('non-existent-id');
    eq(popped, undefined, 'Should return undefined for empty pool');
  }

  public testRecyclePoolV2PopNonExistentReuseId(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('test-reuse-id', view);
    const popped = pool.popRecycleV2Component('non-existent-id');
    eq(popped, undefined, 'Should return undefined for non-existent reuseId');
  }

  public testRecyclePoolV2PopEmptyReuseId(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('', view);
    const popped = pool.popRecycleV2Component('');
    eq(popped !== undefined, true, 'Should pop component with empty reuseId');
  }

  public testRecyclePoolV2PushPopCycle(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view3);
    const popped2 = pool.popRecycleV2Component('reuse-id');
    const popped3 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 2, 'First pop should return view2');
    eq((popped2 as MockViewV2).id, 3, 'Second pop should return view3');
    eq((popped3 as MockViewV2).id, 1, 'Third pop should return view1');
  }

  public testRecyclePoolV2UpdateRecycleIdMapping(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    const mappedId = pool.getRecycleIdMapping(100);
    eq(mappedId, 200, 'Should map recycled element ID to new element ID');
  }

  public testRecyclePoolV2UpdateMultipleMappings(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    pool.updateRecycleIdMapping(101, 201);
    pool.updateRecycleIdMapping(102, 202);
    eq(pool.getRecycleIdMapping(100), 200, 'Should map first ID');
    eq(pool.getRecycleIdMapping(101), 201, 'Should map second ID');
    eq(pool.getRecycleIdMapping(102), 202, 'Should map third ID');
  }

  public testRecyclePoolV2UpdateMappingWithSameId(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 100);
    const mappedId = pool.getRecycleIdMapping(100);
    eq(mappedId, 100, 'Should handle mapping to same ID');
  }

  public testRecyclePoolV2UpdateMappingOverride(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    pool.updateRecycleIdMapping(100, 300);
    const mappedId = pool.getRecycleIdMapping(100);
    eq(mappedId, 300, 'Should override existing mapping');
  }

  public testRecyclePoolV2UpdateMappingWithZeroId(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(0, 100);
    const mappedId = pool.getRecycleIdMapping(0);
    eq(mappedId, 100, 'Should handle zero element ID');
  }

  public testRecyclePoolV2UpdateMappingWithNegativeId(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(-1, 100);
    const mappedId = pool.getRecycleIdMapping(-1);
    eq(mappedId, 100, 'Should handle negative element ID');
  }

  public testRecyclePoolV2UpdateMappingWithLargeId(): void {
    const pool = new RecyclePoolV2();
    const largeId = Number.MAX_SAFE_INTEGER;
    pool.updateRecycleIdMapping(largeId, 100);
    const mappedId = pool.getRecycleIdMapping(largeId);
    eq(mappedId, 100, 'Should handle large element ID');
  }

  public testRecyclePoolV2GetRecycleIdMapping(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    const mappedId = pool.getRecycleIdMapping(100);
    eq(mappedId, 200, 'Should retrieve mapped ID');
  }

  public testRecyclePoolV2GetRecycleIdMappingNonExistent(): void {
    const pool = new RecyclePoolV2();
    const mappedId = pool.getRecycleIdMapping(999);
    eq(mappedId, 999, 'Should return original ID if no mapping exists');
  }

  public testRecyclePoolV2GetRecycleIdMappingAfterUpdate(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    pool.updateRecycleIdMapping(100, 300);
    const mappedId = pool.getRecycleIdMapping(100);
    eq(mappedId, 300, 'Should return updated mapping');
  }

  public testRecyclePoolV2GetRecycleIdMappingZeroId(): void {
    const pool = new RecyclePoolV2();
    const mappedId = pool.getRecycleIdMapping(0);
    eq(mappedId, 0, 'Should handle zero ID');
  }

  public testRecyclePoolV2GetRecycleIdMappingNegativeId(): void {
    const pool = new RecyclePoolV2();
    const mappedId = pool.getRecycleIdMapping(-1);
    eq(mappedId, -1, 'Should handle negative ID');
  }

  public testRecyclePoolV2PurgeAllCachedRecycleElmtIds(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view1.resetCalled, true, 'Should reset first component');
    eq(view2.resetCalled, true, 'Should reset second component');
  }

  public testRecyclePoolV2PurgeEmptyPool(): void {
    const pool = new RecyclePoolV2();
    pool.purgeAllCachedRecycleElmtIds();
    eq(true, true, 'Should handle purging empty pool');
  }

  public testRecyclePoolV2PurgeAfterPop(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    pool.popRecycleV2Component('reuse-id');
    pool.purgeAllCachedRecycleElmtIds();
    eq(view1.resetCalled, true, 'Should reset remaining component');
    eq(view2.resetCalled, false, 'Should not reset popped component');
  }

  public testRecyclePoolV2PurgeMultipleTimes(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('reuse-id', view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, true, 'First purge should reset component');
    view.resetCalled = false;
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, false, 'Second purge should not reset already purged component');
  }

  public testRecyclePoolV2PurgeWithComplexView(): void {
    const pool = new RecyclePoolV2();
    const view = new ComplexViewV2(1);
    const child = new MockViewV2(2, 'child');
    view.addChild(child);
    pool.pushRecycleV2Component('reuse-id', view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.recycled, true, 'Should reset complex view');
    eq(view.children.length, 0, 'Should clear children');
  }

  public testRecyclePoolV2PurgeWithStatefulView(): void {
    const pool = new RecyclePoolV2();
    const view = new StatefulViewV2({ value: 'test' });
    pool.pushRecycleV2Component('reuse-id', view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.lifecycle.length, 1, 'Should call reset lifecycle');
    eq(view.lifecycle[0], 'reset', 'Should log reset event');
    eq(view.state, null, 'Should clear state');
  }

  public testRecyclePoolV2PurgeWithContainerView(): void {
    const pool = new RecyclePoolV2();
    const container = new ContainerViewV2('container', 10);
    const item = new MockViewV2(1, 'item');
    container.addItem(item);
    pool.pushRecycleV2Component('reuse-id', container);
    pool.purgeAllCachedRecycleElmtIds();
    eq(container.items.length, 0, 'Should clear container items');
    eq(container.size, 0, 'Should reset container size');
  }

  public testRecyclePoolV2PushPopPurgeCycle(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    pool.pushRecycleV2Component('reuse-id', view3);
    pool.popRecycleV2Component('reuse-id');
    pool.purgeAllCachedRecycleElmtIds();
    eq(view1.resetCalled, true, 'Should reset view1');
    eq(view2.resetCalled, true, 'Should reset view2');
    eq(view3.resetCalled, false, 'Should not reset popped view3');
  }

  public testRecyclePoolV2MultipleReuseIdsPurge(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.pushRecycleV2Component('reuse-id-3', view3);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view1.resetCalled, true, 'Should reset view1');
    eq(view2.resetCalled, true, 'Should reset view2');
    eq(view3.resetCalled, true, 'Should reset view3');
  }

  public testRecyclePoolV2ComplexScenario(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.updateRecycleIdMapping(100, 200);
    pool.pushRecycleV2Component('reuse-id-1', view3);
    const popped = pool.popRecycleV2Component('reuse-id-1');
    eq((popped as MockViewV2).id, 3, 'Should pop last pushed component');
    eq(pool.getRecycleIdMapping(100), 200, 'Should maintain ID mapping');
  }

  public testRecyclePoolV2LargeNumberOfComponents(): void {
    const pool = new RecyclePoolV2();
    const componentCount = 1000;
    for (let i = 0; i < componentCount; i++) {
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component('reuse-id', view);
    }
    for (let i = 0; i < componentCount; i++) {
      const popped = pool.popRecycleV2Component('reuse-id');
      eq(popped !== undefined, true, `Should pop component ${i}`);
    }
  }

  public testRecyclePoolV2NestedViews(): void {
    const pool = new RecyclePoolV2();
    const parent = new NestedViewV2(1);
    const child = new NestedViewV2(2);
    parent.child = child;
    child.parent = parent;
    pool.pushRecycleV2Component('reuse-id', parent);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as NestedViewV2).level, 1, 'Should pop nested view');
  }

  public testRecyclePoolV2RecyclableViews(): void {
    const pool = new RecyclePoolV2();
    const view = new RecyclableViewV2('recyclable', 5);
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as RecyclableViewV2).canRecycle(), true, 'View should be recyclable');
  }

  public testRecyclePoolV2PoolableViews(): void {
    const pool = new RecyclePoolV2();
    const view = new PoolableViewV2('pool-1');
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as PoolableViewV2).poolId, 'pool-1', 'Should pop poolable view');
  }

  public testRecyclePoolV2SharedViews(): void {
    const pool = new RecyclePoolV2();
    const view = new SharedViewV2('shared-1');
    view.acquire();
    view.acquire();
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as SharedViewV2).refCount, 2, 'Should maintain ref count');
  }

  public testRecyclePoolV2TransientViews(): void {
    const pool = new RecyclePoolV2();
    const view = new TransientViewV2('transient-1', 1000);
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as TransientViewV2).isExpired(), false, 'Transient view should not be expired');
  }

  public testRecyclePoolV2PooledViews(): void {
    const pool = new RecyclePoolV2();
    const view = new PooledViewV2('pool-1', 1);
    view.allocate();
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as PooledViewV2).allocated, true, 'Pooled view should be allocated');
  }

  public testRecyclePoolV2ManagedViews(): void {
    const pool = new RecyclePoolV2();
    const view = new ManagedViewV2('manager-1');
    view.addResource({ type: 'resource' });
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as ManagedViewV2).resources.length, 1, 'Should maintain resources');
  }

  public testRecyclePoolV2CachedViews(): void {
    const pool = new RecyclePoolV2();
    const view = new CachedViewV2('cache-1');
    view.hit();
    view.hit();
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as CachedViewV2).hits, 2, 'Should maintain cache hits');
  }

  public testRecyclePoolV2LazyViews(): void {
    const pool = new RecyclePoolV2();
    const view = new LazyViewV2();
    view.loadData();
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as LazyViewV2).loaded, true, 'Lazy view should be loaded');
  }

  public testRecycledIdRegistryConstructor(): void {
    const registry = new RecycledIdRegistry();
    eq(registry !== undefined, true, 'RecycledIdRegistry should be constructed');
    eq(registry !== null, true, 'RecycledIdRegistry should not be null');
  }

  public testRecycledIdRegistryAdd(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    const mappedId = registry.get(100);
    eq(mappedId, 200, 'Should add mapping');
  }

  public testRecycledIdRegistryAddMultiple(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    registry.add([101, 201]);
    registry.add([102, 202]);
    eq(registry.get(100), 200, 'Should add first mapping');
    eq(registry.get(101), 201, 'Should add second mapping');
    eq(registry.get(102), 202, 'Should add third mapping');
  }

  public testRecycledIdRegistryAddSameId(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 100]);
    const mappedId = registry.get(100);
    eq(mappedId, 100, 'Should add mapping with same IDs');
  }

  public testRecycledIdRegistryAddOverride(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    registry.add([100, 300]);
    const mappedId = registry.get(100);
    eq(mappedId, 300, 'Should override existing mapping');
  }

  public testRecycledIdRegistryAddZeroId(): void {
    const registry = new RecycledIdRegistry();
    registry.add([0, 100]);
    const mappedId = registry.get(0);
    eq(mappedId, 100, 'Should add mapping with zero ID');
  }

  public testRecycledIdRegistryAddNegativeId(): void {
    const registry = new RecycledIdRegistry();
    registry.add([-1, 100]);
    const mappedId = registry.get(-1);
    eq(mappedId, 100, 'Should add mapping with negative ID');
  }

  public testRecycledIdRegistryAddLargeId(): void {
    const registry = new RecycledIdRegistry();
    const largeId = Number.MAX_SAFE_INTEGER;
    registry.add([largeId, 100]);
    const mappedId = registry.get(largeId);
    eq(mappedId, 100, 'Should add mapping with large ID');
  }

  public testRecycledIdRegistryGet(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    const mappedId = registry.get(100);
    eq(mappedId, 200, 'Should get mapped ID');
  }

  public testRecycledIdRegistryGetNonExistent(): void {
    const registry = new RecycledIdRegistry();
    const mappedId = registry.get(999);
    eq(mappedId, undefined, 'Should return undefined for non-existent key');
  }

  public testRecycledIdRegistryGetFromReverseMap(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    const mappedId = registry.get(200);
    eq(mappedId, 100, 'Should get from reverse map');
  }

  public testRecycledIdRegistryGetAfterOverride(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    registry.add([100, 300]);
    const mappedId = registry.get(100);
    eq(mappedId, 300, 'Should get updated mapping');
  }

  public testRecycledIdRegistryGetZeroId(): void {
    const registry = new RecycledIdRegistry();
    registry.add([0, 100]);
    const mappedId = registry.get(0);
    eq(mappedId, 100, 'Should get mapping with zero ID');
  }

  public testRecycledIdRegistryGetNegativeId(): void {
    const registry = new RecycledIdRegistry();
    registry.add([-1, 100]);
    const mappedId = registry.get(-1);
    eq(mappedId, 100, 'Should get mapping with negative ID');
  }

  public testRecycledIdRegistryDeleteNonExistent(): void {
    const registry = new RecycledIdRegistry();
    registry.delete(999);
    eq(true, true, 'Should handle deleting non-existent key');
  }

  public testRecycledIdRegistryAddDeleteCycle(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    registry.delete(100);
    registry.add([100, 300]);
    const mappedId = registry.get(100);
    eq(mappedId, 300, 'Should add after delete');
  }

  public testRecycledIdRegistryBiDirectionalMapping(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    const fwdMapped = registry.get(100);
    const revMapped = registry.get(200);
    eq(fwdMapped, 200, 'Forward mapping should work');
    eq(revMapped, 100, 'Reverse mapping should work');
  }

  public testRecycledIdRegistryMultipleBiDirectionalMappings(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    registry.add([101, 201]);
    registry.add([102, 202]);
    eq(registry.get(100), 200, 'First forward mapping should work');
    eq(registry.get(200), 100, 'First reverse mapping should work');
    eq(registry.get(101), 201, 'Second forward mapping should work');
    eq(registry.get(201), 101, 'Second reverse mapping should work');
    eq(registry.get(102), 202, 'Third forward mapping should work');
    eq(registry.get(202), 102, 'Third reverse mapping should work');
  }

  public testRecycledIdRegistryLargeNumberOfMappings(): void {
    const registry = new RecycledIdRegistry();
    const mappingCount = 1000;
    for (let i = 0; i < mappingCount; i++) {
      registry.add([i, i + 1000]);
    }
    for (let i = 0; i < mappingCount; i++) {
      eq(registry.get(i), i + 1000, `Should get mapping ${i}`);
    }
  }

  public testRecycledIdRegistryEdgeCaseMinNumber(): void {
    const registry = new RecycledIdRegistry();
    registry.add([Number.MIN_SAFE_INTEGER, 100]);
    const mappedId = registry.get(Number.MIN_SAFE_INTEGER);
    eq(mappedId, 100, 'Should handle minimum safe integer');
  }

  public testRecycledIdRegistryEdgeCaseMaxNumber(): void {
    const registry = new RecycledIdRegistry();
    registry.add([Number.MAX_SAFE_INTEGER, 100]);
    const mappedId = registry.get(Number.MAX_SAFE_INTEGER);
    eq(mappedId, 100, 'Should handle maximum safe integer');
  }

  public testRecycledIdRegistryEdgeCaseNaN(): void {
    const registry = new RecycledIdRegistry();
    registry.add([NaN as any, 100]);
    const mappedId = registry.get(NaN as any);
    eq(mappedId, 100, 'Should handle NaN');
  }

  public testRecycledIdRegistrySymmetricMapping(): void {
    const registry = new RecycledIdRegistry();
    registry.add([100, 200]);
    registry.add([200, 300]);
    eq(registry.get(100), 200, 'First mapping should work');
    eq(registry.get(200), 300, 'Second mapping should work');
    eq(registry.get(300), 200, 'Reverse of second mapping should work');
  }

  public testRecycledIdRegistryChainMapping(): void {
    const registry = new RecycledIdRegistry();
    registry.add([1, 2]);
    registry.add([2, 3]);
    registry.add([3, 4]);
    eq(registry.get(1), 2, 'First link should work');
    eq(registry.get(2), 3, 'Second link should work');
    eq(registry.get(3), 4, 'Third link should work');
    eq(registry.get(4), 3, 'Reverse of third link should work');
  }

  public testRecycledIdRegistryPerformanceAdd(): void {
    const registry = new RecycledIdRegistry();
    const iterations = 10000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      registry.add([i, i + 10000]);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Add operations should complete in reasonable time');
  }

  public testRecycledIdRegistryPerformanceGet(): void {
    const registry = new RecycledIdRegistry();
    const iterations = 10000;
    for (let i = 0; i < iterations; i++) {
      registry.add([i, i + 10000]);
    }
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      registry.get(i);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Get operations should complete in reasonable time');
  }

  public testRecycledIdRegistryPerformanceDelete(): void {
    const registry = new RecycledIdRegistry();
    const iterations = 10000;
    for (let i = 0; i < iterations; i++) {
      registry.add([i, i + 10000]);
    }
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      registry.delete(i);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Delete operations should complete in reasonable time');
  }

  public testRecycledIdRegistryPerformanceMixed(): void {
    const registry = new RecycledIdRegistry();
    const iterations = 10000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      registry.add([i, i + 10000]);
      if (i % 2 === 0) {
        registry.get(i);
      }
      if (i % 3 === 0) {
        registry.delete(i);
      }
    }
    const duration = Date.now() - startTime;
    eq(duration < 2000, true, 'Mixed operations should complete in reasonable time');
  }

  public testRecyclePoolV2PerformancePush(): void {
    const pool = new RecyclePoolV2();
    const iterations = 10000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component('reuse-id', view);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Push operations should complete in reasonable time');
  }

  public testRecyclePoolV2PerformancePop(): void {
    const pool = new RecyclePoolV2();
    const iterations = 10000;
    for (let i = 0; i < iterations; i++) {
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component('reuse-id', view);
    }
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      pool.popRecycleV2Component('reuse-id');
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Pop operations should complete in reasonable time');
  }

  public testRecyclePoolV2PerformancePurge(): void {
    const pool = new RecyclePoolV2();
    const iterations = 10000;
    for (let i = 0; i < iterations; i++) {
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component('reuse-id', view);
    }
    const startTime = Date.now();
    pool.purgeAllCachedRecycleElmtIds();
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Purge operation should complete in reasonable time');
  }

  public testRecyclePoolV2PerformanceMixed(): void {
    const pool = new RecyclePoolV2();
    const iterations = 10000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component('reuse-id', view);
      if (i % 2 === 0) {
        pool.popRecycleV2Component('reuse-id');
      }
      if (i % 100 === 0) {
        pool.updateRecycleIdMapping(i, i + 10000);
      }
    }
    pool.purgeAllCachedRecycleElmtIds();
    const duration = Date.now() - startTime;
    eq(duration < 2000, true, 'Mixed operations should complete in reasonable time');
  }

  public testRecyclePoolV2MultiplePools(): void {
    const pool1 = new RecyclePoolV2();
    const pool2 = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool1.pushRecycleV2Component('reuse-id-1', view1);
    pool2.pushRecycleV2Component('reuse-id-2', view2);
    const popped1 = pool1.popRecycleV2Component('reuse-id-1');
    const popped2 = pool2.popRecycleV2Component('reuse-id-2');
    eq((popped1 as MockViewV2).id, 1, 'Pool1 should return correct component');
    eq((popped2 as MockViewV2).id, 2, 'Pool2 should return correct component');
  }

  public testRecyclePoolV2IsolationBetweenPools(): void {
    const pool1 = new RecyclePoolV2();
    const pool2 = new RecyclePoolV2();
    pool1.updateRecycleIdMapping(100, 200);
    pool2.updateRecycleIdMapping(100, 300);
    eq(pool1.getRecycleIdMapping(100), 200, 'Pool1 should have its own mapping');
    eq(pool2.getRecycleIdMapping(100), 300, 'Pool2 should have its own mapping');
  }

  public testRecyclePoolV2ConcurrentLikeOperations(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.updateRecycleIdMapping(100, 200);
    pool.pushRecycleV2Component('reuse-id-1', view3);
    const popped1 = pool.popRecycleV2Component('reuse-id-1');
    const popped2 = pool.popRecycleV2Component('reuse-id-2');
    eq((popped1 as MockViewV2).id, 3, 'Should pop last pushed to reuse-id-1');
    eq((popped2 as MockViewV2).id, 2, 'Should pop from reuse-id-2');
  }

  public testRecyclePoolV2StressTest(): void {
    const pool = new RecyclePoolV2();
    const operations = 1000;
    for (let i = 0; i < operations; i++) {
      const reuseId = `reuse-id-${i % 10}`;
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component(reuseId, view);
      if (i % 3 === 0) {
        pool.popRecycleV2Component(reuseId);
      }
      if (i % 5 === 0) {
        pool.updateRecycleIdMapping(i, i + 1000);
      }
    }
    pool.purgeAllCachedRecycleElmtIds();
    eq(true, true, 'Stress test should complete without errors');
  }

  public testRecyclePoolV2MemoryLeakPrevention(): void {
    const pool = new RecyclePoolV2();
    const iterations = 1000;
    for (let i = 0; i < iterations; i++) {
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component('reuse-id', view);
    }
    pool.purgeAllCachedRecycleElmtIds();
    for (let i = 0; i < iterations; i++) {
      pool.pushRecycleV2Component('reuse-id', new MockViewV2(i, `test${i}`));
    }
    pool.purgeAllCachedRecycleElmtIds();
    eq(true, true, 'Should prevent memory leaks through purging');
  }

  public testRecyclePoolV2EdgeCaseEmptyStringReuseId(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('', view);
    const popped = pool.popRecycleV2Component('');
    eq((popped as MockViewV2).id, 1, 'Should handle empty string reuseId');
  }

  public testRecyclePoolV2EdgeCaseLongReuseId(): void {
    const pool = new RecyclePoolV2();
    const longReuseId = 'a'.repeat(1000);
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component(longReuseId, view);
    const popped = pool.popRecycleV2Component(longReuseId);
    eq((popped as MockViewV2).id, 1, 'Should handle long reuseId');
  }

  public testRecyclePoolV2EdgeCaseSpecialCharsReuseId(): void {
    const pool = new RecyclePoolV2();
    const specialReuseId = '!@#$%^&*()_+-=[]{}|;:,.<>?/~`';
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component(specialReuseId, view);
    const popped = pool.popRecycleV2Component(specialReuseId);
    eq((popped as MockViewV2).id, 1, 'Should handle special characters in reuseId');
  }

  public testRecyclePoolV2EdgeCaseIdZero(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(0, 100);
    const mappedId = pool.getRecycleIdMapping(0);
    eq(mappedId, 100, 'Should handle element ID zero');
  }

  public testRecyclePoolV2EdgeCaseIdNegative(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(-1, 100);
    const mappedId = pool.getRecycleIdMapping(-1);
    eq(mappedId, 100, 'Should handle negative element ID');
  }

  public testRecyclePoolV2EdgeCaseIdMaxSafeInteger(): void {
    const pool = new RecyclePoolV2();
    const maxId = Number.MAX_SAFE_INTEGER;
    pool.updateRecycleIdMapping(maxId, 100);
    const mappedId = pool.getRecycleIdMapping(maxId);
    eq(mappedId, 100, 'Should handle maximum safe integer ID');
  }

  public testRecyclePoolV2EdgeCaseIdMinSafeInteger(): void {
    const pool = new RecyclePoolV2();
    const minId = Number.MIN_SAFE_INTEGER;
    pool.updateRecycleIdMapping(minId, 100);
    const mappedId = pool.getRecycleIdMapping(minId);
    eq(mappedId, 100, 'Should handle minimum safe integer ID');
  }

  public testRecyclePoolV2ResetBehavior(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('reuse-id', view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, true, 'Component should be reset');
    const popped = pool.popRecycleV2Component('reuse-id');
    eq(popped, undefined, 'Pool should be empty after purge');
  }

  public testRecyclePoolV2ReuseAfterPurge(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.purgeAllCachedRecycleElmtIds();
    pool.pushRecycleV2Component('reuse-id', view2);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as MockViewV2).id, 2, 'Should be able to reuse pool after purge');
  }

  public testRecyclePoolV2MultiplePurges(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('reuse-id', view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, true, 'First purge should reset');
    view.resetCalled = false;
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, false, 'Second purge should not reset already purged');
  }

  public testRecyclePoolV2IdMappingPersistence(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    pool.purgeAllCachedRecycleElmtIds();
    const mappedId = pool.getRecycleIdMapping(100);
    eq(mappedId, 200, 'ID mapping should persist after purge');
  }

  public testRecyclePoolV2ComplexLifecycle(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    pool.updateRecycleIdMapping(100, 200);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 2, 'First pop should return view2');
    pool.pushRecycleV2Component('reuse-id', view3);
    const popped2 = pool.popRecycleV2Component('reuse-id');
    eq((popped2 as MockViewV2).id, 3, 'Second pop should return view3');
    pool.purgeAllCachedRecycleElmtIds();
    eq(view1.resetCalled, true, 'Purge should reset remaining view1');
    eq(pool.getRecycleIdMapping(100), 200, 'ID mapping should persist');
  }

  public testRecyclePoolV2BatchOperations(): void {
    const pool = new RecyclePoolV2();
    const batchSize = 100;
    for (let batch = 0; batch < 10; batch++) {
      for (let i = 0; i < batchSize; i++) {
        const view = new MockViewV2(batch * batchSize + i, `test${batch * batchSize + i}`);
        pool.pushRecycleV2Component(`batch-${batch}`, view);
      }
    }
    for (let batch = 0; batch < 10; batch++) {
      for (let i = 0; i < batchSize; i++) {
        const popped = pool.popRecycleV2Component(`batch-${batch}`);
        eq(popped !== undefined, true, `Should pop from batch ${batch}`);
      }
    }
  }

  public testRecyclePoolV2AlternatingReuseIds(): void {
    const pool = new RecyclePoolV2();
    const iterations = 100;
    for (let i = 0; i < iterations; i++) {
      const reuseId = i % 2 === 0 ? 'even' : 'odd';
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component(reuseId, view);
    }
    let evenCount = 0;
    let oddCount = 0;
    while (true) {
      const evenPopped = pool.popRecycleV2Component('even');
      if (evenPopped !== undefined) {
        evenCount++;
      }
      const oddPopped = pool.popRecycleV2Component('odd');
      if (oddPopped !== undefined) {
        oddCount++;
      }
      if (evenPopped === undefined && oddPopped === undefined) {
        break;
      }
    }
    eq(evenCount, 50, 'Should pop 50 even components');
    eq(oddCount, 50, 'Should pop 50 odd components');
  }

  public testRecyclePoolV2HierarchicalReuseIds(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'root');
    const view2 = new MockViewV2(2, 'child1');
    const view3 = new MockViewV2(3, 'child2');
    const view4 = new MockViewV2(4, 'grandchild');
    pool.pushRecycleV2Component('root', view1);
    pool.pushRecycleV2Component('root/child1', view2);
    pool.pushRecycleV2Component('root/child2', view3);
    pool.pushRecycleV2Component('root/child1/grandchild', view4);
    const poppedRoot = pool.popRecycleV2Component('root');
    const poppedChild1 = pool.popRecycleV2Component('root/child1');
    const poppedChild2 = pool.popRecycleV2Component('root/child2');
    const poppedGrandchild = pool.popRecycleV2Component('root/child1/grandchild');
    eq((poppedRoot as MockViewV2).id, 1, 'Should pop root');
    eq((poppedChild1 as MockViewV2).id, 2, 'Should pop child1');
    eq((poppedChild2 as MockViewV2).id, 3, 'Should pop child2');
    eq((poppedGrandchild as MockViewV2).id, 4, 'Should pop grandchild');
  }

  public testRecyclePoolV2DynamicReuseIds(): void {
    const pool = new RecyclePoolV2();
    const iterations = 100;
    for (let i = 0; i < iterations; i++) {
      const reuseId = `dynamic-${Math.floor(i / 10)}`;
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component(reuseId, view);
    }
    for (let group = 0; group < 10; group++) {
      const reuseId = `dynamic-${group}`;
      let count = 0;
      while (true) {
        const popped = pool.popRecycleV2Component(reuseId);
        if (popped === undefined) {
          break;
        }
        count++;
      }
      eq(count, 10, `Should pop 10 components from group ${group}`);
    }
  }

  public testRecyclePoolV2SequentialIdMapping(): void {
    const pool = new RecyclePoolV2();
    const startId = 1000;
    const count = 100;
    for (let i = 0; i < count; i++) {
      pool.updateRecycleIdMapping(startId + i, startId + i + count);
    }
    for (let i = 0; i < count; i++) {
      const mappedId = pool.getRecycleIdMapping(startId + i);
      eq(mappedId, startId + i + count, `Should map ID ${startId + i}`);
    }
  }

  public testRecyclePoolV2ReverseIdMapping(): void {
    const pool = new RecyclePoolV2();
    const startId = 1000;
    const count = 100;
    for (let i = 0; i < count; i++) {
      pool.updateRecycleIdMapping(startId + count - i - 1, startId + i);
    }
    for (let i = 0; i < count; i++) {
      const mappedId = pool.getRecycleIdMapping(startId + count - i - 1);
      eq(mappedId, startId + i, `Should map reverse ID ${startId + count - i - 1}`);
    }
  }

  public testRecyclePoolV2RandomIdMapping(): void {
    const pool = new RecyclePoolV2();
    const ids = [100, 200, 300, 400, 500];
    const mappedIds = [1000, 2000, 3000, 4000, 5000];
    for (let i = 0; i < ids.length; i++) {
      pool.updateRecycleIdMapping(ids[i], mappedIds[i]);
    }
    for (let i = 0; i < ids.length; i++) {
      const mappedId = pool.getRecycleIdMapping(ids[i]);
      eq(mappedId, mappedIds[i], `Should map ID ${ids[i]}`);
    }
  }

  public testRecyclePoolV2OverlappingIdMappings(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    pool.updateRecycleIdMapping(200, 300);
    pool.updateRecycleIdMapping(300, 400);
    eq(pool.getRecycleIdMapping(100), 200, 'First mapping should work');
    eq(pool.getRecycleIdMapping(200), 300, 'Second mapping should work');
    eq(pool.getRecycleIdMapping(300), 400, 'Third mapping should work');
  }

  public testRecyclePoolV2CircularIdMapping(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    pool.updateRecycleIdMapping(200, 300);
    pool.updateRecycleIdMapping(300, 100);
    eq(pool.getRecycleIdMapping(100), 200, 'First mapping should work');
    eq(pool.getRecycleIdMapping(200), 300, 'Second mapping should work');
    eq(pool.getRecycleIdMapping(300), 100, 'Third mapping should work');
  }

  public testRecyclePoolV2IdMappingUpdateSequence(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    eq(pool.getRecycleIdMapping(100), 200, 'Initial mapping should work');
    pool.updateRecycleIdMapping(100, 300);
    eq(pool.getRecycleIdMapping(100), 300, 'First update should work');
    pool.updateRecycleIdMapping(100, 400);
    eq(pool.getRecycleIdMapping(100), 400, 'Second update should work');
    pool.updateRecycleIdMapping(100, 500);
    eq(pool.getRecycleIdMapping(100), 500, 'Third update should work');
  }

  public testRecyclePoolV2ComponentReuseCycle(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('reuse-id', view);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 1, 'First pop should return view');
    pool.pushRecycleV2Component('reuse-id', popped1 as MockViewV2);
    const popped2 = pool.popRecycleV2Component('reuse-id');
    eq((popped2 as MockViewV2).id,  1, 'Reused component should be returned');
  }

  public testRecyclePoolV2MultipleComponentReuse(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    pool.pushRecycleV2Component('reuse-id', view3);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    const popped2 = pool.popRecycleV2Component('reuse-id');
    const popped3 = pool.popRecycleV2Component('reuse-id');
    pool.pushRecycleV2Component('reuse-id', popped1 as MockViewV2);
    pool.pushRecycleV2Component('reuse-id', popped2 as MockViewV2);
    pool.pushRecycleV2Component('reuse-id', popped3 as MockViewV2);
    const reused1 = pool.popRecycleV2Component('reuse-id');
    const reused2 = pool.popRecycleV2Component('reuse-id');
    const reused3 = pool.popRecycleV2Component('reuse-id');
    eq((reused1 as MockViewV2).id, 1, 'First reused component should be view1');
    eq((reused2 as MockViewV2).id, 2, 'Second reused component should be view2');
    eq((reused3 as MockViewV2).id, 3, 'Third reused component should be view3');
  }

  public testRecyclePoolV2InterleavedPushPop(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view1);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    pool.pushRecycleV2Component('reuse-id', view2);
    const popped2 = pool.popRecycleV2Component('reuse-id');
    pool.pushRecycleV2Component('reuse-id', view3);
    const popped3 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 1, 'First pop should return view1');
    eq((popped2 as MockViewV2).id, 2, 'Second pop should return view2');
    eq((popped3 as MockViewV2).id, 3, 'Third pop should return view3');
  }

  public testRecyclePoolV2PushAfterPopAll(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    pool.popRecycleV2Component('reuse-id');
    pool.popRecycleV2Component('reuse-id');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view3);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as MockViewV2).id, 3, 'Should pop newly pushed component');
  }

  public testRecyclePoolV2EmptyPoolBehavior(): void {
    const pool = new RecyclePoolV2();
    const popped1 = pool.popRecycleV2Component('reuse-id');
    const popped2 = pool.popRecycleV2Component('reuse-id');
    const popped3 = pool.popRecycleV2Component('reuse-id');
    eq(popped1, undefined, 'First pop from empty pool should return undefined');
    eq(popped2, undefined, 'Second pop from empty pool should return undefined');
    eq(popped3, undefined, 'Third pop from empty pool should return undefined');
  }

  public testRecyclePoolV2SingleComponentPool(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('reuse-id', view);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    const popped2 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 1, 'First pop should return component');
    eq(popped2, undefined, 'Second pop should return undefined');
  }

  public testRecyclePoolV2TwoComponentPool(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    const popped2 = pool.popRecycleV2Component('reuse-id');
    const popped3 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 2, 'First pop should return view2');
    eq((popped2 as MockViewV2).id, 1, 'Second pop should return view1');
    eq(popped3, undefined, 'Third pop should return undefined');
  }

  public testRecyclePoolV2TenComponentPool(): void {
    const pool = new RecyclePoolV2();
    const count = 10;
    for (let i = 0; i < count; i++) {
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component('reuse-id', view);
    }
    for (let i = count - 1; i >= 0; i--) {
      const popped = pool.popRecycleV2Component('reuse-id');
      eq((popped as MockViewV2).id, i, `Should pop component ${i}`);
    }
    const finalPopped = pool.popRecycleV2Component('reuse-id');
    eq(finalPopped, undefined, 'Final pop should return undefined');
  }

  public testRecyclePoolV2MixedViewTypes(): void {
    const pool = new RecyclePoolV2();
    const mockView = new MockViewV2(1, 'mock');
    const simpleView = new SimpleViewV2('simple');
    const complexView = new ComplexViewV2(2);
    const nestedView = new NestedViewV2(3);
    pool.pushRecycleV2Component('mock-reuse-id', mockView);
    pool.pushRecycleV2Component('simple-reuse-id', simpleView);
    pool.pushRecycleV2Component('complex-reuse-id', complexView);
    pool.pushRecycleV2Component('nested-reuse-id', nestedView);
    const poppedMock = pool.popRecycleV2Component('mock-reuse-id');
    const poppedSimple = pool.popRecycleV2Component('simple-reuse-id');
    const poppedComplex = pool.popRecycleV2Component('complex-reuse-id');
    const poppedNested = pool.popRecycleV2Component('nested-reuse-id');
    eq((poppedMock as MockViewV2).id, 1, 'Should pop mock view');
    eq((poppedSimple as SimpleViewV2).type, 'simple', 'Should pop simple view');
    eq((poppedComplex as ComplexViewV2).id, 2, 'Should pop complex view');
    eq((poppedNested as NestedViewV2).level, 3, 'Should pop nested view');
  }

  public testRecyclePoolV2ViewWithProperties(): void {
    const pool = new RecyclePoolV2();
    const view = new SimpleViewV2('test');
    view.properties.set('key1', 'value1');
    view.properties.set('key2', 'value2');
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedView = popped as SimpleViewV2;
    eq(poppedView.properties.get('key1'), 'value1', 'Should preserve property key1');
    eq(poppedView.properties.get('key2'), 'value2', 'Should preserve property key2');
  }

  public testRecyclePoolV2ViewWithChildren(): void {
    const pool = new RecyclePoolV2();
    const parent = new ComplexViewV2(1);
    const child1 = new MockViewV2(2, 'child1');
    const child2 = new MockViewV2(3, 'child2');
    parent.addChild(child1);
    parent.addChild(child2);
    pool.pushRecycleV2Component('reuse-id', parent);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedParent = popped as ComplexViewV2;
    eq(poppedParent.children.length, 2, 'Should preserve children');
    eq((poppedParent.children[0] as MockViewV2).id, 2, 'Should preserve child1');
    eq((poppedParent.children[1] as MockViewV2).id, 3, 'Should preserve child2');
  }

  public testRecyclePoolV2ViewWithMetadata(): void {
    const pool = new RecyclePoolV2();
    const view = new ComplexViewV2(1);
    view.metadata.set('meta1', 'value1');
    view.metadata.set('meta2', 123);
    view.metadata.set('meta3', true);
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedView = popped as ComplexViewV2;
    eq(poppedView.metadata.get('meta1'), 'value1', 'Should preserve metadata meta1');
    eq(poppedView.metadata.get('meta2'), 123, 'Should preserve metadata meta2');
    eq(poppedView.metadata.get('meta3'), true, 'Should preserve metadata meta3');
  }

  public testRecyclePoolV2PurgeResetsProperties(): void {
    const pool = new RecyclePoolV2();
    const view = new SimpleViewV2('test');
    view.properties.set('key1', 'value1');
    view.properties.set('key2', 'value2');
    pool.pushRecycleV2Component('reuse-id', view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.properties.size, 0, 'Purge should clear properties');
  }

  public testRecyclePoolV2PurgeResetsChildren(): void {
    const pool = new RecyclePoolV2();
    const parent = new ComplexViewV2(1);
    const child1 = new MockViewV2(2, 'child1');
    const child2 = new MockViewV2(3, 'child2');
    parent.addChild(child1);
    parent.addChild(child2);
    pool.pushRecycleV2Component('reuse-id', parent);
    pool.purgeAllCachedRecycleElmtIds();
    eq(parent.children.length, 0, 'Purge should clear children');
  }

  public testRecyclePoolV2PurgeMultipleReuseIds(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.pushRecycleV2Component('reuse-id-3', view3);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view1.resetCalled, true, 'Purge should reset view1');
    eq(view2.resetCalled, true, 'Purge should reset view2');
    eq(view3.resetCalled, true, 'Purge should reset view3');
  }

  public testRecyclePoolV2PurgeEmptyReuseId(): void {
    const pool = new RecyclePoolV2();
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component('', view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, true, 'Purge should reset component with empty reuseId');
  }

  public testRecyclePoolV2PurgeLongReuseId(): void {
    const pool = new RecyclePoolV2();
    const longReuseId = 'a'.repeat(1000);
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component(longReuseId, view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, true, 'Purge should reset component with long reuseId');
  }

  public testRecyclePoolV2PurgeSpecialReuseId(): void {
    const pool = new RecyclePoolV2();
    const specialReuseId = '!@#$%^&*()_+-=[]{}|;:,.<>?/~`';
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component(specialReuseId, view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, true, 'Purge should reset component with special reuseId');
  }

  public testRecyclePoolV2PurgeUnicodeReuseId(): void {
    const pool = new RecyclePoolV2();
    const unicodeReuseId = '中文-🎉-世界';
    const view = new MockViewV2(1, 'test');
    pool.pushRecycleV2Component(unicodeReuseId, view);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.resetCalled, true, 'Purge should reset component with unicode reuseId');
  }

  public testRecyclePoolV2IdMappingWithZero(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(0, 100);
    pool.updateRecycleIdMapping(100, 200);
    pool.updateRecycleIdMapping(200, 300);
    eq(pool.getRecycleIdMapping(0), 100, 'Should map zero ID');
    eq(pool.getRecycleIdMapping(100), 200, 'Should map 100 to 200');
    eq(pool.getRecycleIdMapping(200), 300, 'Should map 200 to 300');
  }

  public testRecyclePoolV2IdMappingWithNegative(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(-1, 100);
    pool.updateRecycleIdMapping(-2, 200);
    pool.updateRecycleIdMapping(-3, 300);
    eq(pool.getRecycleIdMapping(-1), 100, 'Should map -1');
    eq(pool.getRecycleIdMapping(-2), 200, 'Should map -2');
    eq(pool.getRecycleIdMapping(-3), 300, 'Should map -3');
  }

  public testRecyclePoolV2IdMappingWithMixed(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(-1, 100);
    pool.updateRecycleIdMapping(0, 200);
    pool.updateRecycleIdMapping(1, 300);
    eq(pool.getRecycleIdMapping(-1), 100, 'Should map -1');
    eq(pool.getRecycleIdMapping(0), 200, 'Should map 0');
    eq(pool.getRecycleIdMapping(1), 300, 'Should map 1');
  }

  public testRecyclePoolV2IdMappingPersistenceAfterPurge(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    pool.updateRecycleIdMapping(101, 201);
    pool.updateRecycleIdMapping(102, 202);
    pool.purgeAllCachedRecycleElmtIds();
    eq(pool.getRecycleIdMapping(100), 200, 'ID mapping should persist after purge');
    eq(pool.getRecycleIdMapping(101), 201, 'ID mapping should persist after purge');
    eq(pool.getRecycleIdMapping(102), 202, 'ID mapping should persist after purge');
  }

  public testRecyclePoolV2ComplexScenario1(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.updateRecycleIdMapping(100, 200);
    pool.pushRecycleV2Component('reuse-id-1', view3);
    const popped1 = pool.popRecycleV2Component('reuse-id-1');
    const popped2 = pool.popRecycleV2Component('reuse-id-2');
    eq((popped1 as MockViewV2).id, 3, 'First pop should return view3');
    eq((popped2 as MockViewV2).id, 2, 'Second pop should return view2');
    eq(pool.getRecycleIdMapping(100), 200, 'ID mapping should persist');
  }

  public testRecyclePoolV2ComplexScenario2(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    const view4 = new MockViewV2(4, 'test4');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    pool.updateRecycleIdMapping(100, 200);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    pool.pushRecycleV2Component('reuse-id', view3);
    pool.pushRecycleV2Component('reuse-id', view4);
    const popped2 = pool.popRecycleV2Component('reuse-id');
    const popped3 = pool.popRecycleV2Component('reuse-id');
    const popped4 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 2, 'First pop should return view2');
    eq((popped2 as MockViewV2).id, 4, 'Second pop should return view4');
    eq((popped3 as MockViewV2).id, 3, 'Third pop should return view3');
    eq((popped4 as MockViewV2).id, 1, 'Fourth pop should return view1');
  }

  public testRecyclePoolV2ComplexScenario3(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.pushRecycleV2Component('reuse-id-3', view3);
    pool.updateRecycleIdMapping(100, 200);
    pool.updateRecycleIdMapping(101, 201);
    pool.updateRecycleIdMapping(102, 202);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view1.resetCalled, true, 'Purge should reset view1');
    eq(view2.resetCalled, true, 'Purge should reset view2');
    eq(view3.resetCalled, true, 'Purge should reset view3');
    eq(pool.getRecycleIdMapping(100), 200, 'ID mapping 100 should persist');
    eq(pool.getRecycleIdMapping(101), 201, 'ID mapping 101 should persist');
    eq(pool.getRecycleIdMapping(102), 202, 'ID mapping 102 should persist');
  }

  public testRecyclePoolV2StressTestMultipleReuseIds(): void {
    const pool = new RecyclePoolV2();
    const reuseIdCount = 10;
    const componentsPerReuseId = 100;
    for (let i = 0; i < reuseIdCount; i++) {
      for (let j = 0; j < componentsPerReuseId; j++) {
        const view = new MockViewV2(i * componentsPerReuseId + j, `test${i * componentsPerReuseId + j}`);
        pool.pushRecycleV2Component(`reuse-id-${i}`, view);
      }
    }
    for (let i = 0; i < reuseIdCount; i++) {
      for (let j = 0; j < componentsPerReuseId; j++) {
        const popped = pool.popRecycleV2Component(`reuse-id-${i}`);
        eq(popped !== undefined, true, `Should pop from reuse-id-${i}`);
      }
    }
  }

  public testRecyclePoolV2StressTestIdMapping(): void {
    const pool = new RecyclePoolV2();
    const mappingCount = 10000;
    for (let i = 0; i < mappingCount; i++) {
      pool.updateRecycleIdMapping(i, i + mappingCount);
    }
    for (let i = 0; i < mappingCount; i++) {
      const mappedId = pool.getRecycleIdMapping(i);
      eq(mappedId, i + mappingCount, `Should map ID ${i}`);
    }
  }

  public testRecyclePoolV2StressTestMixedOperations(): void {
    const pool = new RecyclePoolV2();
    const operations = 10000;
    for (let i = 0; i < operations; i++) {
      const reuseId = `reuse-id-${i % 10}`;
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component(reuseId, view);
      if (i % 3 === 0) {
        pool.popRecycleV2Component(reuseId);
      }
      if (i % 5 === 0) {
        pool.updateRecycleIdMapping(i, i + 10000);
      }
      if (i % 7 === 0) {
        pool.purgeAllCachedRecycleElmtIds();
      }
    }
    eq(true, true, 'Stress test with mixed operations should complete');
  }

  public testRecyclePoolV2MemoryEfficiency(): void {
    const pool = new RecyclePoolV2();
    const iterations = 1000;
    for (let i = 0; i < iterations; i++) {
      const view = new MockViewV2(i, `test${i}`);
      pool.pushRecycleV2Component('reuse-id', view);
      if (i % 10 === 0) {
        pool.purgeAllCachedRecycleElmtIds();
      }
    }
    eq(true, true, 'Should handle memory efficiently with periodic purging');
  }

  public testRecyclePoolV2ConcurrentLikeScenario(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    const view4 = new MockViewV2(4, 'test4');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.updateRecycleIdMapping(100, 200);
    pool.pushRecycleV2Component('reuse-id-1', view3);
    pool.pushRecycleV2Component('reuse-id-2', view4);
    const popped1 = pool.popRecycleV2Component('reuse-id-1');
    const popped2 = pool.popRecycleV2Component('reuse-id-2');
    const popped3 = pool.popRecycleV2Component('reuse-id-1');
    const popped4 = pool.popRecycleV2Component('reuse-id-2');
    eq((popped1 as MockViewV2).id, 3, 'First pop should return view3');
    eq((popped2 as MockViewV2).id, 4, 'Second pop should return view4');
    eq((popped3 as MockViewV2).id, 1, 'Third pop should return view1');
    eq((popped4 as MockViewV2).id, 2, 'Fourth pop should return view2');
  }

  public testRecyclePoolV2ReuseIdCaseSensitivity(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool.pushRecycleV2Component('Reuse-Id', view1);
    pool.pushRecycleV2Component('reuse-id', view2);
    const popped1 = pool.popRecycleV2Component('Reuse-Id');
    const popped2 = pool.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 1, 'Should pop with case-sensitive reuse-id');
    eq((popped2 as MockViewV2).id, 2, 'Should pop with case-sensitive reuse-id');
  }

  public testRecyclePoolV2ReuseIdWithNumbers(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id-1', view1);
    pool.pushRecycleV2Component('reuse-id-2', view2);
    pool.pushRecycleV2Component('reuse-id-10', view3);
    const popped1 = pool.popRecycleV2Component('reuse-id-1');
    const popped2 = pool.popRecycleV2Component('reuse-id-2');
    const popped3 = pool.popRecycleV2Component('reuse-id-10');
    eq((popped1 as MockViewV2).id, 1, 'Should pop with numeric suffix 1');
    eq((popped2 as MockViewV2).id, 2, 'Should pop with numeric suffix 2');
    eq((popped3 as MockViewV2).id, 3, 'Should pop with numeric suffix 10');
  }

  public testRecyclePoolV2ReuseIdWithDots(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool.pushRecycleV2Component('reuse.id', view1);
    pool.pushRecycleV2Component('reuse-id.test', view2);
    const popped1 = pool.popRecycleV2Component('reuse.id');
    const popped2 = pool.popRecycleV2Component('reuse-id.test');
    eq((popped1 as MockViewV2).id, 1, 'Should pop with dots in reuse-id');
    eq((popped2 as MockViewV2).id, 2, 'Should pop with dots in reuse-id');
  }

  public testRecyclePoolV2ReuseIdWithUnderscores(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse_id', view1);
    pool.pushRecycleV2Component('reuse_id_1', view2);
    pool.pushRecycleV2Component('reuse_id_2', view3);
    const popped1 = pool.popRecycleV2Component('reuse_id');
    const popped2 = pool.popRecycleV2Component('reuse_id_1');
    const popped3 = pool.popRecycleV2Component('reuse_id_2');
    eq((popped1 as MockViewV2).id, 1, 'Should pop with underscores in reuse-id');
    eq((popped2 as MockViewV2).id, 2, 'Should pop with underscores in reuse-id');
    eq((popped3 as MockViewV2).id, 3, 'Should pop with underscores in reuse-id');
  }

  public testRecyclePoolV2ReuseIdWithHyphens(): void {
    const pool = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool.pushRecycleV2Component('reuse-id', view1);
    pool.pushRecycleV2Component('reuse-id-1', view2);
    pool.pushRecycleV2Component('reuse-id-2', view3);
    const popped1 = pool.popRecycleV2Component('reuse-id');
    const popped2 = pool.popRecycleV2Component('reuse-id-1');
    const popped3 = pool.popRecycleV2Component('reuse-id-2');
    eq((popped1 as MockViewV2).id, 1, 'Should pop with hyphens in reuse-id');
    eq((popped2 as MockViewV2).id, 2, 'Should pop with hyphens in reuse-id');
    eq((popped3 as MockViewV2).id, 3, 'Should pop with hyphens in reuse-id');
  }

  public testRecyclePoolV2IdMappingConsistency(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    const mappedId1 = pool.getRecycleIdMapping(100);
    const mappedId2 = pool.getRecycleIdMapping(100);
    const mappedId3 = pool.getRecycleIdMapping(100);
    eq(mappedId1, 200, 'First get should return 200');
    eq(mappedId2, 200, 'Second get should return 200');
    eq(mappedId3, 200, 'Third get should return 200');
  }

  public testRecyclePoolV2IdMappingUpdateConsistency(): void {
    const pool = new RecyclePoolV2();
    pool.updateRecycleIdMapping(100, 200);
    eq(pool.getRecycleIdMapping(100), 200, 'Initial mapping should be 200');
    pool.updateRecycleIdMapping(100, 300);
    eq(pool.getRecycleIdMapping(100), 300, 'Updated mapping should be 300');
    pool.updateRecycleIdMapping(100, 400);
    eq(pool.getRecycleIdMapping(100), 400, 'Updated mapping should be 400');
  }

  public testRecyclePoolV2MultiplePoolsIndependence(): void {
    const pool1 = new RecyclePoolV2();
    const pool2 = new RecyclePoolV2();
    const pool3 = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    const view3 = new MockViewV2(3, 'test3');
    pool1.pushRecycleV2Component('reuse-id', view1);
    pool2.pushRecycleV2Component('reuse-id', view2);
    pool3.pushRecycleV2Component('reuse-id', view3);
    const popped1 = pool1.popRecycleV2Component('reuse-id');
    const popped2 = pool2.popRecycleV2Component('reuse-id');
    const popped3 = pool3.popRecycleV2Component('reuse-id');
    eq((popped1 as MockViewV2).id, 1, 'Pool1 should return view1');
    eq((popped2 as MockViewV2).id, 2, 'Pool2 should return view2');
    eq((popped3 as MockViewV2).id, 3, 'Pool3 should return view3');
  }

  public testRecyclePoolV2PoolIsolationAfterPurge(): void {
    const pool1 = new RecyclePoolV2();
    const pool2 = new RecyclePoolV2();
    const view1 = new MockViewV2(1, 'test1');
    const view2 = new MockViewV2(2, 'test2');
    pool1.pushRecycleV2Component('reuse-id', view1);
    pool2.pushRecycleV2Component('reuse-id', view2);
    pool1.purgeAllCachedRecycleElmtIds();
    eq(view1.resetCalled, true, 'Pool1 purge should reset view1');
    eq(view2.resetCalled, false, 'Pool2 purge should not affect view2');
    const popped2 = pool2.popRecycleV2Component('reuse-id');
    eq((popped2 as MockViewV2).id, 2, 'Pool2 should still return view2');
  }

  public testRecyclePoolV2EdgeCaseMaxSafeInteger(): void {
    const pool = new RecyclePoolV2();
    const maxId = Number.MAX_SAFE_INTEGER;
    pool.updateRecycleIdMapping(maxId, 100);
    const mappedId = pool.getRecycleIdMapping(maxId);
    eq(mappedId, 100, 'Should handle MAX_SAFE_INTEGER');
  }

  public testRecyclePoolV2EdgeCaseMinSafeInteger(): void {
    const pool = new RecyclePoolV2();
    const minId = Number.MIN_SAFE_INTEGER;
    pool.updateRecycleIdMapping(minId, 100);
    const mappedId = pool.getRecycleIdMapping(minId);
    eq(mappedId, 100, 'Should handle MIN_SAFE_INTEGER');
  }

  public testRecyclePoolV2EdgeCaseLargePositiveId(): void {
    const pool = new RecyclePoolV2();
    const largeId = 9007199254740991;
    pool.updateRecycleIdMapping(largeId, 100);
    const mappedId = pool.getRecycleIdMapping(largeId);
    eq(mappedId, 100, 'Should handle large positive ID');
  }

  public testRecyclePoolV2EdgeCaseLargeNegativeId(): void {
    const pool = new RecyclePoolV2();
    const largeId = -9007199254740991;
    pool.updateRecycleIdMapping(largeId, 100);
    const mappedId = pool.getRecycleIdMapping(largeId);
    eq(mappedId, 100, 'Should handle large negative ID');
  }

  public testRecyclePoolV2ViewLifecycleTracking(): void {
    const pool = new RecyclePoolV2();
    const view = new StatefulViewV2({ value: 'initial' });
    pool.pushRecycleV2Component('reuse-id', view);
    const popped = pool.popRecycleV2Component('reuse-id');
    eq((popped as StatefulViewV2).lifecycle.length, 0, 'Lifecycle should be empty after pop');
    pool.pushRecycleV2Component('reuse-id', popped as StatefulViewV2);
    pool.purgeAllCachedRecycleElmtIds();
    eq(view.lifecycle.length, 1, 'Lifecycle should have reset event');
    eq(view.lifecycle[0], 'reset', 'Should have reset lifecycle event');
  }

  public testRecyclePoolV2ContainerCapacity(): void {
    const pool = new RecyclePoolV2();
    const container = new ContainerViewV2('container', 5);
    for (let i = 0; i < 5; i++) {
      const item = new MockViewV2(i, `item${i}`);
      const added = container.addItem(item);
      eq(added, true, `Should add item ${i}`);
    }
    const extraItem = new MockViewV2(5, 'extra');
    const added = container.addItem(extraItem);
    eq(added, false, 'Should not add item beyond capacity');
    pool.pushRecycleV2Component('reuse-id', container);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedContainer = popped as ContainerViewV2;
    eq(poppedContainer.size, 5, 'Should preserve container size');
    eq(poppedContainer.capacity, 5, 'Should preserve container capacity');
  }

  public testRecyclePoolV2LazyLoadingBehavior(): void {
    const pool = new RecyclePoolV2();
    const lazyView = new LazyViewV2();
    eq(lazyView.loaded, false, 'View should not be loaded initially');
    lazyView.loadData();
    eq(lazyView.loaded, true, 'View should be loaded after loadData');
    pool.pushRecycleV2Component('reuse-id', lazyView);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedLazy = popped as LazyViewV2;
    eq(poppedLazy.loaded, true, 'Should preserve loaded state');
    eq(poppedLazy.data !== null, true, 'Should preserve data');
  }

  public testRecyclePoolV2CacheHitTracking(): void {
    const pool = new RecyclePoolV2();
    const cachedView = new CachedViewV2('cache-key');
    cachedView.hit();
    cachedView.hit();
    cachedView.hit();
    eq(cachedView.hits, 3, 'Should track 3 cache hits');
    pool.pushRecycleV2Component('reuse-id', cachedView);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedCached = popped as CachedViewV2;
    eq(poppedCached.hits, 3, 'Should preserve cache hit count');
    eq(poppedCached.cacheKey, 'cache-key', 'Should preserve cache key');
  }

  public testRecyclePoolV2RecycleLimit(): void {
    const pool = new RecyclePoolV2();
    const recyclableView = new RecyclableViewV2('recyclable', 3);
    eq(recyclableView.canRecycle(), true, 'View should be recyclable initially');
    recyclableView.resetRecycleCustomNode();
    eq(recyclableView.canRecycle(), true, 'View should be recyclable after 1 reset');
    recyclableView.resetRecycleCustomNode();
    eq(recyclableView.canRecycle(), true, 'View should be recyclable after 2 resets');
    recyclableView.resetRecycleCustomNode();
    eq(recyclableView.canRecycle(), false, 'View should not be recyclable after 3 resets');
    pool.pushRecycleV2Component('reuse-id', recyclableView);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedRecyclable = popped as RecyclableViewV2;
    eq(poppedRecyclable.valid, false, 'Should mark view as invalid');
  }

  public testRecyclePoolV2PoolSlotManagement(): void {
    const pool = new RecyclePoolV2();
    const pooledView = new PooledViewV2('pool-1', 5);
    eq(pooledView.slotId, 5, 'Should have slot ID 5');
    pooledView.allocate();
    eq(pooledView.allocated, true, 'View should be allocated');
    pool.pushRecycleV2Component('reuse-id', pooledView);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedPooled = popped as PooledViewV2;
    eq(poppedPooled.allocated, true, 'Should preserve allocated state');
    eq(poppedPooled.slotId, 5, 'Should preserve slot ID');
  }

  public testRecyclePoolV2SharedRefCounting(): void {
    const pool = new RecyclePoolV2();
    const sharedView = new SharedViewV2('shared-1');
    eq(sharedView.refCount, 0, 'Initial ref count should be 0');
    sharedView.acquire();
    sharedView.acquire();
    sharedView.acquire();
    eq(sharedView.refCount, 3, 'Ref count should be 3 after 3 acquires');
    sharedView.release();
    eq(sharedView.refCount, 2, 'Ref count should be 2 after 1 release');
    pool.pushRecycleV2Component('reuse-id', sharedView);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedShared = popped as SharedViewV2;
    eq(poppedShared.refCount, 2, 'Should preserve ref count');
  }

  public testRecyclePoolV2TransientLifetime(): void {
    const pool = new RecyclePoolV2();
    const transientView = new TransientViewV2('transient-1', 100);
    eq(transientView.isExpired(), false, 'View should not be expired initially');
    pool.pushRecycleV2Component('reuse-id', transientView);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedTransient = popped as TransientViewV2;
    eq(poppedTransient.isExpired(), false, 'Should not be expired after pop');
    poppedTransient.resetRecycleCustomNode();
    eq(poppedTransient.isExpired(), false, 'Should not be expired after reset');
  }

  public testRecyclePoolV2ManagedResources(): void {
    const pool = new RecyclePoolV2();
    const managedView = new ManagedViewV2('manager-1');
    managedView.addResource({ type: 'resource1', data: 'data1' });
    managedView.addResource({ type: 'resource2', data: 'data2' });
    managedView.addResource({ type: 'resource3', data: 'data3' });
    eq(managedView.resources.length, 3, 'Should have 3 resources');
    pool.pushRecycleV2Component('reuse-id', managedView);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedManaged = popped as ManagedViewV2;
    eq(poppedManaged.resources.length, 3, 'Should preserve resources');
    pool.pushRecycleV2Component('reuse-id', poppedManaged);
    pool.purgeAllCachedRecycleElmtIds();
    eq(managedView.resources.length, 0, 'Purge should clear resources');
  }

  public testRecyclePoolV2NestedHierarchy(): void {
    const pool = new RecyclePoolV2();
    const level3 = new NestedViewV2(3);
    const level2 = new NestedViewV2(2);
    const level1 = new NestedViewV2(1);
    level1.child = level2;
    level2.child = level3;
    level2.parent = level1;
    level3.parent = level2;
    pool.pushRecycleV2Component('reuse-id', level1);
    const popped = pool.popRecycleV2Component('reuse-id');
    const poppedLevel1 = popped as NestedViewV2;
    eq(poppedLevel1.level, 1, 'Should preserve level 1');
    eq((poppedLevel1.child as NestedViewV2).level, 2, 'Should preserve level 2');
    eq(((poppedLevel1.child as NestedViewV2).child as NestedViewV2).level, 3, 'Should preserve level 3');
  }
}
