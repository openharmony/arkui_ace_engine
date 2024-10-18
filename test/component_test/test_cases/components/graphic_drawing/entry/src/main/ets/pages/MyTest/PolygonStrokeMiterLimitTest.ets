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

export default async function polygonStrokeMiterLimitTest() {
  /*
   * Polygon组件 strokeMiterLimit属性
   * 找到画面id为polygonStrokeMiterLimit的Polygon组件
   * 找到画面文本为PolygonStrokeMiterLimit1,PolygonStrokeMiterLimit2的Button组件
   * 获取polygon的strokeMiterLimit属性与期待值5比对
   * 点击button1，变更polygon的strokeMiterLimit属性值为'1.0'
   * 获取polygon的strokeMiterLimit属性与期待值'1.0'比对
   * 点击button2，变更polygon的strokeMiterLimit属性值为4
   * 获取polygon的strokeMiterLimit属性与期待值4比对
   */
  defineTest('polygonStrokeMiterLimitTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polygonStrokeMiterLimitTestDemo running")
    let driver: Tester = Tester.create()
    let polygon: Component = await driver.findComponent(Matcher.create().id('polygonStrokeMiterLimit').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PolygonStrokeMiterLimit1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PolygonStrokeMiterLimit2').enabled(true))

    let strokeMiterLimit1: string = await polygon.getInspectorInfo()
    assertEqual(JSON.parse(strokeMiterLimit1).$attrs.strokeMiterLimit, '5.000000')

    await button1.tap()
    let strokeMiterLimit2: string = await polygon.getInspectorInfo()
    assertEqual(JSON.parse(strokeMiterLimit2).$attrs.strokeMiterLimit, '1.000000')

    await button2.tap()
    let strokeMiterLimit3: string = await polygon.getInspectorInfo()
    assertEqual(JSON.parse(strokeMiterLimit3).$attrs.strokeMiterLimit, '4.000000')
  }, 0)
}