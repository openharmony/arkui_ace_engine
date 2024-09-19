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

export default async function outlineTest_two() {
  /*
* outline 通用属性
* 找到画面id为 textInputOutline2 的组件
* 获取画面文本为 ButtonOutline1 ButtonOutline2 按钮
* 获取 textInputOutline2 的 width 属性与期望值 $r("app.string.common_value_one") 比对
* 获取 textInputOutline2 的 style 属性与期望值 'OutlineStyle.DOTTED' 比对
* 获取 textInputOutline2 的 radius 属性与期望值 $r("app.string.common_value_one") 比对
* 获取 textInputOutline2 的 color.left 属性与期望值 Color.Brown 比对
* 获取 textInputOutline2 的 color.right 属性与期望值 '#FFFF0000' 比对
* 获取 textInputOutline2 的 color.top 属性与期望值 $r("app.string.common_color") 比对
* 获取 textInputOutline2 的 color.bottom 属性与期望值 '#FF0066FF' 比对
* 点击 button1 变更 textInputOutline2 的属性
* 获取 textInputOutline2 的属性与期望值比对
* 获取 textInputOutline2 的 style 属性与期望值 'OutlineStyle.SOLID' 比对
* 获取 textInputOutline2 的 color 属性与期望值 '#FFFFF30C' 比对
* */
  defineTest('outlineTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('outlineTest_twoDemo running')
    let driver: Tester = Tester.create()
    let textInputOutline2: Component =
      await driver.findComponent(Matcher.create().id('textInputOutline2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOutline1').enabled(true))
    let outline1: string = await textInputOutline2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).width, $r("app.string.common_value_one"))
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).style, 'OutlineStyle.DOTTED')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).radius, $r("app.string.common_value_one"))
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).color.left.toLowerCase(), Color.Brown)
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).color.right, '#FFFF0000')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).color.top, $r("app.string.common_color"))
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).color.bottom, '#FF0066FF')

    await button1.tap()
    let outline2: string = await textInputOutline2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(outline2).$attrs.outline).style, 'OutlineStyle.SOLID')
    assertEqual(JSON.parse(JSON.parse(outline2).$attrs.outline).color, '#FFFFF30C')
  }, 0)
}