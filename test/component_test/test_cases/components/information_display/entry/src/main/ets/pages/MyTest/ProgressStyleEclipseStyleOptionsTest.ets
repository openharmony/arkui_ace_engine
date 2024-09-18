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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

/*
* Progress组件 Style属性
* 找到画面id为progressStyleEclipseStyleOptions的Progress组件
* 找到画面文本为ProgressStyleEclipseStyleOptions的组件
* 获取progress的Style.EclipseStyleOptions.enableSmoothEffect属性与期待值True比对
* 点击button1，变更progress的Style.EclipseStyleOptions属性值为False
* 获取progress的Style.EclipseStyleOptions.enableSmoothEffect属性与期待值False比对
*/
export default async function progressStyleEclipseStyleOptionsTest() {
  defineTest('progressStyleEclipseStyleOptionsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressStyleEclipseStyleOptionsTestDemo running")
    let driver: Tester = Tester.create()
    let progress: Component =
      await driver.findComponent(Matcher.create().id('progressStyleEclipseStyleOptions').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('ProgressStyleEclipseStyleOptions').enabled(true))
    let styleEclipseStyleOptions1: string = await progress.getInspectorInfo()
    assertFalse(JSON.parse(styleEclipseStyleOptions1).$attrs.eclipseStyle == undefined)
    assertTrue(JSON.parse(styleEclipseStyleOptions1)
      .$attrs
      .eclipseStyle
      .enableSmoothEffect)
    await button.tap()
    let styleEclipseStyleOptions2: string = await progress.getInspectorInfo()
    assertFalse(JSON.parse(styleEclipseStyleOptions2)
      .$attrs
      .eclipseStyle
      .enableSmoothEffect)
  }, 0)
}