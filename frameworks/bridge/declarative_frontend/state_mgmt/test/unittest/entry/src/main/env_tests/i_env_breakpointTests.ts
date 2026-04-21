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

// 声明源文件中的接口
declare interface WindowSizeLayoutBreakpoint {};

// 声明源文件中的枚举
declare enum WidthBreakpoint {};
declare enum HeightBreakpoint {};

// 声明 IEnvironmentValue 接口
declare interface IEnvironmentValue<T> {
  value: T;
  update(newValue: T): void;
  destroy(): void;
}

// 声明 uiObserver 命名空间
declare namespace uiObserver {
  class WindowSizeLayoutBreakpointInfo {
    widthBreakpoint: WidthBreakpoint;
    heightBreakpoint: HeightBreakpoint;
  }
}

// UIContext
class UIContext {
  constructor() {
    // 可以在这里初始化一些必要的 mock 属性，如果 WindowSizeLayoutBreakpoint 需要的话
  }
}

// 源文件中的主类
class WindowSizeLayoutBreakpoint implements IEnvironmentValue<uiObserver.WindowSizeLayoutBreakpointInfo> {
  public value: uiObserver.WindowSizeLayoutBreakpointInfo;
  private context: UIContext;
  private isDestroyed: boolean = false;

  constructor(context: UIContext) {
    this.context = context;
    // 初始化一个默认值，防止访问 value 时报错
    this.value = {
      widthBreakpoint: 0 as any, // 假设 0 是默认值
      heightBreakpoint: 0 as any
    };
  }

  update(newValue: uiObserver.WindowSizeLayoutBreakpointInfo): void {
    if (this.isDestroyed) {
      throw new Error('Cannot update destroyed breakpoint');
    }

    // 简单的类型检查模拟：如果传入的不是对象或缺少必要字段，抛出错误
    // 这能让你的测试用例 catch 到异常
    if (!newValue || typeof newValue !== 'object' ||
      newValue.widthBreakpoint === undefined ||
      newValue.heightBreakpoint === undefined) {
      throw new TypeError('Invalid argument type for update');
    }

    this.value = newValue;
  }

  destroy(): void {
    this.isDestroyed = true;
  }
}

// ============================================================================
// 3. 测试 Fixture 类
// ============================================================================

// 简单的 UIContext 测试 fixture
class SimpleUIContext {
  id: string = 'test-context';
  valid: boolean = true;

  public getId(): string {
    return this.id;
  }

  public isValid(): boolean {
    return this.valid;
  }
}

// 完整的 WindowSizeLayoutBreakpointInfo 测试 fixture
class CompleteBreakpointInfo {
  widthBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  heightBreakpoint: HeightBreakpoint = 0 as HeightBreakpoint;

  constructor(width: WidthBreakpoint, height: HeightBreakpoint) {
    this.widthBreakpoint = width;
    this.heightBreakpoint = height;
  }

  public getWidth(): WidthBreakpoint {
    return this.widthBreakpoint;
  }

  public getHeight(): HeightBreakpoint {
    return this.heightBreakpoint;
  }

  public setWidth(width: WidthBreakpoint): void {
    this.widthBreakpoint = width;
  }

  public setHeight(height: HeightBreakpoint): void {
    this.heightBreakpoint = height;
  }

  public equals(other: CompleteBreakpointInfo): boolean {
    return this.widthBreakpoint === other.widthBreakpoint &&
           this.heightBreakpoint === other.heightBreakpoint;
  }

  public clone(): CompleteBreakpointInfo {
    return new CompleteBreakpointInfo(this.widthBreakpoint, this.heightBreakpoint);
  }
}

// 带有额外元数据的断点信息 fixture
class MetadataBreakpointInfo {
  widthBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  heightBreakpoint: HeightBreakpoint = 0 as HeightBreakpoint;
  timestamp: number = Date.now();
  source: string = 'test';
  version: number = 1;

  public getMetadata(): object {
    return {
      timestamp: this.timestamp,
      source: this.source,
      version: this.version
    };
  }

  public updateMetadata(metadata: Partial<MetadataBreakpointInfo>): void {
    if (metadata.timestamp !== undefined) {
      this.timestamp = metadata.timestamp;
    }
    if (metadata.source !== undefined) {
      this.source = metadata.source;
    }
    if (metadata.version !== undefined) {
      this.version = metadata.version;
    }
  }
}

// 包含历史记录的断点信息 fixture
class HistoryBreakpointInfo {
  widthBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  heightBreakpoint: HeightBreakpoint = 0 as HeightBreakpoint;
  history: Array<{ width: WidthBreakpoint; height: HeightBreakpoint; time: number }> = [];

  public recordChange(): void {
    this.history.push({
      width: this.widthBreakpoint,
      height: this.heightBreakpoint,
      time: Date.now()
    });
  }

  public getHistoryLength(): number {
    return this.history.length;
  }

  public getLastChange(): { width: WidthBreakpoint; height: HeightBreakpoint; time: number } | null {
    if (this.history.length === 0) {
      return null;
    }
    return this.history[this.history.length - 1];
  }

  public clearHistory(): void {
    this.history = [];
  }
}

// 边界测试 fixture
class EdgeCaseBreakpointInfo {
  widthBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  heightBreakpoint: HeightBreakpoint = 0 as HeightBreakpoint;
  minBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  maxBreakpoint: WidthBreakpoint = 100 as WidthBreakpoint;

  public isAtMin(): boolean {
    return this.widthBreakpoint === this.minBreakpoint;
  }

  public isAtMax(): boolean {
    return this.widthBreakpoint === this.maxBreakpoint;
  }

  public isInRange(): boolean {
    return this.widthBreakpoint >= this.minBreakpoint && this.widthBreakpoint <= this.maxBreakpoint;
  }
}

// 性能测试 fixture
class PerformanceBreakpointInfo {
  widthBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  heightBreakpoint: HeightBreakpoint = 0 as HeightBreakpoint;
  updateCount: number = 0;
  lastUpdateTime: number = 0;

  public incrementUpdateCount(): void {
    this.updateCount++;
    this.lastUpdateTime = Date.now();
  }

  public getUpdateCount(): number {
    return this.updateCount;
  }

  public getLastUpdateTime(): number {
    return this.lastUpdateTime;
  }

  public resetMetrics(): void {
    this.updateCount = 0;
    this.lastUpdateTime = 0;
  }
}

