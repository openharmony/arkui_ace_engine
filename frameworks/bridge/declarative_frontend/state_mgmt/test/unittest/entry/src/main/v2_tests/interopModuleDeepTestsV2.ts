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

import { eq, ITestFile } from '../lib/testRunner'

declare class InteropExtractorModule {
  static createWatchFunc?: (watchFuncCallback: (propertyName: string) => void, newValue: Object) => any;
  static makeObserved?: (value: Object) => Object;
  static compatibleStaticComponent?: (
    factory: () => Object,
    options?: () => Object,
    content?: () => void
  ) => [() => void, number];
  static makeBuilderParameterStaticProxy?: (name: string, value: Object, sourceGetter: Object) => Object;
  static updateInteropExtendableComponent?: (dynamicComponent: any) => void;
  static resetInteropExtendableComponent?: () => void;
  static transferCompatibleBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
  static transferCompatibleDynamicBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
  static createCompatibleStaticState?: (value: Object) => Object;
  static transferCompatibleUpdatableBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
}

declare function registerCallbackForCreateWatchID(callback: (...args: any[]) => any): void;
declare function registerCallbackForMakeObserved(callback: (value: Object) => Object): void;
declare function registerCompatibleStaticComponentCallback(
  callback: (
    factory: () => Object,
    options?: () => Object,
    content?: () => void
  ) => [() => void, number]
): void;
declare function registerMakeBuilderParameterStaticProxy(callback: (name: string, value: Object, sourceGetter: Object) => Object): void;
declare function registerUpdateInteropExtendableComponent(callback: (dynamicComponent: Object) => void): void;
declare function registerResetInteropExtendableComponent(callback: () => void): void;
declare function registerTransferCompatibleBuilderCallback(
  callback: (builder: (...args: any[]) => void) => (...args: any[]) => void
): void;
declare function registerTransferCompatibleDynamicBuilderCallback(
  callback: (builder: (...args: any[]) => void) => (...args: any[]) => void
): void;
declare function registerCreateCompatibleStaticState(callback: (value: Object) => Object): void;
declare function registerTransferCompatibleUpdatableBuilderCallback(
  callback: (builder: (...args: any[]) => void) => (...args: any[]) => void
): void;

declare function __Interop_CreateStaticComponent_Internal(
  factory: () => Object,
  options?: () => Object,
  content?: () => void
): [() => void, number];
declare function __Interop_UpdateInteropExtendableComponent_Internal(dynamicComponent: Object): void;
declare function __Interop_ResetInteropExtendableComponent_Internal(): void;
declare function __Interop_TransferCompatibleBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void;
declare function __Interop_transferCompatibleDynamicBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void;
declare function __Interop_createCompatibleStaticState_Internal(value: Object): Object;
declare function __Interop_TransferCompatibleUpdatableBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void;

interface ModuleScenario {
  id: number;
  label: string;
  componentId: number;
  stateKey: string;
  stateValue: number;
  proxyName: string;
  proxyValue: number;
  dynamicArg: string;
  toggle: boolean;
}

