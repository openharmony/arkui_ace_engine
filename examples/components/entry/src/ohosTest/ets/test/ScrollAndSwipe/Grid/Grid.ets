
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';

const TAG = 'MarqueeBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export async function GridStart(done:Function){

  await delegator.startAbility({
    bundleName: 'cn.ohos.components',
    abilityName: 'EntryAbility'
  });

  await driver.delayMs(6000);
  console.info(TAG + 'GridBootcamp001' + ' begin');

  let atomDisplays: Component = await driver.findComponent(ON.text('滚动与滑动'));
  await atomDisplays.click();
  await driver.delayMs(1000);

  let scrollSearch: Component = await driver.findComponent(ON.text('网格/Grid'))
  await scrollSearch.click()
  await driver.delayMs(1000);
  let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
  await Buttons[1].click()
  await driver.delayMs(1000);

  console.info(`beforeAll end`);

  done()
}
