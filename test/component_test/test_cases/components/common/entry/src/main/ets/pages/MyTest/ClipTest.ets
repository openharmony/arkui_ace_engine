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

export default async function clipTest() {
  /*
   * clip 通用属性
   * 找到画面id为 imageClip1 imageClip2 imageClip3 的三个 Image 组件
   * 找到画面文本为 ButtonImageClip 按钮
   * 获取 imageClip1 imageClip2 imageClip3 的属性
   * imageClip1 的 PathAttribute.width 属性与期望值 180 比对
   * imageClip1 的 PathAttribute.height 属性与期望值 180 比对
   * imageClip2 的 EllipseAttribute.width 属性与期望值 100 比对
   * imageClip2 的 EllipseAttribute.height 属性与期望值 50 比对
   * imageClip3 的 RectAttribute.width 属性与期望值 '70%' 比对
   * imageClip3 的 RectAttribute.height 属性与期望值 40 比对
   * 点击 button1 变更 imageClip1 imageClip2 imageClip3 的属性
   * 获取 imageClip1 imageClip2 imageClip3 的属性
   * imageClip1的clip.value与期望值true比对
   * imageClip2的clip.value与期望值false比对
   * imageClip3的RectAttribute.width与期望值 60 比对
   * imageClip3的RectAttribute.height与期望值 60 比对
   * */
  defineTest('clipTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('clipTestDemo running')
    let driver: Tester = Tester.create()
    let imageClip1: Component = await driver.findComponent(Matcher.create().id('imageClip1').enabled(true))
    let imageClip2: Component = await driver.findComponent(Matcher.create().id('imageClip2').enabled(true))
    let imageClip3: Component = await driver.findComponent(Matcher.create().id('imageClip3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonImageClip').enabled(true))
    let clip1: string = await imageClip1.getInspectorInfo()
    let clip2: string = await imageClip2.getInspectorInfo()
    let clip3: string = await imageClip3.getInspectorInfo()
    assertFalse(JSON.parse(clip1).$attrs.clip.width == undefined)
    assertEqual(JSON.parse(clip1)
      .$attrs
      .clip
      .value
      .PathAttribute
      .width, 180)
    assertEqual(JSON.parse(clip1)
      .$attrs
      .clip
      .value
      .PathAttribute
      .height, 180)
    assertEqual(JSON.parse(clip2)
      .$attrs
      .clip
      .value
      .EllipseAttribute
      .width, 100)
    assertEqual(JSON.parse(clip2)
      .$attrs
      .clip
      .value
      .EllipseAttribute
      .height, 50)
    assertEqual(JSON.parse(clip3)
      .$attrs
      .clip
      .value
      .RectAttribute
      .width, '70%')
    assertEqual(JSON.parse(clip3)
      .$attrs
      .clip
      .value
      .RectAttribute
      .height, 40)
    await button1.tap()
    let clip4: string = await imageClip1.getInspectorInfo()
    let clip5: string = await imageClip2.getInspectorInfo()
    let clip6: string = await imageClip3.getInspectorInfo()
    assertTrue(JSON.parse(clip4).$attrs.clip.value)
    assertFalse(JSON.parse(clip5).$attrs.clip.value)
    assertEqual(JSON.parse(clip6)
      .$attrs
      .clip
      .value
      .RectAttribute
      .width, 60)
    assertEqual(JSON.parse(clip6)
      .$attrs
      .clip
      .value
      .RectAttribute
      .height, 60)
  }, 0)
}