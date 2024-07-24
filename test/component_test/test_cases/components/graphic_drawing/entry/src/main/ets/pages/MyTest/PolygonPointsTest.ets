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

export default async function polygonPointsTest() {
  /*
   * Polygon组件 points属性
   * 找到画面id为polygonPoints的Polygon组件
   * 找到画面文本为PolygonPoints的Button组件
   * 获取polygon的points属性与期待值[5,5]比对
   * 点击button，变更polygon的points属性值为[10,10]
   * 获取polygon的points属性与期待值[10,10]比对
   */
  defineTest('polygonPointsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polygonPointsTestDemo running")
    let driver: Tester = Tester.create()
    let polygon: Component = await driver.findComponent(Matcher.create().id('polygonPoints').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolygonPoints').enabled(true))

    let points1: string = await polygon.getInspectorInfo()
    assertEqual(JSON.parse(points1).$attrs.points.Array, [5, 5])

    await button.tap()
    let points2: string = await polygon.getInspectorInfo()
    assertEqual(JSON.parse(points2).$attrs.points.Array, [10, 10])
  }, 0)
}