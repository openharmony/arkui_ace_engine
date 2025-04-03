/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


export function isPadding(value: Length | Padding): value is Padding {
    let padding = value as Padding;
    return padding.bottom !== undefined
        || padding.left !== undefined
        || padding.right !== undefined
        || padding.top !== undefined;

}

export function isEdgeWidths(value: Length | EdgeWidths): value is EdgeWidths {
    let edges = value as EdgeWidths;
    return edges.bottom !== undefined
        || edges.left !== undefined
        || edges.right !== undefined
        || edges.top !== undefined;

}
export function isEdgeColors(value: EdgeColors | ResourceColor): value is EdgeColors {

    let edgeColors = value as EdgeColors;
    return edgeColors.bottom !== undefined
        || edgeColors.left !== undefined
        || edgeColors.right !== undefined
        || edgeColors.top !== undefined;

}

export function isResourceColor(value: ResourceColor): value is Resource {
    let color = value as Resource;
    return color?.id !== undefined
}

export function isResourceStr(value: ResourceStr): value is Resource {
    let str = value as Resource;
    return str.id !== undefined
}

export class SortedArray<T> {
    private backing = new Array<[T, number]>()

    public add(priority: number, value: T) {
        for (let i = 0; i < this.backing.length; i++) {
            if (this.backing[i][1] == priority) {
                this.backing[i][0] = value
                return
            }
        }
        this.backing.push([value, priority])
        this.backing.sort((a, b) => a[1] - b[1])
    }

    public find(priority: number): T|undefined {
        // TODO: binary search could be used here.
        for (let i = 0; i < this.backing.length; i++) {
            if (this.backing[i][1] > priority) return this.backing[i][0]
        }
        return undefined
    }
}