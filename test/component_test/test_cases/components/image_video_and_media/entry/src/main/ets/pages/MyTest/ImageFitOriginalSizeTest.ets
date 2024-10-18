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
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function imageFitOriginalSizeTest() {
  /*
* Image组件 FitOriginalSize属性
* 找到画面id为imageFitOriginalSize的Image组件
* 找到画面文本为ImageFitOriginalSize1的Button组件
* 获取image的FitOriginalSize属性与期待值true比对
* 点击button，变更image的FitOriginalSize属性值为false
* 获取image的FitOriginalSize属性与期待值false比对
*/
  defineTest('imageFitOriginalSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageFitOriginalSizeTestDemo running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().id('imageFitOriginalSize').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ImageFitOriginalSize1').enabled(true))
    let fitOriginalSize1: string = await image.getInspectorInfo()
    assertTrue(JSON.parse(fitOriginalSize1).$attrs.fitOriginalSize)
    await button.tap()
    let fitOriginalSize2: string = await image.getInspectorInfo()
    assertFalse(JSON.parse(fitOriginalSize2).$attrs.fitOriginalSize)
  }, 0)
}