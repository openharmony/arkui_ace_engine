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

// real implemntation in C+ and exposed to JS
// and mock implementation for testing
class ViewStackProcessor {

    // make and return new elementId
    // will be used to create the next Component
    // this is used for first rneder case
    public static AllocateNewElmetIdForNextComponent(): number {
        return -1;
    }
  
    // start Get access recording, and account all access to given elmtId
    // Note this can be a different elmtId than the one used to create new Component
    public static StartGetAccessRecordingFor(elmtId: number): void {
    }
  
    /**
     * get the elmtId to which any get access shoudl be accounted
     * note this can be the same as the currently created elmtId (top of stack)
     * but also a different one (in case a whole subtree gets accounted its root elmtId)
     * 
     * returns the elmtId given by StartGetAccessRecordingFor
     * -1 no access recording
     */
    public static GetElmtIdToAccountFor(): number {
        return -1;
    }
  
    // Stop get access recording 
    // also invalidates any reserved but unclaimed elmtId for Component creation
    public static StopGetAccessRecording(): void {
    }
  
  
    /**
     * when nesting observeComponentCreation functions, such as in the case of
     * If, and the if branch creates a Text etc that requires an implict pop
     *  this function is needed after executing the inner observeComponentCreation
     *  and before read ViewStackProcessor.GetTopMostElementId(); on the outer one
     */
    public static ImplicitPopBeforeContinue(): void {
    }
  
    /**
     * Called once JS update function has been executed, main component
     * and its wrapping components in the stack need to be 'Finished'
     * and then a local update be done on given main Element and
     * wrapping Elements
     */
    public static FinishAndLocalUpdate(elmtId: number): void  { 
    }

    static MakeUniqueId() : number {
        return ViewStackProcessor.nextId++
    }

    private static nextId : number = 1;
  }
  