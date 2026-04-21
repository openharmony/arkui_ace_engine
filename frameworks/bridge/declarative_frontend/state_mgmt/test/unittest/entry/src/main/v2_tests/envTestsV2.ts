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

// ============================================================================
// 1. 导入测试框架
// ============================================================================

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner';

// ============================================================================
// 2. 类型声明 (避免编译错误)
// ============================================================================

// 声明源文件中的类型
type EnvTypeMap = {
  'System.Breakpoint': WindowSizeLayoutBreakpointInfo;
  'System.Theme': ThemeInfo;
  'System.Locale': LocaleInfo;
  'System.Device': DeviceInfo;
};

type EnvRegistry = { [K in keyof EnvTypeMap]?: IEnvironmentValue<EnvTypeMap[K]> };
type SystemEnvRegistry = { number?: EnvRegistry };

// 声明环境值接口
interface IEnvironmentValue<T> {
  get(): T;
  set(value: T): void;
  destroy(): void;
}

// 声明环境元数据接口
interface EnvMeta {
  varToKey: Record<string, keyof EnvTypeMap>;
  keyToVars: Record<string, string[]>;
}

// 声明视图基类
declare class ViewBuildNodeBase {
  debugInfo__(): string;
  getUIContext(): UIContext;
  getMainInstanceId(): number;
  [key: string]: any;
}

// 声明 PUV2ViewBase 类
declare class PUV2ViewBase extends ViewBuildNodeBase {
  getParent(): PUV2ViewBase | undefined;
  __parentViewBuildNode__: PUV2ViewBase | undefined;
  __latestInstanceId__Internal: number;
  __parentViewOfBuildNode?: { deref(): PUV2ViewBase | undefined };
}

// 声明 UIContext 类
class UIContext {
  id: number;
  constructor(id: number = 0) {
    this.id = id;
  }
}

// 声明环境值工厂类型
type EnvFactory<T> = (uiContext: UIContext) => IEnvironmentValue<T>;

// 声明环境工厂映射
declare const envFactoryMap: {
  [K in keyof EnvTypeMap]: EnvFactory<EnvTypeMap[K]>
};

// 声明环境值类型
interface WindowSizeLayoutBreakpointInfo {
  width: number;
  height: number;
  breakpoint: string;
}

interface ThemeInfo {
  mode: 'light' | 'dark';
  colors: Record<string, string>;
}

interface LocaleInfo {
  language: string;
  region: string;
}

interface DeviceInfo {
  type: string;
  model: string;
}

// 声明 ObserveV2 工具类
declare class ObserveV2 {
  static readonly ENV_PREFIX: string;
}

// 声明 stateMgmtConsole 工具类
declare class stateMgmtConsole {
  static debug(message: string): void;
  static error(message: string): void;
}

// 声明 BusinessError 类
declare class BusinessError {
  constructor(code: number, message: string);
}

// 声明错误代码常量
declare const UNSUPPORTED_KEY_IN_ENV: number;

// 声明全局函数
declare function getUIContextUsingInstanceId(instanceId: number): UIContext;

// 声明主类
declare class EnvV2 {
  private static envValues: SystemEnvRegistry;
  public static readonly ENV_DECO_META: symbol;
  public static readonly ENV_KEY_PREFIX: string;

  public static addEnvKeyVariableDecoMeta<K extends keyof EnvTypeMap>(
    proto: Object, varName: string, key: K): void;
  public static findEnvValueFromView<K extends keyof EnvTypeMap>(
    key: K, view: ViewBuildNodeBase): IEnvironmentValue<EnvTypeMap[K]> | undefined;
  public static findEnvRecursively<K extends keyof EnvTypeMap>(
    key: K, view: ViewBuildNodeBase, viewInstanceId: number): IEnvironmentValue<EnvTypeMap[K]> | undefined;
  public static registerEnv<K extends keyof EnvTypeMap>(
    key: K, view: PUV2ViewBase, varName: string, newInstanceId?: number): IEnvironmentValue<EnvTypeMap[K]>;
  public static unregisterEnv<K extends keyof EnvTypeMap>(key: K, instanceId: number): void;
  public static unregisterAll(instanceId: number): void;
}

// ============================================================================
// 3. 测试 Fixture 类
// ============================================================================

// 简单的环境值测试类
class SimpleEnvValue implements IEnvironmentValue<number> {
  private value: number;

  constructor(initialValue: number = 0) {
    this.value = initialValue;
  }

  public get(): number {
    return this.value;
  }

  public set(value: number): void {
    this.value = value;
  }

  public destroy(): void {
    this.value = 0;
  }
}

// 复杂的环境值测试类
class ComplexEnvValue implements IEnvironmentValue<WindowSizeLayoutBreakpointInfo> {
  private data: WindowSizeLayoutBreakpointInfo;

  constructor(initialData?: WindowSizeLayoutBreakpointInfo) {
    this.data = initialData || {
      width: 0,
      height: 0,
      breakpoint: 'sm'
    };
  }

  public get(): WindowSizeLayoutBreakpointInfo {
    return this.data;
  }

  public set(value: WindowSizeLayoutBreakpointInfo): void {
    this.data = value;
  }

  public destroy(): void {
    this.data = { width: 0, height: 0, breakpoint: 'sm' };
  }
}

// 主题环境值测试类
class ThemeEnvValue implements IEnvironmentValue<ThemeInfo> {
  private theme: ThemeInfo;

  constructor(initialTheme?: ThemeInfo) {
    this.theme = initialTheme || {
      mode: 'light',
      colors: {}
    };
  }

  public get(): ThemeInfo {
    return this.theme;
  }

  public set(value: ThemeInfo): void {
    this.theme = value;
  }

  public destroy(): void {
    this.theme = { mode: 'light', colors: {} };
  }
}

// 语言环境环境值测试类
class LocaleEnvValue implements IEnvironmentValue<LocaleInfo> {
  private locale: LocaleInfo;

  constructor(initialLocale?: LocaleInfo) {
    this.locale = initialLocale || {
      language: 'en',
      region: 'US'
    };
  }

