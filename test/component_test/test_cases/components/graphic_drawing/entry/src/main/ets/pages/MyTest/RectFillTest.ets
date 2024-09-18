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

export default async function rectFillTest() {
  /*
   * Rect组件 fill属性
   * 找到画面id为rectFill1,rectFill2的Rect组件
   * 找到画面文本为RectFill1,RectFill2的Button组件
   * 获取rect1的fill属性与期待值$r('app.color.color_blue')比对
   * 点击button1,变更rect1的fill属性值为0xffc0e6
   * 获取rect1的fill属性与期待值0xffc0e6比对
   * 获取rect2的fill属性与期待值'rgb(255,203,233)'比对
   * 点击button2,变更rect2的fill属性值为Color.Pink
   * 获取rect2的fill属性与期待值Color.Pink比对
   */
  defineTest('rectFillTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rectFillTestDemo running")
    let driver: Tester = Tester.create()
    let rect1: Component = await driver.findComponent(Matcher.create().id('rectFill1').enabled(true))
    let rect2: Component = await driver.findComponent(Matcher.create().id('rectFill2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('RectFill1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('RectFill2').enabled(true))

    let fill1: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(fill1).$attrs.fill, $r('app.color.color_blue'))

    await button1.tap()
    let fill2: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(fill2).$attrs.fill, '#FFFFC0E6')

    let fill3: string = await rect2.getInspectorInfo()
    assertEqual(JSON.parse(fill3).$attrs.fill, '#FFFFCBE9')

    await button2.tap()
    let fill4: string = await rect2.getInspectorInfo()
    assertEqual(JSON.parse(fill4).$attrs.fill.toLowerCase(), Color.Pink)
  }, 0)
}