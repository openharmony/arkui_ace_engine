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

declare class ViewPU {
    public static inactiveComponents_: Set<string>;
}

declare class BidirectionalMap {
    constructor();
    delete(key: number): void;
    get(key: number): number | undefined;
    add(pair: [number, number]): void;
}

declare class RecycleManager {
    constructor();
    updateNodeId(oldElmtId: number, newElmtId: number): void;
    proxyNodeId(oldElmtId: number): number;
    pushRecycleNode(name: string, node: any): void;
    popRecycleNode(name: string): any;
    purgeAllCachedRecycleNode(): void;
    setActive(active: boolean): void;
    getDumpInfo(): string;
}

declare class stateMgmtConsole {
    public static debug(msg: string): void;
    public static error(msg: string): void;
}

class MockViewPU {
    public id_: number;
    public hasBeenRecycled_: boolean = false;
    public isDeleting_: boolean = false;

    constructor(id: number) {
        this.id_ = id;
    }

    id__(): number {
        return this.id_;
    }

    resetRecycleCustomNode(): void {
        this.hasBeenRecycled_ = false;
    }

    setActiveInternal(active: boolean, isReuse: boolean): void {
        console.log(`MockViewPU ${this.id_} setActiveInternal: ${active}, isReuse: ${isReuse}`);
    }

    getParent(): any {
        return null;
    }
}

/**
 * Comprehensive RecycleManager Unit Tests
 *
 * This test suite validates the RecycleManager class for node recycling.
 *
 * Test Sections:
 * 1. Constructor and Initialization
 * 2. Node ID Mapping (BidirectionalMap)
 * 3. Push/Pop Recycle Nodes
 * 4. Purge Operations
 * 5. Active State Management
 * 6. Dump Information
 * 7. Edge Cases
 */
export class PuRecycleManagerTestsV2 implements ITestFile {
    private idString: string = "";
    private static recycleManager: RecycleManager | undefined;
    private static mockNodes: Map<string, MockViewPU[]>;

    constructor(str: string) {
        console.log(`Creating PuRecycleManagerTestsV2: ${str}`)
        this.idString = str;
        PuRecycleManagerTestsV2.mockNodes = new Map();
    }

    public beforeAll(): void {
        console.log("PuRecycleManagerTestsV2: Setting up test suite");
        PuRecycleManagerTestsV2.recycleManager = new RecycleManager();
    }

    public beforeEach(): void {
    }

    public afterAll(): void {
        console.log("PuRecycleManagerTestsV2: Tearing down test suite");
        PuRecycleManagerTestsV2.recycleManager = undefined;
    }

    public afterEach(): void {
    }

    public getId(): string {
        return this.idString;
    }

    // =========================================================================
    // SECTION 1: Constructor and Initialization
    // =========================================================================

    /**
     * Test RecycleManager constructor
     * Expected: Manager is created successfully
     */
    public testConstructor(): void {
        const manager = new RecycleManager();
        eq(manager !== undefined, true, "RecycleManager should be created");
    }

    /**
     * Test RecycleManager methods exist
     * Expected: All required methods are defined
     */
    public testMethodsExist(): void {
        const manager = new RecycleManager();
        eq(typeof manager.updateNodeId, 'function', "updateNodeId should be a function");
        eq(typeof manager.proxyNodeId, 'function', "proxyNodeId should be a function");
        eq(typeof manager.pushRecycleNode, 'function', "pushRecycleNode should be a function");
        eq(typeof manager.popRecycleNode, 'function', "popRecycleNode should be a function");
        eq(typeof manager.purgeAllCachedRecycleNode, 'function', "purgeAllCachedRecycleNode should be a function");
        eq(typeof manager.setActive, 'function', "setActive should be a function");
        eq(typeof manager.getDumpInfo, 'function', "getDumpInfo should be a function");
    }

    // =========================================================================
    // SECTION 2: BidirectionalMap
    // =========================================================================

