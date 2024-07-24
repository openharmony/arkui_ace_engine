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

export default async function circleStrokeOpacityTest() {
  /*
 * Circle组件 StrokeOpacity属性
 * 找到画面id为circleStrokeOpacity的Circle组件
 * 找到画面文本为CircleStrokeOpacity1,CircleStrokeOpacity2的Button组件
 * 获取circle的StrokeOpacity属性与期待值0.000000比对
 * 点击button1，变更circle的StrokeOpacity属性值为$r('app.string.stroke_opacity')
 * 获取circle的StrokeOpacity属性与期待值0.800000比对
 * 点击button2，变更circle的StrokeOpacity属性值为'10px'
 * 获取circle的StrokeOpacity属性与期待值1.000000比对
 */
  defineTest('circleStrokeOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("circleStrokeOpacityTestDemo running")

    let driver: Tester = Tester.create()
    let circle: Component = await driver.findComponent(Matcher.create().id('circleStrokeOpacity').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CircleStrokeOpacity1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CircleStrokeOpacity2').enabled(true))

    let strokeOpacity1: string = await circle.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity1).$attrs.strokeOpacity, '0.000000')
    await button2.tap()
    let strokeOpacity3: string = await circle.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity3).$attrs.strokeOpacity, '1.000000')

    await button1.tap()
    let strokeOpacity2: string = await circle.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity2).$attrs.strokeOpacity, $r('app.string.stroke_opacity'))
  }, 0)
}