export class InteropModuleDeepTestsV2 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating InteropModuleDeepTestsV2: ${str}`)
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

  private static assertScenario(scenario: ModuleScenario): void {
    InteropModuleDeepTestsV2.runOrSkip('registerCallbackForCreateWatchID', () => {
      let watchedProperty = '';
      registerCallbackForCreateWatchID((watchFuncCallback: (propertyName: string) => void, newValue: Object): Object => {
        watchFuncCallback(scenario.stateKey);
        return { id: scenario.id, newValue };
      });
      eq(typeof InteropExtractorModule.createWatchFunc, 'function', `${scenario.label} createWatchFunc`);
      const watchResult = InteropExtractorModule.createWatchFunc?.(
        (propertyName: string): void => {
          watchedProperty = propertyName;
        },
        { [scenario.stateKey]: scenario.stateValue },
      );
      eq(watchedProperty, scenario.stateKey, `${scenario.label} watch callback property`);
      eq((watchResult as any).id, scenario.id, `${scenario.label} watch callback id`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerCallbackForMakeObserved', () => {
      registerCallbackForMakeObserved((value: Object): Object => ({ value, tag: scenario.label }));
      const observed = InteropExtractorModule.makeObserved?.({ [scenario.stateKey]: scenario.stateValue });
      eq((observed as any).tag, scenario.label, `${scenario.label} makeObserved return`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerCompatibleStaticComponentCallback', () => {
      let optionsCalled = false;
      let contentCalled = false;
      // Scenario layering:
      // - - even id: pass options to verify optional-parameter path;
      // - - id divisible by 3: pass content to verify content-callback path;
      // This makes different cases cover different combinations instead of mechanical repetition.
      const expectOptions = scenario.id % 2 === 0;
      const expectContent = scenario.id % 3 === 0;
      registerCompatibleStaticComponentCallback((factory: () => Object, options?: () => Object, content?: () => void): [() => void, number] => {
        factory();
        options?.();
        content?.();
        return [(): void => {}, scenario.componentId];
      });
      const tuple = __Interop_CreateStaticComponent_Internal(
        (): Object => ({ id: scenario.componentId }),
        expectOptions ? (): Object => {
          optionsCalled = true;
          return { toggle: scenario.toggle };
        } : undefined,
        expectContent ? (): void => {
          contentCalled = true;
        } : undefined,
      );
      eq(tuple[1], scenario.componentId, `${scenario.label} component id`);
      eq(optionsCalled, expectOptions, `${scenario.label} options called`);
      eq(contentCalled, expectContent, `${scenario.label} content called`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerUpdateInteropExtendableComponent', () => {
      const updatePayloadList: string[] = [];
      registerUpdateInteropExtendableComponent((dynamicComponent: Object): void => {
        updatePayloadList.push((dynamicComponent as any).name);
      });
      __Interop_UpdateInteropExtendableComponent_Internal({ name: scenario.dynamicArg });
      // Insert an extra update every 4 cases to verify multi-update sequence.
      if (scenario.id % 4 === 0) {
        __Interop_UpdateInteropExtendableComponent_Internal({ name: `${scenario.dynamicArg}_extra` });
      }
      eq(updatePayloadList[0], scenario.dynamicArg, `${scenario.label} update callback payload`);
      eq(updatePayloadList.length, scenario.id % 4 === 0 ? 2 : 1, `${scenario.label} update callback count`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerResetInteropExtendableComponent', () => {
      let resetCount = 0;
      registerResetInteropExtendableComponent((): void => {
        resetCount += 1;
      });
      __Interop_ResetInteropExtendableComponent_Internal();
      // Run reset twice every 5 cases to verify multi-reset behavior.
      if (scenario.id % 5 === 0) {
        __Interop_ResetInteropExtendableComponent_Internal();
      }
      eq(resetCount, scenario.id % 5 === 0 ? 2 : 1, `${scenario.label} reset callback count`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerTransferCompatibleBuilderCallback', () => {
      registerTransferCompatibleBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      });
      let received = '';
      const wrapped = __Interop_TransferCompatibleBuilder_Internal((arg: string): void => {
        received = arg;
      });
      wrapped(scenario.dynamicArg);
      eq(received, scenario.dynamicArg, `${scenario.label} transferCompatibleBuilder`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerTransferCompatibleDynamicBuilderCallback', () => {
      registerTransferCompatibleDynamicBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      });
      let dynamicReceived = '';
      const wrapped = __Interop_transferCompatibleDynamicBuilder_Internal((arg: string): void => {
        dynamicReceived = `dyn_${arg}`;
      });
      wrapped(scenario.dynamicArg);
      eq(dynamicReceived, `dyn_${scenario.dynamicArg}`, `${scenario.label} dynamic builder`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerCreateCompatibleStaticState', () => {
      registerCreateCompatibleStaticState((value: Object): Object => ({ value, label: scenario.label }));
      const result = __Interop_createCompatibleStaticState_Internal({ [scenario.stateKey]: scenario.stateValue });
      eq((result as any).label, scenario.label, `${scenario.label} createCompatibleStaticState label`);
      eq((result as any).value[scenario.stateKey], scenario.stateValue, `${scenario.label} createCompatibleStaticState value`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerTransferCompatibleUpdatableBuilderCallback', () => {
      registerTransferCompatibleUpdatableBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      });
      let updatableReceived = '';
      const wrapped = __Interop_TransferCompatibleUpdatableBuilder_Internal((arg: string): void => {
        updatableReceived = `up_${arg}`;
      });
      wrapped(scenario.dynamicArg);
      eq(updatableReceived, `up_${scenario.dynamicArg}`, `${scenario.label} updatable builder`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerMakeBuilderParameterStaticProxy', () => {
      registerMakeBuilderParameterStaticProxy((name: string, value: Object): Object => ({ name, value, token: scenario.proxyValue }));
      const proxied = InteropExtractorModule.makeBuilderParameterStaticProxy?.(scenario.proxyName, { value: scenario.proxyValue }, {});
      eq((proxied as any).name, scenario.proxyName, `${scenario.label} proxy name`);
      eq((proxied as any).token, scenario.proxyValue, `${scenario.label} proxy token`);
    });
  }

  private static assertWatchAndObservedCase(caseLabel: string, stateKey: string, stateValue: number): void {
    InteropModuleDeepTestsV2.runOrSkip('registerCallbackForCreateWatchID', () => {
      let watchedProperty = '';
      registerCallbackForCreateWatchID((watchFuncCallback: (propertyName: string) => void, newValue: Object): Object => {
        watchFuncCallback(stateKey);
        return { key: stateKey, newValue, tag: caseLabel };
      });
      const watchResult = InteropExtractorModule.createWatchFunc?.(
        (propertyName: string): void => {
          watchedProperty = propertyName;
        },
        { [stateKey]: stateValue },
      );
      eq(watchedProperty, stateKey, `${caseLabel} watch property`);
      eq((watchResult as any).tag, caseLabel, `${caseLabel} watch result tag`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerCallbackForMakeObserved', () => {
      registerCallbackForMakeObserved((value: Object): Object => ({ value, observedTag: caseLabel }));
      const observed = InteropExtractorModule.makeObserved?.({ [stateKey]: stateValue });
      eq((observed as any).observedTag, caseLabel, `${caseLabel} observed tag`);
    });
  }

  private static assertTransferAndProxyCase(caseLabel: string, dynamicArg: string, proxyToken: number): void {
    InteropModuleDeepTestsV2.runOrSkip('registerTransferCompatibleBuilderCallback', () => {
      registerTransferCompatibleBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      });
      let transferResult = '';
      const wrapped = __Interop_TransferCompatibleBuilder_Internal((arg: string): void => {
        transferResult = `transfer_${arg}`;
      });
      wrapped(dynamicArg);
      eq(transferResult, `transfer_${dynamicArg}`, `${caseLabel} transfer builder`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerTransferCompatibleDynamicBuilderCallback', () => {
      registerTransferCompatibleDynamicBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      });
      let dynamicResult = '';
      const wrapped = __Interop_transferCompatibleDynamicBuilder_Internal((arg: string): void => {
        dynamicResult = `dynamic_${arg}`;
      });
      wrapped(dynamicArg);
      eq(dynamicResult, `dynamic_${dynamicArg}`, `${caseLabel} transfer dynamic builder`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerMakeBuilderParameterStaticProxy', () => {
      registerMakeBuilderParameterStaticProxy((name: string, value: Object): Object => ({ name, value, token: proxyToken }));
      const proxy = InteropExtractorModule.makeBuilderParameterStaticProxy?.(caseLabel, { arg: dynamicArg }, {});
      eq((proxy as any).token, proxyToken, `${caseLabel} proxy token`);
    });
  }

  private static assertUpdateAndResetCase(caseLabel: string, names: string[]): void {
    InteropModuleDeepTestsV2.runOrSkip('registerUpdateInteropExtendableComponent', () => {
      const seenNames: string[] = [];
      registerUpdateInteropExtendableComponent((dynamicComponent: Object): void => {
        seenNames.push((dynamicComponent as any).name);
      });
      names.forEach((name) => {
        __Interop_UpdateInteropExtendableComponent_Internal({ name });
      });
      eq(seenNames.length, names.length, `${caseLabel} update count`);
      eq(seenNames[seenNames.length - 1], names[names.length - 1], `${caseLabel} update last payload`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerResetInteropExtendableComponent', () => {
      let resetCount = 0;
      registerResetInteropExtendableComponent((): void => {
        resetCount += 1;
      });
      names.forEach(() => {
        __Interop_ResetInteropExtendableComponent_Internal();
      });
      eq(resetCount, names.length, `${caseLabel} reset count`);
    });
  }

  private static assertStaticComponentCase(
    caseLabel: string,
    componentId: number,
    withOptions: boolean,
    withContent: boolean
  ): void {
    /*
     * Design goals:
     * 1) deterministically verify factory return enters callback chain;
     * 2) cover optional parameter combinations via withOptions/withContent toggles;
     * 3) record call order to avoid missing wrong-order callback issues;
     * 4) validate tuple id returned by __Interop_CreateStaticComponent_Internal.
     */
    InteropModuleDeepTestsV2.runOrSkip('registerCompatibleStaticComponentCallback', () => {
      const callOrder: string[] = [];
      registerCompatibleStaticComponentCallback(
        (factory: () => Object, options?: () => Object, content?: () => void): [() => void, number] => {
          const factoryResult = factory();
          callOrder.push(`factory_${(factoryResult as any).id}`);
          if (options !== undefined) {
            const optionsResult = options();
            callOrder.push(`options_${(optionsResult as any).mode}`);
          }
          if (content !== undefined) {
            content();
            callOrder.push('content_called');
          }
          return [(): void => {}, componentId];
        }
      );
      const tuple = __Interop_CreateStaticComponent_Internal(
        (): Object => ({ id: componentId }),
        withOptions ? (): Object => ({ mode: `${caseLabel}_opt` }) : undefined,
        withContent ? (): void => {} : undefined,
      );
      eq(tuple[1], componentId, `${caseLabel} component tuple id`);
      eq(callOrder[0], `factory_${componentId}`, `${caseLabel} factory call order`);
      eq(callOrder.includes(`options_${caseLabel}_opt`), withOptions, `${caseLabel} options branch`);
      eq(callOrder.includes('content_called'), withContent, `${caseLabel} content branch`);
    });
  }

  private static assertStaticStateAndUpdatableBuilderCase(
    caseLabel: string,
    stateKey: string,
    stateValue: number,
    builderArg: string
  ): void {
    /*
     * Design goals:
     * 1) verify static-state value forwarding and label binding;
     * 2) assert keyCount to ensure full object structure is passed;
     * 3) verify argument forwarding for updatable-builder bridge wrapper;
     * 4) combine state creation and builder transfer in one closed-loop case.
     */
    InteropModuleDeepTestsV2.runOrSkip('registerCreateCompatibleStaticState', () => {
      registerCreateCompatibleStaticState((value: Object): Object => ({
        value,
        stateTag: caseLabel,
        keyCount: Object.keys(value).length
      }));
      const state = __Interop_createCompatibleStaticState_Internal({ [stateKey]: stateValue });
      eq((state as any).stateTag, caseLabel, `${caseLabel} static state tag`);
      eq((state as any).value[stateKey], stateValue, `${caseLabel} static state value`);
      eq((state as any).keyCount, 1, `${caseLabel} static state key count`);
    });

    InteropModuleDeepTestsV2.runOrSkip('registerTransferCompatibleUpdatableBuilderCallback', () => {
      registerTransferCompatibleUpdatableBuilderCallback(
        (builder: (...args: any[]) => void): ((...args: any[]) => void) => {
          return (...args: any[]): void => builder(...args);
        }
      );
      let received = '';
      const wrapped = __Interop_TransferCompatibleUpdatableBuilder_Internal((arg: string): void => {
        received = `updatable_${arg}`;
      });
      wrapped(builderArg);
      eq(received, `updatable_${builderArg}`, `${caseLabel} updatable builder`);
    });
  }



  /*
   * Module deep case A:
   * 1) remove weak cases that only pass one number;
   * 2) verify full interaction chain of watch/createState/update/reset;
   * 3) verify actual builder-transfer forwarding via dynamic arguments.
   */
  public testInteropModuleDeepMatrixCaseA(): void {
    InteropModuleDeepTestsV2.runOrSkip('registerCallbackForCreateWatchID', () => {
      let watchedKey = '';
      registerCallbackForCreateWatchID((watchFuncCallback: (propertyName: string) => void, _newValue: Object): Object => {
        watchFuncCallback('matrix_key_a');
        return { id: 9101, mode: 'matrix_case_a' };
      });
      const watchResult = InteropExtractorModule.createWatchFunc?.(
        (propertyName: string): void => { watchedKey = propertyName; },
        { matrix_key_a: 1 },
      );
      eq(watchedKey, 'matrix_key_a', 'module matrix A watch key');
      eq((watchResult as any).id, 9101, 'module matrix A watch id');
    });

    InteropModuleDeepTestsV2.runOrSkip('registerUpdateInteropExtendableComponent', () => {
      const payloadList: string[] = [];
      registerUpdateInteropExtendableComponent((dynamicComponent: Object): void => {
        payloadList.push((dynamicComponent as any).name);
      });
      __Interop_UpdateInteropExtendableComponent_Internal({ name: 'matrix_dyn_a' });
      __Interop_UpdateInteropExtendableComponent_Internal({ name: 'matrix_dyn_b' });
      eq(payloadList.length, 2, 'module matrix A update count');
      eq(payloadList[1], 'matrix_dyn_b', 'module matrix A update second payload');
    });

    InteropModuleDeepTestsV2.runOrSkip('registerResetInteropExtendableComponent', () => {
      let resetCount = 0;
      registerResetInteropExtendableComponent((): void => { resetCount += 1; });
      __Interop_ResetInteropExtendableComponent_Internal();
      __Interop_ResetInteropExtendableComponent_Internal();
      eq(resetCount, 2, 'module matrix A reset count');
    });

    InteropModuleDeepTestsV2.runOrSkip('registerTransferCompatibleBuilderCallback', () => {
      registerTransferCompatibleBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      });
      let received = '';
      const wrapped = __Interop_TransferCompatibleBuilder_Internal((arg: string): void => {
        received = `matrix_${arg}`;
      });
      wrapped('payload_a');
      eq(received, 'matrix_payload_a', 'module matrix A transfer payload');
    });
  }

    /* Module bridge valid case 02 */
  public testInteropModuleDeepCase02(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_02', 'k_02_watch', 702);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_02', 3002, true, false);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_02',
      'k_02_state',
      1702,
      'dyn_02_up'
    );
  }

    /* Module bridge valid case 03 */
  public testInteropModuleDeepCase03(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_03', 'dyn_03_transfer', 5006);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_03', ['dyn_03_a', 'dyn_03_b']);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_03', 3003, false, true);
  }

    /* Module bridge valid case 04 */
  public testInteropModuleDeepCase04(): void {
    InteropModuleDeepTestsV2.assertUpdateAndResetCase(
      'module_case_04',
      ['dyn_04_first', 'dyn_04_second', 'dyn_04_third']
    );
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_04', 'k_04_observed', 704);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_04',
      'k_04_state',
      1704,
      'dyn_04_updatable'
    );
  }

    /* Module bridge valid case 05 */
  public testInteropModuleDeepCase05(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 5,
      label: 'module_case_05',
      componentId: 3005,
      stateKey: 'k_05',
      stateValue: 705,
      proxyName: 'proxy_05',
      proxyValue: 5010,
      dynamicArg: 'dyn_05',
      toggle: false,
    });
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_05_extra', 'dyn_05_proxy', 9010);
  }

    /* Module bridge valid case 06 */
  public testInteropModuleDeepCase06(): void {
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_06', 3006, true, true);
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_06', 'k_06_mix', 706);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_06', ['dyn_06_a']);
  }

    /* Module bridge valid case 07 */
  public testInteropModuleDeepCase07(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_07', 'dyn_07_json_{"k":7}', 5014);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_07',
      'k_07_cn',
      707,
      'dyn_07_unicode'
    );
  }

    /* Module bridge valid case 08 */
  public testInteropModuleDeepCase08(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 8,
      label: 'module_case_08',
      componentId: 3008,
      stateKey: 'k_08',
      stateValue: 708,
      proxyName: 'proxy_08',
      proxyValue: 5016,
      dynamicArg: 'dyn_08',
      toggle: true,
    });
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_08_extra', 3808, false, false);
  }

    /* Module bridge valid case 09 */
  public testInteropModuleDeepCase09(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_09', 'k_09_observe', 709);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_09', 3009, true, true);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase(
      'module_case_09',
      ['dyn_09_1', 'dyn_09_2', 'dyn_09_3', 'dyn_09_4']
    );
  }

    /* Module bridge valid case 10 */
  public testInteropModuleDeepCase10(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_10', 'dyn_10_transfer', 5020);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_10',
      'k_10_state',
      1710,
      'dyn_10_up'
    );
  }

    /* Module bridge valid case 11 */
  public testInteropModuleDeepCase11(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 11,
      label: 'module_case_11',
      componentId: 3011,
      stateKey: 'k_11',
      stateValue: 711,
      proxyName: 'proxy_11',
      proxyValue: 5022,
      dynamicArg: 'dyn_11',
      toggle: false,
    });
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_11_extra', 'k_11_extra', 1711);
  }

    /* Module bridge valid case 12 */
  public testInteropModuleDeepCase12(): void {
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_12', 3012, false, true);
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_12', 'dyn_12_mix', 5024);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_12', ['dyn_12_a', 'dyn_12_b']);
  }

    /* Module bridge valid case 13 */
  public testInteropModuleDeepCase13(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_13', 'k_13_flag', 713);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_13',
      'k_13',
      1713,
      'dyn_13_bridge'
    );
  }

    /* Module bridge valid case 14 */
  public testInteropModuleDeepCase14(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 14,
      label: 'module_case_14',
      componentId: 3014,
      stateKey: 'k_14',
      stateValue: 714,
      proxyName: 'proxy_14',
      proxyValue: 5028,
      dynamicArg: 'dyn_14',
      toggle: true,
    });
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_14_extra', 3814, true, false);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_14_extra', ['dyn_14_extra']);
  }

    /* Module bridge valid case 15 */
  public testInteropModuleDeepCase15(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_15', 'dyn_15_route', 5030);
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_15', 'k_15_watch', 715);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_15', 3015, true, true);
  }

    /* Module bridge valid case 16 */
  public testInteropModuleDeepCase16(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 16,
      label: 'module_case_16',
      componentId: 3016,
      stateKey: 'k_16',
      stateValue: 716,
      proxyName: 'proxy_16',
      proxyValue: 5032,
      dynamicArg: 'dyn_16',
      toggle: true,
    });
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_16_extra',
      'k_16_extra',
      1716,
      'dyn_16_up'
    );
  }

    /* Module bridge valid case 17 */
  public testInteropModuleDeepCase17(): void {
    InteropModuleDeepTestsV2.assertUpdateAndResetCase(
      'module_case_17',
      ['dyn_17_a', 'dyn_17_b', 'dyn_17_c']
    );
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_17', 'dyn_17_transfer', 5034);
  }

    /* Module bridge valid case 18 */
  public testInteropModuleDeepCase18(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_18', 'k_18_observe', 718);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_18', 3018, false, false);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_18',
      'k_18_state',
      1718,
      'dyn_18_update'
    );
  }

    /* Module bridge valid case 19 */
  public testInteropModuleDeepCase19(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 19,
      label: 'module_case_19',
      componentId: 3019,
      stateKey: 'k_19',
      stateValue: 719,
      proxyName: 'proxy_19',
      proxyValue: 5038,
      dynamicArg: 'dyn_19',
      toggle: false,
    });
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_19_extra', 'dyn_19_extra', 9038);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_19_extra', ['dyn_19_extra_a']);
  }

    /* Module bridge valid case 20 */
  public testInteropModuleDeepCase20(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_20', 'k_20_watch', 720);
    InteropModuleDeepTestsV2.assertScenario({
      id: 20,
      label: 'module_case_20',
      componentId: 3020,
      stateKey: 'k_20',
      stateValue: 720,
      proxyName: 'proxy_20',
      proxyValue: 5040,
      dynamicArg: 'dyn_20',
      toggle: true,
    });
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_20',
      'k_20_state',
      1720,
      'dyn_20_up'
    );
  }

    /* Module bridge valid case 21 */
  public testInteropModuleDeepCase21(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_21', 'dyn_21_transfer', 5042);
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_21', 'k_21_observe', 721);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_21', 3021, true, true);
  }

    /* Module bridge valid case 22 */
  public testInteropModuleDeepCase22(): void {
    InteropModuleDeepTestsV2.assertUpdateAndResetCase(
      'module_case_22',
      ['dyn_22_a', 'dyn_22_b']
    );
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_22', 'dyn_22_proxy', 5044);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_22',
      'k_22_state',
      1722,
      'dyn_22_up'
    );
  }

    /* Module bridge valid case 23 */
  public testInteropModuleDeepCase23(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 23,
      label: 'module_case_23',
      componentId: 3023,
      stateKey: 'k_23',
      stateValue: 723,
      proxyName: 'proxy_23',
      proxyValue: 5046,
      dynamicArg: 'dyn_23',
      toggle: false,
    });
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_23', ['dyn_23_only']);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_23', 3023, false, true);
  }

    /* Module bridge valid case 24 */
  public testInteropModuleDeepCase24(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_24', 'k_24_cn', 724);
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_24', 'dyn_24_!@#', 5048);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_24', ['dyn_24_x', 'dyn_24_y']);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_24',
      'k_24_state',
      1724,
      'dyn_24_up'
    );
  }

    /* Module bridge valid case 25 */
  public testInteropModuleDeepCase25(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_25', 'k_25_flag', 725);
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_25', '{"id":25}', 5050);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_25', 3025, false, false);
  }

    /* Module bridge valid case 26 */
  public testInteropModuleDeepCase26(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_26', 'dyn_26', 5052);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_26', ['dyn_26_1']);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_26',
      'k_26_state',
      1726,
      'dyn_26_up'
    );
  }

    /* Module bridge valid case 27 */
  public testInteropModuleDeepCase27(): void {
    InteropModuleDeepTestsV2.assertUpdateAndResetCase(
      'module_case_27',
      ['dyn_27_a', 'dyn_27_b', 'dyn_27_c']
    );
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_27', 'k_27', 727);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_27', 3027, true, false);
  }

    /* Module bridge valid case 28 */
  public testInteropModuleDeepCase28(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_28', 'k_28', 728);
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_28', 'dyn_28_compose', 5056);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_28',
      'k_28_state',
      1728,
      'dyn_28_up'
    );
  }

    /* Module bridge valid case 29 */
  public testInteropModuleDeepCase29(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 29,
      label: 'module_case_29',
      componentId: 3029,
      stateKey: 'k_29',
      stateValue: 729,
      proxyName: 'proxy_29',
      proxyValue: 5058,
      dynamicArg: 'dyn_29',
      toggle: false,
    });
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_29_extra', 'dyn_29_extra', 9058);
  }

    /* Module bridge valid case 30 */
  public testInteropModuleDeepCase30(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_30', 'k_30_watch', 730);
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_30', 'dyn_30_transfer', 5060);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_30', 3030, true, true);
  }

    /* Module bridge valid case 31 */
  public testInteropModuleDeepCase31(): void {
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_31', ['dyn_31_a', 'dyn_31_b', 'dyn_31_c']);
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_31', 'k_31_observed', 731);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_31',
      'k_31_state',
      1731,
      'dyn_31_up'
    );
  }

    /* Module bridge valid case 32 */
  public testInteropModuleDeepCase32(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_32', 'dyn_32_bridge', 5064);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_32', ['dyn_32_once']);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_32', 3032, false, true);
  }

    /* Module bridge valid case 33 */
  public testInteropModuleDeepCase33(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 33,
      label: 'module_case_33',
      componentId: 3033,
      stateKey: 'k_33',
      stateValue: 733,
      proxyName: 'proxy_33',
      proxyValue: 5066,
      dynamicArg: 'dyn_33',
      toggle: false,
    });
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_33_extra', 'dyn_33_extra', 6333);
  }

    /* Module bridge valid case 34 */
  public testInteropModuleDeepCase34(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_34', 'k_34_watch', 734);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_34', ['dyn_34_1', 'dyn_34_2']);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_34',
      'k_34_state',
      1734,
      'dyn_34_up'
    );
  }

    /* Module bridge valid case 35 */
  public testInteropModuleDeepCase35(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_35', 'dyn_35', 5070);
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_35', 'k_35', 735);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_35', 3035, true, false);
  }

    /* Tier[] Module case 36 */
  public testInteropModuleDeepCase36(): void {
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_36', 3636, false, true);
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_36', 'k_36_observed', 736);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_36',
      'k_36_state_pack',
      2736,
      'dyn_36_payload'
    );
  }

    /* Tier[] Module case 37 */
  public testInteropModuleDeepCase37(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 37,
      label: 'module_case_37',
      componentId: 3037,
      stateKey: 'k_37',
      stateValue: 737,
      proxyName: 'proxy_37',
      proxyValue: 5074,
      dynamicArg: 'dyn_37',
      toggle: false,
    });
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_37_extra', 'dyn_37_json_{"p":37}', 8374);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_37_extra', 3737, true, false);
  }

    /* Tier[] Module case 38 */
  public testInteropModuleDeepCase38(): void {
    InteropModuleDeepTestsV2.assertUpdateAndResetCase(
      'module_case_38',
      ['dyn_38_a', 'dyn_38_b', 'dyn_38_c', 'dyn_38_d']
    );
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_38', 'k_38_cn_state', 738);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_38',
      'k_38_state',
      1838,
      'dyn_38_up_state'
    );
  }

    /* Tier[] Module case 39 */
  public testInteropModuleDeepCase39(): void {
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_39', 'dyn_39_compose', 5078);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_39', 3939, false, true);
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_39', 'k_39_obs_unicode_cn', 739);
  }

    /* Tier[] Module case 40 */
  public testInteropModuleDeepCase40(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 40,
      label: 'module_case_40',
      componentId: 3040,
      stateKey: 'k_40',
      stateValue: 740,
      proxyName: 'proxy_40',
      proxyValue: 5080,
      dynamicArg: 'dyn_40_!@#',
      toggle: true,
    });
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_40', ['dyn_40_a', 'dyn_40_b']);
    InteropModuleDeepTestsV2.assertStaticStateAndUpdatableBuilderCase(
      'module_case_40',
      'k_40_state',
      2740,
      'dyn_40_up'
    );
  }

    /* Tier[] Module case 41 */
  public testInteropModuleDeepCase41(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 41,
      label: 'module_case_41',
      componentId: 3041,
      stateKey: 'k_41',
      stateValue: 741,
      proxyName: 'proxy_41',
      proxyValue: 5082,
      dynamicArg: 'dyn_41',
      toggle: false,
    });
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_41_extra', 'k_41_extra', 1741);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_41_extra', ['dyn_41_a', 'dyn_41_b']);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_41_extra', 4041, true, false);
  }

    /* Tier[] Module case 42 */
  public testInteropModuleDeepCase42(): void {
    InteropModuleDeepTestsV2.assertScenario({
      id: 42,
      label: 'module_case_42',
      componentId: 3042,
      stateKey: 'k_42',
      stateValue: 742,
      proxyName: 'proxy_42',
      proxyValue: 5084,
      dynamicArg: 'dyn_42',
      toggle: true,
    });
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_42_extra', 'dyn_42_extra', 8042);
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_42_extra', 'k_42_extra_watch', 1742);
    InteropModuleDeepTestsV2.assertStaticComponentCase('module_case_42_extra', 4042, false, true);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_42_extra', ['dyn_42_one']);
  }

    /* Module bridge valid case 43 */
  public testInteropModuleDeepCase43(): void {
    InteropModuleDeepTestsV2.assertWatchAndObservedCase('module_case_43', 'k_43', 743);
    InteropModuleDeepTestsV2.assertTransferAndProxyCase('module_case_43', 'dyn_43_bridge', 5086);
    InteropModuleDeepTestsV2.assertUpdateAndResetCase('module_case_43', ['dyn_43_a', 'dyn_43_b', 'dyn_43_c']);
  }
}
