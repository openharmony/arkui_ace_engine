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

export default async function rectRadiusHeightTest() {
  /*
   * Rect组件 radiusHeight属性
   * 找到画面id为rectRadiusHeight的Rect组件
   * 找到画面文本为RectRadiusHeight的Button组件
   * 获取rect的radiusHeight属性与期待值20比对
   * 点击button,变更rect的radiusHeight属性值为'50'
   * 获取rect的radiusHeight属性与期待值'50'比对
   */
  defineTest('rectRadiusHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rectRadiusHeightTestDemo running")
    let driver: Tester = Tester.create()
    let rect: Component = await driver.findComponent(Matcher.create().id('rectRadiusHeight').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RectRadiusHeight').enabled(true))

    let radiusHeight1: string = await rect.getInspectorInfo()
    assertEqual(JSON.parse(radiusHeight1).$attrs.radiusHeight, 20)

    await button.tap()
    let radiusHeight2: string = await rect.getInspectorInfo()
    assertEqual(JSON.parse(radiusHeight2).$attrs.radiusHeight, '50')
  }, 0)
}