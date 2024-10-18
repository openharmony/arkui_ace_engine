/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function menuItemSelectedTest() {
  /*
 * MenuItem组件 Selected属性
 * 找到画面id为menuItemSelected的MenuItem组件
 * 找到画面文本为MenuItemSelected的Button组件
 * 获取menuItemSelected的Selected属性与期待值False比对
 * 点击button，变更menuItemSelected的Selected属性值为True
 * 获取menuItemSelected的Selected属性与期待值True比对
 */
  defineTest('menuItemSelectedTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuItemSelectedTestDemo running')
    let driver: Tester = Tester.create()
    let menuItemSelected: Component = await driver.findComponent(Matcher.create().id('menuItemSelected').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('MenuItemSelected').enabled(true))

    let selected1: string = await menuItemSelected.getInspectorInfo()
    assertFalse(JSON.parse(selected1).$attrs.selected == undefined)
    assertFalse(JSON.parse(selected1).$attrs.selected)

    await button.tap()
    let selected2: string = await menuItemSelected.getInspectorInfo()
    assertTrue(JSON.parse(selected2).$attrs.selected)
  }, 0)
}