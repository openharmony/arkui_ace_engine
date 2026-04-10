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

import { A2UIValueType } from '../types/types';

export interface LocalFunctionRequest {
  surfaceId: string;
  componentId: string;
  functionName: string;
  argsJson: string;
  returnType: string;
}

export interface LocalFunctionContext {
  surfaceId: string;
  componentId: string;
  returnType: string;
}

export interface LocalFunctionResponse {
  success: boolean;
  returnType: string;
  value?: A2UIValueType;
  errorCode?: string;
  errorMessage?: string;
}

export type LocalFunctionArgs = A2UIValueType;
export type LocalFunctionResult = A2UIValueType;
export type LocalFunctionHandler = (args: LocalFunctionArgs, context: LocalFunctionContext) => LocalFunctionResult;