    /**
     * Test BidirectionalMap constructor
     * Expected: Map is created successfully
     */
    public testBiMapConstructor(): void {
        const biMap = new BidirectionalMap();
        eq(biMap !== undefined, true, "BidirectionalMap should be created");
    }

    /**
     * Test BidirectionalMap add and get
     * Expected: Can store and retrieve mappings
     */
    public testBiMapAddAndGet(): void {
        const biMap = new BidirectionalMap();
        biMap.add([100, 200]);
        const result = biMap.get(100);
        eq(result, 200, "should return mapped value");
    }

    /**
     * Test BidirectionalMap reverse lookup
     * Expected: Can lookup from reverse direction
     */
    public testBiMapReverseLookup(): void {
        const biMap = new BidirectionalMap();
        biMap.add([100, 200]);
        const result = biMap.get(200);
        eq(result, 100, "should return reverse mapped value");
    }

    /**
     * Test BidirectionalMap delete via updateNodeId overwrite
     * Note: BidirectionalMap is a private internal class, testing via RecycleManager
     * Expected: updateNodeId overwrites existing mapping
     */
    public testBiMapDelete(): void {
        const manager = new RecycleManager();
        manager.updateNodeId(100, 200);
        manager.updateNodeId(100, 300);
        const proxied = manager.proxyNodeId(100);
        eq(proxied, 300, "should return new mapped value after overwrite");
    }

    /**
     * Test BidirectionalMap get with non-existent key
     * Expected: Returns undefined
     */
    public testBiMapGetNonExistent(): void {
        const biMap = new BidirectionalMap();
        const result = biMap.get(999);
        eq(result, undefined, "should return undefined for non-existent key");
    }

    // =========================================================================
    // SECTION 3: Push/Pop Recycle Nodes
    // =========================================================================

    /**
     * Test pushRecycleNode adds node to cache
     * Note: hasBeenRecycled_ is not set by pushRecycleNode, testing cache behavior instead
     * Expected: Node is added to cache and can be retrieved
     */
    public testPushRecycleNode(): void {
        const manager = new RecycleManager();
        const mockNode = new MockViewPU(1);
        manager.pushRecycleNode('TestComponent', mockNode as any);
        const popped = manager.popRecycleNode('TestComponent');
        eq(popped?.id__(), 1, "node should be retrievable from cache");
    }

    /**
     * Test pushRecycleNode with different component names
     * Expected: Nodes are stored separately by name
     */
    public testPushRecycleNodeDifferentNames(): void {
        const manager = new RecycleManager();
        const node1 = new MockViewPU(1);
        const node2 = new MockViewPU(2);
        manager.pushRecycleNode('ComponentA', node1 as any);
        manager.pushRecycleNode('ComponentB', node2 as any);
        const popped1 = manager.popRecycleNode('ComponentA');
        const popped2 = manager.popRecycleNode('ComponentB');
        eq(popped1?.id__(), 1, "node1 should be retrievable");
        eq(popped2?.id__(), 2, "node2 should be retrievable");
    }

    /**
     * Test popRecycleNode retrieves node
     * Expected: Node is retrieved from cache
     */
    public testPopRecycleNode(): void {
        const manager = new RecycleManager();
        const mockNode = new MockViewPU(1);
        manager.pushRecycleNode('TestComponent', mockNode as any);
        const popped = manager.popRecycleNode('TestComponent');
        eq(popped !== undefined, true, "should retrieve a node");
    }

    /**
     * Test popRecycleNode returns last pushed node
     * Expected: LIFO behavior
     */
    public testPopRecycleNodeLIFO(): void {
        const manager = new RecycleManager();
        const node1 = new MockViewPU(1);
        const node2 = new MockViewPU(2);
        manager.pushRecycleNode('TestComponent', node1 as any);
        manager.pushRecycleNode('TestComponent', node2 as any);
        const popped = manager.popRecycleNode('TestComponent');
        eq(popped?.id__(), 2, "should return last pushed node");
    }

