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
import swiperCurveTest from '../MyTest/SwiperCurveTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import Curves from '@ohos.curves'

let curveValue = Curves.initCurve(Curve.EaseIn)
let value: number = curveValue.interpolate(0.5)

@Entry
@Component
struct SwiperCurveSample {
  @State curve1: Curve = Curve.Sharp
  @State curve2: Curve = Curve.Smooth
  @State curveNum: number = -1

  aboutToAppear(): void {
    loadComponentTestEntry(swiperCurveTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(Curve.Linear)
      .id('swiperCurve1')

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .id('swiperCurve2')
      .curve(Curve.Ease)

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(Curve.EaseIn)
      .id('swiperCurve3')

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(Curve.EaseOut)
      .id('swiperCurve4')

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(Curve.EaseInOut)
      .id('swiperCurve5')

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .id('swiperCurve6')
      .curve(Curve.FastOutSlowIn)

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .id('swiperCurve7')
      .curve(Curve.LinearOutSlowIn)

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(Curve.FastOutLinearIn)
      .id('swiperCurve8')

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(Curve.ExtremeDeceleration)
      .id('swiperCurve9')

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(this.curve1)
      .id('swiperCurve10')

      Button('SwiperCurve1')
        .onClick(() => {
          this.curve1 = Curve.Rhythm
        })
      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(this.curve2)
      .id('swiperCurve11')

      Button('SwiperCurve2')
        .onClick(() => {
          this.curve2 = Curve.Friction
        })
      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(value)
      .id('swiperCurve12')

      Swiper() {
        Text('swiperCurveText1')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText2')
          .width('90%')
          .textAlign(TextAlign.Center)
        Text('swiperCurveText3')
          .width('90%')
          .textAlign(TextAlign.Center)
      }.autoPlay(true)
      .curve(this.curveNum)
      .id('swiperCurve13')

      Button('SwiperCurve3')
        .onClick(() => {
          this.curveNum = 2
        })
    }
  }
}