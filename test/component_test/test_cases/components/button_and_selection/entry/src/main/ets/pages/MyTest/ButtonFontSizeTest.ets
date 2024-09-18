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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function buttonFontSizeTest() {
  /*
   * Button组件 FontSize属性
   * 找到画面id为buttonFontSize1，buttonFontSize2的Button组件
   * 找到画面文本为ButtonFontSize2的Button组件
   * 获取buttonFontSize1的FontSize属性与期待值'30.00fp'比对
   * 获取buttonFontSize2的FontSize属性与期待值'50.00px'比对
   * 点击button，变更buttonFontSize2的FontSize属性值为$r('app.string.font_size')
   * 获取buttonFontSize2的FontSize属性与期待值$r('app.string.font_size')比对
   */
  defineTest('buttonFontSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonFontSizeTestDemo running')
    let driver: Tester = Tester.create()
    let buttonFontSize1: Component = await driver.findComponent(Matcher.create().id('buttonFontSize1').enabled(true))
    let buttonFontSize2: Component = await driver.findComponent(Matcher.create().id('buttonFontSize2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonFontSize2').enabled(true))

    let fontSize1: string = await buttonFontSize1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize1).$attrs.fontSize, '30.00fp')

    let fontSize2: string = await buttonFontSize2.getInspectorInfo()
    assertEqual(JSON.parse(fontSize2).$attrs.fontSize, '50.00px')

    await button.tap()
    let fontSize3: string = await buttonFontSize2.getInspectorInfo()
    assertEqual(JSON.parse(fontSize3).$attrs.fontSize, $r('app.string.font_size'))
  }, 0)
}