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

import { CustomComponentAttribute } from "../custom/CustomComponent";

/**
 * 能力类型
 */
export enum CapabilityType {
  // 协议消息格式
  PROTOCOL_MESSAGE = 0,
  // 组件
  COMPONENT = 1,
  // 函数调用
  LOCAL_FUNCTION = 2,
  // 数据类型
  DATA_TYPE = 3
}

// 提供对应能力的 schema json 定义
export declare type SchemaProvider = () => string;

// 在 PromptProvideResult 中使用
export enum SchemaPromptCombineMode {
  REPLACE = 0, // 使用自定义 customPrompt 替换 schema
  COMBINE = 1  // 使用 schema + customPrompt
}

export interface PromptProvideResult {
  mode: SchemaPromptCombineMode;
  prompt: string;
}
// 提供对应能力的 prompt，通过 mode 可以替换掉整个 schema
export declare type PromptProvider = () => PromptProvideResult;

// 定义可能的值类型 - 使用联合类型而不是Object
export type A2UIValueType =
    | string
    | number
    | boolean
    | null
    | undefined
    | A2UIValueType[]
    | Record<string, Object>

export interface ComponentBuilderParam {
  surfaceId?: string;
  properties: Record<string, A2UIValueType>;
}

export type NativeBuilder = "native";

// 定义组件构建器类型 - 接收属性对象和上下文参数
// 只有 native 组件才允许 undefined
export type ComponentBuilder = WrappedBuilder<[CustomComponentAttribute]> | undefined;

// 定义 local function 执行器类型
export type FunctionCall = (params: A2UIValueType) => A2UIValueType;
