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

export default async function decorationTest() {
  /*
   * decoration 通用属性
   * 找到画面id为 textDecoration1 的 Text 组件
   * 找到画面文本为 ButtonDecoration1 ButtonDecoration2
   * ButtonDecoration3 ButtonDecoration4 的按钮
   * 获取 textDecoration1 的属性
   * textDecoration1 的 type 属性与期望值 'TextDecorationType.None' 比对
   * textDecoration1 的 color 属性与期望值 $r("app.string.common_color") 比对
   * textDecoration1 的 style 属性与期望值 "TextDecorationStyle.SOLID" 比对
   * 点击 button1 变更 textDecoration1 的属性
   * 获取 textDecoration1 的属性
   * textDecoration1 的 type 属性与期望值 'TextDecorationType.LineThrough' 比对
   * textDecoration1 的 color 属性与期望值 Color.Orange 比对
   * textDecoration1 的 style 属性与期望值 "TextDecorationStyle.DOUBLE" 比对
   * 点击 button2 变更 textDecoration1 的属性
   * 获取 textDecoration1 的属性
   * textDecoration1 的 type 属性与期望值 'TextDecorationType.Underline' 比对
   * textDecoration1 的 color 属性与期望值 '#FFAAFFAA' 比对
   * textDecoration1 的 style 属性与期望值 "TextDecorationStyle.DOTTED" 比对
   * 点击 button3 变更 textDecoration1 的属性
   * 获取 textDecoration1 的属性
   * textDecoration1 的 type 属性与期望值 'TextDecorationType.Overline' 比对
   * textDecoration1 的 color 属性与期望值 '#FFFF00FF' 比对
   * textDecoration1 的 style 属性与期望值 "TextDecorationStyle.DASHED" 比对
   * 点击 button4 变更 textDecoration1 的属性
   * 获取 textDecoration1 的 style 属性与期望值 "TextDecorationStyle.WAVY" 比对
   * */
  defineTest('decorationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('decorationTestDemo running')
    let driver: Tester = Tester.create()
    let textDecoration1: Component = await driver.findComponent(Matcher.create().id('textDecoration1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonDecoration1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonDecoration2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonDecoration3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('ButtonDecoration4').enabled(true))
    let decoration1: string = await textDecoration1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(decoration1).$attrs.decoration).type, 'TextDecorationType.None')
    assertEqual(JSON.parse(JSON.parse(decoration1).$attrs.decoration).color, $r("app.string.common_color"))
    assertEqual(JSON.parse(JSON.parse(decoration1).$attrs.decoration).style, "TextDecorationStyle.SOLID")

    await button1.tap()
    let decoration2: string = await textDecoration1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(decoration2).$attrs.decoration).type, 'TextDecorationType.LineThrough')
    assertEqual(JSON.parse(JSON.parse(decoration2).$attrs.decoration).color.toLowerCase(), Color.Orange)
    assertEqual(JSON.parse(JSON.parse(decoration2).$attrs.decoration).style, "TextDecorationStyle.DOUBLE")

    await button2.tap()
    let decoration3: string = await textDecoration1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(decoration3).$attrs.decoration).type, 'TextDecorationType.Underline')
    assertEqual(JSON.parse(JSON.parse(decoration3).$attrs.decoration).color, '#FFAAFFAA')
    assertEqual(JSON.parse(JSON.parse(decoration3).$attrs.decoration).style, "TextDecorationStyle.DOTTED")

    await button3.tap()
    let decoration4: string = await textDecoration1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(decoration4).$attrs.decoration).type, 'TextDecorationType.Overline')
    assertEqual(JSON.parse(JSON.parse(decoration4).$attrs.decoration).color, '#FFFF00FF')
    assertEqual(JSON.parse(JSON.parse(decoration4).$attrs.decoration).style, "TextDecorationStyle.DASHED")

    await button4.tap()
    let decoration5: string = await textDecoration1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(decoration5).$attrs.decoration).style, "TextDecorationStyle.WAVY")
  }, 0)
}