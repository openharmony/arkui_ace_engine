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

import { assertEqual, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function obscuredTest() {
  /*
   * outlineColor 通用属性
   * 找到画面id为 textObscured1 的组件
   * 找到画面id为 imageObscured1 的组件
   * 找到画面文本为 ButtonObscured 按钮
   * 获取 textObscured1 的属性与期望值 ObscuredReasons.PLACEHOLDER 比对
   * 获取 imageObscured1 的属性与期望值 ObscuredReasons.PLACEHOLDER 比对
   * 点击 button1 变更 imageObscured1 的属性
   * 获取 imageObscured1 的 reasons 属性 与期望值 '' 比对
   * */
  defineTest('obscuredTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('obscuredTestDemo running')
    let driver: Tester = Tester.create()
    let textObscured1: Component = await driver.findComponent(Matcher.create().id('textObscured1').enabled(true))
    let imageObscured1: Component = await driver.findComponent(Matcher.create().id('imageObscured1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonObscured').enabled(true))
    let enabled1: string = await textObscured1.getInspectorInfo()
    assertTrue(JSON.parse(enabled1).$attrs.obscured == ObscuredReasons.PLACEHOLDER)
    let enabled2: string = await imageObscured1.getInspectorInfo()
    assertTrue(JSON.parse(enabled2).$attrs.obscured == ObscuredReasons.PLACEHOLDER)

    await button1.tap()
    let enabled3: string = await imageObscured1.getInspectorInfo()
    assertTrue(JSON.parse(enabled3).$attrs.obscured == '')
  }, 0)
}