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

export default async function rectStrokeWidthTest() {
  /*
   * Rect组件 strokeWidth属性
   * 找到画面id为rectStrokeWidth1,rectStrokeWidth2的Rect组件
   * 找到画面文本为RectStrokeWidth的Button组件
   * 获取rect1的strokeWidth属性与期待值5比对
   * 点击button,变更rect1的strokeWidth属性值为'10px'
   * 获取rect1的strokeWidth属性与期待值'1'比对
   * 获取rect2的strokeWidth属性与期待值'3'比对
   */
  defineTest('rectStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rectStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let rect1: Component = await driver.findComponent(Matcher.create().id('rectStrokeWidth1').enabled(true))
    let rect2: Component = await driver.findComponent(Matcher.create().id('rectStrokeWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RectStrokeWidth').enabled(true))

    let strokeWidth1: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, 5)

    await button.tap()
    let strokeWidth2: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, '1')

    let strokeWidth3: string = await rect2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, $r('app.string.stroke_width'))
  }, 0)
}