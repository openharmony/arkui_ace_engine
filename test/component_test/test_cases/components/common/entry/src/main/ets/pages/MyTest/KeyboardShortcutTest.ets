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

export default async function keyboardShortcutTest() {
  /*
   * button组件 keyboardShortcut属性
   * 找到画面id为buttonKeyboardShortcut1，buttonKeyboardShortcut1的button组件
   * 找到画面文本为 ButtonKeyboardShortcut1 的button组件
   * 获取buttonKeyboardShortcut1的keyboardShortcut属性下value参数与期待值'a'比对
   * 获取buttonKeyboardShortcut1的keyboardShortcut属性下key参数与期待值[ModifierKey.CTRL]比对
   * 获取buttonKeyboardShortcut2的keyboardShortcut属性下value参数与期待值FunctionKey.F5比对
   * 点击button1，变更buttonKeyboardShortcut1的keyboardShortcut属性下key参数为[ModifierKey.SHIFT]
   * 获取buttonKeyboardShortcut1的keyboardShortcut属性下key参数与期待值[ModifierKey.SHIFT]比对
   */
  defineTest('keyboardShortcutTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("keyboardShortcutTest running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().id('buttonKeyboardShortcut1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().id('buttonKeyboardShortcut2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonKeyboardShortcut1').enabled(true))
    let keyboardShortcut1: string = await button1.getInspectorInfo()
    assertFalse(JSON.parse(keyboardShortcut1).$attrs.keyboardShortcut == undefined)
    assertEqual(JSON.parse(keyboardShortcut1).$attrs.keyboardShortcut.value, 'a')
    let keyboardShortcut2: string = await button1.getInspectorInfo()
    assertEqual(JSON.parse(keyboardShortcut2).$attrs.keyboardShortcut.keys, [ModifierKey.CTRL])
    let keyboardShortcut3: string = await button2.getInspectorInfo()
    assertEqual(JSON.parse(keyboardShortcut3).$attrs.keyboardShortcut.value, FunctionKey.F5)
    await button3.tap()
    let keyboardShortcut4: string = await button1.getInspectorInfo()
    assertEqual(JSON.parse(keyboardShortcut4).$attrs.keyboardShortcut.keys, [ModifierKey.SHIFT])
  }, 0)
}