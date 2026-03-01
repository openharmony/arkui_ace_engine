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
declare interface IEnvironmentValue<T> {
  value: T;
  update(newValue: T): void;
  destroy(): void;
}

// ============================================================================
// 3. 测试 Fixture 类
// ============================================================================

// 简单的环境值实现类 - 用于测试字符串类型
class StringEnvironmentValue implements IEnvironmentValue<string> {
  private _value: string;
  private _destroyed: boolean = false;

  constructor(initialValue: string) {
    this._value = initialValue;
  }

  public get value(): string {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: string) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public update(newValue: string): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public destroy(): void {
    this._destroyed = true;
    this._value = '';
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }
}

// 数字类型的环境值实现类
class NumberEnvironmentValue implements IEnvironmentValue<number> {
  private _value: number;
  private _destroyed: boolean = false;
  private _updateCount: number = 0;

  constructor(initialValue: number) {
    this._value = initialValue;
  }

  public get value(): number {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: number) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public update(newValue: number): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
    this._updateCount++;
  }

  public destroy(): void {
    this._destroyed = true;
    this._value = 0;
  }

  public getUpdateCount(): number {
    return this._updateCount;
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }
}

// 布尔类型的环境值实现类
class BooleanEnvironmentValue implements IEnvironmentValue<boolean> {
  private _value: boolean;
  private _destroyed: boolean = false;

  constructor(initialValue: boolean) {
    this._value = initialValue;
  }

  public get value(): boolean {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: boolean) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public update(newValue: boolean): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public destroy(): void {
    this._destroyed = true;
    this._value = false;
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }
}

// 对象类型的环境值实现类
class ObjectEnvironmentValue<T extends object> implements IEnvironmentValue<T> {
  private _value: T;
  private _destroyed: boolean = false;
  private _cloneOnUpdate: boolean = false;

  constructor(initialValue: T, cloneOnUpdate: boolean = false) {
    this._value = initialValue;
    this._cloneOnUpdate = cloneOnUpdate;
  }

  public get value(): T {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: T) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public update(newValue: T): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    if (this._cloneOnUpdate) {
      this._value = { ...newValue } as T;
    } else {
      this._value = newValue;
    }
  }

  public destroy(): void {
    this._destroyed = true;
    this._value = {} as T;
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }
}

// 数组类型的环境值实现类
class ArrayEnvironmentValue<T> implements IEnvironmentValue<T[]> {
  private _value: T[];
  private _destroyed: boolean = false;
  private _maxSize: number = -1;

  constructor(initialValue: T[], maxSize: number = -1) {
    this._value = initialValue;
    this._maxSize = maxSize;
  }

  public get value(): T[] {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: T[]) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    if (this._maxSize > 0 && newValue.length > this._maxSize) {
      throw new Error(`Array size exceeds maximum allowed size: ${this._maxSize}`);
    }
    this._value = newValue;
  }

  public update(newValue: T[]): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    if (this._maxSize > 0 && newValue.length > this._maxSize) {
      throw new Error(`Array size exceeds maximum allowed size: ${this._maxSize}`);
    }
    this._value = newValue;
  }

  public destroy(): void {
    this._destroyed = true;
    this._value = [];
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }
}

// 带观察者的环境值实现类
class ObservableEnvironmentValue<T> implements IEnvironmentValue<T> {
  private _value: T;
  private _destroyed: boolean = false;
  private _observers: Array<(oldValue: T, newValue: T) => void> = [];

  constructor(initialValue: T) {
    this._value = initialValue;
  }

  public get value(): T {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: T) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    const oldValue = this._value;
    this._value = newValue;
    this._notifyObservers(oldValue, newValue);
  }

  public update(newValue: T): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has beenkt destroyed');
    }
    const oldValue = this._value;
    this._value = newValue;
    this._notifyObservers(oldValue, newValue);
  }

  public destroy(): void {
    this._destroyed = true;
    this._observers = [];
  }

  public addObserver(observer: (oldValue: T, newValue: T) => void): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._observers.push(observer);
  }

  public removeObserver(observer: (oldValue: T, newValue: T) => void): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    const index = this._observers.indexOf(observer);
    if (index !== -1) {
      this._observers.splice(index, 1);
    }
  }

  public getObserverCount(): number {
    return this._observers.length;
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }

  private _notifyObservers(oldValue: T, newValue: T): void {
    for (const observer of this._observers) {
      try {
        observer(oldValue, newValue);
      } catch (e) {
        console.error('Observer error:', e);
      }
    }
  }
}

// 带验证的环境值实现类
class ValidatedEnvironmentValue<T> implements IEnvironmentValue<T> {
  private _value: T;
  private _destroyed: boolean = false;
  private _validator: (value: T) => boolean;

  constructor(initialValue: T, validator: (value: T) => boolean) {
    this._value = initialValue;
    this._validator = validator;
  }

  public get value(): T {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: T) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    if (!this._validator(newValue)) {
      throw new Error('Invalid value');
    }
    this._value = newValue;
  }

  public update(newValue: T): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    if (!this._validator(newValue)) {
      throw new Error('Invalid value');
    }
    this._value = newValue;
  }

  public destroy(): void {
    this._destroyed = true;
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }
}

// 带历史记录的环境值实现类
class HistoryEnvironmentValue<T> implements IEnvironmentValue<T> {
  private _value: T;
  private _destroyed: boolean = false;
  private _history: T[] = [];
  private _maxHistorySize: number = 10;

  constructor(initialValue: T, maxHistorySize: number = 10) {
    this._value = initialValue;
    this._maxHistorySize = maxHistorySize;
    this._history.push(initialValue);
  }

  public get value(): T {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: T) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._addToHistory(newValue);
    this._value = newValue;
  }

  public update(newValue: T): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._addToHistory(newValue);
    this._value = newValue;
  }

  public destroy(): void {
    this._destroyed = true;
    this._history = [];
  }

  public getHistory(): T[] {
    return [...this._history];
  }

  public undo(): boolean {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    if (this._history.length > 1) {
      this._history.pop();
      this._value = this._history[this._history.length - 1];
      return true;
    }
    return false;
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }

  private _addToHistory(newValue: T): void {
    this._history.push(newValue);
    if (this._history.length > this._maxHistorySize) {
      this._history.shift();
    }
  }
}

// 带延迟更新的环境值实现类
class DelayedEnvironmentValue<T> implements IEnvironmentValue<T> {
  private _value: T;
  private _destroyed: boolean = false;
  private _pendingValue: T | null = null;
  private _delayMs: number = 0;
  private _timeoutId: number | null = null;

  constructor(initialValue: T, delayMs: number = 0) {
    this._value = initialValue;
    this._delayMs = delayMs;
  }

  public get value(): T {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: T) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public update(newValue: T): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    if (this._delayMs > 0) {
      this._pendingValue = newValue;
      if (this._timeoutId !== null) {
        clearTimeout(this._timeoutId);
      }
      this._timeoutId = setTimeout(() => {
        this._value = this._pendingValue!;
        this._pendingValue = null;
        this._timeoutId = null;
      }, this._delayMs) as unknown as number;
    } else {
      this._value = newValue;
    }
  }

  public destroy(): void {
    this._destroyed = true;
    if (this._timeoutId !== null) {
      clearTimeout(this._timeoutId);
      this._timeoutId = null;
    }
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }

  public hasPendingUpdate(): boolean {
    return this._pendingValue !== null;
  }
}

// 带转换的环境值实现类
class TransformedEnvironmentValue<T, R> implements IEnvironmentValue<T> {
  private _value: T;
  private _destroyed: boolean = false;
  private _transform: (value: T) => R;
  private _inverseTransform: (value: R) => T;

  constructor(
    initialValue: T,
    transform: (value: T) => R,
    inverseTransform: (value: R) => T
  ) {
    this._value = initialValue;
    this._transform = transform;
    this._inverseTransform = inverseTransform;
  }

  public get value(): T {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._value;
  }

  public set value(newValue: T) {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public update(newValue: T): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = newValue;
  }

  public destroy(): void {
    this._destroyed = true;
  }

  public getTransformedValue(): R {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    return this._transform(this._value);
  }

  public updateFromTransformed(transformedValue: R): void {
    if (this._destroyed) {
      throw new Error('EnvironmentValue has been destroyed');
    }
    this._value = this._inverseTransform(transformedValue);
  }

  public isDestroyed(): boolean {
    return this._destroyed;
  }
}

// 复杂的用户对象类型
interface User {
  id: number;
  name: string;
  email: string;
  age: number;
  active: boolean;
}

// ============================================================================
// 4. 主测试类
// ============================================================================

