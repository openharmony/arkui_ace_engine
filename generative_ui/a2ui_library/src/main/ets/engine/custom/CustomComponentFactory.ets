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

import nativeEngine from 'libentry.so';
import { ComponentContent, NodeContent, UIContext } from '@kit.ArkUI';
import { CatalogItem } from '../core/CatalogItem';
import { PromptProvider, SchemaProvider } from '../types/types';
import {
  CustomComponentAttribute,
  CustomComponentDescriptor,
  CustomComponentResult
} from './CustomComponent';

const emptySchemaProvider: SchemaProvider = (): string => {
  return '';
};

export interface CustomComponentDefinition {
  type: string;
  builder: WrappedBuilder<[CustomComponentAttribute]>;
  schemaProvider?: SchemaProvider;
  promptProvider?: PromptProvider;
}

export class CustomComponentFactory {
  private static definitions: Map<string, CustomComponentDefinition> = new Map();
  private static bridgeRegistered: boolean = false;
  private static currentUIContext: UIContext | undefined = undefined;

  public static InstallCustomComponent(uiContext: UIContext, definitions: Array<CustomComponentDefinition>): void {
    CustomComponentFactory.currentUIContext = uiContext;
    if (!CustomComponentFactory.bridgeRegistered) {
      nativeEngine.registerCreateCustomComponent(CustomComponentFactory.createCustomComponent);
      nativeEngine.registerUpdateCustomComponent(CustomComponentFactory.updateCustomComponent);
      CustomComponentFactory.bridgeRegistered = true;
    }

    for (let def of definitions) {
      if (!def || !def.type || !def.builder) {
        console.log('InstallCustomComponent Invalid Definition');
        continue;
      }
      CustomComponentFactory.registerCustomComponent(def);
    }
  }

  public static registerCustomComponent(definition: CustomComponentDefinition): void {
    if (definition.type.length === 0) {
      return;
    }
    CustomComponentFactory.definitions.set(definition.type, definition);
  }

  public static getBuilder(type: string): WrappedBuilder<[CustomComponentAttribute]> | undefined {
    return CustomComponentFactory.definitions.get(type)?.builder;
  }

  public static createCustomComponent(value: CustomComponentDescriptor): CustomComponentResult {
    console.log("ArkTS createCustomComponent");
    if (CustomComponentFactory.currentUIContext === undefined) {
      return {};
    }

    let builder = CustomComponentFactory.getBuilder(value.type);
    if (builder === undefined) {
      return {};
    }

    let childSlot: NodeContent = new NodeContent();
    let content = new ComponentContent<CustomComponentAttribute>(CustomComponentFactory.currentUIContext, builder, {
      type: value.type,
      id: value.id,
      properties: value.properties,
      customProps: value.customProps,
      slot: childSlot,
      builder: builder
    });
    return { content: content, childSlot: childSlot };
  }

  public static updateCustomComponent(
    customComponent: ComponentContent<CustomComponentAttribute>,
    childSlot: NodeContent,
    value: CustomComponentDescriptor
  ): void {
    let builder = CustomComponentFactory.getBuilder(value.type);
    if (builder === undefined) {
      return;
    }

    customComponent.update({
      type: value.type,
      id: value.id,
      properties: value.properties,
      customProps: value.customProps,
      slot: childSlot,
      builder: builder
    });
  }

  public static createCatalogItem(type: string): CatalogItem {
    let definition = CustomComponentFactory.definitions.get(type);
    if (definition === undefined) {
      throw new Error(`Custom component is not registered: ${type}`);
    }

    let catalogItem = CatalogItem.forComponent(
      type,
      definition.schemaProvider ?? emptySchemaProvider,
      definition.builder,
      definition.promptProvider
    );
    return catalogItem.markInnerNative(false);
  }
}
