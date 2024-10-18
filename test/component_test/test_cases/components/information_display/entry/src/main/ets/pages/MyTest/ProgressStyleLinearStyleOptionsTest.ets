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

export default async function progressStyleLinearStyleOptionsTest() {
  /*
* Progress组件 Style属性
* 找到画面id为progressStyleLinearStyleOptions的Progress组件
* 找到画面文本为ProgressStyleCapsuleStyleOptions1,ProgressStyleCapsuleStyleOptions2,ProgressStyleCapsuleStyleOptions3组件
* 获取progress的Style.LinearStyleOptions属性与期待值{strokeWidth: 5,strokeRadius: '3px', enableScanEffect: true,enableSmoothEffect: true}比对
* 点击button1，变更progress的Style.LinearStyleOptions属性值为{ strokeWidth: '4px', strokeRadius: '2vp', enableScanEffect: false, enableSmoothEffect: false }
* 获取progress的Style.LinearStyleOptions属性与期待值{ strokeWidth: '4px', strokeRadius: '2vp', enableScanEffect: false, enableSmoothEffect: false }比对
* 点击button2，变更progress的Style.LinearStyleOptions属性值为{strokeWidth:$r("app.integer.stroke_width_length"),strokeRadius:'2lpx',enableScanEffect:true,enableSmoothEffect: true }
* 获取progress的Style.LinearStyleOptions属性与期待值{ strokeWidth:$r("app.integer.stroke_width_length"),strokeRadius:'2lpx',enableScanEffect: true, enableSmoothEffect: true }比对
* 点击button3，变更progress的Style.LinearStyleOptions属性值为{ strokeWidth: 6, strokeRadius: $r("app.integer.scale_radius"), enableScanEffect: true, enableSmoothEffect: true }
* 获取progress的Style.LinearStyleOptions属性与期待值{ strokeWidth: 6, strokeRadius: $r("app.integer.scale_radius"), enableScanEffect: true, enableSmoothEffect: true }比对
*/
  defineTest('progressStyleLinearStyleOptionsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressStyleLinearStyleOptionsTestDemo running")
    let driver: Tester = Tester.create()
    let progress: Component =
      await driver.findComponent(Matcher.create().id('progressStyleLinearStyleOptions').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleLinearStyleOptions1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleLinearStyleOptions2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleLinearStyleOptions3').enabled(true))

    let styleLinearStyleOptions1: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleLinearStyleOptions1)
      .$attrs
      .strokeWidth, '5.00vp')
    assertFalse(JSON.parse(styleLinearStyleOptions1)
      .$attrs
      .style
      .strokeRadius == undefined)
    assertEqual(JSON.parse(styleLinearStyleOptions1)
      .$attrs
      .strokeRadius, '3px')
    assertTrue(JSON.parse(styleLinearStyleOptions1)
      .$attrs
      .enableScanEffect)
    assertTrue(JSON.parse(styleLinearStyleOptions1)
      .$attrs
      .enableSmoothEffect)
    await button1.tap()
    let styleLinearStyleOptions2: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleLinearStyleOptions2)
      .$attrs
      .strokeWidth, '4px')
    assertEqual(JSON.parse(styleLinearStyleOptions2)
      .$attrs
      .strokeRadius, '2vp')
    assertFalse(JSON.parse(styleLinearStyleOptions2)
      .$attrs
      .enableScanEffect)
    assertFalse(JSON.parse(styleLinearStyleOptions2)
      .$attrs
      .enableSmoothEffect)
    await button2.tap()
    let styleLinearStyleOptions3: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleLinearStyleOptions3)
      .$attrs
      .strokeWidth, $r("app.string.stroke_width_length"))
    assertEqual(JSON.parse(styleLinearStyleOptions3)
      .$attrs
      .strokeRadius, '2lpx')
    assertTrue(JSON.parse(styleLinearStyleOptions3)
      .$attrs
      .enableScanEffect)
    assertTrue(JSON.parse(styleLinearStyleOptions3)
      .$attrs
      .enableSmoothEffect)
    await button3.tap()
    let styleLinearStyleOptions4: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleLinearStyleOptions4)
      .$attrs
      .strokeWidth, '6.00vp')
    assertEqual(JSON.parse(styleLinearStyleOptions4)
      .$attrs
      .strokeRadius, $r("app.string.scale_radius"))
    assertTrue(JSON.parse(styleLinearStyleOptions4)
      .$attrs
      .enableScanEffect)
    assertTrue(JSON.parse(styleLinearStyleOptions4)
      .$attrs
      .enableSmoothEffect)
  }, 0)
}