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

export default async function shapeStrokeWidthTest() {
  /*
   * Shape组件 strokeWidth属性
   * 找到画面id为shapeStrokeWidth的Shape组件
   * 找到画面文本为ShapeStrokeWidth的Button组件
   * 获取Shape的strokeWidth属性与期待值5比对
   * 点击button,变更Shape的strokeWidth属性值为'3'
   * 获取Shape的strokeWidth属性与期待值'3'比对
   */
  defineTest('shapeStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("shapeStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let shape: Component = await driver.findComponent(Matcher.create().id('shapeStrokeWidth').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ShapeStrokeWidth').enabled(true))

    let shapeStrokeWidth1: string = await shape.getInspectorInfo()
    assertEqual(JSON.parse(shapeStrokeWidth1).$attrs.strokeWidth, 5)

    await button.tap()
    let shapeStrokeWidth2: string = await shape.getInspectorInfo()
    assertEqual(JSON.parse(shapeStrokeWidth2).$attrs.strokeWidth, '3')
  }, 0)
}