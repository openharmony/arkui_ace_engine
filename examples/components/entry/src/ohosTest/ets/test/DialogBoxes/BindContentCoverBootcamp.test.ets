import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  Search,
  ToggleClick
} from '../../utils';
import { Point } from '@ohos.UiTest';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();
export default function BindContentCoverBootcampTest() {
  describe('BindContentCoverBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);

        let ListItemGroup :Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width:Point = await ListItemGroup[0].getBoundsCenter()
        let width2:Point = await ListItemGroup[4].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(2000);

        let atomDisplays:Component = await driver.findComponent(ON.text('弹窗'));
        await atomDisplays.click();
        await driver.delayMs(3000);
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)


        let ListItemGroup1 :Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3:Point = await ListItemGroup1[0].getBoundsCenter()
        let width4:Point = await ListItemGroup1[2].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(2000);

        let scrollSearch:Component = await driver.findComponent(ON.text('全模态/BindContentCover'))
        await scrollSearch.click()
        await driver.delayMs(2000);

        let Buttons:Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(2000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })


    it('ArkUI_BindContentCover_001', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.modalTransition')
      await radioClick({
        radioClickObj: 0
      })
      done()
    })

    it('ArkUI_BindContentCover_002', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.modalTransition')
      await radioClick({
        radioClickObj: 1
      })
      done()
    })

    it('ArkUI_BindContentCover_003', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.modalTransition')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_BindContentCover_004', 0, async (done: Function) => {
      await Search('参数列表', 'backGroundColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done()
    })

    it('ArkUI_BindContentCover_005', 0, async (done: Function) => {
      await Search('参数列表', 'backGroundColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done()
    })

    it('ArkUI_BindContentCover_006', 0, async (done: Function) => {
      await Search('参数列表', 'backGroundColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done()
    })

    it('ArkUI_BindContentCover_007', 0, async (done: Function) => {
      await Search('参数列表', 'backGroundColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done()
    })

    it('ArkUI_BindContentCover_008', 0, async (done: Function) => {
      await Search('参数列表', 'backGroundColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done()
    })

    it('ArkUI_BindContentCover_009', 0, async (done: Function) => {
      await Search('参数列表', 'backGroundColor')
      await buttonClick({
        buttonClickObj: 5
      })
      done()
    })

    it('ArkUI_BindContentCover_010', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.opacity')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_011', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.translate.x')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_012', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.translate.y')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_013', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.translate.z')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_014', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.scale.x')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_015', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.scale.y')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_016', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.scale.z')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_017', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.scale.centerX')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_018', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.scale.centerY')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_019', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.rotate.x')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_020', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.rotate.y')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_021', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.rotate.z')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_022', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.rotate.centerX')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_023', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.rotate.centerY')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_024', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.rotate.centerZ')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_025', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.rotate.perspective')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_026', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.move')
      await radioClick({
        radioClickObj: 0
      })
      done()
    })

    it('ArkUI_BindContentCover_027', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.move')
      await radioClick({
        radioClickObj: 1
      })
      done()
    })

    it('ArkUI_BindContentCover_028', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.move')
      await radioClick({
        radioClickObj: 2
      })
      done()
    })

    it('ArkUI_BindContentCover_029', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.move')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_BindContentCover_030', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.duration')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_031', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.tempo')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_032', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 0
      })

      done()
    })

    it('ArkUI_BindContentCover_033', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 1
      })

      done()
    })

    it('ArkUI_BindContentCover_034', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 2
      })

      done()
    })

    it('ArkUI_BindContentCover_035', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 3
      })

      done()
    })

    it('ArkUI_BindContentCover_036', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 4
      })

      done()
    })

    it('ArkUI_BindContentCover_037', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 5
      })

      done()
    })

    it('ArkUI_BindContentCover_038', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 6
      })

      done()
    })

    it('ArkUI_BindContentCover_039', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 7
      })

      done()
    })

    it('ArkUI_BindContentCover_040', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 8
      })

      done()
    })

    it('ArkUI_BindContentCover_041', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 9
      })

      done()
    })

    it('ArkUI_BindContentCover_042', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 10
      })

      done()
    })

    it('ArkUI_BindContentCover_043', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 11
      })

      done()
    })

    it('ArkUI_BindContentCover_044', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.curve')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_BindContentCover_045', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.delay')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_046', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.iterations')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_047', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.playMode')
      await radioClick({
        radioClickObj: 0,

      })

      done()
    })

    it('ArkUI_BindContentCover_048', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.playMode')
      await radioClick({
        radioClickObj: 1,

      })

      done()
    })

    it('ArkUI_BindContentCover_049', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.playMode')
      await radioClick({
        radioClickObj: 2,

      })

      done()
    })

    it('ArkUI_BindContentCover_050', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.playMode')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_BindContentCover_051', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.expectedFrameRateRange.max')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'bindContentCover.options.transition.animation.expectedFrameRateRange.max'
        }
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'bindContentCover.options.transition.animation.expectedFrameRateRange.max'
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_052', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.expectedFrameRateRange.min')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'bindContentCover.options.transition.animation.expectedFrameRateRange.min'
        }
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'bindContentCover.options.transition.animation.expectedFrameRateRange.min'
        }

      })
      done()
    })

    it('ArkUI_BindContentCover_053', 0, async (done: Function) => {
      await Search('参数列表', 'bindContentCover.options.transition.animation.expectedFrameRateRange.expected')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'bindContentCover.options.transition.animation.expectedFrameRateRange.expected'
        }
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'bindContentCover.options.transition.animation.expectedFrameRateRange.expected'
        }

      })
      done()
    })
  })
}