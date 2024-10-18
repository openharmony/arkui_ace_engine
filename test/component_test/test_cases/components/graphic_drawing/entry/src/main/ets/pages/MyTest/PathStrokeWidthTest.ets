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

export default async function pathStrokeWidthTest() {
  /*
   * Path组件 strokeWidth属性
   * 找到画面id为pathStrokeWidth1,pathStrokeWidth2的Path组件
   * 找到画面文本为PathStrokeWidth的Button组件
   * 获取path1的strokeWidth属性与期待值1比对
   * 点击button，变更path1的strokeWidth属性值为'10px'
   * 获取path1的strokeWidth属性与期待值'1'比对
   * 获取path2的strokeWidth属性与期待值'3'比对
   */
  defineTest('pathStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("pathStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let path1: Component = await driver.findComponent(Matcher.create().id('pathStrokeWidth1').enabled(true))
    let path2: Component = await driver.findComponent(Matcher.create().id('pathStrokeWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PathStrokeWidth').enabled(true))

    let strokeWidth1: string = await path1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, 1)

    await button.tap()
    let strokeWidth2: string = await path1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, '1')

    let strokeWidth3: string = await path2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, $r('app.string.stroke_width'))
  }, 0)
}