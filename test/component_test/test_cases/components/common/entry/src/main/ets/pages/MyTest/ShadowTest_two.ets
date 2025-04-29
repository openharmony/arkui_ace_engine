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

export default async function shadowTest_two() {
  /*
 * BindPopup 通用属性
 * 找到画面id为 dataPanel1 的 Button 组件
 * 找到画面文本为 ButtonShadow1 ButtonShadow2 ButtonShadow3 ButtonShadow4 ButtonShadow5 的 Button 组件
 * 获取 dataPanel1 的属性shadow 与ShadowStyle.OUTER_DEFAULT_XS 对比
 * 点击button1
 * 获取 dataPanel2 的属性shadow 与ShadowStyle.OUTER_DEFAULT_SM 对比
 * 点击button2
 * 获取 dataPanel3 的属性shadow 与ShadowStyle.OUTER_DEFAULT_MD 对比
 * 点击button3
 * 获取 dataPanel4 的属性shadow 与ShadowStyle.OUTER_DEFAULT_LG 对比
 * 点击button4
 * 获取 dataPanel5 的属性shadow 与ShadowStyle.OUTER_FLOATING_SM 对比
 * 点击button5
 * 获取 dataPanel6 的属性shadow 与ShadowStyle.OUTER_FLOATING_MD 对比
 * */
  defineTest('ShadowTest_two', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("ShadowTest_two running")
    let driver: Tester = Tester.create()
    let dataPanel1: Component = await driver.findComponent(Matcher.create().id('dataPanel1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonShadow1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonShadow2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonShadow3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('ButtonShadow4').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('ButtonShadow5').enabled(true))

    let shadow1: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(shadow1).$attrs.shadow, 'ShadowStyle.OuterDefaultXS')
    await button1.tap()
    let shadow2: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(shadow2).$attrs.shadow, 'ShadowStyle.OuterDefaultSM')
    await button2.tap()
    let shadow3: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(shadow3).$attrs.shadow, 'ShadowStyle.OuterDefaultMD')
    await button3.tap()
    let shadow4: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(shadow4).$attrs.shadow, 'ShadowStyle.OuterDefaultLG')
    await button4.tap()
    let shadow5: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(shadow5).$attrs.shadow, 'ShadowStyle.OuterFloatingSM')
    await button5.tap()
    let shadow6: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(shadow6).$attrs.shadow, 'ShadowStyle.OuterFloatingMD')
  }, 0)
}