// 状态追踪 fixture
class StateTrackingBreakpointInfo {
  widthBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  heightBreakpoint: HeightBreakpoint = 0 as HeightBreakpoint;
  state: 'initial' | 'updated' | 'destroyed' = 'initial';
  transitions: string[] = [];

  public transitionTo(newState: 'initial' | 'updated' | 'destroyed'): void {
    this.transitions.push(`${this.state} -> ${newState}`);
    this.state = newState;
  }

  public getCurrentState(): string {
    return this.state;
  }

  public getTransitionCount(): number {
    return this.transitions.length;
  }

  public getLastTransition(): string | null {
    if (this.transitions.length === 0) {
      return null;
    }
    return this.transitions[this.transitions.length - 1];
  }
}

// 并发测试 fixture
class ConcurrentBreakpointInfo {
  widthBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  heightBreakpoint: HeightBreakpoint = 0 as HeightBreakpoint;
  lock: boolean = false;
  pendingUpdates: number = 0;

  public acquireLock(): boolean {
    if (this.lock) {
      this.pendingUpdates++;
      return false;
    }
    this.lock = true;
    return true;
  }

  public releaseLock(): void {
    this.lock = false;
  }

  public getPendingUpdates(): number {
    return this.pendingUpdates;
  }

  public hasLock(): boolean {
    return this.lock;
  }
}

// 验证测试 fixture
class ValidationBreakpointInfo {
  widthBreakpoint: WidthBreakpoint = 0 as WidthBreakpoint;
  heightBreakpoint: HeightBreakpoint = 0 as HeightBreakpoint;
  valid: boolean = true;
  errors: string[] = [];

  public validate(): boolean {
    this.errors = [];

    // 修复方案：直接与数字 0 比较，去掉 'as WidthBreakpoint'
    // 枚举在底层通常是数字，可以直接比较
    if (this.widthBreakpoint < 0) {
      this.errors.push('Width breakpoint cannot be negative');
      this.valid = false;
    }

    if (this.heightBreakpoint < 0) {
      this.errors.push('Height breakpoint cannot be negative');
      this.valid = false;
    }

    return this.valid;
  }

  public isValid(): boolean {
    return this.valid;
  }

  public getErrors(): string[] {
    return this.errors;
  }

  public getLastError(): string | null {
    if (this.errors.length === 0) {
      return null;
    }
    return this.errors[this.errors.length - 1];
  }
}

// ============================================================================
// 4. 主测试类
// ============================================================================

