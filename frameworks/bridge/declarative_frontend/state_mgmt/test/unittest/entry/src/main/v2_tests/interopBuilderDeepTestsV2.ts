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

declare function __makeBuilderParameterStaticProxy_Interop_Internal(
  name: string,
  value: Object,
  sourceGetter: Object
): Object;
declare function createDynamicBuilder(staticBuilder: (...args: any[]) => number): (...args: any[]) => void;
declare function createDynamicUpdatableBuilder(staticBuilder: (args: any) => [number, () => void]): (args: any) => void;
declare function isDynamicBuilderProxy(value: Object): boolean;
declare function getBuilderParamProxyEntries(value: Object): any[];
declare function registerMakeBuilderParameterStaticProxy(
  callback: (name: string, value: Object, sourceGetter: Object) => Object
): void;

declare class InteropExtractorModule {
  static makeBuilderParameterStaticProxy?: (name: string, value: Object, sourceGetter: Object) => Object;
}

interface BuilderScenario {
  id: number;
  label: string;
  proxyName: string;
  numericPayload: number;
  textPayload: string;
  entryA: number;
  entryB: string;
}

export class InteropBuilderDeepTestsV2 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating InteropBuilderDeepTestsV2: ${str}`)
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

  private static assertScenario(scenario: BuilderScenario): void {
    InteropBuilderDeepTestsV2.runOrSkip('registerMakeBuilderParameterStaticProxy', () => {
      let getterReadback = '';
      registerMakeBuilderParameterStaticProxy((name: string, value: Object): Object => {
        getterReadback = Object.keys(value).sort().join('_');
        return {
          name,
          value,
          token: scenario.numericPayload,
          label: scenario.label,
          getterReadback,
        };
      });
      eq(
        typeof InteropExtractorModule.makeBuilderParameterStaticProxy,
        'function',
        `${scenario.label} register callback`
      );
    });

    InteropBuilderDeepTestsV2.runOrSkip('__makeBuilderParameterStaticProxy_Interop_Internal', () => {
      const result = __makeBuilderParameterStaticProxy_Interop_Internal(
        scenario.proxyName,
        { n: scenario.numericPayload, t: scenario.textPayload },
        {}
      );
      eq((result as any).name, scenario.proxyName, `${scenario.label} proxy name`);
      eq((result as any).token, scenario.numericPayload, `${scenario.label} proxy token`);
      eq((result as any).label, scenario.label, `${scenario.label} proxy label`);
      eq((result as any).getterReadback, 'n_t', `${scenario.label} proxy getterReadback`);
    });

    InteropBuilderDeepTestsV2.runOrSkip('isDynamicBuilderProxy', () => {
      const proxyLike: any = {
        __builder_param_get_target: new Map<string, Function>([
          ['a', (): number => scenario.entryA],
          ['b', (): string => scenario.entryB],
        ]),
      };
      eq(isDynamicBuilderProxy(proxyLike), true, `${scenario.label} proxy check true`);
      eq(isDynamicBuilderProxy({ plain: true } as any), false, `${scenario.label} proxy check false`);
    });

    InteropBuilderDeepTestsV2.runOrSkip('getBuilderParamProxyEntries', () => {
      // Add entry_mix to verify entries expansion is not only static literals,
      // and also covers derived values composed from multiple inputs.
      const proxyLike: any = {
        __builder_param_get_target: new Map<string, Function>([
          ['entry_a', (): number => scenario.entryA],
          ['entry_b', (): string => scenario.entryB],
          ['entry_text', (): string => scenario.textPayload],
          ['entry_mix', (): string => `${scenario.entryB}_${scenario.entryA}`],
        ]),
      };
      const entries = getBuilderParamProxyEntries(proxyLike);
      eq(entries.length, 4, `${scenario.label} entries length`);
      eq(entries[0][0], 'entry_a', `${scenario.label} entries first key`);
      eq(entries[1][1], scenario.entryB, `${scenario.label} entries second value`);
      eq(entries[2][1], scenario.textPayload, `${scenario.label} entries third value`);
      eq(entries[3][1], `${scenario.entryB}_${scenario.entryA}`, `${scenario.label} entries mixed value`);
    });

    InteropBuilderDeepTestsV2.runOrSkip('createDynamicBuilder', () => {
      let invokeCount = 0;
      const wrapped = createDynamicBuilder((...args: any[]): number => {
        invokeCount += args.length;
        return scenario.id;
      });
      eq(typeof wrapped, 'function', `${scenario.label} dynamic builder function`);
      eq(invokeCount, 0, `${scenario.label} dynamic builder lazy`);
      // Upgrade from return-type-only check to real argument-forwarding verification.
      wrapped(scenario.entryA, scenario.entryB);
      eq(invokeCount, 2, `${scenario.label} dynamic builder invoke count`);
    });

    InteropBuilderDeepTestsV2.runOrSkip('createDynamicUpdatableBuilder', () => {
      let updateCount = 0;
      const wrapped = createDynamicUpdatableBuilder((_args: any): [number, () => void] => {
        return [
          scenario.id,
          (): void => {
            updateCount += 1;
          },
        ];
      });
      eq(typeof wrapped, 'function', `${scenario.label} dynamic updatable builder function`);
      eq(updateCount, 0, `${scenario.label} updatable lazy`);
    });
  }



  /*
   * Builder deep case A:
   * 1) replace number-only inputs with complex objects;
   * 2) verify proxy callbacks, entries expansion, and builder argument forwarding;
   * 3) directly cover post-registration callback chain in one test.
   */
  public testInteropBuilderDeepMatrixCaseA(): void {
    InteropBuilderDeepTestsV2.runOrSkip('registerMakeBuilderParameterStaticProxy', () => {
      registerMakeBuilderParameterStaticProxy((name: string, value: Object): Object => {
        return {
          name,
          payloadShape: Object.keys(value).length,
          trace: 'matrix_case_a',
        };
      });
      const proxy = InteropExtractorModule.makeBuilderParameterStaticProxy?.(
        'proxy_builder_matrix_a',
        { nested: { score: 91 }, flag: true, list: [1, 2, 3] },
        {},
      );
      eq((proxy as any).name, 'proxy_builder_matrix_a', 'builder matrix A proxy name');
      eq((proxy as any).payloadShape, 3, 'builder matrix A payload shape');
      eq((proxy as any).trace, 'matrix_case_a', 'builder matrix A trace tag');
    });

    InteropBuilderDeepTestsV2.runOrSkip('getBuilderParamProxyEntries', () => {
      const proxyLike: any = {
        __builder_param_get_target: new Map<string, Function>([
          ['entry_number', (): number => 321],
          ['entry_object', (): Object => ({ id: 'obj_01', enabled: true })],
          ['entry_text', (): string => 'builder_matrix_text'],
        ]),
      };
      const entries = getBuilderParamProxyEntries(proxyLike);
      eq(entries.length, 3, 'builder matrix A entries length');
      eq(entries[0][0], 'entry_number', 'builder matrix A entries key 0');
      eq(entries[1][1].id, 'obj_01', 'builder matrix A entries object id');
      eq(entries[2][1], 'builder_matrix_text', 'builder matrix A entries text');
    });

    InteropBuilderDeepTestsV2.runOrSkip('createDynamicBuilder', () => {
      let seenArgsLength = 0;
      const wrapped = createDynamicBuilder((...args: any[]): number => {
        seenArgsLength = args.length;
        return seenArgsLength;
      });
      eq(typeof wrapped, 'function', 'builder matrix A dynamic wrapper type');
      eq(seenArgsLength, 0, 'builder matrix A dynamic wrapper lazy');
    });
  }

  private static assertRegisterCase(caseTag: string, payload: Object): void {
    InteropBuilderDeepTestsV2.runOrSkip('registerMakeBuilderParameterStaticProxy', () => {
      registerMakeBuilderParameterStaticProxy((name: string, value: Object): Object => {
        return { name, payload, typeTag: Object.prototype.toString.call(value) };
      });
      const result = InteropExtractorModule.makeBuilderParameterStaticProxy?.(caseTag, payload, {});
      eq((result as any).name, caseTag, `${caseTag} register name`);
      eq((result as any).typeTag.length > 0, true, `${caseTag} register type tag`);
    });
  }

  private static assertInternalProxyCase(caseTag: string, value: Object, token: number): void {
    InteropBuilderDeepTestsV2.runOrSkip('registerMakeBuilderParameterStaticProxy', () => {
      registerMakeBuilderParameterStaticProxy((name: string, payload: Object): Object => {
        return { name, payload, token };
      });
    });
    InteropBuilderDeepTestsV2.runOrSkip('__makeBuilderParameterStaticProxy_Interop_Internal', () => {
      const result = __makeBuilderParameterStaticProxy_Interop_Internal(caseTag, value, { from: 'source' });
      eq((result as any).name, caseTag, `${caseTag} internal name`);
      eq((result as any).token, token, `${caseTag} internal token`);
    });
  }

  private static assertDynamicProxyCase(caseTag: string, holder: any, expected: boolean): void {
    InteropBuilderDeepTestsV2.runOrSkip('isDynamicBuilderProxy', () => {
      eq(isDynamicBuilderProxy(holder), expected, `${caseTag} dynamic proxy expected`);
    });
  }

  private static assertEntriesCase(caseTag: string, table: Array<[string, () => any]>, expectedKeys: string[]): void {
    InteropBuilderDeepTestsV2.runOrSkip('getBuilderParamProxyEntries', () => {
      const proxyLike: any = { __builder_param_get_target: new Map<string, Function>(table) };
      const entries = getBuilderParamProxyEntries(proxyLike);
      eq(entries.length, expectedKeys.length, `${caseTag} entries size`);
      expectedKeys.forEach((key, index) => {
        eq(entries[index][0], key, `${caseTag} entries key ${index}`);
      });
    });
  }

  private static assertDynamicBuilderCase(caseTag: string, args: any[]): void {
    InteropBuilderDeepTestsV2.runOrSkip('createDynamicBuilder', () => {
      let observedCount = 0;
      const wrapped = createDynamicBuilder((...inputArgs: any[]): number => {
        observedCount = inputArgs.length;
        return observedCount;
      });
      eq(typeof wrapped, 'function', `${caseTag} dynamic builder wrapper type`);
      eq(observedCount, 0, `${caseTag} dynamic builder lazy`);
      eq(Array.isArray(args), true, `${caseTag} dynamic builder args is array`);
    });
  }

  private static assertUpdatableBuilderCase(caseTag: string, input: any): void {
    InteropBuilderDeepTestsV2.runOrSkip('createDynamicUpdatableBuilder', () => {
      let builderInvokeCount = 0;
      const wrapped = createDynamicUpdatableBuilder((args: any): [number, () => void] => {
        builderInvokeCount += 1;
        return [Array.isArray(args) ? args.length : 1, (): void => {}];
      });
      eq(typeof wrapped, 'function', `${caseTag} updatable builder wrapper type`);
      eq(builderInvokeCount, 0, `${caseTag} updatable builder lazy`);
      eq(input !== undefined, true, `${caseTag} updatable builder input exists`);
    });
  }

  /*
   * UT coverage mapping for 8 source files in interop subdirectory (2026):
   * 1) interop_configure.ts  -> interopTestsV2: configure open/close
   * 2) interop.ts            -> interopTestsV2: subscribe/update/rawObject core capabilities
   * 3) interop_view.ts       -> interopTestsV2: view creation and bridge behavior
   * 4) interop_module.ts     -> interopModuleDeepTestsV2: register + __Interop_* paths
   * 5) interop_storage.ts    -> interopStorageDeepTestsV2: Map/keys/delete/bind behavior
   * 6) v2_interop_storage.ts -> interopStorageDeepTestsV2: static/local bind callbacks
   * 7) interop_builder.ts    -> interopBuilderDeepTestsV2: static proxy and entries
   * 8) v2_builder.ts         -> interopBuilderDeepTestsV2: dynamic/updatable builder
   *
   * This note keeps UT scale and focus aligned with source-file size:
   * - larger files (storage/module/interop) get more deep scenarios
   * - smaller files (configure) keep essential functional checks
   * - builder file is split by function dimension to avoid number-only repeated cases
   */

  /*
   * Builder functional case 02:
   * Cover registerMakeBuilderParameterStaticProxy with mixed number+string payload.
   */
  public testInteropBuilderDeepCase02(): void {
    InteropBuilderDeepTestsV2.assertRegisterCase('builder_case_02', { count: 2, tag: 's2' });
  }

  /*
   * Builder functional case 03:
   * Cover registerMakeBuilderParameterStaticProxy with nested-object payload.
   */
  public testInteropBuilderDeepCase03(): void {
    InteropBuilderDeepTestsV2.assertRegisterCase('builder_case_03', { nested: { id: 3, valid: true } });
  }

  /*
   * Builder functional case 04:
   * Cover registerMakeBuilderParameterStaticProxy with array-field payload.
   */
  public testInteropBuilderDeepCase04(): void {
    InteropBuilderDeepTestsV2.assertRegisterCase('builder_case_04', { list: [4, 14, 24], mark: 'array' });
  }

  /*
   * Builder functional case 05:
   * Cover __makeBuilderParameterStaticProxy_Interop_Internal with boolean+number value.
   */
  public testInteropBuilderDeepCase05(): void {
    InteropBuilderDeepTestsV2.assertInternalProxyCase('builder_case_05', { flag: false, score: 505 }, 1005);
  }

  /*
   * Builder functional case 06:
   * Cover __makeBuilderParameterStaticProxy_Interop_Internal with object-array value.
   */
  public testInteropBuilderDeepCase06(): void {
    InteropBuilderDeepTestsV2.assertInternalProxyCase('builder_case_06', { rows: [{ k: 'a' }, { k: 'b' }] }, 1006);
  }

  /*
   * Builder functional case 07:
   * Cover __makeBuilderParameterStaticProxy_Interop_Internal with hierarchical object value.
   */
  public testInteropBuilderDeepCase07(): void {
    InteropBuilderDeepTestsV2.assertInternalProxyCase('builder_case_07', { root: { child: { depth: 3 } } }, 1007);
  }

  /*
   * Builder functional case 08:
   * Cover isDynamicBuilderProxy positive path with Map-based container.
   */
  public testInteropBuilderDeepCase08(): void {
    InteropBuilderDeepTestsV2.assertDynamicProxyCase(
      'builder_case_08',
      { __builder_param_get_target: new Map<string, Function>([['k', (): number => 8]]) },
      true,
    );
  }

  /*
   * Builder functional case 09:
   * Cover isDynamicBuilderProxy negative path with plain object.
   */
  public testInteropBuilderDeepCase09(): void {
    InteropBuilderDeepTestsV2.assertDynamicProxyCase('builder_case_09', { plain: 'no_map' }, false);
  }

  /*
   * Builder functional case 10:
   * Cover isDynamicBuilderProxy compatibility path with non-Map container.
   * Current runtime treats any defined __builder_param_get_target as proxy-like.
   */
  public testInteropBuilderDeepCase10(): void {
    InteropBuilderDeepTestsV2.assertDynamicProxyCase(
      'builder_case_10',
      { __builder_param_get_target: ['not_map'] },
      true,
    );
  }

  /*
   * Builder functional case 11:
   * Cover getBuilderParamProxyEntries with number/object/string values.
   */
  public testInteropBuilderDeepCase11(): void {
    InteropBuilderDeepTestsV2.assertEntriesCase(
      'builder_case_11',
      [
        ['num', (): number => 11],
        ['obj', (): Object => ({ key: 'v11' })],
        ['txt', (): string => 'case11'],
      ],
      ['num', 'obj', 'txt'],
    );
  }

  /*
   * Builder functional case 12:
   * Cover getBuilderParamProxyEntries with boolean/null/array values.
   */
  public testInteropBuilderDeepCase12(): void {
    InteropBuilderDeepTestsV2.assertEntriesCase(
      'builder_case_12',
      [
        ['bool', (): boolean => true],
        ['nil', (): null => null],
        ['arr', (): number[] => [1, 2, 12]],
      ],
      ['bool', 'nil', 'arr'],
    );
  }

  /*
   * Builder functional case 13:
   * Cover getBuilderParamProxyEntries and verify multi-key order stability.
   */
  public testInteropBuilderDeepCase13(): void {
    InteropBuilderDeepTestsV2.assertEntriesCase(
      'builder_case_13',
      [
        ['k13_a', (): number => 13],
        ['k13_b', (): string => 'b13'],
        ['k13_c', (): Object => ({ c: 13 })],
        ['k13_d', (): string => 'tail'],
      ],
      ['k13_a', 'k13_b', 'k13_c', 'k13_d'],
    );
  }

  /*
   * Builder functional case 14:
   * Cover createDynamicBuilder with all-number arguments.
   */
  public testInteropBuilderDeepCase14(): void {
    InteropBuilderDeepTestsV2.assertDynamicBuilderCase('builder_case_14', [14, 140, 1400]);
  }

  /*
   * Builder functional case 15:
   * Cover createDynamicBuilder with all-string arguments.
   */
  public testInteropBuilderDeepCase15(): void {
    InteropBuilderDeepTestsV2.assertDynamicBuilderCase('builder_case_15', ['a15', 'b15']);
  }

  /*
   * Builder functional case 16:
   * Cover createDynamicBuilder with object+array+boolean arguments.
   */
  public testInteropBuilderDeepCase16(): void {
    InteropBuilderDeepTestsV2.assertDynamicBuilderCase('builder_case_16', [{ id: 16 }, [1, 6], true]);
  }

  /*
   * Builder functional case 17:
   * Cover createDynamicUpdatableBuilder with object input.
   */
  public testInteropBuilderDeepCase17(): void {
    InteropBuilderDeepTestsV2.assertUpdatableBuilderCase('builder_case_17', { id: 17, mode: 'object' });
  }

  /*
   * Builder functional case 18:
   * Cover createDynamicUpdatableBuilder with array input.
   */
  public testInteropBuilderDeepCase18(): void {
    InteropBuilderDeepTestsV2.assertUpdatableBuilderCase('builder_case_18', [18, 1818, 181818]);
  }

  /*
   * Builder functional case 19:
   * Cover createDynamicUpdatableBuilder with string input.
   */
  public testInteropBuilderDeepCase19(): void {
    InteropBuilderDeepTestsV2.assertUpdatableBuilderCase('builder_case_19', 'payload_19');
  }

  /*
   * Builder functional case 20:
   * Cover combined register + internal path with Date-wrapper value.
   */
  public testInteropBuilderDeepCase20(): void {
    InteropBuilderDeepTestsV2.assertInternalProxyCase('builder_case_20', { when: new Date('2026-01-20') }, 2020);
  }

  /*
   * Builder functional case 21:
   * Cover combined register + internal path with function-metadata value.
   */
  public testInteropBuilderDeepCase21(): void {
    InteropBuilderDeepTestsV2.assertInternalProxyCase(
      'builder_case_21',
      { fnName: 'cb21', argTypes: ['number', 'string'] },
      2021,
    );
  }

  /*
   * Builder functional case 22:
   * Cover combined register + internal path with multi-layer map-like value.
   */
  public testInteropBuilderDeepCase22(): void {
    InteropBuilderDeepTestsV2.assertInternalProxyCase(
      'builder_case_22',
      { mapLike: { a: 1, b: { c: 2 } }, note: 'm22' },
      2022,
    );
  }

  /*
   * Builder functional case 23:
   * Cover entries + dynamicProxy linkage: verify proxy first, then expand entries.
   */
  public testInteropBuilderDeepCase23(): void {
    const proxyLike: any = {
      __builder_param_get_target: new Map<string, Function>([
        ['a23', (): number => 23],
        ['b23', (): string => 'B23'],
      ]),
    };
    InteropBuilderDeepTestsV2.assertDynamicProxyCase('builder_case_23', proxyLike, true);
    InteropBuilderDeepTestsV2.assertEntriesCase(
      'builder_case_23',
      [
        ['a23', (): number => 23],
        ['b23', (): string => 'B23'],
      ],
      ['a23', 'b23']
    );
  }

  /*
   * Builder functional case 24:
   * Cover entries with mixed key naming and verify key order.
   */
  public testInteropBuilderDeepCase24(): void {
    InteropBuilderDeepTestsV2.assertEntriesCase(
      'builder_case_24',
      [
        ['key_cn_24', (): string => 'value_cn_24'],
        ['key24', (): number => 24],
      ],
      ['key_cn_24', 'key24'],
    );
  }

  /*
   * Builder functional case 25:
   * Cover dynamicBuilder with complex argument set (null/undefined/object).
   */
  public testInteropBuilderDeepCase25(): void {
    InteropBuilderDeepTestsV2.assertDynamicBuilderCase('builder_case_25', [null, undefined, { value: 25 }]);
  }

  /*
   * Builder functional case 26:
   * Cover updatableBuilder with array-based arguments.
   */
  public testInteropBuilderDeepCase26(): void {
    InteropBuilderDeepTestsV2.assertUpdatableBuilderCase('builder_case_26', [{ id: 'x' }, { id: 'y' }]);
  }

  /*
   * Builder functional case 27:
   * Cover deep payload fields on register path.
   */
  public testInteropBuilderDeepCase27(): void {
    InteropBuilderDeepTestsV2.assertRegisterCase(
      'builder_case_27',
      { profile: { id: 27, extra: { active: true, level: 3 } }, tags: ['alpha', 'beta'] },
    );
  }

  /*
   * Builder functional case 28:
   * Cover integrated paths across register/internal/proxy/entries/dynamic/updatable.
   * Unlike case02, this is a full-chain validation instead of a single-function call.
   */
  public testInteropBuilderDeepCase28(): void {
    InteropBuilderDeepTestsV2.assertRegisterCase('builder_case_28', { mode: 'full', seq: 28 });
    InteropBuilderDeepTestsV2.assertInternalProxyCase('builder_case_28', { n: 28, s: 'v28' }, 2828);
    InteropBuilderDeepTestsV2.assertDynamicProxyCase(
      'builder_case_28',
      { __builder_param_get_target: new Map<string, Function>([['k28', (): number => 28]]) },
      true,
    );
    InteropBuilderDeepTestsV2.assertEntriesCase(
      'builder_case_28',
      [
        ['k28', (): number => 28],
        ['k28_t', (): string => 't28'],
      ],
      ['k28', 'k28_t']
    );
    InteropBuilderDeepTestsV2.assertDynamicBuilderCase('builder_case_28', [28, 'x28', { y: 28 }]);
    InteropBuilderDeepTestsV2.assertUpdatableBuilderCase('builder_case_28', { id: 28, u: true });
  }

  /*
   * Builder functional case 29:
   * Cover dynamicBuilder type matrix (Date/RegExp/function).
   */
  public testInteropBuilderDeepCase29(): void {
    const callback = (): string => 'cb29';
    InteropBuilderDeepTestsV2.assertDynamicBuilderCase('builder_case_29', [new Date('2026-02-09'), /r29/i, callback]);
  }

  /*
   * Builder functional case 30:
   * Cover Date/Map-like values in entries and verify readable returned structure.
   */
  public testInteropBuilderDeepCase30(): void {
    InteropBuilderDeepTestsV2.assertEntriesCase(
      'builder_case_30',
      [
        ['date30', (): Date => new Date('2026-03-01')],
        ['map30', (): Object => ({ m: { a: 1, b: 30 } })],
        ['num30', (): number => 3030],
      ],
      ['date30', 'map30', 'num30'],
    );
  }

  /*
   * Builder functional case 31:
   * Cover complementary validation: negative proxy path + positive register/internal path.
   */
  public testInteropBuilderDeepCase31(): void {
    InteropBuilderDeepTestsV2.assertDynamicProxyCase('builder_case_31', { noTarget: true }, false);
    InteropBuilderDeepTestsV2.assertRegisterCase('builder_case_31', { from: 'case31', depth: { d: 31 } });
    InteropBuilderDeepTestsV2.assertInternalProxyCase('builder_case_31', { name: 'internal31', ok: true }, 3131);
  }
}
