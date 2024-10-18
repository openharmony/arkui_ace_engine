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

export default async function fontStyleTest() {
  /*
   * fontStyle 通用属性
   * 找到画面id为 textFontStyle1 的 Text 组件
   * 找到画面文本为 ButtonFontStyle1 按钮
   * 获取 textFontStyle1 的fontStyle属性与期望值'FontStyle.Normal'比对
   * 点击 button1 变更 textFontStyle1 的属性
   * 获取 textFontStyle1 的fontStyle属性与期望值'FontStyle.Italic'比对
   * */
  defineTest('fontStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('fontStyleTestDemo running')
    let driver: Tester = Tester.create()
    let textFontStyle1: Component = await driver.findComponent(Matcher.create().id('textFontStyle1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonFontStyle1').enabled(true))
    let fontStyle1: string = await textFontStyle1.getInspectorInfo()
    assertEqual(JSON.parse(fontStyle1).$attrs.fontStyle, 'FontStyle.Normal')

    await button1.tap()
    let fontStyle2: string = await textFontStyle1.getInspectorInfo()
    assertEqual(JSON.parse(fontStyle2).$attrs.fontStyle, 'FontStyle.Italic')
  }, 0)
}