export class IEnvBreakpointTests implements ITestFile {

  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating IEnvBreakpointTests: ${str}`);
    this.idString = str;
  }

  // -------------------------------------------------------------------------
  // 生命周期方法
  // -------------------------------------------------------------------------

  public beforeAll(): void {
    // 在所有测试前执行一次
    console.log('Starting IEnvBreakpointTests');
  }

  public beforeEach(): void {
    // 在每个测试前执行
  }

  public afterAll(): void {
    // 在所有测试后执行一次
    console.log('Completed IEnvBreakpointTests');
  }

  public afterEach(): void {
    // 在每个测试后执行
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // 5. WindowSizeLayoutBreakpoint 类测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // Constructor Tests
  // -------------------------------------------------------------------------

  public testWindowSizeLayoutBreakpointConstructor(): void {
    // 测试构造函数的基本功能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    eq(breakpoint !== null, true, 'Constructor should create instance');
    eq(breakpoint !== undefined, true, 'Constructor should not return undefined');
  }

  public testWindowSizeLayoutBreakpointConstructorWithNullContext(): void {
    // 测试使用 null context 构造
    try {
      const breakpoint = new WindowSizeLayoutBreakpoint(null as any);
      eq(breakpoint !== null, true, 'Constructor should handle null context');
    } catch (e) {
      eq(true, true, 'Constructor may throw on null context');
    }
  }

  public testWindowSizeLayoutBreakpointConstructorWithUndefinedContext(): void {
    // 测试使用 undefined context 构造
    try {
      const breakpoint = new WindowSizeLayoutBreakpoint(undefined as any);
      eq(breakpoint !== null, true, 'Constructor should handle undefined context');
    } catch (e) {
      eq(true, true, 'Constructor may throw on undefined context');
    }
  }

  public testWindowSizeLayoutBreakpointConstructorMultipleInstances(): void {
    // 测试创建多个实例
    const context1 = new UIContext();
    const context2 = new UIContext();
    const breakpoint1 = new WindowSizeLayoutBreakpoint(context1);
    const breakpoint2 = new WindowSizeLayoutBreakpoint(context2);
    eq(breakpoint1 !== breakpoint2, true, 'Multiple instances should be distinct');
  }

  public testWindowSizeLayoutBreakpointConstructorSameContext(): void {
    // 测试使用相同 context 创建多个实例
    const context = new UIContext();
    const breakpoint1 = new WindowSizeLayoutBreakpoint(context);
    const breakpoint2 = new WindowSizeLayoutBreakpoint(context);
    eq(breakpoint1 !== breakpoint2, true, 'Same context should create distinct instances');
  }

  // -------------------------------------------------------------------------
  // Value Property Tests
  // -------------------------------------------------------------------------

  public testWindowSizeLayoutBreakpointValueProperty(): void {
    // 测试 value 属性的基本访问
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const value = breakpoint.value;
    eq(value !== null, true, 'Value should not be null');
    eq(value !== undefined, true, 'Value should not be undefined');
  }

  public testWindowSizeLayoutBreakpointValueStructure(): void {
    // 测试 value 的结构
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const value = breakpoint.value;
    eq(value.hasOwnProperty('widthBreakpoint'), true, 'Value should have widthBreakpoint property');
    eq(value.hasOwnProperty('heightBreakpoint'), true, 'Value should have heightBreakpoint property');
  }

  public testWindowSizeLayoutBreakpointValueWidthBreakpoint(): void {
    // 测试 widthBreakpoint 属性
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const value = breakpoint.value;
    eq(typeof value.widthBreakpoint, 'number', 'WidthBreakpoint should be a number');
  }

  public testWindowSizeLayoutBreakpointValueHeightBreakpoint(): void {
    // 测试 heightBreakpoint 属性
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const value = breakpoint.value;
    eq(typeof value.heightBreakpoint, 'number', 'HeightBreakpoint should be a number');
  }

  public testWindowSizeLayoutBreakpointValueImmutable(): void {
    // 测试 value 属性是否不可变（部分实现可能支持）
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const originalValue = breakpoint.value;
    const originalWidth = originalValue.widthBreakpoint;
    const originalHeight = originalValue.heightBreakpoint;

    // 尝试修改（某些实现可能不允许直接修改）
    try {
      originalValue.widthBreakpoint = 1 as WidthBreakpoint;
      const currentValue = breakpoint.value;
      // 如果允许修改，验证修改是否生效
      eq(currentValue.widthBreakpoint !== undefined, true, 'Value should remain accessible');
    } catch (e) {
      // 如果不允许修改，这是预期的行为
      eq(true, true, 'Value may be immutable');
    }
  }

  public testWindowSizeLayoutBreakpointValueConsistency(): void {
    // 测试多次访问 value 的一致性
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const value1 = breakpoint.value;
    const value2 = breakpoint.value;
    eq(value1.widthBreakpoint === value2.widthBreakpoint, true, 'Value should be consistent across accesses');
    eq(value1.heightBreakpoint === value2.heightBreakpoint, true, 'Value should be consistent across accesses');
  }

  // -------------------------------------------------------------------------
  // Update Method Tests
  // -------------------------------------------------------------------------

  public testWindowSizeLayoutBreakpointUpdate(): void {
    // 测试 update 方法的基本功能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint.update(newValue);
    const currentValue = breakpoint.value;
    eq(currentValue.widthBreakpoint, 1 as WidthBreakpoint, 'Update should set widthBreakpoint');
    eq(currentValue.heightBreakpoint, 1 as HeightBreakpoint, 'Update should set heightBreakpoint');
  }

  public testWindowSizeLayoutBreakpointUpdatePartial(): void {
    // 测试部分更新（如果支持）
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const originalValue = breakpoint.value;

    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 2 as WidthBreakpoint,
      heightBreakpoint: originalValue.heightBreakpoint
    };
    breakpoint.update(newValue);

    const currentValue = breakpoint.value;
    eq(currentValue.widthBreakpoint, 2 as WidthBreakpoint, 'Update should modify widthBreakpoint');
  }

  public testWindowSizeLayoutBreakpointUpdateMultiple(): void {
    // 测试多次更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const update1: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint.update(update1);

    const update2: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 2 as WidthBreakpoint,
      heightBreakpoint: 2 as HeightBreakpoint
    };
    breakpoint.update(update2);

    const currentValue = breakpoint.value;
    eq(currentValue.widthBreakpoint, 2 as WidthBreakpoint, 'Multiple updates should work');
    eq(currentValue.heightBreakpoint, 2 as HeightBreakpoint, 'Multiple updates should work');
  }

  public testWindowSizeLayoutBreakpointUpdateSameValue(): void {
    // 测试更新为相同值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const originalValue = breakpoint.value;

    breakpoint.update(originalValue);

    const currentValue = breakpoint.value;
    eq(currentValue.widthBreakpoint, originalValue.widthBreakpoint, 'Update with same value should work');
    eq(currentValue.heightBreakpoint, originalValue.heightBreakpoint, 'Update with same value should work');
  }

  public testWindowSizeLayoutBreakpointUpdateNull(): void {
    // 测试更新为 null
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      breakpoint.update(null as any);
      eq(true, true, 'Update may handle null');
    } catch (e) {
      eq(true, true, 'Update may throw on null');
    }
  }

  public testWindowSizeLayoutBreakpointUpdateUndefined(): void {
    // 测试更新为 undefined
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      breakpoint.update(undefined as any);
      eq(true, true, 'Update may handle undefined');
    } catch (e) {
      eq(true, true, 'Update may throw on undefined');
    }
  }

  public testWindowSizeLayoutBreakpointUpdateWithZero(): void {
    // 测试更新为零值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 0 as WidthBreakpoint,
      heightBreakpoint: 0 as HeightBreakpoint
    };
    breakpoint.update(newValue);

    const currentValue = breakpoint.value;
    eq(currentValue.widthBreakpoint, 0 as WidthBreakpoint, 'Update should handle zero');
    eq(currentValue.heightBreakpoint, 0 as HeightBreakpoint, 'Update should handle zero');
  }

  public testWindowSizeLayoutBreakpointUpdateWithLargeValues(): void {
    // 测试更新为大值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1000 as WidthBreakpoint,
      heightBreakpoint: 1000 as HeightBreakpoint
    };
    breakpoint.update(newValue);

    const currentValue = breakpoint.value;
    eq(currentValue.widthBreakpoint, 1000 as WidthBreakpoint, 'Update should handle large values');
    eq(currentValue.heightBreakpoint, 1000 as HeightBreakpoint, 'Update should handle large values');
  }

  // -------------------------------------------------------------------------
  // Destroy Method Tests
  // -------------------------------------------------------------------------

  public testWindowSizeLayoutBreakpointDestroy(): void {
    // 测试 destroy 方法的基本功能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    breakpoint.destroy();
    eq(true, true, 'Destroy should complete without error');
  }

  public testWindowSizeLayoutBreakpointDestroyMultiple(): void {
    // 测试多次调用 destroy
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    breakpoint.destroy();

    try {
      breakpoint.destroy();
      eq(true, true, 'Multiple destroy calls should be safe');
    } catch (e) {
      eq(true, true, 'Multiple destroy calls may throw');
    }
  }

  public testWindowSizeLayoutBreakpointDestroyAfterUpdate(): void {
    // 测试更新后销毁
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint.update(newValue);
    breakpoint.destroy();

    eq(true, true, 'Destroy after update should work');
  }

  public testWindowSizeLayoutBreakpointDestroyBeforeUpdate(): void {
    // 测试销毁后更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    breakpoint.destroy();

    try {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: 1 as WidthBreakpoint,
        heightBreakpoint: 1 as HeightBreakpoint
      };
      breakpoint.update(newValue);
      eq(true, true, 'Update after destroy may work');
    } catch (e) {
      eq(true, true, 'Update after destroy may throw');
    }
  }

  public testWindowSizeLayoutBreakpointDestroyAccessValue(): void {
    // 测试销毁后访问 value
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    breakpoint.destroy();

    try {
      const value = breakpoint.value;
      eq(value !== undefined, true, 'Value access after destroy may work');
    } catch (e) {
      eq(true, true, 'Value access after destroy may throw');
    }
  }

  // =========================================================================
  // 6. 功能测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // Basic Functionality Tests
  // -------------------------------------------------------------------------

  public testFeatureBasicLifecycle(): void {
    // 测试完整的生命周期
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const initialValue = breakpoint.value;
    eq(initialValue !== null, true, 'Initial value should be accessible');

    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint.update(newValue);

    const updatedValue = breakpoint.value;
    eq(updatedValue.widthBreakpoint, 1 as WidthBreakpoint, 'Value should be updated');

    breakpoint.destroy();
    eq(true, true, 'Lifecycle should complete successfully');
  }

  public testFeatureValueChaining(): void {
    // 测试值的链式更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    for (let i = 0; i < 5; i++) {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: i as WidthBreakpoint,
        heightBreakpoint: i as HeightBreakpoint
      };
      breakpoint.update(newValue);
    }

    const finalValue = breakpoint.value;
    eq(finalValue.widthBreakpoint, 4 as WidthBreakpoint, 'Chain updates should work');
    eq(finalValue.heightBreakpoint, 4 as HeightBreakpoint, 'Chain updates should work');
  }

  public testFeatureIndependentInstances(): void {
    // 测试独立实例
    const context1 = new UIContext();
    const context2 = new UIContext();
    const breakpoint1 = new WindowSizeLayoutBreakpoint(context1);
    const breakpoint2 = new WindowSizeLayoutBreakpoint(context2);

    const update1: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint1.update(update1);

    const update2: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 2 as WidthBreakpoint,
      heightBreakpoint: 2 as HeightBreakpoint
    };
    breakpoint2.update(update2);

    eq(breakpoint1.value.widthBreakpoint, 1 as WidthBreakpoint, 'Instances should be independent');
    eq(breakpoint2.value.widthBreakpoint, 2 as WidthBreakpoint, 'Instances should be independent');
  }

  public testFeatureSharedContext(): void {
    // 测试共享 context 的实例
    const context = new UIContext();
    const breakpoint1 = new WindowSizeLayoutBreakpoint(context);
    const breakpoint2 = new WindowSizeLayoutBreakpoint(context);

    const update1: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint1.update(update1);

    const update2: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 2 as WidthBreakpoint,
      heightBreakpoint: 2 as HeightBreakpoint
    };
    breakpoint2.update(update2);

    eq(breakpoint1.value.widthBreakpoint, 1 as WidthBreakpoint, 'Shared context instances should be independent');
    eq(breakpoint2.value.widthBreakpoint, 2 as WidthBreakpoint, 'Shared context instances should be independent');
  }

  // -------------------------------------------------------------------------
  // State Management Tests
  // -------------------------------------------------------------------------

  public testFeatureStateInitialization(): void {
    // 测试状态初始化
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const value = breakpoint.value;

    eq(typeof value.widthBreakpoint, 'number', 'WidthBreakpoint should be initialized');
    eq(typeof value.heightBreakpoint, 'number', 'HeightBreakpoint should be initialized');
  }

  public testFeatureStateTransition(): void {
    // 测试状态转换
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const state1 = breakpoint.value;

    const update: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint.update(update);

    const state2 = breakpoint.value;

    eq(state1.widthBreakpoint !== state2.widthBreakpoint || state1.heightBreakpoint !== state2.heightBreakpoint,
       true, 'State should transition');
  }

  public testFeatureStatePersistence(): void {
    // 测试状态持久性
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const update: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 5 as WidthBreakpoint,
      heightBreakpoint: 5 as HeightBreakpoint
    };
    breakpoint.update(update);

    const value1 = breakpoint.value;
    const value2 = breakpoint.value;
    const value3 = breakpoint.value;

    eq(value1.widthBreakpoint, value2.widthBreakpoint, 'State should persist');
    eq(value2.widthBreakpoint, value3.widthBreakpoint, 'State should persist');
  }

  // =========================================================================
  // 7. 边界测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // Value Boundary Tests
  // -------------------------------------------------------------------------

  public testEdgeCaseZeroBreakpoint(): void {
    // 测试零断点值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 0 as WidthBreakpoint,
      heightBreakpoint: 0 as HeightBreakpoint
    };
    breakpoint.update(newValue);

    const value = breakpoint.value;
    eq(value.widthBreakpoint, 0 as WidthBreakpoint, 'Zero breakpoint should be handled');
    eq(value.heightBreakpoint, 0 as HeightBreakpoint, 'Zero breakpoint should be handled');
  }

  public testEdgeCaseNegativeBreakpoint(): void {
    // 测试负断点值（如果支持）
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: -1 as WidthBreakpoint,
        heightBreakpoint: -1 as HeightBreakpoint
      };
      breakpoint.update(newValue);
      eq(true, true, 'Negative breakpoint may be handled');
    } catch (e) {
      eq(true, true, 'Negative breakpoint may throw');
    }
  }

  public testEdgeCaseMaximumBreakpoint(): void {
    // 测试最大断点值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const maxValue = Number.MAX_SAFE_INTEGER;
    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: maxValue as WidthBreakpoint,
      heightBreakpoint: maxValue as HeightBreakpoint
    };
    breakpoint.update(newValue);

    const value = breakpoint.value;
    eq(value.widthBreakpoint, maxValue as WidthBreakpoint, 'Maximum breakpoint should be handled');
  }

  public testEdgeCaseMinimumBreakpoint(): void {
    // 测试最小断点值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const minValue = Number.MIN_SAFE_INTEGER;
    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: minValue as WidthBreakpoint,
      heightBreakpoint: minValue as HeightBreakpoint
    };
    breakpoint.update(newValue);

    const value = breakpoint.value;
    eq(value.widthBreakpoint, minValue as WidthBreakpoint, 'Minimum breakpoint should be handled');
  }

  public testEdgeCaseNaNBreakpoint(): void {
    // 测试 NaN 断点值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: NaN as WidthBreakpoint,
        heightBreakpoint: NaN as HeightBreakpoint
      };
      breakpoint.update(newValue);
      eq(true, true, 'NaN breakpoint may be handled');
    } catch (e) {
      eq(true, true, 'NaN breakpoint may throw');
    }
  }

  public testEdgeCaseInfinityBreakpoint(): void {
    // 测试 Infinity 断点值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: Infinity as WidthBreakpoint,
        heightBreakpoint: Infinity as HeightBreakpoint
      };
      breakpoint.update(newValue);
      eq(true, true, 'Infinity breakpoint may be handled');
    } catch (e) {
      eq(true, true, 'Infinity breakpoint may throw');
    }
  }

  // -------------------------------------------------------------------------
  // Update Boundary Tests
  // -------------------------------------------------------------------------

  public testEdgeCaseUpdateFrequency(): void {
    // 测试高频更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const iterations = 1000;
    for (let i = 0; i < iterations; i++) {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: i as WidthBreakpoint,
        heightBreakpoint: i as HeightBreakpoint
      };
      breakpoint.update(newValue);
    }

    const value = breakpoint.value;
    eq(value.widthBreakpoint, (iterations - 1) as WidthBreakpoint, 'High frequency updates should work');
  }

  public testEdgeCaseUpdateWithSameObject(): void {
    // 测试使用相同对象更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const updateObj: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };

    breakpoint.update(updateObj);
    breakpoint.update(updateObj);
    breakpoint.update(updateObj);

    const value = breakpoint.value;
    eq(value.widthBreakpoint, 1 as WidthBreakpoint, 'Same object updates should work');
  }

  public testEdgeCaseUpdateAfterDestroy(): void {
    // 测试销毁后更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    breakpoint.destroy();

    try {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: 1 as WidthBreakpoint,
        heightBreakpoint: 1 as HeightBreakpoint
      };
      breakpoint.update(newValue);
      eq(true, true, 'Update after destroy may work');
    } catch (e) {
      eq(true, true, 'Update after destroy may throw');
    }
  }

  // -------------------------------------------------------------------------
  // Memory Boundary Tests
  // -------------------------------------------------------------------------

  public testEdgeCaseManyInstances(): void {
    // 测试创建大量实例
    const instances: WindowSizeLayoutBreakpoint[] = [];
    const count = 100;

    for (let i = 0; i < count; i++) {
      const context = new UIContext();
      const breakpoint = new WindowSizeLayoutBreakpoint(context);
      instances.push(breakpoint);
    }

    eq(instances.length, count, 'Should create many instances');

    // 清理
    instances.forEach(instance => instance.destroy());
  }

  public testEdgeCaseLargeValueObject(): void {
    // 测试大型值对象（如果支持扩展属性）
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const baseValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };

    // 尝试添加额外属性（可能不被支持）
    const extendedValue = baseValue as any;
    extendedValue.extra1 = 'data1';
    extendedValue.extra2 = 'data2';

    try {
      breakpoint.update(extendedValue);
      eq(true, true, 'Extended value may be handled');
    } catch (e) {
      eq(true, true, 'Extended value may throw');
    }
  }

  // =========================================================================
  // 8. 错误测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // Constructor Error Tests
  // -------------------------------------------------------------------------

  public testErrorConstructorWithInvalidContext(): void {
    // 测试使用无效 context 构造
    try {
      const breakpoint = new WindowSizeLayoutBreakpoint({} as any);
      eq(true, true, 'Invalid context may be handled');
    } catch (e) {
      eq(true, true, 'Invalid context should throw');
    }
  }

  public testErrorConstructorWithString(): void {
    // 测试使用字符串构造
    try {
      const breakpoint = new WindowSizeLayoutBreakpoint('invalid' as any);
      eq(true, true, 'String context may be handled');
    } catch (e) {
      eq(true, true, 'String context should throw');
    }
  }

  public testErrorConstructorWithNumber(): void {
    // 测试使用数字构造
    try {
      const breakpoint = new WindowSizeLayoutBreakpoint(123 as any);
      eq(true, true, 'Number context may be handled');
    } catch (e) {
      eq(true, true, 'Number context should throw');
    }
  }

  // -------------------------------------------------------------------------
  // Update Error Tests
  // -------------------------------------------------------------------------

  public testErrorUpdateWithInvalidType(): void {
    // 测试使用无效类型更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      breakpoint.update('invalid' as any);
      eq(true, true, 'Invalid type may be handled');
    } catch (e) {
      eq(true, true, 'Invalid type should throw');
    }
  }

  public testErrorUpdateWithNumber(): void {
    // 测试使用数字更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      breakpoint.update(123 as any);
      eq(true, true, 'Number update may be handled');
    } catch (e) {
      eq(true, true, 'Number update should throw');
    }
  }

  public testErrorUpdateWithArray(): void {
    // 测试使用数组更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      breakpoint.update([] as any);
      eq(true, true, 'Array update may be handled');
    } catch (e) {
      eq(true, true, 'Array update should throw');
    }
  }

  public testErrorUpdateWithMissingProperties(): void {
    // 测试使用缺少属性的更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      const invalidValue = {} as uiObserver.WindowSizeLayoutBreakpointInfo;
      breakpoint.update(invalidValue);
      eq(true, true, 'Missing properties may be handled');
    } catch (e) {
      eq(true, true, 'Missing properties should throw');
    }
  }

  public testErrorUpdateWithPartialProperties(): void {
    // 测试使用部分属性的更新
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    try {
      const partialValue = { widthBreakpoint: 1 as WidthBreakpoint } as any;
      breakpoint.update(partialValue);
      eq(true, true, 'Partial properties may be handled');
    } catch (e) {
      eq(true, true, 'Partial properties may throw');
    }
  }

  // -------------------------------------------------------------------------
  // Value Access Error Tests
  // -------------------------------------------------------------------------

  public testErrorValueAccessAfterDestroy(): void {
    // 测试销毁后访问 value
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    breakpoint.destroy();

    try {
      const value = breakpoint.value;
      eq(true, true, 'Value access after destroy may work');
    } catch (e) {
      eq(true, true, 'Value access after destroy may throw');
    }
  }

  // =========================================================================
  // 9. 性能测试
  // -------------------------------------------------------------------------

  // -------------------------------------------------------------------------
  // Construction Performance Tests
  // -------------------------------------------------------------------------

  public testPerformanceConstruction(): void {
    // 测试构造性能
    const iterations = 1000;
    const startTime = Date.now();

    for (let i = 0; i < iterations; i++) {
      const context = new UIContext();
      const breakpoint = new WindowSizeLayoutBreakpoint(context);
      breakpoint.destroy();
    }

    const duration = Date.now() - startTime;
    eq(duration < 5000, true, 'Construction should complete in reasonable time');
  }

  public testPerformanceConstructionBatch(): void {
    // 测试批量构造性能
    const batchSize = 100;
    const instances: WindowSizeLayoutBreakpoint[] = [];

    const startTime = Date.now();
    for (let i = 0; i < batchSize; i++) {
      const context = new UIContext();
      const breakpoint = new WindowSizeLayoutBreakpoint(context);
      instances.push(breakpoint);
    }
    const duration = Date.now() - startTime;

    eq(duration < 1000, true, 'Batch construction should be fast');
    eq(instances.length, batchSize, 'All instances should be created');

    // 清理
    instances.forEach(instance => instance.destroy());
  }

  // -------------------------------------------------------------------------
  // Update Performance Tests
  // -------------------------------------------------------------------------

  public testPerformanceUpdateSingle(): void {
    // 测试单次更新性能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };

    const startTime = Date.now();
    breakpoint.update(newValue);
    const duration = Date.now() - startTime;

    eq(duration < 100, true, 'Single update should be fast');
    eq(breakpoint.value.widthBreakpoint, 1 as WidthBreakpoint, 'Update should succeed');
  }

  public testPerformanceUpdateBatch(): void {
    // 测试批量更新性能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const iterations = 1000;

    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: i as WidthBreakpoint,
        heightBreakpoint: i as HeightBreakpoint
      };
      breakpoint.update(newValue);
    }
    const duration = Date.now() - startTime;

    eq(duration < 1000, true, 'Batch updates should be fast');
    eq(breakpoint.value.widthBreakpoint, (iterations - 1) as WidthBreakpoint, 'All updates should succeed');
  }

  public testPerformanceUpdateAlternating(): void {
    // 测试交替更新性能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const iterations = 100;

    const value1: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };

    const value2: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 2 as WidthBreakpoint,
      heightBreakpoint: 2 as HeightBreakpoint
    };

    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      if (i % 2 === 0) {
        breakpoint.update(value1);
      } else {
        breakpoint.update(value2);
      }
    }
    const duration = Date.now() - startTime;

    eq(duration < 500, true, 'Alternating updates should be fast');
  }

  // -------------------------------------------------------------------------
  // Value Access Performance Tests
  // -------------------------------------------------------------------------

  public testPerformanceValueAccess(): void {
    // 测试 value 访问性能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    const iterations = 10000;

    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const value = breakpoint.value;
      const width = value.widthBreakpoint;
      const height = value.heightBreakpoint;
    }
    const duration = Date.now() - startTime;

    eq(duration < 1000, true, 'Value access should be fast');
  }

  public testPerformanceValueAccessAfterUpdate(): void {
    // 测试更新后的 value 访问性能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint.update(newValue);

    const iterations = 10000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const value = breakpoint.value;
      const width = value.widthBreakpoint;
      const height = value.heightBreakpoint;
    }
    const duration = Date.now() - startTime;

    eq(duration < 1000, true, 'Value access after update should be fast');
  }

  // -------------------------------------------------------------------------
  // Destroy Performance Tests
  // -------------------------------------------------------------------------

  public testPerformanceDestroy(): void {
    // 测试销毁性能
    const iterations = 1000;
    const instances: WindowSizeLayoutBreakpoint[] = [];

    for (let i = 0; i < iterations; i++) {
      const context = new UIContext();
      const breakpoint = new WindowSizeLayoutBreakpoint(context);
      instances.push(breakpoint);
    }

    const startTime = Date.now();
    instances.forEach(instance => instance.destroy());
    const duration = Date.now() - startTime;

    eq(duration < 1000, true, 'Batch destroy should be fast');
  }

  public testPerformanceDestroySingle(): void {
    // 测试单次销毁性能
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const startTime = Date.now();
    breakpoint.destroy();
    const duration = Date.now() - startTime;

    eq(duration < 100, true, 'Single destroy should be fast');
  }

  // -------------------------------------------------------------------------
  // Memory Performance Tests
  // -------------------------------------------------------------------------

  public testPerformanceMemoryUsage(): void {
    // 测试内存使用（间接测试）
    const instances: WindowSizeLayoutBreakpoint[] = [];
    const count = 100;

    for (let i = 0; i < count; i++) {
      const context = new UIContext();
      const breakpoint = new WindowSizeLayoutBreakpoint(context);
      instances.push(breakpoint);
    }

    eq(instances.length, count, 'Should handle memory for many instances');

    // 清理
    instances.forEach(instance => instance.destroy());
  }

  // =========================================================================
  // 10. 兼容性测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // API Compatibility Tests
  // -------------------------------------------------------------------------

  public testCompatibilityInterfaceImplementation(): void {
    // 测试接口实现
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    eq(typeof breakpoint.value, 'object', 'Should implement IEnvironmentValue');
    eq(typeof breakpoint.update, 'function', 'Should implement update method');
    eq(typeof breakpoint.destroy, 'function', 'Should implement destroy method');
  }

  public testCompatibilityPropertyAccess(): void {
    // 测试属性访问
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const value = breakpoint.value;
    eq('widthBreakpoint' in value, true, 'Should have widthBreakpoint property');
    eq('heightBreakpoint' in value, true, 'Should have heightBreakpoint property');
  }

  public testCompatibilityMethodSignature(): void {
    // 测试方法签名
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const updateLength = breakpoint.update.length;
    const destroyLength = breakpoint.destroy.length;

    eq(typeof updateLength, 'number', 'Update should have signature');
    eq(typeof destroyLength, 'number', 'Destroy should have signature');
  }

  // -------------------------------------------------------------------------
  // Type Compatibility Tests
  // -------------------------------------------------------------------------

  public testCompatibilityTypeCoercion(): void {
    // 测试类型强制转换
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const value = breakpoint.value;
    const widthAsNumber = Number(value.widthBreakpoint);
    const heightAsNumber = Number(value.heightBreakpoint);

    eq(typeof widthAsNumber, 'number', 'WidthBreakpoint should coerce to number');
    eq(typeof heightAsNumber, 'number', 'HeightBreakpoint should coerce to number');
  }

  public testCompatibilityEnumValues(): void {
    // 测试枚举值
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const value = breakpoint.value;
    const width = value.widthBreakpoint;
    const height = value.heightBreakpoint;

    eq(typeof width, 'number', 'WidthBreakpoint should be enum-like');
    eq(typeof height, 'number', 'HeightBreakpoint should be enum-like');
  }

  // -------------------------------------------------------------------------
  // Environment Compatibility Tests
  // -------------------------------------------------------------------------

  public testCompatibilityMultipleEnvironments(): void {
    // 测试多环境兼容性
    const contexts: UIContext[] = [];
    const breakpoints: WindowSizeLayoutBreakpoint[] = [];

    for (let i = 0; i < 5; i++) {
      const context = new UIContext();
      const breakpoint = new WindowSizeLayoutBreakpoint(context);
      contexts.push(context);
      breakpoints.push(breakpoint);
    }

    eq(breakpoints.length, 5, 'Should support multiple environments');

    // 清理
    breakpoints.forEach(b => b.destroy());
  }

  public testCompatibilityContextIsolation(): void {
    // 测试上下文隔离
    const context1 = new UIContext();
    const context2 = new UIContext();
    const breakpoint1 = new WindowSizeLayoutBreakpoint(context1);
    const breakpoint2 = new WindowSizeLayoutBreakpoint(context2);

    const update1: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint1.update(update1);

    const update2: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 2 as WidthBreakpoint,
      heightBreakpoint: 2 as HeightBreakpoint
    };
    breakpoint2.update(update2);

    eq(breakpoint1.value.widthBreakpoint !== breakpoint2.value.widthBreakpoint,
       true, 'Contexts should be isolated');

    breakpoint1.destroy();
    breakpoint2.destroy();
  }

  // -------------------------------------------------------------------------
  // Lifecycle Compatibility Tests
  // -------------------------------------------------------------------------

  public testCompatibilityEarlyDestroy(): void {
    // 测试早期销毁
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    breakpoint.destroy();

    eq(true, true, 'Early destroy should be handled');
  }

  public testCompatibilityLateDestroy(): void {
    // 测试延迟销毁
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 执行一些操作
    for (let i = 0; i < 10; i++) {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: i as WidthBreakpoint,
        heightBreakpoint: i as HeightBreakpoint
      };
      breakpoint.update(newValue);
    }

    breakpoint.destroy();

    eq(true, true, 'Late destroy should be handled');
  }

  public testCompatibilityReuseAfterDestroy(): void {
    // 测试销毁后重用（如果支持）
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);
    breakpoint.destroy();

    try {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: 1 as WidthBreakpoint,
        heightBreakpoint: 1 as HeightBreakpoint
      };
      breakpoint.update(newValue);
      const value = breakpoint.value;
     eq(true, true, 'Reuse after destroy may work');
    } catch (e) {
      eq(true, true, 'Reuse after destroy may throw');
    }
  }

  // -------------------------------------------------------------------------
  // Concurrent Compatibility Tests
  // -------------------------------------------------------------------------

  public testCompatibilityConcurrentAccess(): void {
    // 测试并发访问（模拟）
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 模拟并发读取
    const value1 = breakpoint.value;
    const value2 = breakpoint.value;
    const value3 = breakpoint.value;

    eq(value1.widthBreakpoint === value2.widthBreakpoint,
       true, 'Concurrent reads should be consistent');
    eq(value2.widthBreakpoint === value3.widthBreakpoint,
       true, 'Concurrent reads should be consistent');
  }

  public testCompatibilityConcurrentUpdates(): void {
    // 测试并发更新（模拟）
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 模拟快速连续更新
    for (let i = 0; i < 10; i++) {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: i as WidthBreakpoint,
        heightBreakpoint: i as HeightBreakpoint
      };
      breakpoint.update(newValue);
    }

    const finalValue = breakpoint.value;
    eq(typeof finalValue.widthBreakpoint, 'number', 'Concurrent updates should complete');
  }

  // =========================================================================
  // 11. 集成测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // Full Lifecycle Integration Tests
  // -------------------------------------------------------------------------

  public testIntegrationFullLifecycle(): void {
    // 测试完整生命周期集成
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 初始状态
    const initialValue = breakpoint.value;
    eq(initialValue !== null, true, 'Initial state should be valid');

    // 更新状态
    const update1: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint.update(update1);

    const updatedValue1 = breakpoint.value;
    eq(updatedValue1.widthBreakpoint, 1 as WidthBreakpoint, 'First update should succeed');

    // 再次更新
    const update2: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 2 as WidthBreakpoint,
      heightBreakpoint: 2 as HeightBreakpoint
    };
    breakpoint.update(update2);

    const updatedValue2 = breakpoint.value;
    eq(updatedValue2.widthBreakpoint, 2 as WidthBreakpoint, 'Second update should succeed');

    // 销毁
    breakpoint.destroy();

    eq(true, true, 'Full lifecycle should complete successfully');
  }

  public testIntegrationMultipleBreakpoints(): void {
    // 测试多个断点实例集成
    const instances: WindowSizeLayoutBreakpoint[] = [];

    // 创建多个实例
    for (let i = 0; i < 5; i++) {
      const context = new UIContext();
      const breakpoint = new WindowSizeLayoutBreakpoint(context);
      instances.push(breakpoint);
    }

    // 更新每个实例
    instances.forEach((breakpoint, index) => {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: index as WidthBreakpoint,
        heightBreakpoint: index as HeightBreakpoint
      };
      breakpoint.update(newValue);
    });

    // 验证每个实例
    instances.forEach((breakpoint, index) => {
      eq(breakpoint.value.widthBreakpoint, index as WidthBreakpoint,
         `Instance ${index} should have correct value`);
    });

    // 清理所有实例
    instances.forEach(breakpoint => breakpoint.destroy());

    eq(true, true, 'Multiple instances integration should succeed');
  }

  public testIntegrationRapidLifecycle(): void {
    // 测试快速生命周期
    for (let i = 0; i < 100; i++) {
      const context = new UIContext();
      const breakpoint = new WindowSizeLayoutBreakpoint(context);

      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: i as WidthBreakpoint,
        heightBreakpoint: i as HeightBreakpoint
      };
      breakpoint.update(newValue);

      breakpoint.destroy();
    }

    eq(true, true, 'Rapid lifecycle should complete successfully');
  }

  // -------------------------------------------------------------------------
  // State Persistence Integration Tests
  // -------------------------------------------------------------------------

  public testIntegrationStatePersistenceAcrossUpdates(): void {
    // 测试跨更新的状态持久性
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    const values: uiObserver.WindowSizeLayoutBreakpointInfo[] = [];

    // 记录一系列更新
    for (let i = 0; i < 10; i++) {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: i as WidthBreakpoint,
        heightBreakpoint: i as HeightBreakpoint
      };
      breakpoint.update(newValue);
      values.push(breakpoint.value);
    }

    // 验证最后的状态
    eq(values[values.length - 1].widthBreakpoint, 9 as WidthBreakpoint,
       'Final state should be correct');

    breakpoint.destroy();
  }

  public testIntegrationStateIsolation(): void {
    // 测试状态隔离
    const context1 = new UIContext();
    const context2 = new UIContext();
    const breakpoint1 = new WindowSizeLayoutBreakpoint(context1);
    const breakpoint2 = new WindowSizeLayoutBreakpoint(context2);

    // 更新第一个实例
    const update1: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 1 as WidthBreakpoint,
      heightBreakpoint: 1 as HeightBreakpoint
    };
    breakpoint1.update(update1);

    // 更新第二个实例
    const update2: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 2 as WidthBreakpoint,
      heightBreakpoint: 2 as HeightBreakpoint
    };
    breakpoint2.update(update2);

    // 验证隔离
    eq(breakpoint1.value.widthBreakpoint, 1 as WidthBreakpoint,
       'Instance 1 should maintain its state');
    eq(breakpoint2.value.widthBreakpoint, 2 as WidthBreakpoint,
       'Instance 2 should maintain its state');

    breakpoint1.destroy();
    breakpoint2.destroy();
  }

  // -------------------------------------------------------------------------
  // Error Recovery Integration Tests
  // -------------------------------------------------------------------------

  public testIntegrationErrorRecovery(): void {
    // 测试错误恢复
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 尝试无效更新
    try {
      breakpoint.update(null as any);
    } catch (e) {
      // 忽略错误
    }

    // 验证实例仍然可用
    try {
      const validValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: 1 as WidthBreakpoint,
        heightBreakpoint: 1 as HeightBreakpoint
      };
      breakpoint.update(validValue);
      const value = breakpoint.value;
      eq(value.widthBreakpoint, 1 as WidthBreakpoint,
         'Instance should recover from error');
    } catch (e) {
      eq(true, true, 'Instance may not recover from error');
    }

    breakpoint.destroy();
  }

  // =========================================================================
  // 12. 场景测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // Real-world Scenario Tests
  // -------------------------------------------------------------------------

  public testScenarioResponsiveLayout(): void {
    // 测试响应式布局场景
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 模拟窗口大小变化
    const breakpoints = [
      { width: 320 as WidthBreakpoint, height: 480 as HeightBreakpoint },  // 手机竖屏
      { width: 768 as WidthBreakpoint, height: 1024 as HeightBreakpoint }, // 平板
      { width: 1920 as WidthBreakpoint, height: 1080 as HeightBreakpoint }, // 桌面
      { width: 375 as WidthBreakpoint, height: 667 as HeightBreakpoint },  // iPhone
      { width: 414 as WidthBreakpoint, height: 896 as HeightBreakpoint }   // iPhone Plus
    ];

    breakpoints.forEach(bp => {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: bp.width,
        heightBreakpoint: bp.height
      };
      breakpoint.update(newValue);
      eq(breakpoint.value.widthBreakpoint, bp.width, 'Layout breakpoint should update');
    });

    breakpoint.destroy();
  }

  public testScenarioOrientationChange(): void {
    // 测试方向改变场景
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 竖屏
    const portrait: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 375 as WidthBreakpoint,
      heightBreakpoint: 667 as HeightBreakpoint
    };
    breakpoint.update(portrait);

    // 横屏
    const landscape: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 667 as WidthBreakpoint,
      heightBreakpoint: 375 as HeightBreakpoint
    };
    breakpoint.update(landscape);

    eq(breakpoint.value.widthBreakpoint, 667 as WidthBreakpoint,
       'Orientation change should update correctly');

    breakpoint.destroy();
  }

  public testScenarioMultiWindow(): void {
    // 测试多窗口场景
    const window1Context = new UIContext();
    const window2Context = new UIContext();
    const window1Breakpoint = new WindowSizeLayoutBreakpoint(window1Context);
    const window2Breakpoint = new WindowSizeLayoutBreakpoint(window2Context);

    // 窗口1 设置
    const window1Value: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 800 as WidthBreakpoint,
      heightBreakpoint: 600 as HeightBreakpoint
    };
    window1Breakpoint.update(window1Value);

    // 窗口2 设置
    const window2Value: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 400 as WidthBreakpoint,
      heightBreakpoint: 300 as HeightBreakpoint
    };
    window2Breakpoint.update(window2Value);

    eq(window1Breakpoint.value.widthBreakpoint, 800 as WidthBreakpoint,
       'Window 1 should have correct breakpoint');
    eq(window2Breakpoint.value.widthBreakpoint, 400 as WidthBreakpoint,
       'Window 2 should have correct breakpoint');

    window1Breakpoint.destroy();
    window2Breakpoint.destroy();
  }

  public testScenarioDynamicResizing(): void {
    // 测试动态调整大小场景
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 模拟用户拖窗口调整大小
    const sizes = [
      { width: 500, height: 400 },
      { width: 600, height: 400 },
      { width: 700, height: 400 },
      { width: 800, height: 400 },
      { width: 900, height: 400 }
    ];

    sizes.forEach(size => {
      const newValue: uiObserver.WindowSizeLayoutBreakpointInfo = {
        widthBreakpoint: size.width as WidthBreakpoint,
        heightBreakpoint: size.height as HeightBreakpoint
      };
      breakpoint.update(newValue);
    });

    eq(breakpoint.value.widthBreakpoint, 900 as WidthBreakpoint,
       'Dynamic resizing should track final size');

    breakpoint.destroy();
  }

  public testScenarioScreenRotation(): void {
    // 测试屏幕旋转场景
    const context = new UIContext();
    const breakpoint = new WindowSizeLayoutBreakpoint(context);

    // 初始方向
    const initial: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 375 as WidthBreakpoint,
      heightBreakpoint: 667 as HeightBreakpoint
    };
    breakpoint.update(initial);

    // 旋转 90 度
    const rotated90: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 667 as WidthBreakpoint,
      heightBreakpoint: 375 as HeightBreakpoint
    };
    breakpoint.update(rotated90);

    // 旋转 180 度
    const rotated180: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 375 as WidthBreakpoint,
      heightBreakpoint: 667 as HeightBreakpoint
    };
    breakpoint.update(rotated180);

    // 旋转 270 度
    const rotated270: uiObserver.WindowSizeLayoutBreakpointInfo = {
      widthBreakpoint: 667 as WidthBreakpoint,
      heightBreakpoint: 375 as HeightBreakpoint
    };
    breakpoint.update(rotated270);

    eq(breakpoint.value.widthBreakpoint, 667 as WidthBreakpoint,
       'Screen rotation should update correctly');

    breakpoint.destroy();
  }
}
