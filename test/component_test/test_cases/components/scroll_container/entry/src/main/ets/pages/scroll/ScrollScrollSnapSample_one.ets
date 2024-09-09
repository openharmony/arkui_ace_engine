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
import scrollScrollSnapTest_one from '../MyTest/ScrollScrollSnapTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ScrollScrollSnapSample_one {
  @State scrollScrollSnapAlign: ScrollSnapAlign = ScrollSnapAlign.CENTER
  @State scrollSnapPagination: Dimension = '10%'
  scroller: Scroller = new Scroller;

  aboutToAppear(): void {
    loadComponentTestEntry(scrollScrollSnapTest_one)
  }

  build() {
    Column() {
      Row() {
        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE })
        .id('scrollScrollSnap1')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.START })
        .id('scrollScrollSnap2')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: this.scrollScrollSnapAlign })
        .id('scrollScrollSnap3')

        Button('ScrollScrollSnap_one1').onClick(() => {
          this.scrollScrollSnapAlign = ScrollSnapAlign.END
        })
      }

      Row() {
        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: '200px' })
        .id('scrollScrollSnap4')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: '200vp' })
        .id('scrollScrollSnap5')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: '200fp' })
        .id('scrollScrollSnap6')
      }

      Row() {
        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('20%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: Array(200) })
        .id('scrollScrollSnap7')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: '200lpx' })
        .id('scrollScrollSnap8')

        Scroll(this.scroller) {
          Column() {
            Text('ScrollScrollSnap_one1')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one2')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
            Text('ScrollScrollSnap_one3')
              .width('90%')
              .height(150)
              .margin({ top: 10 })
          }.width('100%')
        }
        .height('25%')
        .width('30%')
        .scrollSnap({ snapAlign: ScrollSnapAlign.NONE, snapPagination: this.scrollSnapPagination })
        .id('scrollScrollSnap9')

        Button('ScrollScrollSnap_one2').onClick(() => {
          this.scrollSnapPagination = $r('app.string.length')
        })
      }
    }
  }
}