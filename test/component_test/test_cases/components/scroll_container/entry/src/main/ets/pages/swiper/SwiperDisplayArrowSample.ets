/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
// 测试代码路径
import swiperDisplayArrowTest from '../MyTest/SwiperDisplayArrowTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperDisplayArrowSample {
  @State displayArrow1: number | string = '60px'
  @State displayArrow2: number | string = '70px'
  @State displayArrowCol1: ResourceColor = '#85345616'
  @State displayArrowCol2: ResourceColor = '#858e3ed4'
  @State select: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(swiperDisplayArrowTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperDisplayArrowText1')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Pink)
        Text('swiperDisplayArrowText2')
          .width('90%')
          .height(60)
          .backgroundColor(Color.Blue)
      }.displayArrow(this.select, this.select)
      .id('swiperDisplayArrow1')

      Button("SwiperDisplayArrow1")
        .onClick(() => {
          this.select = !this.select
        })
      Swiper() {
        Text('swiperDisplayArrowText1')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Pink)
          .textAlign(TextAlign.Center)
        Text('swiperDisplayArrowText2')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Blue)
          .textAlign(TextAlign.Center)
      }.displayArrow({
        showBackground: true,
        isSidebarMiddle: true,
        backgroundSize: $r('sys.float.ohos_id_text_size_headline9'),
        backgroundColor: $r('sys.color.ohos_id_video_control_bar_background_color'),
        arrowSize: $r('sys.float.ohos_id_text_size_headline9'),
        arrowColor: $r('sys.color.ohos_id_popup_mask_color')
      }, false)
      .id('swiperDisplayArrow2')

      Swiper() {
        Text('swiperDisplayArrowText1')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Pink)
          .textAlign(TextAlign.Center)
        Text('swiperDisplayArrowText2')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Pink)
          .textAlign(TextAlign.Center)
      }.displayArrow({
        showBackground: true,
        isSidebarMiddle: true,
        backgroundSize: '20px',
        backgroundColor: Color.Black,
        arrowSize: '15px',
        arrowColor: Color.Red
      }, false)
      .id('swiperDisplayArrow3')

      Swiper() {
        Text('swiperDisplayArrowText1')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Pink)
          .textAlign(TextAlign.Center)
        Text('swiperDisplayArrowText2')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Pink)
          .textAlign(TextAlign.Center)
      }.displayArrow({
        showBackground: true,
        isSidebarMiddle: true,
        backgroundSize: '30%',
        backgroundColor: Color.Black,
        arrowSize: '30%',
        arrowColor: Color.Red
      }, false)
      .id('swiperDisplayArrow4')

      Swiper() {
        Text('swiperDisplayArrowText1')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Pink)
          .textAlign(TextAlign.Center)
        Text('swiperDisplayArrowText2')
          .width('30%')
          .height(60)
          .backgroundColor(Color.Blue)
          .textAlign(TextAlign.Center)
      }.displayArrow({
        showBackground: false,
        isSidebarMiddle: false,
        backgroundSize: this.displayArrow1,
        backgroundColor: this.displayArrowCol1,
        arrowSize: this.displayArrow2,
        arrowColor: this.displayArrowCol2
      }, false)
      .id('swiperDisplayArrow5')

      Button('SwiperDisplayArrow2')
        .onClick(() => {
          this.displayArrow1 = 24
          this.displayArrow2 = 25
          this.displayArrowCol1 = 0xffff0000
          this.displayArrowCol2 = 0xff00ff00
        })
    }
  }
}