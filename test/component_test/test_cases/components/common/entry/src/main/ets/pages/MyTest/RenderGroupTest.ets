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

import { assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function renderGroupTest() {
  /*
 * renderGroup 通用属性
 * 找到画面id为 rowRenderGroup1 的组件
 * 找到画面文本为 ButtonRenderGroup1 按钮
 * 获取 rowRenderGroup1 的属性与期望值比对
 * 点击 button1 变更 rowRenderGroup1 的属性
 * 获取 rowRenderGroup1 的属性与期望值比对
 * */
  defineTest('renderGroupTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('renderGroupTestDemo running')
    let driver: Tester = Tester.create()
    let rowRenderGroup1: Component = await driver.findComponent(Matcher.create().id('rowRenderGroup1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonRenderGroup1').enabled(true))
    let renderGroup1: string = await rowRenderGroup1.getInspectorInfo()
    assertTrue(JSON.parse(renderGroup1).$attrs.renderGroup)
    await button1.tap()
    let renderGroup2: string = await rowRenderGroup1.getInspectorInfo()
    assertFalse(JSON.parse(renderGroup2).$attrs.renderGroup)
  }, 0)
}