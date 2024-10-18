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

export default async function pathCommandsTest() {
  /*
   * Path组件 commands属性
   * 找到画面id为pathCommands的Path组件
   * 找到画面文本为PathCommands的Button组件
   * 获取path的commands属性与期待值'M0 0 L600 0'比对
   * 点击button，变更path的commands属性值为'M0 0 H200 V200 H0 Z'
   * 获取path的commands属性与期待值'M0 0 H200 V200 H0 Z'比对
   */
  defineTest('pathCommandsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("pathCommandsTestDemo running")
    let driver: Tester = Tester.create()
    let path: Component = await driver.findComponent(Matcher.create().id('pathCommands').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PathCommands').enabled(true))

    let commands1: string = await path.getInspectorInfo()
    assertEqual(JSON.parse(commands1).$attrs.commands, 'M0 0 L600 0')

    await button.tap()
    let commands2: string = await path.getInspectorInfo()
    assertEqual(JSON.parse(commands2).$attrs.commands, 'M0 0 H200 V200 H0 Z')
  }, 0)
}