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

class InteropStorageV2 extends StorageHelper {
  private static instance_: InteropStorageV2 | undefined = undefined;

  // get value from AppStorage in ArkTS1.2
  getStaticValue_: (value: string) => object = () => {
    // will implement further, no error code
    throw new BusinessError(NOT_IMPLEMENT, `getStaticValue_ method does not implement in InteropStorageV2`)
  };
  removeStaticValue_: (value: string) => boolean = () => {
    throw new BusinessError(NOT_IMPLEMENT, `removeStaticValue_ method does not implement in InteropStorageV2`)
  };
  getStaticTotalKeys_: () => Array<string> = () => {
    throw new BusinessError(NOT_IMPLEMENT, `getStaticTotalKeys_ method does not implement in InteropStorageV2`)
  };

  constructor() {
    super();
  }

  public static instance(): InteropStorageV2 {
    if (InteropStorageV2.instance_) {
      return InteropStorageV2.instance_;
    }
    InteropStorageV2.instance_ = new InteropStorageV2();
    return InteropStorageV2.instance_;
  }

  public connect<T extends object>(type: TypeConstructorWithArgs<T>,
    keyOrDefaultCreator?: string | StorageDefaultCreator<T>,
    defaultCreator?: StorageDefaultCreator<T>): T | undefined {
    const key: string | undefined = this.getConnectedKey(type, keyOrDefaultCreator);
    if (!this.isKeyValid(key)) {
      return undefined;
    }
    if (!AppStorageV2Impl.instance().hasKey(key!)) {
      // nonexistence then search in 1.2 
      const interopValue = this.getStaticValue_(key!);
      if (interopValue) {
        return interopValue as T;
      }
    }
    // existence or not in 1.2
    return AppStorageV2Impl.instance().connect(type, keyOrDefaultCreator, defaultCreator);
  }

  public remove<T>(keyOrType: string | TypeConstructorWithArgs<T>): void {
    // delete 1.1
    const isDeleted = AppStorageV2Impl.instance().removeByInterop(keyOrType);
    if (!isDeleted) {
      // keyOrType is verified in remove function
      const key: string | undefined = this.getKeyOrTypeName(keyOrType);
      // delete 1.2
      this.removeStaticValue_(key!);
    }
  }

  public getMemoryKeys(): Array<string> {
    const totalKeys = new Set<string>();
    // 1.1 all keys
    AppStorageV2Impl.instance().getMemoryKeys().forEach((key: string) => {
      totalKeys.add(key);
    });
    // 1.2 all keys
    InteropStorageV2.instance().getStaticTotalKeys_().forEach((key: string) => {
        totalKeys.add(key);
    });
    return Array.from(totalKeys.keys());
  }
}

function bindStaticAppStorageV2(
  getStaticValue: (value: string) => object,
  removeStaticValue: (value: string) => boolean,
  getStaticTotalKeys: () => Array<string>,

  // set callback to ArkTS1.2
  setGetValueFunc: (event: (value: string) => object | undefined) => void,
  setRemoveValueFunc: (event: (value: string | undefined) => boolean) => void,
  setGetKeysFunc: (event: () =>  Array<string>) => void,
): void {
  // bind static storage.
  const interopStorage = InteropStorageV2.instance();
  interopStorage.getStaticValue_ = getStaticValue;
  interopStorage.removeStaticValue_ = removeStaticValue;
  interopStorage.getStaticTotalKeys_ = getStaticTotalKeys;

  setGetValueFunc((key: string) => {
    const obj = AppStorageV2Impl.instance().getValue(key)
    if (obj === undefined) {
        return undefined;
    }
    return obj;
  });

  setRemoveValueFunc((key: string | undefined) => {
    if (key === undefined) {
        return false;
    }
    AppStorageV2Impl.instance().remove(key);
    return true;
  });

  setGetKeysFunc(() => {
    return AppStorageV2Impl.instance().getMemoryKeys();
  });
}