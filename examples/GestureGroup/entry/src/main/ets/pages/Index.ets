/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

interface listItem {
  router?: string;
  name: string;
  description?: string;
};
let demandList: listItem[] = [
  {
    name: 'sequence Identification',
    description: 'The GestureMode corresponding to the sequential recognition of combined gestures is Sequence. The sequential recognition of combined gestures will identify gestures in the order they are registered until all gestures are successfully recognized.',
    router: 'pages/Sequence'
  },
  {
    name: 'parallel recognition',
    description: 'The GestureMode corresponding to the parallel recognition of the combined gestures is Parallel. In the parallel recognition of the combined gestures, the registered gestures will be recognized simultaneously until all gestures have been recognized.',
    router: 'pages/Parallel'
  },
  {
    name: 'Mutual exclusion identification',
    description: 'The GestureMode corresponding to the mutually exclusive recognition gesture combination is Exclusive. The registered gestures in the mutually exclusive recognition gesture combination will be recognized simultaneously.',
    router: 'pages/Exclusive'
  },
  {
    name: 'Scene Example',
    description: 'The following example implements the binding of long press and swipe gestures for the sub-component. The long press gesture and swipe gesture need to be triggered simultaneously. However, if the long press gesture fails, the built-in swipe gesture triggering function of the parent component Swiper needs to be activated.',
    router: 'pages/SceneExample'
  }
];

@Entry
@Component
struct Index {
  @State bgColor: ResourceColor = '#39b5fa';

  build() {
    Column() {
      Column() {
        List({ space: 20, initialIndex: 0 }) {
          ForEach(demandList, (listitem: listItem, index: number) => {
            ListItem() {
              Column({ space: 10 }) {
                Text(listitem.name)
                  .fontSize(20)
                  .fontColor(this.bgColor)
                  .maxLines(1)

                Text(listitem.description)
                  .width('100%')
              }
              .margin({ bottom: index >= demandList.length - 1 ? 100 : 0 })
              .padding({
                top: '3%',
                right: '10.00%',
                bottom: '5%',
                left: '10.00%'
              })
              .width('100%')
              .constraintSize({ minHeight: 100 })
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
              .onClick(() => {
                if (!!listitem.router) {
                  this.getUIContext().getRouter().pushUrl({ url: listitem.router })
                };
              })
            }
          })
        }
        .listDirection(Axis.Vertical) // 排列方向
        .scrollBar(BarState.Off)
        .friction(0.6)
        .divider({
          strokeWidth: 2,
          color: 0xFFFFFF,
          startMargin: 20,
          endMargin: 20
        }) // 每行之间的分界线
        .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
        .width('90%')
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#fff4f3f3')
      .padding({ top: 5 })
    }
  }
}