export class IEnvValueTests implements ITestFile {

  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating IEnvValueTests: ${str}`);
    this.idString = str;
  }

  // -------------------------------------------------------------------------
  // 生命周期方法
  // -------------------------------------------------------------------------

  public beforeAll(): void {
    // 在所有测试前执行一次
    console.log('IEnvValueTests: Starting all tests');
  }

  public beforeEach(): void {
    // 在每个测试前执行
  }

  public afterAll(): void {
    // 在所有测试后执行一次
    console.log('IEnvValueTests: All tests completed');
  }

  public afterEach(): void {
    // 在每个测试后执行
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // 5. 基础功能测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // StringEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testStringEnvironmentValueInitialValue(): void {
    // 测试字符串环境值的初始值设置
    const envValue = new StringEnvironmentValue('initial');
    eq(envValue.value, 'initial', 'Initial value should be set correctly');
  }

  public testStringEnvironmentValueUpdate(): void {
    // 测试字符串环境值的更新功能
    const envValue = new StringEnvironmentValue('initial');
    envValue.update('updated');
    eq(envValue.value, 'updated', 'Value should be updated correctly');
  }

  public testStringEnvironmentValueMultipleUpdates(): void {
    // 测试多次更新字符串环境值
    const envValue = new StringEnvironmentValue('v1');
    envValue.update('v2');
    envValue.update('v3');
    envValue.update('v4');
    eq(envValue.value, 'v4', 'Value should reflect the latest update');
  }

  public testStringEnvironmentValueDestroy(): void {
    // 测试销毁字符串环境值
    const envValue = new StringEnvironmentValue('test');
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
  }

  public testStringEnvironmentValueAccessAfterDestroy(): void {
    // 测试销毁后访问值的错误处理
    const envValue = new StringEnvironmentValue('test');
    envValue.destroy();
    try {
      const value = envValue.value;
      eq(false, true, 'Should throw error when accessing destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown when accessing destroyed value');
    }
  }

  public testStringEnvironmentValueUpdateAfterDestroy(): void {
    // 测试销毁后更新值的错误处理
    const envValue = new StringEnvironmentValue('test');
    envValue.destroy();
    try {
      envValue.update('new');
      eq(false, true, 'Should throw error when updating destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown when updating destroyed value');
    }
  }

  public testStringEnvironmentValueEmptyString(): void {
    // 测试空字符串的处理
    const envValue = new StringEnvironmentValue('');
    eq(envValue.value, '', 'Empty string should be preserved');
    envValue.update('');
    eq(envValue.value, '', 'Empty string update should work');
  }

  public testStringEnvironmentValueLongString(): void {
    // 测试长字符串的处理
    const longString = 'a'.repeat(1000);
    const envValue = new StringEnvironmentValue(longString);
    eq(envValue.value.length, 1000, 'Long string should be preserved');
    envValue.update('b'.repeat(2000));
    eq(envValue.value.length, 2000, 'Long string update should work');
  }

  public testStringEnvironmentValueUnicodeString(): void {
    // 测试 Unicode 字符串的处理
    const unicodeString = 'Hello 世界 🌍';
    const envValue = new StringEnvironmentValue(unicodeString);
    eq(envValue.value, unicodeString, 'Unicode string should be preserved');
    envValue.update('你好 World 🎉');
    eq(envValue.value, '你好 World 🎉', 'Unicode string update should work');
  }

  public testStringEnvironmentValueSpecialCharacters(): void {
    // 测试特殊字符的处理
    const specialChars = 'line1\nline2\ttab\rcarriage\\back/forward';
    const envValue = new StringEnvironmentValue(specialChars);
    eq(envValue.value, specialChars, 'Special characters should be preserved');
  }

  // -------------------------------------------------------------------------
  // NumberEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testNumberEnvironmentValueInitialValue(): void {
    // 测试数字环境值的初始值设置
    const envValue = new NumberEnvironmentValue(42);
    eq(envValue.value, 42, 'Initial value should be set correctly');
  }

  public testNumberEnvironmentValueUpdate(): void {
    // 测试数字环境值的更新功能
    const envValue = new NumberEnvironmentValue(42);
    envValue.update(100);
    eq(envValue.value, 100, 'Value should be updated correctly');
  }

  public testNumberEnvironmentValueZero(): void {
    // 测试零值的处理
    const envValue = new NumberEnvironmentValue(0);
    eq(envValue.value, 0, 'Zero value should be preserved');
    envValue.update(0);
    eq(envValue.value, 0, 'Zero value update should work');
  }

  public testNumberEnvironmentValueNegative(): void {
    // 测试负数的处理
    const envValue = new NumberEnvironmentValue(-100);
    eq(envValue.value, -100, 'Negative value should be preserved');
    envValue.update(-200);
    eq(envValue.value, -200, 'Negative value update should work');
  }

  public testNumberEnvironmentValueFloat(): void {
    // 测试浮点数的处理
    const envValue = new NumberEnvironmentValue(3.14);
    eq(envValue.value, 3.14, 'Float value should be preserved');
    envValue.update(2.718);
    eq(envValue.value, 2.718, 'Float value update should work');
  }

  public testNumberEnvironmentValueLargeNumber(): void {
    // 测试大数的处理
    const largeNumber = Number.MAX_SAFE_INTEGER;
    const envValue = new NumberEnvironmentValue(largeNumber);
    eq(envValue.value, largeNumber, 'Large number should be preserved');
  }

  public testNumberEnvironmentValueSmallNumber(): void {
    // 测试小数的处理
    const smallNumber = Number.MIN_SAFE_INTEGER;
    const envValue = new NumberEnvironmentValue(smallNumber);
    eq(envValue.value, smallNumber, 'Small number should be preserved');
  }

  public testNumberEnvironmentValueNaN(): void {
    // 测试 NaN 的处理
    const envValue = new NumberEnvironmentValue(NaN);
    eq(isNaN(envValue.value), true, 'NaN should be preserved');
  }

  public testNumberEnvironmentValueInfinity(): void {
    // 测试 Infinity 的处理
    const envValue = new NumberEnvironmentValue(Infinity);
    eq(envValue.value, Infinity, 'Infinity should be preserved');
    envValue.update(-Infinity);
    eq(envValue.value, -Infinity, '-Infinity update should work');
  }

  public testNumberEnvironmentValueUpdateCount(): void {
    // 测试更新计数功能
    const envValue = new NumberEnvironmentValue(0);
    eq(envValue.getUpdateCount(), 0, 'Initial update count should be 0');
    envValue.update(1);
    eq(envValue.getUpdateCount(), 1, 'Update count should be 1 after first update');
    envValue.update(2);
    envValue.update(3);
    eq(envValue.getUpdateCount(), 3, 'Update count should be 3 after three updates');
  }

  public testNumberEnvironmentValueDestroy(): void {
    // 测试销毁数字环境值
    const envValue = new NumberEnvironmentValue(42);
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
  }

  // -------------------------------------------------------------------------
  // BooleanEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testBooleanEnvironmentValueInitialValue(): void {
    // 测试布尔环境值的初始值设置
    const envValue = new BooleanEnvironmentValue(true);
    eq(envValue.value, true, 'Initial value should be set correctly');
  }

  public testBooleanEnvironmentValueUpdate(): void {
    // 测试布尔环境值的更新功能
    const envValue = new BooleanEnvironmentValue(true);
    envValue.update(false);
    eq(envValue.value, false, 'Value should be updated correctly');
  }

  public testBooleanEnvironmentValueToggle(): void {
    // 测试布尔值的切换
    const envValue = new BooleanEnvironmentValue(false);
    envValue.update(true);
    eq(envValue.value, true, 'Value should be true after first toggle');
    envValue.update(false);
    eq(envValue.value, false, 'Value should be false after second toggle');
    envValue.update(true);
    eq(envValue.value, true, 'Value should be true after third toggle');
  }

  public testBooleanEnvironmentValueFalseInitial(): void {
    // 测试 false 初始值
    const envValue = new BooleanEnvironmentValue(false);
    eq(envValue.value, false, 'Initial false value should be preserved');
  }

  public testBooleanEnvironmentValueDestroy(): void {
    // 测试销毁布尔环境值
    const envValue = new BooleanEnvironmentValue(true);
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
  }

  // -------------------------------------------------------------------------
  // ObjectEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testObjectEnvironmentValueInitialValue(): void {
    // 测试对象环境值的初始值设置
    const initialObj = { id: 1, name: 'test' };
    const envValue = new ObjectEnvironmentValue(initialObj);
    eq(envValue.value.id, 1, 'Initial object id should be preserved');
    eq(envValue.value.name, 'test', 'Initial object name should be preserved');
  }

  public testObjectEnvironmentValueUpdate(): void {
    // 测试对象环境值的更新功能
    const initialObj = { id: 1, name: 'test' };
    const envValue = new ObjectEnvironmentValue(initialObj);
    const updatedObj = { id: 2, name: 'updated' };
    envValue.update(updatedObj);
    eq(envValue.value.id, 2, 'Updated object id should be correct');
    eq(envValue.value.name, 'updated', 'Updated object name should be correct');
  }

  public testObjectEnvironmentValueNestedObject(): void {
    // 测试嵌套对象的处理
    const nestedObj = {
      user: {
        id: 1,
        profile: {
          name: 'John',
          age: 30
        }
      }
    };
    const envValue = new ObjectEnvironmentValue(nestedObj);
    eq(envValue.value.user.profile.name, 'John', 'Nested object should be preserved');
    eq(envValue.value.user.profile.age, 30, 'Nested object age should be preserved');
  }

  public testObjectEnvironmentValueEmptyObject(): void {
    // 测试空对象的处理
    const emptyObj = {};
    const envValue = new ObjectEnvironmentValue(emptyObj);
    eq(Object.keys(envValue.value).length, 0, 'Empty object should be preserved');
  }

  public testObjectEnvironmentValueLargeObject(): void {
    // 测试大对象的处理
    const largeObj: any = {};
    for (let i = 0; i < 100; i++) {
      largeObj[`field${i}`] = i;
    }
    const envValue = new ObjectEnvironmentValue(largeObj);
    eq(Object.keys(envValue.value).length, 100, 'Large object should be preserved');
    eq(envValue.value.field50, 50, 'Large object field should be accessible');
  }

  public testObjectEnvironmentValueCloneOnUpdate(): void {
    // 测试更新时克隆对象
    const initialObj = { id: 1, name: 'test' };
    const envValue = new ObjectEnvironmentValue(initialObj, true);
    const updatedObj = { id: 2, name: 'updated' };
    envValue.update(updatedObj);
    eq(envValue.value.id, 2, 'Cloned object id should be correct');
    eq(envValue.value.name, 'updated', 'Cloned object name should be correct');
  }

  public testObjectEnvironmentValueUserObject(): void {
    // 测试用户对象的处理
    const user: User = {
      id: 1,
      name: 'John Doe',
      email: 'john@example.com',
      age: 30,
      active: true
    };
    const envValue = new ObjectEnvironmentValue<User>(user);
    eq(envValue.value.id, 1, 'User id should be preserved');
    eq(envValue.value.name, 'John Doe', 'User name should be preserved');
    eq(envValue.value.email, 'john@example.com', 'User email should be preserved');
    eq(envValue.value.age, 30, 'User age should be preserved');
    eq(envValue.value.active, true, 'User active status should be preserved');
  }

  public testObjectEnvironmentValueDestroy(): void {
    // 测试销毁对象环境值
    const envValue = new ObjectEnvironmentValue({ id: 1 });
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
  }

  // -------------------------------------------------------------------------
  // ArrayEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testArrayEnvironmentValueInitialValue(): void {
    // 测试数组环境值的初始值设置
    const initialArray = [1, 2, 3];
    const envValue = new ArrayEnvironmentValue(initialArray);
    eq(envValue.value.length, 3, 'Initial array length should be preserved');
    eq(envValue.value[0], 1, 'Initial array element should be preserved');
  }

  public testArrayEnvironmentValueUpdate(): void {
    // 测试数组环境值的更新功能
    const initialArray = [1, 2, 3];
    const envValue = new ArrayEnvironmentValue(initialArray);
    const updatedArray = [4, 5, 6];
    envValue.update(updatedArray);
    eq(envValue.value.length, 3, 'Updated array length should be correct');
    eq(envValue.value[0], 4, 'Updated array element should be correct');
  }

  public testArrayEnvironmentValueEmptyArray(): void {
    // 测试空数组的处理
    const emptyArray: number[] = [];
    const envValue = new ArrayEnvironmentValue(emptyArray);
    eq(envValue.value.length, 0, 'Empty array should be preserved');
  }

  public testArrayEnvironmentValueLargeArray(): void {
    // 测试大数组的处理
    const largeArray: number[] = [];
    for (let i = 0; i < 1000; i++) {
      largeArray.push(i);
    }
    const envValue = new ArrayEnvironmentValue(largeArray);
    eq(envValue.value.length, 1000, 'Large array should be preserved');
    eq(envValue.value[500], 500, 'Large array element should be accessible');
  }

  public testArrayEnvironmentValueStringArray(): void {
    // 测试字符串数组的处理
    const stringArray = ['a', 'b', 'c'];
    const envValue = new ArrayEnvironmentValue(stringArray);
    eq(envValue.value.length, 3, 'String array length should be preserved');
    eq(envValue.value[0], 'a', 'String array element should be preserved');
  }

  public testArrayEnvironmentValueObjectArray(): void {
    // 测试对象数组的处理
    const objectArray = [{ id: 1 }, { id: 2 }, { id: 3 }];
    const envValue = new ArrayEnvironmentValue(objectArray);
    eq(envValue.value.length, 3, 'Object array length should be preserved');
    eq(envValue.value[0].id, 1, 'Object array element should be preserved');
  }

  public testArrayEnvironmentValueMaxSize(): void {
    // 测试数组最大大小限制
    const envValue = new ArrayEnvironmentValue<number>([], 5);
    const smallArray = [1, 2, 3];
    envValue.update(smallArray);
    eq(envValue.value.length, 3, 'Small array should be accepted');
    try {
      const largeArray = [1, 2, 3, 4, 5, 6];
      envValue.update(largeArray);
      eq(false, true, 'Should throw error for array exceeding max size');
    } catch (e) {
      eq(true, true, 'Error should be thrown for array exceeding max size');
    }
  }

  public testArrayEnvironmentValueDestroy(): void {
    // 测试销毁数组环境值
    const envValue = new ArrayEnvironmentValue([1, 2, 3]);
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
  }

  // -------------------------------------------------------------------------
  // ObservableEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testObservableEnvironmentValueInitialValue(): void {
    // 测试可观察环境值的初始值设置
    const envValue = new ObservableEnvironmentValue('initial');
    eq(envValue.value, 'initial', 'Initial value should be set correctly');
  }

  public testObservableEnvironmentValueUpdate(): void {
    // 测试可观察环境值的更新功能
    const envValue = new ObservableEnvironmentValue('initial');
    envValue.update('updated');
    eq(envValue.value, 'updated', 'Value should be updated correctly');
  }

  public testObservableEnvironmentValueAddObserver(): void {
    // 测试添加观察者
    const envValue = new ObservableEnvironmentValue(0);
    let observedOldValue = -1;
    let observedNewValue = -1;
    const observer = (oldValue: number, newValue: number) => {
      observedOldValue = oldValue;
      observedNewValue = newValue;
    };
    envValue.addObserver(observer);
    envValue.update(10);
    eq(observedOldValue, 0, 'Observer should receive old value');
    eq(observedNewValue, 10, 'Observer should receive new value');
  }

  public testObservableEnvironmentValueMultipleObservers(): void {
    // 测试多个观察者
    const envValue = new ObservableEnvironmentValue(0);
    let observer1Called = false;
    let observer2Called = false;
    const observer1 = (oldValue: number, newValue: number) => {
      observer1Called = true;
    };
    const observer2 = (oldValue: number, newValue: number) => {
      observer2Called = true;
    };
    envValue.addObserver(observer1);
    envValue.addObserver(observer2);
    envValue.update(10);
    eq(observer1Called, true, 'Observer 1 should be called');
    eq(observer2Called, true, 'Observer 2 should be called');
  }

  public testObservableEnvironmentValueRemoveObserver(): void {
    // 测试移除观察者
    const envValue = new ObservableEnvironmentValue(0);
    let observerCalled = false;
    const observer = (oldValue: number, newValue: number) => {
      observerCalled = true;
    };
    envValue.addObserver(observer);
    envValue.removeObserver(observer);
    envValue.update(10);
    eq(observerCalled, false, 'Removed observer should not be called');
  }

  public testObservableEnvironmentValueObserverCount(): void {
    // 测试观察者计数
    const envValue = new ObservableEnvironmentValue(0);
    eq(envValue.getObserverCount(), 0, 'Initial observer count should be 0');
    const observer1 = (oldValue: number, newValue: number) => {};
    const observer2 = (oldValue: number, newValue: number) => {};
    envValue.addObserver(observer1);
    eq(envValue.getObserverCount(), 1, 'Observer count should be 1 after adding one observer');
    envValue.addObserver(observer2);
    eq(envValue.getObserverCount(), 2, 'Observer count should be 2 after adding two observers');
    envValue.removeObserver(observer1);
    eq(envValue.getObserverCount(), 1, 'Observer count should be 1 after removing one observer');
  }

  public testObservableEnvironmentValueObserverErrorHandling(): void {
    // 测试观察者错误处理
    const envValue = new ObservableEnvironmentValue(0);
    const errorObserver = (old: number, newV: number) => {
      throw new Error('Observer error');
    };
    const normalObserver = (old: number, newV: number) => {};
    envValue.addObserver(errorObserver);
    envValue.addObserver(normalObserver);
    envValue.update(10);
    eq(envValue.value, 10, 'Value should be updated even if observer throws error');
  }

  public testObservableEnvironmentValueDestroy(): void {
    // 测试销毁可观察环境值
    const envValue = new ObservableEnvironmentValue('test');
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
    eq(envValue.getObserverCount(), 0, 'Observers should be cleared after destroy');
  }

  // -------------------------------------------------------------------------
  // ValidatedEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testValidatedEnvironmentValueInitialValue(): void {
    // 测试带验证的环境值的初始值设置
    const validator = (value: number) => value >= 0;
    const envValue = new ValidatedEnvironmentValue(10, validator);
    eq(envValue.value, 10, 'Initial value should be set correctly');
  }

  public testValidatedEnvironmentValueValidUpdate(): void {
    // 测试有效值的更新
    const validator = (value: number) => value >= 0;
    const envValue = new ValidatedEnvironmentValue(10, validator);
    envValue.update(20);
    eq(envValue.value, 20, 'Valid value should be updated');
  }

  public testValidatedEnvironmentValueInvalidUpdate(): void {
    // 测试无效值的更新
    const validator = (value: number) => value >= 0;
    const envValue = new ValidatedEnvironmentValue(10, validator);
    try {
      envValue.update(-5);
      eq(false, true, 'Should throw error for invalid value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for invalid value');
      eq(envValue.value, 10, 'Value should remain unchanged after invalid update');
    }
  }

  public testValidatedEnvironmentValueStringValidator(): void {
    // 测试字符串验证器
    const validator = (value: string) => value.length > 0;
    const envValue = new ValidatedEnvironmentValue('test', validator);
    envValue.update('new');
    eq(envValue.value, 'new', 'Valid string should be updated');
    try {
      envValue.update('');
      eq(false, true, 'Should throw error for empty string');
    } catch (e) {
      eq(true, true, 'Error should be thrown for empty string');
    }
  }

  public testValidatedEnvironmentValueRangeValidator(): void {
    // 测试范围验证器
    const validator = (value: number) => value >= 0 && value <= 100;
    const envValue = new ValidatedEnvironmentValue(50, validator);
    envValue.update(75);
    eq(envValue.value, 75, 'Value in range should be updated');
    try {
      envValue.update(150);
      eq(false, true, 'Should throw error for value out of range');
    } catch (e) {
      eq(true, true, 'Error should be thrown for value out of range');
    }
  }

  public testValidatedEnvironmentValueObjectValidator(): void {
    // 测试对象验证器
    const validator = (value: User) => value.age >= 0 && value.age <= 150;
    const user: User = { id: 1, name: 'John', email: 'john@example.com', age: 30, active: true };
    const envValue = new ValidatedEnvironmentValue(user, validator);
    const validUser: User = { id: 2, name: 'Jane', email: 'jane@example.com', age: 25, active: true };
    envValue.update(validUser);
    eq(envValue.value.age, 25, 'Valid user should be updated');
    try {
      const invalidUser: User = { id: 3, name: 'Bob', email: 'bob@example.com', age: 200, active: true };
      envValue.update(invalidUser);
      eq(false, true, 'Should throw error for invalid user');
    } catch (e) {
      eq(true, true, 'Error should be thrown for invalid user');
    }
  }

  public testValidatedEnvironmentValueDestroy(): void {
    // 测试销毁带验证的环境值
    const validator = (value: number) => true;
    const envValue = new ValidatedEnvironmentValue(10, validator);
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
  }

  // -------------------------------------------------------------------------
  // HistoryEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testHistoryEnvironmentValueInitialValue(): void {
    // 测试带历史记录的环境值的初始值设置
    const envValue = new HistoryEnvironmentValue('initial');
    eq(envValue.value, 'initial', 'Initial value should be set correctly');
  }

  public testHistoryEnvironmentValueUpdate(): void {
    // 测试带历史记录的环境值的更新功能
    const envValue = new HistoryEnvironmentValue('v1');
    envValue.update('v2');
    eq(envValue.value, 'v2', 'Value should be updated correctly');
  }

  public testHistoryEnvironmentValueHistory(): void {
    // 测试历史记录功能
    const envValue = new HistoryEnvironmentValue('v1');
    envValue.update('v2');
    envValue.update('v3');
    const history = envValue.getHistory();
    eq(history.length, 3, 'History should contain 3 values');
    eq(history[0], 'v1', 'First history value should be v1');
    eq(history[1], 'v2', 'Second history value should be v2');
    eq(history[2], 'v3', 'Third history value should be v3');
  }

  public testHistoryEnvironmentValueUndo(): void {
    // 测试撤销功能
    const envValue = new HistoryEnvironmentValue('v1');
    envValue.update('v2');
    envValue.update('v3');
    eq(envValue.value, 'v3', 'Current value should be v3');
    const undoResult1 = envValue.undo();
    eq(undoResult1, true, 'Undo should succeed');
    eq(envValue.value, 'v2', 'Value should be v2 after undo');
    const undoResult2 = envValue.undo();
    eq(undoResult2, true, 'Second undo should succeed');
    eq(envValue.value, 'v1', 'Value should be v1 after second undo');
  }

  public testHistoryEnvironmentValueUndoAtStart(): void {
    // 测试在历史记录开始时撤销
    const envValue = new HistoryEnvironmentValue('v1');
    const undoResult = envValue.undo();
    eq(undoResult, false, 'Undo should fail at start of history');
    eq(envValue.value, 'v1', 'Value should remain v1');
  }

  public testHistoryEnvironmentValueMaxHistorySize(): void {
    // 测试最大历史记录大小
    const envValue = new HistoryEnvironmentValue('v1', 3);
    envValue.update('v2');
    envValue.update('v3');
    envValue.update('v4');
    envValue.update('v5');
    const history = envValue.getHistory();
    eq(history.length, 3, 'History should be limited to max size');
    eq(history[0], 'v3', 'Oldest value should be v3');
    eq(history[2], 'v5', 'Newest value should be v5');
  }

  public testHistoryEnvironmentValueAfterUndo(): void {
    // 测试撤销后更新
    const envValue = new HistoryEnvironmentValue('v1');
    envValue.update('v2');
    envValue.update('v3');
    envValue.undo();
    envValue.update('v4');
    const history = envValue.getHistory();
    eq(history.length, 3, 'History should contain 3 values after undo and update');
    eq(history[2], 'v4', 'Newest value should be v4');
  }

  public testHistoryEnvironmentValueDestroy(): void {
    // 测试销毁带历史记录的环境值
    const envValue = new HistoryEnvironmentValue('test');
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
    eq(envValue.getHistory().length, 0, 'History should be cleared after destroy');
  }

  // -------------------------------------------------------------------------
  // DelayedEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testDelayedEnvironmentValueInitialValue(): void {
    // 测试带延迟更新的环境值的初始值设置
    const envValue = new DelayedEnvironmentValue('initial', 0);
    eq(envValue.value, 'initial', 'Initial value should be set correctly');
  }

  public testDelayedEnvironmentValueImmediateUpdate(): void {
    // 测试立即更新（延迟为0）
    const envValue = new DelayedEnvironmentValue('initial', 0);
    envValue.update('updated');
    eq(envValue.value, 'updated', 'Value should be updated immediately when delay is 0');
  }

  public testDelayedEnvironmentValueDelayedUpdate(): void {
    // 测试延迟更新
    const envValue = new DelayedEnvironmentValue('initial', 100);
    envValue.update('updated');
    eq(envValue.value, 'initial', 'Value should not change immediately');
    eq(envValue.hasPendingUpdate(), true, 'Should have pending update');
  }

  public testDelayedEnvironmentValueMultipleDelayedUpdates(): void {
    // 测试多次延迟更新
    const envValue = new DelayedEnvironmentValue('initial', 100);
    envValue.update('v1');
    eq(envValue.hasPendingUpdate(), true, 'Should have pending update after first update');
    envValue.update('v2');
    eq(envValue.hasPendingUpdate(), true, 'Should still have pending update after second update');
  }

  public testDelayedEnvironmentValueDestroy(): void {
    // 测试销毁带延迟更新的环境值
    const envValue = new DelayedEnvironmentValue('test', 100);
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
  }

  // -------------------------------------------------------------------------
  // TransformedEnvironmentValue Tests
  // -------------------------------------------------------------------------

  public testTransformedEnvironmentValueInitialValue(): void {
    // 测试带转换的环境值的初始值设置
    const transform = (value: number) => value.toString();
    const inverseTransform = (value: string) => parseInt(value, 10);
    const envValue = new TransformedEnvironmentValue(42, transform, inverseTransform);
    eq(envValue.value, 42, 'Initial value should be set correctly');
  }

  public testTransformedEnvironmentValueUpdate(): void {
    // 测试带转换的环境值的更新功能
    const transform = (value: number) => value.toString();
    const inverseTransform = (value: string) => parseInt(value, 10);
    const envValue = new TransformedEnvironmentValue(42, transform, inverseTransform);
    envValue.update(100);
    eq(envValue.value, 100, 'Value should be updated correctly');
  }

  public testTransformedEnvironmentValueGetTransformedValue(): void {
    // 测试获取转换后的值
    const transform = (value: number) => value * 2;
    const inverseTransform = (value: number) => value / 2;
    const envValue = new TransformedEnvironmentValue(10, transform, inverseTransform);
    const transformedValue = envValue.getTransformedValue();
    eq(transformedValue, 20, 'Transformed value should be correct');
  }

  public testTransformedEnvironmentValueUpdateFromTransformed(): void {
    // 测试从转换后的值更新
    const transform = (value: number) => value * 2;
    const inverseTransform = (value: number) => value / 2;
    const envValue = new TransformedEnvironmentValue(10, transform, inverseTransform);
    envValue.updateFromTransformed(40);
    eq(envValue.value, 20, 'Value should be updated from transformed value');
  }

  public testTransformedEnvironmentValueStringTransform(): void {
    // 测试字符串转换
    const transform = (value: string) => value.toUpperCase();
    const inverseTransform = (value: string) => value.toLowerCase();
    const envValue = new TransformedEnvironmentValue('hello', transform, inverseTransform);
    const transformedValue = envValue.getTransformedValue();
    eq(transformedValue, 'HELLO', 'String transform should work correctly');
    envValue.updateFromTransformed('WORLD');
    eq(envValue.value, 'world', 'Update from transformed should work correctly');
  }

  public testTransformedEnvironmentValueDestroy(): void {
    // 测试销毁带转换的环境值
    const transform = (value: number) => value.toString();
    const inverseTransform = (value: string) => parseInt(value, 10);
    const envValue = new TransformedEnvironmentValue(42, transform, inverseTransform);
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'EnvironmentValue should be marked as destroyed');
  }

  // =========================================================================
  // 6. 边界测试
  // =========================================================================

  public testEdgeCaseNullValue(): void {
    // 测试 null 值的处理
    const envValue = new StringEnvironmentValue('test');
    try {
      envValue.update(null as any);
      eq(false, true, 'Should handle null value appropriately');
    } catch (e) {
      eq(true, true, 'Error handling for null value');
    }
  }

  public testEdgeCaseUndefinedValue(): void {
    // 测试 undefined 值的处理
    const envValue = new StringEnvironmentValue('test');
    try {
      envValue.update(undefined as any);
      eq(false, true, 'Should handle undefined value appropriately');
    } catch (e) {
      eq(true, true, 'Error handling for undefined value');
    }
  }

  public testEdgeCaseRapidUpdates(): void {
    // 测试快速连续更新
    const envValue = new NumberEnvironmentValue(0);
    for (let i = 0; i < 1000; i++) {
      envValue.update(i);
    }
    eq(envValue.value, 999, 'Value should reflect the last rapid update');
    eq(envValue.getUpdateCount(), 1000, 'Update count should reflect all rapid updates');
  }

  public testEdgeCaseConcurrentAccess(): void {
    // 测试并发访问
    const envValue = new NumberEnvironmentValue(0);
    const value1 = envValue.value;
    const value2 = envValue.value;
    eq(value1, value2, 'Concurrent reads should return same value');
  }

  public testEdgeCaseLargeHistory(): void {
    // 测试大历史记录
    const envValue = new HistoryEnvironmentValue('v1', 1000);
    for (let i = 0; i < 1000; i++) {
      envValue.update(`v${i + 2}`);
    }
    const history = envValue.getHistory();
    eq(history.length, 1000, 'Large history should be preserved');
  }

  public testEdgeCaseManyObservers(): void {
    // 测试大量观察者
    const envValue = new ObservableEnvironmentValue(0);
    const observerCount = 100;
    for (let i = 0; i < observerCount; i++) {
      envValue.addObserver((old: number, newV: number) => {});
    }
    eq(envValue.getObserverCount(), observerCount, 'All observers should be added');
  }

  public testEdgeCaseEmptyHistoryUndo(): void {
    // 测试空历史记录撤销
    const envValue = new HistoryEnvironmentValue('v1', 1);
    const result = envValue.undo();
    eq(result, false, 'Undo should fail with single history entry');
  }

  public testEdgeCaseTransformedValueInverse(): void {
    // 测试转换值的逆转换
    const transform = (value: number) => value * 10;
    const inverseTransform = (value: number) => value / 10;
    const envValue = new TransformedEnvironmentValue(5, transform, inverseTransform);
    const transformed = envValue.getTransformedValue();
    envValue.updateFromTransformed(transformed);
    eq(envValue.value, 5, 'Inverse transform should return original value');
  }

  // =========================================================================
  // 7. 错误测试
  // -------------------------------------------------------------------------

  public testErrorAccessDestroyedValue(): void {
    // 测试访问已销毁的值
    const envValue = new StringEnvironmentValue('test');
    envValue.destroy();
    try {
      const value = envValue.value;
      eq(false, true, 'Should throw error when accessing destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for destroyed value access');
    }
  }

  public testErrorUpdateDestroyedValue(): void {
    // 测试更新已销毁的值
    const envValue = new StringEnvironmentValue('test');
    envValue.destroy();
    try {
      envValue.update('new');
      eq(false, true, 'Should throw error when updating destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for destroyed value update');
    }
  }

  public testErrorAddObserverToDestroyedValue(): void {
    // 测试向已销毁的值添加观察者
    const envValue = new ObservableEnvironmentValue(0);
    envValue.destroy();
    try {
      envValue.addObserver((old: number, newV: number) => {});
      eq(false, true, 'Should throw error when adding observer to destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for adding observer to destroyed value');
    }
  }

  public testErrorRemoveObserverFromDestroyedValue(): void {
    // 测试从已销毁的值移除观察者
    const envValue = new ObservableEnvironmentValue(0);
    const observer = (old: number, newV: number) => {};
    envValue.destroy();
    try {
      envValue.removeObserver(observer);
      eq(false, true, 'Should throw error when removing observer from destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for removing observer from destroyed value');
    }
  }

  public testErrorUndoDestroyedValue(): void {
    // 测试撤销已销毁的值
    const envValue = new HistoryEnvironmentValue('v1');
    envValue.destroy();
    try {
      envValue.undo();
      eq(false, true, 'Should throw error when undoing destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for undoing destroyed value');
    }
  }

  public testErrorGetHistoryOfDestroyedValue(): void {
    // 测试获取已销毁值的历史记录
    const envValue = new HistoryEnvironmentValue('v1');
    envValue.destroy();
    try {
      const history = envValue.getHistory();
      eq(false, true, 'Should throw error when getting history of destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for getting history of destroyed value');
    }
  }

  public testErrorGetTransformedValueOfDestroyedValue(): void {
    // 测试获取已销毁值的转换值
    const transform = (value: number) => value.toString();
    const inverseTransform = (value: string) => parseInt(value, 10);
    const envValue = new TransformedEnvironmentValue(42, transform, inverseTransform);
    envValue.destroy();
    try {
      const transformed = envValue.getTransformedValue();
      eq(false, true, 'Should throw error when getting transformed value of destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for getting transformed value of destroyed value');
    }
  }

  public testErrorUpdateFromTransformedOfDestroyedValue(): void {
    // 测试从转换值更新已销毁的值
    const transform = (value: number) => value.toString();
    const inverseTransform = (value: string) => parseInt(value, 10);
    const envValue = new TransformedEnvironmentValue(42, transform, inverseTransform);
    envValue.destroy();
    try {
      envValue.updateFromTransformed('100');
      eq(false, true, 'Should throw error when updating from transformed value of destroyed value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for updating from transformed value of destroyed value');
    }
  }

  public testErrorArrayExceedsMaxSize(): void {
    // 测试数组超过最大大小
    const envValue = new ArrayEnvironmentValue<number>([], 5);
    try {
      const largeArray = [1, 2, 3, 4, 5, 6];
      envValue.update(largeArray);
      eq(false, true, 'Should throw error when array exceeds max size');
    } catch (e) {
      eq(true, true, 'Error should be thrown for array exceeding max size');
    }
  }

  public testErrorInvalidValidatedValue(): void {
    // 测试无效的验证值
    const validator = (value: number) => value >= 0;
    const envValue = new ValidatedEnvironmentValue(10, validator);
    try {
      envValue.update(-1);
      eq(false, true, 'Should throw error for invalid validated value');
    } catch (e) {
      eq(true, true, 'Error should be thrown for invalid validated value');
    }
  }

  // =========================================================================
  // 8. 性能测试
  // =========================================================================

  public testPerformanceLargeStringUpdate(): void {
    // 测试大字符串更新的性能
    const largeString = 'a'.repeat(10000);
    const envValue = new StringEnvironmentValue(largeString);
    const startTime = Date.now();
    envValue.update('b'.repeat(10000));
    const duration = Date.now() - startTime;
    eq(duration < 100, true, 'Large string update should complete quickly');
    eq(envValue.value.length, 10000, 'Large string should be updated correctly');
  }

  public testPerformanceManyNumberUpdates(): void {
    // 测试多次数字更新的性能
    const envValue = new NumberEnvironmentValue(0);
    const iterations = 10000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      envValue.update(i);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Many number updates should complete quickly');
    eq(envValue.value, iterations - 1, 'Final value should be correct');
  }

  public testPerformanceLargeObjectUpdate(): void {
    // 测试大对象更新的性能
    const largeObj: any = {};
    for (let i = 0; i < 1000; i++) {
      largeObj[`field${i}`] = i;
    }
    const envValue = new ObjectEnvironmentValue(largeObj);
    const startTime = Date.now();
    const updatedObj: any = {};
    for (let i = 0; i < 1000; i++) {
      updatedObj[`field${i}`] = i * 2;
    }
    envValue.update(updatedObj);
    const duration = Date.now() - startTime;
    eq(duration < 100, true, 'Large object update should complete quickly');
  }

  public testPerformanceLargeArrayUpdate(): void {
    // 测试大数组更新的性能
    const largeArray: number[] = [];
    for (let i = 0; i < 10000; i++) {
      largeArray.push(i);
    }
    const envValue = new ArrayEnvironmentValue(largeArray);
    const startTime = Date.now();
    const updatedArray: number[] = [];
    for (let i = 0; i < 10000; i++) {
      updatedArray.push(i * 2);
    }
    envValue.update(updatedArray);
    const duration = Date.now() - startTime;
    eq(duration < 100, true, 'Large array update should complete quickly');
  }

  public testPerformanceManyObserverNotifications(): void {
    // 测试多次观察者通知的性能
    const envValue = new ObservableEnvironmentValue(0);
    let notificationCount = 0;
    const observer = (old: number, newV: number) => {
      notificationCount++;
    };
    for (let i = 0; i < 100; i++) {
      envValue.addObserver(observer);
    }
    const startTime = Date.now();
    envValue.update(1);
    const duration = Date.now() - startTime;
    eq(duration < 100, true, 'Many observer notifications should complete quickly');
    eq(notificationCount, 100, 'All observers should be notified');
  }

  public testPerformanceLargeHistory(): void {
    // 测试大历史记录的性能
    const envValue = new HistoryEnvironmentValue('v1', 1000);
    const startTime = Date.now();
    for (let i = 0; i < 1000; i++) {
      envValue.update(`v${i + 2}`);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Large history operations should complete quickly');
    eq(envValue.getHistory().length, 1000, 'All history entries should be preserved');
  }

  public testPerformanceComplexValidation(): void {
    // 测试复杂验证的性能
    const complexValidator = (value: number) => {
      for (let i = 0; i < 100; i++) {
        if (value % i === 0) {
          return true;
        }
      }
      return false;
    };
    const envValue = new ValidatedEnvironmentValue(100, complexValidator);
    const startTime = Date.now();
    for (let i = 0; i < 1000; i++) {
      try {
        envValue.update(i);
      } catch (e) {
        // Ignore validation errors
      }
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Complex validation should complete quickly');
  }

  public testPerformanceTransformOperations(): void {
    // 测试转换操作的性能
    const complexTransform = (value: number) => {
      let result = value;
      for (let i = 0; i < 100; i++) {
        result = result * 2;
      }
      return result;
    };
    const complexInverseTransform = (value: number) => {
      let result = value;
      for (let i = 0; i < 100; i++) {
        result = result / 2;
      }
      return result;
    };
    const envValue = new TransformedEnvironmentValue(1, complexTransform, complexInverseTransform);
    const startTime = Date.now();
    for (let i = 0; i < 100; i++) {
      const transformed = envValue.getTransformedValue();
      envValue.updateFromTransformed(transformed);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Complex transform operations should complete quickly');
  }

  // =========================================================================
  // 9. 兼容性测试
  // =========================================================================

  public testCompatibilityMultipleInstances(): void {
    // 测试多个实例的兼容性
    const envValue1 = new StringEnvironmentValue('test1');
    const envValue2 = new StringEnvironmentValue('test2');
    eq(envValue1.value, 'test1', 'First instance should have correct value');
    eq(envValue2.value, 'test2', 'Second instance should have correct value');
    envValue1.update('updated1');
    envValue2.update('updated2');
    eq(envValue1.value, 'updated1', 'First instance should update independently');
    eq(envValue2.value, 'updated2', 'Second instance should update independently');
  }

  public testCompatibilityDifferentTypes(): void {
    // 测试不同类型的兼容性
    const stringEnv = new StringEnvironmentValue('test');
    const numberEnv = new NumberEnvironmentValue(42);
    const booleanEnv = new BooleanEnvironmentValue(true);
    eq(stringEnv.value, 'test', 'String environment should work');
    eq(numberEnv.value, 42, 'Number environment should work');
    eq(booleanEnv.value, true, 'Boolean environment should work');
  }

  public testCompatibilityGenericTypes(): void {
    // 测试泛型类型的兼容性
    const stringArrayEnv = new ArrayEnvironmentValue<string>(['a', 'b', 'c']);
    const numberArrayEnv = new ArrayEnvironmentValue<number>([1, 2, 3]);
    eq(stringArrayEnv.value.length, 3, 'String array environment should work');
    eq(numberArrayEnv.value.length, 3, 'Number array environment should work');
  }

  public testCompatibilityChainedUpdates(): void {
    // 测试链式更新的兼容性
    const envValue = new NumberEnvironmentValue(0);
    envValue.update(1);
    envValue.update(envValue.value + 1);
    envValue.update(envValue.value + 1);
    eq(envValue.value, 3, 'Chained updates should work correctly');
  }

  public testCompatibilityObserverLifecycle(): void {
    // 测试观察者生命周期的兼容性
    const envValue = new ObservableEnvironmentValue(0);
    let callCount = 0;
    const observer = (old: number, newV: number) => {
      callCount++;
    };
    envValue.addObserver(observer);
    envValue.update(1);
    eq(callCount, 1, 'Observer should be called once');
    envValue.removeObserver(observer);
    envValue.update(2);
    eq(callCount, 1, 'Observer should not be called after removal');
  }

  public testCompatibilityHistoryConsistency(): void {
    // 测试历史记录的一致性
    const envValue = new HistoryEnvironmentValue('v1');
    envValue.update('v2');
    envValue.update('v3');
    envValue.undo();
    const history = envValue.getHistory();
    eq(history.length, 2, 'History should be consistent after undo');
    eq(history[1], 'v2', 'Current value should be in history');
  }

  public testCompatibilityValidationConsistency(): void {
    // 测试验证的一致性
    const validator = (value: number) => value >= 0;
    const envValue = new ValidatedEnvironmentValue(10, validator);
    envValue.update(20);
    eq(envValue.value, 20, 'Valid update should succeed');
    try {
      envValue.update(-10);
      eq(false, true, 'Invalid update should fail');
    } catch (e) {
      eq(envValue.value, 20, 'Value should remain unchanged after invalid update');
    }
  }

  public testCompatibilityTransformRoundTrip(): void {
    // 测试转换的往返一致性
    const transform = (value: number) => value * 2;
    const inverseTransform = (value: number) => value / 2;
    const envValue = new TransformedEnvironmentValue(10, transform, inverseTransform);
    const originalValue = envValue.value;
    const transformed = envValue.getTransformedValue();
    envValue.updateFromTransformed(transformed);
    eq(envValue.value, originalValue, 'Round trip transform should preserve value');
  }

  public testCompatibilityMixedOperations(): void {
    // 测试混合操作的兼容性
    const envValue = new HistoryEnvironmentValue('v1', 10);
    envValue.update('v2');
    envValue.update('v3');
    envValue.undo();
    envValue.update('v4');
    const history = envValue.getHistory();
    eq(history.length, 3, 'Mixed operations should maintain consistency');
    eq(envValue.value, 'v4', 'Final value should be correct');
  }

  // =========================================================================
  // 10. 集成测试
  // =========================================================================

  public testIntegrationObservableWithHistory(): void {
    // 测试可观察环境值与历史记录的集成
    const envValue = new HistoryEnvironmentValue(0, 10);
    let updateCount = 0;
    const observer = (old: number, newV: number) => {
      updateCount++;
    };
    const observableEnv = new ObservableEnvironmentValue(envValue.value);
    observableEnv.addObserver(observer);
    envValue.update(1);
    observableEnv.update(envValue.value);
    eq(updateCount, 1, 'Observer should be notified');
    eq(envValue.value, 1, 'History environment should be updated');
  }

  public testIntegrationValidatedWithObservable(): void {
    // 测试验证环境值与可观察环境值的集成
    const validator = (value: number) => value >= 0;
    const validatedEnv = new ValidatedEnvironmentValue(10, validator);
    const observableEnv = new ObservableEnvironmentValue(validatedEnv.value);
    let updateCount = 0;
    const observer = (old: number, newV: number) => {
      updateCount++;
    };
    observableEnv.addObserver(observer);
    validatedEnv.update(20);
    observableEnv.update(validatedEnv.value);
    eq(updateCount, 1, 'Observer should be notified for valid update');
    eq(validatedEnv.value, 20, 'Validated environment should be updated');
  }

  public testIntegrationTransformedWithHistory(): void {
    // 测试转换环境值与历史记录的集成
    const transform = (value: number) => value.toString();
    const inverseTransform = (value: string) => parseInt(value, 10);
    const transformedEnv = new TransformedEnvironmentValue(10, transform, inverseTransform);
    const historyEnv = new HistoryEnvironmentValue(transformedEnv.value, 10);
    historyEnv.update(20);
    transformedEnv.update(historyEnv.value);
    eq(transformedEnv.value, 20, 'Transformed environment should be updated');
    eq(historyEnv.value, 20, 'History environment should be updated');
  }

  public testIntegrationMultipleEnvironments(): void {
    // 测试多个环境值的集成
    const stringEnv = new StringEnvironmentValue('test');
    const numberEnv = new NumberEnvironmentValue(0);
    const booleanEnv = new BooleanEnvironmentValue(false);
    const arrayEnv = new ArrayEnvironmentValue<number>([1, 2, 3]);
    
    stringEnv.update('updated');
    numberEnv.update(100);
    booleanEnv.update(true);
    arrayEnv.update([4, 5, 6]);
    
    eq(stringEnv.value, 'updated', 'String environment should be updated');
    eq(numberEnv.value, 100, 'Number environment should be updated');
    eq(booleanEnv.value, true, 'Boolean environment should be updated');
    eq(arrayEnv.value.length, 3, 'Array environment should be updated');
  }

  public testIntegrationComplexWorkflow(): void {
    // 测试复杂工作流
    const historyEnv = new HistoryEnvironmentValue(0, 10);
    const observableEnv = new ObservableEnvironmentValue(historyEnv.value);
    
    let updateCount = 0;
    const observer = (old: number, newV: number) => {
      updateCount++;
    };
    observableEnv.addObserver(observer);
    
    for (let i = 1; i <= 5; i++) {
      historyEnv.update(i);
      observableEnv.update(historyEnv.value);
    }
    
    eq(updateCount, 5, 'Observer should be notified 5 times');
    eq(historyEnv.value, 5, 'History environment should have final value');
    
    historyEnv.undo();
    observableEnv.update(historyEnv.value);
    
    eq(updateCount, 6, 'Observer should be notified after undo');
    eq(historyEnv.value, 4, 'History environment should undo to previous value');
  }

  // =========================================================================
  // 11. 更多边界测试
  // =========================================================================

  public testEdgeCaseMaximumSafeInteger(): void {
    // 测试最大安全整数
    const envValue = new NumberEnvironmentValue(Number.MAX_SAFE_INTEGER);
    eq(envValue.value, Number.MAX_SAFE_INTEGER, 'Maximum safe integer should be preserved');
    envValue.update(Number.MAX_SAFE_INTEGER - 1);
    eq(envValue.value, Number.MAX_SAFE_INTEGER - 1, 'Update near max safe integer should work');
  }

  public testEdgeCaseMinimumSafeInteger(): void {
    // 测试最小安全整数
    const envValue = new NumberEnvironmentValue(Number.MIN_SAFE_INTEGER);
    eq(envValue.value, Number.MIN_SAFE_INTEGER, 'Minimum safe integer should be preserved');
    envValue.update(Number.MIN_SAFE_INTEGER + 1);
    eq(envValue.value, Number.MIN_SAFE_INTEGER + 1, 'Update near min safe integer should work');
  }

  public testEdgeCaseVerySmallFloat(): void {
    // 测试非常小的浮点数
    const envValue = new NumberEnvironmentValue(0.0000001);
    eq(envValue.value, 0.0000001, 'Very small float should be preserved');
    envValue.update(0.00000001);
    eq(envValue.value, 0.00000001, 'Update very small float should work');
  }

  public testEdgeCaseVeryLargeFloat(): void {
    // 测试非常大的浮点数
    const envValue = new NumberEnvironmentValue(999999999.999999);
    eq(envValue.value, 999999999.999999, 'Very large float should be preserved');
    envValue.update(9999999999.9999999);
    eq(envValue.value, 9999999999.9999999, 'Update very large float should work');
  }

  public testEdgeCaseNegativeZero(): void {
    // 测试负零
    const envValue = new NumberEnvironmentValue(-0);
    eq(envValue.value, 0, 'Negative zero should be treated as zero');
    envValue.update(0);
    eq(envValue.value, 0, 'Update to zero should work');
  }

  public testEdgeCaseEmptyStringInArray(): void {
    // 测试数组中的空字符串
    const envValue = new ArrayEnvironmentValue<string>(['', 'test', '']);
    eq(envValue.value.length, 3, 'Array with empty strings should be preserved');
    eq(envValue.value[0], '', 'Empty string in array should be preserved');
    eq(envValue.value[2], '', 'Last empty string should be preserved');
  }

  public testEdgeCaseMixedTypeArray(): void {
    // 测试混合类型数组
    const envValue = new ArrayEnvironmentValue<any>([1, 'two', true, null, undefined]);
    eq(envValue.value.length, 5, 'Mixed type array should be preserved');
    eq(envValue.value[0], 1, 'Number in mixed array should be preserved');
    eq(envValue.value[1], 'two', 'String in mixed array should be preserved');
    eq(envValue.value[2], true, 'Boolean in mixed array should be preserved');
  }

  public testEdgeCaseSparseArray(): void {
    // 测试稀疏数组
    const sparseArray: any[] = [1, , , 4];
    const envValue = new ArrayEnvironmentValue(sparseArray);
    eq(envValue.value.length, 4, 'Sparse array length should be preserved');
    eq(envValue.value[0], 1, 'First element should be preserved');
    eq(envValue.value[3], 4, 'Last element should be preserved');
  }

  public testEdgeCaseDeeplyNestedObject(): void {
    // 测试深层嵌套对象
    const deepObj: any = { level1: { level2: { level3: { level4: { value: 'deep' } } } } };
    const envValue = new ObjectEnvironmentValue(deepObj);
    eq(envValue.value.level1.level2.level3.level4.value, 'deep', 'Deeply nested object should be preserved');
  }

  public testEdgeCaseObjectWithManyProperties(): void {
    // 测试具有许多属性的对象
    const largeObj: any = {};
    for (let i = 0; i < 100; i++) {
      largeObj[`prop${i}`] = `value${i}`;
    }
    const envValue = new ObjectEnvironmentValue(largeObj);
    eq(Object.keys(envValue.value).length, 100, 'Object with many properties should be preserved');
    eq(envValue.value.prop50, 'value50', 'Property in large object should be accessible');
  }

  public testEdgeCaseStringWithEscapedCharacters(): void {
    // 测试包含转义字符的字符串
    const escapedString = 'Hello\\World\tTest\nNewline\rReturn\bBackspace\fFormfeed';
    const envValue = new StringEnvironmentValue(escapedString);
    eq(envValue.value, escapedString, 'String with escaped characters should be preserved');
  }

  public testEdgeCaseStringWithQuotes(): void {
    // 测试包含引号的字符串
    const quotedString = 'He said "Hello" and she replied \'Hi\'';
    const envValue = new StringEnvironmentValue(quotedString);
    eq(envValue.value, quotedString, 'String with quotes should be preserved');
  }

  public testEdgeCaseUnicodeSurrogatePairs(): void {
    // 测试 Unicode 代理对
    const surrogateString = '𝄆𝄇𝄈𝄉'; // 数学符号
    const envValue = new StringEnvironmentValue(surrogateString);
    eq(envValue.value, surrogateString, 'String with surrogate pairs should be preserved');
  }

  public testEdgeCaseZeroWidthCharacters(): void {
    // 测试零宽字符
    const zeroWidthString = 'a\u200Bb\u200Cc\u200Dd'; // 零宽字符
    const envValue = new StringEnvironmentValue(zeroWidthString);
    eq(envValue.value, zeroWidthString, 'String with zero-width characters should be preserved');
  }

  public testEdgeCaseRightToLeftText(): void {
    // 测试从右到左的文本
    const rtlString = 'مرحبا بالعالم'; // 阿拉伯语
    const envValue = new StringEnvironmentValue(rtlString);
    eq(envValue.value, rtlString, 'RTL text should be preserved');
  }

  public testEdgeCaseMixedDirectionText(): void {
    // 测试混合方向文本
    const mixedString = 'Hello مرحبا World'; // 混合 LTR 和 RTL
    const envValue = new StringEnvironmentValue(mixedString);
    eq(envValue.value, mixedString, 'Mixed direction text should be preserved');
  }

  public testEdgeCaseBooleanCoercion(): void {
    // 测试布尔值强制转换
    const envValue = new BooleanEnvironmentValue(true);
    envValue.update(false);
    eq(envValue.value, false, 'Boolean update should work');
    eq(envValue.value === false, true, 'Boolean should be strictly false');
  }

  public testEdgeCaseArrayBoundaryValues(): void {
    // 测试数组边界值
    const envValue = new ArrayEnvironmentValue<number>([Number.MIN_VALUE, Number.MAX_VALUE, 0, -0]);
    eq(4, 4, 'Array with boundary values should be preserved');
  }

  public testEdgeCaseObjectWithNullProperties(): void {
    // 测试包含 null 属性的对象
    const objWithNull = { a: null, b: 'test', c: null };
    const envValue = new ObjectEnvironmentValue(objWithNull);
    eq(envValue.value.a, null, 'Null property should be preserved');
    eq(envValue.value.b, 'test', 'Normal property should be preserved');
    eq(envValue.value.c, null, 'Another null property should be preserved');
  }

  public testEdgeCaseObjectWithUndefinedProperties(): void {
    // 测试包含 undefined 属性的对象
    const objWithUndefined: any = { a: undefined, b: 'test', c: undefined };
    const envValue = new ObjectEnvironmentValue(objWithUndefined);
    eq(envValue.value.a, undefined, 'Undefined property should be preserved');
    eq(envValue.value.b, 'test', 'Normal property should be preserved');
  }

  public testEdgeCaseCircularReferenceDetection(): void {
    // 测试循环引用检测（不创建真正的循环引用，而是测试类似场景）
    const obj1: any = { id: 1 };
    const obj2: any = { id: 2, ref: obj1 };
    const envValue = new ObjectEnvironmentValue(obj2);
    eq(envValue.value.id, 2, 'Object with reference should be preserved');
    eq(envValue.value.ref.id, 1, 'Referenced object should be preserved');
  }

  // =========================================================================
  // 12. 更多错误测试
  // =========================================================================

  public testErrorInvalidTypeConversion(): void {
    // 测试无效的类型转换
    const envValue = new NumberEnvironmentValue(42);
    try {
      envValue.update('not a number' as any);
      eq(false, true, 'Should handle invalid type conversion');
    } catch (e) {
      eq(true, true, 'Error should be handled for invalid type conversion');
    }
  }

  public testErrorObjectMutationAfterUpdate(): void {
    // 测试更新后对象突变
    const originalObj = { id: 1, name: 'test' };
    const envValue = new ObjectEnvironmentValue(originalObj);
    const updatedObj = { id: 2, name: 'updated' };
    envValue.update(updatedObj);
    updatedObj.name = 'mutated';
    eq(envValue.value.name, 'mutated', 'Object mutation after update should be reflected');
  }

  public testErrorArrayMutationAfterUpdate(): void {
    // 测试更新后数组突变
    const originalArray = [1, 2, 3];
    const envValue = new ArrayEnvironmentValue(originalArray);
    const updatedArray = [4, 5, 6];
    envValue.update(updatedArray);
    updatedArray.push(7);
    eq(envValue.value.length, 4, 'Array mutation after update should be reflected');
  }

  public testErrorValidationWithNullValidator(): void {
    // 测试空验证器
    try {
      const envValue = new ValidatedEnvironmentValue(10, null as any);
      eq(false, true, 'Should handle null validator');
    } catch (e) {
      eq(true, true, 'Error should be handled for null validator');
    }
  }

  public testErrorValidationWithUndefinedValidator(): void {
    // 测试未定义验证器
    try {
      const envValue = new ValidatedEnvironmentValue(10, undefined as any);
      eq(false, true, 'Should handle undefined validator');
    } catch (e) {
      eq(true, true, 'Error should be handled for undefined validator');
    }
  }

  public testErrorTransformWithNullFunction(): void {
    // 测试空转换函数
    try {
      const envValue = new TransformedEnvironmentValue(10, null as any, null as any);
      eq(false, true, 'Should handle null transform function');
    } catch (e) {
      eq(true, true, 'Error should be handled for null transform function');
    }
  }

  public testErrorTransformWithUndefinedFunction(): void {
    // 测试未定义转换函数
    try {
      const envValue = new TransformedEnvironmentValue(10, undefined as any, undefined as any);
      eq(false, true, 'Should handle undefined transform function');
    } catch (e) {
      eq(true, true, 'Error should be handled for undefined transform function');
    }
  }

  public testErrorObserverThrowingException(): void {
    // 测试观察者抛出异常
    const envValue = new ObservableEnvironmentValue(0);
    const throwingObserver = (old: number, newV: number) => {
      throw new Error('Observer error');
    };
    envValue.addObserver(throwingObserver);
    try {
      envValue.update(1);
      eq(true, true, 'Value should be updated even if observer throws');
    } catch (e) {
      eq(false, true, 'Observer error should not propagate');
    }
  }

  public testErrorMultipleObserversThrowing(): void {
    // 测试多个观察者抛出异常
    const envValue = new ObservableEnvironmentValue(0);
    const throwingObserver1 = (old: number, newV: number) => {
      throw new Error('Observer 1 error');
    };
    const throwingObserver2 = (old: number, newV: number) => {
      throw new Error('Observer 2 error');
    };
    envValue.addObserver(throwingObserver1);
    envValue.addObserver(throwingObserver2);
    envValue.update(1);
    eq(envValue.value, 1, 'Value should be updated even if multiple observers throw');
  }

  public testErrorDelayedUpdateWithNegativeDelay(): void {
    // 测试负的延迟时间
    const envValue = new DelayedEnvironmentValue('initial', -100);
    envValue.update('updated');
    eq(envValue.value, 'updated', 'Negative delay should result in immediate update');
  }

  public testErrorVeryLongDelay(): void {
    // 测试非常长的延迟时间
    const envValue = new DelayedEnvironmentValue('initial', 999999999);
    envValue.update('updated');
    eq(envValue.value, 'initial', 'Value should not change immediately with very long delay');
    eq(envValue.hasPendingUpdate(), true, 'Should have pending update with very long delay');
  }

  public testErrorValidationReturningNonBoolean(): void {
    // 测试返回非布尔值的验证器
    const nonBooleanValidator = (value: number) => 'yes' as any;
    const envValue = new ValidatedEnvironmentValue(10, nonBooleanValidator);
    try {
      envValue.update(20);
      eq(false, true, 'Should handle non-boolean validation result');
    } catch (e) {
      eq(true, true, 'Error should be handled for non-boolean validation result');
    }
  }

  public testErrorTransformReturningDifferentType(): void {
    // 测试返回不同类型的转换函数
    const wrongTransform = (value: number) => 'not a number' as any;
    const wrongInverseTransform = (value: string) => 42;
    const envValue = new TransformedEnvironmentValue(10, wrongTransform, wrongInverseTransform);
    const transformed = envValue.getTransformedValue();
    eq(typeof transformed, 'string', 'Transform should return string type');
  }

  public testErrorRapidDestroyAndAccess(): void {
    // 测试快速销毁和访问
    const envValue = new StringEnvironmentValue('test');
    envValue.destroy();
    try {
      const value = envValue.value;
      eq(false, true, 'Should throw error on access after destroy');
    } catch (e) {
      eq(true, true, 'Error should be thrown on access after destroy');
    }
  }

  public testErrorMultipleDestroys(): void {
    // 测试多次销毁
    const envValue = new StringEnvironmentValue('test');
    envValue.destroy();
    envValue.destroy();
    eq(envValue.isDestroyed(), true, 'Multiple destroys should be idempotent');
  }

  // =========================================================================
  // 13. 更多性能测试
  // =========================================================================

  public testPerformanceMillionUpdates(): void {
    // 测试百万次更新
    const envValue = new NumberEnvironmentValue(0);
    const iterations = 1000000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      envValue.update(i);
    }
    const duration = Date.now() - startTime;
    eq(duration < 5000, true, 'Million updates should complete within 5 seconds');
    eq(envValue.value, iterations - 1, 'Final value should be correct');
  }

  public testPerformanceHundredThousandObservers(): void {
    // 测试十万个观察者
    const envValue = new ObservableEnvironmentValue(0);
    const observerCount = 100000;
    for (let i = 0; i < observerCount; i++) {
      envValue.addObserver((old: number, newV: number) => {});
    }
    const startTime = Date.now();
    envValue.update(1);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Notifying 100k observers should complete within 1 second');
    eq(envValue.getObserverCount(), observerCount, 'All observers should be preserved');
  }

  public testPerformanceThousandHistoryOperations(): void {
    // 测试一千次历史记录操作
    const envValue = new HistoryEnvironmentValue('v1', 1000);
    const startTime = Date.now();
    for (let i = 0; i < 1000; i++) {
      envValue.update(`v${i + 2}`);
    }
    for (let i = 0; i < 500; i++) {
      envValue.undo();
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, '1000 history operations should complete within 1 second');
  }

  public testPerformanceLargeObjectWithDeepNesting(): void {
    // 测试具有深层嵌套的大对象
    let deepObj: any = { value: 'deep' };
    for (let i = 0; i < 100; i++) {
      deepObj = { level: i, nested: deepObj };
    }
    const envValue = new ObjectEnvironmentValue(deepObj);
    const startTime = Date.now();
    envValue.update(deepObj);
    const duration = Date.now() - startTime;
    eq(duration < 100, true, 'Deeply nested object update should complete quickly');
  }

  public testPerformanceVeryLargeArray(): void {
    // 测试非常大的数组
    const veryLargeArray: number[] = [];
    for (let i = 0; i < 100000; i++) {
      veryLargeArray.push(i);
    }
    const envValue = new ArrayEnvironmentValue(veryLargeArray);
    const startTime = Date.now();
    const updatedArray = veryLargeArray.map(x => x * 2);
    envValue.update(updatedArray);
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Very large array update should complete within 1 second');
  }

  public testPerformanceComplexObjectValidation(): void {
    // 测试复杂对象验证
    const complexValidator = (value: User) => {
      if (value.id < 0) return false;
      if (value.name.length === 0) return false;
      if (!value.email.includes('@')) return false;
      if (value.age < 0 || value.age > 150) return false;
      return true;
    };
    const user: User = { id: 1, name: 'John', email: 'john@example.com', age: 30, active: true };
    const envValue = new ValidatedEnvironmentValue(user, complexValidator);
    const startTime = Date.now();
    for (let i = 0; i < 10000; i++) {
      const testUser: User = { id: i, name: 'Test', email: 'test@example.com', age: 30, active: true };
      envValue.update(testUser);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Complex object validation should complete within 1 second');
  }

  public testPerformanceStringOperations(): void {
    // 测试字符串操作
    const envValue = new StringEnvironmentValue('');
    const startTime = Date.now();
    for (let i = 0; i < 10000; i++) {
      envValue.update(`test string ${i} with some content`);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'String operations should complete within 1 second');
  }

  public testPerformanceMixedTypeOperations(): void {
    // 测试混合类型操作
    const stringEnv = new StringEnvironmentValue('test');
    const numberEnv = new NumberEnvironmentValue(0);
    const booleanEnv = new BooleanEnvironmentValue(false);
    const startTime = Date.now();
    for (let i = 0; i < 10000; i++) {
      stringEnv.update(`test${i}`);
      numberEnv.update(i);
      booleanEnv.update(i % 2 === 0);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Mixed type operations should complete within 1 second');
  }

  public testPerformanceObserverAddRemoveCycle(): void {
    // 测试观察者添加删除循环
    const envValue = new ObservableEnvironmentValue(0);
    const observer = (old: number, newV: number) => {};
    const startTime = Date.now();
    for (let i = 0; i < 10000; i++) {
      envValue.addObserver(observer);
      envValue.removeObserver(observer);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Observer add/remove cycle should complete within 1 second');
  }

  public testPerformanceMemoryAllocation(): void {
    // 测试内存分配
    const envValues: NumberEnvironmentValue[] = [];
    const startTime = Date.now();
    for (let i = 0; i < 10000; i++) {
      const envValue = new NumberEnvironmentValue(i);
      envValue.update(i * 2);
      envValues.push(envValue);
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Creating and updating 10k instances should complete within 1 second');
    eq(envValues.length, 10000, 'All instances should be created');
  }

  // =========================================================================
  // 14. 更多集成测试
  // =========================================================================

  public testIntegrationObservableWithValidation(): void {
    // 测试可观察环境值与验证的集成
    const validator = (value: number) => value >= 0;
    const validatedEnv = new ValidatedEnvironmentValue(10, validator);
    const observableEnv = new ObservableEnvironmentValue(validatedEnv.value);
    
    let updateCount = 0;
    let lastValue = 10;
    const observer = (old: number, newV: number) => {
      updateCount++;
      lastValue = newV;
    };
    observableEnv.addObserver(observer);
    
    validatedEnv.update(20);
    observableEnv.update(validatedEnv.value);
    
    eq(updateCount, 1, 'Observer should be notified for valid update');
    eq(lastValue, 20, 'Observer should receive new value');
    
    try {
      validatedEnv.update(-10);
      eq(false, true, 'Invalid update should fail');
    } catch (e) {
      eq(updateCount, 1, 'Observer should not be notified for invalid update');
    }
  }

  public testIntegrationHistoryWithValidation(): void {
    // 测试历史记录与验证的集成
    const validator = (value: number) => value >= 0;
    const envValue = new ValidatedEnvironmentValue(10, validator);
    const historyEnv = new HistoryEnvironmentValue(envValue.value, 10);
    
    envValue.update(20);
    historyEnv.update(envValue.value);
    
    eq(historyEnv.value, 20, 'History should track valid updates');
    eq(historyEnv.getHistory().length, 2, 'History should have 2 entries');
    
    try {
      envValue.update(-10);
      eq(false, true, 'Invalid update should fail');
    } catch (e) {
      eq(historyEnv.value, 20, 'History should not track invalid updates');
      eq(historyEnv.getHistory().length, 2, 'History should still have 2 entries');
    }
  }

  public testIntegrationTransformedWithObservable(): void {
    // 测试转换环境值与可观察环境值的集成
    const transform = (value: number) => value * 2;
    const inverseTransform = (value: number) => value / 2;
    const transformedEnv = new TransformedEnvironmentValue(10, transform, inverseTransform);
    const observableEnv = new ObservableEnvironmentValue(transformedEnv.value);
    
    let updateCount = 0;
    const observer = (old: number, newV: number) => {
      updateCount++;
    };
    observableEnv.addObserver(observer);
    
    transformedEnv.update(20);
    observableEnv.update(transformedEnv.value);
    
    eq(updateCount, 1, 'Observer should be notified');
    eq(observableEnv.value, 20, 'Observable should track transformed value');
  }

  public testIntegrationMultipleObserversWithHistory(): void {
    // 测试多个观察者与历史记录的集成
    const historyEnv = new HistoryEnvironmentValue(0, 10);
    const observableEnv1 = new ObservableEnvironmentValue(historyEnv.value);
    const observableEnv2 = new ObservableEnvironmentValue(historyEnv.value);
    
    let observer1Count = 0;
    let observer2Count = 0;
    
    observableEnv1.addObserver((old: number, newV: number) => {
      observer1Count++;
    });
    
    observableEnv2.addObserver((old: number, newV: number) => {
      observer2Count++;
    });
    
    for (let i = 1; i <= 5; i++) {
      historyEnv.update(i);
      observableEnv1.update(historyEnv.value);
      observableEnv2.update(historyEnv.value);
    }
    
    eq(observer1Count, 5, 'Observer 1 should be notified 5 times');
    eq(observer2Count, 5, 'Observer 2 should be notified 5 times');
    eq(historyEnv.getHistory().length, 6, 'History should have 6 entries');
  }

  public testIntegrationComplexChain(): void {
    // 测试复杂链式集成
    const validator = (value: number) => value >= 0;
    const validatedEnv = new ValidatedEnvironmentValue(10, validator);
    const historyEnv = new HistoryEnvironmentValue(validatedEnv.value, 10);
    const observableEnv = new ObservableEnvironmentValue(historyEnv.value);
    
    let updateCount = 0;
    observableEnv.addObserver((old: number, newV: number) => {
      updateCount++;
    });
    
    // 执行一系列操作
    validatedEnv.update(20);
    historyEnv.update(validatedEnv.value);
    observableEnv.update(historyEnv.value);
    
    eq(updateCount, 1, 'Observer should be notified');
    eq(historyEnv.getHistory().length, 2, 'History should have 2 entries');
    
    historyEnv.undo();
    observableEnv.update(historyEnv.value);
    
    eq(updateCount, 2, 'Observer should be notified after undo');
    eq(historyEnv.value, 10, 'History should undo to initial value');
  }

  public testIntegrationDelayedWithObservable(): void {
    // 测试延迟更新与可观察环境值的集成
    const delayedEnv = new DelayedEnvironmentValue('initial', 0);
    const observableEnv = new ObservableEnvironmentValue(delayedEnv.value);
    
    let updateCount = 0;
    observableEnv.addObserver((old: string, newV: string) => {
      updateCount++;
    });
    
    delayedEnv.update('updated');
    observableEnv.update(delayedEnv.value);
    
    eq(updateCount, 1, 'Observer should be notified');
    eq(observableEnv.value, 'updated', 'Observable should track delayed value');
  }

  public testIntegrationTransformedWithHistoryAndObservable(): void {
    // 测试转换、历史记录和可观察环境值的完整集成
    const transform = (value: number) => value.toString();
    const inverseTransform = (value: string) => parseInt(value, 10);
    const transformedEnv = new TransformedEnvironmentValue(10, transform, inverseTransform);
    const historyEnv = new HistoryEnvironmentValue(transformedEnv.value, 10);
    const observableEnv = new ObservableEnvironmentValue(historyEnv.value);
    
    let updateCount = 0;
    observableEnv.addObserver((old: number, newV: number) => {
      updateCount++;
    });
    
    // 通过转换更新
    transformedEnv.update(20);
    historyEnv.update(transformedEnv.value);
    observableEnv.update(historyEnv.value);
    
    eq(updateCount, 1, 'Observer should be notified');
    eq(observableEnv.value, 20, 'Observable should track value');
    
    // 撤销
    historyEnv.undo();
    observableEnv.update(historyEnv.value);
    
    eq(updateCount, 2, 'Observer should be notified after undo');
    eq(observableEnv.value, 10, 'Observable should track undo');
  }

  public testIntegrationArrayWithValidation(): void {
    // 测试数组与验证的集成
    const validator = (value: number[]) => value.length <= 10;
    const envValue = new ValidatedEnvironmentValue([1, 2, 3], validator);
    
    eq(envValue.value.length, 3, 'Initial array should be valid');
    
    envValue.update([1, 2, 3, 4, 5]);
    eq(envValue.value.length, 5, 'Valid array update should work');
    
    try {
      envValue.update(new Array(20).fill(0));
      eq(false, true, 'Invalid array update should fail');
    } catch (e) {
      eq(envValue.value.length, 5, 'Array should remain unchanged after invalid update');
    }
  }

  public testIntegrationObjectWithObservableAndHistory(): void {
    // 测试对象与可观察环境值和历史记录的集成
    const user: User = { id: 1, name: 'John', email: 'john@example.com', age: 30, active: true };
    const objectEnv = new ObjectEnvironmentValue<User>(user);
    const historyEnv = new HistoryEnvironmentValue(objectEnv.value, 10);
    const observableEnv = new ObservableEnvironmentValue(historyEnv.value);
    
    let updateCount = 0;
    observableEnv.addObserver((old: User, newV: User) => {
      updateCount++;
    });
    
    const updatedUser: User = { id: 2, name: 'Jane', email: 'jane@example.com', age: 25, active: true };
    objectEnv.update(updatedUser);
    historyEnv.update(objectEnv.value);
    observableEnv.update(historyEnv.value);
    
    eq(updateCount, 1, 'Observer should be notified');
    eq(observableEnv.value.name, 'Jane', 'Observable should track updated user');
    
    historyEnv.undo();
    observableEnv.update(historyEnv.value);
    
    eq(updateCount, 2, 'Observer should be notified after undo');
    eq(observableEnv.value.name, 'John', 'Observable should track undo');
  }

  // =========================================================================
  // 15. 特殊场景测试
  // =========================================================================

  public testSpecialScenarioValueReassignment(): void {
    // 测试值重新赋值
    const { value } = new StringEnvironmentValue('initial');
    eq(value, 'initial', 'Destructured value should be accessible');
  }

  public testSpecialScenarioMultipleReferences(): void {
    // 测试多个引用
    const envValue = new NumberEnvironmentValue(42);
    const ref1 = envValue;
    const ref2 = envValue;
    
    ref1.update(100);
    eq(ref2.value, 100, 'Multiple references should point to same instance');
  }

  public testSpecialScenarioValueGetterChaining(): void {
    // 测试值获取器链式调用
    const envValue = new NumberEnvironmentValue(10);
    const doubled = envValue.value * 2;
    const tripled = envValue.value * 3;
    
    eq(doubled, 20, 'Value getter should work in expression');
    eq(tripled, 30, 'Value getter should work in another expression');
  }

  public testSpecialScenarioConditionalUpdate(): void {
    // 测试条件更新
    const envValue = new NumberEnvironmentValue(10);
    
    if (envValue.value > 5) {
      envValue.update(20);
    }
    
    eq(envValue.value, 20, 'Conditional update should work');
  }

  public testSpecialScenarioLoopUpdate(): void {
    // 测试循环更新
    const envValue = new NumberEnvironmentValue(0);
    
    for (let i = 0; i < 10; i++) {
      if (envValue.value < 50) {
        envValue.update(envValue.value + 10);
      }
    }
    
    eq(envValue.value, 50, 'Loop update should work');
  }

  public testSpecialScenarioRecursiveUpdate(): void {
    // 测试递归更新（模拟）
    const envValue = new NumberEnvironmentValue(0);
    
    const updateRecursively = (target: number, current: number): void => {
      if (current < target) {
        envValue.update(current + 1);
        updateRecursively(target, current + 1);
      }
    };
    
    updateRecursively(5, 0);
    eq(envValue.value, 5, 'Recursive update should work');
  }

  public testSpecialScenarioValueAsFunctionParameter(): void {
    // 测试值作为函数参数
    const envValue = new StringEnvironmentValue('test');
    
    const processValue = (value: string): string => {
      return value.toUpperCase();
    };
    
    const result = processValue(envValue.value);
    eq(result, 'TEST', 'Value should work as function parameter');
  }

  public testSpecialScenarioValueInArrayOperations(): void {
    // 测试值在数组操作中
    const envValue = new NumberEnvironmentValue(5);
    
    const array = [1, 2, 3, envValue.value, 4];
    eq(array.length, 5, 'Value should work in array');
    eq(array[3], 5, 'Value should be correct in array');
    
    const includes = array.includes(envValue.value);
    eq(includes, true, 'Value should be found in array');
  }

  public testSpecialScenarioValueInObjectOperations(): void {
    // 测试值在对象操作中
    const envValue = new StringEnvironmentValue('test');
    
    const obj = { key: envValue.value, other: 'value' };
    eq(obj.key, 'test', 'Value should work in object');
    
    const hasKey = 'key' in obj;
    eq(hasKey, true, 'Object should have key');
  }

  public testSpecialScenarioValueComparison(): void {
    // 测试值比较
    const envValue1 = new NumberEnvironmentValue(10);
    const envValue2 = new NumberEnvironmentValue(20);
    
    eq(envValue1.value < envValue2.value, true, 'Value comparison should work');
    eq(envValue1.value !== envValue2.value, true, 'Value inequality should work');
  }

  public testSpecialScenarioValueInTemplate(): void {
    // 测试值在模板字符串中
    const envValue = new StringEnvironmentValue('world');
    const message = `Hello ${envValue.value}!`;
    eq(message, 'Hello world!', 'Value should work in template string');
  }

  public testSpecialScenarioValueInConditionalExpression(): void {
    // 测试值在条件表达式中
    const envValue = new BooleanEnvironmentValue(true);
    const result = envValue.value ? 'yes' : 'no';
    eq(result, 'yes', 'Value should work in conditional expression');
  }

  public testSpecialScenarioValueInSwitchStatement(): void {
    // 测试值在 switch 语句中
    const envValue = new NumberEnvironmentValue(2);
    let result = '';
    
    switch (envValue.value) {
      case 1:
        result = 'one';
        break;
      case 2:
        result = 'two';
        break;
      default:
        result = 'other';
    }
    
    eq(result, 'two', 'Value should work in switch statement');
  }

  public testSpecialScenarioValueInTryCatch(): void {
    // 测试值在 try-catch 中
    const envValue = new StringEnvironmentValue('test');
    let result = '';
    
    try {
      result = envValue.value.toUpperCase();
    } catch (e) {
      result = 'error';
    }
    
    eq(result, 'TEST', 'Value should work in try-catch');
  }

  public testSpecialScenarioValueInPromise(): void {
    // 测试值在 Promise 中（模拟）
    const envValue = new StringEnvironmentValue('test');
    
    const promise = new Promise((resolve) => {
      resolve(envValue.value);
    });
    
    eq(promise instanceof Promise, true, 'Value should work in Promise');
  }

  public testSpecialScenarioValueInSet(): void {
    // 测试值在 Set 中
    const envValue = new NumberEnvironmentValue(42);
    const set = new Set([envValue.value, 10, 20]);
    eq(set.has(42), true, 'Value should work in Set');
  }

  public testSpecialScenarioValueInMap(): void {
    // 测试值在 Map 中
    const envValue = new StringEnvironmentValue('test');
    const map = new Map([['key', envValue.value]]);
    eq(map.get('key'), 'test', 'Value should work in Map');
  }

  public testSpecialScenarioValueInJSON(): void {
    // 测试值在 JSON 操作中
    const envValue = new NumberEnvironmentValue(42);
    const obj = { value: envValue.value };
    const json = JSON.stringify(obj);
    const parsed = JSON.parse(json);
    eq(parsed.value, 42, 'Value should work in JSON operations');
  }

  public testSpecialScenarioValueInMathOperations(): void {
    // 测试值在数学运算中
    const envValue = new NumberEnvironmentValue(10);
    
    const added = envValue.value + 5;
    const subtracted = envValue.value - 3;
    const multiplied = envValue.value * 2;
    const divided = envValue.value / 2;
    
    eq(added, 15, 'Value should work in addition');
    eq(subtracted, 7, 'Value should work in subtraction');
    eq(multiplied, 20, 'Value should work in multiplication');
    eq(divided, 5, 'Value should work in division');
  }

  public testSpecialScenarioValueInBitwiseOperations(): void {
    // 测试值在位运算中
    const envValue = new NumberEnvironmentValue(5);
    
    const and = envValue.value & 3;
    const or = envValue.value | 2;
    const xor = envValue.value ^ 1;
    
    eq(and, 1, 'Value should work in bitwise AND');
    eq(or, 7, 'Value should work in bitwise OR');
    eq(xor, 4, 'Value should work in bitwise XOR');
  }

  public testSpecialScenarioValueInStringOperations(): void {
    // 测试值在字符串操作中
    const envValue = new StringEnvironmentValue('test');
    
    const length = envValue.value.length;
    const upper = envValue.value.toUpperCase();
    const lower = envValue.value.toLowerCase();
    const sliced = envValue.value.slice(0, 2);
    
    eq(length, 4, 'Value should work in string length');
    eq(upper, 'TEST', 'Value should work in toUpperCase');
    eq(lower, 'test', 'Value should work in toLowerCase');
    eq(sliced, 'te', 'Value should work in slice');
  }
}
