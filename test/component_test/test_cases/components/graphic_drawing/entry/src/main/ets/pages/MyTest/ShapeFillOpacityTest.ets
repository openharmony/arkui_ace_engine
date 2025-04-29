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

import {
  assertContain,
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function shapeFillOpacityTest() {
  /*
   * Shape组件 fillOpacity属性
   * 找到画面id为shapeFillOpacity1,shapeFillOpacity2的Shape组件
   * 找到画面文本为ShapeFillOpacity的Button组件
   * 获取shape1的fillOpacity属性与期待值0.0比对
   * 点击button,变更shape1的fillOpacity属性值为'0.2px'
   * 获取shape1的fillOpacity属性与期待值'1.0'比对
   * 获取shape2的fillOpacity属性与期待值'0.8'比对
   */
  defineTest('shapeFillOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("shapeFillOpacityTestDemo running")
    let driver: Tester = Tester.create()
    let shape1: Component = await driver.findComponent(Matcher.create().id('shapeFillOpacity1').enabled(true))
    let shape2: Component = await driver.findComponent(Matcher.create().id('shapeFillOpacity2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ShapeFillOpacity').enabled(true))

    let fillOpacity1: string = await shape1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity1).$attrs.fillOpacity, '0.000000')

    await button.tap()
    let fillOpacity2: string = await shape1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity2).$attrs.fillOpacity, '1.000000')

    let fillOpacity3: string = await shape2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity3).$attrs.fillOpacity, $r('app.string.fill_opacity'))
  }, 0)
}