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

export default async function ellipseFillColorTest() {
  /*
 * Ellipse组件 fill属性
 * 找到画面id为ellipseFill1,ellipseFill2的Circle组件
 * 找到画面文本为EllipseFillColor1,EllipseFillColor2的Button组件
 * 获取ellipse1的fill属性与期待值Color.Red比对
 * 点击button1，变更ellipse1的fill属性值为0x0000ff
 * 获取ellipse1的fill属性与期待值0x0000ff比对
 * 获取ellipse2的fill属性与期待值'#FF0000'比对
 * 点击button2，变更ellipse2的fill属性值为'rgb(0,0,255)'
 * 获取ellipse2的fill属性与期待值'rgb(0,0,255)'比对
 */
  defineTest('ellipseFillColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("ellipseFillColorTestDemo running")
    let driver: Tester = Tester.create()
    let ellipse1: Component = await driver.findComponent(Matcher.create().id('ellipseFill1').enabled(true))
    let ellipse2: Component = await driver.findComponent(Matcher.create().id('ellipseFill2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('EllipseFill1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('EllipseFill2').enabled(true))

    let fill1: string = await ellipse1.getInspectorInfo()
    assertEqual(JSON.parse(fill1).$attrs.fill.toLowerCase(), Color.Red)

    await button1.tap()
    let fill2: string = await ellipse1.getInspectorInfo()
    assertEqual(JSON.parse(fill2).$attrs.fill, '#FF0000FF')

    let fill3: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(fill3).$attrs.fill, $r('app.color.color_red'))

    await button2.tap()
    let fill4: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(fill4).$attrs.fill, '#FF0000FF')
  }, 0)
}