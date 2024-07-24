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

export default async function lineStrokeOpacityTest() {
  /*
   * Line组件 strokeOpacity属性
   * 找到画面id为lineStrokeOpacity1,lineStrokeOpacity2的Line组件
   * 找到画面文本为LineStrokeOpacity1,LineStrokeOpacity2的Button组件
   * 获取line1的strokeOpacity属性与期待值0.0比对
   * 获取line2的strokeOpacity属性与期待值1.0比对
   * 点击button1，变更line2的strokeOpacity属性值为$r('app.string.stroke_opacity')
   * 获取line2的strokeOpacity属性与期待值'0.8'比对
   * 点击button2，变更line2的strokeOpacity属性值为'-10px'
   * 获取line2的strokeOpacity属性与期待值1.0比对
   */
  defineTest('lineStrokeOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("lineStrokeOpacityTestDemo running")
    let driver: Tester = Tester.create()
    let line1: Component = await driver.findComponent(Matcher.create().id('lineStrokeOpacity1').enabled(true))
    let line2: Component = await driver.findComponent(Matcher.create().id('lineStrokeOpacity2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('LineStrokeOpacity1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('LineStrokeOpacity2').enabled(true))

    let strokeOpacity1: string = await line1.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity1).$attrs.strokeOpacity, '0.000000')

    let strokeOpacity2: string = await line2.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity2).$attrs.strokeOpacity, '1.000000')

    await button1.tap()
    let strokeOpacity3: string = await line2.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity3).$attrs.strokeOpacity, $r('app.string.stroke_opacity'))

    await button2.tap()
    let strokeOpacity4: string = await line2.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity4).$attrs.strokeOpacity, '1.000000')
  }, 0)
}