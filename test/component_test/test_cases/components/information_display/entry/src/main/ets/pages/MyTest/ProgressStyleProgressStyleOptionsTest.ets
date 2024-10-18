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

export default async function progressStyleProgressStyleOptionsTest() {
  /*
* Progress组件 Style属性
* 找到画面id为progressStyleProgressStyleOptions的Progress组件
* 找到画面文本为ProgressStyleProgressStyleOptions1,ProgressStyleProgressStyleOptions2的组件
* 获取progress的Style.ProgressStyleOptions属性与期待值{strokeWidth:10,scaleCount:15,scaleWidth:20,enableSmoothEffect:true}比对
* 点击button1，变更progress的Style.ProgressStyleOptions属性值为{ strokeWidth: '10px', scaleCount: 10, scaleWidth: '10px', enableSmoothEffect: false }
* 获取progress的Style.ProgressStyleOptions属性与期待值{ strokeWidth: '10px', scaleCount: 10, scaleWidth: '10px', enableSmoothEffect: false }比对
* 点击button2，变更progress的Style.ProgressStyleOptions属性值为{ strokeWidth: $r("app.integer.stroke_width_length"), scaleCount: 10, scaleWidth: $r("app.integer.scale_width_length"), enableSmoothEffect: false }
* 获取progress的Style.ProgressStyleOptions属性与期待值{ strokeWidth: $r("app.integer.stroke_width_length"),scaleCount: 10, scaleWidth: $r("app.integer.scale_width_length"), enableSmoothEffect: false }比对
*/
  defineTest('progressStyleProgressStyleOptionsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressStyleProgressStyleOptionsTestDemo running")
    let driver: Tester = Tester.create()
    let progress: Component =
      await driver.findComponent(Matcher.create().id('progressStyleProgressStyleOptions').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleProgressStyleOptions1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleProgressStyleOptions2').enabled(true))
    let styleProgressStyleOptions1: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleProgressStyleOptions1)
      .$attrs
      .strokeWidth, '10.00vp')
    assertEqual(JSON.parse(styleProgressStyleOptions1)
      .$attrs
      .scaleCount, '15.00vp')
    assertEqual(JSON.parse(styleProgressStyleOptions1)
      .$attrs
      .scaleWidth, '20.00vp')
    assertTrue(JSON.parse(styleProgressStyleOptions1)
      .$attrs
      .enableSmoothEffect)
    await button1.tap()
    let styleProgressStyleOptions2: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleProgressStyleOptions2)
      .$attrs
      .strokeWidth, '10px')
    assertEqual(JSON.parse(styleProgressStyleOptions2)
      .$attrs
      .scaleCount, '10.00vp')
    assertEqual(JSON.parse(styleProgressStyleOptions2)
      .$attrs
      .scaleWidth, '10px')
    assertFalse(JSON.parse(styleProgressStyleOptions2)
      .$attrs
      .enableSmoothEffect)
    await button2.tap()
    let styleProgressStyleOptions3: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleProgressStyleOptions3)
      .$attrs
      .strokeWidth, $r("app.string.stroke_width_length"))
    assertEqual(JSON.parse(styleProgressStyleOptions3)
      .$attrs
      .strokeRadius, '5.00vp')
    assertEqual(JSON.parse(styleProgressStyleOptions3)
      .$attrs
      .scaleWidth, $r("app.string.scale_width_length"))
    assertFalse(JSON.parse(styleProgressStyleOptions3)
      .$attrs
      .enableSmoothEffect)
  }, 0)
}