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

export default async function polygonStrokeLineCapTest() {
  /*
   * Polygon组件 strokeLineCap属性
   * 找到画面id为polygonStrokeLineCap1,polygonStrokeLineCap2的Polygon组件
   * 找到画面文本为PolygonStrokeLineCap的Button组件
   * 获取polygon1的strokeLineCap属性与期待值LineCapStyle.Butt比对
   * 获取polygon2的strokeLineCap属性与期待值LineCapStyle.Round比对
   * 点击button，变更polygon2的strokeLineCap属性值为LineCapStyle.Square
   * 获取polygon2的strokeLineCap属性与期待值LineCapStyle.Square比对
   */
  defineTest('polygonStrokeLineCapTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polygonStrokeLineCapTestDemo running")
    let driver: Tester = Tester.create()
    let polygon1: Component = await driver.findComponent(Matcher.create().id('polygonStrokeLineCap1').enabled(true))
    let polygon2: Component = await driver.findComponent(Matcher.create().id('polygonStrokeLineCap2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolygonStrokeLineCap').enabled(true))

    let strokeLineCap1: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(strokeLineCap1).$attrs.strokeLineCap, 'LineCapStyle.Butt')

    let strokeLineCap2: string = await polygon2.getInspectorInfo()
    assertEqual(JSON.parse(strokeLineCap2).$attrs.strokeLineCap, 'LineCapStyle.Round')

    await button.tap()
    let strokeLineCap3: string = await polygon2.getInspectorInfo()
    assertEqual(JSON.parse(strokeLineCap3).$attrs.strokeLineCap, 'LineCapStyle.Square')
  }, 0)
}