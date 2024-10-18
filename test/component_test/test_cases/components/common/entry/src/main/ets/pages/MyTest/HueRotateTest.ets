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
import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function hueRotateTest() {
  /*
  * circle组件 hueRotate属性
  * 找到画面id为circle1、circle2、circle3的menu组件
  * 找到画面文本为 ButtonHueRotate1、ButtonHueRotate2 的Button组件
  * 获取circle1的hueRotate属性与期待值0比对
  * 获取circle2的hueRotate属性与期待值10比对
  * 获取circle3的hueRotate属性与期待值0比对
  * 点击button1，变更circle1的hueRotate属性值为'90deg'
  * 获取circle1的hueRotate属性与期待值'90deg'比对
  * 点击button2，变更circle3的hueRotate属性值为180
  * 获取circle3的hueRotate属性与期待值180比对
  * 点击button2，变更circle3的hueRotate属性值为360
  * 获取circle3的hueRotate属性与期待值0比对
  */
  defineTest(' hueRotateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log(" hueRotateTestDemo running")
    let driver: Tester = Tester.create()
    let circle1: Component = await driver.findComponent(Matcher.create().id('circle1').enabled(true))
    let circle2: Component = await driver.findComponent(Matcher.create().id('circle2').enabled(true))
    let circle3: Component = await driver.findComponent(Matcher.create().id('circle3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonHueRotate1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonHueRotate2').enabled(true))
    let hueRotate1: string = await circle1.getInspectorInfo()
    assertEqual(JSON.parse(hueRotate1).$attrs.hueRotate, 0)
    let hueRotate2: string = await circle2.getInspectorInfo()
    assertEqual(JSON.parse(hueRotate2).$attrs.hueRotate, 10)
    let hueRotate3: string = await circle3.getInspectorInfo()
    assertEqual(JSON.parse(hueRotate3).$attrs.hueRotate, 0)
    await button1.tap()
    let hueRotate4: string = await circle1.getInspectorInfo()
    assertEqual(JSON.parse(hueRotate4).$attrs.hueRotate, 90)
    await button2.tap()
    let hueRotate5: string = await circle3.getInspectorInfo()
    assertEqual(JSON.parse(hueRotate5).$attrs.hueRotate, 180)
    await button2.tap()
    let hueRotate6: string = await circle3.getInspectorInfo()
    assertEqual(JSON.parse(hueRotate6).$attrs.hueRotate, 0)
  }, 0)
}