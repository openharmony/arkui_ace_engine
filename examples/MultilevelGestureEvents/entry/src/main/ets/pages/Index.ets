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
    name: 'TouchEvent',
    description: 'Touch events (onTouch events) form the basis of all gestures and consist of four types: Down, Move, Up, and Cancel.',
    router: 'pages/TouchEvent',
  },
  {
    name: 'GesturesEvents',
    description: 'All gestures and events except for touch events (onTouch events) are implemented through basic gestures or combined gestures. For instance, the drag event is a sequential gesture composed of a long press gesture and a sliding gesture.',
    router: 'pages/GesturesEvents',
  },
  {
    name: 'CustomEvent',
    description: 'By setting the properties, the default multi-level gesture event competition process can be controlled, thereby achieving better gesture event handling.',
    router: 'pages/CustomEvent',
  },
  {
    name: 'OverlayManager',
    description: 'The OverlayManager event mechanism is by default handled first by the components within the WrappedBuilder, and it will not be passed down further.',
    router: 'pages/OverlayManager',
  },
];
@Entry
@Component
struct Home {
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