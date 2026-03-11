/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
/// <reference path="./component_content.ts" />
function createComponentContentByTrans(uiContext: UIContext, nodePtr: number, frameNodePtr: number): TransComponentContent {
    return new TransComponentContent(uiContext, nodePtr, frameNodePtr);
}

class TransComponentContent extends ComponentContent {
    constructor(uiContext: UIContext, nodePtr: number, frameNodePtr: number) {
        super(uiContext, undefined, undefined, undefined, nodePtr, frameNodePtr);
    }

    public isTransferred(): boolean {
        return true;
    }

    public reuse(param: Object): void {
        throw new BusinessError(100031, 'componentContent created by transferDynamic not support reuse');
    }

    public update(params: Object): void {
        throw new BusinessError(100031, 'componentContent created by transferDynamic not support update');
    }

    public recycle(): void {
        throw new BusinessError(100031, 'componentContent created by transferDynamic not support recycle');
    }

    public updateConfiguration(): void {
        throw new BusinessError(100031, 'componentContent created by transferDynamic not support updateConfiguration');
    }

    public inheritFreezeOptions(enable: boolean): void {
        throw new BusinessError(100031, 'componentContent created by transferDynamic not support inheritFreezeOptions');
    }
}
