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
