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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function outlineColorTest_two() {
  /*
   * outlineColor 通用属性
   * 找到画面id为 menuItemOutlineColor2 的组件
   * 找到画面文本为 ButtonOutlineColor1 ButtonOutlineColor2 ButtonOutlineColor3 按钮
   * 获取 menuItemOutlineColor2 的outlineColor属性与期望值'#FFFFC900'比对
   * 点击 button1 变更 menuItemOutlineColor2 的属性
   * 获取 menuItemOutlineColor2 的outlineColor属性与期望值'#FFBFAAFA'比对
   * 点击 button2 变更 menuItemOutlineColor2 的属性
   * 获取 menuItemOutlineColor2 的outlineColor属性与期望值Color.Blue比对
   * 点击 button3 变更 menuItemOutlineColor2 的属性
   * 获取 menuItemOutlineColor2 的outlineColor属性与期望值$r("app.string.common_color")比对
   * */
  defineTest('outlineColorTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('outlineColorTest_twoDemo running')
    let driver: Tester = Tester.create()
    let menuItemOutlineColor2: Component =
      await driver.findComponent(Matcher.create().id('menuItemOutlineColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineColor2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineColor3').enabled(true))
    let outlineColor1: string = await menuItemOutlineColor2.getInspectorInfo()
    assertEqual(JSON.parse(outlineColor1).$attrs.outlineColor, '#FFFFC900')

    await button1.tap()
    let outlineColor2: string = await menuItemOutlineColor2.getInspectorInfo()
    assertEqual(JSON.parse(outlineColor2).$attrs.outlineColor, '#FFBFAAFA')

    await button2.tap()
    let outlineColor3: string = await menuItemOutlineColor2.getInspectorInfo()
    assertEqual(JSON.parse(outlineColor3).$attrs.outlineColor.toLowerCase(), Color.Blue)

    await button3.tap()
    let outlineColor4: string = await menuItemOutlineColor2.getInspectorInfo()
    assertEqual(JSON.parse(outlineColor4).$attrs.outlineColor, $r("app.string.common_color"))
  }, 0)
}