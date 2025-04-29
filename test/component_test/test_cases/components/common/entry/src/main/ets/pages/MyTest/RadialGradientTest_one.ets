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

export default async function radialGradientTest_one() {
  /*
   * Column组件 radialGradient 通用属性
   * 找到画面id为 columnRadialGradient1的组件
   * 找到画面文本为 ButtonRadialGradient1按钮
   * 获取 columnRadialGradient1 的radialGradient属性center[0]与期望值50.00vp比对
   * 获取 columnRadialGradient1 的radialGradient属性center[1]与期望值50.00vp比对
   * 获取 columnRadialGradient1 的radialGradient属性radius与期望值-15.00vp比对
   * 获取 columnRadialGradient1 的radialGradient属性colors[0][0]与期望值$r("app.string.common_color")比对
   * 获取 columnRadialGradient1 的radialGradient属性colors[0][1]与期望值0.000000比对
   * 获取 columnRadialGradient1 的radialGradient属性colors[1][0]与期望值 $r("app.string.common_color")比对
   * 获取 columnRadialGradient1 的radialGradient属性colors[1][1]与期望值0.300000比对
   * 获取 columnRadialGradient1 的radialGradient属性colors[2][0]与期望值$r("app.string.common_color")比对
   * 获取 columnRadialGradient1 的radialGradient属性colors[2][1]与期望值1.000000比对
   * 获取 columnRadialGradient1 的radialGradient属性repeating与期望值true比对
   * 点击 button1 变更 columnRadialGradient1 的属性
   * 获取 columnRadialGradient2 的radialGradient属性radius与期望值60.00vp比对
   * 获取 columnRadialGradient2 的radialGradient属性colors[0][0]与期望值#FFFFAAAA比对
   * 获取 columnRadialGradient2 的radialGradient属性colors[0][1]与期望值0.000000比对
   * 获取 columnRadialGradient2 的radialGradient属性colors[1][0]与期望值Color.Green比对
   * 获取 columnRadialGradient2 的radialGradient属性colors[1][1]与期望值0.300000比对
   * 获取 columnRadialGradient2 的radialGradient属性colors[2][0]与期望值 Color.Pink比对
   * 获取 columnRadialGradient2 的radialGradient属性colors[2][1]与期望值1.000000比对
   * 获取 columnRadialGradient2 的radialGradient属性repeating与期望值true比对
   * */
  defineTest('radialGradientSample_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('radialGradientSample_oneDemo running')
    let driver: Tester = Tester.create()
    let columnRadialGradient1: Component =
      await driver.findComponent(Matcher.create().id('columnRadialGradient1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonRadialGradient1').enabled(true))
    let radialGradient1: string = await columnRadialGradient1.getInspectorInfo()
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .center[0], '50.00vp')
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .center[1], '50.00vp')
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .radius, '-15.00vp')
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[0][0], $r("app.string.common_color"))
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[0][1], '0.000000')
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[1][0], $r("app.string.common_color"))
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[1][1], '0.300000')
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[2][0], $r("app.string.common_color"))
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[2][1], '1.000000')
    assertTrue(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .repeating)
    await button1.tap()
    let radialGradient2: string = await columnRadialGradient1.getInspectorInfo()
    assertEqual(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .radius, '60.00vp')
    assertEqual(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .colors[0][0], '#FFFFAAAA')
    assertEqual(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .colors[0][1], '0.000000')
    assertEqual(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .colors[1][0]
      .toLowerCase(), Color.Green)
    assertEqual(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .colors[1][1], '0.300000')
    assertEqual(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .colors[2][0]
      .toLowerCase(), Color.Pink)
    assertEqual(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .colors[2][1], '1.000000')
    assertFalse(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .repeating)
  }, 0)
}