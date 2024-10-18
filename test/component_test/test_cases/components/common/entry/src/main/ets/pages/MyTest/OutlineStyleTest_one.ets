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

export default async function outlineStyleTest_one() {
  /*
   * outlineStyle 通用属性
   * 找到画面id为 textInputOutlineStyle1 的组件
   * 获取画面文本为 ButtonOutlineStyle1 ButtonOutlineStyle2 按钮
   * 获取 textInputOutlineStyle1 的outlineStyle属性与期望值'OutlineStyle.DOTTED'比对
   * 点击 button1 变更 textInputOutlineStyle1 的属性
   * 获取 textInputOutlineStyle1 的outlineStyle属性与期望值'OutlineStyle.SOLID'比对
   * 点击 button2 变更 textInputOutlineStyle1 的属性
   * 获取 textInputOutlineStyle1 的outlineStyle属性与期望值'OutlineStyle.DASHED'比对
   * */
  defineTest('outlineStyleTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('outlineStyleTest_oneDemo running')
    let driver: Tester = Tester.create()
    let textInputOutlineStyle1: Component =
      await driver.findComponent(Matcher.create().id('textInputOutlineStyle1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineStyle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineStyle2').enabled(true))
    let outlineStyle1: string = await textInputOutlineStyle1.getInspectorInfo()
    assertEqual(JSON.parse(outlineStyle1)
      .$attrs
      .outlineStyle, 'OutlineStyle.DOTTED')

    await button1.tap()
    let outlineStyle2: string = await textInputOutlineStyle1.getInspectorInfo()
    assertEqual(JSON.parse(outlineStyle2)
      .$attrs
      .outlineStyle, 'OutlineStyle.SOLID')

    await button2.tap()
    let outlineStyle3: string = await textInputOutlineStyle1.getInspectorInfo()
    assertEqual(JSON.parse(outlineStyle3)
      .$attrs
      .outlineStyle, 'OutlineStyle.DASHED')
  }, 0)
}