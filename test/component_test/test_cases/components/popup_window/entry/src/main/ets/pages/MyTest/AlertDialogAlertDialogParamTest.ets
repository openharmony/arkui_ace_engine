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
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

/*
* AlertDialog警告弹窗 AlertDialogParam对象
* 找到画面文本为AlertDialogAlertDialogParam，AlertDialogAlertDialogParam1，AlertDialogAlertDialogParam2，
  AlertDialogAlertDialogParam3的组件
* 单击button1，获取alertDialog的AlertDialogParam对象与期待值{ title: 'title', subtitle: 'fax', message: 'text',
  autoCancel: true,alignment: DialogAlignment.Center, offset: { dx: 0, dy: -20 }, gridCount: 5, maskRect:
  { x: 0, y: 0, width: '100%', height: '100%' },showInSubWindow: false, isModal: true, backgroundColor:
  Color.Yellow, backgroundBlurStyle: BlurStyle.Thick}对比
* 单击button2,然后重新点击button1获取alertDialog的AlertDialogParam1对象与期待值{title: $r('app.string.dialog_show_title'),
  subtitle: $r('app.string.dialog_show_subtitle'),message: $r('app.string.dialog_show_message'),autoCancel: true,
  alignment: DialogAlignment.CenterStart,offset: { dx: '1px', dy: '20px' },gridCount: 3,maskRect:
  {x: $r('app.integer.dialog_show_mask_rect_x'),y: $r('app.integer.dialog_show_mask_rect_y'),
  width: $r('app.string.dialog_show_mask_rect_width'),height: $r('app.string.dialog_show_mask_rect_height')},
  showInSubWindow: false,isModal: true,backgroundColor: '#0000ff',backgroundBlurStyle: BlurStyle.Regular}比对
* 点击button3，然后点击button1获取alertDialog的AlertDialogParam2对象与期待值 { title: 'animator',subtitle: 'cat',
  message: 'dog pag pag',autoCancel: true, },alignment: DialogAlignment.Top, offset: { dx:
  $r('app.integer.dialog_show_offset_dx'), dy: $r('app.integer.dialog_show_offset_dy') },gridCount: 4,
  showInSubWindow: false,isModal: false,backgroundColor: 0xFFB6C1,backgroundBlurStyle: BlurStyle.Thin}比对
* 点击button4，然后点击button1获取alertDialog的AlertDialogParam2对象与期待值{title: 'plant',subtitle: 'ferns',},
  message: 'beautiful',autoCancel: false,alignment: DialogAlignment.CenterStart,offset: { dx: 0, dy: -20 },
  gridCount: 3,maskRect: { x: 0, y: 0, width: '100%', height: '100%' },showInSubWindow: false,isModal: true,
  backgroundColor:$r('app.color.dialog_show_background_color'),backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK}比对
*/
export default async function alertDialogAlertDialogParamTest() {

  defineTest('alertDialogAlertDialogParamTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('alertDialogAlertDialogParamTestDemo running')
    let driver: Tester = Tester.create()

    let button1: Component =
      await driver.findComponent(Matcher.create().text('AlertDialogAlertDialogParam').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('AlertDialogAlertDialogParam1').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('AlertDialogAlertDialogParam2').enabled(true))
    let button4: Component =
      await driver.findComponent(Matcher.create().text('AlertDialogAlertDialogParam3').enabled(true))

    await button1.tap()
    let alertDialog1: Component = await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let alertDialogParam1: string = await alertDialog1.getInspectorInfo()
    assertEqual(JSON.parse(alertDialogParam1).$attrs.title, 'title')
    assertEqual(JSON.parse(alertDialogParam1).$attrs.subtitle, 'fax')
    assertEqual(JSON.parse(alertDialogParam1).$attrs.message, 'text')
    assertTrue(JSON.parse(alertDialogParam1).$attrs.autoCancel)
    assertEqual(JSON.parse(alertDialogParam1).$attrs.alignment, 'DialogAlignment.CENTER')
    assertEqual(JSON.parse(alertDialogParam1).$attrs.offset.dX, 0)
    assertEqual(JSON.parse(alertDialogParam1).$attrs.offset.dY, -20)
    assertEqual(JSON.parse(alertDialogParam1).$attrs.girdCount, 5)
    assertEqual(JSON.parse(alertDialogParam1).$attrs.maskRect.x, 0)
    assertEqual(JSON.parse(alertDialogParam1).$attrs.maskRect.y, 0)
    assertEqual(JSON.parse(alertDialogParam1).$attrs.maskRect.width, '100%')
    assertEqual(JSON.parse(alertDialogParam1).$attrs.maskRect.height, '100%')
    assertFalse(JSON.parse(alertDialogParam1).$attrs.showInSubWindow)
    assertTrue(JSON.parse(alertDialogParam1).$attrs.isModel)
    assertEqual(JSON.parse(alertDialogParam1).$attrs.backgroundColor.toLowerCase(), Color.Yellow)
    assertEqual(JSON.parse(alertDialogParam1).$attrs.backgroundBlurStyle, BlurStyle.Thick)
    await driver.tap(100, 100)
    let string1: string = await alertDialog1.getInspectorInfo()
    assertEqual(JSON.parse(string1).$attrs.cancel, 'free')

    await button3.tap()
    let alertDialog2: Component = await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('confirm1').enabled(true))
    let alertDialogParam2: string = await alertDialog2.getInspectorInfo()
    assertEqual(JSON.parse(alertDialogParam2).$attrs.title, 'animator')
    assertEqual(JSON.parse(alertDialogParam2).$attrs.subtitle, 'cat')
    assertEqual(JSON.parse(alertDialogParam2).$attrs.message, 'dog pag pag')
    assertTrue(JSON.parse(alertDialogParam2).$attrs.autoCancel)
    assertEqual(JSON.parse(alertDialogParam2).$attrs.alignment, 'DialogAlignment.TOP')
    assertEqual(JSON.parse(alertDialogParam2).$attrs.offset.dX, $r('app.integer.dialog_show_offset_dx'))
    assertEqual(JSON.parse(alertDialogParam2).$attrs.offset.dY, $r('app.integer.dialog_show_offset_dy'))
    assertEqual(JSON.parse(alertDialogParam2).$attrs.girdCount, 4)
    assertFalse(JSON.parse(alertDialogParam2).$attrs.showInSubWindow)
    assertFalse(JSON.parse(alertDialogParam2).$attrs.isModel)
    assertEqual(JSON.parse(alertDialogParam2).$attrs.backgroundColor, '#FFFFB6C1')
    assertEqual(JSON.parse(alertDialogParam2).$attrs.backgroundBlurStyle, BlurStyle.Thin)
    assertEqual(JSON.parse(alertDialogParam2).$attrs.confirm, 'confirm1')
    await button5.tap()
    let string2: string = await alertDialog2.getInspectorInfo()
    assertEqual(JSON.parse(string2).$attrs.cancel, 'tiger')

    await button4.tap()
    let alertDialog3: Component = await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let button6: Component = await driver.findComponent(Matcher.create().text('confirm2').enabled(true))
    let alertDialogParam3: string = await alertDialog3.getInspectorInfo()
    assertEqual(JSON.parse(alertDialogParam3).$attrs.title, 'plant')
    assertEqual(JSON.parse(alertDialogParam3).$attrs.subtitle, 'ferns')
    assertEqual(JSON.parse(alertDialogParam3).$attrs.message, 'beautiful')
    assertFalse(JSON.parse(alertDialogParam3).$attrs.autoCancel)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.alignment, DialogAlignment.CenterStart)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.offset.dX, 0)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.offset.dY, -20)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.girdCount, 3)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.maskRect.x, 0)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.maskRect.y, 0)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.maskRect.width, '100%')
    assertEqual(JSON.parse(alertDialogParam3).$attrs.maskRect.height, '100%')
    assertFalse(JSON.parse(alertDialogParam3).$attrs.showInSubWindow)
    assertTrue(JSON.parse(alertDialogParam3).$attrs.isModel)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.backgroundColor, $r('app.color.dialog_show_background_color'))
    assertEqual(JSON.parse(alertDialogParam3).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_ULTRA_THICK)
    assertEqual(JSON.parse(alertDialogParam3).$attrs.confirm, 'confirm2')
    await button6.tap()
    let string3: string = await alertDialog3.getInspectorInfo()
    assertEqual(JSON.parse(string3).$attrs.cancel, 'arg')

    await button2.tap()
    await button1.tap()
    let alertDialog4: Component = await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let alertDialogParam4: string = await alertDialog4.getInspectorInfo()
    assertEqual(JSON.parse(alertDialogParam4).$attrs.title, $r("app.string.dialog_show_title"))
    assertEqual(JSON.parse(alertDialogParam4).$attrs.subtitle, $r("app.string.dialog_show_subtitle"))
    assertEqual(JSON.parse(alertDialogParam4).$attrs.message, $r("app.string.dialog_show_message"))
    assertTrue(JSON.parse(alertDialogParam4).$attrs.autoCancel)
    assertEqual(JSON.parse(alertDialogParam4).$attrs.alignment, DialogAlignment.CenterStart)
    assertEqual(JSON.parse(alertDialogParam4).$attrs.offset.dX, '1px')
    assertEqual(JSON.parse(alertDialogParam4).$attrs.offset.dY, '20px')
    assertEqual(JSON.parse(alertDialogParam4).$attrs.girdCount, 3)
    assertEqual(JSON.parse(alertDialogParam4).$attrs.maskRect.x, $r('app.integer.dialog_show_mask_rect_x'))
    assertEqual(JSON.parse(alertDialogParam4).$attrs.maskRect.y, $r('app.integer.dialog_show_mask_rect_y'))
    assertEqual(JSON.parse(alertDialogParam4).$attrs.maskRect.width, $r('app.string.dialog_show_mask_rect_width'))
    assertEqual(JSON.parse(alertDialogParam4).$attrs.maskRect.height, $r('app.string.dialog_show_mask_rect_height'))
    assertFalse(JSON.parse(alertDialogParam4).$attrs.showInSubWindow)
    assertTrue(JSON.parse(alertDialogParam4).$attrs.isModel)
    assertEqual(JSON.parse(alertDialogParam4).$attrs.backgroundColor, '#0000ff')
    assertEqual(JSON.parse(alertDialogParam4).$attrs.backgroundBlurStyle, BlurStyle.Regular)
    await driver.tap(100, 100)
    let string4: string = await alertDialog1.getInspectorInfo()
    assertEqual(JSON.parse(string4).$attrs.cancel, 'world')
  }, 0)
}