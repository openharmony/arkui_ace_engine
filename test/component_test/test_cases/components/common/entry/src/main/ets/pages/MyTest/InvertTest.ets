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

import { assertEqual, } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function invertTest() {
  /*
  * image组件 invert属性
  * 找到画面id为imageInvert1的image组件
  * 找到画面文本为ButtonInvert1的Button组件
  * 获取imageInvert1的invert属性与期待值 1 比对
  * 点击button1，变更imageInvert1的invert属性值为 0
  * 获取imageInvert1的invert属性与期待值 0 比对
  */
  defineTest('invertTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("invertTest running")
    let driver: Tester = Tester.create()
    let imageInvert1: Component = await driver.findComponent(Matcher.create().id('imageInvert1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonInvert1').enabled(true))
    let invert1: string = await imageInvert1.getInspectorInfo()
    assertEqual(JSON.parse(invert1).$attrs.invert, 1)
    await button1.tap()
    let Invert2: string = await imageInvert1.getInspectorInfo()
    assertEqual(JSON.parse(Invert2).$attrs.invert, 0)
  }, 0)
}