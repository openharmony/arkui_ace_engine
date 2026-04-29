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

/** Mock：同时提供命名导出与 default，与真机 NAPI 多种互操作形态一致。 */

export function getContext(): object {
  return {};
}

export function pickerTest(_xComponentId: string): void {
  // No-op without native .so; use device/emulator HAP for real CAPI.
}

export function add(a: number, b: number): number {
  return a + b;
}

export default {
  getContext,
  pickerTest,
  add,
};
