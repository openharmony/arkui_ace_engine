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

export default async function shapeViewPortTest() {
  /*
   * Shape组件 viewPort属性
   * 找到画面id为shapeViewPort的Shape组件
   * 找到画面文本为ShapeViewPort的Button组件
   * 获取shape的viewPort属性与期待值{-2,-2,304,130}比对
   * 点击button,变更shape的viewPort属性值为{'2','2','400','200'}
   * 获取shape的viewPort属性与期待值{'2','2','400','200'}比对
   */
  defineTest('shapeViewPortTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("shapeViewPortTestDemo running")
    let driver: Tester = Tester.create()
    let shape: Component = await driver.findComponent(Matcher.create().id('shapeViewPort').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ShapeViewPort').enabled(true))

    let viewPort1: string = await shape.getInspectorInfo()
    assertEqual(JSON.parse(viewPort1).$attrs.viewPort.x, '-2.00vp')
    assertEqual(JSON.parse(viewPort1).$attrs.viewPort.y, '-2.00vp')
    assertEqual(JSON.parse(viewPort1).$attrs.viewPort.width, '304.00vp')
    assertEqual(JSON.parse(viewPort1).$attrs.viewPort.height, '130.00vp')

    await button.tap()
    let viewPort2: string = await shape.getInspectorInfo()
    assertEqual(JSON.parse(viewPort2).$attrs.viewPort.x, '2.00vp')
    assertEqual(JSON.parse(viewPort2).$attrs.viewPort.y, '2.00vp')
    assertEqual(JSON.parse(viewPort2).$attrs.viewPort.width, '400.00vp')
    assertEqual(JSON.parse(viewPort2).$attrs.viewPort.height, '200.00vp')
  }, 0)
}