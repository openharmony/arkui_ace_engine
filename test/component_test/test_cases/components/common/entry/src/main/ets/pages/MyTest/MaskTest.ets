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

export default async function maskTest() {
  /*
  * text、image、textArea组件 mask属性
  * 找到画面id为textMask1、imageMask1、textAreaMask1的text、image、textArea组件
  * 找到画面文本为 ButtonTextMask1 ButtonTextMask2
  * ButtonTextMask3 ButtonTextMask4 ButtonTextMask5 的Button组件
  * 获取textMask1的mask属性与期待值new ProgressMask(10.0, 100.0, Color.Gray)比对
  * 获取imageMask1的mask属性与期待值new Circle({width: '500px', height: '280px'})比对
  * 获取textAreaMask1的mask属性与期待值new Ellipse({ width: '250px', height: '280px' })比对
  * 点击button1，变更textMask1的mask属性值为new ProgressMask(10.0, 100.0, 0xffffff)
  * 获取textMask1的ClickEffect属性与期待值new ProgressMask(10.0, 100.0, 0xffffff)比对
  * 点击button2，变更textMask1的mask属性值为new ProgressMask(10.0, 100.0, 'rgb(255, 100, 255)')
  * 获取textMask1的ClickEffect属性与期待值new ProgressMask(10.0, 100.0, 'rgb(255, 100, 255)')比对
  * 点击button3，变更textMask1的mask属性值为new ProgressMask(10.0, 100.0, $r('app.color.start_window_background'))
  * 获取textMask1的ClickEffect属性与期待值new ProgressMask(10.0, 100.0, $r('app.color.start_window_background'))比对
  * 点击button4，变更imageMask1的mask属性值为new Rect({ width: '500px', height: '280px' })
  * 获取imageMask1的ClickEffect属性与期待值new Rect({ width: '500px', height: '280px' })比对
  * 点击button5，变更textAreaMask1的mask属性值为 new Path({ width: '50px', height: '280px' })
  * 获取menu2的textAreaMask1属性与期待值 new Path({ width: '50px', height: '280px' })比对
  */
  defineTest('maskTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("maskTestDemo running")
    let driver: Tester = Tester.create()
    let textMask1: Component = await driver.findComponent(Matcher.create().id('textMask1').enabled(true))
    let imageMask1: Component = await driver.findComponent(Matcher.create().id('imageMask1').enabled(true))
    let textAreaMask1: Component = await driver.findComponent(Matcher.create().id('textAreaMask1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonTextMask1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonTextMask2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonTextMask3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('ButtonTextMask4').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('ButtonTextMask5').enabled(true))
    let mask1: string = await textMask1.getInspectorInfo()
    assertEqual(JSON.parse(mask1).$attrs.mask.value, new ProgressMask(10.0, 100.0, Color.Gray))
    let mask2: string = await imageMask1.getInspectorInfo()
    assertEqual(JSON.parse(mask2).$attrs.mask.value, new Circle({
      width: '500px', height: '280px'
    }))
    let mask3: string = await textAreaMask1.getInspectorInfo()
    assertEqual(JSON.parse(mask3).$attrs.mask.value, new Ellipse({
      width: '250px', height: '280px'
    }))
    await button1.tap()
    let mask4: string = await textMask1.getInspectorInfo()
    assertEqual(JSON.parse(mask4).$attrs.mask.value, new ProgressMask(10.0, 100.0, 0xffffff))
    await button2.tap()
    let mask5: string = await textMask1.getInspectorInfo()
    assertEqual(JSON.parse(mask5).$attrs.mask.value, new ProgressMask(10.0, 100.0, 'rgb(255, 100, 255)'))
    await button3.tap()
    let mask6: string = await textMask1.getInspectorInfo()
    assertEqual(JSON.parse(mask6).$attrs.mask.value,
      new ProgressMask(10.0, 100.0, $r('app.color.start_window_background')))
    await button4.tap()
    let mask7: string = await textMask1.getInspectorInfo()
    assertEqual(JSON.parse(mask7).$attrs.mask.value, new Rect({
      width: '500px', height: '280px'
    }))
    await button5.tap()
    let mask8: string = await textMask1.getInspectorInfo()
    assertEqual(JSON.parse(mask8).$attrs.mask.value, new Path({
      width: '50px', height: '280px'
    }))
  }, 0)
}