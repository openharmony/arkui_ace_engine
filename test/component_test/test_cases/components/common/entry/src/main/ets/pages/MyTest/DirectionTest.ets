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

export default async function directionTest() {
  /*
  * row组件 direction属性
  * 找到画面id为rowDirection1的row组件
  * 找到画面文本为ButtonDirection1、ButtonDirection2的Button组件
  * 获取rowDirection1的direction属性与期待值Direction.Ltr比对
  * 点击button1，变更rowDirection1的direction属性值为Direction.Rtl
  * 获取rowDirection1的direction属性与期待值Direction.Rtl比对
  * 点击button2，变更rowDirection1的direction属性值为Direction.Auto
  * 获取rowDirection1的direction属性与期待值Direction.Auto比对
  */
  defineTest('directionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("directionTestDemo running")
    let driver: Tester = Tester.create()
    let rowDirection1: Component = await driver.findComponent(Matcher.create().id('rowDirection1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonDirection1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonDirection2').enabled(true))
    let direction1: string = await rowDirection1.getInspectorInfo()
    assertEqual(JSON.parse(direction1).$attrs.direction, 'Direction.Ltr')

    await button1.tap()
    let direction2: string = await rowDirection1.getInspectorInfo()
    assertEqual(JSON.parse(direction2).$attrs.direction, 'Direction.Rtl')

    await button2.tap()
    let direction3: string = await rowDirection1.getInspectorInfo()
    assertEqual(JSON.parse(direction3).$attrs.direction, 'Direction.Auto')
  }, 0)
}