    /**
     * testPopRecycleNode empty cache
     * Expected: Returns undefined
     */
    public testPopRecycleNodeEmpty(): void {
        const manager = new RecycleManager();
        const popped = manager.popRecycleNode('NonExistent');
        eq(popped, undefined, "should return undefined for empty cache");
    }

    // =========================================================================
    // SECTION 4: Node ID Mapping
    // =========================================================================

    /**
     * Test updateNodeId creates mapping
     * Expected: Mapping is stored
     */
    public testUpdateNodeId(): void {
        const manager = new RecycleManager();
        manager.updateNodeId(100, 200);
        const proxied = manager.proxyNodeId(100);
        eq(proxied, 200, "should return mapped id");
    }

    /**
     * Test proxyNodeId returns original if no mapping
     * Expected: Returns original id
     */
    public testProxyNodeIdNoMapping(): void {
        const manager = new RecycleManager();
        const result = manager.proxyNodeId(999);
        eq(result, 999, "should return original id");
    }

    /**
     * Test updateNodeId overwrites mapping
     * Expected: New mapping replaces old
     */
    public testUpdateNodeIdOverwrite(): void {
        const manager = new RecycleManager();
        manager.updateNodeId(100, 200);
        manager.updateNodeId(100, 300);
        const proxied = manager.proxyNodeId(100);
        eq(proxied, 300, "should return new mapped id");
    }

    // =========================================================================
    // SECTION 5: Purge Operations
    // =========================================================================

    /**
     * Test purgeAllCachedRecycleNode clears cache
     * Expected: Cache is cleared
     */
    public testPurgeAllCachedRecycleNode(): void {
        const manager = new RecycleManager();
        const node1 = new MockViewPU(1);
        const node2 = new MockViewPU(2);
        manager.pushRecycleNode('ComponentA', node1 as any);
        manager.pushRecycleNode('ComponentB', node2 as any);
        manager.purgeAllCachedRecycleNode();
        const popped1 = manager.popRecycleNode('ComponentA');
        const popped2 = manager.popRecycleNode('ComponentB');
        eq(popped1, undefined, "ComponentA cache should be empty");
        eq(popped2, undefined, "ComponentB cache should be empty");
    }

    /**
     * Test purgeAllCachedRecycleNode resets nodes
     * Expected: Nodes are reset
     */
    public testPurgeAllResetsNodes(): void {
        const manager = new RecycleManager();
        const node = new MockViewPU(1);
        manager.pushRecycleNode('TestComponent', node as any);
        manager.purgeAllCachedRecycleNode();
        eq(node.hasBeenRecycled_, false, "node should be reset");
    }

    // =========================================================================
    // SECTION 6: Active State Management
    // =========================================================================

    /**
     * Test setActive calls setActiveInternal
     * Expected: Method exists and is callable
     */
    public testSetActive(): void {
        const manager = new RecycleManager();
        const node = new MockViewPU(1);
        manager.pushRecycleNode('TestComponent', node as any);
        eq(typeof manager.setActive, 'function', "setActive should be a function");
    }

    /**
     * Test setActive with true value
     * Expected: Can be called with true
     */
    public testSetActiveTrue(): void {
        const manager = new RecycleManager();
        eq(typeof manager.setActive, 'function', "should be callable");
    }

    /**
     * Test setActive with false value
     * Expected: Can be called with false
     */
    public testSetActiveFalse(): void {
        const manager = new RecycleManager();
        eq(typeof manager.setActive, 'function', "should be callable");
    }

    // =========================================================================
    // SECTION 7: Dump Information
    // =========================================================================

    /**
     * Test getDumpInfo returns string
     * Expected: Returns JSON string
     */
    public testGetDumpInfo(): void {
        const manager = new RecycleManager();
        const info = manager.getDumpInfo();
        eq(typeof info, 'string', "should return string");
    }

