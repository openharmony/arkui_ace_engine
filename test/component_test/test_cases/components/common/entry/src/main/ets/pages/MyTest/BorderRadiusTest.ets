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

export default async function borderRadiusTest() {
  /*
  * TextTimer、TextPicker组件 borderRadius属性
  * 找到画面id为textTimer1、textTimer2、textPicker1、textPicker2的TextTimer、TextPicker组件
  * 找到画面文本为ButtonBorderRadius1、ButtonBorderRadius2的Button组件
  * 获取textTimer1的borderRadius属性与期待值'10px'比对
  * 获取textTimer2的borderRadius属性与期待值10比对
  * 获取textPicker1的borderRadius属性的topLeft参数与期待值'100'比对
  * 获取textPicker1的borderRadius属性的topRight参数与期待值'100'比对
  * 获取textPicker1的borderRadius属性的bottomLeft参数与期待值'100'比对
  * 获取textPicker1的borderRadius属性的bottomRight参数与期待值'100'比对
  * 获取textPicker2的borderRadius属性的topLeft参数与期待值30比对
  * 获取textPicker2的borderRadius属性的topRight参数与期待值30比对
  * 获取textPicker2的borderRadius属性的bottomLeft参数与期待值30比对
  * 获取textPicker2的borderRadius属性的bottomRight参数与期待值30比对
  * 点击button1，变更textTimer2的borderRadius属性的topLeft、topRight、topRight、topRight参数为$r('app.string.border_radius')
  * 获取textTimer2的borderRadius属性的参数与期待值$r('app.string.border_radius')比对
  * 点击button2，变更textTimer2的borderRadius属性的topLeft、topRight、topRight、topRight参数为$r('app.string.border_radius')
  * 获取textPicker2的borderRadius属性的topLeft参数与期待值$r('app.string.border_radius')比对
  * 获取textPicker2的borderRadius属性的topRight参数与期待值$r('app.string.border_radius')比对
  * 获取textPicker2的borderRadius属性的bottomLeft参数与期待值$r('app.string.border_radius')比对
  * 获取textPicker2的borderRadius属性的bottomRight参数与期待值$r('app.string.border_radius')比对
  */
  defineTest('borderRadiusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("borderRadiusTestDemo running")
    let driver: Tester = Tester.create()
    let textTimer1: Component = await driver.findComponent(Matcher.create().id('textTimer1').enabled(true))
    let textTimer2: Component = await driver.findComponent(Matcher.create().id('textTimer2').enabled(true))
    let textPicker1: Component = await driver.findComponent(Matcher.create().id('textPicker1').enabled(true))
    let textPicker2: Component = await driver.findComponent(Matcher.create().id('textPicker2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBorderRadius1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBorderRadius2').enabled(true))
    let borderRadius1: string = await textTimer1.getInspectorInfo()
    assertEqual(JSON.parse(borderRadius1).$attrs.borderRadius, '10.00px')

    let borderRadius2: string = await textTimer2.getInspectorInfo()
    assertEqual(JSON.parse(borderRadius2).$attrs.borderRadius, '10.00vp')

    let borderRadius3: string = await textPicker1.getInspectorInfo()
    assertEqual(JSON.parse(borderRadius3)
      .$attrs
      .borderRadius
      .topLeft, '100.00vp')
    assertEqual(JSON.parse(borderRadius3)
      .$attrs
      .borderRadius
      .topRight, '100.00vp')
    assertEqual(JSON.parse(borderRadius3)
      .$attrs
      .borderRadius
      .bottomLeft, '100.00vp')
    assertEqual(JSON.parse(borderRadius3)
      .$attrs
      .borderRadius
      .bottomRight, '100.00vp')

    let borderRadius4: string = await textPicker2.getInspectorInfo()
    assertEqual(JSON.parse(borderRadius4)
      .$attrs
      .borderRadius
      .topLeft, '30.00vp')
    assertEqual(JSON.parse(borderRadius4)
      .$attrs
      .borderRadius
      .topRight, '30.00vp')
    assertEqual(JSON.parse(borderRadius4)
      .$attrs
      .borderRadius
      .bottomLeft, '30.00vp')
    assertEqual(JSON.parse(borderRadius4)
      .$attrs
      .borderRadius
      .bottomRight, '30.00vp')

    await button1.tap()
    let borderRadius5: string = await textTimer2.getInspectorInfo()
    assertEqual(JSON.parse(borderRadius5).$attrs.borderRadius, $r('app.string.border_radius'))

    await button2.tap()
    let borderRadius6: string = await textPicker2.getInspectorInfo()
    assertEqual(JSON.parse(borderRadius6)
      .$attrs
      .borderRadius
      .topLeft, $r('app.string.border_radius'))
    assertEqual(JSON.parse(borderRadius6)
      .$attrs
      .borderRadius
      .topRight, $r('app.string.border_radius'))
    assertEqual(JSON.parse(borderRadius6)
      .$attrs
      .borderRadius
      .bottomLeft, $r('app.string.border_radius'))
    assertEqual(JSON.parse(borderRadius6)
      .$attrs
      .borderRadius
      .bottomRight, $r('app.string.border_radius'))
  }, 0)
}