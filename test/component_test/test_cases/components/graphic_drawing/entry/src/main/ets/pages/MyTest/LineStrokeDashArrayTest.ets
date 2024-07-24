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

export default async function lineStrokeDashTest() {
  /*
   * Line组件 strokeDash属性
   * 找到画面id为lineStrokeDash的Line组件
   * 找到画面文本为LineStrokeDash的Button组件
   * 获取line的strokeDash属性与期待值['50.00vp','10.00vp','20.00vp','30.00vp']比对
   * 点击button，变更line的strokeDash属性值为['60.00vp', '20.00vp', '30.00vp', '40.00vp']
   * 获取line的strokeDash属性与期待值['60.00vp', '20.00vp', '30.00vp', '40.00vp']比对
   */
  defineTest('lineStrokeDashTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("lineStrokeDashTestDemo running")
    let driver: Tester = Tester.create()
    let line: Component = await driver.findComponent(Matcher.create().id('lineStrokeDashArray').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('LineStrokeDashArray').enabled(true))

    let strokeDashArray1: string = await line.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashArray1).$attrs.strokeDashArray[0], '50.00vp')
    assertEqual(JSON.parse(strokeDashArray1).$attrs.strokeDashArray[1], '10.00vp')
    assertEqual(JSON.parse(strokeDashArray1).$attrs.strokeDashArray[2], '20.00vp')
    assertEqual(JSON.parse(strokeDashArray1).$attrs.strokeDashArray[3], '30.00vp')

    await button.tap()
    let strokeDashArray2: string = await line.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashArray2).$attrs.strokeDashArray[0], '60.00vp')
    assertEqual(JSON.parse(strokeDashArray2).$attrs.strokeDashArray[1], '20.00vp')
    assertEqual(JSON.parse(strokeDashArray2).$attrs.strokeDashArray[2], '30.00vp')
    assertEqual(JSON.parse(strokeDashArray2).$attrs.strokeDashArray[3], '40.00vp')
  }, 0)
}