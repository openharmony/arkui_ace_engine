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

export default async function markAnchorTest() {
  /*
   * markAnchor 通用属性
   * 找到画面id为 sliderMarkAnchor1 的 Slider 组件
   * 找到画面文本为 ButtonMarkAnchor1 ButtonMarkAnchor2 按钮
   * 获取 sliderMarkAnchor1 的 x 属性与期望值$r("app.string.common_value_one")比对
   * 获取 sliderMarkAnchor1 的 y 属性与期望值$r("app.string.common_value_one")比对
   * 点击 button1 变更 sliderMarkAnchor1 的属性
   * 获取 sliderMarkAnchor1 的 x 属性与期望值 '2.00vp' 比对
   * 获取 sliderMarkAnchor1 的 y 属性与期望值 '2.00vp' 比对
   * 点击 button2 变更 sliderMarkAnchor1 的属性
   * 获取 sliderMarkAnchor1 的 x 属性与期望值 '1.00vp' 比对
   * 获取 sliderMarkAnchor1 的 y 属性与期望值 '1.00vp' 比对
   * */
  defineTest('markAnchorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('markAnchorTestDemo running')
    let driver: Tester = Tester.create()
    let sliderMarkAnchor1: Component =
      await driver.findComponent(Matcher.create().id('sliderMarkAnchor1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonMarkAnchor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonMarkAnchor2').enabled(true))
    let markAnchor1: string = await sliderMarkAnchor1.getInspectorInfo()
    assertEqual(JSON.parse(markAnchor1).$attrs.markAnchor.x, $r("app.string.common_value_one"))
    assertEqual(JSON.parse(markAnchor1).$attrs.markAnchor.y, $r("app.string.common_value_one"))

    await button1.tap()
    let markAnchor2: string = await sliderMarkAnchor1.getInspectorInfo()
    assertEqual(JSON.parse(markAnchor2)
      .$attrs
      .markAnchor
      .x, '2.00vp')
    assertEqual(JSON.parse(markAnchor2)
      .$attrs
      .markAnchor
      .y, '2.00vp')

    await button2.tap()
    let markAnchor3: string = await sliderMarkAnchor1.getInspectorInfo()
    assertEqual(JSON.parse(markAnchor3)
      .$attrs
      .markAnchor
      .x, '1.00vp')
    assertEqual(JSON.parse(markAnchor3)
      .$attrs
      .markAnchor
      .y, '1.00vp')
  }, 0)
}