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

export default async function outlineTest_one() {
  /*
   * outline 通用属性
   * 找到画面id为 textInputOutline1 的组件
   * 找到画面文本为 ButtonOutline1 ButtonOutline2 按钮
   * 获取 textInputOutline1 的 width 属性与期望值 $r("app.string.common_value_one") 比对
   * 获取 textInputOutline1 的 color 属性与期望值 "#FFFF0000" 比对
   * 获取 textInputOutline1 的 style.left 属性与期望值 'OutlineStyle.DASHED' 比对
   * 获取 textInputOutline1 的 style.right 属性与期望值 'OutlineStyle.DASHED' 比对
   * 获取 textInputOutline1 的 style.top 属性与期望值 'OutlineStyle.SOLID' 比对
   * 获取 textInputOutline1 的 style.bottom 属性与期望值 'OutlineStyle.DOTTED' 比对
   * 获取 textInputOutline1 的 radius.topLeft 属性与期望值 '5.00px' 比对
   * 获取 textInputOutline1 的 radius.topRight 属性与期望值 '6.00px' 比对
   * 获取 textInputOutline1 的 radius.bottomLeft 属性与期望值 '7.00vp' 比对
   * 获取 textInputOutline1 的 radius.bottomRight 属性与期望值 '10.00vp' 比对
   * 点击 button1 变更 textInputOutline1 的属性
   * 获取 textInputOutline1 的 width 属性与期望值 '5.00px' 比对
   * 获取 textInputOutline1 的 style 属性与期望值 'OutlineStyle.DOTTED' 比对
   * 获取 textInputOutline1 的 radius 属性与期望值 '5.00vp' 比对
   * 获取 textInputOutline1 的 color 属性与期望值 $r("app.string.common_color") 比对
   * */
  defineTest('outlineTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('outlineTest_oneDemo running')
    let driver: Tester = Tester.create()
    let textInputOutline1: Component =
      await driver.findComponent(Matcher.create().id('textInputOutline1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOutline1').enabled(true))
    let outline1: string = await textInputOutline1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).width, $r("app.string.common_value_one"))
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).color, "#FFFF0000")
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).style.left, 'OutlineStyle.DASHED')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).style.right, 'OutlineStyle.DASHED')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).style.top, 'OutlineStyle.SOLID')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).style.bottom, 'OutlineStyle.DOTTED')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).radius.topLeft, '5.00px')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).radius.topRight, '6.00px')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).radius.bottomLeft, '7.00vp')
    assertEqual(JSON.parse(JSON.parse(outline1).$attrs.outline).radius.bottomRight, '10.00vp')

    await button1.tap()
    let outline2: string = await textInputOutline1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(outline2).$attrs.outline).width, '5.00px')
    assertEqual(JSON.parse(JSON.parse(outline2).$attrs.outline).style, 'OutlineStyle.DOTTED')
    assertEqual(JSON.parse(JSON.parse(outline2).$attrs.outline).radius, '5.00vp')
    assertEqual(JSON.parse(JSON.parse(outline2).$attrs.outline).color, $r("app.string.common_color"))
  }, 0)
}