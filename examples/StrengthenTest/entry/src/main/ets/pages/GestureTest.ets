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
  TapGesture,
  GestureGroup,
  GestureMask,
  GestureEvent,
  LongPressGesture,
  PanGesture,
  PinchGesture,
  GestureMode,
  SourceTool,
  SwipeGesture,
  RotationGesture,
  SwipeDirection,
  PanGestureOptions,
  PanGestureHandlerOptions,
  PanDirection,
  Row,
  GestureInfo,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Component
export struct GestureTest {
  @State stateVar: string = 'state var';
  message: string = 'var';
  panOptionNormal: PanGestureOptions = new PanGestureOptions({
    fingers: 2,
    distance: 5,
    direction: PanDirection.Horizontal,
    isFingerCountLimited: true
  })

  panOptionAbnormal: PanGestureOptions = new PanGestureOptions({ 
    fingers: -1,
    distance: -1,
    direction: undefined,
    isFingerCountLimited: undefined
  })

  aboutToAppear() {
    this.panOptionNormal.setFingers(1);
    this.panOptionNormal.setDistance(10);
    this.panOptionNormal.setDirection(PanDirection.Right)
    let direction = this.panOptionNormal.getDirection()
    let distance = this.panOptionNormal.getDistance()
    hilog.info(0x0000, 'testTag', 'zcb aboutToAppear panOptionNormal direction ' + direction + ' distance ' + distance);
  }
  changeValue() {
    this.stateVar+='~'
  }
  build() {
    NavDestination() {
      Column(undefined) {
        Row(undefined) {
          Button('Normal tap').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              TapGesture({
                fingers: 1,
                count: 1,
                distanceThreshold: 10,
                isFingerCountLimited: true
              })
                .onAction((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal tap trigger ' + JSON.stringify(event) + ' repeat: ' + event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal tap baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal tap getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal tap target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal tap fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal tap fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
          Button('Abnormal tap').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              TapGesture({
                fingers: -1,
                count: -1,
                distanceThreshold: undefined,
                isFingerCountLimited: undefined
              })
                .onAction((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal tap trigger ' + JSON.stringify(event) + ' repeat: ' + event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal tap baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal tap getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal tap target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal tap fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal tap fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
        }

        Row(undefined) {
          Button('Normal longpress').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              LongPressGesture({
                fingers: 1,
                repeat: true,
                duration: 500,
                isFingerCountLimited: true
              })
                .onAction((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress trigger onAction ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal longpress getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal longpress fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal longpress fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal longpress getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal longpress fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal longpress fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' +
                    event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal longpress getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal longpress target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal longpress fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal longpress fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
          Button('Abnormal longpress').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              LongPressGesture({
                fingers: -1,
                repeat: undefined,
                duration: -1,
                isFingerCountLimited: undefined
              })
                .onAction((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress trigger ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal longpress getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal longpress fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal longpress fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal longpress getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal longpress fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal longpress fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' +
                    event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal longpress getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal longpress target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal longpress fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal longpress fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
        }

        Row(undefined) {
          Button('Normal swipe').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              SwipeGesture({
                fingers: 1,
                speed: 100,
                direction: SwipeDirection.Horizontal,
                isFingerCountLimited: true
              })
                .onAction((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal swipe trigger ' + JSON.stringify(event) + ' repeat: ' + event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal swipe baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal swipe getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal swipe target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal swipe fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal swipe fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
          Button('Abnormal swipe').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              SwipeGesture({
                fingers: -1,
                speed: -1,
                direction: undefined,
                isFingerCountLimited: undefined
              })
                .onAction((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal swipe trigger ' + JSON.stringify(event) + ' repeat: ' + event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal swipe baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal swipe getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal swipe target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal swipe fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal swipe fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
        }

        Row(undefined) {
          Button('Normal pan').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              PanGesture({
                fingers: 1,
                distance: 5,
                direction: PanDirection.Right,
                isFingerCountLimited: true
              } as PanGestureHandlerOptions)
                .onActionStart((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan trigger onActionStart ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan trigger onActionUpdate ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
          Button('Abnormal pan').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              PanGesture({
                fingers: -1,
                distance: -1,
                direction: undefined,
                isFingerCountLimited: undefined
              } as PanGestureHandlerOptions)
                .onActionStart((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan trigger onActionStart ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan trigger onActionUpdate ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
        }

        Row(undefined) {
          Button('Normal pan with panGestureOptions').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              PanGesture(this.panOptionNormal)
                .onActionStart((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan trigger onActionStart ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan trigger onActionUpdate ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
          Button('Abnormal pan with panGestureOptions').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              PanGesture(this.panOptionAbnormal)
                .onActionStart((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan trigger onActionStart ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan trigger onActionUpdate ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pan getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pan target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pan fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pan fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
        }

        Row(undefined) {
          Button('Normal pinch').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              PinchGesture({ fingers: 1, distance: 10, isFingerCountLimited: true })
                .onActionStart((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch trigger onActionStart ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pinch getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pinch fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pinch fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch trigger onActionUpdate ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pinch getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pinch fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pinch fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pinch getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pinch fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pinch fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal pinch getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal pinch target width ' + event.target.area.width + ' height ' + event.target.area.height +
                      ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal pinch fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal pinch fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
          Button('Abnormal pinch').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              PinchGesture({ fingers: -1, distance: -1, isFingerCountLimited: undefined })
                .onActionStart((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch trigger onActionStart ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pinch getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pinch fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pinch fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch trigger onActionUpdate ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pinch getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pinch fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pinch fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pinch getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pinch fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pinch fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal pinch getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal pinch target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal pinch fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal pinch fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
        }

        Row(undefined) {
          Button('Normal rotation').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              RotationGesture({ fingers: 1, angle: 10, isFingerCountLimited: true })
                .onActionStart((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation trigger onActionStart ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal rotation getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal rotation fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal rotation fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation trigger onActionUpdate ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal rotation getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal rotation fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal rotation fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal rotation getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal rotation fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal rotation fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Normal rotation getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Normal rotation target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Normal rotation fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Normal rotation fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
          Button('Abnormal rotation').backgroundColor('#FFFF00FF')
            .width(180)
            .height(50)
            .gesture(
              RotationGesture({ fingers: -1, angle: -1, isFingerCountLimited: undefined })
                .onActionStart((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation trigger onActionStart ' + JSON.stringify(event) + ' repeat: ' +
                    event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal rotation getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal rotation fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal rotation fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation trigger onActionUpdate ' + JSON.stringify(event) + ' repeat: ' +
                    event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal rotation getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal rotation fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal rotation fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionCancel((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation trigger onActionCancel ' + JSON.stringify(event) + ' repeat: ' +
                    event.repeat + ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal rotation getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal rotation fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal rotation fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .onActionEnd((event: GestureEvent) => {
                  this.changeValue()
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation trigger onActionEnd ' + JSON.stringify(event) + ' repeat: ' + event.repeat +
                      ' offsetX: ' +
                    event.offsetX + ' offsetY: ' + event.offsetY + ' angle: ' + event.angle + ' speed: ' + event.speed +
                      ' scale: ' +
                    event.scale + ' pinchCenterX: ' + event.pinchCenterX + ' pinchCenterY: ' +
                    event.pinchCenterY + ' velocityX: ' + event.velocityX + ' velocityY: ' + event.velocityY +
                      ' velocity: ' + event.velocity);
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation baseEvent timestamp ' + event.timestamp + ' source ' + event.source +
                      ' axisHorizontal ' +
                    event.axisHorizontal + ' axisVertical ' + event.axisVertical + ' pressure ' + event.pressure +
                      ' tiltX ' +
                    event.tiltX + ' tiltY ' + event.tiltY + ' sourceTool ' + event.sourceTool + ' deviceId ' +
                    event.deviceId + ' targetDisplayId ' + event.targetDisplayId)
                  let keyArray: string[] = ["Shift"];
                  if (event.getModifierKeyState !== undefined) {
                    const modifierState = event.getModifierKeyState as (keys: Array<string>) => boolean;
                    let result = modifierState(keyArray)
                    hilog.info(0x0000, 'testTag', 'zcb  Abnormal rotation getModifierKeyState ' + result);
                  }
                  hilog.info(0x0000, 'testTag',
                    'zcb Abnormal rotation target width ' + event.target.area.width + ' height ' +
                    event.target.area.height + ' x ' +
                    event.target.area.position.x + ' y ' + event.target.area.position.y + ' globalX ' +
                    event.target.area.globalPosition.x + ' globalY ' + event.target.area.globalPosition.y)
                  hilog.info(0x0000, 'testTag', 'zcb Abnormal rotation fingerList.length ' + event.fingerList.length);
                  for (let i = 0; i < event.fingerList.length; i++) {
                    hilog.info(0x0000, 'testTag',
                      'zcb Abnormal rotation fingerList[i]' + i + ' id ' + event.fingerList[i].id + ' globalX ' +
                      event.fingerList[i].globalX + ' globalY ' + event.fingerList[i].globalY + ' localX ' +
                      event.fingerList[i].localX + ' localY ' + event.fingerList[i].localY + ' displayX ' +
                      event.fingerList[i].displayX + ' displayY ' + event.fingerList[i].displayY + ' hand ' +
                      event.fingerList[i].hand);
                  }
                })
                .tag('aaa')
                .allowedTypes([SourceTool.Finger])
            )
        }

        Button('multi group').backgroundColor('#FFFF00FF')
          .width(180)
          .height(50)
          .gesture(GestureGroup(GestureMode.Parallel,
            GestureGroup(GestureMode.Exclusive,
              GestureGroup(GestureMode.Sequence,
                LongPressGesture()
                  .onAction((event: GestureEvent) => {
                    hilog.info(0x0000, 'testTag', 'zcb LongPressGesture trigger');
                  }),
                PanGesture()
                  .onActionStart((event: GestureEvent) => {
                    hilog.info(0x0000, 'testTag', 'zcb PanGesture trigger');
                  })
              ),
              TapGesture()
                .onAction((event: GestureEvent) => {
                  hilog.info(0x0000, 'testTag', 'zcb TapGesture trigger');
                })
            ),
            TapGesture()
              .onAction((event: GestureEvent) => {
                hilog.info(0x0000, 'testTag', 'zcb TapGesture trigger');
              })
          ))

        Column(undefined) {
          Button('test mask')
            .width(180)
            .height(50)
            .onClick((event: ClickEvent) => {
              hilog.info(0x0000, 'testTag', 'zcb child click trigger');
            })
        }
        .parallelGesture(
          TapGesture()
            .onAction((event: GestureEvent) => {
              hilog.info(0x0000, 'testTag', 'zcb father click trigger');
            }), GestureMask.IgnoreInternal
        )

        Column(undefined) {
          Button('test priority binding')
            .width(180)
            .height(50)
            .onClick((event: ClickEvent) => {
              hilog.info(0x0000, 'testTag', 'zcb child click trigger');
            })
        }
        .parallelGesture(
          TapGesture()
            .onAction((event: GestureEvent) => {
              hilog.info(0x0000, 'testTag', 'zcb father click trigger');
            })
        )
        .gesture(
          LongPressGesture()
            .onAction((event: GestureEvent) => {
              hilog.info(0x0000, 'testTag', 'zcb LongPressGesture trigger');
            })
        )
        .priorityGesture(
          PanGesture()
            .onActionStart((event: GestureEvent) => {
              hilog.info(0x0000, 'testTag', 'zcb PanGesture trigger');
            })
        )


        Text(this.stateVar).fontSize(20)
        Child({ stateVar: this.stateVar } as __Options_Child)
      }
    }
    .title('手势基础功能测试用例')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
