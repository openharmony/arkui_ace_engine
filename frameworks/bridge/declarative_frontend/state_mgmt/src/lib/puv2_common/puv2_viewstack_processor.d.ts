/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

/**
 * ViewStackProcessor declaration
 *
 * Implemntation in C+ and exposed to JS
 *
 * all definitions in this file are framework internal
 */

declare class ViewStackProcessor {

  // make and return new elementId
  // will be used to create the next Component
  // this is used for first rneder case
  public static AllocateNewElmetIdForNextComponent(): number;

  // start Get access recording, and account all access to given elmtId
  // Note this can be a different elmtId than the one used to create new Component
  public static StartGetAccessRecordingFor(elmtId: number): void;

  /**
   * get the elmtId to which any get access shoudl be accounted
   * note this can be the same as the currently created elmtId (top of stack)
   * but also a different one (in case a whole subtree gets accounted its root elmtId)
   *
   * returns the elmtId given by StartGetAccessRecordingFor
   * -1 no access recording
   */
  public static GetElmtIdToAccountFor(): number;

  // Stop get access recording
  // also invalidates any reserved but unclaimed elmtId for Component creation
  public static StopGetAccessRecording(): void;


  /**
   * when nesting observeComponentCreation functions, such as in the case of
   * If, and the if branch creates a Text etc that requires an implict pop
   *  this function is needed after executing the inner observeComponentCreation
   *  and before read ViewStackProcessor.GetTopMostElementId(); on the outer one
   */
  public static ImplicitPopBeforeContinue(): void;

  /**
   * Called once JS update function has been executed, main component
   * and its wrapping components in the stack need to be 'Finished'
   * and then a local update be done on given main Element and
   * wrapping Elements
   * @param elmtId
   */
  public static FinishAndLocalUpdate(elmtId: number): void;


  /**
   * Returns a globally unique id from ElementRegister
   * JS signatire: MakeUniqueId() : number
  */
  public static MakeUniqueId(): number;

  /**
   * return true if the current Container uses PartialUpdate code path
   * see Container class foundation/arkui/ace_engine/frameworks/core/common/container.h
   * calls UsesNewPipeline static function
   */
  public static UsesNewPipeline();

  // Gets the framenode with tag and elmtId then pushes to the view stack.
  public static GetAndPushFrameNode(tag: string, elmtId: number): void;

  // move deleted elmtIds from ElementRegistery in C++ to the caller
  public static moveDeletedElmtIds(elmtIds : Array<number>);

  /**
   * Orders frame and registers for update on next vsync.
   * PipelineContext passes the containerId in the callback.
  */
  public static scheduleUpdateOnNextVSync(cbFunc: ((containerId: number) => boolean) | null, containerId?: number): void;

  // get Api version
  public static getApiVersion(): number;

  public static PushPrebuildCompCmd(): void;

  public static CheckIsPrebuildTimeout(): boolean;

  // get send state info to profiler
  public static sendStateInfo(stateInfo: string): void;
  
  public static push(pointer: number): void;

  public static pop(): void;
}