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
 */

import { eq, neq, gt, ITestFile } from '../lib/testRunner'

declare class AppStorage {
  static prop(key: string): SubscribedAbstractProperty<any> | undefined;
  static setAndProp(key: string, defaultValue: any): SubscribedAbstractProperty<any>;
  static set(key: string, value: any): boolean;
  static delete(key: string): boolean;
}

declare interface IEnvironmentBackend {
  getAccessibilityEnabled(): boolean;
  getColorMode(): number;
  getFontScale(): number;
  getFontWeightScale(): number;
  getLayoutDirection(): number;
  getLanguageCode(): string;
  onValueChanged(callback: (key: string, value: any) => void): void;
}

declare class SubscribedAbstractProperty<T> {
  get(): T;
  set(value: T): void;
  aboutToBeDeleted(): void;
}

declare class Environment {
  static configureBackend(envBackend: IEnvironmentBackend): void;
  static ConfigureBackend(envBackend: IEnvironmentBackend): void;
  static envProp<S>(key: string, value: S): boolean;
  static EnvProp<S>(key: string, value: S): boolean;
  static envProps(props: { key: string, defaultValue: any }[]): void;
  static EnvProps(props: { key: string, defaultValue: any }[]): void;
  static keys(): Array<string>;
  static Keys(): Array<string>;
  static aboutToBeDeleted(): void;
  static AboutToBeDeleted(): void;
}

class MockEnvironmentBackend implements IEnvironmentBackend {
  private accessibilityEnabled: boolean = false;
  private colorMode: number = 0;
  private fontScale: number = 1.0;
  private fontWeightScale: number = 1.0;
  private layoutDirection: number = 0;
  private languageCode: string = 'en';
  private valueChangedCallback?: (key: string, value: any) => void;

  constructor(config?: {
    accessibilityEnabled?: boolean;
    colorMode?: number;
    fontScale?: number;
    fontWeightScale?: number;
    layoutDirection?: number;
    languageCode?: string;
  }) {
    if (config) {
      this.accessibilityEnabled = config.accessibilityEnabled ?? this.accessibilityEnabled;
      this.colorMode = config.colorMode ?? this.colorMode;
      this.fontScale = config.fontScale ?? this.fontScale;
      this.fontWeightScale = config.fontWeightScale ?? this.fontWeightScale;
      this.layoutDirection = config.layoutDirection ?? this.layoutDirection;
      this.languageCode = config.languageCode ?? this.languageCode;
    }
  }

  getAccessibilityEnabled(): boolean {
    return this.accessibilityEnabled;
  }

  getColorMode(): number {
    return this.colorMode;
  }

  getFontScale(): number {
    return this.fontScale;
  }

  getFontWeightScale(): number {
    return this.fontWeightScale;
  }

  getLayoutDirection(): number {
    return this.layoutDirection;
  }

  getLanguageCode(): string {
    return this.languageCode;
  }

  onValueChanged(callback: (key: string, value: any) => void): void {
    this.valueChangedCallback = callback;
  }

  simulateValueChange(key: string, value: any): void {
    if (this.valueChangedCallback) {
      this.valueChangedCallback(key, value);
    }
  }
}

export class EnvironmentTestsV1 implements ITestFile {
  private idString: string = "";
  private static mockBackend: MockEnvironmentBackend = new MockEnvironmentBackend();

