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

export default async function lineEndPointTest() {
  /*
   * Line组件 endPoint属性
   * 找到画面id为lineEndPoint的Line组件
   * 找到画面文本为LineEndPoint的Button组件
   * 获取line的endPoint属性与期待值[200, 200]比对
   * 点击button，变更line的endPoint属性值为[100, 300]
   * 获取line的endPoint属性与期待值[100, 300]比对
   */
  defineTest('lineEndPointTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("lineEndPointTestDemo running")
    let driver: Tester = Tester.create()
    let line: Component = await driver.findComponent(Matcher.create().id('lineEndPoint').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('LineEndPoint').enabled(true))

    let endPoint1: string = await line.getInspectorInfo()
    assertEqual(JSON.parse(endPoint1).$attrs.endPoint[0], 200)
    assertEqual(JSON.parse(endPoint1).$attrs.endPoint[1], 200)

    await button.tap()
    let endPoint2: string = await line.getInspectorInfo()
    assertEqual(JSON.parse(endPoint2).$attrs.endPoint[0], 100)
    assertEqual(JSON.parse(endPoint2).$attrs.endPoint[1], 300)
  }, 0)
}