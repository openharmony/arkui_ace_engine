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

export default async function gridEditModeTest() {
  /*
  * Grid组件 EditMode属性
  * 找到画面id为gridEditMode的Grid组件
  * 找到画面文本为GridEditMode的Button组件
  * 获取gridEditMode的EditMode属性与期待值true比对
  * 点击button，变更gridEditMode的EditMode属性值为false
  * 获取gridEditMode的EditMode属性与期待值false比对
  */
  defineTest('gridEditModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridEditModeTestDemo running')
    let driver: Tester = Tester.create()
    let gridEditMode: Component = await driver.findComponent(Matcher.create().id('gridEditMode').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridEditMode').enabled(true))

    let editMode1: string = await gridEditMode.getInspectorInfo()
    assertTrue(JSON.parse(editMode1).$attrs.editMode)
    await button.tap()
    let editMode2: string = await gridEditMode.getInspectorInfo()
    assertFalse(JSON.parse(editMode2).$attrs.editMode)
  }, 0)
}