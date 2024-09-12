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

export default async function rectRadiusWidthTest() {
  /*
   * Rect组件 radiusWidth属性
   * 找到画面id为rectRadiusWidth的Rect组件
   * 找到画面文本为RectRadiusWidth的Button组件
   * 获取rect的radiusWidth属性与期待值40比对
   * 点击button,变更rect的radiusWidth属性值为'50'
   * 获取rect的radiusWidth属性与期待值'50'比对
   */
  defineTest('rectRadiusWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rectRadiusWidthTestDemo running")
    let driver: Tester = Tester.create()
    let rect: Component = await driver.findComponent(Matcher.create().id('rectRadiusWidth').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RectRadiusWidth').enabled(true))

    let radiusWidth1: string = await rect.getInspectorInfo()
    assertEqual(JSON.parse(radiusWidth1).$attrs.radiusWidth, 40)

    await button.tap()
    let radiusWidth2: string = await rect.getInspectorInfo()
    assertEqual(JSON.parse(radiusWidth2).$attrs.radiusWidth, '50')
  }, 0)
}