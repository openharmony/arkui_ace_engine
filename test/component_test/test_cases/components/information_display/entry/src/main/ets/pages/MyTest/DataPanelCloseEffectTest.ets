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

export default async function dataPanelCloseEffectTest() {
  /*
   * DataPanel组件 CloseEffect属性
   * 找到画面id为dataPanelCloseEffect的dataPanel组件
   * 找到画面文本为DataPanelCloseEffect的Button组件
   * 获取dataPanel的CloseEffect属性与期待值true比对
   * 点击button，变更dataPanel的CloseEffect属性值为false
   * 获取dataPanel的CloseEffect属性与期待值false比对
   */
  defineTest('dataPanelCloseEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dataPanelCloseEffectTestDemo running')
    let driver: Tester = Tester.create()
    let dataPanel: Component = await driver.findComponent(Matcher.create().id('dataPanelCloseEffect').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('DataPanelCloseEffect').enabled(true))

    let closeEffect1: string = await dataPanel.getInspectorInfo()
    assertTrue(JSON.parse(closeEffect1).$attrs.closeEffect)
    await button.tap()
    let closeEffect2: string = await dataPanel.getInspectorInfo()
    assertFalse(JSON.parse(closeEffect2).$attrs.closeEffect)
  }, 0)
}