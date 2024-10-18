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

export default async function rectFillOpacityTest() {
  /*
   * Rect组件 fillOpacity属性
   * 找到画面id为rectFillOpacity1,rectFillOpacity2的Rect组件
   * 找到画面文本为RectFillOpacity的Button组件
   * 获取rect1的fillOpacity属性与期待值0.5比对
   * 获取rect2的fillOpacity属性与期待值'1.0'比对
   * 点击button2,变更rect2的fillOpacity属性值为$r('app.string.fill_opacity')
   * 获取rect2的fillOpacity属性与期待值'0.8'比对
   */
  defineTest('rectFillOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rectFillOpacityTestDemo running")
    let driver: Tester = Tester.create()
    let rect1: Component = await driver.findComponent(Matcher.create().id('rectFillOpacity1').enabled(true))
    let rect2: Component = await driver.findComponent(Matcher.create().id('rectFillOpacity2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RectFillOpacity').enabled(true))

    let fillOpacity1: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity1).$attrs.fillOpacity, '0.500000')

    let fillOpacity2: string = await rect2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity2).$attrs.fillOpacity, '1.000000')

    await button.tap()
    let fillOpacity3: string = await rect2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity3).$attrs.fillOpacity, $r('app.string.fill_opacity'))
  }, 0)
}