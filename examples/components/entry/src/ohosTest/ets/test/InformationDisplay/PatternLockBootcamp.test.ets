import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  Search,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  titleSearch,
  searchToggle,
  getToggle,
  searchParentBlock
} from '../../utils';
import { Point } from '@ohos.UiTest';


const TAG = 'AdvancedCounterBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function PatternLockBootcampTest() {
  describe('PatternLockBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async(done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'GaugeBootcamp001' + ' begin');

        let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
        let ListItemGroup2: Point = await ListItemGroup[2].getBoundsCenter()
        await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 2000)
        await driver.delayMs(1000);


        let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[2].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 2000)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('图案密码锁/PatternLock'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);

      done();
    })

    // sideLength
    it('ArkUI_PatternLock_001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'sideLength')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sideLength', JsonType.value),
        ],
        assertEqual: '288.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sideLength', JsonType.value),
        ],
        assertEqual: '200.00vp'
      })

      done();
    })

    // circleRadius
    it('ArkUI_PatternLock_002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'circleRadius')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('circleRadius', JsonType.value),
        ],
        assertEqual: '24.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('circleRadius', JsonType.value),
        ],
        assertEqual: '6.00vp'
      })

      done();
    })

    // pathStrokeWidth
    it('ArkUI_PatternLock_003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pathStrokeWidth')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pathStrokeWidth', JsonType.value),
        ],
        assertEqual: '16.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pathStrokeWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

    // regularColor
    it('ArkUI_PatternLock_004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'regularColor')

      await buttonClick({
        buttonClickObj:0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('regularColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_PatternLock_005', 0, async (done: Function) => {

      await titleSearch('参数列表', 'regularColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('regularColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_PatternLock_006', 0, async (done: Function) => {

      await titleSearch('参数列表', 'regularColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('regularColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_PatternLock_007', 0, async (done: Function) => {

      await titleSearch('参数列表', 'regularColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('regularColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_PatternLock_008', 0, async (done: Function) => {

      await titleSearch('参数列表', 'regularColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('regularColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_PatternLock_009', 0, async (done: Function) => {

      await titleSearch('参数列表', 'regularColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('regularColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // activeColor
    it('ArkUI_PatternLock_010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'activeColor')

      await buttonClick({
        buttonClickObj:0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('activeColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_PatternLock_011', 0, async (done: Function) => {

      await titleSearch('参数列表', 'activeColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('activeColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_PatternLock_012', 0, async (done: Function) => {

      await titleSearch('参数列表', 'activeColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('activeColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_PatternLock_013', 0, async (done: Function) => {

      await titleSearch('参数列表', 'activeColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('activeColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_PatternLock_014', 0, async (done: Function) => {

      await titleSearch('参数列表', 'activeColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('activeColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_PatternLock_015', 0, async (done: Function) => {

      await titleSearch('参数列表', 'activeColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('activeColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // selectedColor
    it('ArkUI_PatternLock_016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj:0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'selectedColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_PatternLock_017', 0, async (done: Function) => {

      await titleSearch('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_PatternLock_018', 0, async (done: Function) => {

      await titleSearch('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'selectedColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_PatternLock_019', 0, async (done: Function) => {

      await titleSearch('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'selectedColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_PatternLock_020', 0, async (done: Function) => {

      await titleSearch('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'selectedColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_PatternLock_021', 0, async (done: Function) => {

      await titleSearch('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'selectedColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // pathColor
    it('ArkUI_PatternLock_022', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pathColor')

      await buttonClick({
        buttonClickObj:0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pathColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pathColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_PatternLock_023', 0, async (done: Function) => {

      await titleSearch('参数列表', 'pathColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'pathColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pathColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_PatternLock_024', 0, async (done: Function) => {

      await titleSearch('参数列表', 'pathColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'pathColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pathColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_PatternLock_025', 0, async (done: Function) => {

      await titleSearch('参数列表', 'pathColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'pathColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pathColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_PatternLock_026', 0, async (done: Function) => {

      await titleSearch('参数列表', 'pathColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'pathColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pathColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_PatternLock_027', 0, async (done: Function) => {

      await titleSearch('参数列表', 'pathColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'pathColor'
        },
        id: 'PatternLock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pathColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // activateCircleStyle
    it('ArkUI_PatternLock_028', 0, async (done: Function) => {

      await titleSearch('参数列表', 'activateCircleStyle')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'activateCircleStyle'
        }
      })

      done();

    })

    it('ArkUI_PatternLock_029', 0, async (done: Function) => {

      await titleSearch('参数列表', 'activateCircleStyle')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'activateCircleStyle'
        }
      })

      done();

    })

    // activateCircleStyle.color
    it('ArkUI_PatternLock_030', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('activateCircleStyle.color'))

      if (!title){

        await Search('参数列表', 'activateCircleStyle')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
            toggleClickObj: 'activateCircleStyle'
          }
        })

      }

      await titleSearch('参数列表', 'activateCircleStyle.color')

      await buttonClick({
        buttonClickObj:0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      done();

    })

    it('ArkUI_PatternLock_031', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('activateCircleStyle.color'))

      if (!title){

        await Search('参数列表', 'activateCircleStyle')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
            toggleClickObj: 'activateCircleStyle'
          }
        })

      }

      await titleSearch('参数列表', 'activateCircleStyle.color')

      await buttonClick({
        buttonClickObj:1,
      })

      done();

    })

    it('ArkUI_PatternLock_032', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('activateCircleStyle.color'))

      if (!title){

        await Search('参数列表', 'activateCircleStyle')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
            toggleClickObj: 'activateCircleStyle'
          }
        })

      }

      await titleSearch('参数列表', 'activateCircleStyle.color')

      await buttonClick({
        buttonClickObj:2,
      })

      done();

    })

    it('ArkUI_PatternLock_033', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('activateCircleStyle.color'))

      if (!title){

        await Search('参数列表', 'activateCircleStyle')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
            toggleClickObj: 'activateCircleStyle'
          }
        })

      }

      await titleSearch('参数列表', 'activateCircleStyle.color')

      await buttonClick({
        buttonClickObj:3,
      })

      done();

    })

    it('ArkUI_PatternLock_034', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('activateCircleStyle.color'))

      if (!title){

        await Search('参数列表', 'activateCircleStyle')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
            toggleClickObj: 'activateCircleStyle'
          }
        })

      }

      await titleSearch('参数列表', 'activateCircleStyle.color')

      await buttonClick({
        buttonClickObj:4,
      })

      done();

    })

    it('ArkUI_PatternLock_035', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('activateCircleStyle.color'))

      if (!title){

        await Search('参数列表', 'activateCircleStyle')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
            toggleClickObj: 'activateCircleStyle'
          }
        })

      }

      await titleSearch('参数列表', 'activateCircleStyle.color')

      await buttonClick({
        buttonClickObj:5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })

  })
}