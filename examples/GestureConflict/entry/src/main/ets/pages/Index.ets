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

import router from '@ohos.router';

interface listItem {
  router?: string;
  name: string;
  description?: string;
};
let demandList: listItem[] = [
  {
    name: 'Custom gesture recognition',
    description: 'The application can independently decide whether to intercept this gesture, causing the gesture recognition to fail, thereby leaving the chance of successful recognition to other gestures.',
    router: 'Component/CustomGestures/CustomGestureDetermination'
  },
  {
    name: 'Gesture and motion control',
    description: 'Gesture and motion control refers to the situation where the gesture has been successfully recognized, but the developer can still control whether the gesture callback can respond by calling the API interface.',
    router: 'Component/GestureAndMotionControl/GestureAndMotionControl'
  },
  {
    name: 'Preventing gesture participation in recognition',
    description: 'When the user presses, by controlling the participation status of the gesture recognizer in the response chain, efficient dynamic intervention of gesture processing is achieved.',
    router: 'Component/PreventGestureRecognition/PreventGestureRecognition'
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