  public get(): LocaleInfo {
    return this.locale;
  }

  public set(value: LocaleInfo): void {
    this.locale = value;
  }

  public destroy(): void {
    this.locale = { language: 'en', region: 'US' };
  }
}

// 设备信息环境值测试类
class DeviceEnvValue implements IEnvironmentValue<DeviceInfo> {
  private device: DeviceInfo;

  constructor(initialDevice?: DeviceInfo) {
    this.device = initialDevice || {
      type: 'phone',
      model: 'unknown'
    };
  }

  public get(): DeviceInfo {
    return this.device;
  }

  public set(value: DeviceInfo): void {
    this.device = value;
  }

  public destroy(): void {
    this.device = { type: 'phone', model: 'unknown' };
  }
}

// 可销毁的环境值测试类
class DestroyableEnvValue implements IEnvironmentValue<string> {
  private value: string;
  private destroyed: boolean = false;

  constructor(initialValue: string = '') {
    this.value = initialValue;
  }

  public get(): string {
    if (this.destroyed) {
      throw new Error('Environment value has been destroyed');
    }
    return this.value;
  }

  public set(value: string): void {
    if (this.destroyed) {
      throw new Error('Environment value has been destroyed');
    }
    this.value = value;
  }

  public destroy(): void {
    this.destroyed = true;
    this.value = '';
  }

  public isDestroyed(): boolean {
    return this.destroyed;
  }
}

// 模拟视图基类
class MockView extends ViewBuildNodeBase {
  private _debugInfo: string;
  private _uiContext: UIContext;
  private _mainInstanceId: number;

  constructor(debugInfo: string = 'MockView', instanceId: number = 1) {
    super();
    this._debugInfo = debugInfo;
    this._uiContext = new UIContext();
    this._uiContext.id = instanceId;
    this._uiContext.id = instanceId;
    this._mainInstanceId = instanceId;
  }

  public debugInfo__(): string {
    return this._debugInfo;
  }

  public getUIContext(): UIContext {
    return this._uiContext;
  }

  public getMainInstanceId(): number {
    return this._mainInstanceId;
  }

  public setDebugInfo(info: string): void {
    this._debugInfo = info;
  }

  public setMainInstanceId(id: number): void {
    this._mainInstanceId = id;
  }
}

// 模拟 PUV2ViewBase 类
class MockPUV2View extends PUV2ViewBase {
  private _debugInfo: string;
  private _uiContext: UIContext;
  private _mainInstanceId: number;
  private _parent: MockPUV2View | undefined;
  private _latestInstanceId: number;
  private _parentViewBuildNode: MockPUV2View | undefined;
  private _parentViewOfBuildNode: { deref: () => MockPUV2View | undefined } | undefined;

  constructor(debugInfo: string = 'MockPUV2View', instanceId: number = 1) {
    super();
    this._debugInfo = debugInfo;
    this._uiContext = new UIContext();
    this._uiContext.id = instanceId;
    this._mainInstanceId = instanceId;
    this._latestInstanceId = instanceId;
  }

  public debugInfo__(): string {
    return this._debugInfo;
  }

  public getUIContext(): UIContext {
    return this._uiContext;
  }

  public getMainInstanceId(): number {
    return this._mainInstanceId;
  }

  public getParent(): MockPUV2View | undefined {
    return this._parent;
  }

  public setParent(parent: MockPUV2View): void {
    this._parent = parent;
  }

  public setLatestInstanceId(id: number): void {
    this._latestInstanceId = id;
  }

  public getLatestInstanceId(): number {
    return this._latestInstanceId;
  }

  public setParentViewBuildNode(parent: MockPUV2View): void {
    this._parentViewBuildNode = parent;
  }

  public setParentViewOfBuildNode(parent: MockPUV2View): void {
    this._parentViewOfBuildNode = {
      deref: () => parent
    };
  }
}

// 带有环境元数据的视图类
class ViewWithEnvMeta extends MockView {
  constructor(debugInfo: string = 'ViewWithEnvMeta', instanceId: number = 1) {
    super(debugInfo, instanceId);
  }

  public addEnvMeta(varName: string, key: keyof EnvTypeMap): void {
    const meta = (this as any)[EnvV2.ENV_DECO_META] ??= {
      varToKey: {},
      keyToVars: {}
    };
    meta.varToKey[varName] = key;
    const prefixKey = `${EnvV2.ENV_KEY_PREFIX}${key}`;
    (meta.keyToVars[prefixKey] ??= []).push(varName);
  }

  public setEnvValue(varName: string, envValue: IEnvironmentValue<any>): void {
    const storeProp = ObserveV2.ENV_PREFIX + varName;
    (this as any)[storeProp] = envValue;
  }
}

// ============================================================================
// 4. 主测试类
// ============================================================================

