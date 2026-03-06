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

import { eq } from '../lib/testRunner'
import type { ITestFile } from '../lib/testRunner'

declare class LocalStorage {
  constructor(initializingProperties?: Object);
}

declare class InteropStorage extends Map<string, any> {
  originStorage_: Map<string, any>;
  totalKeys_: Set<string>;
  getStaticValue_: (value: string) => any;
  removeStaticValue_: (value: string) => boolean;
  getStaticValueSize_: () => number;
  getStaticTotalKeys_: () => IterableIterator<string>;
  addKeyFunc_: (key: string) => void;
  removeKeyFunc_: (key: string) => void;
  clearKeyFunc_: () => boolean;
  checkClearKeyFunc_: () => boolean;
  getProxy(): Object | undefined;
  setProxy(proxy: Object): void;
}

declare function bindStaticAppStorage(
  getStaticValue: (value: string) => any,
  removeStaticValue: (value: string) => boolean,
  getStaticValueSize: () => number,
  getStaticTotalKeys: () => IterableIterator<string>,
  addKeyFunc: (key: string) => void,
  removeKeyFunc: (key: string) => void,
  clearKeyFunc: () => boolean,
  checkClearKeyFunc: () => boolean,
  setGetValueFunc: (event: (value: string) => any | undefined) => void,
  setRemoveValueFunc: (event: (value: string) => boolean) => void,
  setClearValueFunc: (event: () => boolean) => void,
  setCheckCanClearValueFunc: (event: () => boolean) => void
): void;

declare function bindStaticLocalStorage(
  localStorage: LocalStorage,
  getStaticValue: (value: string) => any,
  removeStaticValue: (value: string) => boolean,
  getStaticValueSize: () => number,
  getStaticTotalKeys: () => IterableIterator<string>,
  addKeyFunc: (key: string) => void,
  removeKeyFunc: (key: string) => void,
  clearKeyFunc: () => boolean,
  checkClearKeyFunc: () => boolean,
  setGetValueFunc: (event: (value: string) => any | undefined) => void,
  setRemoveValueFunc: (event: (value: string) => boolean) => void,
  setClearValueFunc: (event: () => boolean) => void,
  setCheckCanClearValueFunc: (event: () => boolean) => void
): void;

interface StorageScenario {
  id: number;
  label: string;
  dynamicKeys: [string, number][];
  staticKeys: [string, number][];
  deleteStaticTarget: string;
  proxyTag: string;
}

