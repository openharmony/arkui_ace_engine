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

export default async function radialGradientTest_two() {
  /*
* Column组件 radialGradient 通用属性
* 找到画面id为 columnRadialGradient2 的组件
* 找到画面文本为 Column_RadialGradient1 按钮
* 获取 columnRadialGradient2 的属性与期望值{#FF0800FF, #FF7A7777, #FFFF0000}比对
* 点击 button1 变更 columnRadialGradient2 的属性repeating的值
* 获取 columnRadialGradient2 的属性repeating值与期望值false比对
* */
  defineTest('radialGradientSample_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('radialGradientSample_twoDemo running')
    let driver: Tester = Tester.create()
    let columnRadialGradient2: Component =
      await driver.findComponent(Matcher.create().id('columnRadialGradient2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonRadialGradient1').enabled(true))
    let radialGradient1: string = await columnRadialGradient2.getInspectorInfo()
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[0][0], '#FF0800FF')
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[1][0], '#FF7A7777')
    assertEqual(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .colors[2][0], '#FFFF0000')
    assertTrue(JSON.parse(radialGradient1)
      .$attrs
      .radialGradient
      .repeating)
    await button1.tap()
    let radialGradient2: string = await columnRadialGradient2.getInspectorInfo()
    assertFalse(JSON.parse(radialGradient2)
      .$attrs
      .radialGradient
      .repeating)
  }, 0)
}