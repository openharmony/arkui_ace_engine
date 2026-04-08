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
import { A2UIFunctionCall } from '../FunctionCall';

export type A2UIFunctionInvoker = (functionCall: A2UIFunctionCall) => A2UIValueType;

export interface A2UIResolveContext {
  surfaceId?: string;
  componentId?: string;
  dataModel?: ESObject;
  invokeFunction?: A2UIFunctionInvoker;
}

export type ResolveSource = 'literal' | 'binding' | 'function';

export interface ResolveResult<T> {
  success: boolean;
  source: ResolveSource;
  value?: T;
  errorMessage?: string;
}
