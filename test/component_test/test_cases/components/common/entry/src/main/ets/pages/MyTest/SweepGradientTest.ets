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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function sweepGradientTest() {
  /*
   * sweepGradient 通用属性
   * 找到画面id为 columnSweepGradient1 的组件
   * 找到画面文本为 ButtonSweepGradient1  ButtonSweepGradient2  ButtonSweepGradient3 按钮
   * 获取sweepGradient的属性与期望值比对
   * 点击button1变更Column1的属性
   * 获取sweepGradient的属性与期望值比对
   * 点击button2变更Column1的属性
   * 获取sweepGradient的属性与期望值比对
   * 点击button3变更Column1的属性
   * 获取sweepGradient的属性与期望值比对
   */
  defineTest('sweepGradientTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sweepGradientTestDemo running')
    let driver: Tester = Tester.create()
    let columnSweepGradient1: Component =
      await driver.findComponent(Matcher.create().id('columnSweepGradient1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonSweepGradient1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonSweepGradient2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonSweepGradient3').enabled(true))
    let enabled1: string = await columnSweepGradient1.getInspectorInfo()
    assertEqual(JSON.parse(enabled1)
      .$attrs
      .sweepGradient
      .center[0], '50.00vp')
    assertEqual(JSON.parse(enabled1)
      .$attrs
      .sweepGradient
      .center[1], '50.00vp')
    assertEqual(JSON.parse(enabled1)
      .$attrs
      .sweepGradient
      .start, '6.00px')
    assertEqual(JSON.parse(enabled1)
      .$attrs
      .sweepGradient
      .end, '6.00px')
    assertEqual(JSON.parse(enabled1)
      .$attrs
      .sweepGradient
      .rotation, '6.00vp')
    assertEqual(JSON.parse(enabled1)
      .$attrs
      .sweepGradient
      .colors, '#FFFF0124,0.000000,#FFFF0124,0.300000,#FFFF0124,1.000000')
    assertTrue(JSON.parse(enabled1)
      .$attrs
      .sweepGradient
      .repeating)
    await button1.tap()
    let enabled2: string = await columnSweepGradient1.getInspectorInfo()
    assertEqual(JSON.parse(enabled2)
      .$attrs
      .sweepGradient
      .colors, [['rgba(8, 0, 255, 1.00)', 0.0], ['rgba(122, 119, 119, 1.00)', 0.3], ['rgba(255, 0, 0, 1.00)', 1.0]])
    assertFalse(JSON.parse(enabled2)
      .$attrs
      .sweepGradient
      .repeating)
    await button2.tap()
    let enabled3: string = await columnSweepGradient1.getInspectorInfo()
    assertEqual(JSON.parse(enabled3)
      .$attrs
      .sweepGradient
      .start, '6')
    assertEqual(JSON.parse(enabled3)
      .$attrs
      .sweepGradient
      .end, '6')
    assertEqual(JSON.parse(enabled3)
      .$attrs
      .sweepGradient
      .rotation, '6')
    assertEqual(JSON.parse(enabled3)
      .$attrs
      .sweepGradient
      .colors, [[0xffaaaa, 0.0], [0xaaaaff, 0.3], [0xf1111f, 1.0]])
    assertTrue(JSON.parse(enabled3)
      .$attrs
      .sweepGradient
      .repeating)
    await button3.tap()
    let enabled4: string = await columnSweepGradient1.getInspectorInfo()
    assertEqual(JSON.parse(enabled4)
      .$attrs
      .sweepGradient
      .start, -6)
    assertEqual(JSON.parse(enabled4)
      .$attrs
      .sweepGradient
      .end, -6)
    assertEqual(JSON.parse(enabled4)
      .$attrs
      .sweepGradient
      .rotation, -6)
    assertEqual(JSON.parse(enabled4)
      .$attrs
      .sweepGradient
      .colors, [[Color.Blue, 0.0], [Color.Green, 0.3], [Color.Pink, 1.0]])
    assertTrue(JSON.parse(enabled4)
      .$attrs
      .sweepGradient
      .repeating)
  }, 0)
}