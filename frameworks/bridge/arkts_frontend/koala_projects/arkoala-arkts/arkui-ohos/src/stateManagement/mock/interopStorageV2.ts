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

import { AppStorageV2Impl } from '../storage/appStorageV2';
import { StorageDefaultCreator } from '../storage/persistenceV2'

export class InteropAppStorageV2 {
  private static instance_: InteropAppStorageV2 | undefined = undefined;

  public static instance(): InteropAppStorageV2 {
      if (InteropAppStorageV2.instance_) {
          return InteropAppStorageV2.instance_!;
      }
      InteropAppStorageV2.instance_ = new InteropAppStorageV2();
      return InteropAppStorageV2.instance_!;
  }

  public connect<T extends object>(
      ttype: Type,
      key: string,
      defaultCreator?: StorageDefaultCreator<T>
  ): T | undefined {
      return AppStorageV2Impl.instance().connect<T>(ttype, key, defaultCreator);
  }

  public connect<T extends object>(ttype: Type, defaultCreator?: StorageDefaultCreator<T>): T | undefined {
      return AppStorageV2Impl.instance().connect<T>(ttype, defaultCreator);
  }

  public remove(keyOrType: string | Type): void {
    AppStorageV2Impl.instance().remove(keyOrType);
  }

  public keys(): Array<string> {
      return AppStorageV2Impl.instance().keys();
  }
}
