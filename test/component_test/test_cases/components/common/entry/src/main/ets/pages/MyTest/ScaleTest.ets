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

import { assertContain, assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function scaleTest() {
  /*
  * progress组件 scale属性
  * 找到画面id为progressScale1，progressScale2的progress组件
  * 找到画面文本为ProgressScale1的Button组件
  * 获取progressScale1的scale属性下的x参数与期待值2比对
  * 获取progressScale1的scale属性下的y参数与期待值0.5比对
  * 获取progressScale1的scale属性下的z参数与期待值3比对
  * 获取progressScale1的scale属性下的centerX参数与期待值2比对
  * 获取progressScale1的scale属性下的centerY参数与期待值30比对
  * 获取progressScale2的scale属性下的x参数与期待值2比对
  * 获取progressScale2的scale属性下的y参数与期待值0.5比对
  * 获取progressScale2的scale属性下的z参数与期待值3比对
  * 获取progressScale2的scale属性下的centerX参数与期待值2比对
  * 获取progressScale2的scale属性下的centerY参数与期待值2比对
  * 点击button1，变更progressScale2的scale属性下的centerX参数为'80%'
  * 获取progressScale2的scale属性下的centerX参数与期待值'80%'比对
  * 获取progressScale2的scale属性下的centerY参数与期待值'80%'比对
  */
  defineTest('scaleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("scaleTestDemo running")
    let driver: Tester = Tester.create()
    let progressScale1: Component = await driver.findComponent(Matcher.create().id('progressScale1').enabled(true))
    let progressScale2: Component = await driver.findComponent(Matcher.create().id('progressScale2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonProgressScale1').enabled(true))
    let scale1: string = await progressScale1.getInspectorInfo()
    assertEqual(JSON.parse(scale1)
      .$attrs
      .scale
      .x, '2.000000')
    let scale2: string = await progressScale1.getInspectorInfo()
    assertEqual(JSON.parse(scale2)
      .$attrs
      .scale
      .y, '0.500000')
    let scale3: string = await progressScale1.getInspectorInfo()
    assertEqual(JSON.parse(scale3)
      .$attrs
      .scale
      .z, '3.000000')
    let scale4: string = await progressScale1.getInspectorInfo()
    assertEqual(JSON.parse(scale4)
      .$attrs
      .scale
      .centerX, '2.00vp')
    let scale5: string = await progressScale1.getInspectorInfo()
    assertEqual(JSON.parse(scale5)
      .$attrs
      .scale
      .centerY, '30.00vp')
    let scale6: string = await progressScale2.getInspectorInfo()
    assertEqual(JSON.parse(scale6)
      .$attrs
      .scale
      .x, '2.000000')
    let scale7: string = await progressScale2.getInspectorInfo()
    assertEqual(JSON.parse(scale7)
      .$attrs
      .scale
      .y, '0.500000')
    let scale8: string = await progressScale2.getInspectorInfo()
    assertEqual(JSON.parse(scale8)
      .$attrs
      .scale
      .z, '3.000000')
    let scale9: string = await progressScale2.getInspectorInfo()
    assertEqual(JSON.parse(scale9)
      .$attrs
      .scale
      .centerX, '2.00vp')
    let scale10: string = await progressScale2.getInspectorInfo()
    assertEqual(JSON.parse(scale10)
      .$attrs
      .scale
      .centerY, '2.00vp')
    await button1.tap()
    let scale11: string = await progressScale2.getInspectorInfo()
    assertEqual(JSON.parse(scale11)
      .$attrs
      .scale
      .centerX, '80.00%')
    let scale12: string = await progressScale2.getInspectorInfo()
    assertEqual(JSON.parse(scale12)
      .$attrs
      .scale
      .centerY, '80.00%')
  }, 0)
}