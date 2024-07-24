/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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
import scrollScrollSnapTest_two from '../MyTest/ScrollScrollSnapTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ScrollScrollSnapSample_two {
  @State scrollEnableSnapToEnd: boolean = true
  scroller: Scroller = new Scroller;

  aboutToAppear(): void {
    loadComponentTestEntry(scrollScrollSnapTest_two)
  }

  build() {
    Column() {
      Row() {
        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_two1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('20%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: Array(10, 20, 30), enableSnapToStart: true })
        .id('scrollScrollSnap1')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_two1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('20%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: Array(10, 20, 30), enableSnapToStart: false })
        .id('scrollScrollSnap2')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_two1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('20%')
        .scrollSnap({
          snapAlign: ScrollSnapAlign.NONE,
          snapPagination: Array(10, 20, 30),
          enableSnapToEnd: this.scrollEnableSnapToEnd
        })
        .id('scrollScrollSnap3')

        Button('ScrollScrollSnap_two').onClick(() => {
          this.scrollEnableSnapToEnd = !this.scrollEnableSnapToEnd
        })
      }

      Row() {
        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_two1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.START, snapPagination: 500 })
        .id('scrollScrollSnap4')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_two1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.START, snapPagination: 0 })
        .id('scrollScrollSnap5')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_two1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.START, snapPagination: Array(100, 200, 300, 400, 500) })
        .id('scrollScrollSnap6')
      }

      Row() {
        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_two1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: '200vp', enableSnapToStart: true })
        .id('scrollScrollSnap7')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_two1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_two3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: '200vp', enableSnapToEnd: true })
        .id('scrollScrollSnap8')
      }
    }
  }
}