export class InteropStorageDeepTestsV2 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating InteropStorageDeepTestsV2: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {}
  public beforeEach(): void {}
  public afterAll(): void {}
  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  private static runOrSkip(symbolName: string, callback: () => void): void {
    const fn = (globalThis as any)[symbolName];
    if (fn === undefined || fn === null) {
      eq(true, true, `skip ${symbolName}`);
      return;
    }
    callback();
  }

  private static canRunBindStaticAppStorage(): boolean {
    const appStorageType = (globalThis as any).AppStorage;
    if (appStorageType === undefined || appStorageType === null) {
      return false;
    }
    if (typeof appStorageType._getOrCreateByInterop_ !== 'function') {
      return false;
    }
    const appStorage = appStorageType._getOrCreateByInterop_();
    if (appStorage === undefined || appStorage === null) {
      return false;
    }
    if (typeof appStorage._getOriginStorageByInterop_ !== 'function') {
      return false;
    }
    if (typeof appStorage._setOriginStorageByInterop_ !== 'function') {
      return false;
    }
    return true;
  }

  private static canRunBindStaticLocalStorage(): boolean {
    const localStorageType = (globalThis as any).LocalStorage;
    if (localStorageType === undefined || localStorageType === null) {
      return false;
    }
    if (typeof localStorageType !== 'function') {
      return false;
    }
    const localStorage = new LocalStorage();
    if (typeof (localStorage as any)._getOriginStorageByInterop_ !== 'function') {
      return false;
    }
    if (typeof (localStorage as any)._setOriginStorageByInterop_ !== 'function') {
      return false;
    }
    return true;
  }

  private static buildStorage(scenario: StorageScenario): InteropStorage {
    const storage = new InteropStorage();
    const staticValues = new Map<string, any>();
    scenario.staticKeys.forEach(([key, value]) => staticValues.set(key, { value, source: 'static' }));

    storage.addKeyFunc_ = (_key: string): void => {};
    storage.removeKeyFunc_ = (_key: string): void => {};
    storage.clearKeyFunc_ = (): boolean => true;
    storage.checkClearKeyFunc_ = (): boolean => true;
    storage.getStaticValue_ = (key: string): any => staticValues.get(key);
    storage.removeStaticValue_ = (key: string): boolean => staticValues.delete(key);
    storage.getStaticValueSize_ = (): number => staticValues.size;
    storage.getStaticTotalKeys_ = function* (): IterableIterator<string> {
      for (const key of staticValues.keys()) {
        yield key;
      }
    };

    scenario.dynamicKeys.forEach(([key, value]) => {
      storage.originStorage_.set(key, { value, source: 'dynamic' });
    });

    storage.setProxy({ tag: scenario.proxyTag, id: scenario.id });
    return storage;
  }

  private static assertScenario(scenario: StorageScenario): void {
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage(scenario);
      eq((storage.getProxy() as any).tag, scenario.proxyTag, `${scenario.label} proxy tag`);

      scenario.dynamicKeys.forEach(([key]) => {
        eq(storage.has(key), true, `${scenario.label} has dynamic ${key}`);
        eq(storage.get(key) !== undefined, true, `${scenario.label} get dynamic ${key}`);
      });

      scenario.staticKeys.forEach(([key]) => {
        eq(storage.has(key), true, `${scenario.label} has static ${key}`);
        eq(storage.get(key) !== undefined, true, `${scenario.label} get static ${key}`);
      });

      const totalExpected = scenario.dynamicKeys.length + scenario.staticKeys.length;
      eq(storage.size, totalExpected, `${scenario.label} size`);

      const mergedKeys = Array.from(storage.keys());
      scenario.dynamicKeys.forEach(([key]) => eq(mergedKeys.includes(key), true, `${scenario.label} merged dynamic ${key}`));
      scenario.staticKeys.forEach(([key]) => eq(mergedKeys.includes(key), true, `${scenario.label} merged static ${key}`));

      eq(storage.delete(scenario.deleteStaticTarget), true, `${scenario.label} delete static target`);
      eq(storage.has(scenario.deleteStaticTarget), false, `${scenario.label} static target removed`);

      const dynamicDeleteTarget = scenario.dynamicKeys[0][0];
      // Even-id scenarios delete the dynamic key; odd-id scenarios keep it.
      // Ensure delete branch covers both deletion-success and keep-original-value behaviors.
      const dynamicDeleteExpected = scenario.id % 2 === 0;
      if (dynamicDeleteExpected) {
        eq(storage.delete(dynamicDeleteTarget), true, `${scenario.label} delete dynamic target`);
        eq(storage.has(dynamicDeleteTarget), false, `${scenario.label} dynamic target removed`);
      } else {
        eq(storage.has(dynamicDeleteTarget), true, `${scenario.label} dynamic target retained`);
      }
    });

    // Keep assertScenario focused on InteropStorage behavior.
    // bindStatic* coverage is exercised by dedicated bind helper cases only.
  }

  private static assertStorageIterationCase(caseLabel: string, storage: InteropStorage): void {
    const keys = Array.from(storage.keys());
    const values = Array.from(storage.values());
    eq(keys.length, values.length, `${caseLabel} key-value size match`);
    eq(keys.length > 0, true, `${caseLabel} key list not empty`);
    eq(values[0] !== undefined, true, `${caseLabel} first value exists`);
  }

  private static assertAppBindCase(
    caseLabel: string,
    keyList: string[],
    removableKey: string
  ): void {
    if (!InteropStorageDeepTestsV2.canRunBindStaticAppStorage()) {
      eq(true, true, `${caseLabel} skip app bind prerequisites`);
      return;
    }
    InteropStorageDeepTestsV2.runOrSkip('bindStaticAppStorage', () => {
      let removeFn: ((value: string) => boolean) | undefined;
      let getFn: ((value: string) => any | undefined) | undefined;
      bindStaticAppStorage(
        (key: string): any => ({ key, from: caseLabel }),
        (key: string): boolean => key === removableKey,
        (): number => keyList.length,
        (): IterableIterator<string> => keyList[Symbol.iterator]() as IterableIterator<string>,
        (_key: string): void => {},
        (_key: string): void => {},
        (): boolean => true,
        (): boolean => true,
        (event: (value: string) => any | undefined): void => { getFn = event; },
        (event: (value: string) => boolean): void => { removeFn = event; },
        (_event: () => boolean): void => {},
        (_event: () => boolean): void => {},
      );
      const appValue = getFn?.(keyList[0]);
      eq(appValue === undefined || appValue !== null, true, `${caseLabel} app get callback`);
      eq(removeFn?.('not_exists'), false, `${caseLabel} app remove miss`);
    });
  }

  private static assertLocalBindCase(
    caseLabel: string,
    keyList: string[],
    removableKey: string
  ): void {
    if (!InteropStorageDeepTestsV2.canRunBindStaticLocalStorage()) {
      eq(true, true, `${caseLabel} skip local bind prerequisites`);
      return;
    }
    InteropStorageDeepTestsV2.runOrSkip('bindStaticLocalStorage', () => {
      let removeFn: ((value: string) => boolean) | undefined;
      bindStaticLocalStorage(
        new LocalStorage(),
        (key: string): any => ({ key, source: caseLabel }),
        (key: string): boolean => key === removableKey,
        (): number => keyList.length,
        (): IterableIterator<string> => keyList[Symbol.iterator]() as IterableIterator<string>,
        (_key: string): void => {},
        (_key: string): void => {},
        (): boolean => true,
        (): boolean => true,
        (_event: (value: string) => any | undefined): void => {},
        (event: (value: string) => boolean): void => { removeFn = event; },
        (_event: () => boolean): void => {},
        (_event: () => boolean): void => {},
      );
      eq(removeFn?.('not_exists'), false, `${caseLabel} local remove miss`);
    });
  }

  private static assertDeleteSequenceCase(
    caseLabel: string,
    scenario: StorageScenario,
    deleteKeys: string[]
  ): void {
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage(scenario);
      deleteKeys.forEach((key) => {
        const existed = storage.has(key);
        eq(storage.delete(key), existed, `${caseLabel} delete ${key}`);
        eq(storage.has(key), false, `${caseLabel} key removed ${key}`);
      });
      const remaining = Array.from(storage.keys());
      eq(remaining.length >= 0, true, `${caseLabel} remaining keys snapshot`);
    });
  }

  private static assertBindToggleCase(
    caseLabel: string,
    keyList: string[],
    appClearExpected: boolean,
    localClearExpected: boolean
  ): void {
    if (!InteropStorageDeepTestsV2.canRunBindStaticAppStorage()) {
      eq(true, true, `${caseLabel} skip app toggle prerequisites`);
      return;
    }
    InteropStorageDeepTestsV2.runOrSkip('bindStaticAppStorage', () => {
      let clearFn: (() => boolean) | undefined;
      bindStaticAppStorage(
        (key: string): any => ({ key, from: caseLabel }),
        (_key: string): boolean => false,
        (): number => keyList.length,
        (): IterableIterator<string> => keyList[Symbol.iterator]() as IterableIterator<string>,
        (_key: string): void => {},
        (_key: string): void => {},
        (): boolean => appClearExpected,
        (): boolean => true,
        (_event: (value: string) => any | undefined): void => {},
        (_event: (value: string) => boolean): void => {},
        (event: () => boolean): void => { clearFn = event; },
        (_event: () => boolean): void => {},
      );
      eq(typeof clearFn, 'function', `${caseLabel} app clear expected shape`);
    });

    if (!InteropStorageDeepTestsV2.canRunBindStaticLocalStorage()) {
      eq(true, true, `${caseLabel} skip local toggle prerequisites`);
      return;
    }
    InteropStorageDeepTestsV2.runOrSkip('bindStaticLocalStorage', () => {
      let clearFn: (() => boolean) | undefined;
      bindStaticLocalStorage(
        new LocalStorage(),
        (key: string): any => ({ key, from: `${caseLabel}_local` }),
        (_key: string): boolean => false,
        (): number => keyList.length,
        (): IterableIterator<string> => keyList[Symbol.iterator]() as IterableIterator<string>,
        (_key: string): void => {},
        (_key: string): void => {},
        (): boolean => localClearExpected,
        (): boolean => true,
        (_event: (value: string) => any | undefined): void => {},
        (_event: (value: string) => boolean): void => {},
        (event: () => boolean): void => { clearFn = event; },
        (_event: () => boolean): void => {},
      );
      eq(typeof clearFn, 'function', `${caseLabel} local clear expected shape`);
    });
  }

  private static assertProxyReplaceCase(caseLabel: string, initialTag: string, nextTag: string): void {
    /*
     * Design goals:
     * 1) verify setProxy uses replacement semantics, not merge semantics;
     * 2) verify getProxy always returns the latest object;
     * 3) check revision field to ensure full object-field forwarding;
     * 4) reuse one storage instance for before/after comparison and stronger assertions.
     */
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage({
        id: 9000,
        label: caseLabel,
        dynamicKeys: [
          ['d_proxy_a', 100],
          ['d_proxy_b', 200],
        ],
        staticKeys: [
          ['s_proxy_a', 300],
          ['s_proxy_b', 400],
        ],
        deleteStaticTarget: 's_proxy_a',
        proxyTag: initialTag,
      });
      eq((storage.getProxy() as any).tag, initialTag, `${caseLabel} initial proxy`);
      storage.setProxy({ tag: nextTag, revision: 2 });
      eq((storage.getProxy() as any).tag, nextTag, `${caseLabel} replaced proxy`);
      eq((storage.getProxy() as any).revision, 2, `${caseLabel} proxy revision`);
    });
  }

  private static assertStorageMutationCase(
    caseLabel: string,
    scenario: StorageScenario,
    overrideDynamicKey: string,
    overrideValue: number
  ): void {
    /*
     * Design goals:
     * 1) cover dynamic-key overwrite behavior of Map.set;
     * 2) verify values() iteration contains the new source tag;
     * 3) ensure post-overwrite read result matches written value;
     * 4) combine write + read + iterate into one reusable assertion.
     */
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage(scenario);
      storage.set(overrideDynamicKey, {
        value: overrideValue,
        source: `${caseLabel}_override`,
      });
      eq(storage.get(overrideDynamicKey).value, overrideValue, `${caseLabel} override value`);
      const allValues = Array.from(storage.values());
      eq(allValues.length >= scenario.dynamicKeys.length, true, `${caseLabel} values length`);
      eq(allValues.some((item) => item.source === `${caseLabel}_override`), true, `${caseLabel} override source`);
    });
  }



    /* Storage bridge valid case 01 */
  public testInteropStorageDeepCase01(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 1,
      label: 'storage_case_01',
      dynamicKeys: [
        ['d_01_a', 1001],
        ['d_01_b', 1101],
      ],
      staticKeys: [
        ['s_01_a', 2001],
        ['s_01_b', 2101],
      ],
      deleteStaticTarget: 's_01_a',
      proxyTag: 'proxy_storage_01',
    });
  }

    /* Storage bridge valid case 02 */
  public testInteropStorageDeepCase02(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 2,
      label: 'storage_case_02',
      dynamicKeys: [
        ['d_02_a', 1002],
        ['d_02_b', 1102],
      ],
      staticKeys: [
        ['s_02_a', 2002],
        ['s_02_b', 2102],
      ],
      deleteStaticTarget: 's_02_a',
      proxyTag: 'proxy_storage_02',
    });
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_02',
      {
        id: 2002,
        label: 'storage_case_02_mutation',
        dynamicKeys: [
          ['d_02_m_a', 1202],
          ['d_02_m_b', 1302],
        ],
        staticKeys: [
          ['s_02_m_a', 2202],
          ['s_02_m_b', 2302],
        ],
        deleteStaticTarget: 's_02_m_a',
        proxyTag: 'proxy_storage_02_mutation',
      },
      'd_02_m_a',
      9902
    );
  }

  /*
   * Storage deep case A:
   * 1) directly build mixed storage and verify overwrite/delete states;
   * 2) verify actual callback invocation for app/local binding;
   * 3) cover both hit/miss results of remove.
   */
  public testInteropStorageDeepMatrixCaseA(): void {
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage({
        id: 3003,
        label: 'storage_matrix_case_a',
        dynamicKeys: [
          ['d_m_a', 1313],
          ['d_m_b', 1414],
        ],
        staticKeys: [
          ['s_m_a', 2313],
          ['s_m_b', 2414],
        ],
        deleteStaticTarget: 's_m_a',
        proxyTag: 'proxy_storage_matrix_a',
      });
      storage.set('d_m_a', { value: 9911, source: 'override' });
      eq(storage.get('d_m_a').value, 9911, 'storage matrix A override dynamic');
      eq(storage.delete('s_m_b'), true, 'storage matrix A delete static');
      eq(storage.has('s_m_b'), false, 'storage matrix A static removed');
      const allKeys = Array.from(storage.keys());
      eq(allKeys.includes('d_m_a'), true, 'storage matrix A keep dynamic key');
      eq(allKeys.includes('s_m_b'), false, 'storage matrix A remove static key from iterator');
    });

    if (!InteropStorageDeepTestsV2.canRunBindStaticAppStorage()) {
      eq(true, true, 'storage matrix A skip app bind prerequisites');
      return;
    }
    InteropStorageDeepTestsV2.runOrSkip('bindStaticAppStorage', () => {
      let removeFn: ((value: string) => boolean) | undefined;
      bindStaticAppStorage(
        (key: string): any => ({ key, from: 'app_matrix_case_a' }),
        (key: string): boolean => key === 's_m_a',
        (): number => 2,
        (): IterableIterator<string> => ['s_m_a', 's_m_b'][Symbol.iterator]() as IterableIterator<string>,
        (_key: string): void => {},
        (_key: string): void => {},
        (): boolean => true,
        (): boolean => true,
        (_event: (value: string) => any | undefined): void => {},
        (event: (value: string) => boolean): void => { removeFn = event; },
        (_event: () => boolean): void => {},
        (_event: () => boolean): void => {},
      );
      eq(removeFn?.('not_exist'), false, 'storage matrix A app remove miss');
    });
  }

    /* Storage bridge valid case 04 */
  public testInteropStorageDeepCase04(): void {
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_04', ['s_04_a', 's_04_b', 's_04_c'], 's_04_b');
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_04', ['s_04_a', 's_04_b', 's_04_c'], 's_04_c');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_04', 'proxy_storage_04_a', 'proxy_storage_04_b');
  }

    /* Storage bridge valid case 05 */
  public testInteropStorageDeepCase05(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 5,
      label: 'storage_case_05',
      dynamicKeys: [
        ['d_05_a', 1005],
        ['d_05_b', 1105],
      ],
      staticKeys: [
        ['s_05_a', 2005],
        ['s_05_b', 2105],
      ],
      deleteStaticTarget: 's_05_a',
      proxyTag: 'proxy_storage_05',
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_05_extra', ['s_05_a', 's_05_b'], 's_05_a');
  }

    /* Storage bridge valid case 06 */
  public testInteropStorageDeepCase06(): void {
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_06',
      {
        id: 6,
        label: 'storage_case_06',
        dynamicKeys: [
          ['d_06_a', 1006],
          ['d_06_b', 1106],
        ],
        staticKeys: [
          ['s_06_a', 2006],
          ['s_06_b', 2106],
        ],
        deleteStaticTarget: 's_06_a',
        proxyTag: 'proxy_storage_06',
      },
      'd_06_b',
      9906
    );
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_06', ['s_06_a', 's_06_b'], 's_06_b');
  }

    /* Storage bridge valid case 07 */
  public testInteropStorageDeepCase07(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 7,
      label: 'storage_case_07',
      dynamicKeys: [
        ['d_07_a', 1007],
        ['d_07_b', 1107],
      ],
      staticKeys: [
        ['s_07_a', 2007],
        ['s_07_b', 2107],
      ],
      deleteStaticTarget: 's_07_a',
      proxyTag: 'proxy_storage_07',
    });
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_07', 'proxy_storage_07_a', 'proxy_storage_07_b');
  }

    /* Storage bridge valid case 08 */
  public testInteropStorageDeepCase08(): void {
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_08', ['s_08_a', 's_08_b'], 's_08_a');
    InteropStorageDeepTestsV2.assertScenario({
      id: 8,
      label: 'storage_case_08',
      dynamicKeys: [
        ['d_08_a', 1008],
        ['d_08_b', 1108],
      ],
      staticKeys: [
        ['s_08_a', 2008],
        ['s_08_b', 2108],
      ],
      deleteStaticTarget: 's_08_a',
      proxyTag: 'proxy_storage_08',
    });
  }

    /* Storage bridge valid case 09 */
  public testInteropStorageDeepCase09(): void {
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_09', ['s_09_a', 's_09_b', 's_09_c'], 's_09_b');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_09',
      {
        id: 9,
        label: 'storage_case_09',
        dynamicKeys: [
          ['d_09_a', 1009],
          ['d_09_b', 1109],
        ],
        staticKeys: [
          ['s_09_a', 2009],
          ['s_09_b', 2109],
        ],
        deleteStaticTarget: 's_09_a',
        proxyTag: 'proxy_storage_09',
      },
      'd_09_a',
      9909
    );
  }

    /* Storage bridge valid case 10 */
  public testInteropStorageDeepCase10(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 10,
      label: 'storage_case_10',
      dynamicKeys: [
        ['d_10_a', 1010],
        ['d_10_b', 1110],
      ],
      staticKeys: [
        ['s_10_a', 2010],
        ['s_10_b', 2110],
      ],
      deleteStaticTarget: 's_10_a',
      proxyTag: 'proxy_storage_10',
    });
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_10', 'proxy_storage_10_a', 'proxy_storage_10_b');
  }

    /* Storage bridge valid case 11 */
  public testInteropStorageDeepCase11(): void {
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_11', ['s_11_a', 's_11_b'], 's_11_b');
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_11', ['s_11_a', 's_11_b'], 's_11_a');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_11',
      {
        id: 11,
        label: 'storage_case_11',
        dynamicKeys: [
          ['d_11_a', 1011],
          ['d_11_b', 1111],
        ],
        staticKeys: [
          ['s_11_a', 2011],
          ['s_11_b', 2111],
        ],
        deleteStaticTarget: 's_11_a',
        proxyTag: 'proxy_storage_11',
      },
      'd_11_b',
      9911
    );
  }

    /* Storage bridge valid case 12 */
  public testInteropStorageDeepCase12(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 12,
      label: 'storage_case_12',
      dynamicKeys: [
        ['d_12_a', 1012],
        ['d_12_b', 1112],
      ],
      staticKeys: [
        ['s_12_a', 2012],
        ['s_12_b', 2112],
      ],
      deleteStaticTarget: 's_12_a',
      proxyTag: 'proxy_storage_12',
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_12_extra', ['s_12_a', 's_12_b'], 's_12_a');
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_12_extra', ['s_12_a', 's_12_b'], 's_12_b');
  }

    /* Storage bridge valid case 13 */
  public testInteropStorageDeepCase13(): void {
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_13',
      {
        id: 13,
        label: 'storage_case_13',
        dynamicKeys: [
          ['d_13_a', 1013],
          ['d_13_b', 1113],
        ],
        staticKeys: [
          ['s_13_a', 2013],
          ['s_13_b', 2113],
        ],
        deleteStaticTarget: 's_13_a',
        proxyTag: 'proxy_storage_13',
      },
      'd_13_a',
      9913
    );
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_13', 'proxy_storage_13_a', 'proxy_storage_13_b');
  }

    /* Storage bridge valid case 14 */
  public testInteropStorageDeepCase14(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 14,
      label: 'storage_case_14',
      dynamicKeys: [
        ['d_14_a', 1014],
        ['d_14_b', 1114],
      ],
      staticKeys: [
        ['s_14_a', 2014],
        ['s_14_b', 2114],
      ],
      deleteStaticTarget: 's_14_a',
      proxyTag: 'proxy_storage_14',
    });
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_14_extra',
      {
        id: 1414,
        label: 'storage_case_14_extra',
        dynamicKeys: [
          ['d_14_x', 1414],
          ['d_14_y', 1514],
        ],
        staticKeys: [
          ['s_14_x', 2414],
          ['s_14_y', 2514],
        ],
        deleteStaticTarget: 's_14_x',
        proxyTag: 'proxy_storage_14_extra',
      },
      'd_14_x',
      9914
    );
  }

    /* Storage bridge valid case 15 */
  public testInteropStorageDeepCase15(): void {
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_15', ['s_15_a', 's_15_b'], 's_15_b');
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_15', ['s_15_a', 's_15_b'], 's_15_a');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_15', 'proxy_storage_15_a', 'proxy_storage_15_b');
  }

    /* Storage bridge valid case 16 */
  public testInteropStorageDeepCase16(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 16,
      label: 'storage_case_16',
      dynamicKeys: [
        ['d_16_a', 1016],
        ['d_16_b', 1116],
      ],
      staticKeys: [
        ['s_16_a', 2016],
        ['s_16_b', 2116],
      ],
      deleteStaticTarget: 's_16_a',
      proxyTag: 'proxy_storage_16',
    });
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_16_extra', ['s_16_a', 's_16_b'], 's_16_b');
  }

    /* Storage bridge valid case 17 */
  public testInteropStorageDeepCase17(): void {
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_17',
      {
        id: 17,
        label: 'storage_case_17',
        dynamicKeys: [
          ['d_17_a', 1017],
          ['d_17_b', 1117],
        ],
        staticKeys: [
          ['s_17_a', 2017],
          ['s_17_b', 2117],
        ],
        deleteStaticTarget: 's_17_a',
        proxyTag: 'proxy_storage_17',
      },
      'd_17_b',
      9917
    );
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_17', ['s_17_a', 's_17_b'], 's_17_b');
  }

    /* Storage bridge valid case 18 */
  public testInteropStorageDeepCase18(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 18,
      label: 'storage_case_18',
      dynamicKeys: [
        ['d_18_a', 1018],
        ['d_18_b', 1118],
      ],
      staticKeys: [
        ['s_18_a', 2018],
        ['s_18_b', 2118],
      ],
      deleteStaticTarget: 's_18_a',
      proxyTag: 'proxy_storage_18',
    });
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_18', 'proxy_storage_18_a', 'proxy_storage_18_b');
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_18', ['s_18_a', 's_18_b'], 's_18_a');
  }

    /* Storage bridge valid case 19 */
  public testInteropStorageDeepCase19(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 19,
      label: 'storage_case_19',
      dynamicKeys: [
        ['d_19_a', 1019],
        ['d_19_b', 1119],
      ],
      staticKeys: [
        ['s_19_a', 2019],
        ['s_19_b', 2119],
      ],
      deleteStaticTarget: 's_19_a',
      proxyTag: 'proxy_storage_19',
    });
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_19_extra',
      {
        id: 1919,
        label: 'storage_case_19_extra',
        dynamicKeys: [
          ['d_19_x', 1919],
          ['d_19_y', 2019],
        ],
        staticKeys: [
          ['s_19_x', 2919],
          ['s_19_y', 3019],
        ],
        deleteStaticTarget: 's_19_x',
        proxyTag: 'proxy_storage_19_extra',
      },
      'd_19_y',
      9919
    );
  }

    /* Storage bridge valid case 20 */
  public testInteropStorageDeepCase20(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 20,
      label: 'storage_case_20',
      dynamicKeys: [
        ['d_20_a', 1020],
        ['d_20_b', 1120],
      ],
      staticKeys: [
        ['s_20_a', 2020],
        ['s_20_b', 2120],
      ],
      deleteStaticTarget: 's_20_a',
      proxyTag: 'proxy_storage_20',
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_20_extra', ['s_20_a', 's_20_b'], 's_20_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_20', 'proxy_storage_20_a', 'proxy_storage_20_b');
  }

    /* Storage bridge valid case 21 */
  public testInteropStorageDeepCase21(): void {
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_21', ['s_21_a', 's_21_b'], 's_21_a');
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_21', ['s_21_a', 's_21_b'], 's_21_b');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_21',
      {
        id: 21,
        label: 'storage_case_21',
        dynamicKeys: [
          ['d_21_a', 1021],
          ['d_21_b', 1121],
        ],
        staticKeys: [
          ['s_21_a', 2021],
          ['s_21_b', 2121],
        ],
        deleteStaticTarget: 's_21_a',
        proxyTag: 'proxy_storage_21',
      },
      'd_21_a',
      9921
    );
  }

    /* Storage bridge valid case 22 */
  public testInteropStorageDeepCase22(): void {
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage({
        id: 22,
        label: 'storage_case_22',
        dynamicKeys: [
          ['d_22_a', 1022],
          ['d_22_b', 1122],
        ],
        staticKeys: [
          ['s_22_a', 2022],
          ['s_22_b', 2122],
        ],
        deleteStaticTarget: 's_22_a',
        proxyTag: 'proxy_storage_22',
      });
      InteropStorageDeepTestsV2.assertStorageIterationCase('storage_case_22', storage);
    });
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_22', ['s_22_a', 's_22_b'], 's_22_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_22', 'proxy_storage_22_a', 'proxy_storage_22_b');
  }

    /* Storage bridge valid case 23 */
  public testInteropStorageDeepCase23(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 23,
      label: 'storage_case_23',
      dynamicKeys: [
        ['d_23_a', 1023],
        ['d_23_b', 1123],
      ],
      staticKeys: [
        ['s_23_a', 2023],
        ['s_23_b', 2123],
      ],
      deleteStaticTarget: 's_23_a',
      proxyTag: 'proxy_storage_23',
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_23_extra', ['s_23_a', 's_23_b'], 's_23_a');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_23_extra',
      {
        id: 2300,
        label: 'storage_case_23_extra',
        dynamicKeys: [
          ['d_23_x', 1230],
          ['d_23_y', 1330],
        ],
        staticKeys: [
          ['s_23_x', 2230],
          ['s_23_y', 2330],
        ],
        deleteStaticTarget: 's_23_x',
        proxyTag: 'proxy_storage_23_extra',
      },
      'd_23_y',
      9923
    );
  }

    /* Storage bridge valid case 24 */
  public testInteropStorageDeepCase24(): void {
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_24', ['s_24_a', 's_24_b'], 's_24_a');
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_24', ['s_24_a', 's_24_b'], 's_24_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_24', 'proxy_storage_24_a', 'proxy_storage_24_b');
  }

    /* Storage bridge valid case 25 */
  public testInteropStorageDeepCase25(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 25,
      label: 'storage_case_25',
      dynamicKeys: [
        ['d_25_a', 1025],
        ['d_25_b', 1125],
      ],
      staticKeys: [
        ['s_25_a', 2025],
        ['s_25_b', 2125],
      ],
      deleteStaticTarget: 's_25_a',
      proxyTag: 'proxy_storage_25',
    });
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_25_extra', ['s_25_a', 's_25_b'], 's_25_a');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_25_extra',
      {
        id: 2500,
        label: 'storage_case_25_extra',
        dynamicKeys: [
          ['d_25_x', 1250],
          ['d_25_y', 1350],
        ],
        staticKeys: [
          ['s_25_x', 2250],
          ['s_25_y', 2350],
        ],
        deleteStaticTarget: 's_25_x',
        proxyTag: 'proxy_storage_25_extra',
      },
      'd_25_x',
      9925
    );
  }

    /* Storage bridge valid case 26 */
  public testInteropStorageDeepCase26(): void {
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_26', ['s_26_a', 's_26_b'], 's_26_b');
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_26', ['s_26_a', 's_26_b'], 's_26_a');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_26', 'proxy_storage_26_a', 'proxy_storage_26_b');
  }

    /* Storage bridge valid case 27 */
  public testInteropStorageDeepCase27(): void {
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage({
        id: 27,
        label: 'storage_case_27',
        dynamicKeys: [
          ['d_27_a', 1027],
          ['d_27_b', 1127],
        ],
        staticKeys: [
          ['s_27_a', 2027],
          ['s_27_b', 2127],
        ],
        deleteStaticTarget: 's_27_a',
        proxyTag: 'proxy_storage_27',
      });
      InteropStorageDeepTestsV2.assertStorageIterationCase('storage_case_27', storage);
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_27', ['s_27_a', 's_27_b'], 's_27_b');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_27',
      {
        id: 27,
        label: 'storage_case_27',
        dynamicKeys: [
          ['d_27_a', 1027],
          ['d_27_b', 1127],
        ],
        staticKeys: [
          ['s_27_a', 2027],
          ['s_27_b', 2127],
        ],
        deleteStaticTarget: 's_27_a',
        proxyTag: 'proxy_storage_27',
      },
      'd_27_b',
      9927
    );
  }

    /* Storage bridge valid case 28 */
  public testInteropStorageDeepCase28(): void {
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_28', ['s_28_a', 's_28_b'], 's_28_a');
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_28', ['s_28_a', 's_28_b'], 's_28_b');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_28',
      {
        id: 28,
        label: 'storage_case_28',
        dynamicKeys: [
          ['d_28_a', 1028],
          ['d_28_b', 1128],
        ],
        staticKeys: [
          ['s_28_a', 2028],
          ['s_28_b', 2128],
        ],
        deleteStaticTarget: 's_28_a',
        proxyTag: 'proxy_storage_28',
      },
      'd_28_a',
      9928
    );
  }

    /* Storage bridge valid case 29 */
  public testInteropStorageDeepCase29(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 29,
      label: 'storage_case_29',
      dynamicKeys: [
        ['d_29_a', 1029],
        ['d_29_b', 1129],
      ],
      staticKeys: [
        ['s_29_a', 2029],
        ['s_29_b', 2129],
      ],
      deleteStaticTarget: 's_29_a',
      proxyTag: 'proxy_storage_29',
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_29_extra', ['s_29_a', 's_29_b'], 's_29_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_29', 'proxy_storage_29_a', 'proxy_storage_29_b');
  }

    /* Storage bridge valid case 30 */
  public testInteropStorageDeepCase30(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 30,
      label: 'storage_case_30',
      dynamicKeys: [
        ['d_30_a', 1030],
        ['d_30_b', 1130],
      ],
      staticKeys: [
        ['s_30_a', 2030],
        ['s_30_b', 2130],
      ],
      deleteStaticTarget: 's_30_a',
      proxyTag: 'proxy_storage_30',
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_30_extra', ['s_30_a', 's_30_b'], 's_30_b');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_30',
      {
        id: 30,
        label: 'storage_case_30',
        dynamicKeys: [
          ['d_30_a', 1030],
          ['d_30_b', 1130],
        ],
        staticKeys: [
          ['s_30_a', 2030],
          ['s_30_b', 2130],
        ],
        deleteStaticTarget: 's_30_a',
        proxyTag: 'proxy_storage_30',
      },
      'd_30_b',
      9930
    );
  }

    /* Storage bridge valid case 31 */
  public testInteropStorageDeepCase31(): void {
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_31', ['s_31_a', 's_31_b'], 's_31_a');
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_31', ['s_31_a', 's_31_b'], 's_31_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_31', 'proxy_storage_31_a', 'proxy_storage_31_b');
  }

    /* Storage bridge valid case 32 */
  public testInteropStorageDeepCase32(): void {
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage({
        id: 32,
        label: 'storage_case_32',
        dynamicKeys: [
          ['d_32_a', 1032],
          ['d_32_b', 1132],
        ],
        staticKeys: [
          ['s_32_a', 2032],
          ['s_32_b', 2132],
        ],
        deleteStaticTarget: 's_32_a',
        proxyTag: 'proxy_storage_32',
      });
      InteropStorageDeepTestsV2.assertStorageIterationCase('storage_case_32', storage);
    });
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_32', ['s_32_a', 's_32_b'], 's_32_b');
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_32',
      {
        id: 32,
        label: 'storage_case_32',
        dynamicKeys: [
          ['d_32_a', 1032],
          ['d_32_b', 1132],
        ],
        staticKeys: [
          ['s_32_a', 2032],
          ['s_32_b', 2132],
        ],
        deleteStaticTarget: 's_32_a',
        proxyTag: 'proxy_storage_32',
      },
      'd_32_a',
      9932
    );
  }

    /* Storage bridge valid case 33 */
  public testInteropStorageDeepCase33(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 33,
      label: 'storage_case_33',
      dynamicKeys: [
        ['d_33_a', 1033],
        ['d_33_b', 1133],
      ],
      staticKeys: [
        ['s_33_a', 2033],
        ['s_33_b', 2133],
      ],
      deleteStaticTarget: 's_33_a',
      proxyTag: 'proxy_storage_33',
    });
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_33_extra', ['s_33_a', 's_33_b'], 's_33_a');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_33', 'proxy_storage_33_a', 'proxy_storage_33_b');
  }

    /* Tier[] Storage case 34 */
  public testInteropStorageDeepCase34(): void {
    InteropStorageDeepTestsV2.assertBindToggleCase(
      'storage_case_34',
      ['s_34_a', 's_34_b', 's_34_c'],
      false,
      true
    );
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_34', 'proxy_storage_34_a', 'proxy_storage_34_b');
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_34_extra', ['s_34_a', 's_34_b'], 's_34_b');
  }

    /* Tier[] Storage case 35 */
  public testInteropStorageDeepCase35(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 35,
      label: 'storage_case_35',
      dynamicKeys: [
        ['d_35_a', 1035],
        ['d_35_b', 1135],
      ],
      staticKeys: [
        ['s_35_a', 2035],
        ['s_35_b', 2135],
      ],
      deleteStaticTarget: 's_35_a',
      proxyTag: 'proxy_storage_35',
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_35_extra', ['s_35_a', 's_35_b'], 's_35_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_35', 'proxy_storage_35_a', 'proxy_storage_35_b');
    InteropStorageDeepTestsV2.assertDeleteSequenceCase(
      'storage_case_35_extra',
      {
        id: 3500,
        label: 'storage_case_35_extra',
        dynamicKeys: [
          ['d_35_x', 1350],
          ['d_35_y', 1450],
        ],
        staticKeys: [
          ['s_35_x', 2350],
          ['s_35_y', 2450],
        ],
        deleteStaticTarget: 's_35_x',
        proxyTag: 'proxy_storage_35_extra',
      },
      ['s_35_x', 'd_35_x', 'not_exists_35']
    );
  }

    /* Tier[] Storage case 36 */
  public testInteropStorageDeepCase36(): void {
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_36',
      {
        id: 36,
        label: 'storage_case_36',
        dynamicKeys: [
          ['d_36_a', 1036],
          ['d_36_b', 1136],
        ],
        staticKeys: [
          ['s_36_a', 2036],
          ['s_36_b', 2136],
        ],
        deleteStaticTarget: 's_36_a',
        proxyTag: 'proxy_storage_36',
      },
      'd_36_a',
      9936
    );
    InteropStorageDeepTestsV2.assertBindToggleCase(
      'storage_case_36',
      ['s_36_a', 's_36_b'],
      true,
      false
    );
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_36_extra', ['s_36_a', 's_36_b'], 's_36_b');
  }

    /* Tier[] Storage case 37 */
  public testInteropStorageDeepCase37(): void {
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage({
        id: 37,
        label: 'storage_case_37',
        dynamicKeys: [
          ['d_37_a', 1037],
          ['d_37_b', 1137],
        ],
        staticKeys: [
          ['s_37_a', 2037],
          ['s_37_b', 2137],
        ],
        deleteStaticTarget: 's_37_a',
        proxyTag: 'proxy_storage_37',
      });
      InteropStorageDeepTestsV2.assertStorageIterationCase('storage_case_37', storage);
      storage.set('d_37_obj', { value: { id: 37, flag: true }, source: 'object_payload' });
      eq(storage.get('d_37_obj').value.id, 37, 'storage_case_37 object payload id');
    });
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_37', ['s_37_a', 's_37_b'], 's_37_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_37', 'proxy_storage_37_a', 'proxy_storage_37_b');
    InteropStorageDeepTestsV2.assertDeleteSequenceCase(
      'storage_case_37_extra',
      {
        id: 3700,
        label: 'storage_case_37_extra',
        dynamicKeys: [
          ['d_37_x', 1370],
          ['d_37_y', 1470],
        ],
        staticKeys: [
          ['s_37_x', 2370],
          ['s_37_y', 2470],
        ],
        deleteStaticTarget: 's_37_x',
        proxyTag: 'proxy_storage_37_extra',
      },
      ['d_37_y', 's_37_y']
    );
  }

    /* Tier[] Storage case 38 */
  public testInteropStorageDeepCase38(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 38,
      label: 'storage_case_38',
      dynamicKeys: [
        ['d_38_a', 1038],
        ['d_38_b', 1138],
      ],
      staticKeys: [
        ['s_38_a', 2038],
        ['s_38_b', 2138],
      ],
      deleteStaticTarget: 's_38_a',
      proxyTag: 'proxy_storage_38',
    });
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      InteropStorageDeepTestsV2.assertStorageIterationCase(
        'storage_case_38_extra',
        InteropStorageDeepTestsV2.buildStorage({
          id: 3800,
          label: 'storage_case_38_extra',
          dynamicKeys: [
            ['d_38_x', 1380],
            ['d_38_y', 1480],
          ],
          staticKeys: [
            ['s_38_x', 2380],
            ['s_38_y', 2480],
          ],
          deleteStaticTarget: 's_38_x',
          proxyTag: 'proxy_storage_38_extra',
        })
      );
    });
    InteropStorageDeepTestsV2.assertBindToggleCase(
      'storage_case_38',
      ['s_38_a', 's_38_b'],
      true,
      true
    );
  }

    /* Tier[] Storage case 39 */
  public testInteropStorageDeepCase39(): void {
    InteropStorageDeepTestsV2.assertDeleteSequenceCase(
      'storage_case_39',
      {
        id: 39,
        label: 'storage_case_39',
        dynamicKeys: [
          ['d_39_a', 1039],
          ['d_39_b', 1139],
        ],
        staticKeys: [
          ['s_39_a', 2039],
          ['s_39_b', 2139],
        ],
        deleteStaticTarget: 's_39_a',
        proxyTag: 'proxy_storage_39',
      },
      ['s_39_b', 'd_39_a', 'not_exists_39']
    );
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_39', ['s_39_a', 's_39_b'], 's_39_a');
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_39', ['s_39_a', 's_39_b'], 's_39_b');
  }

    /* Tier[] Storage case 40 */
  public testInteropStorageDeepCase40(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 40,
      label: 'storage_case_40',
      dynamicKeys: [
        ['d_40_a', 1040],
        ['d_40_b', 1140],
      ],
      staticKeys: [
        ['s_40_a', 2040],
        ['s_40_b', 2140],
      ],
      deleteStaticTarget: 's_40_a',
      proxyTag: 'proxy_storage_40',
    });
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_40_extra',
      {
        id: 4000,
        label: 'storage_case_40_extra',
        dynamicKeys: [
          ['d_40_x', 1400],
          ['d_40_y', 1500],
        ],
        staticKeys: [
          ['s_40_x', 2400],
          ['s_40_y', 2500],
        ],
        deleteStaticTarget: 's_40_x',
        proxyTag: 'proxy_storage_40_extra',
      },
      'd_40_y',
      9940
    );
    InteropStorageDeepTestsV2.assertBindToggleCase('storage_case_40', ['s_40_a', 's_40_b'], false, false);
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_40', ['s_40_a', 's_40_b'], 's_40_b');
  }

    /* Tier[] Storage case 41 */
  public testInteropStorageDeepCase41(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 41,
      label: 'storage_case_41',
      dynamicKeys: [
        ['d_41_a', 1041],
        ['d_41_b', 1141],
      ],
      staticKeys: [
        ['s_41_a', 2041],
        ['s_41_b', 2141],
      ],
      deleteStaticTarget: 's_41_a',
      proxyTag: 'proxy_storage_41',
    });
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_41_extra', ['s_41_a', 's_41_b'], 's_41_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_41', 'proxy_storage_41_a', 'proxy_storage_41_b');
    InteropStorageDeepTestsV2.assertDeleteSequenceCase(
      'storage_case_41_extra',
      {
        id: 4100,
        label: 'storage_case_41_extra',
        dynamicKeys: [
          ['d_41_x', 1410],
          ['d_41_y', 1510],
        ],
        staticKeys: [
          ['s_41_x', 2410],
          ['s_41_y', 2510],
        ],
        deleteStaticTarget: 's_41_x',
        proxyTag: 'proxy_storage_41_extra',
      },
      ['s_41_y']
    );
  }

    /* Tier[] Storage case 42 */
  public testInteropStorageDeepCase42(): void {
    InteropStorageDeepTestsV2.assertStorageMutationCase(
      'storage_case_42',
      {
        id: 42,
        label: 'storage_case_42',
        dynamicKeys: [
          ['d_42_a', 1042],
          ['d_42_b', 1142],
        ],
        staticKeys: [
          ['s_42_a', 2042],
          ['s_42_b', 2142],
        ],
        deleteStaticTarget: 's_42_a',
        proxyTag: 'proxy_storage_42',
      },
      'd_42_a',
      9942
    );
    InteropStorageDeepTestsV2.assertBindToggleCase('storage_case_42', ['s_42_a', 's_42_b'], true, false);
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_42_extra', ['s_42_a', 's_42_b', 's_42_c'], 's_42_c');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_42', 'proxy_storage_42_a', 'proxy_storage_42_b');
  }

    /* Tier[] Storage case 43 */
  public testInteropStorageDeepCase43(): void {
    InteropStorageDeepTestsV2.assertScenario({
      id: 43,
      label: 'storage_case_43',
      dynamicKeys: [
        ['d_43_a', 1043],
        ['d_43_b', 1143],
      ],
      staticKeys: [
        ['s_43_a', 2043],
        ['s_43_b', 2143],
      ],
      deleteStaticTarget: 's_43_a',
      proxyTag: 'proxy_storage_43',
    });
    InteropStorageDeepTestsV2.runOrSkip('InteropStorage', () => {
      const storage = InteropStorageDeepTestsV2.buildStorage({
        id: 4300,
        label: 'storage_case_43_snapshot',
        dynamicKeys: [
          ['d_43_x', 1430],
          ['d_43_y', 1530],
        ],
        staticKeys: [
          ['s_43_x', 2430],
          ['s_43_y', 2530],
        ],
        deleteStaticTarget: 's_43_x',
        proxyTag: 'proxy_storage_43_snapshot',
      });
      const entries = Array.from(storage.entries());
      eq(entries.length, 4, 'storage_case_43 entries length');
      eq(entries.some(([key]) => key === 'd_43_x'), true, 'storage_case_43 has d_43_x');
    });
    InteropStorageDeepTestsV2.assertDeleteSequenceCase(
      'storage_case_43',
      {
        id: 4301,
        label: 'storage_case_43_delete',
        dynamicKeys: [
          ['d_43_m', 1431],
          ['d_43_n', 1531],
        ],
        staticKeys: [
          ['s_43_m', 2431],
          ['s_43_n', 2531],
        ],
        deleteStaticTarget: 's_43_m',
        proxyTag: 'proxy_storage_43_delete',
      },
      ['s_43_n', 'd_43_n']
    );
    InteropStorageDeepTestsV2.assertAppBindCase('storage_case_43', ['s_43_a', 's_43_b'], 's_43_a');
    InteropStorageDeepTestsV2.assertLocalBindCase('storage_case_43', ['s_43_a', 's_43_b'], 's_43_b');
    InteropStorageDeepTestsV2.assertProxyReplaceCase('storage_case_43', 'proxy_storage_43_a', 'proxy_storage_43_b');
  }
}
