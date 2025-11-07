import { Callback } from '@ohos.base';
declare namespace inspector {
    export interface ComponentObserver {
        on(type: 'layout' | 'draw' | 'drawChildren', callback: Callback<void>): void;

        off(type: 'layout' | 'draw' | 'drawChildren', callback?: Callback<void>): void;

        onLayout(callback: Callback<void>): void;

        offLayout(callback?: Callback<void>): void;

        onDraw(callback: Callback<void>): void;

        offDraw(callback?: Callback<void>): void;

        onDrawChildren(callback: Callback<void>): void;

        offDrawChildren(callback?: Callback<void>): void;
    }
    export function createComponentObserver(id: string): ComponentObserver | undefined;
    export function getFilteredInspectorTree(filters?: Array<string>): string;
    export function getFilteredInspectorTreeById(id: string, depth: number, filters?: Array<string>): string;
}
export default inspector;