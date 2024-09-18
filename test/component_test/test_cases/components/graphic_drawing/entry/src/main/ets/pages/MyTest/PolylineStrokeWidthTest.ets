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

export default async function polylineStrokeWidthTest() {
  /*
   * Polyline组件 strokeWidth属性
   * 找到画面id为polylineStrokeWidth1,polylineStrokeWidth2的Polyline组件
   * 找到画面文本为PolylineStrokeWidth的Button组件
   * 获取polyline1的strokeWidth属性与期待值'3'比对
   * 获取polyline2的strokeWidth属性与期待值'1'比对
   * 点击button,变更polyline2的strokeWidth属性值为-5
   * 获取polyline2的strokeWidth属性与期待值-5比对
   */
  defineTest('polylineStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let polyline1: Component = await driver.findComponent(Matcher.create().id('polylineStrokeWidth1').enabled(true))
    let polyline2: Component = await driver.findComponent(Matcher.create().id('polylineStrokeWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolylineStrokeWidth').enabled(true))

    let strokeWidth1: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, $r('app.string.stroke_width'))

    let strokeWidth2: string = await polyline2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, '1')

    await button.tap()
    let strokeWidth3: string = await polyline2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, 1)
  }, 0)
}