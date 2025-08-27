import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import { UIContext, FrameCallback } from '@ohos.arkui.UIContext'
import common from '@ohos.app.ability.common';
import { FrameNode } from '@ohos.arkui.node';
import { Size } from '@ohos.arkui.node';
import { Router } from '@ohos.arkui.UIContext';

@Component
export struct GetHostContextTest {
  @State stateVar: string = 'state var'; 
  message: string = 'var';
  changeValue() {
    this.stateVar+='~'
  }
  build() {
    NavDestination() {
      Column(undefined) {
        Button('getHostContext功能测试')
          .backgroundColor('#FFFF00FF')
          .onClick((e: ClickEvent) => {
            let uicontext = this.getUIContext();
            if (uicontext) {
              let host_context = uicontext.getHostContext()
              if (host_context) {
                let context = host_context! as common.UIAbilityContext;
                if (context) {
                  hilog.info(0x0000, 'testTag', 'wll context' + context?.filesDir);
                } else {
                  hilog.info(0x0000, 'testTag', 'wll context null ');
                }
              }
            }
          })
      }
    }
    .title('getHostContext功能测试')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}