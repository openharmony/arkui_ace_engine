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

export default async function progressStyleScaleRingStyleOptionsTest() {
  /*
* Progress组件 Style属性
* 找到画面id为progressStyleScaleRingStyleOptions的Progress组件
* 找到画面文本为ProgressStyleScaleRingStyleOptions1,ProgressStyleScaleRingStyleOptions2的组件
* 获取progress的Style.ScaleRingStyleOptions属性与期待值{strokeWidth: 6,scaleWidth: 3,scaleCount: 150,enableSmoothEffect: true}比对
* 点击button1，变更progress的Style.ScaleRingStyleOptions属性值为{ strokeWidth: '1px', scaleWidth: '4px', scaleCount: 150, enableSmoothEffect: false }
* 获取progress的Style.ScaleRingStyleOptions属性与期待值{ strokeWidth: '1px', scaleWidth: '4px', scaleCount: 150, enableSmoothEffect: false }比对
* 点击button2，变更progress的Style.ScaleRingStyleOptions属性值为{ strokeWidth: $r("app.integer.stroke_width_length"), scaleWidth: $r("app.integer.scale_width_length"), scaleCount: 150, enableSmoothEffect: true }
* 获取progress的Style.ScaleRingStyleOptions属性与期待值{ strokeWidth: $r("app.integer.stroke_width_length"), scaleWidth: $r("app.integer.scale_width_length"), scaleCount: 150, enableSmoothEffect: true }比对
*/
  defineTest('progressStyleScaleRingStyleOptionsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressStyleScaleRingStyleOptionsTestDemo running")
    let driver: Tester = Tester.create()
    let progress: Component =
      await driver.findComponent(Matcher.create().id('progressStyleScaleRingStyleOptions').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleScaleRingStyleOptions1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleScaleRingStyleOptions2').enabled(true))
    let styleScaleRingStyleOptions1: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleScaleRingStyleOptions1)
      .$attrs
      .strokeWidth, '6.00vp')
    assertEqual(JSON.parse(styleScaleRingStyleOptions1)
      .$attrs
      .scaleWidth, '3.00vp')
    assertEqual(JSON.parse(styleScaleRingStyleOptions1)
      .$attrs
      .scaleCount, '150.00vp')
    assertTrue(JSON.parse(styleScaleRingStyleOptions1)
      .$attrs
      .enableSmoothEffect)
    await button1.tap()
    let styleScaleRingStyleOptions2: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleScaleRingStyleOptions2)
      .$attrs
      .strokeWidth, '1px')
    assertEqual(JSON.parse(styleScaleRingStyleOptions2)
      .$attrs
      .scaleWidth, '4px')
    assertEqual(JSON.parse(styleScaleRingStyleOptions2)
      .$attrs
      .scaleCount, '150.00vp')
    assertFalse(JSON.parse(styleScaleRingStyleOptions2)
      .$attrs
      .enableSmoothEffect)
    await button2.tap()
    let styleScaleRingStyleOptions3: string = await progress.getInspectorInfo()
    assertEqual(JSON.parse(styleScaleRingStyleOptions3)
      .$attrs
      .strokeWidth, $r("app.string.stroke_width_length"))
    assertEqual(JSON.parse(styleScaleRingStyleOptions3)
      .$attrs
      .scaleWidth, $r("app.string.scale_width_length"))
    assertEqual(JSON.parse(styleScaleRingStyleOptions3)
      .$attrs
      .scaleCount, '150.00vp')
    assertTrue(JSON.parse(styleScaleRingStyleOptions3)
      .$attrs
      .enableSmoothEffect)
  }, 0)
}