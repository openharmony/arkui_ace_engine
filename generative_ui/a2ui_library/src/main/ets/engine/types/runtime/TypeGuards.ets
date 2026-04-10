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

import { A2UIValueType } from '../types';

export class TypeGuards {
  static isRecord(value: A2UIValueType | Object | undefined | null): boolean {
    return typeof value === 'object' && value !== null && !Array.isArray(value)
  }

  static isDataBinding(value: A2UIValueType | Object | undefined | null): boolean {
    if (!TypeGuards.isRecord(value)) {
      return false
    }

    let record: ESObject = value as ESObject
    return typeof record['path'] === 'string' && typeof record['call'] !== 'string'
  }

  static isFunctionCall(value: A2UIValueType | Object | undefined | null): boolean {
    if (!TypeGuards.isRecord(value)) {
      return false
    }

    let record: ESObject = value as ESObject
    return typeof record['call'] === 'string'
  }

  static isStringArray(value: A2UIValueType | Object | undefined | null): boolean {
    if (!Array.isArray(value)) {
      return false
    }
    let arrayValue = value as Object[]
    for (let index = 0; index < arrayValue.length; index++) {
      let item = arrayValue[index]
      if (typeof item !== 'string') {
        return false
      }
    }
    return true
  }
}
