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

export default async function offsetTest() {
  /*
   * offset 通用属性
   * 找到画面id为 sliderOffset1 的组件
   * 找到画面文本为 ButtonOffset1 ButtonOffset2 按钮
   * 获取 sliderOffset1 的 offset.x 属性与期望值 $r("app.string.common_value_two") 比对
   * 获取 sliderOffset1 的 offset.x 属性与期望值 $r("app.string.common_value_two") 比对
   * 点击 button1 变更 sliderOffset1 的属性
   * 获取 sliderOffset1 的 offset.x 属性与期望值 '10.00vp' 比对
   * 获取 sliderOffset1 的 offset.x 属性与期望值 '10.00vp' 比对
   * 点击 button2 变更 sliderOffset1 的属性
   * 获取 sliderOffset1 的 offset.x 属性与期望值 '30.00vp' 比对
   * 获取 sliderOffset1 的 offset.x 属性与期望值 '30.00vp' 比对
   * */
  defineTest('offsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('offsetTestDemo running')
    let driver: Tester = Tester.create()
    let sliderOffset1: Component = await driver.findComponent(Matcher.create().id('sliderOffset1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOffset1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonOffset2').enabled(true))
    let enabled1: string = await sliderOffset1.getInspectorInfo()
    assertEqual(JSON.parse(enabled1)
      .$attrs
      .offset
      .x, $r("app.string.common_value_two"))
    assertEqual(JSON.parse(enabled1)
      .$attrs
      .offset
      .y, $r("app.string.common_value_two"))

    await button1.tap()
    let enabled2: string = await sliderOffset1.getInspectorInfo()
    assertEqual(JSON.parse(enabled2)
      .$attrs
      .offset
      .x, '10.00vp')
    assertEqual(JSON.parse(enabled2)
      .$attrs
      .offset
      .y, '10.00vp')
    await button2.tap()
    let enabled3: string = await sliderOffset1.getInspectorInfo()
    assertEqual(JSON.parse(enabled3)
      .$attrs
      .offset
      .x, '30.00vp')
    assertEqual(JSON.parse(enabled3)
      .$attrs
      .offset
      .y, '30.00vp')
  }, 0)
}