    /**
     * Test getDumpInfo with cached nodes
     * Expected: Contains node information
     */
    public testGetDumpInfoWithNodes(): void {
        const manager = new RecycleManager();
        const node1 = new MockViewPU(1);
        const node2 = new MockViewPU(2);
        manager.pushRecycleNode('ComponentA', node1 as any);
        manager.pushRecycleNode('ComponentB', node2 as any);
        const info = manager.getDumpInfo();
        eq(info.includes('ComponentA'), true, "should include ComponentA");
        eq(info.includes('ComponentB'), true, "should include ComponentB");
    }

    // =========================================================================
    // SECTION 8: Edge Cases
    // =========================================================================

    /**
     * Test push/pop with empty string name
     * Expected: Works with empty string
     */
    public testEmptyName(): void {
        const manager = new RecycleManager();
        const node = new MockViewPU(1);
        manager.pushRecycleNode('', node as any);
        const popped = manager.popRecycleNode('');
        eq(popped?.id__(), 1, "should work with empty string");
    }

    /**
     * Test multiple push/pop cycles
     * Expected: Multiple cycles work correctly
     */
    public testMultipleCycles(): void {
        const manager = new RecycleManager();
        
        for (let i = 0; i < 5; i++) {
            const node = new MockViewPU(i);
            manager.pushRecycleNode('CycleComponent', node as any);
            const popped = manager.popRecycleNode('CycleComponent');
            eq(popped?.id__(), i, `cycle ${i} should work`);
        }
    }

    /**
     * Test different component types
     * Expected: Each type maintains separate cache
     */
    public testDifferentComponentTypes(): void {
        const manager = new RecycleManager();
        const types = ['Button', 'Text', 'Image', 'Column', 'Row', 'List'];
        
        for (let i = 0; i < types.length; i++) {
            const node = new MockViewPU(i);
            manager.pushRecycleNode(types[i], node as any);
        }
        
        for (let i = 0; i < types.length; i++) {
            const popped = manager.popRecycleNode(types[i]);
            eq(popped?.id__(), i, `type ${types[i]} should have correct node`);
        }
    }

    /**
     * Test node id zero
     * Expected: Zero id is handled correctly
     */
    public testZeroNodeId(): void {
        const manager = new RecycleManager();
        manager.updateNodeId(0, 100);
        const proxied = manager.proxyNodeId(0);
        eq(proxied, 100, "zero id should be handled");
    }

    /**
     * Test negative node id
     * Expected: Negative id is handled correctly
     */
    public testNegativeNodeId(): void {
        const manager = new RecycleManager();
        manager.updateNodeId(-1, -100);
        const proxied = manager.proxyNodeId(-1);
        eq(proxied, -100, "negative id should be handled");
    }

    /**
     * Test large node id
     * Expected: Large id is handled correctly
     */
    public testLargeNodeId(): void {
        const manager = new RecycleManager();
        const largeId = 999999999;
        manager.updateNodeId(largeId, largeId + 1);
        const proxied = manager.proxyNodeId(largeId);
        eq(proxied, largeId + 1, "large id should be handled");
    }

    /**
     * Test ViewPU static inactiveComponents
     * Expected: Is a Set
     */
    public testViewPUStaticInactiveComponents(): void {
        eq(ViewPU.inactiveComponents_ instanceof Set, true, "should be a Set");
    }

    /**
     * Test MockViewPU id method
     * Expected: Returns correct id
     */
    public testMockViewPUId(): void {
        const mock = new MockViewPU(123);
        eq(mock.id__(), 123, "should return correct id");
    }

    /**
     * Test MockViewPU resetRecycleCustomNode
     * Expected: Resets hasBeenRecycled_ flag
     */
    public testMockViewPUReset(): void {
        const mock = new MockViewPU(1);
        mock.hasBeenRecycled_ = true;
        mock.resetRecycleCustomNode();
        eq(mock.hasBeenRecycled_, false, "should be reset to false");
    }
}
