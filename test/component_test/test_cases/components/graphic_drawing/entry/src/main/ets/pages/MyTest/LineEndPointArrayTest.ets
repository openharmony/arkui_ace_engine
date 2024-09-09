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

export default async function lineEndPointArrayTest() {
  /*
   * Line组件 endPointArray属性
   * 找到画面id为Line的Circle组件
   * 找到画面文本为LineEndPointArray的Button组件
   * 获取line的endPointArray属性与期待值[200, 200]比对
   * 点击button，变更line的endPointArray属性值为[100, 300]
   * 获取line的endPointArray属性与期待值[100, 300]比对
   */
  defineTest('lineEndPointArrayTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("lineEndPointArrayTestDemo running")
    let driver: Tester = Tester.create()
    let line: Component = await driver.findComponent(Matcher.create().id('Line').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('LineEndPointArray').enabled(true))

    let endPoint1: string = await line.getInspectorInfo()
    assertEqual(JSON.parse(endPoint1).$attrs.endPoint, [200, 200])

    await button.tap()
    let endPoint2: string = await line.getInspectorInfo()
    assertEqual(JSON.parse(endPoint2).$attrs.endPoint, [100, 300])
  }, 0)
}