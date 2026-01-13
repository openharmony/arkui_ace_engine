import { VoidCallback } from 'arkui/component/units';
declare namespace inspector {
    export class ComponentObserver {
        on(type: 'layout' | 'draw' | 'drawChildren', callback: VoidCallback): void;

        off(type: 'layout' | 'draw' | 'drawChildren', callback?: VoidCallback): void;

        onLayout(callback: VoidCallback): void;

        offLayout(callback?: VoidCallback): void;

        onDraw(callback: VoidCallback): void;

        offDraw(callback?: VoidCallback): void;

        onDrawChildren(callback: VoidCallback): void;

        offDrawChildren(callback?: VoidCallback): void;
        
        onLayoutChildren(callback: VoidCallback): void;

        offLayoutChildren(callback?: VoidCallback): void;
    }
    export function createComponentObserver(id: string | int): ComponentObserver;
    export function getFilteredInspectorTree(filters?: Array<string>): string;
    export function getFilteredInspectorTreeById(id: string, depth: int, filters?: Array<string>): string;
}
export default inspector;