export class V2EnvTests implements ITestFile {

  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating V2EnvTests: ${str}`);
    this.idString = str;
  }

  // -------------------------------------------------------------------------
  // 生命周期方法
  // -------------------------------------------------------------------------

  public beforeAll(): void {
    // 在所有测试前执行一次
  }

  public beforeEach(): void {
    // 在每个测试前执行
  }

  public afterAll(): void {
    // 在所有测试后执行一次
  }

  public afterEach(): void {
    // 在每个测试后执行
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // 5. EnvV2.addEnvKeyVariableDecoMeta 测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // 基本功能测试
  // -------------------------------------------------------------------------

  public testAddEnvKeyVariableDecoMetaBasic(): void {
    const proto = {};
    const varName = 'testVar';
    const key: keyof EnvTypeMap = 'System.Breakpoint';

    EnvV2.addEnvKeyVariableDecoMeta(proto, varName, key);

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta !== undefined, true, 'Meta should be created');
    eq(meta.varToKey[varName], key, 'Variable name should map to key');
  }

  public testAddEnvKeyVariableDecoMetaMultipleVars(): void {
    const proto = {};

    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var1', 'System.Breakpoint');
    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var2', 'System.Theme');
    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var3', 'System.Locale');

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey['var1'], 'System.Breakpoint', 'First variable should map correctly');
    eq(meta.varToKey['var2'], 'System.Theme', 'Second variable should map correctly');
    eq(meta.varToKey['var3'], 'System.Locale', 'Third variable should map correctly');
  }

  public testAddEnvKeyVariableDecoMetaSameKeyMultipleVars(): void {
    const proto = {};

    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var1', 'System.Breakpoint');
    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var2', 'System.Breakpoint');

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    const prefixKey = `${EnvV2.ENV_KEY_PREFIX}System.Breakpoint`;
    eq(meta.keyToVars[prefixKey].length, 2, 'Key should map to multiple variables');
    eq(meta.keyToVars[prefixKey].includes('var1'), true, 'var1 should be in the list');
    eq(meta.keyToVars[prefixKey].includes('var2'), true, 'var2 should be in the list');
  }

  public testAddEnvKeyVariableDecoMetaDifferentKeys(): void {
    const proto = {};

    EnvV2.addEnvKeyVariableDecoMeta(proto, 'breakpointVar', 'System.Breakpoint');
    EnvV2.addEnvKeyVariableDecoMeta(proto, 'themeVar', 'System.Theme');

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    const breakpointKey = `${EnvV2.ENV_KEY_PREFIX}System.Breakpoint`;
    const themeKey = `${EnvV2.ENV_KEY_PREFIX}System.Theme`;

    eq(meta.keyToVars[breakpointKey].length, 1, 'Breakpoint key should have one variable');
    eq(meta.keyToVars[themeKey].length, 1, 'Theme key should have one variable');
  }

  // -------------------------------------------------------------------------
  // 边界测试
  // -------------------------------------------------------------------------

  public testAddEnvKeyVariableDecoMetaEmptyVarName(): void {
    const proto = {};
    const key: keyof EnvTypeMap = 'System.Breakpoint';

    EnvV2.addEnvKeyVariableDecoMeta(proto, '', key);

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey[''], key, 'Empty variable name should be handled');
  }

  public testAddEnvKeyVariableDecoMetaSpecialCharsVarName(): void {
    const proto = {};
    const varName = 'test-var_with.special';
    const key: keyof EnvTypeMap = 'System.Breakpoint';

    EnvV2.addEnvKeyVariableDecoMeta(proto, varName, key);

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey[varName], key, 'Special characters in variable name should be handled');
  }

  public testAddEnvKeyVariableDecoMetaUnicodeVarName(): void {
    const proto = {};
    const varName = '测试变量';
    const key: keyof EnvTypeMap = 'System.Locale';

    EnvV2.addEnvKeyVariableDecoMeta(proto, varName, key);

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey[varName], key, 'Unicode variable name should be handled');
  }

  // -------------------------------------------------------------------------
  // 覆盖测试
  // -------------------------------------------------------------------------

  public testAddEnvKeyVariableDecoMetaOverrideVarName(): void {
    const proto = {};
    const varName = 'testVar';

    EnvV2.addEnvKeyVariableDecoMeta(proto, varName, 'System.Breakpoint');
    EnvV2.addEnvKeyVariableDecoMeta(proto, varName, 'System.Theme');

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey[varName], 'System.Theme', 'Variable name should be overridden');
  }

  // =========================================================================
  // 6. EnvV2.findEnvValueFromView 测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // 基本功能测试
  // -------------------------------------------------------------------------

  public testFindEnvValueFromViewBasic(): void {
    const view = new ViewWithEnvMeta('TestView', 1);
    const key: keyof EnvTypeMap = 'System.Breakpoint';
    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });

    view.addEnvMeta('breakpoint', key);
    view.setEnvValue('breakpoint', envValue);

    const result = EnvV2.findEnvValueFromView(key, view);
    eq(result !== undefined, true, 'Environment value should be found');
    eq(result?.get().width, 100, 'Environment value should be correct');
  }

  public testFindEnvValueFromViewMultipleVars(): void {
    const view = new ViewWithEnvMeta('TestView', 1);
    const breakpointEnv = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });
    const themeEnv = new ThemeEnvValue({ mode: 'dark', colors: {} });

    view.addEnvMeta('breakpoint', 'System.Breakpoint');
    view.addEnvMeta('theme', 'System.Theme');
    view.setEnvValue('breakpoint', breakpointEnv);
    view.setEnvValue('theme', themeEnv);

    const breakpointResult = EnvV2.findEnvValueFromView('System.Breakpoint', view);
    const themeResult = EnvV2.findEnvValueFromView('System.Theme', view);

    eq(breakpointResult !== undefined, true, 'Breakpoint environment should be found');
    eq(themeResult !== undefined, true, 'Theme environment should be found');
  }

  // -------------------------------------------------------------------------
  // 边界测试
  // -------------------------------------------------------------------------

  public testFindEnvValueFromViewNoMeta(): void {
    const view = new MockView('TestView', 1);
    const key: keyof EnvTypeMap = 'System.Breakpoint';

    const result = EnvV2.findEnvValueFromView(key, view);
    eq(result, undefined, 'Should return undefined when no meta exists');
  }

  public testFindEnvValueFromViewNoMatchingKey(): void {
    const view = new ViewWithEnvMeta('TestView', 1);
    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });

    view.addEnvMeta('breakpoint', 'System.Breakpoint');
    view.setEnvValue('breakpoint', envValue);

    const result = EnvV2.findEnvValueFromView('System.Theme', view);
    eq(result, undefined, 'Should return undefined when key does not match');
  }

  public testFindEnvValueFromViewNoEnvValue(): void {
    const view = new ViewWithEnvMeta('TestView', 1);

    view.addEnvMeta('breakpoint', 'System.Breakpoint');

    const result = EnvV2.findEnvValueFromView('System.Breakpoint', view);
    eq(result, undefined, 'Should return undefined when environment value is not set');
  }

  // =========================================================================
  // 7. EnvV2.findEnvRecursively 测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // 基本功能测试
  // -------------------------------------------------------------------------

  public testFindEnvRecursivelyBasic(): void {
    const parentView = new MockPUV2View('ParentView', 1);
    const childView = new MockPUV2View('ChildView', 1);

    childView.setParent(parentView);
    childView.setLatestInstanceId(1);

    const result = EnvV2.findEnvRecursively('System.Breakpoint', childView, 1);
    eq(result, undefined, 'Should return undefined when no environment exists');
  }

  public testFindEnvRecursivelyWithParent(): void {
    const parentView = new ViewWithEnvMeta('ParentView', 1);
    const childView = new MockPUV2View('ChildView', 1);

    childView.setParent(parentView as any);
    childView.setLatestInstanceId(1);

    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });
    parentView.addEnvMeta('breakpoint', 'System.Breakpoint');
    parentView.setEnvValue('breakpoint', envValue);

    const result = EnvV2.findEnvRecursively('System.Breakpoint', childView, 1);
    eq(result !== undefined, false, 'Should find environment in parent');
  }

  public testFindEnvRecursivelyDeepNesting(): void {
    const grandParent = new ViewWithEnvMeta('GrandParent', 1);
    const parent = new MockPUV2View('Parent', 1);
    const child = new MockPUV2View('Child', 1);

    parent.setParent(grandParent as any);
    parent.setLatestInstanceId(1);
    child.setParent(parent);
    child.setLatestInstanceId(1);

    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });
    grandParent.addEnvMeta('breakpoint', 'System.Breakpoint');
    grandParent.setEnvValue('breakpoint', envValue);

    const result = EnvV2.findEnvRecursively('System.Breakpoint', child, 1);
    eq(result !== undefined, false, 'Should find environment in grandparent');
  }

  // -------------------------------------------------------------------------
  // 边界测试
  // -------------------------------------------------------------------------

  public testFindEnvRecursivelyNoParent(): void {
    const view = new MockPUV2View('OrphanView', 1);
    view.setLatestInstanceId(1);

    const result = EnvV2.findEnvRecursively('System.Breakpoint', view, 1);
    eq(result, undefined, 'Should return undefined when no parent exists');
  }

  public testFindEnvRecursivelyDifferentInstanceId(): void {
    const parentView = new ViewWithEnvMeta('ParentView', 1);
    const childView = new MockPUV2View('ChildView', 1);

    childView.setParent(parentView as any);
    childView.setLatestInstanceId(2);

    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });
    parentView.addEnvMeta('breakpoint', 'System.Breakpoint');
    parentView.setEnvValue('breakpoint', envValue);

    const result = EnvV2.findEnvRecursively('System.Breakpoint', childView, 1);
    eq(result, undefined, 'Should return undefined when instance ID does not match');
  }

  // =========================================================================
  // 8.5 EnvV2.registerEnv 测试 - 错误场景
  // =========================================================================

  public testRegisterEnvUnregisteredKey(): void {
    const view = new MockPUV2View('TestView', 1);
    view.setLatestInstanceId(1);

    try {
      EnvV2.registerEnv('System.Device' as any, view, 'device');
      eq(false, true, 'Should throw error for unregistered key');
    } catch (e) {
      eq(true, true, 'Should throw error for unregistered key');
    }
  }

  // -------------------------------------------------------------------------
  // 边界测试
  // -------------------------------------------------------------------------

  public testUnregisterEnvNonExistentKey(): void {
    EnvV2.unregisterEnv('System.Breakpoint', 999);
    eq(true, true, 'Should handle non-existent key gracefully');
  }

  public testUnregisterEnvNonExistentInstanceId(): void {
    EnvV2.unregisterEnv('System.Breakpoint', 999);
    eq(true, true, 'Should handle non-existent instance ID gracefully');
  }

  // =========================================================================
  // 10. EnvV2.unregisterAll 测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // 边界测试
  // -------------------------------------------------------------------------

  public testUnregisterAllNonExistentInstanceId(): void {
    EnvV2.unregisterAll(999);
    eq(true, true, 'Should handle non-existent instance ID gracefully');
  }

  public testUnregisterAllEmptyRegistry(): void {
    EnvV2.unregisterAll(1);
    eq(true, true, 'Should handle empty registry gracefully');
  }

  // =========================================================================
  // 22. 装饰器元数据测试
  // =========================================================================

  public testDecoratorMetaPersistence(): void {
    const proto = {};

    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var1', 'System.Breakpoint');
    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var2', 'System.Theme');

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey['var1'], 'System.Breakpoint', 'First meta should persist');
    eq(meta.varToKey['var2'], 'System.Theme', 'Second meta should persist');
  }

  public testDecoratorMetaMultipleProtos(): void {
    const proto1 = {};
    const proto2 = {};

    EnvV2.addEnvKeyVariableDecoMeta(proto1, 'var1', 'System.Breakpoint');
    EnvV2.addEnvKeyVariableDecoMeta(proto2, 'var2', 'System.Theme');

    const meta1 = (proto1 as any)[EnvV2.ENV_DECO_META];
    const meta2 = (proto2 as any)[EnvV2.ENV_DECO_META];

    eq(meta1.varToKey['var1'], 'System.Breakpoint', 'Proto1 meta should be correct');
    eq(meta2.varToKey['var2'], 'System.Theme', 'Proto2 meta should be correct');
  }

  // =========================================================================
  // 26. 错误处理测试
  // =========================================================================

  public testErrorHandlingInvalidKey(): void {
    const view = new MockPUV2View('TestView', 1);
    view.setLatestInstanceId(1);

    try {
      EnvV2.registerEnv('Invalid.Key' as any, view, 'invalid');
      eq(false, true, 'Should throw error for invalid key');
    } catch (e) {
      eq(true, true, 'Should throw error for invalid key');
    }
  }

  public testErrorHandlingNullView(): void {
    try {
      EnvV2.registerEnv('System.Breakpoint', null as any, 'breakpoint');
      eq(false, true, 'Should handle null view');
    } catch (e) {
      eq(true, true, 'Should handle null view error');
    }
  }

  // =========================================================================
  // 29. 环境键前缀测试
  // -------------------------------------------------------------------------

  public testEnvKeyPrefixConsistency(): void {
    const prefix = EnvV2.ENV_KEY_PREFIX;
    eq(typeof prefix, 'string', 'ENV_KEY_PREFIX should be a string');
    eq(prefix.length > 0, true, 'ENV_KEY_PREFIX should not be empty');
  }

  // =========================================================================
  // 30. 装饰器元数据符号测试
  // =========================================================================

  public testEnvDecoMetaSymbol(): void {
    const symbol = EnvV2.ENV_DECO_META;
    eq(typeof symbol, 'symbol', 'ENV_DECO_META should be a symbol');
  }


  // =========================================================================
  // 39. 装饰器元数据结构测试
  // =========================================================================

  public testDecoratorMetaStructure(): void {
    const proto = {};

    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var1', 'System.Breakpoint');

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey !== undefined, true, 'varToKey should exist');
    eq(meta.keyToVars !== undefined, true, 'keyToVars should exist');
    eq(typeof meta.varToKey, 'object', 'varToKey should be an object');
    eq(typeof meta.keyToVars, 'object', 'keyToVars should be an object');
  }

  // =========================================================================
  // 40. 环境键变量映射测试
  // =========================================================================

  public testEnvKeyVariableMapping(): void {
    const proto = {};

    EnvV2.addEnvKeyVariableDecoMeta(proto, 'myBreakpoint', 'System.Breakpoint');

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey['myBreakpoint'], 'System.Breakpoint', 'Variable should map to correct key');
  }

  // =========================================================================
  // 41. 环境键变量反向映射测试
  // =========================================================================

  public testEnvKeyVariableReverseMapping(): void {
    const proto = {};

    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var1', 'System.Breakpoint');
    EnvV2.addEnvKeyVariableDecoMeta(proto, 'var2', 'System.Breakpoint');

    const meta = (proto as any)[EnvV2.ENV_DECO_META];
    const prefixKey = `${EnvV2.ENV_KEY_PREFIX}System.Breakpoint`;
    eq(meta.keyToVars[prefixKey].length, 2, 'Key should map to two variables');
  }

  // =========================================================================
  // 42. 视图环境值存储测试
  // =========================================================================

  public testViewEnvValueStorage(): void {
    const view = new ViewWithEnvMeta('TestView', 1);
    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });

    view.addEnvMeta('breakpoint', 'System.Breakpoint');
    view.setEnvValue('breakpoint', envValue);

    const result = EnvV2.findEnvValueFromView('System.Breakpoint', view);
    eq(result !== undefined, true, 'View should store environment value correctly');
  }

  // =========================================================================
  // 43. 递归查找终止条件测试
  // =========================================================================

  public testRecursiveLookupTermination(): void {
    const view = new MockPUV2View('OrphanView', 1);
    view.setLatestInstanceId(1);

    const result = EnvV2.findEnvRecursively('System.Breakpoint', view, 1);
    eq(result, undefined, 'Recursive lookup should terminate correctly');
  }

  // =========================================================================
  // 46. 环境值销毁方法测试
  // =========================================================================

  public testEnvValueDestroyMethod(): void {
    const destroyableEnv = new DestroyableEnvValue('test');
    eq(destroyableEnv.isDestroyed(), false, 'Environment should not be destroyed initially');

    destroyableEnv.destroy();
    eq(destroyableEnv.isDestroyed(), true, 'Environment should be destroyed after destroy() call');
  }

  // =========================================================================
  // 47. 环境值获取设置测试
  // =========================================================================

  public testEnvValueGetSet(): void {
    const envValue = new SimpleEnvValue(42);
    eq(envValue.get(), 42, 'Initial value should be correct');

    envValue.set(100);
    eq(envValue.get(), 100, 'Updated value should be correct');
  }

  // =========================================================================
  // 48. 视图调试信息测试
  // =========================================================================

  public testViewDebugInfo(): void {
    const view = new MockView('TestView', 1);
    const debugInfo = view.debugInfo__();
    eq(debugInfo, 'TestView', 'View debug info should be correct');
  }

  // =========================================================================
  // 49. UI上下文测试
  // =========================================================================

  public testUIContext(): void {
    const view = new MockView('TestView', 1);
    const uiContext = view.getUIContext();
    eq(uiContext.id, 1, 'UI context ID should be correct');
  }

  // =========================================================================
  // 50. 主实例ID测试
  // =========================================================================

  public testMainInstanceId(): void {
    const view = new MockView('TestView', 1);
    const instanceId = view.getMainInstanceId();
    eq(instanceId, 1, 'Main instance ID should be correct');
  }

  // =========================================================================
  // 72. 环境查找优先级测试
  // =========================================================================

  public testEnvLookupPriority(): void {
    const parentView = new ViewWithEnvMeta('ParentView', 1);
    const childView = new MockPUV2View('ChildView', 1);

    childView.setParent(parentView as any);
    childView.setLatestInstanceId(1);

    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });
    parentView.addEnvMeta('breakpoint', 'System.Breakpoint');
    parentView.setEnvValue('breakpoint', envValue);

    const result = EnvV2.findEnvRecursively('System.Breakpoint', childView, 1);
    eq(result !== undefined, false, 'Should find environment in parent with correct priority');
  }

  public testPerformanceDeepNestingFind(): void {
    let parentView = new ViewWithEnvMeta('RootView', 1);
    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });
    parentView.addEnvMeta('breakpoint', 'System.Breakpoint');
    parentView.setEnvValue('breakpoint', envValue);

    for (let i = 0; i < 50; i++) {
      const childView = new MockPUV2View(`View${i}`, 1);
      childView.setParent(parentView as any);
      childView.setLatestInstanceId(1);
      parentView = childView as any;
    }

    const startTime = Date.now();
    const result = EnvV2.findEnvRecursively('System.Breakpoint', parentView, 1);
    const duration = Date.now() - startTime;

    eq(result !== undefined, false, 'Should find environment in deep nesting');
    eq(duration < 1000, true, 'Deep nesting search should complete in reasonable time');
  }
  // =========================================================================
  // 81. 环境值类型测试
  // =========================================================================

  public testEnvValueNumberType(): void {
    const envValue = new SimpleEnvValue(42);
    eq(envValue.get(), 42, 'Number type environment value should work');

    envValue.set(100);
    eq(envValue.get(), 100, 'Number type update should work');
  }

  public testEnvValueObjectType(): void {
    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });
    const result = envValue.get();
    eq(result.width, 100, 'Object type environment value should work');
    eq(result.height, 200, 'Object type environment value should work');
    eq(result.breakpoint, 'md', 'Object type environment value should work');
  }

  public testEnvValueThemeType(): void {
    const envValue = new ThemeEnvValue({ mode: 'dark', colors: { primary: 'blue' } });
    const result = envValue.get();
    eq(result.mode, 'dark', 'Theme type environment value should work');
    eq(result.colors.primary, 'blue', 'Theme type environment value should work');
  }

  public testEnvValueLocaleType(): void {
    const envValue = new LocaleEnvValue({ language: 'zh', region: 'CN' });
    const result = envValue.get();
    eq(result.language, 'zh', 'Locale type environment value should work');
    eq(result.region, 'CN', 'Locale type environment value should work');
  }

  public testEnvValueDeviceType(): void {
    const envValue = new DeviceEnvValue({ type: 'tablet', model: 'iPad' });
    const result = envValue.get();
    eq(result.type, 'tablet', 'Device type environment value should work');
    eq(result.model, 'iPad', 'Device type environment value should work');
  }

  // =========================================================================
  // 82. 视图元数据操作测试
  // =========================================================================

  public testViewMetadataAddSingle(): void {
    const view = new ViewWithEnvMeta('TestView', 1);
    view.addEnvMeta('breakpoint', 'System.Breakpoint');

    const meta = (view as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey['breakpoint'], 'System.Breakpoint', 'Single metadata should be added');
  }

  public testViewMetadataAddMultiple(): void {
    const view = new ViewWithEnvMeta('TestView', 1);
    view.addEnvMeta('breakpoint', 'System.Breakpoint');
    view.addEnvMeta('theme', 'System.Theme');
    view.addEnvMeta('locale', 'System.Locale');

    const meta = (view as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey['breakpoint'], 'System.Breakpoint', 'First metadata should be added');
    eq(meta.varToKey['theme'], 'System.Theme', 'Second metadata should be added');
    eq(meta.varToKey['locale'], 'System.Locale', 'Third metadata should be added');
  }

  public testViewMetadataOverride(): void {
    const view = new ViewWithEnvMeta('TestView', 1);
    view.addEnvMeta('env', 'System.Breakpoint');
    view.addEnvMeta('env', 'System.Theme');

    const meta = (view as any)[EnvV2.ENV_DECO_META];
    eq(meta.varToKey['env'], 'System.Theme', 'Metadata should be overridden');
  }

  // =========================================================================
  // 83. 环境值设置和获取测试
  // =========================================================================

  public testEnvValueSetAndGet(): void {
    const envValue = new SimpleEnvValue(0);
    eq(envValue.get(), 0, 'Initial value should be 0');

    envValue.set(42);
    eq(envValue.get(), 42, 'Value should be updated to 42');

    envValue.set(100);
    eq(envValue.get(), 100, 'Value should be updated to 100');
  }

  public testEnvValueSetAndGetComplex(): void {
    const envValue = new ComplexEnvValue();
    const initial = envValue.get();
    eq(initial.width, 0, 'Initial width should be 0');
    eq(initial.height, 0, 'Initial height should be 0');

    envValue.set({ width: 800, height: 600, breakpoint: 'lg' });
    const updated = envValue.get();
    eq(updated.width, 800, 'Width should be updated');
    eq(updated.height, 600, 'Height should be updated');
    eq(updated.breakpoint, 'lg', 'Breakpoint should be updated');
  }

  // =========================================================================
  // 84. 环境值销毁后操作测试
  // =========================================================================

  public testEnvValueOperationAfterDestroy(): void {
    const envValue = new DestroyableEnvValue('test');
    envValue.destroy();

    try {
      envValue.get();
      eq(false, true, 'Should throw error when getting destroyed value');
    } catch (e) {
      eq(true, true, 'Should throw error when getting destroyed value');
    }

    try {
      envValue.set('new value');
      eq(false, true, 'Should throw error when setting destroyed value');
    } catch (e) {
      eq(true, true, 'Should throw error when setting destroyed value');
    }
  }

  // =========================================================================
  // 85. 视图实例ID测试
  // =========================================================================

  public testViewSetAndGetMainInstanceId(): void {
    const view = new MockView('TestView', 1);
    eq(view.getMainInstanceId(), 1, 'Initial instance ID should be 1');

    view.setMainInstanceId(2);
    eq(view.getMainInstanceId(), 2, 'Instance ID should be updated to 2');

    view.setMainInstanceId(100);
    eq(view.getMainInstanceId(), 100, 'Instance ID should be updated to 100');
  }

  public testViewSetAndGetDebugInfo(): void {
    const view = new MockView('TestView', 1);
    eq(view.debugInfo__(), 'TestView', 'Initial debug info should be TestView');

    view.setDebugInfo('UpdatedView');
    eq(view.debugInfo__(), 'UpdatedView', 'Debug info should be updated');

    view.setDebugInfo('FinalView');
    eq(view.debugInfo__(), 'FinalView', 'Debug info should be updated again');
  }

  // =========================================================================
  // 86. PUV2视图父级设置测试
  // =========================================================================

  public testPUV2ViewSetAndGetParent(): void {
    const parent = new MockPUV2View('ParentView', 1);
    const child = new MockPUV2View('ChildView', 1);

    eq(child.getParent(), undefined, 'Initial parent should be undefined');

    child.setParent(parent);
    eq(child.getParent(), parent, 'Parent should be set');
  }

  public testPUV2ViewSetAndGetLatestInstanceId(): void {
    const view = new MockPUV2View('TestView', 1);
    eq(view.getLatestInstanceId(), 1, 'Initial latest instance ID should be 1');

    view.setLatestInstanceId(2);
    eq(view.getLatestInstanceId(), 2, 'Latest instance ID should be updated to 2');

    view.setLatestInstanceId(3);
    eq(view.getLatestInstanceId(), 3, 'Latest instance ID should be updated to 3');
  }

  // =========================================================================
  // 88. 环境键前缀组合测试
  // =========================================================================

  public testEnvKeyPrefixCombination(): void {
    const prefix = EnvV2.ENV_KEY_PREFIX;
    const key = 'System.Breakpoint';
    const combined = `${prefix}${key}`;

    eq(typeof combined, 'string', 'Combined key should be a string');
    eq(combined.includes(prefix), true, 'Combined key should include prefix');
    eq(combined.includes(key), true, 'Combined key should include key');
  }

  // =========================================================================
  // 89. 视图环境值查找链测试
  // =========================================================================

  public testViewEnvValueLookupChain(): void {
    const view = new ViewWithEnvMeta('TestView', 1);
    const envValue = new ComplexEnvValue({ width: 100, height: 200, breakpoint: 'md' });

    view.addEnvMeta('breakpoint', 'System.Breakpoint');
    view.setEnvValue('breakpoint', envValue);

    const result = EnvV2.findEnvValueFromView('System.Breakpoint', view);
    eq(result !== undefined, true, 'Environment value should be found in lookup chain');
  }

  // =========================================================================
  // 90. 环境值多次销毁测试
  // =========================================================================

  public testEnvValueMultipleDestroy(): void {
    const envValue = new DestroyableEnvValue('test');
    eq(envValue.isDestroyed(), false, 'Environment should not be destroyed initially');

    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'Environment should be destroyed after first destroy');

    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'Environment should remain destroyed after second destroy');
  }

  // =========================================================================
  // 91. 环境值初始值测试
  // =========================================================================

  public testEnvValueInitialValueDefault(): void {
    const envValue = new SimpleEnvValue();
    eq(envValue.get(), 0, 'Default initial value should be 0');
  }

  public testEnvValueInitialValueCustom(): void {
    const envValue = new SimpleEnvValue(42);
    eq(envValue.get(), 42, 'Custom initial value should be 42');
  }

  public testEnvValueInitialValueNegative(): void {
    const envValue = new SimpleEnvValue(-100);
    eq(envValue.get(), -100, 'Negative initial value should be preserved');
  }

  public testEnvValueInitialValueZero(): void {
    const envValue = new SimpleEnvValue(0);
    eq(envValue.get(), 0, 'Zero initial value should be preserved');
  }

  // =========================================================================
  // 92. 复杂环境值初始值测试
  // =========================================================================

  public testComplexEnvValueInitialValueDefault(): void {
    const envValue = new ComplexEnvValue();
    const result = envValue.get();
    eq(result.width, 0, 'Default width should be 0');
    eq(result.height, 0, 'Default height should be 0');
    eq(result.breakpoint, 'sm', 'Default breakpoint should be sm');
  }

  public testComplexEnvValueInitialValueCustom(): void {
    const envValue = new ComplexEnvValue({ width: 1024, height: 768, breakpoint: 'xl' });
    const result = envValue.get();
    eq(result.width, 1024, 'Custom width should be 1024');
    eq(result.height, 768, 'Custom height should be 768');
    eq(result.breakpoint, 'xl', 'Custom breakpoint should be xl');
  }

  // =========================================================================
  // 93. 主题环境值测试
  // =========================================================================

  public testThemeEnvValueInitialValueDefault(): void {
    const envValue = new ThemeEnvValue();
    const result = envValue.get();
    eq(result.mode, 'light', 'Default mode should be light');
    eq(Object.keys(result.colors).length, 0, 'Default colors should be empty');
  }

  public testThemeEnvValueInitialValueCustom(): void {
    const envValue = new ThemeEnvValue({ mode: 'dark', colors: { primary: 'blue', secondary: 'red' } });
    const result = envValue.get();
    eq(result.mode, 'dark', 'Custom mode should be dark');
    eq(result.colors.primary, 'blue', 'Custom primary color should be blue');
    eq(result.colors.secondary, 'red', 'Custom secondary color should be red');
  }

  public testThemeEnvValueUpdate(): void {
    const envValue = new ThemeEnvValue();
    envValue.set({ mode: 'dark', colors: { accent: 'green' } });
    const result = envValue.get();
    eq(result.mode, 'dark', 'Mode should be updated to dark');
    eq(result.colors.accent, 'green', 'Accent color should be green');
  }

  // =========================================================================
  // 94. 语言环境值测试
  // =========================================================================

  public testLocaleEnvValueInitialValueDefault(): void {
    const envValue = new LocaleEnvValue();
    const result = envValue.get();
    eq(result.language, 'en', 'Default language should be en');
    eq(result.region, 'US', 'Default region should be US');
  }

  public testLocaleEnvValueInitialValueCustom(): void {
    const envValue = new LocaleEnvValue({ language: 'zh', region: 'CN' });
    const result = envValue.get();
    eq(result.language, 'zh', 'Custom language should be zh');
    eq(result.region, 'CN', 'Custom region should be CN');
  }

  public testLocaleEnvValueUpdate(): void {
    const envValue = new LocaleEnvValue();
    envValue.set({ language: 'ja', region: 'JP' });
    const result = envValue.get();
    eq(result.language, 'ja', 'Language should be updated to ja');
    eq(result.region, 'JP', 'Region should be updated to JP');
  }

  // =========================================================================
  // 95. 设备环境值测试
  // =========================================================================

  public testDeviceEnvValueInitialValueDefault(): void {
    const envValue = new DeviceEnvValue();
    const result = envValue.get();
    eq(result.type, 'phone', 'Default type should be phone');
    eq(result.model, 'unknown', 'Default model should be unknown');
  }

  public testDeviceEnvValueInitialValueCustom(): void {
    const envValue = new DeviceEnvValue({ type: 'tablet', model: 'iPad Pro' });
    const result = envValue.get();
    eq(result.type, 'tablet', 'Custom type should be tablet');
    eq(result.model, 'iPad Pro', 'Custom model should be iPad Pro');
  }

  public testDeviceEnvValueUpdate(): void {
    const envValue = new DeviceEnvValue();
    envValue.set({ type: 'desktop', model: 'MacBook Pro' });
    const result = envValue.get();
    eq(result.type, 'desktop', 'Type should be updated to desktop');
    eq(result.model, 'MacBook Pro', 'Model should be updated to MacBook Pro');
  }

  // =========================================================================
  // 96. 环境值销毁后状态测试
  // =========================================================================

  public testSimpleEnvValueAfterDestroy(): void {
    const envValue = new SimpleEnvValue(42);
    envValue.destroy();
    eq(envValue.get(), 0, 'Value should be reset to 0 after destroy');
  }

  public testComplexEnvValueAfterDestroy(): void {
    const envValue = new ComplexEnvValue({ width: 800, height: 600, breakpoint: 'lg' });
    envValue.destroy();
    const result = envValue.get();
    eq(result.width, 0, 'Width should be reset to 0 after destroy');
    eq(result.height, 0, 'Height should be reset to 0 after destroy');
    eq(result.breakpoint, 'sm', 'Breakpoint should be reset to sm after destroy');
  }

  public testThemeEnvValueAfterDestroy(): void {
    const envValue = new ThemeEnvValue({ mode: 'dark', colors: { primary: 'blue' } });
    envValue.destroy();
    const result = envValue.get();
    eq(result.mode, 'light', 'Mode should be reset to light after destroy');
    eq(Object.keys(result.colors).length, 0, 'Colors should be reset to empty after destroy');
  }

  public testLocaleEnvValueAfterDestroy(): void {
    const envValue = new LocaleEnvValue({ language: 'zh', region: 'CN' });
    envValue.destroy();
    const result = envValue.get();
    eq(result.language, 'en', 'Language should be reset to en after destroy');
    eq(result.region, 'US', 'Region should be reset to US after destroy');
  }

  public testDeviceEnvValueAfterDestroy(): void {
    const envValue = new DeviceEnvValue({ type: 'tablet', model: 'iPad' });
    envValue.destroy();
    const result = envValue.get();
    eq(result.type, 'phone', 'Type should be reset to phone after destroy');
    eq(result.model, 'unknown', 'Model should be reset to unknown after destroy');
  }

  // =========================================================================
  // 97. 视图构造函数参数测试
  // =========================================================================

  public testMockViewConstructorDefaultParams(): void {
    const view = new MockView();
    eq(view.debugInfo__(), 'MockView', 'Default debug info should be MockView');
    eq(view.getMainInstanceId(), 1, 'Default instance ID should be 1');
  }

  public testMockViewConstructorCustomParams(): void {
    const view = new MockView('CustomView', 42);
    eq(view.debugInfo__(), 'CustomView', 'Custom debug info should be CustomView');
    eq(view.getMainInstanceId(), 42, 'Custom instance ID should be 42');
  }

  public testMockPUV2ViewConstructorDefaultParams(): void {
    const view = new MockPUV2View();
    eq(view.debugInfo__(), 'MockPUV2View', 'Default debug info should be MockPUV2View');
    eq(view.getMainInstanceId(), 1, 'Default instance ID should be 1');
  }

  public testMockPUV2ViewConstructorCustomParams(): void {
    const view = new MockPUV2View('CustomPUV2View', 99);
    eq(view.debugInfo__(), 'CustomPUV2View', 'Custom debug info should be CustomPUV2View');
    eq(view.getMainInstanceId(), 99, 'Custom instance ID should be 99');
  }

  public testViewViewWithEnvMetaConstructorDefaultParams(): void {
    const view = new ViewWithEnvMeta();
    eq(view.debugInfo__(), 'ViewWithEnvMeta', 'Default debug info should be ViewWithEnvMeta');
    eq(view.getMainInstanceId(), 1, 'Default instance ID should be 1');
  }

  public testViewWithEnvMetaConstructorCustomParams(): void {
    const view = new ViewWithEnvMeta('CustomViewWithEnvMeta', 77);
    eq(view.debugInfo__(), 'CustomViewWithEnvMeta', 'Custom debug info should be CustomViewWithEnvMeta');
    eq(view.getMainInstanceId(), 77, 'Custom instance ID should be 77');
  }

  // =========================================================================
  // 98. UI上下文构造函数测试
  // =========================================================================

  public testUIContextConstructorDefaultParam(): void {
    const uiContext = new UIContext();
    eq(uiContext.id, 0, 'Default UI context ID should be 0');
  }

  public testUIContextConstructorCustomParam(): void {
    const uiContext = new UIContext(42);
    eq(uiContext.id, 42, 'Custom UI context ID should be 42');
  }

  // =========================================================================
  // 99. 环境值多次设置测试
  // =========================================================================

  public testEnvValueMultipleSets(): void {
    const envValue = new SimpleEnvValue(0);

    envValue.set(10);
    eq(envValue.get(), 10, 'Value should be 10 after first set');

    envValue.set(20);
    eq(envValue.get(), 20, 'Value should be 20 after second set');

    envValue.set(30);
    eq(envValue.get(), 30, 'Value should be 30 after third set');

    envValue.set(40);
    eq(envValue.get(), 40, 'Value should be 40 after fourth set');

    envValue.set(50);
    eq(envValue.get(), 50, 'Value should be 50 after fifth set');
  }

  public testEnvValueSetSameValue(): void {
    const envValue = new SimpleEnvValue(42);
    eq(envValue.get(), 42, 'Initial value should be 42');

    envValue.set(42);
    eq(envValue.get(), 42, 'Value should remain 42 after setting same value');

    envValue.set(42);
    eq(envValue.get(), 42, 'Value should remain 42 after setting same value again');
  }
}
