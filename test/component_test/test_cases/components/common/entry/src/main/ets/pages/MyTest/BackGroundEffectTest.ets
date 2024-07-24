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
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function backGroundEffectTest() {
  /*
  * gauge组件 backgroundEffect属性
  * 找到画面id为gaugeBackgroundEffect1的gauge组件
  * 找到画面文本为ButtonBackGroundEffect1的Button组件
  * 获取gaugeBackgroundEffect1的backgroundEffect属性的radius参数与期待值100比对
  * 获取gaugeBackgroundEffect1的backgroundEffect属性的saturation参数与期待值50比对
  * 获取gaugeBackgroundEffect1的backgroundEffect属性的brightness参数与期待值50比对
  * 获取gaugeBackgroundEffect1的backgroundEffect属性的color参数与期待值0xa52a3a比对
  * 获取gaugeBackgroundEffect1的backgroundEffect属性的adaptiveColor参数与期待值AdaptiveColor.DEFAULT比对
  * 获取gaugeBackgroundEffect1的backgroundEffect属性的blurOptions的grayscale[0]参数与期待值0比对
  * 获取gaugeBackgroundEffect1的backgroundEffect属性的blurOptions的grayscale[1]参数与期待值50比对
  * 点击button1，变更gaugeBackgroundEffect1的backgroundEffect的属性中options的color参数的值与期望值Color.Blue比对
  * 获取gaugeBackgroundEffect1的backgroundEffect的属性中options的adaptiveColor参数的值与期望值AdaptiveColor.Average比对
  */
  defineTest('backGroundEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("backGroundEffectTestDemo running")
    let driver: Tester = Tester.create()
    let gaugeBackgroundEffect1: Component =
      await driver.findComponent(Matcher.create().id('gaugeBackgroundEffect1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBackGroundEffect1').enabled(true))
    let backgroundEffect1: string = await gaugeBackgroundEffect1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundEffect1)
      .$attrs
      .backgroundEffect
      .options
      .radius, 100)
    let backgroundEffect2: string = await gaugeBackgroundEffect1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundEffect2)
      .$attrs
      .backgroundEffect
      .options
      .saturation, 50)
    let backgroundEffect3: string = await gaugeBackgroundEffect1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundEffect3)
      .$attrs
      .backgroundEffect
      .options
      .brightness, 50)
    let backgroundEffect4: string = await gaugeBackgroundEffect1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundEffect4)
      .$attrs
      .backgroundEffect
      .options
      .color, '#FFA52A3A')
    let backgroundEffect5: string = await gaugeBackgroundEffect1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundEffect5)
      .$attrs
      .backgroundEffect
      .options
      .adaptiveColor, 'AdaptiveColor.Default')
    let backgroundEffect6: string = await gaugeBackgroundEffect1.getInspectorInfo()
    assertFalse(JSON.parse(backgroundEffect6)
      .$attrs
      .backgroundEffect
      .options
      .blurOptions == undefined)
    assertEqual(JSON.parse(backgroundEffect6)
      .$attrs
      .backgroundEffect
      .options
      .blurOptions
      .grayscale[0], 0)
    assertEqual(JSON.parse(backgroundEffect6)
      .$attrs
      .backgroundEffect
      .options
      .blurOptions
      .grayscale[1], 50)

    await button1.tap()
    let backgroundEffect10: string = await gaugeBackgroundEffect1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundEffect10)
      .$attrs
      .backgroundEffect
      .options
      .color
      .toLowerCase(), Color.Blue)
    let backgroundEffect11: string = await gaugeBackgroundEffect1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundEffect11)
      .$attrs
      .backgroundEffect
      .options
      .adaptiveColor, 'AdaptiveColor.Average')
  }, 0)
}