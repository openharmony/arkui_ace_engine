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
import { PersistenceV2 } from '@kit.ArkUI';

class Storage {
  private storage: Map<string, Object> = new Map();

  get<T>(key: string): T | undefined {
    return this.storage.get(key) as T;
  }

  set<T>(key: string, val: T): void {
    this.storage.set(key, val as Object);
  }

  has(key: string): boolean {
    return this.storage.has(key);
  }

  delete(key: string): void {
    this.storage.delete(key);
  }

  clear(): void {
    this.storage.clear();
  }
}

declare interface IPersistenceV2 {
  persistenceV2Impl_: object;
}

declare interface IPersistenceV2ImplStatic {
  storage_: Storage;
  instance_?: object;
  instance: () => object;
}

const instance: object =
  (PersistenceV2 as unknown as IPersistenceV2).persistenceV2Impl_;

const PersistenceV2Impl: IPersistenceV2ImplStatic =
  (instance.constructor as unknown as IPersistenceV2ImplStatic);

const originalStorage: Storage =
  PersistenceV2Impl.storage_;

export const mockStorage = () =>
  PersistenceV2Impl.storage_ = new Storage();

export const unmockStorage = () =>
  PersistenceV2Impl.storage_ = originalStorage;

export const resetPersistenceV2 = () => {
  PersistenceV2Impl.instance_ = undefined;
  (PersistenceV2 as unknown as IPersistenceV2).persistenceV2Impl_ = PersistenceV2Impl.instance();
}
