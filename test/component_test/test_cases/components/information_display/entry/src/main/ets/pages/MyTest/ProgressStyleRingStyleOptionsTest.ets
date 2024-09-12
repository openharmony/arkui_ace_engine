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
import {
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function progressStyleRingStyleOptionsTest() {
  /*
* Progress组件 Style属性
* 找到画面id为progressStyleRingStyleOptions的Progress组件
* 找到画面文本为ProgressStyleRingStyleOptions1,ProgressStyleRingStyleOptions2的组件
* 获取progress的Style.RingStyleOptions属性与期待值{strokeWidth: 5,shadow: true, status: ProgressStatus.LOADING, enableScanEffect: true,enableSmoothEffect: true}比对
* 点击button1，变更progress的Style.RingStyleOptions属性值为{ strokeWidth: '20px', shadow: false, status: ProgressStatus.PROGRESSING, enableScanEffect: false, enableSmoothEffect: false}
* 获取progress的Style.RingStyleOptions属性与期待值{ strokeWidth: '20px', shadow: false, status: ProgressStatus.PROGRESSING, enableScanEffect: false, enableSmoothEffect: false}比对
* 点击button2，变更progress的Style.RingStyleOptions属性值为{ strokeWidth: $r("app.integer.stroke_width_length"),shadow: true,status: ProgressStatus.PROGRESSING,enableScanEffect: true,enableSmoothEffect: true}
* 获取progress的Style.RingStyleOptions属性与期待值{ strokeWidth: $r("app.integer.stroke_width_length"),shadow: true,status: ProgressStatus.PROGRESSING,enableScanEffect: true,enableSmoothEffect: true}比对
*/
  defineTest('progressStyleRingStyleOptionsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressStyleRingStyleOptionsTestDemo running")
    let driver: Tester = Tester.create()
    let progress: Component =
      await driver.findComponent(Matcher.create().id('progressStyleRingStyleOptions').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleRingStyleOptions1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleRingStyleOptions2').enabled(true))

    let styleRingStyleOptions1: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleRingStyleOptions1)
      .$attrs
      .strokeWidth, '5.00vp')
    assertFalse(JSON.parse(styleRingStyleOptions1)
      .$attrs
      .style
      .shadow == undefined)
    assertTrue(JSON.parse(styleRingStyleOptions1)
      .$attrs
      .shadow)
    assertEqual(JSON.parse(styleRingStyleOptions1)
      .$attrs
      .status, ProgressStatus.LOADING)
    assertTrue(JSON.parse(styleRingStyleOptions1)
      .$attrs
      .enableScanEffect)
    assertTrue(JSON.parse(styleRingStyleOptions1)
      .$attrs
      .enableSmoothEffect)
    await button1.tap()
    let styleRingStyleOptions2: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleRingStyleOptions2)
      .$attrs
      .strokeWidth, '20px')
    assertFalse(JSON.parse(styleRingStyleOptions2)
      .$attrs
      .shadow)
    assertEqual(JSON.parse(styleRingStyleOptions2)
      .$attrs
      .status, ProgressStatus.PROGRESSING)
    assertFalse(JSON.parse(styleRingStyleOptions2)
      .$attrs
      .enableScanEffect)
    assertFalse(JSON.parse(styleRingStyleOptions2)
      .$attrs
      .enableSmoothEffect)
    await button2.tap()
    let styleRingStyleOptions3: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleRingStyleOptions3)
      .$attrs
      .strokeWidth, $r("app.string.stroke_width_length"))
    assertTrue(JSON.parse(styleRingStyleOptions3)
      .$attrs
      .shadow)
    assertEqual(JSON.parse(styleRingStyleOptions3)
      .$attrs
      .status, ProgressStatus.PROGRESSING)
    assertTrue(JSON.parse(styleRingStyleOptions3)
      .$attrs
      .enableScanEffect)
    assertTrue(JSON.parse(styleRingStyleOptions3)
      .$attrs
      .enableSmoothEffect)
  }, 0)
}