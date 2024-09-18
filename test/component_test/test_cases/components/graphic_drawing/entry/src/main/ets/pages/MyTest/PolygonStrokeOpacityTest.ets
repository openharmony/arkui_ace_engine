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

import { assertEqual, assertContain, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function polygonStrokeOpacityTest() {
  /*
   * Polygon组件 strokeOpacity属性
   * 找到画面id为polygonStrokeOpacity1,polygonStrokeOpacity2的Polygon组件
   * 找到画面文本为PolygonStrokeOpacity的Button组件
   * 获取polygon1的strokeOpacity属性与期待值0.0比对
   * 点击button，变更polygon1的strokeOpacity属性值为'10px'
   * 获取polygon1的strokeOpacity属性与期待值'1.0'比对
   * 获取polygon2的strokeOpacity属性与期待值'0.8'比对
   */
  defineTest('polygonStrokeOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polygonStrokeOpacityTestDemo running")
    let driver: Tester = Tester.create()
    let polygon1: Component = await driver.findComponent(Matcher.create().id('polygonStrokeOpacity1').enabled(true))
    let polygon2: Component = await driver.findComponent(Matcher.create().id('polygonStrokeOpacity2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolygonStrokeOpacity').enabled(true))

    let fillOpacity1: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity1).$attrs.fillOpacity, '1.000000')
    await button.tap()
    let fillOpacity2: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity2).$attrs.fillOpacity, '1.000000')

    let fillOpacity3: string = await polygon2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity3).$attrs.fillOpacity, $r('app.string.stroke_opacity'))
  }, 0)
}