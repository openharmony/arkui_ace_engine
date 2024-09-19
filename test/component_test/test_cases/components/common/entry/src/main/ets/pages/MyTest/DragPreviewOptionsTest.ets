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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function dragPreviewOptionsTest() {
  /*
   * dragPreviewOptions 通用属性
   * 找到画面id为 imageDragPreviewOptions1 的 Image 组件
   * 找到画面文本为 ButtonDragPreviewOptions 按钮
   * 获取 imageDragPreviewOptions1 的dragPreviewOptions.mode属性与期望值DragPreviewMode.AUTO比对
   * 点击 LoadingProgress1 变更 imageDragPreviewOptions1 的属性
   * 获取 imageDragPreviewOptions1 的dragPreviewOptions.mode属性与期望值DragPreviewMode.DISABLE_SCALE比对
   * */
  defineTest('dragPreviewOptionsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dragPreviewOptionsTestDemo running')
    let driver: Tester = Tester.create()
    let imageDragPreviewOptions1: Component =
      await driver.findComponent(Matcher.create().id('imageDragPreviewOptions1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonDragPreviewOptions').enabled(true))
    let dragPreviewOptions1: string = await imageDragPreviewOptions1.getInspectorInfo()
    assertFalse(JSON.parse(dragPreviewOptions1).$attrs.dragPreviewOptions == undefined)
    assertEqual(JSON.parse(dragPreviewOptions1)
      .$attrs
      .dragPreviewOptions
      .mode, DragPreviewMode.AUTO)

    await button1.tap()
    let dragPreviewOptions2: string = await imageDragPreviewOptions1.getInspectorInfo()
    assertEqual(JSON.parse(dragPreviewOptions2)
      .$attrs
      .dragPreviewOptions
      .mode, DragPreviewMode.DISABLE_SCALE)
  }, 0)
}