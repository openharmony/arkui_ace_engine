import { NavPathStack } from '@ohos.arkui.component'

export interface routerParam {
  data: string
}

export class NavigationParam {
  private info_: string = '';
  public params: routerParam = {
    data: 'test'
  }
  constructor(info: string) {
    this.info_ = info;
  }
}

export let pathStack: NavPathStack = new NavPathStack();