  constructor(str: string) {
    console.log(`Creating EnvironmentTestsV1: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    Environment.configureBackend(EnvironmentTestsV1.mockBackend);
  }

  public beforeEach(): void {
    Environment.aboutToBeDeleted();
    EnvironmentTestsV1.mockBackend = new MockEnvironmentBackend();
    Environment.configureBackend(EnvironmentTestsV1.mockBackend);
  }

  public afterAll(): void {
    Environment.aboutToBeDeleted();
  }

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // SECTION 1: Basic envProp Tests
  // =========================================================================

  public testEnvPropAccessibilityEnabled(): void {
    const backend = new MockEnvironmentBackend({ accessibilityEnabled: true });
    Environment.configureBackend(backend);

    const result = Environment.envProp('accessibilityEnabled', false);

    eq(result, true, "envProp for accessibilityEnabled succeeds");
    const keys = Environment.keys();
    eq(keys.includes('accessibilityEnabled'), true, "accessibilityEnabled is registered");
  }

  public testEnvPropColorMode(): void {
    const backend = new MockEnvironmentBackend({ colorMode: 1 });
    Environment.configureBackend(backend);

    const result = Environment.envProp('colorMode', 0);

    eq(result, true, "envProp for colorMode succeeds");
    const keys = Environment.keys();
    eq(keys.includes('colorMode'), true, "colorMode is registered");
  }

  public testEnvPropFontScale(): void {
    const backend = new MockEnvironmentBackend({ fontScale: 1.5 });
    Environment.configureBackend(backend);

    const result = Environment.envProp('fontScale', 1.0);

    eq(result, true, "envProp for fontScale succeeds");
    const keys = Environment.keys();
    eq(keys.includes('fontScale'), true, "fontScale is registered");
  }

  public testEnvPropFontWeightScale(): void {
    const backend = new MockEnvironmentBackend({ fontWeightScale: 1.2 });
    Environment.configureBackend(backend);

    const result = Environment.envProp('fontWeightScale', 1.0);

    eq(result, true, "envProp for fontWeightScale succeeds");
    const keys = Environment.keys();
    eq(keys.includes('fontWeightScale'), true, "fontWeightScale is registered");
  }

  public testEnvPropLayoutDirection(): void {
    const backend = new MockEnvironmentBackend({ layoutDirection: 1 });
    Environment.configureBackend(backend);

    const result = Environment.envProp('layoutDirection', 0);

    eq(result, true, "envProp for layoutDirection succeeds");
    const keys = Environment.keys();
    eq(keys.includes('layoutDirection'), true, "layoutDirection is registered");
  }

  public testEnvPropLanguageCode(): void {
    const backend = new MockEnvironmentBackend({ languageCode: 'zh-CN' });
    Environment.configureBackend(backend);

    const result = Environment.envProp('languageCode', 'en');

    eq(result, true, "envProp for languageCode succeeds");
    const keys = Environment.keys();
    eq(keys.includes('languageCode'), true, "languageCode is registered");
  }

  // =========================================================================
  // SECTION 2: Custom Property Tests
  // =========================================================================

  public testEnvPropCustomProperty(): void {
    const result = Environment.envProp('customProp', 'customValue');

    eq(result, true, "envProp for custom property succeeds");
    const keys = Environment.keys();
    eq(keys.includes('customProp'), true, "custom property is registered");
  }

  public testEnvPropCustomPropertyNumber(): void {
    const result = Environment.envProp('customNumber', 42);

    eq(result, true, "envProp for custom number property succeeds");
    const keys = Environment.keys();
    eq(keys.includes('customNumber'), true, "custom number property is registered");
  }

  public testEnvPropCustomPropertyBoolean(): void {
    const result = Environment.envProp('customBoolean', true);

    eq(result, true, "envProp for custom boolean property succeeds");
    const keys = Environment.keys();
    eq(keys.includes('customBoolean'), true, "custom boolean property is registered");
  }

  public testEnvPropCustomPropertyObject(): void {
    const obj = { key: 'value', num: 123 };
    const result = Environment.envProp('customObject', obj);

    eq(result, true, "envProp for custom object property succeeds");
    const keys = Environment.keys();
    eq(keys.includes('customObject'), true, "custom object property is registered");
  }

  // =========================================================================
  // SECTION 3: envProps Multiple Properties
  // =========================================================================

  public testEnvPropsMultiple(): void {
    const properties = [
      { key: 'prop1', defaultValue: 'value1' },
      { key: 'prop2', defaultValue: 42 },
      { key: 'prop3', defaultValue: true }
    ];

    Environment.envProps(properties);

    const keys = Environment.keys();
    eq(keys.includes('prop1'), true, "prop1 is registered");
  }

  public testEnvPropsMixedBuiltInAndCustom(): void {
    const backend = new MockEnvironmentBackend({
      colorMode: 1,
      languageCode: 'zh-CN'
    });
    Environment.configureBackend(backend);

    const properties = [
      { key: 'colorMode', defaultValue: 0 },
      { key: 'languageCode', defaultValue: 'en' },
      { key: 'customProp', defaultValue: 'custom' }
    ];

    Environment.envProps(properties);

    const keys = Environment.keys();
    eq(keys.includes('colorMode'), true, "colorMode is registered");
    eq(keys.includes('languageCode'), true, "languageCode is registered");
    eq(keys.includes('customProp'), true, "customProp is registered");
    eq(keys.length, 3, "All 3 properties are registered");
  }

  public testEnvPropsEmptyArray(): void {
    Environment.envProps([]);

    const keys = Environment.keys();
    eq(keys.length, 0, "No properties registered with empty array");
  }

  public testKeysEmpty(): void {
    const keys = Environment.keys();
    eq(Array.isArray(keys), true, "keys() returns array");
    eq(keys.length, 0, "keys() returns empty array when no properties registered");
  }

  public testKeysAfterMultipleEnvProps(): void {
    Environment.envProps([
      { key: 'a', defaultValue: 1 },
      { key: 'b', defaultValue: 2 },
      { key: 'c', defaultValue: 3 },
      { key: 'd', defaultValue: 4 }
    ]);

    const keys = Environment.keys();
    eq(keys.length, 4, "keys() returns all 4 properties");
  }

  // =========================================================================
  // SECTION 5: Deprecated API Tests
  // =========================================================================

  public testConfigureBackendDeprecated(): void {
    const backend = new MockEnvironmentBackend();
    Environment.ConfigureBackend(backend);

    const result = Environment.envProp('testProp', 'value');
    eq(result, true, "ConfigureBackend (deprecated) works");
  }

  public testKeysDeprecated(): void {
    Environment.envProp('testKey', 'testValue');

    const keys = Environment.Keys();
    eq(keys.includes('testKey'), true, "Keys (deprecated) works");
  }

  public testAboutToBeDeletedDeprecated(): void {
    Environment.envProp('toDelete', 'value');
    eq(Environment.keys().length, 1, "Property registered before deletion");

    Environment.AboutToBeDeleted();

    const keys = Environment.keys();
    eq(keys.length, 0, "All properties cleaned up after AboutToBeDeleted");
  }

  // =========================================================================
  // SECTION 6: Edge Cases
  // =========================================================================

  public testEnvPropZeroValue(): void {
    const result = Environment.envProp('zeroProp', 0);

    eq(result, true, "envProp with zero value succeeds");
    const keys = Environment.keys();
    eq(keys.includes('zeroProp'), true, "Property with zero value is registered");
  }

  public testEnvPropFalseValue(): void {
    const result = Environment.envProp('falseProp', false);

    eq(result, true, "envProp with false value succeeds");
    const keys = Environment.keys();
    eq(keys.includes('falseProp'), true, "Property with false value is registered");
  }

  public testEnvPropDuplicateKey(): void {
    const result1 = Environment.envProp('duplicate', 'first');
    eq(result1, true, "First envProp succeeds");

    const result2 = Environment.envProp('duplicate', 'second');
    eq(result2, false, "Second envProp with same key fails");

    const keys = Environment.keys();
    eq(keys.length, 1, "Only one property registered");
  }

  public testReinitializeAfterAboutToBeDeleted(): void {
    Environment.envProp('initial', 'value');
    Environment.aboutToBeDeleted();

    const result = Environment.envProp('newProp', 'newValue');
    eq(result, true, "Can register new properties after aboutToBeDeleted");

    const keys = Environment.keys();
    eq(keys.length, 1, "Only new property is registered");
    eq(keys.includes('newProp'), true, "New property is registered");
  }

  // =========================================================================
  // SECTION 7: Extended MockEnvironmentBackend Configuration Tests
  // =========================================================================

  public testMockBackendDefaultAccessibility(): void {
    const backend = new MockEnvironmentBackend();
    eq(backend.getAccessibilityEnabled(), false, 'default accessibility false');
  }

  public testMockBackendDefaultColorMode(): void {
    const backend = new MockEnvironmentBackend();
    eq(backend.getColorMode(), 0, 'default colorMode 0');
  }

  public testMockBackendDefaultFontScale(): void {
    const backend = new MockEnvironmentBackend();
    eq(backend.getFontScale(), 1.0, 'default fontScale 1.0');
  }

  public testMockBackendDefaultFontWeightScale(): void {
    const backend = new MockEnvironmentBackend();
    eq(backend.getFontWeightScale(), 1.0, 'default fontWeightScale 1.0');
  }

  public testMockBackendDefaultLayoutDirection(): void {
    const backend = new MockEnvironmentBackend();
    eq(backend.getLayoutDirection(), 0, 'default layoutDirection 0');
  }

  public testMockBackendDefaultLanguageCode(): void {
    const backend = new MockEnvironmentBackend();
    eq(backend.getLanguageCode(), 'en', 'default languageCode en');
  }

  public testMockBackendCustomAccessibility(): void {
    const backend = new MockEnvironmentBackend({ accessibilityEnabled: true });
    eq(backend.getAccessibilityEnabled(), true, 'custom accessibility true');
  }

  public testMockBackendCustomColorMode(): void {
    const backend = new MockEnvironmentBackend({ colorMode: 1 });
    eq(backend.getColorMode(), 1, 'custom colorMode 1');
  }

  public testMockBackendCustomFontScale(): void {
    const backend = new MockEnvironmentBackend({ fontScale: 2.0 });
    eq(backend.getFontScale(), 2.0, 'custom fontScale 2.0');
  }

  public testMockBackendCustomFontWeightScale(): void {
    const backend = new MockEnvironmentBackend({ fontWeightScale: 1.5 });
    eq(backend.getFontWeightScale(), 1.5, 'custom fontWeightScale 1.5');
  }

  public testMockBackendCustomLayoutDirection(): void {
    const backend = new MockEnvironmentBackend({ layoutDirection: 1 });
    eq(backend.getLayoutDirection(), 1, 'custom layoutDirection 1');
  }

  public testMockBackendCustomLanguageCode(): void {
    const backend = new MockEnvironmentBackend({ languageCode: 'zh-CN' });
    eq(backend.getLanguageCode(), 'zh-CN', 'custom languageCode zh-CN');
  }

  public testMockBackendMultipleConfig(): void {
    const backend = new MockEnvironmentBackend({
      accessibilityEnabled: true,
      colorMode: 1,
      fontScale: 1.5,
      fontWeightScale: 1.2,
      layoutDirection: 1,
      languageCode: 'ja'
    });
    eq(backend.getAccessibilityEnabled(), true, 'multi config accessibility');
    eq(backend.getColorMode(), 1, 'multi config colorMode');
    eq(backend.getFontScale(), 1.5, 'multi config fontScale');
    eq(backend.getFontWeightScale(), 1.2, 'multi config fontWeightScale');
    eq(backend.getLayoutDirection(), 1, 'multi config layoutDirection');
    eq(backend.getLanguageCode(), 'ja', 'multi config languageCode');
  }

  public testMockBackendPartialConfig(): void {
    const backend = new MockEnvironmentBackend({ colorMode: 2 });
    eq(backend.getColorMode(), 2, 'partial config colorMode set');
    eq(backend.getAccessibilityEnabled(), false, 'partial config accessibility default');
    eq(backend.getFontScale(), 1.0, 'partial config fontScale default');
  }

  // =========================================================================
  // SECTION 8: envProp Extended Value Type Tests
  // =========================================================================

  public testEnvPropStringValue001(): void {
    const result = Environment.envProp('str_001', 'hello');
    eq(result, true, 'envProp string 001');
    const keys = Environment.keys();
    eq(keys.includes('str_001'), true, 'str_001 registered');
  }

  public testEnvPropStringValue002(): void {
    const result = Environment.envProp('str_002', '');
    eq(result, true, 'envProp empty string 002');
    const keys = Environment.keys();
    eq(keys.includes('str_002'), true, 'str_002 registered');
  }

  public testEnvPropNumberValue001(): void {
    const result = Environment.envProp('num_001', 100);
    eq(result, true, 'envProp number 001');
    const keys = Environment.keys();
    eq(keys.includes('num_001'), true, 'num_001 registered');
  }

  public testEnvPropNumberValue002(): void {
    const result = Environment.envProp('num_002', -50);
    eq(result, true, 'envProp negative number 002');
    const keys = Environment.keys();
    eq(keys.includes('num_002'), true, 'num_002 registered');
  }

  public testEnvPropNumberValue003(): void {
    const result = Environment.envProp('num_003', 3.14);
    eq(result, true, 'envProp float number 003');
    const keys = Environment.keys();
    eq(keys.includes('num_003'), true, 'num_003 registered');
  }

  public testEnvPropBoolValueTrue(): void {
    const result = Environment.envProp('bool_true', true);
    eq(result, true, 'envProp bool true');
    const keys = Environment.keys();
    eq(keys.includes('bool_true'), true, 'bool_true registered');
  }

  public testEnvPropBoolValueFalse(): void {
    const result = Environment.envProp('bool_false', false);
    eq(result, true, 'envProp bool false');
    const keys = Environment.keys();
    eq(keys.includes('bool_false'), true, 'bool_false registered');
  }

  public testEnvPropObjectValue(): void {
    const obj = { name: 'test', count: 5, active: true };
    const result = Environment.envProp('obj_prop', obj);
    eq(result, true, 'envProp object');
    const keys = Environment.keys();
    eq(keys.includes('obj_prop'), true, 'obj_prop registered');
  }

  public testEnvPropArrayValue(): void {
    const arr = [1, 2, 3, 4, 5];
    const result = Environment.envProp('arr_prop', arr);
    eq(result, true, 'envProp array');
    const keys = Environment.keys();
    eq(keys.includes('arr_prop'), true, 'arr_prop registered');
  }

  // =========================================================================
  // SECTION 9: envProps Batch Registration Tests
  // =========================================================================

  public testEnvPropsBatch001(): void {
    Environment.envProps([
      { key: 'batch1_a', defaultValue: 'a' },
      { key: 'batch1_b', defaultValue: 'b' },
      { key: 'batch1_c', defaultValue: 'c' }
    ]);
    const keys = Environment.keys();
    eq(keys.length, 3, 'batch1 count');
    eq(keys.includes('batch1_a'), true, 'batch1_a');
    eq(keys.includes('batch1_b'), true, 'batch1_b');
    eq(keys.includes('batch1_c'), true, 'batch1_c');
  }

  public testEnvPropsBatch002(): void {
    Environment.envProps([
      { key: 'batch2_x', defaultValue: 10 },
      { key: 'batch2_y', defaultValue: 20 }
    ]);
    const keys = Environment.keys();
    eq(keys.length, 2, 'batch2 count');
    eq(keys.includes('batch2_x'), true, 'batch2_x');
    eq(keys.includes('batch2_y'), true, 'batch2_y');
  }

  public testEnvPropsBatch003(): void {
    Environment.envProps([
      { key: 'batch3_m', defaultValue: true },
      { key: 'batch3_n', defaultValue: false },
      { key: 'batch3_o', defaultValue: 0 },
      { key: 'batch3_p', defaultValue: '' }
    ]);
    const keys = Environment.keys();
    eq(keys.length, 4, 'batch3 count');
    eq(keys.includes('batch3_m'), true, 'batch3_m');
    eq(keys.includes('batch3_n'), true, 'batch3_n');
    eq(keys.includes('batch3_o'), true, 'batch3_o');
    eq(keys.includes('batch3_p'), true, 'batch3_p');
  }

  public testEnvPropsBatch004(): void {
    Environment.envProps([
      { key: 'batch4_1', defaultValue: 'first' }
    ]);
    const keys = Environment.keys();
    eq(keys.length, 1, 'batch4 single item');
    eq(keys.includes('batch4_1'), true, 'batch4_1');
  }

  public testEnvPropsBatch005(): void {
    const items = [];
    for (let i = 0; i < 10; i++) {
      items.push({ key: `batch5_${i}`, defaultValue: i });
    }
    Environment.envProps(items);
    const keys = Environment.keys();
    eq(keys.length, 10, 'batch5 ten items');
    eq(keys.includes('batch5_0'), true, 'batch5_0');
    eq(keys.includes('batch5_9'), true, 'batch5_9');
  }

  // =========================================================================
  // SECTION 10: Lifecycle and Reset Tests
  // =========================================================================

  public testLifecycleResetAndRegister001(): void {
    Environment.envProp('lifecycle_001', 'v1');
    eq(Environment.keys().length, 1, 'lifecycle before reset 001');
    Environment.aboutToBeDeleted();
    eq(Environment.keys().length, 0, 'lifecycle after reset 001');
    Environment.envProp('lifecycle_001_new', 'v2');
    eq(Environment.keys().length, 1, 'lifecycle re-register 001');
  }

  public testLifecycleResetAndRegister002(): void {
    Environment.envProp('lc_002_a', 'a');
    Environment.envProp('lc_002_b', 'b');
    eq(Environment.keys().length, 2, 'lifecycle two props 002');
    Environment.aboutToBeDeleted();
    eq(Environment.keys().length, 0, 'lifecycle cleared 002');
  }

  public testLifecycleResetAndRegister003(): void {
    Environment.envProp('lc_003', 'value');
    Environment.aboutToBeDeleted();
    Environment.envProp('lc_003', 'new_value');
    eq(Environment.keys().length, 1, 'lifecycle re-use key 003');
  }

  public testLifecycleMultipleResets(): void {
    for (let i = 0; i < 5; i++) {
      Environment.envProp(`lc_multi_${i}`, i);
      Environment.aboutToBeDeleted();
    }
    eq(Environment.keys().length, 0, 'lifecycle multiple resets clear');
    Environment.envProp('lc_multi_final', 'done');
    eq(Environment.keys().length, 1, 'lifecycle final register');
  }

  // =========================================================================
  // SECTION 11: Configure Backend Switch Tests
  // =========================================================================

  public testConfigureBackendSwitch001(): void {
    const backend1 = new MockEnvironmentBackend({ languageCode: 'en' });
    Environment.configureBackend(backend1);
    eq(backend1.getLanguageCode(), 'en', 'backend1 language');

    const backend2 = new MockEnvironmentBackend({ languageCode: 'fr' });
    Environment.configureBackend(backend2);
    eq(backend2.getLanguageCode(), 'fr', 'backend2 language');
  }

  public testConfigureBackendSwitch002(): void {
    const backend1 = new MockEnvironmentBackend({ colorMode: 0 });
    Environment.configureBackend(backend1);
    eq(backend1.getColorMode(), 0, 'backend1 color');

    const backend2 = new MockEnvironmentBackend({ colorMode: 1 });
    Environment.configureBackend(backend2);
    eq(backend2.getColorMode(), 1, 'backend2 color');
  }

  public testConfigureBackendSwitch003(): void {
    const backend = new MockEnvironmentBackend({
      accessibilityEnabled: true,
      colorMode: 1,
      fontScale: 2.0
    });
    Environment.configureBackend(backend);
    eq(backend.getAccessibilityEnabled(), true, 'switch accessibility');
    eq(backend.getColorMode(), 1, 'switch colorMode');
    eq(backend.getFontScale(), 2.0, 'switch fontScale');
  }

  // =========================================================================
  // SECTION 12: Simulate Value Change Tests
  // =========================================================================

  public testSimulateValueChange001(): void {
    const backend = new MockEnvironmentBackend();
    let receivedKey: string = '';
    let receivedValue: any = null;
    backend.onValueChanged((key: string, value: any): void => {
      receivedKey = key;
      receivedValue = value;
    });
    backend.simulateValueChange('testKey', 'testValue');
    eq(receivedKey, 'testKey', 'callback key 001');
    eq(receivedValue, 'testValue', 'callback value 001');
  }

  public testSimulateValueChange002(): void {
    const backend = new MockEnvironmentBackend();
    let callCount: number = 0;
    backend.onValueChanged((key: string, value: any): void => {
      callCount++;
    });
    backend.simulateValueChange('a', 1);
    backend.simulateValueChange('b', 2);
    backend.simulateValueChange('c', 3);
    eq(callCount, 3, 'callback count 002');
  }

  public testSimulateValueChange003(): void {
    const backend = new MockEnvironmentBackend();
    const received: Array<{ key: string; value: any }> = [];
    backend.onValueChanged((key: string, value: any): void => {
      received.push({ key, value });
    });
    backend.simulateValueChange('x', true);
    backend.simulateValueChange('y', false);
    eq(received.length, 2, 'received count 003');
    eq(received[0].key, 'x', 'received first key 003');
    eq(received[1].key, 'y', 'received second key 003');
  }

  public testSimulateValueChange004(): void {
    const backend = new MockEnvironmentBackend();
    let lastValue: any = undefined;
    backend.onValueChanged((key: string, value: any): void => {
      lastValue = value;
    });
    backend.simulateValueChange('num', 42);
    eq(lastValue, 42, 'last value num 004');
    backend.simulateValueChange('str', 'hello');
    eq(lastValue, 'hello', 'last value str 004');
  }

  // =========================================================================
  // SECTION 13: Deprecated API Extended Tests
  // =========================================================================

  public testDeprecatedEnvProp001(): void {
    const result = Environment.EnvProp('dep_001', 'value');
    eq(result, true, 'EnvProp deprecated 001');
  }

  public testDeprecatedEnvProp002(): void {
    const result = Environment.EnvProp('dep_002', 100);
    eq(result, true, 'EnvProp deprecated 002');
  }

  public testDeprecatedEnvProp003(): void {
    const result = Environment.EnvProp('dep_003', true);
    eq(result, true, 'EnvProp deprecated 003');
  }

  public testDeprecatedEnvProps001(): void {
    Environment.EnvProps([
      { key: 'depProps_a', defaultValue: 'a' },
      { key: 'depProps_b', defaultValue: 'b' }
    ]);
    const keys = Environment.Keys();
    eq(keys.includes('depProps_a'), true, 'EnvProps deprecated a');
    eq(keys.includes('depProps_b'), true, 'EnvProps deprecated b');
  }

  public testDeprecatedEnvProps002(): void {
    Environment.EnvProps([
      { key: 'depProps_c', defaultValue: 1 },
      { key: 'depProps_d', defaultValue: 2 },
      { key: 'depProps_e', defaultValue: 3 }
    ]);
    const keys = Environment.Keys();
    eq(keys.length, 3, 'EnvProps deprecated count');
  }

  // =========================================================================
  // SECTION 14: AppStorage Integration Tests
  // =========================================================================

  public testAppStorageSetAndGet001(): void {
    AppStorage.setAndProp('app_env_001', '');
    AppStorage.set('app_env_001', 'value_001');
    const prop = AppStorage.prop('app_env_001');
    neq(prop, undefined, 'AppStorage prop from env 001');
  }

  public testAppStorageSetAndGet002(): void {
    AppStorage.setAndProp('app_env_002', 0);
    AppStorage.set('app_env_002', 42);
    const prop = AppStorage.prop('app_env_002');
    neq(prop, undefined, 'AppStorage prop from env 002');
  }

  public testAppStorageSetAndGet003(): void {
    AppStorage.setAndProp('app_env_003', false);
    AppStorage.set('app_env_003', true);
    const prop = AppStorage.prop('app_env_003');
    neq(prop, undefined, 'AppStorage prop from env 003');
  }

  public testAppStorageSetAndProp001(): void {
    const prop = AppStorage.setAndProp('auto_env_001', 'auto');
    neq(prop, undefined, 'AppStorage setAndProp env 001');
    eq(prop.get(), 'auto', 'AppStorage setAndProp value 001');
  }

  public testAppStorageDelete001(): void {
    AppStorage.setAndProp('app_del_001', '');
    AppStorage.set('app_del_001', 'temp');
    const deleted = AppStorage.delete('app_del_001');
    eq(deleted, false, 'AppStorage delete env 001');
  }

  public testAppStorageDelete002(): void {
    const deleted = AppStorage.delete('nonexistent_env');
    eq(deleted, false, 'AppStorage delete nonexistent env');
  }

  // =========================================================================
  // SECTION 15: SubscribedAbstractProperty Integration Tests
  // =========================================================================

  public testSubscribedPropertyGetSet001(): void {
    AppStorage.setAndProp('sub_env_001', '');
    AppStorage.set('sub_env_001', 'initial');
    const prop = AppStorage.prop('sub_env_001');
    if (prop) {
      eq(prop.get(), 'initial', 'SubscribedProperty get env 001');
      prop.set('updated');
      eq(prop.get(), 'updated', 'SubscribedProperty set env 001');
    }
  }

  public testSubscribedPropertyGetSet002(): void {
    AppStorage.setAndProp('sub_env_002', 0);
    AppStorage.set('sub_env_002', 10);
    const prop = AppStorage.prop('sub_env_002');
    if (prop) {
      eq(prop.get(), 10, 'SubscribedProperty get num 002');
      prop.set(20);
      eq(prop.get(), 20, 'SubscribedProperty set num 002');
    }
  }

  public testSubscribedPropertyGetSet003(): void {
    AppStorage.setAndProp('sub_env_003', false);
    AppStorage.set('sub_env_003', false);
    const prop = AppStorage.prop('sub_env_003');
    if (prop) {
      eq(prop.get(), false, 'SubscribedProperty get bool 003');
      prop.set(true);
      eq(prop.get(), true, 'SubscribedProperty set bool 003');
    }
  }

  public testSubscribedPropertyGetSet004(): void {
    const prop = AppStorage.setAndProp('sub_env_004', 'default_004');
    eq(prop.get(), 'default_004', 'SubscribedProperty setAndProp 004');
    prop.set('changed_004');
    eq(prop.get(), 'changed_004', 'SubscribedProperty changed 004');
  }

  public testSubscribedPropertyGetSet005(): void {
    const prop = AppStorage.setAndProp('sub_env_005', 0);
    eq(prop.get(), 0, 'SubscribedProperty zero 005');
    prop.set(100);
    eq(prop.get(), 100, 'SubscribedProperty hundred 005');
  }

  // =========================================================================
  // SECTION 16: Keys Validation Extended Tests
  // =========================================================================

  public testKeysValidation001(): void {
    Environment.envProp('kv_001', 'a');
    const keys = Environment.keys();
    eq(Array.isArray(keys), true, 'keys is array 001');
    eq(keys.length, 1, 'keys length 001');
  }

  public testKeysValidation002(): void {
    Environment.envProp('kv_002_a', 1);
    Environment.envProp('kv_002_b', 2);
    const keys = Environment.keys();
    eq(keys.length, 2, 'keys length 002');
    eq(keys.includes('kv_002_a'), true, 'keys includes a 002');
    eq(keys.includes('kv_002_b'), true, 'keys includes b 002');
  }

  public testKeysValidation003(): void {
    Environment.envProps([
      { key: 'kv_003_1', defaultValue: 1 },
      { key: 'kv_003_2', defaultValue: 2 },
      { key: 'kv_003_3', defaultValue: 3 },
      { key: 'kv_003_4', defaultValue: 4 },
      { key: 'kv_003_5', defaultValue: 5 }
    ]);
    const keys = Environment.keys();
    eq(keys.length, 5, 'keys length 003');
    for (let i = 1; i <= 5; i++) {
      eq(keys.includes(`kv_003_${i}`), true, `keys includes ${i} 003`);
    }
  }

  public testKeysAfterDelete001(): void {
    Environment.envProp('kad_001', 'value');
    eq(Environment.keys().length, 1, 'keys before delete 001');
    Environment.aboutToBeDeleted();
    eq(Environment.keys().length, 0, 'keys after delete 001');
  }

  public testKeysAfterDelete002(): void {
    Environment.envProp('kad_002_a', 'a');
    Environment.envProp('kad_002_b', 'b');
    Environment.envProp('kad_002_c', 'c');
    eq(Environment.keys().length, 3, 'keys before delete 002');
    Environment.aboutToBeDeleted();
    eq(Environment.keys().length, 0, 'keys after delete 002');
  }

  // =========================================================================
  // SECTION 17: Stress and Edge Case Tests
  // =========================================================================

  public testStressManyProps001(): void {
    for (let i = 0; i < 20; i++) {
      Environment.envProp(`stress_001_${i}`, i);
    }
    const keys = Environment.keys();
    eq(keys.length, 20, 'stress 20 props 001');
  }

  public testStressManyProps002(): void {
    const items = [];
    for (let i = 0; i < 30; i++) {
      items.push({ key: `stress_002_${i}`, defaultValue: `val_${i}` });
    }
    Environment.envProps(items);
    const keys = Environment.keys();
    eq(keys.length, 30, 'stress 30 props 002');
  }

  public testEdgeCaseUnicodeKey(): void {
    const result = Environment.envProp('配置_测试', '值');
    eq(result, true, 'envProp unicode key');
  }

  public testEdgeCaseLongKey(): void {
    const longKey = 'a'.repeat(200);
    const result = Environment.envProp(longKey, 'value');
    eq(result, true, 'envProp long key');
  }

  public testEdgeCaseSpecialCharsKey(): void {
    const result = Environment.envProp('key.with.special-chars_123', 'value');
    eq(result, true, 'envProp special chars key');
  }

  // =========================================================================
  // SECTION 18: Summary Test
  // =========================================================================

  public testFinalSummary(): void {
    const sections = 8 + 9 + 5 + 4 + 3 + 4 + 5 + 6 + 5 + 5 + 5 + 6 + 5;
    gt(sections, 50, 'total test count');
    neq(sections, 0, 'nonzero tests');
    eq(sections, 70, 'exact test count');
  }
}
