/*

Copyright (c) 2025 Huawei Device Co., Ltd.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
import nativeNode from 'libnativeNode.so';
import { NodeContent } from '@kit.ArkUI';

@Builder
function title() {
  Column() {
    Text('输入事件C-API功能示例')
      .fontSize(24)
      .fontWeight(FontWeight.Bold)
      .margin({ top: 15, bottom: 15 })
      .fontColor(Color.White)
      .textAlign(TextAlign.Center)
      .width('100%')
  }
  .width('100%')
  .backgroundColor('#0000FF')
  .linearGradient({
    angle: 90,
    colors: [
      [0x0000FF, 0.0],
      [0x4169E1, 1.0]
    ]
  })
}

@Component
struct NativeDragDropExample {
  // 初始化NodeContent对象
  private rootSlot: NodeContent = new NodeContent();

  build() {
    Column() {
      // 将NodeContent和ContentSlot占位组件绑定
      ContentSlot(this.rootSlot)
    }
    .height(700)
    .onAppear(() => {
      // 传递NodeContent对象用于Native创建组件的挂载显示
      nativeNode.createNativeNode(this.rootSlot);
    })
    .backgroundColor('#ffeff5f5')
  }
}

@Entry
@Component
struct Index {

  build() {
    Column() {
      title()
      Scroll() {
        Column() {
          NativeDragDropExample()
        }
        .alignItems(HorizontalAlign.Start)
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')

  }

}
