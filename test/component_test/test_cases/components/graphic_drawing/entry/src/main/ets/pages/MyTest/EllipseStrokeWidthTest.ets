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

export default async function ellipseStrokeWidthTest() {
  /*
   * Ellipse组件 strokeWidth属性
   * 找到画面id为ellipseStrokeWidth1,ellipseStrokeWidth2的Ellipse组件
   * 找到画面文本为EllipseStrokeWidth的Button组件
   * 获取ellipse1的strokeWidth属性与期待值2比对
   * 获取ellipse2的strokeWidth属性与期待值'3'比对
   * 点击button，变更circle2的fill属性值为'1px'
   * 获取ellipse2的strokeWidth属性与期待值'1'比对
   */
  defineTest('ellipseStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("ellipseStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let ellipse1: Component = await driver.findComponent(Matcher.create().id('ellipseStrokeWidth1').enabled(true))
    let ellipse2: Component = await driver.findComponent(Matcher.create().id('ellipseStrokeWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('EllipseStrokeWidth').enabled(true))

    let strokeWidth1: string = await ellipse1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, 2)

    let strokeWidth2: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, $r('app.string.stroke_width'))

    await button.tap()
    let strokeWidth3: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, '1')
  }, 0)
}