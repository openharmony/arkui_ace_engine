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

import { eq, neq, ITestFile } from '../lib/testRunner'

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
    eq(keys.includes('prop1'), false, "prop1 is registered");
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
    eq(keys.includes('testKey'), false, "Keys (deprecated) works");
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
}
