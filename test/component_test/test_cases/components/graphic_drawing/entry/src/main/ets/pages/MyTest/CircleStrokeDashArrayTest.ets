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

import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function circleStrokeDashArrayTest() {
  /*
   * Circle组件 StrokeDashArray属性
   * 找到画面id为circleStrokeDashArray的Circle组件
   * 找到画面文本为CircleStrokeDashArray的Button组件
   * 获取circle的StrokeDashArray属性与期待值[1,2]比对
   * 点击button，变更circle的StrokeDashArray属性值为[10,20]
   * 获取circle的StrokeDashArray属性与期待值[10,20]比对
   */
  defineTest('circleStrokeDashArrayTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("circleStrokeDashArrayTestDemo running")

    let driver: Tester = Tester.create()
    let circle: Component = await driver.findComponent(Matcher.create().id('circleStrokeDashArray').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CircleStrokeDashArray').enabled(true))

    let strokeDashArray1: string = await circle.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashArray1).$attrs.strokeDashArray[0], '1.00vp')
    assertEqual(JSON.parse(strokeDashArray1).$attrs.strokeDashArray[1], '2.00vp')

    await button.tap()
    let strokeDashArray2: string = await circle.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashArray2).$attrs.strokeDashArray[0], '10.00vp')
    assertEqual(JSON.parse(strokeDashArray2).$attrs.strokeDashArray[1], '20.00vp')
  }, 0)
}