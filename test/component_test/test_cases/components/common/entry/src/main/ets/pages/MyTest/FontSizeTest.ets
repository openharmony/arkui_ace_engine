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

export default async function fontSizeTest() {
  /*
   * fontSize 通用属性
   * 找到画面id为 textFontSize1 的 Text 组件
   * 找到画面文本为 ButtonFontSize1 ButtonFontSize2 按钮
   * 获取 textFontSize1 的fontSize属性与期望值$r("app.string.common_value_two")比对
   * 点击 button1 变更 textFontSize1 的属性
   * 获取 textFontSize1 的fontSize属性与期望值'50.00fp'比对
   * 点击 button2 变更 textFontSize1 的属性
   * 获取 textFontSize1 的fontSize属性与期望值'30.00fp'比对
   * */
  defineTest('fontSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('fontSizeTestDemo running')
    let driver: Tester = Tester.create()
    let textFontSize1: Component = await driver.findComponent(Matcher.create().id('textFontSize1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonFontSize1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonFontSize2').enabled(true))
    let fontSize1: string = await textFontSize1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize1).$attrs.fontSize, $r("app.string.common_value_two"))

    await button1.tap()
    let fontSize2: string = await textFontSize1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize2).$attrs.fontSize, '50.00fp')

    await button2.tap()
    let fontSize3: string = await textFontSize1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize3).$attrs.fontSize, '30.00fp')
  }, 0)
}