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

export default async function polygonStrokeTest() {
  /*
 * Polygon组件 stroke属性
 * 找到画面id为polygonStroke1,polygonStroke2,polygonStroke3的Polygon组件
 * 找到画面文本为PolygonStroke的Button组件
 * 获取polygon1的stroke属性与期待值Color.Blue比对
 * 点击button，变更polygon1的stroke属性值为'rgb(255,0,0)'
 * 获取polygon1的stroke属性与期待值'rgb(255,0,0)'比对
 * 获取polygon2的stroke属性与期待值0x00FF00比对
 * 获取polygon3的stroke属性与期待值$r('app.color.color_blue')比对
 */
  defineTest('polygonStrokeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polygonStrokeTestDemo running")
    let driver: Tester = Tester.create()
    let polygon1: Component = await driver.findComponent(Matcher.create().id('polygonStroke1').enabled(true))
    let polygon2: Component = await driver.findComponent(Matcher.create().id('polygonStroke2').enabled(true))
    let polygon3: Component = await driver.findComponent(Matcher.create().id('polygonStroke3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolygonStroke').enabled(true))

    let stroke: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(stroke).$attrs.stroke.toLowerCase(), Color.Blue)
    await button.tap()
    let stroke1: string = await polygon1.getInspectorInfo()
    assertEqual(JSON.parse(stroke1).$attrs.stroke, '#FFFF0000')
    let stroke2: string = await polygon2.getInspectorInfo()
    assertEqual(JSON.parse(stroke2).$attrs.stroke, '#FF00FF00')
    let stroke3: string = await polygon3.getInspectorInfo()
    assertEqual(JSON.parse(stroke3).$attrs.stroke, $r('app.color.color_blue'))
  }, 0)
}