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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function imageSpanObjectFitTest() {
  /*
   * ImageSpan组件 ObjectFit属性
   * 找到画面id为imageSpanObjectFit1，imageSpanObjectFit2,imageSpanObjectFit3的ImageSpan组件
   * 找到画面文本为ImageSpanObjectFit1,ImageSpanObjectFit2,ImageSpanObjectFit3的Button组件
   * 获取imageSpan1的ObjectFit属性与期待值ImageFit.Contain比对
   * 获取imageSpan2的ObjectFit属性与期待值ImageFit.Cover比对
   * 获取imageSpan3的ObjectFit属性与期待值ImageFit.Auto比对
   * 点击button1，变更imageSpan3的ObjectFit属性值为ImageFit.Fill
   * 获取imageSpan3的ObjectFit属性与期待值ImageFit.Fill比对
   * 点击button2，变更imageSpan3的ObjectFit属性值为ImageFit.ScaleDown
   * 获取imageSpan3的ObjectFit属性与期待值ImageFit.ScaleDown比对
   * 点击button3，变更imageSpan3的ObjectFit属性值为ImageFit.None
   * 获取imageSpan3的ObjectFit属性与期待值ImageFit.None比对
   */
  defineTest('imageSpanObjectFitTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageSpanObjectFitTestDemo running")
    let driver: Tester = Tester.create()
    let imageSpan1: Component = await driver.findComponent(Matcher.create().id('imageSpanObjectFit1').enabled(true))
    let imageSpan2: Component = await driver.findComponent(Matcher.create().id('imageSpanObjectFit2').enabled(true))
    let imageSpan3: Component = await driver.findComponent(Matcher.create().id('imageSpanObjectFit3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageSpanObjectFit1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageSpanObjectFit2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ImageSpanObjectFit3').enabled(true))

    let objectFit1: string = await imageSpan1.getInspectorInfo()
    assertEqual(JSON.parse(objectFit1).$attrs.objectFit, 'ImageFit.Contain')
    let objectFit2: string = await imageSpan2.getInspectorInfo()
    assertEqual(JSON.parse(objectFit2).$attrs.objectFit, 'ImageFit.Cover')
    let objectFit3: string = await imageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(objectFit3).$attrs.objectFit, 'ImageFit.Auto')

    await button1.tap()
    let objectFit4: string = await imageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(objectFit4).$attrs.objectFit, 'ImageFit.Fill')
    await button2.tap()
    let objectFit5: string = await imageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(objectFit5).$attrs.objectFit, 'ImageFit.ScaleDown')
    await button3.tap()
    let objectFit6: string = await imageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(objectFit6).$attrs.objectFit, 'ImageFit.None')
  }, 0)
}