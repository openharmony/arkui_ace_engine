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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function translateTest() {
  /*
  * radio组件 translate属性
  * 找到画面id为radio1，radio2的menu组件
  * 找到画面文本为ButtonTranslate的Button组件
  * 获取radio1的translate属性中x参数与期待值50.00vp比对
  * 获取radio1的translate属性中y参数与期待值50.00vp比对
  * 获取radio1的translate属性中z参数与期待值50.00vp比对
  * 点击button1，变更radio1的translate属性x差数的值为'80.00%'，y参数的值为'80.00%'，z差数的值为'80.00%'
  * 获取radio1的translate属性中x参数与期待值'80.00%'比对
  * 获取radio1的translate属性中y参数与期待值'80.00%'比对
  * 获取radio1的translate属性中z参数与期待值'80.00%'比对
  */
  defineTest('translateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("translateTestDemo running")
    let driver: Tester = Tester.create()
    let radio1: Component = await driver.findComponent(Matcher.create().id('radio1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonTranslate').enabled(true))
    let translate1: string = await radio1.getInspectorInfo()
    assertEqual(JSON.parse(translate1)
      .$attrs
      .translate
      .x, '50.00vp')
    let translate2: string = await radio1.getInspectorInfo()
    assertEqual(JSON.parse(translate2)
      .$attrs
      .translate
      .y, '50.00vp')
    let translate3: string = await radio1.getInspectorInfo()
    assertEqual(JSON.parse(translate3)
      .$attrs
      .translate
      .z, '50.00vp')
    await button1.tap()
    let translate4: string = await radio1.getInspectorInfo()
    assertEqual(JSON.parse(translate4)
      .$attrs
      .translate
      .x, '80.00%')
    let translate5: string = await radio1.getInspectorInfo()
    assertEqual(JSON.parse(translate5)
      .$attrs
      .translate
      .y, '80.00%')
    let translate6: string = await radio1.getInspectorInfo()
    assertEqual(JSON.parse(translate6)
      .$attrs
      .translate
      .z, '80.00%')
  }, 0)
}