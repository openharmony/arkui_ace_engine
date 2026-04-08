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

import { common } from '@kit.AbilityKit';

import { CatalogItem } from '../core/CatalogItem';
import { BuiltinFunctionBase } from './BuiltinFunctionBase';
import { LocalFunctionHandler } from './LocalFunction';
import { openUrlFunction } from './OpenUrlFunction';

const builtinFunctions: BuiltinFunctionBase[] = [
  openUrlFunction
];

export function allA2UIBasicFunctions(): CatalogItem[] {
  return builtinFunctions.map((builtinFunction: BuiltinFunctionBase) => builtinFunction.asCatalogItem());
}

export function applyHostContextToBuiltinFunctions(hostContext: common.UIAbilityContext | undefined): void {
  for (const builtinFunction of builtinFunctions) {
    builtinFunction.setHostContext(hostContext);
  }
}

export function registerA2UIBuiltinFunctionHandlers(
  register: (name: string, handler: LocalFunctionHandler) => void
): void {
  for (const builtinFunction of builtinFunctions) {
    register(builtinFunction.asCatalogItem().name, builtinFunction.createHandler());
  }
}
