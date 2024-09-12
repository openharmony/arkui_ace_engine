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

export default async function polygonStrokeWidthTest() {
  /*
   * Polygon组件 strokeWidth属性
   * 找到画面id为polygonStrokeWidth1,polygonStrokeWidth2的Polygon组件
   * 找到画面文本为CircleFill1,CircleFill2的Button组件
   * 获取polygon1的strokeWidth属性与期待值1.0比对
   * 点击button，变更polygon1的strokeWidth属性值为'5px'
   * 获取polygon1的strokeWidth属性与期待值'1.0'比对
   * 获取polygon2的strokeWidth属性与期待值3比对
   */
  defineTest('polygonStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polygonStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let polygon1: Component = await driver.findComponent(Matcher.create().id('polygonStrokeWidth1').enabled(true))
    let polygon2: Component = await driver.findComponent(Matcher.create().id('polygonStrokeWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolygonStrokeWidth').enabled(true))

    let strokeWidth1: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, 3)

    await button.tap()
    let strokeWidth2: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, 5)

    let strokeWidth3: string = await polygon2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, $r('app.string.stroke_width'))
  }, 0)
}