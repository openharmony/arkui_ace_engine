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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function draggableTest() {
  /*
* draggable 通用属性
* 找到画面id为 qRCodeDraggable1 的 QRCode 组件
* 找到画面文本为 ButtonDraggable 按钮
* 获取 qRCodeDraggable1 的属性与期望值True比对
* 点击 button1 变更 qRCodeDraggable1 的属性
* 获取 qRCodeDraggable1 的属性与期望值False比对
*
* */
  defineTest('draggableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('draggableTestDemo running')
    let driver: Tester = Tester.create()
    let qRCodeDraggable1: Component = await driver.findComponent(Matcher.create().id('qRCodeDraggable1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonDraggable').enabled(true))
    let draggable1: string = await qRCodeDraggable1.getInspectorInfo()
    assertFalse(JSON.parse(draggable1).$attrs.draggable == undefined)
    assertTrue(JSON.parse(draggable1).$attrs.draggable.value)

    await button1.tap()
    let draggable2: string = await qRCodeDraggable1.getInspectorInfo()
    assertFalse(JSON.parse(draggable2).$attrs.draggable.value)
  }, 0)
}