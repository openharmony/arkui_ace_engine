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


const TAG = 'ProgressBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function ProgressBootcampTest() {
  describe('ProgressBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {
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

        let scrollSearch: Component = await driver.findComponent(ON.text('进度条/Progress'))
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

    // progressOptions.value
    it('ArkUI_Progress_001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressOptions.value')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();
    })

    // progressOptions.type
    it('ArkUI_Progress_002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressOptions.type')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ProgressStyle.Linear'
      })

      done();
    })

    it('ArkUI_Progress_003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressOptions.type')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ProgressStyle.Ring'
      })

      done();
    })

    it('ArkUI_Progress_004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressOptions.type')

      await radioClick({
        radioClickObj: 2,
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ProgressStyle.Eclipse'
      })

      done();
    })

    it('ArkUI_Progress_005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressOptions.type')

      await radioClick({
        radioClickObj: 3,
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ProgressStyle.ScaleRing'
      })

      done();
    })

    it('ArkUI_Progress_006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressOptions.type')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ProgressStyle.Capsule'
      })

      done();
    })

    // progressOptions.total
    it('ArkUI_Progress_007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressOptions.total')
      // 设置total取值无效果
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // value
    it('ArkUI_Progress_008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'value')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })

    // color
    it('ArkUI_Progress_009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_Progress_010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_Progress_011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Progress_012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_Progress_013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_Progress_014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // capsuleStyleOptions.borderColor
    it('ArkUI_Progress_015', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.borderColor')
      // capsuleStyleOptions.borderColor设置取值无变化

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    it('ArkUI_Progress_016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.borderColor')
      // capsuleStyleOptions.borderColor设置取值无变化

      await buttonClick({
        buttonClickObj: 1,
      })

      done();
    })

    it('ArkUI_Progress_017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.borderColor')
      // capsuleStyleOptions.borderColor设置取值无变化

      await buttonClick({
        buttonClickObj: 2,
      })

      done();
    })

    it('ArkUI_Progress_018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.borderColor')
      // capsuleStyleOptions.borderColor设置取值无变化

      await buttonClick({
        buttonClickObj: 3,
      })

      done();
    })

    it('ArkUI_Progress_019', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.borderColor')
      // capsuleStyleOptions.borderColor设置取值无变化

      await buttonClick({
        buttonClickObj: 4,
      })

      done();
    })

    it('ArkUI_Progress_020', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.borderColor')
      // capsuleStyleOptions.borderColor设置取值无变化

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })

    // capsuleStyleOptions.borderWidth
    it('ArkUI_Progress_021', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.borderWidth')
      // capsuleStyleOptions.borderWidth设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // capsuleStyleOptions.font
    it('ArkUI_Progress_022', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.font')
      // capsuleStyleOptions.font 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // capsuleStyleOptions.fontColor
    it('ArkUI_Progress_023', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.fontColor')
      // capsuleStyleOptions.fontColor 设置取值无变化

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    it('ArkUI_Progress_024', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.fontColor')
      // capsuleStyleOptions.fontColor 设置取值无变化

      await buttonClick({
        buttonClickObj: 1,
      })

      done();
    })

    it('ArkUI_Progress_025', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.fontColor')
      // capsuleStyleOptions.fontColor 设置取值无变化

      await buttonClick({
        buttonClickObj: 2,
      })

      done();
    })

    it('ArkUI_Progress_026', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.fontColor')
      // capsuleStyleOptions.fontColor 设置取值无变化

      await buttonClick({
        buttonClickObj: 3,
      })

      done();
    })

    it('ArkUI_Progress_027', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.fontColor')
      // capsuleStyleOptions.fontColor 设置取值无变化

      await buttonClick({
        buttonClickObj: 4,
      })

      done();
    })

    it('ArkUI_Progress_028', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.fontColor')
      // capsuleStyleOptions.fontColor 设置取值无变化

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })

    // capsuleStyleOptions.showDefaultPercentage
    it('ArkUI_Progress_029', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.showDefaultPercentage')
      // capsuleStyleOptions.showDefaultPercentage 设置取值无变化

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    it('ArkUI_Progress_030', 0, async (done: Function) => {
      await titleSearch('参数列表', 'capsuleStyleOptions.showDefaultPercentage')
      // capsuleStyleOptions.showDefaultPercentage 设置取值无变化

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })

    // scaleRingStyleOptions.strokeWidth
    it('ArkUI_Progress_031', 0, async (done: Function) => {
      await titleSearch('参数列表', 'scaleRingStyleOptions.strokeWidth')
      // scaleRingStyleOptions.strokeWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // scaleRingStyleOptions.scaleWidth
    it('ArkUI_Progress_032', 0, async (done: Function) => {
      await titleSearch('参数列表', 'scaleRingStyleOptions.scaleWidth')
      // scaleRingStyleOptions.scaleWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // scaleRingStyleOptions.scaleCount
    it('ArkUI_Progress_033', 0, async (done: Function) => {
      await titleSearch('参数列表', 'scaleRingStyleOptions.scaleCount')
      // scaleRingStyleOptions.scaleWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // eclipseStyleOptions.enableSmoothEffect
    it('ArkUI_Progress_034', 0, async (done: Function) => {
      await titleSearch('参数列表', 'eclipseStyleOptions.enableSmoothEffect')
      // eclipseStyleOptions.enableSmoothEffect 设置取值无变化
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_Progress_035', 0, async (done: Function) => {
      await titleSearch('参数列表', 'eclipseStyleOptions.enableSmoothEffect')
      // eclipseStyleOptions.enableSmoothEffect 设置取值无变化
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // ringStyleOptions.strokeWidth
    it('ArkUI_Progress_036', 0, async (done: Function) => {
      await titleSearch('参数列表', 'ringStyleOptions.strokeWidth')
      // ringStyleOptions.strokeWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // ringStyleOptions.shadow
    it('ArkUI_Progress_037', 0, async (done: Function) => {
      await titleSearch('参数列表', 'ringStyleOptions.shadow')
      // ringStyleOptions.shadow 设置取值无变化
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_Progress_038', 0, async (done: Function) => {
      await titleSearch('参数列表', 'ringStyleOptions.shadow')
      // ringStyleOptions.shadow 设置取值无变化
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // ringStyleOptions.status
    it('ArkUI_Progress_039', 0, async (done: Function) => {
      await titleSearch('参数列表', 'ringStyleOptions.status')
      // ringStyleOptions.shadow 设置取值无变化
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    it('ArkUI_Progress_040', 0, async (done: Function) => {
      await titleSearch('参数列表', 'ringStyleOptions.status')
      // ringStyleOptions.shadow 设置取值无变化
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // linearStyleOptions.strokeWidth
    it('ArkUI_Progress_041', 0, async (done: Function) => {
      await titleSearch('参数列表', 'linearStyleOptions.strokeWidth')
      // ringStyleOptions.strokeWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })


    // linearStyleOptions.strokeRadius
    it('ArkUI_Progress_042', 0, async (done: Function) => {
      await titleSearch('参数列表', 'linearStyleOptions.strokeRadius')
      // ringStyleOptions.strokeWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // progressStyleOptions.strokeWidth
    it('ArkUI_Progress_043', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressStyleOptions.strokeWidth')
      // ringStyleOptions.strokeWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })


    // progressStyleOptions.scaleWidth
    it('ArkUI_Progress_044', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressStyleOptions.scaleWidth')
      // ringStyleOptions.strokeWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'progressStyleOptions.scaleWidth'
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'progressStyleOptions.scaleWidth'
        }
      })

      done();

    })
    // progressStyleOptions.scaleCount
    it('ArkUI_Progress_045', 0, async (done: Function) => {
      await titleSearch('参数列表', 'progressStyleOptions.scaleCount')
      // ringStyleOptions.strokeWidth 设置取值无变化
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'progressStyleOptions.scaleCount'
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'progressStyleOptions.scaleCount'
        }
      })

      done();

    })

    // layoutWeight
    it('ArkUI_Progress_046', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutWeight')
      // ringStyleOptions.shadow 设置取值无变化
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'layoutWeight'
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutWeight', JsonType.value),
        ],
        assertEqual: 1
      })

      done();

    })

    it('ArkUI_Progress_047', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutWeight')
      // ringStyleOptions.shadow 设置取值无变化
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'layoutWeight'
        },
        id: 'Progress',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutWeight', JsonType.value),
        ],
        assertEqual: 0
      })

      done();

    })
  })
}