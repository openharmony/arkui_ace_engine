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

export default async function ellipseFillOpacityTest() {
  /*
   * Ellipse组件 fillOpacity属性
   * 找到画面id为ellipseFillOpacity1,ellipseFillOpacity2的Circle组件
   * 找到画面文本为EllipseFillOpacity的Button组件
   * 获取ellipse1的fillOpacity属性与期待值0.5比对
   * 获取ellipse2的fillOpacity属性与期待值0.0比对
   * 点击button2，变更ellipse2的fillOpacity属性值为'20px'
   * 获取ellipse2的fillOpacity属性与期待值1.0比对
   */
  defineTest('ellipseFillOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("ellipseFillOpacityTestDemo running")
    let driver: Tester = Tester.create()
    let ellipse1: Component = await driver.findComponent(Matcher.create().id('ellipseFillOpacity1').enabled(true))
    let ellipse2: Component = await driver.findComponent(Matcher.create().id('ellipseFillOpacity2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('EllipseFillOpacity').enabled(true))

    let fillOpacity1: string = await ellipse1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity1).$attrs.fillOpacity, '0.500000')

    let fillOpacity2: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity2).$attrs.fillOpacity, '0.000000')

    await button.tap()
    let fillOpacity3: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity3).$attrs.fillOpacity, '1.000000')
  }, 0)
}