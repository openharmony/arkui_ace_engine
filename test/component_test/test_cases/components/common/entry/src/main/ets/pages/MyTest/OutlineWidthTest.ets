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

export default async function outlineWidthTest() {
  /*
   * outlineWidth 通用属性
   * 找到画面id为 timePickerOutlineWidth1 的组件
   * 找到画面文本为 ButtonOutlineWidth1 ButtonOutlineWidth2 ButtonOutlineWidth3 按钮
   * 获取 timePickerOutlineWidth1 的 outlineWidth.left 属性与期望值 '5.00vp' 比对
   * 获取 timePickerOutlineWidth1 的 outlineWidth.right 属性与期望值 $r("app.string.common_value_one") 比对
   * 获取 timePickerOutlineWidth1 的 outlineWidth.top 属性与期望值 '15.00px' 比对
   * 获取 timePickerOutlineWidth1 的 outlineWidth.bottom 属性与期望值 '20.00vp' 比对
   * 点击 button1 变更 timePickerOutlineWidth1 的属性
   * 获取 timePickerOutlineWidth1 的Dimension属性与期望值 '15.00px' 比对
   * 点击 button2 变更 timePickerOutlineWidth1 的属性
   * 获取 timePickerOutlineWidth1 的Dimension属性与期望值 $r("app.string.common_value_one") 比对
   * 点击 button3 变更 timePickerOutlineWidth1 的属性
   * 获取 timePickerOutlineWidth1 的Dimension属性与期望值 '20.00vp' 比对
   * */
  defineTest('outlineWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('outlineWidthTestDemo running')
    let driver: Tester = Tester.create()
    let timePickerOutlineWidth1: Component =
      await driver.findComponent(Matcher.create().id('timePickerOutlineWidth1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineWidth1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineWidth2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineWidth3').enabled(true))
    let outlineWidth1: string = await timePickerOutlineWidth1.getInspectorInfo()
    assertEqual(JSON.parse(outlineWidth1)
      .$attrs
      .outlineWidth
      .left, '5.00vp')
    assertEqual(JSON.parse(outlineWidth1)
      .$attrs
      .outlineWidth
      .right, $r("app.string.common_value_one"))
    assertEqual(JSON.parse(outlineWidth1)
      .$attrs
      .outlineWidth
      .top, '15.00px')
    assertEqual(JSON.parse(outlineWidth1)
      .$attrs
      .outlineWidth
      .bottom, '20.00vp')
    await button1.tap()
    let outlineWidth2: string = await timePickerOutlineWidth1.getInspectorInfo()
    assertEqual(JSON.parse(outlineWidth2)
      .$attrs
      .outlineWidth
      .Dimension, '15.00px')
    await button2.tap()
    let outlineWidth3: string = await timePickerOutlineWidth1.getInspectorInfo()
    assertEqual(JSON.parse(outlineWidth3)
      .$attrs
      .outlineWidth
      .Dimension, $r("app.string.common_value_one"))
    await button3.tap()
    let outlineWidth4: string = await timePickerOutlineWidth1.getInspectorInfo()
    assertEqual(JSON.parse(outlineWidth4)
      .$attrs
      .outlineWidth
      .Dimension, '20.00vp')
  }, 0)
}