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

import * as LibEntryModule from 'libentry.so';

type LibEntryPickerFn = (xComponentId: string) => void;

interface LibEntryDefaultExport {
  pickerTest?: LibEntryPickerFn;
}

interface LibEntryShape {
  pickerTest?: LibEntryPickerFn;
  default?: LibEntryDefaultExport;
}

/** 解析 NAPI 导出的 pickerTest；兼容命名空间成员与 default.exports。 */
export function resolveLibEntryPickerTest(): LibEntryPickerFn | undefined {
  const m = LibEntryModule as LibEntryShape;
  if (typeof m.pickerTest === 'function') {
    return m.pickerTest;
  }
  if (m.default !== undefined && typeof m.default.pickerTest === 'function') {
    return m.default.pickerTest;
  }
  return undefined;
}
