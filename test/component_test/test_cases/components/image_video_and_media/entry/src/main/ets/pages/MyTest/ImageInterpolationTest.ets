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

export default async function imageInterpolationTest() {
  /*
* Image组件 Interpolation属性
* 找到画面id为imageInterpolation的Image组件
* 找到画面文本为ImageCopyOption1,ImageInterpolation2,ImageInterpolation3的Button组件
* 获取image的Interpolation属性与期待值ImageInterpolation.None比对
* 点击button1，变更image的ImageInterpolation属性值为ImageInterpolation.Low
* 获取image的Interpolation属性与期待值ImageInterpolation.Low比对
* 点击button2，变更image的ImageInterpolation属性值为ImageInterpolation.Medium
* 获取image的Interpolation属性与期待值ImageInterpolation.Medium比对
* 点击button3，变更image的ImageInterpolation属性值为ImageInterpolation.High
* 获取image的Interpolation属性与期待值ImageInterpolation.High比对
*/
  defineTest('imageInterpolationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageInterpolationTestDemo running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().id('imageInterpolation').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageInterpolation1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageInterpolation2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ImageInterpolation3').enabled(true))
    let interpolation1: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(interpolation1).$attrs.interpolation, 'ImageInterpolation.None')
    await button1.tap()
    let interpolation2: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(interpolation2).$attrs.interpolation, 'ImageInterpolation.Low')
    await button2.tap()
    let interpolation3: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(interpolation3).$attrs.interpolation, 'ImageInterpolation.Medium')
    await button3.tap()
    let interpolation4: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(interpolation4).$attrs.interpolation, 'ImageInterpolation.High')
  }, 0)
}