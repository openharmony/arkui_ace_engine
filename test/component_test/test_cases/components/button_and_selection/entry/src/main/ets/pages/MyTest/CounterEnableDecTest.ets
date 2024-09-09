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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function counterEnableDecTest() {
  /*
   * Counter组件 EnableDec属性
   * 找到画面id为counterEnableDec的Counter组件
   * 找到画面文本为CounterEnableDec的Button组件
   * 获取counterEnableDec的EnableDec属性与期待值false比对
   * 点击button1，变更counterEnableDec1的EnableDec属性值为true
   * 获取counterEnableDec的EnableDec属性与期待值true比对
   */
  defineTest('counterEnableDecTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('counterEnableDecTestDemo running')
    let driver: Tester = Tester.create()
    let counterEnableDec: Component = await driver.findComponent(Matcher.create().id('counterEnableDec').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CounterEnableDec').enabled(true))

    let enableDec1: string = await counterEnableDec.getInspectorInfo()
    assertFalse(JSON.parse(enableDec1).$attrs.enableDec == undefined)
    assertFalse(JSON.parse(enableDec1).$attrs.enableDec)

    await button1.tap()
    let enableDec2: string = await counterEnableDec.getInspectorInfo()
    assertTrue(JSON.parse(enableDec2).$attrs.enableDec)
  })
}