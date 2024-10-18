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

export default async function zIndexTest() {
  /*
  * text组件 zIndex属性
  * 找到画面id为textZIndex1，textZIndex1的text组件
  * 找到画面文本为ButtonZIndex1的Button组件
  * 获取textZIndex1的zIndex属性与期待值2比对
  * 获取textZIndex2的zIndex属性与期待值1比对
  * 点击button1，变更textZIndex2的zIndex属性值为3
  * 获取textZIndex2的zIndex属性与期待值3比对
  */
  defineTest('zIndexTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("zIndexTestDemo running")
    let driver: Tester = Tester.create()
    let textZIndex1: Component = await driver.findComponent(Matcher.create().id('textZIndex1').enabled(true))
    let textZIndex2: Component = await driver.findComponent(Matcher.create().id('textZIndex2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonZIndex1').enabled(true))
    let zIndex1: string = await textZIndex1.getInspectorInfo()
    assertEqual(JSON.parse(zIndex1).$attrs.zIndex, 2)
    let zIndex2: string = await textZIndex2.getInspectorInfo()
    assertEqual(JSON.parse(zIndex2).$attrs.zIndex, 1)
    await button1.tap()
    let zIndex3: string = await textZIndex2.getInspectorInfo()
    assertEqual(JSON.parse(zIndex3).$attrs.zIndex, 3)
  }, 0)
}