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

export default async function pathStrokeOpacityTest() {
  /*
   * Path组件 strokeOpacity属性
   * 找到画面id为pathStrokeOpacity1,pathStrokeOpacity1的Path组件
   * 找到画面文本为PathStrokeOpacity的Button组件
   * 获取path1的strokeOpacity属性与期待值0.0比对
   * 点击button，变更path1的strokeOpacity属性值为'5px'
   * 获取path1的strokeOpacity属性与期待值1.0比对
   * 获取path2的strokeOpacity属性与期待值'0.8'比对
   */
  defineTest('pathStrokeOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("pathStrokeOpacityTestDemo running")
    let driver: Tester = Tester.create()
    let path1: Component = await driver.findComponent(Matcher.create().id('pathStrokeOpacity1').enabled(true))
    let path2: Component = await driver.findComponent(Matcher.create().id('pathStrokeOpacity2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PathStrokeOpacity').enabled(true))

    let strokeOpacity1: string = await path1.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity1).$attrs.strokeOpacity, '0.000000')

    await button.tap()
    let strokeOpacity2: string = await path1.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity2).$attrs.strokeOpacity, '1.000000')

    let strokeOpacity3: string = await path2.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity3).$attrs.strokeOpacity, $r('app.string.stroke_opacity'))
  }, 0)
}