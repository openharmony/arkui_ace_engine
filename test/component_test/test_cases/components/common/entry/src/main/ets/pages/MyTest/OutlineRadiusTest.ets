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

export default async function outlineRadiusTest() {
  /*
   * outlineRadius 通用属性
   * 找到画面id为 textOutlineRadius1 的 text 组件
   * 获取画面文本为 ButtonOutlineRadius1 ButtonOutlineRadius2 按钮
   * 获取 textOutlineRadius1 的 outlineRadius.topLeft 属性与期望值 '20.00vp' 比对
   * 获取 textOutlineRadius1 的 outlineRadius.topRight 属性与期望值 '40.00vp' 比对
   * 获取 textOutlineRadius1 的 outlineRadius.bottomLeft 属性与期望值 $r("app.string.common_value_two") 比对
   * 获取 textOutlineRadius1 的 outlineRadius.bottomRight 属性与期望值 '20.00vp' 比对
   * 点击 button1 变更 textOutlineRadius1 的属性
   * 获取 textOutlineRadius1 的outlineRadius属性与期望值'10.00vp'比对
   * 点击 button2 变更 textOutlineRadius1 的属性
   * 获取 textOutlineRadius1 的属性与期望值$r("app.string.common_value_two")比对
   * */
  defineTest('outlineRadiusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('outlineRadiusTestDemo running')
    let driver: Tester = Tester.create()
    let textOutlineRadius1: Component =
      await driver.findComponent(Matcher.create().id('textOutlineRadius1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineRadius1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonOutlineRadius2').enabled(true))
    let outlineRadius1: string = await textOutlineRadius1.getInspectorInfo()
    assertEqual(JSON.parse(outlineRadius1)
      .$attrs
      .outlineRadius
      .topLeft, '20.00vp')
    assertEqual(JSON.parse(outlineRadius1)
      .$attrs
      .outlineRadius
      .topRight, '40.00vp')
    assertEqual(JSON.parse(outlineRadius1)
      .$attrs
      .outlineRadius
      .bottomLeft, $r("app.string.common_value_two"))
    assertEqual(JSON.parse(outlineRadius1)
      .$attrs
      .outlineRadius
      .bottomRight, '20.00vp')

    await button1.tap()
    let outlineRadius2: string = await textOutlineRadius1.getInspectorInfo()
    assertEqual(JSON.parse(outlineRadius2)
      .$attrs
      .outlineRadius, '10.00vp')

    await button2.tap()
    let outlineRadius3: string = await textOutlineRadius1.getInspectorInfo()
    assertEqual(JSON.parse(outlineRadius3)
      .$attrs
      .outlineRadius, $r("app.string.common_value_two"))
  }, 0)
}