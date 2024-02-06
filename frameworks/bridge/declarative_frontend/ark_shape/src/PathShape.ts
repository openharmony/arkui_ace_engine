/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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


interface PathShapeOptions {
    commands?: string;
}

declare class __PathShape__<T> {
    constructor(options: PathShapeOptions);
    offset(offset: Position): T;
    fill(color: number | string): T;
    position(position: Position): T;
    commands(commands: string): T;
}

class PathShape extends __PathShape__<PathShape> {
    constructor(options: PathShapeOptions) {
        super(options);
    }

    offset(offset: Position): PathShape {
        return super.offset(offset);
    }

    fill(width: string | number): PathShape {
        return super.fill(width);
    }

    position(position: Position): PathShape {
        return super.position(position);
    }

    commands(commands: string): PathShape {
        return super.commands(commands);
    }
}