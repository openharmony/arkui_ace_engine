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

@Builder
function title() {
  Column() {
    Text('拖拽CAPI功能示例')
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
  build() {
    Column() {
      XComponent({
        id: 'dragAndDrop',
        type: XComponentType.NODE,
        libraryname: 'nativeNode'
      })
        .height(1450)
        .onAppear(() => {
          nativeNode.createNativeNode('dragAndDrop', this.getUIContext());
        })
    }
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
        Column({space: 10}) {
          NativeDragDropExample()
        }
        .alignItems(HorizontalAlign.Start)
      }
      .id('scroll')
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')

  }

}