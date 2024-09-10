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

export default async function panelShowCloseIconTest() {
  /*
   * Panel组件 ShowCloseIcon属性
   * 找到画面id为panelShowCloseIcon的Panel组件
   * 找到画面文本为PanelShowCloseIcon的Button组件
   * 获取panel的ShowCloseIcon属性与期待值true比对
   * 点击button，变更panel的ShowCloseIcon属性值为false
   * 获取panel的ShowCloseIcon属性与期待值false比对
   */
  defineTest('panelShowCloseIconTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('panelShowCloseIconTestDemo running')
    let driver: Tester = Tester.create()
    let panel: Component = await driver.findComponent(Matcher.create().id('panelShowCloseIcon').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PanelShowCloseIcon').enabled(true))

    let showCloseIcon1: string = await panel.getInspectorInfo()
    assertTrue(JSON.parse(showCloseIcon1).$attrs.showCloseIcon)

    await button.tap()
    let showCloseIcon2: string = await panel.getInspectorInfo()
    assertFalse(JSON.parse(showCloseIcon2).$attrs.showCloseIcon)
  }, 0)
}