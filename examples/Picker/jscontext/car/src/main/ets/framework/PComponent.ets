/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

import { NodeContent } from '@kit.ArkUI';
import { nativeDestroyPluginComponent, nativeRequirePlugins } from 'libentry.so';
import { ComponentContent, typeNode } from '@ohos.arkui.node';

export const width1 : number = 200;

function getRandom(min: number, max: number): number {
  return Math.floor(Math.random() * (max - min + 1)) + min
}

@Component
export struct LoadAll {
  private holderSlot = new NodeContent();
  aboutToAppear(): void {
    globalThis.aaa = 'I am host.'
    let holder = typeNode.createNode(this.getUIContext(), 'Column');
    holder.initialize();
    for (let i=1;i<=14;i++) {
      let obj = nativeRequirePlugins('car', 'InitBuilder'+i.toString(), this.getUIContext(), i.toString());
      console.log('jsMultiContext obj = ' + typeof obj + ', plugin name = ' + i.toString());
      holder.addComponentContent(obj as ComponentContent<[]>);
    }

    this.holderSlot.addFrameNode(holder);
    console.log('jsMultiContext globalThis.aaa = ' + globalThis.aaa);
  }

  aboutToDisappear(): void {
    for (let i=1;i<=14;i++) {
      console.log('jsMultiContext destroy plugin name = ' + i.toString());
      nativeDestroyPluginComponent(i.toString());
    }
  }
  build() {
    Column() {
      ContentSlot(this.holderSlot)
    }
  }
}

@Component
export struct LoadOne {
  private holderSlot = new NodeContent();
  aboutToAppear(): void {
    globalThis.aaa = 'I am host.'
    let holder = typeNode.createNode(this.getUIContext(), 'Column');
    holder.initialize();
    for (let i=1;i<=14;i++) {
      let obj = nativeRequirePlugins('car', 'InitBuilder' + i.toString(), this.getUIContext(), '1');
      console.log('jsMultiContext obj = ' + typeof obj + ', plugin name = 1');
      holder.addComponentContent(obj as ComponentContent<[]>);
    }

    this.holderSlot.addFrameNode(holder);
    console.log('jsMultiContext globalThis.aaa = ' + globalThis.aaa);
  }

  aboutToDisappear(): void {
    console.log('jsMultiContext destroy plugin name = 1');
    nativeDestroyPluginComponent('1');
  }
  build() {
    Column() {
      ContentSlot(this.holderSlot)
    }
  }
}

@Component
export struct MultiComponent20 {
  private holderSlot = new NodeContent();
  aboutToAppear(): void {
    globalThis.aaa = 'I am host.'
    let holder = typeNode.createNode(this.getUIContext(), 'Column');
    holder.initialize();
    for (let i=1;i<=14;i++) {
      const num = getRandom(1, 14)
      let obj = nativeRequirePlugins('car', 'InitBuilder'+num.toString(), this.getUIContext(), i.toString());
      console.log('jsMultiContext obj = ' + typeof obj + ', plugin name = ' + i.toString());
      holder.addComponentContent(obj as ComponentContent<[]>);
    }

    this.holderSlot.addFrameNode(holder);
    console.log('jsMultiContext globalThis.aaa = ' + globalThis.aaa);
  }

  aboutToDisappear(): void {
    for (let i=1;i<=14;i++) {
      console.log('jsMultiContext destroy plugin name = ' + i.toString());
      nativeDestroyPluginComponent(i.toString());
    }
  }
  build() {
    Column() {
      ContentSlot(this.holderSlot)
    }
  }
}

@Component
export struct MultiComponent50 {
  private holderSlot = new NodeContent();
  aboutToAppear(): void {
    globalThis.aaa = 'I am host.'
    let holder = typeNode.createNode(this.getUIContext(), 'Column');
    holder.initialize();
    for (let i=1;i<=50;i++) {
      const num = getRandom(1, 14)
      let obj = nativeRequirePlugins('car', 'InitBuilder'+num.toString(), this.getUIContext(), i.toString());
      console.log('jsMultiContext obj = ' + typeof obj + ', plugin name = ' + i.toString());
      holder.addComponentContent(obj as ComponentContent<[]>);
    }

    this.holderSlot.addFrameNode(holder);
    console.log('jsMultiContext globalThis.aaa = ' + globalThis.aaa);
  }

  aboutToDisappear(): void {
    for (let i=1;i<=50;i++) {
      console.log('jsMultiContext destroy plugin name = ' + i.toString());
      nativeDestroyPluginComponent(i.toString());
    }
  }
  build() {
    Column() {
      ContentSlot(this.holderSlot)
    }
  }
}

@Component
export struct MultiComponent100 {
  private holderSlot = new NodeContent();
  aboutToAppear(): void {
    globalThis.aaa = 'I am host.'
    let holder = typeNode.createNode(this.getUIContext(), 'Column');
    holder.initialize();
    for (let i=1;i<=100;i++) {
      const num = getRandom(1, 14)
      let obj = nativeRequirePlugins('car', 'InitBuilder'+num.toString(), this.getUIContext(), i.toString());
      console.log('jsMultiContext obj = ' + typeof obj + ', plugin name = ' + i.toString());
      holder.addComponentContent(obj as ComponentContent<[]>);
    }

    this.holderSlot.addFrameNode(holder);
    console.log('jsMultiContext globalThis.aaa = ' + globalThis.aaa);
  }

  aboutToDisappear(): void {
    for (let i=1;i<=100;i++) {
      console.log('jsMultiContext destroy plugin name = ' + i.toString());
      nativeDestroyPluginComponent(i.toString());
    }
  }
  build() {
    Column() {
      ContentSlot(this.holderSlot)
    }
  }
}
