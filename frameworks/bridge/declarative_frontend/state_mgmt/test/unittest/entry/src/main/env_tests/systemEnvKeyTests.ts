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

import { eq, neq, gt, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class SystemEnvKey {
  keyId: string;
  constructor(keyId: string);
}

declare class WritableSystemEnvKey<T> extends SystemEnvKey {
  constructor(keyId: string);
}

declare class ReadonlySystemEnvKey<T> extends SystemEnvKey {
  constructor(keyId: string);
}

declare class WritableEnvKey {
  static readonly DIRECTION: WritableSystemEnvKey<Object>;
  static readonly FONT_SCALE: WritableSystemEnvKey<number>;
}

declare class ReadonlyEnvKey {
  static readonly WINDOW_AVOID_AREA: ReadonlySystemEnvKey<Object>;
  static readonly WINDOW_AVOID_AREA_PX: ReadonlySystemEnvKey<Object>;
  static readonly WINDOW_SIZE: ReadonlySystemEnvKey<Object>;
  static readonly WINDOW_SIZE_PX: ReadonlySystemEnvKey<Object>;
  static readonly WINDOW_DISPLAY_ID: ReadonlySystemEnvKey<number>;
  static readonly WINDOW_SYSTEM_DENSITY: ReadonlySystemEnvKey<number>;
  static readonly WINDOW_IS_FOCUSED: ReadonlySystemEnvKey<boolean>;
  static readonly WINDOW_IS_HIGHLIGHTED: ReadonlySystemEnvKey<boolean>;
}

declare class CustomEnvKey {
  get internalId(): number;
  static create(): CustomEnvKey;
}

/**
 * SystemEnvKey / CustomEnvKey Unit Tests
 *
 * This test suite validates environment key functionality:
 * - SystemEnvKey constructor stores the key id
 * - WritableSystemEnvKey / ReadonlySystemEnvKey inheritance
 * - All predefined WritableEnvKey entries and their key ids
 * - All predefined ReadonlyEnvKey entries and their key ids
 * - Uniqueness of all system key ids
 * - CustomEnvKey.create and monotonically increasing internal ids
 */
export class SystemEnvKeyTests implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating SystemEnvKeyTests: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('SystemEnvKeyTests: Setting up test suite');
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
    console.log('SystemEnvKeyTests: Tearing down test suite');
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // SECTION 1: SystemEnvKey base class tests
  // =========================================================================

  public testSystemEnvKeyStoresKeyId(): void {
    const key = new SystemEnvKey('test.some.key');

    eq(key.keyId, 'test.some.key', 'constructor must store the key id');
  }

  public testSystemEnvKeyAcceptsArbitraryIds(): void {
    eq(new SystemEnvKey('a').keyId, 'a', 'short key id must be stored');
    eq(new SystemEnvKey('').keyId, '', 'empty key id must be stored as-is');
    eq(new SystemEnvKey('system.very.long.path.key').keyId, 'system.very.long.path.key',
      'long key id must be stored');
  }

  public testWritableSystemEnvKeyIsSystemEnvKey(): void {
    const key = new WritableSystemEnvKey<Object>('test.writable');

    eq(key instanceof SystemEnvKey, true,
      'WritableSystemEnvKey must extend SystemEnvKey');
    eq(key.keyId, 'test.writable', 'key id must be stored');
  }

  public testReadonlySystemEnvKeyIsSystemEnvKey(): void {
    const key = new ReadonlySystemEnvKey<number>('test.readonly');

    eq(key instanceof SystemEnvKey, true,
      'ReadonlySystemEnvKey must extend SystemEnvKey');
    eq(key.keyId, 'test.readonly', 'key id must be stored');
  }

  // =========================================================================
  // SECTION 2: WritableEnvKey tests
  // =========================================================================

  public testWritableDirectionKey(): void {
    const key = WritableEnvKey.DIRECTION;

    neq(key, undefined, 'DIRECTION key must exist');
    eq(key.keyId, 'system.arkui.layout.direction',
      'DIRECTION must use the layout direction key id');
    eq(key instanceof WritableSystemEnvKey, true,
      'DIRECTION must be a WritableSystemEnvKey');
    eq(key instanceof SystemEnvKey, true, 'DIRECTION must be a SystemEnvKey');
  }

  public testWritableFontScaleKey(): void {
    const key = WritableEnvKey.FONT_SCALE;

    neq(key, undefined, 'FONT_SCALE key must exist');
    eq(key.keyId, 'system.arkui.fontScale',
      'FONT_SCALE must use the font scale key id');
    eq(key instanceof WritableSystemEnvKey, true,
      'FONT_SCALE must be a WritableSystemEnvKey');
  }

  public testWritableKeysAreSingleInstances(): void {
    // static readonly: repeated access must return the same object
    eq(WritableEnvKey.DIRECTION, WritableEnvKey.DIRECTION,
      'DIRECTION must be a single static instance');
    eq(WritableEnvKey.FONT_SCALE, WritableEnvKey.FONT_SCALE,
      'FONT_SCALE must be a single static instance');
    neq(WritableEnvKey.DIRECTION, WritableEnvKey.FONT_SCALE,
      'DIRECTION and FONT_SCALE must be different keys');
  }

  // =========================================================================
  // SECTION 3: ReadonlyEnvKey tests
  // =========================================================================

  public testReadonlyWindowAvoidAreaKeys(): void {
    eq(ReadonlyEnvKey.WINDOW_AVOID_AREA.keyId, 'system.window.avoidarea',
      'WINDOW_AVOID_AREA key id');
    eq(ReadonlyEnvKey.WINDOW_AVOID_AREA_PX.keyId, 'system.window.avoidarea.px',
      'WINDOW_AVOID_AREA_PX key id');
  }

  public testReadonlyWindowSizeKeys(): void {
    eq(ReadonlyEnvKey.WINDOW_SIZE.keyId, 'system.window.size',
      'WINDOW_SIZE key id');
    eq(ReadonlyEnvKey.WINDOW_SIZE_PX.keyId, 'system.window.size.px',
      'WINDOW_SIZE_PX key id');
  }

  public testReadonlyWindowDisplayAndDensityKeys(): void {
    eq(ReadonlyEnvKey.WINDOW_DISPLAY_ID.keyId, 'system.window.displayid',
      'WINDOW_DISPLAY_ID key id');
    eq(ReadonlyEnvKey.WINDOW_SYSTEM_DENSITY.keyId, 'system.window.density.system',
      'WINDOW_SYSTEM_DENSITY key id');
  }

  public testReadonlyWindowFocusKeys(): void {
    eq(ReadonlyEnvKey.WINDOW_IS_FOCUSED.keyId, 'system.window.focused',
      'WINDOW_IS_FOCUSED key id');
    eq(ReadonlyEnvKey.WINDOW_IS_HIGHLIGHTED.keyId, 'system.window.highlighted',
      'WINDOW_IS_HIGHLIGHTED key id');
  }

  public testAllReadonlyKeysAreReadonlySystemEnvKeys(): void {
    const keys: SystemEnvKey[] = [
      ReadonlyEnvKey.WINDOW_AVOID_AREA, ReadonlyEnvKey.WINDOW_AVOID_AREA_PX,
      ReadonlyEnvKey.WINDOW_SIZE, ReadonlyEnvKey.WINDOW_SIZE_PX,
      ReadonlyEnvKey.WINDOW_DISPLAY_ID, ReadonlyEnvKey.WINDOW_SYSTEM_DENSITY,
      ReadonlyEnvKey.WINDOW_IS_FOCUSED, ReadonlyEnvKey.WINDOW_IS_HIGHLIGHTED
    ];

    keys.forEach((key: SystemEnvKey, index: number): void => {
      neq(key, undefined, `readonly key at index ${index} must exist`);
      eq(key instanceof ReadonlySystemEnvKey, true,
        `readonly key at index ${index} must be a ReadonlySystemEnvKey`);
      eq(key instanceof SystemEnvKey, true,
        `readonly key at index ${index} must be a SystemEnvKey`);
    });
  }

  // =========================================================================
  // SECTION 4: key uniqueness tests
  // =========================================================================

  public testAllSystemKeyIdsAreUnique(): void {
    const allKeys: SystemEnvKey[] = [
      WritableEnvKey.DIRECTION, WritableEnvKey.FONT_SCALE,
      ReadonlyEnvKey.WINDOW_AVOID_AREA, ReadonlyEnvKey.WINDOW_AVOID_AREA_PX,
      ReadonlyEnvKey.WINDOW_SIZE, ReadonlyEnvKey.WINDOW_SIZE_PX,
      ReadonlyEnvKey.WINDOW_DISPLAY_ID, ReadonlyEnvKey.WINDOW_SYSTEM_DENSITY,
      ReadonlyEnvKey.WINDOW_IS_FOCUSED, ReadonlyEnvKey.WINDOW_IS_HIGHLIGHTED
    ];
    const keyIds = new Set<string>(
      allKeys.map((key: SystemEnvKey): string => key.keyId));

    eq(allKeys.length, 10, 'precondition: 10 predefined system keys');
    eq(keyIds.size, 10, 'all predefined system key ids must be unique');
  }

  public testWritableAndReadonlyKeysUseDistinctIds(): void {
    neq(WritableEnvKey.DIRECTION.keyId, ReadonlyEnvKey.WINDOW_SIZE.keyId,
      'writable and readonly keys must not share ids');
    neq(WritableEnvKey.FONT_SCALE.keyId, ReadonlyEnvKey.WINDOW_DISPLAY_ID.keyId,
      'writable and readonly keys must not share ids');
  }

  // =========================================================================
  // SECTION 5: CustomEnvKey tests
  // =========================================================================

  public testCustomEnvKeyCreateReturnsInstance(): void {
    const key = CustomEnvKey.create();

    neq(key, undefined, 'CustomEnvKey.create() must return an instance');
    gt(key.internalId, 0, 'internal id must be a positive number');
  }

  public testCustomEnvKeyInternalIdsIncrease(): void {
    const key1 = CustomEnvKey.create();
    const key2 = CustomEnvKey.create();
    const key3 = CustomEnvKey.create();

    gt(key2.internalId, key1.internalId,
      'internal ids of consecutively created keys must increase');
    gt(key3.internalId, key2.internalId,
      'internal ids of consecutively created keys must increase');
    eq(key2.internalId - key1.internalId, 1,
      'consecutively created keys must differ by exactly 1');
    eq(key3.internalId - key2.internalId, 1,
      'consecutively created keys must differ by exactly 1');
  }

  public testCustomEnvKeyInstancesAreDistinct(): void {
    const key1 = CustomEnvKey.create();
    const key2 = CustomEnvKey.create();

    neq(key1, key2, 'each create() call must return a new instance');
    neq(key1.internalId, key2.internalId, 'each instance must have its own id');
  }
}
