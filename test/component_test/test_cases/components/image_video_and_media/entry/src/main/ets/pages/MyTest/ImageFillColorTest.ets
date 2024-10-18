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

export default async function imageFillColorTest() {
  /*
* Image组件 FillColor属性
* 找到画面id为imageFillColor1,imageFillColor2的Image组件
* 找到画面文本为ImageFillColor1,ImageFillColor2的Button组件
* 获取image1的FillColor属性与期待值#FF008000比对
* 获取image2的FillColor属性与期待值$r('app.color.image_fill_color'))比对
* 点击button1，变更image1的Alt属性值为'#0000ff'
* 获取image1的FillColor属性与期待值'#0000ff'比对
* 点击button2，变更image1的Alt属性值为0x000000
* 获取image1的FillColor属性与期待值0x000000比对
*/
  defineTest('imageFillColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageFillColorTestDemo running")
    let driver: Tester = Tester.create()
    let image1: Component = await driver.findComponent(Matcher.create().id('imageFillColor1').enabled(true))
    let image2: Component = await driver.findComponent(Matcher.create().id('imageFillColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageFillColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageFillColor2').enabled(true))
    let fillColor1: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(fillColor1).$attrs.fillColor, '#FF008000')
    let fillColor2: string = await image2.getInspectorInfo()
    assertEqual(JSON.parse(fillColor2).$attrs.fillColor, $r('app.color.image_fill_color'))
    await button1.tap()
    let fillColor3: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(fillColor3).$attrs.fillColor, '#FF0000FF')
    await button2.tap()
    let fillColor4: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(fillColor4).$attrs.fillColor, '#FF000000')
  }, 0)
}