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

export default async function outlineStyleTest_two() {
  /*
* outlineStyle 通用属性
* 找到画面id为 textInputOutlineStyle2 的组件
* 获取画面文本为 ButtonOutlineStyle2 ButtonOutlineStyle2 按钮
* 获取 textInputOutlineStyle2 的 outlineStyle.left 属性与期望值 'OutlineStyle.DOTTED' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.right 属性与期望值 'OutlineStyle.DOTTED' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.top 属性与期望值 'OutlineStyle.DOTTED' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.bottom 属性与期望值 'OutlineStyle.SOLID' 比对
* 点击 button1 变更 textInputOutlineStyle2 的属性
* 获取 textInputOutlineStyle2 的 outlineStyle.left 属性与期望值 'OutlineStyle.DASHED' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.right 属性与期望值 'OutlineStyle.SOLID' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.top 属性与期望值 'OutlineStyle.DASHED' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.bottom 属性与期望值 'OutlineStyle.DOTTED' 比对
* 点击 button2 变更 textInputOutlineStyle2 的属性
* 获取 textInputOutlineStyle2 的 outlineStyle.left 属性与期望值 'OutlineStyle.SOLID' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.right 属性与期望值 'OutlineStyle.DASHED' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.top 属性与期望值 'OutlineStyle.SOLID' 比对
* 获取 textInputOutlineStyle2 的 outlineStyle.bottom 属性与期望值 'OutlineStyle.DASHED' 比对
* */
  defineTest('outlineStyleTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('outlineStyleTest_twoDemo running')
    let driver: Tester = Tester.create()
    let textInputOutlineStyle2: Component =
      await driver.findComponent(Matcher.create().id('textInputOutlineStyle2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineStyle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineStyle2').enabled(true))
    let outlineStyle1: string = await textInputOutlineStyle2.getInspectorInfo()
    assertEqual(JSON.parse(outlineStyle1)
      .$attrs
      .outlineStyle
      .left, 'OutlineStyle.DOTTED')
    assertEqual(JSON.parse(outlineStyle1)
      .$attrs
      .outlineStyle
      .right, 'OutlineStyle.DOTTED')
    assertEqual(JSON.parse(outlineStyle1)
      .$attrs
      .outlineStyle
      .top, 'OutlineStyle.DOTTED')
    assertEqual(JSON.parse(outlineStyle1)
      .$attrs
      .outlineStyle
      .bottom, 'OutlineStyle.SOLID')
    await button1.tap()
    let outlineStyle2: string = await textInputOutlineStyle2.getInspectorInfo()
    assertEqual(JSON.parse(outlineStyle2)
      .$attrs
      .outlineStyle
      .left, 'OutlineStyle.DASHED')
    assertEqual(JSON.parse(outlineStyle2)
      .$attrs
      .outlineStyle
      .right, 'OutlineStyle.SOLID')
    assertEqual(JSON.parse(outlineStyle2)
      .$attrs
      .outlineStyle
      .top, 'OutlineStyle.DASHED')
    assertEqual(JSON.parse(outlineStyle2)
      .$attrs
      .outlineStyle
      .bottom, 'OutlineStyle.DOTTED')
    await button2.tap()
    let outlineStyle3: string = await textInputOutlineStyle2.getInspectorInfo()
    assertEqual(JSON.parse(outlineStyle3)
      .$attrs
      .outlineStyle
      .left, 'OutlineStyle.SOLID')
    assertEqual(JSON.parse(outlineStyle3)
      .$attrs
      .outlineStyle
      .right, 'OutlineStyle.DASHED')
    assertEqual(JSON.parse(outlineStyle3)
      .$attrs
      .outlineStyle
      .top, 'OutlineStyle.SOLID')
    assertEqual(JSON.parse(outlineStyle3)
      .$attrs
      .outlineStyle
      .bottom, 'OutlineStyle.DASHED')
  }, 0)
}