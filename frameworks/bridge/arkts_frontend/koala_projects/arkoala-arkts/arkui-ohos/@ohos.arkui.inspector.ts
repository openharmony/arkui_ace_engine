import { Callback } from '@ohos.base';
declare namespace inspector {
    export interface ComponentObserver {
        on(type: 'layout' | 'draw' | 'drawChildren', callback: Callback<void>): void;

        off(type: 'layout' | 'draw' | 'drawChildren', callback?: Callback<void>): void;

        onLayout(type: 'layout', callback: Callback<void>): void;

        offLayout(type: 'layout', callback?: Callback<void>): void;

        onDraw(type: 'draw', callback: Callback<void>): void;

        offDraw(type: 'draw', callback?: Callback<void>): void;

        onDrawChildren(type: 'drawChildren', callback: Callback<void>): void;

        offDrawChildren(type: 'drawChildren', callback?: Callback<void>): void;
    }
    export function createComponentObserver(id: string): ComponentObserver | undefined;
    export function getFilteredInspectorTree(filters?: Array<string>): string;
    export function getFilteredInspectorTreeById(id: string, depth: number, filters?: Array<string>): string;
}
export default inspector;