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
* Image组件 ObjectRepeat属性
* 找到画面id为imageObjectRepeat1,imageObjectRepeat2的Image组件
* 找到画面文本为ImageObjectRepeat1,ImageObjectRepeat2的Button组件
* 获取image1的ObjectRepeat属性与期待值ImageRepeat.NoRepeat比对
* 获取image2的ObjectRepeat属性与期待值ImageRepeat.XY比对
* 点击button1，变更image的ObjectRepeat属性值为ImageRepeat.X
* 获取image的ObjectRepeat属性与期待值ImageRepeat.X比对
* 点击button2，变更image的ObjectRepeat属性值为ImageRepeat.Y
* 获取image的ObjectRepeat属性与期待值ImageRepeat.Y比对
*/

export default async function imageObjectRepeatTest() {
  defineTest('imageObjectRepeatTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageObjectRepeatTestDemo running")
    let driver: Tester = Tester.create()
    let image1: Component = await driver.findComponent(Matcher.create().id('imageObjectRepeat1').enabled(true))
    let image2: Component = await driver.findComponent(Matcher.create().id('imageObjectRepeat2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageObjectRepeat1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageObjectRepeat2').enabled(true))
    let imageRepeat1: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(imageRepeat1).$attrs.objectRepeat, 'ImageRepeat.NoRepeat')
    let imageRepeat2: string = await image2.getInspectorInfo()
    assertEqual(JSON.parse(imageRepeat2).$attrs.objectRepeat, 'ImageRepeat.XY')
    await button1.tap()
    let imageRepeat3: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(imageRepeat3).$attrs.objectRepeat, 'ImageRepeat.X')
    await button2.tap()
    let imageRepeat4: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(imageRepeat4).$attrs.objectRepeat, 'ImageRepeat.Y')
  }, 0)
}