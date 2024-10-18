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
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function circleAntiAliasTest() {
  /*
   * Circle组件 antiAlias属性
   * 找到画面id为circleAntiAlias的Circle组件
   * 找到画面文本为CircleAntiAlias的Button组件
   * 获取circle的antiAlias属性判断是否为真
   * 点击button，变更circle的antiAlias属性值为假
   * 获取circle的antiAlias属性判断是否为假
   */
  defineTest('circleAntiAliasTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("circleAntiAliasTestDemo running")

    let driver: Tester = Tester.create()
    let circle: Component = await driver.findComponent(Matcher.create().id('circleAntiAlias').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CircleAntiAlias').enabled(true))

    let antiAlias1: string = await circle.getInspectorInfo()
    assertTrue(JSON.parse(antiAlias1).$attrs.antiAlias)

    await button.tap()
    let antiAlias2: string = await circle.getInspectorInfo()
    assertFalse(JSON.parse(antiAlias2).$attrs.antiAlias)
  }, 0)
}