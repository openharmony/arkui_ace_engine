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

export default async function lineStartPointTest() {
  /*
   * Line组件 startPointArray属性
   * 找到画面id为lineStartPoint的Line组件
   * 找到画面文本为LineStartPoint的Button组件
   * 获取line的startPoint属性与期待值[0, 0]比对
   * 点击button，变更line的startPoint属性值为[100, 100]
   * 获取line的startPoint属性与期待值[100, 100]比对
   */
  defineTest('lineStartPointTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("lineStartPointTestDemo running")
    let driver: Tester = Tester.create()
    let line: Component = await driver.findComponent(Matcher.create().id('lineStartPoint').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('LineStartPoint').enabled(true))

    let startPoint1: string = await line.getInspectorInfo()
    assertEqual(JSON.parse(startPoint1).$attrs.startPoint[0], 0)
    assertEqual(JSON.parse(startPoint1).$attrs.startPoint[1], 0)

    await button.tap()
    let startPoint2: string = await line.getInspectorInfo()
    assertEqual(JSON.parse(startPoint2).$attrs.startPoint[0], 100)
    assertEqual(JSON.parse(startPoint2).$attrs.startPoint[1], 100)
  }, 0)
}