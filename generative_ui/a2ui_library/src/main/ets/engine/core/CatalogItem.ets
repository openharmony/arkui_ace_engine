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

import { SchemaProvider, PromptProvider, ComponentBuilder, FunctionCall } from './../types/types'

export enum CatalogCategory {
  // all basic components defined by A2UI protocol
  A2UI_STANDARD = 0,
  // the components implements for ohos, they extend the styles
  OHOS_EXTENDS = 1
}

/**
 * catalog item 能力类型
 */
export enum CatalogItemType {
  // 协议消息格式
  PROTOCOL_MESSAGE = 0,
  // 组件
  COMPONENT = 1,
  // 函数调用
  LOCAL_FUNCTION = 2
}

/**
 * 通过这个类来定义所圈定的能力
 */
export class CatalogItem {
  // 默认使用 A2UI 标准组件
  category: CatalogCategory = CatalogCategory.OHOS_EXTENDS;
  // 必选
  type: CatalogItemType;
  // 必选
  name: string;
  // 必选，是否为 native 侧 inner 实现，仅支持框架预置实现，默认为 ets 侧实现
  isInnerNative: boolean = false;
  // 必选
  schemaProvider: SchemaProvider;
  // 可选，注册组件时提供，function 不提供
  componentBuilder?: ComponentBuilder;
  // 可选，注册方法时必须提供，组件注册时不提供
  functionCall?: FunctionCall;
  // 可选，优先使用这个函数来获取对应的提示词
  promptProvider?: PromptProvider;

  private constructor(name: string, type: CatalogItemType, schemaProvider: SchemaProvider) {
    this.name = name;
    this.type = type;
    this.schemaProvider = schemaProvider;
  }

  public markCategory(category: CatalogCategory): CatalogItem {
    this.category = category;
    return this;
  }

  public markInnerNative(isNative: boolean): CatalogItem {
    this.isInnerNative = isNative;
    return this;
  }

  // 构造协议消息
  public static forProtocolMessage(name: string, schemaProvider: SchemaProvider,
    promptProvider?: PromptProvider): CatalogItem {
    let catalogItem: CatalogItem = new CatalogItem(name, CatalogItemType.PROTOCOL_MESSAGE, schemaProvider);
    if (promptProvider) {
      catalogItem.setExtraPromptProvider(promptProvider);
    }
    return catalogItem;
  }

  // 构造组件 catalog item
  public static forComponent(name: string, schemaProvider: SchemaProvider,
    componentBuilder: ComponentBuilder, promptProvider?: PromptProvider): CatalogItem {
    let catalogItem: CatalogItem = new CatalogItem(name, CatalogItemType.COMPONENT, schemaProvider);
    catalogItem.setComponentBuilder(componentBuilder);
    if (promptProvider) {
      catalogItem.setExtraPromptProvider(promptProvider);
    }
    return catalogItem;
  }

  // 构造 function catalog item
  public static forFunction(name: string, schemaProvider: SchemaProvider, functionCall: FunctionCall,
    promptProvider?: PromptProvider): CatalogItem {
    let catalogItem: CatalogItem = new CatalogItem(name, CatalogItemType.LOCAL_FUNCTION, schemaProvider);
    if (promptProvider) {
      catalogItem.setExtraPromptProvider(promptProvider);
    }
    catalogItem.setFunctionCall(functionCall)
    return catalogItem;
  }

  private setComponentBuilder(componentBuilder: ComponentBuilder): void {
    this.componentBuilder = componentBuilder;
  }

  private setExtraPromptProvider(promptProvider: PromptProvider): void {
    this.promptProvider = promptProvider;
  }

  private setFunctionCall(functionCall: FunctionCall): void {
    this.functionCall = functionCall;
  }
}
