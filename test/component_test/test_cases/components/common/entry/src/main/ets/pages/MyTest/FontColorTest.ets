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

import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function fontColorTest() {
  /*
   * fontSize 通用属性
   * 找到画面id为 textFontColor1 的 Text 组件
   * 找到画面文本为 ButtonFontColor1 ButtonFontColor2 ButtonFontColor3 按钮
   * 获取 textFontColor1 的fontColor,属性与期望值$r("app.string.common_color")比对
   * 点击 button1 变更 textFontColor1 的属性
   * 获取 textFontColor1 的fontColor属性与期望值Color.Red比对
   * 点击 button2 变更 textFontColor1 的属性
   * 获取 textFontColor1 的fontColor属性与期望值'#FFAAFFAA'比对
   * 点击 button2 变更 textFontColor1 的属性
   * 获取 textFontColor1 的fontColor属性与期望值'#FFFFE000'比对
   * */
  defineTest('fontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('fontColorTestDemo running')
    let driver: Tester = Tester.create()
    let textFontColor: Component = await driver.findComponent(Matcher.create().id('textFontColor1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonFontColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonFontColor2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonFontColor3').enabled(true))
    let fontColor1: string = await textFontColor.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor, $r("app.string.common_color"))

    await button1.tap()
    let fontColor2: string = await textFontColor.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor.toLowerCase(), Color.Red)

    await button2.tap()
    let fontColor3: string = await textFontColor.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor, '#FFAAFFAA')

    await button3.tap()
    let fontColor4: string = await textFontColor.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, '#FFFFE000')
  }, 0)
}