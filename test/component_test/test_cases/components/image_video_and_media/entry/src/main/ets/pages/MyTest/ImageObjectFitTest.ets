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

/*
* Image组件 ObjectFit属性
* 找到画面id为imageObjectFit的Image组件
* 找到画面文本为ImageObjectFit1,ImageObjectFit2,ImageObjectFit3,ImageObjectFit4,ImageObjectFit5的Button组件
* 获取image的ObjectFit属性与期待值ImageFit.Auto比对
* 点击button1，变更image的ObjectFit属性值为ImageFit.Fill
* 获取image的ObjectFit属性与期待值ImageFit.Fill比对
* 点击button2，变更image的ObjectFit属性值为ImageFit.None
* 获取image的ObjectFit属性与期待值ImageFit.None比对
* 点击button3，变更image的ObjectFit属性值为ImageFit.Contain
* 获取image的ObjectFit属性与期待值ImageFit.Contain比对
* 点击button4，变更image的ObjectFit属性值为ImageFit.ScaleDown
* 获取image的ObjectFit属性与期待值ImageFit.ScaleDown比对
* 点击button5，变更image的ObjectFit属性值为ImageFit.Cover
* 获取image的ObjectFit属性与期待值ImageFit.Cover比对
*/

export default async function imageObjectFitTest() {
  defineTest('imageObjectFitTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageObjectFitTestDemo running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().id('imageObjectFit').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageObjectFit1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageObjectFit2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ImageObjectFit3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('ImageObjectFit4').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('ImageObjectFit5').enabled(true))
    let objectFit1: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(objectFit1).$attrs.objectFit, 'ImageFit.Auto')
    await button1.tap()
    let objectFit2: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(objectFit2).$attrs.objectFit, 'ImageFit.Fill')
    await button2.tap()
    let objectFit3: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(objectFit3).$attrs.objectFit, 'ImageFit.None')
    await button3.tap()
    let objectFit4: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(objectFit4).$attrs.objectFit, 'ImageFit.Contain')
    await button4.tap()
    let objectFit5: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(objectFit5).$attrs.objectFit, 'ImageFit.ScaleDown')
    await button5.tap()
    let objectFit6: string = await image.getInspectorInfo()
    assertEqual(JSON.parse(objectFit6).$attrs.objectFit, 'ImageFit.Cover')
  }, 0)
}