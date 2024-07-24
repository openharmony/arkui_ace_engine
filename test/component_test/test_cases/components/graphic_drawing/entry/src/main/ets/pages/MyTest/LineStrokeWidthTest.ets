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

export default async function lineStrokeWidthTest() {
  /*
   * Line组件 strokeWidth属性
   * 找到画面id为lineStrokeWidth1,lineStrokeWidth2的Line组件
   * 找到画面文本为LineStrokeWidth1,LineStrokeWidth2的Button组件
   * 获取line1的strokeWidth属性与期待值-10比对
   * 点击button1，变更line1的strokeWidth属性值为'10px'
   * 获取line1的strokeWidth属性与期待值1比对
   * 点击button2，变更line1的strokeWidth属性值为'50%'
   * 获取line1的strokeWidth属性与期待值'50%'比对
   * 获取line2的strokeWidth属性与期待值'3'比对
   *
   */
  defineTest('lineStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("lineStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let line1: Component = await driver.findComponent(Matcher.create().id('lineStrokeWidth1').enabled(true))
    let line2: Component = await driver.findComponent(Matcher.create().id('lineStrokeWidth2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('LineStrokeWidth1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('LineStrokeWidth2').enabled(true))

    let strokeWidth1: string = await line1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, 2)
    await button1.tap()
    let strokeWidth2: string = await line1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, 1)
    await button2.tap()
    let strokeWidth3: string = await line1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, '50%')
    let strokeWidth4: string = await line2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth4).$attrs.strokeWidth, $r('app.string.stroke_width'))
  }, 0)
}