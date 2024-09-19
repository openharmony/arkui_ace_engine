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

import {
  assertContain,
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function circleStrokeWidthTest() {
  /*
 * Circle组件 StrokeWidth属性
 * 找到画面id为circleStrokeWidth1,circleStrokeWidth2的Circle组件
 * 找到画面文本为CircleStrokeWidth的Button组件
 * 获取circle1的StrokeWidth属性与期待值10比对
 * 获取circle2的StrokeWidth属性与期待值10比对
 * 点击button，变更circle2的StrokeWidth属性值为$r('app.string.stroke_width')
 * 获取circle2的StrokeWidth属性与期待值3比对
 */
  defineTest('circleStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("circleStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let circle1: Component = await driver.findComponent(Matcher.create().id('circleStrokeWidth1').enabled(true))
    let circle2: Component = await driver.findComponent(Matcher.create().id('circleStrokeWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CircleStrokeWidth').enabled(true))

    let strokeWidth1: string = await circle1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, 10)

    let strokeWidth2: string = await circle2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, 10)
    await button.tap()
    let strokeWidth3: string = await circle2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, $r('app.string.stroke_width'))
  }, 0)
}