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

export default async function circleFillSampleTest() {
  /*
   * Circle组件 Fill属性
   * 找到画面id为circleFill1,circleFill2的Circle组件
   * 找到画面文本为CircleFill1,CircleFill2的Button组件
   * 获取circle1的fill属性与期待值#FFFF0000比对
   * 点击button1，变更circle1的fill属性值为'#FFF07DDF'
   * 获取circle1的fill属性与期待值'#FFF07DDF'比对
   * 获取circle2的fill属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   * 点击button2，变更circle2的fill属性值为Color.Blue
   * 获取circle2的fill属性与期待值Color.Blue比对
   */
  defineTest('circleFillSampleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("circleFillSampleTestDemo running")

    let driver: Tester = Tester.create()
    let circle1: Component = await driver.findComponent(Matcher.create().id('circleFill1').enabled(true))
    let circle2: Component = await driver.findComponent(Matcher.create().id('circleFill2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CircleFill1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CircleFill2').enabled(true))

    let fill1: string = await circle1.getInspectorInfo()
    assertEqual(JSON.parse(fill1).$attrs.fill, '#FFFF0000')
    await button1.tap()
    let fill2: string = await circle1.getInspectorInfo()
    assertEqual(JSON.parse(fill2).$attrs.fill, '#FFF07DDF')
    let fill3: string = await circle2.getInspectorInfo()
    assertEqual(JSON.parse(fill3).$attrs.fill, $r('sys.color.ohos_id_color_text_hyperlink'))
    await button2.tap()
    let fill4: string = await circle2.getInspectorInfo()
    assertEqual(JSON.parse(fill4).$attrs.fill.toLowerCase(), Color.Blue)
  }, 0)
}