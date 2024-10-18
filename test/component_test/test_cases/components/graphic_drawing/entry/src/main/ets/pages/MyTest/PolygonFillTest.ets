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

export default async function polygonFillTest() {
  /*
   * Polygon组件 fill属性
   * 找到画面id为polygonFill1,polygonFill2,polygonFill3的Polygon组件
   * 找到画面文本为PolygonFill的Button组件
   * 获取polygon1的fill属性与期待值Color.Green比对
   * 点击button，变更polygon1的fill属性值为0xff0000
   * 获取polygon1的fill属性与期待值#FFFF0000比对
   * 获取polygon2的fill属性与期待值'#FF00FF00'比对
   * 获取polygon3的fill属性与期待值$r('app.color.color_red')比对
   */
  defineTest('polygonFillTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polygonFillTestDemo running")
    let driver: Tester = Tester.create()
    let polygon1: Component = await driver.findComponent(Matcher.create().id('polygonFill1').enabled(true))
    let polygon2: Component = await driver.findComponent(Matcher.create().id('polygonFill2').enabled(true))
    let polygon3: Component = await driver.findComponent(Matcher.create().id('polygonFill3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PolygonFill').enabled(true))

    let fill1: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(fill1).$attrs.fill.toLowerCase(), Color.Green)

    await button1.tap()
    let fill2: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(fill2).$attrs.fill, '#FFFF0000')

    let fill3: string = await polygon2.getInspectorInfo()
    assertEqual(JSON.parse(fill3).$attrs.fill, '#FF00FF00')

    let fill4: string = await polygon3.getInspectorInfo()
    assertEqual(JSON.parse(fill4).$attrs.fill, $r('app.color.color_red'))
  }, 0)
}