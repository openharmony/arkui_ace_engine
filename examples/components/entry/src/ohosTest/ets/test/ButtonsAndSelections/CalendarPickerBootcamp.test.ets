import { describe, beforeAll, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import {
  buttonClick,
  getToggle,
  JsonType, KeyStruct, radioClick,
  Search,
  searchParentBlock,
  searchToggle,
  Slide, sliderDrag,
  titleSearch,
  ToggleClick } from '../../utils';
import { Point } from '@ohos.UiTest';

const TAG = 'CalendarPickerBootcamp'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function CalendarPickerBootcampTest() {
  describe('CalendarPickerBootcampTest', () => {

    //  每条用例执行前会执行的函数
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(8000);
        console.info(TAG + 'CalendarPickerBootcamp' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[1].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let ListItems1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItems1[0].getBoundsCenter()
        let width4: Point = await ListItems1[2].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('日历选择器/CalendarPicker'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }

      console.info(`beforeAll end`);
      done();
    })

    // edgeAlign.CalendarAlign
    it('ArkUI_CalendarPicker_001', 0, async (done: Function) => {

      await Search('参数列表', 'edgeAlign.CalendarAlign')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'edgeAlign.CalendarAlign'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeAlign', JsonType.obj),
          new KeyStruct('alignType', JsonType.value),
        ],
        assertEqual: 'CalendarAlign.END'
      })

      done();
    })

    it('ArkUI_CalendarPicker_002', 0, async (done: Function) => {

      await Search('参数列表', 'edgeAlign.CalendarAlign')

      await radioClick({
        radioClickObj: 0,
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeAlign', JsonType.obj),
          new KeyStruct('alignType', JsonType.value),
        ],
        assertEqual: 'CalendarAlign.START'
      })

      done();
    })

    it('ArkUI_CalendarPicker_003', 0, async (done: Function) => {

      await Search('参数列表', 'edgeAlign.CalendarAlign')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'edgeAlign.CalendarAlign',
          toggleClickType: ToggleClick.Close
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeAlign', JsonType.obj),
          new KeyStruct('alignType', JsonType.value),
        ],
        assertEqual: 'CalendarAlign.CENTER'
      })

      done();
    })

    // edgeAlign.dx
    it('ArkUI_CalendarPicker_004', 0, async (done: Function) => {
      await Search('参数列表', 'edgeAlign.CalendarAlign')

      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('edgeAlign.CalendarAlign')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }

      await Search('参数列表', 'edgeAlign.dx')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'edgeAlign.dx'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeAlign', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('dx', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeAlign', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('dx', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

    // edgeAlign.dy
    it('ArkUI_CalendarPicker_005', 0, async (done: Function) => {

      await Search('参数列表', 'edgeAlign.CalendarAlign')

      let toggleOpen: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('edgeAlign.CalendarAlign')))
      if (await toggleOpen.isChecked() === false) {
        await toggleOpen.click();
      }

      await Search('参数列表', 'edgeAlign.dy')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'edgeAlign.dy'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeAlign', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('dy', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'edgeAlign.dy',
          toggleClickType: ToggleClick.Close,
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeAlign', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('dy', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      await Search('参数列表', 'edgeAlign.CalendarAlign')

      let toggleClose: Array<Component> =
        await driver.findComponents(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('edgeAlign.CalendarAlign')));
      if (await toggleClose[0].isChecked() === true) {
        await toggleClose[0].click()
      }

      done();
    })

    // textStyle.color
    it('ArkUI_CalendarPicker_006', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_CalendarPicker_007', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_CalendarPicker_008', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_CalendarPicker_009', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_CalendarPicker_010', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_CalendarPicker_011', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'textStyle.color',
          toggleClickType: ToggleClick.Close,
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // textStyle.font.size
    it('ArkUI_CalendarPicker_012', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'textStyle.font.size'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value),
        ],
        assertEqual: '100.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'textStyle.font.size',
          toggleClickType: ToggleClick.Close
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value),
        ],
        assertEqual: '16.00fp'
      })

      done();
    })

    // textStyle.font.weight
    it('ArkUI_CalendarPicker_013', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Normal'
      })

      done();
    })

    it('ArkUI_CalendarPicker_014', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Lighter'
      })

      done();
    })

    it('ArkUI_CalendarPicker_015', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bolder'
      })

      done();
    })

    it('ArkUI_CalendarPicker_016', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bold'
      })

      done();
    })

    it('ArkUI_CalendarPicker_017', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    it('ArkUI_CalendarPicker_018', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    // CalendarOptions(未找到该属性)
    it('ArkUI_CalendarPicker_019', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'CalendarOptions'
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'CalendarOptions',
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    // CalendarOptions.start(未找到该属性)
    it('ArkUI_CalendarPicker_020', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.start')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.start'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_021', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.start')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.start'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_022', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.start')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.start'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_023', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.start')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.start'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_024', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.start')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.start'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_025', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.start')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.start',
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
    // CalendarOptions.end(未找到该属性)
    it('ArkUI_CalendarPicker_026', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.end')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.end'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_027', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.end')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.end'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_028', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.end')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.end'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_029', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.end')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.end'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_030', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.end')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.end'
        }
      })

      done();
    })

    it('ArkUI_CalendarPicker_031', 0, async (done: Function) => {

      await Search('参数列表', 'CalendarOptions.end')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'CalendarOptions.end',
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
  })
}